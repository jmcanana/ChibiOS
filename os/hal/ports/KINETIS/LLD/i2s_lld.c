/*
   ChibiOS/HAL - Copyright (C) 2015 James McAnanama

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
 * @file    KINETIS/LLD/i2s_lld.c
 * @brief   KINETIS I2S subsystem low level driver source.
 *
 * @addtogroup I2S
 * @{
 */

#include "osal.h"
#include "hal.h"

#if HAL_USE_I2S || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/
#define I2S_FRAME_SIZE   32
#define I2S_WORD_SIZE    16
#define I2S_FIFO_FBS    (FIFO_MSB_FIRST_16BIT_WORDS_MSB)

/* TODO: Shouldn't DMAMUX Slots and DMA channels be specified in 
 * a chip specific file?  e.g. mk60f12.h or halconf.h?  What happens
 * when two peripherals decide locally to use the same DMA channel? 
 */
/** @brief I2S0 DMA defines.*/
#if KINETIS_I2S_USE_I2S0 || defined(__DOXYGEN__)

#if !defined(KINETIS_I2S0_DMA_MUX)
#define KINETIS_I2S0_DMA_MUX 0
#endif

#if !defined(KINETIS_I2S0_RX_DMA_IRQ_PRIORITY)
#define KINETIS_I2S0_RX_DMA_IRQ_PRIORITY    8
#endif

#if !defined(KINETIS_I2S0_RX_DMAMUX_CHANNEL)
#define KINETIS_I2S0_RX_DMAMUX_CHANNEL      14
#endif

#if !defined(KINETIS_I2S0_RX_DMA_CHANNEL)
#define KINETIS_I2S0_RX_DMA_CHANNEL         14
#define KINETIS_I2S0_RX_DMA_CHANNEL_IRQ_VECTOR  KINETIS_DMA_CH14_VECTOR
#endif

#if !defined(KINETIS_I2S0_TX_DMAMUX_CHANNEL)
#define KINETIS_I2S0_TX_DMAMUX_CHANNEL      15
#endif

#if !defined(KINETIS_I2S0_TX_DMA_CHANNEL)
#define KINETIS_I2S0_TX_DMA_CHANNEL         15
#define KINETIS_I2S0_TX_DMA_CHANNEL_IRQ_VECTOR  KINETIS_DMA_CH15_VECTOR
#endif

#define DMAMUX_I2S0_RX_SOURCE    14
#define DMAMUX_I2S0_TX_SOURCE    15


#endif



/** @brief I2S1 DMA defines.*/

#if KINETIS_I2S_USE_I2S1 || defined(__DOXYGEN__)
#if !defined(KINETIS_I2S1_DMA_MUX)
#define KINETIS_I2S1_DMA_MUX 1
#endif


#if !defined(KINETIS_I2S1_RX_DMA_IRQ_PRIORITY)
#define KINETIS_I2S1_RX_DMA_IRQ_PRIORITY    8
#endif

#if !defined(KINETIS_I2S1_RX_DMAMUX_CHANNEL)
#define KINETIS_I2S1_RX_DMAMUX_CHANNEL      14
#endif

#if !defined(KINETIS_I2S1_RX_DMA_CHANNEL)
#define KINETIS_I2S1_RX_DMA_CHANNEL         14
#define KINETIS_I2S1_RX_DMA_CHANNEL_IRQ_VECTOR  KINETIS_DMA_CH14_VECTOR
#endif

#if !defined(KINETIS_I2S1_TX_DMAMUX_CHANNEL)
#define KINETIS_I2S1_TX_DMAMUX_CHANNEL      15
#endif

#if !defined(KINETIS_I2S1_TX_DMA_CHANNEL)
#define KINETIS_I2S1_TX_DMA_CHANNEL         15
#define KINETIS_I2S1_TX_DMA_CHANNEL_IRQ_VECTOR  KINETIS_DMA_CH15_VECTOR
#endif


#define DMAMUX_I2S1_RX_SOURCE    14
#define DMAMUX_I2S1_TX_SOURCE    15


#endif




/**
 * @brief   I2S interrupt priority level setting.
 */
#if !defined(KINETIS_I2S_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define KINETIS_I2S_IRQ_PRIORITY            5
#endif

enum {
    I2S_INDEX_0,
    I2S_INDEX_1,
};

typedef struct {
    int dmaMux;
    int rxDmaIrqPriority;

    int rxDmaMuxChannel;
    int rxDmaChannel;
    int rxDmaSource;

    int txDmaMuxChannel;
    int txDmaChannel;
    int txDmaSource;
} i2sDmaResources_t;

i2sDmaResources_t i2sDmaResources[] = {
    [0] = {
        dmaMux           = KINETIS_I2S0_DMA_MUX,
        rxDmaIrqPriority = KINETIS_I2S0_RX_DMA_IRQ_PRIORITY,

        rxDmaMuxChannel  = KINETIS_I2S0_RX_DMAMUX_CHANNEL,
        rxDmaChannel     = KINETIS_I2S0_RX_DMA_CHANNEL,
        rxDmaSource      = DMAMUX_I2S0_RX_SOURCE,

        txDmaMuxChannel  = KINETIS_I2S0_TX_DMAMUX_CHANNEL,
        txDmaChannel     = KINETIS_I2S0_TX_DMA_CHANNEL,
        txDmaSource      = DMAMUX_I2S0_TX_SOURCE,
    },
    [1] = {
        dmaMux           = KINETIS_I2S1_DMA_MUX,
        rxDmaIrqPriority = KINETIS_I2S1_RX_DMA_IRQ_PRIORITY,

        rxDmaMuxChannel  = KINETIS_I2S1_RX_DMAMUX1_CHANNEL,
        rxDmaChannel     = KINETIS_I2S1_RX_DMA_CHANNEL,
        rxDmaSource      = DMAMUX_I2S1_RX_SOURCE,

        txDmaMuxChannel  = KINETIS_I2S1_TX_DMAMUX1_CHANNEL,
        txDmaChannel     = KINETIS_I2S1_TX_DMA_CHANNEL,
        txDmaSource      = DMAMUX_I2S1_TX_SOURCE,
    },
};


/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/** @brief I2S0 driver identifier.*/
#if KINETIS_I2S_USE_I2S0 || defined(__DOXYGEN__)
I2SDriver I2SD0;
#endif



/** @brief I2S1 driver identifier.*/
#if KINETIS_I2S_USE_I2S1 || defined(__DOXYGEN__)
I2SDriver I2SD1;
#endif


/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/
uint32_t updateFlag;
enum {
    UPDATE_NONE,
    UPDATE_READ_DATA,
};

enum {
    FIFO_LSB_FIRST_32BIT_WORDS     = 0,   /*bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb*/
    FIFO_LSB_FIRST_24BIT_WORDS_LSB = 0,   /*xxxxxxbbbbbbbbbbbbbbbbbbbbbbbbbb*/
    FIFO_LSB_FIRST_24BIT_WORDS_MSB = 0x8, /*bbbbbbbbbbbbbbbbbbbbbbbbbbxxxxxx*/
    FIFO_LSB_FIRST_20BIT_WORDS_LSB = 0,   /*xxxxxxxxxxxxbbbbbbbbbbbbbbbbbbbb*/
    FIFO_LSB_FIRST_20BIT_WORDS_MSB = 0xC, /*bbbbbbbbbbbbbbbbbbbbxxxxxxxxxxxx*/
    FIFO_LSB_FIRST_16BIT_WORDS_LSB = 0,   /*xxxxxxxxxxxxxxxxbbbbbbbbbbbbbbbb*/
    FIFO_LSB_FIRST_16BIT_WORDS_MSB = 0x10,/*bbbbbbbbbbbbbbbbxxxxxxxxxxxxxxxx*/
    FIFO_LSB_FIRST_12BIT_WORDS_LSB = 0,   /*xxxxxxxxxxxxxxxxxxxxbbbbbbbbbbbb*/
    FIFO_LSB_FIRST_12BIT_WORDS_MSB = 0x14,/*bbbbbbbbbbbxxxxxxxxxxxxxxxxxxxxx*/
    FIFO_LSB_FIRST_8BIT_WORDS_LSB  = 0,   /*xxxxxxxxxxxxxxxxxxxxxxxxbbbbbbbb*/
    FIFO_LSB_FIRST_8BIT_WORDS_MSB  = 0x18,/*bbbbbbbbbxxxxxxxxxxxxxxxxxxxxxxx*/

    FIFO_MSB_FIRST_32BIT_WORDS     = 0x1F,/*bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb*/
    FIFO_MSB_FIRST_24BIT_WORDS_LSB = 0x17,/*xxxxxxbbbbbbbbbbbbbbbbbbbbbbbbbb*/
    FIFO_MSB_FIRST_24BIT_WORDS_MSB = 0x1F /*bbbbbbbbbbbbbbbbbbbbbbbbbbxxxxxx*/
    FIFO_MSB_FIRST_20BIT_WORDS_LSB = 0x13,/*xxxxxxxxxxxxbbbbbbbbbbbbbbbbbbbb*/
    FIFO_MSB_FIRST_20BIT_WORDS_MSB = 0x1F,/*bbbbbbbbbbbbbbbbbbbbxxxxxxxxxxxx*/
    FIFO_MSB_FIRST_16BIT_WORDS_LSB = 0x0F,/*xxxxxxxxxxxxxxxxbbbbbbbbbbbbbbbb*/
    FIFO_MSB_FIRST_16BIT_WORDS_MSB = 0x1F,/*bbbbbbbbbbbbbbbbxxxxxxxxxxxxxxxx*/
    FIFO_MSB_FIRST_12BIT_WORDS_LSB = 0x0B,/*xxxxxxxxxxxxxxxxxxxxbbbbbbbbbbbb*/
    FIFO_MSB_FIRST_12BIT_WORDS_MSB = 0x1F,/*bbbbbbbbbbbxxxxxxxxxxxxxxxxxxxxx*/
    FIFO_MSB_FIRST_8BIT_WORDS_LSB  = 0x07,/*xxxxxxxxxxxxxxxxxxxxxxxxbbbbbbbb*/
    FIFO_MSB_FIRST_8BIT_WORDS_MSB  = 0x1F,/*bbbbbbbbbxxxxxxxxxxxxxxxxxxxxxxx*/
};

/* Use a dummy byte as the source/destination when a buffer is not provided */
static volatile uint16_t dmaRxDummy;
static uint16_t dmaTxDummy = 0xFFFF;



/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/**
 * @brief   DMA transfer controller.
 * @note    Sets up DMA TX and RX 
 *
 * @param[in] i2sp         pointer to an I2SDriver
 */

static void i2s_start_xfer(I2Sriver *i2sp)
{
        int i2sIdx = -1;
        int rxDmaCh;
        int txDmaCh;
        if (&I2SD0 == i2sp) {
            i2sIdx  = I2S_INDEX_0;
        }
        else if (&I2SD1 == i2sp) {
            i2sIdx = I2S_INDEX_1;
        }

        chDbgAssert(i2sCtx != -1, "Invalid i2s instance");
        if (i2sCtx == -1) {
            return;
        }

        rxDmaCh = i2sDmaResources[i2sIdx].rxDmaSource;
        txDmaCh = i2sDmaResources[i2sIdx].txDmaSource;


                                                             /* Flush RX FIFO */
        i2sp->i2s->RCSR |= I2Sx_RCSR_FR;



        /* Configure RX DMA */
        if (i2sp->rxbuf) {
            DMA->TCD[rxDmaCh].DADDR = (uint32_t)spip->rxbuf;
            DMA->TCD[rxDmaCh].DOFF  = I2S_WORD_SIZE;
        } else {
            DMA->TCD[rxDmaCh].DADDR = (uint32_t)&dmaRxDummy;
            DMA->TCD[rxDmaCh].DOFF = 0;
        }
        DMA->TCD[rxDmaCh].BITER_ELINKNO = i2sp->count;
        DMA->TCD[rxDmaCh].CITER_ELINKNO = i2sp->count;

        /* Enable Request Register (ERQ) for RX by writing 0 to SERQ */
        DMA->SERQ = rxDmaCh;

        /* Configure TX DMA */
        if (i2sp->txbuf) {
            DMA->TCD[txDmaCh].SADDR =  (uint32_t)i2sp->txbuf;
            DMA->TCD[txDmaCh].SOFF  = I2S_WORD_SIZE;
        } else {
            DMA->TCD[txDmaCh].SADDR =  (uint32_t)&dmaTxDummy;
            DMA->TCD[txDmaCh].SOFF = 0;
        }
        DMA->TCD[txDmaCh].BITER_ELINKNO = i2sp->count;
        DMA->TCD[txDmaCh].CITER_ELINKNO = i2sp->count;

        /* Enable Request Register (ERQ) for TX by writing 1 to SERQ */
        DMA->SERQ = txDmaCh;

                                                       /* Enable DMA requests */
        i2sp->i2s->RCSR |= I2Sx_RCSR_FWDE | I2Sx_RCSR_FRDE;

                                                    /* Enable RX in stop mode */
        i2sp->i2s->RCSR |= I2Sx_RCSR_STOPE;

}

static void spi_stop_xfer(SPIDriver *spip)
{

                                                    /* Halt RX in stop mode */
        i2sp->i2s->RCSR &= ~I2Sx_RCSR_STOPE;

                                                      /* Disable DMA requests */
        i2sp->i2s->RCSR &= ~(I2Sx_RCSR_FWDE | I2Sx_RCSR_FRDE);

}





/**
 * @brief   Common TX IRQ handler.
 * @note    Tries hard to clear all the pending interrupt sources, we don't
 *          want to go through the whole ISR and have another interrupt soon
 *          after.
 *
 * @param[in] i2sp         pointer to an I2SDriver
 */
static void serve_tx_interrupt(I2SDriver *i2sp) {

  I2S_TypeDef *i2s = i2sp->i2s;
  /* Reset interrupt flag */

#if 0
  if (i2cp->errors != I2C_NO_ERROR)
    _i2c_wakeup_error_isr(i2cp);

  if (i2cp->intstate == STATE_STOP)
    _i2c_wakeup_isr(i2cp);
#endif
}

/**
 * @brief   Common RX IRQ handler.
 * @note    Tries hard to clear all the pending interrupt sources, we don't
 *          want to go through the whole ISR and have another interrupt soon
 *          after.
 *
 * @param[in] i2sp         pointer to an I2SDriver
 */
static void serve_rx_interrupt(I2SDriver *i2sp) {

  I2S_TypeDef *i2s = i2sp->i2s;

  if (i2sp->i2s->RCSR & I2Sx_RCSR_SEF) {
                                                          /* Clear Sync error */
      i2sp->i2s->RCSR |= I2Sx_RCSR_SEF;
  }

                                                            /* Buffer overrun */
  if (i2sp->i2s->RCSR & I2Sx_RCSR_FEF) {
                                                                /* Empty FIFO */

                                                                /* Reset FIFO */
      i2sp->i2s->RCSR |= I2Sx_RCSR_FR;
                                                          /* Clear FIFO error */
      i2sp->i2s->RCSR |= I2Sx_RCSR_FEF;
  }



#if 0
  if (i2cp->errors != I2C_NO_ERROR)
    _i2c_wakeup_error_isr(i2cp);

  if (i2cp->intstate == STATE_STOP)
    _i2c_wakeup_isr(i2cp);
#endif
}




/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/
#if KINETIS_I2S_USE_I2S0 || defined(__DOXYGEN__)

OSAL_IRQ_HANDLER(KINETIS_I2S0_TX_IRQ_VECTOR) {
  OSAL_IRQ_PROLOGUE();
  serve_tx_interrupt(&I2CD0);
  PORT_IRQ_EPILOGUE();
}

OSAL_IRQ_HANDLER(KINETIS_I2S0_RX_IRQ_VECTOR) {
  OSAL_IRQ_PROLOGUE();
  serve_rx_interrupt(&I2CD0);
  PORT_IRQ_EPILOGUE();
}


OSAL_IRQ_HANDLER(KINETIS_I2S0_TX_DMA_CHANNEL_IRQ_VECTOR) {
  OSAL_IRQ_PROLOGUE();
  serve_tx_dma_interrupt(&I2CD0);
  PORT_IRQ_EPILOGUE();
}

OSAL_IRQ_HANDLER(KINETIS_I2S0_RX_IRQ_VECTOR) {
  OSAL_IRQ_PROLOGUE();
  serve_rx_dma_interrupt(&I2CD0);
  PORT_IRQ_EPILOGUE();
}

#endif

#if KINETIS_I2C_USE_I2C1 || defined(__DOXYGEN__)

OSAL_IRQ_HANDLER(KINETIS_I2S1_TX_IRQ_VECTOR) {
  PORT_IRQ_PROLOGUE();
  serve_tx_interrupt(&I2CD1);
  PORT_IRQ_EPILOGUE();
}

OSAL_IRQ_HANDLER(KINETIS_I2S1_RX_IRQ_VECTOR) {
  PORT_IRQ_PROLOGUE();
  serve_rx_interrupt(&I2CD1);
  PORT_IRQ_EPILOGUE();
}

OSAL_IRQ_HANDLER(KINETIS_I2S1_TX_DMA_CHANNEL_IRQ_VECTOR) {
  OSAL_IRQ_PROLOGUE();
  serve_tx_dma_interrupt(&I2CD1);
  PORT_IRQ_EPILOGUE();
}

OSAL_IRQ_HANDLER(KINETIS_I2S1_RX_IRQ_VECTOR) {
  OSAL_IRQ_PROLOGUE();
  serve_rx_dma_interrupt(&I2CD1);
  PORT_IRQ_EPILOGUE();
}


#endif



/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level I2S driver initialization.
 *
 * @notapi
 */
void i2s_lld_init(void) {

#if PLATFORM_I2S_USE_I2S0
  i2sObjectInit(&I2SD0);
#endif


#if PLATFORM_I2S_USE_I2S1
  i2sObjectInit(&I2SD1);
#endif
}

/**
 * @brief   Configures and activates the I2S peripheral.
 *
 * @param[in] i2sp      pointer to the @p I2SDriver object
 *
 * @notapi
 */
void i2s_lld_start(I2SDriver *i2sp) {

    /* If in stopped state then enables the SPI and DMA clocks.*/
    if (i2sp->state == I2S_STOP) {
        int i2sIdx = -1;
        uint32_t srcAddr = NULL;
        uint32_t dstAddr = NULL;

#if PLATFORM_I2S_USE_I2S0
        if (&I2SD0 == i2sp) {
            i2sIdx  = I2S_INDEX_0;
            srcAddr = (unit32_t)&I2SD0->RDR;
            dstAddr = (unit32_t)&IS2D0->TDR;

            SIM->SCGC6 |= SIM_SCGC6_I2S0;
            nvicEnableVector(I2S0_TX_IRQn, KINETIS_I2S_IRQ_PRIORITY);
            nvicEnableVector(I2S0_RX_IRQn, KINETIS_I2S_IRQ_PRIORITY);
        }
#endif


#if PLATFORM_I2S_USE_I2S1
        if (&I2SD1 == i2sp) {
            i2sIdx = I2S_INDEX_1;
            srcAddr = (unit32_t)&I2SD1->RDR;
            dstAddr = (unit32_t)&IS2D1->TDR;

            SIM->SCGC3 |= SIM_SCGC3_I2S1;
            nvicEnableVector(I2S1_TX_IRQn, KINETIS_I2S_IRQ_PRIORITY);
            nvicEnableVector(I2S1_RX_IRQn, KINETIS_I2S_IRQ_PRIORITY);
        }
#endif


        chDbgAssert(i2sCtx != -1, "Invalid i2s instance");
        if (i2sCtx == -1) {
            return;
        }

        nvicEnableVector(DMA0_IRQn + i2sDmaResources[i2sIdx].rxDmaSource,
                                     i2sDmaResources[i2sIdx].rxDmaIrqPriority);

        nvicEnableVector(DMA0_IRQn + i2sDmaResources[i2sIdx].txDmaSource,
                                     i2sDmaResources[i2sIdx].txDmaIrqPriority);


        if (i2sDmaResources[i2sIdx].dmaMux == 1) {
            SIM->SCGC6 |= SIM_SCGC6_DMAMUX1;
        }
        else {
            SIM->SCGC6 |= SIM_SCGC6_DMAMUX;
        }
        SIM->SCGC7 |= SIM_SCGC7_DMA;

        /* Clear DMA error flags */
        DMA->ERR = 0x0F;

        /* Rx, select I2S Rx FIFO */
        DMAMUX->CHCFG[i2sDmaResources[i2sIdx].rxDmaMuxChannel]
                    = DMAMUX_CHCFGn_ENBL
                    | DMAMUX_CHCFGn_SOURCE(i2sDmaResources[i2sIdx].rxDmaSource);

        /* Tx, select I2S Tx FIFO */
        DMAMUX->CHCFG[i2sDmaResources[i2sIdx].txDmaMuxChannel]
                    = DMAMUX_CHCFGn_ENBL
                    | DMAMUX_CHCFGn_SOURCE(i2sDmaResources[i2sIdx].txDmaSource);

        /* DMA transfer size is 16 bits for a frame size > 8 bits */
        uint16_t dma_size;
        switch (I2S_WORD_SIZE) {
        case 8:
            dma_size = 0;
            break;
        case 16:
            dma_size = 1;
            break;
        case 32:
        default:
            dma_size = 2;
            break;
        }

        /* configure DMA RX fixed values */
        DMA->TCD[i2sDmaResources[i2sIdx].rxDmaChannel].SADDR    = srcAddr;
        DMA->TCD[i2sDmaResources[i2sIdx].rxDmaChannel].SOFF     = 0;
        DMA->TCD[i2sDmaResources[i2sIdx].rxDmaChannel].SLAST    = 0;
        DMA->TCD[i2sDmaResources[i2sIdx].rxDmaChannel].DLASTSGA = 0;
        DMA->TCD[i2sDmaResources[i2sIdx].rxDmaChannel].ATTR
                         =  DMA_ATTR_SSIZE(dma_size) | DMA_ATTR_DSIZE(dma_size);
        DMA->TCD[i2sDmaResources[i2sIdx].rxDmaChannel].NBYTES_MLNO
                                                                = I2S_WORD_SIZE;
        DMA->TCD[i2sDmaResources[i2sIdx].rxDmaChannel].CSR
                                    = DMA_CSR_DREQ_MASK | DMA_CSR_INTMAJOR_MASK;

        /* configure DMA TX fixed values */
        DMA->TCD[i2sDmaResources[i2sIdx].txDmaChannel].SLAST    = 0;
        DMA->TCD[i2sDmaResources[i2sIdx].txDmaChannel].DADDR    = dstAddr;
        DMA->TCD[i2sDmaResources[i2sIdx].txDmaChannel].DOFF     = 0;
        DMA->TCD[i2sDmaResources[i2sIdx].txDmaChannel].DLASTSGA = 0;
        DMA->TCD[i2sDmaResources[i2sIdx].txDmaChannel].ATTR
                          = DMA_ATTR_SSIZE(dma_size) | DMA_ATTR_DSIZE(dma_size);
        DMA->TCD[i2sDmaResources[i2sIdx].txDmaChannel].NBYTES_MLNO
                                                                = I2S_WORD_SIZE;
        DMA->TCD[i2sDmaResources[i2sIdx].txDmaChannel].CSR = DMA_CSR_DREQ_MASK;



#if 0
        /* Init transmitter */
        i2sp->i2s->TCSR = I2Sx_TCSR_FR | I2Sx_TCSR_SR;
        | I2Sx_TCSR_WSIE | I2Sx_TCSR_SEIE
            | I2Sx_TCSR_FEIE | I2Sx_TCSR_FWIE
            | I2Sx_TCSR_FRIE;
        i2sp->i2s->TCR1 =  I2Sx_TCR1_TFW(1); /* Tx Watermark 1 */
        i2sp->i2s->TCR2 =  I2Sx_TCR2_BCP; /* Active low, external bit clock */
        i2sp->i2s->TCR3 =  0; /* TX Channel disabled. */

        /* 32 word frame size.  MSB First.
         * Frame sync one bit before first bit.
         * Frame sync active high, external.
         */
        i2sp->i2s->TCR4 =  I2Sx_TCR4_FRSZ(31) | I2Sx_TCR4_MF
            | I2Sx_TCR4_FSE; //| I2Sx_TCR4_FSP;

        i2sp->i2s->TCR5 = I2Sx_TCR5_WNW(15)
            | I2Sx_TCR5_WOW(15)
            | I2Sx_TCR5_FBT(FIFO_MSB_FIRST_16BIT_WORDS_MSB);
#endif


        /* Init receiver */
                           /* SW and FIFO Resets.  Enable interrupt on error. */
        i2sp->i2s->RCSR = I2Sx_RCSR_FR | I2Sx_RCSR_SR
                                        | I2Sx_RCSR_FEIE;
        i2sp->i2s->RCR1 =  I2Sx_RCR1_TFW(3); /* Rx Watermark 3 */
        i2sp->i2s->RCR2 =  I2Sx_RCR2_BCP; /* Active low, external bit clock */
        i2sp->i2s->RCR3 =  I2Sx_RCR3_RCE(1); /* RX Mono channel enabled. */

        /* 32 word frame size.  MSB First.
         * Frame sync one bit before first bit.
         * Frame sync active high, external.
         */
        i2sp->i2s->RCR4 =  I2Sx_RCR4_FRSZ(I2S_FRAME_SIZE -1) | I2Sx_RCR4_MF
            | I2Sx_RCR4_FSE; //| I2Sx_RCR4_FSP;

        i2sp->i2s->RCR5 = I2Sx_RCR5_WNW(I2S_WORD_SIZE - 1)
            | I2Sx_RCR5_WOW(I2S_FRAME_SIZE - 1)
            | I2Sx_RCR5_FBT(I2S_FIFO_FBS);

                                                      /* Take out of SW reset */
        i2sp->i2s->RCSR &= ~I2Sx_RCSR_SR;

        /*
           do config shit and initstate.
           1. Setup clocking (Bus, audio master (if bit clk is output), bit clock)
           2. Setup Synchronization.
           3. Setup Frame Sync (frame size, word size).
           4. Setup FIFO data alignmnet.
           5. Setup interrupt and DMA req handlers:
           a. FIFO Data Ready.
           b. FIFO Warning.
           c. FIFO Error.
           d. Sync Error.
           e. Word Start.
           4. Enable SAI.

           Software reset:
           TX-Reset: resets all tx internal logic (bit clock generation, status flags,
           and FIFO pointers.)  Does not reste cfg registers.  Remains until cleared.
           RX-Reset: resets all rx internal logic (bit clock generation, status flags,
           and FIFO pointers.)  Does not reste cfg registers.  Remains until cleared.

           FIFO Reset:
           TX-Reset: synchronizes the FIFO write pointer to the same value as the FIFO
           read pointer.  This empties the the FIFO contents and is to be used after
           the Transmit FIFO Error Flag is set, and before the FIFO is re-initialized
           and the ERROR flag is cleared.  The FIFO Reset is asserted for one cycle
           only.

           RX-Reset: synchronizes the FIFO read pointer to the same value as the FIFO
           write pointer.  This empties the the FIFO contents and is to be used after
           the Recieve FIFO Error Flag is set and any remaining data has been read
           from the FIFO, and before the ERROR flag is cleared. The FIFO Reset is
           asserted for one cycle only.

           Supports TX-RX synchronization and other I2S synchronization.

           Frame Sync:  Used to indicate the start of each frame.  Can be configured:
           1. Externall generatedc or internally generated.
           2. Active high or low.
           3. Asserts with the first bit in frame or asserts one bit early.
           (but just a bit early...)
           4. Asserts for between 1 bit clock and first workd length.
           5. Frame lenght can be configured from 1 word per frame to 32 words per
           frame.
           6. Word length can be configured to support from 8bit to 32bits per word.
           First word lenth and remaining word lenghts can be configured separately.
           7. Can be configured for MSB first or LSB first.

           Data FIFO:
           Data alignment:
           Each tx or rx channel includes a FIFO of 8x32bit.  The FIFO
           data is accessed usign the SAI TX/RX data registers.  Data in the FIFO
           can be alinged anywhere within the 32-bit wide register through the use
           of the Fist Bit shifted configuration field, which select the bit index
           (between 31 and 0) of the first bit shifted.

           FIFO pointers:
           When writing to the tx data register (TDR), the wrie FIFO
           pointer increments after each valid write.  The SAI supports 8-bit and
           16-bit write to TDR for tx'ing 8-bit and 16-bit data respectively.
           Writes to the tx data register are ignored if the corresponding tx channel
           enable is clear or if the FIFO is full.  If the tx FIFO is empty, the
           transmit data register must be written at least three bit clocks before
           the starty of the next unmasked word to avoid a FIFO underrun.
           When reading the rx data register (RDR), the read FIFO pointer
           icrements after each valid read.  The SAI supports 8-bit and 16-bit reads
           from RDR for rx'ing 8 and 16-bit data respectively.  Reads form the RDR are
           ignored if the corresponding rx channel enable is clear or if the FIFO is
           empty.  If the rx FIFO is full, the rx data register must be read at least
           three bit clocks befor hte end of an unmasked work to avoid FIFO overrun.

           Word mask register: The SAI tx and rx each contain a word mask register
        that can be used to mask any word in the frame.  Sine the word mask
            register is double buffered, sw can update it before the end of each frame
            to mask a particular word in the next frame.  The tx word mask caused the
            tx data pin to be tri-stated for the lengh of each selected word and the tx
            FIFO is not read for masked words.  The rx word mask causes the rx data for
            each selected word to be discarded and not written to the rx FIFO.

            Interrupts and DMA requests:  The SAI tx and rx generate separate
            interrrupts and separate DMA requests, but support the same satus flags.
            Asych versions of the tx and rx interrupts are generated to waek up the
            CPU from stop mode.

            FIFO data ready flag:  (based on num entries in the FIFO and the watermark.
                    Can be used to generate an interrupt to a DMA request.

                    FIFO warning flag: Set based on the number of entries in the FIFO.
                    (Empty or full).   Can be used to generate an interrupt or DMA request.

                    FIFO error flag:
                    The tx FIFO error flag is set when any of the enabled FIFOs underflow.
                    After it is set, all enabled transmits channels repeat the last valid word
                    read from the tx FIFO until the error flag is cleared and the start of the
                    next tx frame.  All enabled tx FIFOs should be reset and iniitialized with
                    new data before the tx FIFO erro flag is cleared.
                    The rx FIFO error flag is set when any of the enabled rx FIFOS overflow.
                    After it is set, all enabled rx channels discard rx data until the rx FIFO
                    error flag is cleared and the start of the next rx frame.  All enabled
                    rx FIFOs should be emptied before the rx FIFO error flag is cleared.
                    The FIFO error flag can generate a interrupt only.

                    Sync error flag:
                    The sync error flag is set when configured for an externally generated
                    frame sync and the external frame sync asserts when the tx or rx is busy
                    with the previous frame.  The external fram sycn assertion is ignored and
                    the sync error flag is set.  The tx or rx continues checking for frame sync
                    assertion at the end of each fraem (or when idle) shen the sync error flag
                    is set.  The sync error flag can generate an interrupt only.

                    Word start flag:
                    The word start flag is set at the start of the second bit clock for
                    the selected word, as configured by the Word Flag register field.  Can
                    generate an interrupt only.





                    */
    }

}

/**
 * @brief   Deactivates the I2S peripheral.
 *
 * @param[in] i2sp      pointer to the @p I2SDriver object
 *
 * @notapi
 */
void i2s_lld_stop(I2SDriver *i2sp) {

    /* If in ready state then disables the I2S clock.*/
    if (i2sp->state == I2S_READY) {
        int i2sIdx = -1;


        i2sp->i2s->TCSR = I2Sx_TCSR_FR | I2Sx_TCSR_SR;
        i2sp->i2s->RCSR = I2Sx_RCSR_FR | I2Sx_RCSR_SR;


#if PLATFORM_I2S_USE_I2S0
        if (&I2SD0 == i2sp) {
            i2sIdx  = I2S_INDEX_0;
            SIM->SCGC6 &= ~SIM_SCGC6_I2S0;
            nvicDisableVector(I2S0_TX_IRQn);
            nvicDisableVector(I2S0_TX_IRQn);
        }
#endif



#if PLATFORM_I2S_USE_I2S1
        if (&I2SD1 == i2sp) {
            i2sIdx = I2S_INDEX_1;
            SIM->SCGC3 &= ~SIM_SCGC3_I2S1;
            nvicDisableVector(I2S1_TX_IRQn);
            nvicDisableVector(I2S1_TX_IRQn);
        }
#endif
        chDbgAssert(i2sCtx != -1, "Invalid i2s instance");
        if (i2sCtx == -1) {
            return;
        }

        nvicDisableVector(DMA0_IRQn + i2sDmaResources[i2sIdx].rxDmaSource);
        nvicDisableVector(DMA0_IRQn + i2sDmaResources[i2sIdx].txDmaSource);
        SIM->SCGC7 &= ~SIM_SCGC7_DMA;
        SIM->SCGC6 &= ~(SIM_SCGC6_DMAMUX | SIM_SCGC6_DMAMUX1);
    }
}

/**
 * @brief   Starts a I2S data exchange.
 *
 * @param[in] i2sp      pointer to the @p I2SDriver object
 * @param[in] n         number of words to be exchanged
 * @param[in] txbuf     the pointer to the transmit buffer
 * @param[out] rxbuf    the pointer to the receive buffer
 *

 *
 * @notapi
 */
void i2s_lld_start_exchange(I2SDriver *i2sp, size_t n,
                                             const void *txbuf, void *rxbuf) {
    i2sp->count = n;
    i2sp->rxbuf = rxbuf;
    i2sp->txbuf = txbuf;

    i2s_start_xfer(i2sp);
}

/**
 * @brief   Stops the ongoing data exchange.
 * @details The ongoing data exchange, if any, is stopped, if the driver
 *          was not active the function does nothing.
 *
 * @param[in] i2sp      pointer to the @p I2SDriver object
 *
 * @notapi
 */
void i2s_lld_stop_exchange(I2SDriver *i2sp) {

  (void)i2sp;
}

#endif /* HAL_USE_I2S */

/** @} */
