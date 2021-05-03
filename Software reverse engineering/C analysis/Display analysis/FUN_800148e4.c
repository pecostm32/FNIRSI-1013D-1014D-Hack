void FUN_800148e4(void)

{
  undefined4 uVar1;
  undefined *puVar2;
  int *piVar3;
  char *pcVar4;
  ushort *puVar5;
  ushort uVar6;
  short sVar7;
  undefined2 *puVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  uint uVar16;
  
  uVar12 = DAT_80014e54;
  uVar1 = DAT_80014e50;
  set_frame_to_global_pointer();
  piVar3 = Global_Frame_Buffer_Pointer;
  puVar2 = PTR_DAT_80014e58;
  uVar16 = 0;
  do {
    iVar15 = 0xb7;
    puVar8 = (undefined2 *)(*piVar3 + uVar16 * 0x640 + 0x121c0);
    puVar5 = (ushort *)(puVar2 + uVar16 * 0x16e);
    do {
      uVar10 = (uint)*puVar5;
      if (*puVar5 == 0) {
        uVar10 = uVar12;
      }
      iVar15 = iVar15 + -1;
      *puVar8 = (short)uVar10;
      iVar13 = DAT_80014e64;
      iVar11 = DAT_80014e60;
      puVar8 = puVar8 + 1;
      puVar5 = puVar5 + 1;
    } while (iVar15 != 0);
    uVar16 = uVar16 + 1 & 0xfffeffff;
  } while (uVar16 < 0xfc);
  uVar6 = (ushort)uVar1;
  if (*(char *)(DAT_80014e60 + 0xc) == '\0') {
    uVar16 = 0x42;
    do {
      puVar5 = (ushort *)(*piVar3 + (uVar16 * 800 + 5) * 2 + 0x330);
      sVar7 = 0x27;
      do {
        sVar7 = sVar7 + -1;
        if (*puVar5 == uVar12) {
          *puVar5 = uVar6;
        }
        else {
          *puVar5 = 0;
        }
        puVar5 = puVar5 + 1;
      } while (sVar7 != 0);
      uVar16 = uVar16 + 1 & 0xfffeffff;
    } while (uVar16 < 0x58);
  }
  else {
    uVar16 = DAT_80014e64 - 0x16d;
    uVar10 = 0x42;
    do {
      puVar5 = (ushort *)(*piVar3 + (uVar10 * 800 + 5) * 2 + 0x2c8);
      uVar9 = uVar16 & 0xffff;
      do {
        if (*puVar5 == uVar12) {
          *puVar5 = uVar6;
        }
        else {
          *puVar5 = 0;
        }
        uVar9 = uVar9 - 1 & 0xffff;
        puVar5 = puVar5 + 1;
      } while (uVar9 != 0);
      uVar10 = uVar10 + 1 & 0xfffeffff;
    } while (uVar10 < 0x58);
  }
  if (*(char *)(iVar11 + 0x10) == '\0') {
    uVar16 = 0x80;
    do {
      puVar5 = (ushort *)(*piVar3 + (uVar16 * 800 + 5) * 2 + 0x330);
      sVar7 = 0x27;
      do {
        sVar7 = sVar7 + -1;
        if (*puVar5 == uVar12) {
          *puVar5 = uVar6;
        }
        else {
          *puVar5 = 0;
        }
        puVar5 = puVar5 + 1;
      } while (sVar7 != 0);
      uVar16 = uVar16 + 1 & 0xfffeffff;
    } while (uVar16 < 0x96);
  }
  else {
    uVar16 = 0x80;
    do {
      puVar5 = (ushort *)(*piVar3 + (uVar16 * 800 + 5) * 2 + 0x2c8);
      uVar10 = iVar13 - 0x16dU & 0xffff;
      do {
        if (*puVar5 == uVar12) {
          *puVar5 = uVar6;
        }
        else {
          *puVar5 = 0;
        }
        uVar10 = uVar10 - 1 & 0xffff;
        puVar5 = puVar5 + 1;
      } while (uVar10 != 0);
      uVar16 = uVar16 + 1 & 0xfffeffff;
    } while (uVar16 < 0x96);
  }
  if (*(char *)(iVar11 + 0xd) == '\0') {
    uVar16 = 0xc0;
    do {
      puVar5 = (ushort *)(*piVar3 + (uVar16 * 800 + 5) * 2 + 0x2c8);
      uVar10 = iVar13 - 0x16dU & 0xffff;
      do {
        if (*puVar5 == uVar12) {
          *puVar5 = uVar6;
        }
        else {
          *puVar5 = 0;
        }
        uVar10 = uVar10 - 1 & 0xffff;
        puVar5 = puVar5 + 1;
      } while (uVar10 != 0);
      uVar16 = uVar16 + 1 & 0xfffeffff;
    } while (uVar16 < 0xd6);
  }
  else {
    uVar16 = 0xc0;
    do {
      puVar5 = (ushort *)(*piVar3 + (uVar16 * 800 + 5) * 2 + 0x330);
      sVar7 = 0x27;
      do {
        sVar7 = sVar7 + -1;
        if (*puVar5 == uVar12) {
          *puVar5 = uVar6;
        }
        else {
          *puVar5 = 0;
        }
        puVar5 = puVar5 + 1;
      } while (sVar7 != 0);
      uVar16 = uVar16 + 1 & 0xfffeffff;
    } while (uVar16 < 0xd6);
  }
  if (*(char *)(iVar11 + 0xe) == '\0') {
    uVar10 = 0xf7;
    uVar16 = DAT_80014e68 - 0x16d;
    do {
      puVar5 = (ushort *)(*piVar3 + (uVar10 * 800 + 5) * 2 + 0x2c8);
      uVar9 = uVar16 & 0xffff;
      do {
        if (*puVar5 == uVar12) {
          *puVar5 = uVar6;
        }
        else {
          *puVar5 = 0;
        }
        uVar9 = uVar9 - 1 & 0xffff;
        puVar5 = puVar5 + 1;
      } while (uVar9 != 0);
      uVar10 = uVar10 + 1 & 0xfffeffff;
    } while (uVar10 < 0x11c);
  }
  else {
    if (*(char *)(iVar11 + 0xe) == '\x01') {
      uVar10 = 0xf7;
      uVar16 = DAT_80014e6c - 399;
      do {
        puVar5 = (ushort *)(*piVar3 + (uVar10 * 800 + 5) * 2 + 0x30c);
        uVar9 = uVar16 & 0xffff;
        do {
          if (*puVar5 == uVar12) {
            *puVar5 = uVar6;
          }
          else {
            *puVar5 = 0;
          }
          uVar9 = uVar9 - 1 & 0xffff;
          puVar5 = puVar5 + 1;
        } while (uVar9 != 0);
        uVar10 = uVar10 + 1 & 0xfffeffff;
      } while (uVar10 < 0x11c);
    }
    else {
      if (*(char *)(iVar11 + 0xe) == '\x02') {
        uVar10 = 0xf7;
        uVar16 = DAT_80014e70 - 0x1ac;
        do {
          puVar5 = (ushort *)(*piVar3 + (uVar10 * 800 + 5) * 2 + 0x346);
          uVar9 = uVar16 & 0xffff;
          do {
            if (*puVar5 == uVar12) {
              *puVar5 = uVar6;
            }
            else {
              *puVar5 = 0;
            }
            uVar9 = uVar9 - 1 & 0xffff;
            puVar5 = puVar5 + 1;
          } while (uVar9 != 0);
          uVar10 = uVar10 + 1 & 0xfffeffff;
        } while (uVar10 < 0x11c);
      }
    }
  }
  set_display_color(DAT_80014e74);
  iVar15 = DAT_80014e78;
  iVar13 = DAT_80014e78 + 0xad;
  FUN_80018da0(0x120,0x2e,iVar13);
  set_display_color(0);
  iVar11 = iVar15 + 0xa0;
  iVar14 = iVar15 + 5;
  FUN_80018ca8(0x6c,iVar14,iVar11);
  FUN_80018ca8(0xab,iVar14,iVar11);
  FUN_80018ca8(0xea,iVar14,iVar11);
  FUN_8001cccc(0x120,0x2e,iVar13,iVar15 + 1);
  set_frame_to_global_pointer();
  set_display_color(0);
  iVar15 = DAT_8000e100;
  display_clear_rect(0x120,4,(ushort)DAT_8000e100,0x2d);
  iVar11 = DAT_8000e104;
  uVar12 = DAT_8000e108;
  if (*(char *)(DAT_8000e104 + 0xc) == '\0') {
    uVar12 = DAT_8000e10c;
  }
  set_display_color(uVar12);
  display_clear_rect(0x120,5,(ushort)DAT_8000e110,0x28);
  set_display_color(0);
  FUN_800197c8(2);
  FUN_80019730(PTR_PTR_FUN_8000e114);
  display_text(&DAT_8000e11c,(ushort)DAT_8000e118,0x10);
  set_display_color(0xffffff);
  if (*(char *)(iVar11 + 0xd) == '\0') {
    pcVar4 = (char *)0x8000e124;
  }
  else {
    pcVar4 = (char *)0x8000e128;
  }
  uVar6 = (ushort)DAT_8000e120;
  display_text(pcVar4,uVar6,8);
  set_display_color(0xffffff);
  if (*(char *)(iVar11 + 0xe) == '\0') {
    display_text(&DAT_8000e140,(ushort)DAT_8000e13c,8);
  }
  else {
    if (*(char *)(iVar11 + 0xe) == '\x01') {
      pcVar4 = (char *)0x8000e130;
    }
    else {
      if (*(char *)(iVar11 + 0xe) != '\x02') goto LAB_8000dec0;
      pcVar4 = (char *)0x8000e134;
    }
    display_text(pcVar4,(ushort)DAT_8000e12c,8);
  }
LAB_8000dec0:
  if (*(char *)(iVar11 + 0xe) != '\0') {
    if (*(char *)(iVar11 + 0xe) == '\x01') {
      switch(*(undefined *)(iVar11 + 0xf)) {
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
      if (*(char *)(iVar11 + 0xe) != '\x02') goto switchD_8000def0_caseD_7;
      switch(*(undefined *)(iVar11 + 0xf)) {
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
  switch(*(undefined *)(iVar11 + 0xf)) {
  case 0:
    display_text(s_5V_div_8000e144,uVar6,0x18);
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
  display_text(pcVar4,uVar6,0x18);
switchD_8000def0_caseD_7:
  iVar13 = Start_Of_Screen_Mem;
  iVar11 = Screen_Frame_Buffer;
  uVar12 = 4;
  do {
    iVar14 = uVar12 * 800 + 0x120;
    copy_short((void *)(iVar13 + iVar14 * 2),(void *)(iVar11 + iVar14 * 2),iVar15 + -0x11f);
    uVar12 = uVar12 + 1;
  } while (uVar12 < 0x2d);
  return;
}

