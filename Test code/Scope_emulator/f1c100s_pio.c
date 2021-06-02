//----------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "f1c100s.h"

//----------------------------------------------------------------------------------------------------------------------------------
//Port A defines for handling the touch panel

//Panel driver state machine
#define PANEL_WAIT_ADDRESS     0
#define PANEL_RCV_REG_HIGH     1
#define PANEL_RCV_REG_LOW      2
#define PANEL_RECEIVE_DATA     3
#define PANEL_SEND_DATA        4

//I2C state machine states
#define I2C_STATE_IDLE         0
#define I2C_STATE_RCV_BITS     1
#define I2C_STATE_SND_BITS     2
#define I2C_STATE_RCV_ACK      3
#define I2C_STATE_SND_ACK      4
#define I2C_STATE_SKIP_ACK     5

#define I2C_NUM_BITS           8

#define I2C_MODE_MASK          0x01
#define I2C_MODE_WRITE         0x00
#define I2C_MODE_READ          0x01

#define I2C_RESET_BIT          0x01
#define I2C_INT_BIT            0x02
#define I2C_SDA_BIT            0x04
#define I2C_SCL_BIT            0x08

//----------------------------------------------------------------------------------------------------------------------------------
//Port E defines for handling the FPGA

//FPGA control pins located in the second byte
#define FPGA_CLOCK             0x01
#define FPGA_READ_WRITE        0x02
#define FPGA_DATA_COMMAND      0x04

//Mask for separating the two control lines
#define FPGA_CONTROL_MASK      0x06

#define FPGA_COMMAND_WRITE     0x06
#define FPGA_COMMAND_READ      0x04
#define FPGA_DATA_WRITE        0x02
#define FPGA_DATA_READ         0x00


//----------------------------------------------------------------------------------------------------------------------------------
void PortAHandler(F1C100S_PIO_PORT *registers,  u_int32_t mode)
{
  TOUCH_PANEL_DATA *pd = (TOUCH_PANEL_DATA *)registers->portdata;
  u_int8_t address;
  
   //Check if there is device data
  if(pd)
  {
    //Handle data being written
    if(mode == PORT_WRITE)
    {
      //Only when device not being reset
      if(registers->data.m_8bit[0] & I2C_RESET_BIT)
      {
        //On rising edge of the SCL pin a data bit needs to be read
        if((registers->data.m_8bit[0] & I2C_SCL_BIT) && ((pd->prev_port_data & I2C_SCL_BIT) == 0))
        {
          //Handle according to the current i2c state
          switch(pd->i2c_state)
          {
            case I2C_STATE_SND_BITS:
              //Set SDA with the bit to send (MSB first)
              if(pd->i2c_currentbyte & 0x80)
              {
                //Set SDA
                registers->data.m_8bit[0] |= I2C_SDA_BIT;
              }
              else
              {
                //Clear SDA
                registers->data.m_8bit[0] &= ~I2C_SDA_BIT;                
              }
              
              //Select next bit
              pd->i2c_currentbyte <<= 1;
              
              //Signal another bit is send
              pd->i2c_currentbit++;
              
              //Check if it was the last bit
              if(pd->i2c_currentbit >= I2C_NUM_BITS)
              {
                //If so switch to receiving the ack
                pd->i2c_state = I2C_STATE_RCV_ACK;
                
                //Select the next byte to send
                pd->i2c_currentbyte = pd->panel_data[pd->panel_address];
                pd->i2c_currentbit = 0;
                
                //Point to next register for next read
                pd->panel_address++;
              }              
              break;
            
            case I2C_STATE_RCV_BITS:
              //Get the bit from SDA and put it in the current byte
              pd->i2c_currentbyte = (pd->i2c_currentbyte << 1) | ((registers->data.m_8bit[0] & I2C_SDA_BIT) >> 2);

              //Signal another bit is received
              pd->i2c_currentbit++;

              //Check if it was the last bit
              if(pd->i2c_currentbit >= I2C_NUM_BITS)
              {
                //Check on process state here
                switch(pd->panel_state)
                {
                  case PANEL_WAIT_ADDRESS:
                    //Check if received byte matches the device address
                    address = pd->i2c_currentbyte >> 1; 
                    if((address == 0x14) || (address == 0x5B))
                    {
                      //Check on the data mode for further action
                      pd->panel_mode = pd->i2c_currentbyte & 0x01;

                      if(pd->panel_mode == I2C_MODE_WRITE)
                      {
                        //For write the next two bytes are the register address
                        pd->panel_state = PANEL_RCV_REG_HIGH;
                      }
                      else
                      {
                        //For a read data needs to be returned
                        pd->panel_state = PANEL_SEND_DATA;
                      }

                      //Switch to set ack state to show the device is present (The scope code does not use this)
                      pd->i2c_state = I2C_STATE_SND_ACK;
                    }
                    else
                    {
                      //Switch to skip ack state since the data is not fur this device
                      pd->i2c_state = I2C_STATE_SKIP_ACK;
                    }
                    break;
                    
                  case PANEL_RCV_REG_HIGH:
                    //Received the high part of the address so set it in the panel address. Limit to 256 byte address range
                    pd->panel_address = (pd->i2c_currentbyte << 8) & 0x100;
                    
                    //Switch to receiving low part of address
                    pd->panel_state = PANEL_RCV_REG_LOW;

                    //Switch to set ack state to show the byte is received well (The scope code does not use this)
                    pd->i2c_state = I2C_STATE_SND_ACK;
                    break;
                    
                  case PANEL_RCV_REG_LOW:
                    //Received the high part of the address so set it in the panel address
                    pd->panel_address |= pd->i2c_currentbyte;
                    
                    //Switch to receiving data
                    pd->panel_state = PANEL_RECEIVE_DATA;

                    //Switch to set ack state to show the byte is received well (The scope code does not use this)
                    pd->i2c_state = I2C_STATE_SND_ACK;
                    break;
                    
                  case PANEL_RECEIVE_DATA:
                    //Just keep receiving data and increment the internal address
                    pd->panel_data[pd->panel_address] = pd->i2c_currentbyte;

                    //Point to next register for next write
                    pd->panel_address++;
                    
                    //Switch to set ack state to show the byte is received well (The scope code does not use this)
                    pd->i2c_state = I2C_STATE_SND_ACK;
                    break;
                }

                //Clear the data byte and bit indicator
                pd->i2c_currentbyte = 0;
                pd->i2c_currentbit = 0;
              }
              break;

            case I2C_STATE_SND_ACK:
              //Need to send an ack bit on the next port read
              registers->data.m_8bit[0] |= I2C_SDA_BIT;
              
              //Check on the panel state for deciding on next state
              if(pd->panel_state == PANEL_SEND_DATA)
              {
                //Check on panel address being 0x814E and if so check if mouse button is down on the touch panel
                //Upper seven bits of the address are not used
                if(pd->panel_address == 0x14E)
                {
                  if(pd->mouse_down)
                  {
                    //Signal there is touch
                    pd->panel_data[0x14E] = 0x81;
                  }
                  else
                  {
                    //Signal there is no touch
                    pd->panel_data[0x14E] = 0x00;
                  }
                }
                
                //Load the current byte with the data to send
                pd->i2c_currentbyte = pd->panel_data[pd->panel_address];
                
                //Point to next register for next read
                pd->panel_address++;
                
                //Switch to send bits state
                pd->i2c_state = I2C_STATE_SND_BITS;
              }
              else
              {
                //Switch to receive bits state
                pd->i2c_state = I2C_STATE_RCV_BITS;
              }
              break;
              
            case I2C_STATE_RCV_ACK:
              //Get the acknowledgment state from SDA and set the correct state based on it
              //Not really needed but nice to know the data was received well

              //Switch to get bits state
              pd->i2c_state = I2C_STATE_SND_BITS;
              break;
              
            default:
              //Switch to idle state
              pd->i2c_state = I2C_STATE_IDLE;
              break;
          }
        }
        //On rising or falling edge of the SDA pin
        else if((registers->data.m_8bit[0] & I2C_SDA_BIT) != (pd->prev_port_data & I2C_SDA_BIT))
        {
          //and SCL high there is a start or stop condition
          if(registers->data.m_8bit[0] & I2C_SCL_BIT)
          {
            //Get the status of the SDA pin to see which condition has been received
            if(registers->data.m_8bit[0] & I2C_SDA_BIT)
            {
              //On SDA high a stop condition is received so switch to idle state
              pd->i2c_state = I2C_STATE_IDLE;
            }
            else
            {
              //On SDA low a start condition is received so clear the data byte and bit indicator
              pd->i2c_currentbyte = 0;
              pd->i2c_currentbit = 0;

              //Switch to get bit state
              pd->i2c_state = I2C_STATE_RCV_BITS;
              
              //After a start the panel needs to be re addressed.
              pd->panel_state = PANEL_WAIT_ADDRESS;
            }
          }
        }
      }

      //store current as previous
      pd->prev_port_data = registers->data.m_8bit[0];
    }
  }  
}

//----------------------------------------------------------------------------------------------------------------------------------
void PortEHandler(F1C100S_PIO_PORT *registers,  u_int32_t mode)
{
  FPGA_DATA *pd = (FPGA_DATA *)registers->portdata;
  
  
  //The low 8 bits of this port are the data lines
  
  //In the second 8 bits there are three control lines
  
  
   //Check if there is device data
  if(pd)
  {
    //Handle data being written
    if(mode == PORT_WRITE)
    {
      //On rising edge of the clock pin data is being transfered
      if((registers->data.m_8bit[1] & FPGA_CLOCK) && ((pd->prev_ctrl_bits & FPGA_CLOCK) == 0))
      {
        //Check on command or data and read or write
        switch(registers->data.m_8bit[1] & FPGA_CONTROL_MASK)
        {
          case FPGA_COMMAND_WRITE:
            if(registers->data.m_8bit[0] == 0x41)
            {
              pd->current_command = 0x41;
              
              pd->read_count = 2;
              pd->read_index = 0;
              pd->read_buffer[0] = 0x81;
              pd->read_buffer[1] = 0x50;
            }
            if(pd->fp)
              fprintf(pd->fp, "command write: 0x%02X\n", registers->data.m_8bit[0]);
            break;

          case FPGA_COMMAND_READ:
            if(pd->fp)
              fprintf(pd->fp, "command read\n");
            break;

          case FPGA_DATA_WRITE:
            if(pd->fp)
              fprintf(pd->fp, "data write: 0x%02X\n", registers->data.m_8bit[0]);
            break;

          case FPGA_DATA_READ:
            if(pd->read_count)
            {
              registers->data.m_8bit[0] = pd->read_buffer[pd->read_index];
              
              pd->read_index++;
              pd->read_count--;
            }
            
            if(pd->fp)
              fprintf(pd->fp, "data read\n");
            break;
        }
      }

      //store current as previous
      pd->prev_ctrl_bits = registers->data.m_8bit[1];
    }
  }
}

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
  if(address == SDR_PAD_DRV)
  {
    //Return the pointer based on the requested mode
    switch(mode & ARM_MEMORY_MASK)
    {
      case ARM_MEMORY_WORD:
        //Return the word aligned data
        return(&core->f1c100s_port_ddr.paddrv.m_32bit);

      case ARM_MEMORY_SHORT:
        //Return the short aligned data
        return(&core->f1c100s_port_ddr.paddrv.m_16bit[(address & 2) >> 1]);

      case ARM_MEMORY_BYTE:
        //Return the byte aligned data
        return(&core->f1c100s_port_ddr.paddrv.m_8bit[address & 3]);
    }
  }
  //Check if DDR pad pull register
  else if(address == SDR_PAD_PUL)
  {
    //Return the pointer based on the requested mode
    switch(mode & ARM_MEMORY_MASK)
    {
      case ARM_MEMORY_WORD:
        //Return the word aligned data
        return(&core->f1c100s_port_ddr.padpul.m_32bit);

      case ARM_MEMORY_SHORT:
        //Return the short aligned data
        return(&core->f1c100s_port_ddr.padpul.m_16bit[(address & 2) >> 1]);

      case ARM_MEMORY_BYTE:
        //Return the byte aligned data
        return(&core->f1c100s_port_ddr.padpul.m_8bit[address & 3]);
    }
  }
  
  //Invalid address so just return NULL
  return(NULL);
}


//----------------------------------------------------------------------------------------------------------------------------------
//PIO control registers read
void F1C100sPIORead(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  address &= 0x03FF;
  
  //Check if port control register selected
  if(address < 0xD8)
  {
    //Read the correct register.  Each set has 9 registers of 4 bytes each.
    F1C100sPIOPortRead(&core->f1c100s_port[address / 0x24], address % 0x24, mode);
  }
  //Check if interrupt control register selected
  else if((address >= 0x0200) && ( address < 0x0260))
  {
    address -= 0x0200;
    
    //Read the correct register.  Each set has 7 registers of 4 bytes each, but base size is 0x20
    F1C100sPIOIntRead(&core->f1c100s_port_int[address / 0x20], address % 0x20, mode);
  }
  //Check if DDR pad driver register
  else if(address == SDR_PAD_DRV)
  {
  }
  //Check if DDR pad pull register
  else if(address == SDR_PAD_PUL)
  {
  }
  
  return;
}

//----------------------------------------------------------------------------------------------------------------------------------
//PIO control registers read
void F1C100sPIOWrite(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  address &= 0x03FF;

  //Check if port control register selected
  if(address < 0xD8)
  {
    //Read the correct register.  Each set has 9 registers of 4 bytes each.
    F1C100sPIOPortWrite(&core->f1c100s_port[address / 0x24], address % 0x24, mode);
  }
  //Check if interrupt control register selected
  else if((address >= 0x0200) && ( address < 0x0260))
  {
    address -= 0x0200;
    
    //Read the correct register.  Each set has 7 registers of 4 bytes each, but base size is 0x20
    F1C100sPIOIntWrite(&core->f1c100s_port_int[address / 0x20], address % 0x20, mode);
  }
  //Check if DDR pad driver register
  else if(address == SDR_PAD_DRV)
  {
  }
  //Check if DDR pad pull register
  else if(address == SDR_PAD_PUL)
  {
  }
  
  return;
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
//PIO port control registers read
void F1C100sPIOPortRead(F1C100S_PIO_PORT *registers, u_int32_t address, u_int32_t mode)
{
  //Select the target register based on word address
  switch(address & 0x0000003C)
  {
    case PIO_CFG0:
      break;
      
    case PIO_CFG1:
      break;
      
    case PIO_CFG2:
      break;
      
    case PIO_CFG3:
      break;
      
    case PIO_DATA:
      //Call a function pointer set in the register data struct to handle the data read
      if(registers->porthandler)
        registers->porthandler(registers, PORT_READ);
      break;
      
    case PIO_DRV0:
      break;
      
    case PIO_DRV1:
      break;
      
    case PIO_PUL0:
      break;
      
    case PIO_PUL1:
      break;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//PIO port control registers read
void F1C100sPIOPortWrite(F1C100S_PIO_PORT *registers, u_int32_t address, u_int32_t mode)
{
  //Select the target register based on word address
  switch(address & 0x0000003C)
  {
    case PIO_CFG0:
      break;
      
    case PIO_CFG1:
      break;
      
    case PIO_CFG2:
      break;
      
    case PIO_CFG3:
      break;
      
    case PIO_DATA:
      //Call a function pointer set in the register data struct to handle the data write
      if(registers->porthandler)
        registers->porthandler(registers, PORT_WRITE);
      break;
      
    case PIO_DRV0:
      break;
      
    case PIO_DRV1:
      break;
      
    case PIO_PUL0:
      break;
      
    case PIO_PUL1:
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
//PIO interrupt control registers read
void F1C100sPIOIntRead(F1C100S_PIO_INT *registers, u_int32_t address, u_int32_t mode)
{
  //Select the target register based on word address
  switch(address & 0x0000003C)
  {
    case PIO_INT_CFG0:
      break;
      
    case PIO_INT_CFG1:
      break;
      
    case PIO_INT_CFG2:
      break;
      
    case PIO_INT_CFG3:
      break;
      
    case PIO_INT_CTRL:
      break;
      
    case PIO_INT_STA:
      break;
      
    case PIO_INT_DEB:
      break;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//PIO interrupt control registers write
void F1C100sPIOIntWrite(F1C100S_PIO_INT *registers, u_int32_t address, u_int32_t mode)
{
  //Select the target register based on word address
  switch(address & 0x0000003C)
  {
    case PIO_INT_CFG0:
      break;
      
    case PIO_INT_CFG1:
      break;
      
    case PIO_INT_CFG2:
      break;
      
    case PIO_INT_CFG3:
      break;
      
    case PIO_INT_CTRL:
      break;
      
    case PIO_INT_STA:
      break;
      
    case PIO_INT_DEB:
      break;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
