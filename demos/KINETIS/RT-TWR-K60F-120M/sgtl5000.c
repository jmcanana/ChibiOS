#define REG_CHIP_ID                       0x0000
#define REG_CHIP_DIG_POWER                0x0002
#define REG_CHIP_CLK_CTRL                 0x0004
#define REG_CHIP_I2S_CTRL                 0x0006
#define REG_CHIP_SSS_CTRL                 0x000A
#define REG_CHIP_ADCDAC_CTRL              0x000E
#define REG_CHIP_DAC_VOL                  0x0010
#define REG_CHIP_PAD_STRENGTH             0x0014
#define REG_CHIP_ANA_ADC_CTRL             0x0020
#define REG_CHIP_ANA_HP_CTRL              0x0022
#define REG_CHIP_ANA_CTRL                 0x0024
#define REG_CHIP_LINREG_CTRL              0x0026
#define REG_CHIP_REF_CTRL                 0x0028
#define REG_CHIP_MIC_CTRL                 0x002A
#define REG_CHIP_LINE_OUT_CTRL            0x002C
#define REG_CHIP_LINE_OUT_VOL             0x002E
#define REG_CHIP_ANA_POWER                0x0030
#define REG_CHIP_PLL_CTRL                 0x0032
#define REG_CHIP_CLK_TOP_CTRL             0x0034
#define REG_CHIP_ANA_STATUS               0x0036
#define REG_CHIP_ANA_TEST1                0x0038
#define REG_CHIP_ANA_TEST2                0x003A
#define REG_CHIP_SHORT_CTRL               0x003C
#define REG_DAP_CONTROL                   0x0100
#define REG_DAP_PEQ                       0x0102
#define REG_DAP_BASS_ENHANCE              0x0104
#define REG_DAP_BASS_ENHANCE_CTRL         0x0106
#define REG_DAP_AUDIO_EQ                  0x0108
#define REG_DAP_SGTL_SURROUND             0x010A
#define REG_DAP_FILTER_COEF_ACCESS        0x010C
#define REG_DAP_COEF_WR_B0_MSB            0x010E
#define REG_DAP_COEF_WR_B0_LSB            0x0110
#define REG_DAP_AUDIO_EQ_BASS_BAND0       0x0116  /* 115 Hz  */
#define REG_DAP_AUDIO_EQ_BAND1            0x0118  /* 330 Hz  */
#define REG_DAP_AUDIO_EQ_BAND2            0x011A  /* 990 Hz  */
#define REG_DAP_AUDIO_EQ_BAND3            0x011C  /* 3000 Hz */
#define REG_DAP_AUDIO_EQ_TREBLE_BAND4     0x011E  /* 9900 Hz */
#define REG_DAP_MAIN_CHAN                 0x0120
#define REG_DAP_MIX_CHAN                  0x0122
#define REG_DAP_AVC_CTRL                  0x0124
#define REG_DAP_AVC_THRESHOLD             0x0126
#define REG_DAP_AVC_ATTACK                0x0128
#define REG_DAP_AVC_DECAY                 0x012A
#define REG_DAP_COEF_WR_B1_MSB            0x012C
#define REG_DAP_COEF_WR_B1_LSB            0x012E
#define REG_DAP_COEF_WR_B2_MSB            0x0130
#define REG_DAP_COEF_WR_B2_LSB            0x0132
#define REG_DAP_COEF_WR_A1_MSB            0x0134
#define REG_DAP_COEF_WR_A1_LSB            0x0136
#define REG_DAP_COEF_WR_A2_MSB            0x0138
#define REG_DAP_COEF_WR_A2_LSB            0x013A


#if 0

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
#endif

/* REG_CHIP_CLK_CTRL */
#define RATE_MODE_MASK     0x3
#define RATE_MODE_SHIFT    4


#define SYS_FS_MASK     0x3
#define SYS_FS_SHIFT    2

#define MCLK_FREQ_MASK  0x3
#define MCLK_FREQ_SHIFT 0
enum {
    RATE_MODE_SYS_FS       = 0 << 4,
    RATE_MODE_SYS_0_5_FS   = 1 << 4,
    RATE_MODE_SYS_0_125_FS = 2 << 4,
    RATE_MODE_SYS_0_166_FS = 3 << 4,

    SYS_FS_32KHZ    = 0 << 2,
    SYS_FS_44_1KHZ  = 1 << 2,
    SYS_FS_48KHZ    = 2 << 2,
    SYS_FS_96KHZ    = 3 << 2,

    MCLK_FREQ_256_FS  = 0 << 0,
    MCLK_FREQ_384_FS  = 1 << 0,
    MCLK_FREQ_512_FS  = 2 << 0,
    MCLK_FREQ_USE_PLL = 3 << 0,

};

/* REG_CHIP_I2S_CTRL */
#define DLEN_MASK  0x3
#define DLEN_SHIFT 4

#define I2S_MODE_MASK 0x3
#define I2S_MODE_SHIFT 2
enum {
    SCLKFREQ        = 1 << 8,
    I2S_MS          = 1 << 7,
    SCLK_INV        = 1 << 6,

    DLEN_32BIT      = 0 << 4,
    DLEN_24BIT      = 1 << 4,
    DLEN_20BIT      = 2 << 4,
    DLEN_16BIT      = 3 << 4,

    I2S_MODE_LEFT   = 0 << 2,
    I2S_MODE_RIGHT  = 1 << 2,
    I2S_MODE_PCM    = 2 << 2,

    LRALIGN         = 1 << 1,
    LRPOL           = 1 << 0,
};


/* REG_CHIP_SSS_CTRL */
#define DAP_MIX_SELECT_MASK  0x3
#define DAP_MIX_SELECT_SHIFT   8

#define DAP_SELECT_MASK  0x3
#define DAP_SELECT_SHIFT   6

#define DAC_SELECT_MASK  0x3
#define DAC_SELECT_SHIFT   4

#define I2S_SELECT_MASK  0x3
#define I2S_SELECT_SHIFT   0

enum {
    DAP_MIX_LRSWAP  = 1 << 14,
    DAP_LRSWAP      = 1 << 13,
    DAC_LRSWAP      = 1 << 12,

    I2S_LRSWAP      = 1 << 10,

    DAP_MIX_SELECT_I2S_IN   = 1 << 8,
    DAP_MIX_SELECT_ADC      = 0 << 8,

    DAP_SELECT_I2S_IN       = 1 << 6,
    DAP_SELECT_ADC          = 0 << 6,

    DAC_SELECT_DAP          = 3 << 4,
    DAC_SELECT_I2S_IN       = 1 << 4,
    DAC_SELECT_ADC          = 0 << 4,

    I2S_SELECT_DAP          = 3 << 0,
    I2S_SELECT_I2S_IN       = 1 << 0,
    I2S_SELECT_ADC          = 0 << 0,
};

/* REG_CHIP_DIG_POWER */
enum {
    ADC_POWERUP     = 1 << 6,
    DAC_POWERUP     = 1 << 5,
    DAP_POWERUP     = 1 << 4,

    I2S_OUT_POWERUP = 1 << 1,
    I2S_IN_POWERUP  = 1 << 0,
};

/* REG_CHIP_ANA_CTRL */
enum {
    MUTE_LO    = 1 << 8,

    SELECT_HP  = 1 << 6,
    EN_ZCD_HP  = 1 << 5,
    MUTE_HP    = 1 << 4,

    SELECT_ADC = 1 << 2,
    EN_ZCD_ADC = 1 << 1,
    MUTE_ADC   = 1 << 0,
}

/* REG_CHIP_ANA_POWER */
enum {
    DAC_MONO                  = 1 << 14,
    LINREG_SIMPLE_POWERUP     = 1 << 13,
    STARTUP_POWERUP           = 1 << 12,
    VDDC_CHRGPMP_POWERUP      = 1 << 11,
    PLL_POWERUP               = 1 << 10,
    LINREG_D_POWERUP          = 1 << 9,
    VCOAMP_POWERUP            = 1 << 8,
    VAG_POWERUP               = 1 << 7,
    ADC_MONO                  = 1 << 6,
    REFTOP_POWERUP            = 1 << 5,
    HEADPHONE_POWERUP         = 1 << 4,
    DAC_POWERUP               = 1 << 3,
    CAPLESS_HEADPHONE_POWERUP = 1 << 2,
    ADC_POWERUP               = 1 << 1,
    LINEOUT_POWERUP           = 1 << 0,
};

/* REG_CHIP_PLL_CTRL */
#define INT_DIVISOR_MASK  0xF8
#define INT_DIVISOR_SHIFT 11

#define FRAC_DIVISOR_MASK  0x7FF
#define FRAC_DIVISOR_SHIFT 0

/* REG_CHIP_CLK_TOP_CTRL */
enum {
    ENABLE_INT_OSC  = 1 << 11,
    INPUT_FREQ_DIV2 = 1 << 3,
};

/* REG_CHIP_LINREG_CTRL */
enum {
    VDDC_MAN_ASSN  =  1 << 6,
    VDDC_ASSN_OVRD =  1 << 5,
};

#define D_PROGRAMMING_MASK 0xF
#define D_PROGRAMMING_SHFT 0
enum {
    D_PROGRAMMING_0_85 = 0xF,
    D_PROGRAMMING_0_90 = 0xE,
    D_PROGRAMMING_0_95 = 0xD,
    D_PROGRAMMING_1_00 = 0xC,
    D_PROGRAMMING_1_05 = 0xB,
    D_PROGRAMMING_1_10 = 0xA,
    D_PROGRAMMING_1_15 = 0x9,
    D_PROGRAMMING_1_20 = 0x8,
    D_PROGRAMMING_1_25 = 0x7,
    D_PROGRAMMING_1_30 = 0x6,
    D_PROGRAMMING_1_35 = 0x5,
    D_PROGRAMMING_1_40 = 0x4,
    D_PROGRAMMING_1_45 = 0x3,
    D_PROGRAMMING_1_50 = 0x2,
    D_PROGRAMMING_1_55 = 0x1,
    D_PROGRAMMING_1_60 = 0x0,
};


/* REG_CHIP_REF_CTRL */
#define BIAS_CTRL_MASK  0xF
#define BIAS_CTRL_SHIFT 1

enum {
   BIAS_CTRL_MINUS_50_0_PCT  = 0x007,
   BIAS_CTRL_MINUS_37_5_PCT  = 0x006,
   BIAS_CTRL_MINUS_25_0_PCT  = 0x005,
   BIAS_CTRL_MINUS_12_5_PCT  = 0x004,
   BIAS_CTRL_PLUS_12_5_PCT   = 0x003,

   BIAS_CTRL_NOMINAL         = 0x000,

   SMALL_POP                 = 0x001,
};

#define VAG_VAL_MASK 0x1F
#define VAG_VAL_SHIFT 4
static int calcVagVal(int VDDAmv)
{
    int vagVal = VDDAmv /= 2;

    LIMIT_VAL(vagVal, 800, 1575);
    vagVal = 0x1F - (1575 - vagVal) / 25;
    vagVal = (vagVal & VAG_VAL_MASK) << VAG_VAL_SHIFT;
    return (vagVal);
}

/* REG_CHIP_LINE_OUT_CTRL */
#define OUT_CURRENT_MASK  0XF
#define OUT_CURRENT_SHIFT 8

enum {
    OUT_CURRENT_0_54_MA     = 0xF << 8,
    OUT_CURRENT_0_45_MA     = 0x7 << 8,
    OUT_CURRENT_0_36_MA     = 0x3 << 8,
    OUT_CURRENT_0_27_MA     = 0x1 << 8,
    OUT_CURRENT_0_18_MA     = 0x0 << 8,
};

#define LO_VAGCNTRL_MASK 0x3F
#define LO_VAGCNTRL_SHIFT 0
static int calcLoVagVal(int VDDIOmv)
{
    int vagVal = VDDIOmv /= 2;

    LIMIT_VAL(vagVal, 800, 1675);
    vagVal = 0x23 - (1675 - vagVal) / 25;
    vagVal = (vagVal & LO_VAGCNTRL_MASK) << LO_VAGCNTRL_SHIFT;
    return (vagVal);
}

/* REG_CHIP_LINE_OUT_VOL */

#define LO_VOL_X_MASK 0x1F
#define LO_VOL_LEFT_SHIFT  0
#define LO_VOL_RIGHT_SHIFT 8
static int calcLoVol(int VDDIOmv, int VDDAmv)
{
    int value = (int) (40 * log((VDDAmv / 2.0) / (VDDIOmv / 2.0)) + 15);

    return value;
}

/* REG_CHIP_SHORT_CTRL */
#define LVLADJR_MASK  0x7
#define LVLADJR_SHIFT  12

#define LVLADJL_MASK 0x7
#define LVLADJL_SHIFT  8

#define LVLADJC_MASK 0x7
#define LVLADJC_SHIFT  4

#define MODE_LR_MASK 0x3
#define MODE_LR_SHIFT  2

#define MODE_CM_MASK 0x3
#define MODE_CM_SHIFT  0

enum {
    LVLADJR_200   = 0x7 << 12,
    LVLADJR_175   = 0x6 << 12,
    LVLADJR_150   = 0x5 << 12,
    LVLADJR_125   = 0x4 << 12,
    LVLADJR_100   = 0x0 << 12,
    LVLADJR_75    = 0x1 << 12,
    LVLADJR_50    = 0x2 << 12,
    LVLADJR_25    = 0x3 << 12,

    LVLADJL_200   = 0x7 <<  8,
    LVLADJL_175   = 0x6 <<  8,
    LVLADJL_150   = 0x5 <<  8,
    LVLADJL_125   = 0x4 <<  8,
    LVLADJL_100   = 0x0 <<  8,
    LVLADJL_75    = 0x1 <<  8,
    LVLADJL_50    = 0x2 <<  8,
    LVLADJL_25    = 0x3 <<  8,

    LVLADJC_400   = 0x7 <<  4,
    LVLADJC_350   = 0x6 <<  4,
    LVLADJC_300   = 0x5 <<  4,
    LVLADJC_250   = 0x4 <<  4,
    LVLADJC_200   = 0x0 <<  4,
    LVLADJC_150   = 0x1 <<  4,
    LVLADJC_100   = 0x2 <<  4,
    LVLADJC_50    = 0x3 <<  4,

    MODE_LR_SHORT_DETECT_ENABLE                 = 0x3 << 2,
    MODE_LR_SHORT_DETECT_ENABLE_WITH_RESET      = 0x1 << 2,
    MODE_LR_SHORT_DETECT_DISABLE                = 0x0,

    MODE_CM_SHORT_DETECT_ENABLE                 = 0x3,
    MODE_CM_SHORT_DETECT_ENABLE_WITH_AUTO_RESET = 0x2,
    MODE_CM_SHORT_DETECT_ENABLE_WITH_RESET      = 0x1,
    MODE_CM_SHORT_DETECT_DISABLE                = 0x0,
};



    static int calcLvlAdjr(int shortValMv)
{
    int lvlAdjr;



}



static void regModify( uint16_t reg, uint16_t clearBits, uint16_t setBits)
{
    uint16_t data;

    regRead(reg, &data);
    data &= ~clearBits;
    data |=    setBits;

    regWrite(reg, data);
}

static void sgtlInit(void)
{

                /* --------------- Power Supply Configuration---------------- */
#if defined(EXTERNAL_VDDD)
    regModify(REG_CHIP_ANA_POWER, STARTUP_POWERUP | LINREG_SIMPLE_POWERUP, 0);
#endif

#if defined(VDDA_AND_VDDIO_LT_3_1V)
    regModify(REG_CHIP_CLK_TOP_CTRL, 0, ENABLE_INT_OSC);
    regModify(REG_CHIP_ANA_POWER, 0, VDDC_CHRGPMP_POWERUP);
#endif


#if defined(VDDA_AND_VDDIO_GT_3_1V)
    regModify(REG_CHIP_LINREG_CTRL,
                           D_PROGRAMMING_MASK << D_PROGRAMMING_SHFT,
                           D_PROGRAMMING_1_60 | VDDC_MAN_ASSN | VDDC_ASSN_OVRD);
#endif


         /* ------ Reference Voltage and Bias Current Configuration---------- */
    osalDbgAssert( VDDA_MV >= 1600 && VDDA_MV <= 3150 ,   "invalid VDDA_MV");
    regModify(REG_CHIP_REF_CTRL,
          (BIAS_CTRL_MASK << BIAS_CTRL_SHIFT) | (VAG_VAL_MASK << VAG_VAL_SHIFT),
           BIAS_CTRL_NOMINAL | calcVagVal(VDDA_MV));

    osalDbgAssert( VDDIO_MV >= 1600 && VDDIO_MV <= 3350 ,   "invalid VDDIO_MV");
    regModify(REG_CHIP_LINE_OUT_CTRL, (OUT_CURRENT_MASK << OUT_CURRENT_SHIFT)
                                    | (LO_VAGCNTRL_MASK << LO_VAGCNTRL_SHIFT),
                                  OUT_CURRENT_0_36_MA | calcLoVagVal(VDDIO_MV));

       /* ----------------Other Analog Block Configurations------------------ */

                                              /* Slow ramp up to minimize pop */
    regModify(REG_CHIP_REF_CTRL,   0, SMALL_POP);
                                          /* Short detect mode for headphones */
    regModify(REG_CHIP_SHORT_CTRL, (LVLADJR_MASK << LVLADJR_SHIFT)
                                 | (LVLADJL_MASK << LVLADJL_SHIFT)
                                 | (LVLADJC_MASK << LVLADJC_SHIFT)
                                 | (MODE_LR_MASK << MODE_LR_SHIFT)
                                 | (MODE_CM_MASK << MODE_CM_SHIFT),
                                     LVLADJR_75 | LVLADJL_75
                                   | MODE_CM_SHORT_DETECT_ENABLE_WITH_AUTO_RESET
                                   | MODE_LR_SHORT_DETECT_ENABLE_WITH_RESET );

                            /* Zero-cross for headphones out (HP_OUT) and ADC */
    regModify(REG_CHIP_ANA_CTRL,   0, EN_ZCD_HP | EN_ZCD_ADC);

       /* ----------------Power up Inputs/Outputs/Digital Blocks------------- */

                                            /* Power up LINEOUT, HP, ADC, DAC */
    regModify(REG_CHIP_ANA_POWER, 0, LINREG_SIMPLE_POWERUP
                                   | VAG_POWERUP
                                   | HEADPHONE_POWERUP
                                   | DAC_POWERUP
                                   | CAPLESS_HEADPHONE_POWERUP
                                   | ADC_POWERUP
                                   | LINEOUT_POWERUP);

                                           /* Power up desired digital blocks */
    regModify(REG_CHIP_DIG_POWER,   0, ADC_POWERUP
                                     | DAC_POWERUP
                                     | DAP_POWERUP
                                     | I2S_OUT_POWERUP
                                     | I2S_IN_POWERUP);


       /* --------------------Set LINEOUT Volume Level----------------------- */

    data  = calcLoVol(VDDIO_MV, VDDA_MV);
    regModify(REG_CHIP_LINE_OUT_VOL,
                                   (LO_VOL_X_MASK << LO_VOL_RIGHT_SHIFT)
                                 | (LO_VOL_X_MASK << LO_VOL_LEFT_SHIFT),
                                   (data & LO_VOL_X_MASK) << LO_VOL_RIGHT_SHIFT
                                 | (data & LO_VOL_X_MASK) << LO_VOL_LEFT_SHIFT);


       /* --------------------System MCLK and Sample Clock-------------------- */
                                                            /* SYS_FS @ 48kHz */
#define SYS_FS 48000000
    regModify(REG_CHIP_CLK_CTRL,
                           RATE_MODE_MASK << RATE_MODE_SHIFT, RATE_MODE_SYS_FS);
    regModify(REG_CHIP_CLK_CTRL, SYS_FS_MASK << SYS_FS_SHIFT, SYS_FS_48KHZ);

                                                        /* MCLK_FREQ @ 256*Fs */
    regModify(REG_CHIP_CLK_CTRL,
                           MCLK_FREQ_MASK << MCLK_FREQ_SHIFT, MCLK_FREQ_256_FS);

                           /* Configure the I2S clocks in master mode.
                            * NOTE: I2S LRCLK is same as the system sample clock.
                            *
                            * Use 16Bit resolution.
                            *
                            */
     regModify(REG_CHIP_I2S_CTRL, (DLEN_MASK << DLEN_SHIFT),
                                   DLEN_16BIT | I2S_MS);


       /* --------------------PLL Configuration          -------------------- */
                                                      /* Scale external clock */
    uint32_t sysMCLK;
    if (SYS_MCLK > 17000000) {
        sysMCLK = SYS_MCLK / 2;
        regModify(REG_CHIP_CLK_TOP_CTRL, 0, INPUT_FREQ_DIV2);
    }
    else {
        sysMCLK = SYS_MCLK;
    }

                                                                 /* Scale PLL */
    uint32_t pllOutputFreq;
    if (SYS_FS == 44100000) {
        pllOutputFreq = 180633600000;
    }
    else {
        pllOutputFreq = 196608000000;
    }

    uint32_t intDivisor  =   pllOutputFreq / sysMCLK;
    uint32_t fracDivisor = ((pllOutputFreq / sysMCLK) - intDivisor) * 2048;

    regModify(REG_CHIP_PLL_CTRL,   0xFFFF,
                       (intDivisor  & INT_DIVISOR_MASK)  << INT_DIVISOR_SHIFT
                    || (fracDivisor & FRAC_DIVISOR_MASK) << FRAC_DIVISOR_SHIFT);

                                                              /* Power up PLL */
    regModify(REG_CHIP_ANA_POWER, 0, PLL_POWERUP);
    regModify(REG_CHIP_ANA_POWER, 0, VCOAMP_POWERUP);




         /* --------------Input Routing: MIC_IN_ -> ADC -> I2S_OUT -----------*/
                                                   /* Set ADC input to MIC_IN */
    regModify(REG_CHIP_ANA_CTRL, SELECT_ADC, 0);
                                                      /* Route ADC to I2S_OUT */
    regModify(REG_CHIP_SSS_CTRL, I2S_SELECT_MASK << I2S_SELECT_SHIFT,
                                 I2S_SELECT_ADC);

}

