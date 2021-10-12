
longlong FUN_80039890(uint param_1,uint param_2,uint param_3,uint param_4)

{
  longlong lVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint unaff_r5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  bool bVar13;
  bool bVar14;
  
  uVar10 = DAT_800399fc & param_2 >> 4;
  bVar13 = uVar10 == 0;

  if (!bVar13)
  {
    unaff_r5 = DAT_800399fc & param_4 >> 4;
    bVar13 = unaff_r5 == 0;
  }

  if (!bVar13)
  {
    bVar13 = uVar10 == DAT_800399fc;
  }

  if (!bVar13)
  {
    bVar13 = unaff_r5 == DAT_800399fc;
  }

  if (bVar13)
  {
    if (uVar10 == DAT_800399fc || (DAT_800399fc & param_4 >> 4) == DAT_800399fc)
    {
                    // WARNING: Subroutine does not return
      FUN_80039a08();
    }

    return (ulonglong)((param_2 ^ param_4) & 0x80000000) << 0x20;
  }

  uVar3 = param_2 & ~(DAT_800399fc << 5) | 0x100000;
  uVar5 = param_4 & ~(DAT_800399fc << 5) | 0x100000;
  iVar11 = (uVar10 | (param_2 ^ param_4) >> 0x1f) + unaff_r5;
  lVar1 = (ulonglong)param_3 * (ulonglong)uVar3;
  uVar10 = (uint)lVar1;
  uVar9 = (uint)((ulonglong)lVar1 >> 0x20);
  lVar1 = (ulonglong)uVar5 * (ulonglong)param_1;
  uVar8 = (uint)lVar1;
  uVar6 = (uint)((ulonglong)lVar1 >> 0x20);
  iVar12 = iVar11 + -0x3fc0000;
  bVar13 = CARRY4(uVar8,uVar10);
  uVar8 = uVar8 + uVar10;
  uVar7 = uVar6 + uVar9 + (uint)bVar13;
  lVar1 = (ulonglong)uVar5 * (ulonglong)uVar3;
  uVar10 = (uint)lVar1;
  uVar3 = (uint)((ulonglong)param_3 * (ulonglong)param_1 >> 0x20);
  bVar14 = CARRY4(uVar8,uVar3);
  uVar8 = uVar8 + uVar3;
  uVar3 = uVar7 + uVar10 + (uint)bVar14;
  uVar10 = (int)((ulonglong)lVar1 >> 0x20) + (uint)(bVar13 == false && CARRY4(uVar6,uVar9) || bVar13 == true && uVar6 + uVar9 + 1 <= uVar6) + (uint)(bVar14 == false && CARRY4(uVar7,uVar10) || bVar14 == true && uVar7 + uVar10 + 1 <= uVar7);

  if ((int)((ulonglong)param_3 * (ulonglong)param_1) != 0)
  {
    uVar8 = uVar8 | 1;
  }

  if ((uVar10 & 0x200) == 0)
  {
    uVar5 = uVar8 << 0xc;
    uVar6 = uVar10 * 0x1000 | uVar3 >> 0x14;
    uVar10 = uVar3 * 0x1000 | uVar8 >> 0x14;
    iVar4 = -4;
  }
  else
  {
    uVar5 = uVar8 << 0xb;
    uVar6 = uVar10 * 0x800 | uVar3 >> 0x15;
    uVar10 = uVar3 * 0x800 | uVar8 >> 0x15;
    iVar4 = -3;
  }

  uVar7 = iVar4 + (iVar12 >> 0x10);
  uVar3 = uVar6 + uVar7 * 0x100000 ^ iVar11 * -0x80000000;

  if (uVar5 != 0)
  {
    bVar2 = -(char)((int)uVar5 >> 0x1f);

    if ((uVar5 & 0x7fffffff) != 0)
    {
      uVar5 = 0;
    }

    uVar3 = uVar3 + (bVar2 == 1 && uVar10 + 1 <= uVar10);
    uVar10 = uVar10 + bVar2 & ~(uVar5 >> 0x1f);
  }

  if (DAT_80039a00 <= uVar7)
  {
    if (0x3ffffff < iVar12)
    {
      uVar3 = uVar3 + 0xa0000000;
    }

    if (iVar11 + -0x7fc0000 < 0 == SBORROW4(iVar12,0x4000000))
    {
      return (ulonglong)(uVar3 & 0x80000000 | 0x7ff00000) << 0x20;
    }

    return (ulonglong)(uVar3 + 0x60000000 & 0x80000000) << 0x20;
  }

  return CONCAT44(uVar3,uVar10);
}


