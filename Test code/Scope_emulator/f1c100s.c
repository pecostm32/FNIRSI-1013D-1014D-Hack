//----------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "f1c100s.h"

//----------------------------------------------------------------------------------------------------------------------------------
//Main peripheral handling function. This function is called every cycle of the ARM core.
void F1C100sProcess(PARMV5TL_CORE core)
{
  //Perform tasks that are parallel to the cpu
  
  //Check if the cpu accessed a peripheral
  if(core->periph_targeted)
  {
    //Handle the last targeted address
    
    //Needs a similar system as in the main cpu for getting to the right peripheral
    
    //Clear it for next check
    core->periph_targeted = 0;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//Memory and peripheral handlers
void *F1C100sSram1(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  u_int32_t idx = address >> 2;
  
  switch(mode)
  {
    case ARM_MEMORY_WORD:
      //Return the word aligned data
      return(&core->sram1[idx].m_32bit);

    case ARM_MEMORY_SHORT:
      //Return the short aligned data
      return(&core->sram1[idx].m_16bit[(address & 2) >> 1]);
      
    case ARM_MEMORY_BYTE:
      //Return the byte aligned data
      return(&core->sram1[idx].m_8bit[address & 3]);
  }
}

void *F1C100sSram2(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  u_int32_t idx = address >> 2;
  
  switch(mode)
  {
    case ARM_MEMORY_WORD:
      //Return the word aligned data
      return(&core->sram2[idx].m_32bit);
      
    case ARM_MEMORY_SHORT:
      //Return the short aligned data
      return(&core->sram1[idx].m_16bit[(address & 2) >> 1]);
      
    case ARM_MEMORY_BYTE:
      //Return the byte aligned data
      return(&core->sram1[idx].m_8bit[address & 3]);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//Clock control registers
void *F1C100sCCU(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  F1C100S_MEMORY *ptr = NULL;
  
  //Select the target register based on word address
  switch(address & 0xFFFFFFFC)
  {
    case CCU_PLL_CPU_CTRL:
      ptr = &core->f1c100s_ccu.pll_cpu_ctrl;
      break;
      
    case CCU_PLL_AUDIO_CTRL:
      ptr = &core->f1c100s_ccu.pll_audio_ctrl;
      break;
      
    case CCU_PLL_VIDEO_CTRL:
      ptr = &core->f1c100s_ccu.pll_video_ctrl;
      break;
      
    case CCU_PLL_VE_CTRL:
      ptr = &core->f1c100s_ccu.pll_ve_ctrl;
      break;
      
    case CCU_PLL_DDR_CTRL:
      ptr = &core->f1c100s_ccu.pll_ddr_ctrl;
      break;
      
    case CCU_PLL_PERIPH_CTRL:
      ptr = &core->f1c100s_ccu.pll_periph_ctrl;
      break;
      
    case CCU_CPU_CLK_SRC:
      ptr = &core->f1c100s_ccu.cpu_clk_src;
      break;
      
    case CCU_AHB_APB_CFG:
      ptr = &core->f1c100s_ccu.ahb_apb_cfg;
      break;
      
    case CCU_BUS_CLK_GATE0:
      ptr = &core->f1c100s_ccu.bus_clk_gate0;
      break;
      
    case CCU_BUS_CLK_GATE1:
      ptr = &core->f1c100s_ccu.bus_clk_gate1;
      break;
      
    case CCU_BUS_CLK_GATE2:
      ptr = &core->f1c100s_ccu.bus_clk_gate2;
      break;

    case CCU_SDMMC0_CLK:
      ptr = &core->f1c100s_ccu.sdmmc0_clk;
      break;
      
    case CCU_SDMMC1_CLK:
      ptr = &core->f1c100s_ccu.sdmmc1_clk;
      break;
      
    case CCU_DAUDIO_CLK:
      ptr = &core->f1c100s_ccu.daudio_clk;
      break;
      
    case CCU_SPDIF_CLK:
      ptr = &core->f1c100s_ccu.spdif_clk;
      break;
      
    case CCU_I2S_CLK:
      ptr = &core->f1c100s_ccu.i2s_clk;
      break;
      
    case CCU_USBPHY_CFG:
      ptr = &core->f1c100s_ccu.usbphy_cfg;
      break;
      
    case CCU_DRAM_CLK_GATE:
      ptr = &core->f1c100s_ccu.dram_clk_gate;
      break;
      
    case CCU_DEBE_CLK:
      ptr = &core->f1c100s_ccu.debe_clk;
      break;
      
    case CCU_DEFE_CLK:
      ptr = &core->f1c100s_ccu.defe_clk;
      break;
      
    case CCU_LCD_CLK:
      ptr = &core->f1c100s_ccu.lcd_clk;
      break;
      
    case CCU_DEINTERLACE_CLK:
      ptr = &core->f1c100s_ccu.deinterlace_clk;
      break;
      
    case CCU_TVE_CLK:
      ptr = &core->f1c100s_ccu.tve_clk;
      break;
      
    case CCU_TVD_CLK:
      ptr = &core->f1c100s_ccu.tvd_clk;
      break;
      
    case CCU_CSI_CLK:
      ptr = &core->f1c100s_ccu.csi_clk;
      break;
      
    case CCU_VE_CLK:
      ptr = &core->f1c100s_ccu.ve_clk;
      break;
      
    case CCU_ADDA_CLK:
      ptr = &core->f1c100s_ccu.adda_clk;
      break;
      
    case CCU_AVS_CLK:
      ptr = &core->f1c100s_ccu.avs_clk;
      break;
      
    case CCU_PLL_STABLE_TIME0:
      ptr = &core->f1c100s_ccu.pll_stable_time0;
      break;
      
    case CCU_PLL_STABLE_TIME1:
      ptr = &core->f1c100s_ccu.pll_stable_time1;
      break;
      
    case CCU_PLL_CPU_BIAS:
      ptr = &core->f1c100s_ccu.pll_cpu_bias;
      break;
      
    case CCU_PLL_AUDIO_BIAS:
      ptr = &core->f1c100s_ccu.pll_audio_bias;
      break;
      
    case CCU_PLL_VIDEO_BIAS:
      ptr = &core->f1c100s_ccu.pll_video_bias;
      break;
      
    case CCU_PLL_VE_BIAS:
      ptr = &core->f1c100s_ccu.pll_ve_bias;
      break;
      
    case CCU_PLL_DDR0_BIAS:
      ptr = &core->f1c100s_ccu.pll_ddr0_bias;
      break;
      
    case CCU_PLL_PERIPH_BIAS:
      ptr = &core->f1c100s_ccu.pll_periph_bias;
      break;
      
    case CCU_PLL_CPU_TUN:
      ptr = &core->f1c100s_ccu.pll_cpu_tun;
      break;
      
    case CCU_PLL_DDR_TUN:
      ptr = &core->f1c100s_ccu.pll_ddr_tun;
      break;
      
    case CCU_PLL_AUDIO_PAT:
      ptr = &core->f1c100s_ccu.pll_audio_pat;
      break;
      
    case CCU_PLL_VIDEO_PAT:
      ptr = &core->f1c100s_ccu.pll_video_pat;
      break;
      
    case CCU_PLL_DDR0_PAT:
      ptr = &core->f1c100s_ccu.pll_ddr0_pat;
      break;
      
    case CCU_BUS_SOFT_RST0:
      ptr = &core->f1c100s_ccu.bus_soft_rst0;
      break;
      
    case CCU_BUS_SOFT_RST1:
      ptr = &core->f1c100s_ccu.bus_soft_rst1;
      break;
      
    case CCU_BUS_SOFT_RST2:
      ptr = &core->f1c100s_ccu.bus_soft_rst2;
      break;
  }

  //Check if valid address has been given
  if(ptr)
  {
    //Save the address for the peripheral handler
    core->last_periph_address = address;
    
    //Signal peripheral has been targeted
    core->periph_targeted = 1;
    
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
