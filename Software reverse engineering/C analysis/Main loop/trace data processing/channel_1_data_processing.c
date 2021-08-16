//------------------------------------------------------------------------------------------------------------------------------------------------

//Some time base setting based delay loop??????? It does some calculation not shown here
//void FUN_800294c4(void)
uint timebase_based_calculation(uint16 *buf1,uint16 *buf2)

{
  ushort *puVar1;
  ushort *puVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int unaff_r5;
  uint uVar7;
  bool bVar8;
  
  puVar1 = (ushort *)((int)buf1 + 10);
  bVar8 = 10 < *(byte *)(DAT_80029534 + 10);
  iVar5 = DAT_8002953c;

  if (bVar8)
  {
    unaff_r5 = 1;
    iVar5 = DAT_80029538;
  }

  iVar3 = 0;
  if (!bVar8)
  {
    unaff_r5 = 2;
  }

  uVar7 = iVar5 - 5U & 0xffff;
  puVar2 = (ushort *)((int)buf2 + 10);

  do
  {
    uVar6 = (uint)*puVar1;
    uVar4 = (uint)*puVar2;
    puVar1 = puVar1 + 1;

    if (uVar6 < uVar4)
    {
      iVar5 = uVar4 - uVar6;
    }
    else
    {
      iVar5 = uVar6 - uVar4;
    }

    iVar3 = iVar3 + iVar5;
    uVar7 = uVar7 - 1 & 0xffff;
    puVar2 = puVar2 + 1;
  } while (uVar7 != 0);

  return iVar3 * unaff_r5;
}


//------------------------------------------------------------------------------------------------------------------------------------------------
//Does not have input or return parameters

void FUN_80003ec8(undefined4 param_1,uint param_2)

{
  undefined *puVar1;
  void *pvVar2;
  void *pvVar3;
  int iVar4;
  undefined2 uVar5;
  ushort uVar6;
  uint *puVar7;
  uint *puVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint *puVar12;
  uint *puVar13;
  byte *pbVar14;
  uint uVar15;
  uint uVar16;
  byte bVar17;
  uint uVar18;
  int iVar19;
  byte bVar20;
  uint in_r12;
  uint uVar21;
  uint uVar22;
  code *UNRECOVERED_JUMPTABLE_00;
  bool bVar23;
  bool bVar24;
  longlong lVar25;
  
  uVar16 = DAT_800040ec;                      //0x00000BB8
  puVar1 = PTR_initialization_data_800040e8;  //0x80192e9c
  uVar18 = DAT_800040e4;                      //0x8019D5A0


  if (*(int *)(DAT_800040e0 + 0x144) == 0)  //Some measurement setting 0x801fa390 (0x801FA24C + 0x144)
  {
    return;
  }

  if (*(byte *)(DAT_800040e4 + 10) < 0xb)   //time base needs to be 11 and up (10mS/div - 10nS/div)
  {
    return;
  }

  if (*(char *)(DAT_800040e4 + 0x21) == '\x01')  //If trigger mode is single return
  {
    return;
  }

  //Channel 1 trace offset not equal to some initial setting???
  if (*(short *)(DAT_800040e4 + 6) != *(short *)(PTR_initialization_data_800040e8 + 4))  //0x80192e9c + 4
  {
    memcpy(DAT_800040f4,DAT_800040f0,DAT_800040ec);    //dest = 0x801A33AA, source = 0x801AC04A, size = 0x00000BB8 = 3000
    memcpy(DAT_800040f8,DAT_800040f0,uVar16);          //dest = 0x801A4B1A, source = 0x801AC04A, size = 0x00000BB8 = 3000
  }

  pvVar2 = DAT_800040f4;                                        //0x801A33AA
  *(undefined2 *)(puVar1 + 4) = *(undefined2 *)(uVar18 + 6);    //initial data + 4 =    trace offset


  uVar9 = FUN_800294c4(DAT_800040f0,pvVar2);

  uVar10 = FUN_800294c4(DAT_800040f0,DAT_800040f8);

  uVar10 = uVar10 & 0xffff;

  if (*(char *)(uVar18 + 3) == '\x06')
  {
    iVar19 = 0x1e;
  }
  else
  {
    iVar19 = 0xf;
  }

  bVar24 = (uVar9 & 0xffff) < DAT_800040fc;
  bVar23 = uVar10 < DAT_800040fc;

  if (bVar24 && bVar23)
  {
    uVar10 = 0;
  }

  uVar5 = (undefined2)uVar10;

  if (!bVar24 || !bVar23)
  {
    uVar6 = *(ushort *)puVar1;
    bVar23 = uVar6 == 0;

    if (bVar23)
    {
      uVar6 = (ushort)*(byte *)(uVar18 + 0x21);
    }

    if (!bVar23 || uVar6 != 0)
    {
      memcpy(DAT_800040f4,DAT_800040f0,uVar16);
      memcpy(DAT_800040f8,DAT_800040f0,uVar16);
      goto LAB_80003fcc;
    }

    memcpy(DAT_800040f0,DAT_800040f4,uVar16);
    uVar5 = 1;
  }

  *(undefined2 *)puVar1 = uVar5;

LAB_80003fcc:
  set_screen_to_global_pointer();

  iVar4 = DAT_80004108;           //0x000005DC   = 1500
  puVar8 = DAT_80004104;          //0x801AEF2A
  uVar9 = DAT_80004100;           //0x0000FFFF    high for min detect??
  pvVar3 = DAT_800040f8;          //0x801A4B1A    buffer
  pvVar2 = DAT_800040f4;          //0x801A33AA    buffer
  puVar13 = DAT_800040f0;         //0x801AC04A    sample buffer
  uVar10 = 0;                     //              low for max detect??

  do
  {
    uVar6 = *(ushort *)((int)puVar13 + uVar10 * 2);
    uVar11 = (uint)uVar6;
    uVar15 = (uint)*(ushort *)((int)pvVar2 + uVar10 * 2);
    uVar21 = uVar11 + iVar19;
    bVar24 = uVar15 <= uVar21;
    bVar23 = uVar21 == uVar15;

    if (bVar24 && !bVar23)
    {
      uVar18 = uVar15 + iVar19;
    }

    if (bVar24 && !bVar23)
    {
      bVar24 = uVar11 <= uVar18;
      bVar23 = uVar18 == uVar11;
    }

    if (!bVar24 || bVar23)
    {
LAB_80004094:
      *(ushort *)((int)puVar8 + uVar10 * 2) = uVar6;
    }
    else
    {
      uVar18 = (uint)*(ushort *)((int)pvVar3 + uVar10 * 2);
      bVar24 = uVar18 <= uVar21;
      bVar23 = uVar21 == uVar18;

      if (bVar24 && !bVar23)
      {
        uVar21 = uVar18 + iVar19;
      }

      if (bVar24 && !bVar23)
      {
        bVar24 = uVar11 <= uVar21;
        bVar23 = uVar21 == uVar11;
      }

      if (!bVar24 || bVar23)
        goto LAB_80004094;

      uVar21 = 0;

      if ((uVar11 == 0) || (uVar22 = uVar9, uVar21 = uVar11, uVar11 < uVar9))
      {
        uVar22 = uVar11;
      }

      if (uVar21 < uVar15)
      {
        uVar21 = uVar15;
      }

      if (uVar15 < uVar22)
      {
        uVar22 = uVar15;
      }

      if (uVar21 < uVar18)
      {
        uVar21 = uVar18;
      }

      if (uVar18 < uVar22)
      {
        uVar22 = uVar18;
      }

      *(short *)((int)puVar8 + uVar10 * 2) = (short)(uVar21 + uVar22 >> 1);
    }

    uVar10 = uVar10 + 1;

    if (iVar4 <= (int)uVar10)
    {
      memcpy(DAT_800040f8,DAT_800040f4,uVar16);
      memcpy(DAT_800040f4,DAT_800040f0,uVar16);

      puVar8 = DAT_800040f0;
      puVar13 = DAT_80004104;

      if (3 < uVar16)
      {
        uVar18 = (uint)DAT_800040f0 & 3;
        in_r12 = uVar18;

        if (uVar18 != 0)
        {
          bVar17 = *(byte *)DAT_80004104;
          puVar12 = (uint *)((int)DAT_80004104 + 1);

          if (uVar18 < 3)
          {
            puVar12 = (uint *)((int)DAT_80004104 + 2);
            in_r12 = (uint)*(byte *)(uint *)((int)DAT_80004104 + 1);
          }

          puVar7 = (uint *)((int)DAT_800040f0 + 1);
          *(byte *)DAT_800040f0 = bVar17;
          puVar13 = puVar12;

          if (uVar18 < 2)
          {
            puVar13 = (uint *)((int)puVar12 + 1);
            bVar17 = *(byte *)puVar12;
          }

          puVar12 = puVar7;

          if (uVar18 < 3)
          {
            puVar12 = (uint *)((int)puVar8 + 2);
            *(byte *)puVar7 = (byte)in_r12;
          }

          uVar16 = (uVar16 + uVar18) - 4;
          puVar8 = puVar12;

          if (uVar18 < 2)
          {
            puVar8 = (uint *)((int)puVar12 + 1);
            *(byte *)puVar12 = bVar17;
          }
        }

        uVar10 = (uint)puVar13 & 3;

        if (uVar10 == 0)
        {
          while (uVar18 = uVar16 - 0x20, 0x1f < uVar16)
          {
            uVar16 = puVar13[1];
            uVar10 = puVar13[2];
            uVar9 = puVar13[3];
            *puVar8 = *puVar13;
            puVar8[1] = uVar16;
            puVar8[2] = uVar10;
            puVar8[3] = uVar9;
            uVar10 = puVar13[4];
            uVar16 = puVar13[5];
            uVar9 = puVar13[6];
            uVar11 = puVar13[7];
            puVar13 = puVar13 + 8;
            puVar8[4] = uVar10;
            puVar8[5] = uVar16;
            puVar8[6] = uVar9;
            puVar8[7] = uVar11;
            puVar8 = puVar8 + 8;
            uVar16 = uVar18;
          }

          if ((bool)((byte)(uVar18 >> 4) & 1))
          {
            uVar10 = *puVar13;
            uVar9 = puVar13[1];
            uVar11 = puVar13[2];
            uVar15 = puVar13[3];
            puVar13 = puVar13 + 4;
            *puVar8 = uVar10;
            puVar8[1] = uVar9;
            puVar8[2] = uVar11;
            puVar8[3] = uVar15;
            puVar8 = puVar8 + 4;
          }

          if ((int)(uVar16 << 0x1c) < 0)
          {
            uVar10 = *puVar13;
            uVar9 = puVar13[1];
            puVar13 = puVar13 + 2;
            *puVar8 = uVar10;
            puVar8[1] = uVar9;
            puVar8 = puVar8 + 2;
          }

          puVar7 = puVar8;
          puVar12 = puVar13;

          if ((bool)((byte)(uVar18 >> 2) & 1))
          {
            puVar12 = puVar13 + 1;
            uVar10 = *puVar13;
            puVar7 = puVar8 + 1;
            *puVar8 = uVar10;
          }

          uVar5 = (undefined2)uVar10;

          if ((uVar18 & 3) == 0)
          {
            return CONCAT44(puVar12,puVar7);
          }

          bVar24 = (bool)((byte)(uVar18 >> 1) & 1);
          uVar16 = uVar16 << 0x1f;
          bVar23 = (int)uVar16 < 0;
          puVar13 = puVar12;

          if (bVar24)
          {
            puVar13 = (uint *)((int)puVar12 + 2);
            uVar5 = *(undefined2 *)puVar12;
          }

          puVar8 = puVar13;

          if (bVar23)
          {
            puVar8 = (uint *)((int)puVar13 + 1);
            uVar16 = (uint)*(byte *)puVar13;
          }

          puVar13 = puVar7;

          if (bVar24)
          {
            puVar13 = (uint *)((int)puVar7 + 2);
            *(undefined2 *)puVar7 = uVar5;
          }

          puVar12 = puVar13;

          if (bVar23)
          {
            puVar12 = (uint *)((int)puVar13 + 1);
            *(byte *)puVar13 = (byte)uVar16;
          }
          return CONCAT44(puVar8,puVar12);
        }

        bVar23 = 3 < uVar16;
        uVar16 = uVar16 - 4;

        if (bVar23)
        {
          puVar13 = (uint *)((int)puVar13 - uVar10);
          in_r12 = *puVar13;
          puVar12 = puVar8;

          if (uVar10 == 2)
          {
            do
            {
              puVar7 = puVar13;
              uVar10 = in_r12 >> 0x10;
              puVar13 = puVar7 + 1;
              in_r12 = *puVar13;
              bVar23 = 3 < uVar16;
              uVar16 = uVar16 - 4;
              uVar10 = uVar10 | in_r12 << 0x10;
              puVar8 = puVar12 + 1;
              *puVar12 = uVar10;
              puVar12 = puVar8;
            } while (bVar23);

            puVar13 = (uint *)((int)puVar7 + 6);
          }
          else
          {
            if (uVar10 < 3)
            {
              do
              {
                puVar7 = puVar13;
                uVar10 = in_r12 >> 8;
                puVar13 = puVar7 + 1;
                in_r12 = *puVar13;
                bVar23 = 3 < uVar16;
                uVar16 = uVar16 - 4;
                uVar10 = uVar10 | in_r12 << 0x18;
                puVar8 = puVar12 + 1;
                *puVar12 = uVar10;
                puVar12 = puVar8;
              } while (bVar23);

              puVar13 = (uint *)((int)puVar7 + 5);
            }
            else
            {
              do
              {
                puVar7 = puVar13;
                uVar10 = in_r12 >> 0x18;
                puVar13 = puVar7 + 1;
                in_r12 = *puVar13;
                bVar23 = 3 < uVar16;
                uVar16 = uVar16 - 4;
                uVar10 = uVar10 | in_r12 << 8;
                puVar8 = puVar12 + 1;
                *puVar12 = uVar10;
                puVar12 = puVar8;
              } while (bVar23);
              puVar13 = (uint *)((int)puVar7 + 7);
            }
          }
        }
      }

      bVar20 = (byte)in_r12;
      bVar17 = (byte)uVar10;
      bVar24 = (bool)((byte)(uVar16 >> 1) & 1);
      uVar16 = uVar16 << 0x1f;
      bVar23 = (int)uVar16 < 0;

      if (bVar24)
      {
        pbVar14 = (byte *)((int)puVar13 + 1);
        bVar17 = *(byte *)puVar13;
        puVar13 = (uint *)((int)puVar13 + 2);
        bVar20 = *pbVar14;
      }

      puVar12 = puVar13;

      if (bVar23)
      {
        puVar12 = (uint *)((int)puVar13 + 1);
        uVar16 = (uint)*(byte *)puVar13;
      }

      if (bVar24)
      {
        pbVar14 = (byte *)((int)puVar8 + 1);
        *(byte *)puVar8 = bVar17;
        puVar8 = (uint *)((int)puVar8 + 2);
        *pbVar14 = bVar20;
      }

      puVar13 = puVar8;

      if (bVar23)
      {
        puVar13 = (uint *)((int)puVar8 + 1);
        *(byte *)puVar8 = (byte)uVar16;
      }

      return CONCAT44(puVar12,puVar13);
    }
  } while( true );
}



//------------------------------------------------------------------------------------------------------------------------------------------------

void FUN_80006654(void)
{
  uint uVar1;
  uint uVar2;
  ushort *puVar3;
  uint uVar4;
  uint uVar5;
  ushort *unaff_r4;
  ushort *puVar6;
  int unaff_r5;
  int iVar7;
  ushort uVar8;
  uint uVar9;

  puVar6 = DAT_800067a0;                      //0x801AC04A   sample buffer
  uVar8 = *(ushort *)(DAT_80006798 + 0xec);   //0x801FA24C   channel 1 average

  uVar1 = (uint)uVar8;                        //again average

  uVar5 = 0;

  if (*(char *)(DAT_8000679c + 3) == '\x06')   //0x8019D5A0   channel 1 volt per div
  {
    uVar2 = 0x23;                              //Some minimum value???
  }
  else
  {
    uVar2 = 0x14;                              //Less when signal not doubled
  }

  uVar4 = DAT_800067a4;                        //0x000009C4     2500 number of samples


  if (*(byte *)(DAT_8000679c + 10) < 0x19)     //Time base less then 25 (50mS/div - 500nS/div)
  {
    uVar4 = DAT_800067a8;                      //000005DC       1500 number of samples
  }

  //Skip when signal is high enough
  if (uVar2 <= *(ushort *)(DAT_80006798 + 0xe8))      //signal peak peak
  {
    return;
  }

  //Channel screen offset
  // avg + minimum signal needed less then screen offset or screen offset plus minimum signal needed less then avg
  //Check if the center of the signal is outside the minimal signal band around the center line
  if ((uVar1 + uVar2 < (uint)*(ushort *)(DAT_8000679c + 6)) || (*(ushort *)(DAT_8000679c + 6) + uVar2 < uVar1))
  {
    //some dc component detection with small signal on it

    //Double compensation less then peakpeak
    if (uVar2 >> 1 < (uint)*(ushort *)(DAT_80006798 + 0xe8))  //This is nonsense. Only if signal peak peak is less then uVar2 it can get here!!
    {
      return;
    }

    if (uVar4 == 0)  //What the bullshit here. Is set to a fixed value in the above code!!!!
    {
      return;
    }

    //With full compiler optimisation it probably does not make a difference if the loop does only one sample at a time
    //Plus with the number of samples set above (1500 or 2500) it will always be even number

    puVar3 = DAT_800067a0 + -1;  //Point to 1 sample before buffer

    if ((uVar4 & 1) != 0)        //Odd number of samples to do
    {
      *DAT_800067a0 = uVar8;     //fill the buffer with avg value??
      puVar3 = puVar6;           //sample buffer
    }

    uVar4 = uVar4 >> 1;          //Half the count

    if (uVar4 == 0)              //How can it be zero when you set it to 2500 or 1500!!!!!!!!!
    {
      return;
    }

    do                            //Fill the buffer with average value
    {
      puVar3[1] = uVar8;
      uVar4 = uVar4 - 1;
      puVar3 = puVar3 + 2;
      *puVar3 = uVar8;
    } while (uVar4 != 0);

    return;
  }

  iVar7 = DAT_8000679c;           //Settings base 0x8019D5A0

  if (uVar4 == 0)                 //Again how can it be zero!!!!
  {
    puVar6 = unaff_r4;            //Some stack stuff restore for return. Ghidra nonsense
    iVar7 = unaff_r5;
  }

  uVar2 = 0;                     //Init

  if (uVar4 == 0)                //And again how can it be zero!!!!!!
  {
    return;
  }

  do
  {
    uVar9 = (uint)puVar6[uVar2];   //Sample buffer indexed, so get sample

    if (uVar1 <= uVar9 && uVar9 != uVar1)  //if average less or equal and it is not equal, so sample above average line or not
    {
      //above average line
      if (uVar5 < 0x15)   //starts on zero   so first samples are on offset
      {
LAB_80006738:
        uVar8 = *(ushort *)(iVar7 + 6);           //avg var is channel offset
      }
      else
      {
        uVar5 = 0;                                //Reset counter 
        uVar8 = *(short *)(iVar7 + 6) + 1;        //avg var is offset + 1
      }
    }
    else
    {
      //below average line

      if (uVar1 <= uVar9)                         //Can only be equal since the other if takes the average less then samples
      {
        uVar8 = *(ushort *)(iVar7 + 6);              //avg var is channel offset
        uVar5 = uVar5 + 1 & 0xfffeffff;
      }
      else
      {
        if ((uVar5 < 0x15) || (uVar5 = 0, *(short *)(iVar7 + 6) == 0))  //The offset can't be zero since it is limitited between 7 and 395 but as safe guard checked on zero before subtract 
          goto LAB_80006738;

        uVar8 = *(short *)(iVar7 + 6) - 1;
      }
    }

    puVar6[uVar2] = uVar8;                  //overwrite the sample
    uVar2 = uVar2 + 1 & 0xfffeffff;

    if (uVar4 <= uVar2)  //do all the samples
    {
      return;
    }

  } while( true );
}




//------------------------------------------------------------------------------------------------------------------------------------------------
//calculate_min_max_avg()

void FUN_800049a0(void)

{
  int dividend;
  int iVar1;
  int iVar2;
  ushort *puVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  if (*(byte *)(DAT_80004a40 + 10) < 0xb)   //Time base 
  {
    //50mS/div and 20mS/div
    iVar2 = 100;
    iVar1 = 600;
  }
  else
  {
    //10mS/div - 10nS/div
    iVar2 = 200;
    iVar1 = 0x4b0;    //1200
  }

  //Pointer to starting point in the sample buffer
  puVar3 = (ushort *)(DAT_80004a48 + iVar2 * 2);   //0x801AC04A   buffer where the channel 1 data is finaly stored

  uVar6 = 0;                        //a max value
  dividend = 0;
  uVar4 = iVar1 - iVar2 & 0xffff;   //number of samples to do
  uVar7 = DAT_80004a44;             //0x0000FFFF    a min value

  do
  {
    uVar5 = (uint)*puVar3;          //Get a sample

    if (uVar6 < uVar5)              //Check if max less then sample
    {
      uVar6 = uVar5;                //Save it
    }

    if (uVar5 < uVar7)             //Check if sample less then min value
    {
      uVar7 = uVar5;               //save it
    }

    uVar4 = uVar4 - 1 & 0xffff;    //one sample done

    dividend = dividend + uVar5;   //Add all samples

    puVar3 = puVar3 + 1;           //Point to next one

  } while (uVar4 != 0);

  iVar1 = divide(dividend,iVar1 - iVar2);     //Calculate average sample value

  iVar2 = DAT_80004a4c;

//Signed numbers stored somewhere

  *(short *)(DAT_80004a4c + 0xe4) = (short)uVar6;           //max value
  *(short *)(iVar2 + 0xe6) = (short)uVar7;                  //min value
  *(short *)(iVar2 + 0xea) = (short)(uVar6 + uVar7 >> 1);   // max plus (min / 2)
  *(short *)(iVar2 + 0xe8) = (short)uVar6 - (short)uVar7;   //max minus min = peakpeak
  *(short *)(iVar2 + 0xec) = (short)iVar1;                  //average

  return;
}

//------------------------------------------------------------------------------------------------------------------------------------------------

