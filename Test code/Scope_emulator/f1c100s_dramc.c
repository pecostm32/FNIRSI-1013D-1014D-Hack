//----------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "f1c100s.h"

//----------------------------------------------------------------------------------------------------------------------------------
//DRAM control registers
void *F1C100sDRAMC(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  F1C100S_MEMORY *ptr = NULL;
  
  //Select the target register based on word address
  switch(address & 0x00000FFC)
  {
    case DRAM_SCONR:
      ptr = &core->f1c100s_dramc.sconr;
      break;
      
    case DRAM_STMG0R:
      ptr = &core->f1c100s_dramc.stmg0r;
      break;
      
    case DRAM_STMG1R:
      ptr = &core->f1c100s_dramc.stmg1r;
      break;
      
    case DRAM_SCTLR:
      ptr = &core->f1c100s_dramc.sctlr;
      break;
      
    case DRAM_SREFR:
      ptr = &core->f1c100s_dramc.srefr;
      break;
      
    case DRAM_SEXTMR:
      ptr = &core->f1c100s_dramc.sextmr;
      break;
      
    case DRAM_DDLYR:
      ptr = &core->f1c100s_dramc.ddlyr;
      break;
      
    case DRAM_DADRR:
      ptr = &core->f1c100s_dramc.dadrr;
      break;
      
    case DRAM_DVALR:
      ptr = &core->f1c100s_dramc.dvalr;
      break;
      
    case DRAM_DRPTR0:
      ptr = &core->f1c100s_dramc.drptr0;
      break;
      
    case DRAM_DRPTR1:
      ptr = &core->f1c100s_dramc.drptr1;
      break;
      
    case DRAM_DRPTR2:
      ptr = &core->f1c100s_dramc.drptr2;
      break;
      
    case DRAM_DRPTR3:
      ptr = &core->f1c100s_dramc.drptr3;
      break;
      
    case DRAM_SEFR:
      ptr = &core->f1c100s_dramc.sefr;
      break;
      
    case DRAM_MAE:
      ptr = &core->f1c100s_dramc.mae;
      break;
      
    case DRAM_ASPR:
      ptr = &core->f1c100s_dramc.aspr;
      break;
      
    case DRAM_SDLY0:
      ptr = &core->f1c100s_dramc.sdly0;
      break;
      
    case DRAM_SDLY1:
      ptr = &core->f1c100s_dramc.sdly1;
      break;
      
    case DRAM_SDLY2:
      ptr = &core->f1c100s_dramc.sdly2;
      break;
      
    case DRAM_MCR0:
      ptr = &core->f1c100s_dramc.mcr0;
      break;
      
    case DRAM_MCR1:
      ptr = &core->f1c100s_dramc.mcr1;
      break;
      
    case DRAM_MCR2:
      ptr = &core->f1c100s_dramc.mcr2;
      break;
      
    case DRAM_MCR3:
      ptr = &core->f1c100s_dramc.mcr3;
      break;
      
    case DRAM_MCR4:
      ptr = &core->f1c100s_dramc.mcr4;
      break;
      
    case DRAM_MCR5:
      ptr = &core->f1c100s_dramc.mcr5;
      break;
      
    case DRAM_MCR6:
      ptr = &core->f1c100s_dramc.mcr6;
      break;
      
    case DRAM_MCR7:
      ptr = &core->f1c100s_dramc.mcr7;
      break;
      
    case DRAM_MCR8:
      ptr = &core->f1c100s_dramc.mcr8;
      break;
      
    case DRAM_MCR9:
      ptr = &core->f1c100s_dramc.mcr9;
      break;
      
    case DRAM_MCR10:
      ptr = &core->f1c100s_dramc.mcr10;
      break;
      
    case DRAM_MCR11:
      ptr = &core->f1c100s_dramc.mcr11;
      break;
      
    case DRAM_BWCR:
      ptr = &core->f1c100s_dramc.bwcr;
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
//DRAM control registers read
void F1C100sDRAMCRead(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  //Select the target register based on word address
  switch(address & 0x00000FFC)
  {
    case DRAM_SCONR:
      break;
      
    case DRAM_STMG0R:
      break;
      
    case DRAM_STMG1R:
      break;
      
    case DRAM_SCTLR:
      //For now just make sure the delay is none
      core->f1c100s_dramc.sctlr.m_32bit &= ~1;
      break;
      
    case DRAM_SREFR:
      break;
      
    case DRAM_SEXTMR:
      break;
      
    case DRAM_DDLYR:
      //For now just make sure the delay is none
      core->f1c100s_dramc.ddlyr.m_32bit &= ~1;
      break;
      
    case DRAM_DADRR:
      break;
      
    case DRAM_DVALR:
      break;
      
    case DRAM_DRPTR0:
      break;
      
    case DRAM_DRPTR1:
      break;
      
    case DRAM_DRPTR2:
      break;
      
    case DRAM_DRPTR3:
      break;
      
    case DRAM_SEFR:
      break;
      
    case DRAM_MAE:
      break;
      
    case DRAM_ASPR:
      break;
      
    case DRAM_SDLY0:
      break;
      
    case DRAM_SDLY1:
      break;
      
    case DRAM_SDLY2:
      break;
      
    case DRAM_MCR0:
      break;
      
    case DRAM_MCR1:
      break;
      
    case DRAM_MCR2:
      break;
      
    case DRAM_MCR3:
      break;
      
    case DRAM_MCR4:
      break;
      
    case DRAM_MCR5:
      break;
      
    case DRAM_MCR6:
      break;
      
    case DRAM_MCR7:
      break;
      
    case DRAM_MCR8:
      break;
      
    case DRAM_MCR9:
      break;
      
    case DRAM_MCR10:
      break;
      
    case DRAM_MCR11:
      break;
      
    case DRAM_BWCR:
      break;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//DRAM control registers write
void F1C100sDRAMCWrite(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  //Select the target register based on word address
  switch(address & 0x00000FFC)
  {
    case DRAM_SCONR:
      break;
      
    case DRAM_STMG0R:
      break;
      
    case DRAM_STMG1R:
      break;
      
    case DRAM_SCTLR:
      break;
      
    case DRAM_SREFR:
      break;
      
    case DRAM_SEXTMR:
      break;
      
    case DRAM_DDLYR:
      break;
      
    case DRAM_DADRR:
      break;
      
    case DRAM_DVALR:
      break;
      
    case DRAM_DRPTR0:
      break;
      
    case DRAM_DRPTR1:
      break;
      
    case DRAM_DRPTR2:
      break;
      
    case DRAM_DRPTR3:
      break;
      
    case DRAM_SEFR:
      break;
      
    case DRAM_MAE:
      break;
      
    case DRAM_ASPR:
      break;
      
    case DRAM_SDLY0:
      break;
      
    case DRAM_SDLY1:
      break;
      
    case DRAM_SDLY2:
      break;
      
    case DRAM_MCR0:
      break;
      
    case DRAM_MCR1:
      break;
      
    case DRAM_MCR2:
      break;
      
    case DRAM_MCR3:
      break;
      
    case DRAM_MCR4:
      break;
      
    case DRAM_MCR5:
      break;
      
    case DRAM_MCR6:
      break;
      
    case DRAM_MCR7:
      break;
      
    case DRAM_MCR8:
      break;
      
    case DRAM_MCR9:
      break;
      
    case DRAM_MCR10:
      break;
      
    case DRAM_MCR11:
      break;
      
    case DRAM_BWCR:
      break;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
