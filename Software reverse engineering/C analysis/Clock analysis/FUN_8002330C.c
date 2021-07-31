undefined FUN_8002330c(void)

{
  uint in_r3;
  uint local_8 [2];
  
  local_8[0] = in_r3 & 0xffff0000;
  FUN_800250f8(DAT_80023350,local_8,2);                 //0x001FE000.  This function does something with SPI0 (FLASH)

  if ((local_8[0] & 0xffff) != 0x9086)
  {
    return (local_8[0] & 0xffff) == 0x7293;
  }
  return 2;
}

