/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef ATMEL_START_PINS_H_INCLUDED
#define ATMEL_START_PINS_H_INCLUDED

#include <hal_gpio.h>

// SAMS70 has 4 pin functions

#define GPIO_PIN_FUNCTION_A 0
#define GPIO_PIN_FUNCTION_B 1
#define GPIO_PIN_FUNCTION_C 2
#define GPIO_PIN_FUNCTION_D 3

#define PA3 GPIO(GPIO_PORTA, 3)
#define PA4 GPIO(GPIO_PORTA, 4)
#define PA9 GPIO(GPIO_PORTA, 9)
#define PA10 GPIO(GPIO_PORTA, 10)
#define PB0 GPIO(GPIO_PORTB, 0)
#define PB1 GPIO(GPIO_PORTB, 1)
#define PB13 GPIO(GPIO_PORTB, 13)
#define LED0 GPIO(GPIO_PORTC, 20)
#define SCLK GPIO(GPIO_PORTC, 24)
#define CS GPIO(GPIO_PORTC, 25)
#define MISO GPIO(GPIO_PORTC, 26)
#define MOSI GPIO(GPIO_PORTC, 27)
#define PD0 GPIO(GPIO_PORTD, 0)
#define PD18 GPIO(GPIO_PORTD, 18)
#define PD19 GPIO(GPIO_PORTD, 19)

#endif // ATMEL_START_PINS_H_INCLUDED
