/**
 * @file AT86_Impl.c
 * @author Pavlo Manovi
 * @brief Contains the implementation of methods used to interact with the AT86.
 * 
 * This implementation takes the hardware abstractions defined for the target MCU/Board
 * and uses them to work with the AT86.
 * 
 * The intended design is that an SPI library with the normal IO operations will be exposed
 * as a generic SPI device and that this library will hook into that and define callback
 * functions for the SPI methods.
 * 
 * TODO: Figure out how to also support the 433 MHz band that the AT86 supports.  Requires
 * a hardware change on the ISM Blasta board.  (V2 change)
 *
 *
 * NOTE: Please do not include any hardware specific peripheral logic in AT86_Impl.c, put
 *       it in the Glue library.
 */

#include "AT86_Impl.h"
#include <stdint.h>

/**
 * We statically allocate our AT86 instances because we're not monsters.
 *
 * When initializing the driver, we use these AT86 instances, they can't
 * exist anywhere else.
 */
static AT86_Instance Instance[MAX_AT86_INSTANCES] = {};
static uint8_t currentInstances = 0;
static volatile uint16_t interruptCounts;
static uint8_t txBuf[2048] = {};
static uint8_t rxBuf[2048] = {};
	
	
void AT86_IRQ_Handler(uint8_t atDev);
uint8_t AT86_BB_FSM(baseband_info_t *bb);
uint8_t AT86_FSM(uint8_t atDevNum);
	

/**
 * @brief      { function_description }
 *
 * @param      spiDev      The spi development
 * @param      atDev       The at86 device instance 0 - MAX_AT86_INSTANCES
 *
 * @pre All peripheral devices must be initialized before this function runs.
 *
 * @return     returns at86_return_codes enum values
 */
uint8_t AT86_Init(SpiDevice *spi_dev, IRQDevice *irq_dev, uint8_t atDev)
{
	AT86_Instance *at = &Instance[atDev];
	
	if (spi_dev == NULL || irq_dev == NULL)
	{
		return AT86_ERROR;
	}

	if (currentInstances == MAX_AT86_INSTANCES)
	{
		return AT86_ERROR;
	}

	if (at->initialized == 1)
	{
		return AT86_ERROR;
	}

	// Each AT86 must have its own SPI/IRQ handlers, no doubling up.
	if (currentInstances != 0)
	{
		uint8_t i;
		for (i = 0; i < currentInstances; i++)
		{
			if ((IRQDevice *) &(Instance[i].irqDev) == irq_dev)
			{
				return AT86_ERROR;
			}

			if ((SpiDevice *) &(Instance[i].spiDev) == spi_dev)
			{
				return AT86_ERROR;
			}
		}
	}
	
	currentInstances++;

	at->baseband_2400.baseband_state = AFE_STATE_POWER_OFF;
	at->baseband_900.baseband_state = AFE_STATE_POWER_OFF;
	at->at86_state = AT86_STATE_INIT;

	at->baseband_900.lastIRQ = 0;
	at->baseband_2400.lastIRQ = 0;

	at->baseband_2400.CSMA_EN = 0;
	at->baseband_900.CSMA_EN = 0;
	
	at->baseband_2400.channel_power_assesment = 1; // Special baseband state.
	at->baseband_900.channel_power_assesment = 1; // Special baseband state.

	at->baseband_900.parent = at;
	at->baseband_2400.parent = at;

	//We set the peripheral interface associated with the driver here
	irq_dev->deviceDriver = (void *) at;
	spi_dev->deviceDriver = (void *) at;
	
	//Set the devices here.
	at->irqDev = irq_dev;
	at->spiDev = spi_dev;

	//This is most definitely wrong.
	irq_dev->callback = (void *)(AT86_IRQ_Handler);

	return AT86_OK;
}

uint8_t AT86_Tick(uint8_t atDev)
{
	AT86_Instance *at = &Instance[atDev];
	
	if (at->at86_state != AT86_STATE_INIT)
	{
		//RFn_STATE to check state.
		txBuf[0] = 0x01;
		txBuf[1] = 0x02;
		//Just read from 0's for status.
		glue_spi_dma_transfer(at->spiDev, txBuf, rxBuf, 10);
		while(glue_spi_in_process(at->spiDev));
	
		txBuf[0] = 0x02;
		txBuf[1] = 0x02;
		txBuf[2] = 0x00;
		//Just read from 0's for status.
		glue_spi_dma_transfer(at->spiDev, txBuf, rxBuf, 10);
		while(glue_spi_in_process(at->spiDev));
	}
	
	if (interruptCounts > 0)
	{
		txBuf[0] = 0;
		txBuf[1] = 0;
		txBuf[2] = 0;
		//Just read from 0's for status.
		glue_spi_dma_transfer(at->spiDev, txBuf, rxBuf, 8);
		//TODO: Go do something else while we wait for the SPI/DMA to finish
		while(glue_spi_in_process(at->spiDev));
		
		if (rxBuf[0] == 0x00 && rxBuf[1] == 0x00)
		{
			if (rxBuf[2] != 0x00 || rxBuf[4] != 0x00)
			{
				at->baseband_900.lastIRQ = (rxBuf[2] << 8) & 0xFF00;
				at->baseband_900.lastIRQ &= rxBuf[4] | 0xFF00;
				at->baseband_900.gotIRQ = 1;
			}
			if (rxBuf[3] != 0x00 || rxBuf[5] != 0x00)
			{
				at->baseband_2400.lastIRQ = (rxBuf[3] << 8) & 0xFF00;
				at->baseband_2400.lastIRQ &= rxBuf[5] | 0xFF00;
				at->baseband_2400.gotIRQ = 1;
			}
		}
		else if (rxBuf[1] == 0x00 && rxBuf[2] == 0x00)
		{
			if (rxBuf[3] != 0x00 || rxBuf[5] != 0x00)
			{
				at->baseband_900.lastIRQ = (rxBuf[3] << 8) & 0xFF00;
				at->baseband_900.lastIRQ &= rxBuf[5] | 0xFF00;
				at->baseband_900.gotIRQ = 1;
			}
			if (rxBuf[4] != 0x00 || rxBuf[6] != 0x00)
			{
				at->baseband_2400.lastIRQ = (rxBuf[4] << 8) & 0xFF00;
				at->baseband_2400.lastIRQ &= rxBuf[6] | 0xFF00;
				at->baseband_2400.gotIRQ = 1;
			}
		}
		else
		{
			//Something bad happened...
		}

		uint8_t i = 0;
		interruptCounts = 0;
	}
	
	//TODO: Check current BB state against actual state in register.
	
	AT86_FSM(atDev);
	
	return(AT86_OK);
}

/**
 * @brief      Run this function in the main loop as quickly as possible.
 *
 * @param      atDev  AT86 driver instance.
 *
 * @return     returns at86_return_codes
 * 
 * This function should be thought of as the high-level controller that deals
 * with data buffers/IRQs, etc.  All of the TX/RX state handling happens in the
 * baseband fsms.
 */
uint8_t AT86_FSM(uint8_t atDevNum)
{
	AT86_Instance *atDev = &Instance[atDevNum];
	
	//TODO: Break until we get the first ext interrupt indicating TXRDY.
	switch (atDev->at86_state)
	{
		case (AT86_STATE_INIT):
		
			// Turn off fast oscillator startup.
			// 0x0009 << 0x00
			AT86_write_reg(0x0009, 0x1D, atDev);
			
			// Turn off CLKO
			// 0x0007 << 0x08
			AT86_write_reg(0x0007, 0x08, atDev);
			
			// BBC0_IRQM - 900 - 0x300
			// Set up baseband IRQ mask.
			// Bit 7 - Frame buffer level indication (FBLI)
			// Bit 6 - AGC release interrupt (AGCR)
			// Bit 5 - AGC Hold (AGCH)
			// Bit 4 - Transmitter frame end (TXFE) X
			// Bit 3 - Receiver extended match (RXEM)
			// Bit 2 - Receiver address match (RXAM)
			// Bit 1 - Receiver frame end interrupt (RXFE) X
			// Bit 0 - Receiver frame start interrupt (RXFS)
			AT86_write_reg(0x0300, 0x12, atDev);
			
			// Set up Radio IRQ mask. RF09_IRQM
			// Bit 5 - IRQM.IQIFSF: I/Q IF Synchronization Failure Interrupt Mask
			// Bit 4 - IRQM.TRXERR: Transceiver Error Interrupt Mask X
			// Bit 3 - IRQM.BATLOW: Battery Low Interrupt Mask
			// Bit 2 - IRQM.EDC: Energy Detection Completion Interrupt Mask
			// Bit 1 - IRQM.TRXRDY: Transceiver Ready Interrupt Mask X
			// Bit 0 - IRQM.WAKEUP: Wake-up / Reset Interrupt Mask
			AT86_write_reg(0x0100, 0x1F, atDev);
			
			// Set up baseband IRQ mask. BBC1_IRQM - 900
			// Bit 7 - Frame buffer level indication (FBLI)
			// Bit 6 - AGC release interrupt (AGCR)
			// Bit 5 - AGC Hold (AGCH)
			// Bit 4 - Transmitter frame end (TXFE) X
			// Bit 3 - Receiver extended match (RXEM)
			// Bit 2 - Receiver address match (RXAM)
			// Bit 1 - Receiver frame end interrupt (RXFE) X
			// Bit 0 - Receiver frame start interrupt (RXFS)
			AT86_write_reg(0x0400, 0x12, atDev);
			
			// Set up Radio IRQ mask. RF24_IRQM
			// Bit 5 - IRQM.IQIFSF: I/Q IF Synchronization Failure Interrupt Mask
			// Bit 4 - IRQM.TRXERR: Transceiver Error Interrupt Mask X
			// Bit 3 - IRQM.BATLOW: Battery Low Interrupt Mask
			// Bit 2 - IRQM.EDC: Energy Detection Completion Interrupt Mask
			// Bit 1 - IRQM.TRXRDY: Transceiver Ready Interrupt Mask X
			// Bit 0 - IRQM.WAKEUP: Wake-up / Reset Interrupt Mask
			AT86_write_reg(0x0200, 0x1F, atDev);
			
			//Set output power with PAC register.
			//0x0114 //09
			//0x0214 //24
			
			//Set center frequency for 2.4Ghz to 2427 center.
			//0x90D8
			//CNM = 0
			AT86_write_reg(RF24_CCF0H, 0x90, atDev);
			AT86_write_reg(RF24_CCF0L, 0xD8, atDev);
			AT86_write_reg(RF24_CNM, 0x00, atDev);
			
			glue_spi0_dma_transfer(atDev->spiDev, txBuf, rxBuf, 3);
			AT86_write_reg(0x0114, 0x60, atDev);
			AT86_write_reg(0x0214, 0x60, atDev);
			
			atDev->at86_state = AT86_STATE_IDLE;
			break;

		//TODO: This system fails if we miss interrupts.  We'll need to have a
		//timeout and an extra state that polls the state and kicks the bb state
		//with the polled state and calls the FSM update.
		case (AT86_STATE_IDLE):
			//Poll for data?
			asm("");
			if (atDev->baseband_900.gotIRQ && atDev->baseband_2400.gotIRQ)
			{
				atDev->baseband_900.gotIRQ = 0;
				atDev->baseband_2400.gotIRQ = 0;
				
				atDev->at86_state = AT86_STATE_ALL_UPDATE;
				break;
			}
			else if (atDev->baseband_900.gotIRQ)
			{
				atDev->baseband_900.gotIRQ = 0;

				atDev->at86_state = AT86_STATE_0900_UPDATE;
				break;
			}
			else if (atDev->baseband_2400.gotIRQ)
			{
				atDev->baseband_2400.gotIRQ = 0;

				atDev->at86_state = AT86_STATE_2400_UPDATE;
				break;
			}
			
			atDev->at86_state = AT86_STATE_IDLE;
			break;

		case (AT86_STATE_0900_UPDATE):

			//if we're doing something that doesn't cause an
			//interrupt upon completion, getSpiStatus will
			//return if there's a bulk spi transaction in
			//process.
			//if (getSpiStatus() == DevSpiState_IN_PROCESS)
			//{
			//	break;
			//	atDev->at86_state = AT86_STATE_0900_UPDATE;
			//}
			AT86_BB_FSM(&atDev->baseband_900);
			
			atDev->at86_state = AT86_STATE_IDLE;
			break;

		case (AT86_STATE_2400_UPDATE):

			//if we're doing something that doesn't cause an
			//interrupt upon completion, getSpiStatus will
			//return if there's a bulk spi transaction in
			//process.
			//if (getSpiStatus() == DevSpiState_IN_PROCESS)
			//{
			//	break;
			//	atDev->at86_state = AT86_STATE_2400_UPDATE;
			//}
			AT86_BB_FSM(&atDev->baseband_2400);
			
			atDev->at86_state = AT86_STATE_IDLE;
			break;
		
		case (AT86_STATE_ALL_UPDATE):
		
			atDev->at86_state = AT86_STATE_0900_UPDATE;
			AT86_BB_FSM(&atDev->baseband_900);
			atDev->at86_state = AT86_STATE_2400_UPDATE;
			AT86_BB_FSM(&atDev->baseband_2400);
			
			atDev->at86_state = AT86_STATE_IDLE;
			break;
			
		default:
			while(1);
			break;
			
	}

	return(AT86_OK);
}

/**
 * @brief      AT86 baseband statemachine for basic/or ieee mac (without ACK)
 *
 * @param      atDev  The at development
 * @param      bb     { parameter_description }
 *
 * @return     { description_of_the_return_value }
 * 
 * This captures basic state transitions.  IEEE MAC state-machine is different
 * as it supports options to automatically transition to the RX state from TX
 * after receiving an ACK.  IEEE MAC can be used with the regular BB FSM if we're
 * only using the MAC definition to do frame filtering.  Not using frame filtering
 * forces the micro controller to handle ALL data that the BB receives as it is truly
 * raw.
 * 
 * This FSM may automatically support CCS/wait to send as it should automatically send
 * when appropriate after sending the TX command.  TODO: Must verify this.
 */
uint8_t AT86_BB_FSM(baseband_info_t *bb)
{
	switch (bb->baseband_state)
	{
		case (AFE_STATE_POWER_OFF):
			asm("");
			if (bb->lastIRQ & WAKEUP)
			{
				bb->lastIRQ &= ~WAKEUP;
				bb->baseband_state = AFE_STATE_TRXOFF;

				// Send SPI command to get us into TXPREP
				if (bb->parent->at86_state == AT86_STATE_0900_UPDATE)
				{
					AT86_write_reg(RF09_CMD, RF_CMD_TXPREP, bb->parent);
				}
				else if (bb->parent->at86_state == AT86_STATE_2400_UPDATE)
				{
					AT86_write_reg(RF24_CMD, RF_CMD_TXPREP, bb->parent);
				}
			}
			break;

		case (AFE_STATE_TRXOFF):
			asm("");
			if (bb->lastIRQ & TRXRDY)
			{
				bb->lastIRQ &= ~TRXRDY;
				bb->baseband_state = AFE_STATE_TXPREP;
				goto txprep;
			}
			break;

		case (AFE_STATE_TRANSITION):
			asm("");
			if (bb->lastIRQ & TRXRDY)
			{
				bb->lastIRQ &= ~TRXRDY;
				bb->baseband_state = AFE_STATE_TXPREP;
				goto txprep;
			}
			break;			

		case (AFE_STATE_TXPREP):
txprep:
			asm("");
			if (bb->lastIRQ & TRXERR)
			{
				bb->lastIRQ &= ~TRXERR;
				bb->baseband_state = AFE_STATE_TXPREP;
			}
			else if (bb->lastIRQ & TRXRDY)
			{
				bb->lastIRQ &= ~TRXRDY;
				bb->baseband_state = AFE_STATE_TXPREP;
			}

			{
				//If we need to send data, which the AT86 top-level-fsm handles, we will do so here.
				//
				//We will only initialize sending data from this state if we're manually handling
				//CCA and energy detection thresholds.  Otherwise CCATX is initiated from the RX state.

				if (bb->channel_power_assesment == 1)
				{
					//Turn off baseband.
					//PC.BBEN to 0
					//RX to RFn_CMD
					//EDC.EDM to 1

					//Send transition command to RX
					if (bb->parent->at86_state == AT86_STATE_0900_UPDATE)
					{
						//0b01010100 Default BBCn_PC
						//0b01010000
						AT86_write_reg(BBC0_PC, 0x50, bb->parent);
						AT86_write_reg(RF09_CMD, RF_CMD_RX, bb->parent);
						AT86_write_reg(RF09_EDC, 0x01, bb->parent);
					}
					else if (bb->parent->at86_state == AT86_STATE_2400_UPDATE)
					{
						AT86_write_reg(BBC1_PC, 0x50, bb->parent);
						AT86_write_reg(RF24_CMD, RF_CMD_RX, bb->parent);
						AT86_write_reg(RF24_EDC, 0x01, bb->parent);
					}
					
					bb->baseband_state = AFE_STATE_RX;
					break;
				}
			}

			break;

		case (AFE_STATE_TX):
			if (bb->lastIRQ & TXFE)
			{
				bb->lastIRQ &= ~TXFE;
				bb->baseband_state = AFE_STATE_TXPREP;

				//return transmission complete, which will be handled in AT86 state machine, where the frame will be dequeued.
			}
			break;

		case (AFE_STATE_RX):
			if (bb->lastIRQ & EDC)
			{
				bb->lastIRQ &= ~EDC;
				//Got energy detection results.
				
				//If we are still in the power assessment override state,
				//reissue the single shot energy detection.
				if (bb->channel_power_assesment)
				{
					if (bb->parent->at86_state == AT86_STATE_0900_UPDATE)
					{
						AT86_read_bytes_from_reg(0x010F, 3, bb->parent);
						AT86_write_reg(RF09_EDD, 0xFF, bb->parent); //Super long integration period: 128 uS * 2^6
						AT86_write_reg(RF09_EDC, 0x01, bb->parent);
					}
					else if (bb->parent->at86_state == AT86_STATE_2400_UPDATE)
					{
						AT86_read_bytes_from_reg(0x020F, 3, bb->parent);
						AT86_write_reg(RF24_EDD, 0xFF, bb->parent); //Super long integration period: 128 uS * 2^6
						AT86_write_reg(RF24_EDC, 0x01, bb->parent);
					}
					bb->baseband_state = AFE_STATE_RX;
				}
				else
				{
					//Send TXPREP command
					//Enable baseband.
					if (bb->parent->at86_state == AT86_STATE_0900_UPDATE)
					{
						AT86_write_reg(BBC0_PC, 0x54, bb->parent);
						AT86_write_reg(RF09_CMD, RF_CMD_TXPREP, bb->parent);
					}
					else if (bb->parent->at86_state == AT86_STATE_2400_UPDATE)
					{
						AT86_write_reg(BBC1_PC, 0x50, bb->parent);
						AT86_write_reg(RF24_CMD, RF_CMD_TXPREP, bb->parent);
					}
					
					bb->baseband_state = AFE_STATE_TXPREP;
				}
			}
		
			if (bb->lastIRQ & RXFE)
			{
				bb->lastIRQ &= ~RXFE;
				bb->baseband_state = AFE_STATE_TXPREP;
			}

			if (bb->lastIRQ & AGCH)
			{
				bb->lastIRQ &= ~AGCH;
				//AGC is held, preamble detected.
			}

			if (bb->lastIRQ & RXFS)
			{
				bb->lastIRQ &= ~RXFS;
				//OFDM frame header detected.
			}

			if (bb->lastIRQ & RXAM)
			{
				bb->lastIRQ &= ~RXAM;
				//Matching address in frame header.
			}

			// if (pending send operation)
			{
				// The procedure CCATX is enabled if the sub-register AMCS.CCATX is set to 1.
				// It is started with a single energy detection (ED) measurement
				// (by writing the value 0x1 to sub-register EDC.EDM;
				
				//BBEN = 0;  //BBEN will automatically be reenabled if it needs to be sent.
				//EDM = 1;
				//bb->baseband_state = ;
			}
			

			break;
		case (AFE_STATE_RX_CCATX):
			if (bb->lastIRQ & (TXFE | EDC))
			{
				bb->lastIRQ &= ~(TXFE | EDC);
				//Busy channel detected, jump back to the RX state.
				
				bb->baseband_state = AFE_STATE_RX;
			}

			if (bb->lastIRQ & (TRXRDY | EDC))
			{
				bb->lastIRQ &= ~(TRXRDY | EDC);
				//Channel free, will transition to TX state.  Assumes this is CCATX.
				
				bb->baseband_state = AFE_STATE_TX;
			}

			break;

		case (AFE_STATE_SLEEP):
			break;

		case (AFE_STATE_DEEP_SLEEP):
			if (bb->lastIRQ & WAKEUP)
			{
				bb->lastIRQ &= ~WAKEUP;
				bb->baseband_state = AFE_STATE_TXPREP;
			}
			break;

		}
}

void AT86_IRQ_Handler(uint8_t atDev)
{
	//Increment the number of interrupts that occurred
	//since the last time the FSM was run.
	interruptCounts++;
}

void AT86_write_reg(uint16_t reg, uint8_t val, AT86_Instance *at)
{
	txBuf[0] = 0x80 | (reg >> 8);
	txBuf[1] = reg & 0x00FF;
	txBuf[2] = val;
	glue_spi_dma_transfer(at->spiDev, txBuf, rxBuf, 3);
	while(glue_spi_in_process(at->spiDev));		
}

void AT86_read_bytes_from_reg(uint16_t reg, uint16_t numBytes, AT86_Instance *at)
{
	txBuf[0] = 0x00 | (reg >> 8);
	txBuf[1] = reg & 0x00FF;
	glue_spi_dma_transfer(at->spiDev, txBuf, rxBuf, 2 + numBytes);
	while(glue_spi_in_process(at->spiDev));		
}