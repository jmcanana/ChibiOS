/*
    ChibiOS/RT - Copyright (C) 2014 Derek Mulcahy

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

#include "ch.h"
#include "hal.h"
#include "test.h"

/* Triggered when the button is pressed. The green led is toggled. */
static void extcb1(EXTDriver *extp, expchannel_t channel) {
  (void)extp;
  (void)channel;

  palTogglePad(IOPORT1, 29);
}

static const EXTConfig extcfg = {
  {
      {EXT_CH_MODE_FALLING_EDGE | EXT_CH_MODE_AUTOSTART, extcb1, PORTE, 26}
  }
};


static THD_WORKING_AREA(waThread1, 64);
static THD_FUNCTION(Thread1, arg) {

  (void)arg;
  chRegSetThreadName("YellowBlinker");
  while (TRUE) {
    palTogglePad(IOPORT1, 28);
    chThdSleepMilliseconds(300);
  }

  return 0;
}

static THD_WORKING_AREA(waThread2, 64);
static THD_FUNCTION(Thread2, arg) {

  (void)arg;
  chRegSetThreadName("OrangeBlinker");
  while (TRUE) {
    palTogglePad(IOPORT1, 11);
    chThdSleepMilliseconds(600);
  }

  return 0;
}

static THD_WORKING_AREA(waThread3, 64);
static THD_FUNCTION(Thread3, arg) {

  (void)arg;
  chRegSetThreadName("BlueBlinker");
  while (TRUE) {
    palTogglePad(IOPORT1, 10);
    chThdSleepMilliseconds(900);
  }

  return 0;
}


/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();


  palSetPad(IOPORT1, 11);    // Orange
  palSetPad(IOPORT1, 28);    // Yellow
  palSetPad(IOPORT1, 29);    // Green
  palSetPad(IOPORT1, 10);    // Blue

  /*
   * Activates the EXT driver 1.
   */
  palSetPadMode(IOPORT1, 19, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(IOPORT5, 26, PAL_MODE_INPUT_PULLUP);
  extStart(&EXTD1, &extcfg);


  /*
   * Activates serial 1 (UART0) using the driver default configuration.
   */
  sdStart(&SD6, NULL);

  /*
   * Creates the blinker threads.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
  chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, Thread2, NULL);
  chThdCreateStatic(waThread3, sizeof(waThread3), NORMALPRIO, Thread3, NULL);

  TestThread(&SD6);
  while (1) {
    chThdSleepMilliseconds(500);
  }


}
