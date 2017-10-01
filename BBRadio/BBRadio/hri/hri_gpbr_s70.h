/**
 * \file
 *
 * \brief SAM GPBR
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

#ifdef _SAMS70_GPBR_COMPONENT_
#ifndef _HRI_GPBR_S70_H_INCLUDED_
#define _HRI_GPBR_S70_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_GPBR_CRITICAL_SECTIONS)
#define GPBR_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define GPBR_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define GPBR_CRITICAL_SECTION_ENTER()
#define GPBR_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_gpbr_sys_gpbr_reg_t;

static inline void hri_gpbr_set_SYS_GPBR_GPBR_VALUE_bf(const void *const hw, uint8_t index,
                                                       hri_gpbr_sys_gpbr_reg_t mask)
{
	GPBR_CRITICAL_SECTION_ENTER();
	((Gpbr *)hw)->SYS_GPBR[index] |= GPBR_SYS_GPBR_GPBR_VALUE(mask);
	GPBR_CRITICAL_SECTION_LEAVE();
}

static inline hri_gpbr_sys_gpbr_reg_t hri_gpbr_get_SYS_GPBR_GPBR_VALUE_bf(const void *const hw, uint8_t index,
                                                                          hri_gpbr_sys_gpbr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gpbr *)hw)->SYS_GPBR[index];
	tmp = (tmp & GPBR_SYS_GPBR_GPBR_VALUE(mask)) >> GPBR_SYS_GPBR_GPBR_VALUE_Pos;
	return tmp;
}

static inline void hri_gpbr_write_SYS_GPBR_GPBR_VALUE_bf(const void *const hw, uint8_t index,
                                                         hri_gpbr_sys_gpbr_reg_t data)
{
	uint32_t tmp;
	GPBR_CRITICAL_SECTION_ENTER();
	tmp = ((Gpbr *)hw)->SYS_GPBR[index];
	tmp &= ~GPBR_SYS_GPBR_GPBR_VALUE_Msk;
	tmp |= GPBR_SYS_GPBR_GPBR_VALUE(data);
	((Gpbr *)hw)->SYS_GPBR[index] = tmp;
	GPBR_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gpbr_clear_SYS_GPBR_GPBR_VALUE_bf(const void *const hw, uint8_t index,
                                                         hri_gpbr_sys_gpbr_reg_t mask)
{
	GPBR_CRITICAL_SECTION_ENTER();
	((Gpbr *)hw)->SYS_GPBR[index] &= ~GPBR_SYS_GPBR_GPBR_VALUE(mask);
	GPBR_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gpbr_toggle_SYS_GPBR_GPBR_VALUE_bf(const void *const hw, uint8_t index,
                                                          hri_gpbr_sys_gpbr_reg_t mask)
{
	GPBR_CRITICAL_SECTION_ENTER();
	((Gpbr *)hw)->SYS_GPBR[index] ^= GPBR_SYS_GPBR_GPBR_VALUE(mask);
	GPBR_CRITICAL_SECTION_LEAVE();
}

static inline hri_gpbr_sys_gpbr_reg_t hri_gpbr_read_SYS_GPBR_GPBR_VALUE_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gpbr *)hw)->SYS_GPBR[index];
	tmp = (tmp & GPBR_SYS_GPBR_GPBR_VALUE_Msk) >> GPBR_SYS_GPBR_GPBR_VALUE_Pos;
	return tmp;
}

static inline void hri_gpbr_set_SYS_GPBR_reg(const void *const hw, uint8_t index, hri_gpbr_sys_gpbr_reg_t mask)
{
	GPBR_CRITICAL_SECTION_ENTER();
	((Gpbr *)hw)->SYS_GPBR[index] |= mask;
	GPBR_CRITICAL_SECTION_LEAVE();
}

static inline hri_gpbr_sys_gpbr_reg_t hri_gpbr_get_SYS_GPBR_reg(const void *const hw, uint8_t index,
                                                                hri_gpbr_sys_gpbr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gpbr *)hw)->SYS_GPBR[index];
	tmp &= mask;
	return tmp;
}

static inline void hri_gpbr_write_SYS_GPBR_reg(const void *const hw, uint8_t index, hri_gpbr_sys_gpbr_reg_t data)
{
	GPBR_CRITICAL_SECTION_ENTER();
	((Gpbr *)hw)->SYS_GPBR[index] = data;
	GPBR_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gpbr_clear_SYS_GPBR_reg(const void *const hw, uint8_t index, hri_gpbr_sys_gpbr_reg_t mask)
{
	GPBR_CRITICAL_SECTION_ENTER();
	((Gpbr *)hw)->SYS_GPBR[index] &= ~mask;
	GPBR_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gpbr_toggle_SYS_GPBR_reg(const void *const hw, uint8_t index, hri_gpbr_sys_gpbr_reg_t mask)
{
	GPBR_CRITICAL_SECTION_ENTER();
	((Gpbr *)hw)->SYS_GPBR[index] ^= mask;
	GPBR_CRITICAL_SECTION_LEAVE();
}

static inline hri_gpbr_sys_gpbr_reg_t hri_gpbr_read_SYS_GPBR_reg(const void *const hw, uint8_t index)
{
	return ((Gpbr *)hw)->SYS_GPBR[index];
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_GPBR_S70_H_INCLUDED */
#endif /* _SAMS70_GPBR_COMPONENT_ */
