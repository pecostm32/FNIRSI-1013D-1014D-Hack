//Read a port pin

//param_1 ==> base address of port configuration register
//param_2 ==> pin number

uint FUN_80017724(int param_1,uint param_2)
{
  uint uVar1;
  
  uVar1 = *(uint *)(param_1 + 0x10) & 1 << (param_2 & 0xff);

  if (uVar1 != 0)
  {
    uVar1 = 1;
  }

  return uVar1;
}

