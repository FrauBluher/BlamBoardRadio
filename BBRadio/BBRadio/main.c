#include <atmel_start.h>
#include "Glue.h"
#include "AT86_Impl.h"

uint8_t started = 0;

void fg_poll(void)
{
	//glue_i2c0_read();
}

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	/*
	if (!started)
	{
		SCB_EnableICache();
		SCB_EnableDCache();
	}
	*/
	
	glue_set_peripherals_inited();
	
	glue_enforce_driver_init();	
	
	glue_init();
	
	delay_ms(100);
	
/*
	usb_d_init();

	//Control endpoint.
	usb_d_ep_init(0, USB_EP_XTYPE_CTRL, 256);
	usb_d_ep_init(1, USB_EP_XTYPE_ISOCH, 2047); //TX - Baseband frame buffer is 2047 octets.
	usb_d_ep_init(2, USB_EP_XTYPE_ISOCH, 2047); //RX - Baseband frame buffer is 2047 octets.
	usb_d_ep_init(3, USB_EP_XTYPE_ISOCH, 32); //Int
	
	usb_d_enable();

	usb_d_attach();
	
	usb_d_ep_enable(0);
	usb_d_ep_enable(1);
	usb_d_ep_enable(2);
	usb_d_ep_enable(3);
*/

	/* Replace with your application code */
	while (1)
	{
		//AT86_Tick(AT86_INSTANCE0);
		//AT86_Tick(AT86_INSTANCE1);
		cdcd_acm_example();

		gpio_toggle_pin_level(LED0);
		
		delay_ms(10);
	}
}
