void FUN_80028828(undefined4 param_1,undefined4 param_2,undefined *param_3)

{
  char cVar1;
  ushort uVar2;
  int *piVar3;
  undefined4 uVar4;
  undefined uVar5;
  short sVar6;
  int iVar7;
  undefined *puVar8;
  short sVar9;
  undefined *puVar10;
  short *psVar11;
  short *psVar12;
  undefined *puVar13;
  undefined *puVar14;
  uint uVar15;
  uint uVar16;
  char *pcVar17;
  undefined *puVar18;
  uint uVar19;
  int iVar20;
  int iVar21;
  undefined *in_r12;
  uint uVar22;
  uint uVar23;
  bool bVar24;
  bool bVar25;
  bool bVar26;
  code **ppcVar27;
  undefined8 uVar28;
  char *in_stack_ffffffd8;
  undefined *in_stack_ffffffdc;
  undefined uVar29;
  undefined4 in_stack_ffffffe0;
  code *UNRECOVERED_JUMPTABLE;
  
  pcVar17 = DAT_80029140;
  puVar18 = DAT_8002913c;
  ppcVar27 = (code **)&stack0xffffffd8;
  uVar5 = 0;
  *DAT_8002913c = 0;
  iVar20 = 0;
  iVar21 = 0;
  bVar25 = false;
  if (pcVar17[6] == '\0') {
                    // WARNING: Could not recover jumptable at 0x8002885c. Too many branches
                    // WARNING: Treating indirect jump as call
    (*UNRECOVERED_JUMPTABLE)();
    return;
  }
  tp_i2c_read_status();
  puVar10 = (undefined *)(uint)*(ushort *)(pcVar17 + 2);
  puVar8 = (undefined *)(uint)*(ushort *)PTR_DAT_80029144;
  if ((puVar8 < puVar10) && (param_3 = PTR_DAT_80029144, puVar10 < puVar8 + 0x95)) {
    puVar13 = (undefined *)(uint)*(ushort *)(pcVar17 + 4);
    param_3 = (undefined *)(uint)*(ushort *)(PTR_DAT_80029144 + 2);
    bVar26 = param_3 <= puVar13;
    bVar24 = puVar13 == param_3;
    if (bVar26 && !bVar24) {
      param_3 = param_3 + 0x3b;
    }
    if (bVar26 && !bVar24) {
      bVar26 = puVar13 <= param_3;
      bVar24 = param_3 == puVar13;
    }
    if (!bVar26 || bVar24) goto LAB_800288e8;
    cVar1 = *pcVar17;
    while (cVar1 != '\0') {
      *puVar18 = 1;
      FUN_8000e1e4();
      tp_i2c_read_status();
      cVar1 = *pcVar17;
    }
    if (pcVar17[7] == '\0') {
      pcVar17[7] = '\x01';
      FUN_800268c8();
      FUN_80011640();
      FUN_80010bd0();
      goto LAB_80028a48;
    }
  }
  else {
LAB_800288e8:
    bVar26 = puVar8 <= puVar10;
    bVar24 = puVar10 == puVar8;
    if (bVar26 && !bVar24) {
      param_3 = puVar8 + 0x95;
    }
    if (bVar26 && !bVar24) {
      bVar26 = puVar10 <= param_3;
      bVar24 = param_3 == puVar10;
    }
    if (bVar26 && !bVar24) {
      puVar13 = (undefined *)(uint)*(ushort *)(PTR_DAT_80029144 + 2);
      param_3 = (undefined *)(uint)*(ushort *)(pcVar17 + 4);
      in_r12 = puVar13 + 0x3b;
      bVar26 = in_r12 <= param_3;
      bVar24 = param_3 == in_r12;
      if (bVar26 && !bVar24) {
        puVar13 = puVar13 + 0x76;
      }
      if (bVar26 && !bVar24) {
        bVar26 = param_3 <= puVar13;
        bVar24 = puVar13 == param_3;
      }
      if (bVar26 && !bVar24) {
        cVar1 = *pcVar17;
        while (cVar1 != '\0') {
          *puVar18 = 2;
          FUN_8000e1e4();
          tp_i2c_read_status();
          cVar1 = *pcVar17;
        }
        *PTR_DAT_80029148 = 0;
        FUN_8002be60();
        FUN_8000a750();
        FUN_8000e8f0();
        goto LAB_80028a48;
      }
    }
    bVar26 = puVar8 <= puVar10;
    bVar24 = puVar10 == puVar8;
    if (bVar26 && !bVar24) {
      param_3 = puVar8 + 0x95;
    }
    if (bVar26 && !bVar24) {
      bVar26 = puVar10 <= param_3;
      bVar24 = param_3 == puVar10;
    }
    if (bVar26 && !bVar24) {
      puVar13 = (undefined *)(uint)*(ushort *)(PTR_DAT_80029144 + 2);
      param_3 = (undefined *)(uint)*(ushort *)(pcVar17 + 4);
      in_r12 = puVar13 + 0x76;
      bVar26 = in_r12 <= param_3;
      bVar24 = param_3 == in_r12;
      if (bVar26 && !bVar24) {
        puVar13 = puVar13 + 0xb1;
      }
      if (bVar26 && !bVar24) {
        bVar26 = param_3 <= puVar13;
        bVar24 = puVar13 == param_3;
      }
      if (bVar26 && !bVar24) {
        cVar1 = *pcVar17;
        while (cVar1 != '\0') {
          *puVar18 = 3;
          FUN_8000e1e4();
          tp_i2c_read_status();
          cVar1 = *pcVar17;
        }
        *PTR_DAT_80029148 = 1;
        FUN_8002be60();
        FUN_8000a750();
        FUN_8000e8f0();
        goto LAB_80028a48;
      }
    }
    bVar26 = puVar8 <= puVar10;
    bVar24 = puVar10 == puVar8;
    if (bVar26 && !bVar24) {
      puVar8 = puVar8 + 0x95;
    }
    if (bVar26 && !bVar24) {
      bVar26 = puVar10 <= puVar8;
      bVar24 = puVar8 == puVar10;
    }
    if (bVar26 && !bVar24) {
      puVar10 = (undefined *)(uint)*(ushort *)(PTR_DAT_80029144 + 2);
      puVar8 = (undefined *)(uint)*(ushort *)(pcVar17 + 4);
      param_3 = puVar10 + 0xb1;
      bVar26 = param_3 <= puVar8;
      bVar24 = puVar8 == param_3;
      if (bVar26 && !bVar24) {
        puVar10 = puVar10 + 0xec;
      }
      if (bVar26 && !bVar24) {
        bVar26 = puVar8 <= puVar10;
        bVar24 = puVar10 == puVar8;
      }
      if (bVar26 && !bVar24) {
        cVar1 = *pcVar17;
        while (cVar1 != '\0') {
          *puVar18 = 4;
          FUN_8000e1e4();
          tp_i2c_read_status();
          cVar1 = *pcVar17;
        }
        FUN_8000a750();
        FUN_80029eb0();
        FUN_80021ef4();
        set_frame_to_global_pointer();
        FUN_80029f00();
        copy_frame_to_screen();
        FUN_8000a750();
        FUN_8000e8f0();
        goto LAB_80028a48;
      }
    }
    if (*pcVar17 != '\0') {
      iVar20 = 1;
    }
LAB_80028a48:
    if (pcVar17[7] == '\0') {
      if (*pcVar17 == '\0' || iVar20 == 0) {
                    // WARNING: Could not recover jumptable at 0x80029138. Too many branches
                    // WARNING: Treating indirect jump as call
        (*UNRECOVERED_JUMPTABLE)();
        return;
      }
      goto code_r0x8000a750;
    }
  }
  uVar29 = (undefined)in_stack_ffffffe0;
  puVar10 = (undefined *)(uint)*(ushort *)(pcVar17 + 2);
  puVar8 = (undefined *)(uint)*(ushort *)(PTR_DAT_80029144 + 4);
  if ((puVar8 < puVar10) && (param_3 = puVar8 + 0xf4, puVar10 < param_3)) {
    param_3 = (undefined *)(uint)*(ushort *)(pcVar17 + 4);
    puVar13 = (undefined *)(uint)*(ushort *)(PTR_DAT_80029144 + 6);
    bVar26 = puVar13 <= param_3;
    bVar24 = param_3 == puVar13;
    if (bVar26 && !bVar24) {
      puVar13 = puVar13 + 0x3b;
    }
    if (bVar26 && !bVar24) {
      bVar26 = param_3 <= puVar13;
      bVar24 = puVar13 == param_3;
    }
    if (!bVar26 || bVar24) goto LAB_80028b08;
    cVar1 = *pcVar17;
    while (uVar29 = (undefined)in_stack_ffffffe0, cVar1 != '\0') {
      puVar18[1] = 1;
      FUN_80010bd0();
      tp_i2c_read_status();
      cVar1 = *pcVar17;
    }
    if (pcVar17[9] == '\x01') {
      pcVar17[9] = '\0';
      FUN_800114f4(0);
      FUN_80009e9c();
    }
    if (pcVar17[10] == '\x01') {
      pcVar17[10] = '\0';
      FUN_80002b3c();
    }
    if (pcVar17[8] == '\0') {
      pcVar17[8] = '\x01';
      FUN_8001c690();
      FUN_8001178c();
      FUN_80011764();
      FUN_800117a8(1);
    }
  }
  else {
LAB_80028b08:
    bVar26 = puVar8 <= puVar10;
    bVar24 = puVar10 == puVar8;
    if (bVar26 && !bVar24) {
      param_3 = puVar8 + 0xf4;
    }
    if (bVar26 && !bVar24) {
      bVar26 = puVar10 <= param_3;
      bVar24 = param_3 == puVar10;
    }
    if (bVar26 && !bVar24) {
      param_3 = (undefined *)(uint)*(ushort *)(PTR_DAT_80029144 + 6);
      puVar13 = (undefined *)(uint)*(ushort *)(pcVar17 + 4);
      in_r12 = param_3 + 0x3b;
      bVar26 = in_r12 <= puVar13;
      bVar24 = puVar13 == in_r12;
      if (bVar26 && !bVar24) {
        param_3 = param_3 + 0x76;
      }
      if (bVar26 && !bVar24) {
        bVar26 = puVar13 <= param_3;
        bVar24 = param_3 == puVar13;
      }
      if (bVar26 && !bVar24) {
        cVar1 = *pcVar17;
        while (cVar1 != '\0') {
          puVar18[1] = 2;
          FUN_80010bd0();
          tp_i2c_read_status();
          uVar29 = (undefined)in_stack_ffffffe0;
          cVar1 = *pcVar17;
        }
        if (pcVar17[8] == '\x01') {
          pcVar17[8] = '\0';
          FUN_800117a8(0);
          FUN_8001c6c0();
        }
        if (pcVar17[10] == '\x01') {
          pcVar17[10] = '\0';
          FUN_80002b3c();
        }
        if (pcVar17[9] == '\0') {
          pcVar17[9] = '\x01';
          FUN_80009e5c();
          FUN_800114d0();
          FUN_800114a0();
          FUN_800114f4(1);
        }
        goto LAB_80028dcc;
      }
    }
    bVar26 = puVar8 <= puVar10;
    bVar24 = puVar10 == puVar8;
    if (bVar26 && !bVar24) {
      param_3 = puVar8 + 0xf4;
    }
    if (bVar26 && !bVar24) {
      bVar26 = puVar10 <= param_3;
      bVar24 = param_3 == puVar10;
    }
    if (!bVar26 || bVar24) {
LAB_80028c60:
      bVar26 = puVar8 <= puVar10;
      bVar24 = puVar10 == puVar8;
      if (bVar26 && !bVar24) {
        param_3 = puVar8 + 0xf4;
      }
      if (bVar26 && !bVar24) {
        bVar26 = puVar10 <= param_3;
        bVar24 = param_3 == puVar10;
      }
      if (bVar26 && !bVar24) {
        puVar14 = (undefined *)(uint)*(ushort *)(PTR_DAT_80029144 + 6);
        puVar13 = (undefined *)(uint)*(ushort *)(pcVar17 + 4);
        in_r12 = puVar14 + 0xb1;
        bVar26 = in_r12 <= puVar13;
        bVar24 = puVar13 == in_r12;
        if (bVar26 && !bVar24) {
          puVar14 = puVar14 + 0xec;
        }
        if (bVar26 && !bVar24) {
          bVar26 = puVar13 <= puVar14;
          bVar24 = puVar14 == puVar13;
        }
        if (bVar26 && !bVar24) {
          cVar1 = *pcVar17;
          while (cVar1 != '\0') {
            puVar18[1] = 4;
            FUN_80010bd0();
            tp_i2c_read_status();
            uVar29 = (undefined)in_stack_ffffffe0;
            cVar1 = *pcVar17;
          }
          if (pcVar17[8] == '\x01') {
            pcVar17[8] = '\0';
            FUN_800117a8(0);
            FUN_8001c6c0();
          }
          if (pcVar17[9] == '\x01') {
            pcVar17[9] = '\0';
            FUN_800114f4(0);
            FUN_80009e9c();
          }
          if (pcVar17[10] == '\0') {
            pcVar17[10] = '\x01';
            puVar18[8] = 0;
            FUN_80002afc();
            FUN_80011154();
            FUN_80010f08();
          }
          goto LAB_80028dcc;
        }
      }
      bVar26 = puVar8 <= puVar10;
      bVar24 = puVar10 == puVar8;
      if (bVar26 && !bVar24) {
        puVar8 = puVar8 + 0xf4;
      }
      if (bVar26 && !bVar24) {
        bVar26 = puVar10 <= puVar8;
        bVar24 = puVar8 == puVar10;
      }
      if (bVar26 && !bVar24) {
        if ((*(ushort *)(PTR_DAT_80029144 + 6) + 0xec < (uint)*(ushort *)(pcVar17 + 4)) &&
           ((uint)*(ushort *)(pcVar17 + 4) < *(ushort *)(PTR_DAT_80029144 + 6) + 0x127)) {
          cVar1 = *pcVar17;
          while (uVar29 = (undefined)in_stack_ffffffe0, cVar1 != '\0') {
            tp_i2c_read_status();
            cVar1 = *pcVar17;
          }
          if (puVar18[7] == '\0') {
            puVar18[7] = 1;
          }
          else {
            puVar18[7] = 0;
          }
          puVar18[1] = 0;
          if (pcVar17[8] == '\x01') {
            pcVar17[8] = '\0';
            FUN_800117a8(0);
            FUN_8001c6c0();
          }
          if (pcVar17[9] == '\x01') {
            pcVar17[9] = '\0';
            FUN_800114f4(0);
            FUN_80009e9c();
          }
          cVar1 = pcVar17[10];
          goto joined_r0x80028db4;
        }
      }
      if (*pcVar17 != '\0') {
        iVar21 = 1;
      }
    }
    else {
      param_3 = (undefined *)(uint)*(ushort *)(PTR_DAT_80029144 + 6);
      puVar13 = (undefined *)(uint)*(ushort *)(pcVar17 + 4);
      in_r12 = param_3 + 0x76;
      bVar26 = in_r12 <= puVar13;
      bVar24 = puVar13 == in_r12;
      if (bVar26 && !bVar24) {
        param_3 = param_3 + 0xb1;
      }
      if (bVar26 && !bVar24) {
        bVar26 = puVar13 <= param_3;
        bVar24 = param_3 == puVar13;
      }
      if (!bVar26 || bVar24) goto LAB_80028c60;
      cVar1 = *pcVar17;
      while (uVar29 = (undefined)in_stack_ffffffe0, cVar1 != '\0') {
        tp_i2c_read_status();
        cVar1 = *pcVar17;
      }
      if (puVar18[4] == '\0') {
        puVar18[4] = 1;
      }
      else {
        puVar18[4] = 0;
      }
      puVar18[1] = 0;
      if (pcVar17[8] == '\x01') {
        pcVar17[8] = '\0';
        FUN_800117a8(0);
        FUN_8001c6c0();
      }
      if (pcVar17[9] == '\x01') {
        pcVar17[9] = '\0';
        FUN_800114f4(0);
        FUN_80009e9c();
      }
      cVar1 = pcVar17[10];
joined_r0x80028db4:
      if (cVar1 == '\x01') {
        pcVar17[10] = '\0';
        FUN_80002b3c();
      }
      FUN_80010bd0();
    }
  }
LAB_80028dcc:
  uVar4 = DAT_80029150;
  uVar16 = DAT_8002914c;
  if (pcVar17[8] == '\x01') {
    uVar23 = (uint)*(ushort *)(pcVar17 + 2);
    uVar19 = (uint)*(ushort *)(PTR_DAT_80029144 + 4);
    uVar15 = uVar19 + 0x108;
    bVar26 = uVar15 <= uVar23;
    bVar24 = uVar23 == uVar15;
    if (bVar26 && !bVar24) {
      uVar15 = uVar19 + 0x200;
    }
    if (bVar26 && !bVar24) {
      uVar15 = uVar15 + 0x2b;
    }
    if (bVar26 && !bVar24) {
      bVar26 = uVar23 <= uVar15;
      bVar24 = uVar15 == uVar23;
    }
    if (bVar26 && !bVar24) {
      uVar22 = (uint)*(ushort *)(pcVar17 + 4);
      uVar15 = (uint)*(ushort *)(PTR_DAT_80029144 + 6);
      bVar26 = uVar15 <= uVar22;
      bVar24 = uVar22 == uVar15;
      if (bVar26 && !bVar24) {
        uVar15 = uVar15 + 0x3b;
      }
      if (bVar26 && !bVar24) {
        bVar26 = uVar22 <= uVar15;
        bVar24 = uVar15 == uVar22;
      }
      if (bVar26 && !bVar24) {
        cVar1 = *pcVar17;
        while (cVar1 != '\0') {
          uVar23 = (uint)*(ushort *)(pcVar17 + 2);
          uVar19 = uVar16;
          if ((0x19c < uVar23) && (uVar19 = uVar23, 0x2c0 < uVar23)) {
            uVar19 = 0x2c0;
          }
          uVar28 = FUN_8003979c(uVar19 - 0x19d);
          FUN_800393ec((int)uVar28,(int)((ulonglong)uVar28 >> 0x20),DAT_80029154,uVar4);
          uVar5 = FUN_8003972c();
          puVar18[2] = uVar5;
          get_brightness_from_settings();
          FUN_800117a8(1);
          FUN_80011764();
          tp_i2c_read_status();
          cVar1 = *pcVar17;
        }
        goto LAB_80028f04;
      }
    }
    if ((uVar19 + 0xf4 < uVar23) && (uVar23 < uVar19 + 0x23f)) {
      uVar19 = (uint)*(ushort *)(pcVar17 + 4);
      uVar16 = (uint)*(ushort *)(PTR_DAT_80029144 + 6);
      bVar26 = uVar16 <= uVar19;
      bVar24 = uVar19 == uVar16;
      if (bVar26 && !bVar24) {
        uVar16 = uVar16 + 0x3b;
      }
      if (bVar26 && !bVar24) {
        bVar26 = uVar19 <= uVar16;
        bVar24 = uVar16 == uVar19;
      }
      if (bVar26 && !bVar24) goto LAB_80028f04;
    }
    cVar1 = *pcVar17;
joined_r0x80028f00:
    if (cVar1 != '\0') {
      bVar25 = true;
    }
  }
  else {
    if (pcVar17[9] != '\x01') {
      if (pcVar17[10] == '\x01') {
        puVar8 = (undefined *)(uint)*(ushort *)(pcVar17 + 2);
        uVar16 = (uint)*(ushort *)(PTR_DAT_80029144 + 4);
        puVar10 = (undefined *)(uVar16 + 0x16e);
        bVar24 = puVar10 <= puVar8;
        bVar25 = puVar8 == puVar10;
        if (bVar24 && !bVar25) {
          in_r12 = (undefined *)(uVar16 + 0x1b0);
        }
        if (bVar24 && !bVar25) {
          bVar24 = puVar8 <= in_r12;
          bVar25 = in_r12 == puVar8;
        }
        if (bVar24 && !bVar25) {
          uVar19 = (uint)*(ushort *)(PTR_DAT_80029144 + 6);
          uVar23 = (uint)*(ushort *)(pcVar17 + 4);
          bVar24 = uVar19 + 0xb7 <= uVar23;
          bVar25 = uVar23 == uVar19 + 0xb7;
          if (bVar24 && !bVar25) {
            uVar19 = uVar19 + 0xe3;
          }
          if (bVar24 && !bVar25) {
            bVar24 = uVar23 <= uVar19;
            bVar25 = uVar19 == uVar23;
          }
          if (bVar24 && !bVar25) {
            if (puVar18[8] != '\0') {
                    // WARNING: Could not recover jumptable at 0x80029068. Too many branches
                    // WARNING: Treating indirect jump as call
              (*UNRECOVERED_JUMPTABLE)();
              return;
            }
            cVar1 = *pcVar17;
            while (cVar1 != '\0') {
              puVar18[9] = 1;
              FUN_80010f08();
              tp_i2c_read_status();
              cVar1 = *pcVar17;
            }
            puVar18[9] = 0;
            FUN_80002b3c();
            FUN_80011254();
            iVar20 = FUN_80027ef8();
            puVar18[8] = (char)iVar20;
            if (iVar20 != 0) {
              signal_sys_ok();
            }
            FUN_80002b3c();
            sVar6 = FUN_800232b4(DAT_80011484);
            iVar20 = DAT_80011498;
            piVar3 = Global_Frame_Buffer_Pointer;
            puVar8 = PTR_DAT_80011490;
            puVar18 = PTR_DAT_8001148c;
            uVar16 = 0;
            *(undefined *)(DAT_80011488 + 8) = 1;
            do {
              iVar21 = 0x6e;
              psVar11 = (short *)(*piVar3 + ((uint)*(ushort *)(puVar8 + 4) +
                                            (*(ushort *)(puVar8 + 6) + uVar16) * 800) * 2 + iVar20);
              psVar12 = (short *)(puVar18 + uVar16 * 0xdc);
              do {
                sVar9 = *psVar12;
                if (*psVar12 == 0) {
                  sVar9 = sVar6;
                }
                iVar21 = iVar21 + -1;
                *psVar11 = sVar9;
                psVar11 = psVar11 + 1;
                psVar12 = psVar12 + 1;
              } while (iVar21 != 0);
              uVar16 = uVar16 + 1 & 0xfffeffff;
            } while (uVar16 < 0x3c);
            set_display_color(DAT_8001149c);
            FUN_80018da0(*(ushort *)(puVar8 + 4) + 0xf4,*(ushort *)(puVar8 + 6) + 0xaf,
                         *(ushort *)(puVar8 + 4) + 0x162,*(ushort *)(puVar8 + 6) + 0xea);
            iVar21 = Start_Of_Screen_Mem;
            iVar20 = Screen_Frame_Buffer;
            uVar2 = *(ushort *)(puVar8 + 4);
            uVar19 = *(ushort *)(puVar8 + 6) + 0xaf & 0xfffeffff;
            uVar23 = *(ushort *)(puVar8 + 6) + 0xeb & 0xfffeffff;
            uVar16 = uVar2 + 0xf4 & 0xfffeffff;
            if (uVar23 <= uVar19) {
              return;
            }
            do {
              iVar7 = uVar16 + uVar19 * 800;
              copy_short((void *)(iVar21 + iVar7 * 2),(void *)(iVar20 + iVar7 * 2),
                         ((uVar2 + 0x162 & 0xfffeffff) - uVar16) + 1);
              uVar19 = uVar19 + 1;
            } while (uVar19 < uVar23);
            return;
          }
        }
        bVar24 = (undefined *)(uVar16 + 0xf4) <= puVar8;
        bVar25 = puVar8 == (undefined *)(uVar16 + 0xf4);
        if (bVar24 && !bVar25) {
          bVar24 = puVar8 <= puVar10;
          bVar25 = puVar10 == puVar8;
        }
        if (bVar24 && !bVar25) {
          uVar16 = (uint)*(ushort *)(PTR_DAT_80029144 + 6);
          uVar19 = (uint)*(ushort *)(pcVar17 + 4);
          bVar24 = uVar16 + 0xb1 <= uVar19;
          bVar25 = uVar19 == uVar16 + 0xb1;
          if (bVar24 && !bVar25) {
            uVar16 = uVar16 + 0xed;
          }
          if (bVar24 && !bVar25) {
            bVar24 = uVar19 <= uVar16;
            bVar25 = uVar16 == uVar19;
          }
          if (bVar24 && !bVar25) {
            ppcVar27 = (code **)&stack0xffffffec;
            pcVar17 = in_stack_ffffffd8;
            puVar18 = in_stack_ffffffdc;
            uVar5 = uVar29;
          }
          if (bVar24 && !bVar25) {
            iVar20 = (int)*ppcVar27;
            iVar21 = ((int *)ppcVar27)[1];
            ppcVar27 = (code **)((int *)ppcVar27 + 4);
          }
                    // WARNING: Could not recover jumptable at 0x800290ec. Too many branches
                    // WARNING: Treating indirect jump as call
          if (bVar24 && !bVar25) {
            (**ppcVar27)();
            return;
          }
        }
        if (*pcVar17 == '\0') {
                    // WARNING: Could not recover jumptable at 0x80029100. Too many branches
                    // WARNING: Treating indirect jump as call
          (**(code **)((int)ppcVar27 + 0x24))();
          return;
        }
        puVar18[8] = uVar5;
        if (iVar20 == 0 || iVar21 == 0) {
                    // WARNING: Could not recover jumptable at 0x80029118. Too many branches
                    // WARNING: Treating indirect jump as call
          (**(code **)((undefined *)((int)ppcVar27 + 0x14) + 0x10))();
          return;
        }
      }
      else {
        bVar26 = *pcVar17 == '\0';
        bVar25 = iVar20 == 0;
        bVar24 = iVar21 == 0;
        if ((bVar26 || bVar25) || bVar24) {
          ppcVar27 = (code **)&stack0xffffffec;
        }
        if ((bVar26 || bVar25) || bVar24) {
          ppcVar27 = (code **)((int)ppcVar27 + 0x10);
        }
                    // WARNING: Could not recover jumptable at 0x80028e0c. Too many branches
                    // WARNING: Treating indirect jump as call
        if ((bVar26 || bVar25) || bVar24) {
          (**ppcVar27)();
          return;
        }
      }
      goto code_r0x8000a750;
    }
    uVar23 = (uint)*(ushort *)(pcVar17 + 2);
    uVar19 = (uint)*(ushort *)(PTR_DAT_80029144 + 4);
    uVar15 = uVar19 + 0x108;
    bVar26 = uVar15 <= uVar23;
    bVar24 = uVar23 == uVar15;
    if (bVar26 && !bVar24) {
      uVar15 = uVar19 + 0x200;
    }
    if (bVar26 && !bVar24) {
      uVar15 = uVar15 + 0x2b;
    }
    if (bVar26 && !bVar24) {
      bVar26 = uVar23 <= uVar15;
      bVar24 = uVar15 == uVar23;
    }
    if (bVar26 && !bVar24) {
      uVar15 = (uint)*(ushort *)(PTR_DAT_80029144 + 6);
      uVar22 = (uint)*(ushort *)(pcVar17 + 4);
      bVar26 = uVar15 + 0x3b <= uVar22;
      bVar24 = uVar22 == uVar15 + 0x3b;
      if (bVar26 && !bVar24) {
        uVar15 = uVar15 + 0x76;
      }
      if (bVar26 && !bVar24) {
        bVar26 = uVar22 <= uVar15;
        bVar24 = uVar15 == uVar22;
      }
      if (bVar26 && !bVar24) {
        cVar1 = *pcVar17;
        while (cVar1 != '\0') {
          uVar23 = (uint)*(ushort *)(pcVar17 + 2);
          uVar19 = uVar16;
          if ((0x19c < uVar23) && (uVar19 = uVar23, 0x2c0 < uVar23)) {
            uVar19 = 0x2c0;
          }
          uVar28 = FUN_8003979c(uVar19 - 0x19d);
          FUN_800393ec((int)uVar28,(int)((ulonglong)uVar28 >> 0x20),DAT_80029154,uVar4);
          uVar5 = FUN_8003972c();
          puVar18[3] = uVar5;
          FUN_800114f4(1);
          FUN_800114a0();
          tp_i2c_read_status();
          cVar1 = *pcVar17;
        }
        goto LAB_80028f04;
      }
    }
    if ((uVar23 <= uVar19 + 0xf4) || (uVar19 + 0x23f <= uVar23)) {
LAB_80029004:
      cVar1 = *pcVar17;
      goto joined_r0x80028f00;
    }
    uVar16 = (uint)*(ushort *)(PTR_DAT_80029144 + 6);
    uVar19 = (uint)*(ushort *)(pcVar17 + 4);
    bVar26 = uVar16 + 0x3b <= uVar19;
    bVar24 = uVar19 == uVar16 + 0x3b;
    if (bVar26 && !bVar24) {
      uVar16 = uVar16 + 0x76;
    }
    if (bVar26 && !bVar24) {
      bVar26 = uVar19 <= uVar16;
      bVar24 = uVar16 == uVar19;
    }
    if (!bVar26 || bVar24) goto LAB_80029004;
  }
LAB_80028f04:
  bVar26 = iVar20 == 0;
  bVar24 = iVar21 == 0;
  bVar25 = !bVar25;
  puVar18[8] = 0;
  if ((bVar26 || bVar24) || bVar25) {
    ppcVar27 = (code **)&stack0xffffffec;
  }
  if ((bVar26 || bVar24) || bVar25) {
    ppcVar27 = (code **)((int)ppcVar27 + 0x10);
  }
                    // WARNING: Could not recover jumptable at 0x80028f1c. Too many branches
                    // WARNING: Treating indirect jump as call
  if ((bVar26 || bVar24) || bVar25) {
    (**ppcVar27)();
    return;
  }
code_r0x8000a750:
  puVar18 = DAT_8000a7ec;
  ppcVar27[9] = ppcVar27[9];
  ppcVar27[8] = ppcVar27[2];
  ppcVar27[7] = ppcVar27[1];
  ppcVar27[6] = *ppcVar27;
  if (DAT_8000a7ec[10] == '\x01') {
    DAT_8000a7ec[10] = 0;
    FUN_80002b3c();
  }
  if (puVar18[8] == '\x01') {
    puVar18[8] = 0;
    FUN_800117a8(0);
    FUN_8001c6c0();
  }
  if (puVar18[9] == '\x01') {
    puVar18[9] = 0;
    FUN_800114f4(0);
    FUN_80009e9c();
  }
  if (puVar18[7] == '\x01') {
    FUN_800268ec();
  }
  FUN_80016b8c();
  puVar18[8] = 0;
  puVar18[9] = 0;
  puVar18[10] = 0;
  puVar18[6] = 0;
  puVar18[0xb] = 0;
  *puVar18 = 0;
  puVar18[7] = 0;
  puVar18[0xc] = 0;
  puVar8 = DAT_8000a7f0;
  *(undefined2 *)(puVar18 + 2) = 0;
  *(undefined2 *)(puVar18 + 4) = 0;
  *puVar8 = 0;
  puVar8[1] = 0;
  return;
}


