//----------------------------------------------------------------------------------------------------------------------------------

#ifndef F1C100S_TCON_H
#define F1C100S_TCON_H

//----------------------------------------------------------------------------------------------------------------------------------
//LCD timing control registers low addresses
#define TCON_CTRL                      0x00000000
#define TCON_INT0                      0x00000004
#define TCON_INT1                      0x00000008
#define TCON_FRM_CTRL                  0x00000010
#define TCON_FRM_SEED0_R               0x00000014
#define TCON_FRM_SEED0_G               0x00000018
#define TCON_FRM_SEED0_B               0x0000001C
#define TCON_FRM_SEED1_R               0x00000020
#define TCON_FRM_SEED1_G               0x00000024
#define TCON_FRM_SEED1_B               0x00000028
#define TCON_FRM_TBL0                  0x0000002C
#define TCON_FRM_TBL1                  0x00000030
#define TCON_FRM_TBL2                  0x00000034
#define TCON_FRM_TBL3                  0x00000038
#define TCON0_CTRL                     0x00000040
#define TCON_CLK_CTRL                  0x00000044
#define TCON0_BASIC_TIMING0            0x00000048
#define TCON0_BASIC_TIMING1            0x0000004C
#define TCON0_BASIC_TIMING2            0x00000050
#define TCON0_BASIC_TIMING3            0x00000054
#define TCON0_HV_TIMING                0x00000058
#define TCON0_CPU_IF                   0x00000060
#define TCON0_CPU_WR                   0x00000064
#define TCON0_CPU_RD                   0x00000068
#define TCON0_CPU_RD_NX                0x0000006C
#define TCON0_IO_CTRL0                 0x00000088
#define TCON0_IO_CTRL1                 0x0000008C
#define TCON1_CTRL                     0x00000090
#define TCON1_BASIC_TIMING0            0x00000094
#define TCON1_BASIC_TIMING1            0x00000098
#define TCON1_BASIC_TIMING2            0x0000009C
#define TCON1_BASIC_TIMING3            0x000000A0
#define TCON1_BASIC_TIMING4            0x000000A4
#define TCON1_BASIC_TIMING5            0x000000A8
#define TCON1_IO_CTRL0                 0x000000F0
#define TCON1_IO_CTRL1                 0x000000F4
#define TCON_DEBUG_INFO                0x000000FC

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* F1C100S_TCON_H */

