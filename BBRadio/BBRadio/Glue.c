/*
 * Hides private methods and variables from global scope.
 */
#include "Glue.h"
#include "AT86_Impl.h"
#include <stdbool.h>
#include <stdint.h>
#include <driver_init.h>

/** Ctrl endpoint buffer */
static uint8_t ctrl_buffer[64];

/** Loop back buffer for data validation */
COMPILER_ALIGNED(4)
static uint8_t main_buf_loopback[1024];

static volatile bool peripherals_inited = false;
static volatile bool spi0_dma_tx_in_process = false;
static volatile bool spi0_dma_rx_in_process = false;
static volatile bool spi1_dma_tx_in_process = false;
static volatile bool spi1_dma_rx_in_process = false;
static volatile uint32_t * spi0_tx_buf_ptr = NULL;
static volatile uint32_t * spi0_rx_buf_ptr = NULL;
static volatile uint32_t * spi1_tx_buf_ptr = NULL;
static volatile uint32_t * spi1_rx_buf_ptr = NULL;
static volatile uint16_t current_spi0_transfer_size = 0;
static volatile uint16_t current_spi1_transfer_size = 0;

//for debug
uint16_t txInts = 0;
uint16_t rxInts = 0;

static SpiDevice SPI_ZERO;
static IRQDevice IRQ_ZERO;
static SpiDevice SPI_ONE;
static IRQDevice IRQ_ONE;
static 

//SPI0
//uint16_t spiTxBuf[] Lives in AT86_Impl.  We don't double buffer it in here.
uint16_t spi0RxBufBytesAvail = 0;
uint16_t spi1RxBufBytesAvail = 0;
static void glue_spi0_cb_tx_done(struct _dma_resource *resource);
static void glue_spi0_cb_rx_done(struct _dma_resource *resource);
static void glue_spi0_cb_error(struct _dma_resource *resource);
static void glue_spi1_cb_tx_done(struct _dma_resource *resource);
static void glue_spi1_cb_rx_done(struct _dma_resource *resource);
static void glue_spi1_cb_error(struct _dma_resource *resource);

//USB0 local static functions
void init_usb_stack(void);
static bool glue_usb_device_cb_iso_in(const uint8_t ep, const enum usb_xfer_code rc, const uint32_t count);
static bool glue_usb_device_cb_iso_out(const uint8_t ep, const enum usb_xfer_code rc, const uint32_t count);
static glue_usb_device_cb_bulk_in(const uint8_t ep, const enum usb_xfer_code rc, const uint32_t count);
static bool glue_usb_device_cb_bulk_out(const uint8_t ep, const enum usb_xfer_code rc, const uint32_t count);
static bool glue_usb_device_cb_int_in(const uint8_t ep, const enum usb_xfer_code rc, const uint32_t count);
static bool glue_usb_device_cb_int_out(const uint8_t ep, const enum usb_xfer_code rc, const uint32_t count);
static void glue_usb_device_cb_ctrl_in(uint16_t count);
static void glue_usb_device_cb_ctrl_out(uint16_t count);

/*
void init_usb_stack(void)
{
		usbdc_init(ctrl_buffer);

		vendordf_init();
		vendordf_register_callback(VENDORDF_CB_CTRL_READ_REQ, (FUNC_PTR)glue_usb_device_cb_ctrl_out);
		vendordf_register_callback(VENDORDF_CB_CTRL_WRITE_REQ, (FUNC_PTR)glue_usb_device_cb_ctrl_in);
		vendordf_register_callback(VENDORDF_CB_INT_READ, (FUNC_PTR)glue_usb_device_cb_int_out);
		vendordf_register_callback(VENDORDF_CB_INT_WRITE, (FUNC_PTR)glue_usb_device_cb_int_in);
		vendordf_register_callback(VENDORDF_CB_BULK_READ, (FUNC_PTR)glue_usb_device_cb_bulk_out);
		vendordf_register_callback(VENDORDF_CB_BULK_WRITE, (FUNC_PTR)glue_usb_device_cb_bulk_in);
		vendordf_register_callback(VENDORDF_CB_ISO_READ, (FUNC_PTR)glue_usb_device_cb_iso_out);
		vendordf_register_callback(VENDORDF_CB_ISO_WRITE, (FUNC_PTR)glue_usb_device_cb_iso_in);

		//usbdc_check_desces(single_desc);
		//usbdc_start(single_desc);
		usbdc_attach();

		//while (!vendordf_is_enabled()) {
		//	// wait vendor application to be installed
		//};
}
*/

void glue_init(void)
{
	//Set up USB communications
	//init_usb_stack();
	
	//Set up SPI0
	//Set up IRQ0
	SPI_ZERO.halSpiDriver = &SPI_0;
	SPI_ONE.halSpiDriver = &SPI_1;
	//IRQ_ZERO.halIRQDriver = IRQ0;
	
	AT86_Init(&SPI_ZERO, &IRQ_ZERO, AT86_INSTANCE0);
	AT86_Init(&SPI_ONE, &IRQ_ONE, AT86_INSTANCE1);
	
	//Set call-backs for spi here.
	spi_m_dma_register_callback(SPI_ZERO.halSpiDriver, SPI_M_DMA_CB_TX_DONE, glue_spi0_cb_tx_done);
	spi_m_dma_register_callback(SPI_ZERO.halSpiDriver, SPI_M_DMA_CB_RX_DONE, glue_spi0_cb_rx_done);
	spi_m_dma_register_callback(SPI_ZERO.halSpiDriver, SPI_M_DMA_CB_ERROR, glue_spi0_cb_error);
	
	//Set call-backs for spi here.
	spi_m_dma_register_callback(SPI_ONE.halSpiDriver, SPI_M_DMA_CB_TX_DONE, glue_spi1_cb_tx_done);
	spi_m_dma_register_callback(SPI_ONE.halSpiDriver, SPI_M_DMA_CB_RX_DONE, glue_spi1_cb_rx_done);
	spi_m_dma_register_callback(SPI_ONE.halSpiDriver, SPI_M_DMA_CB_ERROR, glue_spi1_cb_error);
	
	ext_irq_register(PIO_PB0_IDX, IRQ_ZERO.callback);
	ext_irq_register(PIO_PD23_IDX, IRQ_ONE.callback);
	
	spi_m_dma_set_mode(&SPI_0, SPI_MODE_0);
	spi_m_dma_set_baudrate(&SPI_0, 1000000);
	spi_m_dma_set_char_size(&SPI_0, SPI_CHAR_SIZE_8);
	
	spi_m_dma_set_mode(&SPI_1, SPI_MODE_0);
	spi_m_dma_set_baudrate(&SPI_1, 1000000);
	spi_m_dma_set_char_size(&SPI_1, SPI_CHAR_SIZE_8);
	
	spi_m_dma_enable(&SPI_0);
	spi_m_dma_enable(&SPI_1);
	
	gpio_set_pin_level(CS, true);
	gpio_set_pin_level(CS_2, true);
	
	gpio_set_pin_level(LED0, false);
	gpio_set_pin_level(AT86_1_RST, false);	
	delay_us(100000);
	gpio_set_pin_level(AT86_1_RST, true);
	
	gpio_set_pin_level(AT86_2_RST, false);
	delay_us(100000);
	gpio_set_pin_level(AT86_2_RST, true);
	
	gpio_set_pin_level(LED0, true);
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

void glue_i2c0_read(uint8_t reg, uint8_t *buffer, uint8_t readNum)
{
	i2c_m_sync_cmd_write(&I2C_0, reg, buffer, readNum);
}

void glue_spi0_dma_transfer(SpiDevice* spi, uint8_t *txBuf, uint8_t *rxBuf, uint16_t numBytes)
{
	if (txBuf != NULL)
	{
		spi0_dma_tx_in_process = true;
		spi0_tx_buf_ptr = (uint32_t *) txBuf;
	}
	
	if (rxBuf != NULL)
	{
		spi0_dma_rx_in_process = true;
		spi0_rx_buf_ptr = (uint32_t *) rxBuf;
	}
	
	current_spi0_transfer_size = numBytes;
	
	/*
	// Enforce L1 D-Cache Coherency
	if (spi0_rx_buf_ptr != NULL)
	{
		// Cache operations are done in 32 bit chunks, always.
		uint16_t temp;
		if ((current_spi0_transfer_size % 4) != 0)
		{
			temp++;
		}
		
		temp += (current_spi0_transfer_size / 4);
		
		SCB_CleanDCache_by_Addr((uint32_t *) txBuf, temp);
	}
	*/	

	spi_m_dma_transfer(spi->halSpiDriver, txBuf, rxBuf, numBytes);
}

void glue_spi1_dma_transfer(SpiDevice* spi, uint8_t *txBuf, uint8_t *rxBuf, uint16_t numBytes)
{
	if (txBuf != NULL)
	{
		spi1_dma_tx_in_process = true;
		spi1_tx_buf_ptr = (uint32_t *) txBuf;
	}
	
	if (rxBuf != NULL)
	{
		spi1_dma_rx_in_process = true;
		spi1_rx_buf_ptr = (uint32_t *) rxBuf;
	}
	
	current_spi1_transfer_size = numBytes;
	
	/*
	// Enforce L1 D-Cache Coherency
	if (spi0_rx_buf_ptr != NULL)
	{
		// Cache operations are done in 32 bit chunks, always.
		uint16_t temp;
		if ((current_spi0_transfer_size % 4) != 0)
		{
			temp++;
		}
		
		temp += (current_spi0_transfer_size / 4);
		
		SCB_CleanDCache_by_Addr((uint32_t *) txBuf, temp);
	}
	*/	

	spi_m_dma_transfer(spi->halSpiDriver, txBuf, rxBuf, numBytes);
}

void glue_spi_dma_transfer(SpiDevice* spi, uint8_t *txBuf, uint8_t *rxBuf, uint16_t numBytes)
{
	//TODO: Go do something else while we wait for the SPI/DMA to finish
	if (spi->halSpiDriver == &SPI_0)
	{
		gpio_set_pin_level(CS, false);
		delay_us(10);
		glue_spi0_dma_transfer(spi, txBuf, rxBuf, numBytes);
		while(glue_spi_in_process(spi));
		//Interrupt fires before all bits shifted in...
		//TODO: Find workaround.
		delay_us(20);
		gpio_set_pin_level(CS, true);
		delay_us(20);
	}
	else if (spi->halSpiDriver == &SPI_1)
	{
		gpio_set_pin_level(CS_2, false);
		delay_us(10);
		glue_spi1_dma_transfer(spi, txBuf, rxBuf, numBytes);
		while(glue_spi_in_process(spi));
				//The interrupt fires before all bits are shifted out.  See if we can fix that later.
		//For now we just waste some cycles waiting for it to figure itself out
		delay_us(20);
		gpio_set_pin_level(CS_2, true);
		delay_us(20);
	}
}

bool glue_spi_in_process(SpiDevice* spi)
{
	if (spi->halSpiDriver == &SPI_0)
	{
		if (spi0_dma_tx_in_process || spi0_dma_rx_in_process)
		{
			return(true);
		}
	}
	else if (spi->halSpiDriver == &SPI_1)
	{
		if (spi1_dma_tx_in_process || spi1_dma_rx_in_process)
		{
			return(true);
		}
	}
	else
	{
		return(false);
	}
}

//TODO: Start using cache clean/invalidations from an address up to the
//      point of cache coherency.
// See: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0646b/BABIGDDC.html
// There are potentially silicon eratta issues with cache coherency on this chip revision.
// See: http://community.atmel.com/forum/samv7-scbdisabledcache-crashes-hardfault

void glue_spi0_cb_tx_done(struct _dma_resource *resource)
{
	spi0_dma_tx_in_process = false;
	txInts++;
}

void glue_spi0_cb_rx_done(struct _dma_resource *resource)
{
	/*
	// Enforce L1 D-Cache Coherency
	if (spi0_rx_buf_ptr != NULL)
	{
		// Cache operations are done in 32 bit chunks, always.
		uint16_t temp;
		if ((current_spi0_transfer_size % 4) != 0)
		{
			temp++;
		}
		
		temp += (current_spi0_transfer_size / 4);
		
		SCB_InvalidateDCache_by_Addr(spi0_rx_buf_ptr, temp);
		
		spi0_rx_buf_ptr = NULL;
		current_spi0_transfer_size = 0;
	}
	*/
	spi0_dma_rx_in_process = false;
	rxInts++;
}

void glue_spi0_cb_error(struct _dma_resource *resource)
{
	spi0_dma_tx_in_process = false;
	spi0_dma_rx_in_process = false;
}

void glue_spi1_cb_tx_done(struct _dma_resource *resource)
{
	spi1_dma_tx_in_process = false;
	txInts++;
}

void glue_spi1_cb_rx_done(struct _dma_resource *resource)
{
	/*
	// Enforce L1 D-Cache Coherency
	if (spi0_rx_buf_ptr != NULL)
	{
		// Cache operations are done in 32 bit chunks, always.
		uint16_t temp;
		if ((current_spi0_transfer_size % 4) != 0)
		{
			temp++;
		}
		
		temp += (current_spi0_transfer_size / 4);
		
		SCB_InvalidateDCache_by_Addr(spi0_rx_buf_ptr, temp);
		
		spi0_rx_buf_ptr = NULL;
		current_spi0_transfer_size = 0;
	}
	*/
	spi1_dma_rx_in_process = false;
	rxInts++;
}

void glue_spi1_cb_error(struct _dma_resource *resource)
{
	spi1_dma_tx_in_process = false;
	spi1_dma_rx_in_process = false;
}

//////////////////////////////////////////////////////////////
//////////////////// USB GLUE BELOW //////////////////////////
//////////////////////////////////////////////////////////////

static void glue_usb_device_cb_ctrl_out(uint16_t count)
{
	uint16_t recv_cnt = 1024;

	if (recv_cnt > count) {
		recv_cnt = count;
	}
	vendordf_read(USB_EP_TYPE_CONTROL, main_buf_loopback, recv_cnt);
	vendordf_read(USB_EP_TYPE_INTERRUPT, main_buf_loopback, 1024);
	vendordf_read(USB_EP_TYPE_BULK, main_buf_loopback, 1024);
	vendordf_read(USB_EP_TYPE_ISOCHRONOUS, main_buf_loopback, 1024);
}

static void glue_usb_device_cb_ctrl_in(uint16_t count)
{
	uint16_t recv_cnt = 1024;

	if (recv_cnt > count) {
		recv_cnt = count;
	}
	vendordf_write(USB_EP_TYPE_CONTROL, main_buf_loopback, recv_cnt);
}

static bool glue_usb_device_cb_int_out(const uint8_t ep, const enum usb_xfer_code rc, const uint32_t count)
{
	vendordf_write(USB_EP_TYPE_INTERRUPT, main_buf_loopback, count);
	return false;
}

static bool glue_usb_device_cb_int_in(const uint8_t ep, const enum usb_xfer_code rc, const uint32_t count)
{
	vendordf_read(USB_EP_TYPE_INTERRUPT, main_buf_loopback, count);
	return false;
}

static bool glue_usb_device_cb_bulk_out(const uint8_t ep, const enum usb_xfer_code rc, const uint32_t count)
{
	vendordf_write(USB_EP_TYPE_BULK, main_buf_loopback, count);

	return false;
}

static glue_usb_device_cb_bulk_in(const uint8_t ep, const enum usb_xfer_code rc, const uint32_t count)
{
	vendordf_read(USB_EP_TYPE_BULK, main_buf_loopback, count);

	return false;
}

static bool glue_usb_device_cb_iso_out(const uint8_t ep, const enum usb_xfer_code rc, const uint32_t count)
{
	vendordf_write(USB_EP_TYPE_ISOCHRONOUS, main_buf_loopback, count);

	return false;
}

static bool glue_usb_device_cb_iso_in(const uint8_t ep, const enum usb_xfer_code rc, const uint32_t count)
{
	vendordf_read(USB_EP_TYPE_ISOCHRONOUS, main_buf_loopback, count);

	return false;
}
