
#include <stdio.h>      // standard input / output functions
#include <stdlib.h>
#include <string.h>     // string function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions

#include <sys/ipc.h> 
#include <sys/shm.h> 

#include <stdarg.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>


typedef struct tagByteBits    ByteBits;

typedef union tagByteAndBits  ByteAndBits;

struct tagByteBits
{
  u_int8_t    b0:1;
  u_int8_t    b1:1;
  u_int8_t    b2:1;
  u_int8_t    b3:1;
  u_int8_t    b4:1;
  u_int8_t    b5:1;
  u_int8_t    b6:1;
  u_int8_t    b7:1;
};

union tagByteAndBits
{
  u_int8_t  byte;
  ByteBits  bits;
};

typedef struct tagSaleaeBinData  SaleaeBinData;

struct tagSaleaeBinData
{
  u_int8_t  identifier[8];
  int32_t   version;
  int32_t   type;
  u_int32_t initial_state;
  double    begin_time;
  double    end_time;
  u_int64_t num_transitions;
};

typedef union tagbyteconv byteconv;

union tagbyteconv
{
  u_int8_t  b[8];
  u_int64_t u64;
  double    d;
};

u_int32_t convertword(u_int8_t *ptr)
{
  return(ptr[0] | (ptr[1] << 8) | (ptr[2] << 16) | (ptr[3] << 24));
}

u_int64_t convertdword(u_int8_t *ptr)
{
  byteconv conv;
  
  memcpy(conv.b, ptr, 8);
  
  return(conv.u64);
}

double convertdouble(u_int8_t *ptr)
{
  byteconv conv;
  
  memcpy(conv.b, ptr, 8);
  
  return(conv.d);
}

//I2C state machine states
#define I2C_STATE_IDLE         0
#define I2C_STATE_GET_BITS     1
#define I2C_STATE_GET_ACK      2

#define I2C_NUM_BITS           8


//Since the data is not up to I2C spec, but the format is known, special action is needed to make it work
//After receiving a start the check for re start or stop needs to be delayed.
//A packet consists of 8 bytes, so add a byte counter and once that has been fulfilled check for start or stop

//In the output only the actual bytes are needed in a { .... }, format

int main(int argc, char** argv)
{
  u_int8_t scldata[4000000];
  u_int8_t sdadata[4000000];
  int len;
  int process = 1;
  int j;
  
  u_int8_t  data[10];
  u_int8_t  crypt_byte;
  u_int8_t  checksum;
  
  SaleaeBinData scl;
  SaleaeBinData sda;
  
  int scl_state;
  int sda_state;
  
  double scl_time_1;
  double sda_time_1;
  double sda_time_2;
  
  u_int8_t *sclptr;
  u_int8_t *sdaptr;
  
  u_int64_t scl_transition;
  u_int64_t sda_transition;
  
  //Variables for capturing I2C data
  u_int8_t i2c_currentbyte = 0;
  u_int8_t i2c_currentbit = 0;
  u_int8_t i2c_state = I2C_STATE_IDLE;
  u_int8_t i2c_bytes = 0;

  ByteAndBits crypt_in;
  ByteAndBits crypt_out;
  
  u_int32_t value;
  
  FILE *fp = fopen("/home/peter/Downloads/FNIRSI 1013D/I2C_Capture/03_just-Brightness_bySteps/digital_2.bin", "rb");
  
  if(fp)
  {
    len = fread(scldata, 1, sizeof(scldata), fp);
    fclose(fp);
    
    if(len > 44)
    {
      memcpy(scl.identifier, scldata, 8);
      
      scl.version         = convertword(&scldata[8]);
      scl.type            = convertword(&scldata[12]);
      scl.initial_state   = convertword(&scldata[16]);
      scl.begin_time      = convertdouble(&scldata[20]);
      scl.end_time        = convertdouble(&scldata[28]);
      scl.num_transitions = convertdword(&scldata[36]);
      
      if(scl.num_transitions)
      {
        //Take of the header
        len -= 44;
        
        //Check if there is enough data
        if((scl.num_transitions * 8) != len)
          process = 0;
      }
      else
        process = 0;
    }
  }
  else
    process = 0;
  
  //Check if scl is good to go
  if(process)
  {
    fp = fopen("/home/peter/Downloads/FNIRSI 1013D/I2C_Capture/03_just-Brightness_bySteps/digital_3.bin", "rb");
    
    if(fp)
    {
      len = fread(sdadata, 1, sizeof(sdadata), fp);
      fclose(fp);

      if(len > 44)
      {
        memcpy(sda.identifier, sdadata, 8);

        sda.version         = convertword(&sdadata[8]);
        sda.type            = convertword(&sdadata[12]);
        sda.initial_state   = convertword(&sdadata[16]);
        sda.begin_time      = convertdouble(&sdadata[20]);
        sda.end_time        = convertdouble(&sdadata[28]);
        sda.num_transitions = convertdword(&sdadata[36]);

        if(sda.num_transitions)
        {
          //Take of the header
          len -= 44;

          //Check if there is enough data
          if((sda.num_transitions * 8) != len)
            process = 0;
        }
        else
          process = 0;
      }
    }
    else
      process = 0;
  }

  //Check if both scl and sda good to go
  if(process)
  {
    fp = fopen("i2c_data_out_5_a.txt", "w");
  }
    
  if(fp)
  {
    scl_state = scl.initial_state;
    sda_state = sda.initial_state;
    
    scl_transition = 0;
    sda_transition = 0;
    
    //Point to first transition time
    sclptr = &scldata[44];
    sdaptr = &sdadata[44];

    sda_time_1 = sda.begin_time;
    
    //Process until data is gone
    while((scl_transition < scl.num_transitions) && (sda_transition < sda.num_transitions))
    {
      //Get transition times
      scl_time_1 = convertdouble(sclptr);
      sda_time_2 = convertdouble(sdaptr);
        
      //Synchronize sda transition near scl transition
      while((sda_time_1 < scl_time_1) && (sda_time_2 <= scl_time_1) && (sda_transition < sda.num_transitions))
      {
        //Shift sda to next state
        sda_state ^= 1;
        
        //Move the time
        sda_time_1 = sda_time_2;
        
        //Point to next time
        sdaptr += 8;
        
        //Load the next time
        sda_time_2 = convertdouble(sdaptr);
        
        //Add one transition
        sda_transition++;
        
        //Handle sda transition as needed here to determine start and stop
        //On scl high a start or stop state is signaled
        //Since the data is way of I2C specs special filtering is needed to suppress faulty starts and stops
        if((scl_state) && (scl_time_1 != sda_time_1) && ((i2c_bytes == 0) || (i2c_bytes >= 9)) && ((i2c_currentbit >= 1) || (i2c_bytes == 0)))
        {
          //In any case get the status of the SDA pin to see which condition has been send
          if(sda_state)
          {
            //Stop condition so switch to idle state
            i2c_state = I2C_STATE_IDLE;
          }
          else
          {
            //On SDA low a start condition is send
            fprintf(fp, "{ ");

            //Clear the data byte and bit indicator
            i2c_currentbyte = 0;
            i2c_currentbit = 0;
            
            //Start the bytes counter filter
            i2c_bytes = 1;

            //Switch to get bit state
            i2c_state = I2C_STATE_GET_BITS;
          }
        }
      }
      
      //Toggle the scl state
      scl_state ^= 1;
      
      //Signals a transition from low to high on scl
      if(scl_state)
      {
        if(i2c_state == I2C_STATE_GET_BITS)
        {
          //Get the bit from SDA and put it in the current byte
          i2c_currentbyte = (i2c_currentbyte << 1) | sda_state;
          
          //Signal another bit is received
          i2c_currentbit++;

          //Check if it was the last bit
          if(i2c_currentbit >= I2C_NUM_BITS)
          {
            fprintf(fp, "0x%02X", i2c_currentbyte);
            
            //Save for decrypt
            data[i2c_bytes] = i2c_currentbyte;
            
            //Clear the data byte and bit indicator
            i2c_currentbyte = 0;
            i2c_currentbit = 0;
            
            //Received one more byte
            i2c_bytes++;

            if(i2c_bytes < 9)
              fprintf(fp, ", ");
            else
            {
              fprintf(fp, " },");
            
              //Decrypt the message
              
              //Process the data based on action read or write
              if(data[1] == 0x01)
              {
                //Read
                crypt_byte = ~data[2];

                data[2] = crypt_byte;

                fprintf(fp, "{ 0x01, 0x%02X, ", data[2]);

                //Decrypt the bytes
                for(j=3;j<9;j++)
                {
                  //Decrypt the bytes
                  data[j] = data[j] ^ crypt_byte;

                  fprintf(fp, "0x%02X", data[j]);

                  if(j<8)
                    fprintf(fp, ", ");
                  else
                    fprintf(fp, " },");
                }

                checksum = data[2] + data[3] + data[5] + data[6] + data[7] + data[8];

                if(checksum == data[4])
                  fprintf(fp, "  //Checksum ok");
                else
                  fprintf(fp, "  //Checksum error: 0x%02X", checksum);
                
                //Can be done in a better way, but for now simple and readable
                if(data[3] == 0x55)
                  value = data[8];
                else if(data[3] == 0x5A)
                  value = (data[7] << 8) | data[8];
                else if(data[3] == 0xA5)
                  value = (data[6] << 16) | (data[7] << 8) | data[8];
                else if(data[3] == 0xAA)
                  value = (data[5] << 24) | (data[6] << 16) | (data[7] << 8) | data[8];
                
                fprintf(fp, "  Data: 0x%08X\n", value);
              }
              else
              {
                //Write
                crypt_in.byte = data[2];

                crypt_out.bits.b0 = crypt_in.bits.b5;
                crypt_out.bits.b1 = crypt_in.bits.b3;
                crypt_out.bits.b2 = crypt_in.bits.b7;
                crypt_out.bits.b3 = crypt_in.bits.b1;
                crypt_out.bits.b4 = crypt_in.bits.b6;
                crypt_out.bits.b5 = crypt_in.bits.b0;
                crypt_out.bits.b6 = crypt_in.bits.b4;
                crypt_out.bits.b7 = crypt_in.bits.b2;

                crypt_byte = crypt_out.byte;
                 
                fprintf(fp, "{ 0x00, 0x%02X, ", data[2] ^ crypt_byte);

                for(j=3;j<9;j++)
                {
                  fprintf(fp, "0x%02X", data[j] ^ crypt_byte);

                  if(j<8)
                    fprintf(fp, ", ");
                  else
                    fprintf(fp, " },");
                }

                checksum = data[2] + data[3] + data[5] + data[6] + data[7] + data[8];
                
                if(checksum == data[4])
                  fprintf(fp, "  //Checksum ok");
                else
                  fprintf(fp, "  //Checksum error: 0x%02X", checksum);

                //Get the id and length byte
                data[3] = data[3] ^ crypt_byte;

                //decode the data
                switch(data[3] & 0x03)
                {
                  case 0:
                    value = data[8] ^ crypt_byte;
                    break;
                    
                  case 1:
                    value = ((data[7] ^ crypt_byte) << 8) | (data[8]  ^ crypt_byte);
                    break;
                    
                  case 2:
                    value = ((data[6] ^ crypt_byte) << 16) | ((data[7] ^ crypt_byte) << 8) | (data[8] ^ crypt_byte);
                    break;
                    
                  case 3:
                    value = ((data[5] ^ crypt_byte) << 24) | ((data[6] ^ crypt_byte) << 16) | ((data[7] ^ crypt_byte) << 8) | (data[8] ^ crypt_byte);
                    break;
                }
                 
                fprintf(fp, "  Data: 0x%08X  Id: 0x%02X  Len: %d\n", value, data[3] >> 2, data[3] & 0x03);
              }
            }
            
            //Switch to get ack state
            i2c_state = I2C_STATE_GET_ACK;
          }
        }
        else if(i2c_state == I2C_STATE_GET_ACK)
        {
          //Switch to get bit state
          i2c_state = I2C_STATE_GET_BITS;
        }
        else
        {
          //Switch to idle state
          i2c_state = I2C_STATE_IDLE;
        }
      }
      
      //Select next scl transition
      sclptr += 8;

      //Add one transition
      scl_transition++;
    }
    
    fclose(fp);
  }
}

