//----------------------------------------------------------------------------------------------------------------------------------
//The touch panel on the scope is not connected to a true I2C interface, so bit banging is used
//
//The connections are:
//  PA0:  RESET
//  PA1:  INT
//  PA2:  SDA
//  PA3:  SCL
//
//The touch panel uses a GT911 controller and has a special startup sequence to set the I2C device address
//
//----------------------------------------------------------------------------------------------------------------------------------

#include "fwb_variables.h"
#include "fwb_touchpanel.h"

//----------------------------------------------------------------------------------------------------------------------------------

void tp_i2c_setup(void)
{
  uint8 command;
  
  //Make sure all SCL and SDA are at a high level and RESET and INT  are at a low level before enabling as output 
  *PORT_A_DATA_REG = 0x0000000C;
  
  //Setup all port A pins for output
  *PORT_A_CFG_REG = 0xFFFF1111;
  
  //Wait for 100uS
  tp_delay(200);

  //Set INT high for device address 0x14 select
  *PORT_A_DATA_REG = 0x0000000E;
  
  //Wait for 20mS
  tp_delay(20000);
  
  //Set RESET high for device activation
  *PORT_A_DATA_REG = 0x0000000F;

  //Wait for ~5mS
  tp_delay(10000);
  
  //Set INT as input and keep the rest as output
  *PORT_A_CFG_REG = 0xFFFF1101;

  //Wait for ~50mS
  tp_delay(100000);

  //Start communication by sending 2 to the command register
  command = 2;
  tp_i2c_send_data(TP_CMD_REG, &command, 1);
  
  //Need to read the touch panel configuration here
  tp_i2c_read_data(TP_CFG_VERSION_REG, tp_config_data, sizeof(tp_config_data));

  //Wait for ~100mS
  tp_delay(200000);

  //Start scanning by sending 0 to the command register
  command = 0;
  tp_i2c_send_data(TP_CMD_REG, &command, 1);
}

//----------------------------------------------------------------------------------------------------------------------------------

void tp_i2c_send_data(uint16 reg_addr, uint8 *buffer, uint32 size)
{
  //Start a communication sequence
  tp_i2c_send_start();
  
  //Send the device address for writing
  tp_i2c_send_byte(TP_DEVICE_ADDR_WRITE);

  //Send the register address high byte first
  tp_i2c_send_byte(reg_addr >> 8);

  //Send the low byte second
  tp_i2c_send_byte(reg_addr);
  
  //Send the data bytes
  while(size)
  {
    //Send a byte
    tp_i2c_send_byte(*buffer);
    
    //Point to the next one
    buffer++;
    
    //One byte done
    size--;
  }
  
  //Stop the communication sequence
  tp_i2c_send_stop();
}

//----------------------------------------------------------------------------------------------------------------------------------

void tp_i2c_read_data(uint16 reg_addr, uint8 *buffer, uint32 size)
{
  //Start a communication sequence
  tp_i2c_send_start();

  //Send the device address for writing
  tp_i2c_send_byte(TP_DEVICE_ADDR_WRITE);

  //Send the register address high byte first
  tp_i2c_send_byte(reg_addr >> 8);

  //Send the low byte second
  tp_i2c_send_byte(reg_addr);

  //Re start the communication sequence for reading
  tp_i2c_send_start();
  
  //Send the device address for writing
  tp_i2c_send_byte(TP_DEVICE_ADDR_READ);
  
  //Read all the requested bytes
  while(size)
  {
    //Read a byte from the device
    *buffer = tp_i2c_read_byte();
    
    //Point to the next entry in the buffer
    buffer++;
    
    //One byte done
    size--;
    
    //Check if more data coming
    if(size)
    {
      //Send an ack if so
      tp_i2c_clock_ack();
    }
    else
    {
      //Send a nack if finished
      tp_i2c_clock_nack();
    }
  }
  
  //Stop the communication sequence
  tp_i2c_send_stop();
}

//----------------------------------------------------------------------------------------------------------------------------------

void tp_i2c_send_start(void)
{
  //Make sure INT is set as input and the rest of the signals as output
  *PORT_A_CFG_REG = 0xFFFF1101;

  //Make SDA high
  *PORT_A_DATA_REG |= 0x00000004;

  //Wait for a while
  tp_delay(TP_DATA_DELAY);
  
  //Make SCL high
  *PORT_A_DATA_REG |= 0x00000008;
  
  //Wait for a while
  tp_delay(TP_CLOCK_DELAY);
  
  //Make SDA low
  *PORT_A_DATA_REG &= 0x0000000B;
  
  //Wait for a while
  tp_delay(TP_DATA_DELAY);

  //Make SCL low
  *PORT_A_DATA_REG &= 0x00000007;
  
  //Wait for a while
  tp_delay(TP_DATA_DELAY);
}

//----------------------------------------------------------------------------------------------------------------------------------

void tp_i2c_send_stop(void)
{
  //Make sure INT is set as input and the rest of the signals as output
  *PORT_A_CFG_REG = 0xFFFF1101;

  //Make SDA low
  *PORT_A_DATA_REG &= 0x0000000B;

  //Wait for a while
  tp_delay(TP_DATA_DELAY);
  
  //Make SCL high
  *PORT_A_DATA_REG |= 0x00000008;
  
  //Wait for a while
  tp_delay(TP_CLOCK_DELAY);
  
  //Make SDA high
  *PORT_A_DATA_REG |= 0x00000004;
  
  //Wait for a while
  tp_delay(TP_DATA_DELAY);
}

//----------------------------------------------------------------------------------------------------------------------------------

void tp_i2c_clock_ack(void)
{
  //Make sure INT is set as input and the rest of the signals as output
  *PORT_A_CFG_REG = 0xFFFF1101;
  
  //Make SDA low
  *PORT_A_DATA_REG &= 0x0000000B;
  
  //Wait for a while
  tp_delay(TP_DATA_DELAY);

  //Make SCL high
  *PORT_A_DATA_REG |= 0x00000008;
  
  //Wait for a while
  tp_delay(TP_CLOCK_DELAY);

  //Make SCL low
  *PORT_A_DATA_REG &= 0x00000007;
  
  //Wait for a while
  tp_delay(TP_DATA_DELAY);
}

//----------------------------------------------------------------------------------------------------------------------------------

void tp_i2c_clock_nack(void)
{
  //Make sure INT is set as input and the rest of the signals as output
  *PORT_A_CFG_REG = 0xFFFF1101;
  
  //Make SDA high
  *PORT_A_DATA_REG |= 0x00000004;
  
  //Wait for a while
  tp_delay(TP_DATA_DELAY);

  //Make SCL high
  *PORT_A_DATA_REG |= 0x00000008;
  
  //Wait for a while
  tp_delay(TP_CLOCK_DELAY);

  //Make SCL low
  *PORT_A_DATA_REG &= 0x00000007;
  
  //Wait for a while
  tp_delay(TP_DATA_DELAY);
}

//----------------------------------------------------------------------------------------------------------------------------------

void tp_i2c_send_byte(uint8 data)
{
  int i;
  
  //Make sure INT is set as input and the rest of the signals as output
  *PORT_A_CFG_REG = 0xFFFF1101;

  //Send 8 bits
  for(i=0;i<8;i++)
  {
    //Check if bit to send is high or low
    if(data & 0x80)
    {
      //Make SDA high
      *PORT_A_DATA_REG |= 0x00000004;
    }
    else
    {
      //Make SDA low
      *PORT_A_DATA_REG &= 0x0000000B;
    }
  
    //Wait for a while
    tp_delay(TP_DATA_DELAY);
    
    //Make SCL high
    *PORT_A_DATA_REG |= 0x00000008;

    //Wait for a while
    tp_delay(TP_CLOCK_DELAY);

    //Make SCL low
    *PORT_A_DATA_REG &= 0x00000007;

    //Wait for a while
    tp_delay(TP_DATA_DELAY);
    
    //Select the next bit to send
    data <<= 1;
  }
  
  //Clock the ack bit
  tp_i2c_clock_ack();
}

//----------------------------------------------------------------------------------------------------------------------------------

uint8 tp_i2c_read_byte(void)
{
  int   i;
  uint8 data = 0;
  
  //Set SDA for input
  *PORT_A_CFG_REG = 0xFFFF1001;
  
  //Read all the bits
  for(i=0;i<8;i++)
  {
    //Make SCL high
    *PORT_A_DATA_REG |= 0x00000008;

    //Wait for a while
    tp_delay(TP_DATA_DELAY);
    
    //Shift the bits to make room for the next one
    data <<= 1;
    
    //Put in the new bit
    data |= (*PORT_A_DATA_REG & 0x00000004) >> 2;

    //Wait for a while
    tp_delay(TP_DATA_DELAY);
    
    //Make SCL low
    *PORT_A_DATA_REG &= 0x00000007;

    //Wait for a while
    tp_delay(TP_CLOCK_DELAY);
  }
 
  return(data);
}

//----------------------------------------------------------------------------------------------------------------------------------
//A count of 4 is approximately 3uS when running on 600MHz with cache enabled

void tp_delay(uint32 usec)
#if 0
{
  int i;
  
  for(i=0;i<usec;i++);
}
#else
{
  //Lower then 64 does not work properly, because the panel fails to hold the new configuration when coming from the original code
  unsigned int loops = usec * 90;

  __asm__ __volatile__ ("1:\n" "subs %0, %1, #1\n"  "bne 1b":"=r"(loops):"0"(loops));
}
#endif
  
//----------------------------------------------------------------------------------------------------------------------------------
