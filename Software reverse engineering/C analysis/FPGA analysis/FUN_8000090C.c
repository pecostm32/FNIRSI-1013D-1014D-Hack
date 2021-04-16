longlong FUN_8000090c(uint param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  bool bVar7;
  bool bVar8;
  bool bVar9;
  bool bVar10;
  
  if ((int)(param_1 | param_2) < 0) {
    uVar6 = param_2 & 0x80000000;
    if ((int)uVar6 < 0) {
      param_2 = -param_2;
    }
    uVar5 = uVar6 ^ (int)param_1 >> 0x20;
    if (SUB41(param_1 >> 0x1f,0)) {
      param_1 = -param_1;
    }
    iVar4 = (int)uVar5 >> 0x1f;
    uVar2 = param_2;
    if (param_1 >> 4 < param_2) goto LAB_80000ad8;
    if (param_1 >> 8 < param_2) goto LAB_80000aa8;
    uVar2 = param_2 << 6;
    uVar6 = 0xfc000000;
    if (param_1 >> 8 < uVar2) goto LAB_80000aa8;
    uVar2 = param_2 << 0xc;
    uVar6 = 0xfff00000;
    if (param_1 >> 8 < uVar2) goto LAB_80000aa8;
    uVar2 = param_2 << 0x12;
    uVar6 = 0xffffc000;
    if (uVar2 <= param_1 >> 8) {
      uVar2 = param_2 << 0x18;
      uVar6 = 0xffffff00;
    }
    bVar7 = uVar2 == 0;
    if (!bVar7) {
      do {
        if (bVar7) {
          uVar2 = uVar2 >> 6;
        }
LAB_80000aa8:
        bVar7 = uVar2 <= param_1 >> 7;
        if (bVar7) {
          param_1 = param_1 + uVar2 * -0x80;
        }
        bVar8 = uVar2 <= param_1 >> 6;
        if (bVar8) {
          param_1 = param_1 + uVar2 * -0x40;
        }
        bVar9 = uVar2 <= param_1 >> 5;
        if (bVar9) {
          param_1 = param_1 + uVar2 * -0x20;
        }
        bVar10 = uVar2 <= param_1 >> 4;
        if (bVar10) {
          param_1 = param_1 + uVar2 * -0x10;
        }
        uVar6 = (((uVar6 * 2 + (uint)bVar7) * 2 + (uint)bVar8) * 2 + (uint)bVar9) * 2 + (uint)bVar10
        ;
LAB_80000ad8:
        bVar7 = uVar2 <= param_1 >> 3;
        if (bVar7) {
          param_1 = param_1 + uVar2 * -8;
        }
        uVar6 = uVar6 * 2 + (uint)bVar7;
        bVar8 = uVar2 <= param_1 >> 2;
        if (bVar8) {
          param_1 = param_1 + uVar2 * -4;
        }
        bVar7 = !bVar8 && CARRY4(uVar6,uVar6) || bVar8 && uVar6 * 2 + 1 <= uVar6;
        uVar6 = uVar6 * 2 + (uint)bVar8;
      } while (bVar7);
      bVar7 = uVar2 <= param_1 >> 1;
      if (bVar7) {
        param_1 = param_1 + uVar2 * -2;
      }
      uVar3 = param_1 - uVar2;
      if (uVar2 > param_1) {
        uVar3 = param_1;
      }
      iVar1 = (uVar6 * 2 + (uint)bVar7) * 2 + (uint)(uVar2 <= param_1);
      if (iVar4 < 0) {
        iVar1 = -iVar1;
      }
      if ((bool)((byte)(uVar5 >> 0x1e) & 1)) {
        uVar3 = -uVar3;
      }
      return CONCAT44(uVar3,iVar1);
    }
    if (iVar4 < 0) {
      param_1 = -param_1;
    }
LAB_80000b24:
    return (ulonglong)param_1 << 0x20;
  }
  if (param_1 >> 1 < param_2) {
    if (param_1 < param_2) {
      return (ulonglong)param_1 << 0x20;
    }
    return CONCAT44(param_1 - param_2,1);
  }
  iVar4 = 0;
  uVar6 = param_2;
  if (param_2 <= param_1 >> 4) {
    if (param_2 <= param_1 >> 8) {
      if (param_1 >> 0xc < param_2) goto LAB_80000998;
      if (param_1 >> 0x10 < param_2) goto LAB_80000968;
      uVar6 = param_2 << 8;
      iVar4 = -0x1000000;
      if (uVar6 <= param_1 >> 0x10) {
        iVar4 = -0x10000;
        uVar6 = param_2 << 0x10;
      }
      if (param_1 >> 0xc < uVar6) goto LAB_80000998;
      bVar7 = uVar6 == 0;
      if (bVar7) goto LAB_80000b24;
      do {
        if (bVar7) {
          uVar6 = uVar6 >> 8;
        }
LAB_80000968:
        bVar7 = uVar6 <= param_1 >> 0xf;
        if (bVar7) {
          param_1 = param_1 + uVar6 * -0x8000;
        }
        bVar8 = uVar6 <= param_1 >> 0xe;
        if (bVar8) {
          param_1 = param_1 + uVar6 * -0x4000;
        }
        bVar9 = uVar6 <= param_1 >> 0xd;
        if (bVar9) {
          param_1 = param_1 + uVar6 * -0x2000;
        }
        bVar10 = uVar6 <= param_1 >> 0xc;
        if (bVar10) {
          param_1 = param_1 + uVar6 * -0x1000;
        }
        iVar4 = (((iVar4 * 2 + (uint)bVar7) * 2 + (uint)bVar8) * 2 + (uint)bVar9) * 2 + (uint)bVar10
        ;
LAB_80000998:
        bVar7 = uVar6 <= param_1 >> 0xb;
        if (bVar7) {
          param_1 = param_1 + uVar6 * -0x800;
        }
        bVar8 = uVar6 <= param_1 >> 10;
        if (bVar8) {
          param_1 = param_1 + uVar6 * -0x400;
        }
        bVar9 = uVar6 <= param_1 >> 9;
        if (bVar9) {
          param_1 = param_1 + uVar6 * -0x200;
        }
        uVar5 = ((iVar4 * 2 + (uint)bVar7) * 2 + (uint)bVar8) * 2 + (uint)bVar9;
        bVar8 = uVar6 <= param_1 >> 8;
        if (bVar8) {
          param_1 = param_1 + uVar6 * -0x100;
        }
        bVar7 = !bVar8 && CARRY4(uVar5,uVar5) || bVar8 && uVar5 * 2 + 1 <= uVar5;
        iVar4 = uVar5 * 2 + (uint)bVar8;
      } while (bVar7);
    }
    bVar7 = uVar6 <= param_1 >> 7;
    if (bVar7) {
      param_1 = param_1 + uVar6 * -0x80;
    }
    bVar8 = uVar6 <= param_1 >> 6;
    if (bVar8) {
      param_1 = param_1 + uVar6 * -0x40;
    }
    bVar9 = uVar6 <= param_1 >> 5;
    if (bVar9) {
      param_1 = param_1 + uVar6 * -0x20;
    }
    bVar10 = uVar6 <= param_1 >> 4;
    if (bVar10) {
      param_1 = param_1 + uVar6 * -0x10;
    }
    iVar4 = (((iVar4 * 2 + (uint)bVar7) * 2 + (uint)bVar8) * 2 + (uint)bVar9) * 2 + (uint)bVar10;
  }
  bVar7 = uVar6 <= param_1 >> 3;
  if (bVar7) {
    param_1 = param_1 + uVar6 * -8;
  }
  bVar8 = uVar6 <= param_1 >> 2;
  if (bVar8) {
    param_1 = param_1 + uVar6 * -4;
  }
  bVar9 = uVar6 <= param_1 >> 1;
  if (bVar9) {
    param_1 = param_1 + uVar6 * -2;
  }
  uVar5 = param_1 - uVar6;
  if (uVar6 > param_1) {
    uVar5 = param_1;
  }
  return CONCAT44(uVar5,(((iVar4 * 2 + (uint)bVar7) * 2 + (uint)bVar8) * 2 + (uint)bVar9) * 2 +
                        (uint)(uVar6 <= param_1));
}

