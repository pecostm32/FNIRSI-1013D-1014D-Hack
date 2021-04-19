#include "fpga_control.h"

int main(void)
{
  int i;
  unsigned char cmd = 0x68;
  unsigned char data;
  
  fpga_init();

  while(1)
  {
    //Setup I2C for reading
    fpga_write_cmd(0x64);
    fpga_write_cmd(0x64);

    //Wait for the I2C system to be ready
    for(i=0;i<200;i++);

    //Start the I2C communication
    fpga_write_cmd(0x66);

    do
    {
      //Write command to read I2C status flag
      fpga_write_cmd(0x67);

      //Read the status flag
      i = fpga_read_byte();
    } while((i & 0x01) == 0);  //Keep doing it as long as it is 0

    //Read all the bytes from the I2C parameter storage device
    for(i=0;i<7;i++)
    {
      //Write command to read data
      fpga_write_cmd(cmd);
      data = fpga_read_byte();

      //Select the next command
      cmd++;
    }  

    //Wait for the I2C system to be ready
    for(i=0;i<1000;i++);
  }  
}