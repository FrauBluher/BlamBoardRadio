/*
 * Hides private methods and variables from global scope.
 */
#include "Glue.h"
#include <stdbool.h>
#include <stdint.h>
#include <hal_spi_m_dma.h>
#include <hal_dac_sync.h>
#include <hal_ext_irq.h>
#include <hal_spi_m_dma.h>
#include <hal_i2c_m_sync.h>
#include <hal_usart_sync.h>
#include <hpl_uart_base.h>
#include <hal_usart_async.h>
#include <hpl_uart_base.h>

#include "hal_usb_device.h"

extern struct dac_sync_descriptor DAC_0;
extern struct spi_m_dma_descriptor SPI_0;
extern struct i2c_m_sync_desc I2C_0;
extern struct i2c_m_sync_desc I2C_INSTANCE;
extern struct usart_sync_descriptor  USART_0;
extern struct usart_async_descriptor USART_1;

static bool peripherals_inited = false;

extern struct spi_m_dma_descriptor SPI_0;

SpiDevice SPI0;

IRQDevice IRQ0;

//SPI0
//uint16_t spiTxBuf[] Lives in AT86_Impl.  We don't double buffer it in here.
uint16_t spi0RxBuf[2048] = {};
uint16_t spi0RxBufBytesAvail = 0;

void glue_init(void)
{
	//Set up SPI0
	//Set up IRQ0
	SPI0.deviceDriver = SPI_0;
	//Set call-backs for spi here.
	spi_m_dma_register_callback(SPI0.deviceDriver, SPI_M_DMA_CB_TX_DONE, spi_m_dma_cb_t func);
	spi_m_dma_register_callback(SPI0.deviceDriver, SPI_M_DMA_CB_RX_DONE, spi_m_dma_cb_t func);
	spi_m_dma_register_callback(SPI0.deviceDriver, SPI_M_DMA_CB_ERROR, spi_m_dma_cb_t func);

	AT86_Init(SPI0, IRQ0, AT86_INSTANCE0);
}

void glue_set_peripherals_inited(void)
{
	peripherals_inited = true;
}

//Returns if glue_set_peripherals_inited was called before.  Crashes otherwise.
void glue_enforce_driver_init(void)
{
	if (peripherals_inited == false)
	{
		glue_crash_and_burn();
	}
}

void glue_spi0_dma_send_bytes(SpiDevice* spi, uint16_t *buf, uint16_t numBytes)
{
	//Send data with HAL here.
}

void glue_spi0_cb_tx_done(void)
{

}

void glue_spi0_cb_rx_done(void)
{

}

void glue_spi0_cb_error(void)
{
	
}

