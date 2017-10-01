#include <atmel_start.h>

uint32_t testVar1;
uint32_t testVar2;

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	/* Replace with your application code */
	while (1) {
		testVar1++;
		testVar2--;
	}
}
