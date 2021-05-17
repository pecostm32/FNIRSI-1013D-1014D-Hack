//----------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "f1c100s.h"

//----------------------------------------------------------------------------------------------------------------------------------
//SPI0 control registers
void *F1C100sSPI0(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  //Call the SPI handler with the registers for SPI0
  return(F1C100sSPI(&core->f1c100s_spi0, address, mode));
}

//----------------------------------------------------------------------------------------------------------------------------------
//SPI0 control registers read
void F1C100sSPI0Read(PARMV5TL_CORE core, u_int32_t address)
{
  //Call the SPI handler with the registers for SPI0
  F1C100sSPIRead(&core->f1c100s_spi0, address);
}

//----------------------------------------------------------------------------------------------------------------------------------
//SPI0 control registers write
void F1C100sSPI0Write(PARMV5TL_CORE core, u_int32_t address)
{
  //Call the SPI handler with the registers for SPI0
  F1C100sSPIWrite(&core->f1c100s_spi0, address);
}

//----------------------------------------------------------------------------------------------------------------------------------
//SPI control registers
void *F1C100sSPI(F1C100S_SPI *registers, u_int32_t address, u_int32_t mode)
{
  F1C100S_MEMORY *ptr = NULL;
  
  //Select the target register based on word address
  switch(address & 0x00000FFC)
  {
    case SPI_GCR:
      ptr = &registers->gcr;
      break;
      
    case SPI_TCR:
      ptr = &registers->tcr;
      break;
      
    case SPI_IER:
      ptr = &registers->ier;
      break;
      
    case SPI_ISR:
      ptr = &registers->isr;
      break;
      
    case SPI_FCR:
      ptr = &registers->fcr;
      break;
      
    case SPI_FSR:
      ptr = &registers->fsr;
      break;
      
    case SPI_WCR:
      ptr = &registers->wcr;
      break;
      
    case SPI_CCR:
      ptr = &registers->ccr;
      break;
      
    case SPI_MBC:
      ptr = &registers->mbc;
      break;
      
    case SPI_MTC:
      ptr = &registers->mtc;
      break;
      
    case SPI_BCC:
      ptr = &registers->bcc;
      break;
      
    case SPI_TXD:
      ptr = &registers->txd;
      break;
      
    case SPI_RXD:
      ptr = &registers->rxd;
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
//SPI control registers read
void F1C100sSPIRead(F1C100S_SPI *registers, u_int32_t address)
{
  //Select the target register based on word address
  switch(address & 0x00000FFC)
  {
    case SPI_GCR:
      break;
      
    case SPI_TCR:
      break;
      
    case SPI_IER:
      break;
      
    case SPI_ISR:
      break;
      
    case SPI_FCR:
      break;
      
    case SPI_FSR:
      break;
      
    case SPI_WCR:
      break;
      
    case SPI_CCR:
      break;
      
    case SPI_MBC:
      break;
      
    case SPI_MTC:
      break;
      
    case SPI_BCC:
      break;
      
    case SPI_TXD:
      break;
      
    case SPI_RXD:
      break;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//SPI control registers write
void F1C100sSPIWrite(F1C100S_SPI *registers, u_int32_t address)
{
  //Select the target register based on word address
  switch(address & 0x00000FFC)
  {
    case SPI_GCR:
      break;
      
    case SPI_TCR:
      break;
      
    case SPI_IER:
      break;
      
    case SPI_ISR:
      break;
      
    case SPI_FCR:
      break;
      
    case SPI_FSR:
      break;
      
    case SPI_WCR:
      break;
      
    case SPI_CCR:
      break;
      
    case SPI_MBC:
      break;
      
    case SPI_MTC:
      break;
      
    case SPI_BCC:
      break;
      
    case SPI_TXD:
      break;
      
    case SPI_RXD:
      break;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
