/**
 * \file
 *
 * \brief SAM UTMI
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

#ifdef _SAMS70_UTMI_COMPONENT_
#ifndef _HRI_UTMI_S70_H_INCLUDED_
#define _HRI_UTMI_S70_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_UTMI_CRITICAL_SECTIONS)
#define UTMI_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define UTMI_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define UTMI_CRITICAL_SECTION_ENTER()
#define UTMI_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_utmi_cktrim_reg_t;
typedef uint32_t hri_utmi_ohciicr_reg_t;

static inline void hri_utmi_set_OHCIICR_RES0_bit(const void *const hw)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR |= UTMI_OHCIICR_RES0;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_utmi_get_OHCIICR_RES0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Utmi *)hw)->UTMI_OHCIICR;
	tmp = (tmp & UTMI_OHCIICR_RES0) >> UTMI_OHCIICR_RES0_Pos;
	return (bool)tmp;
}

static inline void hri_utmi_write_OHCIICR_RES0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	UTMI_CRITICAL_SECTION_ENTER();
	tmp = ((Utmi *)hw)->UTMI_OHCIICR;
	tmp &= ~UTMI_OHCIICR_RES0;
	tmp |= value << UTMI_OHCIICR_RES0_Pos;
	((Utmi *)hw)->UTMI_OHCIICR = tmp;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_clear_OHCIICR_RES0_bit(const void *const hw)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR &= ~UTMI_OHCIICR_RES0;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_toggle_OHCIICR_RES0_bit(const void *const hw)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR ^= UTMI_OHCIICR_RES0;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_set_OHCIICR_ARIE_bit(const void *const hw)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR |= UTMI_OHCIICR_ARIE;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_utmi_get_OHCIICR_ARIE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Utmi *)hw)->UTMI_OHCIICR;
	tmp = (tmp & UTMI_OHCIICR_ARIE) >> UTMI_OHCIICR_ARIE_Pos;
	return (bool)tmp;
}

static inline void hri_utmi_write_OHCIICR_ARIE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	UTMI_CRITICAL_SECTION_ENTER();
	tmp = ((Utmi *)hw)->UTMI_OHCIICR;
	tmp &= ~UTMI_OHCIICR_ARIE;
	tmp |= value << UTMI_OHCIICR_ARIE_Pos;
	((Utmi *)hw)->UTMI_OHCIICR = tmp;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_clear_OHCIICR_ARIE_bit(const void *const hw)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR &= ~UTMI_OHCIICR_ARIE;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_toggle_OHCIICR_ARIE_bit(const void *const hw)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR ^= UTMI_OHCIICR_ARIE;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_set_OHCIICR_APPSTART_bit(const void *const hw)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR |= UTMI_OHCIICR_APPSTART;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_utmi_get_OHCIICR_APPSTART_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Utmi *)hw)->UTMI_OHCIICR;
	tmp = (tmp & UTMI_OHCIICR_APPSTART) >> UTMI_OHCIICR_APPSTART_Pos;
	return (bool)tmp;
}

static inline void hri_utmi_write_OHCIICR_APPSTART_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	UTMI_CRITICAL_SECTION_ENTER();
	tmp = ((Utmi *)hw)->UTMI_OHCIICR;
	tmp &= ~UTMI_OHCIICR_APPSTART;
	tmp |= value << UTMI_OHCIICR_APPSTART_Pos;
	((Utmi *)hw)->UTMI_OHCIICR = tmp;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_clear_OHCIICR_APPSTART_bit(const void *const hw)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR &= ~UTMI_OHCIICR_APPSTART;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_toggle_OHCIICR_APPSTART_bit(const void *const hw)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR ^= UTMI_OHCIICR_APPSTART;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_set_OHCIICR_UDPPUDIS_bit(const void *const hw)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR |= UTMI_OHCIICR_UDPPUDIS;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_utmi_get_OHCIICR_UDPPUDIS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Utmi *)hw)->UTMI_OHCIICR;
	tmp = (tmp & UTMI_OHCIICR_UDPPUDIS) >> UTMI_OHCIICR_UDPPUDIS_Pos;
	return (bool)tmp;
}

static inline void hri_utmi_write_OHCIICR_UDPPUDIS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	UTMI_CRITICAL_SECTION_ENTER();
	tmp = ((Utmi *)hw)->UTMI_OHCIICR;
	tmp &= ~UTMI_OHCIICR_UDPPUDIS;
	tmp |= value << UTMI_OHCIICR_UDPPUDIS_Pos;
	((Utmi *)hw)->UTMI_OHCIICR = tmp;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_clear_OHCIICR_UDPPUDIS_bit(const void *const hw)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR &= ~UTMI_OHCIICR_UDPPUDIS;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_toggle_OHCIICR_UDPPUDIS_bit(const void *const hw)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR ^= UTMI_OHCIICR_UDPPUDIS;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_set_OHCIICR_reg(const void *const hw, hri_utmi_ohciicr_reg_t mask)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR |= mask;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline hri_utmi_ohciicr_reg_t hri_utmi_get_OHCIICR_reg(const void *const hw, hri_utmi_ohciicr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Utmi *)hw)->UTMI_OHCIICR;
	tmp &= mask;
	return tmp;
}

static inline void hri_utmi_write_OHCIICR_reg(const void *const hw, hri_utmi_ohciicr_reg_t data)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR = data;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_clear_OHCIICR_reg(const void *const hw, hri_utmi_ohciicr_reg_t mask)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR &= ~mask;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_toggle_OHCIICR_reg(const void *const hw, hri_utmi_ohciicr_reg_t mask)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR ^= mask;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline hri_utmi_ohciicr_reg_t hri_utmi_read_OHCIICR_reg(const void *const hw)
{
	return ((Utmi *)hw)->UTMI_OHCIICR;
}

static inline void hri_utmi_set_CKTRIM_FREQ_bf(const void *const hw, hri_utmi_cktrim_reg_t mask)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_CKTRIM |= UTMI_CKTRIM_FREQ(mask);
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline hri_utmi_cktrim_reg_t hri_utmi_get_CKTRIM_FREQ_bf(const void *const hw, hri_utmi_cktrim_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Utmi *)hw)->UTMI_CKTRIM;
	tmp = (tmp & UTMI_CKTRIM_FREQ(mask)) >> UTMI_CKTRIM_FREQ_Pos;
	return tmp;
}

static inline void hri_utmi_write_CKTRIM_FREQ_bf(const void *const hw, hri_utmi_cktrim_reg_t data)
{
	uint32_t tmp;
	UTMI_CRITICAL_SECTION_ENTER();
	tmp = ((Utmi *)hw)->UTMI_CKTRIM;
	tmp &= ~UTMI_CKTRIM_FREQ_Msk;
	tmp |= UTMI_CKTRIM_FREQ(data);
	((Utmi *)hw)->UTMI_CKTRIM = tmp;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_clear_CKTRIM_FREQ_bf(const void *const hw, hri_utmi_cktrim_reg_t mask)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_CKTRIM &= ~UTMI_CKTRIM_FREQ(mask);
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_toggle_CKTRIM_FREQ_bf(const void *const hw, hri_utmi_cktrim_reg_t mask)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_CKTRIM ^= UTMI_CKTRIM_FREQ(mask);
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline hri_utmi_cktrim_reg_t hri_utmi_read_CKTRIM_FREQ_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Utmi *)hw)->UTMI_CKTRIM;
	tmp = (tmp & UTMI_CKTRIM_FREQ_Msk) >> UTMI_CKTRIM_FREQ_Pos;
	return tmp;
}

static inline void hri_utmi_set_CKTRIM_reg(const void *const hw, hri_utmi_cktrim_reg_t mask)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_CKTRIM |= mask;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline hri_utmi_cktrim_reg_t hri_utmi_get_CKTRIM_reg(const void *const hw, hri_utmi_cktrim_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Utmi *)hw)->UTMI_CKTRIM;
	tmp &= mask;
	return tmp;
}

static inline void hri_utmi_write_CKTRIM_reg(const void *const hw, hri_utmi_cktrim_reg_t data)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_CKTRIM = data;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_clear_CKTRIM_reg(const void *const hw, hri_utmi_cktrim_reg_t mask)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_CKTRIM &= ~mask;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_toggle_CKTRIM_reg(const void *const hw, hri_utmi_cktrim_reg_t mask)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_CKTRIM ^= mask;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline hri_utmi_cktrim_reg_t hri_utmi_read_CKTRIM_reg(const void *const hw)
{
	return ((Utmi *)hw)->UTMI_CKTRIM;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_UTMI_S70_H_INCLUDED */
#endif /* _SAMS70_UTMI_COMPONENT_ */
