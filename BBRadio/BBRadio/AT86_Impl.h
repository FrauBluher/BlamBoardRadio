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
#define RF_CMD_NOP 0x0
#define RF_CMD_SLEEP 0x1
#define RF_CMD_TRXOFF 0x2 //TRXOFF (Transceiver off, SPI active)
#define RF_CMD_TXPREP 0x3 //TXPREP (Transmit preparation)
#define RF_CMD_TX 0x4 //TX (Transmit)
#define RF_CMD_RX 0x5 //RX (Receive)
#define RF_CMD_RESET 0x7 //RESET (transceiver reset, the transceiver state will automatically end up in state TRXOFF)

// Bit masks for interrupt.
// We take the RF and BB interrupts and combine them
// The RF interrupts take the MSB of lastIRQ
#define WAKEUP 0x01 << 8
#define TRXRDY 0x02 << 8
#define EDC 0x04 << 8
#define BATLOW 0x08 << 8
#define TRXERR 0x10 << 8
#define IQIFSF 0x20 << 8
#define RXFS 0x01
#define RXFE 0x02
#define RXAM 0x04
#define RXEM 0x08
#define TXFE 0x10
#define AGCH 0x20
#define AGCR 0x40
#define FBLI 0x80

#define BBC0_PC 0x0301
#define BBC1_PC 0x0401
#define BBC0_IRQM 0x0300 //BBC0_IRQM - 900
#define BBC1_IRQM 0x0400 //BBC1_IRQM - 2400
#define RF09_IRQM 0x0100 //RF09_IRQM
#define RF24_IRQM 0x0200 //RF24_IRQM
#define RF09_EDC 0x010E
#define RF24_EDC 0x020E
#define RF09_EDD 0x010F
#define RF24_EDD 0x020F
#define RF09_EDV 0x0110
#define RF24_EDV 0x0210
#define RF09_CNM 0x0108
#define RF24_CNM 0x0208
#define RF09_CCF0L 0x0105
#define RF24_CCF0L 0x0205
#define RF09_CCF0H 0x0106
#define RF24_CCF0H 0x0206

#define BBC0_FBRXS 0x2000
#define BBC0_FBRXE 0x27FE
#define BBC0_FBTXS 0x2800
#define BBC0_FBTXE 0x2FFE
#define BBC0_TXFLL 0x0306
#define BBC0_TXFLH 0x0307
#define BBC1_FBRXS 0x3000
#define BBC1_FBRXE 0x37FE
#define BBC1_FBTXS 0x3800
#define BBC1_FBTXE 0x3FFE
#define BBC1_TXFLL 0x0406
#define BBC1_TXFLH 0x0407

#define RF09_CMD 0x0103
#define RF24_CMD 0x0203

//We will only allow up to three instances of this driver on the target (designed for ATSAMS70).
#define MAX_AT86_INSTANCES 3

#define AT86_INSTANCE0 0
#define AT86_INSTANCE1 1

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
	AT86_STATE_0900_UPDATE,
	AT86_STATE_2400_UPDATE,
	AT86_STATE_ALL_UPDATE
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
	uint16_t lastIRQ;
	uint8_t CSMA_EN;
	uint8_t channel_power_assesment;
	uint8_t pendingTransmit;
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
	uint16_t numInterrupts;
	uint8_t initialized;
};

uint8_t AT86_Init(SpiDevice *spi_dev, IRQDevice *irq_dev, uint8_t atDev);

uint8_t AT86_Tick(uint8_t atDev);


#endif /* AT86_IMPL_H_ */