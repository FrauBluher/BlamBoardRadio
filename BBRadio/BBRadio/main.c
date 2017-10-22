#include <atmel_start.h>
#include "Glue.h"

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	glue_set_peripherals_inited();
	
	glue_enforce_driver_init();
	
	glue_init();

	/* Replace with your application code */
	while (1) {
		int a;
		
		a++;
	}
}
