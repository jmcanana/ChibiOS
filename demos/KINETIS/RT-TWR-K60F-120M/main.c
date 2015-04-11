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
#include "chprintf.h"

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


/*
 * Console output.
 */
static BaseSequentialStream *chp = (BaseSequentialStream*) &SD6;

/**
 * @brief   Prints a line without final end-of-line.
 *
 * @param[in] msgp      the message
 */
static void console_print(const char *msgp) {

  while (*msgp)
    chSequentialStreamPut(chp, *msgp++);
}

/**
 * @brief   Prints a line.
 *
 * @param[in] msgp      the message
 */
void console_println(const char *msgp) {

  console_print(msgp);
  chSequentialStreamWrite(chp, (const uint8_t *)"\r\n", 2);
}


/* --------------------   ADC ---------------------------- */
#define ADC_GRP1_NUM_CHANNELS   3
#define ADC_GRP1_BUF_DEPTH      1

typedef struct {
    int pot;
    int temp;
    int vamb;
} aips_t;

enum {
    _ADC0,
    _ADC1,
    _ADC2,
    _ADC3,
    _MAX_ADC,
};

static aips_t aips[_MAX_ADC];

static adcsample_t samples0[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];
static adcsample_t samples1[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];
static adcsample_t samples2[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];
static adcsample_t samples3[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];

static void adc_end_cb(ADCDriver *adcp, adcsample_t *buffer, size_t n) {

#if 0
    (void)adcp;
    (void)n;
#endif
    int adcIdx = -1;

    /*
     * The bandgap value represents the ADC reading for 1.0V
     */
    uint16_t pot     = buffer[0];
    uint16_t sensor  = buffer[1];
    uint16_t bandgap = buffer[2];

    /*
     * The v25 value is the voltage reading at 25C, it comes from the ADC
     * electricals table in the processor manual. V25 is in millivolts.
     */
    int32_t v25 = 716;

    /*
     * The m value is slope of the temperature sensor values, again from
     * the ADC electricals table in the processor manual.
     * M in microvolts per degree.
     */
    int32_t m = 1620;

    /*
     * Divide the temperature sensor reading by the bandgap to get
     * the voltage for the ambient temperature in millivolts.
     */
    int32_t vamb = (sensor * 1000) / bandgap;

    /*
     * This formula comes from the reference manual.
     * Temperature is in millidegrees C.
     */
    int32_t delta = (((vamb - v25) * 1000000) / m);
    int32_t temp = 25000 - delta;

    if (&ADCD0 == adcp) {
        adcIdx = _ADC0;
    }
    else if (&ADCD1 == adcp) {
        adcIdx = _ADC1;
    }
    else if (&ADCD2 == adcp) {
        adcIdx = _ADC2;
    }
    else if (&ADCD3 == adcp) {
        adcIdx = _ADC3;
    }

    if (adcIdx > -1) {
        aips[adcIdx].pot  = pot;
        aips[adcIdx].temp = temp;
        aips[adcIdx].vamb = vamb;
    }




#if 0
            if (temp < 19000) {
                /* Turn just the Blue LED on if less than 19C */
                palSetPad(GPIOB,18);    // Red
                palSetPad(GPIOB,19);    // Green
                palClearPad(GPIOD,1);   // Blue
            } else if (temp > 28000) {
                /* Turn just the Red LED on if greater than 28C */
                palClearPad(GPIOB,18);  // Red
                palSetPad(GPIOB,19);    // Green
                palSetPad(GPIOD,1);     // Blue
            } else {
                /* Turn just the Green LED on if between 19C and 28C */
                palSetPad(GPIOB,18);    // Red
                palClearPad(GPIOB,19);  // Green
                palSetPad(GPIOD,1);     // Blue
            }
#endif
}

/*
 * ADC conversion group.
 * Mode:        Linear buffer, 8 samples of 1 channel, SW triggered.
 */
static const ADCConversionGroup adcgrpcfg1 = {
  false,
  ADC_GRP1_NUM_CHANNELS,
  adc_end_cb,
  NULL,
  ADC_AD20 | ADC_TEMP_SENSOR | ADC_BANDGAP,
  /* CFG1 Regiser - ADCCLK = SYSCLK / 16, 16 bits per sample */
  ADCx_CFG1_ADIV(ADCx_CFG1_ADIV_DIV_8) |
    ADCx_CFG1_ADICLK(ADCx_CFG1_ADIVCLK_BUS_CLOCK_DIV_2) |
    ADCx_CFG1_MODE(ADCx_CFG1_MODE_16_BITS),
  /* SC3 Register - Average 32 readings per sample */
  ADCx_SC3_AVGE |
    ADCx_SC3_AVGS(ADCx_SC3_AVGS_AVERAGE_32_SAMPLES)
};

static const ADCConfig adccfg1 = {
  /* Perform initial calibration */
  true
};



/*
 * Threads.
 */

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

static THD_WORKING_AREA(waThread3, 512);
static THD_FUNCTION(Thread3, arg) {
    char string[256];
    (void)arg;
    chRegSetThreadName("BlueBlinker");
    while (TRUE) {
#if 1
        for (int i =0; i < _MAX_ADC; i++) {
            chsnprintf(string, 255, "ADC_%d: Pot: %d, Temp: %d, vamb %d", i,
                    aips[i].pot,  aips[i].temp, aips[i].vamb ) ;
            console_println(string);
        }
        console_println("==========================\n");
#endif


        palTogglePad(IOPORT1, 10);
        chThdSleepMilliseconds(2000);
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

    /*
     * Activate the ADC drivers.
     */
    adcStart(&ADCD0, &adccfg1);
    adcStart(&ADCD1, &adccfg1);
    adcStart(&ADCD2, &adccfg1);
    adcStart(&ADCD3, &adccfg1);


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

    //  TestThread(&SD6);
    console_println("");
    console_println("*** ChibiOS/RT Here we go!");
    console_println("***");

    char string[256];
    chsnprintf(string, 255, "Here we go! %d %x", 3, 0xbeef) ;
    console_println(string);

    while (1) {
        /*
         * ADC linear conversion.
         */
        adcConvert(&ADCD0, &adcgrpcfg1, samples0, ADC_GRP1_BUF_DEPTH);
        adcConvert(&ADCD1, &adcgrpcfg1, samples1, ADC_GRP1_BUF_DEPTH);
        adcConvert(&ADCD2, &adcgrpcfg1, samples2, ADC_GRP1_BUF_DEPTH);
        adcConvert(&ADCD3, &adcgrpcfg1, samples3, ADC_GRP1_BUF_DEPTH);

        chThdSleepMilliseconds(500);
    }


}
