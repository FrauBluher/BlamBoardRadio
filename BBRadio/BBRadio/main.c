#include <atmel_start.h>
#include "Glue.h"
#include "AT86_Impl.h"

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	SCB_EnableICache();
	SCB_EnableDCache();
	
	glue_set_peripherals_inited();
	
	glue_enforce_driver_init();
	
    gpio_set_pin_level(AT86_1_RST, false);	
	delay_us(100000);
	gpio_set_pin_level(AT86_1_RST, true);
	
	gpio_set_pin_level(AT86_2_RST, false);
	delay_us(100000);
	gpio_set_pin_level(AT86_2_RST, true);
	
	delay_us(500000);
	
	glue_init();	
	
	/* Replace with your application code */
	while (1)
	{
		AT86_Tick(AT86_INSTANCE0);
		AT86_Tick(AT86_INSTANCE1);

		//gpio_set_pin_pull_mode(PB0, GPIO_PULL_UP);
		delay_ms(10);
	}
}
