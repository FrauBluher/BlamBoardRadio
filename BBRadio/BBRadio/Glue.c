/*
 * Hides private methods and variables from global scope.
 */
#include "Glue.h"
#include "AT86_Impl.h"
#include <stdbool.h>
#include <stdint.h>
#include <driver_init.h>

static bool peripherals_inited = false;

//For testing...
uint16_t extInts = 0;

SpiDevice SPI_ZERO;

IRQDevice IRQ_ZERO;

//SPI0
//uint16_t spiTxBuf[] Lives in AT86_Impl.  We don't double buffer it in here.
uint8_t spi0RxBuf[2048] = {};
uint16_t spi0RxBufBytesAvail = 0;
static void glue_spi0_cb_tx_done(struct _dma_resource *resource);
static void glue_spi0_cb_rx_done(struct _dma_resource *resource);
static void glue_spi0_cb_error(struct _dma_resource *resource);


void glue_init(void)
{
	//Set up SPI0
	//Set up IRQ0
	SPI_ZERO.halSpiDriver = &SPI_0;
	//IRQ_ZERO.halIRQDriver = IRQ0;
	
	//Set call-backs for spi here.
	spi_m_dma_register_callback(SPI_ZERO.halSpiDriver, SPI_M_DMA_CB_TX_DONE, glue_spi0_cb_tx_done);
	spi_m_dma_register_callback(SPI_ZERO.halSpiDriver, SPI_M_DMA_CB_RX_DONE, glue_spi0_cb_rx_done);
	spi_m_dma_register_callback(SPI_ZERO.halSpiDriver, SPI_M_DMA_CB_ERROR, glue_spi0_cb_error);

	AT86_Init(&SPI_ZERO, &IRQ_ZERO, AT86_INSTANCE0);
	
	spi_m_dma_set_mode(&SPI_0, SPI_MODE_0);
	spi_m_dma_set_baudrate(&SPI_0, 100000);
	spi_m_dma_set_char_size(&SPI_0, SPI_CHAR_SIZE_8);
	//spi_m_sync_set_mode(&SPI_0, SPI_MODE_0);
	//spi_m_sync_set_baudrate(&SPI_0, 100000);
	//spi_m_sync_set_char_size(&SPI_0, SPI_CHAR_SIZE_8);
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

void glue_spi0_dma_send_bytes(SpiDevice* spi, uint8_t *buf, uint16_t numBytes)
{
	gpio_set_pin_level(CS, false);
	
	
	spi_m_dma_enable(&SPI_0);
	spi_m_dma_transfer(spi->halSpiDriver, buf, (uint8_t* const) spi0RxBuf, numBytes);
}

void glue_spi0_cb_tx_done(struct _dma_resource *resource)
{
	//gpio_set_pin_level(CS, true);
	
	int i;
	i = 0;
	i++;
	asm(""); // To stop meddlesome optimization
}

void glue_spi0_cb_rx_done(struct _dma_resource *resource)
{
	gpio_set_pin_level(CS, true);
	
	int i;
	i = 0;
	i++;
	asm(""); // To stop meddlesome optimization
}

void glue_spi0_cb_error(struct _dma_resource *resource)
{
	gpio_set_pin_level(CS, true);
	
	int i;
	i = 0;
	i++;
	asm(""); // To stop meddlesome optimization
}

static uint8_t example_SPI_0[12] = "Hello World!";

static void tx_complete_cb_SPI_0(struct _dma_resource *resource)
{
	/* Transfer completed */
	asm("");
	asm("BKPT #1");
	int i;
	i++;
	asm("");
}

uint8_t txBuf[1024] = {};
uint8_t rxBuf[1024] = {};

void SPI_0_example1(void)
{
	gpio_set_pin_level(CS, false);
	
	txBuf[0] = 0x00;
	txBuf[1] = 0x00;
	
	spi_m_dma_enable(&SPI_0);
	spi_m_dma_transfer(&SPI_0, txBuf, rxBuf, 1024);
}


/*
void SPI_0_example1(void)
{
	gpio_set_pin_level(CS, false);
	
	struct spi_xfer tfr;
	
	tfr.rxbuf = rxBuf;
	tfr.txbuf = txBuf;
	tfr.size = 1024;
	
	txBuf[0] = 0x00;
	txBuf[1] = 0x00;
	
	spi_m_sync_enable(&SPI_0);
	spi_m_sync_transfer(&SPI_0, &tfr);
	
	gpio_set_pin_level(CS, true);
	//asm("BKPT #1");
}
*/

static void button_on_PB0_pressed1(void)
{
	extInts++;
}

void EXTERNAL_IRQ_0_example1(void)
{
	ext_irq_register(PIO_PB0_IDX, button_on_PB0_pressed1);
}