/**
 * \file
 *
 * \brief Power Management Controller register related functionality.
 *
 * Copyright (C) 2016 Atmel Corporation. All rights reserved.
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
#include <hpl_sleep.h>

/* Expected sleep mode for \ref _go_to_sleep() to enter */
static uint8_t _sleep_mode = 0;

/* Wait mode backup for MOR register */
static uint32_t _mor;
/* Wait mode backup for MCKR register */
static uint32_t _mckr;
/* Wait mode backup for FMR register */
static uint32_t _fmr;
/* Wait mode backup for PLLAR register */
static uint32_t _pllar;
/* Wait mode backup for UCKR register */
static uint32_t _uckr;

/**
 * \brief Set the sleep mode for the device
 */
int32_t _set_sleep_mode(const uint8_t mode)
{
	switch (mode) {
	case 0: /* Sleep Mode */
		break;
	case 1: /* Wait Mode - USB suspend */
	case 2: /* Wait Mode */
		SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
		break;
	case 3: /* Backup Mode */
		SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
		hri_supc_write_CR_reg(SUPC, SUPC_CR_KEY_PASSWD | SUPC_CR_VROFF_STOP_VREG);
		break;
	default:
		return ERR_INVALID_ARG;
	}
	_sleep_mode = mode;
	return ERR_NONE;
}

/**
 * \brief Save clock settings and shutdown PLLs/OSCs
 */
static inline void _save_clocks(void)
{
	uint32_t mor = _mor = hri_pmc_read_CKGR_MOR_reg(PMC);
	uint32_t mckr = _mckr = hri_pmc_read_MCKR_reg(PMC);
	_fmr                  = hri_efc_read_EEFC_FMR_reg(EFC);
	_pllar                = hri_pmc_read_CKGR_PLLAR_reg(PMC);
	_uckr                 = hri_pmc_read_CKGR_UCKR_reg(PMC);

	/* Enable FAST RC */
	mor |= CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCRCEN;
	hri_pmc_write_CKGR_MOR_reg(PMC, mor);

	/* If MCK source is PLL, switch to MAINCK */
	if ((mckr & PMC_MCKR_CSS_Msk) > PMC_MCKR_CSS_MAIN_CLK) {
		/* MCK -> MAINCK */
		mckr = (mckr & (~PMC_MCKR_CSS_Msk)) | PMC_MCKR_CSS_MAIN_CLK;
		hri_pmc_write_MCKR_reg(PMC, mckr);
		while (!hri_pmc_get_SR_reg(PMC, PMC_SR_MCKRDY)) {
			/* Wait MCK ready */
		}
	}

	/* MCK PRES -> 1 */
	if (mckr & PMC_MCKR_PRES_Msk) {
		mckr = (mckr & (~PMC_MCKR_PRES_Msk));
		hri_pmc_write_MCKR_reg(PMC, mckr);
		while (!hri_pmc_get_SR_reg(PMC, PMC_SR_MCKRDY)) {
			/* Wait MCK ready */
		}
	}

	/* Disable PLL(s) */
	hri_pmc_write_CKGR_PLLAR_reg(PMC, CKGR_PLLAR_ONE | CKGR_PLLAR_MULA(0));
	hri_pmc_write_CKGR_UCKR_reg(PMC, 0);

	/* Prepare for entering WAIT mode */
	while (!hri_pmc_get_SR_reg(PMC, PMC_SR_MOSCRCS)) {
		/* Wait fast RC ready */
	}

	/* Switch MAINCK to FAST RC */
	mor &= ~CKGR_MOR_MOSCSEL;
	hri_pmc_write_CKGR_MOR_reg(PMC, mor);
	while (!hri_pmc_get_SR_reg(PMC, PMC_SR_MOSCSELS)) {
		/* Wait switch to FAST RC */
	}

	/* Update FWS */
	hri_efc_write_EEFC_FMR_reg(EFC, _fmr & (~EEFC_FMR_FWS_Msk));

	/* Disable XTALs */
	if (_sleep_mode == 2) {
		mor &= ~CKGR_MOR_MOSCXTEN;
		hri_pmc_write_CKGR_MOR_reg(PMC, mor);
	}
}

static inline void _restore_clocks(void)
{
	uint32_t mor;
	uint32_t mckr;
	uint32_t pll_sr = 0;

	/* Switch MAINCK to external XTAL */
	if (CKGR_MOR_MOSCXTBY == (_mor & CKGR_MOR_MOSCXTBY)) {
		/* Bypass mode */
		/* Select bypass mode */
		mor = hri_pmc_read_CKGR_MOR_reg(PMC);
		mor = (mor & (~CKGR_MOR_MOSCXTEN)) | CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCXTBY | CKGR_MOR_MOSCSEL;
		hri_pmc_write_CKGR_MOR_reg(PMC, mor);
		/* Fully restore (Disable XTALs) */
		hri_pmc_write_CKGR_MOR_reg(PMC, _mor | CKGR_MOR_KEY_PASSWD);
	} else if (CKGR_MOR_MOSCXTEN == (_mor & CKGR_MOR_MOSCXTEN)) {
		/* Enable External XTAL */
		if (!hri_pmc_get_CKGR_MOR_reg(PMC, CKGR_MOR_MOSCXTEN)) {
			mor = hri_pmc_read_CKGR_MOR_reg(PMC);
			mor = (mor & (~CKGR_MOR_MOSCXTBY)) | CKGR_MOR_MOSCXTEN;
			hri_pmc_write_CKGR_MOR_reg(PMC, mor);
			while (!hri_pmc_get_SR_reg(PMC, PMC_SR_MOSCXTS)) {
				/* Wait the XTAL to stabilize */
			}
		}
		/* Select External XTAL */
		if (!hri_pmc_get_CKGR_MOR_reg(PMC, CKGR_MOR_MOSCSEL)) {
			mor = hri_pmc_read_CKGR_MOR_reg(PMC);
			mor |= CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCSEL;
			hri_pmc_write_CKGR_MOR_reg(PMC, mor);
			while (!hri_pmc_get_SR_reg(PMC, PMC_SR_MOSCSELS)) {
				/* Wait the XTAL switch */
			}
		}
		/* Fully restore (Disable Fast RC) */
		hri_pmc_write_CKGR_MOR_reg(PMC, _mor | CKGR_MOR_KEY_PASSWD);
	}

	if (_pllar & CKGR_PLLAR_MULA_Msk) {
		hri_pmc_write_CKGR_PLLAR_reg(PMC, _pllar | CKGR_PLLAR_ONE);
		pll_sr |= PMC_SR_LOCKA;
	}
	if (_uckr & CKGR_UCKR_UPLLEN) {
		hri_pmc_write_CKGR_UCKR_reg(PMC, _uckr);
		pll_sr |= PMC_SR_LOCKU;
	}

	/* Wait MCK source ready */
	switch (_mckr & PMC_MCKR_CSS_Msk) {
	case PMC_MCKR_CSS_PLLA_CLK:
		while (!hri_pmc_get_SR_reg(PMC, PMC_SR_LOCKA)) {
			/* Wait PLLA lock */
		}
		break;
	case PMC_MCKR_CSS_UPLL_CLK:
		while (!hri_pmc_get_SR_reg(PMC, PMC_SR_LOCKU)) {
			/* Wait UPLL lock */
		}
	}

	/* Switch to faster clock */
	mckr = hri_pmc_read_MCKR_reg(PMC);
	mckr = (mckr & (~PMC_MCKR_PRES_Msk)) | (_mckr & PMC_MCKR_PRES_Msk);
	hri_pmc_write_MCKR_reg(PMC, mckr);
	while (!hri_pmc_get_SR_reg(PMC, PMC_SR_MCKRDY)) {
		/* Wait MCK ready */
	}

	/* Restore FWS */
	hri_efc_write_EEFC_FMR_reg(EFC, _fmr);

	/* Fully restore MCKR (CSS and others) */
	hri_pmc_write_MCKR_reg(PMC, _mckr);
	while (!hri_pmc_get_SR_reg(PMC, PMC_SR_MCKRDY)) {
		/* Wait MCK ready */
	}

	while (!hri_pmc_get_SR_reg(PMC, pll_sr)) {
		/* Waiting all restored PLLs ready */
	}
}

/**
 * \brief Put MCU to sleep
 */
void _go_to_sleep(void)
{
	bool irq_enabled = (__get_PRIMASK() == 0);
	if (_sleep_mode == 1 || _sleep_mode == 2) {
		__disable_irq();
		_save_clocks();
		__enable_irq();

		/* Flash in wait mode: PMC_FSMR_FLPM_FLASH_STANDBY/_DEEP_POWERDOWN */
		hri_pmc_write_FSMR_FLPM_bf(PMC, _sleep_mode - 1);
		/* Set the WAITMODE bit = 1 */
		__DSB();
		hri_pmc_set_CKGR_MOR_reg(PMC, CKGR_MOR_KEY_PASSWD | CKGR_MOR_WAITMODE);
		while (!hri_pmc_get_SR_reg(PMC, PMC_SR_MCKRDY)) {
			/* Waiting for Master Clock Ready MCKRDY = 1 */
		}
		/* Waiting for MOSCRCEN bit cleared is strongly recommended
		 * to ensure that the core will not execute undesired instructions
		 */
		while (!hri_pmc_get_CKGR_MOR_reg(PMC, CKGR_MOR_MOSCRCEN)) {
			/* Waiting for MOSCRCEN */
		}
		/* Flash in idle mode: PMC_FSMR_FLPM_FLASH_IDLE */
		hri_pmc_write_FSMR_FLPM_bf(PMC, 2);

		__disable_irq();
		_restore_clocks();
		if (irq_enabled) {
			__enable_irq();
		}
	} else {
		__DSB();
		__WFI();
	}
}
