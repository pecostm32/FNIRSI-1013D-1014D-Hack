//------------------------------------------------------------------------------------------------------------------------------------------

void set_fpga_trigger_level(void)
{
  byte bVar1;
  uint *ptr;
  
  FUN_8000b4d4();
  fpga_write_cmd('\x17');
  bVar1 = *(byte *)(DAT_800267e4 + 0x28);

//Write fpga data byte
  ptr = PE_CFG0;
  gpio_config_pin(PE_CFG0,0,1);
  gpio_config_pin(ptr,1,1);
  gpio_config_pin(ptr,2,1);
  gpio_config_pin(ptr,3,1);
  gpio_config_pin(ptr,4,1);
  gpio_config_pin(ptr,5,1);
  gpio_config_pin(ptr,6,1);
  gpio_config_pin(ptr,7,1);
  set_gpio_pin_high(ptr,9);
  set_gpio_pin_low(ptr,10);
  ptr[4] = (uint)bVar1 | ptr[4] & 0xffffff00;
  set_gpio_pin_low(ptr,8);
  ptr[4] = ptr[4] | 0x100;
  return;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//This function is called from two different loacations
//It does not take any input
void FUN_8000b4d4(undefined4 param_1,uint param_2)
{
  char cVar1;
  ushort uVar2;
  int iVar3;
  undefined uVar4;
  uint uVar5;
  int iVar6;
  
  iVar3 = DAT_8000b5c4;   //0x8019D5A0     settings base address

  if (*(char *)(DAT_8000b5c4 + 0x23) == '\0')   //0x8019D5C3 trigger channel
  {
    cVar1 = *(char *)(DAT_8000b5c4 + 3);        //0x8019D5A3  Channel 1 volts per div
    uVar2 = *(ushort *)(DAT_8000b5c4 + 6);      //0x8019D5A6
  }
  else
  {
    cVar1 = *(char *)(DAT_8000b5c4 + 0xf);      //0x8019D5AF  Channel 2 volts per div
    uVar2 = *(ushort *)(DAT_8000b5c4 + 0x12);   //0x8019D5B2
  }

  uVar5 = (uint)uVar2;

  switch(cVar1)
  {
  case '\0':
    param_2 = (uint)*DAT_8000b5c8;          //0x802F18F8   0xAD    Some initial settings ???? Do these change???
    break;                                  //                     These are set in the main initialization
  case '\x01':
    param_2 = (uint)DAT_8000b5c8[1];        //0x802F18FA   0xAF
    break;
  case '\x02':
    param_2 = (uint)DAT_8000b5c8[2];        //0x802F18FC   0xB4
    break;
  case '\x03':
    param_2 = (uint)DAT_8000b5c8[3];        //0x802F18FE   0xB4
    break;
  case '\x04':
    param_2 = (uint)DAT_8000b5c8[4];        //0x802F1900   0xB8
    break;
  case '\x05':
    param_2 = (uint)DAT_8000b5c8[5];        //0x802F1902   0xB8
    break;
  case '\x06':
    param_2 = (uint)DAT_8000b5c8[6];        //0x802F1904   0xB8

LAB_8000b578:
    if (*(ushort *)(DAT_8000b5c4 + 0x26) < uVar5)
    {
      iVar6 = divide_2((uVar5 - (int)(uVar5 - *(ushort *)(DAT_8000b5c4 + 0x26)) / 2) * 100,param_2);    //0x8019D5C6 ????
      *(char *)(iVar3 + 0x28) = (char)iVar6;
      return;
    }

    iVar6 = divide_2((uVar5 + (int)(*(ushort *)(DAT_8000b5c4 + 0x26) - uVar5) / 2) * 100,param_2);
    uVar4 = (undefined)iVar6;
    goto LAB_8000b570;

  default:
    if (cVar1 == '\x06')   //This is bullshit because it is already handled in case 0x06
      goto LAB_8000b578;
  }

  //
  iVar6 = divide((uint)*(ushort *)(DAT_8000b5c4 + 0x26) * 100,param_2);
  uVar4 = (undefined)iVar6;

LAB_8000b570:
  *(undefined *)(iVar3 + 0x28) = uVar4;         //0x8019D5C8   trigger level
  return;
}

//------------------------------------------------------------------------------------------------------------------------------------------

