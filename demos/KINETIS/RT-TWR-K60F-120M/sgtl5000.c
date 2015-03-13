typedef struct {
    uint16_t id;                    /* 0x0000 */
    uint16_t digPower;              /* 0x0002 */
    uint16_t clkCtrl;               /* 0x0004 */
    uint16_t i2SCtrl;               /* 0x0006 */
    uint16_t reserved;              /* 0x0008 */
    uint16_t sssCtrl;               /* 0x000A */
    uint16_t reserved1;             /* 0x000C */
    uint16_t adcDacCtrl;            /* 0x000E */
    uint16_t dacVol;                /* 0x0010 */
    uint16_t reserved2;             /* 0x0012 */
    uint16_t padStrength;           /* 0x0014 */
    uint16_t reserved3[5];          /* 0x0016 - 0x001E */
    uint16_t anaAdcCtrl;            /* 0x0020 */
    uint16_t anaHpCtrl;             /* 0x0022 */
    uint16_t anaCtrl;               /* 0x0024 */
    uint16_t linregCtrl;            /* 0x0026 */
    uint16_t refCtrl;               /* 0x0028 */
    uint16_t micCtrl;               /* 0x002A */
    uint16_t lineOutCtrl;           /* 0x002C */
    uint16_t linOutVol;             /* 0x002E */
    uint16_t anaPower;              /* 0x0030 */
    uint16_t pllCtrl;               /* 0x0032 */
    uint16_t clkTopCtrl;            /* 0x0034 */
    uint16_t anaStatus;             /* 0x0036 */
    uint16_t anaTest1;              /* 0x0038 */
    uint16_t anaTest2;              /* 0x003A */
    uint16_t shortCtlr;             /* 0x003C */
    uint16_t reserved4[97];
    uint16_t dapCtrl;               /* 0x0100 */
    uint16_t dapPeq;                /* 0x0102 */
    uint16_t dapBassEnhance;        /* 0x0104 */
    uint16_t dapBassEnhanceCtrl;    /* 0x0106 */
    uint16_t dapAudioEq;            /* 0x0108 */
    uint16_t dapSgtlSurround;       /* 0x010A */
    uint16_t dapFilterCoeffAccess;  /* 0x010C */
    uint16_t dapCoeffWR_B0_MSB;     /* 0x010E */
    uint16_t dapCoeffWR_B0_LSB;     /* 0x0110 */
    uint16_t reserved5[2];
    uint16_t dapAudioEqBassBand0;   /* 0x0116 */
    uint16_t dapAudioEqBand1;       /* 0x0118 */
    uint16_t dapAudioEqBand2;       /* 0x011A */
    uint16_t dapAudioEqBand3;       /* 0x011C */
    uint16_t dapAudioEqBand4;       /* 0x011E */
    uint16_t dapMainChan;           /* 0x0120 */
    uint16_t dapMixChan;            /* 0x0122 */
    uint16_t dapAvcCtrl;            /* 0x0124 */
    uint16_t dapAvcThreshold;       /* 0x0126 */
    uint16_t dapAvtAttack;          /* 0x0128 */
    uint16_t dapAvcDecay;           /* 0x012A */
    uint16_t dapCoeffWR_B1_MSB;     /* 0x012C */
    uint16_t dapCoeffWR_B1_LSB;     /* 0x012E */
    uint16_t dapCoeffWR_B2_MSB;     /* 0x0130 */
    uint16_t dapCoeffWR_B2_LSB;     /* 0x0132 */
    uint16_t dapCoeffWR_A1_MSB;     /* 0x0134 */
    uint16_t dapCoeffWR_A1_LSB;     /* 0x0136 */
    uint16_t dapCoeffWR_A2_MSB;     /* 0x0138 */
    uint16_t dapCoeffWR_A2_LSB;     /* 0x013A */
};









