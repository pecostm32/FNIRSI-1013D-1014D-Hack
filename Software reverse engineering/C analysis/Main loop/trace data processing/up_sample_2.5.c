
void FUN_80013eac(ushort *param_1,int param_2,uint param_3)

{
  ushort uVar1;
  short sVar2;
  ushort *puVar3;
  ushort *puVar4;
  ushort *puVar5;
  ushort *puVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  
  puVar3 = DAT_80014080;
  uVar8 = param_3 * DAT_8001407c >> 0x12;   //0x0000CCCD   4000 ==> 800
  puVar4 = param_1 + param_2;
  if (uVar8 != 0) {
    puVar5 = DAT_80014080 + -5;
    puVar6 = puVar4 + -2;
    if ((uVar8 & 1) != 0) {
      *DAT_80014080 = *puVar4;
      puVar5 = puVar3;
      puVar6 = puVar4;
    }
    uVar9 = (uVar8 << 0xf) >> 0x10;
    while (uVar9 != 0) {
      puVar5[5] = puVar6[2];
      puVar6 = puVar6 + 4;
      uVar9 = uVar9 - 1 & 0xffff;
      puVar5 = puVar5 + 10;
      *puVar5 = *puVar6;
    }
  }
  uVar9 = uVar8 - 1;
  if (0 < (int)uVar9) {
    puVar6 = puVar4 + -1;
    puVar5 = puVar3 + -2;
    if ((uVar9 & 1) != 0) {
      puVar6 = puVar4 + 1;
      puVar5 = puVar3 + 3;
      *puVar5 = *puVar6;
    }
    uVar9 = uVar9 * 0x8000 >> 0x10;
    while (uVar9 != 0) {
      puVar5[5] = puVar6[2];
      puVar6 = puVar6 + 4;
      uVar9 = uVar9 - 1 & 0xffff;
      puVar5 = puVar5 + 10;
      *puVar5 = *puVar6;
    }
  }
  uVar9 = DAT_80014084;
  if (0 < (int)(uVar8 - 1)) {
    uVar8 = uVar8 - 1 & 0xffff;
    puVar4 = DAT_80014080;
    do {
      uVar1 = *puVar4;
      uVar10 = (uint)uVar1;
      uVar7 = (uint)puVar4[3];
      if (uVar10 < uVar7) {
        uVar10 = uVar7 - uVar10 & 0xffff;
        puVar4[1] = uVar1 + (ushort)(DAT_80014088 * uVar10 >> 0x11);
        puVar4[2] = uVar1 + (short)(uint)((ulonglong)(uVar10 << 1) * (ulonglong)uVar9 >> 0x21);
      }
      else {
        uVar10 = uVar10 - uVar7 & 0xffff;
        puVar4[1] = uVar1 - (ushort)(DAT_80014088 * uVar10 >> 0x11);
        puVar4[2] = uVar1 - (short)(uint)((ulonglong)(uVar10 << 1) * (ulonglong)uVar9 >> 0x21);
      }
      uVar10 = (uint)puVar4[5];
      if (uVar10 <= uVar7) {
        uVar11 = uVar7 - uVar10;
      }
      else {
        uVar11 = uVar10 - uVar7;
      }
      if (uVar10 <= uVar7) {
        sVar2 = -(short)((uVar11 & 0xfffeffff) >> 1);
      }
      else {
        sVar2 = (short)((uVar11 & 0xfffeffff) >> 1);
      }
      puVar4[4] = puVar4[3] + sVar2;
      uVar8 = uVar8 - 1 & 0xffff;
      puVar4 = puVar4 + 5;
    } while (uVar8 != 0);
  }
  if (param_3 == 0) {
    return;
  }
  puVar4 = param_1 + -1;
  puVar5 = puVar3 + -1;
  if ((param_3 & 1) != 0) {
    *param_1 = *puVar3;
    puVar4 = param_1;
    puVar5 = puVar3;
  }
  param_3 = param_3 >> 1;
  if (param_3 == 0) {
    return;
  }
  do {
    param_3 = param_3 - 1;
    puVar4[1] = puVar5[1];
    puVar5 = puVar5 + 2;
    puVar4 = puVar4 + 2;
    *puVar4 = *puVar5;
  } while (param_3 != 0);
  return;
}


