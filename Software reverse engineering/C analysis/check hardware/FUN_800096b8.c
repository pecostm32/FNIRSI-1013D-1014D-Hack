void FUN_800096b8(undefined4 param_1,uint param_2)

{
  uint *ptr;
  int iVar1;
  uint unaff_r4;
  
  switch(*(undefined *)(DAT_800097d0 + 0xf))
  {
  case 0:
    unaff_r4 = (uint)*(ushort *)(DAT_800097d4 + 0x10);
    break;
  case 1:
    unaff_r4 = (uint)*(ushort *)(DAT_800097d4 + 0x12);
    break;
  case 2:
    unaff_r4 = (uint)*(ushort *)(DAT_800097d4 + 0x14);
    break;
  case 3:
    unaff_r4 = (uint)*(ushort *)(DAT_800097d4 + 0x16);
    break;
  case 4:
    unaff_r4 = (uint)*(ushort *)(DAT_800097d4 + 0x18);
    break;
  case 5:
  case 6:
    unaff_r4 = (uint)*(ushort *)(DAT_800097d4 + 0x1a);
  }

  switch(*(undefined *)(DAT_800097d0 + 0xf))
  {
  case 0:
    param_2 = (uint)*DAT_800097d8;
    break;
  case 1:
    param_2 = (uint)DAT_800097d8[1];
    break;
  case 2:
    param_2 = (uint)DAT_800097d8[2];
    break;
  case 3:
    param_2 = (uint)DAT_800097d8[3];
    break;
  case 4:
    param_2 = (uint)DAT_800097d8[4];
    break;
  case 5:
    param_2 = (uint)DAT_800097d8[5];
    break;
  case 6:
    param_2 = (uint)DAT_800097d8[6];
  }

  iVar1 = (int)((ulonglong)((longlong)DAT_800097dc *(longlong)(int)((uint)*(ushort *)(DAT_800097d0 + 0x12) * (uint)*(ushort *)(DAT_800097d4 + 0xe))) >> 0x20);
  iVar1 = divide_2((uint)*DAT_800097d8 * ((iVar1 >> 5) - (iVar1 >> 0x1f)),param_2);

  fpga_write_cmd(0x35);
  fpga_write_data((uchar)((unaff_r4 - iVar1) >> 8));
  fpga_write_data((uchar)((unaff_r4 - iVar1) & 0xFF));
  return;
}

