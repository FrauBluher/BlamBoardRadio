/* Auto-generated config file peripheral_clk_config.h */
#ifndef PERIPHERAL_CLK_CONFIG_H
#define PERIPHERAL_CLK_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> DAC Clock Settings
// <y> DAC Clock source
// <CONF_SRC_MCK"> Master Clock (MCK)
// <i> This defines the clock source for the DAC
// <id> dac_clock_source
#ifndef CONF_DACC_SRC
#define CONF_DACC_SRC CONF_SRC_MCK
#endif
// </h>

/**
 * \def DAC FREQUENCY
 * \brief DAC's Clock frequency
 */
#ifndef CONF_DACC_FREQUENCY
#define CONF_DACC_FREQUENCY 150000000
#endif

/**
 * \def CONF_HCLK_FREQUENCY
 * \brief HCLK's Clock frequency
 */
#ifndef CONF_HCLK_FREQUENCY
#define CONF_HCLK_FREQUENCY 300000000
#endif

/**
 * \def CONF_FCLK_FREQUENCY
 * \brief FCLK's Clock frequency
 */
#ifndef CONF_FCLK_FREQUENCY
#define CONF_FCLK_FREQUENCY 300000000
#endif

/**
 * \def CONF_CPU_FREQUENCY
 * \brief CPU's Clock frequency
 */
#ifndef CONF_CPU_FREQUENCY
#define CONF_CPU_FREQUENCY 300000000
#endif

/**
 * \def CONF_SLCK_FREQUENCY
 * \brief Slow Clock frequency
 */
#define CONF_SLCK_FREQUENCY 32000

/**
 * \def CONF_MCK_FREQUENCY
 * \brief Master Clock frequency
 */
#define CONF_MCK_FREQUENCY 150000000

/**
 * \def CONF_PCK6_FREQUENCY
 * \brief Programmable Clock Controller 6 frequency
 */
#define CONF_PCK6_FREQUENCY 12000000

// <h> SPI1 Clock Settings
// <y> SPI1 Clock source
// <CONF_SRC_MCK"> Master Clock (MCK)
// <i> This defines the clock source for the SPI1
// <id> spi_clock_source
#ifndef CONF_SPI1_SRC
#define CONF_SPI1_SRC CONF_SRC_MCK
#endif
// </h>

/**
 * \def SPI1 FREQUENCY
 * \brief SPI1's Clock frequency
 */
#ifndef CONF_SPI1_FREQUENCY
#define CONF_SPI1_FREQUENCY 150000000
#endif

// <h> TWIHS Clock Settings
// <y> TWIHS Clock source
// <CONF_SRC_MCK"> Master Clock (MCK)
// <i> This defines the clock source for the TWIHS
// <id> twihs_clock_source
#ifndef CONF_TWIHS0_SRC
#define CONF_TWIHS0_SRC CONF_SRC_MCK
#endif
// </h>

/**
 * \def TWIHS FREQUENCY
 * \brief TWIHS's Clock frequency
 */
#ifndef CONF_TWIHS0_FREQUENCY
#define CONF_TWIHS0_FREQUENCY 150000000
#endif

// <h> TWIHS Clock Settings
// <y> TWIHS Clock source
// <CONF_SRC_MCK"> Master Clock (MCK)
// <i> This defines the clock source for the TWIHS
// <id> twihs_clock_source
#ifndef CONF_TWIHS1_SRC
#define CONF_TWIHS1_SRC CONF_SRC_MCK
#endif
// </h>

/**
 * \def TWIHS FREQUENCY
 * \brief TWIHS's Clock frequency
 */
#ifndef CONF_TWIHS1_FREQUENCY
#define CONF_TWIHS1_FREQUENCY 150000000
#endif

// <h> UART Clock Settings
// <o> UART Clock source
// <0=> Master Clock (MCK)
// <1=> Programmable Clock Controller 4 (PMC_PCK4)
// <i> This defines the clock source for the UART
// <id> uart_clock_source
#ifndef CONF_UART0_CK_SRC
#define CONF_UART0_CK_SRC 0
#endif
// </h>

/**
 * \def UART FREQUENCY
 * \brief UART's Clock frequency
 */
#ifndef CONF_UART0_FREQUENCY
#define CONF_UART0_FREQUENCY 150000000
#endif

// <h> UART Clock Settings
// <o> UART Clock source
// <0=> Master Clock (MCK)
// <1=> Programmable Clock Controller 4 (PMC_PCK4)
// <i> This defines the clock source for the UART
// <id> uart_clock_source
#ifndef CONF_UART4_CK_SRC
#define CONF_UART4_CK_SRC 0
#endif
// </h>

/**
 * \def UART FREQUENCY
 * \brief UART's Clock frequency
 */
#ifndef CONF_UART4_FREQUENCY
#define CONF_UART4_FREQUENCY 150000000
#endif

#ifndef CONF_SRC_USB_480M
#define CONF_SRC_USB_480M 0
#endif

#ifndef CONF_SRC_USB_48M
#define CONF_SRC_USB_48M 1
#endif

// <y> USB Full/Low Speed Clock
// <CONF_SRC_USB_48M"> USB Clock Controller (USB_48M)
// <id> usb_fsls_clock_source
// <i> 48MHz clock source for low speed and full speed.
// <i> It must be available when low speed is supported by host driver.
// <i> It must be available when low power mode is selected.
#ifndef CONF_USBHS_FSLS_SRC
#define CONF_USBHS_FSLS_SRC CONF_SRC_USB_48M
#endif

// <y> USB Clock Source(Normal/Low-power Mode Selection)
// <CONF_SRC_USB_480M"> USB High Speed Clock (USB_480M)
// <CONF_SRC_USB_48M"> USB Clock Controller (USB_48M)
// <id> usb_clock_source
// <i> Select the clock source for USB.
// <i> In normal mode, use "USB High Speed Clock (USB_480M)".
// <i> In low-power mode, use "USB Clock Controller (USB_48M)".
#ifndef CONF_USBHS_SRC
#define CONF_USBHS_SRC CONF_SRC_USB_480M
#endif

/**
 * \def CONF_USBHS_FSLS_FREQUENCY
 * \brief USBHS's Full/Low Speed Clock Source frequency
 */
#ifndef CONF_USBHS_FSLS_FREQUENCY
#define CONF_USBHS_FSLS_FREQUENCY 300000000
#endif

/**
 * \def CONF_USBHS_FREQUENCY
 * \brief USBHS's Selected Clock Source frequency
 */
#ifndef CONF_USBHS_FREQUENCY
#define CONF_USBHS_FREQUENCY 480000000
#endif

// <<< end of configuration section >>>

#endif // PERIPHERAL_CLK_CONFIG_H
