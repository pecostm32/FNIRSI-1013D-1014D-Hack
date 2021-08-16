//-----------------------------------------------------------------------------------------------------------------------------------------------

void display_trace_data(void)

{
  char cVar1;
  undefined2 uVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  undefined *puVar6;
  char *pcVar7;
  undefined *puVar8;
  ushort uVar9;
  int iVar10;
  ushort *puVar11;
  int iVar12;
  undefined2 *puVar13;
  uint uVar14;
  uint uVar15;
  int iVar16;
  ushort uVar17;
  code *UNRECOVERED_JUMPTABLE_00;
  bool bVar18;
  
  pcVar7 = DAT_8002b64c;        //0x8019D5A0  base of settings
  puVar6 = PTR_DAT_8002b648;    //0x80192f08  touch state
  cVar1 = *PTR_DAT_8002b648;


  //Touch state equal to 2 and (trigger mode not single or run mode stop)
  if ((cVar1 == '\x02') && ((DAT_8002b64c[0x21] != '\x01' || (DAT_8002b64c[0x3a] == '\x01'))))
  {
    DAT_8002b64c[0x18] = '\x01';  //Some trigger flag set  triggerflag2
    pcVar7[0x17] = '\x01';        //Plus another           triggerflag1
  }

  puVar8 = PTR_DAT_8002b65c;      //0x80192eaa  base of display trace data settings
  iVar5 = DAT_8002b658;           //0x80361378  base of some settings like brightness
  iVar4 = DAT_8002b654;           //0x801C374A  ??  some large buffer
  uVar17 = (ushort)DAT_8002b650;  //0x000002DA  730
  iVar16 = DAT_8002b654 + 2000;

  if (8 < (byte)pcVar7[10])   //time base setting when > 8 means 50mS/div down to 10nS/div
  {
    //So drawing of the short time base data
    if (pcVar7[0x18] != '\0')
    {
      set_frame_to_global_pointer();
      set_display_fg_color(0);
      display_fill_rect(2,0x2f,uVar17,uVar17 - 0xfb);
      display_draw_grid();
    }

    if (pcVar7[0x17] == '\0')
      goto LAB_8002b414;


//======
 
    //Get starting point in signal buffer based on trigger position on screen
    FUN_8001b424(pcVar7 + 0x1a,pcVar7 + 0x1c);  //pass in two variables that are written with fixed values in this function???

    //scope_determine_sample_buffer_indexes in my code without the input parameters. Makes use of zoom_select



    if (*pcVar7 != '\0')    //channel 1 enabled
    {
      if ((pcVar7[0x3a] == '\0') && (*puVar6 != '\x02'))   //run state (running) touchstate needs to be zero, because non zero means moving in my code
      {
        *(undefined2 *)(puVar8 + 0x12) = 400;  //some position var???
      }

      //Zoom based on zoom_select
      FUN_8000410c();  //process_channel1_trace_data

      cVar1 = pcVar7[0x21];      //trigger mode
      bVar18 = cVar1 != '\0';

      if (bVar18)
      {
        cVar1 = pcVar7[0x21];
      }

      //Trigger mode auto or normal and timebase > 26 and (trigger channel is channel 2 or some flag is not 0)
      if (((!bVar18 || cVar1 == '\x02') && (0x1a < (byte)pcVar7[10])) && ( (pcVar7[0x23] == '\x01' || (pcVar7[9] != '\0') ) ))
      {
        FUN_8000583c();
      }

      if (*(char *)(iVar5 + 7) == '\0')   //normal display mode
      {
        FUN_80012a64(*(undefined2 *)(pcVar7 + 0x1a),0,*(undefined2 *)(pcVar7 + 0x1c),DAT_8002b654);
      }
    }


    //channel 2
    if (pcVar7[0xc] == '\0')
    {
LAB_8002b2e8:
      if (*(char *)(iVar5 + 7) != '\0')
        goto LAB_8002b2f4;
    }
    else
    {
      if ((pcVar7[0x3a] == '\0') && (*puVar6 != '\x02'))
      {
        *(undefined2 *)(puVar8 + 0x14) = 400;
      }

      FUN_80006f28();

      cVar1 = pcVar7[0x21];
      bVar18 = cVar1 != '\0';

      if (bVar18)
      {
        cVar1 = pcVar7[0x21];
      }

      if (((!bVar18 || cVar1 == '\x02') && (0x1a < (byte)pcVar7[10])) && ((pcVar7[0x23] == '\0' || (pcVar7[0x15] != '\0'))))
      {
        FUN_80008594();
      }

      if (*(char *)(iVar5 + 7) == '\0')
      {
        FUN_80012a64(*(undefined2 *)(pcVar7 + 0x1a),0,*(undefined2 *)(pcVar7 + 0x1c),DAT_8002b668);

        goto LAB_8002b2e8;
      }

LAB_8002b2f4:
      set_frame_to_global_pointer();
      set_display_fg_color(DAT_8002b66c);   //0x00FF00FF   (purple) so x-y mode here

      if (*(ushort *)(pcVar7 + 0x1c) < 2)    //Number of samples???
      {
        *(undefined2 *)(pcVar7 + 0x1c) = 2;
      }

      uVar15 = 1;

      if (1 < (int)(*(ushort *)(pcVar7 + 0x1c) - 2))
      {
        do
        {
          puVar11 = (ushort *)(iVar4 + uVar15 * 2);          //sample from first channel
          puVar13 = (undefined2 *)(iVar16 + uVar15 * 2);     //sample from second channel

          FUN_80018d30(*puVar11 + 0x96,*puVar13,puVar11[1] + 0x96,puVar13[1]);   //display_draw_line single pixel!! for x-y mode only

          uVar15 = uVar15 + 1 & 0xfffeffff;
        } while ((int)uVar15 < (int)(*(ushort *)(pcVar7 + 0x1c) - 2));
      }
    }

    cVar1 = pcVar7[4];
    bVar18 = cVar1 != '\0';

    if (bVar18)  //fft enable on channel 1
    {
      cVar1 = *pcVar7;
    }

    if (bVar18 && cVar1 != '\0')   //if channel 1 enabled and fft enabled
    {
      FUN_800043e4();              //display the fft for channel 1
    }


    cVar1 = pcVar7[0x10];         //channel 2 fft enable
    bVar18 = cVar1 != '\0';

    if (bVar18)
    {
      cVar1 = pcVar7[0xc];
    }

    if (bVar18 && cVar1 != '\0')   //if channel 2 enabled and fft for channel 2
    {
      set_display_fg_color(0);
      display_fill_rect(3,0x81,0x2d5,0xd1);

      FUN_800075dc();  //calculate fft

      set_display_fg_color(DAT_8002b670);   //0x00FF00CC another shade of purple

      puVar13 = DAT_8002b674;
      uVar15 = 0;
      *DAT_8002b674 = DAT_8002b674[1];

      do
      {
        puVar11 = puVar13 + uVar15;

        if (0x50 < *puVar11)
        {
          *puVar11 = 0x50;
        }

        display_draw_vert_line((short)uVar15 + 3,0xd1 - *puVar11,0xd1);

        uVar15 = uVar15 + 1 & 0xfffeffff;
      } while (uVar15 < 0x2d3);
    }



//======


LAB_8002b414:
    iVar4 = DAT_8002b678;

    if (pcVar7[0x18] == '\0')
    {
      return;
    }

    if (*(char *)(DAT_8002b678 + 0x292) != '\0')
    {
      display_draw_time_cursors();
    }

    if (*(char *)(iVar4 + 0x29a) != '\0')
    {
      display_draw_volt_cursors();
    }

    cVar1 = *(char *)(iVar4 + 0x292);
    bVar18 = cVar1 == '\0';

    if (bVar18)
    {
      cVar1 = *(char *)(iVar4 + 0x29a);
    }

    if (!bVar18 || cVar1 != '\0')
    {
      FUN_8000ebf8();
    }

    display_draw_trace_pointers();

    FUN_80021810();

    uVar15 = DAT_8002b67c;
    iVar5 = Start_Of_Screen_Mem;
    iVar4 = Screen_Frame_Buffer;
    uVar14 = 0x2e;
    iVar16 = DAT_8002b67c + 0xf6;

    if (DAT_8002b67c < 0x2f)
    {
      return;
    }

    do
    {
      iVar10 = uVar14 * 800 + 2;
      copy_short((void *)(iVar5 + iVar10 * 2),(void *)(iVar4 + iVar10 * 2),iVar16);
      uVar14 = uVar14 + 1;
    } while (uVar14 < uVar15);

    return;
  }




//|||||||||||||||||||||||||||||||||||||||||||||||||||||||\


  //Handle long time base data
  uVar9 = (ushort)(byte)pcVar7[0x3a];  //run mode

  if (uVar9 != 0)   //When stopped just return
  {
    return;
  }

  if (cVar1 != '\x02')            //Check the touch state not being 2
  {
    uVar9 = *(ushort *)PTR_DAT_8002b65c;  //0x80192eaa
  }
  else
  {
    *(undefined2 *)PTR_DAT_8002b65c = 0;   //Flag set zero
  }

  //Touch state set to 2 when time base change???
  //This action seems to be taken in that case
  if (cVar1 == '\x02' || uVar9 == 0)       //Check if touch state == 2 or flag == 0
  {
    set_frame_to_global_pointer();
    set_display_fg_color(0);

    uVar9 = (ushort)DAT_8002b67c;          //0x000001DF   479

    display_fill_rect(2,0x2f,uVar17,uVar9);   //730, 479

    display_draw_grid();

    //This is a problem, because the traces are drawn through the pointers
    //So needs a check on where the traces are or just do it after every new pixel drawn
    display_draw_trace_pointers();

    copy_rect_to_screen(2,0x2e,uVar9 + 0xf7,uVar9);

    set_screen_to_global_pointer();
  }

  iVar10 = DAT_8002b680;  //0x000001C1  449

  //Channel 1 enabled
  if (*pcVar7 != '\0')
  {
    set_screen_to_global_pointer();

    iVar12 = iVar10 - (uint)*DAT_8002b684;         //0x801AC04A
    *(short *)(puVar8 + 0x16) = (short)iVar12;
    iVar12 = iVar12 * 0x10000 >> 0x10;    //and with 0xffff

    if (iVar12 < 0x2f)     //Limit on top of the screen
    {
      iVar12 = 0x2f;
    }
    else
    {
      if (0x1c0 < iVar12)  //Limit on bottom of the screen
      {
        iVar12 = 0x1c0;
      }
    }

    *(short *)(puVar8 + 0x16) = (short)iVar12;  //Save it somewhere

    if (*(char *)(iVar5 + 7) == '\0')   //x-y display mode. 0 is normal mode
    {
      FUN_800067ac();  //Draw the trace part
    }
  }

  //Channel 2 enable
  if (pcVar7[0xc] == '\0') //Not enabled
  {
LAB_8002b590:
    if (*(char *)(iVar5 + 7) == '\0')
      goto LAB_8002b624;
  }
  else
  {
    set_screen_to_global_pointer();

    iVar10 = iVar10 - (uint)*DAT_8002b688;     //0x801AD7BA
    *(short *)(puVar8 + 0x18) = (short)iVar10;
    iVar10 = iVar10 * 0x10000 >> 0x10;

    if (iVar10 < 0x2f)
    {
      iVar10 = 0x2f;
    }
    else
    {
      if (0x1c0 < iVar10)
      {
        iVar10 = 0x1c0;
      }
    }

    *(short *)(puVar8 + 0x18) = (short)iVar10;

    if (*(char *)(iVar5 + 7) == '\0')
    {
      FUN_800094f8();

      goto LAB_8002b590;
    }
  }


  //x-y mode ???
  if (*(short *)puVar8 == 0)  //x position counter
  {
    *(undefined2 *)(puVar8 + 2) = *(undefined2 *)(puVar8 + 0x16);   //Channel 1 data old and new
    *(undefined2 *)(puVar8 + 4) = *(undefined2 *)(puVar8 + 0x18);   //Channel 2 data
  }

  set_display_fg_color(DAT_8002b66c);



  FUN_80018d30(*(ushort *)(puVar8 + 2) + 0x96,*(undefined2 *)(puVar8 + 4),*(ushort *)(puVar8 + 0x16) + 0x96,*(undefined2 *)(puVar8 + 0x18));

  FUN_80018d30(*(ushort *)(puVar8 + 2) + 0x97,*(ushort *)(puVar8 + 4) + 1,*(ushort *)(puVar8 + 0x16) + 0x97,*(ushort *)(puVar8 + 0x18) + 1);



  *(undefined2 *)(puVar8 + 2) = *(undefined2 *)(puVar8 + 0x16);

  uVar2 = *(undefined2 *)(puVar8 + 0x18);

  *(undefined2 *)(puVar8 + 4) = uVar2;

  uVar17 = *(ushort *)puVar8;   //disp_xpos

//Save to an array of points???? For saving to SD card????
  *(undefined2 *)(iVar4 + (uint)uVar17 * 2) = *(undefined2 *)(puVar8 + 0x16);

  *(undefined2 *)(iVar16 + (uint)uVar17 * 2) = uVar2;


LAB_8002b624:
  //Select next pixel
  sVar3 = *(short *)puVar8;      //disp_xpos
  *(ushort *)puVar8 = sVar3 + 1U;

  if (0x2cf < (ushort)(sVar3 + 1U))
  {
    *(undefined2 *)puVar8 = 0;
  }

  return;
}


//-----------------------------------------------------------------------------------------------------------------------------------------------

void FUN_800067ac(void)

{
  undefined2 *puVar1;
  undefined *puVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  bool bVar8;
  bool bVar9;
  
  set_display_fg_color(DAT_80006890);   //0x00FFFF00


  puVar2 = PTR_DAT_80006894;    //0x80192eaa    disp_xpos

  uVar4 = (uint)*(ushort *)PTR_DAT_80006894;  //disp_xpos

  if (uVar4 == 0)  //Reset on beginning of screen
  {
    puVar1 = (undefined2 *)(PTR_DAT_80006894 + 0x16);   //disp_ch1_y
    *(undefined2 *)(PTR_DAT_80006894 + 2) = *puVar1;    //disp_ch1_prev_y
    *(undefined2 *)(puVar2 + 6) = *puVar1;              //Yet another save
  }

  uVar7 = (uint)*(ushort *)(puVar2 + 0x16);             //disp_ch1_y            r3
  uVar5 = (uint)*(ushort *)(puVar2 + 2);                //disp_ch1_prev_y       r1

  uVar6 = uVar7 + 0xf;            //plus 15                                     r2

  bVar9 = uVar5 <= uVar6;         //previous lower or equal to adjusted         cmp r2,r1
  bVar8 = uVar6 == uVar5;         //equal to

  if (bVar9 && !bVar8)            //Lower but not equal   r2 > r1
  {
    uVar6 = uVar5 + 0xf;          //use previous plus 15                        addhi r2,r1,#15
  }

  if (bVar9 && !bVar8)            //lower but not equal
  {
    bVar9 = uVar7 <= uVar6;       //y lower or equal to adjusted prev or y
    bVar8 = uVar6 == uVar7;       //equal to
  }

  if (!bVar9 || bVar8)            //if greater or equal
  {
    uVar6 = uVar5 + 0x14;         //previous plus 20

    bVar9 = uVar6 <= uVar7;       //lower or equal to y
    bVar8 = uVar7 == uVar6;

    if (!bVar9 || bVar8)          //if greater or equal
    {
      uVar6 = uVar7 + 0x14;       //use y + 20
    }

    if (!bVar9 || bVar8)          //if greater or equal
    {
      bVar9 = uVar6 <= uVar5;     //lower equal
      bVar8 = uVar5 == uVar6;     //equal
    }

    //Some detection on rise speed??? When quicker draw on same x???
    if (bVar9 && !bVar8)          //lower then
    {
      FUN_80018d30(uVar4 + 3,uVar5,uVar4 + 3, uVar7);

      FUN_80018d30(*(ushort *)puVar2 + 3,*(ushort *)(puVar2 + 2) + 1,*(ushort *)puVar2 + 3,*(ushort *)(puVar2 + 0x16) + 1);

      goto LAB_80006828;
    }
  }
  else
  {
    //set point to be an average
    *(short *)(puVar2 + 0x16) = (short)(uVar7 + uVar5 >> 1);
  }


  //Draw the lines
  FUN_80018d30(uVar4 + 3,uVar5,uVar4 + 4);

  FUN_80018d30(*(ushort *)puVar2 + 3,*(ushort *)(puVar2 + 2) + 1,*(ushort *)puVar2 + 4,*(ushort *)(puVar2 + 0x16) + 1);



LAB_80006828:
  iVar3 = DAT_80006898;   //801C374A
  *(undefined2 *)(puVar2 + 6) = *(undefined2 *)(puVar2 + 2);

  //Save as previous
  *(undefined2 *)(puVar2 + 2) = *(undefined2 *)(puVar2 + 0x16);

  //Store in point array
  *(undefined2 *)(iVar3 + (uint)*(ushort *)puVar2 * 2) = *(undefined2 *)(puVar2 + 0x16);

  return;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

