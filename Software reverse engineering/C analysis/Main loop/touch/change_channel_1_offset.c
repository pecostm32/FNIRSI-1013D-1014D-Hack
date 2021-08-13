//change_channel_1_offset

void FUN_8001a5d0(void)

{
  ushort uVar1;
  ushort uVar2;
  uint *ptr;
  undefined *puVar3;
  undefined *puVar4;
  short sVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint unaff_r4;
  int iVar9;
  
  iVar6 = DAT_8001a754;

  iVar9 = 1;
  if (*(char *)(DAT_8001a754 + 0x16) != '\0')
  {
    iVar9 = 5;
  }

  iVar7 = FUN_80017790();  //check on valid touch

  puVar4 = PTR_DAT_8001a760;
  puVar3 = PTR_DAT_8001a75c;

  if (iVar7 != 0)  //check touch valid
  {
    return;
  }

  if (*(char *)(DAT_8001a758 + 7) == '\0')
  {
    uVar1 = *(ushort *)(PTR_DAT_8001a760 + 0x30);
    uVar2 = *(ushort *)(PTR_DAT_8001a760 + 0x34);

    if (uVar1 < uVar2)
    {
      iVar9 = divide((uint)(ushort)(uVar2 - uVar1),iVar9);
      uVar8 = (uint)*(ushort *)(puVar4 + 0x12);

      if (iVar9 + uVar8 < 0x18b)
      {
        *(short *)(iVar6 + 6) = (short)(iVar9 + uVar8);  //traceoffset
      }
      else
      {
        *(undefined2 *)(iVar6 + 6) = 0x18b;
      }

      goto joined_r0x8001a6f0;
    }

    iVar9 = divide((uint)(ushort)(uVar1 - uVar2),iVar9);
    uVar8 = (uint)*(ushort *)(puVar4 + 0x12);

    if (iVar9 + 7U < uVar8)
    {
      *(ushort *)(iVar6 + 6) = *(ushort *)(puVar4 + 0x12) - (short)iVar9;
    }
    else
    {
      *(undefined2 *)(iVar6 + 6) = 7;
    }
  }
  else
  {
    uVar1 = *(ushort *)(PTR_DAT_8001a760 + 0x2e);
    uVar2 = *(ushort *)(PTR_DAT_8001a760 + 0x32);

    if (uVar1 < uVar2)
    {
      iVar9 = divide((uint)(ushort)(uVar2 - uVar1),iVar9);
      uVar8 = (uint)*(ushort *)(puVar4 + 0x12);

      if (iVar9 + uVar8 < 0x18b)
      {
        *(short *)(iVar6 + 6) = (short)(iVar9 + uVar8);
      }
      else
      {
        *(undefined2 *)(iVar6 + 6) = 0x18b;
      }

joined_r0x8001a6f0:
      if (0x18b < uVar8)
      {
        *(undefined2 *)(puVar4 + 0x12) = 0x18b;
      }

      uVar1 = *(ushort *)(puVar4 + 0xe);
      sVar5 = (*(short *)(iVar6 + 6) - *(short *)(puVar4 + 0x12)) + uVar1;

      goto set_fpga_channel1_offset;
    }

    iVar9 = divide((uint)(ushort)(uVar1 - uVar2),iVar9);
    uVar8 = (uint)*(ushort *)(puVar4 + 0x12);

    if (iVar9 + 7U < uVar8)
    {
      *(ushort *)(iVar6 + 6) = *(ushort *)(puVar4 + 0x12) - (short)iVar9;
    }
    else
    {
      *(undefined2 *)(iVar6 + 6) = 7;
    }
  }

  if (uVar8 < 7)
  {
    *(undefined2 *)(puVar4 + 0x12) = 7;
  }

  uVar1 = *(ushort *)(puVar4 + 0xe);
  sVar5 = uVar1 - (*(short *)(puVar4 + 0x12) - *(short *)(iVar6 + 6));



set_fpga_channel1_offset:
  uVar8 = (uint)uVar1;
  *(short *)puVar3 = sVar5;
  switch(*(undefined *)(DAT_80006a84 + 3)) {
  case 0:
    unaff_r4 = (uint)DAT_80006a88[1];
    break;
  case 1:
    unaff_r4 = (uint)DAT_80006a88[2];
    break;
  case 2:
    unaff_r4 = (uint)DAT_80006a88[3];
    break;
  case 3:
    unaff_r4 = (uint)DAT_80006a88[4];
    break;
  case 4:
    unaff_r4 = (uint)DAT_80006a88[5];
    break;
  case 5:
  case 6:
    unaff_r4 = (uint)DAT_80006a88[6];
  }
  switch(*(undefined *)(DAT_80006a84 + 3)) {
  case 0:
    uVar8 = (uint)*DAT_80006a8c;
    break;
  case 1:
    uVar8 = (uint)DAT_80006a8c[1];
    break;
  case 2:
    uVar8 = (uint)DAT_80006a8c[2];
    break;
  case 3:
    uVar8 = (uint)DAT_80006a8c[3];
    break;
  case 4:
    uVar8 = (uint)DAT_80006a8c[4];
    break;
  case 5:
    uVar8 = (uint)DAT_80006a8c[5];
    break;
  case 6:
    uVar8 = (uint)DAT_80006a8c[6];
  }
  iVar6 = (int)((ulonglong)
                ((longlong)DAT_80006a90 *
                (longlong)(int)((uint)*(ushort *)(DAT_80006a84 + 6) * (uint)*DAT_80006a88)) >> 0x20)
  ;
  iVar6 = divide_2((uint)*DAT_80006a8c * ((iVar6 >> 5) - (iVar6 >> 0x1f)),uVar8);
  fpga_write_cmd('2');
  fpga_write_data((uchar)(unaff_r4 - iVar6 >> 8));
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
  ptr[4] = unaff_r4 - iVar6 & 0xff | ptr[4] & 0xffffff00;
  set_gpio_pin_low(ptr,8);
  ptr[4] = ptr[4] | 0x100;
  return;
}

