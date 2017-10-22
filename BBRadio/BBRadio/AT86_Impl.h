/**
 * @file AT86_Impl.h
 * @author Pavlo Manovi
 * @brief Contains the implementation of methods used to interact with the AT86.
 * 
 * This implementation takes the hardware abstractions defined for the target MCU/Board
 * and uses them to work with the AT86.
 * 
 * The intended design is that an SPI library with the normal IO operations will be exposed
 * as a generic SPI device and that this library will hook into that and define callback
 * functions for the SPI methods.
 * 
 * TODO: Figure out how to also support the 433 MHz band that the AT86 supports.  Requires
 * a hardware change on the ISM Blasta board.  (V2 change)
 */


#ifndef AT86_IMPL_H_
#define AT86_IMPL_H_

// Glue is defined on all blamboard implementations and is modified for each board.
#include "Glue.h"

// Commands for the RFn_CMD register.
#define RF_NOP 0x0
#define RF_SLEEP 0x1
#define RF_TRXOFF 0x2 //TRXOFF (Transceiver off, SPI active)
#define RF_TXPREP 0x3 //TXPREP (Transmit preparation)
#define RF_TX 0x4 //TX (Transmit)
#define RF_RX 0x5 //RX (Receive)
#define RF_RESET 0x7 //RESET (transceiver reset, the transceiver state will automatically end up in state TRXOFF)

// Bit masks for interrupt.
// TODO: Update with real values.
#define WAKEUP 0x00
#define TXFE 0x00
#define EDC 0x00
#define RXFS 0x00
#define RXAM 0x00
#define AGCH 0x00
#define RXFE 0x00
#define TRXRDY 0x00
#define TRXERR 0x00

//We will only allow up to three instances of this driver on the target (designed for ATSAMS70).
#define MAX_AT86_INSTANCES 3

#define AT86_INSTANCE0 0

/**
 * @brief This enum defines the state machines for each radio front-end.
 * 
 * This mirrors the statemachine in the basebands on the AT86.
 * See pg.33 of the AT86 datasheet for the statemachine diagram.
 */
typedef enum radio_state
{
	AFE_STATE_POWER_OFF = 0,
	AFE_STATE_TRXOFF,
	AFE_STATE_TRANSITION,
	AFE_STATE_TXPREP,
	AFE_STATE_TX,
	AFE_STATE_RX,
	AFE_STATE_RX_CCATX,
	AFE_STATE_SLEEP,
	AFE_STATE_DEEP_SLEEP
} radio_state_t;

/**
 * @brief Defines overall management states for at86.
 */
typedef enum at86_driver_state
{
	AT86_STATE_INIT = 0,
	AT86_STATE_IDLE,
	AT86_STATE_AFE1_UPDATE,
	AT86_STATE_AFE2_UPDATE
} at86_driver_state_t;

/**
 * @brief What calls to the FSM handler will return.
 */
enum at86_return_codes
{
	AT86_OK = 0,
	AT86_IRQ_LAG,
	AT86_ERROR
};

// Gotta do this or else we get incompatible pointer errors
typedef struct _AT86_Instance AT86_Instance;

/**
 * @brief Defines the AFE info struct. HF/LF agnostic.
 */
typedef struct
{
	radio_state_t baseband_state;
	uint8_t	gotIRQ; //Set by the IRQ handler.
	uint8_t gotState;
	uint8_t lastIRQ;
	uint8_t CSMA_EN;
	uint8_t initialized;
	AT86_Instance *parent;
} baseband_info_t;

/**
 * @brief The struct containing the actual AT86 instance.
 * 
 * Not packed.
 */
struct _AT86_Instance
{
	baseband_info_t baseband_900;
	baseband_info_t baseband_2400;
	at86_driver_state_t at86_state;
	SpiDevice *spiDev;
	IRQDevice *irqDev;
	uint8_t initialized;
};

/**
 * We statically allocate our AT86 instances because we're not monsters.
 *
 * When initializing the driver, we use these AT86 instances, they can't
 * exist anywhere else.
 */
AT86_Instance Instance[MAX_AT86_INSTANCES] = {};

uint8_t AT86_Init(SpiDevice *spi_dev, IRQDevice *irq_dev, uint8_t atDev);

uint8_t AT86_FSM(AT86_Instance *atDev);

// TODO: Maybe make these Private Functions
void AT86_IRQ_Handler(uint8_t atDev);
uint8_t AT86_BB_FSM(baseband_info_t *bb);


#endif /* AT86_IMPL_H_ */