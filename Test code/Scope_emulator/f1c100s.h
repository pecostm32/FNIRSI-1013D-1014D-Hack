//----------------------------------------------------------------------------------------------------------------------------------

#ifndef F1C100S_H
#define F1C100S_H

//----------------------------------------------------------------------------------------------------------------------------------

#include "armv5tl.h"

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
//PIO controller register low addresses

#define PIO_CFG0                 0x00000000
#define PIO_CFG1                 0x00000004
#define PIO_CFG2                 0x00000008
#define PIO_CFG3                 0x0000000C
#define PIO_DATA                 0x00000010
#define PIO_DRV0                 0x00000014
#define PIO_DRV1                 0x00000018
#define PIO_PUL0                 0x0000001C
#define PIO_PUL1                 0x00000020

#define PIO_INT_CFG0             0x00000000
#define PIO_INT_CFG1             0x00000004
#define PIO_INT_CFG2             0x00000008
#define PIO_INT_CFG3             0x0000000C
#define PIO_INT_CTRL             0x00000010
#define PIO_INT_STA              0x00000014
#define PIO_INT_DEB              0x00000018

#define SDR_PAD_DRV              0x000002C0
#define SDR_PAD_PUL              0x000002C4

//----------------------------------------------------------------------------------------------------------------------------------
//Main process peripheral handling functions
void F1C100sProcess(PARMV5TL_CORE core);

void F1C100sProcessSPI0(PARMV5TL_CORE core);

//----------------------------------------------------------------------------------------------------------------------------------
//Reset functions
void F1C100sResetSPI0(PARMV5TL_CORE core);

//----------------------------------------------------------------------------------------------------------------------------------
//Memory map functions
void *F1C100sSram1(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);
void *F1C100sSram2(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);
void *F1C100sDDR(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);

//Clock control registers
void *F1C100sCCU(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);
void F1C100sCCURead(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);
void F1C100sCCUWrite(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);


//DRAM control registers
void *F1C100sDRAMC(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);
void F1C100sDRAMCRead(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);
void F1C100sDRAMCWrite(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);

//SPI control registers
void *F1C100sSPI0(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);
void F1C100sSPI0Read(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);
void F1C100sSPI0Write(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);

void *F1C100sSPI(F1C100S_SPI *registers, u_int32_t address, u_int32_t mode);
void F1C100sSPIRead(F1C100S_SPI *registers, u_int32_t address, u_int32_t mode);
void F1C100sSPIWrite(PARMV5TL_CORE core, F1C100S_SPI *registers, u_int32_t address, u_int32_t mode);

//PIO control registers
void *F1C100sPIO(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);
void *F1C100sPIOPort(F1C100S_PIO_PORT *registers, u_int32_t address, u_int32_t mode);
void *F1C100sPIOInt(F1C100S_PIO_INT *registers, u_int32_t address, u_int32_t mode);

//TCON registers
void *F1C100sTCON(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);
void F1C100sTCONRead(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);
void F1C100sTCONWrite(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);

//DEBE registers
void *F1C100sDEBE(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);
void F1C100sDEBERead(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);
void F1C100sDEBEWrite(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);

//Function for checking on the display frame buffer bounds after a write to DRAM
void F1C100sDisplayCheck(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode);

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* F1C100S_H */

