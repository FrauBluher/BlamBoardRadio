/**
 * \file
 *
 * \brief SAM CHIPID
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

#ifdef _SAMS70_CHIPID_COMPONENT_
#ifndef _HRI_CHIPID_S70_H_INCLUDED_
#define _HRI_CHIPID_S70_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_CHIPID_CRITICAL_SECTIONS)
#define CHIPID_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define CHIPID_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define CHIPID_CRITICAL_SECTION_ENTER()
#define CHIPID_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_chipid_cidr_reg_t;
typedef uint32_t hri_chipid_exid_reg_t;

static inline bool hri_chipid_get_CIDR_EXT_bit(const void *const hw)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_EXT) > 0;
}

static inline hri_chipid_cidr_reg_t hri_chipid_get_CIDR_VERSION_bf(const void *const hw, hri_chipid_cidr_reg_t mask)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_VERSION(mask)) >> CHIPID_CIDR_VERSION_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_read_CIDR_VERSION_bf(const void *const hw)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_VERSION_Msk) >> CHIPID_CIDR_VERSION_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_get_CIDR_EPROC_bf(const void *const hw, hri_chipid_cidr_reg_t mask)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_EPROC(mask)) >> CHIPID_CIDR_EPROC_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_read_CIDR_EPROC_bf(const void *const hw)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_EPROC_Msk) >> CHIPID_CIDR_EPROC_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_get_CIDR_NVPSIZ_bf(const void *const hw, hri_chipid_cidr_reg_t mask)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_NVPSIZ(mask)) >> CHIPID_CIDR_NVPSIZ_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_read_CIDR_NVPSIZ_bf(const void *const hw)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_NVPSIZ_Msk) >> CHIPID_CIDR_NVPSIZ_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_get_CIDR_NVPSIZ2_bf(const void *const hw, hri_chipid_cidr_reg_t mask)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_NVPSIZ2(mask)) >> CHIPID_CIDR_NVPSIZ2_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_read_CIDR_NVPSIZ2_bf(const void *const hw)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_NVPSIZ2_Msk) >> CHIPID_CIDR_NVPSIZ2_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_get_CIDR_SRAMSIZ_bf(const void *const hw, hri_chipid_cidr_reg_t mask)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_SRAMSIZ(mask)) >> CHIPID_CIDR_SRAMSIZ_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_read_CIDR_SRAMSIZ_bf(const void *const hw)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_SRAMSIZ_Msk) >> CHIPID_CIDR_SRAMSIZ_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_get_CIDR_ARCH_bf(const void *const hw, hri_chipid_cidr_reg_t mask)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_ARCH(mask)) >> CHIPID_CIDR_ARCH_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_read_CIDR_ARCH_bf(const void *const hw)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_ARCH_Msk) >> CHIPID_CIDR_ARCH_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_get_CIDR_NVPTYP_bf(const void *const hw, hri_chipid_cidr_reg_t mask)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_NVPTYP(mask)) >> CHIPID_CIDR_NVPTYP_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_read_CIDR_NVPTYP_bf(const void *const hw)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_NVPTYP_Msk) >> CHIPID_CIDR_NVPTYP_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_get_CIDR_reg(const void *const hw, hri_chipid_cidr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Chipid *)hw)->CHIPID_CIDR;
	tmp &= mask;
	return tmp;
}

static inline hri_chipid_cidr_reg_t hri_chipid_read_CIDR_reg(const void *const hw)
{
	return ((Chipid *)hw)->CHIPID_CIDR;
}

static inline hri_chipid_exid_reg_t hri_chipid_get_EXID_EXID_bf(const void *const hw, hri_chipid_exid_reg_t mask)
{
	return (((Chipid *)hw)->CHIPID_EXID & CHIPID_EXID_EXID(mask)) >> CHIPID_EXID_EXID_Pos;
}

static inline hri_chipid_exid_reg_t hri_chipid_read_EXID_EXID_bf(const void *const hw)
{
	return (((Chipid *)hw)->CHIPID_EXID & CHIPID_EXID_EXID_Msk) >> CHIPID_EXID_EXID_Pos;
}

static inline hri_chipid_exid_reg_t hri_chipid_get_EXID_reg(const void *const hw, hri_chipid_exid_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Chipid *)hw)->CHIPID_EXID;
	tmp &= mask;
	return tmp;
}

static inline hri_chipid_exid_reg_t hri_chipid_read_EXID_reg(const void *const hw)
{
	return ((Chipid *)hw)->CHIPID_EXID;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_CHIPID_S70_H_INCLUDED */
#endif /* _SAMS70_CHIPID_COMPONENT_ */
