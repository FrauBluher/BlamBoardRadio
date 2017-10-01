/**
 * \file
 *
 * \brief Power Management Controller register related functionality.
 *
 * Copyright (C) 2017 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

#include <compiler.h>
#include <hpl_init.h>
#include <hpl_pmc.h>
#include <hpl_pmc_config.h>

/**
 * \brief Initializes clock generators
 *
 * All clock sources are running when this function returns.
 */
static void _pmc_init_sources(void)
{
	uint32_t data = 0;

#if CONF_CLK_SLCK_ENABLE == 1
#if (CONF_XOSC32K_ENABLE && (CONF_CLK_GEN_SLCK_SRC == CLK_SRC_OPTION_XOSC32K))
#if (CONF_XOSC32K == CONF_XOSC32K_BYPASS)
	hri_supc_set_MR_reg(SUPC, (SUPC_MR_KEY_PASSWD | SUPC_MR_OSCBYPASS));
#endif
	hri_supc_write_CR_reg(SUPC, (SUPC_CR_KEY_PASSWD | SUPC_CR_XTALSEL));
	while (!(hri_supc_get_SR_OSCSEL_bit(SUPC) && hri_pmc_get_SR_OSCSELS_bit(PMC))) {
		/* Wait until the oscillator is ready */
	}
#endif
#endif

#if (CONF_CLK_MAINCK_ENABLE == 1)
#if (CONF_OSC12M_ENABLE && (CONF_CLK_GEN_MAINCK_SRC == CLK_SRC_OPTION_OSC12M))
	/* Enable Fast RC oscillator but DO NOT switch to RC now */
	hri_pmc_set_CKGR_MOR_reg(PMC, (CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCRCEN));
	while (!hri_pmc_get_SR_MOSCRCS_bit(PMC)) {
		/* Wait until the Fast RC to stabilize */
	}
	/* Change Fast RC oscillator frequency */
	data = hri_pmc_read_CKGR_MOR_reg(PMC) & ~CKGR_MOR_MOSCRCF_Msk;
	data |= CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCRCF(CONF_OSC12M_SELECTOR);
	hri_pmc_write_CKGR_MOR_reg(PMC, data);
	while (!hri_pmc_get_SR_MOSCRCS_bit(PMC)) {
		/* Wait until the Fast RC to stabilize */
	}
	/* Switch to Fast RC */
	data = hri_pmc_read_CKGR_MOR_reg(PMC) & ~CKGR_MOR_MOSCSEL;
	data |= CKGR_MOR_KEY_PASSWD;
	hri_pmc_write_CKGR_MOR_reg(PMC, data);
#endif

#if (CONF_XOSC20M_ENABLE && (CONF_CLK_GEN_MAINCK_SRC == CLK_SRC_OPTION_XOSC20M))
#if (CONF_XOSC20M == CONF_XOSC20M_BYPASS)
	/* Enable Main XTAL oscillator */
	data = hri_pmc_read_CKGR_MOR_reg(PMC) & ~CKGR_MOR_MOSCXTEN;
	data |= CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCXTBY | CKGR_MOR_MOSCSEL;
	hri_pmc_write_CKGR_MOR_reg(PMC, data);
#else
	data = hri_pmc_read_CKGR_MOR_reg(PMC) & ~CKGR_MOR_MOSCXTBY;
	data |= CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCXTEN | CKGR_MOR_MOSCXTST(CONF_XOSC20M_STARTUP_TIME);
	hri_pmc_write_CKGR_MOR_reg(PMC, data);
	while (!hri_pmc_get_SR_MOSCXTS_bit(PMC)) {
		/* Wait until the XTAL to stabilize */
	}
	hri_pmc_set_CKGR_MOR_reg(PMC, CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCSEL);
#endif
#endif
#endif

#if (CONF_PLLACK_ENABLE == 1)
	data = CKGR_PLLAR_MULA(CONF_PLLACK_MUL - 1) | CKGR_PLLAR_DIVA(CONF_PLLACK_DIV) | CKGR_PLLAR_PLLACOUNT(PLL_COUNT);
	/* Stop PLL first */
	hri_pmc_write_CKGR_PLLAR_MULA_bf(PMC, 0);
	hri_pmc_write_CKGR_PLLAR_reg(PMC, (CKGR_PLLAR_ONE | data));
	while (!hri_pmc_get_SR_LOCKA_bit(PMC)) {
		/* Wait until PLLACK stabilize */
	}
#endif

#if (CONF_UPLLCK_ENABLE == 1)
	data = CKGR_UCKR_UPLLCOUNT(PLL_COUNT);
	hri_pmc_write_CKGR_UCKR_reg(PMC, (CKGR_UCKR_UPLLEN | data));
	while (!hri_pmc_get_SR_LOCKU_bit(PMC)) {
		/* Wait until USB UTMI stabilize */
	}
#endif

#if ((CONF_CLK_GEN_MCKR_SRC == CLK_SRC_OPTION_MAINCK) && (CONF_CLK_GEN_MAINCK_SRC == CLK_SRC_OPTION_OSC12M))
#if (CONF_CLK_CFDEN_ENABLE == 1)
	/* Enable main clock failure detection */
	hri_pmc_set_CKGR_MOR_CFDEN_bit(PMC);
#endif
#endif
}

/**
 * \brief Initializes master clock generators
 *
 * Master clock are running when this function returns.
 */
static void _pmc_init_master_clock(void)
{
#if (CONF_CLK_MCKR_ENABLE == 1)
#if (CONF_UPLLCK_ENABLE == 1)
	hri_pmc_write_MCKR_UPLLDIV2_bit(PMC, CONF_UPLLCKDIV_DIV);
	while (!hri_pmc_get_SR_MCKRDY_bit(PMC)) {
		/* Wait until master clock is ready */
	}
#endif

#if ((CONF_CLK_GEN_MCKR_SRC == CLK_SRC_OPTION_SLCK) || (CONF_CLK_GEN_MCKR_SRC == CLK_SRC_OPTION_MAINCK))
	hri_pmc_write_MCKR_CSS_bf(PMC, CONF_CLK_GEN_MCKR_SRC);
	while (!hri_pmc_get_SR_MCKRDY_bit(PMC)) {
		/* Wait until master clock is ready */
	}
	hri_pmc_write_MCKR_PRES_bf(PMC, CONF_MCKR_PRESC);
	while (!hri_pmc_get_SR_MCKRDY_bit(PMC)) {
		/* Wait until master clock is ready */
	}
	hri_pmc_write_MCKR_MDIV_bf(PMC, CONF_MCK_DIV);
	while (!hri_pmc_get_SR_MCKRDY_bit(PMC)) {
		/* Wait until master clock is ready */
	}
#elif ((CONF_CLK_GEN_MCKR_SRC == CLK_SRC_OPTION_PLLACK) || (CONF_CLK_GEN_MCKR_SRC == CLK_SRC_OPTION_UPLLCKDIV))
	hri_pmc_write_MCKR_PRES_bf(PMC, CONF_MCKR_PRESC);
	while (!hri_pmc_get_SR_MCKRDY_bit(PMC)) {
		/* Wait until master clock is ready */
	}
	hri_pmc_write_MCKR_MDIV_bf(PMC, CONF_MCK_DIV);
	while (!hri_pmc_get_SR_MCKRDY_bit(PMC)) {
		/* Wait until master clock is ready */
	}
	hri_pmc_write_MCKR_CSS_bf(PMC, CONF_CLK_GEN_MCKR_SRC);
	while (!hri_pmc_get_SR_MCKRDY_bit(PMC)) {
		/* Wait until master clock is ready */
	}
#endif
#endif
}

/**
 * \brief Initializes programmable clock generators
 *
 * Programmable clock are running when this function returns.
 */
static void _pmc_init_program_clock(void)
{
#if (CONF_CLK_PCK0_ENABLE == 1)
	hri_pmc_write_PCK_reg(PMC, 0, PMC_PCK_CSS(CONF_CLK_GEN_PCK0_SRC) | PMC_PCK_PRES(CONF_PCK0_PRESC - 1));
	while (!hri_pmc_get_SR_PCKRDY0_bit(PMC)) {
		/* Wait until PCK0 clock is ready */
	}
	hri_pmc_write_SCER_reg(PMC, PMC_SCER_PCK0);
#endif

#if (CONF_CLK_PCK1_ENABLE == 1)
	hri_pmc_write_PCK_reg(PMC, 1, PMC_PCK_CSS(CONF_CLK_GEN_PCK1_SRC) | PMC_PCK_PRES(CONF_PCK1_PRESC - 1));
	while (!hri_pmc_get_SR_PCKRDY0_bit(PMC)) {
		/* Wait until PCK1 clock is ready */
	}
	hri_pmc_write_SCER_reg(PMC, PMC_SCER_PCK1);
#endif

#if (CONF_CLK_PCK2_ENABLE == 1)
	hri_pmc_write_PCK_reg(PMC, 2, PMC_PCK_CSS(CONF_CLK_GEN_PCK2_SRC) | PMC_PCK_PRES(CONF_PCK2_PRESC - 1));
	while (!hri_pmc_get_SR_PCKRDY0_bit(PMC)) {
		/* Wait until PCK2 clock is ready */
	}
	hri_pmc_write_SCER_reg(PMC, PMC_SCER_PCK2);
#endif

#if (CONF_CLK_PCK3_ENABLE == 1)
	hri_pmc_write_PCK_reg(PMC, 3, PMC_PCK_CSS(CONF_CLK_GEN_PCK3_SRC) | PMC_PCK_PRES(CONF_PCK3_PRESC - 1));
	while (!hri_pmc_get_SR_PCKRDY0_bit(PMC)) {
		/* Wait until PCK3 clock is ready */
	}
	hri_pmc_write_SCER_reg(PMC, PMC_SCER_PCK3);
#endif

#if (CONF_CLK_PCK4_ENABLE == 1)
	hri_pmc_write_PCK_reg(PMC, 4, PMC_PCK_CSS(CONF_CLK_GEN_PCK4_SRC) | PMC_PCK_PRES(CONF_PCK4_PRESC - 1));
	while (!hri_pmc_get_SR_PCKRDY0_bit(PMC)) {
		/* Wait until PCK4 clock is ready */
	}
	hri_pmc_write_SCER_reg(PMC, PMC_SCER_PCK4);
#endif

#if (CONF_CLK_PCK5_ENABLE == 1)
	hri_pmc_write_PCK_reg(PMC, 5, PMC_PCK_CSS(CONF_CLK_GEN_PCK5_SRC) | PMC_PCK_PRES(CONF_PCK5_PRESC - 1));
	while (!hri_pmc_get_SR_PCKRDY0_bit(PMC)) {
		/* Wait until PCK5 clock is ready */
	}
	hri_pmc_write_SCER_reg(PMC, PMC_SCER_PCK5);
#endif

#if (CONF_CLK_PCK6_ENABLE == 1)
	hri_pmc_write_PCK_reg(PMC, 6, PMC_PCK_CSS(CONF_CLK_GEN_PCK6_SRC) | PMC_PCK_PRES(CONF_PCK6_PRESC - 1));
	while (!hri_pmc_get_SR_PCKRDY0_bit(PMC)) {
		/* Wait until PCK6 clock is ready */
	}
	hri_pmc_write_SCER_reg(PMC, PMC_SCER_PCK6);
#endif
}

/**
 * \brief Initializes USB FS clock generators
 *
 * USB FS clock are running when this function returns.
 */
static void _pmc_init_fs_clock(void)
{
#if (CONF_CLK_USB_48M_ENABLE == 1)
	uint32_t data = 0;

	if (CONF_CLK_GEN_USB_48M_SRC == CLK_SRC_OPTION_UPLLCKDIV) {
		data = PMC_USB_USBS;
	}
	data |= PMC_USB_USBDIV(CONF_USB_48M_DIV - 1);
	hri_pmc_write_USB_reg(PMC, data);
	hri_pmc_write_SCER_reg(PMC, PMC_SCER_USBCLK);
#endif
}

/**
 * \brief Initializes cortex M7 core clock
 *
 */
void _pmc_init(void)
{
	_pmc_init_sources();
	_pmc_init_master_clock();
	_pmc_init_program_clock();
	_pmc_init_fs_clock();
}
