//----------------------------------------------------------------------------------------------------------------------------------

#ifndef F1C100S_CCU_H
#define F1C100S_CCU_H

//----------------------------------------------------------------------------------------------------------------------------------
//CCU register low addresses
#define CCU_PLL_CPU_CTRL         0x00000000
#define CCU_PLL_AUDIO_CTRL       0x00000008
#define CCU_PLL_VIDEO_CTRL       0x00000010
#define CCU_PLL_VE_CTRL          0x00000018
#define CCU_PLL_DDR_CTRL         0x00000020
#define CCU_PLL_PERIPH_CTRL      0x00000028
#define CCU_CPU_CLK_SRC          0x00000050
#define CCU_AHB_APB_CFG          0x00000054

#define CCU_BUS_CLK_GATE0        0x00000060
#define CCU_BUS_CLK_GATE1        0x00000064
#define CCU_BUS_CLK_GATE2        0x00000068

#define CCU_SDMMC0_CLK           0x00000088
#define CCU_SDMMC1_CLK           0x0000008C
#define CCU_DAUDIO_CLK           0x000000B0
#define CCU_SPDIF_CLK            0x000000B4
#define CCU_I2S_CLK              0x000000B8
#define CCU_USBPHY_CFG           0x000000CC
#define CCU_DRAM_CLK_GATE        0x00000100
#define CCU_DEBE_CLK             0x00000104
#define CCU_DEFE_CLK             0x0000010C
#define CCU_LCD_CLK              0x00000118
#define CCU_DEINTERLACE_CLK      0x0000011C
#define CCU_TVE_CLK              0x00000120
#define CCU_TVD_CLK              0x00000124
#define CCU_CSI_CLK              0x00000134
#define CCU_VE_CLK               0x0000013C
#define CCU_ADDA_CLK             0x00000140
#define CCU_AVS_CLK              0x00000144

#define CCU_PLL_STABLE_TIME0     0x00000200
#define CCU_PLL_STABLE_TIME1     0x00000204
#define CCU_PLL_CPU_BIAS         0x00000220
#define CCU_PLL_AUDIO_BIAS       0x00000224
#define CCU_PLL_VIDEO_BIAS       0x00000228
#define CCU_PLL_VE_BIAS          0x0000022C
#define CCU_PLL_DDR0_BIAS        0x00000230
#define CCU_PLL_PERIPH_BIAS      0x00000234
#define CCU_PLL_CPU_TUN          0x00000250
#define CCU_PLL_DDR_TUN          0x00000260
#define CCU_PLL_AUDIO_PAT        0x00000284
#define CCU_PLL_VIDEO_PAT        0x00000288
#define CCU_PLL_DDR0_PAT         0x00000290

#define CCU_BUS_SOFT_RST0        0x000002C0
#define CCU_BUS_SOFT_RST1        0x000002C4
#define CCU_BUS_SOFT_RST2        0x000002D0

//----------------------------------------------------------------------------------------------------------------------------------
//Clock source selections
#define CPU_CLK_SRC_LOSC               0x00000000
#define CPU_CLK_SRC_OSC24M             0x00010000
#define CPU_CLK_SRC_PLL                0x00020000

//----------------------------------------------------------------------------------------------------------------------------------
//PLL enable
#define CCU_PLL_ENABLE                 0x80000000

//PLL locked flag
#define CCU_PLL_LOCKED                 0x10000000

//----------------------------------------------------------------------------------------------------------------------------------
//PLL CPU settings
//CPU frequency is based on (24MHz * N * K) / (M * P)
//Divider multiplier P
#define CCU_PLL_CPU_OUT_EXT_DIV_P_1    0x00000000
#define CCU_PLL_CPU_OUT_EXT_DIV_P_2    0x00010000
#define CCU_PLL_CPU_OUT_EXT_DIV_P_4    0x00020000

//multiply factor N (1 -- 32)
#define CCU_PLL_CPU_FACTOR_N(x)        (((x - 1) & 0x1F) << 8)

//multiply factor K (1 -- 4)
#define CCU_PLL_CPU_FACTOR_K(x)        (((x - 1) & 0x03) << 4)

//divide factor M (1 -- 4)
#define CCU_PLL_CPU_PREDIV_M(x)        ((x - 1) & 0x03)

//----------------------------------------------------------------------------------------------------------------------------------
//PLL VIDEO settings
#define CCU_PLL_VIDEO_MODE_AUTO        0x40000000
#define CCU_PLL_VIDEO_FRAC_CLK_OUT     0x02000000
#define CCU_PLL_VIDEO_MODE_SEL_INT     0x01000000
#define CCU_PLL_VIDEO_SDM_EN           0x00100000

//Video frequency is based on (24MHz * N) / M and must be between 30MHz and 600MHz
//multiply factor N (1 -- 128)
#define CCU_PLL_VIDEO_FACTOR_N(x)      (((x - 1) & 0x7F) << 8)

//divide factor M (1 -- 16)
#define CCU_PLL_VIDEO_PREDIV_M(x)      ((x - 1) & 0x0F)

//----------------------------------------------------------------------------------------------------------------------------------
//PLL PERIPH settings
#define CCU_PLL_PERIPH_24M_OUT_EN      0x00040000

//24M output clock post divider (when 25MHz crystal used)
#define CCU_PLL_PERIPH_24M_POST_DIV(x) (((x - 1) & 0x03) << 16)

//Peripheral frequency is based on 24MHz*N*K
//multiply factor N (1 -- 32)
#define CCU_PLL_PERIPH_FACTOR_N(x)      (((x - 1) & 0x1F) << 8)

//multiply factor K (1 -- 4)
#define CCU_PLL_PERIPH_FACTOR_K(x)      (((x - 1) & 0x03) << 4)

//divide factor M (1 -- 4) Only valid in plltest debug
#define CCU_PLL_PERIPH_PREDIV_M(x)      ((x - 1) & 0x03)

//----------------------------------------------------------------------------------------------------------------------------------
//AHB / APB / HCLCK settings
#define CCU_HCLKC_DIV_1                0x00000000
#define CCU_HCLKC_DIV_2                0x00010000
#define CCU_HCLKC_DIV_3                0x00020000
#define CCU_HCLKC_DIV_4                0x00030000

#define CCU_AHB_CLK_SRC_LOSC           0x00000000
#define CCU_AHB_CLK_SRC_OSC24M         0x00001000
#define CCU_AHB_CLK_SRC_CPUCLK         0x00002000
#define CCU_AHB_CLK_SRC_PLL_PERIPH     0x00003000

#define CCU_APB_CLK_RATIO_2            0x00000100
#define CCU_APB_CLK_RATIO_4            0x00000200
#define CCU_APB_CLK_RATIO_8            0x00000300

#define CCU_AHB_PRE_DIV_1              0x00000000
#define CCU_AHB_PRE_DIV_2              0x00000040
#define CCU_AHB_PRE_DIV_3              0x00000080
#define CCU_AHB_PRE_DIV_4              0x000000C0

#define CCU_AHB_CLK_DIV_RATIO_1        0x00000000
#define CCU_AHB_CLK_DIV_RATIO_2        0x00000010
#define CCU_AHB_CLK_DIV_RATIO_4        0x00000020

//----------------------------------------------------------------------------------------------------------------------------------
//DRAM gating settings
#define CCU_DRAM_BE_DCLK_GATING_PASS            0x04000000
#define CCU_DRAM_FE_DCLK_GATING_PASS            0x01000000
#define CCU_DRAM_TVD_DCLK_GATING_PASS           0x00000008
#define CCU_DRAM_DEINTERLACE_DCLK_GATING_PASS   0x00000004
#define CCU_DRAM_CSI_DCLK_GATING_PASS           0x00000002
#define CCU_DRAM_VE_DCLK_GATING_PASS            0x00000001

//----------------------------------------------------------------------------------------------------------------------------------
//Bus clock gating settings
#define CCU_BCGR0_SPI0_EN                       0x00100000


#define CCU_BCGR1_LCD_EN                        0x00000010

#define CCU_BCGR1_DEBE_EN                       0x00001000


//----------------------------------------------------------------------------------------------------------------------------------
//Bus software reset settings
#define CCU_BSRR0_SPI0_RST                      0x00100000


#define CCU_BSRR1_LCD_RST                       0x00000010

#define CCU_BSRR1_DEBE_RST                      0x00001000


//----------------------------------------------------------------------------------------------------------------------------------
//LCD clock settings
#define CCU_LCD_CLK_EN                          0x80000000

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* F1C100S_CCU_H */

