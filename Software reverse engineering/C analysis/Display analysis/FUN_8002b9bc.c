void FUN_8002b9bc(void)

{
  uint uVar1;
  ushort uVar2;
  ushort uVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  uint uVar7;
  int iVar8;
  short *psVar9;
  short *psVar10;
  short *psVar11;
  int *piVar12;
  char *pcVar13;
  short *psVar14;
  ushort *puVar15;
  short *psVar16;
  undefined2 *puVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  int iVar22;
  uint uVar23;
  uint uVar24;
  uint uVar25;
  uint uVar26;
  int *in_r12;
  uint local_58;
  
  local_58 = 0;
  uVar2 = *(ushort *)(DAT_8002be10 + 2);
  uVar21 = (uint)uVar2;
  uVar24 = (uint)*(ushort *)(DAT_8002be10 + 4);
  uVar25 = (uint)*(ushort *)(DAT_8002be10 + 6);
  uVar26 = (uint)*(ushort *)(DAT_8002be10 + 8);
  FUN_8002c7a4();
  FUN_8000b2ac();
  set_frame_to_global_pointer();
  set_display_color(0);
  iVar8 = DAT_8002be14;
  iVar22 = DAT_8002be14 + 0xfa;
  display_clear_rect(0,0,(ushort)iVar22,(ushort)DAT_8002be14);
  set_display_color(DAT_8002be18);
  FUN_80018ef4(iVar22,0,iVar8);
  psVar11 = DAT_8002be28;
  iVar8 = DAT_8002be24;
  psVar10 = DAT_8002be20;
  psVar9 = DAT_8002be1c;
  uVar19 = 0;
  do {
    uVar20 = 0;
    do {
      uVar1 = local_58 + (uint)*(byte *)(DAT_8002be10 + 10) * 0x10 + -0x10 & 0xffff;
      if (*(byte *)(DAT_8002be10 + 0xc) <= uVar1) break;
      if (uVar24 != 0) {
        in_r12 = Global_Frame_Buffer_Pointer;
      }
      uVar23 = uVar20 + 4 & 0xfffeffff;
      local_58 = local_58 + 1 & 0xfffeffff;
      uVar18 = 0;
      if (uVar24 != 0) {
        do {
          if (uVar21 != 0) {
            iVar22 = *in_r12 + (uVar25 + (uVar18 + uVar26 + uVar19) * 800 + uVar20) * 2;
            puVar17 = (undefined2 *)(iVar22 + 0x63e);
            uVar7 = (uint)(uVar2 >> 1);
            if ((uVar2 & 1) != 0) {
              puVar17 = (undefined2 *)(iVar22 + 0x640);
              *puVar17 = 0;
            }
            while (uVar7 != 0) {
              puVar17[1] = 0;
              puVar17 = puVar17 + 2;
              *puVar17 = 0;
              uVar7 = uVar7 - 1;
            }
          }
          uVar18 = uVar18 + 1 & 0xfffeffff;
        } while (uVar18 < uVar24);
      }
      FUN_8000b9c4(*(undefined2 *)(DAT_8002be10 + uVar1 * 2 + 0x1e));
      psVar14 = DAT_8002be38;
      psVar16 = DAT_8002be34;
      sVar6 = (short)uVar19;
      if (*(char *)(DAT_8002be30 + 7) == '\0') {
        iVar22 = 0x57;
        *DAT_8002be38 = *DAT_8002be34 + sVar6;
        sVar4 = psVar16[1];
        do {
          iVar22 = iVar22 + -1;
          sVar5 = psVar16[2];
          psVar14[1] = sVar4 + sVar6;
          sVar4 = psVar16[3];
          psVar14 = psVar14 + 2;
          *psVar14 = sVar5 + sVar6;
          psVar16 = psVar16 + 2;
        } while (iVar22 != 0);
        *psVar9 = *psVar10 + sVar6;
      }
      else {
        memcpy(DAT_8002be38,DAT_8002be34,0x160);
      }
      psVar16 = DAT_8002be3c;
      iVar22 = 0x57;
      psVar14 = (short *)(iVar8 + 2);
      *psVar14 = *DAT_8002be3c + sVar6;
      uVar3 = psVar16[1];
      do {
        iVar22 = iVar22 + -1;
        in_r12 = (int *)(uVar3 + uVar19);
        sVar4 = psVar16[2];
        psVar14[1] = (short)in_r12;
        uVar3 = psVar16[3];
        psVar14 = psVar14 + 2;
        *psVar14 = sVar4 + sVar6;
        psVar16 = psVar16 + 2;
      } while (iVar22 != 0);
      psVar9[200] = *psVar11 + sVar6;
      pcVar13 = DAT_8002be44;
      if (*(char *)(DAT_8002be30 + 7) == '\0') {
        if (*(ushort *)(DAT_8002be44 + 0x1c) < 4) {
          *(undefined2 *)(DAT_8002be44 + 0x1c) = 4;
        }
        if (*pcVar13 != '\0') {
          FUN_80012a64(*(ushort *)(pcVar13 + 0x1a) + uVar23 & 0xfffeffff,0,
                       *(short *)(pcVar13 + 0x1c) + -4,DAT_8002be38,DAT_8002be54);
        }
        if (pcVar13[0xc] != '\0') {
          FUN_80012a64(*(ushort *)(pcVar13 + 0x1a) + uVar23 & 0xfffeffff,0,
                       *(short *)(pcVar13 + 0x1c) + -4,DAT_8002be5c,DAT_8002be58);
        }
      }
      else {
        set_display_color(DAT_8002be40);
        pcVar13 = DAT_8002be44;
        if (*(ushort *)(DAT_8002be44 + 0x1c) < 5) {
          *(undefined2 *)(DAT_8002be44 + 0x1c) = 5;
        }
        uVar18 = 0;
        if (0 < (int)(*(ushort *)(pcVar13 + 0x1c) - 5)) {
          do {
            puVar15 = (ushort *)(DAT_8002be38 + uVar18);
            in_r12 = (int *)(*puVar15 + uVar23);
            FUN_80018d30((int)in_r12 + 0x1b,puVar15[200],uVar23 + puVar15[1] + 0x1b,puVar15[0xc9]);
            uVar18 = uVar18 + 1 & 0xfffeffff;
          } while ((int)uVar18 < (int)(*(ushort *)(DAT_8002be44 + 0x1c) - 5));
        }
      }
      set_display_color(DAT_8002be18);
      FUN_80018da0(uVar25 + uVar20 + -1,uVar26 + uVar19 + -1,uVar25 + uVar21 + uVar20,
                   uVar26 + uVar24 + uVar19);
      uVar20 = uVar21 + uVar25 + uVar20 & 0xfffcffff;
    } while (uVar20 < 700);
    if ((*(byte *)(DAT_8002be10 + 0xc) <= uVar1) ||
       (uVar19 = uVar24 + uVar26 + uVar19 & 0xfffcffff, DAT_8002be48 <= uVar19)) {
      FUN_8001cccc(0,0,DAT_8002be14 + 0xfa);
      iVar22 = DAT_8002be50;
      iVar8 = Screen_Frame_Buffer_2;
      piVar12 = Global_Frame_Buffer_Pointer;
      uVar19 = 0;
      do {
        memcpy((void *)(iVar8 + uVar19 * 0x640),(void *)(*piVar12 + uVar19 * 0x640),iVar22);
        uVar19 = uVar19 + 1 & 0xfffeffff;
      } while (uVar19 < 0x1e0);
      return;
    }
  } while( true );
}

