#include <atmel_start.h>
#include "Glue.h"
#include "AT86_Impl.h"

uint8_t started = 0;

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
	
	/* Replace with your application code */
	while (1)
	{
		AT86_Tick(AT86_INSTANCE0);
		AT86_Tick(AT86_INSTANCE1);

		//gpio_set_pin_pull_mode(PB0, GPIO_PULL_UP);
		delay_ms(10);
	}
}
