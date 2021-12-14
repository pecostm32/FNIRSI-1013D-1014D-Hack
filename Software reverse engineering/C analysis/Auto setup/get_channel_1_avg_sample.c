//--------------------------------------------------------------------------------

void get_channel_1_avg_sample(int count)

{
  uint *ptr;
  uint uVar1;
  uint dividend;
  
  dividend = 0;                       //No data yet

  fpga_write_cmd('$');                //0x24, allows for reading a bunch of samples

  fpga_bus_dir_in();
  ptr = DAT_8001b0f0;
  set_gpio_pin_low(DAT_8001b0f0,9);
  set_gpio_pin_low(ptr,10);
  uVar1 = 0;

  if (count != 0)
  {
    do
    {
      set_gpio_pin_low(ptr,8);
      set_gpio_pin_high(ptr,8);
      uVar1 = uVar1 + 1 & 0xfffeffff;
      dividend = (ptr[4] & 0xff) + dividend & 0xfffeffff;  //Sum the samples
    } while (uVar1 < (uint)count);
  }

  divide(dividend,count);  //Average the samples

  return;
}


//--------------------------------------------------------------------------------

