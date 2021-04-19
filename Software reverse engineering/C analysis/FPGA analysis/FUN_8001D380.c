void FUN_8001d380(void)

{
  uint uVar2;
  
  uVar2 = FUN_800248f8(0x10,*(undefined *)(DAT_8001d3b8 + 2));   //0x80361378 + 2
  FUN_800169f8(0x38);                                            //Send command 0x38 (Display brightness)
  FUN_800168fc((uVar2 & 0xffff) >> 8);                           //Write MSB to data register
  FUN_800168fc((uVar2 & 0xff));                                  //Write LSB to data register
  return;
}

