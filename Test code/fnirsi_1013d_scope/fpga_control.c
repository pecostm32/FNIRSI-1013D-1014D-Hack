//----------------------------------------------------------------------------------------------------------------------------------

#include "fpga_control.h"

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct tagByteBits    ByteBits;

typedef union tagByteAndBits  ByteAndBits;

//----------------------------------------------------------------------------------------------------------------------------------

struct tagByteBits
{
  unsigned char b0:1;
  unsigned char b1:1;
  unsigned char b2:1;
  unsigned char b3:1;
  unsigned char b4:1;
  unsigned char b5:1;
  unsigned char b6:1;
  unsigned char b7:1;
};

//----------------------------------------------------------------------------------------------------------------------------------

union tagByteAndBits
{
  unsigned char byte;
  ByteBits      bits;
};

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_init(void)
{
  //First set pin high in data register to avoid spikes when changing from input to output
  FPGA_CLK_INIT();
  
  //Initialize the three control lines for output
  FPGA_CTRL_INIT();
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_write_cmd(unsigned char command)
{
  //Set the control lines for writing a command
  FPGA_CMD_WRITE();

  //Set the bus for writing
  FPGA_BUS_DIR_OUT();

  //Write the data to the bus  
  FPGA_SET_DATA(command);
  
  //Clock the data into the FPGA
  FPGA_PULSE_CLK();
}

//----------------------------------------------------------------------------------------------------------------------------------

unsigned char fpga_read_cmd(void)
{
  //Set the bus for reading
  FPGA_BUS_DIR_IN();
  
  //Set the control lines for reading a command
  FPGA_CMD_READ();

  //Clock the data to the output of the FPGA
  FPGA_PULSE_CLK();
 
  //Read the data
  return(FPGA_GET_DATA());
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_write_byte(unsigned char data)
{
  //Set the control lines for writing a command
  FPGA_DATA_WRITE();

  //Set the bus for writing
  FPGA_BUS_DIR_OUT();
  
  //Write the data to the bus  
  FPGA_SET_DATA(data);
  
  //Clock the data into the FPGA
  FPGA_PULSE_CLK();
}

//----------------------------------------------------------------------------------------------------------------------------------

unsigned char fpga_read_byte(void)
{
  //Set the bus for reading
  FPGA_BUS_DIR_IN();
  
  //Set the control lines for reading a command
  FPGA_DATA_READ();

  //Clock the data to the output of the FPGA
  FPGA_PULSE_CLK();
 
  //Read the data
  return(FPGA_GET_DATA());
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_write_short(unsigned short data)
{
  //Set the control lines for writing a command
  FPGA_DATA_WRITE();

  //Set the bus for writing
  FPGA_BUS_DIR_OUT();
  
  //Write the msb to the bus  
  FPGA_SET_DATA(data >> 8);
  
  //Clock the data into the FPGA
  FPGA_PULSE_CLK();
  
  //Write the lsb to the bus  
  FPGA_SET_DATA(data);
  
  //Clock the data into the FPGA
  FPGA_PULSE_CLK();
}

//----------------------------------------------------------------------------------------------------------------------------------

unsigned short fpga_read_short(void)
{
  unsigned short data;
  
  //Set the bus for reading
  FPGA_BUS_DIR_IN();
  
  //Set the control lines for reading a command
  FPGA_DATA_READ();

  //Clock the data to the output of the FPGA
  FPGA_PULSE_CLK();

  //Get the msb
  data = FPGA_GET_DATA() << 8;

  //Clock the data to the output of the FPGA
  FPGA_PULSE_CLK();

  //Get the lsb
  data |= FPGA_GET_DATA();
  
  //Read the data
  return(data);
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_write_int(unsigned int data)
{
  //Set the control lines for writing a command
  FPGA_DATA_WRITE();

  //Set the bus for writing
  FPGA_BUS_DIR_OUT();
  
  //Write the msb to the bus  
  FPGA_SET_DATA(data >> 24);
  
  //Clock the data into the FPGA
  FPGA_PULSE_CLK();

  //Write the mlsb to the bus  
  FPGA_SET_DATA(data >> 16);
  
  //Clock the data into the FPGA
  FPGA_PULSE_CLK();
  
  //Write the lmsb to the bus  
  FPGA_SET_DATA(data >> 8);
  
  //Clock the data into the FPGA
  FPGA_PULSE_CLK();
  
  //Write the lsb to the bus  
  FPGA_SET_DATA(data);
  
  //Clock the data into the FPGA
  FPGA_PULSE_CLK();
}

//----------------------------------------------------------------------------------------------------------------------------------

void set_backlight_brightness(unsigned short brightness)
{
  fpga_write_cmd(0x38);
  fpga_write_short(brightness);
}

//----------------------------------------------------------------------------------------------------------------------------------

unsigned short fpga_get_version(void)
{
  fpga_write_cmd(0x06);

  return(fpga_read_short());
}

//----------------------------------------------------------------------------------------------------------------------------------

void check_fpga_ready(void)
{
  int i;
  
  //Check if the FPGA is up and running by reading the version number
  while(fpga_get_version() != 0x1432)
  {
    //if not just wait a bit and try it again
    //At 600MHz CPU_CLK 1000 = ~200uS
    for(i=0;i<1000;i++);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

unsigned char parameter_buffer[7];
unsigned char parameter_crypt_byte;

//----------------------------------------------------------------------------------------------------------------------------------

void init_parameter_ic(void)
{
  int i;
  
  //Prepare FPGA for reading the parameter ic
  fpga_write_cmd(0x64);
  fpga_write_cmd(0x64);
  
  //Need a delay here. In the scope it is delay(20) but not sure what the base of the delay is
  
  //Start the read action
  fpga_write_cmd(0x66);
  
  //Wait until the FPGA is ready with reading
  do
  {
    //Send command for status read
    fpga_write_cmd(0x67);
  }
  while((fpga_read_byte() & 0x01) == 0);

  for(i=0;i<7;i++)
  {
    //Send the command for reading a received byte
    fpga_write_cmd(0x68 + i);
    
    //Store in the global buffer
    parameter_buffer[i] = fpga_read_byte();
  }
  
  //Use the MSB of the received data as the next crypt byte
  parameter_crypt_byte = parameter_buffer[3];
}

//----------------------------------------------------------------------------------------------------------------------------------

void write_parameter_ic(unsigned char id, unsigned int value)
{
  unsigned char length = 3;
  int i;

  ByteAndBits crypt_in;
  ByteAndBits crypt_out;
  
  //First data byte is the crypt byte
  parameter_buffer[0] = parameter_crypt_byte;

  //Load the data bytes with the value
  parameter_buffer[3] = (unsigned char)(value >> 24);
  parameter_buffer[4] = (unsigned char)(value >> 16);
  parameter_buffer[5] = (unsigned char)(value >> 8);
  parameter_buffer[6] = (unsigned char)(value);

  //Check if MSB is actually used
  if(parameter_buffer[3] == 0x00)
  {
    //Set the MSB to a fixed value if not used
    parameter_buffer[3] = 0x69;
    
    //Take one of the length
    length--;
  }

  //Check if MLSB is actually used
  if(parameter_buffer[4] == 0x00)
  {
    //Set the MLSB to a fixed value if not used
    parameter_buffer[4] = 0x96;
    
    //Take one of the length
    length--;
  }

  //Check if LMSB is actually used
  if(parameter_buffer[5] == 0x00)
  {
    //Set the LMSB to a fixed value if not used
    parameter_buffer[5] = 0x99;
    
    //Take one of the length
    length--;
  }

  //Set the parameter id mixed with the length of the value
  parameter_buffer[1] = (id << 2) | length;
  
  //Crypt the bytes
  for(i=1;i<7;i++)
  {
    //Crypting is an xor with the crypt byte
    parameter_buffer[i] ^= parameter_crypt_byte;
  }
  
  //Mangle the crypt byte
  crypt_in.byte = parameter_buffer[0];

  //Basically a swapping of bits in pairs
  crypt_out.bits.b0 = crypt_in.bits.b5;
  crypt_out.bits.b1 = crypt_in.bits.b3;
  crypt_out.bits.b2 = crypt_in.bits.b7;
  crypt_out.bits.b3 = crypt_in.bits.b1;
  crypt_out.bits.b4 = crypt_in.bits.b6;
  crypt_out.bits.b5 = crypt_in.bits.b0;
  crypt_out.bits.b6 = crypt_in.bits.b4;
  crypt_out.bits.b7 = crypt_in.bits.b2;

  //Put it back in the buffer
  parameter_buffer[0] = crypt_out.byte;
  
  //Calculate the checksum
  parameter_buffer[2] = parameter_buffer[0] + parameter_buffer[1] + parameter_buffer[3] + parameter_buffer[4] + parameter_buffer[5] + parameter_buffer[6];
  
  //Prepare FPGA for writing to the parameter ic
  fpga_write_cmd(0x65);
  fpga_write_cmd(0x65);
  
  //Write the data to the FPGA
  for(i=0;i<7;i++)
  {
    //Send the command for writing a send byte
    fpga_write_cmd(0x68 + i);
    
    //Write the byte to the FPGA
    fpga_write_byte(parameter_buffer[i]);
  }
  
  //Start the write action
  fpga_write_cmd(0x66);
  
  //Wait until the FPGA is ready with writing
  do
  {
    //Send command for status read
    fpga_write_cmd(0x67);
  }
  while((fpga_read_byte() & 0x01) == 0);
}

//----------------------------------------------------------------------------------------------------------------------------------

unsigned int read_parameter_ic(unsigned char id, unsigned int value)
{
  int           i,j;
  int           unvalid = 0;
  unsigned int  rcv_value;
  unsigned char checksum;
  
  //Max retry on write read sequence
  while(i < 6)
  {
    //Start the sequence with a write
    write_parameter_ic(id, value);
    
    //Need a delay here. In the scope it is delay(500) but not sure what the base of the delay is
 
    
    //Reset counter
    j=0;
    
    //Max retry on read
    while(j < 50)
    {
      //Assume all will go well
      unvalid = 0;
      
      //Prepare FPGA for reading the parameter ic
      fpga_write_cmd(0x64);
      fpga_write_cmd(0x64);

      //Need a delay here. In the scope it is delay(20) but not sure what the base of the delay is

      //Start the read action
      fpga_write_cmd(0x66);

      //Wait until the FPGA is ready with reading
      do
      {
        //Send command for status read
        fpga_write_cmd(0x67);
      }
      while((fpga_read_byte() & 0x01) == 0);

      for(i=0;i<7;i++)
      {
        //Send the command for reading a received byte
        fpga_write_cmd(0x68 + i);

        //Store in the global buffer
        parameter_buffer[i] = fpga_read_byte();
      }
      
      //Get the crypt byte and invert it
      parameter_crypt_byte = ~parameter_buffer[0];
      
      //Decrypt the bytes
      for(i=1;i<7;i++)
      {
        //Decrypting is an xor with the crypt byte
        parameter_buffer[i] ^= parameter_crypt_byte;
      }
      
      //Restore the value
      rcv_value = 0;

      //Check the type byte on which bytes to use
      switch(parameter_buffer[1])
      {
        case 0xAA:
          rcv_value = (parameter_buffer[3] << 24);
         
        case 0xA5:
          rcv_value |= (parameter_buffer[4] << 16);
         
        case 0x5A:
          rcv_value |= (parameter_buffer[5] << 8);
         
        case 0x55:
          rcv_value |= parameter_buffer[6];
          break;
          
        default:
          unvalid = 1;
          break;
      }
      
      //Check if valid data type given
      if(unvalid == 0)
      {
        //Calculate the checksum
        checksum = parameter_crypt_byte + parameter_buffer[1] + parameter_buffer[3] + parameter_buffer[4] + parameter_buffer[5] + parameter_buffer[6];
        
        //Check if the checksum is correct
        if(checksum == parameter_buffer[2])
        {
          //Return the valid value
          return(rcv_value);
        }
      }
      
      //Need a delay here. In the scope it is delay(100) but not sure what the base of the delay is

      
      //One more try if not valid
      j++;
    }
    
    //One more complete sequence try if not valid
    i++;
  }
  
  //If all fails just return 0
  return(0);
}

//----------------------------------------------------------------------------------------------------------------------------------
