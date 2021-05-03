void FUN_80012a64(int param_1,uint param_2,int param_3,int param_4,undefined4 param_5)

{
  int *piVar1;
  undefined2 uVar2;
  uint uVar3;
  undefined2 *puVar4;
  ushort *puVar5;
  int iVar6;
  undefined2 *puVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  code *UNRECOVERED_JUMPTABLE_00;
  bool bVar12;
  
  uVar2 = FUN_800232b4(param_5);
  piVar1 = Global_Frame_Buffer_Pointer;
  iVar8 = param_2 + param_3 + -1;
  uVar3 = param_2;
  if ((int)param_2 < iVar8) {
    do {
      puVar5 = (ushort *)(param_4 + uVar3 * 2);
      uVar10 = (uint)*puVar5;
      uVar11 = (uint)puVar5[1];
      uVar9 = uVar10 + uVar11 >> 1;
      if (uVar11 <= uVar10 && uVar10 != uVar11) {
        if (uVar11 + 10 < uVar10) {
          if (uVar11 <= uVar10) {
            iVar6 = *piVar1 + ((param_1 + uVar11 * 800 + uVar3) - param_2) * 2;
            bVar12 = (uVar10 - uVar11 & 1) == 0;
            puVar7 = (undefined2 *)(iVar6 + -0x63e);
            if (bVar12) {
              puVar7 = (undefined2 *)(iVar6 + 2);
            }
            if (bVar12) {
              *puVar7 = uVar2;
            }
            uVar9 = (uVar10 - uVar11) * 0x8000 + 0x8000 >> 0x10;
            while (uVar9 != 0) {
              puVar7[800] = uVar2;
              puVar7 = puVar7 + 0x640;
              uVar9 = uVar9 - 1 & 0xffff;
              *puVar7 = uVar2;
            }
          }
        }
        else {
          if (uVar11 <= uVar9) {
            bVar12 = (uVar9 - uVar11 & 1) == 0;
            iVar6 = *piVar1 + ((param_1 + uVar11 * 800 + uVar3) - param_2) * 2;
            puVar7 = (undefined2 *)(iVar6 + -0x63e);
            if (bVar12) {
              puVar7 = (undefined2 *)(iVar6 + 2);
            }
            if (bVar12) {
              *puVar7 = uVar2;
            }
            uVar11 = (uVar9 - uVar11) * 0x8000 + 0x8000 >> 0x10;
            while (uVar11 != 0) {
              puVar7[800] = uVar2;
              puVar7 = puVar7 + 0x640;
              uVar11 = uVar11 - 1 & 0xffff;
              *puVar7 = uVar2;
            }
          }
          if (uVar9 <= uVar10) {
            bVar12 = (uVar10 - uVar9 & 1) == 0;
            puVar4 = (undefined2 *)(*piVar1 + ((param_1 + uVar9 * 800 + uVar3) - param_2) * 2);
            puVar7 = puVar4 + -800;
            if (bVar12) {
              puVar7 = puVar4;
            }
            if (bVar12) {
              *puVar7 = uVar2;
            }
            uVar9 = (uVar10 - uVar9) * 0x8000 + 0x8000 >> 0x10;
            while (uVar9 != 0) {
              puVar7[800] = uVar2;
              puVar7 = puVar7 + 0x640;
              uVar9 = uVar9 - 1 & 0xffff;
              *puVar7 = uVar2;
            }
          }
        }
      }
      else {
        if (uVar11 <= uVar10) {
          puVar7 = (undefined2 *)(*piVar1 + ((param_1 + uVar10 * 800 + uVar3) - param_2) * 2);
          *puVar7 = uVar2;
          puVar7[1] = uVar2;
        }
        else {
          if (uVar10 + 10 < uVar11) {
            bVar12 = (uVar11 - uVar10 & 1) == 0;
            puVar4 = (undefined2 *)(*piVar1 + ((param_1 + uVar10 * 800 + uVar3) - param_2) * 2);
            puVar7 = puVar4 + -800;
            if (bVar12) {
              puVar7 = puVar4;
            }
            if (bVar12) {
              *puVar7 = uVar2;
            }
            uVar9 = (uVar11 - uVar10) * 0x8000 + 0x8000 >> 0x10;
            while (uVar9 != 0) {
              puVar7[800] = uVar2;
              puVar7 = puVar7 + 0x640;
              uVar9 = uVar9 - 1 & 0xffff;
              *puVar7 = uVar2;
            }
          }
          else {
            if (uVar10 <= uVar9) {
              puVar4 = (undefined2 *)(*piVar1 + ((param_1 + uVar10 * 800 + uVar3) - param_2) * 2);
              bVar12 = (uVar9 - uVar10 & 1) == 0;
              puVar7 = puVar4 + -800;
              if (bVar12) {
                puVar7 = puVar4;
              }
              if (bVar12) {
                *puVar7 = uVar2;
              }
              uVar10 = (uVar9 - uVar10) * 0x8000 + 0x8000 >> 0x10;
              while (uVar10 != 0) {
                puVar7[800] = uVar2;
                puVar7 = puVar7 + 0x640;
                uVar10 = uVar10 - 1 & 0xffff;
                *puVar7 = uVar2;
              }
            }
            if (uVar9 <= uVar11) {
              bVar12 = (uVar11 - uVar9 & 1) == 0;
              iVar6 = *piVar1 + ((param_1 + uVar9 * 800 + uVar3) - param_2) * 2;
              puVar7 = (undefined2 *)(iVar6 + -0x63e);
              if (bVar12) {
                puVar7 = (undefined2 *)(iVar6 + 2);
              }
              if (bVar12) {
                *puVar7 = uVar2;
              }
              uVar9 = (uVar11 - uVar9) * 0x8000 + 0x8000 >> 0x10;
              while (uVar9 != 0) {
                puVar7[800] = uVar2;
                puVar7 = puVar7 + 0x640;
                uVar9 = uVar9 - 1 & 0xffff;
                *puVar7 = uVar2;
              }
            }
          }
        }
      }
      uVar3 = uVar3 + 1 & 0xfffeffff;
    } while ((int)uVar3 < iVar8);
  }
  iVar8 = param_2 + param_3 + -2;
  uVar3 = param_2;
  if (iVar8 <= (int)param_2) {
                    // WARNING: Could not recover jumptable at 0x80012da0. Too many branches
                    // WARNING: Treating indirect jump as call
    (*UNRECOVERED_JUMPTABLE_00)();
    return;
  }
  do {
    puVar5 = (ushort *)(param_4 + uVar3 * 2);
    uVar9 = (uint)*puVar5;
    uVar10 = (uint)puVar5[1];
    if (uVar9 != 0) {
      uVar9 = uVar9 - 1 & 0xffff;
    }
    if (uVar10 != 0) {
      uVar10 = uVar10 - 1 & 0xffff;
    }
    uVar11 = uVar9 + uVar10 >> 1;
    if (uVar10 <= uVar9 && uVar9 != uVar10) {
      if (uVar10 + 10 < uVar9) {
        if (uVar10 <= uVar9) {
          bVar12 = (uVar9 - uVar10 & 1) == 0;
          iVar6 = *piVar1 + ((param_1 + uVar10 * 800 + uVar3) - param_2) * 2;
          puVar7 = (undefined2 *)(iVar6 + -0x63e);
          if (bVar12) {
            puVar7 = (undefined2 *)(iVar6 + 2);
          }
          if (bVar12) {
            *puVar7 = uVar2;
          }
          uVar9 = (uVar9 - uVar10) * 0x8000 + 0x8000 >> 0x10;
          while (uVar9 != 0) {
            puVar7[800] = uVar2;
            puVar7 = puVar7 + 0x640;
            uVar9 = uVar9 - 1 & 0xffff;
            *puVar7 = uVar2;
          }
        }
      }
      else {
        if (uVar10 <= uVar11) {
          bVar12 = (uVar11 - uVar10 & 1) == 0;
          iVar6 = *piVar1 + ((param_1 + uVar10 * 800 + uVar3) - param_2) * 2;
          puVar7 = (undefined2 *)(iVar6 + -0x63e);
          if (bVar12) {
            puVar7 = (undefined2 *)(iVar6 + 2);
          }
          if (bVar12) {
            *puVar7 = uVar2;
          }
          uVar10 = (uVar11 - uVar10) * 0x8000 + 0x8000 >> 0x10;
          while (uVar10 != 0) {
            puVar7[800] = uVar2;
            puVar7 = puVar7 + 0x640;
            uVar10 = uVar10 - 1 & 0xffff;
            *puVar7 = uVar2;
          }
        }
        if (uVar11 <= uVar9) {
          bVar12 = (uVar9 - uVar11 & 1) == 0;
          puVar4 = (undefined2 *)(*piVar1 + ((param_1 + uVar11 * 800 + uVar3) - param_2) * 2);
          puVar7 = puVar4 + -800;
          if (bVar12) {
            puVar7 = puVar4;
          }
          if (bVar12) {
            *puVar7 = uVar2;
          }
          uVar9 = (uVar9 - uVar11) * 0x8000 + 0x8000 >> 0x10;
          while (uVar9 != 0) {
            puVar7[800] = uVar2;
            puVar7 = puVar7 + 0x640;
            uVar9 = uVar9 - 1 & 0xffff;
            *puVar7 = uVar2;
          }
        }
      }
    }
    else {
      if (uVar10 <= uVar9) {
        puVar7 = (undefined2 *)(*piVar1 + ((param_1 + uVar9 * 800 + uVar3) - param_2) * 2);
        *puVar7 = uVar2;
        puVar7[1] = uVar2;
      }
      else {
        if (uVar9 + 10 < uVar10) {
          bVar12 = (uVar10 - uVar9 & 1) == 0;
          puVar4 = (undefined2 *)(*piVar1 + ((param_1 + uVar9 * 800 + uVar3) - param_2) * 2);
          puVar7 = puVar4 + -800;
          if (bVar12) {
            puVar7 = puVar4;
          }
          if (bVar12) {
            *puVar7 = uVar2;
          }
          uVar9 = (uVar10 - uVar9) * 0x8000 + 0x8000 >> 0x10;
          while (uVar9 != 0) {
            puVar7[800] = uVar2;
            puVar7 = puVar7 + 0x640;
            uVar9 = uVar9 - 1 & 0xffff;
            *puVar7 = uVar2;
          }
        }
        else {
          if (uVar9 <= uVar11) {
            bVar12 = (uVar11 - uVar9 & 1) == 0;
            puVar4 = (undefined2 *)(*piVar1 + ((param_1 + uVar9 * 800 + uVar3) - param_2) * 2);
            puVar7 = puVar4 + -800;
            if (bVar12) {
              puVar7 = puVar4;
            }
            if (bVar12) {
              *puVar7 = uVar2;
            }
            uVar9 = (uVar11 - uVar9) * 0x8000 + 0x8000 >> 0x10;
            while (uVar9 != 0) {
              puVar7[800] = uVar2;
              puVar7 = puVar7 + 0x640;
              uVar9 = uVar9 - 1 & 0xffff;
              *puVar7 = uVar2;
            }
          }
          if (uVar11 <= uVar10) {
            bVar12 = (uVar10 - uVar11 & 1) == 0;
            iVar6 = *piVar1 + ((param_1 + uVar11 * 800 + uVar3) - param_2) * 2;
            puVar7 = (undefined2 *)(iVar6 + -0x63e);
            if (bVar12) {
              puVar7 = (undefined2 *)(iVar6 + 2);
            }
            if (bVar12) {
              *puVar7 = uVar2;
            }
            uVar9 = (uVar10 - uVar11) * 0x8000 + 0x8000 >> 0x10;
            while (uVar9 != 0) {
              puVar7[800] = uVar2;
              puVar7 = puVar7 + 0x640;
              uVar9 = uVar9 - 1 & 0xffff;
              *puVar7 = uVar2;
            }
          }
        }
      }
    }
    uVar3 = uVar3 + 1 & 0xfffeffff;
  } while ((int)uVar3 < iVar8);
                    // WARNING: Could not recover jumptable at 0x800130bc. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE_00)();
  return;
}


