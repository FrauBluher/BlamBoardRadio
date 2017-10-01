/**
 * \file
 *
 * \brief SAM TRNG
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

#ifdef _SAMS70_TRNG_COMPONENT_
#ifndef _HRI_TRNG_S70_H_INCLUDED_
#define _HRI_TRNG_S70_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_TRNG_CRITICAL_SECTIONS)
#define TRNG_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define TRNG_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define TRNG_CRITICAL_SECTION_ENTER()
#define TRNG_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_trng_cr_reg_t;
typedef uint32_t hri_trng_imr_reg_t;
typedef uint32_t hri_trng_isr_reg_t;
typedef uint32_t hri_trng_odata_reg_t;

static inline void hri_trng_set_IMR_DATRDY_bit(const void *const hw)
{
	((Trng *)hw)->TRNG_IER = TRNG_IMR_DATRDY;
}

static inline bool hri_trng_get_IMR_DATRDY_bit(const void *const hw)
{
	return (((Trng *)hw)->TRNG_IMR & TRNG_IMR_DATRDY) >> TRNG_IMR_DATRDY_Pos;
}

static inline void hri_trng_write_IMR_DATRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Trng *)hw)->TRNG_IDR = TRNG_IMR_DATRDY;
	} else {
		((Trng *)hw)->TRNG_IER = TRNG_IMR_DATRDY;
	}
}

static inline void hri_trng_clear_IMR_DATRDY_bit(const void *const hw)
{
	((Trng *)hw)->TRNG_IDR = TRNG_IMR_DATRDY;
}

static inline void hri_trng_set_IMR_reg(const void *const hw, hri_trng_imr_reg_t mask)
{
	((Trng *)hw)->TRNG_IER = mask;
}

static inline hri_trng_imr_reg_t hri_trng_get_IMR_reg(const void *const hw, hri_trng_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Trng *)hw)->TRNG_IMR;
	tmp &= mask;
	return tmp;
}

static inline hri_trng_imr_reg_t hri_trng_read_IMR_reg(const void *const hw)
{
	return ((Trng *)hw)->TRNG_IMR;
}

static inline void hri_trng_write_IMR_reg(const void *const hw, hri_trng_imr_reg_t data)
{
	((Trng *)hw)->TRNG_IER = data;
	((Trng *)hw)->TRNG_IDR = ~data;
}

static inline void hri_trng_clear_IMR_reg(const void *const hw, hri_trng_imr_reg_t mask)
{
	((Trng *)hw)->TRNG_IDR = mask;
}

static inline bool hri_trng_get_ISR_DATRDY_bit(const void *const hw)
{
	return (((Trng *)hw)->TRNG_ISR & TRNG_ISR_DATRDY) >> TRNG_ISR_DATRDY_Pos;
}

static inline hri_trng_isr_reg_t hri_trng_get_ISR_reg(const void *const hw, hri_trng_isr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Trng *)hw)->TRNG_ISR;
	tmp &= mask;
	return tmp;
}

static inline hri_trng_isr_reg_t hri_trng_read_ISR_reg(const void *const hw)
{
	return ((Trng *)hw)->TRNG_ISR;
}

static inline void hri_trng_write_CR_reg(const void *const hw, hri_trng_cr_reg_t data)
{
	TRNG_CRITICAL_SECTION_ENTER();
	((Trng *)hw)->TRNG_CR = data;
	TRNG_CRITICAL_SECTION_LEAVE();
}

static inline hri_trng_odata_reg_t hri_trng_get_ODATA_ODATA_bf(const void *const hw, hri_trng_odata_reg_t mask)
{
	return (((Trng *)hw)->TRNG_ODATA & TRNG_ODATA_ODATA(mask)) >> TRNG_ODATA_ODATA_Pos;
}

static inline hri_trng_odata_reg_t hri_trng_read_ODATA_ODATA_bf(const void *const hw)
{
	return (((Trng *)hw)->TRNG_ODATA & TRNG_ODATA_ODATA_Msk) >> TRNG_ODATA_ODATA_Pos;
}

static inline hri_trng_odata_reg_t hri_trng_get_ODATA_reg(const void *const hw, hri_trng_odata_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Trng *)hw)->TRNG_ODATA;
	tmp &= mask;
	return tmp;
}

static inline hri_trng_odata_reg_t hri_trng_read_ODATA_reg(const void *const hw)
{
	return ((Trng *)hw)->TRNG_ODATA;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_TRNG_S70_H_INCLUDED */
#endif /* _SAMS70_TRNG_COMPONENT_ */
