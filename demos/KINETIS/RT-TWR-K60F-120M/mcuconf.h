/*
    ChibiOS/RT - Copyright (C) 2006-2014 Giovanni Di Sirio

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

#define K60x_MCUCONF

/*
 * HAL driver system settings.
 */

/* Select the MCU clocking mode below by enabling the appropriate block. */

/* Disable all clock intialization */
#define KINETIS_NO_INIT             FALSE

/* PEE mode - external 50 MHz crystal with PLL for 128 MHz core/system clock. */
#if 1
/*******************************************************************************
*  FLL-              |OUTDIV1---Core/System Clocks  [<=150 MHz]
*      \__MCGOUTCLK__|OUTDIV2---Bus Clock           [Core Clock/integer, <=75MHz]
*      /             |OUTDIV3---FlexBus Clock       [<=50MHz]
*  PLL-              |OUTDIV4---Flash Clock         [Bus Clock/integer, <=25MHz]
*
*******************************************************************************/
#define KINETIS_MCG_MODE             KINETIS_MCG_MODE_PEE
#define KINETIS_MCG_PLLREFSEL0       1 /* 12 MHz Crystal */
#define KINETIS_XTAL_FREQUENCY       12000000UL
#define KINETIS_SYSCLK_FREQUENCY    120000000UL
#define KINETIS_BUSCLK_FREQUENCY     60000000UL
#define KINETIS_FB_CLK_FREQUENCY     48000000UL
#define KINETIS_FLASH_CLK_FREQUENCY  20000000UL

#define KINETIS_MCG_PRDIV0       1  /* 12/1 =  12 MHz PLL input */
#define KINETIS_MCG_VDIV0        40 /* 20X  = 240 MHz PLL output */

/* It looks like there is a /2 somewhere in the MCG that isn't
 * clearly documented.  Maybe the /2 shown in Fig 25-1 of
 * K60P144M150SF3RM.pdf?
 *
 * To account for this, VDIV0 has been doubled from 20x to 40x.
 *
 */

#define KINETIS_MCG_OUTDIV1      2 /* System clock 120 MHz */
#define KINETIS_MCG_OUTDIV2      4 /* Bus clock 60 MHz */
#define KINETIS_MCG_OUTDIV3      5 /* FlexBus 48 MHz */
#define KINETIS_MCG_OUTDIV4     12 /* Flash clock 20 MHz */
#endif

/* FEI mode - 48 MHz with internal 32.768 kHz crystal */
#if 0
#define KINETIS_MCG_MODE            KINETIS_MCG_MODE_FEI
#define KINETIS_MCG_FLL_DMX32       1           /* Fine-tune for 32.768 kHz */
#define KINETIS_MCG_FLL_DRS         1           /* 1464x FLL factor */
#define KINETIS_SYSCLK_FREQUENCY    47972352UL  /* 32.768 kHz * 1464 (~48 MHz) */
#endif /* 0 */

/* FEE mode - 24 MHz with external 32.768 kHz crystal */
#if 0
#define KINETIS_MCG_MODE            KINETIS_MCG_MODE_FEE
#define KINETIS_MCG_FLL_DMX32       1           /* Fine-tune for 32.768 kHz */
#define KINETIS_MCG_FLL_DRS         0           /* 732x FLL factor */
#define KINETIS_MCG_FLL_OUTDIV1     1           /* Divide 48 MHz FLL by 1 => 24 MHz */
#define KINETIS_MCG_FLL_OUTDIV4     2           /* Divide OUTDIV1 output by 2 => 12 MHz */
#define KINETIS_SYSCLK_FREQUENCY    23986176UL  /* 32.768 kHz*732 (~24 MHz) */
#define KINETIS_UART0_CLOCK_FREQ    (32768 * 732) /* FLL output */
#define KINETIS_UART0_CLOCK_SRC     1           /* Select FLL clock */
#define KINETIS_BUSCLK_FREQUENCY    (KINETIS_SYSCLK_FREQUENCY / KINETIS_MCG_FLL_OUTDIV4)
#endif /* 0 */

/* FEE mode - 48 MHz */
#if 0
#define KINETIS_MCG_MODE            KINETIS_MCG_MODE_FEE
#define KINETIS_MCG_FLL_DMX32       1           /* Fine-tune for 32.768 kHz */
#define KINETIS_MCG_FLL_DRS         1           /* 1464x FLL factor */
#define KINETIS_MCG_FLL_OUTDIV1     1           /* Divide 48 MHz FLL by 1 => 48 MHz */
#define KINETIS_MCG_FLL_OUTDIV4     2           /* Divide OUTDIV1 output by 2 => 24 MHz */
#define KINETIS_SYSCLK_FREQUENCY    47972352UL  /* 32.768 kHz * 1464 (~48 MHz) */
#endif /* 0 */

/*
 * SERIAL driver system settings.
 */
#define KINETIS_SERIAL_USE_UART5              TRUE

/*
 * I2C driver system settings.
 */
#define KINETIS_I2C_USE_I2C0                  TRUE
#define KINETIS_I2C_USE_I2C1                  TRUE

/*
 * ADC driver system settings.
 */
#define KINETIS_ADC_USE_ADC0                  TRUE
#define KINETIS_ADC_USE_ADC1                  TRUE
#define KINETIS_ADC_USE_ADC2                  TRUE
#define KINETIS_ADC_USE_ADC3                  TRUE

/*
 * EXTI driver system settings.
 */
#define KINETIS_EXTI_NUM_CHANNELS               1
#define KINETIS_EXT_PORTA_IRQ_PRIORITY          3
#define KINETIS_EXT_PORTB_IRQ_PRIORITY          3
#define KINETIS_EXT_PORTC_IRQ_PRIORITY          3
#define KINETIS_EXT_PORTD_IRQ_PRIORITY          3
#define KINETIS_EXT_PORTE_IRQ_PRIORITY          3
#define KINETIS_EXT_PORTF_IRQ_PRIORITY          3

/*
 * Processor specific widths of each port.
 * Smaller numbers can be used if only lower pins in a port are being used to
 * generate interrupts. Can be set to 0 if a port is unused.
 */


#if 0
/* MK20 48pin */
#define KINETIS_EXT_PORTA_WIDTH                 20
#define KINETIS_EXT_PORTB_WIDTH                 18
#define KINETIS_EXT_PORTC_WIDTH                 8
#define KINETIS_EXT_PORTD_WIDTH                 8
#define KINETIS_EXT_PORTE_WIDTH                 0
#endif

#if 0
/* MK20 64pin  */
#define KINETIS_EXT_PORTA_WIDTH                 20
#define KINETIS_EXT_PORTB_WIDTH                 20
#define KINETIS_EXT_PORTC_WIDTH                 12
#define KINETIS_EXT_PORTD_WIDTH                 8
#define KINETIS_EXT_PORTE_WIDTH                 2
#define KINETIS_EXT_PORTF_WIDTH                 2
#endif

/* MK60 144pin  */
#define KINETIS_EXT_PORTA_WIDTH                 30
#define KINETIS_EXT_PORTB_WIDTH                 24
#define KINETIS_EXT_PORTC_WIDTH                 20
#define KINETIS_EXT_PORTD_WIDTH                 16
#define KINETIS_EXT_PORTE_WIDTH                 29
#define KINETIS_EXT_PORTF_WIDTH                  0
