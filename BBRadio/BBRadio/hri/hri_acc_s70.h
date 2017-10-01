/**
 * \file
 *
 * \brief SAM ACC
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

#ifdef _SAMS70_ACC_COMPONENT_
#ifndef _HRI_ACC_S70_H_INCLUDED_
#define _HRI_ACC_S70_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_ACC_CRITICAL_SECTIONS)
#define ACC_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define ACC_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define ACC_CRITICAL_SECTION_ENTER()
#define ACC_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_acc_acr_reg_t;
typedef uint32_t hri_acc_cr_reg_t;
typedef uint32_t hri_acc_imr_reg_t;
typedef uint32_t hri_acc_isr_reg_t;
typedef uint32_t hri_acc_mr_reg_t;
typedef uint32_t hri_acc_wpmr_reg_t;
typedef uint32_t hri_acc_wpsr_reg_t;

static inline void hri_acc_set_IMR_CE_bit(const void *const hw)
{
	((Acc *)hw)->ACC_IER = ACC_IMR_CE;
}

static inline bool hri_acc_get_IMR_CE_bit(const void *const hw)
{
	return (((Acc *)hw)->ACC_IMR & ACC_IMR_CE) >> ACC_IMR_CE_Pos;
}

static inline void hri_acc_write_IMR_CE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Acc *)hw)->ACC_IDR = ACC_IMR_CE;
	} else {
		((Acc *)hw)->ACC_IER = ACC_IMR_CE;
	}
}

static inline void hri_acc_clear_IMR_CE_bit(const void *const hw)
{
	((Acc *)hw)->ACC_IDR = ACC_IMR_CE;
}

static inline void hri_acc_set_IMR_reg(const void *const hw, hri_acc_imr_reg_t mask)
{
	((Acc *)hw)->ACC_IER = mask;
}

static inline hri_acc_imr_reg_t hri_acc_get_IMR_reg(const void *const hw, hri_acc_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Acc *)hw)->ACC_IMR;
	tmp &= mask;
	return tmp;
}

static inline hri_acc_imr_reg_t hri_acc_read_IMR_reg(const void *const hw)
{
	return ((Acc *)hw)->ACC_IMR;
}

static inline void hri_acc_write_IMR_reg(const void *const hw, hri_acc_imr_reg_t data)
{
	((Acc *)hw)->ACC_IER = data;
	((Acc *)hw)->ACC_IDR = ~data;
}

static inline void hri_acc_clear_IMR_reg(const void *const hw, hri_acc_imr_reg_t mask)
{
	((Acc *)hw)->ACC_IDR = mask;
}

static inline bool hri_acc_get_ISR_CE_bit(const void *const hw)
{
	return (((Acc *)hw)->ACC_ISR & ACC_ISR_CE) >> ACC_ISR_CE_Pos;
}

static inline bool hri_acc_get_ISR_SCO_bit(const void *const hw)
{
	return (((Acc *)hw)->ACC_ISR & ACC_ISR_SCO) >> ACC_ISR_SCO_Pos;
}

static inline bool hri_acc_get_ISR_MASK_bit(const void *const hw)
{
	return (((Acc *)hw)->ACC_ISR & ACC_ISR_MASK) >> ACC_ISR_MASK_Pos;
}

static inline hri_acc_isr_reg_t hri_acc_get_ISR_reg(const void *const hw, hri_acc_isr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Acc *)hw)->ACC_ISR;
	tmp &= mask;
	return tmp;
}

static inline hri_acc_isr_reg_t hri_acc_read_ISR_reg(const void *const hw)
{
	return ((Acc *)hw)->ACC_ISR;
}

static inline void hri_acc_write_CR_reg(const void *const hw, hri_acc_cr_reg_t data)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_CR = data;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_set_MR_ACEN_bit(const void *const hw)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_MR |= ACC_MR_ACEN;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_acc_get_MR_ACEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Acc *)hw)->ACC_MR;
	tmp = (tmp & ACC_MR_ACEN) >> ACC_MR_ACEN_Pos;
	return (bool)tmp;
}

static inline void hri_acc_write_MR_ACEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ACC_CRITICAL_SECTION_ENTER();
	tmp = ((Acc *)hw)->ACC_MR;
	tmp &= ~ACC_MR_ACEN;
	tmp |= value << ACC_MR_ACEN_Pos;
	((Acc *)hw)->ACC_MR = tmp;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_clear_MR_ACEN_bit(const void *const hw)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_MR &= ~ACC_MR_ACEN;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_toggle_MR_ACEN_bit(const void *const hw)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_MR ^= ACC_MR_ACEN;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_set_MR_INV_bit(const void *const hw)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_MR |= ACC_MR_INV;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_acc_get_MR_INV_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Acc *)hw)->ACC_MR;
	tmp = (tmp & ACC_MR_INV) >> ACC_MR_INV_Pos;
	return (bool)tmp;
}

static inline void hri_acc_write_MR_INV_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ACC_CRITICAL_SECTION_ENTER();
	tmp = ((Acc *)hw)->ACC_MR;
	tmp &= ~ACC_MR_INV;
	tmp |= value << ACC_MR_INV_Pos;
	((Acc *)hw)->ACC_MR = tmp;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_clear_MR_INV_bit(const void *const hw)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_MR &= ~ACC_MR_INV;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_toggle_MR_INV_bit(const void *const hw)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_MR ^= ACC_MR_INV;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_set_MR_SELFS_bit(const void *const hw)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_MR |= ACC_MR_SELFS;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_acc_get_MR_SELFS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Acc *)hw)->ACC_MR;
	tmp = (tmp & ACC_MR_SELFS) >> ACC_MR_SELFS_Pos;
	return (bool)tmp;
}

static inline void hri_acc_write_MR_SELFS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ACC_CRITICAL_SECTION_ENTER();
	tmp = ((Acc *)hw)->ACC_MR;
	tmp &= ~ACC_MR_SELFS;
	tmp |= value << ACC_MR_SELFS_Pos;
	((Acc *)hw)->ACC_MR = tmp;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_clear_MR_SELFS_bit(const void *const hw)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_MR &= ~ACC_MR_SELFS;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_toggle_MR_SELFS_bit(const void *const hw)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_MR ^= ACC_MR_SELFS;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_set_MR_FE_bit(const void *const hw)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_MR |= ACC_MR_FE;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_acc_get_MR_FE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Acc *)hw)->ACC_MR;
	tmp = (tmp & ACC_MR_FE) >> ACC_MR_FE_Pos;
	return (bool)tmp;
}

static inline void hri_acc_write_MR_FE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ACC_CRITICAL_SECTION_ENTER();
	tmp = ((Acc *)hw)->ACC_MR;
	tmp &= ~ACC_MR_FE;
	tmp |= value << ACC_MR_FE_Pos;
	((Acc *)hw)->ACC_MR = tmp;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_clear_MR_FE_bit(const void *const hw)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_MR &= ~ACC_MR_FE;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_toggle_MR_FE_bit(const void *const hw)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_MR ^= ACC_MR_FE;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_set_MR_SELMINUS_bf(const void *const hw, hri_acc_mr_reg_t mask)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_MR |= ACC_MR_SELMINUS(mask);
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_acc_mr_reg_t hri_acc_get_MR_SELMINUS_bf(const void *const hw, hri_acc_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Acc *)hw)->ACC_MR;
	tmp = (tmp & ACC_MR_SELMINUS(mask)) >> ACC_MR_SELMINUS_Pos;
	return tmp;
}

static inline void hri_acc_write_MR_SELMINUS_bf(const void *const hw, hri_acc_mr_reg_t data)
{
	uint32_t tmp;
	ACC_CRITICAL_SECTION_ENTER();
	tmp = ((Acc *)hw)->ACC_MR;
	tmp &= ~ACC_MR_SELMINUS_Msk;
	tmp |= ACC_MR_SELMINUS(data);
	((Acc *)hw)->ACC_MR = tmp;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_clear_MR_SELMINUS_bf(const void *const hw, hri_acc_mr_reg_t mask)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_MR &= ~ACC_MR_SELMINUS(mask);
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_toggle_MR_SELMINUS_bf(const void *const hw, hri_acc_mr_reg_t mask)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_MR ^= ACC_MR_SELMINUS(mask);
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_acc_mr_reg_t hri_acc_read_MR_SELMINUS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Acc *)hw)->ACC_MR;
	tmp = (tmp & ACC_MR_SELMINUS_Msk) >> ACC_MR_SELMINUS_Pos;
	return tmp;
}

static inline void hri_acc_set_MR_SELPLUS_bf(const void *const hw, hri_acc_mr_reg_t mask)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_MR |= ACC_MR_SELPLUS(mask);
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_acc_mr_reg_t hri_acc_get_MR_SELPLUS_bf(const void *const hw, hri_acc_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Acc *)hw)->ACC_MR;
	tmp = (tmp & ACC_MR_SELPLUS(mask)) >> ACC_MR_SELPLUS_Pos;
	return tmp;
}

static inline void hri_acc_write_MR_SELPLUS_bf(const void *const hw, hri_acc_mr_reg_t data)
{
	uint32_t tmp;
	ACC_CRITICAL_SECTION_ENTER();
	tmp = ((Acc *)hw)->ACC_MR;
	tmp &= ~ACC_MR_SELPLUS_Msk;
	tmp |= ACC_MR_SELPLUS(data);
	((Acc *)hw)->ACC_MR = tmp;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_clear_MR_SELPLUS_bf(const void *const hw, hri_acc_mr_reg_t mask)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_MR &= ~ACC_MR_SELPLUS(mask);
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_toggle_MR_SELPLUS_bf(const void *const hw, hri_acc_mr_reg_t mask)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_MR ^= ACC_MR_SELPLUS(mask);
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_acc_mr_reg_t hri_acc_read_MR_SELPLUS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Acc *)hw)->ACC_MR;
	tmp = (tmp & ACC_MR_SELPLUS_Msk) >> ACC_MR_SELPLUS_Pos;
	return tmp;
}

static inline void hri_acc_set_MR_EDGETYP_bf(const void *const hw, hri_acc_mr_reg_t mask)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_MR |= ACC_MR_EDGETYP(mask);
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_acc_mr_reg_t hri_acc_get_MR_EDGETYP_bf(const void *const hw, hri_acc_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Acc *)hw)->ACC_MR;
	tmp = (tmp & ACC_MR_EDGETYP(mask)) >> ACC_MR_EDGETYP_Pos;
	return tmp;
}

static inline void hri_acc_write_MR_EDGETYP_bf(const void *const hw, hri_acc_mr_reg_t data)
{
	uint32_t tmp;
	ACC_CRITICAL_SECTION_ENTER();
	tmp = ((Acc *)hw)->ACC_MR;
	tmp &= ~ACC_MR_EDGETYP_Msk;
	tmp |= ACC_MR_EDGETYP(data);
	((Acc *)hw)->ACC_MR = tmp;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_clear_MR_EDGETYP_bf(const void *const hw, hri_acc_mr_reg_t mask)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_MR &= ~ACC_MR_EDGETYP(mask);
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_toggle_MR_EDGETYP_bf(const void *const hw, hri_acc_mr_reg_t mask)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_MR ^= ACC_MR_EDGETYP(mask);
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_acc_mr_reg_t hri_acc_read_MR_EDGETYP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Acc *)hw)->ACC_MR;
	tmp = (tmp & ACC_MR_EDGETYP_Msk) >> ACC_MR_EDGETYP_Pos;
	return tmp;
}

static inline void hri_acc_set_MR_reg(const void *const hw, hri_acc_mr_reg_t mask)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_MR |= mask;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_acc_mr_reg_t hri_acc_get_MR_reg(const void *const hw, hri_acc_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Acc *)hw)->ACC_MR;
	tmp &= mask;
	return tmp;
}

static inline void hri_acc_write_MR_reg(const void *const hw, hri_acc_mr_reg_t data)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_MR = data;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_clear_MR_reg(const void *const hw, hri_acc_mr_reg_t mask)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_MR &= ~mask;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_toggle_MR_reg(const void *const hw, hri_acc_mr_reg_t mask)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_MR ^= mask;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_acc_mr_reg_t hri_acc_read_MR_reg(const void *const hw)
{
	return ((Acc *)hw)->ACC_MR;
}

static inline void hri_acc_set_ACR_ISEL_bit(const void *const hw)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_ACR |= ACC_ACR_ISEL;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_acc_get_ACR_ISEL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Acc *)hw)->ACC_ACR;
	tmp = (tmp & ACC_ACR_ISEL) >> ACC_ACR_ISEL_Pos;
	return (bool)tmp;
}

static inline void hri_acc_write_ACR_ISEL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ACC_CRITICAL_SECTION_ENTER();
	tmp = ((Acc *)hw)->ACC_ACR;
	tmp &= ~ACC_ACR_ISEL;
	tmp |= value << ACC_ACR_ISEL_Pos;
	((Acc *)hw)->ACC_ACR = tmp;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_clear_ACR_ISEL_bit(const void *const hw)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_ACR &= ~ACC_ACR_ISEL;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_toggle_ACR_ISEL_bit(const void *const hw)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_ACR ^= ACC_ACR_ISEL;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_set_ACR_HYST_bf(const void *const hw, hri_acc_acr_reg_t mask)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_ACR |= ACC_ACR_HYST(mask);
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_acc_acr_reg_t hri_acc_get_ACR_HYST_bf(const void *const hw, hri_acc_acr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Acc *)hw)->ACC_ACR;
	tmp = (tmp & ACC_ACR_HYST(mask)) >> ACC_ACR_HYST_Pos;
	return tmp;
}

static inline void hri_acc_write_ACR_HYST_bf(const void *const hw, hri_acc_acr_reg_t data)
{
	uint32_t tmp;
	ACC_CRITICAL_SECTION_ENTER();
	tmp = ((Acc *)hw)->ACC_ACR;
	tmp &= ~ACC_ACR_HYST_Msk;
	tmp |= ACC_ACR_HYST(data);
	((Acc *)hw)->ACC_ACR = tmp;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_clear_ACR_HYST_bf(const void *const hw, hri_acc_acr_reg_t mask)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_ACR &= ~ACC_ACR_HYST(mask);
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_toggle_ACR_HYST_bf(const void *const hw, hri_acc_acr_reg_t mask)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_ACR ^= ACC_ACR_HYST(mask);
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_acc_acr_reg_t hri_acc_read_ACR_HYST_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Acc *)hw)->ACC_ACR;
	tmp = (tmp & ACC_ACR_HYST_Msk) >> ACC_ACR_HYST_Pos;
	return tmp;
}

static inline void hri_acc_set_ACR_reg(const void *const hw, hri_acc_acr_reg_t mask)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_ACR |= mask;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_acc_acr_reg_t hri_acc_get_ACR_reg(const void *const hw, hri_acc_acr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Acc *)hw)->ACC_ACR;
	tmp &= mask;
	return tmp;
}

static inline void hri_acc_write_ACR_reg(const void *const hw, hri_acc_acr_reg_t data)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_ACR = data;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_clear_ACR_reg(const void *const hw, hri_acc_acr_reg_t mask)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_ACR &= ~mask;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_toggle_ACR_reg(const void *const hw, hri_acc_acr_reg_t mask)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_ACR ^= mask;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_acc_acr_reg_t hri_acc_read_ACR_reg(const void *const hw)
{
	return ((Acc *)hw)->ACC_ACR;
}

static inline void hri_acc_set_WPMR_WPEN_bit(const void *const hw)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_WPMR |= ACC_WPMR_WPEN;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_acc_get_WPMR_WPEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Acc *)hw)->ACC_WPMR;
	tmp = (tmp & ACC_WPMR_WPEN) >> ACC_WPMR_WPEN_Pos;
	return (bool)tmp;
}

static inline void hri_acc_write_WPMR_WPEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ACC_CRITICAL_SECTION_ENTER();
	tmp = ((Acc *)hw)->ACC_WPMR;
	tmp &= ~ACC_WPMR_WPEN;
	tmp |= value << ACC_WPMR_WPEN_Pos;
	((Acc *)hw)->ACC_WPMR = tmp;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_clear_WPMR_WPEN_bit(const void *const hw)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_WPMR &= ~ACC_WPMR_WPEN;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_toggle_WPMR_WPEN_bit(const void *const hw)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_WPMR ^= ACC_WPMR_WPEN;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_set_WPMR_WPKEY_bf(const void *const hw, hri_acc_wpmr_reg_t mask)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_WPMR |= ACC_WPMR_WPKEY(mask);
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_acc_wpmr_reg_t hri_acc_get_WPMR_WPKEY_bf(const void *const hw, hri_acc_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Acc *)hw)->ACC_WPMR;
	tmp = (tmp & ACC_WPMR_WPKEY(mask)) >> ACC_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_acc_write_WPMR_WPKEY_bf(const void *const hw, hri_acc_wpmr_reg_t data)
{
	uint32_t tmp;
	ACC_CRITICAL_SECTION_ENTER();
	tmp = ((Acc *)hw)->ACC_WPMR;
	tmp &= ~ACC_WPMR_WPKEY_Msk;
	tmp |= ACC_WPMR_WPKEY(data);
	((Acc *)hw)->ACC_WPMR = tmp;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_clear_WPMR_WPKEY_bf(const void *const hw, hri_acc_wpmr_reg_t mask)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_WPMR &= ~ACC_WPMR_WPKEY(mask);
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_toggle_WPMR_WPKEY_bf(const void *const hw, hri_acc_wpmr_reg_t mask)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_WPMR ^= ACC_WPMR_WPKEY(mask);
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_acc_wpmr_reg_t hri_acc_read_WPMR_WPKEY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Acc *)hw)->ACC_WPMR;
	tmp = (tmp & ACC_WPMR_WPKEY_Msk) >> ACC_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_acc_set_WPMR_reg(const void *const hw, hri_acc_wpmr_reg_t mask)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_WPMR |= mask;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_acc_wpmr_reg_t hri_acc_get_WPMR_reg(const void *const hw, hri_acc_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Acc *)hw)->ACC_WPMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_acc_write_WPMR_reg(const void *const hw, hri_acc_wpmr_reg_t data)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_WPMR = data;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_clear_WPMR_reg(const void *const hw, hri_acc_wpmr_reg_t mask)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_WPMR &= ~mask;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_acc_toggle_WPMR_reg(const void *const hw, hri_acc_wpmr_reg_t mask)
{
	ACC_CRITICAL_SECTION_ENTER();
	((Acc *)hw)->ACC_WPMR ^= mask;
	ACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_acc_wpmr_reg_t hri_acc_read_WPMR_reg(const void *const hw)
{
	return ((Acc *)hw)->ACC_WPMR;
}

static inline bool hri_acc_get_WPSR_WPVS_bit(const void *const hw)
{
	return (((Acc *)hw)->ACC_WPSR & ACC_WPSR_WPVS) > 0;
}

static inline hri_acc_wpsr_reg_t hri_acc_get_WPSR_reg(const void *const hw, hri_acc_wpsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Acc *)hw)->ACC_WPSR;
	tmp &= mask;
	return tmp;
}

static inline hri_acc_wpsr_reg_t hri_acc_read_WPSR_reg(const void *const hw)
{
	return ((Acc *)hw)->ACC_WPSR;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_ACC_S70_H_INCLUDED */
#endif /* _SAMS70_ACC_COMPONENT_ */
