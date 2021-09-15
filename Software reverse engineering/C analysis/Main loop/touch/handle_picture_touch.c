
void handle_picture_touch(void)

{
  ushort uVar1;
  undefined *puVar2;
  int *piVar3;
  undefined *puVar4;
  ushort uVar5;
  ushort uVar6;
  ushort uVar7;
  ushort uVar8;
  short sVar9;
  int iVar10;
  ushort *puVar11;
  ushort *puVar12;
  uint uVar13;
  
  puVar4 = PTR_DAT_80022fb4;
  piVar3 = Global_Frame_Buffer_Pointer;
  puVar2 = PTR_BITMAP_CONFIRM_DELETE_MENU_80022fac;

LAB_80022df0:
  while( true ) 
  {
    do
    {
      //Check for touch
      iVar10 = FUN_800230a0();
    } while (iVar10 == 0);

    if (iVar10 == 1)
    {
      //1 means return
      memset(DAT_80022fbc,0,DAT_80022fb8);  //0x805B7228, 0, 0x0005DC00
      *puVar4 = 1;
      puVar4[4] = 1;
      puVar4[5] = 0;
      return;
    }

    //2 means delete
    if (iVar10 != 2)
      break;

    uVar5 = convert_color(DAT_80022fc0);
    uVar6 = convert_color(DAT_80022fc4);
    uVar7 = convert_color(DAT_80022fc8);
    set_screen_to_global_pointer();
    uVar13 = 0xc0;

    //Show confirm delete bitmap
    do
    {
      iVar10 = 0xb4;
      puVar11 = (ushort *)(*piVar3 + uVar13 * 0x640 + 0x226);
      puVar12 = (ushort *)(puVar2 + uVar13 * 0x2d0 + -0x21c00);

      do
      {
        uVar1 = *puVar12;
        uVar8 = uVar7;

        if (((uVar1 != 0) && (uVar8 = uVar5, uVar1 != 0xf800)) && (uVar8 = uVar1, uVar1 == 0x7e0))
        {
          uVar8 = uVar6;
        }

        iVar10 = iVar10 + -1;
        *puVar11 = uVar8;
        puVar11 = puVar11 + 1;
        puVar12 = puVar12 + 2;
      } while (iVar10 != 0);

      uVar13 = uVar13 + 1 & 0xfffeffff;
    } while (uVar13 < 0x121);

    //Wait for touch on delete question
    do
    {
      iVar10 = check_delete_confirmation();
    } while (iVar10 == 2);

    //Check if no
    if (iVar10 == 0)
      goto LAB_80022f64;

    //Delete the file
    load_selected_system_file();
    setup_filename_list();
    iVar10 = DAT_80022fcc;
    remove_item_from_lists((uint)*(ushort *)(DAT_80022fcc + (uint)*(ushort *)(puVar4 + 2) * 2 + 0x1e));
    f_unlink((char *)((uint)*(ushort *)(puVar4 + 2) * 0xf + iVar10 + 0x7ee));
    save_selected_system_file();
    save_selected_list_file();
    load_selected_system_file();
    setup_filename_list();
    puVar4[4] = 1;
    puVar4[5] = 0;

    iVar10 = display_picture();

    if (iVar10 != 0)
    {
      //Return if selected picture does not exist
      //Only the case after last picture has been deleted
      return;
    }
  }


  //Breaks out to here when iVar10 !=2

  if (iVar10 == 3)
  {
    //Previous image
    if (*(short *)(puVar4 + 2) == 0)  //Check on already on first image
      goto LAB_80022df0;

    sVar9 = *(short *)(puVar4 + 2) + -1;
  }
  else
  {
    if (iVar10 != 4)
    {
      if (iVar10 == 5)
      {
        //refresh picture toggle the delete return menu???
        display_picture();
      }

      //Keep scanning touch
      goto LAB_80022df0;
    }

    //4 means next image
    if ((int)(*(byte *)(DAT_80022fcc + 0xc) - 1) <= (int)(uint)*(ushort *)(puVar4 + 2))  //check if not already on last image
      goto LAB_80022df0;

    sVar9 = *(ushort *)(puVar4 + 2) + 1;
  }

  //Select the new image
  *(short *)(puVar4 + 2) = sVar9;

LAB_80022f64:
  puVar4[4] = 1;
  puVar4[5] = 0;
  display_picture();
  goto LAB_80022df0;
}


