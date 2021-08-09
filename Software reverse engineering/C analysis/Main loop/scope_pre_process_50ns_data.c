//------------------------------------------------------------------------------------------------------------------------------------------------

void scope_pre_process_50ns_data(uint16 *buffer,uint offset,uint count)

{
  uint uVar1;
  ushort uVar2;
  longlong lVar3;
  longlong lVar4;
  int iVar5;
  ushort *puVar6;
  uint16 *puVar7;
  undefined2 *puVar8;
  uint uVar9;
  uint16 *puVar10;
  ushort *puVar11;
  undefined2 *puVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  ushort uVar16;
  uint uVar17;
  short sVar18;
  short *psVar19;
  
  uVar9 = count * DAT_8001360c;  //0x0000CCCD
  uVar15 = uVar9 >> 0x13;        // count / 10

  if (uVar15 != 0)
  {
    puVar7 = (uint16 *)((int)buffer + offset * 2);
    puVar8 = DAT_80013610;                                //0x801AEF16  ten samples before
    puVar10 = (uint16 *)((int)puVar7 + -2);

    //First sample loaded from: 0x8019D5EA, 0x8019D5EC, 0x8019D5EE
    //Stored to:                0x801AEF2A, 0x801AEF3E, 0x801AEF52

    if ((uVar15 & 1) != 0)
    {
      puVar8 = DAT_80013610 + 10;
      *puVar8 = *(undefined2 *)puVar7;
      puVar10 = puVar7;
    }

    uVar17 = (uVar15 << 0xf) >> 0x10;

    while (uVar17 != 0)
    {
      puVar8[10] = *(undefined2 *)((int)puVar10 + 2);
      puVar10 = (uint16 *)((int)puVar10 + 4);
      uVar17 = uVar17 - 1 & 0xffff;
      puVar8 = puVar8 + 0x14;
      *puVar8 = *(undefined2 *)puVar10;
    }
  }

  iVar5 = DAT_80013614;   //0x66666667
  uVar17 = 0;

  if (0 < (int)(uVar15 - 1))
  {
    do
    {
      puVar11 = (ushort *)(DAT_80013618 + uVar17 * 0x14);  //801AEF2A  start of buffer
      uVar2 = *puVar11;        //sample 1   0x801AEF2A, 0x801AEF3E, 0x801AEF52
      uVar16 = puVar11[10];    //sample 2   0x801AEF3E, 0x801AEF52, 0x801AEF66

      if (uVar2 < uVar16)
      {
        uVar1 = (uint)(ushort)(uVar16 - uVar2);   //Positive delta
        iVar13 = 1;
        sVar18 = 4;
        puVar11 = puVar11 + 1;  //sample 2

        //one tenth step????
        *puVar11 = ((short)(int)((longlong)iVar5 * (longlong)(int)uVar1 >> 0x22) - (short)((longlong)iVar5 * (longlong)(int)uVar1 >> 0x3f)) + uVar2;  //0x801AEF2C

        do
        {
          lVar3 = (longlong)iVar5 * (longlong)(int)(uVar1 * (iVar13 + 2));  //3 tenths
          lVar4 = (longlong)iVar5 * (longlong)(int)(uVar1 * (iVar13 + 1));  //2 tenths
          sVar18 = sVar18 + -1;
          puVar11[1] = ((short)(int)(lVar4 >> 0x22) - (short)(lVar4 >> 0x3f)) + uVar2;  //0x801AEF2E
          iVar13 = iVar13 + 2;
          puVar11 = puVar11 + 2;
          *puVar11 = ((short)(int)(lVar3 >> 0x22) - (short)(lVar3 >> 0x3f)) + uVar2;    //0x801AEF30
        } while (sVar18 != 0);
      }
      else
      {
        uVar1 = (uint)(ushort)(uVar2 - uVar16);
        iVar13 = 1;
        sVar18 = 4;
        puVar11 = puVar11 + 1;
        *puVar11 = uVar2 - ((short)(int)((longlong)iVar5 * (longlong)(int)uVar1 >> 0x22) - (short)((longlong)iVar5 * (longlong)(int)uVar1 >> 0x3f));

        do
        {
          lVar3 = (longlong)iVar5 * (longlong)(int)(uVar1 * (iVar13 + 2));
          lVar4 = (longlong)iVar5 * (longlong)(int)(uVar1 * (iVar13 + 1));
          sVar18 = sVar18 + -1;
          puVar11[1] = uVar2 - ((short)(int)(lVar4 >> 0x22) - (short)(lVar4 >> 0x3f));
          iVar13 = iVar13 + 2;
          puVar11 = puVar11 + 2;
          *puVar11 = uVar2 - ((short)(int)(lVar3 >> 0x22) - (short)(lVar3 >> 0x3f));
        } while (sVar18 != 0);
      }

      uVar17 = uVar17 + 1 & 0xfffeffff;
    } while ((int)uVar17 < (int)(uVar15 - 1));
  }

  //Third bit
  uVar17 = uVar15 - 1;

  if (0 < (int)uVar17)
  {
    puVar8 = DAT_80013620;     //r3  0x801B8B60
    puVar12 = DAT_8001361c;    //r12 0x801AEF20      5 samples before

    if ((uVar17 & 1) != 0)
    {
      puVar12 = DAT_8001361c + 10;         //0x801AEF34
      puVar8 = DAT_80013620 + 10;          //0x801B8B74
      *puVar8 = *puVar12;                  //Store at 0x801B8B74, load from 0x801aef34
    }

    uVar17 = uVar17 * 0x8000 >> 0x10;  // /2

    while (uVar17 != 0)
    {
      puVar8[10] = puVar12[10];            //0x801AEF48 ==> 0x801B8B88, 0x801AEF70 ==> 0x801B8BB0, 0x801AEF98 ==> 0x801B8BD8, ---- 0x801B0280 ==> 0x801B9EC0
      puVar12 = puVar12 + 0x14;
      uVar17 = uVar17 - 1 & 0xffff;
      puVar8 = puVar8 + 0x14;              //0x801AEF5C ==> 0x801B8B9C, 0x801AEF84 ==> 0x801B8BC4, 0x801AEFAC ==> 0x801B8BEC, ---- 0x801B0294 ==> 0x801B9ED4
      *puVar8 = *puVar12;
    }
  }

  //Fourth bit
  //Up sample a second set of samples
  uVar17 = 0;

  if (0 < (int)(uVar15 - 2))
  {
    do
    {                                          //Not sure if this is correct. Needs checking
      iVar13 = DAT_80013624 + uVar17 * 0x14;   //0x801B8B6A  5 samples before the data???
      uVar2 = *(ushort *)(iVar13 + 10);        //sample1 from start of buffer (first sample)    0x801B8B74,  0x801B8B88
      uVar16 = *(ushort *)(iVar13 + 0x1e);     //sample2 from 10th sample                       0x801B8B88,  0x801B8B9C

      if (uVar2 < uVar16)
      {
        uVar1 = (uint)(ushort)(uVar16 - uVar2);  //delta
        iVar14 = 1;
        sVar18 = 4;
        psVar19 = (short *)(iVar13 + 0xc);  //second sample in buffer
        *psVar19 = ((short)(int)((longlong)iVar5 * (longlong)(int)uVar1 >> 0x22) - (short)((longlong)iVar5 * (longlong)(int)uVar1 >> 0x3f)) + uVar2;  //0x801B8B76, 0x801B8B8A

        do
        {
          lVar3 = (longlong)iVar5 * (longlong)(int)(uVar1 * (iVar14 + 1));
          lVar4 = (longlong)iVar5 * (longlong)(int)(uVar1 * (iVar14 + 2));
          sVar18 = sVar18 + -1;
          psVar19[1] = ((short)(int)(lVar3 >> 0x22) - (short)(lVar3 >> 0x3f)) + uVar2;  //0x801B8B78, 0x801B8B7C, 0x801B8B80, 0x801B8B84
          iVar14 = iVar14 + 2;
          psVar19 = psVar19 + 2;
          *psVar19 = ((short)(int)(lVar4 >> 0x22) - (short)(lVar4 >> 0x3f)) + uVar2;    //0x801B8B7A, 0x801B8B7E, 0x801B8B82, 0x801B8B86
        } while (sVar18 != 0);
      }
      else
      {
        uVar1 = (uint)(ushort)(uVar2 - uVar16);
        iVar14 = 1;
        sVar18 = 4;
        psVar19 = (short *)(iVar13 + 0xc);
        *psVar19 = uVar2 - ((short)(int)((longlong)iVar5 * (longlong)(int)uVar1 >> 0x22) - (short)((longlong)iVar5 * (longlong)(int)uVar1 >> 0x3f));

        do
        {
          lVar3 = (longlong)iVar5 * (longlong)(int)(uVar1 * (iVar14 + 1));
          lVar4 = (longlong)iVar5 * (longlong)(int)(uVar1 * (iVar14 + 2));
          sVar18 = sVar18 + -1;
          psVar19[1] = uVar2 - ((short)(int)(lVar3 >> 0x22) - (short)(lVar3 >> 0x3f));
          iVar14 = iVar14 + 2;
          psVar19 = psVar19 + 2;
          *psVar19 = uVar2 - ((short)(int)(lVar4 >> 0x22) - (short)(lVar4 >> 0x3f));
        } while (sVar18 != 0);
      }

      uVar17 = uVar17 + 1 & 0xfffeffff;
    } while ((int)uVar17 < (int)(uVar15 - 2));
  }




  //This is wrong since no data has been written to 0x801B8B6A

  //Fifth bit
  uVar15 = count >> 1;

  if (count != 0)
  {
    uVar17 = uVar15;
    puVar10 = (uint16 *)((int)buffer + -2);
    puVar11 = DAT_80013628;    //0x801AEF28     1 sample before the actual buffer
    puVar6 = DAT_8001362c;     //0x801B8B68     1 sample before the actual buffer

    if ((count & 1) != 0)
    {
      puVar11 = DAT_80013628 + 1;
      puVar6 = DAT_8001362c + 1;
      *(short *)buffer = (short)((uint)*puVar11 + (uint)*puVar6 >> 1);
      puVar10 = buffer;
    }


    //Average the samples from the two interpolations. Only problem is that they start at a wrong address for the second data????
    while (uVar17 != 0)
    {
      *(short *)((int)puVar10 + 2) = (short)((uint)puVar11[1] + (uint)puVar6[1] >> 1);               //(0x801AEF2A, 0x801B8B6A) ==> 0x8019D5EA
      *(short *)(uint16 *)((int)puVar10 + 4) = (short)((uint)puVar11[2] + (uint)puVar6[2] >> 1);     //(0x801AEF2C, 0x801B8B6C) ==> 0x8019D5EC
      uVar17 = uVar17 - 1;
      puVar10 = (uint16 *)((int)puVar10 + 4); //Dest plus two samples
      puVar11 = puVar11 + 2;                  //Src plus one sample
      puVar6 = puVar6 + 2;                    //Src plus one sample
    }
  }








  //Sixth bit
  uVar9 = uVar9 >> 0x12;   //count / 5
  uVar17 = uVar9 - 1;      //499 samples to process

  if (0 < (int)uVar17)
  {
    puVar12 = (undefined2 *)((int)buffer + -6);
    puVar8 = DAT_80013630;                                 //0x801B8B64  Again second temp buffer

    if ((uVar17 & 1) != 0)
    {
      puVar12 = (undefined2 *)((int)buffer + 4);
      puVar8 = DAT_80013630 + 5;
      *puVar8 = *puVar12;                                 //0x8019D5EE ==> 0x801B8B6E
    }

    //Div by two
    uVar17 = uVar17 * 0x8000 >> 0x10;

    while (uVar17 != 0)
    {                                                    //Copy from buffer to temp buffer with a 5 sample interval
      puVar8[5] = puVar12[5];                            //0x8019D5F8 ==> 0x801B8B78, 0x8019D60C ==> 0x801B8B8C
      puVar12 = puVar12 + 10;
      uVar17 = uVar17 - 1 & 0xffff;
      puVar8 = puVar8 + 10;
      *puVar8 = *puVar12;                                //0x8019D602 ==> 0x801B8B82, 0x8019D616 ==> 0x801B8B96
    }
  }




  //Seventh bit
  uVar17 = DAT_80013638;   //0xCCCCCCCD

  //Do two samples less
  uVar9 = uVar9 - 2;  //498

  //Interpolate between the five samples
  if (0 < (int)uVar9)
  {
    uVar9 = uVar9 & 0xffff;
    puVar11 = DAT_80013634;    //0x801B8B6E second temp buffer x samples before

    do
    {
      uVar2 = *puVar11;           //Sample 1   0x801B8B6E
      uVar16 = puVar11[5];        //Sample 2   0x801B8B78

      if (uVar2 < uVar16)
      {
        uVar16 = uVar16 - uVar2;
        puVar11[1] = uVar2 + (ushort)((uint)uVar16 * DAT_8001360c >> 0x12);
        puVar11[2] = (short)(uint)((ulonglong)uVar16 * 2 * (ulonglong)uVar17 >> 0x22) + uVar2;
        sVar18 = (short)(uint)((ulonglong)uVar16 * 4 * (ulonglong)uVar17 >> 0x22);
        puVar11[3] = (short)(uint)((ulonglong)((uint)uVar16 * 3) * (ulonglong)uVar17 >> 0x22) + uVar2;
      }
      else
      {
        uVar16 = uVar2 - uVar16;
        puVar11[1] = uVar2 - (ushort)((uint)uVar16 * DAT_8001360c >> 0x12);
        puVar11[2] = uVar2 - (short)(uint)((ulonglong)uVar16 * 2 * (ulonglong)uVar17 >> 0x22);
        sVar18 = -(short)(uint)((ulonglong)uVar16 * 4 * (ulonglong)uVar17 >> 0x22);
        puVar11[3] = uVar2 - (short)(uint)((ulonglong)((uint)uVar16 * 3) * (ulonglong)uVar17 >> 0x22);
      }

      puVar11[4] = uVar2 + sVar18;
      uVar9 = uVar9 - 1 & 0xffff;
      puVar11 = puVar11 + 5;
    } while (uVar9 != 0);
  }



  //Eight bit
  if (count != 0)   //2500
  {
    puVar10 = (uint16 *)((int)buffer + -2);
    puVar11 = DAT_8001362c;

    if ((count & 1) != 0)
    {
      puVar11 = DAT_8001362c + 1;
      *(short *)buffer = (short)((uint)*(ushort *)buffer + (uint)*puVar11 >> 1);
      puVar10 = buffer;
    }

    //Again an error in first sample pointer
    //Average the samples again with the 5 time up sampled data
    if (uVar15 != 0)  //1250
    {
      do
      {
        puVar6 = (ushort *)((int)puVar10 + 2);    //Point to sample buffer

        uVar15 = uVar15 - 1;                      //One set done

        puVar10 = (uint16 *)((int)puVar10 + 4);   //Point to second sample in buffer

        *puVar6 = (ushort)((uint)*puVar6 + (uint)puVar11[1] >> 1);                        //0x8019D5EA + 0x801B8B6A ==> 0x8019D5EA,  0x8019D5EE + 0x801B8B6E  ==> 0x8019D5EE

        puVar11 = puVar11 + 2;

        *(ushort *)puVar10 = (ushort)((uint)*puVar11 + (uint)*(ushort *)puVar10 >> 1);    //0x8019D5EC + 0x801B8B6C ==> 0x8019D5EC,  0x8019D5F0 + 0x801B8B70 ==> 0x8019D5F0

      } while (uVar15 != 0);

      return;
    }

    return;
  }

  return;
}

//------------------------------------------------------------------------------------------------------------------------------------------------




