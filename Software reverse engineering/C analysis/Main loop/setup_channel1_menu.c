//------------------------------------------------------------------------------------------------------------------------------------------
//

void FUN_80021c3c(void)

{
  ushort uVar1;
  undefined4 uVar2;
  undefined *puVar3;
  int *piVar4;
  char *pcVar5;
  char *pcVar6;
  uint uVar7;
  ushort *puVar8;
  int iVar9;
  short *psVar10;
  uint uVar11;
  uint uVar12;
  short *psVar13;
  ushort uVar14;
  int iVar15;
  short sVar16;
  undefined4 unaff_r4;
  short sVar17;
  int iVar18;
  undefined2 *puVar19;
  uint uVar20;
  uint color;
  
  FUN_8001c6f0(0xa1,6,0x15D, 0x012D);         //Copy part of the active screen to a save buffer

  set_screen_to_global_pointer();

  sVar17 = (short)DAT_80021d04;               //0x000018C3  The color of the background    00011000  00011000  00011000    0x00181818

  set_screen_to_global_pointer();             //Directly displaying onto the screen

  piVar4 = Global_Frame_Buffer_Pointer;

  puVar3 = PTR_BITMAP_CHANNEL_MENU_80021d08;  //Pointer to the bitmap  0x80051fa4

  uVar20 = 0xfc;                              //252 lines
  uVar11 = uVar20;

  do   //This slides in the bitmap by drawing bigger parts every loop. It starts with 16 lines, then an extra 15, etc. and in the last loops only a single line is added to the total
  {
    while (uVar20 < 0xfc)   //skip first run
    {
      iVar15 = 0xb7;                          //183 pixels

      psVar10 = (short *)(*piVar4 + (uVar20 - uVar11) * 0x640 + 0x120c2);  //Pointer to first pixel on some line on the screen. (Start on y = 46, x = 161)
      psVar13 = (short *)(puVar3 + uVar20 * 0x16e);                        //Pointer to the last line in the bitmap

      do
      {
        sVar16 = *psVar13;       //Get a pixel

        if (*psVar13 == 0)       //When it is zero change its color
        {
          sVar16 = sVar17;
        }

        iVar15 = iVar15 + -1;     //One pixel done
        *psVar10 = sVar16;        //Store it in the screen buffer
        psVar10 = psVar10 + 1;    //Point to next pixel on the screen
        psVar13 = psVar13 + 1;    //Point to next pixel of the bitmap
      } while (iVar15 != 0);

      uVar20 = uVar20 + 1 & 0xfffeffff;   //Do it untill the last line
    }

    //Calculate the next starting line
    uVar20 = (uVar11 - (uVar11 * DAT_80021d10 >> 0x13)) - 1 & 0xffff;    //0x00008889

    uVar11 = uVar20;                   //First start is 235, second 219 etc.

  } while (uVar20 != 0);

  FUN_8001cfb8();  //Empty function

  FUN_8001cfb8();  //Empty function



//display_channel1_menu (jumps to this function instead of call)
  uVar20 = DAT_800148c0;

  uVar2 = DAT_800148bc;

  color = 0;

  set_frame_to_global_pointer();  //Print in other buffer

  piVar4 = Global_Frame_Buffer_Pointer;
  puVar3 = PTR_BITMAP_CHANNEL_MENU_800148c4;
  uVar11 = 0;

  //Display the meny bitmap
  do
  {
    iVar15 = 0xb7;
    puVar8 = (ushort *)(puVar3 + uVar11 * 0x16e);
    puVar19 = (undefined2 *)(*piVar4 + uVar11 * 0x640 + 0x120c2);

    do
    {
      uVar7 = (uint)*puVar8;

      if (*puVar8 == 0)
      {
        uVar7 = uVar20;
      }

      iVar15 = iVar15 + -1;
      *puVar19 = (short)uVar7;
      iVar18 = DAT_800148cc;
      puVar8 = puVar8 + 1;
      puVar19 = puVar19 + 1;
    } while (iVar15 != 0);

    uVar11 = uVar11 + 1 & 0xfffeffff;
  } while (uVar11 < 0xfc);


  uVar11 = 0x42;   //number of lines??

  if (*DAT_800148d0 == '\0')
  {
    uVar7 = DAT_800148cc - 0xef;
  }
  else
  {
    uVar7 = DAT_800148cc - 0xee;
  }

  uVar14 = (ushort)uVar2;

  if (*DAT_800148d0 == '\0')
  {
    do
    {
      puVar8 = (ushort *)(*piVar4 + (uVar11 * 800 + 5) * 2 + 0x232);
      uVar12 = uVar7 & 0xffff;

      do
      {
        if (*puVar8 == uVar20)
        {
          *puVar8 = uVar14;
        }
        else
        {
          *puVar8 = 0;
        }

        uVar12 = uVar12 - 1 & 0xffff;
        puVar8 = puVar8 + 1;
      } while (uVar12 != 0);

      uVar11 = uVar11 + 1 & 0xfffeffff;
    } while (uVar11 < 0x58);
  }
  else
  {
    do {
      puVar8 = (ushort *)(*piVar4 + (uVar11 * 800 + 5) * 2 + 0x1ca);
      uVar12 = uVar7 & 0xffff;
      do {
        if (*puVar8 == uVar20) {
          *puVar8 = uVar14;
        }
        else {
          *puVar8 = 0;
        }
        uVar12 = uVar12 - 1 & 0xffff;
        puVar8 = puVar8 + 1;
      } while (uVar12 != 0);
      uVar11 = uVar11 + 1 & 0xfffeffff;
    } while (uVar11 < 0x58);
  }
  uVar11 = 0x80;

  if (DAT_800148d0[4] == '\0') {
    uVar7 = iVar18 - 0xef;
  }
  else {
    uVar7 = iVar18 - 0xee;
  }
  if (DAT_800148d0[4] == '\0') {
    do {
      puVar8 = (ushort *)(*piVar4 + (uVar11 * 800 + 5) * 2 + 0x232);
      uVar12 = uVar7 & 0xffff;
      do {
        if (*puVar8 == uVar20) {
          *puVar8 = uVar14;
        }
        else {
          *puVar8 = 0;
        }
        uVar12 = uVar12 - 1 & 0xffff;
        puVar8 = puVar8 + 1;
      } while (uVar12 != 0);
      uVar11 = uVar11 + 1 & 0xfffeffff;
    } while (uVar11 < 0x96);
  }
  else {
    do {
      puVar8 = (ushort *)(*piVar4 + (uVar11 * 800 + 5) * 2 + 0x1ca);
      uVar12 = uVar7 & 0xffff;
      do {
        if (*puVar8 == uVar20) {
          *puVar8 = uVar14;
        }
        else {
          *puVar8 = 0;
        }
        uVar12 = uVar12 - 1 & 0xffff;
        puVar8 = puVar8 + 1;
      } while (uVar12 != 0);
      uVar11 = uVar11 + 1 & 0xfffeffff;
    } while (uVar11 < 0x96);
  }
  uVar11 = 0xc0;
  if (DAT_800148d0[1] == '\0') {
    uVar7 = iVar18 - 0xee;
  }
  else {
    uVar7 = iVar18 - 0xef;
  }
  if (DAT_800148d0[1] == '\0') {
    do {
      puVar8 = (ushort *)(*piVar4 + (uVar11 * 800 + 5) * 2 + 0x1ca);
      uVar12 = uVar7 & 0xffff;
      do {
        if (*puVar8 == uVar20) {
          *puVar8 = uVar14;
        }
        else {
          *puVar8 = 0;
        }
        uVar12 = uVar12 - 1 & 0xffff;
        puVar8 = puVar8 + 1;
      } while (uVar12 != 0);
      uVar11 = uVar11 + 1 & 0xfffeffff;
    } while (uVar11 < 0xd6);
  }
  else {
    do {
      puVar8 = (ushort *)(*piVar4 + (uVar11 * 800 + 5) * 2 + 0x232);
      uVar12 = uVar7 & 0xffff;
      do {
        if (*puVar8 == uVar20) {
          *puVar8 = uVar14;
        }
        else {
          *puVar8 = 0;
        }
        uVar12 = uVar12 - 1 & 0xffff;
        puVar8 = puVar8 + 1;
      } while (uVar12 != 0);
      uVar11 = uVar11 + 1 & 0xfffeffff;
    } while (uVar11 < 0xd6);
  }

  if (DAT_800148d0[2] == '\0')
  {
    uVar7 = 0xf7;
    uVar11 = DAT_800148d4 - 0xee;
    do {
      puVar8 = (ushort *)(*piVar4 + (uVar7 * 800 + 5) * 2 + 0x1ca);
      uVar12 = uVar11 & 0xffff;
      do {
        if (*puVar8 == uVar20) {
          *puVar8 = uVar14;
        }
        else {
          *puVar8 = 0;
        }
        uVar12 = uVar12 - 1 & 0xffff;
        puVar8 = puVar8 + 1;
      } while (uVar12 != 0);

      uVar7 = uVar7 + 1 & 0xfffeffff;
    } while (uVar7 < 0x11c);
  }
  else
  {
    if (DAT_800148d0[2] == '\x01')
    {
      uVar7 = 0xf7;
      uVar11 = DAT_800148d8 - 0x110;
      do {
        puVar8 = (ushort *)(*piVar4 + (uVar7 * 800 + 5) * 2 + 0x20e);
        uVar12 = uVar11 & 0xffff;
        do {
          uVar1 = *puVar8;
          if (uVar1 == uVar20) {
            *puVar8 = uVar14;
          }
          if (uVar1 != uVar20) {
            *puVar8 = 0;
          }
          uVar12 = uVar12 - 1 & 0xffff;
          puVar8 = puVar8 + 1;
        } while (uVar12 != 0);
        uVar7 = uVar7 + 1 & 0xfffeffff;
      } while (uVar7 < 0x11c);
    }
    else {
      if (DAT_800148d0[2] == '\x02') {
        uVar11 = 0xf7;
        do {
          puVar8 = (ushort *)(*piVar4 + (uVar11 * 800 + 5) * 2 + 0x248);
          sVar17 = 0x1f;
          do {
            sVar17 = sVar17 + -1;
            if (*puVar8 == uVar20) {
              *puVar8 = uVar14;
            }
            else {
              *puVar8 = 0;
            }
            puVar8 = puVar8 + 1;
          } while (sVar17 != 0);
          uVar11 = uVar11 + 1 & 0xfffeffff;
        } while (uVar11 < 0x11c);
      }
    }
  }

  set_display_fg_color(DAT_800148dc);
  iVar15 = DAT_800148e0;
  iVar18 = DAT_800148e0 + 0x2e;
  FUN_80018da0(0xa1,0x2e,iVar18,DAT_800148e0,color,unaff_r4);
  set_display_fg_color(color);
  uVar14 = (short)iVar15 + 0x21;
  display_draw_horz_line(0x6c,0xaf,uVar14);
  display_draw_horz_line(0xab,0xaf,uVar14);
  display_draw_horz_line(0xea,0xaf,uVar14);
  copy_rect_to_screen(0xa1,0x2e,(ushort)iVar18,(short)iVar15 + 1);
  set_frame_to_global_pointer();
  set_display_fg_color(0);
  display_fill_rect(0xa1,4,0x104,0x2d);
  pcVar6 = DAT_8000dcf0;
  uVar20 = DAT_8000dcf4;
  if (*DAT_8000dcf0 == '\0') {
    uVar20 = DAT_8000dcf8;
  }
  set_display_fg_color(uVar20);
  display_fill_rect(0xa1,5,0xbf,0x28);
  set_display_fg_color(0);
  set_font_paint_mode(2);
  select_font(PTR_FONT_2_8000dcfc);
  display_text(&DAT_8000dd00,0xa6,0x10);
  set_display_fg_color(0xffffff);
  if (pcVar6[1] == '\0') {
    pcVar5 = (char *)0x8000dd04;
  }
  else {
    pcVar5 = (char *)0x8000dd08;
  }
  display_text(pcVar5,199,8);
  set_display_fg_color(0xffffff);
  if (pcVar6[2] == '\0') {
    display_text(&DAT_8000dd0c,0xe0,8);
  }
  else {
    if (pcVar6[2] == '\x01') {
      pcVar5 = &DAT_8000dd10;
    }
    else {
      if (pcVar6[2] != '\x02') goto LAB_8000dac0;
      pcVar5 = &DAT_8000dd14;
    }
    display_text(pcVar5,0xde,8);
  }
LAB_8000dac0:
  if (pcVar6[2] != '\0') {
    if (pcVar6[2] == '\x01') {
      switch(pcVar6[3]) {
      case '\0':
switchD_8000db84_caseD_0:
        pcVar6 = &DAT_8000dda4;
        break;
      case '\x01':
        pcVar6 = &DAT_8000dd60;
        break;
      case '\x02':
switchD_8000db84_caseD_2:
        pcVar6 = &DAT_8000dd68;
        break;
      case '\x03':
switchD_8000db84_caseD_3:
        pcVar6 = s_5V_div_8000dd1c;
        break;
      case '\x04':
        pcVar6 = &DAT_8000dd70;
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
      if (pcVar6[2] != '\x02') goto switchD_8000daf0_caseD_7;
      switch(pcVar6[3]) {
      case '\0':
        pcVar6 = &DAT_8000dd80;
        break;
      case '\x01':
        pcVar6 = &DAT_8000dd8c;
        break;
      case '\x02':
        pcVar6 = &DAT_8000dd98;
        break;
      case '\x03':
        goto switchD_8000db84_caseD_0;
      case '\x04':
        pcVar6 = &DAT_8000ddac;
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
  switch(pcVar6[3]) {
  case '\0':
    display_text(s_5V_div_8000dd1c,199,0x18);
    goto switchD_8000daf0_caseD_7;
  case '\x01':
    pcVar6 = s_2_5V_div_8000dd24;
    break;
  case '\x02':
switchD_8000daf0_caseD_2:
    pcVar6 = &DAT_8000dd78;
    break;
  case '\x03':
switchD_8000daf0_caseD_3:
    pcVar6 = &DAT_8000dd30;
    break;
  case '\x04':
    pcVar6 = &DAT_8000dd3c;
    break;
  case '\x05':
    pcVar6 = &DAT_8000dd48;
    break;
  case '\x06':
    pcVar6 = &DAT_8000dd54;
    break;
  default:
    goto switchD_8000daf0_caseD_7;
  }
LAB_8000db34:
  display_text(pcVar6,199,0x18);
switchD_8000daf0_caseD_7:
  iVar18 = Start_Of_Screen_Mem;
  iVar15 = Screen_Frame_Buffer;
  uVar20 = 4;
  do {
    iVar9 = uVar20 * 800 + 0xa1;
    copy_short((void *)(iVar18 + iVar9 * 2),(void *)(iVar15 + iVar9 * 2),100);
    uVar20 = uVar20 + 1;
  } while (uVar20 < 0x2d);
  return;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//  (0xa1, 6, 0x15D, 0x012D)


void FUN_8001c6f0(uint param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  uint uVar2;
  undefined2 *puVar3;
  undefined2 *puVar4;
  int iVar5;
  int iVar6;
  undefined2 *puVar7;
  int iVar8;
  undefined2 *puVar9;
  
  iVar6 = Screen_Frame_Buffer_2;   //0x804401B4
  iVar5 = Start_Of_Screen_Mem;     //0x803849A0
  if (param_2 < param_4)
  {
    uVar1 = (param_3 - param_1) * 0x8000 >> 0x10;  //Count div 2 because it copies 2 pixels per round

    do
    {
      if (param_1 < param_3)
      {
        iVar8 = param_1 + param_2 * 800;             //Index into buffers based on xstart and ystart
        puVar7 = (undefined2 *)(iVar5 + iVar8 * 2);  //Start of line in Start_Of_Screen_Mem
        puVar9 = (undefined2 *)(iVar6 + iVar8 * 2);  //Start of line in Screen_Frame_Buffer_2
        uVar2 = uVar1;                               //X count
        puVar3 = puVar9 + -1;                        //Point to one pixel before in Screen_Frame_Buffer_2
        puVar4 = puVar7 + -1;                        //Point to one pixel before in Start_Of_Screen_Mem

        if ((param_3 - param_1 & 1) != 0)            //For odd numer of pixels
        {
          *puVar9 = *puVar7;                         //Copy the first pixel from Start_Of_Screen_Mem to Screen_Frame_Buffer_2
          puVar3 = puVar9;                           //Start on first pixel
          puVar4 = puVar7;
        }

        while (uVar2 != 0)
        {
          puVar3[1] = puVar4[1];                     //Copy second pixel
          puVar3[2] = puVar4[2];                     //Copy third pixel
          uVar2 = uVar2 - 1 & 0xffff;                //One done
          puVar3 = puVar3 + 2;
          puVar4 = puVar4 + 2;
        }
      }

      param_2 = param_2 + 1 & 0xfffeffff;
    } while (param_2 < param_4);

    return;
  }

  return;
}

//------------------------------------------------------------------------------------------------------------------------------------------

