/*
 * Hides private methods and variables from global scope.
 */
#include "Glue.h"
#include <stdbool.h>

static bool peripherals_inited = false;

void glue_init(void)
{
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