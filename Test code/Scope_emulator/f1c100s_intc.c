//----------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "f1c100s.h"
#include "f1c100s_intc.h"
#include "f1c100s_timer.h"

//----------------------------------------------------------------------------------------------------------------------------------
//Interrupt processing
void F1C100sProcessINTC(PARMV5TL_CORE core)
{
  //Need to handle 63 interrupt sources (Only 34 are actually used)
  
  //For now only timer 0, one external interrupt and maybe usb need to be handled here
  //Interrupt number 13 for timer 0
  
  //Once an interrupt has come in and has priority the core irq or fiq flag needs to be set
  //When the FF register bit for an interrupt is set it will be redirected to the fiq.
}

//----------------------------------------------------------------------------------------------------------------------------------
//Interrupt control registers
void *F1C100sINTC(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  F1C100S_MEMORY *ptr = NULL;
  
  //Select the target register based on word address
  switch(address & 0x000000FC)
  {
    case INTC_VECTOR:
      ptr = &core->f1c100s_intc.vector;
      break;
      
    case INTC_BASE_ADDR:
      ptr = &core->f1c100s_intc.base_addr;
      break;
      
    case NMI_INT_CTRL:
      ptr = &core->f1c100s_intc.nmi_int_ctrl;
      break;
      
    case INTC_PEND0:
      ptr = &core->f1c100s_intc.pend0;
      break;
      
    case INTC_PEND1:
      ptr = &core->f1c100s_intc.pend1;
      break;
      
    case INTC_EN0:
      ptr = &core->f1c100s_intc.en0;
      break;
      
    case INTC_EN1:
      ptr = &core->f1c100s_intc.en1;
      break;
      
    case INTC_MASK0:
      ptr = &core->f1c100s_intc.mask0;
      break;
      
    case INTC_MASK1:
      ptr = &core->f1c100s_intc.mask1;
      break;
      
    case INTC_RESP0:
      ptr = &core->f1c100s_intc.resp0;
      break;
      
    case INTC_RESP1:
      ptr = &core->f1c100s_intc.resp1;
      break;
      
    case INTC_FF0:
      ptr = &core->f1c100s_intc.ff0;
      break;
      
    case INTC_FF1:
      ptr = &core->f1c100s_intc.ff1;
      break;
      
    case INTC_PRIO0:
      ptr = &core->f1c100s_intc.prio0;
      break;
      
    case INTC_PRIO1:
      ptr = &core->f1c100s_intc.prio1;
      break;
      
    case INTC_PRIO2:
      ptr = &core->f1c100s_intc.prio2;
      break;
      
    case INTC_PRIO3:
      ptr = &core->f1c100s_intc.prio3;
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
//Timer control registers read function
void F1C100sINTCRead(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  F1C100S_MEMORY *ptr = NULL;
  
  //Select the target register based on word address
  switch(address & 0x000000FC)
  {
    case INTC_VECTOR:
      break;
      
    case INTC_BASE_ADDR:
      break;
      
    case NMI_INT_CTRL:
      break;
      
    case INTC_PEND0:
      break;
      
    case INTC_PEND1:
      break;
      
    case INTC_EN0:
      break;
      
    case INTC_EN1:
      break;
      
    case INTC_MASK0:
      break;
      
    case INTC_MASK1:
      break;
      
    case INTC_RESP0:
      break;
      
    case INTC_RESP1:
      break;
      
    case INTC_FF0:
      break;
      
    case INTC_FF1:
      break;
      
    case INTC_PRIO0:
      break;
      
    case INTC_PRIO1:
      break;
      
    case INTC_PRIO2:
      break;
      
    case INTC_PRIO3:
      break;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//Timer control registers write function
void F1C100sINTCWrite(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  F1C100S_MEMORY *ptr = NULL;
  
  //Select the target register based on word address
  switch(address & 0x000000FC)
  {
    case INTC_VECTOR:
      break;
      
    case INTC_BASE_ADDR:
      break;
      
    case NMI_INT_CTRL:
      break;
      
    case INTC_PEND0:
      break;
      
    case INTC_PEND1:
      break;
      
    case INTC_EN0:
      break;
      
    case INTC_EN1:
      break;
      
    case INTC_MASK0:
      break;
      
    case INTC_MASK1:
      break;
      
    case INTC_RESP0:
      break;
      
    case INTC_RESP1:
      break;
      
    case INTC_FF0:
      break;
      
    case INTC_FF1:
      break;
      
    case INTC_PRIO0:
      break;
      
    case INTC_PRIO1:
      break;
      
    case INTC_PRIO2:
      break;
      
    case INTC_PRIO3:
      break;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
