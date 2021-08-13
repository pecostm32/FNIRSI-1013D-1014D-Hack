//------------------------------------------------------------------------------------------------------------------------------------------


  //Is this next part the handling of the line positions, trigger time base, cursors etc??????
  //Some waiting loop with a time out??? On touch active????
  if (*puVar19 == '\0')   //This is the state variable (0x80192f08)    touchstate
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


    //All that is needed here is to detect short touch
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
  iVar25 = DAT_8001bc14;               //0x000001C1     449
  pcVar5 = DAT_8001bc10;               //0x8019D5A0     settings base
  uVar10 = *(ushort *)(puVar19 + 2);   //saved x touch
  uVar12 = (uint)uVar10;

  if (0x2e0 < uVar12 - 3)  //previous x touch in the right menu then return
  {
    return;
  }

  uVar13 = *(ushort *)(puVar19 + 4);   //previous y touch
  uVar11 = (uint)uVar13;
  bVar27 = 0x2c < uVar11;
  bVar26 = uVar11 == 0x2d;

  if (0x2d < uVar11)                     //Lower then menu bar
  {
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

  if (!bVar27 || bVar26)                  //Below trace screen
  {
    return;
  }

  //Channel 1 trace offset 
  uVar15 = DAT_8001bc14 - (uint)*(ushort *)(DAT_8001bc10 + 6) & 0xffff;
  sVar14 = (short)uVar15;

  if (uVar11 < uVar15)           //y touch less than justified trace offset
  {
    sVar14 = sVar14 - uVar13;    //ch1 center - y touch
  }
  else
  {
    sVar14 = uVar13 - sVar14;    //y touch - ch1 center
  }

  *(short *)(puVar19 + 0x1e) = sVar14;  //Store somewhere 0x80192f08 + 0x1E. This is distance to trace center
  uVar15 = 1000;

  if (0x3c < uVar12)   //xtouch above 60 then store 1000. Below 60 it has preference over other traces
  {
    *(undefined2 *)(puVar19 + 0x1e) = 1000;
  }


  //Channel 2 trace offset
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
  *(short *)(puVar19 + 0x20) = sVar14;   //Store somewhere 0x80192f08 + 0x20

  if (0x3c < uVar12)
  {
    *(undefined2 *)(puVar19 + 0x20) = 1000;
  }

  if (*(ushort *)(puVar19 + 0x1e) < 0x1e)  //Channel 1 distance below 30
  {
    //Check if channel 2 distance is also less then 30 and it is less then the channel 1 distance
    if (*(ushort *)(puVar19 + 0x20) < 0x1e && *(ushort *)(puVar19 + 0x20) < *(ushort *)(puVar19 + 0x1e))
      goto LAB_8001b884;  //Go and handle that

    goto LAB_8001b874; //otherwhise do this one
  }

  //Channel 1 not close then check if channel 2 is close
  if (*(ushort *)(puVar19 + 0x20) < 0x1e)
    goto LAB_8001b884; //if so handle channel 2


  //Trigger level screen offset
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

  *(short *)(puVar19 + 0x22) = sVar14;   //Store somewhere 0x80192f08 + 0x22

  if (uVar12 - 0x2a2 < 0x47)  //Only active within last 70 pixels on the trace display
  {
    if (*(ushort *)(puVar19 + 0x22) < 0x1e)  //Y range needs to be within 30 pixels of the pointer
    {
      puVar19[1] = uVar21;   //State variable for which trace set to 1
      return;
    }
  }
  else
  {
    *(undefined2 *)(puVar19 + 0x22) = 1000;   //Not in x range
  }




  iVar25 = DAT_8001bc18;   //0x801FA24C Starting point of measurements list. These can be in the way of trace and cursors. seems not an issue



  if (*(char *)(DAT_8001bc18 + 0x292) == '\0')  //time cursor disabled
  {
    *(undefined2 *)(puVar19 + 0x24) = 1000;  //first line distance
    *(undefined2 *)(puVar19 + 0x26) = 1000;  //second line distance
  }
  else
  {
    uVar3 = *(ushort *)(DAT_8001bc18 + 0x294);  //first line position

    if (uVar12 < uVar3)  //x touch compared
    {
      sVar14 = uVar3 - uVar10;
    }
    else
    {
      sVar14 = uVar10 - uVar3;
    }

    *(short *)(puVar19 + 0x24) = sVar14;  //first line distance

    uVar3 = *(ushort *)(iVar25 + 0x296);  //second line position

    if (uVar12 < uVar3)
    {
      sVar14 = uVar3 - uVar10;
    }
    else
    {
      sVar14 = uVar10 - uVar3;
    }

    *(short *)(puVar19 + 0x26) = sVar14;  //second line distance
  }

  if (*(char *)(iVar25 + 0x29a) == '\0')   //volt cursor disabled
  {
    *(undefined2 *)(puVar19 + 0x28) = 1000;
    *(undefined2 *)(puVar19 + 0x2a) = 1000;
  }
  else
  {
    uVar10 = *(ushort *)(iVar25 + 0x29c);

    if (uVar11 < uVar10)
    {
      sVar14 = uVar10 - uVar13;
    }
    else
    {
      sVar14 = uVar13 - uVar10;
    }

    *(short *)(puVar19 + 0x28) = sVar14;

    uVar15 = (uint)*(ushort *)(iVar25 + 0x29e);

    if (uVar11 < uVar15)
    {
      uVar15 = uVar15 - uVar11;
    }
    else
    {
      uVar15 = uVar11 - uVar15;
    }

    *(short *)(puVar19 + 0x2a) = (short)uVar15;
  }




  uVar18 = DAT_8001bc24;                      //0x0000FFFF
  uVar16 = DAT_8001bc20;                      //0x000002CD

  uVar17 = (uint)*(ushort *)(puVar19 + 0x24);  //Time cursors left 
  uVar24 = (uint)*(ushort *)(puVar19 + 0x26);  //Time cursors right

  bVar27 = uVar24 <= uVar17;   //touch closer to right
  bVar26 = uVar17 == uVar24;   //Same distance

  if (!bVar27 || bVar26)  //Touch closer to left or same distance
  {
    uVar15 = (uint)*(ushort *)(puVar19 + 0x28);  //Get the volt cursor distance

    bVar27 = uVar15 <= uVar17;    //touch closer to volt top
    bVar26 = uVar17 == uVar15;    //or same
  }

  //touch closer to volt top or volt bottom
  if ((bVar27 && !bVar26) || (uVar15 = (uint)*(ushort *)(puVar19 + 0x2a), uVar15 < uVar17))
  {
    //Touch closer to time right
    if (uVar17 >= uVar24)
    {
      uVar15 = (uint)*(ushort *)(puVar19 + 0x28);  //get volt top
    }

    //touch closer to left time compared to right  or closer to volt top compared to right  or closer to volt bottom compared to right
    if ((uVar17 < uVar24 || uVar15 < uVar24) || (*(ushort *)(puVar19 + 0x2a) < uVar24))
    {
      uVar15 = (uint)*(ushort *)(puVar19 + 0x28);  //get volt top again

      bVar27 = uVar17 <= uVar15;   //touch closer to time left then volt top
      bVar26 = uVar15 == uVar17;

      if (!bVar27 || bVar26)  //touch closer or equal to volt top compared to time left
      {
        bVar27 = uVar24 <= uVar15;  //time right versus volt top
        bVar26 = uVar15 == uVar24;
      }

      //time right less then volt top  or bottom less then top
      if ((bVar27 && !bVar26) || (*(ushort *)(puVar19 + 0x2a) < uVar15))
      {
        uVar22 = (uint)*(ushort *)(puVar19 + 0x2a);  //get volt bottom

        if (uVar22 <= uVar17 && uVar22 <= uVar24)
        {
          bVar26 = uVar15 <= uVar22;

          if (uVar22 <= uVar15)
          {
            bVar26 = 0x22 < uVar22;
          }

          if (!bVar26)
          {
            uVar9 = 7;
            goto LAB_8001ba00;
          }
        }
      }
      else
      {
        if (uVar15 < 0x23)
        {
          uVar9 = 6;
          goto LAB_8001ba00;
        }
      }
    }
    else
    {
      if (uVar24 < 0x23)
      {
        uVar9 = 5;
        goto LAB_8001ba00;
      }
    }
  }
  else
  {
    if (uVar17 < 0x23)
    {
      puVar19[1] = 4;
      return;
    }
  }

  if (*(char *)(DAT_8001bc1c + 7) != '\0')   //0x80361378 + 7 = x-y mode display
  {
    uVar9 = 0x17;

LAB_8001ba00:
    puVar19[1] = uVar9;
    return;
  }

  if (*pcVar5 == '\0')
  {
    *(short *)(puVar19 + 0x1e) = (short)DAT_8001bc24;
  }
  else 
  {
    iVar25 = 0;
    uVar17 = DAT_8001bc24;
    uVar15 = DAT_8001bc20;
    puVar23 = DAT_8001bc28;

    do
    {
      if (*puVar23 == uVar11)
      {
        if (iVar25 + 3 < (int)uVar12)
        {
          uVar24 = (uVar12 - iVar25) - 3;
        }
        else
        {
          uVar24 = (iVar25 - uVar12) + 3;
        }

        if ((uVar24 & 0xffff) < uVar17)
        {
          uVar17 = uVar24 & 0xffff;
        }
      }

      uVar15 = uVar15 - 1 & 0xffff;
      iVar25 = iVar25 + 1;
      puVar23 = puVar23 + 1;
    } while (uVar15 != 0);

    if (uVar12 < 3)
    {
      *(undefined2 *)(puVar19 + 2) = 3;
    }

    uVar12 = (uint)DAT_8001bc28[*(ushort *)(puVar19 + 2) - 3];

    if (uVar12 < uVar11)
    {
      uVar12 = uVar11 - uVar12;
    }
    else
    {
      uVar12 = uVar12 - uVar11;
    }

    if (uVar17 < (uVar12 & 0xffff))
    {
      *(short *)(puVar19 + 0x1e) = (short)uVar17;
    }
    else
    {
      *(short *)(puVar19 + 0x1e) = (short)uVar12;
    }
  }

  if (pcVar5[0xc] == '\0')
  {
LAB_8001bb8c:
    *(short *)(puVar19 + 0x20) = (short)uVar18;
  }
  else
  {
    uVar12 = (uint)*(ushort *)(puVar19 + 2);
    iVar25 = 0;
    puVar23 = DAT_8001bc2c;

    do
    {
      if (*puVar23 == uVar11)
      {
        if (iVar25 + 3 < (int)uVar12)
        {
          uVar15 = (uVar12 - iVar25) - 3;
        }
        else
        {
          uVar15 = (iVar25 - uVar12) + 3;
        }

        if ((uVar15 & 0xffff) < uVar18)
        {
          uVar18 = uVar15 & 0xffff;
        }
      }

      uVar16 = uVar16 - 1 & 0xffff;
      iVar25 = iVar25 + 1;
      puVar23 = puVar23 + 1;
    } while (uVar16 != 0);

    if (uVar12 < 3)
    {
      *(undefined2 *)(puVar19 + 2) = 3;
    }

    uVar12 = (uint)DAT_8001bc2c[*(ushort *)(puVar19 + 2) - 3];

    if (uVar12 < uVar11)
    {
      uVar12 = uVar11 - uVar12;
    }
    else
    {
      uVar12 = uVar12 - uVar11;
    }

    if (uVar18 < (uVar12 & 0xffff))
      goto LAB_8001bb8c;

    *(short *)(puVar19 + 0x20) = (short)uVar12;
  }

  if (*(ushort *)(puVar19 + 0x1e) < 0x1e)
  {
    if (0x1d < *(ushort *)(puVar19 + 0x20) || *(ushort *)(puVar19 + 0x1e) <= *(ushort *)(puVar19 + 0x20))
    {

LAB_8001b874:
      puVar19[1] = uVar20;
      return;
    }
  }
  else
  {
    if (0x1d < *(ushort *)(puVar19 + 0x20))
    {
      puVar19[1] = 0;

      iVar25 = FUN_8001bc80();

      if (iVar25 == 1 || iVar25 == 3)
        goto LAB_8001b874;

      if (iVar25 != 2)
      {
        return;
      }
    }
  }


LAB_8001b884:
  puVar19[1] = 3;  //Select second trace for movement
  return;
}

//------------------------------------------------------------------------------------------------------------------------------------------

