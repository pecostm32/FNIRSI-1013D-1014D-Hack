//------------------------------------------------------------------------------------------------------------------------------------------


void handle_main_menu_touch(void)

{
  char cVar1;
  int *piVar2;
  undefined4 uVar3;
  undefined uVar4;
  ushort uVar5;
  int iVar6;
  undefined *puVar7;
  ushort uVar8;
  undefined *puVar9;
  ushort *puVar10;
  undefined *in_r2;
  ushort *puVar11;
  undefined *puVar12;
  undefined *puVar13;
  uint uVar14;
  uint uVar15;
  char *pcVar16;
  undefined *puVar17;
  uint uVar18;
  int iVar19;
  int iVar20;
  undefined *in_r12;
  uint uVar21;
  uint uVar22;
  bool bVar23;
  bool bVar24;
  bool bVar25;
  code **ppcVar26;
  undefined8 uVar27;
  char *in_stack_ffffffd8;
  undefined *in_stack_ffffffdc;
  undefined uVar28;
  undefined4 in_stack_ffffffe0;
  code *UNRECOVERED_JUMPTABLE;
  
  pcVar16 = DAT_80029140;                       //0x8036B792  Touch panel data
  puVar17 = DAT_8002913c;                       //0x80361378  State variable for highlight routine

  ppcVar26 = (code **)&stack0xffffffd8;

  uVar4 = 0;
  *DAT_8002913c = 0;
  iVar19 = 0;
  iVar20 = 0;
  bVar24 = false;


  if (pcVar16[6] == '\0')                      //Set in calling function setup_main_menu (0x8036b798)
  {
    return;
  }

  tp_i2c_read_status();

  puVar9 = (undefined *)(uint)*(ushort *)(pcVar16 + 2);      //Xtouch
  puVar7 = (undefined *)(uint)*(ushort *)PTR_DAT_80029144;   //0x80192ef8  set to 2 in display_slide_down_main_menu

  //xtouch between 2 and 149 (main menu x range)
  if ((puVar7 < puVar9) && (in_r2 = PTR_DAT_80029144, puVar9 < puVar7 + 0x95))
  {
    puVar12 = (undefined *)(uint)*(ushort *)(pcVar16 + 4);   //Ytouch

    in_r2 = (undefined *)(uint)*(ushort *)(PTR_DAT_80029144 + 2);  //set to 46 in display_slide_down_main_menu
    bVar25 = in_r2 <= puVar12;
    bVar23 = puVar12 == in_r2;

    if (bVar25 && !bVar23)
    {
      in_r2 = in_r2 + 0x3b;
    }

    if (bVar25 && !bVar23)
    {
      bVar25 = puVar12 <= in_r2;
      bVar23 = in_r2 == puVar12;
    }

    //Touch not in first item so go check next
    if (!bVar25 || bVar23)
      goto LAB_800288e8;

    cVar1 = *pcVar16;  //Have touch

    while (cVar1 != '\0')
    {
      *puVar17 = 1;
      display_highlight_main_menu_item();
      tp_i2c_read_status();
      cVar1 = *pcVar16;
    }

    if (pcVar16[7] == '\0')  //Some other state variable
    {
      pcVar16[7] = '\x01';  //Signal system settings menu is open
      save_screen_under_settings_menu();         //Save the screen under the new menu
      display_slide_left_system_settings_menu(); // ???
      display_system_settings_menu();            // ???
      goto LAB_80028a48;
    }
  }
  else
  {
LAB_800288e8:
    bVar25 = puVar7 <= puVar9;
    bVar23 = puVar9 == puVar7;
    if (bVar25 && !bVar23) {
      in_r2 = puVar7 + 0x95;
    }
    if (bVar25 && !bVar23) {
      bVar25 = puVar9 <= in_r2;
      bVar23 = in_r2 == puVar9;
    }
    if (bVar25 && !bVar23) {
      puVar12 = (undefined *)(uint)*(ushort *)(PTR_DAT_80029144 + 2);
      in_r2 = (undefined *)(uint)*(ushort *)(pcVar16 + 4);
      in_r12 = puVar12 + 0x3b;
      bVar25 = in_r12 <= in_r2;
      bVar23 = in_r2 == in_r12;
      if (bVar25 && !bVar23) {
        puVar12 = puVar12 + 0x76;
      }
      if (bVar25 && !bVar23) {
        bVar25 = in_r2 <= puVar12;
        bVar23 = puVar12 == in_r2;
      }
      if (bVar25 && !bVar23) {
        cVar1 = *pcVar16;
        while (cVar1 != '\0') {
          *puVar17 = 2;
          display_highlight_main_menu_item();
          tp_i2c_read_status();
          cVar1 = *pcVar16;
        }
        *PTR_DAT_80029148 = 0;   //Picture view
        FUN_8002be60();          //Handle the picture view
        FUN_8000a750();          //Restart the scope function
        setup_main_screen();
        goto LAB_80028a48;
      }
    }

    bVar25 = puVar7 <= puVar9;
    bVar23 = puVar9 == puVar7;
    if (bVar25 && !bVar23) {
      in_r2 = puVar7 + 0x95;
    }
    if (bVar25 && !bVar23) {
      bVar25 = puVar9 <= in_r2;
      bVar23 = in_r2 == puVar9;
    }
    if (bVar25 && !bVar23) {
      puVar12 = (undefined *)(uint)*(ushort *)(PTR_DAT_80029144 + 2);
      in_r2 = (undefined *)(uint)*(ushort *)(pcVar16 + 4);
      in_r12 = puVar12 + 0x76;
      bVar25 = in_r12 <= in_r2;
      bVar23 = in_r2 == in_r12;
      if (bVar25 && !bVar23) {
        puVar12 = puVar12 + 0xb1;
      }
      if (bVar25 && !bVar23) {
        bVar25 = in_r2 <= puVar12;
        bVar23 = puVar12 == in_r2;
      }
      if (bVar25 && !bVar23) {
        cVar1 = *pcVar16;
        while (cVar1 != '\0') {
          *puVar17 = 3;
          display_highlight_main_menu_item();
          tp_i2c_read_status();
          cVar1 = *pcVar16;
        }
        *PTR_DAT_80029148 = 1;   //Waveform view
        FUN_8002be60();          //Handle the waveform view
        FUN_8000a750();          //Restart the scope function
        setup_main_screen();
        goto LAB_80028a48;
      }
    }
    bVar25 = puVar7 <= puVar9;
    bVar23 = puVar9 == puVar7;
    if (bVar25 && !bVar23) {
      puVar7 = puVar7 + 0x95;
    }
    if (bVar25 && !bVar23) {
      bVar25 = puVar9 <= puVar7;
      bVar23 = puVar7 == puVar9;
    }
    if (bVar25 && !bVar23) {
      puVar9 = (undefined *)(uint)*(ushort *)(PTR_DAT_80029144 + 2);
      puVar7 = (undefined *)(uint)*(ushort *)(pcVar16 + 4);
      in_r2 = puVar9 + 0xb1;
      bVar25 = in_r2 <= puVar7;
      bVar23 = puVar7 == in_r2;
      if (bVar25 && !bVar23) {
        puVar9 = puVar9 + 0xec;
      }
      if (bVar25 && !bVar23) {
        bVar25 = puVar7 <= puVar9;
        bVar23 = puVar9 == puVar7;
      }
      if (bVar25 && !bVar23) {
        cVar1 = *pcVar16;
        while (cVar1 != '\0') {
          *puVar17 = 4;
          display_highlight_main_menu_item();
          tp_i2c_read_status();
          cVar1 = *pcVar16;
        }
        FUN_8000a750();                    //Restart the scope function
        FUN_80029eb0();                    //Save the screen
        enter_usb_connect();
        set_frame_to_global_pointer();    //Set frame as destinatioon
        FUN_80029f00();                   //Copy saved screen to frame
        copy_frame_to_screen();           //Copy it back to screen
        FUN_8000a750();                   //Restart the scope function
        setup_main_screen();              //Show initial screen
        goto LAB_80028a48;
      }
    }
    if (*pcVar16 != '\0') {
      iVar19 = 1;
    }

LAB_80028a48:
    if (pcVar16[7] == '\0')  //State is 0
    {
      if (*pcVar16 == '\0' || iVar19 == 0)  //no touch or ??
      {
        return;
      }

      goto code_r0x8000a750;
    }
  }

//Handling of system settings????
  uVar28 = (undefined)in_stack_ffffffe0;
  puVar9 = (undefined *)(uint)*(ushort *)(pcVar16 + 2);           //xpos of touch
  puVar7 = (undefined *)(uint)*(ushort *)(PTR_DAT_80029144 + 4);  //xpos of menu

  if ((puVar7 < puVar9) && (in_r2 = puVar7 + 0xf4, puVar9 < in_r2))
  {
    in_r2 = (undefined *)(uint)*(ushort *)(pcVar16 + 4);            //ypos of touch
    puVar12 = (undefined *)(uint)*(ushort *)(PTR_DAT_80029144 + 6); //ypos of menu
    bVar25 = puVar12 <= in_r2;
    bVar23 = in_r2 == puVar12;

    if (bVar25 && !bVar23)
    {
      puVar12 = puVar12 + 0x3b;       //59
    }

    if (bVar25 && !bVar23)
    {
      bVar25 = in_r2 <= puVar12;
      bVar23 = puVar12 == in_r2;
    }

    if (!bVar25 || bVar23)
      goto LAB_80028b08;

    cVar1 = *pcVar16;  //Have touch

    //First menu item touched
    while (uVar28 = (undefined)in_stack_ffffffe0, cVar1 != '\0')
    {
      puVar17[1] = 1;   //0x80361379
      display_system_settings_menu();
      tp_i2c_read_status();
      cVar1 = *pcVar16;
    }

    if (pcVar16[9] == '\x01')     //Check on grid brightness slider opened
    {
      pcVar16[9] = '\0';
      FUN_800114f4(0);            //display grid brightness in buffer
      FUN_80009e9c();             //copy something to the screen from the second buffer. Previously saved screen data
    }

    if (pcVar16[10] == '\x01')    //Check on calibration text opened
    {
      pcVar16[10] = '\0';
      FUN_80002b3c();             //Another restore to screen (calibration data ???)
    }

    if (pcVar16[8] == '\0')
    {
      pcVar16[8] = '\x01';
      FUN_8001c690();             //Copy something from screen
      FUN_8001178c();             //Open en display slider
      FUN_80011764();             //Display slider
      FUN_800117a8(1);            //Display the screen brightness
    }
  }
  else
  {
LAB_80028b08:
    bVar25 = puVar7 <= puVar9;
    bVar23 = puVar9 == puVar7;
    if (bVar25 && !bVar23) {
      in_r2 = puVar7 + 0xf4;
    }
    if (bVar25 && !bVar23) {
      bVar25 = puVar9 <= in_r2;
      bVar23 = in_r2 == puVar9;
    }
    if (bVar25 && !bVar23) {
      in_r2 = (undefined *)(uint)*(ushort *)(PTR_DAT_80029144 + 6);
      puVar12 = (undefined *)(uint)*(ushort *)(pcVar16 + 4);
      in_r12 = in_r2 + 0x3b;
      bVar25 = in_r12 <= puVar12;
      bVar23 = puVar12 == in_r12;
      if (bVar25 && !bVar23) {
        in_r2 = in_r2 + 0x76;
      }
      if (bVar25 && !bVar23) {
        bVar25 = puVar12 <= in_r2;
        bVar23 = in_r2 == puVar12;
      }
      if (bVar25 && !bVar23) {
        cVar1 = *pcVar16;
        while (cVar1 != '\0') {
          puVar17[1] = 2;
          display_system_settings_menu();
          tp_i2c_read_status();
          uVar28 = (undefined)in_stack_ffffffe0;
          cVar1 = *pcVar16;
        }
        if (pcVar16[8] == '\x01')         //Screen brightness opened
        {
          pcVar16[8] = '\0';
          FUN_800117a8(0);
          FUN_8001c6c0();                 //Restore screen
        }
        if (pcVar16[10] == '\x01')        //Calibration text opened
        {
          pcVar16[10] = '\0';
          FUN_80002b3c();                //Restore screen
        }
        if (pcVar16[9] == '\0')           //Grid birghtness
        {
          pcVar16[9] = '\x01';
          FUN_80009e5c();                //Save screen
          FUN_800114d0();                //Open and display slider
          FUN_800114a0();                //Display slider
          FUN_800114f4(1);
        }
        goto LAB_80028dcc;
      }
    }
    bVar25 = puVar7 <= puVar9;
    bVar23 = puVar9 == puVar7;
    if (bVar25 && !bVar23) {
      in_r2 = puVar7 + 0xf4;
    }
    if (bVar25 && !bVar23) {
      bVar25 = puVar9 <= in_r2;
      bVar23 = in_r2 == puVar9;
    }
    if (!bVar25 || bVar23) {
LAB_80028c60:
      bVar25 = puVar7 <= puVar9;
      bVar23 = puVar9 == puVar7;
      if (bVar25 && !bVar23) {
        in_r2 = puVar7 + 0xf4;
      }
      if (bVar25 && !bVar23) {
        bVar25 = puVar9 <= in_r2;
        bVar23 = in_r2 == puVar9;
      }
      if (bVar25 && !bVar23) {
        puVar13 = (undefined *)(uint)*(ushort *)(PTR_DAT_80029144 + 6);
        puVar12 = (undefined *)(uint)*(ushort *)(pcVar16 + 4);
        in_r12 = puVar13 + 0xb1;
        bVar25 = in_r12 <= puVar12;
        bVar23 = puVar12 == in_r12;
        if (bVar25 && !bVar23) {
          puVar13 = puVar13 + 0xec;
        }
        if (bVar25 && !bVar23) {
          bVar25 = puVar12 <= puVar13;
          bVar23 = puVar13 == puVar12;
        }
        if (bVar25 && !bVar23) {
          cVar1 = *pcVar16;
          while (cVar1 != '\0') {            //Baseline calibration
            puVar17[1] = 4;
            display_system_settings_menu();
            tp_i2c_read_status();
            uVar28 = (undefined)in_stack_ffffffe0;
            cVar1 = *pcVar16;
          }
          if (pcVar16[8] == '\x01') {        //Screen brightness opened
            pcVar16[8] = '\0';
            FUN_800117a8(0);
            FUN_8001c6c0();
          }
          if (pcVar16[9] == '\x01') {        //Grid brightness opened
            pcVar16[9] = '\0';
            FUN_800114f4(0);
            FUN_80009e9c();
          }
          if (pcVar16[10] == '\0') {        //Open baseline calibration
            pcVar16[10] = '\x01';
            puVar17[8] = 0;
            FUN_80002afc();                //Save screen under the calib start text
            FUN_80011154();                //Open the calib start text menu
            FUN_80010f08();                //Show the calibration start text
          }
          goto LAB_80028dcc;
        }
      }
      bVar25 = puVar7 <= puVar9;
      bVar23 = puVar9 == puVar7;
      if (bVar25 && !bVar23) {
        puVar7 = puVar7 + 0xf4;
      }
      if (bVar25 && !bVar23) {
        bVar25 = puVar9 <= puVar7;
        bVar23 = puVar7 == puVar9;
      }
      if (bVar25 && !bVar23) {
        if ((*(ushort *)(PTR_DAT_80029144 + 6) + 0xec < (uint)*(ushort *)(pcVar16 + 4)) &&
           ((uint)*(ushort *)(pcVar16 + 4) < *(ushort *)(PTR_DAT_80029144 + 6) + 0x127)) {
          cVar1 = *pcVar16;
          while (uVar28 = (undefined)in_stack_ffffffe0, cVar1 != '\0') {
            tp_i2c_read_status();
            cVar1 = *pcVar16;
          }
          if (puVar17[7] == '\0') {
            puVar17[7] = 1;                     //x-y mode display toggle
          }
          else {
            puVar17[7] = 0;
          }
          puVar17[1] = 0;
          if (pcVar16[8] == '\x01') {
            pcVar16[8] = '\0';
            FUN_800117a8(0);
            FUN_8001c6c0();
          }
          if (pcVar16[9] == '\x01') {
            pcVar16[9] = '\0';
            FUN_800114f4(0);
            FUN_80009e9c();
          }
          cVar1 = pcVar16[10];
          goto joined_r0x80028db4;
        }
      }
      if (*pcVar16 != '\0') {
        iVar20 = 1;
      }
    }
    else {
      in_r2 = (undefined *)(uint)*(ushort *)(PTR_DAT_80029144 + 6);
      puVar12 = (undefined *)(uint)*(ushort *)(pcVar16 + 4);
      in_r12 = in_r2 + 0x76;
      bVar25 = in_r12 <= puVar12;
      bVar23 = puVar12 == in_r12;
      if (bVar25 && !bVar23) {
        in_r2 = in_r2 + 0xb1;
      }
      if (bVar25 && !bVar23) {
        bVar25 = puVar12 <= in_r2;
        bVar23 = in_r2 == puVar12;
      }
      if (!bVar25 || bVar23) goto LAB_80028c60;
      cVar1 = *pcVar16;
      while (uVar28 = (undefined)in_stack_ffffffe0, cVar1 != '\0') {
        tp_i2c_read_status();
        cVar1 = *pcVar16;
      }
      if (puVar17[4] == '\0') {
        puVar17[4] = 1;                     //always 50% trigger toggle
      }
      else {
        puVar17[4] = 0;
      }
      puVar17[1] = 0;
      if (pcVar16[8] == '\x01') {
        pcVar16[8] = '\0';
        FUN_800117a8(0);
        FUN_8001c6c0();
      }
      if (pcVar16[9] == '\x01') {
        pcVar16[9] = '\0';
        FUN_800114f4(0);
        FUN_80009e9c();
      }
      cVar1 = pcVar16[10];
joined_r0x80028db4:
      if (cVar1 == '\x01') {
        pcVar16[10] = '\0';
        FUN_80002b3c();
      }
      display_system_settings_menu();
    }
  }
LAB_80028dcc:
  uVar3 = DAT_80029150;
  uVar15 = DAT_8002914c;


  if (pcVar16[8] == '\x01') {                                //screen brightness
    uVar22 = (uint)*(ushort *)(pcVar16 + 2);
    uVar18 = (uint)*(ushort *)(PTR_DAT_80029144 + 4);
    uVar14 = uVar18 + 0x108;
    bVar25 = uVar14 <= uVar22;
    bVar23 = uVar22 == uVar14;
    if (bVar25 && !bVar23) {
      uVar14 = uVar18 + 0x200;
    }
    if (bVar25 && !bVar23) {
      uVar14 = uVar14 + 0x2b;
    }
    if (bVar25 && !bVar23) {
      bVar25 = uVar22 <= uVar14;
      bVar23 = uVar14 == uVar22;
    }
    if (bVar25 && !bVar23) {
      uVar21 = (uint)*(ushort *)(pcVar16 + 4);
      uVar14 = (uint)*(ushort *)(PTR_DAT_80029144 + 6);
      bVar25 = uVar14 <= uVar21;
      bVar23 = uVar21 == uVar14;
      if (bVar25 && !bVar23) {
        uVar14 = uVar14 + 0x3b;
      }
      if (bVar25 && !bVar23) {
        bVar25 = uVar21 <= uVar14;
        bVar23 = uVar14 == uVar21;
      }
      if (bVar25 && !bVar23) {
        cVar1 = *pcVar16;
        while (cVar1 != '\0') {
          uVar22 = (uint)*(ushort *)(pcVar16 + 2);
          uVar18 = uVar15;
          if ((0x19c < uVar22) && (uVar18 = uVar22, 0x2c0 < uVar22)) {
            uVar18 = 0x2c0;
          }
          uVar27 = FUN_8003979c(uVar18 - 0x19d);
          FUN_800393ec((int)uVar27,(int)((ulonglong)uVar27 >> 0x20),DAT_80029154,uVar3);
          uVar4 = FUN_8003972c();
          puVar17[2] = uVar4;
          set_translated_brightness();
          FUN_800117a8(1);
          FUN_80011764();
          tp_i2c_read_status();
          cVar1 = *pcVar16;
        }
        goto LAB_80028f04;
      }
    }
    if ((uVar18 + 0xf4 < uVar22) && (uVar22 < uVar18 + 0x23f)) {
      uVar18 = (uint)*(ushort *)(pcVar16 + 4);
      uVar15 = (uint)*(ushort *)(PTR_DAT_80029144 + 6);
      bVar25 = uVar15 <= uVar18;
      bVar23 = uVar18 == uVar15;
      if (bVar25 && !bVar23) {
        uVar15 = uVar15 + 0x3b;
      }
      if (bVar25 && !bVar23) {
        bVar25 = uVar18 <= uVar15;
        bVar23 = uVar15 == uVar18;
      }
      if (bVar25 && !bVar23) goto LAB_80028f04;
    }
    cVar1 = *pcVar16;
joined_r0x80028f00:
    if (cVar1 != '\0') {
      bVar24 = true;
    }
  }
  else {
    if (pcVar16[9] != '\x01')                    //not grid brightness
    {
      if (pcVar16[10] == '\x01') {               //baseline calibration yes
        puVar7 = (undefined *)(uint)*(ushort *)(pcVar16 + 2);
        uVar15 = (uint)*(ushort *)(PTR_DAT_80029144 + 4);
        puVar9 = (undefined *)(uVar15 + 0x16e);
        bVar23 = puVar9 <= puVar7;
        bVar24 = puVar7 == puVar9;
        if (bVar23 && !bVar24) {
          in_r12 = (undefined *)(uVar15 + 0x1b0);
        }
        if (bVar23 && !bVar24) {
          bVar23 = puVar7 <= in_r12;
          bVar24 = in_r12 == puVar7;
        }
        if (bVar23 && !bVar24) {
          uVar18 = (uint)*(ushort *)(PTR_DAT_80029144 + 6);
          uVar22 = (uint)*(ushort *)(pcVar16 + 4);
          bVar23 = uVar18 + 0xb7 <= uVar22;
          bVar24 = uVar22 == uVar18 + 0xb7;
          if (bVar23 && !bVar24) {
            uVar18 = uVar18 + 0xe3;
          }
          if (bVar23 && !bVar24) {
            bVar23 = uVar22 <= uVar18;
            bVar24 = uVar18 == uVar22;
          }
          if (bVar23 && !bVar24) {
            if (puVar17[8] != '\0') {
                    // WARNING: Could not recover jumptable at 0x80029068. Too many branches
                    // WARNING: Treating indirect jump as call
              (*UNRECOVERED_JUMPTABLE)();
              return;
            }
            cVar1 = *pcVar16;
            while (cVar1 != '\0') {
              puVar17[9] = 1;
              FUN_80010f08();     //Show the calibration start text with button highlighted
              tp_i2c_read_status();
              cVar1 = *pcVar16;
            }

            puVar17[9] = 0;
            FUN_80002b3c();    //Restore the screen

            display_calibrating_text();
            iVar19 = FUN_80027ef8();        //Do the calibration??????  (do_baseline_calibration)
            puVar17[8] = (char)iVar19;

            if (iVar19 != 0) {
              signal_sys_ok();
            }

            FUN_80002b3c();    //Restore the screen again

            //Display the calib success text
            uVar5 = convert_color(DAT_80011484);
            iVar19 = DAT_80011498;
            piVar2 = Global_Frame_Buffer_Pointer;
            puVar7 = PTR_DAT_80011490;
            puVar17 = PTR_TEXT_BITMAP_CALIB_SUCCESS_8001148c;
            uVar15 = 0;
            *(undefined *)(DAT_80011488 + 8) = 1;
            do {
              iVar20 = 0x6e;
              puVar10 = (ushort *)
                        (*piVar2 + ((uint)*(ushort *)(puVar7 + 4) +
                                   (*(ushort *)(puVar7 + 6) + uVar15) * 800) * 2 + iVar19);
              puVar11 = (ushort *)(puVar17 + uVar15 * 0xdc);
              do {
                uVar8 = *puVar11;
                if (*puVar11 == 0) {
                  uVar8 = uVar5;
                }
                iVar20 = iVar20 + -1;
                *puVar10 = uVar8;
                puVar10 = puVar10 + 1;
                puVar11 = puVar11 + 1;
              } while (iVar20 != 0);
              uVar15 = uVar15 + 1 & 0xfffeffff;
            } while (uVar15 < 0x3c);
            set_display_fg_color(DAT_8001149c);
            display_draw_rect(*(short *)(puVar7 + 4) + 0xf4,*(short *)(puVar7 + 6) + 0xaf,
                              *(short *)(puVar7 + 4) + 0x162,*(short *)(puVar7 + 6) + 0xea);
            iVar20 = Start_Of_Screen_Mem;
            iVar19 = Screen_Frame_Buffer;
            uVar5 = *(ushort *)(puVar7 + 4);
            uVar18 = *(ushort *)(puVar7 + 6) + 0xaf & 0xfffeffff;
            uVar22 = *(ushort *)(puVar7 + 6) + 0xeb & 0xfffeffff;
            uVar15 = uVar5 + 0xf4 & 0xfffeffff;
            if (uVar22 <= uVar18) {
              return;
            }
            do {
              iVar6 = uVar15 + uVar18 * 800;
              copy_short((void *)(iVar20 + iVar6 * 2),(void *)(iVar19 + iVar6 * 2),
                         ((uVar5 + 0x162 & 0xfffeffff) - uVar15) + 1);
              uVar18 = uVar18 + 1;
            } while (uVar18 < uVar22);
            return;
          }
        }
        bVar23 = (undefined *)(uVar15 + 0xf4) <= puVar7;
        bVar24 = puVar7 == (undefined *)(uVar15 + 0xf4);
        if (bVar23 && !bVar24) {
          bVar23 = puVar7 <= puVar9;
          bVar24 = puVar9 == puVar7;
        }
        if (bVar23 && !bVar24) {
          uVar15 = (uint)*(ushort *)(PTR_DAT_80029144 + 6);
          uVar18 = (uint)*(ushort *)(pcVar16 + 4);
          bVar23 = uVar15 + 0xb1 <= uVar18;
          bVar24 = uVar18 == uVar15 + 0xb1;
          if (bVar23 && !bVar24) {
            uVar15 = uVar15 + 0xed;
          }
          if (bVar23 && !bVar24) {
            bVar23 = uVar18 <= uVar15;
            bVar24 = uVar15 == uVar18;
          }
          if (bVar23 && !bVar24) {
            ppcVar26 = (code **)&stack0xffffffec;
            pcVar16 = in_stack_ffffffd8;
            puVar17 = in_stack_ffffffdc;
            uVar4 = uVar28;
          }
          if (bVar23 && !bVar24) {
            iVar19 = (int)*ppcVar26;
            iVar20 = ((int *)ppcVar26)[1];
            ppcVar26 = (code **)((int *)ppcVar26 + 4);
          }
                    // WARNING: Could not recover jumptable at 0x800290ec. Too many branches
                    // WARNING: Treating indirect jump as call
          if (bVar23 && !bVar24) {
            (**ppcVar26)();
            return;
          }
        }
        if (*pcVar16 == '\0') {
                    // WARNING: Could not recover jumptable at 0x80029100. Too many branches
                    // WARNING: Treating indirect jump as call
          (**(code **)((int)ppcVar26 + 0x24))();
          return;
        }
        puVar17[8] = uVar4;
        if (iVar19 == 0 || iVar20 == 0) {
                    // WARNING: Could not recover jumptable at 0x80029118. Too many branches
                    // WARNING: Treating indirect jump as call
          (**(code **)((undefined *)((int)ppcVar26 + 0x14) + 0x10))();
          return;
        }
      }
      else {
        bVar25 = *pcVar16 == '\0';
        bVar24 = iVar19 == 0;
        bVar23 = iVar20 == 0;
        if ((bVar25 || bVar24) || bVar23) {
          ppcVar26 = (code **)&stack0xffffffec;
        }
        if ((bVar25 || bVar24) || bVar23) {
          ppcVar26 = (code **)((int)ppcVar26 + 0x10);
        }
                    // WARNING: Could not recover jumptable at 0x80028e0c. Too many branches
                    // WARNING: Treating indirect jump as call
        if ((bVar25 || bVar24) || bVar23) {
          (**ppcVar26)();
          return;
        }
      }
      goto code_r0x8000a750;
    }

    //Grid brightness true
    uVar22 = (uint)*(ushort *)(pcVar16 + 2);
    uVar18 = (uint)*(ushort *)(PTR_DAT_80029144 + 4);
    uVar14 = uVar18 + 0x108;
    bVar25 = uVar14 <= uVar22;
    bVar23 = uVar22 == uVar14;
    if (bVar25 && !bVar23) {
      uVar14 = uVar18 + 0x200;
    }
    if (bVar25 && !bVar23) {
      uVar14 = uVar14 + 0x2b;
    }
    if (bVar25 && !bVar23) {
      bVar25 = uVar22 <= uVar14;
      bVar23 = uVar14 == uVar22;
    }
    if (bVar25 && !bVar23) {
      uVar14 = (uint)*(ushort *)(PTR_DAT_80029144 + 6);
      uVar21 = (uint)*(ushort *)(pcVar16 + 4);
      bVar25 = uVar14 + 0x3b <= uVar21;
      bVar23 = uVar21 == uVar14 + 0x3b;
      if (bVar25 && !bVar23) {
        uVar14 = uVar14 + 0x76;
      }
      if (bVar25 && !bVar23) {
        bVar25 = uVar21 <= uVar14;
        bVar23 = uVar14 == uVar21;
      }
      if (bVar25 && !bVar23) {
        cVar1 = *pcVar16;
        while (cVar1 != '\0') {
          uVar22 = (uint)*(ushort *)(pcVar16 + 2);
          uVar18 = uVar15;
          if ((0x19c < uVar22) && (uVar18 = uVar22, 0x2c0 < uVar22)) {
            uVar18 = 0x2c0;
          }
          uVar27 = FUN_8003979c(uVar18 - 0x19d);
          FUN_800393ec((int)uVar27,(int)((ulonglong)uVar27 >> 0x20),DAT_80029154,uVar3);
          uVar4 = FUN_8003972c();
          puVar17[3] = uVar4;
          FUN_800114f4(1);
          FUN_800114a0();
          tp_i2c_read_status();
          cVar1 = *pcVar16;
        }
        goto LAB_80028f04;
      }
    }
    if ((uVar22 <= uVar18 + 0xf4) || (uVar18 + 0x23f <= uVar22)) {
LAB_80029004:
      cVar1 = *pcVar16;
      goto joined_r0x80028f00;
    }
    uVar15 = (uint)*(ushort *)(PTR_DAT_80029144 + 6);
    uVar18 = (uint)*(ushort *)(pcVar16 + 4);
    bVar25 = uVar15 + 0x3b <= uVar18;
    bVar23 = uVar18 == uVar15 + 0x3b;
    if (bVar25 && !bVar23) {
      uVar15 = uVar15 + 0x76;
    }
    if (bVar25 && !bVar23) {
      bVar25 = uVar18 <= uVar15;
      bVar23 = uVar15 == uVar18;
    }
    if (!bVar25 || bVar23) goto LAB_80029004;
  }
LAB_80028f04:
  bVar25 = iVar19 == 0;
  bVar23 = iVar20 == 0;
  bVar24 = !bVar24;
  puVar17[8] = 0;
  if ((bVar25 || bVar23) || bVar24) {
    ppcVar26 = (code **)&stack0xffffffec;
  }
  if ((bVar25 || bVar23) || bVar24) {
    ppcVar26 = (code **)((int)ppcVar26 + 0x10);
  }
                    // WARNING: Could not recover jumptable at 0x80028f1c. Too many branches
                    // WARNING: Treating indirect jump as call
  if ((bVar25 || bVar23) || bVar24) {
    (**ppcVar26)();
    return;
  }


code_r0x8000a750:
  puVar17 = DAT_8000a7ec;
  ppcVar26[9] = ppcVar26[9];
  ppcVar26[8] = ppcVar26[2];
  ppcVar26[7] = ppcVar26[1];
  ppcVar26[6] = *ppcVar26;
  if (DAT_8000a7ec[10] == '\x01') {
    DAT_8000a7ec[10] = 0;
    FUN_80002b3c();
  }
  if (puVar17[8] == '\x01') {
    puVar17[8] = 0;
    FUN_800117a8(0);
    FUN_8001c6c0();
  }
  if (puVar17[9] == '\x01') {
    puVar17[9] = 0;
    FUN_800114f4(0);
    FUN_80009e9c();
  }
  if (puVar17[7] == '\x01') {
    FUN_800268ec();
  }
  FUN_80016b8c();
  puVar17[8] = 0;
  puVar17[9] = 0;
  puVar17[10] = 0;
  puVar17[6] = 0;
  puVar17[0xb] = 0;
  *puVar17 = 0;
  puVar17[7] = 0;
  puVar17[0xc] = 0;
  puVar7 = DAT_8000a7f0;
  *(undefined2 *)(puVar17 + 2) = 0;
  *(undefined2 *)(puVar17 + 4) = 0;
  *puVar7 = 0;
  puVar7[1] = 0;
  return;
}

//------------------------------------------------------------------------------------------------------------------------------------------

void display_slide_left_system_settings_menu(void)

{
  uint uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  ushort *puVar8;
  ushort uVar9;
  uint uVar10;
  ushort *puVar11;
  
  uVar2 = convert_color(DAT_8001174c);
  uVar3 = convert_color(0);
  uVar4 = convert_color(0xffffff);
  set_screen_to_global_pointer();
  uVar1 = DAT_80011750;
  uVar5 = 0xf4;
  do
  {
    uVar7 = 0;

    do
    {
      if (uVar5 < 0xf4)
      {
        uVar6 = 0xf4 - uVar5 & 0xffff;

        puVar8 = (ushort *)(PTR_BITMAP_SYSTEM_SETTINGS_MENU_8001175c + uVar5 * 2 + uVar7 * 0x1e8);
        puVar11 = (ushort *)(*Global_Frame_Buffer_Pointer + ((*(ushort *)(PTR_DAT_80011754 + 6) + uVar7) * 800 + (uint)*(ushort *)(PTR_DAT_80011754 + 4)) * 2);

        do
        {
          uVar10 = (uint)*puVar8;
          uVar9 = uVar2;

          if (((uVar10 != 0) && (uVar9 = uVar3, uVar10 != 0xf800)) && (uVar9 = *puVar8, uVar10 == uVar1))
          {
            uVar9 = uVar4;
          }

          uVar6 = uVar6 - 1 & 0xffff;

          *puVar11 = uVar9;

          puVar8 = puVar8 + 1;
          puVar11 = puVar11 + 1;
        } while (uVar6 != 0);
      }

      uVar7 = uVar7 + 1 & 0xfffeffff;
    } while (uVar7 < 0x126);

    uVar5 = (uVar5 - (uVar5 * DAT_80011760 >> 0x13)) - 1 & 0xffff;
  } while (uVar5 != 0);

  *Global_Frame_Buffer_Pointer = Screen_Frame_Buffer;
  return;
}

//------------------------------------------------------------------------------------------------------------------------------------------

void display_system_settings_menu(void)

{
  undefined *puVar1;
  undefined *puVar2;
  int *piVar3;
  int iVar4;
  ushort uVar5;
  ushort uVar6;
  ushort uVar7;
  uint uVar8;
  int iVar9;
  ushort *puVar10;
  uint uVar11;
  int iVar12;
  ushort uVar13;
  uint uVar14;
  ushort *puVar15;
  
  uVar5 = convert_color(DAT_80010ce4);
  uVar6 = convert_color(0);
  uVar7 = convert_color(0xffffff);
  uVar8 = DAT_80010cf4;
  piVar3 = Global_Frame_Buffer_Pointer;
  puVar2 = PTR_DAT_80010cec;
  puVar1 = PTR_BITMAP_SYSTEM_SETTINGS_MENU_80010ce8;
  uVar11 = 0;
  do {
    iVar12 = 0xf4;
    puVar10 = (ushort *)(puVar1 + uVar11 * 0x1e8);
    puVar15 = (ushort *)
              (*piVar3 +
              ((uint)*(ushort *)(puVar2 + 4) + (*(ushort *)(puVar2 + 6) + uVar11) * 800) * 2);
    do {
      uVar14 = (uint)*puVar10;
      uVar13 = uVar5;
      if (((uVar14 != 0) && (uVar13 = uVar6, uVar14 != 0xf800)) &&
         (uVar13 = *puVar10, uVar14 == uVar8)) {
        uVar13 = uVar7;
      }
      iVar12 = iVar12 + -1;
      *puVar15 = uVar13;
      puVar10 = puVar10 + 1;
      puVar15 = puVar15 + 1;
    } while (iVar12 != 0);
    uVar11 = uVar11 + 1 & 0xfffeffff;
  } while (uVar11 < DAT_80010cf8);
  set_display_fg_color(DAT_80010cfc);
  display_draw_rect(*(ushort *)(puVar2 + 4),*(ushort *)(puVar2 + 6),*(ushort *)(puVar2 + 4) + 0xf3,
                    *(ushort *)(puVar2 + 6) + 0x125);
  FUN_800117a8(0);
  FUN_800114f4(0);
  FUN_80010d00();
  FUN_80011c3c();
  FUN_800118f4();

  //Copy rect to screen
  iVar4 = Start_Of_Screen_Mem;
  iVar12 = Screen_Frame_Buffer;
  uVar11 = (uint)*(ushort *)(puVar2 + 6);
  uVar8 = (uint)*(ushort *)(puVar2 + 4);
  uVar14 = uVar11 + 0x126 & 0xfffeffff;
  if (uVar14 <= uVar11) {
    return;
  }
  do {
    iVar9 = uVar8 + uVar11 * 800;
    copy_short((void *)(iVar4 + iVar9 * 2),(void *)(iVar12 + iVar9 * 2),
               ((uVar8 + 0xf3 & 0xfffeffff) - uVar8) + 1);
    uVar11 = uVar11 + 1;
  } while (uVar11 < uVar14);
  return;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//display_sys_menu_disp_brightness

void FUN_800117a8(int param_1)

{
  byte bVar1;
  undefined *puVar2;
  uint uVar3;
  char local_18;
  char local_17;
  undefined local_16;
  undefined local_15;
  
  bVar1 = *(byte *)(DAT_800118e0 + 2);
  uVar3 = (uint)bVar1;
  set_display_fg_color(DAT_800118e4);
  puVar2 = PTR_DAT_800118e8;
  display_fill_rect(*(short *)(PTR_DAT_800118e8 + 4) + 0xb6,*(short *)(PTR_DAT_800118e8 + 6) + 0x15,
                    *(short *)(PTR_DAT_800118e8 + 4) + 0xd6,*(short *)(PTR_DAT_800118e8 + 6) + 0x24)
  ;
  if (uVar3 < 100) {
    if (uVar3 < 10) {
      local_18 = bVar1 + (char)(uint)((ulonglong)uVar3 * (ulonglong)DAT_800118ec >> 0x23) * -10 +
                 '0';
      local_17 = '\0';
    }
    else {
      local_18 = (char)((uint)((short)(ushort)bVar1 * 0xcd) >> 0xb) + '0';
      local_17 = bVar1 + (char)(uint)((ulonglong)uVar3 * (ulonglong)DAT_800118ec >> 0x23) * -10 +
                 '0';
      local_16 = 0;
    }
  }
  else {
    local_18 = '1';
    local_17 = '0';
    local_16 = 0x30;
    local_15 = 0;
  }
  set_display_fg_color(0);
  select_font(PTR_FONT_1_800118f0);
  set_font_paint_mode(2);
  display_text(&local_18,*(short *)(puVar2 + 4) + 0xbb,*(short *)(puVar2 + 6) + 0x16);
  if (param_1 == 1) {
    copy_rect_to_screen(*(short *)(puVar2 + 4) + 0xb6,*(short *)(puVar2 + 6) + 0x15,
                        *(short *)(puVar2 + 4) + 0xd6,*(short *)(puVar2 + 6) + 0x25);
    return;
  }
  return;
}

//------------------------------------------------------------------------------------------------------------------------------------------

void FUN_80010d00(void)

{
  ushort uVar1;
  undefined *puVar2;
  uint color;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  color = DAT_80010efc;              //0x00444444
  puVar2 = PTR_DAT_80010ef8;

  if (*(char *)(DAT_80010f00 + 4) == '\0')
  {
    set_display_fg_color(DAT_80010f04);   //0x00008800 Dark green

    display_fill_rounded_rect(*(short *)(puVar2 + 4) + 0xb0,*(short *)(puVar2 + 6) + 0x89,*(short *)(puVar2 + 4) + 0xdc,*(short *)(puVar2 + 6) + 0x9c,2);

    set_display_fg_color(color);
    display_draw_rounded_rect(*(short *)(puVar2 + 4) + 0xb0,*(short *)(puVar2 + 6) + 0x89,*(short *)(puVar2 + 4) + 0xdc,*(short *)(puVar2 + 6) + 0x9c,2);


    set_display_fg_color(color);
    display_fill_rounded_rect
              (*(short *)(puVar2 + 4) + 0xb3,*(short *)(puVar2 + 6) + 0x8c,
               *(short *)(puVar2 + 4) + 0xc6,*(short *)(puVar2 + 6) + 0x99,0);


    set_display_fg_color(0);
    display_draw_vert_line
              (*(short *)(puVar2 + 4) + 0xb8,*(short *)(puVar2 + 6) + 0x8e,
               *(short *)(puVar2 + 6) + 0x97);
    display_draw_vert_line
              (*(short *)(puVar2 + 4) + 0xbb,*(short *)(puVar2 + 6) + 0x8e,
               *(short *)(puVar2 + 6) + 0x97);
    display_draw_vert_line
              (*(short *)(puVar2 + 4) + 0xbe,*(short *)(puVar2 + 6) + 0x8e,
               *(short *)(puVar2 + 6) + 0x97);
    uVar1 = *(ushort *)(puVar2 + 6);
    iVar3 = *(ushort *)(puVar2 + 4) + 0xc1;
  }
  else {
    set_display_fg_color(0xff00);       //Light green
    display_fill_rounded_rect(*(short *)(puVar2 + 4) + 0xb0,*(short *)(puVar2 + 6) + 0x89,*(short *)(puVar2 + 4) + 0xdc,*(short *)(puVar2 + 6) + 0x9c,2);

    set_display_fg_color(0x8800);
    display_draw_rounded_rect(*(short *)(puVar2 + 4) + 0xb0,*(short *)(puVar2 + 6) + 0x89,*(short *)(puVar2 + 4) + 0xdc,*(short *)(puVar2 + 6) + 0x9c,2);

    set_display_fg_color(color);
    display_fill_rounded_rect
              (*(short *)(puVar2 + 4) + 0xc6,*(short *)(puVar2 + 6) + 0x8c,
               *(short *)(puVar2 + 4) + 0xd9,*(short *)(puVar2 + 6) + 0x99,0);
    set_display_fg_color(0);
    display_draw_vert_line
              (*(short *)(puVar2 + 4) + 0xcb,*(short *)(puVar2 + 6) + 0x8e,
               *(short *)(puVar2 + 6) + 0x97);
    display_draw_vert_line
              (*(short *)(puVar2 + 4) + 0xce,*(short *)(puVar2 + 6) + 0x8e,
               *(short *)(puVar2 + 6) + 0x97);
    display_draw_vert_line
              (*(short *)(puVar2 + 4) + 0xd1,*(short *)(puVar2 + 6) + 0x8e,
               *(short *)(puVar2 + 6) + 0x97);
    uVar1 = *(ushort *)(puVar2 + 6);
    iVar3 = *(ushort *)(puVar2 + 4) + 0xd4;
  }

  //Draw vertical line
  save_context();
  iVar6 = *(int *)(*DAT_80018f68 + 0x4c);
  iVar4 = *(int *)(*DAT_80018f68 + 0x50);
  iVar5 = FUN_8002ac10(&stack0xffffffe8);
  while (iVar5 != 0) {
    FUN_8001cc4c(iVar3 + iVar6,uVar1 + 0x8e + iVar4,uVar1 + 0x97 + iVar4);
    iVar5 = FUN_8002ab40();
  }
  restore_context();
  return;
}


//------------------------------------------------------------------------------------------------------------------------------------------

void FUN_80011c3c(void)

{
  ushort uVar1;
  short sVar2;
  undefined *puVar3;
  uint color;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  color = DAT_80011e70;
  puVar3 = PTR_DAT_80011e6c;
  if (*(char *)(DAT_80011e74 + 7) == '\0') {
    set_display_fg_color(DAT_80011e78);
    display_fill_rounded_rect
              (*(short *)(puVar3 + 4) + 0xb0,*(short *)(puVar3 + 6) + 0xfe,
               *(short *)(puVar3 + 4) + 0xdc,*(short *)(puVar3 + 6) + 0x111,2);
    set_display_fg_color(color);
    display_draw_rounded_rect
              (*(short *)(puVar3 + 4) + 0xb0,*(short *)(puVar3 + 6) + 0xfe,
               *(short *)(puVar3 + 4) + 0xdc,*(short *)(puVar3 + 6) + 0x111,2);
    set_display_fg_color(color);
    display_fill_rounded_rect
              (*(short *)(puVar3 + 4) + 0xb3,*(short *)(puVar3 + 6) + 0x101,
               *(short *)(puVar3 + 4) + 0xc6,*(short *)(puVar3 + 6) + 0x10e,0);
    set_display_fg_color(0);
    display_draw_vert_line
              (*(short *)(puVar3 + 4) + 0xb8,*(short *)(puVar3 + 6) + 0x103,
               *(short *)(puVar3 + 6) + 0x10c);
    display_draw_vert_line
              (*(short *)(puVar3 + 4) + 0xbb,*(short *)(puVar3 + 6) + 0x103,
               *(short *)(puVar3 + 6) + 0x10c);
    display_draw_vert_line
              (*(short *)(puVar3 + 4) + 0xbe,*(short *)(puVar3 + 6) + 0x103,
               *(short *)(puVar3 + 6) + 0x10c);
    uVar1 = *(ushort *)(puVar3 + 6);
    iVar4 = *(ushort *)(puVar3 + 4) + 0xc1;
  }
  else {
    set_display_fg_color(0xff00);
    sVar2 = (short)((int)color >> 0xe);
    display_fill_rounded_rect
              (*(short *)(puVar3 + 4) + 0xb0,*(short *)(puVar3 + 6) + 0xfe,
               *(short *)(puVar3 + 4) + 0xdc,*(short *)(puVar3 + 6) + sVar2,2);
    set_display_fg_color(0x8800);
    display_draw_rounded_rect
              (*(short *)(puVar3 + 4) + 0xb0,*(short *)(puVar3 + 6) + 0xfe,
               *(short *)(puVar3 + 4) + 0xdc,*(short *)(puVar3 + 6) + sVar2,2);
    set_display_fg_color(color);
    display_fill_rounded_rect
              (*(short *)(puVar3 + 4) + 0xc6,*(short *)(puVar3 + 6) + 0x101,
               *(short *)(puVar3 + 4) + 0xd9,*(short *)(puVar3 + 6) + 0x10e,0);
    set_display_fg_color(0);
    display_draw_vert_line
              (*(short *)(puVar3 + 4) + 0xcb,*(short *)(puVar3 + 6) + 0x103,
               *(short *)(puVar3 + 6) + 0x10c);
    display_draw_vert_line
              (*(short *)(puVar3 + 4) + 0xce,*(short *)(puVar3 + 6) + 0x103,
               *(short *)(puVar3 + 6) + 0x10c);
    display_draw_vert_line
              (*(short *)(puVar3 + 4) + 0xd1,*(short *)(puVar3 + 6) + 0x103,
               *(short *)(puVar3 + 6) + 0x10c);
    uVar1 = *(ushort *)(puVar3 + 6);
    iVar4 = *(ushort *)(puVar3 + 4) + 0xd4;
  }

  //display_draw_vert_line
  save_context();
  iVar7 = *(int *)(*DAT_80018f68 + 0x4c);
  iVar5 = *(int *)(*DAT_80018f68 + 0x50);
  iVar6 = FUN_8002ac10(&stack0xffffffe8);
  while (iVar6 != 0) {
    FUN_8001cc4c(iVar4 + iVar7,uVar1 + 0x103 + iVar5,uVar1 + 0x10c + iVar5);
    iVar6 = FUN_8002ab40();
  }
  restore_context();
  return;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//High light a selected menu item

void FUN_800118f4(void)

{
  char cVar1;
  undefined *puVar2;
  int *piVar3;
  ushort uVar4;
  ushort uVar5;
  uint uVar6;
  uint uVar7;
  ushort *puVar8;
  uint uVar9;
  uint uVar10;
  
  cVar1 = *(char *)(DAT_80011c24 + 1);  //0x80361378 + 1 ==> state variable
  uVar4 = convert_color(DAT_80011c28);  //0x00FFFF00 (Yellow)
  uVar9 = 0xe;
  uVar5 = convert_color(DAT_80011c2c);  //0x001B1B1B (Grey)
  piVar3 = Global_Frame_Buffer_Pointer;
  puVar2 = PTR_DAT_80011c30;            //0x80192ef8  some data structure with positions

  if (cVar1 == '\x01')
  {
    do
    {
      uVar10 = (uint)*(ushort *)(puVar2 + 4);  //Xpos
      uVar6 = uVar10 + 9 & 0xfffeffff;

      if (uVar6 < uVar10 + 0xeb)
      {
        uVar10 = (uVar10 - uVar6) + 0xeb & 0xffff;
        puVar8 = (ushort *)(*piVar3 + (uVar6 + (*(ushort *)(puVar2 + 6) + uVar9) * 800) * 2);
        do {
          if (*puVar8 == uVar5) {
            *puVar8 = uVar4;
          }
          else {
            *puVar8 = ~*puVar8;
          }
          uVar10 = uVar10 - 1 & 0xffff;
          puVar8 = puVar8 + 1;
        } while (uVar10 != 0);
      }
      uVar9 = uVar9 + 1 & 0xfffeffff;
    } while (uVar9 < 0x2e);
    return;
  }
  if (cVar1 == '\x02')
  {
    uVar9 = 0x47;
    do {
      uVar10 = (uint)*(ushort *)(puVar2 + 4);
      uVar6 = uVar10 + 9 & 0xfffeffff;
      if (uVar6 < uVar10 + 0xeb) {
        uVar10 = (uVar10 - uVar6) + 0xeb & 0xffff;
        puVar8 = (ushort *)(*piVar3 + (uVar6 + (*(ushort *)(puVar2 + 6) + uVar9) * 800) * 2);
        do {
          if (*puVar8 == uVar5) {
            *puVar8 = uVar4;
          }
          else {
            *puVar8 = ~*puVar8;
          }
          uVar10 = uVar10 - 1 & 0xffff;
          puVar8 = puVar8 + 1;
        } while (uVar10 != 0);
      }
      uVar9 = uVar9 + 1 & 0xfffeffff;
    } while (uVar9 < 0x69);
    return;
  }
  if (cVar1 == '\x03') {
    uVar9 = 0x82;
    do {
      uVar10 = (uint)*(ushort *)(puVar2 + 4);
      uVar6 = uVar10 + 9 & 0xfffeffff;
      if (uVar6 < uVar10 + 0xeb) {
        uVar10 = (uVar10 - uVar6) + 0xeb & 0xffff;
        puVar8 = (ushort *)(*piVar3 + (uVar6 + (*(ushort *)(puVar2 + 6) + uVar9) * 800) * 2);
        do {
          if (*puVar8 == uVar5) {
            *puVar8 = uVar4;
          }
          else {
            *puVar8 = ~*puVar8;
          }
          uVar10 = uVar10 - 1 & 0xffff;
          puVar8 = puVar8 + 1;
        } while (uVar10 != 0);
      }
      uVar9 = uVar9 + 1 & 0xfffeffff;
    } while (uVar9 < 0xa4);
    return;
  }
  if (cVar1 == '\x04') {
    uVar9 = 0xbd;
    do {
      uVar10 = (uint)*(ushort *)(puVar2 + 4);
      uVar6 = uVar10 + 9 & 0xfffeffff;
      if (uVar6 < uVar10 + 0xeb) {
        uVar10 = (uVar10 - uVar6) + 0xeb & 0xffff;
        puVar8 = (ushort *)(*piVar3 + (uVar6 + (*(ushort *)(puVar2 + 6) + uVar9) * 800) * 2);
        do {
          if (*puVar8 == uVar5) {
            *puVar8 = uVar4;
          }
          else {
            *puVar8 = ~*puVar8;
          }
          uVar10 = uVar10 - 1 & 0xffff;
          puVar8 = puVar8 + 1;
        } while (uVar10 != 0);
      }
      uVar9 = uVar9 + 1 & 0xfffeffff;
    } while (uVar9 < 0xde);
    return;
  }
  if (cVar1 != '\x05') {
    return;
  }
  uVar9 = 0xf7;
  uVar10 = DAT_80011c38 - 0xe;
  do {
    uVar6 = (uint)*(ushort *)(puVar2 + 4);
    uVar7 = uVar6 + 9 & 0xfffeffff;
    if (uVar7 < uVar6 + 0xeb) {
      uVar6 = (uVar6 - uVar7) + 0xeb & 0xffff;
      puVar8 = (ushort *)(*piVar3 + (uVar7 + (*(ushort *)(puVar2 + 6) + uVar9) * 800) * 2);
      do {
        if (*puVar8 == uVar5) {
          *puVar8 = uVar4;
        }
        else {
          *puVar8 = ~*puVar8;
        }
        uVar6 = uVar6 - 1 & 0xffff;
        puVar8 = puVar8 + 1;
      } while (uVar6 != 0);
    }
    uVar9 = uVar9 + 1 & 0xfffeffff;
  } while (uVar9 < uVar10);
  return;
}

//------------------------------------------------------------------------------------------------------------------------------------------

void FUN_8001178c(void)

{
  ushort uVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  undefined2 *puVar8;
  uint uVar9;
  undefined2 *puVar10;
  undefined2 *puVar11;
  uint unaff_r4;
  uint uVar12;
  uint uVar13;
  undefined2 *puVar14;
  
  uVar1 = *(ushort *)(PTR_DAT_800117a4 + 4);  //0x_80192ef8    xpos of menu  + 0xf4
  uVar2 = *(ushort *)(PTR_DAT_800117a4 + 6);  //               ypos of menu
  convert_color(DAT_80012254);                //0x00EEEEEE
  convert_color(DAT_80012258);                //0x001B1B1B

  iVar6 = DAT_80012264;                       //0x80361382

  iVar5 = Screen_Frame_Buffer;

  uVar4 = DAT_8001225c;                       //0x0000014B
  uVar13 = DAT_8001225c - unaff_r4;

  uVar9 = 0;
  uVar12 = uVar13 * 0x8000 >> 0x10;

  //Save some screen part??????
  do
  {
    if (unaff_r4 < uVar4)
    {
      puVar14 = (undefined2 *)(iVar6 + (uVar9 * DAT_8001225c + unaff_r4) * 2);
      puVar11 = (undefined2 *)(iVar5 + (unaff_r4 + uVar9 * 800) * 2);
      uVar3 = uVar12;
      puVar8 = puVar11 + -1;
      puVar10 = puVar14 + -1;
      if ((uVar13 & 1) != 0) {
        *puVar14 = *puVar11;
        puVar8 = puVar11;
        puVar10 = puVar14;
      }
      while (uVar3 != 0) {
        puVar10[1] = puVar8[1];
        puVar10[2] = puVar8[2];
        uVar3 = uVar3 - 1 & 0xffff;
        puVar8 = puVar8 + 2;
        puVar10 = puVar10 + 2;
      }
    }
    uVar9 = uVar9 + 1 & 0xfffeffff;
  } while (uVar9 < 0x3b);


  set_display_fg_color(DAT_80012268);   //0x001B1A1B

  display_fill_rect(0,0,(ushort)uVar4,0x3a);

  set_display_fg_color(DAT_8001226c);   //0x00303030

  display_draw_rect(0,0,(ushort)uVar4,0x3a);


  set_display_fg_color(DAT_80012270);   //0x00666666

  display_fill_rounded_rect(0x14,0x18,(ushort)DAT_80012274,0x22,2);


  set_screen_to_global_pointer();

  piVar7 = Global_Frame_Buffer_Pointer;

  uVar9 = 0;
  uVar12 = uVar4;

  //Slide image onto the screen
  do
  {
    uVar9 = uVar9 + 1 & 0xfffeffff;
    if (0x3a < uVar9) {
      uVar12 = (uVar12 - (uVar12 * DAT_8001227c >> 0x14)) - 1 & 0xffff;
      if (uVar12 < 2) {
        uVar13 = 0;
        uVar9 = (uVar4 - uVar12) * 0x8000 >> 0x10;
        do
        {
          puVar14 = (undefined2 *)(iVar6 + (uVar13 * DAT_8001225c + uVar12) * 2);
          puVar11 = (undefined2 *)(iVar5 + (uVar12 + uVar13 * 800) * 2);
          uVar3 = uVar9;
          puVar8 = puVar11 + -1;
          puVar10 = puVar14 + -1;

          if ((uVar4 - uVar12 & 1) != 0)
          {
            *puVar11 = *puVar14;
            puVar8 = puVar11;
            puVar10 = puVar14;
          }

          while (uVar3 != 0)
          {
            puVar8[1] = puVar10[1];
            puVar8[2] = puVar10[2];
            uVar3 = uVar3 - 1 & 0xffff;
            puVar8 = puVar8 + 2;
            puVar10 = puVar10 + 2;
          }
          do
          {
            uVar13 = uVar13 + 1 & 0xfffeffff;
            if (0x3a < uVar13)
            {
              *Global_Frame_Buffer_Pointer = Screen_Frame_Buffer;
              return;
            }
          } while (uVar4 <= uVar12);
        } while( true );
      }
      uVar9 = 0;
    }

    if (uVar12 < uVar4)
    {
      puVar14 = (undefined2 *)(*piVar7 + ((uVar9 + uVar2) * 800 + (uVar1 + 0xf4 & 0xfffeffff)) * 2);
      puVar11 = (undefined2 *)(iVar5 + (uVar12 + uVar9 * 800) * 2);
      puVar8 = puVar14 + -1;
      puVar10 = puVar11 + -1;

      if ((uVar4 - uVar12 & 1) != 0)
      {
        *puVar14 = *puVar11;
        puVar8 = puVar14;
        puVar10 = puVar11;
      }
      uVar13 = (uVar4 - uVar12) * 0x8000 >> 0x10;

      while (uVar13 != 0)
      {
        puVar8[1] = puVar10[1];
        puVar10 = puVar10 + 2;
        uVar13 = uVar13 - 1 & 0xffff;
        puVar8 = puVar8 + 2;
        *puVar8 = *puVar10;
      }
    }
  } while( true );
}

//------------------------------------------------------------------------------------------------------------------------------------------

void FUN_80011764(void)

{
  undefined uVar1;
  ushort ystart;
  int iVar2;
  int iVar3;
  short sVar4;
  ushort xstart;
  int iVar5;
  uint uVar6;
  ushort xend;
  uint uVar7;
  uint uVar8;
  undefined8 uVar9;
  
  ystart = *(ushort *)(PTR_DAT_80011788 + 6);
  uVar7 = (uint)ystart;
  uVar1 = *(undefined *)(DAT_80011784 + 2);
  uVar6 = *(ushort *)(PTR_DAT_80011788 + 4) + 0xf4 & 0xfffeffff;
  convert_color(DAT_80011fc8);
  convert_color(DAT_80011fcc);

  uVar9 = FUN_800397d0(uVar1);

  FUN_80039890((int)uVar9,(int)((ulonglong)uVar9 >> 0x20),DAT_80011fd0,DAT_80011fd4);

  sVar4 = FUN_8003972c();

  set_display_fg_color(DAT_80011fd8);

  xstart = (ushort)uVar6;
  xend = (ushort)(uVar6 + 0x14b);

  display_fill_rect(xstart,ystart,xend,ystart + 0x3a);

  set_display_fg_color(DAT_80011fdc);

  display_draw_rect(xstart,ystart,xend,ystart + 0x3a);

  set_display_fg_color(DAT_80011fe0);  //0x00666666

  display_fill_rounded_rect(xstart + 0x14,ystart + 0x18,xstart + 0x137,ystart + 0x22,2);

  set_display_fg_color(DAT_80011fe4);  //0x00FFFF00

  sVar4 = sVar4 + xstart;

  display_fill_rounded_rect(xstart + 0x14,ystart + 0x18,sVar4 + 0x14,ystart + 0x22,2);

  set_display_fg_color(DAT_80011fe8);   //0x00AAAAAA

  display_fill_rounded_rect(sVar4 + 9,ystart + 0x12,sVar4 + 0x1f,ystart + 0x28,2);

  set_display_fg_color(0);

  display_draw_vert_line(sVar4 + 0xf,ystart + 0x17,ystart + 0x23);
  display_draw_vert_line(sVar4 + 0x14,ystart + 0x17,ystart + 0x23);
  display_draw_vert_line(sVar4 + 0x19,ystart + 0x17,ystart + 0x23);



  iVar3 = Start_Of_Screen_Mem;
  iVar2 = Screen_Frame_Buffer;
  uVar8 = uVar7 + 0x3b & 0xfffeffff;
  if (uVar8 <= uVar7) {
    return;
  }
  do {
    iVar5 = uVar6 + uVar7 * 800;
    copy_short((void *)(iVar3 + iVar5 * 2),(void *)(iVar2 + iVar5 * 2),
               ((uVar6 + 0x14b & 0xfffeffff) - uVar6) + 1);
    uVar7 = uVar7 + 1;
  } while (uVar7 < uVar8);
  return;
}

//------------------------------------------------------------------------------------------------------------------------------------------

