/*
    ChibiOS/RT - Copyright (C) 2014 Fabio Utzig

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    K60x/hal_lld.h
 * @brief   Kinetis K60x HAL subsystem low level driver header.
 *
 * @addtogroup HAL
 * @{
 */

#ifndef _HAL_LLD_H_
#define _HAL_LLD_H_

#include "mk60f12.h"
#include "kinetis_registry.h"

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*******************************************************************************
*  FLL-              |OUTDIV1---Core/System Clocks  [<=150 MHz]
*      \__MCGOUTCLK__|OUTDIV2---Bus Clock           [Core Clock/integer, <=75MHz]
*      /             |OUTDIV3---FlexBus Clock       [<=50MHz]
*  PLL-              |OUTDIV4---Flash Clock         [Bus Clock/integer, <=25MHz]
*
*******************************************************************************/
/* @brief   Defines the support for realtime counters in the HAL.
 */
#define HAL_IMPLEMENTS_COUNTERS FALSE

/**
 * @name    Platform identification
 * @{
 */
#define PLATFORM_NAME           "Kinetis"
/** @} */

/**
 * @brief   Maximum system and core clock (f_SYS) frequency.
 */
#define KINETIS_SYSCLK_MAX      150000000

/**
 * @brief   Maximum bus clock (f_BUS) frequency.
 */
#define KINETIS_BUSCLK_MAX      75000000

/**
 * @brief   Maximum FlexFus clock (FB_CLK) frequency.
 */
#define KINETIS_FB_CLK_MAX      50000000

/**
 * @brief   Maximum Flash clock frequency.
 */
#define KINETIS_FLASH_CLK_MAX   25000000


/**
 * @name    Internal clock sources
 * @{
 */
#define KINETIS_IRCLK_F         4000000     /**< Fast internal reference clock, factory trimmed. */
#define KINETIS_IRCLK_S         32768       /**< Slow internal reference clock, factory trimmed. */
/** @} */

#define KINETIS_MCG_MODE_FEI    1    /**< FLL Engaged Internal. */
#define KINETIS_MCG_MODE_FEE    2    /**< FLL Engaged External. */
#define KINETIS_MCG_MODE_FBI    3    /**< FLL Bypassed Internal. */
#define KINETIS_MCG_MODE_FBE    4    /**< FLL Bypassed External. */
#define KINETIS_MCG_MODE_PEE    5    /**< PLL Engaged External. */
#define KINETIS_MCG_MODE_PBE    6    /**< PLL Bypassed External. */
#define KINETIS_MCG_MODE_BLPI   7    /**< Bypassed Low Power Internal. */
#define KINETIS_MCG_MODE_BLPE   8    /**< Bypassed Low Power External. */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   Disables the MCG/system clock initialization in the HAL.
 */
#if !defined(KINETIS_NO_INIT) || defined(__DOXYGEN__)
#define KINETIS_NO_INIT             FALSE
#endif

/**
 * @brief   MCG mode selection.
 */
#if !defined(KINETIS_MCG_MODE) || defined(__DOXYGEN__)
#define KINETIS_MCG_MODE            KINETIS_MCG_MODE_PEE
#endif

/**
 * @brief   MCG PLLO Source selection.
 */
#if !defined(KINETIS_MCG_PLLREFSEL0) || defined(__DOXYGEN__)
#define KINETIS_MCG_PLLREFSEL0          0
#endif


/**
 * @brief   Clock divider for PLL input (PRDIV0).
 * @note    The allowed range is 1...8.
 * @note    The default value is calculated for a 10 MHz PLL input
 *          from a 50 MHz crystal.
 */
#if !defined(KINETIS_MCG_PRDIV0) || defined(__DOXYGEN__)
#define KINETIS_MCG_PRDIV0    5
#endif

/**
 * @brief   Clock multiplier for PLL output (VDIV0).
 * @note    The allowed range is 16...47.
 * @note    The default value is calculated for a 240 MHz PLL ouput
 *          from a 10 MHz input.
 */
#if !defined(KINETIS_MCG_VDIV0) || defined(__DOXYGEN__)
#define KINETIS_MCG_VDIV0    24
#endif


/**
 * @brief   Clock divider for core/system (OUTDIV1).
 * @note    The allowed range is 1...16.
 * @note    The default value is calculated for a 120 MHz system clock
 *          from a 240 MHz PLL output.
 */
#if !defined(KINETIS_MCG_OUTDIV1) || defined(__DOXYGEN__)
#define KINETIS_MCG_OUTDIV1     2
#endif

/**
 * @brief   Clock divider for core/system and bus/flash clocks (OUTDIV2).
 * @note    The allowed range is 1...16.
 * @note    The default value is calculated for a 60 MHz system clock
 *          from a 240 MHz PLL output.
 */
#if !defined(KINETIS_MCG_OUTDIV2) || defined(__DOXYGEN__)
#define KINETIS_MCG_OUTDIV2     4
#endif

/**
 * @brief   Clock divider for flexBus clocks (OUTDIV3).
 * @note    The allowed range is 1...16.
 * @note    The default value is calculated for a 48 MHz flexBus clock
 *          from a 240 MHz PLL output.
 */
#if !defined(KINETIS_MCG_OUTDIV3) || defined(__DOXYGEN__)
#define KINETIS_MCG_OUTDIV3     5
#endif

/**
 * @brief   Clock divider for flexBus clocks (OUTDIV4).
 * @note    The allowed range is 1...16.
 * @note    The default value is calculated for a 20 MHz flash clock
 *          from a 240 MHz PLL output.
 */
#if !defined(KINETIS_MCG_OUTDIV4) || defined(__DOXYGEN__)
#define KINETIS_MCG_OUTDIV4    12
#endif



/**
 * @brief   FLL DCO tuning enable for 32.768 kHz reference.
 * @note    Set to 1 for fine-tuning DCO for maximum frequency with
 *          a 32.768 kHz reference.
 * @note    The default value is for a 32.768 kHz external crystal.
 */
#if !defined(KINETIS_MCG_FLL_DMX32) || defined(__DOXYGEN__)
#define KINETIS_MCG_FLL_DMX32       1
#endif

/**
 * @brief   FLL DCO range selection.
 * @note    The allowed range is 0...3.
 * @note    The default value is calculated for 48 MHz FLL output
 *          from a 32.768 kHz external crystal.
 *          (DMX32 && DRST_DRS=1 => F=1464; 32.768 kHz * F ~= 48 MHz.)
 *
 */
#if !defined(KINETIS_MCG_FLL_DRS) || defined(__DOXYGEN__)
#define KINETIS_MCG_FLL_DRS         2
#endif

/**
 * @brief   MCU system/core clock frequency.
 */
#if !defined(KINETIS_SYSCLK_FREQUENCY) || defined(__DOXYGEN__)
#define KINETIS_SYSCLK_FREQUENCY    120000000UL
#endif

/**
 * @brief   MCU bus/flash clock frequency.
 */
#if !defined(KINETIS_BUSCLK_FREQUENCY) || defined(__DOXYGEN__)
#define KINETIS_BUSCLK_FREQUENCY    (KINETIS_SYSCLK_FREQUENCY / KINETIS_MCG_OUTDIV4)
#endif

/**
 * @brief   UART0 and UART1 clock frequency.
 * @note    The default value is based on 128 MHz PLL/2 source.
 *          If you use a different source, such as the FLL,
 *          you must set this properly.
 */
#if !defined(KINETIS_UART0_CLOCK_FREQ) || defined(__DOXYGEN__)
#define KINETIS_UART0_CLOCK_FREQ    KINETIS_SYSCLK_FREQUENCY
#endif
#if !defined(KINETIS_UART1_CLOCK_FREQ) || defined(__DOXYGEN__)
#define KINETIS_UART1_CLOCK_FREQ    KINETIS_SYSCLK_FREQUENCY
#endif


/**
 * @brief   UART0 and UART1 clock source.
 * @note    The default value is to use PLL/2 or FLL source.
 */
#if !defined(KINETIS_UART0_CLOCK_SRC) || defined(__DOXYGEN__)
#define KINETIS_UART0_CLOCK_SRC     1
#endif
#if !defined(KINETIS_UART1_CLOCK_SRC) || defined(__DOXYGEN__)
#define KINETIS_UART1_CLOCK_SRC     1
#endif

/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if !defined(KINETIS_SYSCLK_FREQUENCY)
#error KINETIS_SYSCLK_FREQUENCY must be defined
#endif

#if KINETIS_SYSCLK_FREQUENCY <= 0 || KINETIS_SYSCLK_FREQUENCY > KINETIS_SYSCLK_MAX
#error KINETIS_SYSCLK_FREQUENCY out of range
#endif

#if !defined(KINETIS_BUSCLK_FREQUENCY)
#error KINETIS_BUSCLK_FREQUENCY must be defined
#endif

#if KINETIS_BUSCLK_FREQUENCY <= 0 || KINETIS_BUSCLK_FREQUENCY > KINETIS_BUSCLK_MAX
#error KINETIS_BUSCLK_FREQUENCY out of range
#endif

#if KINETIS_FB_CLK_FREQUENCY <= 0 || KINETIS_FB_CLK_FREQUENCY > KINETIS_FB_CLK_MAX
#error KINETIS_FB_CLK_FREQUENCY out of range
#endif

#if KINETIS_FLASH_CLK_FREQUENCY <= 0 || KINETIS_FLASH_CLK_FREQUENCY > KINETIS_FLASH_CLK_MAX
#error KINETIS_FLASH_CLK_FREQUENCY out of range
#endif



#if !(defined(KINETIS_MCG_OUTDIV1) && \
      KINETIS_MCG_OUTDIV1 >= 1 && KINETIS_MCG_OUTDIV1 <= 16)
#error KINETIS_MCG_FLL_OUTDIV1 must be 1 through 16
#endif

#if !(defined(KINETIS_MCG_OUTDIV2) && \
      KINETIS_MCG_OUTDIV2 >= 1 && KINETIS_MCG_OUTDIV2 <= 16)
#error KINETIS_MCG_FLL_OUTDIV1 must be 1 through 16
#endif
#if !(defined(KINETIS_MCG_OUTDIV3) && \
      KINETIS_MCG_OUTDIV3 >= 1 && KINETIS_MCG_OUTDIV3 <= 16)
#error KINETIS_MCG_FLL_OUTDIV1 must be 1 through 16
#endif
#if !(defined(KINETIS_MCG_OUTDIV4) && \
      KINETIS_MCG_OUTDIV4 >= 1 && KINETIS_MCG_OUTDIV4 <= 16)
#error KINETIS_MCG_FLL_OUTDIV1 must be 1 through 16
#endif

#if !(KINETIS_MCG_FLL_DMX32 == 0 || KINETIS_MCG_FLL_DMX32 == 1)
#error Invalid KINETIS_MCG_FLL_DMX32 value, must be 0 or 1
#endif

#if !(0 <= KINETIS_MCG_FLL_DRS && KINETIS_MCG_FLL_DRS <= 3)
#error Invalid KINETIS_MCG_FLL_DRS value, must be 0...3
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Type representing a system clock frequency.
 */
typedef uint32_t halclock_t;

/**
 * @brief   Type of the realtime free counter value.
 */
typedef uint32_t halrtcnt_t;

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @brief   Returns the current value of the system free running counter.
 * @note    This service is implemented by returning the content of the
 *          DWT_CYCCNT register.
 *
 * @return              The value of the system free running counter of
 *                      type halrtcnt_t.
 *
 * @notapi
 */
#define hal_lld_get_counter_value()         0

/**
 * @brief   Realtime counter frequency.
 * @note    The DWT_CYCCNT register is incremented directly by the system
 *          clock so this function returns STM32_HCLK.
 *
 * @return              The realtime counter frequency of type halclock_t.
 *
 * @notapi
 */
#define hal_lld_get_counter_frequency()     0

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#include "nvic.h"

#ifdef __cplusplus
extern "C" {
#endif
  void hal_lld_init(void);
  void mk60f120_clock_init(void);
#ifdef __cplusplus
}
#endif

#endif /* _HAL_LLD_H_ */

/** @} */
