
void setup_view_mode_screen(void)

{
  uint uVar1;
  char cVar2;
  bool bVar3;
  char *pcVar4;
  int *piVar5;
  int count;
  undefined *puVar6;
  undefined *puVar7;
  ushort uVar8;
  ushort uVar9;
  ushort uVar10;
  ushort uVar11;
  ushort uVar12;
  int iVar13;
  uint uVar14;
  uint uVar15;
  int iVar16;
  ushort *puVar17;
  ushort *puVar18;
  undefined auStack592 [556];
  
  iVar16 = DAT_8002c570;                              //0x8019D5A0  base of scope settings
  bVar3 = false;
  *(undefined *)(DAT_8002c570 + 0x3a) = 0;            //0x8019D5DA  Scope run mode, set to active. Should not be done to return to same state as before view, but needs full wave save
  *(undefined *)(iVar16 + 0x43) = 0;                  //0x8019D5E3  wave view mode, set to normal mode. Is to signal which buttons are shown. Not needed!!! on entry here already 0

  save_system_setup(DAT_8002c574);                    //0x80356EE6  Memory location to save all the important scope variables??  scope_save_setup()

  pcVar4 = DAT_8002c578;                              //0x8035A97E
  *DAT_8002c578 = '\0';                               //store byte     This is mode. 0 no select active, 1 select active
  pcVar4[10] = '\x01';                                //same           Active page indicator. Decremented on page down and incremented on page up

  *(undefined2 *)(pcVar4 + 2) = 0xb4;                 //store short    Coordinates of item to draw???  xend      0x8035A980   Will use defines in my code
  *(undefined2 *)(pcVar4 + 4) = 0x75;                 //same                                           yend      0x8035A982
  *(undefined2 *)(pcVar4 + 6) = 2;                    //same                                           xstart    0x8035A984
  *(undefined2 *)(pcVar4 + 8) = 2;                    //same                                           ystart    0x8035A988

  memclear((uint)(pcVar4 + 0xd),0x10);                //clear 16 bytes from 0x8035A98B   These are item selected flags

  display_file_select_menu();                         //scope_setup_right_file_menu()

  load_selected_list_file();                          //scope_load_list_file()

  display_thumbnails();                               //display the thumbnails   0x8035A98A is set after this function. Is last item indicator. Is index into system file

  piVar5 = Global_Frame_Buffer_Pointer;


  //A big while loop to scan for touch
LAB_8002bed0:
  do
  {
    iVar13 = handle_view_mode_touch();   //touch handler for this part????? returns 1 - 6 for button touch, 7 - 22 for items

    iVar16 = DAT_8002c570;   //0x8019D5A0
  } while (iVar13 == 0);

  if (iVar13 == 1)   //return button
  {
    *(undefined *)(DAT_8002c570 + 0x43) = 0;   //wave view mode to normal

    restore_system_setup(DAT_8002c574);  //restore_system_setup  0x80356EE6

    *(undefined *)(iVar16 + 0x21) = 0;        //trigger mode to auto

    set_fpga_channel1_voltperdiv();
    set_fpga_channel2_voltperdiv();
    set_fpga_trigger_timebase();
    set_fpga_trigger_channel();
    set_fpga_channel_trigger_channel();
    set_fpga_trigger_edge();
    set_fpga_trigger_level();
    set_fpga_trigger_mode();
    set_fpga_channel1_offset();
    set_fpga_channel2_offset();

    *(undefined2 *)PTR_DAT_8002c5b4 = 0;   //0x80192eaa  disp_xpos = 0 so trace starts from beginning

//So best to also do restart of the scope here instead of after return from this function.

    setup_main_screen();                   //Rebuild the scope screen. also done after return from this function.

    *Global_Frame_Buffer_Pointer = Start_Of_Screen_Mem;
    return;
  }

  if (iVar13 == 2)   //select all
  {
    bVar3 = !bVar3;

    display_highlight_select_button(0);

    *pcVar4 = '\0';

    if (!bVar3)
    {
      display_highlight_select_all_button(0);
      iVar13 = DAT_8002c584;
      iVar16 = Screen_Frame_Buffer_2;
      uVar15 = 0;

      do
      {
        memcpy((void *)(*piVar5 + uVar15 * 0x640),(void *)(iVar16 + uVar15 * 0x640),iVar13);
        uVar15 = uVar15 + 1 & 0xfffeffff;
      } while (uVar15 < 0x1e0);

      memclear((uint)(pcVar4 + 0xd),0x10);

      goto LAB_8002bed0;
    }

    *pcVar4 = '\x01';

    display_highlight_select_all_button(1);

    memset(pcVar4 + 0xd,0x10,1);  //Different type of memset, since count becomes for value

    display_selected_sign();
  }
  else
  {
    if (iVar13 == 3)  //select
    {
      bVar3 = false;

      if (*pcVar4 == '\0')
      {
        *pcVar4 = '\x01';
      }
      else
      {
        *pcVar4 = '\0';
      }

      display_highlight_select_all_button(0);

      if (*pcVar4 == '\0')
      {
        display_highlight_select_button(0);

        count = DAT_8002c584;
        iVar16 = Screen_Frame_Buffer_2;
        uVar15 = 0;

        do
        {
          memcpy((void *)(*piVar5 + uVar15 * 0x640),(void *)(iVar16 + uVar15 * 0x640),count);
          uVar15 = uVar15 + 1 & 0xfffeffff;
        } while (uVar15 < 0x1e0);

        memclear((uint)(pcVar4 + 0xd),0x10);
      }
      else
      {
        display_highlight_select_button(1);
      }

      goto LAB_8002c1ac;
    }

    if (iVar13 != 4)
    {
      if (iVar13 == 5)  //page up
      {
        if (1 < (byte)pcVar4[10])
        {
          if (*pcVar4 != '\0')
          {
            *pcVar4 = '\0';

            display_highlight_select_button(0);
            display_highlight_select_all_button(0);

            iVar13 = DAT_8002c584;
            iVar16 = Screen_Frame_Buffer_2;
            uVar15 = 0;

            do
            {
              memcpy((void *)(*piVar5 + uVar15 * 0x640),(void *)(iVar16 + uVar15 * 0x640),iVar13);
              uVar15 = uVar15 + 1 & 0xfffeffff;
            } while (uVar15 < 0x1e0);

            memclear((uint)(pcVar4 + 0xd),0x10);
          }

          pcVar4[10] = pcVar4[10] + -1;

          goto LAB_8002c510;
        }
      }
      else
      {
        if (iVar13 != 6)
          goto LAB_8002c1ac;

        if ((byte)pcVar4[10] < (byte)pcVar4[0xb])  //page down
        {
          if (*pcVar4 != '\0')
          {
            *pcVar4 = '\0';

            display_highlight_select_button(0);
            display_highlight_select_all_button(0);

            iVar13 = DAT_8002c584;
            iVar16 = Screen_Frame_Buffer_2;
            uVar15 = 0;

            do
            {
              memcpy((void *)(*piVar5 + uVar15 * 0x640),(void *)(iVar16 + uVar15 * 0x640),iVar13);
              uVar15 = uVar15 + 1 & 0xfffeffff;
            } while (uVar15 < 0x1e0);

            memclear((uint)(pcVar4 + 0xd),0x10);
          }

          pcVar4[10] = pcVar4[10] + '\x01';

          display_thumbnails();
        }
      }

      goto LAB_8002bed0;
    }


    //delete
    if (*pcVar4 != '\0')
    {
      uVar10 = convert_color(DAT_8002c588);
      uVar11 = convert_color(DAT_8002c58c);
      uVar8 = convert_color(DAT_8002c590);
      set_screen_to_global_pointer();
      puVar6 = PTR_BITMAP_CONFIRM_DELETE_MENU_8002c594;
      uVar15 = 0xc0;

      do
      {
        iVar16 = 0xb4;
        puVar17 = (ushort *)(*piVar5 + uVar15 * 0x640 + 0x226);
        puVar18 = (ushort *)(puVar6 + uVar15 * 0x2d0 + -0x21c00);

        do
        {
          uVar12 = *puVar18;
          uVar9 = uVar8;

          if (((uVar12 != 0) && (uVar9 = uVar10, uVar12 != 0xf800)) && (uVar9 = uVar12, uVar12 == 0x7e0))
          {
            uVar9 = uVar11;
          }

          iVar16 = iVar16 + -1;
          *puVar17 = uVar9;
          puVar17 = puVar17 + 1;
          puVar18 = puVar18 + 2;
        } while (iVar16 != 0);

        uVar15 = uVar15 + 1 & 0xfffeffff;
      } while (uVar15 < 0x121);

      do
      {
        iVar16 = check_delete_confirmation();
      } while (iVar16 == 2);

      if (iVar16 == 0)
      {
        display_selected_sign();  //Does this rebuild the complete screen????
        goto LAB_8002c1ac;
      }

      //Do delete of the selected files
      display_highlight_select_button(0);  //Something with the file select menu bitmap???
      display_highlight_select_all_button(0);  //Something with the file select menu bitmap???

      uVar14 = 0;

      load_selected_system_file();

      setup_filename_list();

      uVar15 = 0;

      do
      {
        //Walk through the selected list
        if (pcVar4[uVar15 + 0xd] != '\0')
        {
          uVar1 = (uint)(byte)pcVar4[10] * 0x10 + -0x10 + uVar15 & 0xffff;  //((Page number * 16) - 16) + index

          iVar16 = uVar1 - uVar14;

          uVar14 = uVar14 + 1 & 0xff;  //Count of selected items

          //Some setup to detect how many items are available???
          if ((byte)pcVar4[0xc] <= uVar1)
            break;

          //Delete the file in the system list???
          remove_item_from_list(*(undefined2 *)(pcVar4 + iVar16 * 2 + 0x1e));

          //Delete the file on the disk
          f_unlink(pcVar4 + uVar1 * 0xf + 0x7ee);  //Input is a pointer to the filename set in a list
        }

        uVar15 = uVar15 + 1 & 0xfffeffff;

      } while (uVar15 < 0x10);

      //Clear the selected list
      memclear((uint)(pcVar4 + 0xd),0x10);


      save_selected_system_file();
      save_selected_list_file();

      load_selected_system_file();

      setup_filename_list();
      display_thumbnails();

      *pcVar4 = '\0';

      goto LAB_8002bed0;
    }
  }

//Actual item touched
LAB_8002c1ac:
  puVar7 = PTR_DAT_8002c59c;    //0x80192ee2
  puVar6 = PTR_DAT_8002c598;

  if (iVar13 - 7U < 0x10)  //Check if valid touch, which is not needed since it can't be a higher value!!!!
  {
    if (*pcVar4 == '\0')  //Check the mode. On 0 open the touched item
    {
      uVar14 = ((uint)(byte)pcVar4[10] * 0x10 + iVar13) - 0x17;
      uVar15 = uVar14 & 0xffff;
      *(short *)(PTR_DAT_8002c598 + 2) = (short)(uVar14 * 0x10000 >> 0x10);

      if (*puVar7 == '\0')  //0x80192ee2 view item mode 0 is picture, 1 is waveform
      {
        iVar16 = 1;
        *puVar6 = 1;
        puVar6[4] = 1;
        puVar6[5] = 0;

        iVar16 = display_picture();

        //File exists if 0 is returned, so display the bitmap again?? and wait for touch
        if (iVar16 == 0)
        {
          uVar10 = convert_color(0);
          uVar11 = convert_color(DAT_8002c590);
          set_screen_to_global_pointer();
          puVar6 = PTR_BITMAP_RETURN_DELETE_MENU_8002c5ac;
          uVar15 = 0x1a4;
          do
          {
            iVar16 = 800;
            puVar17 = (ushort *)(*piVar5 + uVar15 * 0x640);
            puVar18 = (ushort *)(puVar6 + uVar15 * 0xc80 + -0x148200);

            do
            {
              uVar8 = *puVar18;
              uVar12 = uVar11;
              if ((uVar8 != 0) && (uVar12 = uVar8, uVar8 == 0xf800))
              {
                uVar12 = uVar10;
              }

              iVar16 = iVar16 + -1;
              *puVar17 = uVar12;
              puVar17 = puVar17 + 1;
              puVar18 = puVar18 + 2;
            } while (iVar16 != 0);

            uVar15 = uVar15 + 1 & 0xfffeffff;
          } while (uVar15 < 0x1e0);

          set_frame_to_global_pointer();

          handle_picture_touch();  //in this function. Allows for selection of prev or next image or delete this image or return.
        }
      }
      else
      {
        //Item valid??? or needed for last item???
        if ((byte)pcVar4[0xc] <= uVar15)
        {
          if (uVar15 == 0)
            goto LAB_8002c4f0;

          uVar15 = uVar15 - 1;
          *(short *)(puVar6 + 2) = (short)uVar15;
        }

        //Open selected file
        iVar16 = f_open(auStack592,pcVar4 + (uVar15 & 0xffff) * 0xf + 0x7ee,1);

        //File not available
        if (iVar16 == 4)
        {
          load_selected_system_file();
          setup_filename_list();
          remove_item_from_list(*(undefined2 *)(pcVar4 + (uint)*(ushort *)(puVar6 + 2) * 2 + 0x1e));

          //Delete the file
          f_unlink(pcVar4 + (uint)*(ushort *)(puVar6 + 2) * 0xf + 0x7ee);

          save_selected_system_file();
          save_selected_list_file();

          load_selected_system_file();
          setup_filename_list();
          f_close(auStack592);
        }
        else
        {
          f_lseek(auStack592,0);

          f_read(auStack592,DAT_8002c5a4,DAT_8002c5a0,NULL);

          f_close(auStack592);

          iVar16 = DAT_8002c570;  //0x8019D5A0

          *(undefined *)(DAT_8002c570 + 0x43) = 1;  //Set view mode to waveform

          restore_system_setup(DAT_8002c5a4);   //Load setup data from this file

          *(undefined *)(iVar16 + 0x18) = 1;
          *(undefined *)(iVar16 + 0x17) = 1;
          *(undefined *)(iVar16 + 0x43) = 1;
          *(undefined *)(iVar16 + 0x3a) = 1;
          display_run_stop_text(0);
          set_frame_to_global_pointer();
          set_display_fg_color(0);
          display_fill_rect(2,0x2f,(ushort)DAT_8002c5a8 + 0xfb,(ushort)DAT_8002c5a8);
          setup_main_screen();
          display_trace_data();
          cVar2 = *(char *)(iVar16 + 0x43);

          while (cVar2 != '\0')   //Stay in the waveform view as long as it is set to waveform view.
          {
            //timebase setting
            if (*(byte *)(iVar16 + 10) < 9)
            {  //Long time base 50S - 100mS
              FUN_8002b68c();          //long time base trace drawing
            }
            else
            {  //Short time base 50mS - 10nS
              display_trace_data();
            }

            touch_handler();

            cVar2 = *(char *)(iVar16 + 0x43);
          }
        }
      }

LAB_8002c4f0:
      set_display_fg_color(DAT_8002c5b0);
      uVar10 = (ushort)DAT_8002c5a8;
      display_fill_rect(uVar10 + 0xfa,0,uVar10 + 0x140,uVar10);
      display_file_select_menu();

LAB_8002c510:
      display_thumbnails();
    }
    else
    {
      //On mode 1 update the selected signs
      display_selected_sign();
    }
  }

  goto LAB_8002bed0;
}


