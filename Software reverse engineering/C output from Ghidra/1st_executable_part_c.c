#include "1st_executable_part_c.h"



uint * FUN_800001cc(uint param_1)

{
  uint *puVar1;
  uint *puVar2;
  uint **ppuVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  uint *puVar7;
  
  ppuVar3 = (uint **)FUN_80000754();
  puVar7 = *ppuVar3;
  uVar6 = param_1 + 0xb & 0xfffffff8;
  if (uVar6 <= param_1) {
    return (uint *)0x0;
  }
  do {
    puVar1 = puVar7;
    puVar2 = (uint *)puVar7[1];
    while (puVar2 != (uint *)0x0) {
      if (uVar6 <= *puVar2) {
        if (*puVar2 < uVar6 + 8) {
          puVar1[1] = puVar2[1];
        }
        else {
          piVar5 = (int *)((int)puVar2 + uVar6);
          piVar5[1] = puVar2[1];
          *piVar5 = *puVar2 - uVar6;
          puVar1[1] = (uint)piVar5;
          *puVar2 = uVar6;
        }
        return puVar2 + 1;
      }
      puVar1 = puVar2;
      puVar2 = (uint *)puVar2[1];
    }
    iVar4 = FUN_80000768(puVar7,uVar6);
  } while (iVar4 != 0);
  return (uint *)0x0;
}



void FUN_8000022e(int param_1)

{
  int **ppiVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  
  piVar4 = (int *)(param_1 + -4);
  ppiVar1 = (int **)FUN_80000754();
  if (param_1 != 0) {
    piVar2 = *ppiVar1;
    piVar3 = (int *)(*ppiVar1)[1];
    while ((piVar3 != (int *)0x0 && (piVar3 < piVar4))) {
      piVar2 = piVar3;
      piVar3 = (int *)piVar3[1];
    }
    if ((int *)(*piVar2 + (int)piVar2) == piVar4) {
      *piVar2 = *piVar2 + *piVar4;
      piVar4 = piVar2;
    }
    else {
      piVar2[1] = (int)piVar4;
    }
    if ((int *)(*piVar4 + (int)piVar4) != piVar3) {
      piVar4[1] = (int)piVar3;
      return;
    }
    piVar4[1] = piVar3[1];
    *piVar4 = *piVar4 + *piVar3;
  }
  return;
}



ulonglong FUN_800002a4(uint param_1,uint param_2,uint param_3)

{
  if ((int)(param_3 - 0x20) < 0) {
    return CONCAT44(param_2 >> (param_3 & 0xff),
                    param_1 >> (param_3 & 0xff) | param_2 << (0x20 - param_3 & 0xff));
  }
  return (ulonglong)(param_2 >> (param_3 - 0x20 & 0xff));
}



uint * FUN_800002cc(uint *param_1)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  
  pcVar3 = (char *)((int)param_1 + 1);
  while (((uint)param_1 & 3) != 0) {
    cVar1 = *(char *)param_1;
    param_1 = (uint *)((int)param_1 + 1);
    if (cVar1 == '\0') {
      return (uint *)((int)param_1 - (int)pcVar3);
    }
  }
  do {
    uVar2 = *param_1;
    param_1 = param_1 + 1;
    uVar2 = uVar2 - DAT_8000030c & ~uVar2 & DAT_8000030c << 7;
  } while (uVar2 == 0);
  param_1 = (uint *)((int)param_1 - (int)pcVar3);
  if ((uVar2 & 0xff) != 0) {
    return (uint *)((int)param_1 + -3);
  }
  if ((uVar2 & 0xffff) == 0) {
    if ((uVar2 & 0xffffff) != 0) {
      return (uint *)((int)param_1 + -1);
    }
  }
  else {
    param_1 = (uint *)((int)param_1 + -2);
  }
  return param_1;
}



undefined8 FUN_80000310(undefined2 *param_1,uint param_2,uint param_3)

{
  undefined2 *puVar1;
  uint uVar2;
  uint local_20;
  
  puVar1 = param_1;
  local_20 = param_2;
  if (((uint)param_1 & 3) != 0) {
    if (param_3 == 0) goto LAB_80000344;
    param_3 = param_3 - 1;
    *param_1 = (short)param_2;
    puVar1 = param_1 + 1;
  }
  if (1 < param_3) {
    uVar2 = param_3 & 0xfffffffe;
    local_20 = uVar2 * 2;
    FUN_800004dc(puVar1,local_20,param_2 << 0x10 | param_2);
    param_3 = param_3 - uVar2;
    puVar1 = puVar1 + uVar2;
  }
LAB_80000344:
  if (param_3 != 0) {
    *puVar1 = (short)param_2;
  }
  return CONCAT44(local_20,param_1);
}



undefined8 FUN_80000350(uint *param_1,uint *param_2,uint param_3,uint param_4)

{
  uint *puVar1;
  uint *puVar2;
  byte *pbVar3;
  uint *puVar4;
  byte bVar5;
  undefined2 uVar6;
  uint uVar7;
  byte bVar8;
  uint in_r12;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  bool bVar12;
  bool bVar13;
  
  if (3 < param_3) {
    uVar9 = (uint)param_1 & 3;
    in_r12 = uVar9;
    if (uVar9 != 0) {
      bVar5 = *(byte *)param_2;
      puVar2 = (uint *)((int)param_2 + 1);
      if (uVar9 < 3) {
        puVar2 = (uint *)((int)param_2 + 2);
        in_r12 = (uint)*(byte *)(uint *)((int)param_2 + 1);
      }
      *(byte *)param_1 = bVar5;
      param_2 = puVar2;
      if (uVar9 < 2) {
        param_2 = (uint *)((int)puVar2 + 1);
        bVar5 = *(byte *)puVar2;
      }
      puVar2 = (uint *)((int)param_1 + 1);
      if (uVar9 < 3) {
        puVar2 = (uint *)((int)param_1 + 2);
        *(byte *)(uint *)((int)param_1 + 1) = (byte)in_r12;
      }
      param_3 = (param_3 + uVar9) - 4;
      param_1 = puVar2;
      if (uVar9 < 2) {
        param_1 = (uint *)((int)puVar2 + 1);
        *(byte *)puVar2 = bVar5;
      }
    }
    param_4 = (uint)param_2 & 3;
    if (param_4 == 0) {
      while (uVar9 = param_3 - 0x20, 0x1f < param_3) {
        uVar7 = param_2[1];
        uVar10 = param_2[2];
        uVar11 = param_2[3];
        *param_1 = *param_2;
        param_1[1] = uVar7;
        param_1[2] = uVar10;
        param_1[3] = uVar11;
        param_4 = param_2[4];
        uVar7 = param_2[5];
        uVar10 = param_2[6];
        uVar11 = param_2[7];
        param_2 = param_2 + 8;
        param_1[4] = param_4;
        param_1[5] = uVar7;
        param_1[6] = uVar10;
        param_1[7] = uVar11;
        param_1 = param_1 + 8;
        param_3 = uVar9;
      }
      if ((bool)((byte)(uVar9 >> 4) & 1)) {
        param_4 = *param_2;
        uVar7 = param_2[1];
        uVar10 = param_2[2];
        uVar11 = param_2[3];
        param_2 = param_2 + 4;
        *param_1 = param_4;
        param_1[1] = uVar7;
        param_1[2] = uVar10;
        param_1[3] = uVar11;
        param_1 = param_1 + 4;
      }
      if ((int)(param_3 << 0x1c) < 0) {
        param_4 = *param_2;
        uVar7 = param_2[1];
        param_2 = param_2 + 2;
        *param_1 = param_4;
        param_1[1] = uVar7;
        param_1 = param_1 + 2;
      }
      puVar1 = param_1;
      puVar2 = param_2;
      if ((bool)((byte)(uVar9 >> 2) & 1)) {
        puVar2 = param_2 + 1;
        param_4 = *param_2;
        puVar1 = param_1 + 1;
        *param_1 = param_4;
      }
      uVar6 = (undefined2)param_4;
      if ((uVar9 & 3) != 0) {
        bVar13 = (bool)((byte)(uVar9 >> 1) & 1);
        param_3 = param_3 << 0x1f;
        bVar12 = (int)param_3 < 0;
        puVar4 = puVar2;
        if (bVar13) {
          puVar4 = (uint *)((int)puVar2 + 2);
          uVar6 = *(undefined2 *)puVar2;
        }
        puVar2 = puVar4;
        if (bVar12) {
          puVar2 = (uint *)((int)puVar4 + 1);
          param_3 = (uint)*(byte *)puVar4;
        }
        puVar4 = puVar1;
        if (bVar13) {
          puVar4 = (uint *)((int)puVar1 + 2);
          *(undefined2 *)puVar1 = uVar6;
        }
        puVar1 = puVar4;
        if (bVar12) {
          puVar1 = (uint *)((int)puVar4 + 1);
          *(byte *)puVar4 = (byte)param_3;
        }
        return CONCAT44(puVar2,puVar1);
      }
      return CONCAT44(puVar2,puVar1);
    }
    bVar12 = 3 < param_3;
    param_3 = param_3 - 4;
    if (bVar12) {
      param_2 = (uint *)((int)param_2 - param_4);
      in_r12 = *param_2;
      puVar2 = param_1;
      if (param_4 == 2) {
        do {
          puVar1 = param_2;
          param_4 = in_r12 >> 0x10;
          param_2 = puVar1 + 1;
          in_r12 = *param_2;
          bVar12 = 3 < param_3;
          param_3 = param_3 - 4;
          param_4 = param_4 | in_r12 << 0x10;
          param_1 = puVar2 + 1;
          *puVar2 = param_4;
          puVar2 = param_1;
        } while (bVar12);
        param_2 = (uint *)((int)puVar1 + 6);
      }
      else {
        if (param_4 < 3) {
          do {
            puVar1 = param_2;
            param_4 = in_r12 >> 8;
            param_2 = puVar1 + 1;
            in_r12 = *param_2;
            bVar12 = 3 < param_3;
            param_3 = param_3 - 4;
            param_4 = param_4 | in_r12 << 0x18;
            param_1 = puVar2 + 1;
            *puVar2 = param_4;
            puVar2 = param_1;
          } while (bVar12);
          param_2 = (uint *)((int)puVar1 + 5);
        }
        else {
          do {
            puVar1 = param_2;
            param_4 = in_r12 >> 0x18;
            param_2 = puVar1 + 1;
            in_r12 = *param_2;
            bVar12 = 3 < param_3;
            param_3 = param_3 - 4;
            param_4 = param_4 | in_r12 << 8;
            param_1 = puVar2 + 1;
            *puVar2 = param_4;
            puVar2 = param_1;
          } while (bVar12);
          param_2 = (uint *)((int)puVar1 + 7);
        }
      }
    }
  }
  bVar8 = (byte)in_r12;
  bVar5 = (byte)param_4;
  bVar13 = (bool)((byte)(param_3 >> 1) & 1);
  param_3 = param_3 << 0x1f;
  bVar12 = (int)param_3 < 0;
  if (bVar13) {
    pbVar3 = (byte *)((int)param_2 + 1);
    bVar5 = *(byte *)param_2;
    param_2 = (uint *)((int)param_2 + 2);
    bVar8 = *pbVar3;
  }
  puVar2 = param_2;
  if (bVar12) {
    puVar2 = (uint *)((int)param_2 + 1);
    param_3 = (uint)*(byte *)param_2;
  }
  if (bVar13) {
    pbVar3 = (byte *)((int)param_1 + 1);
    *(byte *)param_1 = bVar5;
    param_1 = (uint *)((int)param_1 + 2);
    *pbVar3 = bVar8;
  }
  puVar1 = param_1;
  if (bVar12) {
    puVar1 = (uint *)((int)param_1 + 1);
    *(byte *)param_1 = (byte)param_3;
  }
  return CONCAT44(puVar2,puVar1);
}



uint * FUN_80000488(uint *param_1,uint param_2,uint param_3)

{
  uint uVar1;
  undefined uVar2;
  uint *puVar3;
  undefined *puVar4;
  uint *puVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  bool bVar9;
  
  param_3 = param_3 & 0xff;
  uVar6 = param_3 | param_3 << 8;
  uVar7 = uVar6 | uVar6 << 0x10;
  uVar2 = (undefined)param_3;
  if (param_2 < 4) {
    if ((bool)((byte)(param_2 >> 1) & 1)) {
      puVar4 = (undefined *)((int)param_1 + 1);
      *(undefined *)param_1 = uVar2;
      param_1 = (uint *)((int)param_1 + 2);
      *puVar4 = uVar2;
    }
    puVar3 = param_1;
    if ((int)(param_2 << 0x1f) < 0) {
      puVar3 = (uint *)((int)param_1 + 1);
      *(undefined *)param_1 = uVar2;
    }
    return puVar3;
  }
  if (((uint)param_1 & 3) != 0) {
    iVar8 = 4 - ((uint)param_1 & 3);
    puVar3 = param_1;
    if (iVar8 != 2) {
      puVar3 = (uint *)((int)param_1 + 1);
      *(undefined *)param_1 = uVar2;
    }
    param_2 = param_2 - iVar8;
    param_1 = puVar3;
    if (1 < iVar8) {
      param_1 = (uint *)((int)puVar3 + 2);
      *(short *)puVar3 = (short)uVar6;
    }
  }
  bVar9 = 0x1f < param_2;
  param_2 = param_2 - 0x20;
  do {
    if (bVar9) {
      *param_1 = uVar7;
      param_1[1] = uVar7;
      param_1[2] = uVar7;
      param_1[3] = uVar7;
      param_1[4] = uVar7;
      param_1[5] = uVar7;
      param_1[6] = uVar7;
      param_1[7] = uVar7;
      param_1 = param_1 + 8;
      bVar9 = 0x1f < param_2;
      param_2 = param_2 - 0x20;
    }
  } while (bVar9);
  if ((bool)((byte)(param_2 >> 4) & 1)) {
    *param_1 = uVar7;
    param_1[1] = uVar7;
    param_1[2] = uVar7;
    param_1[3] = uVar7;
    param_1 = param_1 + 4;
  }
  if ((int)(param_2 << 0x1c) < 0) {
    *param_1 = uVar7;
    param_1[1] = uVar7;
    param_1 = param_1 + 2;
  }
  uVar1 = param_2 << 0x1e;
  puVar3 = param_1;
  if ((bool)((byte)((param_2 << 0x1c) >> 0x1e) & 1)) {
    puVar3 = param_1 + 1;
    *param_1 = uVar7;
  }
  if (uVar1 == 0) {
    return puVar3;
  }
  puVar5 = puVar3;
  if ((int)uVar1 < 0) {
    puVar5 = (uint *)((int)puVar3 + 2);
    *(short *)puVar3 = (short)uVar6;
  }
  puVar3 = puVar5;
  if ((uVar1 & 0x40000000) != 0) {
    puVar3 = (uint *)((int)puVar5 + 1);
    *(undefined *)puVar5 = uVar2;
  }
  return puVar3;
}



undefined4 * FUN_800004dc(undefined4 *param_1,uint param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  bool bVar4;
  
  bVar4 = 0x1f < param_2;
  param_2 = param_2 - 0x20;
  do {
    if (bVar4) {
      *param_1 = param_3;
      param_1[1] = param_3;
      param_1[2] = param_3;
      param_1[3] = param_3;
      param_1[4] = param_3;
      param_1[5] = param_3;
      param_1[6] = param_3;
      param_1[7] = param_3;
      param_1 = param_1 + 8;
      bVar4 = 0x1f < param_2;
      param_2 = param_2 - 0x20;
    }
  } while (bVar4);
  if ((bool)((byte)(param_2 >> 4) & 1)) {
    *param_1 = param_3;
    param_1[1] = param_3;
    param_1[2] = param_3;
    param_1[3] = param_3;
    param_1 = param_1 + 4;
  }
  if ((int)(param_2 << 0x1c) < 0) {
    *param_1 = param_3;
    param_1[1] = param_3;
    param_1 = param_1 + 2;
  }
  uVar1 = param_2 << 0x1e;
  puVar3 = param_1;
  if ((bool)((byte)((param_2 << 0x1c) >> 0x1e) & 1)) {
    puVar3 = param_1 + 1;
    *param_1 = param_3;
  }
  if (uVar1 != 0) {
    puVar2 = puVar3;
    if ((int)uVar1 < 0) {
      puVar2 = (undefined4 *)((int)puVar3 + 2);
      *(short *)puVar3 = (short)param_3;
    }
    puVar3 = puVar2;
    if ((uVar1 & 0x40000000) != 0) {
      puVar3 = (undefined4 *)((int)puVar2 + 1);
      *(char *)puVar2 = (char)param_3;
    }
    return puVar3;
  }
  return puVar3;
}



longlong FUN_8000052c(uint param_1,uint param_2)

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
    if (param_1 >> 4 < param_2) goto LAB_800006f8;
    if (param_1 >> 8 < param_2) goto LAB_800006c8;
    uVar2 = param_2 << 6;
    uVar6 = 0xfc000000;
    if (param_1 >> 8 < uVar2) goto LAB_800006c8;
    uVar2 = param_2 << 0xc;
    uVar6 = 0xfff00000;
    if (param_1 >> 8 < uVar2) goto LAB_800006c8;
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
LAB_800006c8:
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
LAB_800006f8:
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
LAB_80000744:
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
      if (param_1 >> 0xc < param_2) goto LAB_800005b8;
      if (param_1 >> 0x10 < param_2) goto LAB_80000588;
      uVar6 = param_2 << 8;
      iVar4 = -0x1000000;
      if (uVar6 <= param_1 >> 0x10) {
        iVar4 = -0x10000;
        uVar6 = param_2 << 0x10;
      }
      if (param_1 >> 0xc < uVar6) goto LAB_800005b8;
      bVar7 = uVar6 == 0;
      if (bVar7) goto LAB_80000744;
      do {
        if (bVar7) {
          uVar6 = uVar6 >> 8;
        }
LAB_80000588:
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
LAB_800005b8:
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



undefined4 FUN_80000754(void)

{
  return DAT_8000075c;
}



int FUN_80000768(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 local_10;
  
  local_10 = param_4;
  iVar1 = FUN_80000854(0,&local_10,param_2);
  if (iVar1 != 0) {
    FUN_800007fa(param_1,local_10,iVar1);
    iVar1 = 1;
  }
  return iVar1;
}



void FUN_80000788(void)

{
  FUN_8000082e(1);
  return;
}



void FUN_80000792(void)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  uint in_r3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  uint local_18;
  
  local_18 = in_r3;
  uVar7 = FUN_8000083c();
  uVar3 = (uint)((ulonglong)uVar7 >> 0x20);
  if (uVar3 < (uint)uVar7 + 0x10) {
    iVar1 = FUN_80000854(0,&local_18,0x10);
    if (iVar1 == 0) {
      FUN_8000082e();
    }
    uVar4 = (uint)uVar7;
    if (local_18 != uVar3) {
      uVar4 = local_18;
    }
    uVar7 = CONCAT44(local_18 + iVar1,uVar4);
  }
  iVar1 = (int)((ulonglong)uVar7 >> 0x20);
  iVar5 = (int)uVar7;
  piVar2 = (int *)FUN_80000754();
  *piVar2 = iVar5;
  iVar6 = iVar5 + 0x10;
  FUN_800007ec(iVar5);
  if (iVar1 != iVar6) {
    FUN_800007fa(*piVar2,iVar6,iVar1 - iVar6);
  }
  return;
}



void FUN_800007ec(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = param_1;
  return;
}



void FUN_800007fa(int *param_1,int *param_2,int param_3)

{
  int *piVar1;
  int *piVar2;
  
  piVar2 = (int *)param_1[1];
  while ((piVar1 = piVar2, piVar1 != (int *)0x0 && (piVar1 < param_2))) {
    piVar2 = (int *)piVar1[1];
    param_1 = piVar1;
  }
  piVar2 = param_2;
  if ((int *)(*param_1 + (int)param_1) != param_2) {
    piVar2 = (int *)(((int)param_2 + 3U & 0xfffffff8) + 4);
    param_3 = param_3 - (int)((int)piVar2 - (int)param_2);
  }
  *piVar2 = param_3;
  FUN_8000022e(piVar2 + 1);
  return;
}



void FUN_8000082e(void)

{
  FUN_800008a4();
  FUN_80000898();
  return;
}



void FUN_8000083c(int param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR_DAT_80000888;
  *(undefined **)PTR_DAT_80000888 = (undefined *)(param_1 + 0x1000U);
  if ((undefined *)(param_1 + 0x1000U) <= register0x00000054) {
    return;
  }
  *(BADSPACEBASE **)puVar1 = register0x00000054;
  return;
}



int FUN_80000854(int param_1,int *param_2,int param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  undefined auStack4112 [4096];
  
  puVar1 = PTR_DAT_80000888;
  iVar4 = *(int *)PTR_DAT_80000888;
  puVar3 = (undefined *)(iVar4 + param_3);
  if (puVar3 <= auStack4112) {
    puVar2 = puVar3 + 0x1000;
    if (puVar3 + (int)(auStack4112 + -(int)puVar3) / 2 < puVar3 + 0x1000) {
      puVar2 = puVar3 + (int)(auStack4112 + -(int)puVar3) / 2;
    }
    *param_2 = iVar4;
    param_1 = ((uint)(puVar2 + 7) & 0xfffffff8) - iVar4;
    *(uint *)puVar1 = (uint)(puVar2 + 7) & 0xfffffff8;
  }
  return param_1;
}



void FUN_80000898(int param_1)

{
  if (param_1 != 0) {
    FUN_80003794();
  }
  return;
}



undefined4 FUN_800008a4(int param_1)

{
  char *pcVar1;
  
  if (param_1 == 1) {
    pcVar1 = s___Heap_memory_corrupted_800008dc;
  }
  else {
    pcVar1 = (char *)0x0;
  }
  FUN_800008f4(s_SIGRTMEM__Out_of_heap_memory_800008bc,pcVar1);
  return 1;
}



void FUN_800008f4(char *param_1,char *param_2)

{
  char cVar1;
  
  cVar1 = '\n';
  while ((FUN_80003798(cVar1), param_1 != (char *)0x0 && (cVar1 = *param_1, cVar1 != '\0'))) {
    param_1 = param_1 + 1;
  }
  while ((param_2 != (char *)0x0 && (*param_2 != '\0'))) {
    param_2 = param_2 + 1;
    FUN_80003798();
  }
  FUN_80003798(10);
  return;
}



longlong FUN_80000928(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  
  iVar3 = 0;
  uVar1 = param_2;
  if (param_2 <= param_1 >> 2) {
    if (param_2 <= param_1 >> 5) {
      if (param_2 <= param_1 >> 8) {
        if (param_1 >> 0xc < param_2) goto LAB_800005b8;
        if (param_1 >> 0x10 < param_2) goto LAB_80000588;
        uVar1 = param_2 << 8;
        iVar3 = -0x1000000;
        if (uVar1 <= param_1 >> 0x10) {
          iVar3 = -0x10000;
          uVar1 = param_2 << 0x10;
        }
        if (param_1 >> 0xc < uVar1) goto LAB_800005b8;
        bVar4 = uVar1 == 0;
        if (bVar4) {
          return (ulonglong)param_1 << 0x20;
        }
        do {
          if (bVar4) {
            uVar1 = uVar1 >> 8;
          }
LAB_80000588:
          bVar4 = uVar1 <= param_1 >> 0xf;
          if (bVar4) {
            param_1 = param_1 + uVar1 * -0x8000;
          }
          bVar5 = uVar1 <= param_1 >> 0xe;
          if (bVar5) {
            param_1 = param_1 + uVar1 * -0x4000;
          }
          bVar6 = uVar1 <= param_1 >> 0xd;
          if (bVar6) {
            param_1 = param_1 + uVar1 * -0x2000;
          }
          bVar7 = uVar1 <= param_1 >> 0xc;
          if (bVar7) {
            param_1 = param_1 + uVar1 * -0x1000;
          }
          iVar3 = (((iVar3 * 2 + (uint)bVar4) * 2 + (uint)bVar5) * 2 + (uint)bVar6) * 2 +
                  (uint)bVar7;
LAB_800005b8:
          bVar4 = uVar1 <= param_1 >> 0xb;
          if (bVar4) {
            param_1 = param_1 + uVar1 * -0x800;
          }
          bVar5 = uVar1 <= param_1 >> 10;
          if (bVar5) {
            param_1 = param_1 + uVar1 * -0x400;
          }
          bVar6 = uVar1 <= param_1 >> 9;
          if (bVar6) {
            param_1 = param_1 + uVar1 * -0x200;
          }
          uVar2 = ((iVar3 * 2 + (uint)bVar4) * 2 + (uint)bVar5) * 2 + (uint)bVar6;
          bVar5 = uVar1 <= param_1 >> 8;
          if (bVar5) {
            param_1 = param_1 + uVar1 * -0x100;
          }
          bVar4 = !bVar5 && CARRY4(uVar2,uVar2) || bVar5 && uVar2 * 2 + 1 <= uVar2;
          iVar3 = uVar2 * 2 + (uint)bVar5;
        } while (bVar4);
      }
      bVar4 = uVar1 <= param_1 >> 7;
      if (bVar4) {
        param_1 = param_1 + uVar1 * -0x80;
      }
      bVar5 = uVar1 <= param_1 >> 6;
      if (bVar5) {
        param_1 = param_1 + uVar1 * -0x40;
      }
      bVar6 = uVar1 <= param_1 >> 5;
      if (bVar6) {
        param_1 = param_1 + uVar1 * -0x20;
      }
      iVar3 = ((iVar3 * 2 + (uint)bVar4) * 2 + (uint)bVar5) * 2 + (uint)bVar6;
    }
    bVar4 = uVar1 <= param_1 >> 4;
    if (bVar4) {
      param_1 = param_1 + uVar1 * -0x10;
    }
    bVar5 = uVar1 <= param_1 >> 3;
    if (bVar5) {
      param_1 = param_1 + uVar1 * -8;
    }
    bVar6 = uVar1 <= param_1 >> 2;
    if (bVar6) {
      param_1 = param_1 + uVar1 * -4;
    }
    iVar3 = ((iVar3 * 2 + (uint)bVar4) * 2 + (uint)bVar5) * 2 + (uint)bVar6;
  }
  bVar4 = uVar1 <= param_1 >> 1;
  if (bVar4) {
    param_1 = param_1 + uVar1 * -2;
  }
  uVar2 = param_1 - uVar1;
  if (uVar1 > param_1) {
    uVar2 = param_1;
  }
  return CONCAT44(uVar2,(iVar3 * 2 + (uint)bVar4) * 2 + (uint)(uVar1 <= param_1));
}



int FUN_800009f8(undefined4 param_1,undefined2 *param_2)

{
  undefined *puVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar2 = DAT_80000b14;
  puVar1 = DAT_80000b10;
  *param_2 = 6;
  *(undefined4 *)(param_2 + 2) = 5;
  *(undefined4 *)(param_2 + 4) = uVar2;
  iVar3 = FUN_800067dc(param_1);
  uVar2 = DAT_80000b18;
  if (iVar3 != 0) {
    return iVar3;
  }
  if ((CONCAT11(*puVar1,puVar1[1]) != 0) && (CONCAT11(puVar1[0x1c],puVar1[0x1d]) == 0)) {
    *param_2 = 6;
    *(undefined4 *)(param_2 + 2) = 5;
    *(undefined4 *)(param_2 + 4) = uVar2;
    iVar3 = FUN_800067dc(param_1);
    if (iVar3 != 0) {
      return iVar3;
    }
    if (CONCAT11(*puVar1,puVar1[1]) != 0) {
      if (CONCAT11(puVar1[0x1c],puVar1[0x1d]) == 0) {
        FUN_8000705c(s_switch_into_high_speed_mode_____80000b1c);
      }
      return 0;
    }
  }
  return 1;
}



void FUN_80000b40(void)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  char *pcVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  bool bVar21;
  bool bVar22;
  undefined auStack680 [552];
  int local_80 [6];
  undefined auStack104 [32];
  uint local_48;
  uint local_44;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  
  iVar8 = FUN_80004208(auStack680,s_UTX_1013_bin_80000ef4,1);
  if (iVar8 == 0) {
    iVar8 = 1;
    pcVar10 = s_UTX_1013_bin_80000ef4;
  }
  else {
    FUN_80004124(auStack680);
    iVar8 = FUN_80004208(auStack680,s_FSI_1013_bin_80000f04,1);
    if (iVar8 == 0) {
      iVar8 = 2;
      pcVar10 = s_FSI_1013_bin_80000f04;
    }
    else {
      FUN_80004124(auStack680);
      iVar8 = FUN_80004208(auStack680,s_DAN_1013_bin_80000f14,1);
      if (iVar8 == 0) {
        iVar8 = 3;
        pcVar10 = s_DAN_1013_bin_80000f14;
      }
      else {
        FUN_80004124(auStack680);
        iVar8 = FUN_80004208(auStack680,s_YPK_1013_bin_80000f24,1);
        if (iVar8 != 0) {
          FUN_80004124(auStack680);
          return;
        }
        iVar8 = 4;
        pcVar10 = s_YPK_1013_bin_80000f24;
      }
    }
  }
  FUN_800047bc(pcVar10,local_80);
  uVar6 = DAT_80000f34;
  FUN_80001a34(0xca,0xd0,DAT_80000f38,0x40,DAT_80000f34);
  FUN_80001a34(0xcc,0xd2,DAT_80000f3c,0x3c,0);
  FUN_80004558(auStack680,DAT_80000f40,local_80[0],0);
  FUN_80004124(auStack680);
  iVar7 = DAT_80000f40;
  iVar9 = DAT_80000f40 + local_80[0];
  local_2c = (uint)*(byte *)(iVar9 + -0x21) |
             (uint)*(byte *)(iVar9 + -0x23) << 0x10 | (uint)*(byte *)(iVar9 + -0x24) << 0x18 |
             (uint)*(byte *)(iVar9 + -0x22) << 8;
  local_30 = (uint)*(byte *)(iVar9 + -0x1d) |
             (uint)*(byte *)(iVar9 + -0x1f) << 0x10 | (uint)*(byte *)(iVar9 + -0x20) << 0x18 |
             (uint)*(byte *)(iVar9 + -0x1e) << 8;
  local_34 = (uint)*(byte *)(iVar9 + -0x19) |
             (uint)*(byte *)(iVar9 + -0x1b) << 0x10 | (uint)*(byte *)(iVar9 + -0x1c) << 0x18 |
             (uint)*(byte *)(iVar9 + -0x1a) << 8;
  local_38 = (uint)*(byte *)(iVar9 + -0x15) |
             (uint)*(byte *)(iVar9 + -0x17) << 0x10 | (uint)*(byte *)(iVar9 + -0x18) << 0x18 |
             (uint)*(byte *)(iVar9 + -0x16) << 8;
  local_3c = (uint)*(byte *)(iVar9 + -0x11) |
             (uint)*(byte *)(iVar9 + -0x13) << 0x10 | (uint)*(byte *)(iVar9 + -0x14) << 0x18 |
             (uint)*(byte *)(iVar9 + -0x12) << 8;
  local_40 = (uint)*(byte *)(iVar9 + -0xd) |
             (uint)*(byte *)(iVar9 + -0xf) << 0x10 | (uint)*(byte *)(iVar9 + -0x10) << 0x18 |
             (uint)*(byte *)(iVar9 + -0xe) << 8;
  bVar1 = *(byte *)(iVar9 + -3);
  bVar2 = *(byte *)(iVar9 + -4);
  local_44 = (uint)*(byte *)(iVar9 + -0xb) << 0x10 | (uint)*(byte *)(iVar9 + -0xc) << 0x18 |
             (uint)*(byte *)(iVar9 + -10) << 8 | (uint)*(byte *)(iVar9 + -9);
  bVar3 = *(byte *)(iVar9 + -2);
  bVar4 = *(byte *)(iVar9 + -1);
  local_48 = (uint)*(byte *)(iVar9 + -5) |
             (uint)*(byte *)(iVar9 + -6) << 8 |
             (uint)*(byte *)(iVar9 + -7) << 0x10 | (uint)*(byte *)(iVar9 + -8) << 0x18;
  FUN_80000350(auStack104,DAT_80000f40 + 0x14000,0xc);
  FUN_80000488(iVar7 + 0x14000,0xc,0xff);
  uVar15 = 0;
  do {
    FUN_80002d48(uVar15 * 0xffff + 0x13000,iVar7 + uVar15 * 0xffff,uVar6);
    FUN_80001a34(uVar15 * 0xd + 0xcf & 0xffff,0xd5,10,0x36,uVar6);
    uVar15 = uVar15 + 1;
  } while (uVar15 < 0x1e);
  FUN_80000350(DAT_80000f40,auStack104,0xc);
  FUN_80002d58(0,DAT_80000f40,0x27000,0xc);
  FUN_80002c98(0x13000,DAT_80000f40,local_80[0] + -0x24);
  uVar11 = 0;
  uVar19 = 0;
  uVar18 = 0;
  uVar17 = 0;
  uVar16 = 0;
  uVar14 = 0;
  uVar13 = 0;
  uVar20 = 0;
  uVar12 = 0;
  uVar15 = 0;
  if (local_80[0] != 0x48) {
    do {
      bVar5 = *(byte *)(DAT_80000f40 + uVar15);
      if ((bVar5 & 0x80) != 0) {
        uVar19 = uVar19 + uVar15;
      }
      if ((bVar5 & 0x40) != 0) {
        uVar18 = uVar18 + uVar15;
      }
      if ((bVar5 & 0x20) != 0) {
        uVar17 = uVar17 + uVar15;
      }
      if ((bVar5 & 0x10) != 0) {
        uVar16 = uVar16 + uVar15;
      }
      if ((bVar5 & 8) != 0) {
        uVar14 = uVar14 + uVar15;
      }
      if ((bVar5 & 4) != 0) {
        uVar13 = uVar13 + uVar15;
      }
      if ((bVar5 & 2) != 0) {
        uVar20 = uVar20 + uVar15;
      }
      if ((bVar5 & 1) != 0) {
        uVar12 = uVar12 + uVar15;
      }
      uVar15 = uVar15 + 1;
      uVar11 = uVar11 + bVar5;
    } while (uVar15 < local_80[0] - 0x48U);
  }
  uVar15 = local_2c;
  if (uVar11 == local_2c) {
    uVar15 = local_30;
  }
  if (uVar11 == local_2c && uVar19 == uVar15) {
    uVar15 = local_34;
    if (uVar18 == local_34) {
      uVar15 = local_38;
    }
    if (uVar18 == local_34 && uVar17 == uVar15) {
      uVar15 = local_3c;
      if (uVar16 == local_3c) {
        uVar15 = local_40;
      }
      if (uVar16 == local_3c && uVar14 == uVar15) {
        bVar21 = uVar13 == local_44;
        uVar15 = local_44;
        if (bVar21) {
          uVar15 = local_48;
        }
        bVar22 = bVar21 && uVar20 == uVar15;
        if (bVar21 && uVar20 == uVar15) {
          bVar22 = uVar12 == ((uint)bVar4 |
                             (uint)bVar1 << 0x10 | (uint)bVar2 << 0x18 | (uint)bVar3 << 8);
        }
        if (bVar22) {
          if (iVar8 == 1) {
            pcVar10 = s_UTX_1013_bin_80000ef4;
          }
          else {
            if (iVar8 == 2) {
              pcVar10 = s_FSI_1013_bin_80000f04;
            }
            else {
              if (iVar8 == 3) {
                pcVar10 = s_DAN_1013_bin_80000f14;
              }
              else {
                if (iVar8 != 4) goto LAB_80001008;
                pcVar10 = s_YPK_1013_bin_80000f24;
              }
            }
          }
          FUN_80004a10(pcVar10);
          goto LAB_80001008;
        }
      }
    }
  }
  FUN_80002d48(0x27000,DAT_80000f40,1000);
LAB_80001008:
  FUN_8000338c();
  return;
}



void FUN_80001018(int param_1)

{
  uint *puVar1;
  int iVar2;
  
  puVar1 = DAT_800010e0;
  iVar2 = *(int *)(param_1 + 8);
  *DAT_800010e0 = *DAT_800010e0 | 0x1000;
  puVar1[0x98] = puVar1[0x98] | 0x1000;
  FUN_800010e4(1);
  puVar1 = (uint *)(iVar2 + 0x800);
  *(uint *)(iVar2 + 0x800) = *(uint *)(iVar2 + 0x800) | 1;
  *(uint *)(iVar2 + 0x808) =
       *(int *)(param_1 + 0x1c) - 1U | (*(ushort *)(param_1 + 0x20) - 1) * 0x10000;
  *(uint *)(iVar2 + 0x810) =
       *(int *)(param_1 + 0x1c) - 1U | (*(ushort *)(param_1 + 0x20) - 1) * 0x10000;
  *(int *)(iVar2 + 0x840) = *(int *)(param_1 + 0x1c) << 4;
  *(int *)(iVar2 + 0x850) = *(int *)(param_1 + 0x38) << 3;
  *(uint *)(iVar2 + 0x860) = *(uint *)(param_1 + 0x38) >> 0x1d;
  *(undefined4 *)(iVar2 + 0x8a0) = 0x500;
  *puVar1 = *puVar1 | 0x100;
  *(uint *)(iVar2 + 0x870) = *(uint *)(iVar2 + 0x870) | 1;
  *puVar1 = *puVar1 | 2;
  return;
}



void FUN_800010e4(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined8 uVar2;
  uint uVar3;
  
  uVar1 = FUN_80001b38(0,param_1,param_3,param_4,0);
  uVar3 = uVar1;
  do {
    uVar2 = FUN_80001b38(uVar1);
    uVar1 = (int)uVar2 - uVar3;
  } while (uVar1 < (uint)((ulonglong)uVar2 >> 0x20));
  return;
}



void FUN_80001118(undefined4 param_1)

{
  bool bVar1;
  undefined4 uVar2;
  uint uVar3;
  uint local_18;
  
  uVar2 = FUN_800075cc(param_1);
  FUN_800075fc(uVar2,DAT_80001198);
  uVar3 = FUN_80007578();
  local_18 = 0;
  while (local_18 < uVar3) {
    bVar1 = false;
    while (!bVar1) {
      bVar1 = true;
    }
    local_18 = local_18 + 1;
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x80001644)
// WARNING: Removing unreachable block (ram,0x80001648)
// WARNING: Removing unreachable block (ram,0x8000164c)
// WARNING: Removing unreachable block (ram,0x80001650)
// WARNING: Removing unreachable block (ram,0x80001654)
// WARNING: Removing unreachable block (ram,0x80001658)
// WARNING: Removing unreachable block (ram,0x8000165c)
// WARNING: Removing unreachable block (ram,0x80001660)

void FUN_800012b8(void)

{
  uint *puVar1;
  
  puVar1 = DAT_80001364;
  FUN_8000160c(DAT_80001364,0,0);
  FUN_8000160c(puVar1,1,0);
  FUN_8000160c(puVar1,2,0);
  FUN_8000160c(puVar1,3,0);
  FUN_8000160c(puVar1,4,0);
  FUN_8000160c(puVar1,5,0);
  FUN_8000160c(puVar1,6,0);
  *puVar1 = *puVar1 & 0xfffffff;
  *puVar1 = *puVar1 & 0xefffffff;
  return;
}



uint FUN_80001368(void)

{
  int iVar1;
  
  FUN_800012b8();
  iVar1 = DAT_800013b4;
  FUN_80001670(DAT_800013b4,9);
  FUN_80001670(iVar1,10);
  FUN_80001670(iVar1,8);
  FUN_80001684(iVar1,8);
  return *(uint *)(iVar1 + 0x10) & 0xff;
}



// WARNING: Removing unreachable block (ram,0x80001644)
// WARNING: Removing unreachable block (ram,0x80001648)
// WARNING: Removing unreachable block (ram,0x8000164c)
// WARNING: Removing unreachable block (ram,0x80001650)
// WARNING: Removing unreachable block (ram,0x80001654)
// WARNING: Removing unreachable block (ram,0x80001658)
// WARNING: Removing unreachable block (ram,0x8000165c)
// WARNING: Removing unreachable block (ram,0x80001660)

void FUN_800013b8(void)

{
  uint *puVar1;
  undefined4 uVar2;
  undefined4 unaff_r4;
  undefined4 in_lr;
  
  uVar2 = DAT_80001410;
  FUN_8000160c(DAT_80001410,9,1,0);
  FUN_8000160c(uVar2,10,1,0);
  FUN_8000160c(uVar2,8,1,0);
  FUN_80001684(uVar2,8);
  puVar1 = DAT_80001364;
  FUN_8000160c(DAT_80001364,0,0,0,unaff_r4,in_lr);
  FUN_8000160c(puVar1,1,0);
  FUN_8000160c(puVar1,2,0);
  FUN_8000160c(puVar1,3,0);
  FUN_8000160c(puVar1,4,0);
  FUN_8000160c(puVar1,5,0);
  FUN_8000160c(puVar1,6,0);
  *puVar1 = *puVar1 & 0xfffffff;
  *puVar1 = *puVar1 & 0xefffffff;
  return;
}



void FUN_80001414(uint param_1)

{
  int iVar1;
  
  iVar1 = DAT_8000150c;
  FUN_8000160c(DAT_8000150c,0,1);
  FUN_8000160c(iVar1,1,1,0);
  FUN_8000160c(iVar1,2,1,0);
  FUN_8000160c(iVar1,3,1,0);
  FUN_8000160c(iVar1,4,1,0);
  FUN_8000160c(iVar1,5,1,0);
  FUN_8000160c(iVar1,6,1,0);
  FUN_8000160c(iVar1,7,1,0);
  FUN_80001684(iVar1,9);
  FUN_80001670(iVar1,10);
  *(uint *)(iVar1 + 0x10) = param_1 & 0xff | *(uint *)(iVar1 + 0x10) & 0xffffff00;
  FUN_80001670(iVar1,8);
  *(uint *)(iVar1 + 0x10) = *(uint *)(iVar1 + 0x10) | 0x100;
  return;
}



void FUN_80001510(uint param_1)

{
  int iVar1;
  
  iVar1 = DAT_80001608;
  FUN_8000160c(DAT_80001608,0,1);
  FUN_8000160c(iVar1,1,1,0);
  FUN_8000160c(iVar1,2,1,0);
  FUN_8000160c(iVar1,3,1,0);
  FUN_8000160c(iVar1,4,1,0);
  FUN_8000160c(iVar1,5,1,0);
  FUN_8000160c(iVar1,6,1,0);
  FUN_8000160c(iVar1,7,1,0);
  FUN_80001684(iVar1,9);
  FUN_80001684(iVar1,10);
  *(uint *)(iVar1 + 0x10) = param_1 & 0xff | *(uint *)(iVar1 + 0x10) & 0xffffff00;
  FUN_80001670(iVar1,8);
  *(uint *)(iVar1 + 0x10) = *(uint *)(iVar1 + 0x10) | 0x100;
  return;
}



void FUN_8000160c(int param_1,uint param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  
  uVar1 = param_2 >> 3;
  uVar2 = (param_2 << 0x1d) >> 0x1b;
  bVar3 = param_3 == 0;
  *(uint *)(param_1 + uVar1 * 4) = *(uint *)(param_1 + uVar1 * 4) & ~(0xf << uVar2);
  if (bVar3) {
    param_3 = *(uint *)(param_1 + uVar1 * 4);
  }
  if (bVar3) {
    param_3 = param_3 & ~(1 << uVar2);
  }
  else {
    if (param_3 == 1) {
      *(uint *)(param_1 + uVar1 * 4) = *(uint *)(param_1 + uVar1 * 4) | 1 << uVar2;
      return;
    }
    param_3 = *(uint *)(param_1 + uVar1 * 4) | param_3 << uVar2;
  }
  *(uint *)(param_1 + uVar1 * 4) = param_3;
  return;
}



void FUN_80001670(int param_1,uint param_2)

{
  *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) & ~(1 << (param_2 & 0xff));
  return;
}



void FUN_80001684(int param_1,uint param_2)

{
  *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | 1 << (param_2 & 0xff);
  return;
}



void FUN_80001698(undefined4 param_1,undefined2 *param_2,int param_3)

{
  byte bVar1;
  byte bVar2;
  byte **ppbVar3;
  uint *puVar4;
  undefined *puVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  char cVar10;
  uint *puVar11;
  int iVar12;
  undefined4 unaff_r4;
  int iVar13;
  undefined4 unaff_r5;
  undefined4 unaff_r6;
  byte *unaff_r7;
  byte *pbVar14;
  undefined4 unaff_r8;
  byte *pbVar15;
  byte **ppbVar16;
  undefined4 uVar17;
  bool bVar18;
  bool bVar19;
  undefined8 uVar20;
  byte abStack105 [41];
  uint uStack64;
  uint uStack60;
  undefined4 uStack52;
  undefined4 uStack48;
  undefined4 uStack44;
  byte *pbStack40;
  undefined4 uStack36;
  char *pcVar21;
  undefined4 uStack4;
  
  puVar5 = PTR_DAT_80001840;
  uVar17 = *(undefined4 *)(PTR_DAT_80001840 + 4);
  *param_2 = 9;
  *(undefined4 *)(param_2 + 2) = 7;
  *(undefined4 *)(param_2 + 4) = uVar17;
  FUN_800067dc(param_1,param_2,0);
  puVar4 = DAT_80001844;
  uVar6 = *(uint *)(param_2 + 0xc);
  *DAT_80001844 = uVar6;
  uVar9 = *(uint *)(param_2 + 10);
  bVar18 = (uVar6 & 0xc0000000) == 0;
  puVar4[1] = uVar9;
  uVar7 = *(uint *)(param_2 + 8);
  puVar4[2] = uVar7;
  uVar6 = *(uint *)(param_2 + 6);
  puVar4[3] = uVar6;
  if (!bVar18) {
    uVar6 = *(uint *)puVar5;
  }
  if (bVar18 || uVar6 == 3) {
    uVar7 = (((uVar9 << 0x16) >> 0x14 | uVar7 >> 0x1e) + 1 << ((uVar7 << 0xe) >> 0x1d) + 2) <<
            ((uVar9 << 0xc) >> 0x1c);
    uVar6 = uVar7 >> 9;
    *(uint *)(param_3 + 4) = uVar6;
    *(uint *)(param_3 + 8) = uVar7 >> 10;
  }
  else {
    iVar8 = ((uVar9 << 0x1a) >> 10 | uVar7 >> 0x10) * 0x200 + 0x200;
    uVar6 = iVar8 * 2;
    *(int *)(param_3 + 8) = iVar8;
    *(uint *)(param_3 + 4) = uVar6;
  }
  *(uint *)(puVar5 + 0xc) = uVar6;
  *(undefined4 *)(param_3 + 0xc) = 0x200;
  uVar17 = *(undefined4 *)(puVar5 + 4);
  uStack4 = 7;
  *param_2 = 10;
  *(undefined4 *)(param_2 + 2) = 7;
  *(undefined4 *)(param_2 + 4) = uVar17;
  FUN_800067dc(param_1,param_2,0);
  puVar11 = DAT_80001844;
  uVar6 = *(uint *)(param_2 + 0xc);
  *puVar4 = uVar6;
  puVar4[1] = *(uint *)(param_2 + 10);
  puVar4[2] = *(uint *)(param_2 + 8);
  puVar4[3] = *(uint *)(param_2 + 6);
  *(char *)(param_3 + 0x10) = (char)(uVar6 >> 0x18);
  *(undefined *)(param_3 + 0x30) = *(undefined *)(puVar11 + 1);
  *(undefined *)(param_3 + 0x31) = *(undefined *)((int)puVar11 + 5);
  *(undefined *)(param_3 + 0x32) = *(undefined *)((int)puVar11 + 6);
  *(undefined *)(param_3 + 0x33) = *(undefined *)((int)puVar11 + 7);
  *(undefined *)(param_3 + 0x34) = *(undefined *)(puVar11 + 2);
  *(undefined *)(param_3 + 0x50) = *(undefined *)((int)puVar11 + 0x13);
  *(undefined *)(param_3 + 0x51) = *(undefined *)(puVar11 + 5);
  *(undefined *)(param_3 + 0x52) = *(undefined *)((int)puVar11 + 0x15);
  *(undefined *)(param_3 + 0x53) = *(undefined *)((int)puVar11 + 0x16);
  FUN_8000705c(s_SD_info_print____80001848);
  FUN_8000705c(s_SD_info__diskSize___d__8000185c,*(undefined4 *)(param_3 + 8));
  FUN_8000705c(s_SD_info__totalSectorN___d__80001878,*(undefined4 *)(param_3 + 4));
  pcVar21 = s_SD_info__sectorSize___d__80001898;
  uStack36 = unaff_r8;
  pbStack40 = unaff_r7;
  uStack44 = unaff_r6;
  uStack48 = unaff_r5;
  uStack52 = unaff_r4;
  ppbVar3 = (byte **)&stack0xfffffff4;
  puVar4 = DAT_80007510;
  bVar1 = s_SD_info__sectorSize___d__80001898[0];
joined_r0x8000707c:
  if (bVar1 == 0) {
    DAT_80007510 = puVar4;
    return;
  }
  bVar1 = *pcVar21;
  DAT_80007510 = puVar4;
  if (bVar1 == 0x25) {
    uVar7 = (uint)((byte *)pcVar21)[1];
    uVar6 = 0;
    uVar9 = 0x20;
    ppbVar16 = ppbVar3 + 1;
    pbVar15 = *ppbVar3;
    if (uVar7 == 0x30) {
      uVar9 = 0x30;
    }
    bVar18 = false;
    iVar8 = 0;
    pcVar21 = (char *)((byte *)pcVar21 + 2);
    if (uVar7 != 0) {
      do {
        if (9 < uVar7 - 0x30) {
          if (uVar7 == 100) {
LAB_800073f0:
            iVar8 = -10;
            break;
          }
          if (uVar7 < 0x65) {
            if (uVar7 == 0x2d) {
              bVar18 = true;
              goto LAB_80007118;
            }
            if (uVar7 < 0x2e) {
              if (uVar7 == 0) {
                pcVar21 = (char *)((byte *)pcVar21 + -1);
                goto LAB_800070b4;
              }
              if (uVar7 == 0x25) {
                uVar6 = 0x25;
                do {
                } while ((DAT_8000750c[0x1f] & 2) == 0);
LAB_80007324:
                *DAT_8000750c = uVar6;
                goto LAB_800070b4;
              }
            }
            else {
              if (uVar7 == 0x58) {
LAB_800073f8:
                iVar8 = 0x10;
                break;
              }
              if (uVar7 == 99) {
                if (bVar18) {
                  do {
                  } while ((DAT_8000750c[0x1f] & 2) == 0);
                  *DAT_8000750c = (uint)pbVar15 & 0x7f;
                }
                puVar4 = DAT_80007510;
                if ((0 < (int)uVar6) && (iVar8 = uVar6 - 2, iVar8 != -1)) {
                  puVar11 = DAT_80007510 + -0x1f;
                  do {
                    do {
                    } while ((*puVar4 & 2) == 0);
                    *puVar11 = uVar9;
                    bVar19 = iVar8 != 0;
                    iVar8 = iVar8 + -1;
                  } while (bVar19);
                }
                if (bVar18) goto LAB_800070b4;
                uVar6 = (uint)pbVar15 & 0x7f;
                do {
                } while ((DAT_8000750c[0x1f] & 2) == 0);
                goto LAB_80007324;
              }
            }
          }
          else {
            if (uVar7 == 0x73) {
              if ((bVar18) && (uVar7 = (uint)*pbVar15, uVar7 != 0)) {
                pbVar14 = pbVar15;
                do {
                  do {
                  } while ((*puVar4 & 2) == 0);
                  puVar4[-0x1f] = uVar7;
                  pbVar14 = pbVar14 + 1;
                  uVar7 = (uint)*pbVar14;
                } while (uVar7 != 0);
              }
              uVar7 = FUN_800002cc(pbVar15);
              if (uVar7 < uVar6) {
                iVar8 = FUN_800002cc(pbVar15);
                puVar4 = DAT_80007510;
                iVar13 = (uVar6 - iVar8) + -1;
                if (uVar6 - iVar8 != 0) {
                  puVar11 = DAT_80007510 + -0x1f;
                  do {
                    do {
                    } while ((*puVar4 & 2) == 0);
                    *puVar11 = uVar9;
                    bVar19 = iVar13 != 0;
                    iVar13 = iVar13 + -1;
                  } while (bVar19);
                }
              }
              puVar4 = DAT_80007510;
              if ((!bVar18) && (uVar6 = (uint)*pbVar15, uVar6 != 0)) {
                puVar11 = DAT_80007510 + -0x1f;
                do {
                  do {
                  } while ((*puVar4 & 2) == 0);
                  *puVar11 = uVar6;
                  pbVar15 = pbVar15 + 1;
                  uVar6 = (uint)*pbVar15;
                } while (uVar6 != 0);
              }
              goto LAB_800070b4;
            }
            if (uVar7 < 0x74) {
              if (uVar7 == 0x69) goto LAB_800073f0;
              if (uVar7 != 0x6f) goto LAB_80007288;
              iVar8 = 8;
              break;
            }
            if (uVar7 == 0x75) {
              iVar8 = 10;
              break;
            }
            if (uVar7 == 0x78) goto LAB_800073f8;
          }
LAB_80007288:
          iVar8 = 3;
          break;
        }
        uVar6 = (uVar7 + uVar6 * 10) - 0x30;
LAB_80007118:
        pbVar14 = (byte *)pcVar21 + 1;
        uVar7 = (uint)(byte)*pcVar21;
        pcVar21 = (char *)pbVar14;
      } while (uVar7 != 0);
      if (bVar18) {
        uVar6 = -uVar6;
      }
    }
    if (uVar9 == 0) {
      uVar9 = 0x20;
    }
    bVar18 = (int)uVar6 < 0;
    uStack64 = 0;
    uStack60 = 0;
    if (bVar18) {
      uVar6 = -uVar6;
      uStack64 = 1;
    }
    uStack64 = (uint)bVar18;
    if (0x50 < uVar6) {
      uVar6 = 0;
    }
    bVar18 = iVar8 < 0;
    if (bVar18) {
      iVar8 = -iVar8;
    }
    bVar18 = bVar18 && (int)pbVar15 < 0;
    if (bVar18) {
      pbVar15 = (byte *)-(int)pbVar15;
      uStack60 = 1;
    }
    uStack60 = (uint)bVar18;
    iVar13 = 0;
LAB_80007180:
    do {
      iVar12 = iVar13;
      if (iVar8 == 0x10) {
        uVar7 = (uint)pbVar15 & 0xf;
        pbVar15 = (byte *)((uint)pbVar15 >> 4);
      }
      else {
        uVar20 = FUN_80000928(pbVar15,iVar8);
        pbVar15 = (byte *)uVar20;
        uVar7 = (uint)((ulonglong)uVar20 >> 0x20) & 0xffff;
      }
      puVar4 = DAT_80007510;
      if (uVar7 < 10) {
        cVar10 = '0';
      }
      else {
        cVar10 = '7';
      }
      abStack105[iVar12 + 1] = (char)uVar7 + cVar10;
      iVar13 = iVar12 + 1;
      if (pbVar15 == (byte *)0x0) goto LAB_80007400;
      if (iVar8 == 10) {
        if (iVar13 != 3 && iVar13 != 7) {
          if (iVar13 == 0xb) {
            bVar1 = 1;
LAB_800071f0:
            bVar2 = 0;
          }
          else {
            bVar1 = 0;
            if (iVar13 != 0xf) goto LAB_800071f0;
            bVar2 = 1;
          }
          if (!(bool)(bVar1 | bVar2)) goto LAB_80007180;
        }
        abStack105[iVar12 + 2] = 0x2c;
        iVar13 = iVar12 + 2;
      }
    } while( true );
  }
  pcVar21 = (char *)((byte *)pcVar21 + 1);
  do {
  } while ((DAT_8000750c[0x1f] & 2) == 0);
  *DAT_8000750c = (uint)bVar1;
  ppbVar16 = ppbVar3;
  goto LAB_800070b4;
LAB_80007400:
  if (uStack60 != 0) {
    abStack105[iVar12 + 2] = 0x2d;
    iVar13 = iVar12 + 2;
  }
  if (iVar13 < (int)uVar6) {
    iVar8 = uVar6 - iVar13;
    if ((uStack64 == 0) && (iVar12 = iVar8 + -1, iVar8 != 0)) {
      puVar11 = DAT_80007510 + -0x1f;
      do {
        do {
        } while ((*puVar4 & 2) == 0);
        *puVar11 = uVar9;
        bVar18 = iVar12 != 0;
        iVar12 = iVar12 + -1;
      } while (bVar18);
    }
    puVar4 = DAT_80007510;
    if (0 < iVar13) {
      puVar11 = DAT_80007510 + -0x1f;
      do {
        iVar12 = iVar13 + -1;
        do {
        } while ((*puVar4 & 2) == 0);
        *puVar11 = (uint)abStack105[iVar13];
        iVar13 = iVar12;
      } while (0 < iVar12);
    }
    puVar4 = DAT_80007510;
    if ((uStack64 != 0) && (iVar13 = iVar8 + -1, iVar8 != 0)) {
      puVar11 = DAT_80007510 + -0x1f;
      do {
        do {
        } while ((*puVar4 & 2) == 0);
        *puVar11 = uVar9;
        bVar18 = iVar13 != 0;
        iVar13 = iVar13 + -1;
      } while (bVar18);
    }
  }
  else {
    if (0 < iVar13) {
      puVar11 = DAT_80007510 + -0x1f;
      do {
        iVar8 = iVar13 + -1;
        do {
        } while ((*puVar4 & 2) == 0);
        *puVar11 = (uint)abStack105[iVar13];
        iVar13 = iVar8;
      } while (0 < iVar8);
    }
  }
LAB_800070b4:
  bVar1 = *pcVar21;
  ppbVar3 = ppbVar16;
  puVar4 = DAT_80007510;
  goto joined_r0x8000707c;
}



void FUN_800018b4(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  
  uVar2 = *DAT_8000193c;
  uVar3 = DAT_8000193c[1];
  *DAT_8000193c = 0;
  iVar4 = 1;
  do {
    uVar1 = FUN_800002a4(uVar2,uVar3,iVar4);
    if ((~uVar1 & 1) == 0) {
                    // WARNING: Could not recover jumptable at 0x80001938. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(PTR_DAT_80001940 + iVar4 * 4))();
      return;
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x40);
  return;
}



undefined4 FUN_80001944(undefined4 param_1,uint param_2,undefined4 param_3,int param_4)

{
  uint *puVar1;
  
  if (*PTR_DAT_800019fc == '\0') {
    *PTR_DAT_800019fc = 1;
  }
  switch(param_1) {
  case 0:
    param_1 = *(undefined4 *)(PTR_DAT_80001a00 + param_2 * 4);
    *(undefined4 *)(PTR_DAT_80001a00 + param_2 * 4) = param_3;
    break;
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
    param_1 = *(undefined4 *)(PTR_DAT_80001a04 + param_2 * 4);
    *(undefined4 *)(PTR_DAT_80001a04 + param_2 * 4) = param_3;
  }
  puVar1 = (uint *)(DAT_80001a08 + (param_2 * 0x89 >> 0xb) * 4);
  *puVar1 = *puVar1 | param_4 <<
                      (((uint)((ulonglong)param_2 * (ulonglong)DAT_80001a0c >> 0x23) * -0xf +
                       param_2) * 2 & 0xff);
  puVar1 = (uint *)(DAT_80001a10 + (param_2 >> 5) * 4);
  *puVar1 = *puVar1 | 1 << (param_2 & 0x1f);
  return param_1;
}



void FUN_80001a34(int param_1,int param_2,undefined4 param_3,int param_4,undefined4 param_5)

{
  undefined *puVar1;
  uint uVar2;
  uint uVar3;
  
  puVar1 = PTR_DAT_80001a9c;
  uVar2 = param_4 - 1;
  param_2 = param_2 * 800;
  if (param_4 == 0) {
    return;
  }
  do {
    uVar3 = uVar2 & 0xffff;
    FUN_80000310(*(int *)puVar1 + param_2 * 2 + param_1 * 2,param_5,param_3);
    uVar2 = uVar3 - 1;
    param_2 = param_2 + 800;
  } while (uVar3 != 0);
  return;
}



undefined4 FUN_80001b38(void)

{
  return *(undefined4 *)PTR_DAT_80001b44;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined4 FUN_80001b48(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined *puVar3;
  uint *puVar4;
  char *pcVar5;
  int iVar6;
  uint *puVar7;
  uint *puVar8;
  uint *puVar9;
  undefined4 unaff_r9;
  undefined2 local_40 [2];
  undefined4 local_3c;
  undefined4 local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  
  uVar2 = DAT_800020cc;
  puVar7 = DAT_800020c4;
  puVar8 = DAT_800020c4 + 0x400;
  puVar9 = DAT_800020c4;
  if ((param_1 != 0) && (puVar9 = puVar8, param_1 != 1)) {
    puVar9 = (uint *)0x0;
  }
  if (param_1 == 0) {
    unaff_r9 = DAT_800020c8;
  }
  iVar6 = 0;
  if (param_1 == 0) {
    do {
      FUN_8000160c(unaff_r9,iVar6,2,0);
      iVar6 = iVar6 + 1;
    } while (iVar6 < 6);
  }
  else {
    if (param_1 == 1) {
      do {
        FUN_8000160c(uVar2,iVar6,3,0);
        iVar6 = iVar6 + 1;
      } while (iVar6 < 3);
    }
  }
  puVar4 = DAT_800020d0;
  uVar1 = 1 << (param_1 + 8U & 0xff);
  *DAT_800020d0 = *DAT_800020d0 | uVar1;
  puVar4[0x98] = uVar1 | puVar4[0x98];
  FUN_80003a2c(1);
  FUN_80005a08(param_1,DAT_800020d4);
  puVar4 = puVar7;
  if ((param_1 != 0) && (puVar4 = puVar8, param_1 != 1)) {
    puVar4 = (uint *)0x0;
  }
  puVar4[0x1e] = puVar4[0x1e] | 2;
  puVar4[0x1e] = puVar4[0x1e] & 0xfffffffd;
  uVar2 = DAT_800020d8;
  FUN_80001118(DAT_800020d8);
  puVar4[0x1e] = puVar4[0x1e] | 2;
  FUN_80001118(uVar2);
  puVar4 = puVar7;
  if ((param_1 != 0) && (puVar4 = puVar8, param_1 != 1)) {
    puVar4 = (uint *)0x0;
  }
  *puVar4 = *puVar4 | 7;
  FUN_80001118(uVar2);
  puVar4 = puVar7;
  if ((param_1 != 0) && (puVar4 = puVar8, param_1 != 1)) {
    puVar4 = (uint *)0x0;
  }
  *puVar4 = *puVar4 & 0xfffffeff;
  puVar4 = puVar7;
  if ((param_1 != 0) && (puVar4 = puVar8, param_1 != 1)) {
    puVar4 = (uint *)0x0;
  }
  puVar4[1] = puVar4[1] | 0x20000;
  puVar4 = puVar7;
  if ((param_1 != 0) && (puVar4 = puVar8, param_1 != 1)) {
    puVar4 = (uint *)0x0;
  }
  puVar4[3] = 0;
  puVar9[2] = 0xffffffff;
  if ((param_1 != 0) && (puVar7 = puVar8, param_1 != 1)) {
    puVar7 = (uint *)0x0;
  }
  puVar7[1] = puVar7[1] | 0x10000;
  FUN_80005eec();
  FUN_80003a2c(0x32);
  local_40[0] = 0;
  local_38 = 0;
  local_3c = 0;
  FUN_800067dc(param_1,local_40);
  FUN_80003a2c(500);
  local_3c = 5;
  local_40[0] = 8;
  local_38 = DAT_800020dc;
  iVar6 = FUN_800067dc(param_1,local_40,0);
  puVar3 = PTR_DAT_800020e0;
  if (iVar6 == 0) {
    FUN_8000705c(s_SD2_0____80002100);
    local_40[0] = 0x37;
    local_38 = 0;
    local_3c = 5;
    FUN_800067dc(param_1,local_40);
    uVar2 = _DAT_8000210c;
    local_40[0] = 0x29;
    local_3c = 7;
    local_38 = _DAT_8000210c;
    FUN_800067dc(param_1,local_40,0);
    while ((local_28 & 0x80000000) == 0) {
      local_40[0] = 0x37;
      local_38 = 0;
      local_3c = 5;
      FUN_800067dc(param_1,local_40);
      local_40[0] = 0x29;
      local_3c = 7;
      local_38 = uVar2;
      FUN_800067dc(param_1,local_40,0);
    }
    if ((local_28 & 0x40000000) != 0) {
      pcVar5 = s__TYPE_SD_HIGH____8000210f + 1;
      *(undefined4 *)puVar3 = 1;
      goto LAB_80001ed0;
    }
  }
  else {
    FUN_8000705c(s_SD1_1____800020e4);
    local_40[0] = 0;
    local_38 = 0;
    local_3c = 0;
    FUN_800067dc(param_1,local_40);
    FUN_80003a2c(500);
    local_40[0] = 0x37;
    local_38 = 0;
    local_3c = 5;
    iVar6 = FUN_800067dc(param_1,local_40);
    uVar2 = DAT_8000214c;
    if (iVar6 == 0x98) {
      local_40[0] = 0;
      local_38 = 0;
      local_3c = 0;
      FUN_800067dc(param_1,local_40);
      FUN_80003a2c(1);
      uVar2 = DAT_80002128;
      local_40[0] = 1;
      local_3c = 5;
      local_38 = DAT_80002128;
      iVar6 = FUN_800067dc(param_1,local_40,0);
      if (iVar6 == 0x98) {
        *(undefined4 *)puVar3 = 0;
        FUN_8000705c(s_ERR_DEVICE____8000213c);
        return 0xffffffff;
      }
      while ((local_28 & 0x80000000) == 0) {
        local_3c = 5;
        local_40[0] = 1;
        local_38 = uVar2;
        FUN_800067dc(param_1,local_40,0);
      }
      *(undefined4 *)puVar3 = 3;
      pcVar5 = s_TYPE_MMC____8000212c;
      goto LAB_80001ed0;
    }
    if (iVar6 != 0) {
      *(undefined4 *)puVar3 = 0;
      FUN_8000705c(s_Init_Error____800020f0);
      return 0xffffffff;
    }
    local_3c = 7;
    local_40[0] = 0x29;
    local_38 = DAT_8000214c;
    FUN_800067dc(param_1,local_40,0);
    while ((local_28 & 0x80000000) == 0) {
      local_40[0] = 0x37;
      local_38 = 0;
      local_3c = 5;
      FUN_800067dc(param_1,local_40);
      local_40[0] = 0x29;
      local_3c = 7;
      local_38 = uVar2;
      FUN_800067dc(param_1,local_40,0);
    }
  }
  pcVar5 = s_TYPE_SD_LOW____80002150;
  *(undefined4 *)puVar3 = 2;
LAB_80001ed0:
  FUN_8000705c(pcVar5);
  if (*(int *)puVar3 != 0) {
    local_40[0] = 2;
    local_3c = 7;
    local_38 = 0;
    FUN_800067dc(param_1,local_40);
    puVar7 = DAT_80002124;
    *DAT_80002124 = local_28;
    puVar7[1] = local_2c;
    puVar7[2] = local_30;
    puVar7[3] = local_34;
    if (*(int *)puVar3 == 3) {
      local_40[0] = 3;
      local_3c = 7;
      local_38 = 0x10000;
      iVar6 = FUN_800067dc(param_1,local_40,0);
      if (iVar6 != 0) {
        return 0xffffffff;
      }
      local_28 = 0x10000;
    }
    else {
      local_40[0] = 3;
      local_3c = 7;
      local_38 = 0;
      iVar6 = FUN_800067dc(param_1,local_40,0);
      if (iVar6 != 0) {
        return 0xffffffff;
      }
    }
    *(uint *)(puVar3 + 4) = local_28;
  }
  FUN_80001698(param_1,local_40,DAT_800021bc);
  FUN_80002e48(param_1,local_40,1);
  return 0;
}



int FUN_800021c0(undefined4 param_1,int param_2,int param_3,uint param_4)

{
  undefined *puVar1;
  int iVar2;
  uint uVar3;
  undefined2 uVar4;
  undefined2 local_50 [2];
  undefined4 local_4c;
  int local_48;
  uint uStack48;
  undefined4 uStack44;
  int iStack40;
  undefined4 uStack36;
  
  puVar1 = PTR_DAT_8000232c;
  uVar3 = (param_2 + param_3) - 1;
  if (*(uint *)(PTR_DAT_8000232c + 0xc) < uVar3) {
    FUN_8000705c(PTR_s_ERROR__Fail_to_access_invalid_se_80002330,uVar3);
    FUN_8000705c(PTR_s__The_max_valid_sector_number_for_80002334,*(undefined4 *)(puVar1 + 0xc));
    return DAT_80002338;
  }
  if (param_4 == 0) {
    FUN_8000705c(s_ERROR__fmiSD_Read_in____uBufcnt_c_80002364);
    return DAT_80002394;
  }
  if ((param_4 & 3) != 0) {
    FUN_8000705c(s_SD_Read_Addr_Align_Err__08x______8000233c,param_4);
    return DAT_80002360;
  }
  local_48 = *(int *)(PTR_DAT_8000232c + 4);
  if (*(int *)PTR_DAT_8000232c != 1) {
    param_2 = param_2 << 9;
  }
  local_50[0] = 7;
  if (param_3 == 1) {
    uVar4 = 0x11;
  }
  else {
    uVar4 = 0x12;
  }
  local_4c = 0xd;
  iVar2 = FUN_800067dc(param_1,local_50,0);
  if (iVar2 == 0) {
    uStack36 = 0x200;
    uStack44 = 1;
    local_4c = 0xd;
    local_50[0] = uVar4;
    local_48 = param_2;
    uStack48 = param_4;
    iStack40 = param_3;
    iVar2 = FUN_800067dc(param_1,local_50,&uStack48);
    if (iVar2 == 0) {
      local_50[0] = 7;
      local_48 = 0;
      local_4c = 0;
      FUN_800067dc(param_1,local_50);
      return 0;
    }
    return iVar2;
  }
  return iVar2;
}



int FUN_80002398(undefined4 param_1,int param_2,int param_3,uint param_4)

{
  undefined *puVar1;
  int iVar2;
  uint uVar3;
  undefined2 uVar4;
  undefined2 local_50 [2];
  undefined4 local_4c;
  int local_48;
  uint uStack48;
  undefined4 uStack44;
  int iStack40;
  undefined4 uStack36;
  
  puVar1 = PTR_DAT_80002500;
  uVar3 = (param_2 + param_3) - 1;
  if (*(uint *)(PTR_DAT_80002500 + 0xc) < uVar3) {
    FUN_8000705c(PTR_s_ERROR__Fail_to_access_invalid_se_80002504,uVar3);
    FUN_8000705c(PTR_s__The_max_valid_sector_number_for_80002508,*(undefined4 *)(puVar1 + 0xc));
    return DAT_8000250c;
  }
  if (param_4 == 0) {
    FUN_8000705c(s_ERROR__fmiSD_Read_in____uBufcnt_c_8000252c);
    return DAT_8000255c;
  }
  if ((param_4 & 3) != 0) {
    FUN_8000705c(s_Addr_Align_Err_____80002510);
    return DAT_80002528;
  }
  local_48 = *(int *)(PTR_DAT_80002500 + 4);
  if (*(int *)PTR_DAT_80002500 != 1) {
    param_2 = param_2 << 9;
  }
  local_50[0] = 7;
  if (param_3 == 1) {
    uVar4 = 0x18;
  }
  else {
    uVar4 = 0x19;
  }
  local_4c = 0xd;
  iVar2 = FUN_800067dc(param_1,local_50,0);
  if (iVar2 == 0) {
    uStack36 = 0x200;
    uStack44 = 2;
    local_4c = 0xd;
    local_50[0] = uVar4;
    local_48 = param_2;
    uStack48 = param_4;
    iStack40 = param_3;
    iVar2 = FUN_800067dc(param_1,local_50,&uStack48);
    if (iVar2 == 0) {
      local_50[0] = 7;
      local_48 = 0;
      local_4c = 0;
      FUN_800067dc(param_1,local_50);
      return 0;
    }
    return iVar2;
  }
  return iVar2;
}



uint FUN_80002560(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  bool bVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined uVar6;
  byte bVar7;
  byte bVar8;
  uint uVar9;
  
  puVar4 = PTR_DAT_80002778;
  puVar3 = PTR_DAT_80002774;
  bVar8 = 0;
  do {
    FUN_80002a80(param_1,param_2);
    FUN_80001118(500);
    bVar7 = 0;
    do {
      FUN_80001118(100);
      puVar5 = PTR_DAT_80002778;
      FUN_80001510(100);
      FUN_80001510(100);
      FUN_80001118(0x14);
      FUN_80001510(0x66);
      do {
        FUN_80001510(0x67);
        uVar9 = FUN_80001368();
      } while ((uVar9 & 1) == 0);
      FUN_80001510(0x68);
      uVar6 = FUN_80001368();
      *puVar5 = uVar6;
      FUN_80001510(0x69);
      uVar6 = FUN_80001368();
      puVar5[1] = uVar6;
      FUN_80001510(0x6a);
      uVar6 = FUN_80001368();
      puVar5[2] = uVar6;
      FUN_80001510(0x6b);
      uVar6 = FUN_80001368();
      puVar5[3] = uVar6;
      FUN_80001510(0x6c);
      uVar6 = FUN_80001368();
      puVar5[4] = uVar6;
      FUN_80001510(0x6d);
      uVar6 = FUN_80001368();
      puVar5[5] = uVar6;
      FUN_80001510(0x6e);
      uVar6 = FUN_80001368();
      puVar5[6] = uVar6;
      FUN_8000277c();
      *puVar3 = *puVar4;
      if (puVar4[1] == 'U') {
        uVar9 = (uint)(byte)puVar4[6];
      }
      else {
        if (puVar4[1] == 'Z') {
          uVar9 = (uint)CONCAT11(puVar4[5],puVar4[6]);
        }
        else {
          if (puVar4[1] == -0x5b) {
            uVar9 = (uint)CONCAT21(CONCAT11(puVar4[4],puVar4[5]),puVar4[6]);
          }
          else {
            if (puVar4[1] == -0x56) {
              uVar9 = CONCAT31(CONCAT21(CONCAT11(puVar4[3],puVar4[4]),puVar4[5]),puVar4[6]);
            }
            else {
              uVar9 = 0;
            }
          }
        }
      }
      cVar1 = puVar4[1];
      bVar2 = true;
      if ((cVar1 != 'U' && cVar1 != 'Z') && (cVar1 != -0x5b && cVar1 != -0x56)) {
        bVar2 = false;
      }
      if (((undefined)(*puVar4 + puVar4[1] + puVar4[3] + puVar4[4] + puVar4[5] + puVar4[6]) ==
           puVar4[2]) && (bVar2)) {
        return uVar9;
      }
      bVar7 = bVar7 + 1;
    } while (bVar7 < 0x32);
    FUN_80001118(10);
    bVar8 = bVar8 + 1;
    if (5 < bVar8) {
      return uVar9;
    }
  } while( true );
}



void FUN_8000277c(void)

{
  undefined *puVar1;
  uint uVar2;
  byte bVar3;
  
  puVar1 = PTR_DAT_800028e0;
  uVar2 = 1;
  bVar3 = ~*PTR_DAT_800028e0;
  *PTR_DAT_800028e0 = ~*PTR_DAT_800028e0;
  do {
    if ((bVar3 & 0x80) != 0) {
      puVar1[uVar2] = ~puVar1[uVar2] & 0x80 | puVar1[uVar2] & 0x7f;
    }
    if ((bVar3 & 0x40) != 0) {
      puVar1[uVar2] = ~puVar1[uVar2] & 0x40 | puVar1[uVar2] & 0xbf;
    }
    if ((bVar3 & 0x20) != 0) {
      puVar1[uVar2] = ~puVar1[uVar2] & 0x20 | puVar1[uVar2] & 0xdf;
    }
    if ((bVar3 & 0x10) != 0) {
      puVar1[uVar2] = ~puVar1[uVar2] & 0x10 | puVar1[uVar2] & 0xef;
    }
    if ((bVar3 & 8) != 0) {
      puVar1[uVar2] = ~puVar1[uVar2] & 8 | puVar1[uVar2] & 0xf7;
    }
    if ((bVar3 & 4) != 0) {
      puVar1[uVar2] = ~puVar1[uVar2] & 4 | puVar1[uVar2] & 0xfb;
    }
    if ((bVar3 & 2) != 0) {
      puVar1[uVar2] = ~puVar1[uVar2] & 2 | puVar1[uVar2] & 0xfd;
    }
    if ((bVar3 & 1) != 0) {
      puVar1[uVar2] = ~puVar1[uVar2] & 1 | puVar1[uVar2] & 0xfe;
    }
    uVar2 = uVar2 + 1 & 0xff;
  } while (uVar2 < 7);
  return;
}



void FUN_800028e4(void)

{
  byte bVar1;
  undefined *puVar2;
  byte bVar3;
  uint uVar4;
  
  puVar2 = PTR_DAT_80002a7c;
  bVar1 = *PTR_DAT_80002a7c;
  uVar4 = 1;
  do {
    if ((bVar1 & 0x80) != 0) {
      puVar2[uVar4] = ~puVar2[uVar4] & 0x80 | puVar2[uVar4] & 0x7f;
    }
    if ((bVar1 & 0x40) != 0) {
      puVar2[uVar4] = ~puVar2[uVar4] & 0x40 | puVar2[uVar4] & 0xbf;
    }
    if ((bVar1 & 0x20) != 0) {
      puVar2[uVar4] = ~puVar2[uVar4] & 0x20 | puVar2[uVar4] & 0xdf;
    }
    if ((bVar1 & 0x10) != 0) {
      puVar2[uVar4] = ~puVar2[uVar4] & 0x10 | puVar2[uVar4] & 0xef;
    }
    if ((bVar1 & 8) != 0) {
      puVar2[uVar4] = ~puVar2[uVar4] & 8 | puVar2[uVar4] & 0xf7;
    }
    if ((bVar1 & 4) != 0) {
      puVar2[uVar4] = ~puVar2[uVar4] & 4 | puVar2[uVar4] & 0xfb;
    }
    if ((bVar1 & 2) != 0) {
      puVar2[uVar4] = ~puVar2[uVar4] & 2 | puVar2[uVar4] & 0xfd;
    }
    if ((bVar1 & 1) != 0) {
      puVar2[uVar4] = ~puVar2[uVar4] & 1 | puVar2[uVar4] & 0xfe;
    }
    uVar4 = uVar4 + 1 & 0xff;
  } while (uVar4 < 7);
  bVar3 = 0;
  if ((bVar1 & 4) != 0) {
    bVar3 = 0x80;
  }
  if ((bVar1 & 0x10) != 0) {
    bVar3 = bVar3 | 0x40;
  }
  if ((bVar1 & 1) != 0) {
    bVar3 = bVar3 | 0x20;
  }
  if ((bVar1 & 0x40) != 0) {
    bVar3 = bVar3 | 0x10;
  }
  if ((bVar1 & 2) != 0) {
    bVar3 = bVar3 | 8;
  }
  if ((bVar1 & 0x80) != 0) {
    bVar3 = bVar3 | 4;
  }
  if ((bVar1 & 8) != 0) {
    bVar3 = bVar3 | 2;
  }
  if ((bVar1 & 0x20) != 0) {
    bVar3 = bVar3 | 1;
  }
  *puVar2 = bVar3;
  return;
}



void FUN_80002a80(int param_1,uint param_2)

{
  undefined uVar1;
  undefined uVar2;
  undefined uVar3;
  undefined *puVar4;
  byte bVar5;
  uint uVar6;
  
  puVar4 = PTR_DAT_80002c34;
  *PTR_DAT_80002c34 = *PTR_DAT_80002c38;
  puVar4[1] = (char)(param_1 << 2);
  uVar3 = (undefined)param_2;
  bVar5 = 0;
  uVar1 = (undefined)((param_2 << 8) >> 0x18);
  uVar2 = (undefined)((param_2 << 0x10) >> 0x18);
  if (param_2 < 0x1000000) {
    if (param_2 < 0x10000) {
      if (param_2 < 0x100) {
        puVar4[3] = 0x69;
        puVar4[4] = 0x96;
        puVar4[5] = 0x99;
        puVar4[6] = uVar3;
      }
      else {
        puVar4[3] = 0x69;
        bVar5 = 1;
        puVar4[4] = 0x96;
        puVar4[5] = uVar2;
        puVar4[6] = uVar3;
      }
    }
    else {
      bVar5 = 2;
      puVar4[3] = 0x69;
      puVar4[4] = uVar1;
      puVar4[5] = uVar2;
      puVar4[6] = uVar3;
    }
  }
  else {
    bVar5 = 3;
    puVar4[3] = (char)(param_2 >> 0x18);
    puVar4[4] = uVar1;
    puVar4[5] = uVar2;
    puVar4[6] = uVar3;
  }
  puVar4[1] = bVar5 | puVar4[1];
  FUN_800028e4();
  puVar4[2] = puVar4[6] + puVar4[3] + puVar4[4] + puVar4[1] + *puVar4 + puVar4[5];
  FUN_80001510(0x65);
  FUN_80001510(0x65);
  uVar1 = *puVar4;
  FUN_80001510(0x68);
  FUN_80001414(uVar1);
  uVar1 = puVar4[1];
  FUN_80001510(0x69);
  FUN_80001414(uVar1);
  uVar1 = puVar4[2];
  FUN_80001510(0x6a);
  FUN_80001414(uVar1);
  uVar1 = puVar4[3];
  FUN_80001510(0x6b);
  FUN_80001414(uVar1);
  uVar1 = puVar4[4];
  FUN_80001510(0x6c);
  FUN_80001414(uVar1);
  uVar1 = puVar4[5];
  FUN_80001510(0x6d);
  FUN_80001414(uVar1);
  uVar1 = puVar4[6];
  FUN_80001510(0x6e);
  FUN_80001414(uVar1);
  FUN_80001510(0x66);
  do {
    FUN_80001510(0x67);
    uVar6 = FUN_80001368();
  } while ((uVar6 & 1) == 0);
  return;
}



undefined4 FUN_80002c3c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint *puVar2;
  undefined4 uVar3;
  undefined4 local_10;
  
  local_10 = CONCAT31((int3)((uint)param_4 >> 8),6);
  uVar3 = 0;
  puVar2 = (uint *)(DAT_80002c94 + param_1 * 0x1000 + 8);
  *puVar2 = *puVar2 & 0xffffff4f;
  iVar1 = FUN_80006f54(param_1,&local_10,0,1);
  if (iVar1 != 1) {
    uVar3 = 0xffffffff;
  }
  *puVar2 = *puVar2 & 0xffffff4f | 0x80;
  return uVar3;
}



// WARNING: Could not reconcile some variable overlaps

undefined4 FUN_80002c98(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  uint *puVar2;
  undefined4 uVar3;
  undefined4 local_20;
  
  local_20 = CONCAT13((char)param_1,
                      CONCAT12((char)((uint)param_1 >> 8),CONCAT11((char)((uint)param_1 >> 0x10),3))
                     );
  uVar3 = 0;
  puVar2 = (uint *)(DAT_80006f50 + 8);
  *puVar2 = *puVar2 & 0xffffff4f;
  iVar1 = FUN_80006f54(0,&local_20,0,4);
  if ((iVar1 != 4) || (iVar1 = FUN_80006f54(0,0,param_2,param_3), iVar1 != param_3)) {
    uVar3 = 0xffffffff;
  }
  *puVar2 = *puVar2 & 0xffffff4f | 0x80;
  return uVar3;
}



void FUN_80002cb4(int param_1)

{
  int iVar1;
  uint *puVar2;
  undefined local_20 [4];
  byte local_1c [4];
  
  puVar2 = (uint *)(DAT_80002d44 + param_1 * 0x1000 + 8);
  do {
    local_20[0] = 5;
    *puVar2 = *puVar2 & 0xffffff4f;
    iVar1 = FUN_80006f54(param_1,local_20,0,1);
    if (iVar1 == 1) {
      FUN_80006f54(param_1,0,local_1c,1);
    }
    *puVar2 = *puVar2 & 0xffffff4f | 0x80;
  } while ((local_1c[0] & 1) != 0);
  return;
}



// WARNING: Restarted to delay deadcode elimination for space: stack

void FUN_80002d48(uint param_1,undefined *param_2,uint param_3)

{
  undefined uVar1;
  undefined uVar2;
  int iVar3;
  uint uVar4;
  undefined *puVar5;
  int iVar6;
  int extraout_r1;
  undefined *puVar7;
  undefined *puVar8;
  uint *puVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  undefined8 uVar15;
  undefined local_48;
  undefined local_47;
  undefined local_46;
  undefined local_45;
  uint local_44;
  uint *local_40;
  int local_3c;
  int local_34;
  undefined *local_30;
  uint local_2c;
  uint local_28;
  
  local_28 = param_3;
  local_2c = param_1;
  local_30 = param_2;
  local_34 = 0;
  local_44 = param_1 >> 0xc;
  param_1 = param_1 & 0xfff;
  uVar10 = 0x1000 - param_1;
  if (param_3 <= 0x1000 - param_1) {
    uVar10 = param_3;
  }
  local_40 = (uint *)(DAT_800067d4 + 8);
  do {
    iVar3 = local_34;
    puVar9 = local_40;
    local_3c = DAT_800067d8;
    iVar12 = local_44 << 0xc;
    local_48 = 3;
    uVar1 = (undefined)((local_44 << 0x14) >> 0x18);
    uVar2 = (undefined)((local_44 << 0x1c) >> 0x18);
    local_45 = 0;
    *local_40 = *local_40 & 0xffffff4f;
    local_47 = uVar1;
    local_46 = uVar2;
    uVar15 = FUN_80006f54(local_34,&local_48,0,4);
    iVar14 = (int)((ulonglong)uVar15 >> 0x20);
    if ((int)uVar15 == 4) {
      FUN_80006f54(iVar3,0,local_3c,0x1000);
      iVar14 = extraout_r1;
    }
    iVar3 = local_34;
    *puVar9 = *puVar9 & 0xffffff4f | 0x80;
    if (uVar10 != 0) {
      iVar14 = DAT_800067d8;
    }
    uVar4 = 0;
    if (uVar10 != 0) {
      do {
        if (*(char *)(iVar14 + param_1 + uVar4) != -1) break;
        uVar4 = uVar4 + 1 & 0xfffeffff;
      } while (uVar4 < uVar10);
    }
    if (uVar4 < uVar10) {
      local_48 = 0x20;
      local_45 = 0;
      local_47 = uVar1;
      local_46 = uVar2;
      FUN_80002c3c(local_34);
      FUN_80002cb4(iVar3);
      puVar9 = local_40;
      iVar14 = DAT_800067d4;
      *local_40 = *local_40 & 0xffffff4f;
      FUN_80006f54(iVar3,&local_48,0,4);
      *puVar9 = *puVar9 & 0xffffff4f | 0x80;
      FUN_80002cb4(iVar3);
      iVar3 = local_34;
      if (uVar10 != 0) {
        puVar7 = (undefined *)(DAT_800067d8 + param_1);
        puVar5 = local_30 + -1;
        puVar8 = puVar7 + -1;
        if ((uVar10 & 1) != 0) {
          *puVar7 = *local_30;
          puVar5 = local_30;
          puVar8 = puVar7;
        }
        uVar4 = uVar10 >> 1;
        while (uVar4 != 0) {
          uVar4 = uVar4 - 1;
          puVar8[1] = puVar5[1];
          puVar5 = puVar5 + 2;
          puVar8 = puVar8 + 2;
          *puVar8 = *puVar5;
        }
      }
      puVar9 = (uint *)(iVar14 + local_34 * 0x1000 + 8);
      uVar4 = 0x1000;
      uVar11 = 0x100;
      iVar14 = DAT_800067d8;
      while( true ) {
        local_48 = 2;
        local_47 = (undefined)((uint)iVar12 >> 0x10);
        local_46 = (undefined)((uint)iVar12 >> 8);
        local_45 = 0;
        FUN_80002c3c(iVar3);
        FUN_80002cb4(iVar3);
        *puVar9 = *puVar9 & 0xffffff4f;
        iVar6 = FUN_80006f54(iVar3,&local_48,0,4);
        if (iVar6 == 4) {
          FUN_80006f54(iVar3,iVar14,0,uVar11);
        }
        *puVar9 = *puVar9 & 0xffffff4f | 0x80;
        FUN_80002cb4(iVar3);
        if (uVar4 == uVar11) break;
        uVar4 = uVar4 - uVar11 & 0xffff;
        iVar14 = iVar14 + uVar11;
        iVar12 = iVar12 + uVar11;
        uVar11 = uVar4;
        if (0x100 < uVar4) {
          uVar11 = 0x100;
        }
      }
    }
    else {
      uVar4 = 0x100 - (local_2c & 0xff);
      if (uVar10 <= uVar4) {
        uVar4 = uVar10;
      }
      puVar9 = (uint *)(DAT_800067d4 + local_34 * 0x1000 + 8);
      uVar13 = local_2c;
      uVar11 = uVar10;
      puVar5 = local_30;
      while( true ) {
        local_48 = 2;
        local_47 = (undefined)(uVar13 >> 0x10);
        local_46 = (undefined)(uVar13 >> 8);
        local_45 = (undefined)uVar13;
        FUN_80002c3c(iVar3);
        FUN_80002cb4(iVar3);
        *puVar9 = *puVar9 & 0xffffff4f;
        iVar12 = FUN_80006f54(iVar3,&local_48,0,4);
        if (iVar12 == 4) {
          FUN_80006f54(iVar3,puVar5,0,uVar4);
        }
        *puVar9 = *puVar9 & 0xffffff4f | 0x80;
        FUN_80002cb4(iVar3);
        if (uVar11 == uVar4) break;
        uVar11 = uVar11 - uVar4 & 0xffff;
        puVar5 = puVar5 + uVar4;
        uVar13 = uVar13 + uVar4;
        uVar4 = uVar11;
        if (0x100 < uVar11) {
          uVar4 = 0x100;
        }
      }
    }
    if (local_28 == uVar10) {
      return;
    }
    param_1 = 0;
    local_44 = local_44 + 1;
    local_28 = local_28 - uVar10 & 0xffff;
    local_30 = local_30 + uVar10;
    local_2c = local_2c + uVar10;
    uVar10 = local_28;
    if (0x1000 < local_28) {
      uVar10 = 0x1000;
    }
  } while( true );
}



// WARNING (jumptable): Heritage AFTER dead removal. Example location: s0xfffffffc : 0x80002e18
// WARNING: Could not reconcile some variable overlaps
// WARNING: Restarted to delay deadcode elimination for space: stack

void FUN_80002d58(int param_1,int param_2,uint param_3,uint param_4)

{
  int iVar1;
  uint *puVar2;
  uint uVar3;
  code *in_lr;
  uint local_28;
  code *UNRECOVERED_JUMPTABLE;
  
  local_28 = param_4;
  uVar3 = 0x100 - (param_3 & 0xff);
  if (param_4 <= uVar3) {
    uVar3 = param_4;
  }
  puVar2 = (uint *)(DAT_80002e40 + param_1 * 0x1000 + 8);
  UNRECOVERED_JUMPTABLE = in_lr;
  while( true ) {
                    // WARNING: Ignoring partial resolution of indirect
    local_28._0_1_ = 2;
    FUN_80002c3c(param_1);
    FUN_80002cb4(param_1);
    *puVar2 = *puVar2 & 0xffffff4f;
    iVar1 = FUN_80006f54(param_1,&local_28,0,4);
    if (iVar1 == 4) {
      FUN_80006f54(param_1,param_2,0,uVar3);
    }
    *puVar2 = *puVar2 & 0xffffff4f | 0x80;
    FUN_80002cb4(param_1);
    if (param_4 == uVar3) break;
    param_4 = param_4 - uVar3 & 0xffff;
    param_2 = param_2 + uVar3;
    uVar3 = param_4;
    if (0x100 < param_4) {
      uVar3 = 0x100;
    }
  }
                    // WARNING: Could not recover jumptable at 0x80002e18. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE)();
  return;
}



int FUN_80002e48(int param_1,undefined2 *param_2,int param_3)

{
  undefined *puVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  byte *pbStack56;
  undefined4 uStack52;
  undefined4 uStack48;
  undefined4 uStack44;
  
  FUN_8000705c(s_SelectCard____80003174);
  puVar1 = PTR_DAT_80003184;
  uVar6 = *(undefined4 *)(PTR_DAT_80003184 + 4);
  *param_2 = 7;
  *(undefined4 *)(param_2 + 2) = 5;
  *(undefined4 *)(param_2 + 4) = uVar6;
  iVar3 = FUN_800067dc(param_1,param_2,0);
  iVar5 = DAT_8000318c;
  uVar6 = DAT_80003188;
  if (iVar3 != 0) {
    return iVar3;
  }
  iVar3 = DAT_8000318c + 0x1000;
  if (*(int *)puVar1 == 1) {
    FUN_8000705c(s_CARD_TYPE_SD_HIGH_80003190);
    uVar7 = *(undefined4 *)(puVar1 + 4);
    *param_2 = 0x37;
    *(undefined4 *)(param_2 + 2) = 5;
    *(undefined4 *)(param_2 + 4) = uVar7;
    iVar4 = FUN_800067dc(param_1,param_2,0);
    pbVar2 = DAT_800031a8;
    if (iVar4 != 0) {
      return iVar4;
    }
    uStack48 = 1;
    uStack44 = 8;
    uStack52 = 1;
    pbStack56 = DAT_800031a8;
    *param_2 = 0x33;
    *(undefined4 *)(param_2 + 2) = 5;
    *(undefined4 *)(param_2 + 4) = 0;
    iVar4 = FUN_800067dc(param_1,param_2,&pbStack56);
    if (iVar4 != 0) {
      return iVar4;
    }
    if (((*pbVar2 & 0xf) == 2) && (iVar4 = FUN_800009f8(param_1,param_2), iVar4 == 0)) {
      FUN_8000705c(s_Set_Clock___d_HZ_800031ac,uVar6);
      FUN_800058b4(param_1,uVar6);
    }
    if (param_3 != 1) goto LAB_80003110;
    FUN_8000705c(s_Card_width_4bit_800031c0);
    uVar6 = *(undefined4 *)(puVar1 + 4);
    *param_2 = 0x37;
    *(undefined4 *)(param_2 + 2) = 5;
    *(undefined4 *)(param_2 + 4) = uVar6;
    iVar4 = FUN_800067dc(param_1,param_2,0);
    if (iVar4 != 0) {
      return iVar4;
    }
    *param_2 = 6;
    *(undefined4 *)(param_2 + 2) = 5;
    *(undefined4 *)(param_2 + 4) = 2;
    iVar4 = FUN_800067dc(param_1,param_2,0);
    if (iVar4 != 0) {
      return iVar4;
    }
  }
  else {
    if (*(int *)puVar1 != 2) goto LAB_80003110;
    FUN_8000705c(s_CARD_TYPE_SD_LOW_800031d4);
    FUN_800058b4(param_1,uVar6);
    if (param_3 != 1) goto LAB_80003110;
    FUN_8000705c(s_Card_width_4bit_800031c0);
    uVar6 = *(undefined4 *)(puVar1 + 4);
    *param_2 = 0x37;
    *(undefined4 *)(param_2 + 2) = 5;
    *(undefined4 *)(param_2 + 4) = uVar6;
    iVar4 = FUN_800067dc(param_1,param_2,0);
    if (iVar4 != 0) {
      return iVar4;
    }
    *param_2 = 6;
    *(undefined4 *)(param_2 + 2) = 5;
    *(undefined4 *)(param_2 + 4) = 2;
    iVar4 = FUN_800067dc(param_1,param_2,0);
    if (iVar4 != 0) {
      return iVar4;
    }
  }
  if ((param_1 != 0) && (iVar5 = iVar3, param_1 != 1)) {
    iVar5 = 0;
  }
  *(undefined4 *)(iVar5 + 0xc) = 1;
LAB_80003110:
  FUN_8000705c(s_SD_BLOCK_SIZE_512_800031e8);
  *param_2 = 0x10;
  *(undefined4 *)(param_2 + 2) = 0xd;
  *(undefined4 *)(param_2 + 4) = 0x200;
  FUN_800067dc(param_1,param_2,0);
  *param_2 = 7;
  *(undefined4 *)(param_2 + 4) = 0;
  *(undefined4 *)(param_2 + 2) = 0;
  FUN_800067dc(param_1);
  return 0;
}



void FUN_80003200(void)

{
  FUN_80003550(0,1000,1);
  FUN_80001944(2,0xd,PTR_LAB_8000323c,0);
  FUN_80003724(0);
  FUN_80006d88(0x7f);
  return;
}



void FUN_8000338c(void)

{
  uint *puVar1;
  
  *DAT_800033b8 = *DAT_800033b8 | 1;
  puVar1 = DAT_800033b8 + 1;
  *puVar1 = *puVar1;
  *puVar1 = *puVar1 | 1;
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



void FUN_80003418(int param_1)

{
  uint *puVar1;
  uint uVar2;
  uint *puVar3;
  uint *puVar4;
  
  puVar1 = DAT_8000353c;
  puVar4 = *(uint **)(param_1 + 0x10);
  *DAT_8000353c = *DAT_8000353c & 0x7fffffff;
  *puVar1 = DAT_80003540;
  *puVar1 = *puVar1 | 0x80000000;
  FUN_800010e4(1);
  puVar1 = DAT_80003544;
  *DAT_80003544 = *DAT_80003544 | 0x10;
  puVar3 = puVar1 + 0x2d;
  *puVar3 = *puVar3 | 0x80000000;
  puVar1 = puVar1 + 0x98;
  *puVar1 = *puVar1 | 0x10;
  FUN_800010e4(1);
  *puVar4 = *puVar4 & 0xfffffffe;
  puVar4[0x10] = ((uint)*(byte *)(param_1 + 0x50) + (uint)*(byte *)(param_1 + 0x54) +
                  (uint)*(byte *)(param_1 + 0x58) & 0x1f) << 4 | 0x80000000;
  puVar4[0x11] = 0xf0000006;
  puVar4[0x12] = *(int *)(param_1 + 0x20) - 1U | (*(ushort *)(param_1 + 0x1c) - 1) * 0x10000;
  puVar4[0x13] = DAT_80003548;
  puVar4[0x14] = DAT_8000354c;
  puVar4[0x15] = 0x160000;
  puVar4[0x16] = 0;
  puVar4[0x18] = 0;
  uVar2 = 0x10000000;
  if (*(int *)(param_1 + 0x5c) == 0) {
    uVar2 = 0x12000000;
  }
  if (*(int *)(param_1 + 0x60) == 0) {
    uVar2 = uVar2 | 0x1000000;
  }
  if (*(int *)(param_1 + 100) == 0) {
    uVar2 = uVar2 | 0x8000000;
  }
  if (*(int *)(param_1 + 0x68) == 0) {
    uVar2 = uVar2 | 0x4000000;
  }
  puVar4[0x22] = uVar2;
  puVar4[0x23] = 0;
  return;
}



void FUN_80003550(uint param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  
  iVar1 = (param_1 + 1) * 0x10 + 0x1c20c00;
  FUN_80007570(iVar1,iVar1 >> 0x1f,0);
  iVar1 = (param_1 + 1) * 0x10 + 0x1c20c00;
  uVar2 = FUN_800061b8(iVar1,iVar1 >> 0x1f,iVar1);
  iVar1 = (param_1 + 1) * 0x10 + 0x1c20c00;
  FUN_80007570(iVar1,iVar1 >> 0x1f,uVar2);
  iVar1 = (param_1 + 1) * 0x10 + 0x1c20c00;
  uVar2 = FUN_800061b8(iVar1,iVar1 >> 0x1f,iVar1);
  iVar1 = (param_1 + 1) * 0x10 + 0x1c20c00;
  FUN_80007570(iVar1,iVar1 >> 0x1f,uVar2);
  iVar1 = (param_1 + 1) * 0x10 + 0x1c20c00;
  uVar3 = FUN_800061b8(iVar1,iVar1 >> 0x1f,iVar1);
  iVar1 = (param_1 + 1) * 0x10 + 0x1c20c00;
  FUN_80007570(iVar1,iVar1 >> 0x1f,uVar3 | 4);
  iVar1 = (param_1 + 1) * 0x10 + 0x1c20c00;
  uVar3 = FUN_800061b8(iVar1,iVar1 >> 0x1f,iVar1);
  iVar1 = (param_1 + 1) * 0x10 + 0x1c20c00;
  FUN_80007570(iVar1,iVar1 >> 0x1f,uVar3 | 2);
  iVar1 = (param_1 + 1) * 0x10 + 0x1c20c04;
  FUN_80007570(iVar1,iVar1 >> 0x1f,param_2 * 0x18);
  if (param_3 == 1) {
    uVar3 = FUN_800061b8(DAT_80003720,0);
    FUN_80007570(DAT_80003720,0,uVar3 | 1 << (param_1 & 0xff));
  }
  return;
}



void FUN_80003724(int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = (param_1 + 1) * 0x10 + 0x1c20c00;
  uVar2 = FUN_800061b8(iVar1,iVar1 >> 0x1f,iVar1);
  iVar1 = (param_1 + 1) * 0x10 + 0x1c20c00;
  FUN_80007570(iVar1,iVar1 >> 0x1f,uVar2 | 1);
  return;
}



void FUN_80003794(void)

{
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



void FUN_80003798(void)

{
  return;
}



void FUN_8000379c(void)

{
  uint uVar1;
  
  uVar1 = FUN_800037ec();
  FUN_80003810(uVar1 | 4);
  return;
}



void FUN_800037b4(undefined4 param_1)

{
  coproc_moveto_Domain_Access_Control(param_1);
  return;
}



void FUN_800037bc(void)

{
  uint uVar1;
  
  uVar1 = FUN_800037ec();
  FUN_80003810(uVar1 | 0x1000);
  return;
}



void FUN_800037d4(void)

{
  uint uVar1;
  
  uVar1 = FUN_800037ec();
  FUN_80003810(uVar1 | 1);
  return;
}



undefined4 FUN_800037ec(void)

{
  undefined4 uVar1;
  
  uVar1 = coproc_movefrom_Control();
  return uVar1;
}



undefined4 FUN_800037f4(void)

{
  undefined4 in_cr5;
  undefined4 in_cr6;
  undefined4 in_cr8;
  
  coproc_moveto_Data_Synchronization(0);
  coprocessor_moveto(0xf,0,0,0,in_cr8,in_cr6);
  coprocessor_moveto(0xf,0,0,0,in_cr8,in_cr5);
  return 0;
}



void FUN_80003808(undefined4 param_1)

{
  coproc_moveto_Translation_table_base_0(param_1);
  return;
}



void FUN_80003810(undefined4 param_1)

{
  coproc_moveto_Control(param_1);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined4 FUN_80003818(void)

{
  uint *puVar1;
  
  FUN_8000705c(s_U_clock_set_pll6___d_hz_8000386a + 2,_DAT_80003868);
  puVar1 = DAT_80003884;
  *DAT_80003884 = *DAT_80003884 & 0x7fffffff;
  *puVar1 = *puVar1 & 0xfffff000;
  *puVar1 = *puVar1 | 0x1700;
  *puVar1 = *puVar1 | 0x80000000;
  return 0;
}



// WARNING (jumptable): Heritage AFTER dead removal. Example location: s0xffffffe8 : 0x80003910
// WARNING: Restarted to delay deadcode elimination for space: stack

void FUN_80003888(int *param_1,int *param_2)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  uint uVar6;
  int *piVar7;
  int *piVar8;
  int iVar9;
  code *in_lr;
  bool bVar10;
  undefined8 uVar11;
  code *UNRECOVERED_JUMPTABLE_00;
  
  iVar9 = *param_1;
  UNRECOVERED_JUMPTABLE_00 = in_lr;
  if (param_2 == (int *)0x0) {
    piVar7 = *(int **)(iVar9 + 0xc);
    bVar10 = piVar7 != (int *)0x0;
    piVar2 = param_1;
    if (bVar10) {
      piVar2 = *(int **)(iVar9 + 0x14);
    }
    if (bVar10 && piVar2 < piVar7 || (!bVar10 || piVar2 == piVar7)) {
      piVar7 = (int *)0x1;
    }
  }
  else {
    uVar1 = FUN_800055b4();
    if (uVar1 < 2) {
                    // WARNING: Could not recover jumptable at 0x800038b0. Too many branches
                    // WARNING: Treating indirect jump as call
      (*UNRECOVERED_JUMPTABLE_00)();
      return;
    }
    if (uVar1 == 0xffffffff) {
                    // WARNING: Could not recover jumptable at 0x800038bc. Too many branches
                    // WARNING: Treating indirect jump as call
      (*UNRECOVERED_JUMPTABLE_00)();
      return;
    }
    piVar7 = param_2;
    if (uVar1 < *(uint *)(iVar9 + 0x14)) {
                    // WARNING: Could not recover jumptable at 0x800038d0. Too many branches
                    // WARNING: Treating indirect jump as call
      (*UNRECOVERED_JUMPTABLE_00)();
      return;
    }
  }
  if (*(int *)(iVar9 + 0x10) == 0) {
                    // WARNING: Could not recover jumptable at 0x800038e0. Too many branches
                    // WARNING: Treating indirect jump as call
    (*UNRECOVERED_JUMPTABLE_00)();
    return;
  }
  piVar2 = piVar7;
  if (piVar7 == param_2) {
    piVar8 = (int *)((int)piVar7 + 1);
    if (*(int **)(iVar9 + 0x14) <= piVar8) {
      piVar8 = (int *)0x2;
    }
    uVar11 = FUN_800055b4(param_1,piVar8);
    piVar5 = (int *)((ulonglong)uVar11 >> 0x20);
    iVar3 = (int)uVar11;
    if (iVar3 == 1 || iVar3 == -1) {
                    // WARNING: Could not recover jumptable at 0x80003914. Too many branches
                    // WARNING: Treating indirect jump as call
      (*UNRECOVERED_JUMPTABLE_00)();
      return;
    }
    if (iVar3 == 0) {
      if (piVar8 != (int *)0x0) {
LAB_800039b0:
        iVar3 = FUN_80006010(iVar9,piVar8,0xffffffff);
        if ((iVar3 == 0) &&
           ((param_2 == (int *)0x0 || (iVar3 = FUN_80006010(iVar9,param_2,piVar8), iVar3 == 0)))) {
          uVar4 = *(uint *)(iVar9 + 0x10);
          uVar6 = *(int *)(iVar9 + 0x14) - 2;
          uVar1 = uVar4;
          if (uVar4 <= uVar6) {
            uVar1 = uVar4 - 1;
          }
          *(int **)(iVar9 + 0xc) = piVar8;
          if (uVar4 <= uVar6) {
            *(uint *)(iVar9 + 0x10) = uVar1;
          }
          *(byte *)(iVar9 + 4) = *(byte *)(iVar9 + 4) | 1;
        }
        else {
          if (iVar3 == 1) {
            piVar8 = (int *)0xffffffff;
          }
          else {
            piVar8 = (int *)0x1;
          }
        }
                    // WARNING: Could not recover jumptable at 0x800039fc. Too many branches
                    // WARNING: Treating indirect jump as call
        (**(code **)(&stack0xffffffe8 + 0x14))(piVar8);
        return;
      }
    }
    else {
      piVar8 = *(int **)(iVar9 + 0xc);
      bVar10 = piVar8 == (int *)0x2;
      if ((int *)0x1 < piVar8) {
        piVar5 = *(int **)(iVar9 + 0x14);
        bVar10 = piVar5 == piVar8;
      }
      if (((int *)0x1 < piVar8 && piVar8 <= piVar5) && !bVar10) {
        piVar7 = piVar8;
        piVar2 = piVar8;
      }
    }
  }
  do {
    piVar8 = (int *)((int)piVar2 + 1);
    if ((*(int **)(iVar9 + 0x14) <= piVar8) && (piVar8 = (int *)0x2, piVar7 < (int *)0x2)) break;
    iVar3 = FUN_800055b4(param_1,piVar8);
    if (iVar3 == 0) goto LAB_800039b0;
    if (iVar3 == 1 || iVar3 == -1) {
                    // WARNING: Could not recover jumptable at 0x80003998. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(&stack0xffffffe8 + 0x14))();
      return;
    }
    piVar2 = piVar8;
  } while (piVar8 != piVar7);
                    // WARNING: Could not recover jumptable at 0x800039ac. Too many branches
                    // WARNING: Treating indirect jump as call
  (**(code **)(&stack0xffffffe8 + 0x14))(0);
  return;
}



void FUN_80003a2c(int param_1)

{
  uint local_c;
  uint local_8;
  
  local_8 = 0;
  while (local_8 < (uint)(param_1 * DAT_80003a8c)) {
    local_c = 0;
    while (local_c < 0x14) {
      local_c = local_c + 1;
    }
    local_8 = local_8 + 1;
  }
  return;
}



void FUN_80003a90(int *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  code *pcStack4;
  
  uVar5 = param_1[4] + 0x20;
  iVar4 = *param_1;
  if (param_1[6] == 0 || 0x1fffff < uVar5) {
                    // WARNING: Could not recover jumptable at 0x80003ac4. Too many branches
                    // WARNING: Treating indirect jump as call
    (**(code **)(&stack0xffffffec + 0x10))();
    return;
  }
  if ((uVar5 & 0x1ff) == 0) {
    param_1[6] = param_1[6] + 1;
    if (param_1[5] == 0) {
      if ((uint)*(ushort *)(iVar4 + 8) <= uVar5 >> 5) {
LAB_80003b98:
        param_1[6] = 0;
                    // WARNING: Could not recover jumptable at 0x80003ba8. Too many branches
                    // WARNING: Treating indirect jump as call
        (**(code **)(&stack0xffffffd8 + 0x24))(4);
        return;
      }
    }
    else {
      if ((*(ushort *)(iVar4 + 10) - 1 & uVar5 >> 9) == 0) {
        uVar1 = FUN_800055b4(param_1);
        if (uVar1 < 2) {
LAB_80003bac:
                    // WARNING: Could not recover jumptable at 0x80003bb8. Too many branches
                    // WARNING: Treating indirect jump as call
          (**(code **)(&stack0xffffffd8 + 0x24))(2);
          return;
        }
        if (uVar1 == 0xffffffff) goto LAB_80003c74;
        if (*(uint *)(iVar4 + 0x14) <= uVar1) {
          if (param_2 == 0) goto LAB_80003b98;
          uVar1 = FUN_80003888(param_1,param_1[5]);
          if (uVar1 == 0) {
                    // WARNING: Could not recover jumptable at 0x80003b58. Too many branches
                    // WARNING: Treating indirect jump as call
            (**(code **)(&stack0xffffffd8 + 0x24))(7);
            return;
          }
          if (uVar1 == 1) goto LAB_80003bac;
          if (uVar1 == 0xffffffff) {
LAB_80003c74:
                    // WARNING: Could not recover jumptable at 0x80003c80. Too many branches
                    // WARNING: Treating indirect jump as call
            (**(code **)(&stack0xffffffd8 + 0x24))(1);
            return;
          }
          if (*(char *)(iVar4 + 3) != '\0') {
            iVar2 = FUN_8000404c(*(undefined *)(iVar4 + 1),iVar4 + 0x30,
                                 *(undefined4 *)(iVar4 + 0x2c),1);
            if (iVar2 != 0) goto LAB_80003c74;
            *(undefined *)(iVar4 + 3) = 0;
            if (((uint)(*(int *)(iVar4 + 0x2c) - *(int *)(iVar4 + 0x20)) < *(uint *)(iVar4 + 0x18))
               && (*(char *)(iVar4 + 2) == '\x02')) {
              FUN_8000404c(*(undefined *)(iVar4 + 1),iVar4 + 0x30,
                           *(uint *)(iVar4 + 0x18) + *(int *)(iVar4 + 0x2c),1);
            }
          }
          if (uVar1 - 2 < *(int *)(iVar4 + 0x14) - 2U) {
            iVar2 = (uint)*(ushort *)(iVar4 + 10) * (uVar1 - 2) + *(int *)(iVar4 + 0x28);
          }
          else {
            iVar2 = 0;
          }
          *(int *)(iVar4 + 0x2c) = iVar2;
          FUN_80005868(iVar4 + 0x30,0,0x200);
          uVar6 = 0;
          while ((uVar6 < *(ushort *)(iVar4 + 10) &&
                 (iVar3 = FUN_8000404c(*(undefined *)(iVar4 + 1),iVar4 + 0x30,iVar2 + uVar6,1),
                 iVar3 == 0))) {
            uVar6 = uVar6 + 1;
          }
          if (*(ushort *)(iVar4 + 10) != uVar6) goto LAB_80003c74;
        }
        param_1[5] = uVar1;
        if (uVar1 - 2 < *(int *)(iVar4 + 0x14) - 2U) {
          iVar2 = (uint)*(ushort *)(iVar4 + 10) * (uVar1 - 2) + *(int *)(iVar4 + 0x28);
        }
        else {
          iVar2 = 0;
        }
        param_1[6] = iVar2;
      }
    }
  }
  param_1[4] = uVar5;
  param_1[7] = (uVar5 & 0x1ff) + iVar4 + 0x30;
                    // WARNING: Could not recover jumptable at 0x80003cd4. Too many branches
                    // WARNING: Treating indirect jump as call
  (**(code **)(&stack0xffffffd8 + 0x24))(0);
  return;
}



int FUN_80003cd8(int *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *param_1;
  iVar1 = FUN_80003d84(param_1,0);
  while ((iVar1 == 0 && (iVar1 = FUN_80005f60(iVar2,param_1[6]), iVar1 == 0))) {
    if (*(char *)param_1[7] == -0x1b || *(char *)param_1[7] == '\0') {
      iVar1 = FUN_80005f60(iVar2,param_1[6]);
      if (iVar1 == 0) {
        FUN_80005868(param_1[7],0,0x20);
        FUN_800057f4(param_1[7],param_1 + 8,0xb);
        *(undefined *)(iVar2 + 3) = 1;
        return 0;
      }
      return iVar1;
    }
    iVar1 = FUN_80003a90(param_1,1);
  }
  if (iVar1 == 4) {
    iVar1 = 7;
  }
  return iVar1;
}



undefined4 FUN_80003d84(byte **param_1,uint param_2)

{
  uint uVar1;
  ushort uVar2;
  byte *pbVar3;
  byte *pbVar4;
  byte *pbVar5;
  bool bVar6;
  
  pbVar4 = param_1[2];
  param_1[4] = (byte *)0x0;
  pbVar5 = *param_1;
  if ((pbVar4 == (byte *)0x0) &&
     ((*pbVar5 < 3 || (pbVar4 = *(byte **)(pbVar5 + 0x24), pbVar4 == (byte *)0x0)))) {
    if (*(short *)(pbVar5 + 8) == 0) {
      return 2;
    }
    pbVar3 = *(byte **)(pbVar5 + 0x24);
    param_1[6] = pbVar3;
  }
  else {
    uVar2 = *(ushort *)(pbVar5 + 10);
    uVar1 = (uint)uVar2 * 0x200;
    if (uVar1 <= param_2) {
      do {
        pbVar4 = (byte *)FUN_800055b4(param_1);
        if (pbVar4 == (byte *)0xffffffff) {
          return 1;
        }
        bVar6 = pbVar4 == (byte *)0x2;
        pbVar3 = pbVar4;
        if (pbVar4 >= (byte *)0x2) {
          pbVar3 = *(byte **)(pbVar5 + 0x14);
          bVar6 = pbVar3 == pbVar4;
        }
        if ((pbVar4 < (byte *)0x2 || pbVar3 < pbVar4) || bVar6) {
          return 2;
        }
        param_2 = param_2 + (uint)uVar2 * -0x200;
      } while (uVar1 <= param_2);
    }
    if (pbVar4 + -2 < (byte *)(*(int *)(pbVar5 + 0x14) + -2)) {
      pbVar3 = (byte *)((uint)*(ushort *)(pbVar5 + 10) * (int)(pbVar4 + -2) +
                       *(int *)(pbVar5 + 0x28));
    }
    else {
      pbVar3 = (byte *)0x0;
    }
    param_1[6] = pbVar3;
  }
  param_1[5] = pbVar4;
  if (pbVar3 == (byte *)0x0) {
    return 2;
  }
  param_1[6] = pbVar3 + (param_2 >> 9);
  param_1[7] = pbVar5 + (param_2 & 0x1ff) + 0x30;
  return 0;
}



int FUN_80003e8c(int param_1)

{
  int iVar1;
  
  if (param_1 != 0) {
    return 1;
  }
  iVar1 = FUN_80001b48(0);
  if (iVar1 != 0) {
    iVar1 = 2;
  }
  return iVar1;
}



undefined4 FUN_80003eb0(undefined4 param_1,int param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  
  switch(param_1) {
  case 0:
    if (param_2 == 0) {
      return 0;
    }
    if (param_2 == 1) {
      uVar1 = *(undefined4 *)(DAT_80003f84 + 4);
      goto LAB_80003efc;
    }
    break;
  case 1:
    uVar1 = 0;
    if (param_2 == 0) {
      return uVar1;
    }
    if (param_2 != 1) {
      if (param_2 == 2) {
        *(undefined2 *)param_3 = 0x200;
        return uVar1;
      }
      if (param_2 != 3) {
        return 4;
      }
      *param_3 = 0x200;
      return uVar1;
    }
    uVar1 = 0x40000;
LAB_80003efc:
    *param_3 = uVar1;
    return 0;
  case 2:
    if (param_2 == 0) {
      return 0;
    }
    if (param_2 == 1) {
      return 1;
    }
    break;
  default:
    goto switchD_80003eb8_caseD_3;
  }
  if (param_2 == 2) {
    *(undefined2 *)param_3 = 0x200;
    return 0;
  }
  if (param_2 == 3) {
    *param_3 = 0x200;
    return 0;
  }
switchD_80003eb8_caseD_3:
  return 4;
}



uint FUN_80003f88(int param_1,uint param_2,uint param_3,int param_4)

{
  int iVar1;
  int iVar2;
  
  if (param_1 == 0) {
    if ((param_2 & 3) == 0) {
      param_3 = FUN_800021c0(0,param_3,param_4,param_2);
      if (param_3 != 0) {
        param_3 = 1;
      }
    }
    else {
      iVar1 = FUN_800001cc(param_4 << 9);
      if (iVar1 == 0) {
        FUN_8000705c(s_SD_malloc_ERR____80004030);
      }
      else {
        iVar2 = FUN_800021c0(0,param_3,param_4,iVar1);
        param_3 = (uint)(iVar2 != 0);
        FUN_80000350(param_2,iVar1,param_4 << 9);
        FUN_8000022e(iVar1);
      }
    }
  }
  return param_3;
}



undefined4 FUN_80004044(void)

{
  return 0;
}



uint FUN_8000404c(undefined4 param_1,uint param_2,uint param_3,int param_4)

{
  int iVar1;
  int iVar2;
  
  switch(param_1) {
  case 0:
    if ((param_2 & 3) == 0) {
      param_3 = FUN_80002398(0,param_3,param_4,param_2);
      if (param_3 != 0) {
        param_3 = 1;
      }
    }
    else {
      iVar1 = FUN_800001cc(param_4 << 9);
      if (iVar1 == 0) {
        FUN_8000705c(s_SD_malloc_ERR____80004110);
      }
      else {
        FUN_80000350(iVar1,param_2,param_4 << 9);
        iVar2 = FUN_80002398(0,param_3,param_4,iVar1);
        param_3 = (uint)(iVar2 != 0);
        FUN_8000022e(iVar1);
      }
    }
    break;
  case 1:
  case 2:
  case 3:
  case 4:
    break;
  default:
    param_3 = 4;
  }
  return param_3;
}



void FUN_80004124(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uStack16;
  
  uStack16 = param_4;
  iVar1 = FUN_800048f0();
  if (iVar1 == 0) {
    iVar1 = FUN_80007514(param_1,&uStack16);
    if (iVar1 == 0) {
      *param_1 = 0;
    }
    return;
  }
  return;
}



// WARNING (jumptable): Heritage AFTER dead removal. Example location: s0xfffffffc : 0x800041e8
// WARNING: Restarted to delay deadcode elimination for space: stack

undefined4 FUN_80004154(undefined *param_1,byte *param_2,int param_3)

{
  byte bVar1;
  undefined *puVar2;
  byte *pbVar3;
  undefined4 uVar5;
  uint uVar6;
  code *UNRECOVERED_JUMPTABLE_00;
  bool bVar7;
  undefined *local_10;
  byte *local_c;
  int iStack8;
  code *UNRECOVERED_JUMPTABLE;
  byte *pbVar4;
  
  puVar2 = PTR_DAT_80004204;
  pbVar4 = param_2;
  if (param_2 != (byte *)0x0) {
    do {
      pbVar3 = pbVar4 + 1;
      bVar1 = *pbVar4;
      if (bVar1 < 0x21) {
        uVar6 = 0;
        goto LAB_800041b8;
      }
      pbVar4 = pbVar3;
    } while (bVar1 != 0x3a);
    uVar6 = *param_2 - 0x30;
    bVar7 = uVar6 == 9;
    if (uVar6 < 10) {
      bVar7 = param_2 + 2 == pbVar3;
    }
    if (((bVar7) && ((int)uVar6 < 1)) && (-1 < (int)uVar6)) {
LAB_800041b8:
      if (*(undefined **)(PTR_DAT_80004204 + uVar6 * 4) != (undefined *)0x0) {
        **(undefined **)(PTR_DAT_80004204 + uVar6 * 4) = 0;
      }
      if (param_1 != (undefined *)0x0) {
        *param_1 = 0;
      }
      *(undefined **)(puVar2 + uVar6 * 4) = param_1;
      local_10 = param_1;
      local_c = param_2;
      iStack8 = param_3;
      if (param_3 != 0) {
        UNRECOVERED_JUMPTABLE = UNRECOVERED_JUMPTABLE_00;
        FUN_80004c10(&local_c,&local_10,0);
                    // WARNING: Could not recover jumptable at 0x80004200. Too many branches
                    // WARNING: Treating indirect jump as call
        uVar5 = (*UNRECOVERED_JUMPTABLE)();
        return uVar5;
      }
                    // WARNING: Could not recover jumptable at 0x800041e8. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar5 = (*UNRECOVERED_JUMPTABLE_00)(0);
      return uVar5;
    }
  }
  return 0xb;
}



int FUN_80004208(char **param_1,undefined4 param_2,uint param_3)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  char *pcVar4;
  int iVar5;
  char *pcVar6;
  uint uVar7;
  bool bVar8;
  char *local_58;
  char *local_54;
  byte local_4e;
  char *local_38;
  byte local_29;
  char **ppcStack40;
  undefined4 local_24;
  uint uStack32;
  
  if (param_1 == (char **)0x0) {
    return 9;
  }
  pcVar6 = (char *)(param_3 & 0x3f);
  ppcStack40 = param_1;
  local_24 = param_2;
  uStack32 = param_3;
  iVar2 = FUN_80004c10(&local_24,&local_58,pcVar6);
  if (iVar2 != 0) goto LAB_8000453c;
  local_54 = local_58;
  iVar2 = FUN_800052d4(&local_54,local_24);
  if ((iVar2 == 0) && ((local_29 & 0x80) != 0)) {
    iVar2 = 6;
  }
  if ((param_3 & 0x1c) == 0) {
    if (iVar2 != 0) goto LAB_8000453c;
    if ((local_4e & 0x10) != 0) {
      iVar2 = 4;
      goto LAB_8000453c;
    }
    bVar8 = (param_3 & 2) == 0;
    if (!bVar8) {
      bVar8 = (local_4e & 1) == 0;
    }
    if (!bVar8) goto LAB_800042ac;
LAB_800043d4:
    if (((uint)pcVar6 & 8) != 0) {
LAB_800043dc:
      pcVar6 = (char *)((uint)pcVar6 | 0x40);
    }
  }
  else {
    if (iVar2 == 0) {
      if ((local_4e & 0x11) != 0) {
LAB_800042ac:
        iVar2 = 7;
        goto LAB_8000453c;
      }
      if ((param_3 & 4) != 0) {
        iVar2 = 8;
        goto LAB_8000453c;
      }
    }
    else {
      if (iVar2 == 4) {
        iVar2 = FUN_80003cd8(&local_54);
      }
      pcVar6 = (char *)((uint)pcVar6 | 8);
      if (iVar2 != 0) goto LAB_8000453c;
    }
    pcVar4 = local_38;
    if (((uint)pcVar6 & 8) != 0) {
      uVar7 = (uint)*(ushort *)(local_38 + 0x1a);
      if (*local_58 == '\x03') {
        uVar7 = CONCAT22(*(undefined2 *)(local_38 + 0x14),*(ushort *)(local_38 + 0x1a));
      }
      uVar3 = FUN_800056e8();
      pcVar4[0xe] = (char)uVar3;
      pcVar4[0xf] = (char)((uint)uVar3 >> 8);
      pcVar4[0x10] = (char)((uint)uVar3 >> 0x10);
      pcVar4[0x11] = (char)((uint)uVar3 >> 0x18);
      local_38[0xb] = ' ';
      local_38[0x1a] = '\0';
      local_38[0x1b] = '\0';
      if (*local_58 == '\x03') {
        local_38[0x14] = '\0';
        local_38[0x15] = '\0';
      }
      local_38[0x1c] = '\0';
      local_38[0x1d] = '\0';
      local_38[0x1e] = '\0';
      local_38[0x1f] = '\0';
      local_58[3] = '\x01';
      if (uVar7 != 0) {
        uVar3 = *(undefined4 *)(local_58 + 0x2c);
        iVar2 = FUN_800061c8(&local_54,uVar7,0);
        if (iVar2 != 0) goto LAB_8000453c;
        iVar2 = FUN_80005f60(local_58,uVar3);
        *(uint *)(local_58 + 0xc) = uVar7 - 1;
        if (iVar2 != 0) goto LAB_8000453c;
        goto LAB_800043d4;
      }
      goto LAB_800043dc;
    }
  }
  param_1[8] = *(char **)(local_58 + 0x2c);
  param_1[9] = local_38;
  pcVar4 = (char *)(uint)*(ushort *)(local_38 + 0x1a);
  if (*local_58 == '\x03') {
    pcVar4 = (char *)CONCAT22(*(undefined2 *)(local_38 + 0x14),*(ushort *)(local_38 + 0x1a));
  }
  param_1[2] = pcVar4;
  param_1[3] = *(char **)(local_38 + 0x1c);
  *param_1 = local_58;
  *(undefined2 *)(param_1 + 1) = *(undefined2 *)(local_58 + 6);
  *(char *)(param_1 + 4) = (char)pcVar6;
  *(undefined *)((int)param_1 + 0x11) = 0;
  param_1[7] = (char *)0x0;
  param_1[5] = (char *)0x0;
  FUN_80005868(param_1 + 10,0,0x200);
  bVar8 = ((uint)pcVar6 & 0x20) == 0;
  if (!bVar8) {
    pcVar6 = param_1[3];
  }
  if (bVar8 || pcVar6 == (char *)0x0) {
    return iVar2;
  }
  param_1[5] = pcVar6;
  pcVar4 = param_1[2];
  uVar1 = *(ushort *)(local_58 + 10);
  do {
    if (pcVar6 <= (char *)((uint)uVar1 * 0x200)) {
      param_1[6] = pcVar4;
      if (((uint)pcVar6 & 0x1ff) == 0) {
        return iVar2;
      }
      if ((pcVar4 + -2 < (char *)(*(int *)(local_58 + 0x14) + -2)) &&
         (iVar5 = (uint)*(ushort *)(local_58 + 10) * (int)(pcVar4 + -2) + *(int *)(local_58 + 0x28),
         iVar5 != 0)) {
        pcVar6 = (char *)(iVar5 + ((uint)pcVar6 >> 9));
        param_1[7] = pcVar6;
        iVar5 = FUN_80003f88(local_58[1],param_1 + 10,pcVar6,1);
        if (iVar5 == 0) {
          return iVar2;
        }
        iVar2 = 1;
      }
      else {
        iVar2 = 2;
      }
      goto LAB_8000453c;
    }
    pcVar4 = (char *)FUN_800055b4(param_1);
    if (pcVar4 < (char *)0x2) {
      iVar2 = 2;
    }
    if (pcVar4 == (char *)0xffffffff) {
      iVar2 = 1;
      param_1[6] = (char *)0xffffffff;
      goto LAB_8000453c;
    }
    pcVar6 = pcVar6 + (uint)uVar1 * -0x200;
  } while (iVar2 == 0);
  param_1[6] = pcVar4;
LAB_8000453c:
  *param_1 = (char *)0x0;
  return iVar2;
}



uint FUN_80004558(int param_1,int param_2,uint param_3,int *param_4)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  bool bVar7;
  int aiStack44 [2];
  
  *param_4 = 0;
  uVar1 = FUN_80007514(param_1,aiStack44);
  bVar7 = uVar1 == 0;
  if (bVar7) {
    uVar1 = (uint)*(byte *)(param_1 + 0x11);
  }
  if (!bVar7 || uVar1 != 0) {
    return uVar1;
  }
  if ((*(byte *)(param_1 + 0x10) & 1) == 0) {
    return 7;
  }
  uVar1 = *(uint *)(param_1 + 0x14);
  uVar2 = *(int *)(param_1 + 0xc) - uVar1;
  if (uVar2 < param_3) {
    param_3 = uVar2;
  }
  do {
    if (param_3 == 0) {
      return 0;
    }
    if ((uVar1 & 0x1ff) == 0) {
      uVar2 = *(ushort *)(aiStack44[0] + 10) - 1 & uVar1 >> 9;
      if (uVar2 == 0) {
        if (uVar1 == 0) {
          uVar1 = *(uint *)(param_1 + 8);
        }
        else {
          uVar1 = FUN_800055b4(param_1,*(undefined4 *)(param_1 + 0x18));
        }
        if (uVar1 < 2) goto LAB_80004698;
        if (uVar1 == 0xffffffff) goto LAB_80004740;
        *(uint *)(param_1 + 0x18) = uVar1;
      }
      uVar1 = *(int *)(param_1 + 0x18) - 2;
      if (*(int *)(aiStack44[0] + 0x14) - 2U <= uVar1) {
LAB_80004698:
        *(undefined *)(param_1 + 0x11) = 2;
        return 2;
      }
      uVar5 = (uint)*(ushort *)(aiStack44[0] + 10);
      iVar4 = uVar5 * uVar1 + *(int *)(aiStack44[0] + 0x28);
      if (iVar4 == 0) goto LAB_80004698;
      iVar4 = iVar4 + uVar2;
      uVar6 = param_3 >> 9;
      if (uVar6 == 0) {
        if (*(int *)(param_1 + 0x1c) != iVar4) {
          if ((*(byte *)(param_1 + 0x10) & 0x80) != 0) {
            iVar3 = FUN_8000404c(*(undefined *)(aiStack44[0] + 1),param_1 + 0x28,
                                 *(int *)(param_1 + 0x1c),1);
            if (iVar3 != 0) goto LAB_80004740;
            *(byte *)(param_1 + 0x10) = *(byte *)(param_1 + 0x10) & 0x7f;
          }
          iVar3 = FUN_80003f88(*(undefined *)(aiStack44[0] + 1),param_1 + 0x28,iVar4,1);
          if (iVar3 != 0) goto LAB_80004740;
        }
        *(int *)(param_1 + 0x1c) = iVar4;
        goto LAB_8000475c;
      }
      if (uVar5 < uVar2 + uVar6) {
        uVar6 = uVar5 - uVar2;
      }
      iVar3 = FUN_80003f88(*(undefined *)(aiStack44[0] + 1),param_2,iVar4,uVar6);
      if (iVar3 != 0) {
LAB_80004740:
        *(undefined *)(param_1 + 0x11) = 1;
        return 1;
      }
      if (((*(byte *)(param_1 + 0x10) & 0x80) != 0) &&
         (uVar1 = *(int *)(param_1 + 0x1c) - iVar4, uVar1 < uVar6)) {
        FUN_800057f4(param_2 + uVar1 * 0x200,param_1 + 0x28,0x200);
      }
      uVar6 = uVar6 << 9;
    }
    else {
LAB_8000475c:
      uVar1 = *(ushort *)(param_1 + 0x14) & 0x1ff;
      uVar6 = 0x200 - uVar1;
      if (param_3 < uVar6) {
        uVar6 = param_3;
      }
      FUN_800057f4(param_2,uVar1 + param_1 + 0x28,uVar6);
    }
    *param_4 = *param_4 + uVar6;
    param_2 = param_2 + uVar6;
    uVar1 = *(int *)(param_1 + 0x14) + uVar6;
    *(uint *)(param_1 + 0x14) = uVar1;
    param_3 = param_3 - uVar6;
  } while( true );
}



// WARNING: Restarted to delay deadcode elimination for space: stack

int FUN_800047bc(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  char cVar4;
  undefined auStack72 [24];
  int iStack48;
  int iStack44;
  byte bStack29;
  undefined4 local_18;
  undefined4 *puStack20;
  
  local_18 = param_1;
  puStack20 = param_2;
  iVar1 = FUN_80004c10(&local_18,auStack72,0);
  if (iVar1 != 0) {
    return iVar1;
  }
  iVar1 = FUN_800052d4(auStack72,local_18);
  if (iVar1 != 0) {
    return iVar1;
  }
  if ((bStack29 & 0x80) != 0) {
    return 6;
  }
  if (param_2 != (undefined4 *)0x0) {
    *(undefined *)((int)param_2 + 9) = 0;
    if (iStack48 != 0) {
      iVar1 = 0;
      uVar3 = 0;
      do {
        cVar4 = *(char *)(iStack44 + uVar3);
        uVar3 = uVar3 + 1;
        if (cVar4 != ' ') {
          if (cVar4 == '\x05') {
            cVar4 = -0x1b;
          }
          iVar2 = iVar1;
          if (uVar3 == 9) {
            iVar2 = iVar1 + 1;
            *(undefined *)((int)param_2 + iVar1 + 9) = 0x2e;
          }
          iVar1 = iVar2 + 1;
          *(char *)((int)param_2 + iVar2 + 9) = cVar4;
        }
      } while (uVar3 < 0xb);
      *(undefined *)((int)param_2 + iVar1 + 9) = 0;
      *(undefined *)(param_2 + 2) = *(undefined *)(iStack44 + 0xb);
      *param_2 = *(undefined4 *)(iStack44 + 0x1c);
      *(undefined2 *)((int)param_2 + 6) = *(undefined2 *)(iStack44 + 0x16);
      *(undefined2 *)(param_2 + 1) = *(undefined2 *)(iStack44 + 0x18);
      return 0;
    }
    return 0;
  }
  return 0;
}



int FUN_800048f0(char **param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  int local_10;
  
  local_10 = param_4;
  iVar1 = FUN_80007514(param_1,&local_10);
  if (iVar1 != 0) {
    return iVar1;
  }
  if ((*(byte *)(param_1 + 4) & 0x40) == 0) {
    return 0;
  }
  if ((*(byte *)(param_1 + 4) & 0x80) != 0) {
    iVar1 = FUN_8000404c(*(undefined *)(local_10 + 1),param_1 + 10,param_1[7],1);
    if (iVar1 != 0) {
      return 1;
    }
    *(byte *)(param_1 + 4) = *(byte *)(param_1 + 4) & 0x7f;
  }
  uVar2 = FUN_800056e8();
  iVar1 = FUN_80005f60(local_10,param_1[8]);
  if (iVar1 == 0) {
    pcVar3 = param_1[9];
    pcVar3[0xb] = pcVar3[0xb] | 0x20;
    pcVar4 = param_1[2];
    pcVar5 = *param_1;
    pcVar3[0x1a] = (char)pcVar4;
    pcVar3[0x1b] = (char)((uint)pcVar4 >> 8);
    if (*pcVar5 == '\x03') {
      pcVar3[0x14] = (char)((uint)pcVar4 >> 0x10);
      pcVar3[0x15] = (char)((uint)pcVar4 >> 0x18);
    }
    pcVar4 = param_1[3];
    pcVar3[0x1c] = (char)pcVar4;
    pcVar3[0x1d] = (char)((uint)pcVar4 >> 8);
    pcVar3[0x1e] = (char)((uint)pcVar4 >> 0x10);
    pcVar3[0x1f] = (char)((uint)pcVar4 >> 0x18);
    pcVar3[0x16] = (char)uVar2;
    pcVar3[0x17] = (char)((uint)uVar2 >> 8);
    pcVar3[0x18] = (char)((uint)uVar2 >> 0x10);
    pcVar3[0x19] = (char)((uint)uVar2 >> 0x18);
    pcVar3[0x12] = '\0';
    pcVar3[0x13] = '\0';
    *(undefined *)(local_10 + 3) = 1;
    iVar1 = FUN_80006c24();
    *(byte *)(param_1 + 4) = *(byte *)(param_1 + 4) & 0xbf;
    return iVar1;
  }
  return iVar1;
}



// WARNING (jumptable): Heritage AFTER dead removal. Example location: s0xfffffffc : 0x80004a38
// WARNING: Could not reconcile some variable overlaps
// WARNING: Restarted to delay deadcode elimination for space: stack

void FUN_80004a10(undefined4 param_1)

{
  char *pcVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  code *in_lr;
  undefined4 uStack136;
  byte bStack130;
  uint uStack128;
  int iStack112;
  byte *pbStack108;
  char *pcStack92;
  byte bStack86;
  undefined4 uStack68;
  undefined *puStack64;
  byte bStack49;
  char *apcStack40 [3];
  undefined4 uStack28;
  code *UNRECOVERED_JUMPTABLE;
  
  uStack28 = param_1;
  UNRECOVERED_JUMPTABLE = in_lr;
  iVar3 = FUN_80004c10(&uStack28,apcStack40,2);
  if (iVar3 != 0) {
                    // WARNING: Could not recover jumptable at 0x80004a38. Too many branches
                    // WARNING: Treating indirect jump as call
    (*UNRECOVERED_JUMPTABLE)();
    return;
  }
  pcStack92 = apcStack40[0];
  iVar3 = FUN_800052d4(&pcStack92,uStack28);
  if (iVar3 != 0) {
                    // WARNING: Could not recover jumptable at 0x80004a5c. Too many branches
                    // WARNING: Treating indirect jump as call
    (*UNRECOVERED_JUMPTABLE)();
    return;
  }
  if ((bStack49 & 0x80) != 0) {
                    // WARNING: Could not recover jumptable at 0x80004a74. Too many branches
                    // WARNING: Treating indirect jump as call
    (*UNRECOVERED_JUMPTABLE)(6);
    return;
  }
  if ((bStack86 & 1) == 0) {
    uVar4 = (uint)*(ushort *)(puStack64 + 0x1a);
    if (*apcStack40[0] == '\x03') {
      uVar4 = CONCAT22(*(undefined2 *)(puStack64 + 0x14),*(ushort *)(puStack64 + 0x1a));
    }
    if ((bStack86 & 0x10) == 0) {
LAB_80004b94:
      pcVar1 = pcStack92;
      iVar3 = FUN_80005f60(pcStack92,uStack68);
      if (iVar3 != 0) {
                    // WARNING: Could not recover jumptable at 0x80004bb0. Too many branches
                    // WARNING: Treating indirect jump as call
        (*UNRECOVERED_JUMPTABLE)();
        return;
      }
      *puStack64 = 0xe5;
      pcVar1[3] = '\x01';
      if ((uVar4 != 0) && (iVar3 = FUN_800061c8(&pcStack92,uVar4,0), iVar3 != 0)) {
                    // WARNING: Could not recover jumptable at 0x80004be8. Too many branches
                    // WARNING: Treating indirect jump as call
        (*UNRECOVERED_JUMPTABLE)();
        return;
      }
      FUN_80006c24(apcStack40[0]);
                    // WARNING: Could not recover jumptable at 0x80004bfc. Too many branches
                    // WARNING: Treating indirect jump as call
      (*UNRECOVERED_JUMPTABLE)();
      return;
    }
    uStack136 = apcStack40[0];
    uStack128 = uVar4;
    iVar3 = FUN_80003d84(&uStack136,0);
    pcVar1 = uStack136;
    if (iVar3 != 0) {
                    // WARNING: Could not recover jumptable at 0x80004af0. Too many branches
                    // WARNING: Treating indirect jump as call
      (*UNRECOVERED_JUMPTABLE)();
      return;
    }
    iVar3 = 4;
    if (iStack112 == 0) {
LAB_80004b78:
      iStack112 = 0;
      if (iVar3 != 0) {
        if (iVar3 != 4) {
                    // WARNING: Could not recover jumptable at 0x80004b90. Too many branches
                    // WARNING: Treating indirect jump as call
          (*UNRECOVERED_JUMPTABLE)();
          return;
        }
        goto LAB_80004b94;
      }
    }
    else {
      do {
        iVar3 = FUN_80005f60(pcVar1,iStack112);
        if (iVar3 != 0) goto LAB_80004b78;
        bVar2 = *pbStack108;
        if (bVar2 == 0) {
          iVar3 = 4;
          goto LAB_80004b78;
        }
        bStack130 = pbStack108[0xb] & 0x3f;
        if (bVar2 != 0xe5 && bVar2 != 0x2e) {
          if (bStack130 != 0xf) {
            bVar2 = pbStack108[0xb] & 0x1f;
          }
          if (bStack130 != 0xf && bVar2 != 8) break;
        }
        iVar3 = FUN_80003a90(&uStack136,0);
        if (iVar3 != 0) goto LAB_80004b78;
      } while (iStack112 != 0);
    }
  }
                    // WARNING: Could not recover jumptable at 0x80004a90. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE)(7);
  return;
}



undefined4 FUN_80004c10(byte **param_1,char **param_2,uint param_3)

{
  byte bVar1;
  char cVar2;
  ushort uVar3;
  undefined *puVar4;
  uint uVar5;
  int iVar6;
  char *pcVar7;
  short sVar8;
  char *pcVar9;
  byte *pbVar10;
  char *pcVar12;
  uint uVar13;
  int iVar14;
  char cVar15;
  uint uVar16;
  byte *pbVar17;
  bool bVar18;
  int aiStack56 [4];
  uint uStack40;
  byte *pbVar11;
  
  *param_2 = (char *)0x0;
  pbVar17 = *param_1;
  pbVar11 = pbVar17;
  if (pbVar17 != (byte *)0x0) {
    do {
      pbVar10 = pbVar11 + 1;
      bVar1 = *pbVar11;
      if (bVar1 < 0x21) {
        uVar13 = 0;
        goto LAB_80004c88;
      }
      pbVar11 = pbVar10;
    } while (bVar1 != 0x3a);
    uVar13 = *pbVar17 - 0x30;
    bVar18 = uVar13 == 9;
    if (uVar13 < 10) {
      bVar18 = pbVar17 + 2 == pbVar10;
    }
    if (((bVar18) && ((int)uVar13 < 1)) && (*param_1 = pbVar10, -1 < (int)uVar13)) {
LAB_80004c88:
      pcVar12 = *(char **)(PTR_DAT_800050cc + uVar13 * 4);
      if (pcVar12 == (char *)0x0) {
        return 0xc;
      }
      *param_2 = pcVar12;
      if ((*pcVar12 == '\0') || (uVar5 = FUN_80004044(pcVar12[1]), (uVar5 & 1) != 0)) {
        *pcVar12 = '\0';
        pcVar12[1] = (char)uVar13;
        uVar13 = FUN_80003e8c();
        if ((uVar13 & 1) != 0) {
          return 3;
        }
        bVar18 = (param_3 & 0xfe) == 0;
        if (!bVar18) {
          bVar18 = (uVar13 & 4) == 0;
        }
        if (bVar18) {
          iVar14 = 0;
          *(undefined4 *)(pcVar12 + 0x2c) = 0xffffffff;
          pcVar12[3] = '\0';
          iVar6 = FUN_80005f60(pcVar12,0);
          if (iVar6 != 0) {
            return 1;
          }
          if (*(short *)(pcVar12 + 0x22e) == -0x55ab) {
            cVar15 = pcVar12[0x30];
            if ((cVar15 == -0x17 || cVar15 == -0x15) || cVar15 == -0x18) {
              iVar6 = 3;
              pcVar7 = &DAT_800050d0;
              pcVar9 = pcVar12 + 0x66;
              do {
                cVar15 = *pcVar9;
                cVar2 = *pcVar7;
                iVar6 = iVar6 + -1;
                if (iVar6 == 0) {
                  if (cVar15 == cVar2) goto LAB_80004ea8;
                  break;
                }
                pcVar7 = pcVar7 + 1;
                pcVar9 = pcVar9 + 1;
              } while (cVar15 == cVar2);
              iVar6 = 5;
              pcVar7 = &DAT_800050d4;
              pcVar9 = pcVar12 + 0x82;
              do {
                cVar15 = *pcVar9;
                cVar2 = *pcVar7;
                iVar6 = iVar6 + -1;
                if (iVar6 == 0) {
                  if (cVar15 == cVar2) goto LAB_80004ea8;
                  break;
                }
                pcVar7 = pcVar7 + 1;
                pcVar9 = pcVar9 + 1;
              } while (cVar15 == cVar2);
            }
            uVar13 = 0;
            do {
              if ((pcVar12 + uVar13 * 0x10)[0x1f2] == '\0') {
                iVar6 = 0;
              }
              else {
                iVar6 = *(int *)(pcVar12 + uVar13 * 0x10 + 0x1f6);
              }
              aiStack56[uVar13] = iVar6;
              uVar13 = uVar13 + 1;
            } while (uVar13 < 4);
            uVar13 = 0;
            do {
              iVar14 = aiStack56[uVar13];
              if (iVar14 == 0) {
LAB_80004e88:
                uVar5 = 3;
              }
              else {
                pcVar12[3] = '\0';
                *(undefined4 *)(pcVar12 + 0x2c) = 0xffffffff;
                iVar6 = FUN_80005f60(pcVar12,iVar14);
                if (iVar6 == 0) {
                  if (*(short *)(pcVar12 + 0x22e) != -0x55ab) goto LAB_80004e88;
                  cVar15 = pcVar12[0x30];
                  if ((cVar15 == -0x17 || cVar15 == -0x15) || cVar15 == -0x18) {
                    iVar6 = 3;
                    pcVar7 = &DAT_800050d0;
                    pcVar9 = pcVar12 + 0x66;
                    do {
                      cVar15 = *pcVar9;
                      cVar2 = *pcVar7;
                      iVar6 = iVar6 + -1;
                      if (iVar6 == 0) {
                        if (cVar15 == cVar2) goto LAB_80004ea8;
                        break;
                      }
                      pcVar7 = pcVar7 + 1;
                      pcVar9 = pcVar9 + 1;
                    } while (cVar15 == cVar2);
                    iVar6 = 5;
                    pcVar7 = &DAT_800050d4;
                    pcVar9 = pcVar12 + 0x82;
                    do {
                      cVar15 = *pcVar9;
                      cVar2 = *pcVar7;
                      iVar6 = iVar6 + -1;
                      if (iVar6 == 0) {
                        if (cVar15 == cVar2) goto LAB_80004ea8;
                        break;
                      }
                      pcVar7 = pcVar7 + 1;
                      pcVar9 = pcVar9 + 1;
                    } while (cVar15 == cVar2);
                  }
                  uVar5 = 2;
                }
                else {
                  uVar5 = 4;
                }
              }
              uVar13 = uVar13 + 1;
            } while (uVar13 < 4);
            if (uVar5 == 4) {
              return 1;
            }
            if (uVar5 < 2) {
LAB_80004ea8:
              if (*(short *)(pcVar12 + 0x3b) == 0x200) {
                uStack40 = (uint)*(ushort *)(pcVar12 + 0x46);
                if (uStack40 == 0) {
                  uStack40 = *(uint *)(pcVar12 + 0x54);
                }
                uVar13 = (uint)(byte)pcVar12[0x40];
                *(uint *)(pcVar12 + 0x18) = uStack40;
                pcVar12[2] = pcVar12[0x40];
                if (uVar13 == 1 || uVar13 == 2) {
                  bVar1 = pcVar12[0x3d];
                  iVar6 = uVar13 * uStack40;
                  *(ushort *)(pcVar12 + 10) = (ushort)bVar1;
                  if ((bVar1 != 0) && ((bVar1 & bVar1 - 1) == 0)) {
                    uVar3 = *(ushort *)(pcVar12 + 0x41);
                    *(ushort *)(pcVar12 + 8) = uVar3;
                    if ((uVar3 & 0xf) == 0) {
                      uVar13 = (uint)*(ushort *)(pcVar12 + 0x43);
                      if (uVar13 == 0) {
                        uVar13 = *(uint *)(pcVar12 + 0x50);
                      }
                      uVar5 = (uint)*(ushort *)(pcVar12 + 0x3e);
                      if (((uVar5 != 0) &&
                          (uVar16 = uVar5 + iVar6 + (uint)(uVar3 >> 4), uVar16 <= uVar13)) &&
                         (uVar13 = FUN_80000928(uVar13 - uVar16), uVar13 != 0)) {
                        cVar15 = '\0';
                        if (uVar13 < 0xffffff6) {
                          cVar15 = '\x03';
                        }
                        if (uVar13 <= DAT_800050dc) {
                          cVar15 = '\x02';
                        }
                        if (DAT_800050e0 < uVar13) {
                          if (cVar15 == '\0') {
                            return 0xd;
                          }
                        }
                        else {
                          cVar15 = '\x01';
                        }
                        uVar13 = uVar13 + 2;
                        *(uint *)(pcVar12 + 0x14) = uVar13;
                        *(uint *)(pcVar12 + 0x20) = iVar14 + uVar5;
                        *(uint *)(pcVar12 + 0x28) = iVar14 + uVar16;
                        *(int *)(pcVar12 + 0x1c) = iVar14;
                        if (cVar15 == '\x03') {
                          if (*(short *)(pcVar12 + 0x5a) != 0 || uVar3 != 0) {
                            return 0xd;
                          }
                          iVar6 = uVar13 * 4;
                          *(undefined4 *)(pcVar12 + 0x24) = *(undefined4 *)(pcVar12 + 0x5c);
                        }
                        else {
                          if (uVar3 == 0) {
                            return 0xd;
                          }
                          *(uint *)(pcVar12 + 0x24) = iVar14 + uVar5 + iVar6;
                          if (cVar15 == '\x02') {
                            iVar6 = uVar13 * 2;
                          }
                          else {
                            iVar6 = (uVar13 & 1) + (uVar13 * 3 >> 1);
                          }
                        }
                        if (iVar6 + 0x1ffU >> 9 <= uStack40) {
                          pcVar12[4] = -0x80;
                          *(undefined4 *)(pcVar12 + 0x10) = 0xffffffff;
                          *(undefined4 *)(pcVar12 + 0xc) = 0xffffffff;
                          if ((((cVar15 == '\x03') && (*(short *)(pcVar12 + 0x60) == 1)) &&
                              ((iVar6 = FUN_80005f60(pcVar12,iVar14 + 1), iVar6 == 0 &&
                               ((pcVar12[4] = '\0', *(short *)(pcVar12 + 0x22e) == -0x55ab &&
                                (*(int *)(pcVar12 + 0x30) == DAT_8000523c)))))) &&
                             (*(int *)(pcVar12 + 0x214) == DAT_80005240)) {
                            *(undefined4 *)(pcVar12 + 0x10) = *(undefined4 *)(pcVar12 + 0x218);
                            *(undefined4 *)(pcVar12 + 0xc) = *(undefined4 *)(pcVar12 + 0x21c);
                          }
                          puVar4 = PTR_DAT_80005244;
                          *pcVar12 = cVar15;
                          sVar8 = *(short *)puVar4 + 1;
                          *(short *)puVar4 = sVar8;
                          *(short *)(pcVar12 + 6) = sVar8;
                          return 0;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
          return 0xd;
        }
      }
      else {
        bVar18 = (param_3 & 0xfe) == 0;
        if (!bVar18) {
          bVar18 = (uVar5 & 4) == 0;
        }
        if (bVar18) {
          return 0;
        }
      }
      return 10;
    }
  }
  return 0xb;
}



undefined4 FUN_80005248(int param_1,int param_2)

{
  undefined *puVar1;
  uint uVar2;
  
  puVar1 = PTR_DAT_80005288;
  uVar2 = (param_1 + param_2) - 1;
  if (*(uint *)(PTR_DAT_80005288 + 0xc) < uVar2) {
    FUN_8000705c(PTR_s_ERROR__Fail_to_access_invalid_se_8000528c,uVar2);
    FUN_8000705c(s__The_max_valid_sector_number_for_80005290,*(undefined4 *)(puVar1 + 0xc));
    return DAT_800052d0;
  }
  return 0;
}



// WARNING (jumptable): Heritage AFTER dead removal. Example location: s0xfffffffc : 0x800053f8
// WARNING: Restarted to delay deadcode elimination for space: stack

undefined4 FUN_800052d4(byte **param_1,byte *param_2)

{
  byte bVar1;
  short sVar2;
  ushort uVar3;
  undefined uVar4;
  byte bVar5;
  byte *pbVar6;
  uint uVar7;
  int iVar8;
  undefined4 uVar9;
  int iVar10;
  byte **ppbVar11;
  byte *pbVar12;
  byte *pbVar13;
  uint uVar14;
  uint uVar15;
  code *UNRECOVERED_JUMPTABLE;
  bool bVar16;
  
  pbVar13 = *param_1;
  while (*param_2 == 0x2f || *param_2 == 0x5c) {
    param_2 = param_2 + 1;
  }
  param_1[2] = (byte *)0x0;
  if (0x1f < *param_2) {
LAB_80005334:
    ppbVar11 = param_1 + 8;
    FUN_80005868(ppbVar11,0x20,0xb);
    uVar15 = 0;
    uVar14 = 8;
    iVar8 = 0;
    while( true ) {
      bVar5 = param_2[iVar8];
      uVar7 = (uint)bVar5;
      iVar10 = iVar8 + 1;
      if (uVar7 < 0x21) break;
      if (uVar7 == 0x2f || uVar7 == 0x5c) goto LAB_80005384;
      if (uVar7 == 0x2e) {
        if (uVar14 == 0xb) {
          return 6;
        }
        uVar15 = 8;
        uVar14 = 0xb;
        iVar8 = iVar10;
      }
      else {
        if (uVar14 <= uVar15) {
          return 6;
        }
        if ((uVar7 < 0x81) || (0xfe < uVar7)) {
          pbVar12 = &DAT_800055a4;
          while (*pbVar12 != 0) {
            if (*pbVar12 == uVar7) {
              return 6;
            }
            pbVar12 = pbVar12 + 1;
          }
          if (uVar7 - 0x61 < 0x1a) {
            bVar5 = bVar5 - 0x20;
          }
          *(byte *)((int)ppbVar11 + uVar15) = bVar5;
          uVar15 = uVar15 + 1;
          iVar8 = iVar10;
        }
        else {
          bVar1 = param_2[iVar10];
          uVar7 = (uint)bVar1;
          if (uVar7 < 0x40) {
            return 6;
          }
          if (0x7e < uVar7) {
            uVar7 = uVar7 - 0x80;
          }
          bVar16 = 0x7d < uVar7;
          if (uVar7 < 0x7f) {
            bVar16 = uVar14 - 1 <= uVar15;
          }
          if (bVar16) {
            return 6;
          }
          *(byte *)((int)ppbVar11 + uVar15) = bVar5;
          iVar10 = uVar15 + 1;
          uVar15 = uVar15 + 2;
          *(byte *)((int)ppbVar11 + iVar10) = bVar1;
          iVar8 = iVar8 + 2;
        }
      }
    }
    goto LAB_80005398;
  }
  *(undefined *)((int)param_1 + 0x2b) = 0x80;
  pbVar13 = param_1[2];
  param_1[4] = (byte *)0x0;
  pbVar12 = *param_1;
  if ((pbVar13 == (byte *)0x0) &&
     ((*pbVar12 < 3 || (pbVar13 = *(byte **)(pbVar12 + 0x24), pbVar13 == (byte *)0x0)))) {
    if (*(short *)(pbVar12 + 8) != 0) {
      pbVar6 = *(byte **)(pbVar12 + 0x24);
      param_1[6] = pbVar6;
LAB_80003e2c:
      param_1[5] = pbVar13;
      if (pbVar6 != (byte *)0x0) {
        param_1[6] = pbVar6;
        param_1[7] = pbVar12 + 0x30;
        return 0;
      }
    }
  }
  else {
    sVar2 = *(short *)(pbVar12 + 10);
    do {
      if (sVar2 != 0) {
        if (pbVar13 + -2 < (byte *)(*(int *)(pbVar12 + 0x14) + -2)) {
          pbVar6 = (byte *)((uint)*(ushort *)(pbVar12 + 10) * (int)(pbVar13 + -2) +
                           *(int *)(pbVar12 + 0x28));
        }
        else {
          pbVar6 = (byte *)0x0;
        }
        param_1[6] = pbVar6;
        goto LAB_80003e2c;
      }
      pbVar13 = (byte *)FUN_800055b4(param_1);
      if (pbVar13 == (byte *)0xffffffff) {
        return 1;
      }
      bVar16 = pbVar13 == (byte *)0x2;
      pbVar6 = pbVar13;
      if ((byte *)0x1 < pbVar13) {
        pbVar6 = *(byte **)(pbVar12 + 0x14);
        bVar16 = pbVar6 == pbVar13;
      }
    } while (((byte *)0x1 < pbVar13 && pbVar13 <= pbVar6) && !bVar16);
  }
  return 2;
LAB_80005384:
  while (param_2[iVar10] == 0x2f || param_2[iVar10] == 0x5c) {
    iVar10 = iVar10 + 1;
  }
LAB_80005398:
  param_2 = param_2 + iVar10;
  if (uVar15 == 0) {
    return 6;
  }
  if (*(char *)ppbVar11 == -0x1b) {
    *(undefined *)ppbVar11 = 5;
  }
  if (uVar7 < 0x21) {
    uVar4 = 4;
  }
  else {
    uVar4 = 0;
  }
  *(undefined *)((int)param_1 + 0x2b) = uVar4;
  pbVar12 = *param_1;
  iVar8 = FUN_80003d84(param_1,0);
  if (iVar8 == 0) {
    while (iVar8 = FUN_80005f60(pbVar12,param_1[6]), iVar8 == 0) {
      pbVar6 = param_1[7];
      if (*pbVar6 == 0) {
        iVar8 = 4;
        break;
      }
      *(byte *)((int)param_1 + 6) = pbVar6[0xb] & 0x3f;
      if ((pbVar6[0xb] & 8) == 0) {
        iVar10 = 0xb;
        ppbVar11 = param_1 + 8;
        do {
          bVar5 = *pbVar6;
          bVar1 = *(byte *)ppbVar11;
          iVar10 = iVar10 + -1;
          if (iVar10 == 0) {
            if (bVar5 == bVar1) goto LAB_80005514;
            break;
          }
          pbVar6 = pbVar6 + 1;
          ppbVar11 = (byte **)((int)ppbVar11 + 1);
        } while (bVar5 == bVar1);
      }
      iVar8 = FUN_80003a90(param_1,0);
      if (iVar8 != 0) break;
    }
  }
LAB_80005514:
  if (iVar8 != 0) {
    bVar16 = iVar8 == 4;
    if (bVar16) {
      bVar16 = (*(byte *)((int)param_1 + 0x2b) & 4) == 0;
    }
    if (!bVar16) {
                    // WARNING: Could not recover jumptable at 0x80005530. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar9 = (*UNRECOVERED_JUMPTABLE)();
      return uVar9;
    }
LAB_80005534:
                    // WARNING: Could not recover jumptable at 0x80005540. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar9 = (*UNRECOVERED_JUMPTABLE)(5);
    return uVar9;
  }
  if ((*(byte *)((int)param_1 + 0x2b) & 4) != 0) {
                    // WARNING: Could not recover jumptable at 0x80005550. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar9 = (*UNRECOVERED_JUMPTABLE)();
    return uVar9;
  }
  if ((*(byte *)((int)param_1 + 6) & 0x10) == 0) goto LAB_80005534;
  pbVar12 = pbVar13 + (*(ushort *)(param_1 + 4) & 0x1ff);
  uVar3 = *(ushort *)(pbVar12 + 0x4a);
  pbVar6 = (byte *)(uint)uVar3;
  if (*pbVar13 == 3) {
    pbVar6 = (byte *)CONCAT22(*(undefined2 *)(pbVar12 + 0x44),uVar3);
  }
  param_1[2] = pbVar6;
  goto LAB_80005334;
}



uint FUN_800055b4(char **param_1,char **param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  uint uVar4;
  bool bVar5;
  
  pcVar3 = *param_1;
  bVar5 = param_2 == (char **)0x2;
  if ((char **)0x1 < param_2) {
    param_1 = *(char ***)(pcVar3 + 0x14);
    bVar5 = param_1 == param_2;
  }
  if (((char **)0x1 < param_2 && param_2 <= param_1) && !bVar5) {
    cVar1 = *pcVar3;
    if (cVar1 == '\x01') {
      uVar4 = (int)param_2 + ((uint)param_2 >> 1);
      iVar2 = FUN_80005f60(pcVar3,*(int *)(pcVar3 + 0x20) + (uVar4 >> 9));
      if (iVar2 != 0) {
        return 0xffffffff;
      }
      cVar1 = pcVar3[(uVar4 & 0x1ff) + 0x30];
      iVar2 = FUN_80005f60(pcVar3,*(int *)(pcVar3 + 0x20) + (uVar4 + 1 >> 9));
      if (iVar2 != 0) {
        return 0xffffffff;
      }
      if (((uint)param_2 & 1) == 0) {
        return CONCAT11(pcVar3[(uVar4 + 1 & 0x1ff) + 0x30],cVar1) & 0xffff0fff;
      }
      return (uint)(ushort)(CONCAT11(pcVar3[(uVar4 + 1 & 0x1ff) + 0x30],cVar1) >> 4);
    }
    if (cVar1 == '\x02') {
      iVar2 = FUN_80005f60(pcVar3,*(int *)(pcVar3 + 0x20) + ((uint)param_2 >> 8));
      if (iVar2 != 0) {
        return 0xffffffff;
      }
      return (uint)*(ushort *)(pcVar3 + ((uint)param_2 & 0xff) * 2 + 0x30);
    }
    if (cVar1 == '\x03') {
      iVar2 = FUN_80005f60(pcVar3,*(int *)(pcVar3 + 0x20) + ((uint)param_2 >> 7));
      if (iVar2 != 0) {
        return 0xffffffff;
      }
      return *(uint *)(pcVar3 + ((uint)param_2 & 0x7f) * 4 + 0x30) & 0xfffffff;
    }
  }
  return 1;
}



undefined4 FUN_800056e8(void)

{
  return DAT_800056f0;
}



void FUN_80005754(int param_1,undefined4 param_2,uint param_3,int param_4,uint param_5,
                 undefined4 param_6,uint param_7,uint param_8,uint param_9)

{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  
  uVar1 = param_3 >> 0x14 | param_4 << 0xc;
  param_5 = param_5 >> 0x14;
  uVar2 = param_7 >> 0x14 | param_8 << 0xc;
  param_8 = param_8 >> 0x14;
  while ((param_8 | uVar2) != 0) {
    *(uint *)(param_1 + uVar1 * 4) = param_5 << 0x14 | 0xc10 | (param_9 & 3) << 2 | 2;
    bVar3 = uVar2 == 0;
    uVar2 = uVar2 - 1;
    param_8 = param_8 - bVar3;
    uVar1 = uVar1 + 1;
    param_5 = param_5 + 1;
  }
  return;
}



void FUN_800057f4(undefined *param_1,undefined *param_2,uint param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  int iVar3;
  
  if (param_3 == 0) {
    return;
  }
  if (0x7fffffff < param_3) {
    do {
      param_3 = param_3 - 1;
      *param_1 = *param_2;
      param_1 = param_1 + 1;
      param_2 = param_2 + 1;
    } while (param_3 != 0);
    return;
  }
  if ((int)param_3 < 2) {
    param_3 = 1;
  }
  else {
    if ((int)param_3 < 1) {
      return;
    }
  }
  puVar1 = param_1 + -1;
  puVar2 = param_2 + -1;
  if ((param_3 & 1) != 0) {
    *param_1 = *param_2;
    puVar1 = param_1;
    puVar2 = param_2;
  }
  iVar3 = (int)param_3 >> 1;
  if (iVar3 != 0) {
    do {
      iVar3 = iVar3 + -1;
      puVar1[1] = puVar2[1];
      puVar2 = puVar2 + 2;
      puVar1 = puVar1 + 2;
      *puVar1 = *puVar2;
    } while (iVar3 != 0);
    return;
  }
  return;
}



void FUN_80005868(undefined *param_1,undefined param_2,uint param_3)

{
  undefined *puVar1;
  int iVar2;
  
  if (0x7fffffff < param_3) {
    do {
      param_3 = param_3 - 1;
      *param_1 = param_2;
      param_1 = param_1 + 1;
    } while (param_3 != 0);
    return;
  }
  if ((int)param_3 < 2) {
    param_3 = 1;
  }
  puVar1 = param_1 + -1;
  if ((param_3 & 1) != 0) {
    *param_1 = param_2;
    puVar1 = param_1;
  }
  iVar2 = (int)param_3 >> 1;
  if (iVar2 == 0) {
    return;
  }
  do {
    puVar1[1] = param_2;
    iVar2 = iVar2 + -1;
    puVar1 = puVar1 + 2;
    *puVar1 = param_2;
  } while (iVar2 != 0);
  return;
}



// WARNING (jumptable): Heritage AFTER dead removal. Example location: s0xfffffffc : 0x8000595c
// WARNING: Restarted to delay deadcode elimination for space: stack

undefined4 FUN_800058b4(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  code *UNRECOVERED_JUMPTABLE;
  
  iVar2 = DAT_8000596c;
  iVar5 = DAT_8000596c + 0x1000;
  iVar4 = DAT_8000596c;
  if ((param_1 != 0) && (iVar4 = iVar5, param_1 != 1)) {
    iVar4 = 0;
  }
  iVar1 = DAT_8000596c;
  if ((param_1 != 0) && (iVar1 = iVar5, param_1 != 1)) {
    iVar1 = 0;
  }
  *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) & 0xfffeffff;
  iVar1 = FUN_80005eec();
  if ((iVar1 == 0) && (iVar1 = FUN_80005a08(param_1,param_2), iVar1 == 0)) {
    *(uint *)(iVar4 + 4) = *(uint *)(iVar4 + 4) & 0xffffff00;
    if ((param_1 != 0) && (iVar2 = iVar5, param_1 != 1)) {
      iVar2 = 0;
    }
    *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 0x10000;
    iVar2 = FUN_80005eec();
    if (iVar2 == 0) {
                    // WARNING: Could not recover jumptable at 0x8000595c. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
  }
  return 0xffffffff;
}



undefined4 FUN_80005a08(int param_1,uint param_2)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  undefined8 uVar9;
  
  if (DAT_80005bb8 < param_2) {
    uVar8 = 0x1000000;
    FUN_8000705c(DAT_80005bc0,DAT_80005bbc);
    puVar1 = DAT_80005bc4;
    *DAT_80005bc4 = *DAT_80005bc4 & 0x7fffffff;
    *puVar1 = *puVar1 & 0xfffff000;
    *puVar1 = *puVar1 | 0x1700;
    *puVar1 = *puVar1 | 0x80000000;
    uVar2 = *puVar1;
    uVar2 = FUN_8000052c(DAT_80005bb8 *
                         (int)(short)((ushort)((uVar2 << 0x13) >> 0x1b) + 1) *
                         (int)(short)((ushort)((uVar2 << 0x1a) >> 0x1e) + 1),(uVar2 & 3) + 1);
    FUN_8000705c(s_pll_hz___d_hz_80005bc8,uVar2);
  }
  else {
    uVar8 = 0;
    uVar2 = DAT_80005bb8;
  }
  uVar9 = FUN_80000928(uVar2,param_2);
  uVar7 = (uint)uVar9;
  if ((int)((ulonglong)uVar9 >> 0x20) != 0) {
    uVar7 = uVar7 + 1;
  }
  uVar3 = 0;
  if (0x10 < uVar7) {
    do {
      uVar7 = uVar7 + 1 >> 1;
      uVar3 = uVar3 + 1;
    } while (0x10 < uVar7);
    if (3 < uVar3) {
      FUN_8000705c(s_mmc__u_error_cannot_set_clock_to_80005bd8,param_1,param_2);
      return 0xffffffff;
    }
  }
  if (DAT_80005c00 < param_2) {
    if (DAT_80005c04 < param_2) {
      if (DAT_80005c08 < param_2) {
        iVar6 = 1;
      }
      else {
        iVar6 = 3;
      }
      iVar5 = 4;
    }
    else {
      iVar6 = 0;
      iVar5 = 5;
    }
  }
  else {
    iVar5 = 0;
    iVar6 = iVar5;
  }
  *(uint *)(DAT_80005c0c + param_1 * 4) =
       uVar7 - 1 | uVar8 | iVar5 << 0x14 | uVar3 << 0x10 | iVar6 << 8 | 0x80000000;
  iVar6 = 1 << (uVar3 & 0xff);
  uVar4 = FUN_80000928(uVar2,iVar6);
  uVar4 = FUN_80000928(uVar4,uVar7);
  FUN_8000705c(PTR_s_mmc__u_set__mod_clk_req__u___par_80005c10,param_1,param_2,uVar2,iVar6,uVar7,
               uVar4);
  return 0;
}



undefined4 FUN_80005c14(int param_1,int *param_2)

{
  byte bVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  bool bVar8;
  
  bVar1 = *(byte *)(param_2 + 1);
  iVar6 = *param_2;
  uVar5 = param_2[3] * param_2[2];
  if ((bVar1 & 1) == 0) {
    uVar7 = 8;
  }
  else {
    uVar7 = 4;
  }
  uVar4 = (uVar5 >> 8) * 1000;
  puVar2 = DAT_80005d00;
  if ((param_1 != 0) && (puVar2 = DAT_80005d04, param_1 != 1)) {
    puVar2 = (uint *)0x0;
  }
  if (uVar4 < DAT_80005d08) {
    uVar4 = DAT_80005d08;
  }
  *puVar2 = *puVar2 | 0x80000000;
  uVar3 = 0;
  if (uVar5 >> 2 != 0) {
    do {
      while ((puVar2[0xf] & uVar7) != 0) {
        bVar8 = uVar4 == 0;
        uVar4 = uVar4 - 1;
        if (bVar8) {
          FUN_8000705c(s_Data__d__timeout_BIT_0x_08x____80005d0c,uVar3,puVar2[0xf]);
          return 0xffffffff;
        }
        FUN_80001118(5);
      }
      if ((bVar1 & 1) == 0) {
        puVar2[0x80] = *(uint *)(iVar6 + uVar3 * 4);
      }
      else {
        *(uint *)(iVar6 + uVar3 * 4) = puVar2[0x80];
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < uVar5 >> 2);
  }
  return 0;
}



undefined4 FUN_80005d30(int param_1,uint *param_2,uint param_3)

{
  uint uVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  undefined2 uVar7;
  uint *puVar8;
  
  uVar3 = (int)(uint *)param_2[2] * param_2[3];
  puVar8 = (uint *)param_2[2];
  if (param_1 == 0) {
    puVar8 = DAT_80005ee0;
  }
  iVar5 = 0;
  if ((param_1 != 0) && (puVar8 = DAT_80005ee4, param_1 != 1)) {
    puVar8 = (uint *)0x0;
  }
  uVar7 = (undefined2)(uVar3 & 0xfff);
  uVar4 = uVar3 >> 0xc;
  if ((uVar3 & 0xfff) == 0) {
    uVar7 = 0x1000;
  }
  else {
    uVar4 = uVar4 + 1;
  }
  uVar6 = *param_2;
  if (uVar4 < 0x101) {
    uVar1 = uVar6 & 0xffffffe0;
    while (uVar1 <= (uVar3 + uVar6 & 0xffffffe0)) {
      coproc_moveto_Invalidate_Data_Cache_by_MVA(uVar1);
      coproc_moveto_Invalidate_Instruction_Cache_by_MVA(uVar1);
      uVar1 = uVar1 + 0x20;
    }
    uVar3 = 0;
    if (uVar4 != 0) {
      do {
        puVar2 = (uint *)(param_3 + iVar5 * 0x10);
        puVar2[1] = 0;
        puVar2[2] = 0;
        puVar2[3] = 0;
        *puVar2 = (uint)&DAT_80000012;
        if ((uVar4 < 2) || (uVar3 == uVar4 - 1)) {
          *(undefined2 *)(puVar2 + 1) = uVar7;
        }
        else {
          *(undefined2 *)(puVar2 + 1) = 0x1000;
        }
        puVar2[2] = uVar6 + uVar3 * 0x1000;
        if (uVar3 == 0) {
          *puVar2 = (uint)&DAT_8000001a;
        }
        if (uVar3 == uVar4 - 1) {
          *puVar2 = *puVar2 & 0xfffffffd | 0x24;
        }
        else {
          puVar2[3] = (uint)(puVar2 + 4);
        }
        uVar3 = uVar3 + 1;
        iVar5 = iVar5 + 1;
      } while (uVar3 < uVar4);
    }
    uVar3 = param_3 & 0xffffffe0;
    while (uVar3 <= (param_3 + iVar5 * 0x10 + 0x10 & 0xffffffe0)) {
      coproc_moveto_Invalidate_Data_Cache_by_MVA(uVar3);
      coproc_moveto_Invalidate_Instruction_Cache_by_MVA(uVar3);
      uVar3 = uVar3 + 0x20;
    }
    *puVar8 = *puVar8 & 0x7fffffff;
    *puVar8 = *puVar8 | 0x24;
    puVar8[0x20] = 1;
    do {
    } while ((puVar8[0x20] & 1) != 0);
    puVar8[0x20] = 0x82;
    if ((*(byte *)(param_2 + 1) & 2) == 0) {
      uVar3 = puVar8[0x23] & 0xfffffffc | 2;
    }
    else {
      uVar3 = puVar8[0x23] & 0xfffffffc | 1;
    }
    puVar8[0x23] = uVar3;
    puVar8[0x21] = param_3;
    puVar8[0x10] = DAT_80005ee8;
    return 0;
  }
  return 0xffffffff;
}



undefined4 FUN_80005eec(int param_1)

{
  int unaff_r4;
  int iVar1;
  bool bVar2;
  
  if (param_1 == 0) {
    unaff_r4 = DAT_80005f44;
  }
  iVar1 = 2000;
  if ((param_1 != 0) && (unaff_r4 = DAT_80005f48, param_1 != 1)) {
    unaff_r4 = 0;
  }
  *(uint *)(unaff_r4 + 0x18) = DAT_80005f4c;
  while( true ) {
    if ((*(uint *)(unaff_r4 + 0x18) & 0x80000000) == 0) {
      return 0;
    }
    bVar2 = iVar1 == 0;
    iVar1 = iVar1 + -1;
    if (bVar2) break;
    FUN_80001118(5);
  }
  FUN_8000705c(s_timeout____80005f50);
  return 0xffffffff;
}



bool FUN_80005f60(int param_1,int param_2)

{
  int iVar1;
  bool bVar2;
  
  bVar2 = false;
  if (*(int *)(param_1 + 0x2c) != param_2) {
    if (*(char *)(param_1 + 3) != '\0') {
      iVar1 = FUN_8000404c(*(undefined *)(param_1 + 1),param_1 + 0x30,*(int *)(param_1 + 0x2c),1);
      bVar2 = iVar1 != 0;
      if (bVar2) {
        return bVar2;
      }
      *(undefined *)(param_1 + 3) = 0;
      if (((uint)(*(int *)(param_1 + 0x2c) - *(int *)(param_1 + 0x20)) < *(uint *)(param_1 + 0x18))
         && (*(char *)(param_1 + 2) == '\x02')) {
        FUN_8000404c(*(undefined *)(param_1 + 1),param_1 + 0x30,
                     *(int *)(param_1 + 0x2c) + *(uint *)(param_1 + 0x18),1);
      }
    }
    iVar1 = FUN_80003f88(*(undefined *)(param_1 + 1),param_1 + 0x30,param_2,1);
    if (iVar1 != 0) {
      param_2 = -1;
      bVar2 = true;
    }
    *(int *)(param_1 + 0x2c) = param_2;
  }
  return bVar2;
}



void FUN_80006010(char *param_1,uint param_2,uint param_3)

{
  char cVar1;
  int iVar2;
  byte extraout_r1;
  byte bVar3;
  byte bVar4;
  uint uVar5;
  char *pcVar6;
  uint uVar7;
  char *unaff_r4;
  uint unaff_r5;
  uint uVar8;
  uint unaff_r6;
  code **ppcVar9;
  bool bVar10;
  bool bVar11;
  undefined auStack4 [4];
  
  ppcVar9 = (code **)&stack0xffffffe8;
  bVar11 = 1 < param_2;
  bVar10 = param_2 == 2;
  uVar5 = param_2;
  if (bVar11) {
    uVar5 = *(uint *)(param_1 + 0x14);
    bVar10 = uVar5 == param_2;
  }
  uVar8 = param_2;
  uVar7 = param_3;
  if ((!bVar11 || uVar5 < param_2) || bVar10) {
    ppcVar9 = (code **)auStack4;
    param_1 = unaff_r4;
    uVar8 = unaff_r5;
    uVar7 = unaff_r6;
  }
                    // WARNING: Could not recover jumptable at 0x80006038. Too many branches
                    // WARNING: Treating indirect jump as call
  if ((!bVar11 || uVar5 < param_2) || bVar10) {
    (**ppcVar9)();
    return;
  }
  cVar1 = *param_1;
  bVar4 = (byte)uVar7;
  if (cVar1 == '\x01') {
    uVar5 = uVar8 + (uVar8 >> 1);
    iVar2 = FUN_80005f60(param_1,*(int *)(param_1 + 0x20) + (uVar5 >> 9));
    if (iVar2 != 0) {
                    // WARNING: Could not recover jumptable at 0x800060f4. Too many branches
                    // WARNING: Treating indirect jump as call
      (*ppcVar9[5])();
      return;
    }
    bVar10 = (uVar8 & 1) != 0;
    bVar3 = extraout_r1;
    if (bVar10) {
      bVar3 = param_1[(uVar5 & 0x1ff) + 0x30];
    }
    if (bVar10) {
      bVar4 = bVar3 & 0xf | (byte)(uVar7 << 4);
    }
    param_1[(uVar5 & 0x1ff) + 0x30] = bVar4;
    param_1[3] = '\x01';
    iVar2 = FUN_80005f60(param_1,*(int *)(param_1 + 0x20) + (uVar5 + 1 >> 9));
    if (iVar2 != 0) {
                    // WARNING: Could not recover jumptable at 0x80006140. Too many branches
                    // WARNING: Treating indirect jump as call
      (*ppcVar9[5])();
      return;
    }
    bVar10 = (uVar8 & 1) != 0;
    if (bVar10) {
      param_3 = uVar7 << 0x14;
    }
    if (bVar10) {
      param_3 = param_3 >> 0x18;
    }
    bVar4 = (byte)param_3;
    if (!bVar10) {
      bVar4 = param_1[(uVar5 + 1 & 0x1ff) + 0x30] & 0xf0U | (byte)((uVar7 << 0x14) >> 0x1c);
    }
    param_1[(uVar5 + 1 & 0x1ff) + 0x30] = bVar4;
  }
  else {
    if (cVar1 != '\x02') {
      if (cVar1 != '\x03') {
                    // WARNING: Could not recover jumptable at 0x8000605c. Too many branches
                    // WARNING: Treating indirect jump as call
        (*ppcVar9[5])(2);
        return;
      }
      iVar2 = FUN_80005f60(param_1,*(int *)(param_1 + 0x20) + (uVar8 >> 7));
      if (iVar2 != 0) {
                    // WARNING: Could not recover jumptable at 0x80006078. Too many branches
                    // WARNING: Treating indirect jump as call
        (*ppcVar9[5])();
        return;
      }
      pcVar6 = param_1 + (uVar8 & 0x7f) * 4;
      uVar7 = uVar7 & 0xfffffff;
      pcVar6[0x30] = (char)uVar7;
      pcVar6[0x31] = (char)(uVar7 >> 8);
      pcVar6[0x32] = (char)(uVar7 >> 0x10);
      pcVar6[0x33] = pcVar6[0x33] & 0xf0U | (byte)(uVar7 >> 0x18);
      param_1[3] = '\x01';
                    // WARNING: Could not recover jumptable at 0x800060d4. Too many branches
                    // WARNING: Treating indirect jump as call
      (*ppcVar9[5])();
      return;
    }
    iVar2 = FUN_80005f60(param_1,*(int *)(param_1 + 0x20) + (uVar8 >> 8));
    if (iVar2 != 0) {
                    // WARNING: Could not recover jumptable at 0x80006194. Too many branches
                    // WARNING: Treating indirect jump as call
      (*ppcVar9[5])();
      return;
    }
    (param_1 + (uVar8 & 0xff) * 2)[0x30] = bVar4;
    (param_1 + (uVar8 & 0xff) * 2)[0x31] = (char)(uVar7 >> 8);
  }
  param_1[3] = '\x01';
                    // WARNING: Could not recover jumptable at 0x800061b4. Too many branches
                    // WARNING: Treating indirect jump as call
  (*ppcVar9[5])();
  return;
}



undefined4 FUN_800061b8(undefined4 *param_1)

{
  return *param_1;
}



// WARNING (jumptable): Heritage AFTER dead removal. Example location: s0xfffffffc : 0x80006210
// WARNING: Restarted to delay deadcode elimination for space: stack

undefined4 FUN_800061c8(int *param_1,int *param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  code *UNRECOVERED_JUMPTABLE_00;
  bool bVar5;
  
  iVar4 = *param_1;
  bVar5 = param_2 == (int *)0x2;
  piVar1 = param_1;
  if (param_2 >= (int *)0x2) {
    piVar1 = *(int **)(iVar4 + 0x14);
    bVar5 = piVar1 == param_2;
  }
  if ((param_2 < (int *)0x2 || piVar1 < param_2) || bVar5) {
    return 2;
  }
  if ((param_3 != 0) && (iVar2 = FUN_80006010(iVar4,param_3,0xffffffff), iVar2 != 0)) {
                    // WARNING: Could not recover jumptable at 0x80006210. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (*UNRECOVERED_JUMPTABLE_00)();
    return uVar3;
  }
  do {
    piVar1 = (int *)FUN_800055b4(param_1,param_2);
    if (piVar1 == (int *)0x0) break;
    if (piVar1 == (int *)0x1) {
      return 2;
    }
    if (piVar1 == (int *)0xffffffff) {
                    // WARNING: Could not recover jumptable at 0x800062a8. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE_00)(1);
      return uVar3;
    }
    iVar2 = FUN_80006010(iVar4,param_2,0);
    if (iVar2 != 0) {
                    // WARNING: Could not recover jumptable at 0x80006250. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE_00)();
      return uVar3;
    }
    if (*(uint *)(iVar4 + 0x10) < (int)*(int **)(iVar4 + 0x14) - 2U) {
      *(uint *)(iVar4 + 0x10) = *(uint *)(iVar4 + 0x10) + 1;
      *(byte *)(iVar4 + 4) = *(byte *)(iVar4 + 4) | 1;
    }
    param_2 = piVar1;
  } while (piVar1 < *(int **)(iVar4 + 0x14));
                    // WARNING: Could not recover jumptable at 0x80006290. Too many branches
                    // WARNING: Treating indirect jump as call
  uVar3 = (*UNRECOVERED_JUMPTABLE_00)(0);
  return uVar3;
}



// WARNING (jumptable): Heritage AFTER dead removal. Example location: s0xfffffffc : 0x80006828
// WARNING: Restarted to delay deadcode elimination for space: stack

void FUN_800067dc(int param_1,ushort *param_2,uint *param_3)

{
  uint uVar1;
  char *pcVar2;
  uint *puVar3;
  uint uVar4;
  uint *puVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  uint *puVar9;
  uint *puVar10;
  code *UNRECOVERED_JUMPTABLE_00;
  bool bVar11;
  bool bVar12;
  
  puVar9 = DAT_80006b68;
  bVar11 = false;
  puVar10 = DAT_80006b68 + 0x400;
  puVar5 = DAT_80006b68;
  if ((param_1 != 0) && (puVar5 = puVar10, param_1 != 1)) {
    puVar5 = (uint *)0x0;
  }
  if (*param_2 == 0xc) {
                    // WARNING: Could not recover jumptable at 0x80006828. Too many branches
                    // WARNING: Treating indirect jump as call
    (*UNRECOVERED_JUMPTABLE_00)();
    return;
  }
  uVar1 = *(uint *)(param_2 + 2);
  uVar7 = 0x80000000;
  if (*param_2 == 0) {
    uVar7 = DAT_80006b6c;
  }
  if ((uVar1 & 1) != 0) {
    uVar7 = uVar7 | 0x40;
  }
  if ((uVar1 & 2) != 0) {
    uVar7 = uVar7 | 0x80;
  }
  if ((uVar1 & 4) != 0) {
    uVar7 = uVar7 | 0x100;
  }
  if (param_3 == (uint *)0x0) {
LAB_800068a8:
    puVar5[7] = *(uint *)(param_2 + 4);
    if (param_3 == (uint *)0x0) {
      puVar5[6] = *param_2 | uVar7;
    }
    else {
      if (param_3[2] * param_3[3] < 0x41) {
        puVar5[6] = *param_2 | uVar7;
        iVar6 = FUN_80005c14(param_1,param_3);
        if (iVar6 != 0) {
          FUN_8000705c(s_error__08x_80006b90,DAT_80006b8c & puVar5[0xe]);
LAB_80006a90:
          uVar8 = 0xffffff68;
          goto LAB_80006a94;
        }
      }
      else {
        bVar11 = true;
        FUN_80005d30(param_1,param_3,DAT_80006b88);
        puVar5[6] = *param_2 | uVar7;
      }
    }
    uVar7 = DAT_80006b8c;
    puVar3 = puVar9;
    if ((param_1 != 0) && (puVar3 = puVar10, param_1 != 1)) {
      puVar3 = (uint *)0x0;
    }
    iVar6 = DAT_80006ba0;
    do {
      uVar1 = puVar3[0xe];
      bVar12 = iVar6 == 0;
      iVar6 = iVar6 + -1;
      if ((bVar12) || ((uVar1 & DAT_80006b8c) != 0)) {
        FUN_8000705c(PTR_s_ERR__mmc_d_tmier___d__timeout__x_80006ba4,param_1,iVar6,
                     DAT_80006b8c & uVar1);
        pcVar2 = s_ERR1_80006ba8;
        goto LAB_80006a54;
      }
    } while ((uVar1 & 4) == 0);
    if (bVar11) {
      do {
        puVar3 = puVar9;
        if ((param_1 != 0) && (puVar3 = puVar10, param_1 != 1)) {
          puVar3 = (uint *)0x0;
        }
        uVar1 = (uint)((puVar3[0x22] & 1) != 0);
        if ((puVar3[0x22] & 2) != 0) {
          uVar1 = uVar1 | 2;
        }
        if (uVar1 != 0) {
          puVar3[0x22] = uVar1 | puVar3[0x22];
          break;
        }
      } while (uVar1 == 0);
    }
    if (param_3 != (uint *)0x0) {
      if (param_3[2] < 2) {
        uVar1 = 8;
      }
      else {
        uVar1 = 0x4000;
      }
      puVar3 = puVar9;
      if ((param_1 != 0) && (puVar3 = puVar10, param_1 != 1)) {
        puVar3 = (uint *)0x0;
      }
      iVar6 = DAT_80006ba0;
LAB_80006a2c:
      uVar4 = puVar3[0xe];
      bVar12 = iVar6 != 0;
      iVar6 = iVar6 + -1;
      if ((bVar12) && ((uVar4 & uVar7) == 0)) goto LAB_80006a5c;
      FUN_8000705c(PTR_s_ERR__mmc_d_tmier___d__timeout__x_80006ba4,param_1,iVar6,uVar7 & uVar4);
      pcVar2 = s_ERR2_80006bb0;
LAB_80006a54:
      uVar8 = 0xffffff68;
      FUN_8000705c(pcVar2);
      goto LAB_80006a94;
    }
LAB_80006a68:
    uVar8 = 0;
    if ((*(uint *)(param_2 + 2) & 8) != 0) {
      iVar6 = DAT_80006bb8;
      do {
        bVar12 = iVar6 == 0;
        iVar6 = iVar6 + -1;
        if (bVar12) {
          FUN_8000705c(s_busy_timeout_80006bbc);
          goto LAB_80006a90;
        }
      } while ((puVar5[0xf] & 0x200) != 0);
    }
    *(uint *)(param_2 + 6) = puVar5[8];
    *(uint *)(param_2 + 8) = puVar5[9];
    if ((*(uint *)(param_2 + 2) & 2) != 0) {
      *(uint *)(param_2 + 10) = puVar5[10];
      *(uint *)(param_2 + 0xc) = puVar5[0xb];
    }
  }
  else {
    if ((*(byte *)param_3 & 3) == 0) {
      uVar1 = uVar7 | 0x2200;
      if ((*(byte *)(param_3 + 1) & 2) != 0) {
        uVar1 = uVar7 | 0x2600;
      }
      uVar7 = uVar1;
      if (1 < param_3[2]) {
        uVar7 = uVar7 | 0x1000;
      }
      puVar5[4] = param_3[3];
      puVar5[5] = param_3[3] * param_3[2];
      goto LAB_800068a8;
    }
    uVar8 = 0xffffffff;
    FUN_8000705c(s_Addr_Align_Err_____80006b70);
LAB_80006a94:
    FUN_8000705c(s_err_reset____80006bcc);
    *puVar5 = 7;
    iVar6 = 2000;
    if ((param_1 != 0) && (puVar9 = puVar10, param_1 != 1)) {
      puVar9 = (uint *)0x0;
    }
    puVar9[6] = DAT_80006bdc;
    while ((puVar9[6] & 0x80000000) != 0) {
      bVar12 = iVar6 == 0;
      iVar6 = iVar6 + -1;
      if (bVar12) {
        FUN_8000705c(PTR_s_timeout____80006be0);
        break;
      }
      FUN_80001118(5);
    }
  }
  if (param_3 != (uint *)0x0 && bVar11) {
    puVar5[0x22] = puVar5[0x22];
    puVar5[0x23] = 0;
    puVar5[0x20] = 0;
  }
  puVar5[0xe] = puVar5[0xe];
  *puVar5 = *puVar5 | 6;
  bVar11 = param_3 == (uint *)0x0;
  if (!bVar11) {
    bVar11 = (*(byte *)(param_3 + 1) & 1) == 0;
  }
  if (!bVar11) {
    uVar7 = *param_3 & 0xffffffe0;
    while (uVar7 <= (param_3[3] * param_3[2] + *param_3 & 0xffffffe0)) {
      coproc_moveto_Invalidate_Data_Cache_by_MVA(uVar7);
      coproc_moveto_Invalidate_Instruction_Cache_by_MVA(uVar7);
      uVar7 = uVar7 + 0x20;
    }
  }
                    // WARNING: Could not recover jumptable at 0x80006b64. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE_00)(uVar8);
  return;
LAB_80006a5c:
  if ((uVar4 & uVar1) != 0) goto LAB_80006a68;
  goto LAB_80006a2c;
}



undefined4 FUN_80006c24(char *param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  bool bVar4;
  
  if (param_1[3] != '\0') {
    iVar2 = FUN_8000404c(param_1[1],param_1 + 0x30,*(undefined4 *)(param_1 + 0x2c),1);
    if (iVar2 != 0) {
      return 1;
    }
    param_1[3] = '\0';
    if (((uint)(*(int *)(param_1 + 0x2c) - *(int *)(param_1 + 0x20)) < *(uint *)(param_1 + 0x18)) &&
       (param_1[2] == '\x02')) {
      FUN_8000404c(param_1[1],param_1 + 0x30,*(int *)(param_1 + 0x2c) + *(uint *)(param_1 + 0x18),1)
      ;
    }
  }
  cVar1 = *param_1;
  bVar4 = cVar1 == '\x03';
  if (bVar4) {
    cVar1 = param_1[4];
  }
  if (bVar4 && cVar1 == '\x01') {
    FUN_80005868(param_1 + 0x30,0,0x200);
    param_1[0x22e] = 'U';
    param_1[0x22f] = -0x56;
    param_1[0x30] = 'R';
    param_1[0x31] = 'R';
    param_1[0x32] = 'a';
    param_1[0x33] = 'A';
    param_1[0x214] = 'r';
    param_1[0x215] = 'r';
    param_1[0x216] = 'A';
    param_1[0x217] = 'a';
    uVar3 = *(undefined4 *)(param_1 + 0x10);
    param_1[0x218] = (char)uVar3;
    param_1[0x219] = (char)((uint)uVar3 >> 8);
    param_1[0x21a] = (char)((uint)uVar3 >> 0x10);
    param_1[0x21b] = (char)((uint)uVar3 >> 0x18);
    uVar3 = *(undefined4 *)(param_1 + 0xc);
    param_1[0x21c] = (char)uVar3;
    param_1[0x21d] = (char)((uint)uVar3 >> 8);
    param_1[0x21e] = (char)((uint)uVar3 >> 0x10);
    param_1[0x21f] = (char)((uint)uVar3 >> 0x18);
    *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x1c) + 1;
    FUN_8000404c(param_1[1],param_1 + 0x30,*(int *)(param_1 + 0x1c) + 1,1);
    param_1[4] = '\0';
  }
  iVar2 = FUN_80003eb0(param_1[1],0);
  if (iVar2 != 0) {
    return 1;
  }
  return 0;
}



longlong FUN_80006d88(uint param_1,uint param_2)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  byte in_Q;
  
  bVar3 = 0x7f < param_1;
  bVar4 = SBORROW4(param_1,0x80);
  bVar1 = (int)(param_1 - 0x80) < 0;
  bVar2 = param_1 == 0x80;
  if (bVar2) {
LAB_80006dd4:
    param_2 = (uint)(byte)(bVar1 << 4 | bVar2 << 3 | bVar3 << 2 | bVar4 << 1 | in_Q) << 0x1b;
  }
  else {
    if ((int)param_1 < 0x81) {
      bVar3 = 0x3e < param_1;
      bVar4 = SBORROW4(param_1,0x3f);
      bVar1 = (int)(param_1 - 0x3f) < 0;
      bVar2 = param_1 == 0x3f;
      if (!bVar2) {
        bVar3 = 0x3f < param_1;
        bVar4 = SBORROW4(param_1,0x40);
        bVar1 = (int)(param_1 - 0x40) < 0;
        bVar2 = param_1 == 0x40;
        if (bVar2) goto LAB_80006dd4;
        bVar3 = 0x7e < param_1;
        bVar4 = SBORROW4(param_1,0x7f);
        bVar1 = (int)(param_1 - 0x7f) < 0;
        bVar2 = param_1 == 0x7f;
        if (!bVar2) goto LAB_80006de0;
      }
    }
    else {
      bVar3 = 0xbe < param_1;
      bVar4 = SBORROW4(param_1,0xbf);
      bVar1 = (int)(param_1 - 0xbf) < 0;
      bVar2 = param_1 == 0xbf;
      if (!bVar2) {
        bVar3 = 0xbf < param_1;
        bVar4 = SBORROW4(param_1,0xc0);
        bVar1 = (int)(param_1 - 0xc0) < 0;
        bVar2 = param_1 == 0xc0;
        if (!bVar2) goto LAB_80006de0;
        goto LAB_80006dd4;
      }
    }
    param_2 = (uint)(byte)(bVar1 << 4 | bVar2 << 3 | bVar3 << 2 | bVar4 << 1 | in_Q) << 0x1b;
  }
LAB_80006de0:
  return (ulonglong)param_2 << 0x20;
}



void FUN_80006de8(void)

{
  undefined4 uVar1;
  
  uVar1 = DAT_80006eac;
  FUN_80005754(DAT_80006eac,0x80000000,0,0,0,0,0x80000000,0,0);
  FUN_80005754(uVar1,0,0x80000000,0,0x80000000,0,0x80000000,0,0);
  FUN_80005754(uVar1,0x80000000,0x80000000,0,0x80000000,0,0x2000000,0,3);
  FUN_80003808(uVar1);
  FUN_800037f4();
  FUN_800037b4(1);
  FUN_800037d4();
  FUN_800037bc();
  FUN_8000379c();
  return;
}



uint FUN_80006f54(int param_1,undefined *param_2,undefined *param_3,uint param_4)

{
  uint uVar1;
  undefined *puVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  
  iVar5 = DAT_80007058 + param_1 * 0x1000;
  if (0 < (int)param_4) {
    uVar4 = param_4;
    do {
      uVar1 = uVar4;
      if (0x40 < (int)uVar4) {
        uVar1 = 0x40;
      }
      *(uint *)(iVar5 + 0x30) = uVar1;
      uVar6 = uVar1;
      if (param_2 == (undefined *)0x0) {
        uVar6 = 0;
      }
      *(uint *)(iVar5 + 0x34) = uVar6 & 0xffffff;
      *(uint *)(iVar5 + 0x38) = uVar6 & 0xffffff;
      iVar3 = 0;
      if (0 < (int)uVar6) {
        puVar2 = param_2;
        do {
          iVar3 = iVar3 + 1;
          *(undefined *)(iVar5 + 0x200) = *puVar2;
          puVar2 = puVar2 + 1;
        } while (iVar3 < (int)uVar6);
      }
      *(uint *)(iVar5 + 8) = *(uint *)(iVar5 + 8) | 0x80000000;
      do {
      } while ((*(uint *)(iVar5 + 0x1c) & 0xff) < uVar1);
      iVar3 = 0;
      puVar2 = param_3;
      if (0 < (int)uVar1) {
        do {
          iVar3 = iVar3 + 1;
          param_3 = puVar2;
          if (puVar2 != (undefined *)0x0) {
            param_3 = puVar2 + 1;
            *puVar2 = *(undefined *)(iVar5 + 0x300);
          }
          puVar2 = param_3;
        } while (iVar3 < (int)uVar1);
      }
      if (param_2 != (undefined *)0x0) {
        param_2 = param_2 + uVar1;
      }
      uVar4 = uVar4 - uVar1;
    } while (0 < (int)uVar4);
  }
  return param_4;
}



void FUN_8000705c(byte *param_1,byte *param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  byte bVar2;
  byte **ppbVar3;
  uint *puVar4;
  uint uVar5;
  char cVar6;
  uint *puVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  byte *pbVar12;
  byte *pbVar13;
  uint uVar14;
  byte *pbVar15;
  byte **ppbVar16;
  bool bVar17;
  bool bVar18;
  undefined8 uVar19;
  byte abStack105 [41];
  uint local_40;
  uint local_3c;
  byte *local_10;
  byte *apbStack12 [3];
  
  apbStack12[2] = (byte *)param_4;
  apbStack12[1] = (byte *)param_3;
  apbStack12[0] = param_2;
  local_10 = param_1;
  bVar1 = *param_1;
  ppbVar3 = apbStack12;
  puVar4 = DAT_80007510;
joined_r0x8000707c:
  if (bVar1 == 0) {
    DAT_80007510 = puVar4;
    return;
  }
  bVar1 = *local_10;
  DAT_80007510 = puVar4;
  if (bVar1 == 0x25) {
    uVar5 = (uint)local_10[1];
    uVar10 = 0;
    uVar14 = 0x20;
    ppbVar16 = ppbVar3 + 1;
    pbVar15 = *ppbVar3;
    if (uVar5 == 0x30) {
      uVar14 = 0x30;
    }
    bVar17 = false;
    iVar11 = 0;
    pbVar12 = local_10 + 2;
    if (uVar5 != 0) {
      do {
        if (9 < uVar5 - 0x30) {
          if (uVar5 == 100) {
LAB_800073f0:
            iVar11 = -10;
            break;
          }
          if (uVar5 < 0x65) {
            if (uVar5 == 0x2d) {
              bVar17 = true;
              goto LAB_80007118;
            }
            if (uVar5 < 0x2e) {
              if (uVar5 == 0) {
                pbVar12 = pbVar12 + -1;
                goto LAB_80007504;
              }
              if (uVar5 == 0x25) {
                uVar10 = 0x25;
                do {
                } while ((DAT_8000750c[0x1f] & 2) == 0);
LAB_80007324:
                *DAT_8000750c = uVar10;
                goto LAB_80007504;
              }
            }
            else {
              if (uVar5 == 0x58) {
LAB_800073f8:
                iVar11 = 0x10;
                break;
              }
              if (uVar5 == 99) {
                if (bVar17) {
                  do {
                  } while ((DAT_8000750c[0x1f] & 2) == 0);
                  *DAT_8000750c = (uint)pbVar15 & 0x7f;
                }
                puVar4 = DAT_80007510;
                if ((0 < (int)uVar10) && (iVar11 = uVar10 - 2, iVar11 != -1)) {
                  puVar7 = DAT_80007510 + -0x1f;
                  do {
                    do {
                    } while ((*puVar4 & 2) == 0);
                    *puVar7 = uVar14;
                    bVar18 = iVar11 != 0;
                    iVar11 = iVar11 + -1;
                  } while (bVar18);
                }
                if (bVar17) goto LAB_80007504;
                uVar10 = (uint)pbVar15 & 0x7f;
                do {
                } while ((DAT_8000750c[0x1f] & 2) == 0);
                goto LAB_80007324;
              }
            }
          }
          else {
            if (uVar5 == 0x73) {
              if ((bVar17) && (uVar5 = (uint)*pbVar15, uVar5 != 0)) {
                pbVar13 = pbVar15;
                do {
                  do {
                  } while ((*puVar4 & 2) == 0);
                  puVar4[-0x1f] = uVar5;
                  pbVar13 = pbVar13 + 1;
                  uVar5 = (uint)*pbVar13;
                } while (uVar5 != 0);
              }
              uVar5 = FUN_800002cc(pbVar15);
              if (uVar5 < uVar10) {
                iVar11 = FUN_800002cc(pbVar15);
                puVar4 = DAT_80007510;
                iVar9 = (uVar10 - iVar11) + -1;
                if (uVar10 - iVar11 != 0) {
                  puVar7 = DAT_80007510 + -0x1f;
                  do {
                    do {
                    } while ((*puVar4 & 2) == 0);
                    *puVar7 = uVar14;
                    bVar18 = iVar9 != 0;
                    iVar9 = iVar9 + -1;
                  } while (bVar18);
                }
              }
              puVar4 = DAT_80007510;
              if ((!bVar17) && (uVar10 = (uint)*pbVar15, uVar10 != 0)) {
                puVar7 = DAT_80007510 + -0x1f;
                do {
                  do {
                  } while ((*puVar4 & 2) == 0);
                  *puVar7 = uVar10;
                  pbVar15 = pbVar15 + 1;
                  uVar10 = (uint)*pbVar15;
                } while (uVar10 != 0);
              }
              goto LAB_80007504;
            }
            if (uVar5 < 0x74) {
              if (uVar5 == 0x69) goto LAB_800073f0;
              if (uVar5 != 0x6f) goto LAB_80007288;
              iVar11 = 8;
              break;
            }
            if (uVar5 == 0x75) {
              iVar11 = 10;
              break;
            }
            if (uVar5 == 0x78) goto LAB_800073f8;
          }
LAB_80007288:
          iVar11 = 3;
          break;
        }
        uVar10 = (uVar5 + uVar10 * 10) - 0x30;
LAB_80007118:
        pbVar13 = pbVar12 + 1;
        uVar5 = (uint)*pbVar12;
        pbVar12 = pbVar13;
      } while (uVar5 != 0);
      if (bVar17) {
        uVar10 = -uVar10;
      }
    }
    if (uVar14 == 0) {
      uVar14 = 0x20;
    }
    bVar17 = (int)uVar10 < 0;
    local_40 = 0;
    local_3c = 0;
    if (bVar17) {
      uVar10 = -uVar10;
      local_40 = 1;
    }
    local_40 = (uint)bVar17;
    if (0x50 < uVar10) {
      uVar10 = 0;
    }
    bVar17 = iVar11 < 0;
    if (bVar17) {
      iVar11 = -iVar11;
    }
    bVar17 = bVar17 && (int)pbVar15 < 0;
    if (bVar17) {
      pbVar15 = (byte *)-(int)pbVar15;
      local_3c = 1;
    }
    local_3c = (uint)bVar17;
    iVar9 = 0;
LAB_80007180:
    do {
      iVar8 = iVar9;
      if (iVar11 == 0x10) {
        uVar5 = (uint)pbVar15 & 0xf;
        pbVar15 = (byte *)((uint)pbVar15 >> 4);
      }
      else {
        uVar19 = FUN_80000928(pbVar15,iVar11);
        pbVar15 = (byte *)uVar19;
        uVar5 = (uint)((ulonglong)uVar19 >> 0x20) & 0xffff;
      }
      puVar4 = DAT_80007510;
      if (uVar5 < 10) {
        cVar6 = '0';
      }
      else {
        cVar6 = '7';
      }
      abStack105[iVar8 + 1] = (char)uVar5 + cVar6;
      iVar9 = iVar8 + 1;
      if (pbVar15 == (byte *)0x0) goto LAB_80007400;
      if (iVar11 == 10) {
        if (iVar9 != 3 && iVar9 != 7) {
          if (iVar9 == 0xb) {
            bVar1 = 1;
LAB_800071f0:
            bVar2 = 0;
          }
          else {
            bVar1 = 0;
            if (iVar9 != 0xf) goto LAB_800071f0;
            bVar2 = 1;
          }
          if (!(bool)(bVar1 | bVar2)) goto LAB_80007180;
        }
        abStack105[iVar8 + 2] = 0x2c;
        iVar9 = iVar8 + 2;
      }
    } while( true );
  }
  local_10 = local_10 + 1;
  do {
  } while ((DAT_8000750c[0x1f] & 2) == 0);
  *DAT_8000750c = (uint)bVar1;
  ppbVar16 = ppbVar3;
  goto LAB_800070b4;
LAB_80007400:
  if (local_3c != 0) {
    abStack105[iVar8 + 2] = 0x2d;
    iVar9 = iVar8 + 2;
  }
  if (iVar9 < (int)uVar10) {
    iVar11 = uVar10 - iVar9;
    if ((local_40 == 0) && (iVar8 = iVar11 + -1, iVar11 != 0)) {
      puVar7 = DAT_80007510 + -0x1f;
      do {
        do {
        } while ((*puVar4 & 2) == 0);
        *puVar7 = uVar14;
        bVar17 = iVar8 != 0;
        iVar8 = iVar8 + -1;
      } while (bVar17);
    }
    puVar4 = DAT_80007510;
    if (0 < iVar9) {
      puVar7 = DAT_80007510 + -0x1f;
      do {
        iVar8 = iVar9 + -1;
        do {
        } while ((*puVar4 & 2) == 0);
        *puVar7 = (uint)abStack105[iVar9];
        iVar9 = iVar8;
      } while (0 < iVar8);
    }
    puVar4 = DAT_80007510;
    if ((local_40 != 0) && (iVar9 = iVar11 + -1, iVar11 != 0)) {
      puVar7 = DAT_80007510 + -0x1f;
      do {
        do {
        } while ((*puVar4 & 2) == 0);
        *puVar7 = uVar14;
        bVar17 = iVar9 != 0;
        iVar9 = iVar9 + -1;
      } while (bVar17);
    }
  }
  else {
    if (0 < iVar9) {
      puVar7 = DAT_80007510 + -0x1f;
      do {
        iVar11 = iVar9 + -1;
        do {
        } while ((*puVar4 & 2) == 0);
        *puVar7 = (uint)abStack105[iVar9];
        iVar9 = iVar11;
      } while (0 < iVar11);
    }
  }
LAB_80007504:
  local_10 = pbVar12;
LAB_800070b4:
  bVar1 = *local_10;
  ppbVar3 = ppbVar16;
  puVar4 = DAT_80007510;
  goto joined_r0x8000707c;
}



undefined4 FUN_80007514(byte **param_1,byte **param_2)

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
  if ((((bVar6 && ppbVar1 != (byte **)0x0) && ppbVar4 != (byte **)0x0) &&
      (*(short *)(param_1 + 1) == *(short *)((int)ppbVar1 + 6))) &&
     (uVar2 = FUN_80004044(*(byte *)((int)ppbVar1 + 1)), (uVar2 & 1) == 0)) {
    pbVar3 = *param_1;
    uVar5 = 0;
  }
  else {
    pbVar3 = (byte *)0x0;
  }
  *param_2 = pbVar3;
  return uVar5;
}



void FUN_80007570(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  *param_1 = param_3;
  return;
}



// WARNING: Control flow encountered bad instruction data

uint FUN_80007578(uint param_1)

{
  if (param_1 >> 0x17 < 0x9f) {
    return (param_1 << 8 | 0x80000000) >> (0x9e - (param_1 >> 0x17) & 0xff);
  }
  if (((int)param_1 < 0) && (param_1 << 1 < 0x7f000000)) {
    return 0;
  }
  FUN_800076fc();
                    // WARNING: Bad instruction - Truncating control flow here
  halt_baddata();
}



uint FUN_800075cc(uint param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  
  uVar2 = param_1 & 0x80000000;
  if ((int)uVar2 < 0) {
    param_1 = -param_1;
  }
  uVar3 = count_leading_zeroes(param_1);
  uVar1 = param_1 << (uVar3 & 0xff);
  if (uVar1 == 0) {
    return param_1;
  }
  bVar4 = (bool)((byte)(uVar1 >> 7) & 1);
  uVar2 = (uVar2 | (0x9d - uVar3) * 0x800000) + (uVar1 >> 8) + (uint)bVar4;
  if (!bVar4) {
    return uVar2;
  }
  if ((uVar1 & 0x7f) == 0) {
    uVar2 = uVar2 & 0xfffffffe;
  }
  return uVar2;
}



uint FUN_800075fc(uint param_1,uint param_2,undefined4 param_3,uint param_4)

{
  longlong lVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  bool bVar6;
  bool bVar7;
  undefined4 in_cr0;
  undefined4 in_cr1;
  undefined4 in_cr9;
  undefined8 uVar8;
  
  uVar2 = param_1 >> 7 & 0xff0000;
  bVar7 = uVar2 == 0;
  if (!bVar7) {
    param_4 = param_2 >> 7 & 0xff0000;
    bVar7 = param_4 == 0;
  }
  if (!bVar7) {
    bVar7 = uVar2 == 0xff0000;
  }
  if (!bVar7) {
    bVar7 = param_4 == 0xff0000;
  }
  if (bVar7) {
    if ((int)(param_1 ^ param_2) < 0) {
      uVar2 = uVar2 | 0x100;
    }
    bVar7 = 0xfeffff < (param_2 >> 7 & 0xff0000);
    bVar6 = 0xfeffff < uVar2 || bVar7;
    if (0xfeffff >= uVar2 && !bVar7) {
      return (param_1 ^ param_2) & 0x80000000;
    }
    uVar8 = FUN_800076fc();
    if (!bVar6) {
      coprocessor_function(0,0,4,in_cr0,in_cr1,in_cr9);
    }
    uVar2 = (uint)uVar8 ^ (uint)((ulonglong)uVar8 >> 0x20);
  }
  else {
    if ((int)(param_1 ^ param_2) < 0) {
      uVar2 = uVar2 | 0x100;
    }
    lVar1 = (ulonglong)(param_2 << 8 | 0x80000000) * (ulonglong)(param_1 << 8 | 0x80000000);
    uVar5 = (uint)((ulonglong)lVar1 >> 0x20);
    iVar3 = uVar2 + param_4 + -0x800000;
    if ((int)lVar1 != 0) {
      uVar5 = uVar5 | 1;
    }
    bVar7 = SUB41(uVar5 >> 0x1f,0);
    uVar2 = uVar5 << 1;
    uVar4 = iVar3 + (iVar3 >> 0x10) + (uint)bVar7;
    if (bVar7) {
      uVar2 = (uint)bVar7 << 0x1f | uVar5 & 0x7fffffff;
    }
    bVar7 = (bool)((byte)(uVar2 >> 7) & 1);
    uVar5 = uVar2 >> 8;
    if (bVar7) {
      uVar5 = uVar2 & 0x7f;
    }
    uVar2 = (uVar2 >> 8) + uVar4 * 0x800000 + (uint)bVar7;
    if (uVar5 != 0) {
      bVar7 = 0xfbffff < uVar4;
    }
    if (!bVar7) {
      return uVar2;
    }
    if (uVar5 == 0 || uVar4 == 0xfc0000) {
      uVar2 = uVar2 & 0xfffffffe;
    }
    if (uVar4 < 0xfc0000) {
      return uVar2;
    }
    if ((int)(uVar4 - 0xfc0000) < 0) {
      uVar4 = uVar4 ^ 0xff;
      bVar7 = (int)(uVar4 + 0x10000) < 0;
      if (uVar4 != 0xffff0000 && bVar7 == SCARRY4(uVar4,0x10000)) {
        return uVar2;
      }
      uVar2 = uVar2 + 0x60000000;
      if (uVar4 == 0xffff0000 || bVar7 != SCARRY4(uVar4,0x10000)) {
        uVar2 = uVar2 & 0x80000000;
      }
      return uVar2;
    }
    if ((int)((uVar2 + 0x800000) * 2) < 0) {
      return uVar2;
    }
    uVar2 = uVar2 + 0xa0000000;
  }
  return (uVar2 >> 0x17 | 0xff) << 0x17;
}



uint FUN_800076fc(uint param_1,uint param_2,uint param_3)

{
  uint uVar1;
  uint *in_lr;
  bool bVar2;
  
  if ((((int)*in_lr < 0) || (param_3 = param_2 * 2, param_3 < 0xff000001)) &&
     (param_1 * 2 < 0xff000001)) {
    if (param_1 * 2 == 0xff000000) {
      uVar1 = ((int)param_1 >> 0x1f) * -3 + 2;
      if (param_3 == 0xff000000) {
        uVar1 = (uVar1 - ((int)param_2 >> 0x1f)) + (uint)(0xfeffffff < param_3);
      }
    }
    else {
      uVar1 = param_2 >> 0x1f;
    }
  }
  else {
    uVar1 = 8;
  }
  uVar1 = *in_lr >> uVar1 * 3 & 7;
  switch(uVar1) {
  case 4:
    break;
  case 5:
    param_2 = param_1;
    break;
  case 6:
  case 7:
    return 0x7fc00000;
  default:
                    // WARNING: Could not recover jumptable at 0x80007764. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar1 = (*(code *)(in_lr + uVar1 + 1))();
    return uVar1;
  }
  bVar2 = SUB41(param_2 >> 0x1f,0);
  uVar1 = param_2 * 2;
  if (uVar1 != 0) {
    bVar2 = uVar1 < 0x1000001;
  }
  if (bVar2 && (uVar1 != 0 && uVar1 != 0x1000000)) {
    param_2 = param_2 & 0x80000000;
  }
  return param_2;
}


