//Function is called to determine if hardware check is needed

undefined FUN_8002330c(void)

{
  uint in_r3;
  uint local_8 [2];
  
  local_8[0] = in_r3 & 0xffff0000;
  FUN_800250f8(DAT_80023350,local_8,2);

  if ((local_8[0] & 0xffff) != 0x9086)
  {
    return (local_8[0] & 0xffff) == 0x7293;
  }

  return 2;
}


//Function is called with 
//r0 = 0x001FE000
//r1 = sp
//r2 = 0x2


undefined4 FUN_800250f8(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  uint *puVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  puVar2 = (uint *)(DAT_800375ec + 8);
  *puVar2 = *puVar2 & 0xffffff4f;
  iVar1 = spi0_start_transfer();
  if ((iVar1 != 4) || (iVar1 = spi0_start_transfer(), iVar1 != param_3)) {
    uVar3 = 0xffffffff;
  }
  *puVar2 = *puVar2 & 0xffffff4f | 0x80;
  return uVar3;
}

