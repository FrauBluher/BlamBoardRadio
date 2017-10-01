/**
 * \file
 *
 * \brief SAM RSTC
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

#ifdef _SAMS70_RSTC_COMPONENT_
#ifndef _HRI_RSTC_S70_H_INCLUDED_
#define _HRI_RSTC_S70_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_RSTC_CRITICAL_SECTIONS)
#define RSTC_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define RSTC_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define RSTC_CRITICAL_SECTION_ENTER()
#define RSTC_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_rstc_cr_reg_t;
typedef uint32_t hri_rstc_mr_reg_t;
typedef uint32_t hri_rstc_sr_reg_t;

static inline void hri_rstc_write_CR_reg(const void *const hw, hri_rstc_cr_reg_t data)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_CR = data;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rstc_set_MR_URSTEN_bit(const void *const hw)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR |= RSTC_MR_URSTEN;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rstc_get_MR_URSTEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rstc *)hw)->RSTC_MR;
	tmp = (tmp & RSTC_MR_URSTEN) >> RSTC_MR_URSTEN_Pos;
	return (bool)tmp;
}

static inline void hri_rstc_write_MR_URSTEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RSTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rstc *)hw)->RSTC_MR;
	tmp &= ~RSTC_MR_URSTEN;
	tmp |= value << RSTC_MR_URSTEN_Pos;
	((Rstc *)hw)->RSTC_MR = tmp;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rstc_clear_MR_URSTEN_bit(const void *const hw)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR &= ~RSTC_MR_URSTEN;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rstc_toggle_MR_URSTEN_bit(const void *const hw)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR ^= RSTC_MR_URSTEN;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rstc_set_MR_URSTIEN_bit(const void *const hw)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR |= RSTC_MR_URSTIEN;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rstc_get_MR_URSTIEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rstc *)hw)->RSTC_MR;
	tmp = (tmp & RSTC_MR_URSTIEN) >> RSTC_MR_URSTIEN_Pos;
	return (bool)tmp;
}

static inline void hri_rstc_write_MR_URSTIEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RSTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rstc *)hw)->RSTC_MR;
	tmp &= ~RSTC_MR_URSTIEN;
	tmp |= value << RSTC_MR_URSTIEN_Pos;
	((Rstc *)hw)->RSTC_MR = tmp;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rstc_clear_MR_URSTIEN_bit(const void *const hw)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR &= ~RSTC_MR_URSTIEN;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rstc_toggle_MR_URSTIEN_bit(const void *const hw)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR ^= RSTC_MR_URSTIEN;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rstc_set_MR_ERSTL_bf(const void *const hw, hri_rstc_mr_reg_t mask)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR |= RSTC_MR_ERSTL(mask);
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rstc_mr_reg_t hri_rstc_get_MR_ERSTL_bf(const void *const hw, hri_rstc_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rstc *)hw)->RSTC_MR;
	tmp = (tmp & RSTC_MR_ERSTL(mask)) >> RSTC_MR_ERSTL_Pos;
	return tmp;
}

static inline void hri_rstc_write_MR_ERSTL_bf(const void *const hw, hri_rstc_mr_reg_t data)
{
	uint32_t tmp;
	RSTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rstc *)hw)->RSTC_MR;
	tmp &= ~RSTC_MR_ERSTL_Msk;
	tmp |= RSTC_MR_ERSTL(data);
	((Rstc *)hw)->RSTC_MR = tmp;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rstc_clear_MR_ERSTL_bf(const void *const hw, hri_rstc_mr_reg_t mask)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR &= ~RSTC_MR_ERSTL(mask);
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rstc_toggle_MR_ERSTL_bf(const void *const hw, hri_rstc_mr_reg_t mask)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR ^= RSTC_MR_ERSTL(mask);
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rstc_mr_reg_t hri_rstc_read_MR_ERSTL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rstc *)hw)->RSTC_MR;
	tmp = (tmp & RSTC_MR_ERSTL_Msk) >> RSTC_MR_ERSTL_Pos;
	return tmp;
}

static inline void hri_rstc_set_MR_KEY_bf(const void *const hw, hri_rstc_mr_reg_t mask)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR |= RSTC_MR_KEY(mask);
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rstc_mr_reg_t hri_rstc_get_MR_KEY_bf(const void *const hw, hri_rstc_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rstc *)hw)->RSTC_MR;
	tmp = (tmp & RSTC_MR_KEY(mask)) >> RSTC_MR_KEY_Pos;
	return tmp;
}

static inline void hri_rstc_write_MR_KEY_bf(const void *const hw, hri_rstc_mr_reg_t data)
{
	uint32_t tmp;
	RSTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rstc *)hw)->RSTC_MR;
	tmp &= ~RSTC_MR_KEY_Msk;
	tmp |= RSTC_MR_KEY(data);
	((Rstc *)hw)->RSTC_MR = tmp;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rstc_clear_MR_KEY_bf(const void *const hw, hri_rstc_mr_reg_t mask)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR &= ~RSTC_MR_KEY(mask);
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rstc_toggle_MR_KEY_bf(const void *const hw, hri_rstc_mr_reg_t mask)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR ^= RSTC_MR_KEY(mask);
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rstc_mr_reg_t hri_rstc_read_MR_KEY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rstc *)hw)->RSTC_MR;
	tmp = (tmp & RSTC_MR_KEY_Msk) >> RSTC_MR_KEY_Pos;
	return tmp;
}

static inline void hri_rstc_set_MR_reg(const void *const hw, hri_rstc_mr_reg_t mask)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR |= mask;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rstc_mr_reg_t hri_rstc_get_MR_reg(const void *const hw, hri_rstc_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rstc *)hw)->RSTC_MR;
	tmp &= mask;
	return tmp;
}

static inline void hri_rstc_write_MR_reg(const void *const hw, hri_rstc_mr_reg_t data)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR = data;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rstc_clear_MR_reg(const void *const hw, hri_rstc_mr_reg_t mask)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR &= ~mask;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rstc_toggle_MR_reg(const void *const hw, hri_rstc_mr_reg_t mask)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR ^= mask;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rstc_mr_reg_t hri_rstc_read_MR_reg(const void *const hw)
{
	return ((Rstc *)hw)->RSTC_MR;
}

static inline bool hri_rstc_get_SR_URSTS_bit(const void *const hw)
{
	return (((Rstc *)hw)->RSTC_SR & RSTC_SR_URSTS) > 0;
}

static inline bool hri_rstc_get_SR_NRSTL_bit(const void *const hw)
{
	return (((Rstc *)hw)->RSTC_SR & RSTC_SR_NRSTL) > 0;
}

static inline bool hri_rstc_get_SR_SRCMP_bit(const void *const hw)
{
	return (((Rstc *)hw)->RSTC_SR & RSTC_SR_SRCMP) > 0;
}

static inline hri_rstc_sr_reg_t hri_rstc_get_SR_RSTTYP_bf(const void *const hw, hri_rstc_sr_reg_t mask)
{
	return (((Rstc *)hw)->RSTC_SR & RSTC_SR_RSTTYP(mask)) >> RSTC_SR_RSTTYP_Pos;
}

static inline hri_rstc_sr_reg_t hri_rstc_read_SR_RSTTYP_bf(const void *const hw)
{
	return (((Rstc *)hw)->RSTC_SR & RSTC_SR_RSTTYP_Msk) >> RSTC_SR_RSTTYP_Pos;
}

static inline hri_rstc_sr_reg_t hri_rstc_get_SR_reg(const void *const hw, hri_rstc_sr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rstc *)hw)->RSTC_SR;
	tmp &= mask;
	return tmp;
}

static inline hri_rstc_sr_reg_t hri_rstc_read_SR_reg(const void *const hw)
{
	return ((Rstc *)hw)->RSTC_SR;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_RSTC_S70_H_INCLUDED */
#endif /* _SAMS70_RSTC_COMPONENT_ */
