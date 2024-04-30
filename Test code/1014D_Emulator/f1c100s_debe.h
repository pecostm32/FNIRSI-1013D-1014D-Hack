//----------------------------------------------------------------------------------------------------------------------------------

#ifndef F1C100S_DEBE_H
#define F1C100S_DEBE_H

//----------------------------------------------------------------------------------------------------------------------------------
//Display engine back end register low addresses
#define DEBE_MODE_CTRL                 0x00000800
#define DEBE_COLOR_CTRL                0x00000804
#define DEBE_LAY_SIZE                  0x00000808
#define DEBE_LAY0_SIZE                 0x00000810
#define DEBE_LAY1_SIZE                 0x00000814
#define DEBE_LAY2_SIZE                 0x00000818
#define DEBE_LAY3_SIZE                 0x0000081C
#define DEBE_LAY0_CODNT                0x00000820
#define DEBE_LAY1_CODNT                0x00000824
#define DEBE_LAY2_CODNT                0x00000828
#define DEBE_LAY3_CODNT                0x0000082C
#define DEBE_LAY0_LINEWIDTH            0x00000840
#define DEBE_LAY1_LINEWIDTH            0x00000844
#define DEBE_LAY2_LINEWIDTH            0x00000848
#define DEBE_LAY3_LINEWIDTH            0x0000084C
#define DEBE_LAY0_FB_ADDR1             0x00000850
#define DEBE_LAY1_FB_ADDR1             0x00000854
#define DEBE_LAY2_FB_ADDR1             0x00000858
#define DEBE_LAY3_FB_ADDR1             0x0000085C
#define DEBE_LAY0_FB_ADDR2             0x00000860
#define DEBE_LAY1_FB_ADDR2             0x00000864
#define DEBE_LAY2_FB_ADDR2             0x00000868
#define DEBE_LAY3_FB_ADDR2             0x0000086C
#define DEBE_REGBUFF_CTRL              0x00000870
#define DEBE_CK_MAX                    0x00000880
#define DEBE_CK_MIN                    0x00000884
#define DEBE_CK_CFG                    0x00000888
#define DEBE_LAY0_ATT_CTRL0            0x00000890
#define DEBE_LAY1_ATT_CTRL0            0x00000894
#define DEBE_LAY2_ATT_CTRL0            0x00000898
#define DEBE_LAY3_ATT_CTRL0            0x0000089C
#define DEBE_LAY0_ATT_CTRL1            0x000008A0
#define DEBE_LAY1_ATT_CTRL1            0x000008A4
#define DEBE_LAY2_ATT_CTRL1            0x000008A8
#define DEBE_LAY3_ATT_CTRL1            0x000008AC
#define DEBE_HWC_CTRL                  0x000008D8
#define DEBE_HWCFB_CTRL                0x000008E0
#define DEBE_WB_CTRL                   0x000008F0
#define DEBE_WB_ADDR                   0x000008F4
#define DEBE_WB_LW                     0x000008F8
#define DEBE_IYUV_CH_CTRL              0x00000920
#define DEBE_CH0_YUV_FB_ADDR           0x00000930
#define DEBE_CH1_YUV_FB_ADDR           0x00000934
#define DEBE_CH2_YUV_FB_ADDR           0x00000938
#define DEBE_CH0_YUV_BLW               0x00000940
#define DEBE_CH1_YUV_BLW               0x00000944
#define DEBE_CH2_YUV_BLW               0x00000948
#define DEBE_COEF00                    0x00000950
#define DEBE_COEF01                    0x00000954
#define DEBE_COEF02                    0x00000958
#define DEBE_COEF03                    0x0000095C
#define DEBE_COEF10                    0x00000960
#define DEBE_COEF11                    0x00000964
#define DEBE_COEF12                    0x00000968
#define DEBE_COEF13                    0x0000096C
#define DEBE_COEF20                    0x00000970
#define DEBE_COEF21                    0x00000974
#define DEBE_COEF22                    0x00000978
#define DEBE_COEF23                    0x0000097C

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* F1C100S_DEBE_H */

