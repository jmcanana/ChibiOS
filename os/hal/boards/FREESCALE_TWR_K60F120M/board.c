/*
   ChibiOS/RT - Copyright (C) 2006-2014 Giovanni Di Sirio

   Licensed under the Apache License,
   Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software
distributed under the License is distributed on an "AS IS" BASIS,

WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
 */
#include "hal.h"

#if HAL_USE_PAL || defined(__DOXYGEN__)
/**
 * @brief   PAL setup.
 * @details Digital I/O ports static configuration as defined in @p board.h.
 *          This variable is used by the HAL when initializing the PAL driver.
 */

/*
 * JM:  See pal_lld.c for effect...
 *       switch (mode) {
 *       case PAL_MODE_RESET:
 *       case PAL_MODE_INPUT:
 *       case PAL_MODE_OUTPUT_PUSHPULL:
 *       portcfg->PCR[pad] = PIN_MUX_ALTERNATIVE(1);
 *       break;
 *       case PAL_MODE_OUTPUT_PUSHPULL:
 *       portcfg->PCR[pad] = PIN_MUX_ALTERNATIVE(1) |
 *       PORTx_PCRn_ODE;
 *       break;
 *       case PAL_MODE_INPUT_PULLUP:
 *       portcfg->PCR[pad] = PIN_MUX_ALTERNATIVE(1) |
 *       PORTx_PCRn_PE |
 *       PORTx_PCRn_PS;
 *       break;
 *       case PAL_MODE_INPUT_PULLDOWN:
 *       portcfg->PCR[pad] = PIN_MUX_ALTERNATIVE(1) |
 *       PORTx_PCRn_PE;
 *       break;
 *       case PAL_MODE_UNCONNECTED: <- this actually means alt(0)...
 *       case PAL_MODE_INPUT_ANALOG:
 *       portcfg->PCR[pad] = PIN_MUX_ALTERNATIVE(0);
 *       break;
 *       case PAL_MODE_ALTERNATIVE_1:
 *       portcfg->PCR[pad] = PIN_MUX_ALTERNATIVE(1);
 *       break;
 *       case PAL_MODE_ALTERNATIVE_2:
 *       portcfg->PCR[pad] = PIN_MUX_ALTERNATIVE(2);
 *       break;
 *       case PAL_MODE_ALTERNATIVE_3:
 *       portcfg->PCR[pad] = PIN_MUX_ALTERNATIVE(3);
 *       break;
 *       case PAL_MODE_ALTERNATIVE_4:
 *       portcfg->PCR[pad] = PIN_MUX_ALTERNATIVE(4);
 *       break;
 *       case PAL_MODE_ALTERNATIVE_5:
 *       portcfg->PCR[pad] = PIN_MUX_ALTERNATIVE(5);
 *       break;
 *       case PAL_MODE_ALTERNATIVE_6:
 *       portcfg->PCR[pad] = PIN_MUX_ALTERNATIVE(6);
 *       break;
 *       case PAL_MODE_ALTERNATIVE_7:
 *       portcfg->PCR[pad] = PIN_MUX_ALTERNATIVE(7);
 *       break;
 *       }
 */
const PALConfig pal_default_config =
{
    .ports = {
        {
            .port = IOPORT1, // PORTA
            .pads = {
                /* PTA0*/ PAL_MODE_ALTERNATIVE_7,   /* [TCLK] */
                /* PTA1*/ PAL_MODE_ALTERNATIVE_7,   /* [TDI],FTM0_CH6,UART0_RX */
                /* PTA2*/ PAL_MODE_ALTERNATIVE_7,   /* [TDO],FTMO_CH7,UART0_TX */
                /* PTA3*/ PAL_MODE_ALTERNATIVE_7,   /* [TMS] */
                /* PTA4*/ PAL_MODE_UNCONNECTED,     /* ESP_CSr_N, TSI_CH5 */
                /* PTA5*/ PAL_MODE_UNCONNECTED,     /* TRST, RMIIO_RXER-MIIO_RXER */
                /* PTA6*/ PAL_MODE_ALTERNATIVE_3,   /* ULPI_CLK,TRACE_CLKOUT,[FTM0_CH3] */
                /* PTA7*/ PAL_MODE_ALTERNATIVE_3,   /* ULPI_DIR/TRACE_D3/[FTM0_CH4] */
                /* PTA8*/ PAL_MODE_ALTERNATIVE_3,   /* ULPI_NXT/TRACE_D2/[FTM1_CH0] */
                /* PTA9*/ PAL_MODE_ALTERNATIVE_3,   /* ULPI_STP/[FTM1_CH1]/TRACE_D1 */
                /*PTA10*/ PAL_MODE_OUTPUT_PUSHPULL,/* ULPI_DATA0, [Blue LED] */
                /*PTA11*/ PAL_MODE_OUTPUT_PUSHPULL,/* ULPI_DATA1, [Orange LED] */
                /*PTA12*/ PAL_MODE_ALTERNATIVE_6,   /* I2S0_TXD0 - Requires Jumper J21 pins 1,2 */
                /*PTA13*/ PAL_MODE_ALTERNATIVE_6,   /* I2S0_TX_FS- Requires Jumper J22 pins 1,2 */
                /*PTA14*/ PAL_MODE_UNCONNECTED,     /* RMII0_CRS_DV-MII0_RXDV */
                /*PTA15*/ PAL_MODE_UNCONNECTED,     /* RMII0_TXEN-MII0_TXEN */
                /*PTA16*/ PAL_MODE_UNCONNECTED,	    /* RMII0_TXD0-MII0_TXD0 */
                /*PTA17*/ PAL_MODE_UNCONNECTED,	    /* RMII0_TXD1-MII0_TXD1 */
                /*PTA18*/ PAL_MODE_UNCONNECTED,     /* [EXTAL] */
                /*PTA19*/ PAL_MODE_INPUT_PULLUP,    /* TWRPI_GPIO3/[pushbutton1] */
                /*PTA20*/ PAL_MODE_UNCONNECTED,     /* NC */
                /*PTA21*/ PAL_MODE_UNCONNECTED,     /* NC */
                /*PTA22*/ PAL_MODE_UNCONNECTED,     /* NC */
                /*PTA23*/ PAL_MODE_UNCONNECTED,     /* NC */
                /*PTA24*/ PAL_MODE_ALTERNATIVE_2,   /* ULPI_DATA2 */
                /*PTA25*/ PAL_MODE_ALTERNATIVE_2,   /* ULPI_DATA3 */
                /*PTA26*/ PAL_MODE_ALTERNATIVE_2,   /* ULPI_DATA4 */
                /*PTA27*/ PAL_MODE_ALTERNATIVE_2,   /* ULPI_DATA5 */
                /*PTA28*/ PAL_MODE_OUTPUT_PUSHPULL,/* ULPI_DATA6, [Yellow LED] */
                /*PTA29*/ PAL_MODE_OUTPUT_PUSHPULL,/* ULPI_DATA7, [Green LED] */
                /*PTA30*/ PAL_MODE_UNCONNECTED,     /* NC */
                /*PTA31*/ PAL_MODE_UNCONNECTED,     /* NC */
            },
        },
        {
            .port = IOPORT2, // PORTB
            .pads = {
                /* PTB1*/ PAL_MODE_UNCONNECTED,	    /* RMII0_MDIO-MII0_MDIO/TSI0_CH0 */
                /* PTB1*/ PAL_MODE_UNCONNECTED,	    /* RMII0_MDC-MII0_MDC/TSI0_CH6 */
                /* PTB2*/ PAL_MODE_UNCONNECTED,	    /* TS_TCH_I2C_SCL/TSI0_CH7 */
                /* PTB3*/ PAL_MODE_UNCONNECTED,	    /* TS_TCH_I2C_SDA/TSI_CH8 */
                /* PTB4*/ PAL_MODE_UNCONNECTED,	    /* IRQ from Accel or ADC1_SE10 */
                /* PTB5*/ PAL_MODE_UNCONNECTED,	    /* IRQE/IRQF/ADC1_SE11 */
                /* PTB6*/ PAL_MODE_UNCONNECTED,	    /* FB_AD23/IRQC/IRQD/ADC1_SE12 */
                /* PTB7*/ PAL_MODE_UNCONNECTED,	    /* FB_AD22/IRQA/IRQB/ADC1_SE13 */
                /* PTB8*/ PAL_MODE_UNCONNECTED,	    /* FB_AD21/TWRPI_GPIO1 */
                /* PTB9*/ PAL_MODE_UNCONNECTED,	    /* FB_AD20/TWRPI_GPIO2 */
                /*PTB10*/ PAL_MODE_UNCONNECTED,	    /* FB_AD19 */
                /*PTB11*/ PAL_MODE_UNCONNECTED,	    /* FB_AD18 */
                /*PTB12*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTB13*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTB14*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTB15*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTB16*/ PAL_MODE_UNCONNECTED,     /* FB_AD17/DSPI_DOUT/TSI_CH9 */
                /*PTB17*/ PAL_MODE_UNCONNECTED,	    /* FB_AD16/DSPI_DIN/TSI0_CH10 */
                /*PTB18*/ PAL_MODE_UNCONNECTED,	    /* FB_AD15/TSI0_CH11 */
                /*PTB19*/ PAL_MODE_UNCONNECTED,	    /* FB_OE_N/TSI0_CH12 */
                /*PTB20*/ PAL_MODE_UNCONNECTED,	    /* FB_AD31-NF_IO15/SPI2_PCS0 */
                /*PTB21*/ PAL_MODE_UNCONNECTED,	    /* FB_AD30-NF_IO14/SPI2_SCLK */
                /*PTB22*/ PAL_MODE_UNCONNECTED,	    /* FB_AD29-NF_IO13/SPI2_SOUT */
                /*PTB23*/ PAL_MODE_UNCONNECTED,	    /* FB_AD28-NF_IO12/SPI2_SIN */
                /*PTB24*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTB25*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTB26*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTB27*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTB28*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTB29*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTB30*/ PAL_MODE_UNCONNECTED,     /* NC */
                /*PTB31*/ PAL_MODE_UNCONNECTED,	    /* NC */
            },
        },
        {
            .port = IOPORT3, // PORTC
            .pads = {
                /* PTC0*/ PAL_MODE_UNCONNECTED,	    /* FB_AD14-NF_IO11/TSI0_CH13 */
                /* PTC1*/ PAL_MODE_ALTERNATIVE_4,   /* FB_AD13-NF_IO10/TSI0_CH14/[FTM0_CH0] */
                /* PTC2*/ PAL_MODE_ALTERNATIVE_4,   /* FB_AD12-NF_IO9/[FTM0_CH1]/TSI0_CH15 */
                /* PTC3*/ PAL_MODE_ALTERNATIVE_5,   /* [CLKOUT]/FTM0_CH2 */
                /* PTC4*/ PAL_MODE_UNCONNECTED,     /* FB_AD11-NF_IO8/DSPI_CS_N */
                /* PTC5*/ PAL_MODE_UNCONNECTED,     /* FB_AD10-NF_IO7/DSPI_SCK */
                /* PTC6*/ PAL_MODE_UNCONNECTED,     /* FB_AD9-NF_IO6/CMP_IN0 */
                /* PTC7*/ PAL_MODE_UNCONNECTED,     /* FB_AD8-NF_IO5/USB_AB_ID */
                /* PTC8*/ PAL_MODE_UNCONNECTED,     /* FB_AD7-NF_IO4/SSI_MCLK */
                /* PTC9*/ PAL_MODE_UNCONNECTED,     /* FB_AD6-NF_IO3/USB_AB_VBUS_OC */
                /*PTC10*/ PAL_MODE_UNCONNECTED,     /* FB_AD5-NF_IO2/I2C1_SCL */
                /*PTC11*/ PAL_MODE_UNCONNECTED,     /* FB_WE/I2C1_SDA */
                /*PTC12*/ PAL_MODE_UNCONNECTED,     /* FB_AD27/UART4_RTS_B */
                /*PTC13*/ PAL_MODE_UNCONNECTED,     /* FB_AD26/UART4_CTS_B */
                /*PTC14*/ PAL_MODE_UNCONNECTED,     /* FB_AD25/UART4_RXD1 */
                /*PTC15*/ PAL_MODE_UNCONNECTED,     /* FB_AD24/UART4_TXD1 */
                /*PTC16*/ PAL_MODE_UNCONNECTED,     /* CAN_RX1/NFC_RnB/UART3_RXD */
                /*PTC17*/ PAL_MODE_UNCONNECTED,     /* CAN_TX1/NF_CE_B/UART3_TXD */
                /*PTC18*/ PAL_MODE_UNCONNECTED,     /* NC */
                /*PTC19*/ PAL_MODE_UNCONNECTED,     /* NC */
                /*PTC20*/ PAL_MODE_UNCONNECTED,     /* NC */
                /*PTC21*/ PAL_MODE_UNCONNECTED,     /* NC */
                /*PTC22*/ PAL_MODE_UNCONNECTED,     /* NC */
                /*PTC23*/ PAL_MODE_UNCONNECTED,     /* NC */
                /*PTC24*/ PAL_MODE_UNCONNECTED,     /* NC */
                /*PTC25*/ PAL_MODE_UNCONNECTED,     /* NC */
                /*PTC26*/ PAL_MODE_UNCONNECTED,     /* NC */
                /*PTC27*/ PAL_MODE_UNCONNECTED,     /* NC */
                /*PTC28*/ PAL_MODE_UNCONNECTED,     /* NC */
                /*PTC29*/ PAL_MODE_UNCONNECTED,     /* NC */
                /*PTC30*/ PAL_MODE_UNCONNECTED,     /* NC */
                /*PTC31*/ PAL_MODE_UNCONNECTED,     /* NC */
            },
        },
        {
            .port = IOPORT4, // PORTD
            .pads = {
                /* PTD0*/ PAL_MODE_UNCONNECTED,	    /* FB_CS1_B/USB_AB_VBUS_EN */
                /* PTD1*/ PAL_MODE_UNCONNECTED,	    /* FB_CS0_B */
                /* PTD2*/ PAL_MODE_UNCONNECTED,	    /* FB_AD4/UART2_RX */
                /* PTD3*/ PAL_MODE_UNCONNECTED,	    /* FB_AD3/IRDA_TXD */
                /* PTD4*/ PAL_MODE_UNCONNECTED,     /* FB_AD2-NF_IO1 */
                /* PTD5*/ PAL_MODE_ALTERNATIVE_4,   /* FB_AD1-NF_IO0/[FTM0_CH5] */
                /* PTD6*/ PAL_MODE_ALTERNATIVE_4,   /* FB_AD0/[TMR2]/UART0_RX */
                /* PTD7*/ PAL_MODE_UNCONNECTED,	    /* CMT_IRO/UART0_TX */
                /* PTD8*/ PAL_MODE_ALTERNATIVE_2,   /* NFC_CLE/[I2C0_SCL] */
                /* PTD9*/ PAL_MODE_ALTERNATIVE_2,   /* NFC_ALE/[I2C0_SDA] */
                /*PTD10*/ PAL_MODE_UNCONNECTED,	    /* NFC_RE/TWRPI_GPIO0/IRQ */
                /*PTD11*/ PAL_MODE_ALTERNATIVE_2,   /* [SPI2_CS0] */
                /*PTD12*/ PAL_MODE_ALTERNATIVE_2,   /* [SPI2_CLK] */
                /*PTD13*/ PAL_MODE_ALTERNATIVE_2,   /* [SPI2_MOSI */
                /*PTD14*/ PAL_MODE_ALTERNATIVE_2,   /* [SPI2_MISO] */
                /*PTD15*/ PAL_MODE_ALTERNATIVE_2,   /* [SPI2_CS1] */
                /*PTD16*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTD17*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTD18*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTD19*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTD20*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTD21*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTD22*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTD23*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTD24*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTD25*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTD26*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTD27*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTD28*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTD29*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTD30*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTD31*/ PAL_MODE_UNCONNECTED,	    /* NC */
            },
        },
        {
            .port = IOPORT5, // PORTE
            .pads = {
                /* PTE0*/ PAL_MODE_UNCONNECTED,	    /* SDHC0_D1 */
                /* PTE1*/ PAL_MODE_UNCONNECTED,	    /* SDHC0_D0/SPI1_SIN */
                /* PTE2*/ PAL_MODE_UNCONNECTED,	    /* SDHC0_DCLK/SPI1_SCK */
                /* PTE3*/ PAL_MODE_UNCONNECTED,	    /* SDHC0_CMD/SPI1_SOUT */
                /* PTE4*/ PAL_MODE_UNCONNECTED,	    /* SDHC0_D3/SPI1_PCS0 */
                /* PTE5*/ PAL_MODE_UNCONNECTED,	    /* SDHC0_D2/GPIO_E5 */
                /* PTE6*/ PAL_MODE_ALTERNATIVE_4,   /* I2S0_MCLK */
                /* PTE7*/ PAL_MODE_ALTERNATIVE_4,   /* I2S0_RXD0 */
                /* PTE8*/ PAL_MODE_ALTERNATIVE_3,   /* I2S0_RX_FS/[UART5_TXD] */
                /* PTE9*/ PAL_MODE_ALTERNATIVE_3,   /* I2S0_RX_BCLK/[UART5_RXD] */
                /*PTE10*/ PAL_MODE_UNCONNECTED,	    /* AUD_SDATAO/UART5_CTS_B */
                /*PTE11*/ PAL_MODE_UNCONNECTED,	    /* I2S0_TX_FS/UART5_RTS_B */
                /*PTE12*/ PAL_MODE_ALTERNATIVE_4,   /* I2S0_TX_BCLK */
                /*PTE13*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTE14*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTE15*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTE16*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTE17*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTE18*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTE19*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTE20*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTE21*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTE22*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTE23*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTE24*/ PAL_MODE_UNCONNECTED,	    /* [EXTAL1] */
                /*PTE25*/ PAL_MODE_UNCONNECTED,	    /* XTAL1 */
                /*PTE26*/ PAL_MODE_INPUT_PULLUP,    /* [Push_Button0]/RTC_CLKOUT/TWRPI_GPIO4 */
                /*PTE27*/ PAL_MODE_UNCONNECTED,	    /* GPIO_E27 */
                /*PTE28*/ PAL_MODE_UNCONNECTED,	    /* SD_Card_Detect */
                /*PTE29*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTE30*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTE31*/ PAL_MODE_UNCONNECTED,	    /* NC */
            },
        },
        {
            .port = IOPORT6, // PORTF
            .pads = {
                /*PTF0*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF1*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF2*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF3*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF4*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF5*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF6*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF7*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF8*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF9*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF10*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF11*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF12*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF13*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF14*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF15*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF16*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF17*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF18*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF19*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF20*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF21*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF22*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF23*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF24*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF25*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF26*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF27*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF28*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF29*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF30*/ PAL_MODE_UNCONNECTED,	    /* NC */
                /*PTF31*/ PAL_MODE_UNCONNECTED,	    /* NC */
            },
        },
    },
};
#endif

/**
 * @brief   Early initialization code.
 * @details This initialization must be performed just after stack setup
 *          and before any other initialization.
 */
void __early_init(void) {

    mk60f120_clock_init();
}

/**
 * @brief   Board-specific initialization code.
 * @todo    Add your board-specific code,
 if any.
 */
void boardInit(void) {
}
