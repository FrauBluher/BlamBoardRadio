/*
 * This header contains all of the other header files necessary to interact with peripherals
 * which have been set up with Atmel Start.
 *
 * Here is where we also glue together a few types to work with my pseudo hardware agnostic
 * peripheral device scheme that I use between projects.  Think 'FooDev'
 *
 * If using atmel start to set up peripherals (you should, it's easy) make sure to initialize
 * the glue library after the Atmel Start init code (usually called from main.c to driver_init.c).
 */ 


#ifndef GLUE_H_
#define GLUE_H_

#include <stdint.h>

/*
 * Define board type either here or somewhere else in the code or during compilation to glue
 * peripheral/board code and generic drivers together.
 */
#define BLAMBOARD_V_1_RADIO
//#define BLAMBOARD_V_2 // Doesn't exist yet.

#ifdef BLAMBOARD_V_1_RADIO

#include "hal_spi_m_dma.h"
#include "hal_ext_irq.h"
#include "hal_gpio.h"
#include "hal_delay.h"
#include "atmel_start_pins.h"
#include "AT86_Impl.h"

//Glue together the generic External Interrupt IRQCallbackFcn.
typedef ext_irq_cb_t IrqCallbackFcn;

//Glue together the generic SpiDevice and the hardware specific descriptor.
//typedef spi_m_dma_descriptor SpiDevice;

//Placeholder.
typedef struct
{
	void *deviceDriver;
	IrqCallbackFcn callback;
} IRQDevice;

//Placeholder.
typedef struct
{
	void *deviceDriver;
} SpiDevice;

void glue_init(void);

void glue_set_peripherals_inited(void);

//Returns if glue_set_peripherals_inited was called before.  Crashes otherwise.
void glue_enforce_driver_init(void);

//For use during debugging.  Mainly used to check that things don't return zero.
static inline void glue_crash_and_burn(void)
{
	while(1)
	{
		gpio_toggle_pin_level(LED0);
		//delay_ms(1);
		uint8_t test;
		for(uint32_t i = 0; i < 150000000; i++)
		{
			test++;
			asm(""); // To stop meddlesome optimization
		}
	}
}

#else
#error "We don't support other blamboard hardware yet."
#endif

#endif /* GLUE_H_ */