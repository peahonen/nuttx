/************************************************************************************
 * arch/arm/src/stm32l4/stm32l4_qencoder.h
 *
 *   Copyright (C) 2012 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ************************************************************************************/

#ifndef __ARCH_ARM_SRC_STM32L4_STM32L4_QENCODER_H
#define __ARCH_ARM_SRC_STM32L4_STM32L4_QENCODER_H

/************************************************************************************
 * Included Files
 ************************************************************************************/

#include <nuttx/config.h>

#include "chip.h"

#ifdef CONFIG_QENCODER

/************************************************************************************
 * Included Files
 ************************************************************************************/
/* Timer devices may be used for different purposes.  One special purpose is as
 * a quadrature encoder input device.  If CONFIG_STM32L4_TIMn is defined then the
 * CONFIG_STM32L4_TIMn_QE must also be defined to indicate that timer "n" is intended
 * to be used for as a quadrature encoder.
 */

#ifndef CONFIG_STM32L4_TIM1
#  undef CONFIG_STM32L4_TIM1_QE
#endif
#ifndef CONFIG_STM32L4_TIM2
#  undef CONFIG_STM32L4_TIM2_QE
#endif
#ifndef CONFIG_STM32L4_TIM3
#  undef CONFIG_STM32L4_TIM3_QE
#endif
#ifndef CONFIG_STM32L4_TIM4
#  undef CONFIG_STM32L4_TIM4_QE
#endif
#ifndef CONFIG_STM32L4_TIM5
#  undef CONFIG_STM32L4_TIM5_QE
#endif
#ifndef CONFIG_STM32L4_TIM8
#  undef CONFIG_STM32L4_TIM8_QE
#endif

/* Only timers 2-5, and 1 & 8 can be used as a quadrature encoder
 */

#undef CONFIG_STM32L4_TIM6_QE
#undef CONFIG_STM32L4_TIM7_QE
#undef CONFIG_STM32L4_TIM9_QE
#undef CONFIG_STM32L4_TIM10_QE
#undef CONFIG_STM32L4_TIM11_QE
#undef CONFIG_STM32L4_TIM12_QE
#undef CONFIG_STM32L4_TIM13_QE
#undef CONFIG_STM32L4_TIM14_QE

/* Clock out frequency.  This value is used to calculation the timer CLKIN in
 * prescaler value.
 */

#ifndef CONFIG_STM32L4_TIM1_QECLKOUT
#  define CONFIG_STM32L4_TIM1_QECLKOUT 28000000
#endif

#ifndef CONFIG_STM32L4_TIM2_QECLKOUT
#  define CONFIG_STM32L4_TIM2_QECLKOUT 28000000
#endif

#ifndef CONFIG_STM32L4_TIM3_QECLKOUT
#  define CONFIG_STM32L4_TIM3_QECLKOUT 28000000
#endif

#ifndef CONFIG_STM32L4_TIM4_QECLKOUT
#  define CONFIG_STM32L4_TIM4_QECLKOUT 28000000
#endif

#ifndef CONFIG_STM32L4_TIM5_QECLKOUT
#  define CONFIG_STM32L4_TIM5_QECLKOUT 28000000
#endif

#ifndef CONFIG_STM32L4_TIM8_QECLKOUT
#  define CONFIG_STM32L4_TIM8_QECLKOUT 28000000
#endif

/************************************************************************************
 * Included Files
 ************************************************************************************/

/************************************************************************************
 * Name: stm32l4_qeinitialize
 *
 * Description:
 *   Initialize a quadrature encoder interface.  This function must be called from
 *   board-specific logic..
 *
 * Input Parameters:
 *   devpath - The full path to the driver to register. E.g., "/dev/qe0"
 *   tim     - The timer number to used.  'tim' must be an element of {1,2,3,4,5,8}
 *
 * Returned Values:
 *   Zero on success; A negated errno value is returned on failure.
 *
 ************************************************************************************/

int stm32l4_qeinitialize(FAR const char *devpath, int tim);

#endif /* CONFIG_QENCODER */
#endif /* __ARCH_ARM_SRC_STM32L4_STM32L4_QENCODER_H */

