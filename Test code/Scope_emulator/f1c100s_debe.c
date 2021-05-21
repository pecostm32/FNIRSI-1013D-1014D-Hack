//----------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "f1c100s.h"
#include "f1c100s_debe.h"

//----------------------------------------------------------------------------------------------------------------------------------
//To connect the video system into the emulator the memory address where the frame buffer resides needs to be known
//core->f1c100s_debe.lay0_fb_addr1.m_32bit >> 3 gives the low part of the address
//core->f1c100s_debe.lay0_fb_addr2.m_32bit << 29 gives the upper three bits of the address

//core->f1c100s_debe.lay0_size holds the information about the screen dimensions
//bit 26:16 give the height minus 1
//bit 10:0  give the width minus 1

//For this system it is known that it is 800x480 pixels with 2 bytes per pixel 565 rgb color coding

//A function is needed that checks the writing to the dram on the frame buffer bounds to enable copying to the emulator screen

//Need a struct with data for display memory bounds

void F1C100sDisplayCheck(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  //Check if address in range of of the display frame buffer bounds
  
  //Need a function to send messages to the emulator with the address and the changed data. Based on the mode the data size needs to be set and used
  
  
  //Other option is to look into shared memory between the threads
  /*
   * 
  #define SHARED_MEMORY_KEY   0x32D5F90C

  //Setup a key for getting the shared memory
  key_t key = SHARED_MEMORY_KEY;
 
  //Get a handle to the shared memory
  int shmid = shmget(key,sizeof(RAWDATA),0666|IPC_CREAT); 

  //Check on error shmid == -1.
  if(shmid == -1)
  {
    cout << "Error " << errno << " getting shared memory: " << strerror (errno) << endl;
    return(-1);
  }
  
  //Attach to the shared memory
  PRAWDATA prawdata = (PRAWDATA)shmat(shmid,(void*)0,0);
   * 
    //detach from shared memory  
    shmdt(prawdata);   

    //destroy the shared memory 
    shmctl(shmid,IPC_RMID,NULL); 


   * In all parts it is the same setup
   * 
  //Setup a key for getting the shared memory
  key_t key = SHARED_MEMORY_KEY;
 
  //Get a handle to the shared memory
  int shmid = shmget(key,sizeof(RAWDATA),0666|IPC_CREAT); 

  //Check on error shmid == -1.
  if(shmid == -1)
  {
    cout << "Error: " << errno << " getting shared memory: " << strerror (errno) << endl;
    return(-1);
  }
  
  //Attach to the shared memory
  PRAWDATA prawdata = (PRAWDATA)shmat(shmid,(void*)0,0);
   * 
  //detach from shared memory  
  shmdt(prawdata);   

  //destroy the shared memory 
  shmctl(shmid,IPC_RMID,NULL); 
   * 
   */
}

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
    switch(mode)
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
  else
  {
    return(NULL); 
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//LCD timing control registers
void F1C100sDEBERead(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  F1C100S_MEMORY *ptr = NULL;
  
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
  F1C100S_MEMORY *ptr = NULL;
  
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
