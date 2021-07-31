//Check on relays are in this function

void FUN_80026918(void)

{
  ushort uVar1;
  ushort uVar2;
  undefined2 uVar3;
  bool bVar4;
  bool bVar5;
  undefined *puVar6;
  int iVar7;
  int iVar8;
  ushort *puVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  char *pcVar13;
  uint uVar14;
  uint uVar15;
  ushort *puVar16;
  int iVar17;
  int iVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  uint uVar22;
  uint unaff_r4;
  uint uVar23;
  int iVar24;
  uint uVar25;
  uint uVar26;
  bool bVar27;
  undefined8 uVar28;
  uint local_54;
  uint local_50;
  uint local_4c;
  uint local_48;
  
  local_50 = 0;
  local_54 = 0;
  local_4c = 0;
  local_48 = 0;
  bVar4 = false;
  bVar5 = false;
  iVar8 = FUN_8002330c();
  if (iVar8 == 2) {
    return;
  }
  FUN_8001d380();
  FUN_80017778();
  FUN_80019704(0xffffff);
  FUN_80019730(PTR_PTR_FUN_80026ca0);
  FUN_800197c8(2);
  FUN_800186b0();
  FUN_80018bf8(s_Please_insert_test_clip_and_pres_80026ca4,0xf7,100);
  FUN_80018f6c(0x168,0x140,0x1b8,400);
  FUN_80019704(0);
  FUN_80019730(PTR_PTR_FUN_80026cd8);
  FUN_80018bf8(&DAT_80026ce0,0x17c,DAT_80026cdc);
  puVar6 = PTR_DAT_80026ce4;
  do {
    do {
      FUN_800177c4();
    } while (0x4e < *(ushort *)(puVar6 + 2) - 0x169);
  } while (((*(ushort *)(puVar6 + 4) < 0x141) || (399 < *(ushort *)(puVar6 + 4))) ||
          (*puVar6 == '\0'));
  do {
    FUN_800177c4();
    FUN_80019704(0xdd00);
    FUN_80018f6c(0x168,0x140,0x1b8,400);
  } while (*puVar6 != '\0');
  FUN_800186b0();
  FUN_80019704(0xffffff);
  FUN_80019730(PTR_PTR_FUN_80026ca0);
  FUN_800197c8(2);
  iVar8 = DAT_80026ce8;
  *(undefined *)(DAT_80026ce8 + 1) = 0;
  *(undefined2 *)(iVar8 + 6) = 0x96;
  *(undefined2 *)(iVar8 + 0x12) = 0x96;
  *(undefined *)(iVar8 + 10) = 0x11;
  FUN_800068d4();
  FUN_8000696c();
  FUN_800096b8();
  FUN_800266c4();
  iVar8 = DAT_80026cec;
  uVar23 = 0;
  do {
    iVar7 = DAT_80026ce8;
    *(char *)(DAT_80026ce8 + 3) = (char)uVar23;
    FUN_8000689c();
    *(char *)(iVar7 + 0xf) = (char)uVar23;
    FUN_800095e8();
    FUN_8000bc00(100);
    FUN_800253e8();
    iVar7 = DAT_80026cf0;
    iVar17 = 0;
    iVar24 = 0;
    puVar9 = (ushort *)(DAT_80026cf0 + 200);
    uVar14 = 0;
    uVar25 = 0;
    iVar18 = 900;
    do {
      uVar26 = (uint)*puVar9;
      if (uVar26 < 0x9c) {
        iVar24 = iVar24 + uVar26;
        uVar25 = uVar25 + 1 & 0xfffeffff;
      }
      else {
        iVar17 = iVar17 + uVar26;
        uVar14 = uVar14 + 1 & 0xfffeffff;
      }
      iVar18 = iVar18 + -1;
      puVar9 = puVar9 + 1;
    } while (iVar18 != 0);
    uVar26 = FUN_80000dc4(iVar17,uVar14);
    uVar25 = FUN_80000dc4(iVar24,uVar25);
    uVar10 = 100;
    uVar14 = (uVar26 & 0xffff) - (uVar25 & 0xffff) & 0xffff;
    do {
      puVar9 = (ushort *)(iVar7 + uVar10 * 2);
      if ((*puVar9 < 0x9b) && (uVar12 = uVar10, 0x9b < puVar9[2])) break;
      uVar10 = uVar10 + 1 & 0xfffeffff;
      uVar12 = unaff_r4;
    } while (uVar10 < 1000);
    uVar15 = uVar12 + 5 & 0xfffeffff;
    uVar10 = 0;
    if (uVar15 < uVar12 + 0x19) {
      puVar16 = (ushort *)(iVar7 + uVar15 * 2);
      puVar9 = puVar16 + -1;
      if ((uVar12 - uVar15 & 1) == 0) {
        uVar10 = (uint)*puVar16;
        puVar9 = puVar16;
      }
      uVar15 = (uVar12 - uVar15) * 0x8000 + 0xc8000 >> 0x10;
      uVar19 = 0;
      while (uVar15 != 0) {
        puVar16 = puVar9 + 1;
        puVar9 = puVar9 + 2;
        uVar15 = uVar15 - 1 & 0xffff;
        uVar10 = uVar10 + *puVar16 & 0xfffeffff;
        uVar19 = uVar19 + *puVar9 & 0xfffeffff;
      }
      uVar10 = uVar10 + uVar19 & 0xfffeffff;
    }
    uVar19 = uVar12 + 0xd2 & 0xfffeffff;
    uVar15 = 0;
    uVar10 = uVar10 * DAT_80026cf4 >> 0x14;
    if (uVar19 < uVar12 + 0xe6) {
      puVar16 = (ushort *)(iVar7 + uVar19 * 2);
      puVar9 = puVar16 + -1;
      if (((uVar12 - uVar19 ^ 0xe5) & 1) == 0) {
        uVar15 = (uint)*puVar16;
        puVar9 = puVar16;
      }
      uVar19 = (uVar12 - uVar19) * 0x8000 + 0x730000 >> 0x10;
      uVar20 = 0;
      while (uVar19 != 0) {
        puVar16 = puVar9 + 1;
        puVar9 = puVar9 + 2;
        uVar19 = uVar19 - 1 & 0xffff;
        uVar15 = uVar15 + *puVar16 & 0xfffeffff;
        uVar20 = uVar20 + *puVar9 & 0xfffeffff;
      }
      uVar15 = uVar15 + uVar20 & 0xfffeffff;
    }
    iVar17 = 900;
    puVar9 = (ushort *)(iVar8 + 200);
    uVar15 = DAT_80026cf4 * uVar15 >> 0x14;
    if (uVar10 < uVar15) {
      uVar10 = uVar15 - uVar10;
    }
    else {
      uVar10 = uVar10 - uVar15;
    }
    uVar10 = uVar10 & 0xffff;
    iVar18 = 0;
    iVar24 = 0;
    uVar15 = 0;
    uVar19 = 0;
    do {
      uVar20 = (uint)*puVar9;
      if (uVar20 < 0x9c) {
        iVar24 = iVar24 + uVar20;
        uVar19 = uVar19 + 1 & 0xfffeffff;
      }
      else {
        iVar18 = iVar18 + uVar20;
        uVar15 = uVar15 + 1 & 0xfffeffff;
      }
      iVar17 = iVar17 + -1;
      puVar9 = puVar9 + 1;
    } while (iVar17 != 0);
    uVar20 = FUN_80000dc4(iVar18,uVar15);
    uVar19 = FUN_80000dc4(iVar24,uVar19);
    iVar17 = DAT_80026ce8;
    uVar11 = 100;
    uVar15 = (uVar20 & 0xffff) - (uVar19 & 0xffff) & 0xffff;
    do {
      puVar9 = (ushort *)(iVar8 + uVar11 * 2);
      if ((*puVar9 < 0x9b) && (unaff_r4 = uVar11, 0x9b < puVar9[2])) break;
      uVar11 = uVar11 + 1 & 0xfffeffff;
      unaff_r4 = uVar12;
    } while (uVar11 < 1000);
    uVar11 = unaff_r4 + 5 & 0xfffeffff;
    uVar12 = 0;
    if (uVar11 < unaff_r4 + 0x19) {
      puVar16 = (ushort *)(iVar8 + uVar11 * 2);
      puVar9 = puVar16 + -1;
      if ((unaff_r4 - uVar11 & 1) == 0) {
        uVar12 = (uint)*puVar16;
        puVar9 = puVar16;
      }
      uVar11 = (unaff_r4 - uVar11) * 0x8000 + 0xc8000 >> 0x10;
      uVar21 = 0;
      while (uVar11 != 0) {
        puVar16 = puVar9 + 1;
        puVar9 = puVar9 + 2;
        uVar11 = uVar11 - 1 & 0xffff;
        uVar12 = uVar12 + *puVar16 & 0xfffeffff;
        uVar21 = uVar21 + *puVar9 & 0xfffeffff;
      }
      uVar12 = uVar12 + uVar21 & 0xfffeffff;
    }
    uVar21 = unaff_r4 + 0xd2 & 0xfffeffff;
    uVar11 = 0;
    uVar12 = uVar12 * DAT_80026cf4 >> 0x14;
    if (uVar21 < unaff_r4 + 0xe6) {
      puVar16 = (ushort *)(iVar8 + uVar21 * 2);
      puVar9 = puVar16 + -1;
      if (((unaff_r4 - uVar21 ^ 0xe5) & 1) == 0) {
        uVar11 = (uint)*puVar16;
        puVar9 = puVar16;
      }
      uVar21 = (unaff_r4 - uVar21) * 0x8000 + 0x730000 >> 0x10;
      uVar22 = 0;
      while (uVar21 != 0) {
        puVar16 = puVar9 + 1;
        puVar9 = puVar9 + 2;
        uVar21 = uVar21 - 1 & 0xffff;
        uVar11 = uVar11 + *puVar16 & 0xfffeffff;
        uVar22 = uVar22 + *puVar9 & 0xfffeffff;
      }
      uVar11 = uVar11 + uVar22 & 0xfffeffff;
    }
    uVar11 = DAT_80026cf4 * uVar11 >> 0x14;
    if (uVar12 < uVar11) {
      uVar12 = uVar11 - uVar12;
    }
    else {
      uVar12 = uVar12 - uVar11;
    }
    uVar12 = uVar12 & 0xffff;
    if (uVar23 == 4) {
      uVar3 = (undefined2)DAT_800275b0;
      *(undefined2 *)(DAT_80026ce8 + 6) = uVar3;
      *(undefined2 *)(iVar17 + 0x12) = uVar3;
      FUN_8000696c();
      FUN_800096b8();
      FUN_8000bc00(100);
      FUN_800253e8();
      uVar25 = 100;
      do {
        puVar9 = (ushort *)(iVar7 + uVar25 * 2);
        uVar1 = *puVar9;
        uVar2 = puVar9[2];
        bVar27 = 0x15d < uVar1;
        if (0x15e < uVar1) {
          bVar27 = uVar2 < 0x15f;
          uVar1 = uVar2;
        }
        uVar26 = uVar25;
      } while ((!bVar27 || uVar1 == 0x15e) &&
              (uVar25 = uVar25 + 1 & 0xfffeffff, uVar26 = unaff_r4, uVar25 < 1000));
      uVar10 = uVar26 + 5 & 0xfffeffff;
      uVar25 = 0;
      if (uVar10 < uVar26 + 0x19) {
        puVar16 = (ushort *)(iVar7 + uVar10 * 2);
        puVar9 = puVar16 + -1;
        if ((uVar26 - uVar10 & 1) == 0) {
          uVar25 = (uint)*puVar16;
          puVar9 = puVar16;
        }
        uVar10 = (uVar26 - uVar10) * 0x8000 + 0xc8000 >> 0x10;
        uVar12 = 0;
        while (uVar10 != 0) {
          puVar16 = puVar9 + 1;
          puVar9 = puVar9 + 2;
          uVar10 = uVar10 - 1 & 0xffff;
          uVar25 = uVar25 + *puVar16 & 0xfffeffff;
          uVar12 = uVar12 + *puVar9 & 0xfffeffff;
        }
        uVar25 = uVar25 + uVar12 & 0xfffeffff;
      }
      uVar12 = uVar26 + 0xd2 & 0xfffeffff;
      uVar10 = 0;
      uVar25 = uVar25 * DAT_80026cf4 >> 0x14;
      if (uVar12 < uVar26 + 0xe6) {
        puVar16 = (ushort *)(iVar7 + uVar12 * 2);
        puVar9 = puVar16 + -1;
        if (((uVar26 - uVar12 ^ 0xe5) & 1) == 0) {
          uVar10 = (uint)*puVar16;
          puVar9 = puVar16;
        }
        uVar12 = (uVar26 - uVar12) * 0x8000 + 0x730000 >> 0x10;
        uVar19 = 0;
        while (uVar12 != 0) {
          puVar16 = puVar9 + 1;
          puVar9 = puVar9 + 2;
          uVar12 = uVar12 - 1 & 0xffff;
          uVar10 = uVar10 + *puVar16 & 0xfffeffff;
          uVar19 = uVar19 + *puVar9 & 0xfffeffff;
        }
        uVar10 = uVar10 + uVar19 & 0xfffeffff;
      }
      uVar10 = DAT_80026cf4 * uVar10 >> 0x14;
      if (uVar25 < uVar10) {
        uVar25 = uVar10 - uVar25;
      }
      else {
        uVar25 = uVar25 - uVar10;
      }
      uVar10 = 100;
      do {
        puVar9 = (ushort *)(iVar8 + uVar10 * 2);
        uVar1 = *puVar9;
        uVar2 = puVar9[2];
        bVar27 = 0x15d < uVar1;
        if (0x15e < uVar1) {
          bVar27 = uVar2 < 0x15f;
          uVar1 = uVar2;
        }
        unaff_r4 = uVar10;
      } while ((!bVar27 || uVar1 == 0x15e) &&
              (uVar10 = uVar10 + 1 & 0xfffeffff, unaff_r4 = uVar26, uVar10 < 1000));
      uVar10 = unaff_r4 + 5 & 0xfffeffff;
      uVar26 = 0;
      if (uVar10 < unaff_r4 + 0x19) {
        puVar16 = (ushort *)(iVar8 + uVar10 * 2);
        puVar9 = puVar16 + -1;
        if ((unaff_r4 - uVar10 & 1) == 0) {
          uVar26 = (uint)*puVar16;
          puVar9 = puVar16;
        }
        uVar10 = (unaff_r4 - uVar10) * 0x8000 + 0xc8000 >> 0x10;
        uVar12 = 0;
        while (uVar10 != 0) {
          puVar16 = puVar9 + 1;
          puVar9 = puVar9 + 2;
          uVar10 = uVar10 - 1 & 0xffff;
          uVar26 = uVar26 + *puVar16 & 0xfffeffff;
          uVar12 = uVar12 + *puVar9 & 0xfffeffff;
        }
        uVar26 = uVar26 + uVar12 & 0xfffeffff;
      }
      uVar12 = unaff_r4 + 0xd2 & 0xfffeffff;
      uVar10 = 0;
      uVar26 = uVar26 * DAT_80026cf4 >> 0x14;
      if (uVar12 < unaff_r4 + 0xe6) {
        puVar16 = (ushort *)(iVar8 + uVar12 * 2);
        puVar9 = puVar16 + -1;
        if (((unaff_r4 - uVar12 ^ 0xe5) & 1) == 0) {
          uVar10 = (uint)*puVar16;
          puVar9 = puVar16;
        }
        uVar12 = (unaff_r4 - uVar12) * 0x8000 + 0x730000 >> 0x10;
        uVar19 = 0;
        while (uVar12 != 0) {
          puVar16 = puVar9 + 1;
          puVar9 = puVar9 + 2;
          uVar12 = uVar12 - 1 & 0xffff;
          uVar10 = uVar10 + *puVar16 & 0xfffeffff;
          uVar19 = uVar19 + *puVar9 & 0xfffeffff;
        }
        uVar10 = uVar10 + uVar19 & 0xfffeffff;
      }
      uVar10 = DAT_80026cf4 * uVar10 >> 0x14;
      if (uVar26 < uVar10) {
        uVar26 = uVar10 - uVar26;
      }
      else {
        uVar26 = uVar26 - uVar10;
      }
      if (uVar14 == DAT_800275b4) {
        local_4c = local_4c | 0x10;
      }
      if (uVar15 == DAT_800275b4) {
        local_48 = local_48 | 0x10;
      }
      if ((uVar25 & 0xffff) < 0x65) {
        local_50 = local_50 | 0x10;
      }
      if ((uVar26 & 0xffff) < 0x65) {
        local_54 = local_54 | 0x10;
      }
    }
    else {
      if (uVar23 == 0) {
        if (uVar14 - 0x1b < 0xb) {
          local_4c = local_4c | 1;
        }
        if (uVar15 - 0x1b < 0xb) {
          local_48 = local_48 | 1;
        }
        if (uVar10 < 7) {
          local_50 = local_50 | 1;
        }
        if (uVar12 < 7) {
          local_54 = local_54 | 1;
        }
      }
      else {
        if (uVar23 == 1) {
          if (uVar14 - 0x3b < 0xd) {
            local_4c = local_4c | 2;
          }
          if (uVar15 - 0x3b < 0xd) {
            local_48 = local_48 | 2;
          }
          if (uVar10 < 0xb) {
            local_50 = local_50 | 2;
          }
          if (uVar12 < 0xb) {
            local_54 = local_54 | 2;
          }
        }
        else {
          if (uVar23 == 2) {
            if (uVar14 - 0x8e < 0x21) {
              local_4c = local_4c | 4;
            }
            if (uVar15 - 0x8e < 0x21) {
              local_48 = local_48 | 4;
            }
            if (uVar10 < 0x10) {
              local_50 = local_50 | 4;
            }
            if (uVar12 < 0x10) {
              local_54 = local_54 | 4;
            }
            if (0xa0 < (uVar26 & 0xffff) + (uVar25 & 0xffff) >> 1) {
              bVar4 = true;
            }
            if (0xa0 < (uVar19 & 0xffff) + (uVar20 & 0xffff) >> 1) {
              bVar5 = true;
            }
          }
          else {
            if (uVar23 == 3) {
              if (uVar14 - 0x11e < 0x41) {
                local_4c = local_4c | 8;
              }
              if (uVar15 - 0x11e < 0x41) {
                local_48 = local_48 | 8;
              }
              if (uVar10 < 0x1a) {
                local_50 = local_50 | 8;
              }
              if (uVar12 < 0x1a) {
                local_54 = local_54 | 8;
              }
            }
          }
        }
      }
    }
    uVar23 = uVar23 + 1 & 0xfffeffff;
    if (4 < uVar23) {
      if (local_4c == 0x1f) {
        FUN_80019704(0xffffff);
        pcVar13 = s_CH1_amplitude_OK_80027628;
      }
      else {
        local_4c = 0;
        FUN_80019704(0xff0000);
        pcVar13 = s_CH1_relay_or_resistance_ERROR_800275b8;
      }
      FUN_80018bf8(pcVar13,0x1e,100);
      if (local_50 == 0x1f) {
        FUN_80019704(0xffffff);
        pcVar13 = s_CH1_phase_OK_8002763c;
      }
      else {
        local_50 = 0;
        FUN_80019704(0xff0000);
        pcVar13 = s_CH1_capacitance_ERROR_800275d8;
      }
      FUN_80018bf8(pcVar13,0x1e,0x78);
      if (local_48 == 0x1f) {
        FUN_80019704(0xffffff);
        pcVar13 = s_CH2_amplitude_OK_8002764c;
      }
      else {
        local_48 = 0;
        FUN_80019704(0xff0000);
        pcVar13 = s_CH2_relay_or_resistance_ERROR_800275f0;
      }
      FUN_80018bf8(pcVar13,0x1e,0x8c);
      if (local_54 == 0x1f) {
        FUN_80019704(0xffffff);
        pcVar13 = s_CH2_phase_OK_80027660;
      }
      else {
        local_54 = 0;
        FUN_80019704(0xff0000);
        pcVar13 = s_CH2_capacitance_ERROR_80027610;
      }
      FUN_80018bf8(pcVar13,0x1e,0xa0);
      uVar23 = local_4c;
      if (local_4c != 0) {
        uVar23 = local_50;
      }
      if ((local_4c != 0 && uVar23 != 0) && (!bVar4)) {
        FUN_80019704(0xff0000);
        FUN_80018bf8(s_KAQY214S_1_ERROR_80027670,0x1e,0xb4);
      }
      uVar23 = local_48;
      if (local_48 != 0) {
        uVar23 = local_54;
      }
      if ((local_48 != 0 && uVar23 != 0) && (!bVar5)) {
        FUN_80019704(0xff0000);
        FUN_80018bf8(s_KAQY214S_2_ERROR_80027684,0x1e,200);
      }
      bVar27 = local_4c != 0;
      if (bVar27) {
        local_4c = local_50;
      }
      if (bVar27 && local_4c != 0) {
        bVar27 = local_48 != 0;
        if (bVar27) {
          local_48 = local_54;
        }
        if (bVar27 && local_48 != 0) {
          bVar27 = bVar4;
          if (bVar4) {
            bVar27 = bVar5;
          }
          if (bVar4 && bVar27) {
            FUN_80019704(0xffffff);
            FUN_80018bf8(s_Channel_Checked_Successful___80027698,0x1e,200);
            iVar8 = DAT_80026ce8;
            *(undefined *)(DAT_80026ce8 + 3) = 0;
            *(undefined2 *)(iVar8 + 6) = 300;
            *(undefined *)(iVar8 + 0xf) = 0;
            *(undefined2 *)(iVar8 + 0x12) = 100;
            *(undefined *)(iVar8 + 10) = 0x13;
            FUN_8000696c();
            FUN_800096b8();
            FUN_8000689c();
            FUN_800095e8();
            FUN_800266c4();
            FUN_80025bb0();
            FUN_80025bf8(2);
            uVar14 = FUN_80023564(0,700);
            uVar23 = uVar14;
            do {
              uVar28 = FUN_80023564(uVar14);
              uVar14 = (int)uVar28 - uVar23;
            } while (uVar14 < (uint)((ulonglong)uVar28 >> 0x20));
            return;
          }
        }
      }
      do {
                    // WARNING: Do nothing block with infinite loop
      } while( true );
    }
  } while( true );
}

