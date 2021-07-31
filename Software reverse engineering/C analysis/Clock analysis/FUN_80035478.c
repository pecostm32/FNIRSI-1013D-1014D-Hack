
//Some parameter processing

void FUN_80035478(int param_1,undefined4 param_2,uint param_3,int param_4,uint param_5,undefined4 param_6,uint param_7,uint param_8,uint param_9)
{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  
  uVar1 = param_3 >> 0x14 | param_4 << 0xc;
  param_5 = param_5 >> 0x14;
  uVar2 = param_7 >> 0x14 | param_8 << 0xc;
  param_8 = param_8 >> 0x14;

  while ((param_8 | uVar2) != 0)
  {
    *(uint *)(param_1 + uVar1 * 4) = param_5 << 0x14 | 0xc10 | (param_9 & 3) << 2 | 2;
    bVar3 = uVar2 == 0;
    uVar2 = uVar2 - 1;
    param_8 = param_8 - bVar3;
    uVar1 = uVar1 + 1;
    param_5 = param_5 + 1;
  }
  return;
}


