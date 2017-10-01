/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <hal_init.h>
#include <hpl_pmc.h>
#include <peripheral_clk_config.h>
#include <utils.h>

/*! The buffer size for USART */
#define USART_1_BUFFER_SIZE 16

struct spi_m_sync_descriptor  SPI_0;
struct usart_async_descriptor USART_1;

static uint8_t USART_1_buffer[USART_1_BUFFER_SIZE];

struct dac_sync_descriptor DAC_0;

struct i2c_m_sync_desc I2C_0;

struct usart_sync_descriptor USART_0;

void DAC_0_PORT_init(void)
{

	gpio_set_pin_function(PB13, GPIO_PIN_FUNCTION_OFF);

	gpio_set_pin_function(PD0, GPIO_PIN_FUNCTION_OFF);
}

void DAC_0_CLOCK_init(void)
{

	_pmc_enable_periph_clock(ID_DACC);
}

void DAC_0_init(void)
{
	DAC_0_CLOCK_init();
	dac_sync_init(&DAC_0, DACC);
	DAC_0_PORT_init();
}

void EXTERNAL_IRQ_0_init(void)
{

	// Set pin direction to input
	gpio_set_pin_direction(PB0, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(PB0,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PB0, GPIO_PIN_FUNCTION_OFF);
}

void SPI_0_PORT_init(void)
{

	gpio_set_pin_function(MISO, PINMUX_PC26C_SPI1_MISO);

	gpio_set_pin_function(MOSI, PINMUX_PC27C_SPI1_MOSI);

	gpio_set_pin_function(SCLK, PINMUX_PC24C_SPI1_SPCK);
}

void SPI_0_CLOCK_init(void)
{
	_pmc_enable_periph_clock(ID_SPI1);
}

void SPI_0_init(void)
{
	SPI_0_CLOCK_init();

	spi_m_sync_init(&SPI_0, SPI1);

	SPI_0_PORT_init();
}

void I2C_0_PORT_init(void)
{

	gpio_set_pin_function(PA4, PINMUX_PA4A_TWIHS0_TWCK0);

	gpio_set_pin_function(PA3, PINMUX_PA3A_TWIHS0_TWD0);
}

void I2C_0_CLOCK_init(void)
{
	_pmc_enable_periph_clock(ID_TWIHS0);
}

void I2C_0_init(void)
{
	I2C_0_CLOCK_init();

	i2c_m_sync_init(&I2C_0, TWIHS0);

	I2C_0_PORT_init();
}

void USART_0_PORT_init(void)
{

	gpio_set_pin_function(PA9, PINMUX_PA9A_UART0_URXD0);

	gpio_set_pin_function(PA10, PINMUX_PA10A_UART0_UTXD0);
}

void USART_0_CLOCK_init(void)
{
	_pmc_enable_periph_clock(ID_UART0);
}

void USART_0_init(void)
{
	USART_0_CLOCK_init();
	usart_sync_init(&USART_0, UART0, _uart_get_usart_sync());
	USART_0_PORT_init();
}

/**
 * \brief USART Clock initialization function
 *
 * Enables register interface and peripheral clock
 */
void USART_1_CLOCK_init()
{
	_pmc_enable_periph_clock(ID_UART4);
}

/**
 * \brief USART pinmux initialization function
 *
 * Set each required pin to USART functionality
 */
void USART_1_PORT_init()
{

	gpio_set_pin_function(PD18, PINMUX_PD18C_UART4_URXD4);

	gpio_set_pin_function(PD19, PINMUX_PD19C_UART4_UTXD4);
}

/**
 * \brief USART initialization function
 *
 * Enables USART peripheral, clocks and initializes USART driver
 */
void USART_1_init(void)
{
	USART_1_CLOCK_init();
	usart_async_init(&USART_1, UART4, USART_1_buffer, USART_1_BUFFER_SIZE, _uart_get_usart_async());
	USART_1_PORT_init();
}

/* The USB module requires a GCLK_USB of 48 MHz ~ 0.25% clock
 * for low speed and full speed operation. */
#if (CONF_USBHS_SRC == CONF_SRC_USB_48M)
#if (CONF_USBHS_FREQUENCY > (48000000 + 48000000 / 400)) || (CONF_USBHS_FREQUENCY < (48000000 - 48000000 / 400))
#warning USB clock should be 48MHz ~ 0.25% clock, check your configuration!
#endif
#endif

void USB_0_CLOCK_init(void)
{
	_pmc_enable_periph_clock(ID_USBHS);
}

void USB_0_init(void)
{
	USB_0_CLOCK_init();
	usb_d_init();
}

void system_init(void)
{
	init_mcu();

	_pmc_enable_periph_clock(ID_PIOB);

	_pmc_enable_periph_clock(ID_PIOC);

	/* Disable Watchdog */
	hri_wdt_set_MR_WDDIS_bit(WDT);

	/* GPIO on PC20 */

	// Set pin direction to output
	gpio_set_pin_direction(LED0, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(LED0,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	gpio_set_pin_function(LED0, GPIO_PIN_FUNCTION_OFF);

	/* GPIO on PC25 */

	gpio_set_pin_direction(CS,
	                       // <y> Pin direction
	                       // <id> pad_direction
	                       // <GPIO_DIRECTION_OFF"> Off
	                       // <GPIO_DIRECTION_IN"> In
	                       // <GPIO_DIRECTION_OUT"> Out
	                       GPIO_DIRECTION_OUT);

	gpio_set_pin_level(CS,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_pull_mode(CS,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(CS,
	                      // <y> Pin function
	                      // <id> pad_function
	                      // <i> Auto : use driver pinmux if signal is imported by driver, else turn off function
	                      // <GPIO_PIN_FUNCTION_OFF"> Auto
	                      // <GPIO_PIN_FUNCTION_OFF"> Off
	                      // <GPIO_PIN_FUNCTION_A"> A
	                      // <GPIO_PIN_FUNCTION_B"> B
	                      // <GPIO_PIN_FUNCTION_C"> C
	                      // <GPIO_PIN_FUNCTION_D"> D
	                      GPIO_PIN_FUNCTION_C);

	DAC_0_init();
	EXTERNAL_IRQ_0_init();

	SPI_0_init();

	I2C_0_init();

	USART_0_init();
	USART_1_init();

	USB_0_init();

	ext_irq_init();
}
