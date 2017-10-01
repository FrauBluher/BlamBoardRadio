/**
 * \file
 *
 * \brief SAM WDT
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

#ifdef _SAMS70_WDT_COMPONENT_
#ifndef _HRI_WDT_S70_H_INCLUDED_
#define _HRI_WDT_S70_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_WDT_CRITICAL_SECTIONS)
#define WDT_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define WDT_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define WDT_CRITICAL_SECTION_ENTER()
#define WDT_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_wdt_cr_reg_t;
typedef uint32_t hri_wdt_mr_reg_t;
typedef uint32_t hri_wdt_sr_reg_t;

static inline void hri_wdt_write_CR_reg(const void *const hw, hri_wdt_cr_reg_t data)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->WDT_CR = data;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_set_MR_WDFIEN_bit(const void *const hw)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->WDT_MR |= WDT_MR_WDFIEN;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_wdt_get_MR_WDFIEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Wdt *)hw)->WDT_MR;
	tmp = (tmp & WDT_MR_WDFIEN) >> WDT_MR_WDFIEN_Pos;
	return (bool)tmp;
}

static inline void hri_wdt_write_MR_WDFIEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	WDT_CRITICAL_SECTION_ENTER();
	tmp = ((Wdt *)hw)->WDT_MR;
	tmp &= ~WDT_MR_WDFIEN;
	tmp |= value << WDT_MR_WDFIEN_Pos;
	((Wdt *)hw)->WDT_MR = tmp;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_clear_MR_WDFIEN_bit(const void *const hw)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->WDT_MR &= ~WDT_MR_WDFIEN;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_toggle_MR_WDFIEN_bit(const void *const hw)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->WDT_MR ^= WDT_MR_WDFIEN;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_set_MR_WDRSTEN_bit(const void *const hw)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->WDT_MR |= WDT_MR_WDRSTEN;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_wdt_get_MR_WDRSTEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Wdt *)hw)->WDT_MR;
	tmp = (tmp & WDT_MR_WDRSTEN) >> WDT_MR_WDRSTEN_Pos;
	return (bool)tmp;
}

static inline void hri_wdt_write_MR_WDRSTEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	WDT_CRITICAL_SECTION_ENTER();
	tmp = ((Wdt *)hw)->WDT_MR;
	tmp &= ~WDT_MR_WDRSTEN;
	tmp |= value << WDT_MR_WDRSTEN_Pos;
	((Wdt *)hw)->WDT_MR = tmp;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_clear_MR_WDRSTEN_bit(const void *const hw)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->WDT_MR &= ~WDT_MR_WDRSTEN;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_toggle_MR_WDRSTEN_bit(const void *const hw)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->WDT_MR ^= WDT_MR_WDRSTEN;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_set_MR_WDDIS_bit(const void *const hw)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->WDT_MR |= WDT_MR_WDDIS;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_wdt_get_MR_WDDIS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Wdt *)hw)->WDT_MR;
	tmp = (tmp & WDT_MR_WDDIS) >> WDT_MR_WDDIS_Pos;
	return (bool)tmp;
}

static inline void hri_wdt_write_MR_WDDIS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	WDT_CRITICAL_SECTION_ENTER();
	tmp = ((Wdt *)hw)->WDT_MR;
	tmp &= ~WDT_MR_WDDIS;
	tmp |= value << WDT_MR_WDDIS_Pos;
	((Wdt *)hw)->WDT_MR = tmp;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_clear_MR_WDDIS_bit(const void *const hw)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->WDT_MR &= ~WDT_MR_WDDIS;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_toggle_MR_WDDIS_bit(const void *const hw)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->WDT_MR ^= WDT_MR_WDDIS;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_set_MR_WDDBGHLT_bit(const void *const hw)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->WDT_MR |= WDT_MR_WDDBGHLT;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_wdt_get_MR_WDDBGHLT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Wdt *)hw)->WDT_MR;
	tmp = (tmp & WDT_MR_WDDBGHLT) >> WDT_MR_WDDBGHLT_Pos;
	return (bool)tmp;
}

static inline void hri_wdt_write_MR_WDDBGHLT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	WDT_CRITICAL_SECTION_ENTER();
	tmp = ((Wdt *)hw)->WDT_MR;
	tmp &= ~WDT_MR_WDDBGHLT;
	tmp |= value << WDT_MR_WDDBGHLT_Pos;
	((Wdt *)hw)->WDT_MR = tmp;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_clear_MR_WDDBGHLT_bit(const void *const hw)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->WDT_MR &= ~WDT_MR_WDDBGHLT;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_toggle_MR_WDDBGHLT_bit(const void *const hw)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->WDT_MR ^= WDT_MR_WDDBGHLT;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_set_MR_WDIDLEHLT_bit(const void *const hw)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->WDT_MR |= WDT_MR_WDIDLEHLT;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_wdt_get_MR_WDIDLEHLT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Wdt *)hw)->WDT_MR;
	tmp = (tmp & WDT_MR_WDIDLEHLT) >> WDT_MR_WDIDLEHLT_Pos;
	return (bool)tmp;
}

static inline void hri_wdt_write_MR_WDIDLEHLT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	WDT_CRITICAL_SECTION_ENTER();
	tmp = ((Wdt *)hw)->WDT_MR;
	tmp &= ~WDT_MR_WDIDLEHLT;
	tmp |= value << WDT_MR_WDIDLEHLT_Pos;
	((Wdt *)hw)->WDT_MR = tmp;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_clear_MR_WDIDLEHLT_bit(const void *const hw)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->WDT_MR &= ~WDT_MR_WDIDLEHLT;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_toggle_MR_WDIDLEHLT_bit(const void *const hw)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->WDT_MR ^= WDT_MR_WDIDLEHLT;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_set_MR_WDV_bf(const void *const hw, hri_wdt_mr_reg_t mask)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->WDT_MR |= WDT_MR_WDV(mask);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_wdt_mr_reg_t hri_wdt_get_MR_WDV_bf(const void *const hw, hri_wdt_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Wdt *)hw)->WDT_MR;
	tmp = (tmp & WDT_MR_WDV(mask)) >> WDT_MR_WDV_Pos;
	return tmp;
}

static inline void hri_wdt_write_MR_WDV_bf(const void *const hw, hri_wdt_mr_reg_t data)
{
	uint32_t tmp;
	WDT_CRITICAL_SECTION_ENTER();
	tmp = ((Wdt *)hw)->WDT_MR;
	tmp &= ~WDT_MR_WDV_Msk;
	tmp |= WDT_MR_WDV(data);
	((Wdt *)hw)->WDT_MR = tmp;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_clear_MR_WDV_bf(const void *const hw, hri_wdt_mr_reg_t mask)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->WDT_MR &= ~WDT_MR_WDV(mask);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_toggle_MR_WDV_bf(const void *const hw, hri_wdt_mr_reg_t mask)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->WDT_MR ^= WDT_MR_WDV(mask);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_wdt_mr_reg_t hri_wdt_read_MR_WDV_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Wdt *)hw)->WDT_MR;
	tmp = (tmp & WDT_MR_WDV_Msk) >> WDT_MR_WDV_Pos;
	return tmp;
}

static inline void hri_wdt_set_MR_WDD_bf(const void *const hw, hri_wdt_mr_reg_t mask)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->WDT_MR |= WDT_MR_WDD(mask);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_wdt_mr_reg_t hri_wdt_get_MR_WDD_bf(const void *const hw, hri_wdt_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Wdt *)hw)->WDT_MR;
	tmp = (tmp & WDT_MR_WDD(mask)) >> WDT_MR_WDD_Pos;
	return tmp;
}

static inline void hri_wdt_write_MR_WDD_bf(const void *const hw, hri_wdt_mr_reg_t data)
{
	uint32_t tmp;
	WDT_CRITICAL_SECTION_ENTER();
	tmp = ((Wdt *)hw)->WDT_MR;
	tmp &= ~WDT_MR_WDD_Msk;
	tmp |= WDT_MR_WDD(data);
	((Wdt *)hw)->WDT_MR = tmp;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_clear_MR_WDD_bf(const void *const hw, hri_wdt_mr_reg_t mask)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->WDT_MR &= ~WDT_MR_WDD(mask);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_toggle_MR_WDD_bf(const void *const hw, hri_wdt_mr_reg_t mask)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->WDT_MR ^= WDT_MR_WDD(mask);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_wdt_mr_reg_t hri_wdt_read_MR_WDD_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Wdt *)hw)->WDT_MR;
	tmp = (tmp & WDT_MR_WDD_Msk) >> WDT_MR_WDD_Pos;
	return tmp;
}

static inline void hri_wdt_set_MR_reg(const void *const hw, hri_wdt_mr_reg_t mask)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->WDT_MR |= mask;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_wdt_mr_reg_t hri_wdt_get_MR_reg(const void *const hw, hri_wdt_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Wdt *)hw)->WDT_MR;
	tmp &= mask;
	return tmp;
}

static inline void hri_wdt_write_MR_reg(const void *const hw, hri_wdt_mr_reg_t data)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->WDT_MR = data;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_clear_MR_reg(const void *const hw, hri_wdt_mr_reg_t mask)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->WDT_MR &= ~mask;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_toggle_MR_reg(const void *const hw, hri_wdt_mr_reg_t mask)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->WDT_MR ^= mask;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_wdt_mr_reg_t hri_wdt_read_MR_reg(const void *const hw)
{
	return ((Wdt *)hw)->WDT_MR;
}

static inline bool hri_wdt_get_SR_WDUNF_bit(const void *const hw)
{
	return (((Wdt *)hw)->WDT_SR & WDT_SR_WDUNF) > 0;
}

static inline bool hri_wdt_get_SR_WDERR_bit(const void *const hw)
{
	return (((Wdt *)hw)->WDT_SR & WDT_SR_WDERR) > 0;
}

static inline hri_wdt_sr_reg_t hri_wdt_get_SR_reg(const void *const hw, hri_wdt_sr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Wdt *)hw)->WDT_SR;
	tmp &= mask;
	return tmp;
}

static inline hri_wdt_sr_reg_t hri_wdt_read_SR_reg(const void *const hw)
{
	return ((Wdt *)hw)->WDT_SR;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_WDT_S70_H_INCLUDED */
#endif /* _SAMS70_WDT_COMPONENT_ */
