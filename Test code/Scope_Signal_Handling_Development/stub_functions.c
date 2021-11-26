//----------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>

#include <linux/loop.h>

#include <sys/ioctl.h>

#include "stub_functions.h"
#include "ff.h"
#include "diskio.h"
#include "variables.h"

//----------------------------------------------------------------------------------------------------------------------------------

extern int quit_scopeprocessing_thread_on_zero;

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct tagByteBits    ByteBits;

typedef union tagByteAndBits  ByteAndBits;

//----------------------------------------------------------------------------------------------------------------------------------

struct tagByteBits
{
  uint8 b0:1;
  uint8 b1:1;
  uint8 b2:1;
  uint8 b3:1;
  uint8 b4:1;
  uint8 b5:1;
  uint8 b6:1;
  uint8 b7:1;
};

//----------------------------------------------------------------------------------------------------------------------------------

union tagByteAndBits
{
  uint8    byte;
  ByteBits bits;
};

//----------------------------------------------------------------------------------------------------------------------------------
//Defines for handling the FPGA

#define FPGA_COMMAND_WRITE     0x06
#define FPGA_COMMAND_READ      0x04
#define FPGA_DATA_WRITE        0x02
#define FPGA_DATA_READ         0x00

#define FPGA_DATA_ERROR        0xFF

//Parameter storage handling
#define PARAM_MODE_READ          0
#define PARAM_MODE_WRITE         1

#define PARAM_STATE_NOT_INIT     0
#define PARAM_STATE_INIT         1

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct tagFPGA_DATA                FPGA_DATA;

//----------------------------------------------------------------------------------------------------------------------------------
//Data for FPGA handling
struct tagFPGA_DATA
{
  uint8        current_command;
  uint16       read_count;
  const uint8 *read_ptr;
  uint16       write_count;
  uint8       *write_ptr;
  
  //Data for parameter storage system
  uint8   param_state;
  uint8   param_crypt;
  uint8   param_mode;
  uint8   param_id;
  uint8   param_data[7];
  
  uint8   param_0x0B_data;
  
  uint8   cmd0x14count[2];
  
  FILE   *channel1_trace_data;
  
  uint32  channel1_sample_buffer_index;
  
};

//----------------------------------------------------------------------------------------------------------------------------------

FILE *sd_emu_file = NULL;

int loop_device_open = 0;

//----------------------------------------------------------------------------------------------------------------------------------

FPGA_DATA fpga_data;

//----------------------------------------------------------------------------------------------------------------------------------

void   fpga_init_parameter_ic(void);
void   fpga_write_parameter_ic(uint8 id, uint32 value);
uint32 fpga_read_parameter_ic(uint8 id, uint32 value);

//----------------------------------------------------------------------------------------------------------------------------------

void sys_clock_init(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void arm32_icache_enable(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void arm32_dcache_enable(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void arm32_interrupt_enable(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void timer0_setup(void)
{
  timer0ticks = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------

uint32 timer0_get_ticks(void)
{
  return(timer0ticks);
}

//----------------------------------------------------------------------------------------------------------------------------------

void timer0_delay(uint32 timeout)
{
  //Calculate the timeout ticks
  timeout += timer0ticks;
  
  //While technically prone to error on timer ticks overflow the scope has to be running for >49 days before it occurs
  //Wait until time has past
  while(timer0ticks < timeout);
}

//----------------------------------------------------------------------------------------------------------------------------------

void power_interrupt_init(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void battery_check_init(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void battery_check_status(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void sys_spi_flash_init(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void sys_spi_flash_read(int addr, unsigned char *buffer, int length)
{
  FILE *fp = fopen("scope_flash_memory.bin", "rb");
  
  if(fp)
  {
    fseek(fp, addr, SEEK_SET);
    
    fread(buffer, 1, length, fp);
    
    fclose(fp);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void sys_spi_flash_write(int addr, unsigned char *buffer, int length)
{
  FILE *fp = fopen("scope_flash_memory.bin", "wb");
  
  if(fp)
  {
    fseek(fp, addr, SEEK_SET);
    
    fwrite(buffer, 1, length, fp);
    
    fclose(fp);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_init(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_exit(void)
{
  //Check if file open
  if(fpga_data.channel1_trace_data)
  {
    //Close it
    fclose(fpga_data.channel1_trace_data);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//Static data
const uint8 tp_coord_reg[2] = { 0x81, 0x50 };

const uint8 param_status_byte = 0x01;


const uint8 scope_ch1_long_data[] = 
{
  0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
  0x68, 0x68, 0x68, 0x68, 0x68, 0x68, 0x68, 0x68, 0x68, 0x68,
  0xB8, 0xB8, 0xB8, 0xB8, 0xB8, 0xB8, 0xB8, 0xB8, 0xB8, 0xB8,
  0xC1, 0xC1, 0xC1, 0xC1, 0xC1, 0xC1, 0xC1, 0xC1, 0xC1, 0xC1,
};

uint32 ch1_long_idx = 0;

uint8 cmd40_response = 40;

uint8 no_data_response = 0;

uint16 channel1_signal_data_1[1500];
uint16 channel1_signal_data_2[1500];

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_write_cmd(uint8 command)
{
  int i;
  
  //Set the new command as current
  fpga_data.current_command = command;

  //Decide on which action to take
  switch(fpga_data.current_command)
  {
    case 0x14:
      fpga_data.read_count = 2;
      fpga_data.read_ptr = fpga_data.cmd0x14count;
      break;

    case 0x20:  //Channel 1
      if(fpga_data.channel1_trace_data)
      {
        uint32 seekpoint = fpga_data.channel1_sample_buffer_index * 6080;
        
        fseek(fpga_data.channel1_trace_data, seekpoint, SEEK_SET);
        
        fread(channel1_signal_data_1, 2, 1500, fpga_data.channel1_trace_data);
      }
      
      fpga_data.read_count = 3000;
      fpga_data.read_ptr = (uint8 *)channel1_signal_data_1;
      break;

    case 0x21:
      if(fpga_data.channel1_trace_data)
      {
        uint32 seekpoint = (fpga_data.channel1_sample_buffer_index * 6080) + 3040;
        
        fseek(fpga_data.channel1_trace_data, seekpoint, SEEK_SET);
        
        fread(channel1_signal_data_2, 2, 1500, fpga_data.channel1_trace_data);
      }
      
      fpga_data.read_count = 3000;
      fpga_data.read_ptr = (uint8 *)channel1_signal_data_2;
      break;

    case 0x22:
        fpga_data.read_count = 1;
        fpga_data.read_ptr = &no_data_response;
      break;

    case 0x23:
        fpga_data.read_count = 1;
        fpga_data.read_ptr = &no_data_response;
      break;

    case 0x24:
      fpga_data.read_count = 10;
      fpga_data.read_ptr = &scope_ch1_long_data[ch1_long_idx];

      ch1_long_idx += 10;

      if(ch1_long_idx > sizeof(scope_ch1_long_data))
        ch1_long_idx = 0;
      break;

    case 0x26:
      fpga_data.read_count = 1;
      fpga_data.read_ptr = &cmd40_response;
      break;

    case 0x38:
      //Set brightness
      break;

    case 0x41:
      //Read touch panel coordinates register address
      fpga_data.read_count = 2;
      fpga_data.read_ptr = tp_coord_reg;
      break;

    case 0x64:
      fpga_data.param_mode = PARAM_MODE_READ;
      break;

    case 0x65:
      fpga_data.param_mode = PARAM_MODE_WRITE;
      break;

    case 0x66:
      //Start the process based on the mode
      if(fpga_data.param_mode == PARAM_MODE_READ)
      {
        //Check if this is the first read after start up
        if(fpga_data.param_state == PARAM_STATE_NOT_INIT)
        {
          //Set it for reading
          fpga_data.param_data[3] = fpga_data.param_crypt;

          //Signal parameter storage has been initialized
          fpga_data.param_state = PARAM_STATE_INIT;
        }
        else
        {
          switch(fpga_data.param_id)
          {
            case 0x0B:
              //This one depends on data coming from the scope
              fpga_data.param_data[3] = 0;
              fpga_data.param_data[4] = 0;
              fpga_data.param_data[5] = 0;
              
              switch(fpga_data.param_0x0B_data)
              {
                case 0:
                  fpga_data.param_data[6] = 0xAD;
                  break;
                  
                case 1:
                  fpga_data.param_data[6] = 0xAF;
                  break;
                  
                case 2:
                case 3:
                  fpga_data.param_data[6] = 0xB4;
                  break;
                  
                default:
                  fpga_data.param_data[6] = 0xB8;
                  break;
              }
              break;
              
            case 0x0C:
              fpga_data.param_data[3] = 0;
              fpga_data.param_data[4] = 0;
              fpga_data.param_data[5] = 0;
              fpga_data.param_data[6] = 0x20;
              break;
              
            case 0x0D:
              fpga_data.param_data[3] = 0;
              fpga_data.param_data[4] = 0;
              fpga_data.param_data[5] = 0;
              fpga_data.param_data[6] = 0x22;
              break;
          }

          //Add the crypt byte to the data
          fpga_data.param_data[0] = fpga_data.param_crypt;

          //Invert it for the crypting
          fpga_data.param_crypt = ~fpga_data.param_crypt;

          //Decide what size descriptor needs to be returned
          if(fpga_data.param_data[3])
          {
            //More than 24 bits used then use 0xAA
            fpga_data.param_data[1] = 0xAA;
          }
          else if(fpga_data.param_data[4])
          {
            //More than 16 bits but less than 24 bits used then use 0xA5
            fpga_data.param_data[1] = 0xA5;
          }
          else if(fpga_data.param_data[5])
          {
            //More than 8 bits but less than 16 bits used then use 0x5A
            fpga_data.param_data[1] = 0x5A;
          }
          else
          {
            //8 bits or less used then use 0x55
            fpga_data.param_data[1] = 0x55;
          }

          //Calculate the checksum
          fpga_data.param_data[2] = fpga_data.param_crypt + fpga_data.param_data[1] + fpga_data.param_data[3] + fpga_data.param_data[4] + fpga_data.param_data[5] + fpga_data.param_data[6];

          //Crypt the data
          for(i=1;i<7;i++)
          {
            fpga_data.param_data[i] ^= fpga_data.param_crypt;
          }  
        }
      }
      else
      {
        //Get the parameter id for file handling
        fpga_data.param_id = (fpga_data.param_data[1] ^ fpga_data.param_crypt) >> 2;
        
        switch(fpga_data.param_id)
        {
          case 0x0B:
            //No checks, just get the data for now
            fpga_data.param_0x0B_data = fpga_data.param_data[6] ^ fpga_data.param_crypt;
            break;
        }
      }
      break;

    case 0x67:
      //Since the process is synchronous just respond with ready status
      fpga_data.read_ptr = &param_status_byte;
      fpga_data.read_count = 1;
      break;

  
    case 0x0A:  //For this one the software tests against one and continues if so, else it waits for touch
      //Select next trace buffer
      fpga_data.channel1_sample_buffer_index++;
      
      //Only 50 buffers
      if(fpga_data.channel1_sample_buffer_index >= 50)
      {
        fpga_data.channel1_sample_buffer_index = 0;
      }
      
      //Since the process is synchronous just respond with ready status
      fpga_data.read_ptr = &param_status_byte;
      fpga_data.read_count = 1;
      break;

    case 0x68:
    case 0x69:
    case 0x6A:
    case 0x6B:
    case 0x6C:
    case 0x6D:
    case 0x6E:
      if(fpga_data.param_mode == PARAM_MODE_READ)
      {
        fpga_data.read_ptr = &fpga_data.param_data[fpga_data.current_command - 0x68];
        fpga_data.read_count = 1;
      }
      else
      {
        fpga_data.write_ptr = &fpga_data.param_data[fpga_data.current_command - 0x68];
        fpga_data.write_count = 1;
      }
      break;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

uint8 fpga_read_cmd(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_write_byte(uint8 data)
{
  //Store the data in the target register if needed
  if(fpga_data.write_count)
  {
    *fpga_data.write_ptr = data;

    fpga_data.write_ptr++;
    fpga_data.write_count--;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

uint8 fpga_read_byte(void)
{
  uint8 retval = 0xFF;

  if(fpga_data.read_count)
  {
    retval = *fpga_data.read_ptr;

    fpga_data.read_ptr++;
    fpga_data.read_count--;
  }

  return(retval);
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_write_short(uint16 data)
{
  fpga_write_byte((data >> 8) & 0xFF);
  fpga_write_byte(data & 0xFF);
}

//----------------------------------------------------------------------------------------------------------------------------------

uint16 fpga_read_short(void)
{
  return((fpga_read_byte() << 8) | fpga_read_byte());
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_write_int(uint32 data)
{
  fpga_write_byte((data >> 24) & 0xFF);
  fpga_write_byte((data >> 16) & 0xFF);
  fpga_write_byte((data >> 8) & 0xFF);
  fpga_write_byte(data & 0xFF);
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_backlight_brightness(uint16 brightness)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_translated_brightness(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

uint16 fpga_get_version(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_check_ready(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_enable_system(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_channel_1_enable(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_channel_1_coupling(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_channel_1_voltperdiv(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_channel_1_offset(void)
{
  uint32 offset;

  //Do some fractional calculation with sign correction?????
  //For now a copy of what Ghidra made of it
  offset = ((uint64)((uint64)0x51EB851F * (uint64)(scopesettings.channel1.traceoffset * channel1_calibration_factor)) >> 37);
  offset = (signal_adjusters[0] * offset) / signal_adjusters[scopesettings.channel1.voltperdiv];
  
  //Send the command for channel 1 offset to the FPGA
  fpga_write_cmd(0x32);

  //Write the calibrated offset data  
  fpga_write_short(channel1_calibration_data[scopesettings.channel1.voltperdiv] - offset);
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_channel_2_enable(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_channel_2_coupling(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_channel_2_voltperdiv(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_channel_2_offset(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_trigger_timebase(uint32 timeperdiv)
{
  //Open a signal file based on the new time base setting
  char file_name[256];
  
  //Check if file already open
  if(fpga_data.channel1_trace_data)
  {
    //Close it before opening the new one
    fclose(fpga_data.channel1_trace_data);
  }
  
  snprintf(file_name, 256, "signals/fnirsi_samples_%d.bin", timeperdiv + 7);

  //Open the new file
  fpga_data.channel1_trace_data = fopen(file_name, "rb");
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_trigger_channel(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_trigger_edge(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_swap_trigger_channel(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_trigger_level(void)
{
  uint32 voltperdiv;
  uint32 traceoffset;
  uint32 adjuster;
  uint32 level;
  
  //Check which channel is used for triggering
  if(scopesettings.triggerchannel == 0)
  {
    //Channel 1, so use its data
    voltperdiv  = scopesettings.channel1.voltperdiv;
    traceoffset = scopesettings.channel1.traceoffset;
  }
  else
  {
    //Channel 2, so use its data
    voltperdiv  = scopesettings.channel2.voltperdiv;
    traceoffset = scopesettings.channel2.traceoffset;
  }
  
  //Get the adjuster for the level based on the volts per div setting
  adjuster = signal_adjusters[voltperdiv];
  
  //Process the data different when on lowest volts per div setting
  if(voltperdiv == 6)
  {
    //check if trigger trace offset below channel trace offset
    if(scopesettings.triggeroffset < traceoffset)
    {
      //Below the trace
      //Use the trace screen offset minus half the delta of the screen offsets and scale it with the signal adjuster setting
      level = ((traceoffset - ((traceoffset - scopesettings.triggeroffset) / 2)) * 100) / adjuster;
    }
    else
    {
      //Above the trace
      //Use the trace screen offset plus half the delta of the screen offsets and scale it with the signal adjuster setting
      level = ((traceoffset + ((scopesettings.triggeroffset - traceoffset) / 2)) * 100) / adjuster;
    }
  }
  else
  {
    //Scale the screen offset with the signal adjuster setting
    level = (scopesettings.triggeroffset * 100) / adjuster;
  }
  
  //This needs to hold the adjusted level since the sample data checked is also adjusted
  //Translate the trigger channels volts per div setting
  adjuster = fpga_read_parameter_ic(0x0B, voltperdiv) & 0x0000FFFF;
  
  //Store the result in the global settings
  scopesettings.triggerlevel = (41954 * level * adjuster) >> 22;
  
  //Send the command for setting the trigger level to the FPGA
  fpga_write_cmd(0x17);
  
  //Write the actual level to the FPGA
  fpga_write_byte(level);
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_trigger_mode(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_long_timebase(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_short_timebase(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

uint16 fpga_prepare_for_transfer(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_read_adc1_data(uint8 command, uint16 *buffer, int32 count, uint32 signaladjust, uint32 multiply, uint32 offset)
{
  register uint32 sample;
  
  //Send a command for getting trace data from the FPGA
  fpga_write_cmd(command);

  //Start on the second sample location
  //First ADC samples after the second ADC
  buffer++;
  
  //Read the data as long as there is count
  while(count)
  {
    //Read the data
    sample = fpga_read_byte() | (fpga_read_byte() << 8);
    
    //Adjust the data for the correct voltage per div setting
    sample = (41954 * sample * signaladjust) >> 22;

    //Check on lowest volt per div setting for doubling and offsetting
    if(multiply)
    {
      //Multiply the sample by two
      sample <<= 1;

      //Correct the position for the set trace offset
      //Check if the data is smaller then the offset
      if(sample < offset)
      {
        //If so limit to top of the screen
        sample = 0;
      }
      else
      {
        //Else take of the offset
        sample -= offset;
      }
    }
    
    //Store the data
    *buffer = sample;

    //Skip a sample for ADC2 data
    buffer += 2;
    
    //One read done
    count--;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_read_adc2_data(uint8 command, uint16 *buffer, int32 count, uint32 signaladjust, uint32 multiply, uint32 offset, PADC2CALIBRATIONDATA calibration)
{
  register uint32 sample;
  
  //Get the compensation into a register for better performance
  register uint32 compensation = calibration->compensation;
  
  //Send a command for getting trace data from the FPGA
  fpga_write_cmd(command);

  //Read the data as long as there is count
  while(count)
  {
    //Read the data
    sample = fpga_read_byte() | (fpga_read_byte() << 8);
    
    //Check on what to do with the calibration compensation
    if(calibration->flag == 0)
    {
      //Check if there is data to compensate
      if(sample > compensation)
      {
        //Store the compensated sample to the lower entries
        sample -= compensation;
      }
      else
      {
        //Zero the sample if to small
        sample = 0;
      }
    }
    else
    {
      //Compensate and store the sample
      sample += compensation;
    }
    
    //Adjust the data for the correct voltage per div setting
    sample = (41954 * sample * signaladjust) >> 22;

    //Check on lowest volt per div setting for doubling and offsetting
    if(multiply)
    {
      //Multiply the sample by two
      sample <<= 1;

      //Correct the position for the set trace offset
      //Check if the data is smaller then the offset
      if(sample < offset)
      {
        //If so limit to top of the screen
        sample = 0;
      }
      else
      {
        //Else take of the offset
        sample -= offset;
      }
    }
    
    //Store the data
    *buffer = sample;

    //Skip a sample since it holds ADC1 data
    buffer += 2;
    
    //One read done
    count--;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

uint16 fpga_average_trace_data(uint8 command)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_battery_level(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_init_parameter_ic(void)
{
  int i;
  
  //Prepare FPGA for reading the parameter ic
  fpga_write_cmd(0x64);
  fpga_write_cmd(0x64);
  
  //Need a delay here. In the scope it is delay(20) but not sure what the base of the delay is
  //It works without this one
//  fpga_delay(10);
  
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

void fpga_write_parameter_ic(uint8 id, uint32 value)
{
  uint8 length = 3;
  int i;

  ByteAndBits crypt_in;
  ByteAndBits crypt_out;
  
  //First data byte is the crypt byte
  parameter_buffer[0] = parameter_crypt_byte;

  //Load the data bytes with the value
  parameter_buffer[3] = (uint8)(value >> 24);
  parameter_buffer[4] = (uint8)(value >> 16);
  parameter_buffer[5] = (uint8)(value >> 8);
  parameter_buffer[6] = (uint8)(value);

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

uint32 fpga_read_parameter_ic(uint8 id, uint32 value)
{
  int32  i = 0;
  int32  j = 0;
  int32  unvalid = 0;
  uint32 rcv_value;
  uint8  checksum;
  
  //Max retry on write read sequence
  while(i < 6)
  {
    //Start the sequence with a write
    fpga_write_parameter_ic(id, value);
    
    //Need a delay here. In the scope it is delay(500) but not sure what the base of the delay is
    //This one is actually needed to allow the parameter ic to respond. Tweaked with a scope attached to make sure no resend is done
//    fpga_delay(500);
    
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
      //It works without this one
//      fpga_delay(10);

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
      //It works without this one
//      fpga_delay(50);
      
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

void sys_init_display(uint16 xsize, uint16 ysize, uint16 *address)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void tp_i2c_setup(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void tp_i2c_read_status(void)
{
  //Check if stop of process requested
  if(quit_scopeprocessing_thread_on_zero == 0)
  {
    //If so check if there was no touch
    if(havetouch == 0)
    {
      //Fake coordinates to force any menu to close and the process to stop
      havetouch = 1;

      //Check if the loop device is opened (USB connected)
      if(loop_device_open)
      {
        //Signal touch to turn it off
        xtouch = 120;
        ytouch = 250;
      }
      else
      {
        xtouch = 10;
        ytouch = 470;
      }
    }
    else
    {
      //Otherwise remove touch when stop is requested
      havetouch = 0;
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void tp_i2c_wait_for_touch_release(void)
{
  //Wait until touch is released or process stopped
  while(havetouch && quit_scopeprocessing_thread_on_zero);
}

//----------------------------------------------------------------------------------------------------------------------------------

void usb_device_init(void)
{
}

//----------------------------------------------------------------------------------------------------------------------------------

void usb_device_disable(void)
{
  if(loop_device_open)
  {
    //Not the most elegant solution but it works more or less
    system("sudo umount /dev/loop0p1");
    system("sudo losetup -d /dev/loop0");
    
    loop_device_open = 0;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void usb_device_enable(void)
{
  if(loop_device_open == 0)
  {
    //Not the most elegant solution but it works more or less
    system("sudo losetup /dev/loop0 scope_sd_card.img");
    system("sudo partprobe /dev/loop0");
    
    loop_device_open = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

//Definitions of physical drive number for each drive
#define DEV_FILE     0 

DSTATUS disk_initialize(BYTE pdrv)
{
  //Check if the SD card device is addressed
  if(pdrv == DEV_FILE)
  {
    if(sd_emu_file == NULL)
    {
      //Try to initialize the interface and the card
      if((sd_emu_file = fopen("scope_sd_card.img", "rb+")) == NULL)
      {
        //Some error then signal no disk
        return(STA_NODISK);
      }
    }
  }
  else
  {
    //Not the SD card emulation drive then no init
    return(STA_NOINIT);
  }
  
  //All went well
  return(RES_OK);
}

//----------------------------------------------------------------------------------------------------------------------------------

void disk_exit(void)
{
  //Check if the sd card emulation file is open
  if(sd_emu_file)
  {
    //Close it if so
    fclose(sd_emu_file);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

DSTATUS disk_status(BYTE pdrv)
{
  //Check if the sd card emulation file is opened
  if(sd_emu_file == NULL)
  {
    //Not then signal no disk available
    return(STA_NODISK);
  }
  
  //Else everything ok
  return(RES_OK);
}

//----------------------------------------------------------------------------------------------------------------------------------

DRESULT disk_read(BYTE pdrv, BYTE *buff, LBA_t sector, UINT count)
{
  //Check if the SD card device is addressed
  if(pdrv == DEV_FILE)
  {
    //Check if the sd card emulation file is opened
    if(sd_emu_file == NULL)
    {
      //Not then signal no disk available
      return(STA_NODISK);
    }
    
    //Seek the requested location
    if(fseek(sd_emu_file, sector * 512, SEEK_SET))
    {
      //Error while seeking
      return(RES_ERROR);
    }
    
    //Read the data from the card emulation file
    fread(buff, 1, count * 512, sd_emu_file);
  }
  else
  {
    //Not the SD card drive selected
    return(RES_PARERR);
  }
  
  //All went well
  return(RES_OK);
}

//----------------------------------------------------------------------------------------------------------------------------------

DRESULT disk_write(BYTE pdrv, const BYTE *buff, LBA_t sector, UINT count)
{
  //Check if the SD card device is addressed
  if(pdrv == DEV_FILE)
  {
    //Check if the sd card emulation file is opened
    if(sd_emu_file == NULL)
    {
      //Not then signal no disk available
      return(STA_NODISK);
    }
    
    //Seek the requested location
    if(fseek(sd_emu_file, sector * 512, SEEK_SET))
    {
      //Error while seeking
      return(RES_ERROR);
    }
    
    //Write the data to the card emulation file
    fwrite(buff, 1, count * 512, sd_emu_file);
  }
  else
  {
    //Not the SD card drive selected
    return(RES_PARERR);
  }
  
  //All went well
  return(RES_OK);
}

//----------------------------------------------------------------------------------------------------------------------------------

DRESULT disk_ioctl(BYTE pdrv, BYTE cmd, void *buff)
{
  //Check if the SD card device is addressed
  if(pdrv == DEV_FILE)
  {
    //Check if the sd card emulation file is opened
    if(sd_emu_file == NULL)
    {
      //Not then signal no disk available
      return(STA_NODISK);
    }
    
    //Check if buffer is valid
    if(buff)
    {
      if(cmd == CTRL_SYNC)
      {
        return(RES_OK);
      }
      else if(cmd == GET_SECTOR_COUNT)
      {
        //Seek the requested location
        if(fseek(sd_emu_file, 0, SEEK_END))
        {
          //Error while seeking
          return(RES_ERROR);
        }
        
        *(uint32 *)buff = (ftell(sd_emu_file) + 511) / 512;
        
        return(RES_OK);
      }
    }
  }
  
  //Invalid input parameters given
  return(RES_PARERR);
}

//----------------------------------------------------------------------------------------------------------------------------------

DWORD get_fattime (void)
{
  //Some date and time value
  return(1349957149);
}

//----------------------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------------------
