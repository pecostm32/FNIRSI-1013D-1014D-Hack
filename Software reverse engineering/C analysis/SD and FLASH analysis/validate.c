undefined4 validate(byte **param_1,byte **param_2)

{
  byte **ppbVar1;
  uint uVar2;
  byte *pbVar3;
  byte **ppbVar4;
  undefined4 uVar5;
  bool bVar6;
  
  bVar6 = param_1 != (byte **)0x0;
  ppbVar1 = param_1;
  if (bVar6) {
    ppbVar1 = (byte **)*param_1;
  }
  ppbVar4 = param_2;
  if (bVar6 && ppbVar1 != (byte **)0x0) {
    ppbVar4 = (byte **)(uint)*(byte *)ppbVar1;
  }
  uVar5 = 9;
  if (((bVar6 && ppbVar1 != (byte **)0x0) && ppbVar4 != (byte **)0x0) &&
     (*(short *)(param_1 + 1) == *(short *)((int)ppbVar1 + 6))) {
    uVar2 = (uint)*(byte *)((int)ppbVar1 + 1);
    just_return_zero();
    if ((uVar2 & 1) == 0) {
      pbVar3 = *param_1;
      uVar5 = 0;
      goto LAB_80039138;
    }
  }
  pbVar3 = (byte *)0x0;
LAB_80039138:
  *param_2 = pbVar3;
  return uVar5;
}

