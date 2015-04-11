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

/**
 * @file    K60x/serial_lld.c
 * @brief   Kinetis K60x Serial Driver subsystem low level driver source.
 *
 * @addtogroup SERIAL
 * @{
 */

#include "osal.h"
#include "hal.h"

#if HAL_USE_SERIAL || defined(__DOXYGEN__)

#include "mk60f12.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/**
 * @brief   SD1 driver identifier.
 */
#if KINETIS_SERIAL_USE_UART0 || defined(__DOXYGEN__)
SerialDriver SD1;
#endif

#if KINETIS_SERIAL_USE_UART1 || defined(__DOXYGEN__)
SerialDriver SD2;
#endif

#if KINETIS_SERIAL_USE_UART2 || defined(__DOXYGEN__)
SerialDriver SD3;
#endif

#if KINETIS_SERIAL_USE_UART3 || defined(__DOXYGEN__)
SerialDriver SD4;
#endif

#if KINETIS_SERIAL_USE_UART4 || defined(__DOXYGEN__)
SerialDriver SD5;
#endif

#if KINETIS_SERIAL_USE_UART5 || defined(__DOXYGEN__)
SerialDriver SD6;
#endif

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/**
 * @brief   Driver default configuration.
 */
static const SerialConfig default_config = {
  SERIAL_DEFAULT_BITRATE
};

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/**
 * @brief   Common IRQ handler.
 * @note    Tries hard to clear all the pending interrupt sources, we don't
 *          want to go through the whole ISR and have another interrupt soon
 *          after.
 *
 * @param[in] u         pointer to an UART I/O block
 * @param[in] sdp       communication channel associated to the UART
 */
static void serve_interrupt(SerialDriver *sdp) {
  UART_TypeDef *u = sdp->uart;
  uint8_t s1 = u->S1;

  if (s1 & UARTx_S1_RDRF) {
    osalSysLockFromISR();
    if (chIQIsEmptyI(&sdp->iqueue))
      chnAddFlagsI(sdp, CHN_INPUT_AVAILABLE);
    if (chIQPutI(&sdp->iqueue, u->D) < Q_OK)
      chnAddFlagsI(sdp, SD_OVERRUN_ERROR);
    osalSysUnlockFromISR();
  }

  if (s1 & UARTx_S1_TDRE) {
    msg_t b;

    osalSysLockFromISR();
    b = chOQGetI(&sdp->oqueue);
    osalSysUnlockFromISR();

    if (b < Q_OK) {
      osalSysLockFromISR();
      chnAddFlagsI(sdp, CHN_OUTPUT_EMPTY);
      osalSysUnlockFromISR();
      u->C2 &= ~UARTx_C2_TIE;
    } else {
       u->D = b;
    }
  }
}

/**
 * @brief   Attempts a TX preload
 */
static void preload(SerialDriver *sdp) {
  UART_TypeDef *u = sdp->uart;

  if (u->S1 & UARTx_S1_TDRE) {
    msg_t b = chOQGetI(&sdp->oqueue);
    if (b < Q_OK) {
      chnAddFlagsI(sdp, CHN_OUTPUT_EMPTY);
      return;
    }
    u->D = b;
    u->C2 |= UARTx_C2_TIE;
  }
}

/**
 * @brief   Driver output notification.
 */
#if KINETIS_SERIAL_USE_UART0 || defined(__DOXYGEN__)
static void notify1(io_queue_t *qp)
{
  (void)qp;
  preload(&SD1);
}
#endif

#if KINETIS_SERIAL_USE_UART1 || defined(__DOXYGEN__)
static void notify2(io_queue_t *qp)
{
  (void)qp;
  preload(&SD2);
}
#endif

#if KINETIS_SERIAL_USE_UART2 || defined(__DOXYGEN__)
static void notify3(io_queue_t *qp)
{
  (void)qp;
  preload(&SD3);
}
#endif


#if KINETIS_SERIAL_USE_UART3 || defined(__DOXYGEN__)
static void notify4(io_queue_t *qp)
{
  (void)qp;
  preload(&SD4);
}
#endif

#if KINETIS_SERIAL_USE_UART4 || defined(__DOXYGEN__)
static void notify5(io_queue_t *qp)
{
  (void)qp;
  preload(&SD5);
}
#endif

#if KINETIS_SERIAL_USE_UART5 || defined(__DOXYGEN__)
static void notify6(io_queue_t *qp)
{
  (void)qp;
  preload(&SD6);
}
#endif

/**
 * @brief   Common UART configuration.
 *
 */

static void configure_uart(UART_TypeDef *uart, const SerialConfig *config)
{
  uint32_t divisor;

  if (uart == UART0 || uart == UART1) {
      divisor = (KINETIS_SYSCLK_FREQUENCY * 2 + 1) / config->sc_speed;
  }
  else {
      divisor = (KINETIS_BUSCLK_FREQUENCY * 2 + 1) / config->sc_speed;
  }
  /* Disable UART while configuring */
  uart->C2 &= ~(UARTx_C2_RE | UARTx_C2_TE);
  uart->C1 = 0;

  uart->BDH = UARTx_BDH_SBR(divisor >> 13) | (uart->BDH & ~UARTx_BDH_SBR_MASK);
  uart->BDL = divisor >> 5;
  uart->C4  = UARTx_C4_BRFA(divisor) | (uart->C4 & ~UARTx_C4_BRFA_MASK);

  uart->C2 |= UARTx_C2_RE | UARTx_C2_RIE | UARTx_C2_TE;
  uart->C3 = UARTx_C3_ORIE | UARTx_C3_NEIE | UARTx_C3_FEIE | UARTx_C3_PEIE;
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

/* TODO:
 *   UART0_Status is VectorF4
 *   UART1_Status is VectorFC
 *   UART2_Status is Vector104
 *   UART3_Status is Vector10C
 *   UART4_Status is Vector114
 *   UART5_Status is Vector11C
 */

#if KINETIS_SERIAL_USE_UART0 || defined(__DOXYGEN__)
CH_IRQ_HANDLER(VectorF4) {

  CH_IRQ_PROLOGUE();
  serve_interrupt(&SD1);
  CH_IRQ_EPILOGUE();
}
#endif

#if KINETIS_SERIAL_USE_UART1 || defined(__DOXYGEN__)
CH_IRQ_HANDLER(VectorFC) {

  CH_IRQ_PROLOGUE();
  serve_interrupt(&SD2);
  CH_IRQ_EPILOGUE();
}
#endif

#if KINETIS_SERIAL_USE_UART2 || defined(__DOXYGEN__)
CH_IRQ_HANDLER(Vector104) {

  CH_IRQ_PROLOGUE();
  serve_interrupt(&SD3);
  CH_IRQ_EPILOGUE();
}

CH_IRQ_HANDLER(Vector108) {

  CH_IRQ_PROLOGUE();
  serve_interrupt(&SD3);
  CH_IRQ_EPILOGUE();
}
#endif

#if KINETIS_SERIAL_USE_UART3 || defined(__DOXYGEN__)
CH_IRQ_HANDLER(Vector10C) {

  CH_IRQ_PROLOGUE();
  serve_interrupt(&SD4);
  CH_IRQ_EPILOGUE();
}

CH_IRQ_HANDLER(Vector110) {

  CH_IRQ_PROLOGUE();
  serve_interrupt(&SD4);
  CH_IRQ_EPILOGUE();
}
#endif
#if KINETIS_SERIAL_USE_UART4 || defined(__DOXYGEN__)
CH_IRQ_HANDLER(Vector114) {

  CH_IRQ_PROLOGUE();
  serve_interrupt(&SD5);
  CH_IRQ_EPILOGUE();
}

CH_IRQ_HANDLER(Vector118) {

  CH_IRQ_PROLOGUE();
  serve_interrupt(&SD5);
  CH_IRQ_EPILOGUE();
}
#endif
#if KINETIS_SERIAL_USE_UART5 || defined(__DOXYGEN__)
CH_IRQ_HANDLER(Vector11C) {

  CH_IRQ_PROLOGUE();
  serve_interrupt(&SD6);
  CH_IRQ_EPILOGUE();
}
#endif


/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level serial driver initialization.
 *
 * @notapi
 */
void sd_lld_init(void) {

#if KINETIS_SERIAL_USE_UART0
  /* Driver initialization.*/
  sdObjectInit(&SD1, NULL, notify1);
  SD1.uart = UART0;
#endif

#if KINETIS_SERIAL_USE_UART1
  /* Driver initialization.*/
  sdObjectInit(&SD2, NULL, notify2);
  SD2.uart = UART1;
#endif

#if KINETIS_SERIAL_USE_UART2
  /* Driver initialization.*/
  sdObjectInit(&SD3, NULL, notify3);
  SD3.uart = UART2;
#endif

#if KINETIS_SERIAL_USE_UART3
  /* Driver initialization.*/
  sdObjectInit(&SD4, NULL, notify4);
  SD4.uart = UART3;
#endif

#if KINETIS_SERIAL_USE_UART4
  /* Driver initialization.*/
  sdObjectInit(&SD5, NULL, notify5);
  SD5.uart = UART4;
#endif

#if KINETIS_SERIAL_USE_UART5
  /* Driver initialization.*/
  sdObjectInit(&SD6, NULL, notify6);
  SD6.uart = UART5;
#endif

}

/**
 * @brief   Low level serial driver configuration and (re)start.
 *
 * @param[in] sdp       pointer to a @p SerialDriver object
 * @param[in] config    the architecture-dependent serial driver configuration.
 *                      If this parameter is set to @p NULL then a default
 *                      configuration is used.
 *
 * @notapi
 */
void sd_lld_start(SerialDriver *sdp, const SerialConfig *config) {

  if (config == NULL)
    config = &default_config;

  if (sdp->state == SD_STOP) {
    /* Enables the peripheral.*/

#if KINETIS_SERIAL_USE_UART0
    if (sdp == &SD1) {
      SIM->SCGC4 |= SIM_SCGC4_UART0;
      configure_uart(sdp->uart, config);
      nvicEnableVector(UART0Status_IRQn, KINETIS_SERIAL_UART0_PRIORITY);
    }
#endif /* KINETIS_SERIAL_USE_UART0 */

#if KINETIS_SERIAL_USE_UART1
    if (sdp == &SD2) {
      SIM->SCGC4 |= SIM_SCGC4_UART1;
      configure_uart(sdp->uart, config);
      nvicEnableVector(UART1Status_IRQn, KINETIS_SERIAL_UART1_PRIORITY);
    }
#endif /* KINETIS_SERIAL_USE_UART1 */

#if KINETIS_SERIAL_USE_UART2
    if (sdp == &SD3) {
      SIM->SCGC4 |= SIM_SCGC4_UART2;
      configure_uart(sdp->uart, config);
      nvicEnableVector(UART2Status_IRQn, KINETIS_SERIAL_UART2_PRIORITY);
    }
#endif /* KINETIS_SERIAL_USE_UART2 */

#if KINETIS_SERIAL_USE_UART3
    if (sdp == &SD4) {
      SIM->SCGC4 |= SIM_SCGC4_UART3;
      configure_uart(sdp->uart, config);
      nvicEnableVector(UART3Status_IRQn, KINETIS_SERIAL_UART3_PRIORITY);
    }
#endif /* KINETIS_SERIAL_USE_UART3 */

#if KINETIS_SERIAL_USE_UART4
    if (sdp == &SD5) {
      SIM->SCGC1 |= SIM_SCGC1_UART4;
      configure_uart(sdp->uart, config);
      nvicEnableVector(UART4Status_IRQn, KINETIS_SERIAL_UART4_PRIORITY);
    }
#endif /* KINETIS_SERIAL_USE_UART4 */

#if KINETIS_SERIAL_USE_UART5
    if (sdp == &SD6) {
      SIM->SCGC1 |= SIM_SCGC1_UART5;
      configure_uart(sdp->uart, config);
      nvicEnableVector(UART5Status_IRQn, KINETIS_SERIAL_UART5_PRIORITY);
    }
#endif /* KINETIS_SERIAL_USE_UART5 */


  }
  /* Configures the peripheral.*/

}

/**
 * @brief   Low level serial driver stop.
 * @details De-initializes the USART, stops the associated clock, resets the
 *          interrupt vector.
 *
 * @param[in] sdp       pointer to a @p SerialDriver object
 *
 * @notapi
 */
void sd_lld_stop(SerialDriver *sdp) {

  if (sdp->state == SD_READY) {
    /* TODO: Resets the peripheral.*/

#if KINETIS_SERIAL_USE_UART0
    if (sdp == &SD1) {
      nvicDisableVector(UART0Status_IRQn);
      SIM->SCGC4 &= ~SIM_SCGC4_UART0;
    }
#endif

#if KINETIS_SERIAL_USE_UART1
    if (sdp == &SD2) {
      nvicDisableVector(UART1Status_IRQn);
      SIM->SCGC4 &= ~SIM_SCGC4_UART1;
    }
#endif

#if KINETIS_SERIAL_USE_UART2
    if (sdp == &SD3) {
      nvicDisableVector(UART2Status_IRQn);
      SIM->SCGC4 &= ~SIM_SCGC4_UART2;
    }
#endif

#if KINETIS_SERIAL_USE_UART3
    if (sdp == &SD4) {
      nvicDisableVector(UART3Status_IRQn);
      SIM->SCGC4 &= ~SIM_SCGC4_UART3;
    }
#endif

#if KINETIS_SERIAL_USE_UART4
    if (sdp == &SD5) {
      nvicDisableVector(UART4Status_IRQn);
      SIM->SCGC1 &= ~SIM_SCGC1_UART4;
    }
#endif

#if KINETIS_SERIAL_USE_UART5
    if (sdp == &SD6) {
      nvicDisableVector(UART5Status_IRQn);
      SIM->SCGC1 &= ~SIM_SCGC1_UART5;
    }
#endif



  }
}

#endif /* HAL_USE_SERIAL */

/** @} */
