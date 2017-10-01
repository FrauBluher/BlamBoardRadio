/**
 * \file
 *
 * \brief SAM UART
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
 */

#ifdef _SAMS70_UART_COMPONENT_
#ifndef _HRI_UART_S70_H_INCLUDED_
#define _HRI_UART_S70_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_UART_CRITICAL_SECTIONS)
#define UART_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define UART_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define UART_CRITICAL_SECTION_ENTER()
#define UART_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_uart_brgr_reg_t;
typedef uint32_t hri_uart_cmpr_reg_t;
typedef uint32_t hri_uart_cr_reg_t;
typedef uint32_t hri_uart_imr_reg_t;
typedef uint32_t hri_uart_mr_reg_t;
typedef uint32_t hri_uart_rhr_reg_t;
typedef uint32_t hri_uart_sr_reg_t;
typedef uint32_t hri_uart_thr_reg_t;
typedef uint32_t hri_uart_wpmr_reg_t;

static inline void hri_uart_set_IMR_RXRDY_bit(const void *const hw)
{
	((Uart *)hw)->UART_IER = UART_IMR_RXRDY;
}

static inline bool hri_uart_get_IMR_RXRDY_bit(const void *const hw)
{
	return (((Uart *)hw)->UART_IMR & UART_IMR_RXRDY) >> UART_IMR_RXRDY_Pos;
}

static inline void hri_uart_write_IMR_RXRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Uart *)hw)->UART_IDR = UART_IMR_RXRDY;
	} else {
		((Uart *)hw)->UART_IER = UART_IMR_RXRDY;
	}
}

static inline void hri_uart_clear_IMR_RXRDY_bit(const void *const hw)
{
	((Uart *)hw)->UART_IDR = UART_IMR_RXRDY;
}

static inline void hri_uart_set_IMR_TXRDY_bit(const void *const hw)
{
	((Uart *)hw)->UART_IER = UART_IMR_TXRDY;
}

static inline bool hri_uart_get_IMR_TXRDY_bit(const void *const hw)
{
	return (((Uart *)hw)->UART_IMR & UART_IMR_TXRDY) >> UART_IMR_TXRDY_Pos;
}

static inline void hri_uart_write_IMR_TXRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Uart *)hw)->UART_IDR = UART_IMR_TXRDY;
	} else {
		((Uart *)hw)->UART_IER = UART_IMR_TXRDY;
	}
}

static inline void hri_uart_clear_IMR_TXRDY_bit(const void *const hw)
{
	((Uart *)hw)->UART_IDR = UART_IMR_TXRDY;
}

static inline void hri_uart_set_IMR_OVRE_bit(const void *const hw)
{
	((Uart *)hw)->UART_IER = UART_IMR_OVRE;
}

static inline bool hri_uart_get_IMR_OVRE_bit(const void *const hw)
{
	return (((Uart *)hw)->UART_IMR & UART_IMR_OVRE) >> UART_IMR_OVRE_Pos;
}

static inline void hri_uart_write_IMR_OVRE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Uart *)hw)->UART_IDR = UART_IMR_OVRE;
	} else {
		((Uart *)hw)->UART_IER = UART_IMR_OVRE;
	}
}

static inline void hri_uart_clear_IMR_OVRE_bit(const void *const hw)
{
	((Uart *)hw)->UART_IDR = UART_IMR_OVRE;
}

static inline void hri_uart_set_IMR_FRAME_bit(const void *const hw)
{
	((Uart *)hw)->UART_IER = UART_IMR_FRAME;
}

static inline bool hri_uart_get_IMR_FRAME_bit(const void *const hw)
{
	return (((Uart *)hw)->UART_IMR & UART_IMR_FRAME) >> UART_IMR_FRAME_Pos;
}

static inline void hri_uart_write_IMR_FRAME_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Uart *)hw)->UART_IDR = UART_IMR_FRAME;
	} else {
		((Uart *)hw)->UART_IER = UART_IMR_FRAME;
	}
}

static inline void hri_uart_clear_IMR_FRAME_bit(const void *const hw)
{
	((Uart *)hw)->UART_IDR = UART_IMR_FRAME;
}

static inline void hri_uart_set_IMR_PARE_bit(const void *const hw)
{
	((Uart *)hw)->UART_IER = UART_IMR_PARE;
}

static inline bool hri_uart_get_IMR_PARE_bit(const void *const hw)
{
	return (((Uart *)hw)->UART_IMR & UART_IMR_PARE) >> UART_IMR_PARE_Pos;
}

static inline void hri_uart_write_IMR_PARE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Uart *)hw)->UART_IDR = UART_IMR_PARE;
	} else {
		((Uart *)hw)->UART_IER = UART_IMR_PARE;
	}
}

static inline void hri_uart_clear_IMR_PARE_bit(const void *const hw)
{
	((Uart *)hw)->UART_IDR = UART_IMR_PARE;
}

static inline void hri_uart_set_IMR_TXEMPTY_bit(const void *const hw)
{
	((Uart *)hw)->UART_IER = UART_IMR_TXEMPTY;
}

static inline bool hri_uart_get_IMR_TXEMPTY_bit(const void *const hw)
{
	return (((Uart *)hw)->UART_IMR & UART_IMR_TXEMPTY) >> UART_IMR_TXEMPTY_Pos;
}

static inline void hri_uart_write_IMR_TXEMPTY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Uart *)hw)->UART_IDR = UART_IMR_TXEMPTY;
	} else {
		((Uart *)hw)->UART_IER = UART_IMR_TXEMPTY;
	}
}

static inline void hri_uart_clear_IMR_TXEMPTY_bit(const void *const hw)
{
	((Uart *)hw)->UART_IDR = UART_IMR_TXEMPTY;
}

static inline void hri_uart_set_IMR_CMP_bit(const void *const hw)
{
	((Uart *)hw)->UART_IER = UART_IMR_CMP;
}

static inline bool hri_uart_get_IMR_CMP_bit(const void *const hw)
{
	return (((Uart *)hw)->UART_IMR & UART_IMR_CMP) >> UART_IMR_CMP_Pos;
}

static inline void hri_uart_write_IMR_CMP_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Uart *)hw)->UART_IDR = UART_IMR_CMP;
	} else {
		((Uart *)hw)->UART_IER = UART_IMR_CMP;
	}
}

static inline void hri_uart_clear_IMR_CMP_bit(const void *const hw)
{
	((Uart *)hw)->UART_IDR = UART_IMR_CMP;
}

static inline void hri_uart_set_IMR_reg(const void *const hw, hri_uart_imr_reg_t mask)
{
	((Uart *)hw)->UART_IER = mask;
}

static inline hri_uart_imr_reg_t hri_uart_get_IMR_reg(const void *const hw, hri_uart_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Uart *)hw)->UART_IMR;
	tmp &= mask;
	return tmp;
}

static inline hri_uart_imr_reg_t hri_uart_read_IMR_reg(const void *const hw)
{
	return ((Uart *)hw)->UART_IMR;
}

static inline void hri_uart_write_IMR_reg(const void *const hw, hri_uart_imr_reg_t data)
{
	((Uart *)hw)->UART_IER = data;
	((Uart *)hw)->UART_IDR = ~data;
}

static inline void hri_uart_clear_IMR_reg(const void *const hw, hri_uart_imr_reg_t mask)
{
	((Uart *)hw)->UART_IDR = mask;
}

static inline void hri_uart_write_CR_reg(const void *const hw, hri_uart_cr_reg_t data)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_CR = data;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_write_THR_reg(const void *const hw, hri_uart_thr_reg_t data)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_THR = data;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_set_MR_FILTER_bit(const void *const hw)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_MR |= UART_MR_FILTER;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_uart_get_MR_FILTER_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Uart *)hw)->UART_MR;
	tmp = (tmp & UART_MR_FILTER) >> UART_MR_FILTER_Pos;
	return (bool)tmp;
}

static inline void hri_uart_write_MR_FILTER_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	UART_CRITICAL_SECTION_ENTER();
	tmp = ((Uart *)hw)->UART_MR;
	tmp &= ~UART_MR_FILTER;
	tmp |= value << UART_MR_FILTER_Pos;
	((Uart *)hw)->UART_MR = tmp;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_clear_MR_FILTER_bit(const void *const hw)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_MR &= ~UART_MR_FILTER;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_toggle_MR_FILTER_bit(const void *const hw)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_MR ^= UART_MR_FILTER;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_set_MR_BRSRCCK_bit(const void *const hw)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_MR |= UART_MR_BRSRCCK;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_uart_get_MR_BRSRCCK_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Uart *)hw)->UART_MR;
	tmp = (tmp & UART_MR_BRSRCCK) >> UART_MR_BRSRCCK_Pos;
	return (bool)tmp;
}

static inline void hri_uart_write_MR_BRSRCCK_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	UART_CRITICAL_SECTION_ENTER();
	tmp = ((Uart *)hw)->UART_MR;
	tmp &= ~UART_MR_BRSRCCK;
	tmp |= value << UART_MR_BRSRCCK_Pos;
	((Uart *)hw)->UART_MR = tmp;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_clear_MR_BRSRCCK_bit(const void *const hw)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_MR &= ~UART_MR_BRSRCCK;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_toggle_MR_BRSRCCK_bit(const void *const hw)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_MR ^= UART_MR_BRSRCCK;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_set_MR_PAR_bf(const void *const hw, hri_uart_mr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_MR |= UART_MR_PAR(mask);
	UART_CRITICAL_SECTION_LEAVE();
}

static inline hri_uart_mr_reg_t hri_uart_get_MR_PAR_bf(const void *const hw, hri_uart_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Uart *)hw)->UART_MR;
	tmp = (tmp & UART_MR_PAR(mask)) >> UART_MR_PAR_Pos;
	return tmp;
}

static inline void hri_uart_write_MR_PAR_bf(const void *const hw, hri_uart_mr_reg_t data)
{
	uint32_t tmp;
	UART_CRITICAL_SECTION_ENTER();
	tmp = ((Uart *)hw)->UART_MR;
	tmp &= ~UART_MR_PAR_Msk;
	tmp |= UART_MR_PAR(data);
	((Uart *)hw)->UART_MR = tmp;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_clear_MR_PAR_bf(const void *const hw, hri_uart_mr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_MR &= ~UART_MR_PAR(mask);
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_toggle_MR_PAR_bf(const void *const hw, hri_uart_mr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_MR ^= UART_MR_PAR(mask);
	UART_CRITICAL_SECTION_LEAVE();
}

static inline hri_uart_mr_reg_t hri_uart_read_MR_PAR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Uart *)hw)->UART_MR;
	tmp = (tmp & UART_MR_PAR_Msk) >> UART_MR_PAR_Pos;
	return tmp;
}

static inline void hri_uart_set_MR_CHMODE_bf(const void *const hw, hri_uart_mr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_MR |= UART_MR_CHMODE(mask);
	UART_CRITICAL_SECTION_LEAVE();
}

static inline hri_uart_mr_reg_t hri_uart_get_MR_CHMODE_bf(const void *const hw, hri_uart_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Uart *)hw)->UART_MR;
	tmp = (tmp & UART_MR_CHMODE(mask)) >> UART_MR_CHMODE_Pos;
	return tmp;
}

static inline void hri_uart_write_MR_CHMODE_bf(const void *const hw, hri_uart_mr_reg_t data)
{
	uint32_t tmp;
	UART_CRITICAL_SECTION_ENTER();
	tmp = ((Uart *)hw)->UART_MR;
	tmp &= ~UART_MR_CHMODE_Msk;
	tmp |= UART_MR_CHMODE(data);
	((Uart *)hw)->UART_MR = tmp;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_clear_MR_CHMODE_bf(const void *const hw, hri_uart_mr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_MR &= ~UART_MR_CHMODE(mask);
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_toggle_MR_CHMODE_bf(const void *const hw, hri_uart_mr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_MR ^= UART_MR_CHMODE(mask);
	UART_CRITICAL_SECTION_LEAVE();
}

static inline hri_uart_mr_reg_t hri_uart_read_MR_CHMODE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Uart *)hw)->UART_MR;
	tmp = (tmp & UART_MR_CHMODE_Msk) >> UART_MR_CHMODE_Pos;
	return tmp;
}

static inline void hri_uart_set_MR_reg(const void *const hw, hri_uart_mr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_MR |= mask;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline hri_uart_mr_reg_t hri_uart_get_MR_reg(const void *const hw, hri_uart_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Uart *)hw)->UART_MR;
	tmp &= mask;
	return tmp;
}

static inline void hri_uart_write_MR_reg(const void *const hw, hri_uart_mr_reg_t data)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_MR = data;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_clear_MR_reg(const void *const hw, hri_uart_mr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_MR &= ~mask;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_toggle_MR_reg(const void *const hw, hri_uart_mr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_MR ^= mask;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline hri_uart_mr_reg_t hri_uart_read_MR_reg(const void *const hw)
{
	return ((Uart *)hw)->UART_MR;
}

static inline void hri_uart_set_BRGR_CD_bf(const void *const hw, hri_uart_brgr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_BRGR |= UART_BRGR_CD(mask);
	UART_CRITICAL_SECTION_LEAVE();
}

static inline hri_uart_brgr_reg_t hri_uart_get_BRGR_CD_bf(const void *const hw, hri_uart_brgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Uart *)hw)->UART_BRGR;
	tmp = (tmp & UART_BRGR_CD(mask)) >> UART_BRGR_CD_Pos;
	return tmp;
}

static inline void hri_uart_write_BRGR_CD_bf(const void *const hw, hri_uart_brgr_reg_t data)
{
	uint32_t tmp;
	UART_CRITICAL_SECTION_ENTER();
	tmp = ((Uart *)hw)->UART_BRGR;
	tmp &= ~UART_BRGR_CD_Msk;
	tmp |= UART_BRGR_CD(data);
	((Uart *)hw)->UART_BRGR = tmp;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_clear_BRGR_CD_bf(const void *const hw, hri_uart_brgr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_BRGR &= ~UART_BRGR_CD(mask);
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_toggle_BRGR_CD_bf(const void *const hw, hri_uart_brgr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_BRGR ^= UART_BRGR_CD(mask);
	UART_CRITICAL_SECTION_LEAVE();
}

static inline hri_uart_brgr_reg_t hri_uart_read_BRGR_CD_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Uart *)hw)->UART_BRGR;
	tmp = (tmp & UART_BRGR_CD_Msk) >> UART_BRGR_CD_Pos;
	return tmp;
}

static inline void hri_uart_set_BRGR_reg(const void *const hw, hri_uart_brgr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_BRGR |= mask;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline hri_uart_brgr_reg_t hri_uart_get_BRGR_reg(const void *const hw, hri_uart_brgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Uart *)hw)->UART_BRGR;
	tmp &= mask;
	return tmp;
}

static inline void hri_uart_write_BRGR_reg(const void *const hw, hri_uart_brgr_reg_t data)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_BRGR = data;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_clear_BRGR_reg(const void *const hw, hri_uart_brgr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_BRGR &= ~mask;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_toggle_BRGR_reg(const void *const hw, hri_uart_brgr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_BRGR ^= mask;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline hri_uart_brgr_reg_t hri_uart_read_BRGR_reg(const void *const hw)
{
	return ((Uart *)hw)->UART_BRGR;
}

static inline void hri_uart_set_CMPR_CMPMODE_bit(const void *const hw)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_CMPR |= UART_CMPR_CMPMODE;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_uart_get_CMPR_CMPMODE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Uart *)hw)->UART_CMPR;
	tmp = (tmp & UART_CMPR_CMPMODE) >> UART_CMPR_CMPMODE_Pos;
	return (bool)tmp;
}

static inline void hri_uart_write_CMPR_CMPMODE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	UART_CRITICAL_SECTION_ENTER();
	tmp = ((Uart *)hw)->UART_CMPR;
	tmp &= ~UART_CMPR_CMPMODE;
	tmp |= value << UART_CMPR_CMPMODE_Pos;
	((Uart *)hw)->UART_CMPR = tmp;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_clear_CMPR_CMPMODE_bit(const void *const hw)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_CMPR &= ~UART_CMPR_CMPMODE;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_toggle_CMPR_CMPMODE_bit(const void *const hw)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_CMPR ^= UART_CMPR_CMPMODE;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_set_CMPR_CMPPAR_bit(const void *const hw)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_CMPR |= UART_CMPR_CMPPAR;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_uart_get_CMPR_CMPPAR_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Uart *)hw)->UART_CMPR;
	tmp = (tmp & UART_CMPR_CMPPAR) >> UART_CMPR_CMPPAR_Pos;
	return (bool)tmp;
}

static inline void hri_uart_write_CMPR_CMPPAR_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	UART_CRITICAL_SECTION_ENTER();
	tmp = ((Uart *)hw)->UART_CMPR;
	tmp &= ~UART_CMPR_CMPPAR;
	tmp |= value << UART_CMPR_CMPPAR_Pos;
	((Uart *)hw)->UART_CMPR = tmp;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_clear_CMPR_CMPPAR_bit(const void *const hw)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_CMPR &= ~UART_CMPR_CMPPAR;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_toggle_CMPR_CMPPAR_bit(const void *const hw)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_CMPR ^= UART_CMPR_CMPPAR;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_set_CMPR_VAL1_bf(const void *const hw, hri_uart_cmpr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_CMPR |= UART_CMPR_VAL1(mask);
	UART_CRITICAL_SECTION_LEAVE();
}

static inline hri_uart_cmpr_reg_t hri_uart_get_CMPR_VAL1_bf(const void *const hw, hri_uart_cmpr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Uart *)hw)->UART_CMPR;
	tmp = (tmp & UART_CMPR_VAL1(mask)) >> UART_CMPR_VAL1_Pos;
	return tmp;
}

static inline void hri_uart_write_CMPR_VAL1_bf(const void *const hw, hri_uart_cmpr_reg_t data)
{
	uint32_t tmp;
	UART_CRITICAL_SECTION_ENTER();
	tmp = ((Uart *)hw)->UART_CMPR;
	tmp &= ~UART_CMPR_VAL1_Msk;
	tmp |= UART_CMPR_VAL1(data);
	((Uart *)hw)->UART_CMPR = tmp;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_clear_CMPR_VAL1_bf(const void *const hw, hri_uart_cmpr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_CMPR &= ~UART_CMPR_VAL1(mask);
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_toggle_CMPR_VAL1_bf(const void *const hw, hri_uart_cmpr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_CMPR ^= UART_CMPR_VAL1(mask);
	UART_CRITICAL_SECTION_LEAVE();
}

static inline hri_uart_cmpr_reg_t hri_uart_read_CMPR_VAL1_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Uart *)hw)->UART_CMPR;
	tmp = (tmp & UART_CMPR_VAL1_Msk) >> UART_CMPR_VAL1_Pos;
	return tmp;
}

static inline void hri_uart_set_CMPR_VAL2_bf(const void *const hw, hri_uart_cmpr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_CMPR |= UART_CMPR_VAL2(mask);
	UART_CRITICAL_SECTION_LEAVE();
}

static inline hri_uart_cmpr_reg_t hri_uart_get_CMPR_VAL2_bf(const void *const hw, hri_uart_cmpr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Uart *)hw)->UART_CMPR;
	tmp = (tmp & UART_CMPR_VAL2(mask)) >> UART_CMPR_VAL2_Pos;
	return tmp;
}

static inline void hri_uart_write_CMPR_VAL2_bf(const void *const hw, hri_uart_cmpr_reg_t data)
{
	uint32_t tmp;
	UART_CRITICAL_SECTION_ENTER();
	tmp = ((Uart *)hw)->UART_CMPR;
	tmp &= ~UART_CMPR_VAL2_Msk;
	tmp |= UART_CMPR_VAL2(data);
	((Uart *)hw)->UART_CMPR = tmp;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_clear_CMPR_VAL2_bf(const void *const hw, hri_uart_cmpr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_CMPR &= ~UART_CMPR_VAL2(mask);
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_toggle_CMPR_VAL2_bf(const void *const hw, hri_uart_cmpr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_CMPR ^= UART_CMPR_VAL2(mask);
	UART_CRITICAL_SECTION_LEAVE();
}

static inline hri_uart_cmpr_reg_t hri_uart_read_CMPR_VAL2_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Uart *)hw)->UART_CMPR;
	tmp = (tmp & UART_CMPR_VAL2_Msk) >> UART_CMPR_VAL2_Pos;
	return tmp;
}

static inline void hri_uart_set_CMPR_reg(const void *const hw, hri_uart_cmpr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_CMPR |= mask;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline hri_uart_cmpr_reg_t hri_uart_get_CMPR_reg(const void *const hw, hri_uart_cmpr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Uart *)hw)->UART_CMPR;
	tmp &= mask;
	return tmp;
}

static inline void hri_uart_write_CMPR_reg(const void *const hw, hri_uart_cmpr_reg_t data)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_CMPR = data;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_clear_CMPR_reg(const void *const hw, hri_uart_cmpr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_CMPR &= ~mask;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_toggle_CMPR_reg(const void *const hw, hri_uart_cmpr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_CMPR ^= mask;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline hri_uart_cmpr_reg_t hri_uart_read_CMPR_reg(const void *const hw)
{
	return ((Uart *)hw)->UART_CMPR;
}

static inline void hri_uart_set_WPMR_WPEN_bit(const void *const hw)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_WPMR |= UART_WPMR_WPEN;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_uart_get_WPMR_WPEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Uart *)hw)->UART_WPMR;
	tmp = (tmp & UART_WPMR_WPEN) >> UART_WPMR_WPEN_Pos;
	return (bool)tmp;
}

static inline void hri_uart_write_WPMR_WPEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	UART_CRITICAL_SECTION_ENTER();
	tmp = ((Uart *)hw)->UART_WPMR;
	tmp &= ~UART_WPMR_WPEN;
	tmp |= value << UART_WPMR_WPEN_Pos;
	((Uart *)hw)->UART_WPMR = tmp;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_clear_WPMR_WPEN_bit(const void *const hw)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_WPMR &= ~UART_WPMR_WPEN;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_toggle_WPMR_WPEN_bit(const void *const hw)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_WPMR ^= UART_WPMR_WPEN;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_set_WPMR_WPKEY_bf(const void *const hw, hri_uart_wpmr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_WPMR |= UART_WPMR_WPKEY(mask);
	UART_CRITICAL_SECTION_LEAVE();
}

static inline hri_uart_wpmr_reg_t hri_uart_get_WPMR_WPKEY_bf(const void *const hw, hri_uart_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Uart *)hw)->UART_WPMR;
	tmp = (tmp & UART_WPMR_WPKEY(mask)) >> UART_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_uart_write_WPMR_WPKEY_bf(const void *const hw, hri_uart_wpmr_reg_t data)
{
	uint32_t tmp;
	UART_CRITICAL_SECTION_ENTER();
	tmp = ((Uart *)hw)->UART_WPMR;
	tmp &= ~UART_WPMR_WPKEY_Msk;
	tmp |= UART_WPMR_WPKEY(data);
	((Uart *)hw)->UART_WPMR = tmp;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_clear_WPMR_WPKEY_bf(const void *const hw, hri_uart_wpmr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_WPMR &= ~UART_WPMR_WPKEY(mask);
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_toggle_WPMR_WPKEY_bf(const void *const hw, hri_uart_wpmr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_WPMR ^= UART_WPMR_WPKEY(mask);
	UART_CRITICAL_SECTION_LEAVE();
}

static inline hri_uart_wpmr_reg_t hri_uart_read_WPMR_WPKEY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Uart *)hw)->UART_WPMR;
	tmp = (tmp & UART_WPMR_WPKEY_Msk) >> UART_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_uart_set_WPMR_reg(const void *const hw, hri_uart_wpmr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_WPMR |= mask;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline hri_uart_wpmr_reg_t hri_uart_get_WPMR_reg(const void *const hw, hri_uart_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Uart *)hw)->UART_WPMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_uart_write_WPMR_reg(const void *const hw, hri_uart_wpmr_reg_t data)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_WPMR = data;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_clear_WPMR_reg(const void *const hw, hri_uart_wpmr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_WPMR &= ~mask;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_uart_toggle_WPMR_reg(const void *const hw, hri_uart_wpmr_reg_t mask)
{
	UART_CRITICAL_SECTION_ENTER();
	((Uart *)hw)->UART_WPMR ^= mask;
	UART_CRITICAL_SECTION_LEAVE();
}

static inline hri_uart_wpmr_reg_t hri_uart_read_WPMR_reg(const void *const hw)
{
	return ((Uart *)hw)->UART_WPMR;
}

static inline bool hri_uart_get_SR_RXRDY_bit(const void *const hw)
{
	return (((Uart *)hw)->UART_SR & UART_SR_RXRDY) > 0;
}

static inline bool hri_uart_get_SR_TXRDY_bit(const void *const hw)
{
	return (((Uart *)hw)->UART_SR & UART_SR_TXRDY) > 0;
}

static inline bool hri_uart_get_SR_OVRE_bit(const void *const hw)
{
	return (((Uart *)hw)->UART_SR & UART_SR_OVRE) > 0;
}

static inline bool hri_uart_get_SR_FRAME_bit(const void *const hw)
{
	return (((Uart *)hw)->UART_SR & UART_SR_FRAME) > 0;
}

static inline bool hri_uart_get_SR_PARE_bit(const void *const hw)
{
	return (((Uart *)hw)->UART_SR & UART_SR_PARE) > 0;
}

static inline bool hri_uart_get_SR_TXEMPTY_bit(const void *const hw)
{
	return (((Uart *)hw)->UART_SR & UART_SR_TXEMPTY) > 0;
}

static inline bool hri_uart_get_SR_CMP_bit(const void *const hw)
{
	return (((Uart *)hw)->UART_SR & UART_SR_CMP) > 0;
}

static inline hri_uart_sr_reg_t hri_uart_get_SR_reg(const void *const hw, hri_uart_sr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Uart *)hw)->UART_SR;
	tmp &= mask;
	return tmp;
}

static inline hri_uart_sr_reg_t hri_uart_read_SR_reg(const void *const hw)
{
	return ((Uart *)hw)->UART_SR;
}

static inline hri_uart_rhr_reg_t hri_uart_get_RHR_RXCHR_bf(const void *const hw, hri_uart_rhr_reg_t mask)
{
	return (((Uart *)hw)->UART_RHR & UART_RHR_RXCHR(mask)) >> UART_RHR_RXCHR_Pos;
}

static inline hri_uart_rhr_reg_t hri_uart_read_RHR_RXCHR_bf(const void *const hw)
{
	return (((Uart *)hw)->UART_RHR & UART_RHR_RXCHR_Msk) >> UART_RHR_RXCHR_Pos;
}

static inline hri_uart_rhr_reg_t hri_uart_get_RHR_reg(const void *const hw, hri_uart_rhr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Uart *)hw)->UART_RHR;
	tmp &= mask;
	return tmp;
}

static inline hri_uart_rhr_reg_t hri_uart_read_RHR_reg(const void *const hw)
{
	return ((Uart *)hw)->UART_RHR;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_UART_S70_H_INCLUDED */
#endif /* _SAMS70_UART_COMPONENT_ */
