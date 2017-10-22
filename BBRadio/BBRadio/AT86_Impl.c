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

static uint8_t currentInstances = 0;

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

	at->baseband_2400.CSMA_EN = 1;

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
uint8_t AT86_FSM(AT86_Instance *atDev)
{
	switch (atDev->at86_state)
	{
		case (AT86_STATE_INIT):
			//Configure the AT86.
			break;

		//TODO: This system fails if we miss interrupts.  We'll need to have a
		//timeout and an extra state that polls the state and kicks the bb state
		//with the polled state and calls the FSM update.
		case (AT86_STATE_IDLE):
			//Poll for data?
			//
			if (atDev->baseband_2400.gotIRQ != 0)
			{
				atDev->baseband_2400.gotIRQ = 0;

				atDev->at86_state = AT86_STATE_AFE1_UPDATE;

				break;
			}

			if (atDev->baseband_900.gotIRQ != 0)
			{
				atDev->baseband_900.gotIRQ = 0;

				atDev->at86_state = AT86_STATE_AFE2_UPDATE;

				break;
			}

			atDev->at86_state = AT86_STATE_IDLE;

			break;

		case (AT86_STATE_AFE1_UPDATE):

			//if we're doing something that doesn't cause an
			//interrupt upon completion, getSpiStatus will
			//return if there's a bulk spi transaction in
			//process.
			//if (getSpiStatus() == DevSpiState_IN_PROCESS)
			//{
			//	break;
			//	atDev->at86_state = AT86_STATE_AFE1_UPDATE;
			//}

			AT86_BB_FSM(&atDev->baseband_2400);

			atDev->at86_state = AT86_STATE_IDLE;

			break;

		case (AT86_STATE_AFE2_UPDATE):

			//if we're doing something that doesn't cause an
			//interrupt upon completion, getSpiStatus will
			//return if there's a bulk spi transaction in
			//process.
			//if (getSpiStatus() == DevSpiState_IN_PROCESS)
			//{
			//	break;
			//	atDev->at86_state = AT86_STATE_AFE2_UPDATE;
			//}

			AT86_BB_FSM(&atDev->baseband_900);

			atDev->at86_state = AT86_STATE_IDLE;

			break;
	}

	return(AT86_OK);

	//For our hello world application with the AT86 we'll only TX or only RX.
	//This will require two devices though it will allow me to test the RX and TX
	//logic separately.
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
			if (bb->lastIRQ & WAKEUP)
			{
				bb->baseband_state = AFE_STATE_TRXOFF;

				// Send SPI command to get us into TXPREP
			}
			break;

		case (AFE_STATE_TRXOFF):
			if (bb->lastIRQ & TRXRDY)
			{
				bb->baseband_state = AFE_STATE_TXPREP;
			}
			break;

		case (AFE_STATE_TRANSITION):
			if (bb->lastIRQ & TRXRDY)
			{
				bb->baseband_state = AFE_STATE_TXPREP;
			}
			break;			

		case (AFE_STATE_TXPREP):
			if (bb->lastIRQ & TRXERR)
			{
				bb->baseband_state = AFE_STATE_TXPREP;
			}
			else if (bb->lastIRQ & TRXRDY)
			{
				bb->baseband_state = AFE_STATE_TXPREP;
			}

			{
				//If we need to send data, which the AT86 top-level-fsm handles, we will do so here.
				//
				//We will only initialize sending data from this state if we're manually handling
				//CCA and energy detection thresholds.  Otherwise CCATX is initiated from the RX state.

				if (bb->CSMA_EN == 1)
				{
					bb->baseband_state = AFE_STATE_RX;

					//Send command RX

					break;
				}
			}

			break;

		case (AFE_STATE_TX):
			if (bb->lastIRQ & TXFE)
			{
				bb->baseband_state = AFE_STATE_TXPREP;

				//return transmission complete, which will be handled in AT86 state machine, where the frame will be dequeued.
			}
			break;

		case (AFE_STATE_RX):
			if (bb->lastIRQ & RXFE)
			{
				bb->baseband_state = AFE_STATE_TXPREP;
			}

			if (bb->lastIRQ & AGCH)
			{
				//AGC is held, preamble detected.
			}

			if (bb->lastIRQ & RXFS)
			{
				//OFDM frame header detected.
			}

			if (bb->lastIRQ & RXAM)
			{
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
				//Busy channel detected, jump back to the RX state.
				
				bb->baseband_state = AFE_STATE_RX;
			}

			if (bb->lastIRQ & (TRXRDY | EDC))
			{
				//Channel free, will transition to TX state.  Assumes this is CCATX.
				
				bb->baseband_state = AFE_STATE_TX;
			}

			break;

		case (AFE_STATE_SLEEP):
			break;

		case (AFE_STATE_DEEP_SLEEP):
			if (bb->lastIRQ & WAKEUP)
			{
				bb->baseband_state = AFE_STATE_TXPREP;
			}
			break;

		}
}

void AT86_IRQ_Handler(uint8_t atDev)
{
	//atDev->afe_900.gotIRQ++;
	//atDev->afe_2400.gotIRQ++;

	//Kick off SPI transaction here.  (Should be DMA'd)
}


