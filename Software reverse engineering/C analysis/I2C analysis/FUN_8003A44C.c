uint FUN_8003a44c(uint param_1,uint param_2,undefined4 param_3,uint param_4)

{
  longlong lVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  bool bVar6;
  
  uVar2 = param_1 >> 7 & 0xff0000;
  bVar6 = uVar2 == 0;
  if (!bVar6) {
    param_4 = param_2 >> 7 & 0xff0000;
    bVar6 = param_4 == 0;
  }
  if (!bVar6) {
    bVar6 = uVar2 == 0xff0000;
  }
  if (!bVar6) {
    bVar6 = param_4 == 0xff0000;
  }
  if (bVar6) {
    if ((int)(param_1 ^ param_2) < 0) {
      uVar2 = uVar2 | 0x100;
    }
    if (uVar2 < 0xff0000 && (param_2 >> 7 & 0xff0000) < 0xff0000) {
      return (param_1 ^ param_2) & 0x80000000;
    }
                    // WARNING: Subroutine does not return
    FUN_8003a54c();
  }
  if ((int)(param_1 ^ param_2) < 0) {
    uVar2 = uVar2 | 0x100;
  }
  lVar1 = (ulonglong)(param_2 << 8 | 0x80000000) * (ulonglong)(param_1 << 8 | 0x80000000);
  uVar5 = (uint)((ulonglong)lVar1 >> 0x20);
  iVar3 = uVar2 + param_4 + -0x800000;
  if ((int)lVar1 != 0) {
    uVar5 = uVar5 | 1;
  }
  bVar6 = SUB41(uVar5 >> 0x1f,0);
  uVar2 = uVar5 << 1;
  uVar4 = iVar3 + (iVar3 >> 0x10) + (uint)bVar6;
  if (bVar6) {
    uVar2 = (uint)bVar6 << 0x1f | uVar5 & 0x7fffffff;
  }
  bVar6 = (bool)((byte)(uVar2 >> 7) & 1);
  uVar5 = uVar2 >> 8;
  if (bVar6) {
    uVar5 = uVar2 & 0x7f;
  }
  uVar2 = (uVar2 >> 8) + uVar4 * 0x800000 + (uint)bVar6;
  if (uVar5 != 0) {
    bVar6 = 0xfbffff < uVar4;
  }
  if (!bVar6) {
    return uVar2;
  }
  if (uVar5 == 0 || uVar4 == 0xfc0000) {
    uVar2 = uVar2 & 0xfffffffe;
  }
  if (uVar4 < 0xfc0000) {
    return uVar2;
  }
  if (-1 < (int)(uVar4 - 0xfc0000)) {
    if ((int)((uVar2 + 0x800000) * 2) < 0) {
      return uVar2;
    }
    return (uVar2 + 0xa0000000 >> 0x17 | 0xff) << 0x17;
  }
  uVar4 = uVar4 ^ 0xff;
  bVar6 = (int)(uVar4 + 0x10000) < 0;
  if (uVar4 != 0xffff0000 && bVar6 == SCARRY4(uVar4,0x10000)) {
    return uVar2;
  }
  uVar2 = uVar2 + 0x60000000;
  if (uVar4 == 0xffff0000 || bVar6 != SCARRY4(uVar4,0x10000)) {
    uVar2 = uVar2 & 0x80000000;
  }
  return uVar2;
}

