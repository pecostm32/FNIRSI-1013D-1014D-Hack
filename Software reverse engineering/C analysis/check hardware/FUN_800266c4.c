void FUN_800266c4(void)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = get_setting(10,(uint)*(byte *)(DAT_80026720 + 10));
  uVar2 = get_setting(0x14,0xed);

  fpga_write_cmd((uchar)uVar2);

  fpga_write_data((uchar)(uVar1 >> 0x18));
  fpga_write_data((uchar)(uVar1 >> 0x10));
  fpga_write_data((uchar)(uVar1 >> 8));
  fpga_write_data((uchar)uVar1);

  *(undefined2 *)PTR_DAT_80026724 = 0;
  return;
}

