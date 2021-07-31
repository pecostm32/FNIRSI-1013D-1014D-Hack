//Output a string to UART0

void FUN_800376f8(byte *param_1,byte *param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  byte bVar2;
  byte **ppbVar3;
  uint *puVar4;
  uint *puVar5;
  uint uVar6;
  int iVar7;
  char cVar8;
  int iVar9;
  byte *pbVar10;
  int iVar11;
  byte *pbVar12;
  byte *pbVar13;
  uint uVar14;
  uint uVar15;
  byte **ppbVar16;
  bool bVar17;
  bool bVar18;
  undefined8 uVar19;
  byte abStack105 [41];
  uint local_40;
  int local_3c;
  byte *local_10;
  byte *apbStack12 [3];
  
  apbStack12[2] = (byte *)param_4;
  apbStack12[1] = (byte *)param_3;
  apbStack12[0] = param_2;
  local_10 = param_1;
  bVar1 = *param_1;
  ppbVar3 = apbStack12;
  puVar4 = DAT_80037bb8;
joined_r0x80037718:
  if (bVar1 == 0) {
    DAT_80037bb8 = puVar4;
    return;
  }
  bVar1 = *local_10;
  DAT_80037bb8 = puVar4;
  if (bVar1 == 0x25) {
    uVar6 = (uint)local_10[1];
    uVar15 = 0;
    uVar14 = 0x20;
    ppbVar16 = ppbVar3 + 1;
    pbVar10 = *ppbVar3;
    if (uVar6 == 0x30) {
      uVar14 = 0x30;
    }
    bVar17 = false;
    iVar7 = 0;
    pbVar12 = local_10 + 2;
    if (uVar6 != 0) {
      do {
        if (9 < uVar6 - 0x30) {
          if (uVar6 == 100) {
LAB_80037a94:
            iVar7 = -10;
            break;
          }
          if (uVar6 < 0x65) {
            if (uVar6 == 0x2d) {
              bVar17 = true;
              goto LAB_800377b8;
            }
            if (uVar6 < 0x2e) {
              if (uVar6 == 0) {
                pbVar12 = pbVar12 + -1;
                goto LAB_80037bb0;
              }
              if (uVar6 == 0x25) {
                uVar15 = 0x25;
                do {
                } while ((puVar4[0x1f] & 2) == 0);
LAB_800379c4:
                *DAT_80037bb8 = uVar15;
                goto LAB_80037bb0;
              }
            }
            else {
              if (uVar6 == 0x58) {
LAB_80037a9c:
                iVar7 = 0x10;
                break;
              }
              if (uVar6 == 99) {
                if (bVar17) {
                  do {
                  } while ((puVar4[0x1f] & 2) == 0);
                  *puVar4 = (uint)pbVar10 & 0x7f;
                }
                puVar4 = DAT_80037bb8;
                if ((0 < (int)uVar15) && (iVar7 = uVar15 - 2, iVar7 != -1)) {
                  do {
                    do {
                    } while ((puVar4[0x1f] & 2) == 0);
                    *puVar4 = uVar14;
                    bVar18 = iVar7 != 0;
                    iVar7 = iVar7 + -1;
                  } while (bVar18);
                }
                if (bVar17) goto LAB_80037bb0;
                uVar15 = (uint)pbVar10 & 0x7f;
                do {
                } while ((DAT_80037bb8[0x1f] & 2) == 0);
                goto LAB_800379c4;
              }
            }
          }
          else {
            if (uVar6 == 0x73) {
              if (bVar17) {
                bVar1 = *pbVar10;
                pbVar13 = pbVar10;
                while (bVar1 != 0) {
                  do {
                  } while ((puVar4[0x1f] & 2) == 0);
                  *puVar4 = (uint)bVar1;
                  pbVar13 = pbVar13 + 1;
                  bVar1 = *pbVar13;
                }
              }
              uVar6 = FUN_800005bc(pbVar10);
              if (uVar6 < uVar15) {
                iVar7 = FUN_800005bc(pbVar10);
                puVar4 = DAT_80037bb8;
                iVar7 = uVar15 - iVar7;
                while (iVar7 != 0) {
                  iVar7 = iVar7 + -1;
                  do {
                  } while ((puVar4[0x1f] & 2) == 0);
                  *puVar4 = uVar14;
                }
              }
              puVar4 = DAT_80037bb8;
              if (!bVar17) {
                bVar1 = *pbVar10;
                while (bVar1 != 0) {
                  do {
                  } while ((puVar4[0x1f] & 2) == 0);
                  *puVar4 = (uint)bVar1;
                  pbVar10 = pbVar10 + 1;
                  bVar1 = *pbVar10;
                }
              }
              goto LAB_80037bb0;
            }
            if (uVar6 < 0x74) {
              if (uVar6 == 0x69) goto LAB_80037a94;
              if (uVar6 != 0x6f) goto LAB_80037928;
              iVar7 = 8;
              break;
            }
            if (uVar6 == 0x75) {
              iVar7 = 10;
              break;
            }
            if (uVar6 == 0x78) goto LAB_80037a9c;
          }
LAB_80037928:
          iVar7 = 3;
          break;
        }
        uVar15 = (uVar6 + uVar15 * 10) - 0x30;
LAB_800377b8:
        pbVar13 = pbVar12 + 1;
        uVar6 = (uint)*pbVar12;
        pbVar12 = pbVar13;
      } while (uVar6 != 0);
      if (bVar17) {
        uVar15 = -uVar15;
      }
    }
    if (uVar14 == 0) {
      uVar14 = 0x20;
    }
    bVar17 = (int)uVar15 < 0;
    local_40 = 0;
    local_3c = 0;
    if (bVar17) {
      uVar15 = -uVar15;
      local_40 = 1;
    }
    local_40 = (uint)bVar17;
    if (0x50 < uVar15) {
      uVar15 = 0;
    }
    bVar17 = iVar7 < 0;
    if (bVar17) {
      iVar7 = -iVar7;
    }
    iVar11 = 0;
    if (bVar17 && (int)pbVar10 < 0) {
      pbVar10 = (byte *)-(int)pbVar10;
      local_3c = 1;
    }
LAB_80037820:
    do {
      iVar9 = iVar11;
      if (iVar7 == 0x10) {
        uVar6 = (uint)pbVar10 & 0xf;
        pbVar10 = (byte *)((uint)pbVar10 >> 4);
      }
      else {
        uVar19 = FUN_80000dc4(pbVar10,iVar7);
        pbVar10 = (byte *)uVar19;
        uVar6 = (uint)((ulonglong)uVar19 >> 0x20) & 0xffff;
      }
      puVar4 = DAT_80037bb8;
      if (uVar6 < 10) {
        cVar8 = '0';
      }
      else {
        cVar8 = '7';
      }
      abStack105[iVar9 + 1] = (char)uVar6 + cVar8;
      iVar11 = iVar9 + 1;
      if (pbVar10 == (byte *)0x0) goto LAB_80037aa4;
      if (iVar7 == 10) {
        if (iVar11 != 3 && iVar11 != 7) {
          if (iVar11 == 0xb) {
            bVar1 = 1;
LAB_80037890:
            bVar2 = 0;
          }
          else {
            bVar1 = 0;
            if (iVar11 != 0xf) goto LAB_80037890;
            bVar2 = 1;
          }
          if (!(bool)(bVar1 | bVar2)) goto LAB_80037820;
        }
        abStack105[iVar9 + 2] = 0x2c;
        iVar11 = iVar9 + 2;
      }
    } while( true );
  }
  local_10 = local_10 + 1;
  do {
  } while ((puVar4[0x1f] & 2) == 0);
  *puVar4 = (uint)bVar1;
  ppbVar16 = ppbVar3;
  goto LAB_80037754;
LAB_80037aa4:
  if (local_3c != 0) {
    abStack105[iVar9 + 2] = 0x2d;
    iVar11 = iVar9 + 2;
  }
  if (iVar11 < (int)uVar15) {
    iVar9 = uVar15 - iVar11;
    iVar7 = iVar9;
    puVar5 = DAT_80037bb8;
    if (local_40 == 0) {
      while (puVar5 = DAT_80037bb8, iVar7 != 0) {
        do {
        } while ((puVar4[0x1f] & 2) == 0);
        *puVar4 = uVar14;
        iVar7 = iVar7 + -1;
      }
    }
    while (puVar4 = DAT_80037bb8, 0 < iVar11) {
      do {
      } while ((DAT_80037bb8[0x1f] & 2) == 0);
      *DAT_80037bb8 = (uint)abStack105[iVar11];
      DAT_80037bb8 = puVar5;
      iVar11 = iVar11 + -1;
      puVar5 = DAT_80037bb8;
      DAT_80037bb8 = puVar4;
    }
    DAT_80037bb8 = puVar5;
    if (local_40 != 0) {
      while (iVar9 != 0) {
        iVar9 = iVar9 + -1;
        do {
        } while ((puVar5[0x1f] & 2) == 0);
        *puVar5 = uVar14;
      }
    }
  }
  else {
    while (0 < iVar11) {
      do {
      } while ((puVar4[0x1f] & 2) == 0);
      *puVar4 = (uint)abStack105[iVar11];
      iVar11 = iVar11 + -1;
    }
  }
LAB_80037bb0:
  local_10 = pbVar12;
LAB_80037754:
  bVar1 = *local_10;
  ppbVar3 = ppbVar16;
  puVar4 = DAT_80037bb8;
  goto joined_r0x80037718;
}


