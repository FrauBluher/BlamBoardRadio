/**
 * \file
 *
 * \brief SAM SysTick
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

#ifdef _SAMS70_SysTick_COMPONENT_
#ifndef _HRI_SysTick_S70_H_INCLUDED_
#define _HRI_SysTick_S70_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_SysTick_CRITICAL_SECTIONS)
#define SysTick_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define SysTick_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define SysTick_CRITICAL_SECTION_ENTER()
#define SysTick_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_systick_calib_reg_t;
typedef uint32_t hri_systick_csr_reg_t;
typedef uint32_t hri_systick_cvr_reg_t;
typedef uint32_t hri_systick_rvr_reg_t;

static inline void hri_systick_set_CSR_ENABLE_bit(const void *const hw)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CSR |= SysTick_CSR_ENABLE;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_systick_get_CSR_ENABLE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Systick *)hw)->CSR;
	tmp = (tmp & SysTick_CSR_ENABLE) >> 0;
	return (bool)tmp;
}

static inline void hri_systick_write_CSR_ENABLE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SysTick_CRITICAL_SECTION_ENTER();
	tmp = ((Systick *)hw)->CSR;
	tmp &= ~SysTick_CSR_ENABLE;
	tmp |= value << 0;
	((Systick *)hw)->CSR = tmp;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_clear_CSR_ENABLE_bit(const void *const hw)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CSR &= ~SysTick_CSR_ENABLE;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_toggle_CSR_ENABLE_bit(const void *const hw)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CSR ^= SysTick_CSR_ENABLE;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_set_CSR_TICKINT_bit(const void *const hw)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CSR |= SysTick_CSR_TICKINT;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_systick_get_CSR_TICKINT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Systick *)hw)->CSR;
	tmp = (tmp & SysTick_CSR_TICKINT) >> 1;
	return (bool)tmp;
}

static inline void hri_systick_write_CSR_TICKINT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SysTick_CRITICAL_SECTION_ENTER();
	tmp = ((Systick *)hw)->CSR;
	tmp &= ~SysTick_CSR_TICKINT;
	tmp |= value << 1;
	((Systick *)hw)->CSR = tmp;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_clear_CSR_TICKINT_bit(const void *const hw)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CSR &= ~SysTick_CSR_TICKINT;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_toggle_CSR_TICKINT_bit(const void *const hw)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CSR ^= SysTick_CSR_TICKINT;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_set_CSR_CLKSOURCE_bit(const void *const hw)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CSR |= SysTick_CSR_CLKSOURCE;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_systick_get_CSR_CLKSOURCE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Systick *)hw)->CSR;
	tmp = (tmp & SysTick_CSR_CLKSOURCE) >> 2;
	return (bool)tmp;
}

static inline void hri_systick_write_CSR_CLKSOURCE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SysTick_CRITICAL_SECTION_ENTER();
	tmp = ((Systick *)hw)->CSR;
	tmp &= ~SysTick_CSR_CLKSOURCE;
	tmp |= value << 2;
	((Systick *)hw)->CSR = tmp;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_clear_CSR_CLKSOURCE_bit(const void *const hw)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CSR &= ~SysTick_CSR_CLKSOURCE;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_toggle_CSR_CLKSOURCE_bit(const void *const hw)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CSR ^= SysTick_CSR_CLKSOURCE;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_set_CSR_COUNTFLAG_bit(const void *const hw)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CSR |= SysTick_CSR_COUNTFLAG;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_systick_get_CSR_COUNTFLAG_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Systick *)hw)->CSR;
	tmp = (tmp & SysTick_CSR_COUNTFLAG) >> 16;
	return (bool)tmp;
}

static inline void hri_systick_write_CSR_COUNTFLAG_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SysTick_CRITICAL_SECTION_ENTER();
	tmp = ((Systick *)hw)->CSR;
	tmp &= ~SysTick_CSR_COUNTFLAG;
	tmp |= value << 16;
	((Systick *)hw)->CSR = tmp;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_clear_CSR_COUNTFLAG_bit(const void *const hw)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CSR &= ~SysTick_CSR_COUNTFLAG;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_toggle_CSR_COUNTFLAG_bit(const void *const hw)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CSR ^= SysTick_CSR_COUNTFLAG;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_set_CSR_reg(const void *const hw, hri_systick_csr_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CSR |= mask;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline hri_systick_csr_reg_t hri_systick_get_CSR_reg(const void *const hw, hri_systick_csr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Systick *)hw)->CSR;
	tmp &= mask;
	return tmp;
}

static inline void hri_systick_write_CSR_reg(const void *const hw, hri_systick_csr_reg_t data)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CSR = data;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_clear_CSR_reg(const void *const hw, hri_systick_csr_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CSR &= ~mask;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_toggle_CSR_reg(const void *const hw, hri_systick_csr_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CSR ^= mask;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline hri_systick_csr_reg_t hri_systick_read_CSR_reg(const void *const hw)
{
	return ((Systick *)hw)->CSR;
}

static inline void hri_systick_set_RVR_RELOAD_bf(const void *const hw, hri_systick_rvr_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->RVR |= SysTick_RVR_RELOAD(mask);
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline hri_systick_rvr_reg_t hri_systick_get_RVR_RELOAD_bf(const void *const hw, hri_systick_rvr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Systick *)hw)->RVR;
	tmp = (tmp & SysTick_RVR_RELOAD(mask)) >> 0;
	return tmp;
}

static inline void hri_systick_write_RVR_RELOAD_bf(const void *const hw, hri_systick_rvr_reg_t data)
{
	uint32_t tmp;
	SysTick_CRITICAL_SECTION_ENTER();
	tmp = ((Systick *)hw)->RVR;
	tmp &= ~SysTick_RVR_RELOAD_Msk;
	tmp |= SysTick_RVR_RELOAD(data);
	((Systick *)hw)->RVR = tmp;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_clear_RVR_RELOAD_bf(const void *const hw, hri_systick_rvr_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->RVR &= ~SysTick_RVR_RELOAD(mask);
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_toggle_RVR_RELOAD_bf(const void *const hw, hri_systick_rvr_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->RVR ^= SysTick_RVR_RELOAD(mask);
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline hri_systick_rvr_reg_t hri_systick_read_RVR_RELOAD_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Systick *)hw)->RVR;
	tmp = (tmp & SysTick_RVR_RELOAD_Msk) >> 0;
	return tmp;
}

static inline void hri_systick_set_RVR_reg(const void *const hw, hri_systick_rvr_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->RVR |= mask;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline hri_systick_rvr_reg_t hri_systick_get_RVR_reg(const void *const hw, hri_systick_rvr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Systick *)hw)->RVR;
	tmp &= mask;
	return tmp;
}

static inline void hri_systick_write_RVR_reg(const void *const hw, hri_systick_rvr_reg_t data)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->RVR = data;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_clear_RVR_reg(const void *const hw, hri_systick_rvr_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->RVR &= ~mask;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_toggle_RVR_reg(const void *const hw, hri_systick_rvr_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->RVR ^= mask;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline hri_systick_rvr_reg_t hri_systick_read_RVR_reg(const void *const hw)
{
	return ((Systick *)hw)->RVR;
}

static inline void hri_systick_set_CVR_CURRENT_bf(const void *const hw, hri_systick_cvr_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CVR |= SysTick_CVR_CURRENT(mask);
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline hri_systick_cvr_reg_t hri_systick_get_CVR_CURRENT_bf(const void *const hw, hri_systick_cvr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Systick *)hw)->CVR;
	tmp = (tmp & SysTick_CVR_CURRENT(mask)) >> 0;
	return tmp;
}

static inline void hri_systick_write_CVR_CURRENT_bf(const void *const hw, hri_systick_cvr_reg_t data)
{
	uint32_t tmp;
	SysTick_CRITICAL_SECTION_ENTER();
	tmp = ((Systick *)hw)->CVR;
	tmp &= ~SysTick_CVR_CURRENT_Msk;
	tmp |= SysTick_CVR_CURRENT(data);
	((Systick *)hw)->CVR = tmp;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_clear_CVR_CURRENT_bf(const void *const hw, hri_systick_cvr_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CVR &= ~SysTick_CVR_CURRENT(mask);
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_toggle_CVR_CURRENT_bf(const void *const hw, hri_systick_cvr_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CVR ^= SysTick_CVR_CURRENT(mask);
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline hri_systick_cvr_reg_t hri_systick_read_CVR_CURRENT_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Systick *)hw)->CVR;
	tmp = (tmp & SysTick_CVR_CURRENT_Msk) >> 0;
	return tmp;
}

static inline void hri_systick_set_CVR_reg(const void *const hw, hri_systick_cvr_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CVR |= mask;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline hri_systick_cvr_reg_t hri_systick_get_CVR_reg(const void *const hw, hri_systick_cvr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Systick *)hw)->CVR;
	tmp &= mask;
	return tmp;
}

static inline void hri_systick_write_CVR_reg(const void *const hw, hri_systick_cvr_reg_t data)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CVR = data;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_clear_CVR_reg(const void *const hw, hri_systick_cvr_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CVR &= ~mask;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_toggle_CVR_reg(const void *const hw, hri_systick_cvr_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CVR ^= mask;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline hri_systick_cvr_reg_t hri_systick_read_CVR_reg(const void *const hw)
{
	return ((Systick *)hw)->CVR;
}

static inline void hri_systick_set_CALIB_SKEW_bit(const void *const hw)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CALIB |= SysTick_CALIB_SKEW;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_systick_get_CALIB_SKEW_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Systick *)hw)->CALIB;
	tmp = (tmp & SysTick_CALIB_SKEW) >> 30;
	return (bool)tmp;
}

static inline void hri_systick_write_CALIB_SKEW_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SysTick_CRITICAL_SECTION_ENTER();
	tmp = ((Systick *)hw)->CALIB;
	tmp &= ~SysTick_CALIB_SKEW;
	tmp |= value << 30;
	((Systick *)hw)->CALIB = tmp;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_clear_CALIB_SKEW_bit(const void *const hw)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CALIB &= ~SysTick_CALIB_SKEW;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_toggle_CALIB_SKEW_bit(const void *const hw)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CALIB ^= SysTick_CALIB_SKEW;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_set_CALIB_NOREF_bit(const void *const hw)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CALIB |= SysTick_CALIB_NOREF;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_systick_get_CALIB_NOREF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Systick *)hw)->CALIB;
	tmp = (tmp & SysTick_CALIB_NOREF) >> 31;
	return (bool)tmp;
}

static inline void hri_systick_write_CALIB_NOREF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SysTick_CRITICAL_SECTION_ENTER();
	tmp = ((Systick *)hw)->CALIB;
	tmp &= ~SysTick_CALIB_NOREF;
	tmp |= value << 31;
	((Systick *)hw)->CALIB = tmp;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_clear_CALIB_NOREF_bit(const void *const hw)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CALIB &= ~SysTick_CALIB_NOREF;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_toggle_CALIB_NOREF_bit(const void *const hw)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CALIB ^= SysTick_CALIB_NOREF;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_set_CALIB_TENMS_bf(const void *const hw, hri_systick_calib_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CALIB |= SysTick_CALIB_TENMS(mask);
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline hri_systick_calib_reg_t hri_systick_get_CALIB_TENMS_bf(const void *const hw, hri_systick_calib_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Systick *)hw)->CALIB;
	tmp = (tmp & SysTick_CALIB_TENMS(mask)) >> 0;
	return tmp;
}

static inline void hri_systick_write_CALIB_TENMS_bf(const void *const hw, hri_systick_calib_reg_t data)
{
	uint32_t tmp;
	SysTick_CRITICAL_SECTION_ENTER();
	tmp = ((Systick *)hw)->CALIB;
	tmp &= ~SysTick_CALIB_TENMS_Msk;
	tmp |= SysTick_CALIB_TENMS(data);
	((Systick *)hw)->CALIB = tmp;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_clear_CALIB_TENMS_bf(const void *const hw, hri_systick_calib_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CALIB &= ~SysTick_CALIB_TENMS(mask);
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_toggle_CALIB_TENMS_bf(const void *const hw, hri_systick_calib_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CALIB ^= SysTick_CALIB_TENMS(mask);
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline hri_systick_calib_reg_t hri_systick_read_CALIB_TENMS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Systick *)hw)->CALIB;
	tmp = (tmp & SysTick_CALIB_TENMS_Msk) >> 0;
	return tmp;
}

static inline void hri_systick_set_CALIB_reg(const void *const hw, hri_systick_calib_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CALIB |= mask;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline hri_systick_calib_reg_t hri_systick_get_CALIB_reg(const void *const hw, hri_systick_calib_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Systick *)hw)->CALIB;
	tmp &= mask;
	return tmp;
}

static inline void hri_systick_write_CALIB_reg(const void *const hw, hri_systick_calib_reg_t data)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CALIB = data;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_clear_CALIB_reg(const void *const hw, hri_systick_calib_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CALIB &= ~mask;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_toggle_CALIB_reg(const void *const hw, hri_systick_calib_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CALIB ^= mask;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline hri_systick_calib_reg_t hri_systick_read_CALIB_reg(const void *const hw)
{
	return ((Systick *)hw)->CALIB;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_SysTick_S70_H_INCLUDED */
#endif /* _SAMS70_SysTick_COMPONENT_ */
