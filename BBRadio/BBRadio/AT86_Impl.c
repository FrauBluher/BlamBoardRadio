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
static uint8_t testTxBuf[] = "00Hello computer-man.";
static uint8_t testTxBufLen = 19;
static uint8_t txBuf[2050] = {};
static uint8_t rxBuf[2048] = {};
	
void AT86_IRQ_Handler(uint8_t pinNum);
uint8_t AT86_BB_FSM(baseband_info_t *bb);
uint8_t AT86_FSM(uint8_t atDevNum);

void AT86_fill_BBC0_frame_buffer(uint8_t *buf, uint16_t numBytes, AT86_Instance *at);
void AT86_fill_BBC1_frame_buffer(uint8_t *buf, uint16_t numBytes, AT86_Instance *at);

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
	
	at->numInterrupts = 0;
	
	at->baseband_2400.channel_power_assesment = 0; // Special baseband state.
	at->baseband_900.channel_power_assesment = 0; // Special baseband state.
	
	//TODO: Connect this logic to configuration parameters.
	//THIS IS JUST FOR TESTING LOOPBACK.
	if (atDev == 0)
	{
		at->baseband_2400.pendingTransmit = 0;
		at->baseband_900.pendingTransmit = 0;
	}
	else
	{
		at->baseband_2400.pendingTransmit = 1;
		at->baseband_900.pendingTransmit = 1;
	}

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
	
	//at->initialized = 1;

	return AT86_OK;  
}

uint8_t AT86_Tick(uint8_t atDev)
{
	AT86_Instance *at = &Instance[atDev];
	
	if (!at->initialized)
	{
		AT86_FSM(atDev);
		at->initialized = 1;
	}
	
	if (at->at86_state != AT86_STATE_INIT)
	{
		//RFn_STATE to check state.
		txBuf[0] = 0x01;
		txBuf[1] = 0x02;
		//Just read from 0's for status.
		glue_spi_dma_transfer(at->spiDev, txBuf, rxBuf, 10);
		
		txBuf[0] = 0x02;
		txBuf[1] = 0x02;
		txBuf[2] = 0x00;
		//Just read from 0's for status.
		glue_spi_dma_transfer(at->spiDev, txBuf, rxBuf, 10);
	}
	
	if (at->numInterrupts > 0)
	{
		txBuf[0] = 0;
		txBuf[1] = 0;
		txBuf[2] = 0;
		//Just read from 0's for status.
		glue_spi_dma_transfer(at->spiDev, txBuf, rxBuf, 8);
		
		if (rxBuf[0] == 0x00 && rxBuf[1] == 0x00)
		{
			if (rxBuf[2] != 0x00 || rxBuf[4] != 0x00)
			{
				at->baseband_900.lastIRQ = (rxBuf[2] << 8) & 0xFF00;
				at->baseband_900.lastIRQ |= rxBuf[4] & 0x00FF;
				at->baseband_900.gotIRQ = 1;
				at->numInterrupts = 0;
			}
			if (rxBuf[3] != 0x00 || rxBuf[5] != 0x00)
			{
				at->baseband_2400.lastIRQ = (rxBuf[3] << 8) & 0xFF00;
				at->baseband_2400.lastIRQ |= rxBuf[5] & 0x00FF;
				at->baseband_2400.gotIRQ = 1;
				at->numInterrupts = 0;
			}
		}
		else if (rxBuf[1] == 0x00 && rxBuf[2] == 0x00)
		{
			if (rxBuf[3] != 0x00 || rxBuf[5] != 0x00)
			{
				at->baseband_900.lastIRQ = (rxBuf[3] << 8) & 0xFF00;
				at->baseband_900.lastIRQ |= rxBuf[5] & 0x00FF;
				at->baseband_900.gotIRQ = 1;
				at->numInterrupts = 0;
			}
			if (rxBuf[4] != 0x00 || rxBuf[6] != 0x00)
			{
				at->baseband_2400.lastIRQ = (rxBuf[4] << 8) & 0xFF00;
				at->baseband_2400.lastIRQ |= rxBuf[6] & 0x00FF;
				at->baseband_2400.gotIRQ = 1;
				at->numInterrupts = 0;
			}
		}
		else
		{
			//Something bad happened...
		}
	}

	AT86_FSM(atDev);

	//TODO: Check current BB state against actual state in register.
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
			
			AT86_write_reg(0x0104, 0x30, atDev);
			AT86_write_reg(0x0105, 0x20, atDev);
			AT86_write_reg(0x0106, 0x8D, atDev);
			AT86_write_reg(0x0107, 0x03, atDev);
			AT86_write_reg(0x0109, 0x09, atDev);
			AT86_write_reg(0x010A, 0x83, atDev);
			AT86_write_reg(0x010F, 0x7A, atDev);
			
			AT86_write_reg(0x0112, 0x0B, atDev);
			AT86_write_reg(0x0113, 0x83, atDev);
			AT86_write_reg(0x0114, 0x7C, atDev);
			
			AT86_write_reg(0x0301, 0x56, atDev);
			AT86_write_reg(0x030C, 0x03, atDev);
			
			AT86_write_reg(0x0204, 0x30, atDev);
			AT86_write_reg(0x0205, 0x20, atDev);
			AT86_write_reg(0x0206, 0x8D, atDev);
			AT86_write_reg(0x0207, 0x03, atDev);
			AT86_write_reg(0x0209, 0x09, atDev);
			AT86_write_reg(0x020A, 0x83, atDev);
			AT86_write_reg(0x020F, 0x7A, atDev);
			
			AT86_write_reg(0x0212, 0x0B, atDev);
			AT86_write_reg(0x0213, 0x83, atDev);
			AT86_write_reg(0x0214, 0x7C, atDev);
			
			AT86_write_reg(0x0401, 0x56, atDev);
			AT86_write_reg(0x040C, 0x03, atDev);
			
			atDev->at86_state = AT86_STATE_IDLE;
			break;

		//TODO: This system fails if we miss interrupts.  We'll need to have a
		//timeout and an extra state that polls the state and kicks the bb state
		//with the polled state and calls the FSM update.
		case (AT86_STATE_IDLE):
			//Poll for data?
			asm("");
			if (atDev->baseband_900.gotIRQ && atDev->baseband_2400.gotIRQ || atDev->baseband_900.pendingTransmit && atDev->baseband_2400.pendingTransmit)
			{
				atDev->baseband_900.gotIRQ = 0;
				atDev->baseband_2400.gotIRQ = 0;
				
				atDev->at86_state = AT86_STATE_ALL_UPDATE;
				break;
			}
			else if (atDev->baseband_900.gotIRQ || atDev->baseband_900.pendingTransmit)
			{
				atDev->baseband_900.gotIRQ = 0;

				atDev->at86_state = AT86_STATE_0900_UPDATE;
				break;
			}
			else if (atDev->baseband_2400.gotIRQ || atDev->baseband_2400.pendingTransmit)
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
				else if (bb->pendingTransmit == 0)
				{
					if (bb->parent->at86_state == AT86_STATE_0900_UPDATE)
					{
						AT86_write_reg(RF09_CMD, RF_CMD_RX, bb->parent);
					}
					else if (bb->parent->at86_state == AT86_STATE_2400_UPDATE)
					{
						AT86_write_reg(RF24_CMD, RF_CMD_RX, bb->parent);
					}
					
					bb->baseband_state = AFE_STATE_RX;
					break;
				}
				else if (bb->pendingTransmit)
				{
					//Take what's in the pending buffer from the application layer
					//and load it into the baseband buffer vector.
					// Send SPI command to get us into TXPREP
					if (bb->parent->at86_state == AT86_STATE_0900_UPDATE)
					{
						AT86_fill_BBC0_frame_buffer(testTxBuf, testTxBufLen, bb->parent);
						AT86_write_reg(RF09_CMD, RF_CMD_TX, bb->parent);
					}
					else if (bb->parent->at86_state == AT86_STATE_2400_UPDATE)
					{
						AT86_fill_BBC1_frame_buffer(testTxBuf, testTxBufLen, bb->parent);
						AT86_write_reg(RF24_CMD, RF_CMD_TX, bb->parent);
					}
					
					bb->baseband_state = AFE_STATE_TX;
					break;
				}
			}

			break;

		case (AFE_STATE_TX):
			asm("");
			if (bb->lastIRQ & TXFE)
			{
				bb->lastIRQ &= ~TXFE;
				bb->baseband_state = AFE_STATE_TXPREP;
			}
			break;

		case (AFE_STATE_RX):
			if (bb->lastIRQ & EDC)
			{
				bb->lastIRQ &= ~EDC;
				uint16_t edv;
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

//TODO: Define pin number when initing the atDev in Glue and don't
//      put the real pin numbers here in the irq handler.
void AT86_IRQ_Handler(uint8_t pinNum)
{
	//Increment the number of interrupts that occurred
	//since the last time the FSM was run.
	if (pinNum == 32)
	{
		Instance[AT86_INSTANCE0].numInterrupts++;;
	}
	if (pinNum == 119)
	{
		Instance[AT86_INSTANCE1].numInterrupts++;;
	}
}

void AT86_write_reg(uint16_t reg, uint8_t val, AT86_Instance *at)
{
	txBuf[0] = 0x80 | (reg >> 8);
	txBuf[1] = reg & 0x00FF;
	txBuf[2] = val;
	glue_spi_dma_transfer(at->spiDev, txBuf, rxBuf, 3);
}

void AT86_read_bytes_from_reg(uint16_t reg, uint16_t numBytes, AT86_Instance *at)
{
	txBuf[0] = 0x00 | (reg >> 8);
	txBuf[1] = reg & 0x00FF;
	glue_spi_dma_transfer(at->spiDev, txBuf, rxBuf, 2 + numBytes);	
}

void AT86_fill_BBC0_frame_buffer(uint8_t *buf, uint16_t numBytes, AT86_Instance *at)
{
	txBuf[0] = 0x80 | (BBC0_TXFLL >> 8);
	txBuf[1] = BBC0_TXFLL & 0x00FF;
	txBuf[2] = 19;
	txBuf[3] = 0;
	glue_spi_dma_transfer(at->spiDev, txBuf, rxBuf, 4);
	
	buf[0] = 0x80 | (BBC0_FBTXS >> 8);
	buf[1] = BBC0_FBTXS & 0x00FF;
	glue_spi_dma_transfer(at->spiDev, buf, rxBuf, 2 + numBytes);
}

void AT86_fill_BBC1_frame_buffer(uint8_t *buf, uint16_t numBytes, AT86_Instance *at)
{
	txBuf[0] = 0x80 | (BBC1_TXFLL >> 8);
	txBuf[1] = BBC1_TXFLL & 0x00FF;
	txBuf[2] = 19;
	txBuf[3] = 0;
	glue_spi_dma_transfer(at->spiDev, txBuf, rxBuf, 4);
		
	buf[0] = 0x80 | (BBC1_FBTXS >> 8);
	buf[1] = BBC1_FBTXS & 0x00FF;
	glue_spi_dma_transfer(at->spiDev, buf, rxBuf, 2 + numBytes);
}