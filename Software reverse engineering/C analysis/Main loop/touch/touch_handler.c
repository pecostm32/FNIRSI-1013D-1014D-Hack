//------------------------------------------------------------------------------------------------------------------------------------------
//0x80192f02  have touch indicator
//0x8036b792  same

//0x80192f04  x coordinate of touch
//0x8036b794  same
//0x8019cf7e  same

//0x80192f06  y coordinate of touch
//0x8036b792  same
//0x8019cf80  same


void touch_handler(void)
{
  char cVar1;
  ushort uVar2;
  ushort uVar3;
  uint *ptr;
  undefined *puVar4;
  undefined *puVar5;
  short sVar6;
  undefined2 uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint unaff_r4;
  int iVar11;
  code *UNRECOVERED_JUMPTABLE;
  bool bVar12;
  
  iVar8 = DAT_8001a5b8;            //0x8019D5A0 Base address of settings
  puVar4 = PTR_DAT_8001a5b4;       //0x80192f08

  //Check if no previous touch??  This state seems to be for detecting short taps that indicate change of time base and longer taps that signal cursor or trace movement
  if (*PTR_DAT_8001a5b4 == '\0')   //0x80192f08 In the last part of the scan for touch this is set.
  {
    //Call this function in that case
    //In my version of the code this is "void scan_for_touch(void);"
    FUN_8001b674();                //Returns directly if there is no touch. !!!This function is almost implemented (scan_for_touch)!!!


    iVar9 = DAT_8001a5c8;          //0x801FA44C
   
    if (*puVar4 != '\x02')         //Check if there is previous touch from call FUN_8001b674
      goto LAB_8001a410;           //If so go and process it

    //When 2 set these variables
    *(undefined2 *)(puVar4 + 0xe) = *(undefined2 *)PTR_DAT_8001a5c4;                   //0x0x80192f08 + 0x0E  = short from 0x80192ebc
    *(undefined2 *)(puVar4 + 0x10) = *(undefined2 *)PTR_DAT_8001a5cc;                  //0x0x80192f08 + 0x10  = short from 0x80192ebe

    *(undefined2 *)(puVar4 + 0x12) = *(undefined2 *)(iVar8 + 6);                       //0x0x80192f08 + 0x12  = short from 0x8019D5A0 + 6    Channel 1 trace offset
    *(undefined2 *)(puVar4 + 0x14) = *(undefined2 *)(iVar8 + 0x12);                    //0x0x80192f08 + 0x14  = short from 0x8019D5A0 + 0x12 Channel 2 trace offset

    *(undefined2 *)(puVar4 + 10) = *(undefined2 *)(iVar8 + 0x24);                      //trigger position
    *(undefined2 *)(puVar4 + 0xc) = *(undefined2 *)(iVar8 + 0x26);                     //trigger level

    *(undefined2 *)(puVar4 + 0x16) = *(undefined2 *)(iVar9 + 0x94);                    //0x0x80192f08 + 0x16  = short from 0x801FA44C + 0x94
    *(undefined2 *)(puVar4 + 0x18) = *(undefined2 *)(iVar9 + 0x96);
    *(undefined2 *)(puVar4 + 0x1a) = *(undefined2 *)(iVar9 + 0x9c);
    *(undefined2 *)(puVar4 + 0x1c) = *(undefined2 *)(iVar9 + 0x9e);

    if (*(char *)(iVar8 + 0x3a) == '\0')      //When acquisition is running (scope run mode 0x8019d5da)
    {
      *(undefined2 *)(puVar4 + 0xe) = 400;    //0x80192f08 + 0x0E  some limit??
    }
  }
  else
  {
    //Previous run gave touch so check again
    tp_i2c_read_status();              //Check the touch panel on touch

    puVar5 = PTR_DAT_8001a5bc;         //0x80192f02. Touch data

    if (*PTR_DAT_8001a5bc == '\0')     //Check if there is touch or not
    {
      *puVar4 = 0;                     //Not so signal this some where.  0x80192f08  Clear the state variables
      puVar4[1] = 0;                   //                                0x80192f09
      return;                          //Done
    }

    //Copy the coordinates to somewhere
    *(undefined2 *)(puVar4 + 0x2e) = *(undefined2 *)(PTR_DAT_8001a5bc + 2);     //0x80192f08 + 0x2E (0x80192f36) = 0x80192f04  (x coord)
    *(undefined2 *)(puVar4 + 0x30) = *(undefined2 *)(puVar5 + 4);               //0x80192f08 + 0x30 (0x80192f38) = 0x80192f06  (y coord)

LAB_8001a410:
    if (*puVar4 == '\x01')   //Check if there was touch before. Some state machine setup?? (0x80192f08)
    {
      if ((10 < *(byte *)(iVar8 + 0xb)) || (*(char *)(iVar8 + 0x3a) == '\0'))  //Some not yet known setting and scope run mode
      {
        //When in run mode or the other variable is 11 or more. Is a copy of the time base setting
        //This is for changing the time base setting
        FUN_8001ac54();
      }

      *puVar4 = 0;    //Touch handled for now
      return;         //Done
    }

    if (*puVar4 != '\x02')  //This is some state machine flag
    {
      return;
    }
  }

//If not bailed out due to some touch continue here
//pa:0x8001a424
  if (*(char *)(DAT_8001a5c0 + 7) == '\0')  //0x8036137f byte pointer  Normal display mode not x-y
  {
    cVar1 = puVar4[1];   //0x80192f09  some state byte??  Could this be a trace select????

    if (cVar1 == '\x04')
    {
      FUN_8001a9c0();   //target 0x801fa4e0 time cursor left
    }
    else
    {
      if (cVar1 == '\x05')
      {
        FUN_8001a860();  //right
      }
      else
      {
        if (cVar1 == '\x06')
        {
          FUN_8001aa6c(); //volt top
        }
        else
        {
          if (cVar1 == '\a')
          {
            FUN_8001a910();//volt bottom
          }
        }
      }
    }

    iVar9 = DAT_8001a754;  //0x8019D5A0

    if (10 < *(byte *)(iVar8 + 10))  //time base
    {
      if (puVar4[1] == '\0')
      {
        FUN_8001ab18();    //Move trigger point position
      }

      cVar1 = puVar4[1];

      if (cVar1 != '\x01')
      {
        if (cVar1 == '\x02')   //Channel 1
        {
          FUN_8001ab18();    //Move trigger point position

          FUN_8001a5d0();    //Move channel 1 ????

          if (*(char *)(iVar8 + 0x23) != '\0')   //Trigger channel not on this channel
          {
            return;
          }
        }
        else
        {
          if (cVar1 != '\x03')  //Channel 2
          {
            return;
          }

          FUN_8001ab18();    //Move trigger point position

          FUN_8001a764();    //Move channel 2 ????

          if (*(char *)(iVar8 + 0x23) != '\x01')   //Trigger channel not on this channel
          {
            return;
          }
        }
      }

//This bit handles trigger level
      iVar11 = 1;

      iVar9 = FUN_80017790();    //check on valid touch

      puVar4 = PTR_DAT_8001ac50;

      iVar8 = DAT_8001ac4c;

      if (iVar9 != 0)    //check on valid touch
      {
        return;
      }

      uVar2 = *(ushort *)(PTR_DAT_8001ac50 + 0x30);

      uVar3 = *(ushort *)(PTR_DAT_8001ac50 + 0x34);

      if (*(char *)(DAT_8001ac4c + 0x16) != '\0')
      {
        iVar11 = 5;
      }

      if (uVar2 < uVar3)
      {
        iVar9 = divide((uint)(ushort)(uVar3 - uVar2),iVar11);

        uVar10 = iVar9 + (uint)*(ushort *)(puVar4 + 0xc);

        bVar12 = 0x18b < uVar10;

        if (bVar12)
        {
          uVar10 = 0x18c;
        }

        uVar7 = (undefined2)uVar10;

        if (bVar12)
        {
          *(undefined2 *)(iVar8 + 0x26) = uVar7;
          return;
        }
      }
      else
      {
        iVar9 = divide((uint)(ushort)(uVar2 - uVar3),iVar11);
        uVar10 = (uint)*(ushort *)(puVar4 + 0xc);
        bVar12 = iVar9 + 6U < uVar10;

        if (bVar12)
        {
          iVar9 = uVar10 - iVar9;
        }

        uVar7 = (undefined2)iVar9;

        if (!bVar12)
        {
          uVar7 = 6;
        }
      }

      *(undefined2 *)(iVar8 + 0x26) = uVar7;
      return;
    }


//The rest is only active when running and time base 10 and up (50mS/div - 10nS/div)
    if ((*(char *)(iVar8 + 0x3a) != '\0') && (*(byte *)(iVar8 + 10) < 9))
    {
      return;
    }

    if (puVar4[1] == '\x02')
    {
      iVar8 = 1;

      if (*(char *)(DAT_8001a754 + 0x16) != '\0')
      {
        iVar8 = 5;
      }

      iVar11 = FUN_80017790();

      puVar5 = PTR_DAT_8001a760;
      puVar4 = PTR_DAT_8001a75c;

      if (iVar11 != 0)
      {
        return;
      }

      //channel 1 displacement
      //display x-y mode flag. check on normal display mode
      if (*(char *)(DAT_8001a758 + 7) == '\0')
      {
        uVar2 = *(ushort *)(PTR_DAT_8001a760 + 0x30);
        uVar3 = *(ushort *)(PTR_DAT_8001a760 + 0x34);

        if (uVar3 <= uVar2)
        {
          iVar8 = divide((uint)(ushort)(uVar2 - uVar3),iVar8);

          uVar10 = (uint)*(ushort *)(puVar5 + 0x12);

          if (iVar8 + 7U < uVar10)
          {
            *(ushort *)(iVar9 + 6) = *(ushort *)(puVar5 + 0x12) - (short)iVar8;
          }
          else
          {
            *(undefined2 *)(iVar9 + 6) = 7;
          }

          goto joined_r0x8001a6a4;
        }

        iVar8 = divide((uint)(ushort)(uVar3 - uVar2),iVar8);

        uVar10 = (uint)*(ushort *)(puVar5 + 0x12);

        if (iVar8 + uVar10 < 0x18b)
        {
          *(short *)(iVar9 + 6) = (short)(iVar8 + uVar10);
        }
        else
        {
          *(undefined2 *)(iVar9 + 6) = 0x18b;
        }

joined_r0x8001a6f0:
        if (0x18b < uVar10)
        {
          *(undefined2 *)(puVar5 + 0x12) = 0x18b;
        }
        uVar2 = *(ushort *)(puVar5 + 0xe);
        sVar6 = (*(short *)(iVar9 + 6) - *(short *)(puVar5 + 0x12)) + uVar2;
      }
      else
      {
        //x-y mode display
        uVar2 = *(ushort *)(PTR_DAT_8001a760 + 0x2e);
        uVar3 = *(ushort *)(PTR_DAT_8001a760 + 0x32);

        if (uVar2 < uVar3)
        {
          iVar8 = divide((uint)(ushort)(uVar3 - uVar2),iVar8);
          uVar10 = (uint)*(ushort *)(puVar5 + 0x12);

          if (iVar8 + uVar10 < 0x18b)
          {
            *(short *)(iVar9 + 6) = (short)(iVar8 + uVar10);
          }
          else
          {
            *(undefined2 *)(iVar9 + 6) = 0x18b;
          }

          goto joined_r0x8001a6f0;
        }

        iVar8 = divide((uint)(ushort)(uVar2 - uVar3),iVar8);

        uVar10 = (uint)*(ushort *)(puVar5 + 0x12);

        if (iVar8 + 7U < uVar10)
        {
          *(ushort *)(iVar9 + 6) = *(ushort *)(puVar5 + 0x12) - (short)iVar8;
        }
        else
        {
          *(undefined2 *)(iVar9 + 6) = 7;
        }

joined_r0x8001a6a4:
        if (uVar10 < 7)
        {
          *(undefined2 *)(puVar5 + 0x12) = 7;
        }

        uVar2 = *(ushort *)(puVar5 + 0xe);
        sVar6 = uVar2 - (*(short *)(puVar5 + 0x12) - *(short *)(iVar9 + 6));
      }

//Write new trace offset to the fpga
      uVar10 = (uint)uVar2;
      *(short *)puVar4 = sVar6;

      switch(*(undefined *)(DAT_80006a84 + 3))
      {
      case 0:
        unaff_r4 = (uint)DAT_80006a88[1];
        break;
      case 1:
        unaff_r4 = (uint)DAT_80006a88[2];
        break;
      case 2:
        unaff_r4 = (uint)DAT_80006a88[3];
        break;
      case 3:
        unaff_r4 = (uint)DAT_80006a88[4];
        break;
      case 4:
        unaff_r4 = (uint)DAT_80006a88[5];
        break;
      case 5:
      case 6:
        unaff_r4 = (uint)DAT_80006a88[6];
      }

      switch(*(undefined *)(DAT_80006a84 + 3))
      {
      case 0:
        uVar10 = (uint)*DAT_80006a8c;
        break;
      case 1:
        uVar10 = (uint)DAT_80006a8c[1];
        break;
      case 2:
        uVar10 = (uint)DAT_80006a8c[2];
        break;
      case 3:
        uVar10 = (uint)DAT_80006a8c[3];
        break;
      case 4:
        uVar10 = (uint)DAT_80006a8c[4];
        break;
      case 5:
        uVar10 = (uint)DAT_80006a8c[5];
        break;
      case 6:
        uVar10 = (uint)DAT_80006a8c[6];
      }

      iVar8 = (int)((ulonglong)((longlong)DAT_80006a90 * (longlong)(int)((uint)*(ushort *)(DAT_80006a84 + 6) * (uint)*DAT_80006a88)) >> 0x20);
      iVar8 = divide_2((uint)*DAT_80006a8c * ((iVar8 >> 5) - (iVar8 >> 0x1f)),uVar10);
      uVar10 = unaff_r4 - iVar8 & 0xffff;

      fpga_write_cmd('2');                    //Channel 1 trace offset
      fpga_write_data((uchar)(uVar10 >> 8));
      fpga_write_data((uchar)(uVar10));
      return;
    }

    if (puVar4[1] != '\x03')
    {
      return;
    }
  }
  else
  {
    //When in x - y mode

    FUN_8001a5d0();
  }

  iVar11 = 1;

  iVar9 = FUN_80017790();

  puVar5 = PTR_DAT_8001a858;
  puVar4 = PTR_DAT_8001a854;
  iVar8 = DAT_8001a850;

  if (iVar9 != 0)
  {
    return;
  }

  uVar2 = *(ushort *)(PTR_DAT_8001a854 + 0x30);
  uVar3 = *(ushort *)(PTR_DAT_8001a854 + 0x34);

  if (*(char *)(DAT_8001a850 + 0x16) != '\0')
  {
    iVar11 = 5;
  }

  if (uVar2 < uVar3)
  {
    iVar9 = divide((uint)(ushort)(uVar3 - uVar2),iVar11);
    uVar2 = *(ushort *)(puVar4 + 0x14);
    uVar10 = iVar9 + (uint)uVar2;
    uVar7 = (undefined2)DAT_8001a85c;

    if (uVar10 < DAT_8001a85c)
    {
      *(short *)(iVar8 + 0x12) = (short)uVar10;
    }
    else
    {
      *(undefined2 *)(iVar8 + 0x12) = uVar7;
    }
    if (0x18b < uVar2)
    {
      *(undefined2 *)(puVar4 + 0x14) = uVar7;
    }
    uVar2 = *(ushort *)(puVar4 + 0x10);
    sVar6 = (*(short *)(iVar8 + 0x12) - *(short *)(puVar4 + 0x14)) + uVar2;
  }
  else
  {
    iVar9 = divide((uint)(ushort)(uVar2 - uVar3),iVar11);
    uVar2 = *(ushort *)(puVar4 + 0x14);

    if (iVar9 + 7U < (uint)uVar2)
    {
      *(ushort *)(iVar8 + 0x12) = uVar2 - (short)iVar9;
    }
    else
    {
      *(undefined2 *)(iVar8 + 0x12) = 7;
    }

    if (uVar2 < 7)
    {
      *(undefined2 *)(puVar4 + 0x14) = 7;
    }

    uVar2 = *(ushort *)(puVar4 + 0x10);
    sVar6 = uVar2 - (*(short *)(puVar4 + 0x14) - *(short *)(iVar8 + 0x12));
  }

//Write channel 2 trace offset to fpga
  uVar10 = (uint)uVar2;
  *(short *)puVar5 = sVar6;
  switch(*(undefined *)(DAT_800097d0 + 0xf)) {
  case 0:
    unaff_r4 = (uint)*(ushort *)(DAT_800097d4 + 0x10);
    break;
  case 1:
    unaff_r4 = (uint)*(ushort *)(DAT_800097d4 + 0x12);
    break;
  case 2:
    unaff_r4 = (uint)*(ushort *)(DAT_800097d4 + 0x14);
    break;
  case 3:
    unaff_r4 = (uint)*(ushort *)(DAT_800097d4 + 0x16);
    break;
  case 4:
    unaff_r4 = (uint)*(ushort *)(DAT_800097d4 + 0x18);
    break;
  case 5:
  case 6:
    unaff_r4 = (uint)*(ushort *)(DAT_800097d4 + 0x1a);
  }
  switch(*(undefined *)(DAT_800097d0 + 0xf)) {
  case 0:
    uVar10 = (uint)*DAT_800097d8;
    break;
  case 1:
    uVar10 = (uint)DAT_800097d8[1];
    break;
  case 2:
    uVar10 = (uint)DAT_800097d8[2];
    break;
  case 3:
    uVar10 = (uint)DAT_800097d8[3];
    break;
  case 4:
    uVar10 = (uint)DAT_800097d8[4];
    break;
  case 5:
    uVar10 = (uint)DAT_800097d8[5];
    break;
  case 6:
    uVar10 = (uint)DAT_800097d8[6];
  }
  iVar8 = (int)((ulonglong)
                ((longlong)DAT_800097dc *
                (longlong)
                (int)((uint)*(ushort *)(DAT_800097d0 + 0x12) * (uint)*(ushort *)(DAT_800097d4 + 0xe)
                     )) >> 0x20);
  iVar8 = divide_2((uint)*DAT_800097d8 * ((iVar8 >> 5) - (iVar8 >> 0x1f)),uVar10);
  uVar10 = unaff_r4 - iVar8 & 0xffff;

  fpga_write_cmd('5');    //Channel 2 offset, set after moving a trace

  fpga_write_data((uchar)(uVar10 >> 8));
  fpga_write_data((uchar)(uVar10));
  return;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//scan_for_touch

void FUN_8001b674(void)

{
  char cVar1;
  byte bVar2;
  ushort uVar3;
  undefined *puVar4;
  char *pcVar5;
  int iVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined uVar9;
  ushort uVar10;
  uint uVar11;
  uint uVar12;
  ushort uVar13;
  short sVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  undefined *unaff_r4;
  undefined *puVar19;
  uint unaff_r5;
  undefined uVar20;
  undefined4 unaff_r6;
  undefined uVar21;
  undefined4 unaff_r7;
  uint uVar22;
  ushort *puVar23;
  uint uVar24;
  int iVar25;
  code *in_lr;
  bool bVar26;
  bool bVar27;
  code **ppcVar28;
  undefined uVar29;
  code *UNRECOVERED_JUMPTABLE;
  
  ppcVar28 = (code **)&stack0xffffffd8;

  UNRECOVERED_JUMPTABLE = in_lr;

  tp_i2c_read_status();             //Scan the touch panel

  uVar12 = DAT_8001bc08;            //0x000002E3
  puVar19 = PTR_DAT_8001bc04;       //0x80192f08    ==> Touch state byte
  puVar4 = PTR_DAT_8001bc00;        //0x80192f02    ==> Have touch indicator
  uVar29 = (undefined)unaff_r7;
  uVar9 = (undefined)unaff_r6;

  if (*PTR_DAT_8001bc00 == '\0')   //0x80192f02  Have touch indicator
  {
    return;                        //Done if no touch
  }

  //Start processing when there is touch
  uVar10 = *(ushort *)(PTR_DAT_8001bc00 + 2);  //0x80192f04    x coord
  *(ushort *)(PTR_DAT_8001bc04 + 2) = uVar10;  //0x80192f0a = x coord
  uVar13 = *(ushort *)(puVar4 + 4);            //0x80192f06    y coord

  uVar11 = (uint)uVar13;                       //y coord

  bVar27 = uVar10 - 1 <= uVar12;               //(x coord - 1) <= 0x02E3 (739) Flag to signal x not in right menu field ?? 

  bVar26 = uVar12 == uVar10 - 1;               //flag to signal x coord - 1 on 739

  *(ushort *)(puVar19 + 4) = uVar13;           //0x80192f0c = y coord

  if (bVar27 && !bVar26)                       //When x in range of top menu
  {
    bVar27 = 0x2e < uVar11;                    //46 less then y coord. So not in top menu
    bVar26 = uVar11 == 0x2f;                   //y coord is 47 so on top line indicator
  }

  *(ushort *)(puVar19 + 0x32) = uVar10;        //0x80192f08 + 0x32 = x coord

  if (bVar27 && !bVar26)                       //When not in top menu or on top line
  {
    unaff_r5 = DAT_8001bc0c;                   //0x000001DE  end of y on screen
  }

  *(ushort *)(puVar19 + 0x34) = uVar13;        //0x80192f08 + 0x34 = y coord
  *(ushort *)(puVar19 + 0x2e) = uVar10;        //0x80192f08 + 0x2E = x coord

  if (bVar27 && !bVar26)                       //Not on top line or top menu
  {
    bVar27 = uVar11 <= unaff_r5;               //y coord less then or equal to end of screen
    bVar26 = unaff_r5 == uVar11;               //y coord equal to end of screen
  }

  *(ushort *)(puVar19 + 0x30) = uVar13;        //0x80192f08 + 0x30 = y coord

  if (!bVar27 || bVar26)                       //In top menu range
  {
    *puVar19 = 0;                              //Clear touch states
    puVar19[1] = 0;                            //0x80192f08 and 0x80192f09


//FUN_8001dabc
    set_frame_to_global_pointer();             //Prepare for drawing in separate screen buffer

    tp_i2c_read_status();                      //Scan the touch panel again

    uVar12 = DAT_8001e9c0;                     //0x0000012A Some coordinate
    pcVar5 = DAT_8001e9bc;                     //0x8019D5A0 Scope settings
    iVar25 = DAT_8001e9b8;                     //0x801FA24C Measures settings
    puVar4 = PTR_DAT_8001e9b4;                 //0x80192f02 Touch data
    uVar11 = (uint)*(ushort *)(PTR_DAT_8001e9b4 + 2);  //Y touch

    //X coord less then 80 and y coord less then 42
    if ((uVar11 - 1 < 0x4f) && (*(ushort *)(PTR_DAT_8001e9b4 + 4) != 0 && *(ushort *)(PTR_DAT_8001e9b4 + 4) < 0x2a))
    {
      cVar1 = *PTR_DAT_8001e9b4;  //0x80192f02  Have touch

      if (DAT_8001e9bc[0x43] == '\0')  //Wave view mode state variable. 0 is normal view, > 0  is wave view
      {
        //As long as there is touch keep displaying the inverted menu button
        while (cVar1 != '\0')
        {
          display_menu_button(1);
          tp_i2c_read_status();
          cVar1 = *puVar4;
        }

        //Release the button
        display_menu_button(0);

        //go display the menu???
        FUN_80029158();             //Setup main menu (slide open)

        tp_i2c_read_status();

        cVar1 = *puVar4;

        while (cVar1 != '\0')
        {
          tp_i2c_read_status();
          cVar1 = *puVar4;
        }
      }
      else
      {
        while (cVar1 != '\0')
        {
          display_return_arrow_symbol(1);
          tp_i2c_read_status();
          cVar1 = *puVar4;
        }

        display_return_arrow_symbol(0);

        pcVar5[0x43] = '\0';                 //Wave view mode state

        tp_i2c_read_status();

        cVar1 = *puVar4;

        while (cVar1 != '\0')
        {
          tp_i2c_read_status();
          cVar1 = *puVar4;
        }
      }
    }
    else
    {
//pa:0x8001b6e0
      //if x coord > 162 and < 265 and y coord less then 61???
      if ((uVar11 - 0xa2 < 0x67) && (*(ushort *)(PTR_DAT_8001e9b4 + 4) != 0 && *(ushort *)(PTR_DAT_8001e9b4 + 4) < 0x3d))
      {
        cVar1 = *PTR_DAT_8001e9b4;

        while (cVar1 != '\0')
        {
          display_ch1_settings(1);
          tp_i2c_read_status();
          cVar1 = *puVar4;
        }

        display_ch1_settings(0);

        //setup channel 1 menu
        FUN_80021c3c();               //Most likely this function slides the menu onto the screen. So need to figure out how this is done

LAB_8001dc04:
        do
        {
          tp_i2c_read_status();
          uVar11 = (uint)*(ushort *)(puVar4 + 2);

          if (uVar11 - 0xa2 < 0xb6)   //Check the xrange
          {
            uVar15 = (uint)*(ushort *)(puVar4 + 4);  //Get the y pos
            bVar27 = 0x2d < uVar15;
            bVar26 = uVar15 == 0x2e;

            if (0x2e < uVar15)
            {
              bVar27 = uVar15 <= uVar12;
              bVar26 = uVar12 == uVar15;
            }

            if (bVar27 && !bVar26)
            {
              uVar16 = uVar11 - 0xdc;

              if (((uVar16 < 0x3b) && (0x30 < uVar15)) && (uVar15 < 0x6a))
              {
                if (*puVar4 != '\0')           //Do we have touch
                {
                  *pcVar5 = '\x01';            //This is for channel 1 enable
                  display_channel1_menu();

                  FUN_80002790();              //Hardware enable of the channel????

                  tp_i2c_read_status();
                  cVar1 = *puVar4;

                  while (cVar1 != '\0')
                  {
                    tp_i2c_read_status();
                    cVar1 = *puVar4;
                  }
                }
              }
              else
              {
                uVar18 = uVar11 - 0x11a;
                if (((uVar18 < 0x3a) && (0x31 < uVar15)) && (uVar15 < 0x6b))
                {
                  if (*puVar4 != '\0')
                  {
                    *pcVar5 = '\0';             //This is for channel 1 disable
                    display_channel1_menu();

                    FUN_80002790();

                    pcVar5[3] = '\0';           //Set volts per div back to highest input range

                    FUN_8000689c();

                    tp_i2c_read_status();
                    cVar1 = *puVar4;
                    while (cVar1 != '\0') {
                      tp_i2c_read_status();
                      cVar1 = *puVar4;
                    }
                  }
                }
                else {
                  if (((uVar16 < 0x3b) && (0x6f < uVar15)) && (uVar15 < 0xa9)) {
                    if (*puVar4 != '\0') {
                      pcVar5[4] = '\x01';
                      display_channel1_menu();
                      tp_i2c_read_status();
                      cVar1 = *puVar4;
                      while (cVar1 != '\0') {
                        tp_i2c_read_status();
                        cVar1 = *puVar4;
                      }
                    }
                  }
                  else {
                    if (((uVar18 < 0x3a) && (0x6f < uVar15)) && (uVar15 < 0xa9)) {
                      if (*puVar4 != '\0') {
                        pcVar5[4] = '\0';
                        display_channel1_menu();
                        tp_i2c_read_status();
                        cVar1 = *puVar4;
                        while (cVar1 != '\0') {
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                        }
                      }
                    }
                    else {
                      if (((uVar16 < 0x3b) && (0xad < uVar15)) && (uVar15 < 0xe7)) {
                        if (*puVar4 != '\0') {
                          pcVar5[1] = '\0';

                          FUN_800068d4();    //Change coupling
                          display_channel1_menu();
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                          while (cVar1 != '\0') {
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                          }
                        }
                      }
                      else {
                        if (((uVar18 < 0x3a) && (0xad < uVar15)) && (uVar15 < 0xe7)) {
                          if (*puVar4 != '\0') {
                            pcVar5[1] = '\x01';

                            FUN_800068d4();
                            display_channel1_menu();
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                            while (cVar1 != '\0') {
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                            }
                          }
                        }
                        else {
                          if (((uVar11 - 0xe6 < 0x22) && (0xeb < uVar15)) && (uVar15 < 0x125)) {
                            if (*puVar4 != '\0') {
                              pcVar5[2] = '\0';
                              display_channel1_menu();
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                              while (cVar1 != '\0') {
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                              }
                            }
                          }
                          else {
                            if (((uVar11 - 0x108 < 0x20) && (0xeb < uVar15)) && (uVar15 < 0x125)) {
                              if (*puVar4 != '\0') {
                                pcVar5[2] = '\x01';
                                display_channel1_menu();
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                                while (cVar1 != '\0') {
                                  tp_i2c_read_status();
                                  cVar1 = *puVar4;
                                }
                              }
                            }
                            else {
                              if (((uVar11 - 0x129 < 0x20) && (0xeb < uVar15)) &&
                                 ((uVar15 < 0x125 && (*puVar4 != '\0')))) {
                                pcVar5[2] = '\x02';
                                display_channel1_menu();
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                                while (cVar1 != '\0') {
                                  tp_i2c_read_status();
                                  cVar1 = *puVar4;
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
              goto LAB_8001dc04;
            }
          }
        } while (*puVar4 == '\0');

        FUN_8000a6c0();  //Copy saved screen rect back to the screen


        tp_i2c_read_status();
        cVar1 = *puVar4;
        while (cVar1 != '\0') {
          tp_i2c_read_status();
          cVar1 = *puVar4;
        }
      }
      else
      {
        if ((uVar11 - 0x121 < 0x67) && (*(ushort *)(PTR_DAT_8001e9b4 + 4) != 0 && *(ushort *)(PTR_DAT_8001e9b4 + 4) < 0x3d))
        {
          cVar1 = *PTR_DAT_8001e9b4;

          while (cVar1 != '\0')
          {
            display_ch2_settings(1);
            tp_i2c_read_status();
            cVar1 = *puVar4;
          }

          display_ch2_settings(0);

          FUN_80021d14();

LAB_8001dfb0:
          do {
            tp_i2c_read_status();
            uVar11 = (uint)*(ushort *)(puVar4 + 2);
            if (uVar11 - 0x121 < 0xb6) {
              uVar15 = (uint)*(ushort *)(puVar4 + 4);
              bVar27 = 0x2d < uVar15;
              bVar26 = uVar15 == 0x2e;
              if (0x2e < uVar15) {
                bVar27 = uVar15 <= uVar12;
                bVar26 = uVar12 == uVar15;
              }
              if (bVar27 && !bVar26) {
                uVar16 = uVar11 - 0x15b;
                if (((uVar16 < 0x3b) && (0x31 < uVar15)) && (uVar15 < 0x6b)) {
                  if (*puVar4 != '\0') {
                    pcVar5[0xc] = '\x01';
                    display_channel2_menu();

                    FUN_80002790();
                    tp_i2c_read_status();
                    cVar1 = *puVar4;
                    while (cVar1 != '\0') {
                      tp_i2c_read_status();
                      cVar1 = *puVar4;
                    }
                  }
                }
                else {
                  uVar18 = uVar11 - 0x199;
                  if (((uVar18 < 0x3a) && (0x31 < uVar15)) && (uVar15 < 0x6b)) {
                    if (*puVar4 != '\0') {
                      pcVar5[0xc] = '\0';
                      display_channel2_menu();
                      FUN_80002790();

                      pcVar5[0xf] = '\0';

                      FUN_800095e8();

                      tp_i2c_read_status();
                      cVar1 = *puVar4;
                      while (cVar1 != '\0') {
                        tp_i2c_read_status();
                        cVar1 = *puVar4;
                      }
                    }
                  }
                  else {
                    if (((uVar16 < 0x3b) && (0x6f < uVar15)) && (uVar15 < 0xa9)) {
                      if (*puVar4 != '\0') {
                        pcVar5[0x10] = '\x01';
                        display_channel2_menu();
                        tp_i2c_read_status();
                        cVar1 = *puVar4;
                        while (cVar1 != '\0') {
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                        }
                      }
                    }
                    else {
                      if (((uVar18 < 0x3a) && (0x6f < uVar15)) && (uVar15 < 0xa9)) {
                        if (*puVar4 != '\0') {
                          pcVar5[0x10] = '\0';
                          display_channel2_menu();
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                          while (cVar1 != '\0') {
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                          }
                        }
                      }
                      else {
                        if (((uVar16 < 0x3b) && (0xad < uVar15)) && (uVar15 < 0xe7)) {
                          if (*puVar4 != '\0') {
                            pcVar5[0xd] = '\0';
                            FUN_80009620();
                            display_channel2_menu();
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                            while (cVar1 != '\0') {
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                            }
                          }
                        }
                        else {
                          if (((uVar18 < 0x3a) && (0xad < uVar15)) && (uVar15 < 0xe7)) {
                            if (*puVar4 != '\0') {
                              pcVar5[0xd] = '\x01';       //Channel 2 coupling
                              FUN_80009620();
                              display_channel2_menu();
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                              while (cVar1 != '\0') {
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                              }
                            }
                          }
                          else {
                            if (((uVar11 - 0x165 < 0x22) && (0xeb < uVar15)) && (uVar15 < 0x125)) {
                              if (*puVar4 != '\0') {
                                pcVar5[0xe] = '\0';
                                display_channel2_menu();
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                                while (cVar1 != '\0') {
                                  tp_i2c_read_status();
                                  cVar1 = *puVar4;
                                }
                              }
                            }
                            else {
                              if (((uVar11 - 0x187 < 0x20) && (0xeb < uVar15)) && (uVar15 < 0x125))
                              {
                                if (*puVar4 != '\0') {
                                  pcVar5[0xe] = '\x01';
                                  display_channel2_menu();
                                  tp_i2c_read_status();
                                  cVar1 = *puVar4;
                                  while (cVar1 != '\0') {
                                    tp_i2c_read_status();
                                    cVar1 = *puVar4;
                                  }
                                }
                              }
                              else {
                                if (((uVar11 - 0x1a8 < 0x20) && (0xeb < uVar15)) &&
                                   ((uVar15 < 0x125 && (*puVar4 != '\0')))) {
                                  pcVar5[0xe] = '\x02';
                                  display_channel2_menu();
                                  tp_i2c_read_status();
                                  cVar1 = *puVar4;
                                  while (cVar1 != '\0') {
                                    tp_i2c_read_status();
                                    cVar1 = *puVar4;
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
                goto LAB_8001dfb0;
              }
            }
          } while (*puVar4 == '\0');
          FUN_8000a6e8();
          tp_i2c_read_status();
          cVar1 = *puVar4;
          while (cVar1 != '\0') {
            tp_i2c_read_status();
            cVar1 = *puVar4;
          }
        }
        else 
        {
          if ((uVar11 - 0x1f1 < 0x2c) && (*(ushort *)(PTR_DAT_8001e9b4 + 4) != 0 && *(ushort *)(PTR_DAT_8001e9b4 + 4) < 0x3c))
          {
            cVar1 = *PTR_DAT_8001e9b4;
            while (cVar1 != '\0') {
              display_move_speed(1);
              tp_i2c_read_status();
              cVar1 = *puVar4;
            }
            if (pcVar5[0x16] == '\0') {
              pcVar5[0x16] = '\x01';
            }
            else {
              pcVar5[0x16] = '\0';
            }
            display_move_speed(0);
            tp_i2c_read_status();
            cVar1 = *puVar4;
            while (cVar1 != '\0') {
              tp_i2c_read_status();
              cVar1 = *puVar4;
            }
          }
          else 
          {
            if ((uVar11 - 0x23b < 0x77) && (*(ushort *)(PTR_DAT_8001e9b4 + 4) != 0 && *(ushort *)(PTR_DAT_8001e9b4 + 4) < 0x3c))
            {
              if (DAT_8001e9bc[0x43] == '\0')
              {
                cVar1 = *PTR_DAT_8001e9b4;
                while (cVar1 != '\0')
                {
                  display_trigger_settings(1);
                  tp_i2c_read_status();
                  cVar1 = *puVar4;
                }

                display_trigger_settings(0);

                FUN_80021e1c();   //Setup_trigger_menu (slide open)

                do
                {
                  while( true )
                  {
                    tp_i2c_read_status();
                    uVar12 = (uint)*(ushort *)(puVar4 + 2);
                    if (((0xaa < uVar12 - 0x230) || (uVar10 = *(ushort *)(puVar4 + 4), uVar10 < 0x2f)) || (0xe7 < uVar10))
                      break;

                    if (((uVar12 - 0x26e < 0x1e) && (0x30 < uVar10)) && (uVar10 < 0x6a))
                    {
                      if (*puVar4 != '\0')
                      {
                        pcVar5[0x21] = '\0';    //Trigger mode auto
                        FUN_80026828();         //Set FPGA trigger mode
                        display_trigger_menu();

                        pcVar5[0x3a] = '\0';    //Scope run state

                        pcVar5[0x18] = '\x01';
                        pcVar5[0x17] = '\x01';

                        display_run_stop_text((uint)(byte)pcVar5[0x3a]);
                        tp_i2c_read_status();
                        cVar1 = *puVar4;
                        while (cVar1 != '\0') {
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                        }
                      }
                    }
                    else {
                      if (((uVar12 - 0x28e < 0x2a) && (0x30 < uVar10)) && (uVar10 < 0x6a)) {
                        if (*puVar4 != '\0') {
                          pcVar5[0x21] = '\x01';  //Single

                          pcVar5[0x3a] = '\0';
                          pcVar5[0x36] = '\0';
                          pcVar5[0x37] = '\x01';

                          FUN_80026828();
                          display_trigger_menu();

                          display_run_stop_text((uint)(byte)pcVar5[0x3a]);

                          if ((byte)pcVar5[10] < 0xb) {     //Time base change when less then 11 (below 5ms/div ??)
                            pcVar5[10] = '\v';  //Make it 11
                            FUN_800266c4();       //Translate a parameter and write to fpga
                            display_time_div_setting();
                          }
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                          while (cVar1 != '\0') {
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                          }
                        }
                      }
                      else {
                        if (((uVar12 - 0x2b9 < 0x1f) && (0x30 < uVar10)) && (uVar10 < 0x6a)) {
                          if (*puVar4 != '\0')
                          {
                            pcVar5[0x21] = '\x02';   //Normal

                            FUN_80026828();

                            display_trigger_menu();
                            pcVar5[0x3a] = '\0';

                            display_run_stop_text((uint)(byte)pcVar5[0x3a]);

                            pcVar5[0x36] = '\0';
                            pcVar5[0x37] = '\x01';

                            if ((byte)pcVar5[10] < 0xb)
                            {
                              pcVar5[10] = '\v';
                              FUN_800266c4();
                              display_time_div_setting();
                            }
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                            while (cVar1 != '\0') {
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                            }
                          }
                        }
                        else   //Trigger edge
                        {
                          if (((uVar12 - 0x268 < 0x35) && (0x6e < uVar10)) && (uVar10 < 0xa8)) {
                            if (*puVar4 != '\0') {
                              pcVar5[0x22] = '\0';
                              FUN_80026808();            //Trigger edge
                              display_trigger_menu();
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                              while (cVar1 != '\0') {
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                              }
                            }
                          }
                          else {
                            if (((uVar12 - 0x29e < 0x34) && (0x6e < uVar10)) && (uVar10 < 0xa8)) {
                              if (*puVar4 != '\0') {
                                pcVar5[0x22] = '\x01';
                                FUN_80026808();
                                display_trigger_menu();
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                                while (cVar1 != '\0') {
                                  tp_i2c_read_status();
                                  cVar1 = *puVar4;
                                }
                              }
                            }
                            else
                            {
                              if (((uVar12 - 0x268 < 0x35) && (0xac < uVar10)) && (uVar10 < 0xe6)) {
                                if (*puVar4 != '\0') {
                                  if (*pcVar5 != '\0') {
                                    pcVar5[0x23] = '\0';
                                    FUN_800267e8();            //Trigger channel
                                    display_trigger_menu();
                                  }
                                  tp_i2c_read_status();
                                  cVar1 = *puVar4;
                                  while (cVar1 != '\0') {
                                    tp_i2c_read_status();
                                    cVar1 = *puVar4;
                                  }
                                }
                              }
                              else {
                                if (((uVar12 - 0x29e < 0x34) && (0xac < uVar10)) &&
                                   ((uVar10 < 0xe6 && (*puVar4 != '\0')))) {
                                  if (pcVar5[0xc] != '\0') {
                                    pcVar5[0x23] = '\x01';
                                    FUN_800267e8();
                                    display_trigger_menu();
                                  }
                                  tp_i2c_read_status();
                                  cVar1 = *puVar4;
                                  while (cVar1 != '\0') {
                                    tp_i2c_read_status();
                                    cVar1 = *puVar4;
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                } while (*puVar4 == '\0');
                FUN_8000a728();
                tp_i2c_read_status();
                cVar1 = *puVar4;
                while (cVar1 != '\0') {
                  tp_i2c_read_status();
                  cVar1 = *puVar4;
                }
              }
            }
            else 
            {
              if ((uVar11 - 0x2e5 < 0x3a) &&
                 (uVar10 = *(ushort *)(PTR_DAT_8001e9b4 + 4), 0x12f < uVar10)) {
                bVar26 = uVar10 == 0x164;
                if (uVar10 < 0x165) {
                  bVar26 = DAT_8001e9bc[0x42] == '\0';
                }
                if (bVar26) {
                  cVar1 = *PTR_DAT_8001e9b4;
                  while (cVar1 != '\0') {
                    display_measures_button(1);
                    tp_i2c_read_status();
                    cVar1 = *puVar4;
                  }
                  display_measures_button(0);
                  FUN_80021dec();
                  uVar12 = DAT_8001e9c4;
                  uVar15 = DAT_8001e9c4 - 0x15;
                  uVar11 = DAT_8001e9c4 - 0x92;
LAB_8001e7b0:
                  do
                  {
                    tp_i2c_read_status();
                    iVar6 = DAT_8001e9b8;    //0x801FA24C base address of settings
                    uVar16 = (uint)*(ushort *)(puVar4 + 2);
                    if (uVar16 - 0xe7 < uVar12) {
                      uVar18 = (uint)*(ushort *)(puVar4 + 4);
                      bVar26 = uVar18 == 0x108;
                      if (0x107 < uVar18) {
                        bVar26 = uVar15 == uVar18;
                      }
                      if ((0x107 < uVar18 && uVar18 <= uVar15) && !bVar26) {
                        uVar17 = uVar16 - 0x1e2;
                        if (((uVar17 < 0x3c) && (0x123 < uVar18)) && (uVar18 < 0x160)) {
                          if (*puVar4 != '\0')
                          {
                            if (*(char *)(iVar25 + 0x100) == '\0')
                            {
                              uVar16 = 0;
                              *(undefined *)(iVar25 + 0x100) = 1;

                              do  //Find an empty slot to be displayed on the screen
                              {
                                uVar17 = (uint)*(byte *)(iVar6 + uVar16);

                                if (uVar17 == 0)
                                {
                                  *(undefined *)(iVar6 + uVar16) = 1;
                                  break;
                                }

                                uVar16 = uVar16 + 1 & 0xff;
                              } while (uVar16 < 0x18);          //24 settings
                            }
                            else
                            {
                              *(undefined *)(iVar25 + 0x100) = 0;
                              FUN_8002177c(1);
                            }
                          }
                          highlight_measures_menu_items();
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                          while (cVar1 != '\0') {
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                          }
                        }
                        else {
                          uVar17 = uVar16 - 0x220;
                          if (((uVar17 < 0x3c) && (0x123 < uVar18)) && (uVar18 < 0x160)) {
                            if (*puVar4 != '\0') {
                              if (*(char *)(iVar25 + 0x112) == '\0')
                              {
                                uVar16 = 0;
                                *(undefined *)(iVar25 + 0x112) = 1;
                                do {
                                  uVar17 = (uint)*(byte *)(iVar6 + uVar16);
                                  if (uVar17 == 0) {
                                    *(undefined *)(iVar6 + uVar16) = 2;
                                    break;
                                  }
                                  uVar16 = uVar16 + 1 & 0xff;
                                } while (uVar16 < 0x18);
                              }
                              else
                              {
                                *(undefined *)(iVar25 + 0x112) = 0;
                                FUN_8002177c(2);
                              }
                            }
                            highlight_measures_menu_items();
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                            while (cVar1 != '\0') {
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                            }
                          }
                          else {
                            uVar17 = uVar16 - 0x25e;
                            if (((uVar17 < 0x3c) && (0x123 < uVar18)) && (uVar18 < 0x160)) {
                              if (*puVar4 != '\0') {
                                if (*(char *)(iVar25 + 0x122) == '\0') {
                                  uVar16 = 0;
                                  *(undefined *)(iVar25 + 0x122) = 1;
                                  do {
                                    uVar17 = (uint)*(byte *)(iVar6 + uVar16);
                                    if (uVar17 == 0) {
                                      *(undefined *)(iVar6 + uVar16) = 3;
                                      break;
                                    }
                                    uVar16 = uVar16 + 1 & 0xff;
                                  } while (uVar16 < 0x18);
                                }
                                else {
                                  *(undefined *)(iVar25 + 0x122) = 0;
                                  FUN_8002177c(3);
                                }
                              }
                              highlight_measures_menu_items();
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                              while (cVar1 != '\0') {
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                              }
                            }
                            else {
                              if (((uVar16 - 0x29c < 0x3c) && (0x123 < uVar18)) && (uVar18 < 0x160))
                              {
                                if (*puVar4 != '\0') {
                                  if (*(char *)(iVar25 + 0x132) == '\0') {
                                    uVar16 = 0;
                                    *(undefined *)(iVar25 + 0x132) = 1;
                                    do {
                                      uVar17 = (uint)*(byte *)(iVar6 + uVar16);
                                      if (uVar17 == 0) {
                                        *(undefined *)(iVar6 + uVar16) = 4;
                                        break;
                                      }
                                      uVar16 = uVar16 + 1 & 0xff;
                                    } while (uVar16 < 0x18);
                                  }
                                  else {
                                    *(undefined *)(iVar25 + 0x132) = 0;
                                    FUN_8002177c(4);
                                  }
                                }
                                highlight_measures_menu_items();
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                                while (cVar1 != '\0') {
                                  tp_i2c_read_status();
                                  cVar1 = *puVar4;
                                }
                              }
                            }
                          }
                        }
                        iVar6 = DAT_8001e9b8;
                        uVar18 = (uint)*(ushort *)(puVar4 + 2);
                        uVar16 = uVar18 - 0x1e2;
                        bVar26 = 0x3b < uVar16;
                        if (!bVar26) {
                          uVar16 = (uint)*(ushort *)(puVar4 + 4);
                        }
                        if (!bVar26 && uVar16 > uVar11) {
                          uVar17 = DAT_8001f98c;
                        }
                        if ((bVar26 || uVar16 <= uVar11) || uVar17 <= uVar16) {
                          uVar16 = uVar18 - 0x220;
                          bVar26 = 0x3b < uVar16;
                          if (!bVar26) {
                            uVar16 = (uint)*(ushort *)(puVar4 + 4);
                          }
                          if (!bVar26 && uVar16 > uVar11) {
                            uVar17 = DAT_8001f98c;
                          }
                          if ((bVar26 || uVar16 <= uVar11) || uVar17 <= uVar16) {
                            uVar16 = uVar18 - 0x25e;
                            bVar26 = 0x3b < uVar16;
                            if (!bVar26) {
                              uVar16 = (uint)*(ushort *)(puVar4 + 4);
                            }
                            if (!bVar26 && uVar16 > uVar11) {
                              uVar17 = DAT_8001f98c;
                            }
                            if ((bVar26 || uVar16 <= uVar11) || uVar17 <= uVar16) {
                              uVar18 = uVar18 - 0x29c;
                              bVar26 = uVar18 < 0x3c;
                              if (bVar26) {
                                uVar18 = (uint)*(ushort *)(puVar4 + 4);
                              }
                              if (bVar26 && uVar11 < uVar18) {
                                uVar16 = DAT_8001f98c;
                              }
                              if ((bVar26 && uVar11 < uVar18) && uVar18 < uVar16) {
                                if (*puVar4 != '\0') {
                                  if (*(char *)(iVar25 + 0x172) == '\0') {
                                    uVar16 = 0;
                                    *(undefined *)(iVar25 + 0x172) = 1;
                                    do {
                                      uVar17 = (uint)*(byte *)(iVar6 + uVar16);
                                      if (uVar17 == 0) {
                                        *(undefined *)(iVar6 + uVar16) = 8;
                                        break;
                                      }
                                      uVar16 = uVar16 + 1 & 0xff;
                                    } while (uVar16 < 0x18);
                                  }
                                  else {
                                    *(undefined *)(iVar25 + 0x172) = 0;
                                    FUN_8002177c(8);
                                  }
                                }
                                highlight_measures_menu_items();
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                                while (cVar1 != '\0') {
                                  tp_i2c_read_status();
                                  cVar1 = *puVar4;
                                }
                              }
                            }
                            else {
                              if (*puVar4 != '\0') {
                                if (*(char *)(iVar25 + 0x162) == '\0') {
                                  uVar16 = 0;
                                  *(undefined *)(iVar25 + 0x162) = 1;
                                  do {
                                    uVar17 = (uint)*(byte *)(iVar6 + uVar16);
                                    if (uVar17 == 0) {
                                      *(undefined *)(iVar6 + uVar16) = 7;
                                      break;
                                    }
                                    uVar16 = uVar16 + 1 & 0xff;
                                  } while (uVar16 < 0x18);
                                }
                                else {
                                  *(undefined *)(iVar25 + 0x162) = 0;
                                  FUN_8002177c(7);
                                }
                              }
                              highlight_measures_menu_items();
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                              while (cVar1 != '\0') {
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                              }
                            }
                          }
                          else {
                            if (*puVar4 != '\0') {
                              if (*(char *)(iVar25 + 0x152) == '\0') {
                                uVar16 = 0;
                                *(undefined *)(iVar25 + 0x152) = 1;
                                do {
                                  uVar17 = (uint)*(byte *)(iVar6 + uVar16);
                                  if (uVar17 == 0) {
                                    *(undefined *)(iVar6 + uVar16) = 6;
                                    break;
                                  }
                                  uVar16 = uVar16 + 1 & 0xff;
                                } while (uVar16 < 0x18);
                              }
                              else {
                                *(undefined *)(iVar25 + 0x152) = 0;
                                FUN_8002177c(6);
                              }
                            }
                            highlight_measures_menu_items();
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                            while (cVar1 != '\0') {
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                            }
                          }
                        }
                        else {
                          if (*puVar4 != '\0') {
                            if (*(char *)(iVar25 + 0x142) == '\0') {
                              uVar16 = 0;
                              *(undefined *)(iVar25 + 0x142) = 1;
                              do {
                                uVar17 = (uint)*(byte *)(iVar6 + uVar16);
                                if (uVar17 == 0) {
                                  *(undefined *)(iVar6 + uVar16) = 5;
                                  break;
                                }
                                uVar16 = uVar16 + 1 & 0xff;
                              } while (uVar16 < 0x18);
                            }
                            else {
                              *(undefined *)(iVar25 + 0x142) = 0;
                              FUN_8002177c(5);
                            }
                          }
                          highlight_measures_menu_items();
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                          while (cVar1 != '\0') {
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                          }
                        }
                        iVar6 = DAT_8001e9b8;
                        uVar16 = (uint)*(ushort *)(puVar4 + 2);
                        if (((uVar16 - 0x1e2 < 0x3c) && (0x19f < *(ushort *)(puVar4 + 4))) &&
                           (*(ushort *)(puVar4 + 4) < 0x1dc)) {
                          if (*puVar4 != '\0') {
                            if (*(char *)(iVar25 + 0x182) == '\0') {
                              uVar16 = 0;
                              *(undefined *)(iVar25 + 0x182) = 1;
                              do {
                                uVar17 = (uint)*(byte *)(iVar6 + uVar16);
                                if (uVar17 == 0) {
                                  *(undefined *)(iVar6 + uVar16) = 9;
                                  break;
                                }
                                uVar16 = uVar16 + 1 & 0xff;
                              } while (uVar16 < 0x18);
                            }
                            else {
                              *(undefined *)(iVar25 + 0x182) = 0;
                              FUN_8002177c(9);
                            }
                          }
                          highlight_measures_menu_items();
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                          while (cVar1 != '\0') {
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                          }
                        }
                        else {
                          if (((uVar16 - 0x220 < 0x3c) && (0x19f < *(ushort *)(puVar4 + 4))) &&
                             (*(ushort *)(puVar4 + 4) < 0x1dc)) {
                            if (*puVar4 != '\0') {
                              if (*(char *)(iVar25 + 0x192) == '\0') {
                                uVar16 = 0;
                                *(undefined *)(iVar25 + 0x192) = 1;
                                do {
                                  uVar17 = (uint)*(byte *)(iVar6 + uVar16);
                                  if (uVar17 == 0) {
                                    *(undefined *)(iVar6 + uVar16) = 10;
                                    break;
                                  }
                                  uVar16 = uVar16 + 1 & 0xff;
                                } while (uVar16 < 0x18);
                              }
                              else {
                                *(undefined *)(iVar25 + 0x192) = 0;
                                FUN_8002177c(10);
                              }
                            }
                            highlight_measures_menu_items();
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                            while (cVar1 != '\0') {
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                            }
                          }
                          else {
                            if (((uVar16 - 0x25e < 0x3c) && (0x19f < *(ushort *)(puVar4 + 4))) &&
                               (*(ushort *)(puVar4 + 4) < 0x1dc)) {
                              if (*puVar4 != '\0') {
                                if (*(char *)(iVar25 + 0x1a2) == '\0') {
                                  uVar16 = 0;
                                  *(undefined *)(iVar25 + 0x1a2) = 1;
                                  do {
                                    uVar17 = (uint)*(byte *)(iVar6 + uVar16);
                                    if (uVar17 == 0) {
                                      *(undefined *)(iVar6 + uVar16) = 0xb;
                                      break;
                                    }
                                    uVar16 = uVar16 + 1 & 0xff;
                                  } while (uVar16 < 0x18);
                                }
                                else {
                                  *(undefined *)(iVar25 + 0x1a2) = 0;
                                  FUN_8002177c(0xb);
                                }
                              }
                              highlight_measures_menu_items();
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                              while (cVar1 != '\0') {
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                              }
                            }
                            else {
                              if (((uVar16 - 0x29c < 0x3c) && (0x19f < *(ushort *)(puVar4 + 4))) &&
                                 (*(ushort *)(puVar4 + 4) < 0x1dc)) {
                                if (*puVar4 != '\0') {
                                  if (*(char *)(iVar25 + 0x1b2) == '\0') {
                                    uVar16 = 0;
                                    *(undefined *)(iVar25 + 0x1b2) = 1;
                                    do {
                                      uVar17 = (uint)*(byte *)(iVar6 + uVar16);
                                      if (uVar17 == 0) {
                                        *(undefined *)(iVar6 + uVar16) = 0xc;
                                        break;
                                      }
                                      uVar16 = uVar16 + 1 & 0xff;
                                    } while (uVar16 < 0x18);
                                  }
                                  else {
                                    *(undefined *)(iVar25 + 0x1b2) = 0;
                                    FUN_8002177c(0xc);
                                  }
                                }
                                highlight_measures_menu_items();
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                                while (cVar1 != '\0') {
                                  tp_i2c_read_status();
                                  cVar1 = *puVar4;
                                }
                              }
                            }
                          }
                        }
                        iVar6 = DAT_8001e9b8;
                        uVar16 = (uint)*(ushort *)(puVar4 + 2);
                        if (((uVar16 - 0xe9 < 0x3c) && (0x123 < *(ushort *)(puVar4 + 4))) &&
                           (*(ushort *)(puVar4 + 4) < 0x160)) {
                          if (*puVar4 != '\0') {
                            if (*(char *)(iVar25 + 0x1c2) == '\0') {
                              uVar16 = 0;
                              *(undefined *)(iVar25 + 0x1c2) = 1;
                              do {
                                uVar17 = (uint)*(byte *)(iVar6 + uVar16);
                                if (uVar17 == 0) {
                                  *(undefined *)(iVar6 + uVar16) = 0xd;
                                  break;
                                }
                                uVar16 = uVar16 + 1 & 0xff;
                              } while (uVar16 < 0x18);
                            }
                            else {
                              *(undefined *)(iVar25 + 0x1c2) = 0;
                              FUN_8002177c(0xd);
                            }
                          }
                          highlight_measures_menu_items();
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                          while (cVar1 != '\0') {
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                          }
                        }
                        else {
                          if (((uVar16 - 0x127 < 0x3c) && (0x123 < *(ushort *)(puVar4 + 4))) &&
                             (*(ushort *)(puVar4 + 4) < 0x160)) {
                            if (*puVar4 != '\0') {
                              if (*(char *)(iVar25 + 0x1d2) == '\0') {
                                uVar16 = 0;
                                *(undefined *)(iVar25 + 0x1d2) = 1;
                                do {
                                  uVar17 = (uint)*(byte *)(iVar6 + uVar16);
                                  if (uVar17 == 0) {
                                    *(undefined *)(iVar6 + uVar16) = 0xe;
                                    break;
                                  }
                                  uVar16 = uVar16 + 1 & 0xff;
                                } while (uVar16 < 0x18);
                              }
                              else {
                                *(undefined *)(iVar25 + 0x1d2) = 0;
                                FUN_8002177c(0xe);
                              }
                            }
                            highlight_measures_menu_items();
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                            while (cVar1 != '\0') {
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                            }
                          }
                          else {
                            if (((uVar16 - 0x165 < 0x3c) && (0x123 < *(ushort *)(puVar4 + 4))) &&
                               (*(ushort *)(puVar4 + 4) < 0x160)) {
                              if (*puVar4 != '\0') {
                                if (*(char *)(iVar25 + 0x1e2) == '\0') {
                                  uVar16 = 0;
                                  *(undefined *)(iVar25 + 0x1e2) = 1;
                                  do {
                                    uVar17 = (uint)*(byte *)(iVar6 + uVar16);
                                    if (uVar17 == 0) {
                                      *(undefined *)(iVar6 + uVar16) = 0xf;
                                      break;
                                    }
                                    uVar16 = uVar16 + 1 & 0xff;
                                  } while (uVar16 < 0x18);
                                }
                                else {
                                  *(undefined *)(iVar25 + 0x1e2) = 0;
                                  FUN_8002177c(0xf);
                                }
                              }
                              highlight_measures_menu_items();
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                              while (cVar1 != '\0') {
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                              }
                            }
                            else {
                              if (((uVar16 - 0x1a3 < 0x3c) && (0x123 < *(ushort *)(puVar4 + 4))) &&
                                 (*(ushort *)(puVar4 + 4) < 0x160)) {
                                if (*puVar4 != '\0') {
                                  if (*(char *)(iVar25 + 0x1f2) == '\0') {
                                    uVar16 = 0;
                                    *(undefined *)(iVar25 + 0x1f2) = 1;
                                    do {
                                      uVar17 = (uint)*(byte *)(iVar6 + uVar16);
                                      if (uVar17 == 0) {
                                        *(undefined *)(iVar6 + uVar16) = 0x10;
                                        break;
                                      }
                                      uVar16 = uVar16 + 1 & 0xff;
                                    } while (uVar16 < 0x18);
                                  }
                                  else {
                                    *(undefined *)(iVar25 + 0x1f2) = 0;
                                    FUN_8002177c(0x10);
                                  }
                                }
                                highlight_measures_menu_items();
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                                while (cVar1 != '\0') {
                                  tp_i2c_read_status();
                                  cVar1 = *puVar4;
                                }
                              }
                            }
                          }
                        }
                        iVar6 = DAT_8001e9b8;
                        uVar18 = (uint)*(ushort *)(puVar4 + 2);
                        uVar16 = uVar18 - 0xe9;
                        bVar26 = 0x3b < uVar16;
                        if (!bVar26) {
                          uVar16 = (uint)*(ushort *)(puVar4 + 4);
                        }
                        if (!bVar26 && uVar16 > uVar11) {
                          uVar17 = DAT_8001f98c;
                        }
                        if ((bVar26 || uVar16 <= uVar11) || uVar17 <= uVar16) {
                          uVar16 = uVar18 - 0x127;
                          bVar26 = 0x3b < uVar16;
                          if (!bVar26) {
                            uVar16 = (uint)*(ushort *)(puVar4 + 4);
                          }
                          if (!bVar26 && uVar16 > uVar11) {
                            uVar17 = DAT_8001f98c;
                          }
                          if ((bVar26 || uVar16 <= uVar11) || uVar17 <= uVar16) {
                            uVar16 = uVar18 - 0x165;
                            bVar26 = 0x3b < uVar16;
                            if (!bVar26) {
                              uVar16 = (uint)*(ushort *)(puVar4 + 4);
                            }
                            if (!bVar26 && uVar16 > uVar11) {
                              uVar17 = DAT_8001f98c;
                            }
                            if ((bVar26 || uVar16 <= uVar11) || uVar17 <= uVar16) {
                              uVar18 = uVar18 - 0x1a3;
                              bVar26 = uVar18 < 0x3c;
                              if (bVar26) {
                                uVar18 = (uint)*(ushort *)(puVar4 + 4);
                              }
                              if (bVar26 && uVar11 < uVar18) {
                                uVar16 = DAT_8001f98c;
                              }
                              if ((bVar26 && uVar11 < uVar18) && uVar18 < uVar16) {
                                if (*puVar4 != '\0') {
                                  if (*(char *)(iVar25 + 0x242) == '\0') {
                                    uVar16 = 0;
                                    *(undefined *)(iVar25 + 0x242) = 1;
                                    do {
                                      if (*(char *)(iVar6 + uVar16) == '\0') {
                                        *(undefined *)(iVar6 + uVar16) = 0x14;
                                        break;
                                      }
                                      uVar16 = uVar16 + 1 & 0xff;
                                    } while (uVar16 < 0x18);
                                  }
                                  else {
                                    *(undefined *)(iVar25 + 0x242) = 0;
                                    FUN_8002177c(0x14);
                                  }
                                }
                                highlight_measures_menu_items();
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                                while (cVar1 != '\0') {
                                  tp_i2c_read_status();
                                  cVar1 = *puVar4;
                                }
                              }
                            }
                            else {
                              if (*puVar4 != '\0') {
                                if (*(char *)(iVar25 + 0x232) == '\0') {
                                  uVar16 = 0;
                                  *(undefined *)(iVar25 + 0x232) = 1;
                                  do {
                                    if (*(char *)(iVar6 + uVar16) == '\0') {
                                      *(undefined *)(iVar6 + uVar16) = 0x13;
                                      break;
                                    }
                                    uVar16 = uVar16 + 1 & 0xff;
                                  } while (uVar16 < 0x18);
                                }
                                else {
                                  *(undefined *)(iVar25 + 0x232) = 0;
                                  FUN_8002177c(0x13);
                                }
                              }
                              highlight_measures_menu_items();
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                              while (cVar1 != '\0') {
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                              }
                            }
                          }
                          else {
                            if (*puVar4 != '\0') {
                              if (*(char *)(iVar25 + 0x212) == '\0') {
                                uVar16 = 0;
                                *(undefined *)(iVar25 + 0x212) = 1;
                                do {
                                  if (*(char *)(iVar6 + uVar16) == '\0') {
                                    *(undefined *)(iVar6 + uVar16) = 0x12;
                                    break;
                                  }
                                  uVar16 = uVar16 + 1 & 0xff;
                                } while (uVar16 < 0x18);
                              }
                              else {
                                *(undefined *)(iVar25 + 0x212) = 0;
                                FUN_8002177c(0x12);
                              }
                            }
                            highlight_measures_menu_items();
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                            while (cVar1 != '\0') {
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                            }
                          }
                        }
                        else {
                          if (*puVar4 != '\0') {
                            if (*(char *)(iVar25 + 0x202) == '\0') {
                              uVar16 = 0;
                              *(undefined *)(iVar25 + 0x202) = 1;
                              do {
                                if (*(char *)(iVar6 + uVar16) == '\0') {
                                  *(undefined *)(iVar6 + uVar16) = 0x11;
                                  break;
                                }
                                uVar16 = uVar16 + 1 & 0xff;
                              } while (uVar16 < 0x18);
                            }
                            else {
                              *(undefined *)(iVar25 + 0x202) = 0;
                              FUN_8002177c(0x11);
                            }
                          }
                          highlight_measures_menu_items();
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                          while (cVar1 != '\0') {
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                          }
                        }
                        iVar6 = DAT_8001e9b8;
                        uVar16 = (uint)*(ushort *)(puVar4 + 2);
                        if (((uVar16 - 0xe9 < 0x3c) && (0x19f < *(ushort *)(puVar4 + 4))) &&
                           (*(ushort *)(puVar4 + 4) < 0x1dc)) {
                          if (*puVar4 != '\0') {
                            if (*(char *)(iVar25 + 0x252) == '\0') {
                              uVar16 = 0;
                              *(undefined *)(iVar25 + 0x252) = 1;
                              do {
                                if (*(char *)(iVar6 + uVar16) == '\0') {
                                  *(undefined *)(iVar6 + uVar16) = 0x15;
                                  break;
                                }
                                uVar16 = uVar16 + 1 & 0xff;
                              } while (uVar16 < 0x18);
                            }
                            else {
                              *(undefined *)(iVar25 + 0x252) = 0;
                              FUN_8002177c(0x15);
                            }
                          }
                          highlight_measures_menu_items();
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                          while (cVar1 != '\0') {
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                          }
                        }
                        else {
                          if (((uVar16 - 0x127 < 0x3c) && (0x19f < *(ushort *)(puVar4 + 4))) &&
                             (*(ushort *)(puVar4 + 4) < 0x1dc)) {
                            if (*puVar4 != '\0') {
                              if (*(char *)(iVar25 + 0x262) == '\0') {
                                uVar16 = 0;
                                *(undefined *)(iVar25 + 0x262) = 1;
                                do {
                                  if (*(char *)(iVar6 + uVar16) == '\0') {
                                    *(undefined *)(iVar6 + uVar16) = 0x16;
                                    break;
                                  }
                                  uVar16 = uVar16 + 1 & 0xff;
                                } while (uVar16 < 0x18);
                              }
                              else {
                                *(undefined *)(iVar25 + 0x262) = 0;
                                FUN_8002177c(0x16);
                              }
                            }
                            highlight_measures_menu_items();
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                            while (cVar1 != '\0') {
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                            }
                          }
                          else {
                            if (((uVar16 - 0x165 < 0x3c) && (0x19f < *(ushort *)(puVar4 + 4))) &&
                               (*(ushort *)(puVar4 + 4) < 0x1dc)) {
                              if (*puVar4 != '\0') {
                                if (*(char *)(iVar25 + 0x272) == '\0') {
                                  uVar16 = 0;
                                  *(undefined *)(iVar25 + 0x272) = 1;
                                  do {
                                    if (*(char *)(iVar6 + uVar16) == '\0') {
                                      *(undefined *)(iVar6 + uVar16) = 0x17;
                                      break;
                                    }
                                    uVar16 = uVar16 + 1 & 0xff;
                                  } while (uVar16 < 0x18);
                                }
                                else {
                                  *(undefined *)(iVar25 + 0x272) = 0;
                                  FUN_8002177c(0x17);
                                }
                              }
                              highlight_measures_menu_items();
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                              while (cVar1 != '\0') {
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                              }
                            }
                            else {
                              if (((uVar16 - 0x1a3 < 0x3c) && (0x19f < *(ushort *)(puVar4 + 4))) &&
                                 (*(ushort *)(puVar4 + 4) < 0x1dc)) {
                                if (*puVar4 != '\0') {
                                  if (*(char *)(iVar25 + 0x282) == '\0') {
                                    uVar16 = 0;
                                    *(undefined *)(iVar25 + 0x282) = 1;
                                    do {
                                      if (*(char *)(iVar6 + uVar16) == '\0') {
                                        *(undefined *)(iVar6 + uVar16) = 0x18;
                                        break;
                                      }
                                      uVar16 = uVar16 + 1 & 0xff;
                                    } while (uVar16 < 0x18);
                                  }
                                  else {
                                    *(undefined *)(iVar25 + 0x282) = 0;
                                    FUN_8002177c(0x18);
                                  }
                                }
                                highlight_measures_menu_items();
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                                while (cVar1 != '\0') {
                                  tp_i2c_read_status();
                                  cVar1 = *puVar4;
                                }
                              }
                            }
                          }
                        }
                        goto LAB_8001e7b0;
                      }
                    }
                  } while (*puVar4 == '\0');


                  FUN_8000a710();                  //Restore screen under menu
                  tp_i2c_read_status();
                  cVar1 = *puVar4;
                  while (cVar1 != '\0') {
                    tp_i2c_read_status();
                    cVar1 = *puVar4;
                  }
                }
              }
            }
          }
        }
      }
    }






    puVar8 = PTR_DAT_8001f998;     //0x80192ee4
    puVar7 = PTR_DAT_8001f994;     //0x80192ec8
    puVar19 = PTR_DAT_8001f990;    //0x80192ec6

    if (pcVar5[0x42] == '\0')      //0x8019D5A0 + 0x42 = right menu mode state = normal mode so not the volts/div adjustment
    {
      if (0x39 < *(ushort *)(puVar4 + 2) - 0x2e5) //Touch not in right menu range then return ((puVar4 + 2) = xtouch)
      {
        return;
      }

      uVar10 = *(ushort *)(puVar4 + 4);  //Get Y touch

      if ((3 < uVar10) && (uVar10 < 0x39))
      {
        cVar1 = *puVar4;
        while (cVar1 != '\0') {
          display_ctrl_button(1);
          tp_i2c_read_status();
          cVar1 = *puVar4;
        }
        display_ctrl_button(0);

        if (pcVar5[0x42] == '\0')
        {
          pcVar5[0x42] = '\x01';
        }
        else
        {
          pcVar5[0x42] = '\0';
        }

        display_right_menu();

        tp_i2c_read_status();

        if (*puVar4 != '\0')
        {
          do {
            tp_i2c_read_status();
          } while (*puVar4 != '\0');

          return;
        }

        return;
      }

      if ((0x3f < uVar10) && (uVar10 < 0x75))
      {
        cVar1 = *puVar4;
        if (pcVar5[0x43] == '\0')       //view mode (waveform or normal)
        {
          while (cVar1 != '\0')         //Normal mode
          {
            display_run_stop_button(1);
            tp_i2c_read_status();
            cVar1 = *puVar4;
          }

          display_run_stop_button(0);

          //Based on the mode several variables need to be set
          if (pcVar5[0x3a] == '\0')
          {
            pcVar5[0x3a] = '\x01';
            *(ushort *)puVar19 = (ushort)(byte)pcVar5[3];   //Channel1 volts per div
            *(ushort *)puVar7 = (ushort)(byte)pcVar5[0xf];  //Channel2 volts per div
          }
          else
          {
            pcVar5[0x3a] = '\0';
            *(undefined2 *)PTR_DAT_800202ec = 0;
            *(undefined2 *)PTR_DAT_800202f0 = 400;
            *(undefined2 *)PTR_DAT_800202f4 = 0;
            *(undefined2 *)PTR_DAT_800202f8 = 400;
          }

          if ((pcVar5[0x21] == '\0') || (pcVar5[0x3a] != '\0')) {
            pcVar5[0x18] = '\x01';
            pcVar5[0x17] = '\x01';
          }
          else {
            pcVar5[0x36] = '\0';
            pcVar5[0x37] = '\x01';
          }

          display_run_stop_text((uint)(byte)pcVar5[0x3a]);
        }
        else
        {
          while (cVar1 != '\0')             //Wavefrom view mode
          {
            display_page_up_button(1);
            tp_i2c_read_status();
            cVar1 = *puVar4;
          }

          display_page_up_button(0);

          if (*(short *)(puVar8 + 2) != 0)
          {
            *(short *)(puVar8 + 2) = *(short *)(puVar8 + 2) + -1;
            FUN_8002ca8c();
          }
        }

        tp_i2c_read_status();
        if (*puVar4 != '\0') {
          do {
            tp_i2c_read_status();
          } while (*puVar4 != '\0');

          return;
        }

        return;
      }



      if ((0x7b < uVar10) && (uVar10 < 0xb1)) {
        cVar1 = *puVar4;
        if (pcVar5[0x43] == '\0') {
          while (cVar1 != '\0') {
            display_auto_set_button(1);
            tp_i2c_read_status();
            cVar1 = *puVar4;
          }
          display_auto_set_button(0);
          pcVar5[0x21] = '\0';
          FUN_80026828();
          display_trigger_settings(0);
          FUN_80002050();
          display_ch1_settings(0);
          display_ch2_settings(0);
        }
        else {
          while (cVar1 != '\0') {
            display_page_down_button(1);
            tp_i2c_read_status();
            cVar1 = *puVar4;
          }
          display_page_down_button(0);
          if ((int)(uint)*(ushort *)(puVar8 + 2) < (int)(*(byte *)(DAT_800202fc + 0xc) - 1)) {
            *(ushort *)(puVar8 + 2) = *(ushort *)(puVar8 + 2) + 1;
            FUN_8002ca8c();
          }
        }
        tp_i2c_read_status();
        if (*puVar4 != '\0') {
          do {
            tp_i2c_read_status();
          } while (*puVar4 != '\0');
          return;
        }
        return;
      }


      if ((0xb7 < uVar10) && (uVar10 < 0xed)) {
        cVar1 = *puVar4;
        while (cVar1 != '\0') {
          display_t_cursor_button(1);
          tp_i2c_read_status();
          cVar1 = *puVar4;
        }
        display_t_cursor_button(0);
        if (8 < (byte)pcVar5[10]) {
          if (*(char *)(iVar25 + 0x292) == '\0') {
            *(undefined *)(iVar25 + 0x292) = 1;
          }
          else {
            *(undefined *)(iVar25 + 0x292) = 0;
          }
        }
        tp_i2c_read_status();
        if (*puVar4 != '\0') {
          do {
            tp_i2c_read_status();
          } while (*puVar4 != '\0');
          return;
        }
        return;
      }


      if ((0xf3 < uVar10) && (uVar10 < 0x129)) {
        cVar1 = *puVar4;
        while (cVar1 != '\0') {
          display_v_cursor_button(1);
          tp_i2c_read_status();
          cVar1 = *puVar4;
        }
        display_v_cursor_button(0);
        if (8 < (byte)pcVar5[10]) {
          if (*(char *)(iVar25 + 0x29a) == '\0') {
            *(undefined *)(iVar25 + 0x29a) = 1;
          }
          else {
            *(undefined *)(iVar25 + 0x29a) = 0;
          }
        }
        tp_i2c_read_status();
        if (*puVar4 != '\0') {
          do {
            tp_i2c_read_status();
          } while (*puVar4 != '\0');
          return;
        }
        return;
      }


      if ((0x16b < uVar10) && (uVar10 < 0x1a1)) {
        cVar1 = *puVar4;
        while (cVar1 != '\0') {
          display_save_pic_button(1);
          tp_i2c_read_status();
          cVar1 = *puVar4;
        }
        display_save_pic_button(0);
        FUN_80025f2c();
        if ((pcVar5[0x43] != '\0') && (*PTR_DAT_80020300 == '\x01')) {
          FUN_8002c8e4();
          some_sd_card_stuff_3();
        }
        tp_i2c_read_status();
        if (*puVar4 != '\0') {
          do {
            tp_i2c_read_status();
          } while (*puVar4 != '\0');
          return;
        }
        return;
      }

      if (uVar10 < 0x1a8)
      {
        return;
      }
      if (uVar10 < 0x1dd) {
        cVar1 = *puVar4;
        if (pcVar5[0x43] == '\0') {
          while (cVar1 != '\0') {
            display_save_wave_button(1);
            tp_i2c_read_status();
            cVar1 = *puVar4;
          }
          display_save_wave_button(0);
          FUN_80025c38();
        }
        else {
          while (cVar1 != '\0') {
            display_delete_wave_button(1);
            tp_i2c_read_status();
            cVar1 = *puVar4;
          }
          display_delete_wave_button(0);
          iVar25 = FUN_8002b8e8();
          if (iVar25 == 0) {
            FUN_8002ca8c();
          }
          else {
            FUN_8002ca34();
            iVar25 = FUN_8002ca8c();
            if (iVar25 != 0) {
              pcVar5[0x43] = '\0';
            }
          }
        }
        tp_i2c_read_status();
        if (*puVar4 != '\0') {
          do {
            tp_i2c_read_status();
          } while (*puVar4 != '\0');
          return;
        }
        return;
      }
      return;
    }



    if (pcVar5[0x42] == '\0') //Right menu state on control mode then return
    {
      return;
    }

    if (0x39 < *(ushort *)(puVar4 + 2) - 0x2e5)  //Touch not in the right menu range then return
    {
      return;
    }

    uVar12 = (uint)*(ushort *)(puVar4 + 4);  //Ytouch

    if ((3 < uVar12) && (uVar12 < 0x39))
    {
      cVar1 = *puVar4;
      while (cVar1 != '\0') {
        display_ctrl_button(1);
        tp_i2c_read_status();
        cVar1 = *puVar4;
      }
      display_ctrl_button(0);

      if (pcVar5[0x42] == '\0') {
        pcVar5[0x42] = '\x01';
      }
      else {
        pcVar5[0x42] = '\0';
      }
      display_right_menu();
      tp_i2c_read_status();
      if (*puVar4 != '\0') {
        do {
          tp_i2c_read_status();
        } while (*puVar4 != '\0');
        return;
      }
      return;
    }



    if ((0x4e < uVar12) && (uVar12 < 0x8c)) {
      cVar1 = *puVar4;
      while (cVar1 != '\0') {
        display_ch1_sensitivity_control(0,1);
        tp_i2c_read_status();
        cVar1 = *puVar4;
      }
      display_ch1_sensitivity_control(0,0);
      if (*pcVar5 != '\0')
      {
        bVar2 = pcVar5[0x3a];
        bVar26 = bVar2 != 0;

        if (bVar26)
        {
          bVar2 = pcVar5[10];
        }

        //At some points in the code it saves the settings and forces a limit on it??

        //puVar19 = 0x80192ec6
        if (((!bVar26 || 8 < bVar2) && ((byte)pcVar5[3] < 6)) && ((pcVar5[0x3a] == '\0' || (((ushort)(byte)pcVar5[3] <= *(ushort *)puVar19 || (((ushort)(byte)pcVar5[3] - *(ushort *)puVar19 & 0xff) < 2))))))
        {
          pcVar5[3] = pcVar5[3] + '\x01';
          display_ch1_settings(0);

          if (pcVar5[0x43] == '\0')
          {
            FUN_8000689c();
            FUN_8000696c();
            delay_2(0x3c);
          }
        }
      }
      tp_i2c_read_status();
      if (*puVar4 != '\0') {
        do {
          tp_i2c_read_status();
        } while (*puVar4 != '\0');
        return;
      }
      return;
    }


    if ((0xa3 < uVar12) && (uVar12 < 0xdf)) {
      cVar1 = *puVar4;
      while (cVar1 != '\0') {
        display_ch1_sensitivity_control(1,1);
        tp_i2c_read_status();
        cVar1 = *puVar4;
      }
      display_ch1_sensitivity_control(1,0);
      if (*pcVar5 != '\0') {
        bVar2 = pcVar5[0x3a];
        bVar26 = bVar2 != 0;
        if (bVar26) {
          bVar2 = pcVar5[10];
        }

        if (((!bVar26 || 8 < bVar2) && (pcVar5[3] != '\0')) && ((pcVar5[0x3a] == '\0' || ((*(ushort *)puVar19 <= (ushort)(byte)pcVar5[3] || ((*(ushort *)puVar19 - (ushort)(byte)pcVar5[3] & 0xff) < 2))))))
        {
          pcVar5[3] = pcVar5[3] + -1;
          display_ch1_settings(0);
          if (pcVar5[0x43] == '\0') {
            FUN_8000689c();
            FUN_8000696c();
            delay_2(0x3c);
          }
        }
      }
      tp_i2c_read_status();
      if (*puVar4 != '\0') {
        do {
          tp_i2c_read_status();
        } while (*puVar4 != '\0');
        return;
      }
      return;
    }


    if (DAT_80020304 < uVar12 && uVar12 < 0x140)
    {
      cVar1 = *puVar4;
      while (cVar1 != '\0') {
        display_ch2_sensitivity_control(0,1);
        tp_i2c_read_status();
        cVar1 = *puVar4;
      }
      display_ch2_sensitivity_control(0,0);

      if (pcVar5[0xc] != '\0') {
        bVar2 = pcVar5[0x3a];
        bVar26 = bVar2 != 0;
        if (bVar26) {
          bVar2 = pcVar5[10];
        }

        //puVar7 = 0x80192ec8. Some previous save of the volts div setting
        if (((!bVar26 || 8 < bVar2) && ((byte)pcVar5[0xf] < 6)) && ((pcVar5[0x3a] == '\0' || (((ushort)(byte)pcVar5[0xf] <= *(ushort *)puVar7 || (((ushort)(byte)pcVar5[0xf] - *(ushort *)puVar7 & 0xff) < 2))))))
        {
          pcVar5[0xf] = pcVar5[0xf] + '\x01';
          display_ch2_settings(0);
          if (pcVar5[0x43] == '\0') {
            FUN_800095e8();
            FUN_800096b8();
            delay_2(0x3c);
          }
        }
      }
      tp_i2c_read_status();
      if (*puVar4 != '\0') {
        do {
          tp_i2c_read_status();
        } while (*puVar4 != '\0');
        return;
      }
      return;
    }


    if (uVar12 < 0x158)
    {
      return;
    }

    if (uVar12 < DAT_80020308)
    {
      cVar1 = *puVar4;
      while (cVar1 != '\0') {
        display_ch2_sensitivity_control(1,1);
        tp_i2c_read_status();
        cVar1 = *puVar4;
      }
      display_ch2_sensitivity_control(1,0);
      if (pcVar5[0xc] != '\0') {
        bVar2 = pcVar5[0x3a];
        bVar26 = bVar2 != 0;
        if (bVar26) {
          bVar2 = pcVar5[10];
        }

        if (((!bVar26 || 8 < bVar2) && (pcVar5[0xf] != '\0')) && ((pcVar5[0x3a] == '\0' || ((*(ushort *)puVar7 <= (ushort)(byte)pcVar5[0xf] || ((*(ushort *)puVar7 - (ushort)(byte)pcVar5[0xf] & 0xff) < 2))))))
        {
          pcVar5[0xf] = pcVar5[0xf] + -1;
          display_ch2_settings(0);
          if (pcVar5[0x43] == '\0') {
            FUN_800095e8();
            FUN_800096b8();
            delay_2(0x3c);
          }
        }
      }
      tp_i2c_read_status();
      if (*puVar4 != '\0') {
        do {
          tp_i2c_read_status();
        } while (*puVar4 != '\0');
        return;
      }
      return;
    }




    if (uVar12 < 0x1a8)
    {
      return;
    }

    if (0x1dc < uVar12)
    {
      return;
    }

    cVar1 = *puVar4;
    if (pcVar5[0x43] == '\0') {
      while (cVar1 != '\0') {
        display_50_trigger_button(1);
        tp_i2c_read_status();
        cVar1 = *puVar4;
      }
      display_50_trigger_button(0);
      if (pcVar5[0x3a] == '\0')
      {
        FUN_80029314();
      }
      tp_i2c_read_status();
      if (*puVar4 != '\0') {
        do {
          tp_i2c_read_status();
        } while (*puVar4 != '\0');
        return;
      }
      return;
    }

    while (cVar1 != '\0')
    {
      display_show_grid_button(1);
      tp_i2c_read_status();
      cVar1 = *puVar4;
    }
    display_show_grid_button(0);

    if (*(char *)(DAT_8002030c + 3) == '\x14')
    {
      *(undefined *)(DAT_8002030c + 3) = 0;
    }
    else
    {
      *(undefined *)(DAT_8002030c + 3) = 0x14;
    }

    tp_i2c_read_status();
    if (*puVar4 != '\0') {
      do {
        tp_i2c_read_status();
      } while (*puVar4 != '\0');
      return;
    }
    return;
  }




  

  //Is this next part the handling of the line positions, trigger time base, cursors etc??????
  //Some waiting loop with a time out??? On touch active????
  if (*puVar19 == '\0')   //This is the state variable (0x80192f08)
  {
    uVar12 = get_timer_ticks();

    *(uint *)(puVar19 + 0x38) = uVar12;  //Start time saved
    cVar1 = *puVar4;

    while( true )
    {
      uVar9 = (undefined)unaff_r6;
      uVar29 = (undefined)unaff_r7;

      if (cVar1 == '\0')                      //No touch than bail
        break;

      uVar10 = *(ushort *)(puVar4 + 2);       //X touch

      *(ushort *)(puVar19 + 6) = uVar10;      //0x80192f0E  Store it somewhere

      uVar13 = *(ushort *)(puVar4 + 4);       //Y touch 

      *(ushort *)(puVar19 + 8) = uVar13;      //0x80192f10  Store it somewhere

      uVar3 = *(ushort *)(puVar19 + 2);       //0x80192f0A  previous X touch

      if (uVar10 < uVar3)                     //New touch left of old touch
      {
        uVar10 = uVar3 - uVar10;              //Calculate absolute X displacement
      }
      else
      {
        uVar10 = uVar10 - uVar3;              //Calculate absolute X displacement
      }

      uVar3 = *(ushort *)(puVar19 + 4);       //0x80192f0C  previous Y touch

      if (uVar13 < uVar3)                     //New touch above old touch
      {
        uVar13 = uVar3 - uVar13;              //Calculate absolute Y displacement
      }
      else
      {
        uVar13 = uVar13 - uVar3;              //Calculate absolute Y displacement
      }

      if (uVar13 < uVar10)                    //Check which one is bigger
      {
        *(ushort *)(puVar19 + 0x2c) = uVar10; //0x80192f34 Keep the biggest displacement
      }
      else
      {
        *(ushort *)(puVar19 + 0x2c) = uVar13; //0x80192f34 Keep the biggest displacement
      }

      if (2 < *(ushort *)(puVar19 + 0x2c))    //0x80192f34 Moved more then 2 pixels
      {
        *puVar19 = 2;                         //0x80192f08  Set first state variable to two
        goto LAB_8001b7c8;                    //Go and continue with the processing
      }

      tp_i2c_read_status();                   //Otherwise wait until touch is done
      cVar1 = *puVar4;
    }

    //Touch state needs to be 0 and less then 200ms gone by                                               //This does something with touch data
//    if (((*puVar19 == '\0') && (uVar12 = get_timer_ticks(), uVar12 - *(int *)(puVar19 + 0x38) < 200)) && (FUN_8001bc30(), *(ushort *)(puVar19 + 0x2c) < 3))

    if(*puVar19 == '\0')
    {
      uVar12 = get_timer_ticks() - *(int *)(puVar19 + 0x38);

      if(uVar12 < 200)
      {
        FUN_8001bc30();                       //Calculate the absolute displacement

        if(*(ushort *)(puVar19 + 0x2c) < 3))  //Absolute movement less then 3 pixels
        {
          //Detect short touch on a single position for changing the time base
          *puVar19 = 1;                       //0x80192f08  Set first state variable to one
          return;                             //And quit the show
        }
      }
    }
  }

  
  if (*puVar19 != '\x02')                     //Quit if state not is 2
  {
    return;
  }


//Had a larger movement here
LAB_8001b7c8:
  iVar25 = DAT_8001bc14;
  pcVar5 = DAT_8001bc10;
  uVar10 = *(ushort *)(puVar19 + 2);
  uVar12 = (uint)uVar10;

  if (0x2e0 < uVar12 - 3)  //previous x touch in the right menu then return
  {
    return;
  }

  uVar13 = *(ushort *)(puVar19 + 4);   //previous y touch
  uVar11 = (uint)uVar13;
  bVar27 = 0x2c < uVar11;
  bVar26 = uVar11 == 0x2d;

  if (0x2d < uVar11) {
    bVar27 = uVar11 <= unaff_r5;
    bVar26 = unaff_r5 == uVar11;
  }
  uVar21 = 1;
  uVar20 = 2;

  if (!bVar27 || bVar26)
  {
    puVar19 = unaff_r4;
    uVar21 = uVar29;
    uVar20 = uVar9;
  }

  if (!bVar27 || bVar26)
  {
    return;
  }

  uVar15 = DAT_8001bc14 - (uint)*(ushort *)(DAT_8001bc10 + 6) & 0xffff;
  sVar14 = (short)uVar15;

  if (uVar11 < uVar15)
  {
    sVar14 = sVar14 - uVar13;
  }
  else
  {
    sVar14 = uVar13 - sVar14;
  }

  *(short *)(puVar19 + 0x1e) = sVar14;
  uVar15 = 1000;

  if (0x3c < uVar12)
  {
    *(undefined2 *)(puVar19 + 0x1e) = 1000;
  }

  uVar16 = iVar25 - (uint)*(ushort *)(pcVar5 + 0x12) & 0xffff;
  sVar14 = (short)uVar16;

  if (uVar11 < uVar16)
  {
    sVar14 = sVar14 - uVar13;
  }
  else
  {
    sVar14 = uVar13 - sVar14;
  }
  *(short *)(puVar19 + 0x20) = sVar14;

  if (0x3c < uVar12)
  {
    *(undefined2 *)(puVar19 + 0x20) = 1000;
  }

  if (*(ushort *)(puVar19 + 0x1e) < 0x1e)
  {
    if (*(ushort *)(puVar19 + 0x20) < 0x1e && *(ushort *)(puVar19 + 0x20) < *(ushort *)(puVar19 + 0x1e))
      goto LAB_8001b884;

    goto LAB_8001b874;
  }

  if (*(ushort *)(puVar19 + 0x20) < 0x1e)
    goto LAB_8001b884;

  uVar16 = iVar25 - (uint)*(ushort *)(pcVar5 + 0x26) & 0xffff;
  sVar14 = (short)uVar16;

  if (uVar11 < uVar16)
  {
    sVar14 = sVar14 - uVar13;
  }
  else
  {
    sVar14 = uVar13 - sVar14;
  }

  *(short *)(puVar19 + 0x22) = sVar14;

  if (uVar12 - 0x2a2 < 0x47)
  {
    if (*(ushort *)(puVar19 + 0x22) < 0x1e)
    {
      puVar19[1] = uVar21;
      return;
    }
  }
  else {
    *(undefined2 *)(puVar19 + 0x22) = 1000;
  }
  iVar25 = DAT_8001bc18;
  if (*(char *)(DAT_8001bc18 + 0x292) == '\0') {
    *(undefined2 *)(puVar19 + 0x24) = 1000;
    *(undefined2 *)(puVar19 + 0x26) = 1000;
  }
  else {
    uVar3 = *(ushort *)(DAT_8001bc18 + 0x294);
    if (uVar12 < uVar3) {
      sVar14 = uVar3 - uVar10;
    }
    else {
      sVar14 = uVar10 - uVar3;
    }
    *(short *)(puVar19 + 0x24) = sVar14;
    uVar3 = *(ushort *)(iVar25 + 0x296);
    if (uVar12 < uVar3) {
      sVar14 = uVar3 - uVar10;
    }
    else {
      sVar14 = uVar10 - uVar3;
    }
    *(short *)(puVar19 + 0x26) = sVar14;
  }
  if (*(char *)(iVar25 + 0x29a) == '\0') {
    *(undefined2 *)(puVar19 + 0x28) = 1000;
    *(undefined2 *)(puVar19 + 0x2a) = 1000;
  }
  else {
    uVar10 = *(ushort *)(iVar25 + 0x29c);
    if (uVar11 < uVar10) {
      sVar14 = uVar10 - uVar13;
    }
    else {
      sVar14 = uVar13 - uVar10;
    }
    *(short *)(puVar19 + 0x28) = sVar14;
    uVar15 = (uint)*(ushort *)(iVar25 + 0x29e);
    if (uVar11 < uVar15) {
      uVar15 = uVar15 - uVar11;
    }
    else {
      uVar15 = uVar11 - uVar15;
    }
    *(short *)(puVar19 + 0x2a) = (short)uVar15;
  }
  uVar18 = DAT_8001bc24;
  uVar16 = DAT_8001bc20;
  uVar17 = (uint)*(ushort *)(puVar19 + 0x24);
  uVar24 = (uint)*(ushort *)(puVar19 + 0x26);
  bVar27 = uVar24 <= uVar17;
  bVar26 = uVar17 == uVar24;
  if (!bVar27 || bVar26) {
    uVar15 = (uint)*(ushort *)(puVar19 + 0x28);
  }
  if (!bVar27 || bVar26) {
    bVar27 = uVar15 <= uVar17;
    bVar26 = uVar17 == uVar15;
  }
  if ((bVar27 && !bVar26) || (uVar15 = (uint)*(ushort *)(puVar19 + 0x2a), uVar15 < uVar17)) {
    if (uVar17 >= uVar24) {
      uVar15 = (uint)*(ushort *)(puVar19 + 0x28);
    }
    if ((uVar17 < uVar24 || uVar15 < uVar24) || (*(ushort *)(puVar19 + 0x2a) < uVar24)) {
      uVar15 = (uint)*(ushort *)(puVar19 + 0x28);
      bVar27 = uVar17 <= uVar15;
      bVar26 = uVar15 == uVar17;
      if (!bVar27 || bVar26) {
        bVar27 = uVar24 <= uVar15;
        bVar26 = uVar15 == uVar24;
      }
      if ((bVar27 && !bVar26) || (*(ushort *)(puVar19 + 0x2a) < uVar15)) {
        uVar22 = (uint)*(ushort *)(puVar19 + 0x2a);
        if (uVar22 <= uVar17 && uVar22 <= uVar24) {
          bVar26 = uVar15 <= uVar22;
          if (uVar22 <= uVar15) {
            bVar26 = 0x22 < uVar22;
          }
          if (!bVar26) {
            uVar9 = 7;
            goto LAB_8001ba00;
          }
        }
      }
      else {
        if (uVar15 < 0x23) {
          uVar9 = 6;
          goto LAB_8001ba00;
        }
      }
    }
    else {
      if (uVar24 < 0x23) {
        uVar9 = 5;
        goto LAB_8001ba00;
      }
    }
  }
  else {
    if (uVar17 < 0x23)
    {
      puVar19[1] = 4;
      return;
    }
  }
  if (*(char *)(DAT_8001bc1c + 7) != '\0') {
    uVar9 = 0x17;

LAB_8001ba00:
    puVar19[1] = uVar9;
    return;
  }

  if (*pcVar5 == '\0') {
    *(short *)(puVar19 + 0x1e) = (short)DAT_8001bc24;
  }
  else {
    iVar25 = 0;
    uVar17 = DAT_8001bc24;
    uVar15 = DAT_8001bc20;
    puVar23 = DAT_8001bc28;
    do {
      if (*puVar23 == uVar11) {
        if (iVar25 + 3 < (int)uVar12) {
          uVar24 = (uVar12 - iVar25) - 3;
        }
        else {
          uVar24 = (iVar25 - uVar12) + 3;
        }
        if ((uVar24 & 0xffff) < uVar17) {
          uVar17 = uVar24 & 0xffff;
        }
      }
      uVar15 = uVar15 - 1 & 0xffff;
      iVar25 = iVar25 + 1;
      puVar23 = puVar23 + 1;
    } while (uVar15 != 0);
    if (uVar12 < 3) {
      *(undefined2 *)(puVar19 + 2) = 3;
    }
    uVar12 = (uint)DAT_8001bc28[*(ushort *)(puVar19 + 2) - 3];
    if (uVar12 < uVar11) {
      uVar12 = uVar11 - uVar12;
    }
    else {
      uVar12 = uVar12 - uVar11;
    }
    if (uVar17 < (uVar12 & 0xffff)) {
      *(short *)(puVar19 + 0x1e) = (short)uVar17;
    }
    else {
      *(short *)(puVar19 + 0x1e) = (short)uVar12;
    }
  }
  if (pcVar5[0xc] == '\0') {
LAB_8001bb8c:
    *(short *)(puVar19 + 0x20) = (short)uVar18;
  }
  else {
    uVar12 = (uint)*(ushort *)(puVar19 + 2);
    iVar25 = 0;
    puVar23 = DAT_8001bc2c;
    do {
      if (*puVar23 == uVar11) {
        if (iVar25 + 3 < (int)uVar12) {
          uVar15 = (uVar12 - iVar25) - 3;
        }
        else {
          uVar15 = (iVar25 - uVar12) + 3;
        }
        if ((uVar15 & 0xffff) < uVar18) {
          uVar18 = uVar15 & 0xffff;
        }
      }
      uVar16 = uVar16 - 1 & 0xffff;
      iVar25 = iVar25 + 1;
      puVar23 = puVar23 + 1;
    } while (uVar16 != 0);
    if (uVar12 < 3) {
      *(undefined2 *)(puVar19 + 2) = 3;
    }
    uVar12 = (uint)DAT_8001bc2c[*(ushort *)(puVar19 + 2) - 3];
    if (uVar12 < uVar11) {
      uVar12 = uVar11 - uVar12;
    }
    else {
      uVar12 = uVar12 - uVar11;
    }
    if (uVar18 < (uVar12 & 0xffff)) goto LAB_8001bb8c;
    *(short *)(puVar19 + 0x20) = (short)uVar12;
  }
  if (*(ushort *)(puVar19 + 0x1e) < 0x1e) {
    if (0x1d < *(ushort *)(puVar19 + 0x20) ||
        *(ushort *)(puVar19 + 0x1e) <= *(ushort *)(puVar19 + 0x20)) {

LAB_8001b874:
      puVar19[1] = uVar20;
      return;
    }
  }
  else {
    if (0x1d < *(ushort *)(puVar19 + 0x20)) {
      puVar19[1] = 0;
      iVar25 = FUN_8001bc80();
      if (iVar25 == 1 || iVar25 == 3) goto LAB_8001b874;
      if (iVar25 != 2) {
        return;
      }
    }
  }
LAB_8001b884:
  puVar19[1] = 3;
  return;
}


//------------------------------------------------------------------------------------------------------------------------------------------

void setup_main_menu(void)

{
  int iVar1;
  
  iVar1 = DAT_80029194;                    //0x8036B792  //8036B792

  *(undefined *)(DAT_80029194 + 6) = 1;    //0x8036b798 = 1

  save_screen_under_main_menu();           //Save rect under main menu

  display_slide_down_main_menu();          //Display the menu

  display_highlight_main_menu_item();      //Highlight an active item
 
  if (*(char *)(iVar1 + 6) == '\0')        //Where is this cleared (0x8036b798)
  {
    return;
  }

  do
  {
    handle_main_menu_touch();              //Handle the main menu touch
  } while (*(char *)(iVar1 + 6) != '\0');  //As long as this one is set (0x8036b798)

  return;
}

//------------------------------------------------------------------------------------------------------------------------------------------

void display_highlight_main_menu_item(void)

{
  char cVar1;
  undefined *puVar2;
  int *piVar3;
  ushort uVar4;
  short sVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  ushort *puVar13;
  int iVar14;
  uint uVar15;
  ushort *puVar16;
  undefined2 *puVar17;
  int iVar18;
  
  //Convert colors
  uVar4 = FUN_800232b4(DAT_8000e6d8);   //Yellow  (0x00FFFF00)
  uVar6 = FUN_800232b4(DAT_8000e6dc);   //Grey    (0x001B1B1B)
  uVar7 = FUN_800232b4(0);              //Black
  uVar8 = FUN_800232b4(0xffffff);       //White

  cVar1 = *DAT_8000e6e0;                //0x80361378

  set_frame_to_global_pointer();

  piVar3 = Global_Frame_Buffer_Pointer;
  puVar2 = PTR_DAT_8000e6e8;              //0x80192ef8
  uVar11 = DAT_8000e6e4;
  uVar15 = 0;

  //Display the menu again in a separate buffer
  do
  {
    iVar18 = 0x95;
    puVar13 = (ushort *)(PTR_BITMAP_MAIN_MENU_8000e6f0 + uVar15 * 0x12a);
    puVar17 = (undefined2 *)(*piVar3 + ((uint)*(ushort *)puVar2 + (*(ushort *)(puVar2 + 2) + uVar15) * 800) * 2);
    do
    {
      uVar9 = (uint)*puVar13;
      uVar10 = uVar6;
      if (((uVar9 != 0) && (uVar10 = uVar7, uVar9 != 0xf800)) && (uVar10 = uVar9, uVar9 == uVar11))
      {
        uVar10 = uVar8;
      }
      iVar18 = iVar18 + -1;
      *puVar17 = (short)uVar10;
      puVar13 = puVar13 + 1;
      puVar17 = puVar17 + 1;
    } while (iVar18 != 0);
    uVar15 = uVar15 + 1 & 0xfffeffff;
  } while (uVar15 < 0xeb);

  //Check on some state variable
  if (cVar1 == '\x01')
  {
    //Highlight the system settings if on 1
    uVar11 = 0xe;
    do
    {
      puVar13 = (ushort *)(*piVar3 + ((*(ushort *)(puVar2 + 2) + uVar11) * 800 + 9 + (uint)*(ushort *)puVar2) * 2);
      sVar5 = 0x83;

      do
      {
        sVar5 = sVar5 + -1;

        if (*puVar13 == uVar6)
        {
          *puVar13 = uVar4;
        }
        else
        {
          *puVar13 = ~*puVar13;
        }

        puVar13 = puVar13 + 1;
      } while (sVar5 != 0);

      uVar11 = uVar11 + 1 & 0xfffeffff;
    } while (uVar11 < 0x2e);
  }
  else
  {
    if (cVar1 == '\x02')
    {
      iVar18 = *piVar3;
      uVar11 = 0x47;
      do
      {
        puVar13 = (ushort *)(iVar18 + ((uint)*(ushort *)puVar2 + (*(ushort *)(puVar2 + 2) + uVar11) * 800 + 9) * 2);

        if (uVar10 == uVar6)
        {
          *puVar13 = uVar4;
        }
        else
        {
          *puVar13 = ~*puVar13;
        }

        iVar14 = 1;
        sVar5 = 0x41;

        do
        {
          puVar13 = (ushort *)(iVar18 + ((uint)*(ushort *)puVar2 + (*(ushort *)(puVar2 + 2) + uVar11) * 800 + iVar14 + 9) * 2);
          if (uVar10 == uVar6)
          {
            *puVar13 = uVar4;
          }
          else
          {
            *puVar13 = ~*puVar13;
          }

          iVar12 = iVar18 + ((uint)*(ushort *)puVar2 + (*(ushort *)(puVar2 + 2) + uVar11) * 800 + iVar14 + 9) * 2;

          if (uVar10 == uVar6)
          {
            *(ushort *)(iVar12 + 2) = uVar4;
          }
          else
          {
            *(ushort *)(iVar12 + 2) = ~*(ushort *)(iVar12 + 2);
          }

          sVar5 = sVar5 + -1;
          iVar14 = iVar14 + 2;
        } while (sVar5 != 0);

        uVar11 = uVar11 + 1 & 0xfffeffff;
      } while (uVar11 < 0x69);
    }
    else
    {
      if (cVar1 == '\x03') {
        iVar18 = *piVar3;
        uVar11 = 0x82;
        do {
          puVar13 = (ushort *)
                    (iVar18 + ((uint)*(ushort *)puVar2 + (*(ushort *)(puVar2 + 2) + uVar11) * 800 +
                              9) * 2);
          if (uVar10 == uVar6) {
            *puVar13 = uVar4;
          }
          else {
            *puVar13 = ~*puVar13;
          }
          iVar14 = 1;
          sVar5 = 0x41;
          do {
            puVar13 = (ushort *)
                      (iVar18 + ((uint)*(ushort *)puVar2 + (*(ushort *)(puVar2 + 2) + uVar11) * 800
                                + iVar14 + 9) * 2);
            if (uVar10 == uVar6) {
              *puVar13 = uVar4;
            }
            else {
              *puVar13 = ~*puVar13;
            }
            iVar12 = iVar18 + ((uint)*(ushort *)puVar2 + (*(ushort *)(puVar2 + 2) + uVar11) * 800 +
                              iVar14 + 9) * 2;
            if (uVar10 == uVar6) {
              *(ushort *)(iVar12 + 2) = uVar4;
            }
            else {
              *(ushort *)(iVar12 + 2) = ~*(ushort *)(iVar12 + 2);
            }
            sVar5 = sVar5 + -1;
            iVar14 = iVar14 + 2;
          } while (sVar5 != 0);
          uVar11 = uVar11 + 1 & 0xfffeffff;
        } while (uVar11 < 0xa4);
      }
      else {
        if (cVar1 == '\x04') {
          uVar11 = 0xbe;
          do {
            if (uVar10 == uVar6) {
              puVar13 = (ushort *)
                        (*piVar3 +
                        ((uint)*(ushort *)puVar2 + (*(ushort *)(puVar2 + 2) + uVar11) * 800 + 9) * 2
                        );
              *puVar13 = uVar4;
              sVar5 = 0x41;
              do {
                sVar5 = sVar5 + -1;
                puVar13[1] = uVar4;
                puVar13 = puVar13 + 2;
                *puVar13 = uVar4;
              } while (sVar5 != 0);
            }
            else {
              puVar13 = (ushort *)
                        (*piVar3 +
                        ((uint)*(ushort *)puVar2 + (*(ushort *)(puVar2 + 2) + uVar11) * 800 + 9) * 2
                        );
              *puVar13 = ~*puVar13;
              sVar5 = 0x41;
              do {
                puVar16 = puVar13 + 2;
                sVar5 = sVar5 + -1;
                puVar13[1] = ~puVar13[1];
                *puVar16 = ~*puVar16;
                puVar13 = puVar16;
              } while (sVar5 != 0);
            }
            uVar11 = uVar11 + 1 & 0xfffeffff;
          } while (uVar11 < 0xde);
        }
      }
    }
  }

  set_display_fg_color(DAT_8000e6f4);

  //Some display functionality
  FUN_80018da0((uint)*(ushort *)puVar2,(uint)*(ushort *)(puVar2 + 2),*(ushort *)puVar2 + 0x94,*(ushort *)(puVar2 + 2) + 0xea);

  //Copy rect to screen
  iVar14 = Start_Of_Screen_Mem;
  iVar18 = Screen_Frame_Buffer;
  uVar6 = (uint)*(ushort *)(puVar2 + 2);
  uVar11 = (uint)*(ushort *)puVar2;
  uVar7 = uVar6 + 0xeb & 0xfffeffff;
  if (uVar6 < uVar7) {
    do {
      iVar12 = uVar11 + uVar6 * 800;
      copy_short((void *)(iVar14 + iVar12 * 2),(void *)(iVar18 + iVar12 * 2),
                 ((uVar11 + 0x94 & 0xfffeffff) - uVar11) + 1);
      uVar6 = uVar6 + 1;
    } while (uVar6 < uVar7);
    return;
  }
  return;
}

//------------------------------------------------------------------------------------------------------------------------------------------

void display_slide_down_main_menu(void)

{
  short sVar1;
  undefined *puVar2;
  undefined *puVar3;
  int *piVar4;
  short sVar5;
  short sVar6;
  uint uVar7;
  uint uVar8;
  short *psVar9;
  int iVar10;
  short *psVar11;
  short sVar12;
  
  sVar5 = FUN_800232b4(DAT_8000e7e4);    //0x001B1B1B Convert color
  sVar6 = FUN_800232b4(0);
  puVar2 = PTR_DAT_8000e7e8;             //0x80192ef8

  *(undefined2 *)PTR_DAT_8000e7e8 = 2;
  *(undefined2 *)(puVar2 + 2) = 0x2e;
  *(undefined2 *)(puVar2 + 4) = 0x97;
  *(undefined2 *)(puVar2 + 6) = 0x2e;

  set_screen_to_global_pointer();
  piVar4 = Global_Frame_Buffer_Pointer;
  puVar3 = PTR_BITMAP_MAIN_MENU_8000e7ec;
  uVar7 = 0xeb;
  uVar8 = uVar7;
  do {
    while (uVar7 < 0xeb) {
      iVar10 = 0x95;
      psVar9 = (short *)(puVar3 + uVar7 * 0x12a);
      psVar11 = (short *)(*piVar4 + ((uint)*(ushort *)puVar2 + ((uint)*(ushort *)(puVar2 + 2) + (uVar7 - uVar8)) * 800) * 2);
      do {
        sVar1 = *psVar9;
        sVar12 = sVar5;
        if ((sVar1 != 0) && (sVar12 = sVar1, sVar1 == -0x800)) {
          sVar12 = sVar6;
        }
        iVar10 = iVar10 + -1;
        *psVar11 = sVar12;
        psVar9 = psVar9 + 1;
        psVar11 = psVar11 + 1;
      } while (iVar10 != 0);
      uVar7 = uVar7 + 1 & 0xfffeffff;
    }
    uVar7 = (uVar8 - (uVar8 * DAT_8000e7f4 >> 0x14)) - 1 & 0xffff;  //0x0000E38F
    uVar8 = uVar7;
  } while (uVar7 != 0);
  *Global_Frame_Buffer_Pointer = Screen_Frame_Buffer;
  return;
}


//------------------------------------------------------------------------------------------------------------------------------------------

uint FUN_800232b4(int param_1)

{
  return ((uint)(param_1 << 8) >> 0x1b) << 0xb | ((uint)(param_1 << 0x10) >> 0x1a) << 5 | (uint)(param_1 << 0x18) >> 0x1b;
  //001B1B1B 
  //1800 | C0 | 3 = 18C3
}

//------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------


