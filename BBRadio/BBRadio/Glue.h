/*
 * This header contains all of the other header files necessary to interact with peripherals
 * which have been set up with Atmel Start.
 *
 * Here is where we also glue together a few types to work with my pseudo hardware agnostic
 * peripheral device scheme that I use between projects.  Think 'FooDev'
 *
 * If using atmel start to set up peripherals (you should, it's easy) make sure to initialize
 * the glue library after the Atmel Start init code (usually called from main.c to driver_init.c).
 */ 


#ifndef GLUE_H_
#define GLUE_H_

#include <stdint.h>

/*
 * Define board type either here or somewhere else in the code or during compilation to glue
 * peripheral/board code and generic drivers together.
 */
#define BLAMBOARD_V_1_RADIO
//#define BLAMBOARD_V_2 // Doesn't exist yet.

#ifdef BLAMBOARD_V_1_RADIO

#include <driver_init.h>
#include "atmel_start_pins.h"

//Glue together the generic External Interrupt IRQCallbackFcn.
typedef ext_irq_cb_t IrqCallbackFcn;

//Glue together the generic External Interrupt IRQCallbackFcn.
//typedef spi_m_dma_cb_t SpiIrqCallbackFcn;

//Glue together the generic SpiDevice and the hardware specific descriptor.
typedef struct 
{
	void *halSpiDriver;
	void *deviceDriver;
}SpiDevice;

//Placeholder.
typedef struct
{
	void *halIRQDriver;
	void *deviceDriver;
	IrqCallbackFcn callback;
} IRQDevice;

void glue_init(void);

void glue_set_peripherals_inited(void);

//Returns if glue_set_peripherals_inited was called before.  Crashes otherwise.
void glue_enforce_driver_init(void);

bool glue_spi_in_process(SpiDevice *spi_dev);

//For use during debugging.  Mainly used to check that things don't return zero.
static inline void glue_crash_and_burn(void)
{
	while(1)
	{
		gpio_toggle_pin_level(LED0);
		//delay_ms(1);
		uint8_t test;
		for(uint32_t i = 0; i < 150000000; i++)
		{
			test++;
			asm(""); // To stop meddlesome optimization
		}
	}
}

/*
 *
 * SPI HAL-AL
 *
 */
void glue_spi_dma_transfer(SpiDevice* spi, uint8_t *txBuf, uint8_t *rxBuf, uint16_t numBytes);

#else
#error "We don't support other blamboard hardware yet."
#endif

/************************************************************************/
/* XDMAC Should be configured on the ATSAM(E/V/S)7x series with the     */
/* following flags for SPI/DMA for channels 1/0.                        */
/* 
xdmac_tx_cfg.mbr_cfg = XDMAC_CC_TYPE_PER_TRAN |
		XDMAC_CC_MBSIZE_SINGLE |
		XDMAC_CC_DSYNC_MEM2PER |
		XDMAC_CC_CSIZE_CHK_1 |
		XDMAC_CC_DWIDTH_BYTE |
		XDMAC_CC_SIF_AHB_IF0 |/
		XDMAC_CC_DIF_AHB_IF1 |/
		XDMAC_CC_SAM_INCREMENTED_AM |
		XDMAC_CC_DAM_FIXED_AM |
		XDMAC_CC_PERID(SPI0_XDMAC_TX_CH_NUM);
		
		xdmac_rx_cfg.mbr_cfg = XDMAC_CC_TYPE_PER_TRAN |
		XDMAC_CC_MBSIZE_SINGLE |
		XDMAC_CC_DSYNC_PER2MEM |
		XDMAC_CC_CSIZE_CHK_1 |
		XDMAC_CC_DWIDTH_BYTE|
		XDMAC_CC_SIF_AHB_IF1 |/
		XDMAC_CC_DIF_AHB_IF0 |/
		XDMAC_CC_SAM_FIXED_AM |
		XDMAC_CC_DAM_INCREMENTED_AM |/
		XDMAC_CC_PERID(SPI0_XDMAC_RX_CH_NUM);
/************************************************************************/


#endif /* GLUE_H_ */