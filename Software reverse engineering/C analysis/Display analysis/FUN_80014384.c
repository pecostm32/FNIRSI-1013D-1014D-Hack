void FUN_80014384(void)

{
  ushort uVar1;
  ushort uVar2;
  undefined4 uVar3;
  undefined *puVar4;
  int *piVar5;
  char *pcVar6;
  char *pcVar7;
  uint uVar8;
  ushort *puVar9;
  short sVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  int iVar16;
  undefined2 *puVar17;
  
  uVar14 = DAT_800148c0;
  uVar3 = DAT_800148bc;
  set_frame_to_global_pointer();
  piVar5 = Global_Frame_Buffer_Pointer;
  puVar4 = PTR_DAT_800148c4;
  uVar11 = 0;
  do {
    iVar16 = 0xb7;
    puVar9 = (ushort *)(puVar4 + uVar11 * 0x16e);
    puVar17 = (undefined2 *)(*piVar5 + uVar11 * 0x640 + 0x120c2);
    do {
      uVar8 = (uint)*puVar9;
      if (*puVar9 == 0) {
        uVar8 = uVar14;
      }
      iVar16 = iVar16 + -1;
      *puVar17 = (short)uVar8;
      iVar13 = DAT_800148cc;
      puVar9 = puVar9 + 1;
      puVar17 = puVar17 + 1;
    } while (iVar16 != 0);
    uVar11 = uVar11 + 1 & 0xfffeffff;
  } while (uVar11 < 0xfc);
  uVar11 = 0x42;
  if (*DAT_800148d0 == '\0') {
    uVar8 = DAT_800148cc - 0xef;
  }
  else {
    uVar8 = DAT_800148cc - 0xee;
  }
  uVar2 = (ushort)uVar3;
  if (*DAT_800148d0 == '\0') {
    do {
      puVar9 = (ushort *)(*piVar5 + (uVar11 * 800 + 5) * 2 + 0x232);
      uVar12 = uVar8 & 0xffff;
      do {
        if (*puVar9 == uVar14) {
          *puVar9 = uVar2;
        }
        else {
          *puVar9 = 0;
        }
        uVar12 = uVar12 - 1 & 0xffff;
        puVar9 = puVar9 + 1;
      } while (uVar12 != 0);
      uVar11 = uVar11 + 1 & 0xfffeffff;
    } while (uVar11 < 0x58);
  }
  else {
    do {
      puVar9 = (ushort *)(*piVar5 + (uVar11 * 800 + 5) * 2 + 0x1ca);
      uVar12 = uVar8 & 0xffff;
      do {
        if (*puVar9 == uVar14) {
          *puVar9 = uVar2;
        }
        else {
          *puVar9 = 0;
        }
        uVar12 = uVar12 - 1 & 0xffff;
        puVar9 = puVar9 + 1;
      } while (uVar12 != 0);
      uVar11 = uVar11 + 1 & 0xfffeffff;
    } while (uVar11 < 0x58);
  }
  uVar11 = 0x80;
  if (DAT_800148d0[4] == '\0') {
    uVar8 = iVar13 - 0xef;
  }
  else {
    uVar8 = iVar13 - 0xee;
  }
  if (DAT_800148d0[4] == '\0') {
    do {
      puVar9 = (ushort *)(*piVar5 + (uVar11 * 800 + 5) * 2 + 0x232);
      uVar12 = uVar8 & 0xffff;
      do {
        if (*puVar9 == uVar14) {
          *puVar9 = uVar2;
        }
        else {
          *puVar9 = 0;
        }
        uVar12 = uVar12 - 1 & 0xffff;
        puVar9 = puVar9 + 1;
      } while (uVar12 != 0);
      uVar11 = uVar11 + 1 & 0xfffeffff;
    } while (uVar11 < 0x96);
  }
  else {
    do {
      puVar9 = (ushort *)(*piVar5 + (uVar11 * 800 + 5) * 2 + 0x1ca);
      uVar12 = uVar8 & 0xffff;
      do {
        if (*puVar9 == uVar14) {
          *puVar9 = uVar2;
        }
        else {
          *puVar9 = 0;
        }
        uVar12 = uVar12 - 1 & 0xffff;
        puVar9 = puVar9 + 1;
      } while (uVar12 != 0);
      uVar11 = uVar11 + 1 & 0xfffeffff;
    } while (uVar11 < 0x96);
  }
  uVar11 = 0xc0;
  if (DAT_800148d0[1] == '\0') {
    uVar8 = iVar13 - 0xee;
  }
  else {
    uVar8 = iVar13 - 0xef;
  }
  if (DAT_800148d0[1] == '\0') {
    do {
      puVar9 = (ushort *)(*piVar5 + (uVar11 * 800 + 5) * 2 + 0x1ca);
      uVar12 = uVar8 & 0xffff;
      do {
        if (*puVar9 == uVar14) {
          *puVar9 = uVar2;
        }
        else {
          *puVar9 = 0;
        }
        uVar12 = uVar12 - 1 & 0xffff;
        puVar9 = puVar9 + 1;
      } while (uVar12 != 0);
      uVar11 = uVar11 + 1 & 0xfffeffff;
    } while (uVar11 < 0xd6);
  }
  else {
    do {
      puVar9 = (ushort *)(*piVar5 + (uVar11 * 800 + 5) * 2 + 0x232);
      uVar12 = uVar8 & 0xffff;
      do {
        if (*puVar9 == uVar14) {
          *puVar9 = uVar2;
        }
        else {
          *puVar9 = 0;
        }
        uVar12 = uVar12 - 1 & 0xffff;
        puVar9 = puVar9 + 1;
      } while (uVar12 != 0);
      uVar11 = uVar11 + 1 & 0xfffeffff;
    } while (uVar11 < 0xd6);
  }
  if (DAT_800148d0[2] == '\0') {
    uVar8 = 0xf7;
    uVar11 = DAT_800148d4 - 0xee;
    do {
      puVar9 = (ushort *)(*piVar5 + (uVar8 * 800 + 5) * 2 + 0x1ca);
      uVar12 = uVar11 & 0xffff;
      do {
        if (*puVar9 == uVar14) {
          *puVar9 = uVar2;
        }
        else {
          *puVar9 = 0;
        }
        uVar12 = uVar12 - 1 & 0xffff;
        puVar9 = puVar9 + 1;
      } while (uVar12 != 0);
      uVar8 = uVar8 + 1 & 0xfffeffff;
    } while (uVar8 < 0x11c);
  }
  else {
    if (DAT_800148d0[2] == '\x01') {
      uVar8 = 0xf7;
      uVar11 = DAT_800148d8 - 0x110;
      do {
        puVar9 = (ushort *)(*piVar5 + (uVar8 * 800 + 5) * 2 + 0x20e);
        uVar12 = uVar11 & 0xffff;
        do {
          uVar1 = *puVar9;
          if (uVar1 == uVar14) {
            *puVar9 = uVar2;
          }
          if (uVar1 != uVar14) {
            *puVar9 = 0;
          }
          uVar12 = uVar12 - 1 & 0xffff;
          puVar9 = puVar9 + 1;
        } while (uVar12 != 0);
        uVar8 = uVar8 + 1 & 0xfffeffff;
      } while (uVar8 < 0x11c);
    }
    else {
      if (DAT_800148d0[2] == '\x02') {
        uVar11 = 0xf7;
        do {
          puVar9 = (ushort *)(*piVar5 + (uVar11 * 800 + 5) * 2 + 0x248);
          sVar10 = 0x1f;
          do {
            sVar10 = sVar10 + -1;
            if (*puVar9 == uVar14) {
              *puVar9 = uVar2;
            }
            else {
              *puVar9 = 0;
            }
            puVar9 = puVar9 + 1;
          } while (sVar10 != 0);
          uVar11 = uVar11 + 1 & 0xfffeffff;
        } while (uVar11 < 0x11c);
      }
    }
  }
  set_display_color(DAT_800148dc);
  iVar16 = DAT_800148e0;
  iVar15 = DAT_800148e0 + 0x2e;
  FUN_80018da0(0xa1,0x2e,iVar15);
  set_display_color(0);
  iVar13 = iVar16 + 0x21;
  FUN_80018ca8(0x6c,0xaf,iVar13);
  FUN_80018ca8(0xab,0xaf,iVar13);
  FUN_80018ca8(0xea,0xaf,iVar13);
  FUN_8001cccc(0xa1,0x2e,iVar15,iVar16 + 1);
  set_frame_to_global_pointer();
  set_display_color(0);
  display_clear_rect(0xa1,4,0x104,0x2d);
  pcVar7 = DAT_8000dcf0;
  uVar14 = DAT_8000dcf4;
  if (*DAT_8000dcf0 == '\0') {
    uVar14 = DAT_8000dcf8;
  }
  set_display_color(uVar14);
  display_clear_rect(0xa1,5,0xbf,0x28);
  set_display_color(0);
  FUN_800197c8(2);
  FUN_80019730(PTR_PTR_FUN_8000dcfc);
  display_text(&DAT_8000dd00,0xa6,0x10);
  set_display_color(0xffffff);
  if (pcVar7[1] == '\0') {
    pcVar6 = (char *)0x8000dd04;
  }
  else {
    pcVar6 = (char *)0x8000dd08;
  }
  display_text(pcVar6,199,8);
  set_display_color(0xffffff);
  if (pcVar7[2] == '\0') {
    display_text(&DAT_8000dd0c,0xe0,8);
  }
  else {
    if (pcVar7[2] == '\x01') {
      pcVar6 = &DAT_8000dd10;
    }
    else {
      if (pcVar7[2] != '\x02') goto LAB_8000dac0;
      pcVar6 = &DAT_8000dd14;
    }
    display_text(pcVar6,0xde,8);
  }
LAB_8000dac0:
  if (pcVar7[2] != '\0') {
    if (pcVar7[2] == '\x01') {
      switch(pcVar7[3]) {
      case '\0':
switchD_8000db84_caseD_0:
        pcVar7 = &DAT_8000dda4;
        break;
      case '\x01':
        pcVar7 = &DAT_8000dd60;
        break;
      case '\x02':
switchD_8000db84_caseD_2:
        pcVar7 = &DAT_8000dd68;
        break;
      case '\x03':
switchD_8000db84_caseD_3:
        pcVar7 = s_5V_div_8000dd1c;
        break;
      case '\x04':
        pcVar7 = &DAT_8000dd70;
        break;
      case '\x05':
        goto switchD_8000daf0_caseD_2;
      case '\x06':
        goto switchD_8000daf0_caseD_3;
      default:
        goto switchD_8000daf0_caseD_7;
      }
    }
    else {
      if (pcVar7[2] != '\x02') goto switchD_8000daf0_caseD_7;
      switch(pcVar7[3]) {
      case '\0':
        pcVar7 = &DAT_8000dd80;
        break;
      case '\x01':
        pcVar7 = &DAT_8000dd8c;
        break;
      case '\x02':
        pcVar7 = &DAT_8000dd98;
        break;
      case '\x03':
        goto switchD_8000db84_caseD_0;
      case '\x04':
        pcVar7 = &DAT_8000ddac;
        break;
      case '\x05':
        goto switchD_8000db84_caseD_2;
      case '\x06':
        goto switchD_8000db84_caseD_3;
      default:
        goto switchD_8000daf0_caseD_7;
      }
    }
    goto LAB_8000db34;
  }
  switch(pcVar7[3]) {
  case '\0':
    display_text(s_5V_div_8000dd1c,199,0x18);
    goto switchD_8000daf0_caseD_7;
  case '\x01':
    pcVar7 = s_2_5V_div_8000dd24;
    break;
  case '\x02':
switchD_8000daf0_caseD_2:
    pcVar7 = &DAT_8000dd78;
    break;
  case '\x03':
switchD_8000daf0_caseD_3:
    pcVar7 = &DAT_8000dd30;
    break;
  case '\x04':
    pcVar7 = &DAT_8000dd3c;
    break;
  case '\x05':
    pcVar7 = &DAT_8000dd48;
    break;
  case '\x06':
    pcVar7 = &DAT_8000dd54;
    break;
  default:
    goto switchD_8000daf0_caseD_7;
  }
LAB_8000db34:
  display_text(pcVar7,199,0x18);
switchD_8000daf0_caseD_7:
  iVar13 = Start_Of_Screen_Mem;
  iVar16 = Screen_Frame_Buffer;
  uVar14 = 4;
  do {
    iVar15 = uVar14 * 800 + 0xa1;
    copy_short((void *)(iVar13 + iVar15 * 2),(void *)(iVar16 + iVar15 * 2),100);
    uVar14 = uVar14 + 1;
  } while (uVar14 < 0x2d);
  return;
}

