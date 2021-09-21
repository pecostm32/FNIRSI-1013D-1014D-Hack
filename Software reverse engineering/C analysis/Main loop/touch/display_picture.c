
int display_picture(void)

{
  ushort uVar1;
  undefined *puVar2;
  int *piVar3;
  ushort uVar4;
  ushort uVar5;
  ushort uVar6;
  int iVar7;
  ushort *puVar8;
  ushort *puVar9;
  int iVar10;
  uint uVar11;
  code *in_lr;
  undefined auStack576 [556];
  code *UNRECOVERED_JUMPTABLE_00;
  
  iVar10 = DAT_80022dac;
  puVar2 = PTR_DAT_80022da8;                     //0x80192ee4 some mode or what ever byte. Indicates the displaying of the bottom file menu bar
  uVar4 = *(ushort *)(PTR_DAT_80022da8 + 2);

  if (*(byte *)(DAT_80022dac + 0xc) <= uVar4)
  {
    if (uVar4 == 0)
    {
      return 1;
    }

    uVar4 = uVar4 - 1;
    *(ushort *)(PTR_DAT_80022da8 + 2) = uVar4;
  }

  UNRECOVERED_JUMPTABLE_00 = in_lr;

  iVar7 = f_open(auStack576,(char *)((uint)uVar4 * 0xf + iVar10 + 0x7ee),1);

  if (iVar7 != 4)  //Check should be on OK!!!
  {
    f_lseek(auStack576,0x46);  //Skip the bitmap header

    f_read(auStack576,DAT_80022db4,DAT_80022db0,NULL);  //Read the bitmap data  0x8035344E, 0x00003A98 = 150000 bytes. This is system setting data plus trace data

    f_close(auStack576);

    iVar10 = DAT_80022db8;
    *(undefined *)(DAT_80022db8 + 0x43) = 0;

    restore_system_setup(DAT_80022db4);   //To get the trace data in the buffers

    *(undefined *)(iVar10 + 0x18) = 1;  //Trigger a redraw????
    *(undefined *)(iVar10 + 0x17) = 1;

    //Have the DEBE point to other memory to display from
    set_screen_frame_buffer(DAT_80022dbc);    //0x805B7228


    delay_2(0xf);    //Need 15mS for the screen to adapt

    set_frame_to_global_pointer();  //Select empty frame buffer to draw in

    setup_main_screen();     //Draw the normal screen in it

    set_frame_to_global_pointer();    //Set the pointer agian???

    view_mode_display_trace();   //draw trace and other data (fft)

    if (*puVar2 != '\0')  //set to one when a picture is selected for viewing
    {
      uVar4 = convert_color(0);
      uVar5 = convert_color(DAT_80022dc0);
      set_screen_to_global_pointer();               //original screen buffer
      piVar3 = Global_Frame_Buffer_Pointer;
      puVar2 = PTR_BITMAP_RETURN_DELETE_MENU_80022dc4;
      uVar11 = 0x1a4;

      do
      {
        iVar10 = 800;
        puVar8 = (ushort *)(*piVar3 + uVar11 * 0x640);
        puVar9 = (ushort *)(puVar2 + uVar11 * 0xc80 + -0x148200);

        do
        {
          uVar1 = *puVar9;
          uVar6 = uVar5;

          if ((uVar1 != 0) && (uVar6 = uVar1, uVar1 == 0xf800))
          {
            uVar6 = uVar4;
          }

          iVar10 = iVar10 + -1;
          *puVar8 = uVar6;
          puVar8 = puVar8 + 1;
          puVar9 = puVar9 + 2;
        } while (iVar10 != 0);

        uVar11 = uVar11 + 1 & 0xfffeffff;
      } while (uVar11 < 0x1e0);

      set_frame_to_global_pointer();    //back to frame pointer
    }

    copy_short(DAT_80022dbc,Start_Of_Screen_Mem,number_of_pixels);  //0x805B7228   copy what is in the original screen buffer to the new frame buffer

    FUN_8001d4ec(Start_Of_Screen_Mem);   //set DEBE back to original frame buffer

    return(0);
  }


  //When file not available remove it from the two lists
  load_selected_system_file();  //Already in memory!!!!
  setup_filename_list();        //No need for this

  remove_item_from_lists((uint)*(ushort *)(iVar10 + (uint)*(ushort *)(puVar2 + 2) * 2 + 0x1e));

  //Delete the file on disk not needed when file does not exist!!!!!!!!
  f_unlink((char *)((uint)*(ushort *)(puVar2 + 2) * 0xf + iVar10 + 0x7ee));

  save_selected_system_file();
  save_selected_list_file();

  load_selected_system_file();  //Not needed since you just wrote it and the data is in memory idiots.

  setup_filename_list();        //Waste of memory. Print file name only on demand!!!

  f_close(auStack576);

  return(1);
}

