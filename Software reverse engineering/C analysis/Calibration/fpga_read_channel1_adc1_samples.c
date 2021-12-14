//--------------------------------------------------------------------------------

void fpga_read_channel1_adc1_samples(void)

{
  int iVar1;
  uint *ptr;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = LENGTH_1500;

  if (*(byte *)(DAT_8001b044 + 10) < 0xb)  //Time base dependend number of samples to read
  {
    uVar4 = LENGTH_750;
  }

  uVar3 = translate_parameter(0xc,(uint)*(byte *)(DAT_8001b044 + 0x23));

  fpga_write_cmd((uchar)uVar3);

  fpga_bus_dir_in();
  ptr = PORT_E_DATA;
  set_gpio_pin_low(PORT_E_DATA,9);
  set_gpio_pin_low(ptr,10);
  iVar2 = DAT_8001b054;
  uVar3 = 0;

  //Read the needed number of samples into channel 1 sample buffer at 0x8019D5EA
  if (uVar4 != 0)
  {
    do
    {
      set_gpio_pin_low(ptr,8);
      set_gpio_pin_high(ptr,8);
      iVar1 = uVar3 * 2;
      uVar3 = uVar3 + 1 & 0xfffeffff;
      *(ushort *)(iVar2 + iVar1) = (ushort)ptr[4] & 0xff;
    } while (uVar3 < uVar4);

    return;
  }

  return;
}

//--------------------------------------------------------------------------------

void fpga_read_channel1_adc2_samples(void)

{
  int iVar1;
  uint *ptr;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = DAT_8001b194;  //1500

  if (*(byte *)(DAT_8001b190 + 10) < 0xb)
  {
    uVar4 = DAT_8001b198;  //750
  }

  fpga_write_cmd('!');   //0x21

  fpga_bus_dir_in();

  ptr = DAT_8001b19c;                     //0x8019ED5A  (channel1tracebuffer2)
  set_gpio_pin_low(DAT_8001b19c,9);
  set_gpio_pin_low(ptr,10);
  iVar2 = DAT_8001b1a0;
  uVar3 = 0;

  if (uVar4 != 0)
  {
    do
    {
      set_gpio_pin_low(ptr,8);
      set_gpio_pin_high(ptr,8);
      iVar1 = uVar3 * 2;
      uVar3 = uVar3 + 1 & 0xfffeffff;
      *(ushort *)(iVar2 + iVar1) = (ushort)ptr[4] & 0xff;
    } while (uVar3 < uVar4);

    return;
  }

  return;
}

//--------------------------------------------------------------------------------


