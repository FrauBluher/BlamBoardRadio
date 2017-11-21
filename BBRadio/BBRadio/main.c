#include <atmel_start.h>
#include "Glue.h"
#include "AT86_Impl.h"

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	glue_set_peripherals_inited();
	
	glue_enforce_driver_init();
	
	glue_init();	

	EXTERNAL_IRQ_0_example1();
	
	gpio_set_pin_level(PB1, true);
	delay_us(100000);

	/* Replace with your application code */
	while (1)
	{
		asm("");
		AT86_Test_Comms(AT86_INSTANCE0);

		
		//gpio_set_pin_pull_mode(PB0, GPIO_PULL_UP);
		//delay_us(100000);
		//gpio_set_pin_level(PB1, false);
		delay_us(100000);
		
		
		//SPI_0_example1();
	}
}
