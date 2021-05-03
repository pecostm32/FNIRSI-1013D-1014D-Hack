void FUN_80021d14(void)

{
  undefined4 uVar1;
  undefined *puVar2;
  int *piVar3;
  char *pcVar4;
  ushort *puVar5;
  short *psVar6;
  ushort uVar7;
  undefined2 *puVar8;
  uint uVar9;
  short *psVar10;
  uint uVar11;
  int iVar12;
  short sVar13;
  int iVar14;
  undefined4 unaff_r4;
  short sVar15;
  int iVar16;
  int iVar17;
  uint uVar18;
  uint uVar19;
  uint color;
  
  FUN_8001c6f0(0x120,0x2e,DAT_80021dd8 + 0xad);
  set_screen_to_global_pointer();
  sVar15 = (short)DAT_80021ddc;
  set_screen_to_global_pointer();
  piVar3 = Global_Frame_Buffer_Pointer;
  puVar2 = PTR_DAT_80021de0;
  uVar19 = 0xfc;
  uVar18 = uVar19;
  do {
    while (uVar19 < 0xfc) {
      iVar12 = 0xb7;
      psVar6 = (short *)(*piVar3 + (uVar19 - uVar18) * 0x640 + 0x121c0);
      psVar10 = (short *)(puVar2 + uVar19 * 0x16e);
      do {
        sVar13 = *psVar10;
        if (*psVar10 == 0) {
          sVar13 = sVar15;
        }
        iVar12 = iVar12 + -1;
        *psVar6 = sVar13;
        psVar6 = psVar6 + 1;
        psVar10 = psVar10 + 1;
      } while (iVar12 != 0);
      uVar19 = uVar19 + 1 & 0xfffeffff;
    }
    uVar19 = (uVar18 - (uVar18 * DAT_80021de8 >> 0x13)) - 1 & 0xffff;
    uVar18 = uVar19;
  } while (uVar19 != 0);
  FUN_8001cfb8();
  FUN_8001cfb8();
  uVar19 = DAT_80014e54;
  uVar1 = DAT_80014e50;
  color = 0;
  set_frame_to_global_pointer();
  piVar3 = Global_Frame_Buffer_Pointer;
  puVar2 = PTR_DAT_80014e58;
  uVar18 = 0;
  do {
    iVar12 = 0xb7;
    puVar8 = (undefined2 *)(*piVar3 + uVar18 * 0x640 + 0x121c0);
    puVar5 = (ushort *)(puVar2 + uVar18 * 0x16e);
    do {
      uVar11 = (uint)*puVar5;
      if (*puVar5 == 0) {
        uVar11 = uVar19;
      }
      iVar12 = iVar12 + -1;
      *puVar8 = (short)uVar11;
      iVar16 = DAT_80014e64;
      iVar14 = DAT_80014e60;
      puVar8 = puVar8 + 1;
      puVar5 = puVar5 + 1;
    } while (iVar12 != 0);
    uVar18 = uVar18 + 1 & 0xfffeffff;
  } while (uVar18 < 0xfc);
  uVar7 = (ushort)uVar1;
  if (*(char *)(DAT_80014e60 + 0xc) == '\0') {
    uVar18 = 0x42;
    do {
      puVar5 = (ushort *)(*piVar3 + (uVar18 * 800 + 5) * 2 + 0x330);
      sVar15 = 0x27;
      do {
        sVar15 = sVar15 + -1;
        if (*puVar5 == uVar19) {
          *puVar5 = uVar7;
        }
        else {
          *puVar5 = 0;
        }
        puVar5 = puVar5 + 1;
      } while (sVar15 != 0);
      uVar18 = uVar18 + 1 & 0xfffeffff;
    } while (uVar18 < 0x58);
  }
  else {
    uVar18 = DAT_80014e64 - 0x16d;
    uVar11 = 0x42;
    do {
      puVar5 = (ushort *)(*piVar3 + (uVar11 * 800 + 5) * 2 + 0x2c8);
      uVar9 = uVar18 & 0xffff;
      do {
        if (*puVar5 == uVar19) {
          *puVar5 = uVar7;
        }
        else {
          *puVar5 = 0;
        }
        uVar9 = uVar9 - 1 & 0xffff;
        puVar5 = puVar5 + 1;
      } while (uVar9 != 0);
      uVar11 = uVar11 + 1 & 0xfffeffff;
    } while (uVar11 < 0x58);
  }
  if (*(char *)(iVar14 + 0x10) == '\0') {
    uVar18 = 0x80;
    do {
      puVar5 = (ushort *)(*piVar3 + (uVar18 * 800 + 5) * 2 + 0x330);
      sVar15 = 0x27;
      do {
        sVar15 = sVar15 + -1;
        if (*puVar5 == uVar19) {
          *puVar5 = uVar7;
        }
        else {
          *puVar5 = 0;
        }
        puVar5 = puVar5 + 1;
      } while (sVar15 != 0);
      uVar18 = uVar18 + 1 & 0xfffeffff;
    } while (uVar18 < 0x96);
  }
  else {
    uVar18 = 0x80;
    do {
      puVar5 = (ushort *)(*piVar3 + (uVar18 * 800 + 5) * 2 + 0x2c8);
      uVar11 = iVar16 - 0x16dU & 0xffff;
      do {
        if (*puVar5 == uVar19) {
          *puVar5 = uVar7;
        }
        else {
          *puVar5 = 0;
        }
        uVar11 = uVar11 - 1 & 0xffff;
        puVar5 = puVar5 + 1;
      } while (uVar11 != 0);
      uVar18 = uVar18 + 1 & 0xfffeffff;
    } while (uVar18 < 0x96);
  }
  if (*(char *)(iVar14 + 0xd) == '\0') {
    uVar18 = 0xc0;
    do {
      puVar5 = (ushort *)(*piVar3 + (uVar18 * 800 + 5) * 2 + 0x2c8);
      uVar11 = iVar16 - 0x16dU & 0xffff;
      do {
        if (*puVar5 == uVar19) {
          *puVar5 = uVar7;
        }
        else {
          *puVar5 = 0;
        }
        uVar11 = uVar11 - 1 & 0xffff;
        puVar5 = puVar5 + 1;
      } while (uVar11 != 0);
      uVar18 = uVar18 + 1 & 0xfffeffff;
    } while (uVar18 < 0xd6);
  }
  else {
    uVar18 = 0xc0;
    do {
      puVar5 = (ushort *)(*piVar3 + (uVar18 * 800 + 5) * 2 + 0x330);
      sVar15 = 0x27;
      do {
        sVar15 = sVar15 + -1;
        if (*puVar5 == uVar19) {
          *puVar5 = uVar7;
        }
        else {
          *puVar5 = 0;
        }
        puVar5 = puVar5 + 1;
      } while (sVar15 != 0);
      uVar18 = uVar18 + 1 & 0xfffeffff;
    } while (uVar18 < 0xd6);
  }
  if (*(char *)(iVar14 + 0xe) == '\0') {
    uVar11 = 0xf7;
    uVar18 = DAT_80014e68 - 0x16d;
    do {
      puVar5 = (ushort *)(*piVar3 + (uVar11 * 800 + 5) * 2 + 0x2c8);
      uVar9 = uVar18 & 0xffff;
      do {
        if (*puVar5 == uVar19) {
          *puVar5 = uVar7;
        }
        else {
          *puVar5 = 0;
        }
        uVar9 = uVar9 - 1 & 0xffff;
        puVar5 = puVar5 + 1;
      } while (uVar9 != 0);
      uVar11 = uVar11 + 1 & 0xfffeffff;
    } while (uVar11 < 0x11c);
  }
  else {
    if (*(char *)(iVar14 + 0xe) == '\x01') {
      uVar11 = 0xf7;
      uVar18 = DAT_80014e6c - 399;
      do {
        puVar5 = (ushort *)(*piVar3 + (uVar11 * 800 + 5) * 2 + 0x30c);
        uVar9 = uVar18 & 0xffff;
        do {
          if (*puVar5 == uVar19) {
            *puVar5 = uVar7;
          }
          else {
            *puVar5 = 0;
          }
          uVar9 = uVar9 - 1 & 0xffff;
          puVar5 = puVar5 + 1;
        } while (uVar9 != 0);
        uVar11 = uVar11 + 1 & 0xfffeffff;
      } while (uVar11 < 0x11c);
    }
    else {
      if (*(char *)(iVar14 + 0xe) == '\x02') {
        uVar11 = 0xf7;
        uVar18 = DAT_80014e70 - 0x1ac;
        do {
          puVar5 = (ushort *)(*piVar3 + (uVar11 * 800 + 5) * 2 + 0x346);
          uVar9 = uVar18 & 0xffff;
          do {
            if (*puVar5 == uVar19) {
              *puVar5 = uVar7;
            }
            else {
              *puVar5 = 0;
            }
            uVar9 = uVar9 - 1 & 0xffff;
            puVar5 = puVar5 + 1;
          } while (uVar9 != 0);
          uVar11 = uVar11 + 1 & 0xfffeffff;
        } while (uVar11 < 0x11c);
      }
    }
  }
  set_display_color(DAT_80014e74);
  iVar12 = DAT_80014e78;
  iVar16 = DAT_80014e78 + 0xad;
  FUN_80018da0(0x120,0x2e,iVar16,DAT_80014e78,color,unaff_r4);
  set_display_color(color);
  iVar14 = iVar12 + 0xa0;
  iVar17 = iVar12 + 5;
  FUN_80018ca8(0x6c,iVar17,iVar14);
  FUN_80018ca8(0xab,iVar17,iVar14);
  FUN_80018ca8(0xea,iVar17,iVar14);
  FUN_8001cccc(0x120,0x2e,iVar16,iVar12 + 1);
  set_frame_to_global_pointer();
  set_display_color(0);
  iVar12 = DAT_8000e100;
  display_clear_rect(0x120,4,(ushort)DAT_8000e100,0x2d);
  iVar14 = DAT_8000e104;
  uVar19 = DAT_8000e108;
  if (*(char *)(DAT_8000e104 + 0xc) == '\0') {
    uVar19 = DAT_8000e10c;
  }
  set_display_color(uVar19);
  display_clear_rect(0x120,5,(ushort)DAT_8000e110,0x28);
  set_display_color(0);
  FUN_800197c8(2);
  FUN_80019730(PTR_PTR_FUN_8000e114);
  display_text(&DAT_8000e11c,(ushort)DAT_8000e118,0x10);
  set_display_color(0xffffff);
  if (*(char *)(iVar14 + 0xd) == '\0') {
    pcVar4 = (char *)0x8000e124;
  }
  else {
    pcVar4 = (char *)0x8000e128;
  }
  uVar7 = (ushort)DAT_8000e120;
  display_text(pcVar4,uVar7,8);
  set_display_color(0xffffff);
  if (*(char *)(iVar14 + 0xe) == '\0') {
    display_text(&DAT_8000e140,(ushort)DAT_8000e13c,8);
  }
  else {
    if (*(char *)(iVar14 + 0xe) == '\x01') {
      pcVar4 = (char *)0x8000e130;
    }
    else {
      if (*(char *)(iVar14 + 0xe) != '\x02') goto LAB_8000dec0;
      pcVar4 = (char *)0x8000e134;
    }
    display_text(pcVar4,(ushort)DAT_8000e12c,8);
  }
LAB_8000dec0:
  if (*(char *)(iVar14 + 0xe) != '\0') {
    if (*(char *)(iVar14 + 0xe) == '\x01') {
      switch(*(undefined *)(iVar14 + 0xf)) {
      case 0:
switchD_8000df84_caseD_0:
        pcVar4 = &DAT_8000e1cc;
        break;
      case 1:
        pcVar4 = &DAT_8000e188;
        break;
      case 2:
switchD_8000df84_caseD_2:
        pcVar4 = &DAT_8000e190;
        break;
      case 3:
switchD_8000df84_caseD_3:
        pcVar4 = s_5V_div_8000e144;
        break;
      case 4:
        pcVar4 = &DAT_8000e198;
        break;
      case 5:
        goto switchD_8000def0_caseD_2;
      case 6:
        goto switchD_8000def0_caseD_3;
      default:
        goto switchD_8000def0_caseD_7;
      }
    }
    else {
      if (*(char *)(iVar14 + 0xe) != '\x02') goto switchD_8000def0_caseD_7;
      switch(*(undefined *)(iVar14 + 0xf)) {
      case 0:
        pcVar4 = &DAT_8000e1a8;
        break;
      case 1:
        pcVar4 = &DAT_8000e1b4;
        break;
      case 2:
        pcVar4 = &DAT_8000e1c0;
        break;
      case 3:
        goto switchD_8000df84_caseD_0;
      case 4:
        pcVar4 = &DAT_8000e1d4;
        break;
      case 5:
        goto switchD_8000df84_caseD_2;
      case 6:
        goto switchD_8000df84_caseD_3;
      default:
        goto switchD_8000def0_caseD_7;
      }
    }
    goto LAB_8000df34;
  }
  switch(*(undefined *)(iVar14 + 0xf)) {
  case 0:
    display_text(s_5V_div_8000e144,uVar7,0x18);
    goto switchD_8000def0_caseD_7;
  case 1:
    pcVar4 = s_2_5V_div_8000e14c;
    break;
  case 2:
switchD_8000def0_caseD_2:
    pcVar4 = &DAT_8000e1a0;
    break;
  case 3:
switchD_8000def0_caseD_3:
    pcVar4 = &DAT_8000e158;
    break;
  case 4:
    pcVar4 = &DAT_8000e164;
    break;
  case 5:
    pcVar4 = &DAT_8000e170;
    break;
  case 6:
    pcVar4 = &DAT_8000e17c;
    break;
  default:
    goto switchD_8000def0_caseD_7;
  }
LAB_8000df34:
  display_text(pcVar4,uVar7,0x18);
switchD_8000def0_caseD_7:
  iVar16 = Start_Of_Screen_Mem;
  iVar14 = Screen_Frame_Buffer;
  uVar19 = 4;
  do {
    iVar17 = uVar19 * 800 + 0x120;
    copy_short((void *)(iVar16 + iVar17 * 2),(void *)(iVar14 + iVar17 * 2),iVar12 + -0x11f);
    uVar19 = uVar19 + 1;
  } while (uVar19 < 0x2d);
  return;
}

