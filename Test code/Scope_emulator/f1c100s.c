//----------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "f1c100s.h"
#include "f1c100s_ccu.h"
#include "f1c100s_spi.h"

//----------------------------------------------------------------------------------------------------------------------------------
//Main peripheral handling function. This function is called every cycle of the ARM core.
void F1C100sProcess(PARMV5TL_CORE core)
{
  //Handle peripherals that are enabled
  if(core->f1c100s_ccu.bus_clk_gate0.m_32bit & CCU_BCGR0_SPI0_EN)
    F1C100sProcessSPI0(core);
  
  
  
  
  
  
}

//----------------------------------------------------------------------------------------------------------------------------------
//Memory handlers
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
  
  return(NULL);
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
  
  return(NULL);
}

void *F1C100sDDR(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  u_int32_t idx = address >> 2;
  
  //Check if the DDR has been malloced
  if(core->dram)
  {
    switch(mode)
    {
      case ARM_MEMORY_WORD:
        //Return the word aligned data
        return(&core->dram[idx].m_32bit);

      case ARM_MEMORY_SHORT:
        //Return the short aligned data
        return(&core->dram[idx].m_16bit[(address & 2) >> 1]);

      case ARM_MEMORY_BYTE:
        //Return the byte aligned data
        return(&core->dram[idx].m_8bit[address & 3]);
    }
  }
  
  return(NULL);
}

//----------------------------------------------------------------------------------------------------------------------------------
