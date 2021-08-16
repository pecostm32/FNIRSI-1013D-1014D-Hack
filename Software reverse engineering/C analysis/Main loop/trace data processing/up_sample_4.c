void FUN_8001408c(ushort *param_1,int param_2,uint param_3)

{
  ushort uVar1;
  ushort *puVar2;
  ushort *puVar3;
  ushort *puVar4;
  ushort *puVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  
  puVar2 = DAT_800141c4;
  uVar6 = param_3 >> 2;
  if (uVar6 != 0) {
    puVar4 = param_1 + param_2;
    puVar3 = DAT_800141c4 + -4;
    puVar5 = puVar4 + -1;
    if ((uVar6 & 1) != 0) {
      *DAT_800141c4 = *puVar4;
      puVar3 = puVar2;
      puVar5 = puVar4;
    }
    uVar6 = (uVar6 << 0xf) >> 0x10;
    while (uVar6 != 0) {
      puVar3[4] = puVar5[1];
      puVar5 = puVar5 + 2;
      uVar6 = uVar6 - 1 & 0xffff;
      puVar3 = puVar3 + 8;
      *puVar3 = *puVar5;
    }
  }
  uVar6 = (param_3 >> 2) - 1;
  if (0 < (int)uVar6) {
    uVar6 = uVar6 & 0xffff;
    puVar3 = DAT_800141c4;
    do {
      uVar1 = *puVar3;
      uVar7 = (uint)uVar1;
      uVar8 = (uint)puVar3[4];
      if (uVar7 < uVar8) {
        uVar7 = uVar8 - uVar7 & 0xfffcffff;
        puVar3[1] = uVar1 + (short)(uVar7 >> 2);
        puVar3[2] = uVar1 + (short)(uVar7 >> 1);
        puVar3[3] = uVar1 + (short)(uVar7 * 3 >> 2);
      }
      else {
        uVar7 = uVar7 - uVar8 & 0xfffcffff;
        puVar3[1] = uVar1 - (short)(uVar7 >> 2);
        puVar3[2] = uVar1 - (short)(uVar7 >> 1);
        puVar3[3] = uVar1 - (short)(uVar7 * 3 >> 2);
      }
      uVar6 = uVar6 - 1 & 0xffff;
      puVar3 = puVar3 + 4;
    } while (uVar6 != 0);
  }
  if (param_3 == 0) {
    return;
  }
  puVar3 = param_1 + -1;
  puVar5 = puVar2 + -1;
  if ((param_3 & 1) != 0) {
    *param_1 = *puVar2;
    puVar3 = param_1;
    puVar5 = puVar2;
  }
  param_3 = param_3 >> 1;
  if (param_3 == 0) {
    return;
  }
  do {
    param_3 = param_3 - 1;
    puVar3[1] = puVar5[1];
    puVar5 = puVar5 + 2;
    puVar3 = puVar3 + 2;
    *puVar3 = *puVar5;
  } while (param_3 != 0);
  return;
}


