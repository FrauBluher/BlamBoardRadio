/**
 * \file
 *
 * \brief SAM RTT
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

#ifdef _SAMS70_RTT_COMPONENT_
#ifndef _HRI_RTT_S70_H_INCLUDED_
#define _HRI_RTT_S70_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_RTT_CRITICAL_SECTIONS)
#define RTT_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define RTT_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define RTT_CRITICAL_SECTION_ENTER()
#define RTT_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_rtt_ar_reg_t;
typedef uint32_t hri_rtt_mr_reg_t;
typedef uint32_t hri_rtt_sr_reg_t;
typedef uint32_t hri_rtt_vr_reg_t;

static inline void hri_rtt_set_MR_ALMIEN_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR |= RTT_MR_ALMIEN;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtt_get_MR_ALMIEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp = (tmp & RTT_MR_ALMIEN) >> RTT_MR_ALMIEN_Pos;
	return (bool)tmp;
}

static inline void hri_rtt_write_MR_ALMIEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTT_CRITICAL_SECTION_ENTER();
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp &= ~RTT_MR_ALMIEN;
	tmp |= value << RTT_MR_ALMIEN_Pos;
	((Rtt *)hw)->RTT_MR = tmp;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_clear_MR_ALMIEN_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR &= ~RTT_MR_ALMIEN;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_toggle_MR_ALMIEN_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR ^= RTT_MR_ALMIEN;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_set_MR_RTTINCIEN_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR |= RTT_MR_RTTINCIEN;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtt_get_MR_RTTINCIEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp = (tmp & RTT_MR_RTTINCIEN) >> RTT_MR_RTTINCIEN_Pos;
	return (bool)tmp;
}

static inline void hri_rtt_write_MR_RTTINCIEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTT_CRITICAL_SECTION_ENTER();
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp &= ~RTT_MR_RTTINCIEN;
	tmp |= value << RTT_MR_RTTINCIEN_Pos;
	((Rtt *)hw)->RTT_MR = tmp;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_clear_MR_RTTINCIEN_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR &= ~RTT_MR_RTTINCIEN;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_toggle_MR_RTTINCIEN_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR ^= RTT_MR_RTTINCIEN;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_set_MR_RTTRST_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR |= RTT_MR_RTTRST;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtt_get_MR_RTTRST_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp = (tmp & RTT_MR_RTTRST) >> RTT_MR_RTTRST_Pos;
	return (bool)tmp;
}

static inline void hri_rtt_write_MR_RTTRST_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTT_CRITICAL_SECTION_ENTER();
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp &= ~RTT_MR_RTTRST;
	tmp |= value << RTT_MR_RTTRST_Pos;
	((Rtt *)hw)->RTT_MR = tmp;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_clear_MR_RTTRST_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR &= ~RTT_MR_RTTRST;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_toggle_MR_RTTRST_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR ^= RTT_MR_RTTRST;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_set_MR_RTTDIS_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR |= RTT_MR_RTTDIS;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtt_get_MR_RTTDIS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp = (tmp & RTT_MR_RTTDIS) >> RTT_MR_RTTDIS_Pos;
	return (bool)tmp;
}

static inline void hri_rtt_write_MR_RTTDIS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTT_CRITICAL_SECTION_ENTER();
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp &= ~RTT_MR_RTTDIS;
	tmp |= value << RTT_MR_RTTDIS_Pos;
	((Rtt *)hw)->RTT_MR = tmp;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_clear_MR_RTTDIS_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR &= ~RTT_MR_RTTDIS;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_toggle_MR_RTTDIS_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR ^= RTT_MR_RTTDIS;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_set_MR_RTC1HZ_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR |= RTT_MR_RTC1HZ;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtt_get_MR_RTC1HZ_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp = (tmp & RTT_MR_RTC1HZ) >> RTT_MR_RTC1HZ_Pos;
	return (bool)tmp;
}

static inline void hri_rtt_write_MR_RTC1HZ_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTT_CRITICAL_SECTION_ENTER();
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp &= ~RTT_MR_RTC1HZ;
	tmp |= value << RTT_MR_RTC1HZ_Pos;
	((Rtt *)hw)->RTT_MR = tmp;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_clear_MR_RTC1HZ_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR &= ~RTT_MR_RTC1HZ;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_toggle_MR_RTC1HZ_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR ^= RTT_MR_RTC1HZ;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_set_MR_RTPRES_bf(const void *const hw, hri_rtt_mr_reg_t mask)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR |= RTT_MR_RTPRES(mask);
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtt_mr_reg_t hri_rtt_get_MR_RTPRES_bf(const void *const hw, hri_rtt_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp = (tmp & RTT_MR_RTPRES(mask)) >> RTT_MR_RTPRES_Pos;
	return tmp;
}

static inline void hri_rtt_write_MR_RTPRES_bf(const void *const hw, hri_rtt_mr_reg_t data)
{
	uint32_t tmp;
	RTT_CRITICAL_SECTION_ENTER();
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp &= ~RTT_MR_RTPRES_Msk;
	tmp |= RTT_MR_RTPRES(data);
	((Rtt *)hw)->RTT_MR = tmp;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_clear_MR_RTPRES_bf(const void *const hw, hri_rtt_mr_reg_t mask)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR &= ~RTT_MR_RTPRES(mask);
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_toggle_MR_RTPRES_bf(const void *const hw, hri_rtt_mr_reg_t mask)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR ^= RTT_MR_RTPRES(mask);
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtt_mr_reg_t hri_rtt_read_MR_RTPRES_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp = (tmp & RTT_MR_RTPRES_Msk) >> RTT_MR_RTPRES_Pos;
	return tmp;
}

static inline void hri_rtt_set_MR_reg(const void *const hw, hri_rtt_mr_reg_t mask)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR |= mask;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtt_mr_reg_t hri_rtt_get_MR_reg(const void *const hw, hri_rtt_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtt_write_MR_reg(const void *const hw, hri_rtt_mr_reg_t data)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR = data;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_clear_MR_reg(const void *const hw, hri_rtt_mr_reg_t mask)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR &= ~mask;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_toggle_MR_reg(const void *const hw, hri_rtt_mr_reg_t mask)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR ^= mask;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtt_mr_reg_t hri_rtt_read_MR_reg(const void *const hw)
{
	return ((Rtt *)hw)->RTT_MR;
}

static inline void hri_rtt_set_AR_ALMV_bf(const void *const hw, hri_rtt_ar_reg_t mask)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_AR |= RTT_AR_ALMV(mask);
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtt_ar_reg_t hri_rtt_get_AR_ALMV_bf(const void *const hw, hri_rtt_ar_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtt *)hw)->RTT_AR;
	tmp = (tmp & RTT_AR_ALMV(mask)) >> RTT_AR_ALMV_Pos;
	return tmp;
}

static inline void hri_rtt_write_AR_ALMV_bf(const void *const hw, hri_rtt_ar_reg_t data)
{
	uint32_t tmp;
	RTT_CRITICAL_SECTION_ENTER();
	tmp = ((Rtt *)hw)->RTT_AR;
	tmp &= ~RTT_AR_ALMV_Msk;
	tmp |= RTT_AR_ALMV(data);
	((Rtt *)hw)->RTT_AR = tmp;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_clear_AR_ALMV_bf(const void *const hw, hri_rtt_ar_reg_t mask)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_AR &= ~RTT_AR_ALMV(mask);
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_toggle_AR_ALMV_bf(const void *const hw, hri_rtt_ar_reg_t mask)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_AR ^= RTT_AR_ALMV(mask);
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtt_ar_reg_t hri_rtt_read_AR_ALMV_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtt *)hw)->RTT_AR;
	tmp = (tmp & RTT_AR_ALMV_Msk) >> RTT_AR_ALMV_Pos;
	return tmp;
}

static inline void hri_rtt_set_AR_reg(const void *const hw, hri_rtt_ar_reg_t mask)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_AR |= mask;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtt_ar_reg_t hri_rtt_get_AR_reg(const void *const hw, hri_rtt_ar_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtt *)hw)->RTT_AR;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtt_write_AR_reg(const void *const hw, hri_rtt_ar_reg_t data)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_AR = data;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_clear_AR_reg(const void *const hw, hri_rtt_ar_reg_t mask)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_AR &= ~mask;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_toggle_AR_reg(const void *const hw, hri_rtt_ar_reg_t mask)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_AR ^= mask;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtt_ar_reg_t hri_rtt_read_AR_reg(const void *const hw)
{
	return ((Rtt *)hw)->RTT_AR;
}

static inline hri_rtt_vr_reg_t hri_rtt_get_VR_CRTV_bf(const void *const hw, hri_rtt_vr_reg_t mask)
{
	return (((Rtt *)hw)->RTT_VR & RTT_VR_CRTV(mask)) >> RTT_VR_CRTV_Pos;
}

static inline hri_rtt_vr_reg_t hri_rtt_read_VR_CRTV_bf(const void *const hw)
{
	return (((Rtt *)hw)->RTT_VR & RTT_VR_CRTV_Msk) >> RTT_VR_CRTV_Pos;
}

static inline hri_rtt_vr_reg_t hri_rtt_get_VR_reg(const void *const hw, hri_rtt_vr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtt *)hw)->RTT_VR;
	tmp &= mask;
	return tmp;
}

static inline hri_rtt_vr_reg_t hri_rtt_read_VR_reg(const void *const hw)
{
	return ((Rtt *)hw)->RTT_VR;
}

static inline bool hri_rtt_get_SR_ALMS_bit(const void *const hw)
{
	return (((Rtt *)hw)->RTT_SR & RTT_SR_ALMS) > 0;
}

static inline bool hri_rtt_get_SR_RTTINC_bit(const void *const hw)
{
	return (((Rtt *)hw)->RTT_SR & RTT_SR_RTTINC) > 0;
}

static inline hri_rtt_sr_reg_t hri_rtt_get_SR_reg(const void *const hw, hri_rtt_sr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtt *)hw)->RTT_SR;
	tmp &= mask;
	return tmp;
}

static inline hri_rtt_sr_reg_t hri_rtt_read_SR_reg(const void *const hw)
{
	return ((Rtt *)hw)->RTT_SR;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_RTT_S70_H_INCLUDED */
#endif /* _SAMS70_RTT_COMPONENT_ */
