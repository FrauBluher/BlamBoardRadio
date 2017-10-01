/**
 * \file
 *
 * \brief SAM RSWDT
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

#ifdef _SAMS70_RSWDT_COMPONENT_
#ifndef _HRI_RSWDT_S70_H_INCLUDED_
#define _HRI_RSWDT_S70_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_RSWDT_CRITICAL_SECTIONS)
#define RSWDT_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define RSWDT_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define RSWDT_CRITICAL_SECTION_ENTER()
#define RSWDT_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_rswdt_cr_reg_t;
typedef uint32_t hri_rswdt_mr_reg_t;
typedef uint32_t hri_rswdt_sr_reg_t;

static inline void hri_rswdt_write_CR_reg(const void *const hw, hri_rswdt_cr_reg_t data)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_CR = data;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_set_MR_WDFIEN_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR |= RSWDT_MR_WDFIEN;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rswdt_get_MR_WDFIEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp = (tmp & RSWDT_MR_WDFIEN) >> RSWDT_MR_WDFIEN_Pos;
	return (bool)tmp;
}

static inline void hri_rswdt_write_MR_WDFIEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RSWDT_CRITICAL_SECTION_ENTER();
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp &= ~RSWDT_MR_WDFIEN;
	tmp |= value << RSWDT_MR_WDFIEN_Pos;
	((Rswdt *)hw)->RSWDT_MR = tmp;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_clear_MR_WDFIEN_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR &= ~RSWDT_MR_WDFIEN;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_toggle_MR_WDFIEN_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR ^= RSWDT_MR_WDFIEN;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_set_MR_WDRSTEN_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR |= RSWDT_MR_WDRSTEN;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rswdt_get_MR_WDRSTEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp = (tmp & RSWDT_MR_WDRSTEN) >> RSWDT_MR_WDRSTEN_Pos;
	return (bool)tmp;
}

static inline void hri_rswdt_write_MR_WDRSTEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RSWDT_CRITICAL_SECTION_ENTER();
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp &= ~RSWDT_MR_WDRSTEN;
	tmp |= value << RSWDT_MR_WDRSTEN_Pos;
	((Rswdt *)hw)->RSWDT_MR = tmp;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_clear_MR_WDRSTEN_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR &= ~RSWDT_MR_WDRSTEN;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_toggle_MR_WDRSTEN_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR ^= RSWDT_MR_WDRSTEN;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_set_MR_WDDIS_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR |= RSWDT_MR_WDDIS;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rswdt_get_MR_WDDIS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp = (tmp & RSWDT_MR_WDDIS) >> RSWDT_MR_WDDIS_Pos;
	return (bool)tmp;
}

static inline void hri_rswdt_write_MR_WDDIS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RSWDT_CRITICAL_SECTION_ENTER();
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp &= ~RSWDT_MR_WDDIS;
	tmp |= value << RSWDT_MR_WDDIS_Pos;
	((Rswdt *)hw)->RSWDT_MR = tmp;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_clear_MR_WDDIS_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR &= ~RSWDT_MR_WDDIS;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_toggle_MR_WDDIS_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR ^= RSWDT_MR_WDDIS;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_set_MR_WDDBGHLT_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR |= RSWDT_MR_WDDBGHLT;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rswdt_get_MR_WDDBGHLT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp = (tmp & RSWDT_MR_WDDBGHLT) >> RSWDT_MR_WDDBGHLT_Pos;
	return (bool)tmp;
}

static inline void hri_rswdt_write_MR_WDDBGHLT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RSWDT_CRITICAL_SECTION_ENTER();
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp &= ~RSWDT_MR_WDDBGHLT;
	tmp |= value << RSWDT_MR_WDDBGHLT_Pos;
	((Rswdt *)hw)->RSWDT_MR = tmp;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_clear_MR_WDDBGHLT_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR &= ~RSWDT_MR_WDDBGHLT;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_toggle_MR_WDDBGHLT_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR ^= RSWDT_MR_WDDBGHLT;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_set_MR_WDIDLEHLT_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR |= RSWDT_MR_WDIDLEHLT;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rswdt_get_MR_WDIDLEHLT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp = (tmp & RSWDT_MR_WDIDLEHLT) >> RSWDT_MR_WDIDLEHLT_Pos;
	return (bool)tmp;
}

static inline void hri_rswdt_write_MR_WDIDLEHLT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RSWDT_CRITICAL_SECTION_ENTER();
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp &= ~RSWDT_MR_WDIDLEHLT;
	tmp |= value << RSWDT_MR_WDIDLEHLT_Pos;
	((Rswdt *)hw)->RSWDT_MR = tmp;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_clear_MR_WDIDLEHLT_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR &= ~RSWDT_MR_WDIDLEHLT;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_toggle_MR_WDIDLEHLT_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR ^= RSWDT_MR_WDIDLEHLT;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_set_MR_WDV_bf(const void *const hw, hri_rswdt_mr_reg_t mask)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR |= RSWDT_MR_WDV(mask);
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rswdt_mr_reg_t hri_rswdt_get_MR_WDV_bf(const void *const hw, hri_rswdt_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp = (tmp & RSWDT_MR_WDV(mask)) >> RSWDT_MR_WDV_Pos;
	return tmp;
}

static inline void hri_rswdt_write_MR_WDV_bf(const void *const hw, hri_rswdt_mr_reg_t data)
{
	uint32_t tmp;
	RSWDT_CRITICAL_SECTION_ENTER();
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp &= ~RSWDT_MR_WDV_Msk;
	tmp |= RSWDT_MR_WDV(data);
	((Rswdt *)hw)->RSWDT_MR = tmp;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_clear_MR_WDV_bf(const void *const hw, hri_rswdt_mr_reg_t mask)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR &= ~RSWDT_MR_WDV(mask);
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_toggle_MR_WDV_bf(const void *const hw, hri_rswdt_mr_reg_t mask)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR ^= RSWDT_MR_WDV(mask);
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rswdt_mr_reg_t hri_rswdt_read_MR_WDV_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp = (tmp & RSWDT_MR_WDV_Msk) >> RSWDT_MR_WDV_Pos;
	return tmp;
}

static inline void hri_rswdt_set_MR_ALLONES_bf(const void *const hw, hri_rswdt_mr_reg_t mask)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR |= RSWDT_MR_ALLONES(mask);
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rswdt_mr_reg_t hri_rswdt_get_MR_ALLONES_bf(const void *const hw, hri_rswdt_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp = (tmp & RSWDT_MR_ALLONES(mask)) >> RSWDT_MR_ALLONES_Pos;
	return tmp;
}

static inline void hri_rswdt_write_MR_ALLONES_bf(const void *const hw, hri_rswdt_mr_reg_t data)
{
	uint32_t tmp;
	RSWDT_CRITICAL_SECTION_ENTER();
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp &= ~RSWDT_MR_ALLONES_Msk;
	tmp |= RSWDT_MR_ALLONES(data);
	((Rswdt *)hw)->RSWDT_MR = tmp;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_clear_MR_ALLONES_bf(const void *const hw, hri_rswdt_mr_reg_t mask)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR &= ~RSWDT_MR_ALLONES(mask);
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_toggle_MR_ALLONES_bf(const void *const hw, hri_rswdt_mr_reg_t mask)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR ^= RSWDT_MR_ALLONES(mask);
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rswdt_mr_reg_t hri_rswdt_read_MR_ALLONES_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp = (tmp & RSWDT_MR_ALLONES_Msk) >> RSWDT_MR_ALLONES_Pos;
	return tmp;
}

static inline void hri_rswdt_set_MR_reg(const void *const hw, hri_rswdt_mr_reg_t mask)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR |= mask;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rswdt_mr_reg_t hri_rswdt_get_MR_reg(const void *const hw, hri_rswdt_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp &= mask;
	return tmp;
}

static inline void hri_rswdt_write_MR_reg(const void *const hw, hri_rswdt_mr_reg_t data)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR = data;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_clear_MR_reg(const void *const hw, hri_rswdt_mr_reg_t mask)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR &= ~mask;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_toggle_MR_reg(const void *const hw, hri_rswdt_mr_reg_t mask)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR ^= mask;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rswdt_mr_reg_t hri_rswdt_read_MR_reg(const void *const hw)
{
	return ((Rswdt *)hw)->RSWDT_MR;
}

static inline bool hri_rswdt_get_SR_WDUNF_bit(const void *const hw)
{
	return (((Rswdt *)hw)->RSWDT_SR & RSWDT_SR_WDUNF) > 0;
}

static inline hri_rswdt_sr_reg_t hri_rswdt_get_SR_reg(const void *const hw, hri_rswdt_sr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rswdt *)hw)->RSWDT_SR;
	tmp &= mask;
	return tmp;
}

static inline hri_rswdt_sr_reg_t hri_rswdt_read_SR_reg(const void *const hw)
{
	return ((Rswdt *)hw)->RSWDT_SR;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_RSWDT_S70_H_INCLUDED */
#endif /* _SAMS70_RSWDT_COMPONENT_ */
