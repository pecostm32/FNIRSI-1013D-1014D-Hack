//----------------------------------------------------------------------------------------------------------------------------------

#ifndef F1C100S_H
#define F1C100S_H

//----------------------------------------------------------------------------------------------------------------------------------

#include "armv5tl.h"

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
//Main process peripheral handling function
void F1C100sProcess(PARMV5TL_CORE core);

//----------------------------------------------------------------------------------------------------------------------------------
//Memory map functions
void *F1C100sSram1(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);
void *F1C100sSram2(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);

//Clock control registers
void *F1C100sCCU(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* F1C100S_H */

