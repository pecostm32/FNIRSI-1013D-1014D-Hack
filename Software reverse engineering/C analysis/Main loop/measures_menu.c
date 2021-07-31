//----------------------------------------------------------------------------------------------------------------------

void slide_measures_menu_on_screen(void)

{
  uint uVar1;
  uint uVar2;
  undefined *puVar3;
  int *piVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  undefined2 *puVar8;
  int iVar9;
  ushort *puVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  
  uVar2 = DAT_8000eaf8;             //0x00004228
  uVar1 = DAT_8000eaf4;             //0x000018C3
  iVar7 = DAT_8000eb0c;             //0x66666667
  uVar6 = DAT_8000eb08;             //0x000001F3
  uVar5 = DAT_8000eb04;             //0x0000FFFF

  set_screen_to_global_pointer();

  piVar4 = Global_Frame_Buffer_Pointer;
  puVar3 = PTR_BITMAP_MEASURES_MENU_8000eafc;
  uVar15 = 0;

  //Keep looping until the whole image is on the screen
  do
  {
    uVar11 = 0;  //Starting line from offset position

    //Draw the lines
    do
    {
      if (uVar15 != 0)
      {
        //Calculate the starting pixel
        puVar8 = (undefined2 *)(*piVar4 + (uVar11 * 800 - uVar15) * 2 + 0x67174);   //Offset is 263 lines and pixel 730
        puVar10 = (ushort *)(puVar3 + uVar11 * DAT_8000eb08 * 2);                   //First pixel of current line in the bitmap
        uVar12 = uVar15;                                                            //Number of pixels to do

        do
        {
          uVar13 = (uint)*puVar10;
          uVar14 = uVar1;

          if (uVar13 != 0)
          {
            if (uVar13 == 0xf800)
            {
              uVar14 = 0;
            }
            else
            {
              uVar14 = uVar13;

              if (uVar13 == uVar5)
              {
                uVar14 = uVar2;
              }
            }
          }

          uVar12 = uVar12 - 1;
          *puVar8 = (short)uVar14;
          puVar8 = puVar8 + 1;
          puVar10 = puVar10 + 1;
        } while (uVar12 != 0);
      }

      uVar11 = uVar11 + 1 & 0xfffeffff;
    } while (uVar11 < 0xd6);

    iVar9 = (int)((ulonglong)((longlong)iVar7 * (longlong)(int)(uVar6 - uVar15)) >> 0x20);
    uVar15 = (((iVar9 >> 2) - (iVar9 >> 0x1f)) + uVar15 & 0xffff) + 1 & 0xfffeffff;
  } while (uVar15 < uVar6);

  return;
}

//----------------------------------------------------------------------------------------------------------------------
//Setup_measures_menu
void FUN_80021dec(void)

{
  undefined2 uVar1;
  uint uVar2;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  ushort *puVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  undefined2 *puVar12;
  ushort uVar13;
  short sVar14;
  uint uVar15;
  int iVar16;
  
  uVar13 = (ushort)DAT_80021e18;
  copy_rect_from_screen(0xe6,uVar13 - 0xd8,uVar13 + 0xfb,uVar13);
  slide_measures_menu_on_screen();            //Slide the menu onto the screen
  set_screen_to_global_pointer();
  empty_func_7();

//Handle measures menu function
  iVar3 = DAT_800152dc;
  uVar2 = DAT_800152d8;              //0x0000FFFF
  uVar9 = DAT_800152d4;
  uVar15 = DAT_800152d0;
  set_frame_to_global_pointer();
  iVar5 = DAT_800152e4;              //0xFFF99274  (so a negative number being added gives 421260 plus is 263 lines and 230 pixels)
  puVar4 = PTR_BITMAP_MEASURES_MENU_800152e0;
  uVar11 = 0;

  //Draw the menu again
  do {
    puVar12 = (undefined2 *)((*Global_Frame_Buffer_Pointer + uVar11 * 0x640) - iVar5);
    puVar8 = (ushort *)(puVar4 + uVar11 * DAT_800152dc * 2);
    iVar16 = iVar3;
    do {
      uVar6 = (uint)*puVar8;
      uVar7 = uVar15;
      if (uVar6 != 0) {
        if (uVar6 == 0xf800)  //Make red pixels black
        {
          uVar7 = 0;
        }
        else
        {
          uVar7 = uVar6;

          if (uVar6 == uVar2)  //Make white pixels 0x00004228 (0x00404440)
          {
            uVar7 = uVar9;     //So text is made grey
          }
        }
      }
      iVar16 = iVar16 + -1;
      *puVar12 = (short)uVar7;
      puVar12 = puVar12 + 1;
      puVar8 = puVar8 + 1;
    } while (iVar16 != 0);

    //Walk through the image lines??
    do
    {
      uVar11 = uVar11 + 1 & 0xfffeffff;   //Line index

      if (0xd5 < uVar11)
      {
        set_font_paint_mode(2);
        select_font(PTR_FONT_2_800152ec);
        set_display_fg_color(0);                        //Black color
        uVar13 = (ushort)DAT_800152f0;
        display_text(&DAT_800152f4,0xef,uVar13);        //"CH2"
        display_text(&DAT_800152f8,0x1e8,uVar13);       //"CH1"
        uVar1 = (undefined2)uVar2;                      //0x0000FFFF (white color)


        //Paint the white pixels found in the source bitmap white in the target if some variable not is zero
        if (*(char *)(DAT_800152fc + 0x1c2) != '\0')    //0x801FA24C + 0x1C2  Channel2 Vmax
        {
          uVar15 = 0x1b;                    //Starting line 27, so first item row
          do
          {
            sVar14 = 0x3d;                  //61 pixels
            puVar12 = (undefined2 *)((*Global_Frame_Buffer_Pointer + (uVar15 * 800 + 2) * 2) - iVar5);
            puVar8 = (ushort *)(puVar4 + (uVar15 * iVar3 + 2) * 2);

            do
            {
              sVar14 = sVar14 + -1;

              if (*puVar8 == uVar2)
              {
                *puVar12 = uVar1;
              }
              puVar12 = puVar12 + 1;
              puVar8 = puVar8 + 1;
            } while (sVar14 != 0);

            uVar15 = uVar15 + 1 & 0xfffeffff;
          } while (uVar15 < 0x58);                       //end line 88 so 61 lines handled
        }

        if (*(char *)(DAT_800152fc + 0x1d2) != '\0')    //Channel 2 Vmin
        {
          uVar15 = 0x1b;
          do {
            sVar14 = 0x3d;
            puVar12 = (undefined2 *)
                      ((*Global_Frame_Buffer_Pointer + (uVar15 * 800 + 0x40) * 2) - iVar5);
            puVar8 = (ushort *)(puVar4 + (uVar15 * iVar3 + 0x40) * 2);
            do {
              sVar14 = sVar14 + -1;
              if (*puVar8 == uVar2) {
                *puVar12 = uVar1;
              }
              puVar12 = puVar12 + 1;
              puVar8 = puVar8 + 1;
            } while (sVar14 != 0);
            uVar15 = uVar15 + 1 & 0xfffeffff;
          } while (uVar15 < 0x58);
        }

        if (*(char *)(DAT_800152fc + 0x1e2) != '\0')   //Channel 2 Vavg
        {
          uVar15 = 0x1b;
          do {
            sVar14 = 0x3d;
            puVar12 = (undefined2 *)
                      ((*Global_Frame_Buffer_Pointer + (uVar15 * 800 + 0x7e) * 2) - iVar5);
            puVar8 = (ushort *)(puVar4 + (uVar15 * iVar3 + 0x7e) * 2);
            do {
              sVar14 = sVar14 + -1;
              if (*puVar8 == uVar2) {
                *puVar12 = uVar1;
              }
              puVar12 = puVar12 + 1;
              puVar8 = puVar8 + 1;
            } while (sVar14 != 0);
            uVar15 = uVar15 + 1 & 0xfffeffff;
          } while (uVar15 < 0x58);
        }

        if (*(char *)(DAT_800152fc + 0x1f2) != '\0')   //Channel 2 Vrms
        {
          uVar15 = 0x1b;
          do {
            sVar14 = 0x3d;
            puVar12 = (undefined2 *)
                      ((*Global_Frame_Buffer_Pointer + (uVar15 * 800 + 0xbc) * 2) - iVar5);
            puVar8 = (ushort *)(puVar4 + (uVar15 * iVar3 + 0xbc) * 2);
            do {
              sVar14 = sVar14 + -1;
              if (*puVar8 == uVar2) {
                *puVar12 = uVar1;
              }
              puVar12 = puVar12 + 1;
              puVar8 = puVar8 + 1;
            } while (sVar14 != 0);
            uVar15 = uVar15 + 1 & 0xfffeffff;
          } while (uVar15 < 0x58);
        }

        if (*(char *)(DAT_800152fc + 0x202) != '\0')   //Channel 2 VPP
        {
          uVar15 = 0x59;
          do {
            sVar14 = 0x3d;
            puVar12 = (undefined2 *)
                      ((*Global_Frame_Buffer_Pointer + (uVar15 * 800 + 2) * 2) - iVar5);
            puVar8 = (ushort *)(puVar4 + (uVar15 * iVar3 + 2) * 2);
            do {
              sVar14 = sVar14 + -1;
              if (*puVar8 == uVar2) {
                *puVar12 = uVar1;
              }
              puVar12 = puVar12 + 1;
              puVar8 = puVar8 + 1;
            } while (sVar14 != 0);
            uVar15 = uVar15 + 1 & 0xfffeffff;
          } while (uVar15 < 0x96);
        }

        if (*(char *)(DAT_800152fc + 0x212) != '\0')   //Channel 2 VP
        {
          uVar15 = 0x59;
          do {
            sVar14 = 0x3d;
            puVar12 = (undefined2 *)
                      ((*Global_Frame_Buffer_Pointer + (uVar15 * 800 + 0x40) * 2) - iVar5);
            puVar8 = (ushort *)(puVar4 + (uVar15 * iVar3 + 0x40) * 2);
            do {
              sVar14 = sVar14 + -1;
              if (*puVar8 == uVar2) {
                *puVar12 = uVar1;
              }
              puVar12 = puVar12 + 1;
              puVar8 = puVar8 + 1;
            } while (sVar14 != 0);
            uVar15 = uVar15 + 1 & 0xfffeffff;
          } while (uVar15 < 0x96);
        }

        if (*(char *)(DAT_800152fc + 0x232) != '\0')  //Channel 2 Freq
        {
          uVar15 = 0x59;
          do {
            sVar14 = 0x3d;
            puVar12 = (undefined2 *)
                      ((*Global_Frame_Buffer_Pointer + (uVar15 * 800 + 0x7e) * 2) - iVar5);
            puVar8 = (ushort *)(puVar4 + (uVar15 * iVar3 + 0x7e) * 2);
            do {
              sVar14 = sVar14 + -1;
              if (*puVar8 == uVar2) {
                *puVar12 = uVar1;
              }
              puVar12 = puVar12 + 1;
              puVar8 = puVar8 + 1;
            } while (sVar14 != 0);
            uVar15 = uVar15 + 1 & 0xfffeffff;
          } while (uVar15 < 0x96);
        }

        if (*(char *)(DAT_800152fc + 0x242) != '\0')    //Channel 2 Cycle
        {
          uVar15 = 0x59;
          do {
            sVar14 = 0x3d;
            puVar12 = (undefined2 *)
                      ((*Global_Frame_Buffer_Pointer + (uVar15 * 800 + 0xbc) * 2) - iVar5);
            puVar8 = (ushort *)(puVar4 + (uVar15 * iVar3 + 0xbc) * 2);
            do {
              sVar14 = sVar14 + -1;
              if (*puVar8 == uVar2) {
                *puVar12 = uVar1;
              }
              puVar12 = puVar12 + 1;
              puVar8 = puVar8 + 1;
            } while (sVar14 != 0);
            uVar15 = uVar15 + 1 & 0xfffeffff;
          } while (uVar15 < 0x96);
        }

        if (*(char *)(DAT_800152fc + 0x252) != '\0')    //Channel 2 Tim+
        {
          uVar15 = 0x97;
          do {
            sVar14 = 0x3d;
            puVar12 = (undefined2 *)
                      ((*Global_Frame_Buffer_Pointer + (uVar15 * 800 + 2) * 2) - iVar5);
            puVar8 = (ushort *)(puVar4 + (uVar15 * iVar3 + 2) * 2);
            do {
              sVar14 = sVar14 + -1;
              if (*puVar8 == uVar2) {
                *puVar12 = uVar1;
              }
              puVar12 = puVar12 + 1;
              puVar8 = puVar8 + 1;
            } while (sVar14 != 0);
            uVar15 = uVar15 + 1 & 0xfffeffff;
          } while (uVar15 < 0xd4);
        }

        if (*(char *)(DAT_800152fc + 0x262) != '\0')   //Channel 2 Tim-
        {
          uVar15 = 0x97;
          do {
            sVar14 = 0x3d;
            puVar12 = (undefined2 *)
                      ((*Global_Frame_Buffer_Pointer + (uVar15 * 800 + 0x40) * 2) - iVar5);
            puVar8 = (ushort *)(puVar4 + (uVar15 * iVar3 + 0x40) * 2);
            do {
              sVar14 = sVar14 + -1;
              if (*puVar8 == uVar2) {
                *puVar12 = uVar1;
              }
              puVar12 = puVar12 + 1;
              puVar8 = puVar8 + 1;
            } while (sVar14 != 0);
            uVar15 = uVar15 + 1 & 0xfffeffff;
          } while (uVar15 < 0xd4);
        }

        if (*(char *)(DAT_800152fc + 0x272) != '\0')  //Channel 2 Duty+
        {
          uVar15 = 0x97;
          do {
            sVar14 = 0x3d;
            puVar12 = (undefined2 *)
                      ((*Global_Frame_Buffer_Pointer + (uVar15 * 800 + 0x7e) * 2) - iVar5);
            puVar8 = (ushort *)(puVar4 + (uVar15 * iVar3 + 0x7e) * 2);
            do {
              sVar14 = sVar14 + -1;
              if (*puVar8 == uVar2) {
                *puVar12 = uVar1;
              }
              puVar12 = puVar12 + 1;
              puVar8 = puVar8 + 1;
            } while (sVar14 != 0);
            uVar15 = uVar15 + 1 & 0xfffeffff;
          } while (uVar15 < 0xd4);
        }

        if (*(char *)(DAT_800152fc + 0x282) != '\0')  //Channel 2 Duty-
        {
          uVar15 = 0x97;
          do {
            sVar14 = 0x3d;
            puVar12 = (undefined2 *)
                      ((*Global_Frame_Buffer_Pointer + (uVar15 * 800 + 0xbc) * 2) - iVar5);
            puVar8 = (ushort *)(puVar4 + (uVar15 * iVar3 + 0xbc) * 2);
            do {
              sVar14 = sVar14 + -1;
              if (*puVar8 == uVar2) {
                *puVar12 = uVar1;
              }
              puVar12 = puVar12 + 1;
              puVar8 = puVar8 + 1;
            } while (sVar14 != 0);
            uVar15 = uVar15 + 1 & 0xfffeffff;
          } while (uVar15 < 0xd4);
        }

        if (*(char *)(DAT_800152fc + 0x100) != '\0')  //Channel 1 Vmax
        {
          uVar11 = 0x1b;
          uVar15 = DAT_80015ef8 | (int)DAT_80015ef8 >> 4;
          uVar9 = DAT_80015ef8 - 0xf9;
          do {
            if (0xfa < (int)uVar15) {
              puVar12 = (undefined2 *)
                        ((*Global_Frame_Buffer_Pointer + (uVar11 * 800 + 0xfa) * 2) - iVar5);
              uVar7 = uVar9 & 0xffff;
              puVar8 = (ushort *)(puVar4 + (uVar11 * iVar3 + 0xfa) * 2);
              do {
                if (*puVar8 == uVar2) {
                  *puVar12 = uVar1;
                }
                uVar7 = uVar7 - 1 & 0xffff;
                puVar12 = puVar12 + 1;
                puVar8 = puVar8 + 1;
              } while (uVar7 != 0);
            }
            uVar11 = uVar11 + 1 & 0xfffeffff;
          } while (uVar11 < 0x58);
        }

        iVar16 = DAT_80015efc;
        if (*(char *)(DAT_800152fc + 0x112) != '\0') {
          uVar15 = 0x1b;
          do {
            if (0x138 < iVar16) {
              sVar14 = 0x3d;
              puVar12 = (undefined2 *)
                        ((*Global_Frame_Buffer_Pointer + (uVar15 * 800 + 0x138) * 2) - iVar5);
              puVar8 = (ushort *)(puVar4 + (uVar15 * iVar3 + 0x138) * 2);
              do {
                sVar14 = sVar14 + -1;
                if (*puVar8 == uVar2) {
                  *puVar12 = uVar1;
                }
                puVar12 = puVar12 + 1;
                puVar8 = puVar8 + 1;
              } while (sVar14 != 0);
            }
            uVar15 = uVar15 + 1 & 0xfffeffff;
          } while (uVar15 < 0x58);
        }

        if (*(char *)(DAT_800152fc + 0x122) != '\0') {
          uVar11 = 0x1b;
          uVar15 = DAT_80015f00 | (int)DAT_80015f00 >> 7;
          uVar9 = DAT_80015f00 - 0x175;
          do {
            if (0x176 < (int)uVar15) {
              puVar12 = (undefined2 *)
                        ((*Global_Frame_Buffer_Pointer + (uVar11 * 800 + 0x176) * 2) - iVar5);
              uVar7 = uVar9 & 0xffff;
              puVar8 = (ushort *)(puVar4 + (uVar11 * iVar3 + 0x176) * 2);
              do {
                if (*puVar8 == uVar2) {
                  *puVar12 = uVar1;
                }
                uVar7 = uVar7 - 1 & 0xffff;
                puVar12 = puVar12 + 1;
                puVar8 = puVar8 + 1;
              } while (uVar7 != 0);
            }
            uVar11 = uVar11 + 1 & 0xfffeffff;
          } while (uVar11 < 0x58);
        }

        iVar16 = DAT_80015f04;
        if (*(char *)(DAT_800152fc + 0x132) != '\0') {
          uVar15 = 0x1b;
          do {
            if (0x1b4 < iVar16) {
              sVar14 = 0x3d;
              puVar12 = (undefined2 *)
                        ((*Global_Frame_Buffer_Pointer + (uVar15 * 800 + 0x1b4) * 2) - iVar5);
              puVar8 = (ushort *)(puVar4 + (uVar15 * iVar3 + 0x1b4) * 2);
              do {
                sVar14 = sVar14 + -1;
                if (*puVar8 == uVar2) {
                  *puVar12 = uVar1;
                }
                puVar12 = puVar12 + 1;
                puVar8 = puVar8 + 1;
              } while (sVar14 != 0);
            }
            uVar15 = uVar15 + 1 & 0xfffeffff;
          } while (uVar15 < 0x58);
        }

        if (*(char *)(DAT_800152fc + 0x142) != '\0') {
          uVar11 = 0x59;
          uVar15 = DAT_80015ef8 | (int)DAT_80015ef8 >> 4;
          uVar9 = DAT_80015ef8 - 0xf9;
          do {
            if (0xfa < (int)uVar15) {
              puVar12 = (undefined2 *)
                        ((*Global_Frame_Buffer_Pointer + (uVar11 * 800 + 0xfa) * 2) - iVar5);
              uVar7 = uVar9 & 0xffff;
              puVar8 = (ushort *)(puVar4 + (uVar11 * iVar3 + 0xfa) * 2);
              do {
                if (*puVar8 == uVar2) {
                  *puVar12 = uVar1;
                }
                uVar7 = uVar7 - 1 & 0xffff;
                puVar12 = puVar12 + 1;
                puVar8 = puVar8 + 1;
              } while (uVar7 != 0);
            }
            uVar11 = uVar11 + 1 & 0xfffeffff;
          } while (uVar11 < 0x96);
        }
        iVar16 = DAT_80015efc;
        if (*(char *)(DAT_800152fc + 0x152) != '\0') {
          uVar15 = 0x59;
          do {
            if (0x138 < iVar16) {
              sVar14 = 0x3d;
              puVar12 = (undefined2 *)
                        ((*Global_Frame_Buffer_Pointer + (uVar15 * 800 + 0x138) * 2) - iVar5);
              puVar8 = (ushort *)(puVar4 + (uVar15 * iVar3 + 0x138) * 2);
              do {
                sVar14 = sVar14 + -1;
                if (*puVar8 == uVar2) {
                  *puVar12 = uVar1;
                }
                puVar12 = puVar12 + 1;
                puVar8 = puVar8 + 1;
              } while (sVar14 != 0);
            }
            uVar15 = uVar15 + 1 & 0xfffeffff;
          } while (uVar15 < 0x96);
        }
        if (*(char *)(DAT_800152fc + 0x162) != '\0') {
          uVar11 = 0x59;
          uVar15 = DAT_80015f00 | (int)DAT_80015f00 >> 7;
          uVar9 = DAT_80015f00 - 0x175;
          do {
            if (0x176 < (int)uVar15) {
              puVar12 = (undefined2 *)
                        ((*Global_Frame_Buffer_Pointer + (uVar11 * 800 + 0x176) * 2) - iVar5);
              uVar7 = uVar9 & 0xffff;
              puVar8 = (ushort *)(puVar4 + (uVar11 * iVar3 + 0x176) * 2);
              do {
                if (*puVar8 == uVar2) {
                  *puVar12 = uVar1;
                }
                uVar7 = uVar7 - 1 & 0xffff;
                puVar12 = puVar12 + 1;
                puVar8 = puVar8 + 1;
              } while (uVar7 != 0);
            }
            uVar11 = uVar11 + 1 & 0xfffeffff;
          } while (uVar11 < 0x96);
        }
        iVar16 = DAT_80015f04;
        if (*(char *)(DAT_800152fc + 0x172) != '\0') {
          uVar15 = 0x59;
          do {
            if (0x1b4 < iVar16) {
              sVar14 = 0x3d;
              puVar12 = (undefined2 *)
                        ((*Global_Frame_Buffer_Pointer + (uVar15 * 800 + 0x1b4) * 2) - iVar5);
              puVar8 = (ushort *)(puVar4 + (uVar15 * iVar3 + 0x1b4) * 2);
              do {
                sVar14 = sVar14 + -1;
                if (*puVar8 == uVar2) {
                  *puVar12 = uVar1;
                }
                puVar12 = puVar12 + 1;
                puVar8 = puVar8 + 1;
              } while (sVar14 != 0);
            }
            uVar15 = uVar15 + 1 & 0xfffeffff;
          } while (uVar15 < 0x96);
        }
        if (*(char *)(DAT_800152fc + 0x182) != '\0') {
          uVar11 = 0x97;
          uVar15 = DAT_80015ef8 | (int)DAT_80015ef8 >> 4;
          uVar9 = DAT_80015ef8 - 0xf9;
          do {
            if (0xfa < (int)uVar15) {
              puVar12 = (undefined2 *)
                        ((*Global_Frame_Buffer_Pointer + (uVar11 * 800 + 0xfa) * 2) - iVar5);
              uVar7 = uVar9 & 0xffff;
              puVar8 = (ushort *)(puVar4 + (uVar11 * iVar3 + 0xfa) * 2);
              do {
                if (*puVar8 == uVar2) {
                  *puVar12 = uVar1;
                }
                uVar7 = uVar7 - 1 & 0xffff;
                puVar12 = puVar12 + 1;
                puVar8 = puVar8 + 1;
              } while (uVar7 != 0);
            }
            uVar11 = uVar11 + 1 & 0xfffeffff;
          } while (uVar11 < 0xd4);
        }
        iVar16 = DAT_80015efc;
        if (*(char *)(DAT_800152fc + 0x192) != '\0') {
          uVar15 = 0x97;
          do {
            if (0x138 < iVar16) {
              sVar14 = 0x3d;
              puVar12 = (undefined2 *)
                        ((*Global_Frame_Buffer_Pointer + (uVar15 * 800 + 0x138) * 2) - iVar5);
              puVar8 = (ushort *)(puVar4 + (uVar15 * iVar3 + 0x138) * 2);
              do {
                sVar14 = sVar14 + -1;
                if (*puVar8 == uVar2) {
                  *puVar12 = uVar1;
                }
                puVar12 = puVar12 + 1;
                puVar8 = puVar8 + 1;
              } while (sVar14 != 0);
            }
            uVar15 = uVar15 + 1 & 0xfffeffff;
          } while (uVar15 < 0xd4);
        }
        if (*(char *)(DAT_800152fc + 0x1a2) != '\0') {
          uVar9 = 0x97;
          uVar11 = DAT_80015f00 | (int)DAT_80015f00 >> 7;
          uVar15 = DAT_80015f00 - 0x175;
          do {
            if (0x176 < (int)uVar11) {
              puVar12 = (undefined2 *)
                        ((*Global_Frame_Buffer_Pointer + (uVar9 * 800 + 0x176) * 2) - iVar5);
              uVar7 = uVar15 & 0xffff;
              puVar8 = (ushort *)(puVar4 + (uVar9 * iVar3 + 0x176) * 2);
              do {
                if (*puVar8 == uVar2) {
                  *puVar12 = uVar1;
                }
                uVar7 = uVar7 - 1 & 0xffff;
                puVar12 = puVar12 + 1;
                puVar8 = puVar8 + 1;
              } while (uVar7 != 0);
            }
            uVar9 = uVar9 + 1 & 0xfffeffff;
          } while (uVar9 < 0xd4);
        }
        iVar16 = DAT_80015f04;
        if (*(char *)(DAT_800152fc + 0x1b2) != '\0')  //Channel 1 Duty-
        {
          uVar15 = 0x97;
          do {
            if (0x1b4 < iVar16) {
              puVar12 = (undefined2 *)
                        ((*Global_Frame_Buffer_Pointer + (uVar15 * 800 + 0x1b4) * 2) - iVar5);
              puVar8 = (ushort *)(puVar4 + (uVar15 * iVar3 + 0x1b4) * 2);
              sVar14 = 0x3d;
              do {
                sVar14 = sVar14 + -1;
                if (*puVar8 == uVar2) {
                  *puVar12 = uVar1;
                }
                puVar12 = puVar12 + 1;
                puVar8 = puVar8 + 1;
              } while (sVar14 != 0);
            }
            uVar15 = uVar15 + 1 & 0xfffeffff;
          } while (uVar15 < 0xd4);
        }


        iVar5 = Start_Of_Screen_Mem;
        iVar3 = Screen_Frame_Buffer;
        uVar15 = DAT_80015f08;
        uVar9 = DAT_80015f08 - 0xd8;
        iVar16 = DAT_80015f08 + 0x16;
        if (DAT_80015f08 <= uVar9) {
          return;
        }
        do {
          iVar10 = uVar9 * 800 + 0xe6;
          copy_short((void *)(iVar5 + iVar10 * 2),(void *)(iVar3 + iVar10 * 2),iVar16);
          uVar9 = uVar9 + 1;
        } while (uVar9 < uVar15);
        return;
      }
    } while (iVar3 == 0);
  } while( true );
}

//----------------------------------------------------------------------------------------------------------------------
//Some handling based on item id (1 - 24)

void FUN_8002177c(uint param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  undefined *puVar3;
  undefined *puVar4;
  
  iVar1 = DAT_8002180c;  //0x801FA24C
  uVar2 = 0;
  do {
    if (*(byte *)(DAT_8002180c + uVar2) == param_1) {
      *(undefined *)(DAT_8002180c + uVar2) = 0;
      param_3 = uVar2;
      break;
    }
    uVar2 = uVar2 + 1 & 0xff;
  } while (uVar2 < 0x18);

  if (param_3 < 0x17) {
    puVar3 = (undefined *)(iVar1 + param_3);
    puVar4 = puVar3;
    if ((0x17 - param_3 & 1) != 0) {
      puVar4 = puVar3 + 1;
      *puVar3 = *puVar4;
    }
    uVar2 = (int)(0x17 - param_3) >> 1;
    while ((uVar2 & 0xff) != 0) {
      uVar2 = (uVar2 & 0xff) - 1;
      *puVar4 = puVar4[1];
      puVar4[1] = puVar4[2];
      puVar4 = puVar4 + 2;
    }
  }
  if (param_1 != 0) {
    *(undefined *)(iVar1 + 0x17) = 0;
  }
  return;
}


//----------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------

