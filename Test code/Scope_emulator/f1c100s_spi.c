//----------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "f1c100s.h"
#include "f1c100s_ccu.h"
#include "f1c100s_spi.h"

//----------------------------------------------------------------------------------------------------------------------------------
//SPI0 processing
void F1C100sProcessSPI0(PARMV5TL_CORE core)
{
  //Action needed when active and in flash read mode
  if((core->f1c100s_spi[0].tcr.m_32bit & SPI_TCR_XCH_START) && (core->flashmemory.mode == FLASH_MODE_READ))
  {
    //For now just keep it on max 64 for the count
    if(core->f1c100s_spi[0].mbc.m_32bit > 64)
      core->f1c100s_spi[0].mbc.m_32bit = 64;
    
    //When there is a flash file read from it and return that data
    if(core->FlashFilePointer)
    {
      fread(core->f1c100s_spi[0].rxfifo, 1, core->f1c100s_spi[0].mbc.m_32bit, core->FlashFilePointer);
    }
    
    //Set the count to the number of bytes requested. For now instant fulfillment of the need
    core->f1c100s_spi[0].fsr.m_32bit = core->f1c100s_spi[0].mbc.m_32bit;
    
    //Clear the exchange start flag after reading the bytes from file
    core->f1c100s_spi[0].tcr.m_32bit &= ~SPI_TCR_XCH_START;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//SPI0 reset
void F1C100sResetSPI0(PARMV5TL_CORE core)
{
  
  //Signal peripheral is reset
  core->f1c100s_periph_status.spi0_reset = 1;
}

//----------------------------------------------------------------------------------------------------------------------------------
//SPI0 control registers
void *F1C100sSPI0(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  //Call the SPI handler with the registers for SPI0
  return(F1C100sSPI(&core->f1c100s_spi[0], address, mode));
}

//----------------------------------------------------------------------------------------------------------------------------------
//SPI0 control registers read
void F1C100sSPI0Read(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  //Call the SPI read handler with the registers for SPI0
  F1C100sSPIRead(&core->f1c100s_spi[0], address, mode);
}

//----------------------------------------------------------------------------------------------------------------------------------
//SPI0 control registers write
void F1C100sSPI0Write(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  //Call the SPI write handler with the registers for SPI0
  F1C100sSPIWrite(core, &core->f1c100s_spi[0], address, mode);
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
void F1C100sSPIRead(F1C100S_SPI *registers, u_int32_t address, u_int32_t mode)
{
  //Select the target register based on word address
  switch(address & 0x00000FFC)
  {
    case SPI_GCR:
      //Make sure the reset flag gets cleared
      registers->gcr.m_32bit &= ~SPI_GCR_SRST;
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
      //Need to return data in the register here. Based on the mode either 1, 2 or 4 bytes need to be copied
      //FIFO count needs to be decremented accordingly
      if(registers->fsr.m_32bit)
      {
        //Return the bytes starting from fifo[0] based on requested number of bytes and the current fifo count
        registers->rxd.m_8bit[0] = registers->rxfifo[registers->mbc.m_32bit - registers->fsr.m_32bit];
        
        //Take of a byte
        registers->fsr.m_32bit--;
      }
      
      break;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//SPI control registers write
void F1C100sSPIWrite(PARMV5TL_CORE core, F1C100S_SPI *registers, u_int32_t address, u_int32_t mode)
{
  //Select the target register based on word address
  switch(address & 0x00000FFC)
  {
    case SPI_GCR:
      break;
      
    case SPI_TCR:
      //In this register the start of the transfer is signaled by setting the SPI_TCR_XCH_START bit
      //Also the slave select is asserted by clearing the SPI_TCR_SS_LEVEL_HIGH bit
      
      //Check if read command has been written and needs to be processed on start
      if((registers->tcr.m_32bit & SPI_TCR_XCH_START) && (core->flashmemory.commandstate == FLASH_STATE_PROCESS))
      {
        //Switch back to idle state
        core->flashmemory.commandstate = FLASH_STATE_IDLE;
        core->flashmemory.mode = FLASH_MODE_READ;

        //Seek to the address given if there is a flash file
        if(core->FlashFilePointer)
          fseek(core->FlashFilePointer, core->flashmemory.readaddress, SEEK_SET);

        //Clear the exchange start flag after reception of the fourth byte
        registers->tcr.m_32bit &= ~SPI_TCR_XCH_START;
        
        //Signal 4 bytes received to satisfy the code
        core->f1c100s_spi[0].fsr.m_32bit = core->f1c100s_spi[0].mbc.m_32bit;
      }
      
      //When the slave select is de-asserted clear the flash memory state and mode
      if(registers->tcr.m_32bit & SPI_TCR_SS_LEVEL_HIGH)
      {
        core->flashmemory.commandstate = FLASH_STATE_IDLE;
        core->flashmemory.mode = FLASH_MODE_IDLE;
      }
      break;
      
    case SPI_IER:
      break;
      
    case SPI_ISR:
      break;
      
    case SPI_FCR:  //FIFO control register. Upper 16 bit TX FIFO. Lower 16 bit RX FIFO.
      //For a receive this is either cleared with setting of the SPI_FCR_RX_FIFO_RST bit or by reading the bytes in the fifo
      break;
      
    case SPI_FSR:  //FIFO status register. Upper 16 bit TX FIFO. Lower 16 bit RX FIFO.
      break;
      
    case SPI_WCR:
      break;
      
    case SPI_CCR:
      break;
      
    case SPI_MBC:
      //In this register the transmit or receive count is written (max 64 bytes per session)
      break;
      
    case SPI_MTC:
      //The same number is written to this register. This indicates bytes being transmitted. Zero for receive.
      break;
      
    case SPI_BCC:
      //The same number is written to this register. This indicates bytes being transmitted. Zero for receive.
      break;
      
    case SPI_TXD:
      //The bytes are written to this register in a single loop without waits, so transfer to the TX fifo or handle directly in some state machine
      //After the bytes have been transmitted out of the fifo the SPI_TCR_XCH_START needs to be cleared
      //The mode specifies how many bytes need to be copied to the fifo
      
      //Simple state machine for getting the flash read address. Only command used for now
      //For now all data is used in byte mode since the code is known to do so
      //Need a flash data structure to hold state machine information
      switch(core->flashmemory.commandstate)
      {
        //First byte written is the command byte
        case FLASH_STATE_IDLE:
          if(registers->txd.m_8bit[0] == 0x03)
            core->flashmemory.commandstate = FLASH_STATE_RX_ADDRESS_H;
          break;
          
        case FLASH_STATE_RX_ADDRESS_H:
          //Get the high byte of the address (24 bit addressing)
          core->flashmemory.readaddress = registers->txd.m_8bit[0] << 16;
          core->flashmemory.commandstate = FLASH_STATE_RX_ADDRESS_M;
          break;
          
        case FLASH_STATE_RX_ADDRESS_M:
          //Get the middle byte of the address (24 bit addressing)
          core->flashmemory.readaddress |= registers->txd.m_8bit[0] << 8;
          core->flashmemory.commandstate = FLASH_STATE_RX_ADDRESS_L;
          break;
          
        case FLASH_STATE_RX_ADDRESS_L:
          //Get the low byte of the address (24 bit addressing)
          core->flashmemory.readaddress |= registers->txd.m_8bit[0];
          core->flashmemory.commandstate = FLASH_STATE_PROCESS;
          break;
      }
      break;
      
    case SPI_RXD:
      //Not used here since it is a read register
      break;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
