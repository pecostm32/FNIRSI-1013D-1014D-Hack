void FUN_8000696c(undefined4 param_1,uint param_2)

{
  uint *ptr;
  int iVar1;
  uint unaff_r4;
  
  switch(*(undefined *)(DAT_80006a84 + 3))
  {
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

  switch(*(undefined *)(DAT_80006a84 + 3))
  {
    case 0:
      param_2 = (uint)*DAT_80006a8c;
      break;
    case 1:
      param_2 = (uint)DAT_80006a8c[1];
      break;
    case 2:
      param_2 = (uint)DAT_80006a8c[2];
      break;
    case 3:
      param_2 = (uint)DAT_80006a8c[3];
      break;
    case 4:
      param_2 = (uint)DAT_80006a8c[4];
      break;
    case 5:
      param_2 = (uint)DAT_80006a8c[5];
      break;
    case 6:
      param_2 = (uint)DAT_80006a8c[6];
  }

  iVar1 = (int)((ulonglong)((longlong)DAT_80006a90 * (longlong)(int)((uint)*(ushort *)(DAT_80006a84 + 6) * (uint)*DAT_80006a88)) >> 0x20);
  iVar1 = divide_2((uint)*DAT_80006a8c * ((iVar1 >> 5) - (iVar1 >> 0x1f)),param_2);

  fpga_write_cmd(0x32);
  fpga_write_data((uchar)((unaff_r4 - iVar1) >> 8));
  fpga_write_data((uchar)((unaff_r4 - iVar1) & 0xFF));
  return;
}

