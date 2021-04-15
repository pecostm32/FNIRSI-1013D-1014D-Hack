//Function to set pin output state high

//param_1 ==> base address of port configuration register
//param_2 ==> pin number

void FUN_8001774c(int param_1,uint param_2)
{
  *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | 1 << (param_2 & 0xff);
  return;
}

