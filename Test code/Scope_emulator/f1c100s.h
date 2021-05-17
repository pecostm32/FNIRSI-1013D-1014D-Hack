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
//DRAM controller registers low addresses
#define DRAM_SCONR               0x00000000
#define DRAM_STMG0R              0x00000004
#define DRAM_STMG1R              0x00000008
#define DRAM_SCTLR               0x0000000C
#define DRAM_SREFR               0x00000010
#define DRAM_SEXTMR              0x00000014
#define DRAM_DDLYR               0x00000024
#define DRAM_DADRR               0x00000028
#define DRAM_DVALR               0x0000002C
#define DRAM_DRPTR0              0x00000030
#define DRAM_DRPTR1              0x00000034
#define DRAM_DRPTR2              0x00000038
#define DRAM_DRPTR3              0x0000003C
#define DRAM_SEFR                0x00000040
#define DRAM_MAE                 0x00000044
#define DRAM_ASPR                0x00000048
#define DRAM_SDLY0               0x0000004C
#define DRAM_SDLY1               0x00000050
#define DRAM_SDLY2               0x00000054
#define DRAM_MCR0                0x00000100
#define DRAM_MCR1                0x00000104
#define DRAM_MCR2                0x00000108
#define DRAM_MCR3                0x0000010C
#define DRAM_MCR4                0x00000110
#define DRAM_MCR5                0x00000114
#define DRAM_MCR6                0x00000118
#define DRAM_MCR7                0x0000011C
#define DRAM_MCR8                0x00000120
#define DRAM_MCR9                0x00000124
#define DRAM_MCR10               0x00000128
#define DRAM_MCR11               0x0000012C
#define DRAM_BWCR                0x00000140

//----------------------------------------------------------------------------------------------------------------------------------
//SPI controller register low addresses
#define SPI_GCR                  0x01C05004
#define SPI_TCR                  0x01C05008
#define SPI_IER                  0x01C05010
#define SPI_ISR                  0x01C05014
#define SPI_FCR                  0x01C05018
#define SPI_FSR                  0x01C0501C
#define SPI_WCR                  0x01C05020
#define SPI_CCR                  0x01C05024
#define SPI_MBC                  0x01C05030
#define SPI_MTC                  0x01C05034
#define SPI_BCC                  0x01C05038
#define SPI_TXD                  0x01C05200
#define SPI_RXD                  0x01C05300

//----------------------------------------------------------------------------------------------------------------------------------
//Main process peripheral handling function
void F1C100sProcess(PARMV5TL_CORE core);

//----------------------------------------------------------------------------------------------------------------------------------
//Memory map functions
void *F1C100sSram1(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);
void *F1C100sSram2(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);
void *F1C100sDDR(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);

//Clock control registers
void *F1C100sCCU(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);
void F1C100sCCURead(PARMV5TL_CORE core, u_int32_t address);
void F1C100sCCUWrite(PARMV5TL_CORE core, u_int32_t address);


//DRAM control registers
void *F1C100sDRAMC(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);
void F1C100sDRAMCRead(PARMV5TL_CORE core, u_int32_t address);
void F1C100sDRAMCWrite(PARMV5TL_CORE core, u_int32_t address);

//SPI control registers
void *F1C100sSPI0(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);
void F1C100sSPI0Read(PARMV5TL_CORE core, u_int32_t address);
void F1C100sSPI0Write(PARMV5TL_CORE core, u_int32_t address);

void *F1C100sSPI(F1C100S_SPI *registers, u_int32_t address, u_int32_t mode);
void F1C100sSPIRead(F1C100S_SPI *registers, u_int32_t address);
void F1C100sSPIWrite(F1C100S_SPI *registers, u_int32_t address);

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* F1C100S_H */

