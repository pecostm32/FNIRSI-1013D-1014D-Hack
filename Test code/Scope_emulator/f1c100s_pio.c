//----------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "f1c100s.h"

//----------------------------------------------------------------------------------------------------------------------------------
//PIO control registers
void *F1C100sPIO(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  //Check if port control register selected
  if(address < 0xD8)
  {
    //Return the pointer to the correct register.  Each set has 9 registers of 4 bytes each.
    return(F1C100sPIOPort(&core->f1c100s_port[address / 0x24], address % 0x24, mode));
  }
  //Check if interrupt control register selected
  if((address >= 0x0200) && ( address < 0x0260))
  {
    address -= 0x0200;
    
    //Return the pointer to the correct register.  Each set has 7 registers of 4 bytes each, but base size is 0x20
    return(F1C100sPIOInt(&core->f1c100s_port_int[address / 0x20], address % 0x20, mode));
  }
  //Check if DDR pad driver register
  else if(address == SDR_PAD_DRV)
  {
    return(&core->f1c100s_port_ddr.paddrv);
  }
  //Check if DDR pad pull register
  else if(address == SDR_PAD_PUL)
  {
    return(&core->f1c100s_port_ddr.padpul);
  }
  else
  {
    //Invalid address so just return NULL
    return(NULL);
  }
}



//----------------------------------------------------------------------------------------------------------------------------------
//PIO port control registers
void *F1C100sPIOPort(F1C100S_PIO_PORT *registers, u_int32_t address, u_int32_t mode)
{
  F1C100S_MEMORY *ptr = NULL;
  
  //Select the target register based on word address
  switch(address & 0x0000003C)
  {
    case PIO_CFG0:
      ptr = &registers->cfg0;
      break;
      
    case PIO_CFG1:
      ptr = &registers->cfg1;
      break;
      
    case PIO_CFG2:
      ptr = &registers->cfg2;
      break;
      
    case PIO_CFG3:
      ptr = &registers->cfg3;
      break;
      
    case PIO_DATA:
      ptr = &registers->data;
      break;
      
    case PIO_DRV0:
      ptr = &registers->drv0;
      break;
      
    case PIO_DRV1:
      ptr = &registers->drv1;
      break;
      
    case PIO_PUL0:
      ptr = &registers->pul0;
      break;
      
    case PIO_PUL1:
      ptr = &registers->pul1;
      break;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//PIO interrupt control registers
void *F1C100sPIOInt(F1C100S_PIO_INT *registers, u_int32_t address, u_int32_t mode)
{
  F1C100S_MEMORY *ptr = NULL;
  
  //Select the target register based on word address
  switch(address & 0x0000003C)
  {
    case PIO_INT_CFG0:
      ptr = &registers->cfg0;
      break;
      
    case PIO_INT_CFG1:
      ptr = &registers->cfg1;
      break;
      
    case PIO_INT_CFG2:
      ptr = &registers->cfg2;
      break;
      
    case PIO_INT_CFG3:
      ptr = &registers->cfg3;
      break;
      
    case PIO_INT_CTRL:
      ptr = &registers->ctrl;
      break;
      
    case PIO_INT_STA:
      ptr = &registers->sta;
      break;
      
    case PIO_INT_DEB:
      ptr = &registers->deb;
      break;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
