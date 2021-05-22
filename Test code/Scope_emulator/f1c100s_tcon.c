//----------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "f1c100s.h"
#include "f1c100s_tcon.h"

#include "scopeemulator.h"

//----------------------------------------------------------------------------------------------------------------------------------
//Processing of the LCD timing
void F1C100sProcessTCON(PARMV5TL_CORE core)
{
  //Check if device enabled
  if(core->f1c100s_tcon.ctrl.m_32bit & TCON_CTRL_MODULE_EN)
  {
    if((core->cpu_cycles - core->displaymemory.prevcycles) > core->displaymemory.numcycles)
    {
      //Signal main window to update the display
      updatedisplaymessage();
      
      //Setup for next delay
      core->displaymemory.prevcycles = core->cpu_cycles;
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//LCD timing control registers
void *F1C100sTCON(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  F1C100S_MEMORY *ptr = NULL;
  
  //Select the target register based on word address
  switch(address & 0x00000FFC)
  {
    case TCON_CTRL:
      ptr = &core->f1c100s_tcon.ctrl;
      break;
      
    case TCON_INT0:
      ptr = &core->f1c100s_tcon.int0;
      break;
      
    case TCON_INT1:
      ptr = &core->f1c100s_tcon.int1;
      break;
      
    case TCON_FRM_CTRL:
      ptr = &core->f1c100s_tcon.frm_ctrl;
      break;
      
    case TCON_FRM_SEED0_R:
      ptr = &core->f1c100s_tcon.frm_seed0_r;
      break;
      
    case TCON_FRM_SEED0_G:
      ptr = &core->f1c100s_tcon.frm_seed0_g;
      break;
      
    case TCON_FRM_SEED0_B:
      ptr = &core->f1c100s_tcon.frm_seed0_b;
      break;
      
    case TCON_FRM_SEED1_R:
      ptr = &core->f1c100s_tcon.frm_seed1_r;
      break;
      
    case TCON_FRM_SEED1_G:
      ptr = &core->f1c100s_tcon.frm_seed1_g;
      break;
      
    case TCON_FRM_SEED1_B:
      ptr = &core->f1c100s_tcon.frm_seed1_b;
      break;
      
    case TCON_FRM_TBL0:
      ptr = &core->f1c100s_tcon.frm_tbl0;
      break;
      
    case TCON_FRM_TBL1:
      ptr = &core->f1c100s_tcon.frm_tbl1;
      break;
      
    case TCON_FRM_TBL2:
      ptr = &core->f1c100s_tcon.frm_tbl2;
      break;
      
    case TCON_FRM_TBL3:
      ptr = &core->f1c100s_tcon.frm_tbl3;
      break;
      
    case TCON0_CTRL:
      ptr = &core->f1c100s_tcon.tcon0_ctrl;
      break;
      
    case TCON_CLK_CTRL:
      ptr = &core->f1c100s_tcon.clk_ctrl;
      break;
      
    case TCON0_BASIC_TIMING0:
      ptr = &core->f1c100s_tcon.tcon0_basic_timing0;
      break;
      
    case TCON0_BASIC_TIMING1:
      ptr = &core->f1c100s_tcon.tcon0_basic_timing1;
      break;
      
    case TCON0_BASIC_TIMING2:
      ptr = &core->f1c100s_tcon.tcon0_basic_timing2;
      break;
      
    case TCON0_BASIC_TIMING3:
      ptr = &core->f1c100s_tcon.tcon0_basic_timing3;
      break;
      
    case TCON0_HV_TIMING:
      ptr = &core->f1c100s_tcon.tcon0_hv_timing;
      break;
      
    case TCON0_CPU_IF:
      ptr = &core->f1c100s_tcon.tcon0_cpu_if;
      break;
      
    case TCON0_CPU_WR:
      ptr = &core->f1c100s_tcon.tcon0_cpu_wr;
      break;
      
    case TCON0_CPU_RD:
      ptr = &core->f1c100s_tcon.tcon0_cpu_rd;
      break;
      
    case TCON0_CPU_RD_NX:
      ptr = &core->f1c100s_tcon.tcon0_cpu_rd_nx;
      break;
      
    case TCON0_IO_CTRL0:
      ptr = &core->f1c100s_tcon.tcon0_io_ctrl0;
      break;
      
    case TCON0_IO_CTRL1:
      ptr = &core->f1c100s_tcon.tcon0_io_ctrl1;
      break;
      
    case TCON1_CTRL:
      ptr = &core->f1c100s_tcon.tcon1_ctrl;
      break;
      
    case TCON1_BASIC_TIMING0:
      ptr = &core->f1c100s_tcon.tcon1_basic_timing0;
      break;
      
    case TCON1_BASIC_TIMING1:
      ptr = &core->f1c100s_tcon.tcon1_basic_timing1;
      break;
      
    case TCON1_BASIC_TIMING2:
      ptr = &core->f1c100s_tcon.tcon1_basic_timing2;
      break;
      
    case TCON1_BASIC_TIMING3:
      ptr = &core->f1c100s_tcon.tcon1_basic_timing3;
      break;
      
    case TCON1_BASIC_TIMING4:
      ptr = &core->f1c100s_tcon.tcon1_basic_timing4;
      break;
      
    case TCON1_BASIC_TIMING5:
      ptr = &core->f1c100s_tcon.tcon1_basic_timing5;
      break;
      
    case TCON1_IO_CTRL0:
      ptr = &core->f1c100s_tcon.tcon1_io_ctrl0;
      break;
      
    case TCON1_IO_CTRL1:
      ptr = &core->f1c100s_tcon.tcon1_io_ctrl1;
      break;
      
    case TCON_DEBUG_INFO:
      ptr = &core->f1c100s_tcon.debug_info;
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
//LCD timing control registers read function
void F1C100sTCONRead(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  //Select the target register based on word address
  switch(address & 0x000003FC)
  {
    case TCON_CTRL:
      break;
      
    case TCON_INT0:
      break;
      
    case TCON_INT1:
      break;
      
    case TCON_FRM_CTRL:
      break;
      
    case TCON_FRM_SEED0_R:
      break;
      
    case TCON_FRM_SEED0_G:
      break;
      
    case TCON_FRM_SEED0_B:
      break;
      
    case TCON_FRM_SEED1_R:
      break;
      
    case TCON_FRM_SEED1_G:
      break;
      
    case TCON_FRM_SEED1_B:
      break;
      
    case TCON_FRM_TBL0:
      break;
      
    case TCON_FRM_TBL1:
      break;
      
    case TCON_FRM_TBL2:
      break;
      
    case TCON_FRM_TBL3:
      break;
      
    case TCON0_CTRL:
      break;
      
    case TCON_CLK_CTRL:
      break;
      
    case TCON0_BASIC_TIMING0:
      break;
      
    case TCON0_BASIC_TIMING1:
      break;
      
    case TCON0_BASIC_TIMING2:
      break;
      
    case TCON0_BASIC_TIMING3:
      break;
      
    case TCON0_HV_TIMING:
      break;
      
    case TCON0_CPU_IF:
      break;
      
    case TCON0_CPU_WR:
      break;
      
    case TCON0_CPU_RD:
      break;
      
    case TCON0_CPU_RD_NX:
      break;
      
    case TCON0_IO_CTRL0:
      break;
      
    case TCON0_IO_CTRL1:
      break;
      
    case TCON1_CTRL:
      break;
      
    case TCON1_BASIC_TIMING0:
      break;
      
    case TCON1_BASIC_TIMING1:
      break;
      
    case TCON1_BASIC_TIMING2:
      break;
      
    case TCON1_BASIC_TIMING3:
      break;
      
    case TCON1_BASIC_TIMING4:
      break;
      
    case TCON1_BASIC_TIMING5:
      break;
      
    case TCON1_IO_CTRL0:
      break;
      
    case TCON1_IO_CTRL1:
      break;
      
    case TCON_DEBUG_INFO:
      break;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//LCD timing control registers write function
void F1C100sTCONWrite(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  //Select the target register based on word address
  switch(address & 0x000003FC)
  {
    case TCON_CTRL:
      break;
      
    case TCON_INT0:
      break;
      
    case TCON_INT1:
      break;
      
    case TCON_FRM_CTRL:
      break;
      
    case TCON_FRM_SEED0_R:
      break;
      
    case TCON_FRM_SEED0_G:
      break;
      
    case TCON_FRM_SEED0_B:
      break;
      
    case TCON_FRM_SEED1_R:
      break;
      
    case TCON_FRM_SEED1_G:
      break;
      
    case TCON_FRM_SEED1_B:
      break;
      
    case TCON_FRM_TBL0:
      break;
      
    case TCON_FRM_TBL1:
      break;
      
    case TCON_FRM_TBL2:
      break;
      
    case TCON_FRM_TBL3:
      break;
      
    case TCON0_CTRL:
      break;
      
    case TCON_CLK_CTRL:
      break;
      
    case TCON0_BASIC_TIMING0:
      break;
      
    case TCON0_BASIC_TIMING1:
      //Gives line time.
      core->displaymemory.linetime = ((core->f1c100s_tcon.tcon0_basic_timing1.m_32bit >> 16) & 0x0FFF) * 10;
      
      //Check if verticaltime already set
      if(core->displaymemory.verticaltime)
        core->displaymemory.numcycles = core->displaymemory.linetime * core->displaymemory.verticaltime;
      break;
      
    case TCON0_BASIC_TIMING2:
      //Gives vertical front porch and back porch time in line times
      core->displaymemory.verticaltime = ((core->f1c100s_tcon.tcon0_basic_timing2.m_32bit >> 16) & 0x0FFF) + (core->f1c100s_tcon.tcon0_basic_timing2.m_32bit & 0x03FF);
      
      //Check if line time already set
      if(core->displaymemory.linetime)
        core->displaymemory.numcycles = core->displaymemory.linetime * core->displaymemory.verticaltime;
      break;
      
    case TCON0_BASIC_TIMING3:
      break;
      
    case TCON0_HV_TIMING:
      break;
      
    case TCON0_CPU_IF:
      break;
      
    case TCON0_CPU_WR:
      break;
      
    case TCON0_CPU_RD:
      break;
      
    case TCON0_CPU_RD_NX:
      break;
      
    case TCON0_IO_CTRL0:
      break;
      
    case TCON0_IO_CTRL1:
      break;
      
    case TCON1_CTRL:
      break;
      
    case TCON1_BASIC_TIMING0:
      break;
      
    case TCON1_BASIC_TIMING1:
      break;
      
    case TCON1_BASIC_TIMING2:
      break;
      
    case TCON1_BASIC_TIMING3:
      break;
      
    case TCON1_BASIC_TIMING4:
      break;
      
    case TCON1_BASIC_TIMING5:
      break;
      
    case TCON1_IO_CTRL0:
      break;
      
    case TCON1_IO_CTRL1:
      break;
      
    case TCON_DEBUG_INFO:
      break;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
