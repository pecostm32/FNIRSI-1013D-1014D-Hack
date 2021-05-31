//----------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "f1c100s.h"
#include "f1c100s_debe.h"

//----------------------------------------------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------------------------------------------
//LCD timing control registers
void *F1C100sDEBE(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  F1C100S_MEMORY *ptr = NULL;
  
  //Select the target register based on word address
  switch(address & 0x0000FFFC)
  {
    case DEBE_MODE_CTRL:
      ptr = &core->f1c100s_debe.mode_ctrl;
      break;
      
    case DEBE_COLOR_CTRL:
      ptr = &core->f1c100s_debe.color_ctrl;
      break;
      
    case DEBE_LAY_SIZE:
      ptr = &core->f1c100s_debe.lay_size;
      break;
      
    case DEBE_LAY0_SIZE:
      ptr = &core->f1c100s_debe.lay0_size;
      break;
      
    case DEBE_LAY1_SIZE:
      ptr = &core->f1c100s_debe.lay1_size;
      break;
      
    case DEBE_LAY2_SIZE:
      ptr = &core->f1c100s_debe.lay2_size;
      break;
      
    case DEBE_LAY3_SIZE:
      ptr = &core->f1c100s_debe.lay2_size;
      break;
      
    case DEBE_LAY0_CODNT:
      ptr = &core->f1c100s_debe.lay0_codnt;
      break;
      
    case DEBE_LAY1_CODNT:
      ptr = &core->f1c100s_debe.lay1_codnt;
      break;
      
    case DEBE_LAY2_CODNT:
      ptr = &core->f1c100s_debe.lay2_codnt;
      break;
      
    case DEBE_LAY3_CODNT:
      ptr = &core->f1c100s_debe.lay3_codnt;
      break;
      
    case DEBE_LAY0_LINEWIDTH:
      ptr = &core->f1c100s_debe.lay0_linewidth;
      break;
      
    case DEBE_LAY1_LINEWIDTH:
      ptr = &core->f1c100s_debe.lay1_linewidth;
      break;
      
    case DEBE_LAY2_LINEWIDTH:
      ptr = &core->f1c100s_debe.lay2_linewidth;
      break;
      
    case DEBE_LAY3_LINEWIDTH:
      ptr = &core->f1c100s_debe.lay3_linewidth;
      break;
      
    case DEBE_LAY0_FB_ADDR1:
      ptr = &core->f1c100s_debe.lay0_fb_addr1;
      break;
      
    case DEBE_LAY1_FB_ADDR1:
      ptr = &core->f1c100s_debe.lay1_fb_addr1;
      break;
      
    case DEBE_LAY2_FB_ADDR1:
      ptr = &core->f1c100s_debe.lay2_fb_addr1;
      break;
      
    case DEBE_LAY3_FB_ADDR1:
      ptr = &core->f1c100s_debe.lay3_fb_addr1;
      break;
      
    case DEBE_LAY0_FB_ADDR2:
      ptr = &core->f1c100s_debe.lay0_fb_addr2;
      break;
      
    case DEBE_LAY1_FB_ADDR2:
      ptr = &core->f1c100s_debe.lay1_fb_addr2;
      break;
      
    case DEBE_LAY2_FB_ADDR2:
      ptr = &core->f1c100s_debe.lay2_fb_addr2;
      break;
      
    case DEBE_LAY3_FB_ADDR2:
      ptr = &core->f1c100s_debe.lay3_fb_addr2;
      break;
      
    case DEBE_REGBUFF_CTRL:
      ptr = &core->f1c100s_debe.regbuff_ctrl;
      break;
      
    case DEBE_CK_MAX:
      ptr = &core->f1c100s_debe.ck_max;
      break;
      
    case DEBE_CK_MIN:
      ptr = &core->f1c100s_debe.ck_min;
      break;
      
    case DEBE_CK_CFG:
      ptr = &core->f1c100s_debe.ck_cfg;
      break;
      
    case DEBE_LAY0_ATT_CTRL0:
      ptr = &core->f1c100s_debe.lay0_att_ctrl0;
      break;
      
    case DEBE_LAY1_ATT_CTRL0:
      ptr = &core->f1c100s_debe.lay1_att_ctrl0;
      break;
      
    case DEBE_LAY2_ATT_CTRL0:
      ptr = &core->f1c100s_debe.lay2_att_ctrl0;
      break;
      
    case DEBE_LAY3_ATT_CTRL0:
      ptr = &core->f1c100s_debe.lay3_att_ctrl0;
      break;
      
    case DEBE_LAY0_ATT_CTRL1:
      ptr = &core->f1c100s_debe.lay0_att_ctrl1;
      break;
      
    case DEBE_LAY1_ATT_CTRL1:
      ptr = &core->f1c100s_debe.lay1_att_ctrl1;
      break;
      
    case DEBE_LAY2_ATT_CTRL1:
      ptr = &core->f1c100s_debe.lay2_att_ctrl1;
      break;
      
    case DEBE_LAY3_ATT_CTRL1:
      ptr = &core->f1c100s_debe.lay3_att_ctrl1;
      break;
      
    case DEBE_HWC_CTRL:
      ptr = &core->f1c100s_debe.hwc_ctrl;
      break;
      
    case DEBE_HWCFB_CTRL:
      ptr = &core->f1c100s_debe.hwcfb_ctrl;
      break;
      
    case DEBE_WB_CTRL:
      ptr = &core->f1c100s_debe.wb_ctrl;
      break;
      
    case DEBE_WB_ADDR:
      ptr = &core->f1c100s_debe.wb_addr;
      break;
      
    case DEBE_WB_LW:
      ptr = &core->f1c100s_debe.wb_lw;
      break;
      
    case DEBE_IYUV_CH_CTRL:
      ptr = &core->f1c100s_debe.iyuv_ch_ctrl;
      break;
      
    case DEBE_CH0_YUV_FB_ADDR:
      ptr = &core->f1c100s_debe.ch0_yuv_fb_addr;
      break;
      
    case DEBE_CH1_YUV_FB_ADDR:
      ptr = &core->f1c100s_debe.ch1_yuv_fb_addr;
      break;
      
    case DEBE_CH2_YUV_FB_ADDR:
      ptr = &core->f1c100s_debe.ch2_yuv_fb_addr;
      break;
      
    case DEBE_CH0_YUV_BLW:
      ptr = &core->f1c100s_debe.ch0_yuv_blw;
      break;
      
    case DEBE_CH1_YUV_BLW:
      ptr = &core->f1c100s_debe.ch1_yuv_blw;
      break;
      
    case DEBE_CH2_YUV_BLW:
      ptr = &core->f1c100s_debe.ch2_yuv_blw;
      break;
      
    case DEBE_COEF00:
      ptr = &core->f1c100s_debe.coef00;
      break;
      
    case DEBE_COEF01:
      ptr = &core->f1c100s_debe.coef01;
      break;
      
    case DEBE_COEF02:
      ptr = &core->f1c100s_debe.coef02;
      break;
      
    case DEBE_COEF03:
      ptr = &core->f1c100s_debe.coef03;
      break;
      
    case DEBE_COEF10:
      ptr = &core->f1c100s_debe.coef10;
      break;
      
    case DEBE_COEF11:
      ptr = &core->f1c100s_debe.coef11;
      break;
      
    case DEBE_COEF12:
      ptr = &core->f1c100s_debe.coef12;
      break;
      
    case DEBE_COEF13:
      ptr = &core->f1c100s_debe.coef13;
      break;
      
    case DEBE_COEF20:
      ptr = &core->f1c100s_debe.coef20;
      break;
      
    case DEBE_COEF21:
      ptr = &core->f1c100s_debe.coef21;
      break;
      
    case DEBE_COEF22:
      ptr = &core->f1c100s_debe.coef22;
      break;
      
    case DEBE_COEF23:
      ptr = &core->f1c100s_debe.coef23;
      break;
  }

  //Check if valid address has been given
  if(ptr)
  {
    //Return the pointer based on the requested mode
    switch(mode & ARM_MEMORY_MASK)
    {
      case ARM_MEMORY_WORD:
        //Return the word aligned data
        return(&ptr->m_32bit);

      case ARM_MEMORY_SHORT:
        //Return the short aligned data
        return(&ptr->m_16bit[(address & 2) >> 1]);

      case ARM_MEMORY_BYTE:
        //Return the byte aligned data
        return(&ptr->m_8bit[address & 3]);
    }
  }
  
  return(NULL); 
}

//----------------------------------------------------------------------------------------------------------------------------------
//LCD timing control registers
void F1C100sDEBERead(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  //Select the target register based on word address
  switch(address & 0x00000FFC)
  {
    case DEBE_MODE_CTRL:
      break;
      
    case DEBE_COLOR_CTRL:
      break;
      
    case DEBE_LAY_SIZE:
      break;
      
    case DEBE_LAY0_SIZE:
      break;
      
    case DEBE_LAY1_SIZE:
      break;
      
    case DEBE_LAY2_SIZE:
      break;
      
    case DEBE_LAY3_SIZE:
      break;
      
    case DEBE_LAY0_CODNT:
      break;
      
    case DEBE_LAY1_CODNT:
      break;
      
    case DEBE_LAY2_CODNT:
      break;
      
    case DEBE_LAY3_CODNT:
      break;
      
    case DEBE_LAY0_LINEWIDTH:
      break;
      
    case DEBE_LAY1_LINEWIDTH:
      break;
      
    case DEBE_LAY2_LINEWIDTH:
      break;
      
    case DEBE_LAY3_LINEWIDTH:
      break;

    case DEBE_LAY0_FB_ADDR1:
      break;
      
    case DEBE_LAY1_FB_ADDR1:
      break;
      
    case DEBE_LAY2_FB_ADDR1:
      break;
      
    case DEBE_LAY3_FB_ADDR1:
      break;
      
    case DEBE_LAY0_FB_ADDR2:
      break;
      
    case DEBE_LAY1_FB_ADDR2:
      break;
      
    case DEBE_LAY2_FB_ADDR2:
      break;
      
    case DEBE_LAY3_FB_ADDR2:
      break;
      
    case DEBE_REGBUFF_CTRL:
      break;
      
    case DEBE_CK_MAX:
      break;
      
    case DEBE_CK_MIN:
      break;
      
    case DEBE_CK_CFG:
      break;
      
    case DEBE_LAY0_ATT_CTRL0:
      break;
      
    case DEBE_LAY1_ATT_CTRL0:
      break;
      
    case DEBE_LAY2_ATT_CTRL0:
      break;
      
    case DEBE_LAY3_ATT_CTRL0:
      break;
      
    case DEBE_LAY0_ATT_CTRL1:
      break;
      
    case DEBE_LAY1_ATT_CTRL1:
      break;
      
    case DEBE_LAY2_ATT_CTRL1:
      break;
      
    case DEBE_LAY3_ATT_CTRL1:
      break;
      
    case DEBE_HWC_CTRL:
      break;
      
    case DEBE_HWCFB_CTRL:
      break;
      
    case DEBE_WB_CTRL:
      break;
      
    case DEBE_WB_ADDR:
      break;
      
    case DEBE_WB_LW:
      break;
      
    case DEBE_IYUV_CH_CTRL:
      break;
      
    case DEBE_CH0_YUV_FB_ADDR:
      break;
      
    case DEBE_CH1_YUV_FB_ADDR:
      break;
      
    case DEBE_CH2_YUV_FB_ADDR:
      break;
      
    case DEBE_CH0_YUV_BLW:
      break;
      
    case DEBE_CH1_YUV_BLW:
      break;
      
    case DEBE_CH2_YUV_BLW:
      break;
      
    case DEBE_COEF00:
      break;
      
    case DEBE_COEF01:
      break;
      
    case DEBE_COEF02:
      break;
      
    case DEBE_COEF03:
      break;
      
    case DEBE_COEF10:
      break;
      
    case DEBE_COEF11:
      break;
      
    case DEBE_COEF12:
      break;
      
    case DEBE_COEF13:
      break;
      
    case DEBE_COEF20:
      break;
      
    case DEBE_COEF21:
      break;
      
    case DEBE_COEF22:
      break;
      
    case DEBE_COEF23:
      break;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//LCD timing control registers
void F1C100sDEBEWrite(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  //Select the target register based on word address
  switch(address & 0x00000FFC)
  {
    case DEBE_MODE_CTRL:
      break;
      
    case DEBE_COLOR_CTRL:
      break;
      
    case DEBE_LAY_SIZE:
      break;
      
    case DEBE_LAY0_SIZE:
      //Setup part of the display memory based on written data
      core->displaymemory.xsize = (core->f1c100s_debe.lay0_size.m_32bit & 0x07FF) + 1;
      core->displaymemory.ysize = ((core->f1c100s_debe.lay0_size.m_32bit >> 16) & 0x07FF) + 1;
      break;
      
    case DEBE_LAY1_SIZE:
      break;
      
    case DEBE_LAY2_SIZE:
      break;
      
    case DEBE_LAY3_SIZE:
      break;
      
    case DEBE_LAY0_CODNT:
      break;
      
    case DEBE_LAY1_CODNT:
      break;
      
    case DEBE_LAY2_CODNT:
      break;
      
    case DEBE_LAY3_CODNT:
      break;
      
    case DEBE_LAY0_LINEWIDTH:
      core->displaymemory.linewidth = core->f1c100s_debe.lay0_linewidth.m_32bit >> 3;
      break;
      
    case DEBE_LAY1_LINEWIDTH:
      break;
      
    case DEBE_LAY2_LINEWIDTH:
      break;
      
    case DEBE_LAY3_LINEWIDTH:
      break;
      
    case DEBE_LAY0_FB_ADDR1:
      //The dram array is 4 bytes per word and the information set in this register is a bit address so divide by 32 to get the actual index
      core->displaymemory.startaddress = core->f1c100s_debe.lay0_fb_addr1.m_32bit >> 5;
      break;
      
    case DEBE_LAY1_FB_ADDR1:
      break;
      
    case DEBE_LAY2_FB_ADDR1:
      break;
      
    case DEBE_LAY3_FB_ADDR1:
      break;
      
    case DEBE_LAY0_FB_ADDR2:
      break;
      
    case DEBE_LAY1_FB_ADDR2:
      break;
      
    case DEBE_LAY2_FB_ADDR2:
      break;
      
    case DEBE_LAY3_FB_ADDR2:
      break;
      
    case DEBE_REGBUFF_CTRL:
      break;
      
    case DEBE_CK_MAX:
      break;
      
    case DEBE_CK_MIN:
      break;
      
    case DEBE_CK_CFG:
      break;
      
    case DEBE_LAY0_ATT_CTRL0:
      break;
      
    case DEBE_LAY1_ATT_CTRL0:
      break;
      
    case DEBE_LAY2_ATT_CTRL0:
      break;
      
    case DEBE_LAY3_ATT_CTRL0:
      break;
      
    case DEBE_LAY0_ATT_CTRL1:
      break;
      
    case DEBE_LAY1_ATT_CTRL1:
      break;
      
    case DEBE_LAY2_ATT_CTRL1:
      break;
      
    case DEBE_LAY3_ATT_CTRL1:
      break;
      
    case DEBE_HWC_CTRL:
      break;
      
    case DEBE_HWCFB_CTRL:
      break;
      
    case DEBE_WB_CTRL:
      break;
      
    case DEBE_WB_ADDR:
      break;
      
    case DEBE_WB_LW:
      break;
      
    case DEBE_IYUV_CH_CTRL:
      break;
      
    case DEBE_CH0_YUV_FB_ADDR:
      break;
      
    case DEBE_CH1_YUV_FB_ADDR:
      break;
      
    case DEBE_CH2_YUV_FB_ADDR:
      break;
      
    case DEBE_CH0_YUV_BLW:
      break;
      
    case DEBE_CH1_YUV_BLW:
      break;
      
    case DEBE_CH2_YUV_BLW:
      break;
      
    case DEBE_COEF00:
      break;
      
    case DEBE_COEF01:
      break;
      
    case DEBE_COEF02:
      break;
      
    case DEBE_COEF03:
      break;
      
    case DEBE_COEF10:
      break;
      
    case DEBE_COEF11:
      break;
      
    case DEBE_COEF12:
      break;
      
    case DEBE_COEF13:
      break;
      
    case DEBE_COEF20:
      break;
      
    case DEBE_COEF21:
      break;
      
    case DEBE_COEF22:
      break;
      
    case DEBE_COEF23:
      break;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
