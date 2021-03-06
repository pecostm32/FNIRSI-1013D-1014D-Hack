
void FUN_8002b9bc(void)

{
  uint uVar1;
  ushort xend_uVar2;
  ushort yend_uVar3;
  ushort xstart_uVar4;
  ushort ystart_uVar5;
  ushort uVar6;
  short sVar7;
  short sVar8;
  short sVar9;
  uint uVar10;
  short *psVar11;
  short *psVar12;
  int iVar13;
  short *psVar14;
  int *piVar15;
  char *pcVar16;
  int iVar17;
  short *psVar18;
  ushort *puVar19;
  short *psVar20;
  undefined2 *puVar21;
  uint uVar22;
  uint uVar23;
  uint uVar24;
  uint uVar25;
  uint yend_uVar26;
  int *in_r12;
  uint local_58;
  
  local_58 = 0;
  xend_uVar2 = *(ushort *)(DAT_8002be10 + 2);   //0x8035A97E  Data set before system file data
  yend_uVar3 = *(ushort *)(DAT_8002be10 + 4);
  yend_uVar26 = (uint)yend_uVar3;
  xstart_uVar4 = *(ushort *)(DAT_8002be10 + 6);
  ystart_uVar5 = *(ushort *)(DAT_8002be10 + 8);

  load_selected_system_file();  //Need to get the number of available items in this function

  setup_filename_list();  //This is not needed when file names are made on the fly

  set_frame_to_global_pointer();

  set_display_fg_color(0);

  uVar6 = (ushort)DAT_8002be14;  //0x000001DF

  display_fill_rect(0,0,uVar6 + 0xfa,uVar6);  //clear the list part of the screen (0,0,729,479)

  set_display_fg_color(DAT_8002be18);   //0x00202020

  display_draw_vert_line(uVar6 + 0xfa,0,uVar6); //Seperator for the right menu (729,0,479)

  psVar14 = DAT_8002be28;   //0x801C4078
  iVar13 = DAT_8002be24;    //0x801AF0B8
  psVar12 = DAT_8002be20;   //0x801C38A8
  psVar11 = DAT_8002be1c;   //0x801AF088
  uVar23 = 0;


  //Does the system file contain thumbnail data????? 2000 bytes of data is not much for the number of items that could be present
  //or is it the list file?? Most likely

  do
  {
    uVar24 = 0;                //xposition
    sVar9 = (short)uVar23;     //yposition

    do  //loop through this untill uVar24 > 700 (some xpos??)
    {
      //page number is used here
      uVar1 = local_58 + (uint)*(byte *)(DAT_8002be10 + 10) * 0x10 + -0x10 & 0xffff;   //0x8035A97E  ??? system file data is loaded to this address + 0x1E (2000 bytes)

      if (*(byte *)(DAT_8002be10 + 0xc) <= uVar1)
        break;

      if (yend_uVar26 != 0)  //fixed value set in setup_view_screen function
      {
        in_r12 = Global_Frame_Buffer_Pointer;
      }

      uVar25 = uVar24 + 4 & 0xfffeffff;
      local_58 = local_58 + 1 & 0xfffeffff;  //point to next entry in system file
      uVar22 = 0;


      //Clear part of the screen, as if they never heard of memset and do not understand what display_fill_rect does!!!!
      //So not needed
      if (yend_uVar26 != 0)
      {
        do
        {
          if (xend_uVar2 != 0)
          {
            iVar17 = *in_r12 + ((uint)xstart_uVar4 + (uVar22 + ystart_uVar5 + uVar23) * 800 + uVar24) * 2;
            puVar21 = (undefined2 *)(iVar17 + 0x63e);
            uVar10 = (uint)(xend_uVar2 >> 1);

            if ((xend_uVar2 & 1) != 0)
            {
              puVar21 = (undefined2 *)(iVar17 + 0x640);
              *puVar21 = 0;
            }

            //Do two pixels per loop
            while (uVar10 != 0)
            {
              puVar21[1] = 0;
              puVar21 = puVar21 + 2;
              *puVar21 = 0;
              uVar10 = uVar10 - 1;
            }
          }

          uVar22 = uVar22 + 1 & 0xfffeffff;
        } while (uVar22 < yend_uVar26);
      }

      //uVar1 is item number and times two gives an index into the system file number list file
      //This function loads the selected files thumbnail data from the thumbnail list
      //Seems there is no fixed relation between the indexes in the two files
      get_thumbnail_data(*(undefined2 *)(DAT_8002be10 + uVar1 * 2 + 0x1e));

      psVar18 = DAT_8002be38;   //0x801AEF2A
      psVar20 = DAT_8002be34;   //0x801C374A

      //Check if xy mode
      if (*(char *)(DAT_8002be30 + 7) == '\0')
      {
        //Not then offset the sample in y direction
        iVar17 = 0x57;
        *DAT_8002be38 = *DAT_8002be34 + sVar9;
        sVar7 = psVar20[1];

        do
        {
          iVar17 = iVar17 + -1;
          sVar8 = psVar20[2];
          psVar18[1] = sVar7 + sVar9;
          sVar7 = psVar20[3];
          psVar18 = psVar18 + 2;
          *psVar18 = sVar8 + sVar9;
          psVar20 = psVar20 + 2;
        } while (iVar17 != 0);

        *psVar11 = *psVar12 + sVar9;
      }
      else
      {
        memcpy(DAT_8002be38,DAT_8002be34,0x160);  //352 bytes means only 176 byte samples
      }

      psVar20 = DAT_8002be3c;
      iVar17 = 0x57;
      psVar18 = (short *)(iVar13 + 2);
      *psVar18 = *DAT_8002be3c + sVar9;
      uVar6 = psVar20[1];

      do
      {
        iVar17 = iVar17 + -1;
        in_r12 = (int *)(uVar6 + uVar23);
        sVar7 = psVar20[2];
        psVar18[1] = (short)in_r12;
        uVar6 = psVar20[3];
        psVar18 = psVar18 + 2;
        *psVar18 = sVar7 + sVar9;
        psVar20 = psVar20 + 2;
      } while (iVar17 != 0);

      psVar11[200] = *psVar14 + sVar9;
      pcVar16 = DAT_8002be44;

      if (*(char *)(DAT_8002be30 + 7) == '\0')  //0x80361378 + 7  is xy display mode.  Loaded per thumbnail into actual variable????
      {
        if (*(ushort *)(DAT_8002be44 + 0x1c) < 4)
        {
          *(undefined2 *)(DAT_8002be44 + 0x1c) = 4;
        }

        if (*pcVar16 != '\0') //channel 1
        {
          //Some drawing function???????
          display_thumbnail_trace(*(ushort *)(pcVar16 + 0x1a) + uVar25 & 0xfffeffff, 0, *(short *)(pcVar16 + 0x1c) + -4, DAT_8002be38, DAT_8002be54);  //0x801AEF2A  0x00FFFF00
        }

        if (pcVar16[0xc] != '\0')  //channel 2
        {
          display_thumbnail_trace(*(ushort *)(pcVar16 + 0x1a) + uVar25 & 0xfffeffff, 0, *(short *)(pcVar16 + 0x1c) + -4, DAT_8002be5c, DAT_8002be58);   //0x801AF0BA  0x0000FFFF
        }
      }
      else
      {
        set_display_fg_color(DAT_8002be40);
        pcVar16 = DAT_8002be44;

        //At the time of taking the snapshot it is possible there is no valid data yet. So for this a check is done on sample count
        if (*(ushort *)(DAT_8002be44 + 0x1c) < 5)
        {
          *(undefined2 *)(DAT_8002be44 + 0x1c) = 5;
        }

        uVar22 = 0;

        if (0 < (int)(*(ushort *)(pcVar16 + 0x1c) - 5))
        {
          do
          {
            puVar19 = (ushort *)(DAT_8002be38 + uVar22);         //0x801AEF2A + sample
            in_r12 = (int *)(*puVar19 + uVar25);                 //uVar25 = uVar24 + 4  is x start position. Channel1 data + x start pos

            //xstart, ystart, xend, yend
            display_draw_line((int)in_r12 + 0x1b, (uint)puVar19[200], uVar25 + puVar19[1] + 0x1b, (uint)puVar19[201]);

            uVar22 = uVar22 + 1 & 0xfffeffff;
          } while ((int)uVar22 < (int)(*(ushort *)(DAT_8002be44 + 0x1c) - 5));
        }
      }

      set_display_fg_color(DAT_8002be18);

      display_draw_rect((xstart_uVar4 + (short)uVar24) - 1,(ystart_uVar5 + sVar9) - 1,xstart_uVar4 + xend_uVar2 + (short)uVar24,ystart_uVar5 + yend_uVar3 + sVar9);

      uVar24 = (uint)xend_uVar2 + (uint)xstart_uVar4 + uVar24 & 0xfffcffff;
    } while (uVar24 < 700);

    if ((*(byte *)(DAT_8002be10 + 0xc) <= uVar1) || (uVar23 = yend_uVar26 + ystart_uVar5 + uVar23 & 0xfffcffff, DAT_8002be48 <= uVar23))
    {
      copy_rect_to_screen(0,0,(ushort)DAT_8002be14 + 0xfa,(ushort)DAT_8002be14);

      iVar17 = DAT_8002be50;  //0x000005B4
      iVar13 = Screen_Frame_Buffer_2;
      piVar15 = Global_Frame_Buffer_Pointer;
      uVar23 = 0;

      do
      {
        memcpy((void *)(iVar13 + uVar23 * 0x640),(void *)(*piVar15 + uVar23 * 0x640),iVar17);

        uVar23 = uVar23 + 1 & 0xfffeffff;
      } while (uVar23 < 0x1e0);

      return;
    }

  } while( true );
}


