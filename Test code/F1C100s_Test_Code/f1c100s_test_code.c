#include "fpga_control.h"

int main(void)
{
  fpga_init();
  
  fpga_write_cmd(0x38);
  fpga_write_short(0xEA60);
  
  while(1);
}