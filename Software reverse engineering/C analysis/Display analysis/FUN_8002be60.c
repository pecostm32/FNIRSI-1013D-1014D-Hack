void FUN_8002be60(void)

{
  uint uVar1;
  char cVar2;
  bool bVar3;
  ushort ysize;
  char *pcVar4;
  int *piVar5;
  int count;
  undefined *puVar6;
  undefined *puVar7;
  short sVar8;
  short sVar9;
  short sVar10;
  short sVar11;
  short sVar12;
  int iVar13;
  uint uVar14;
  uint uVar15;
  int iVar16;
  short *psVar17;
  short *psVar18;
  undefined auStack592 [556];
  
  iVar16 = DAT_8002c570;
  bVar3 = false;
  *(undefined *)(DAT_8002c570 + 0x3a) = 0;
  *(undefined *)(iVar16 + 0x43) = 0;
  FUN_800019fc(DAT_8002c574);
  pcVar4 = DAT_8002c578;
  *DAT_8002c578 = '\0';
  pcVar4[10] = '\x01';
  *(undefined2 *)(pcVar4 + 2) = 0xb4;
  *(undefined2 *)(pcVar4 + 4) = 0x75;
  *(undefined2 *)(pcVar4 + 6) = 2;
  *(undefined2 *)(pcVar4 + 8) = 2;
  FUN_80000878(pcVar4 + 0xd,0x10);
  FUN_800105e0();
  some_sd_card_stuff_3();
  FUN_8002b9bc();
  piVar5 = Global_Frame_Buffer_Pointer;
LAB_8002bed0:
  do {
    iVar13 = FUN_80022204();
    iVar16 = DAT_8002c570;
  } while (iVar13 == 0);
  if (iVar13 == 1) {
    *(undefined *)(DAT_8002c570 + 0x43) = 0;
    FUN_80001358(DAT_8002c574);
    *(undefined *)(iVar16 + 0x21) = 0;
    FUN_8000689c();
    FUN_800095e8();
    FUN_800266c4();
    FUN_800267e8();
    FUN_80002790();
    FUN_80026808();
    FUN_800267c4();
    FUN_80026828();
    FUN_8000696c();
    FUN_800096b8();
    *(undefined2 *)PTR_DAT_8002c5b4 = 0;
    FUN_8000e8f0();
    *Global_Frame_Buffer_Pointer = Start_Of_Screen_Mem;
    return;
  }
  if (iVar13 == 2) {
    bVar3 = !bVar3;
    FUN_800106a4(0);
    *pcVar4 = '\0';
    if (!bVar3) {
      FUN_800107f4(0);
      iVar13 = DAT_8002c584;
      iVar16 = Screen_Frame_Buffer_2;
      uVar15 = 0;
      do {
        memcpy((void *)(*piVar5 + uVar15 * 0x640),(void *)(iVar16 + uVar15 * 0x640),iVar13);
        uVar15 = uVar15 + 1 & 0xfffeffff;
      } while (uVar15 < 0x1e0);
      FUN_80000878(pcVar4 + 0xd,0x10);
      goto LAB_8002bed0;
    }
    *pcVar4 = '\x01';
    FUN_800107f4();
    FUN_80000868(pcVar4 + 0xd,0x10,1);
    FUN_8002c5b8();
  }
  else {
    if (iVar13 == 3) {
      bVar3 = false;
      if (*pcVar4 == '\0') {
        *pcVar4 = '\x01';
      }
      else {
        *pcVar4 = '\0';
      }
      FUN_800107f4(0);
      if (*pcVar4 == '\0') {
        FUN_800106a4(0);
        count = DAT_8002c584;
        iVar16 = Screen_Frame_Buffer_2;
        uVar15 = 0;
        do {
          memcpy((void *)(*piVar5 + uVar15 * 0x640),(void *)(iVar16 + uVar15 * 0x640),count);
          uVar15 = uVar15 + 1 & 0xfffeffff;
        } while (uVar15 < 0x1e0);
        FUN_80000878(pcVar4 + 0xd,0x10);
      }
      else {
        FUN_800106a4(1);
      }
      goto LAB_8002c1ac;
    }
    if (iVar13 != 4) {
      if (iVar13 == 5) {
        if (1 < (byte)pcVar4[10]) {
          if (*pcVar4 != '\0') {
            *pcVar4 = '\0';
            FUN_800106a4(0);
            FUN_800107f4(0);
            iVar13 = DAT_8002c584;
            iVar16 = Screen_Frame_Buffer_2;
            uVar15 = 0;
            do {
              memcpy((void *)(*piVar5 + uVar15 * 0x640),(void *)(iVar16 + uVar15 * 0x640),iVar13);
              uVar15 = uVar15 + 1 & 0xfffeffff;
            } while (uVar15 < 0x1e0);
            FUN_80000878(pcVar4 + 0xd,0x10);
          }
          pcVar4[10] = pcVar4[10] + -1;
          goto LAB_8002c510;
        }
      }
      else {
        if (iVar13 != 6) goto LAB_8002c1ac;
        if ((byte)pcVar4[10] < (byte)pcVar4[0xb]) {
          if (*pcVar4 != '\0') {
            *pcVar4 = '\0';
            FUN_800106a4(0);
            FUN_800107f4(0);
            iVar13 = DAT_8002c584;
            iVar16 = Screen_Frame_Buffer_2;
            uVar15 = 0;
            do {
              memcpy((void *)(*piVar5 + uVar15 * 0x640),(void *)(iVar16 + uVar15 * 0x640),iVar13);
              uVar15 = uVar15 + 1 & 0xfffeffff;
            } while (uVar15 < 0x1e0);
            FUN_80000878(pcVar4 + 0xd,0x10);
          }
          pcVar4[10] = pcVar4[10] + '\x01';
          FUN_8002b9bc();
        }
      }
      goto LAB_8002bed0;
    }
    if (*pcVar4 != '\0') {
      sVar10 = FUN_800232b4(DAT_8002c588);
      sVar11 = FUN_800232b4(DAT_8002c58c);
      sVar8 = FUN_800232b4(DAT_8002c590);
      set_screen_to_global_pointer();
      puVar6 = PTR_DAT_8002c594;
      uVar15 = 0xc0;
      do {
        iVar16 = 0xb4;
        psVar17 = (short *)(*piVar5 + uVar15 * 0x640 + 0x226);
        psVar18 = (short *)(puVar6 + uVar15 * 0x2d0 + -0x21c00);
        do {
          sVar12 = *psVar18;
          sVar9 = sVar8;
          if (((sVar12 != 0) && (sVar9 = sVar10, sVar12 != -0x800)) &&
             (sVar9 = sVar12, sVar12 == 0x7e0)) {
            sVar9 = sVar11;
          }
          iVar16 = iVar16 + -1;
          *psVar17 = sVar9;
          psVar17 = psVar17 + 1;
          psVar18 = psVar18 + 2;
        } while (iVar16 != 0);
        uVar15 = uVar15 + 1 & 0xfffeffff;
      } while (uVar15 < 0x121);
      do {
        iVar16 = FUN_80022fd0();
      } while (iVar16 == 2);
      if (iVar16 == 0) {
        FUN_8002c5b8();
        goto LAB_8002c1ac;
      }
      FUN_800106a4(0);
      FUN_800107f4(0);
      uVar14 = 0;
      FUN_8002c7a4();
      FUN_8000b2ac();
      uVar15 = 0;
      do {
        if (pcVar4[uVar15 + 0xd] != '\0') {
          uVar1 = (uint)(byte)pcVar4[10] * 0x10 + -0x10 + uVar15 & 0xffff;
          iVar16 = uVar1 - uVar14;
          uVar14 = uVar14 + 1 & 0xff;
          if ((byte)pcVar4[0xc] <= uVar1) break;
          FUN_8000bb04(*(undefined2 *)(pcVar4 + iVar16 * 2 + 0x1e));
          FUN_80033ea4(pcVar4 + uVar1 * 0xf + 0x7ee);
        }
        uVar15 = uVar15 + 1 & 0xfffeffff;
      } while (uVar15 < 0x10);
      FUN_80000878(pcVar4 + 0xd,0x10);
      FUN_8002c8f4();
      FUN_800261b4();
      FUN_8002c7a4();
      FUN_8000b2ac();
      FUN_8002b9bc();
      *pcVar4 = '\0';
      goto LAB_8002bed0;
    }
  }
LAB_8002c1ac:
  puVar7 = PTR_DAT_8002c59c;
  puVar6 = PTR_DAT_8002c598;
  if (iVar13 - 7U < 0x10) {
    if (*pcVar4 == '\0') {
      uVar14 = ((uint)(byte)pcVar4[10] * 0x10 + iVar13) - 0x17;
      uVar15 = uVar14 & 0xffff;
      *(short *)(PTR_DAT_8002c598 + 2) = (short)(uVar14 * 0x10000 >> 0x10);
      if (*puVar7 == '\0') {
        *puVar6 = 1;
        puVar6[4] = 1;
        puVar6[5] = 0;
        iVar16 = FUN_80022bc8();
        if (iVar16 == 0) {
          sVar10 = FUN_800232b4(0);
          sVar11 = FUN_800232b4(DAT_8002c590);
          set_screen_to_global_pointer();
          puVar6 = PTR_DAT_8002c5ac;
          uVar15 = 0x1a4;
          do {
            iVar16 = 800;
            psVar17 = (short *)(*piVar5 + uVar15 * 0x640);
            psVar18 = (short *)(puVar6 + uVar15 * 0xc80 + -0x148200);
            do {
              sVar8 = *psVar18;
              sVar12 = sVar11;
              if ((sVar8 != 0) && (sVar12 = sVar8, sVar8 == -0x800)) {
                sVar12 = sVar10;
              }
              iVar16 = iVar16 + -1;
              *psVar17 = sVar12;
              psVar17 = psVar17 + 1;
              psVar18 = psVar18 + 2;
            } while (iVar16 != 0);
            uVar15 = uVar15 + 1 & 0xfffeffff;
          } while (uVar15 < 0x1e0);
          set_frame_to_global_pointer();
          FUN_80022dd4();
        }
      }
      else {
        if ((byte)pcVar4[0xc] <= uVar15) {
          if (uVar15 == 0) goto LAB_8002c4f0;
          uVar15 = uVar15 - 1;
          *(short *)(puVar6 + 2) = (short)uVar15;
        }
        iVar16 = FUN_800337c4(auStack592,pcVar4 + (uVar15 & 0xffff) * 0xf + 0x7ee,1);
        if (iVar16 == 4) {
          FUN_8002c7a4();
          FUN_8000b2ac();
          FUN_8000bb04(*(undefined2 *)(pcVar4 + (uint)*(ushort *)(puVar6 + 2) * 2 + 0x1e));
          FUN_80033ea4(pcVar4 + (uint)*(ushort *)(puVar6 + 2) * 0xf + 0x7ee);
          FUN_8002c8f4();
          FUN_800261b4();
          FUN_8002c7a4();
          FUN_8000b2ac();
          FUN_8003347c(auStack592);
        }
        else {
          FUN_800334ac(auStack592,0);
          FUN_80033b18(auStack592,DAT_8002c5a4,DAT_8002c5a0,0);
          FUN_8003347c(auStack592);
          iVar16 = DAT_8002c570;
          *(undefined *)(DAT_8002c570 + 0x43) = 1;
          FUN_80001358(DAT_8002c5a4);
          *(undefined *)(iVar16 + 0x18) = 1;
          *(undefined *)(iVar16 + 0x17) = 1;
          *(undefined *)(iVar16 + 0x43) = 1;
          *(undefined *)(iVar16 + 0x3a) = 1;
          FUN_80010944(0);
          set_frame_to_global_pointer();
          set_display_color(0);
          display_clear_rect(2,0x2f,(ushort)DAT_8002c5a8 + 0xfb,(ushort)DAT_8002c5a8);
          FUN_8000e8f0();
          FUN_8002b124();
          cVar2 = *(char *)(iVar16 + 0x43);
          while (cVar2 != '\0') {
            if (*(byte *)(iVar16 + 10) < 9) {
              FUN_8002b68c();
            }
            else {
              FUN_8002b124();
            }
            FUN_8001a3b4();
            cVar2 = *(char *)(iVar16 + 0x43);
          }
        }
      }
LAB_8002c4f0:
      set_display_color(DAT_8002c5b0);
      ysize = (ushort)DAT_8002c5a8;
      display_clear_rect(ysize + 0xfa,0,ysize + 0x140,ysize);
      FUN_800105e0();
LAB_8002c510:
      FUN_8002b9bc();
    }
    else {
      FUN_8002c5b8();
    }
  }
  goto LAB_8002bed0;
}


