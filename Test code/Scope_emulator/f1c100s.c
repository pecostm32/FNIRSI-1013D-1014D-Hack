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
  
  
  //Separate function pointers are setup for this
    //Handle the last targeted address
    
    //Needs a similar system as in the main cpu for getting to the right peripheral
    //For most reads there is no need to do something, but for reads of receive registers it is certainly needed
    
    //Timing is also an issue. For spi par example there is a relation between the spi_clk and the amount of instructions it takes
    //for a byte to be send or received. This also relates to the cpu clock setting
    
    //Clear flags for next check
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
