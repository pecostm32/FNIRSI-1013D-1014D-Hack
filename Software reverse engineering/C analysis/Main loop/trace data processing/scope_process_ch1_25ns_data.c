void scope_process_ch1_25ns_data(void)
{
  ushort uVar1;
  longlong lVar2;
  longlong lVar3;
  undefined2 uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  ushort *puVar8;
  int iVar9;
  uint16 *puVar10;
  ushort *puVar11;
  undefined2 *puVar12;
  ushort uVar13;
  short *psVar14;
  int iVar15;
  ushort uVar16;
  short sVar17;
  uint uVar18;
  uint uVar19;
  undefined4 uVar20;
  uint16 *puVar21;
  int iVar22;
  uint16 *puVar23;
  undefined2 *puVar24;
  undefined8 uVar25;
  undefined8 uVar26;
  undefined8 uVar27;
  undefined8 uVar28;
  undefined8 uVar29;
  undefined8 uVar30;
  
  uVar19 = DAT_80006504;                              //0x000009C4   2500
  iVar22 = DAT_80006500;                              //0x8019D5A0   settings base
  uVar7 = 0;
  puVar8 = (ushort *)((int)DAT_800064f0 + 200);       //0x8019D5EA   sample buffer + 200 (100 samples in)  (&channel1tracebuffer1[100])
  uVar20 = 0;
  iVar9 = DAT_800064f8;                               //0x0000056E   1390
  uVar18 = DAT_800064f4;                              //0x0000FFFF   65535

  //Loop through 1390 samples
  //Start on 0x8019D6B2 (100 samples into the buffer)
  do
  {
    uVar5 = (uint)*puVar8;  //Get the sample
    puVar8 = puVar8 + 1;

    //Determine max value
    if (uVar7 < uVar5)
    {
      uVar7 = uVar5;
    }

    //Determine min value
    if (uVar5 < uVar18)
    {
      uVar18 = uVar5;
    }

    iVar9 = iVar9 + -1;
  } while (iVar9 != 0);


  
  puVar21 = (uint16 *)(uVar7 + uVar18 >> 1);           //Average between min and max

  uVar5 = 0;

  puVar8 = (ushort *)((int)DAT_800064f0 + 0x14);       //                   &channel1tracebuffer1[10]
  iVar9 = DAT_800064fc;                                //0x000005C8         1480
  puVar23 = DAT_800064f0;                              //0x8019D5EA         channel1tracebuffer1


  //Determine if there is high frequency signal in the buffer (more then 320 rising edges)
  //Loop through 1480 samples
  //Start on 0x8019D5FE
  do
  {
    puVar10 = (uint16 *)(uint)*puVar8;            //Get sample

    if (puVar10 < puVar21)                        //Check sample against average
    {
      puVar23 = (uint16 *)(uint)puVar8[1];        //Below average then get the next sample too
    }


    //Need to figure this out on what it is counting

    //first sample below average and second sample above average or second sample above or equal to average
    //Count the rising edges in the buffer discriminating on a single bit 
    //The first part of the if is abundant
    if ((puVar10 < puVar21 && puVar21 < puVar23) || ((puVar10 < puVar21 && (puVar21 <= (uint16 *)(uint)puVar8[1]))))
    {
      uVar5 = uVar5 + 1 & 0xfffeffff;   //Count the number of samples that comply to what???
    }

    iVar9 = iVar9 + -1;       //one sample done
    puVar8 = puVar8 + 1;      //select next sample
  } while (iVar9 != 0);



/*
                             LAB_80006320                                    XREF[1]:     80006358(j)  
        80006320 b0 30 d0 e1     ldrh       r3,[r0,#0x0]=>DAT_8019d5fe       ;get a sample
        80006324 01 00 53 e1     cmp        r3,r1                            ;compare it to the average
        80006328 b2 c0 d0 31     ldrhcc     r12,[r0,#0x2]=>DAT_8019d600      ;if below average get the next sample
        8000632c 0c 00 51 31     cmpcc      r1,r12                           ;and compare the average with it
        80006330 04 00 00 3a     bcc        LAB_80006348                     ;average below then jump to count
        80006334 03 00 51 e1     cmp        r1,r3                            ;compare average with first sample again
        80006338 04 00 00 9a     bls        LAB_80006350                     ;average less then jump
        8000633c b2 30 d0 e1     ldrh       r3,[r0,#0x2]=>DAT_8019d600       ;get the next sanmple
        80006340 03 00 51 e1     cmp        r1,r3                            ;compare the average with it
        80006344 01 00 00 8a     bhi        LAB_80006350                     ;average higher then jump
                             LAB_80006348                                    XREF[1]:     80006330(j)  
        80006348 01 30 84 e2     add        r3,r4,#0x1                       ;increment the counter
        8000634c 01 48 c3 e3     bic        r4,r3,#0x10000
                             LAB_80006350                                    XREF[2]:     80006338(j), 80006344(j)  
        80006350 01 20 52 e2     subs       r2,r2,#0x1                       ;one sample set done
        80006354 02 00 80 e2     add        r0=>DAT_8019d600,r0,#0x2         ;point to next sample
        80006358 f0 ff ff 1a     bne        LAB_80006320                     ;repeat until done
*/




  //If more then 320 samples comply do this next bit. This means high frequency signal or noise
  //This is the case in the emulator with the given input (alternates on every sample between 0x6D and 0xB0 or 0x90)
  if (0x140 < uVar5)
  {
    uVar6 = get_timer_ticks();
    puVar21 = DAT_800064f0;                            //0x8019D5EA         channel1tracebuffer1

    if (*(char *)(iVar22 + 10) == '\x1c')              //time base = 25nS/div
    {
      uVar20 = 0x14;                                   //20
    }

    if (*(char *)(iVar22 + 10) == '\x1d')              //time base = 10nS/div
    {
      uVar20 = 0x32;                                   //50
    }

    iVar9 = 0;

    //y + (((y * 2863311531) / 8589934592) * -3)
    //2863311531 / 8589934592 ~ 1/3 so the rounding of error leads to a modulo 3
    //Is indeed %3 based on the timer ticks. What is the use of it. Some sort of random number input????
    uVar25 = FUN_800397d0(uVar6 + (uint)((ulonglong)uVar6 * (ulonglong)DAT_80006508 >> 0x21) * -3);   //do some calc on the timer ticks???
    //input = 1, output ==> r0 = 0, r1 = 0x3FF00000

    uVar26 = FUN_800397d0(uVar18);                          //min value
    //input = 0x6D, output ==> r0 = 0, r1 = 0x405B4000

    uVar27 = FUN_800397d0((uVar7 - uVar18 & 0xffff) >> 1);  //max minus min value / 2
    //input = 0x21, output ==> r0 = 0, r1 = 0x40408000

    uVar28 = FUN_800397d0(uVar5);                           //number of rising edges
    //input = 0x2E4, output ==> r0 = 0, r1 = 0x40872000

    uVar29 = FUN_800397d0(uVar20);                          //Time base dependent input
    //input = 0x14, output ==> r0 = 0, r1 = 0x40340000
    //input = 0x32, output ==> r0 = 0, r1 = 0x40490000


    uVar29 = FUN_800393ec(DAT_8000650c,DAT_80006510,(int)uVar29,(int)((ulonglong)uVar29 >> 0x20));  //0x53AFAA7D, 0x3F816151, 0x00, 0x40340000
    //output ==> r0 = 0x85E5DD95, r1 = 0x3F3BCEE8

    //Process 2500 samples???
    do
    {
      //Sample index as input
      uVar30 = FUN_8003979c(iVar9);  //similar action as FUN_800397d0 but a check on being negative and make positive is done before clz. Never the case here

      //time base dependent re calculated input
      uVar30 = FUN_80039890((int)uVar30,(int)((ulonglong)uVar30 >> 0x20),(int)uVar29,(int)((ulonglong)uVar29 >> 0x20));

      //number of rising edges input
      FUN_80039890((int)uVar30,(int)((ulonglong)uVar30 >> 0x20),(int)uVar28,(int)((ulonglong)uVar28 >> 0x20));

      uVar30 = FUN_80036000();

      uVar30 = FUN_8003926c((int)uVar30,(int)((ulonglong)uVar30 >> 0x20),0,DAT_80006514);  //r0, r1, 0x3FF00000

      //max minus min value / 2 as input
      uVar30 = FUN_80039890((int)uVar30,(int)((ulonglong)uVar30 >> 0x20),(int)uVar27,(int)((ulonglong)uVar27 >> 0x20));

      //min value as input
      uVar30 = FUN_8003926c((int)uVar30,(int)((ulonglong)uVar30 >> 0x20),(int)uVar26,(int)((ulonglong)uVar26 >> 0x20));

      //Timer ticks modulo as input
      FUN_8003926c((int)uVar30,(int)((ulonglong)uVar30 >> 0x20),(int)uVar25,(int)((ulonglong)uVar25 >> 0x20));


      uVar4 = FUN_8003972c();

      *(undefined2 *)puVar21 = uVar4;

      uVar19 = uVar19 - 1 & 0xffff;             //one sample done
      iVar9 = iVar9 + 1;                        //next index
      puVar21 = (uint16 *)((int)puVar21 + 2);   //point to next buffer entry
    } while (uVar19 != 0);

    return;
  }

  if (*(char *)(DAT_80006500 + 10) == '\x1c')   //0x8019D5AA is time base setting 28 = 25nS/div
  {
    //With 5nS per sample this up sampling leads to 25nS/div. Every tenth pixel is 5nS, so 50 pixels is 25nS
    scope_up_sample_x_10(DAT_800064f0,0,DAT_80006504);
  }

  puVar21 = DAT_800064f0;




  //scope_up_sample_x_25()
  //From here on down is for 10nS/div time base setting. Most likely it is the up sampling needed to go from 5nS per sample
  //to 10nS/div. With 50 pixels per div each pixel is 200pS, so need up sampling x_25
  if (*(char *)(iVar22 + 10) == '\x1d')
  {
    puVar8 = (ushort *)(uVar19 * DAT_80013e70 + 0xa3d7 >> 0x14);  //2500 

    if (puVar8 != NULL)
    {
      puVar11 = DAT_80013e74;
      puVar23 = (uint16 *)((int)DAT_800064f0 + -2);

      if (((uint)puVar8 & 1) != 0)
      {
        puVar11 = DAT_80013e74 + 0x19;
        *puVar11 = *(ushort *)DAT_800064f0;
        puVar23 = puVar21;
      }

      uVar7 = (uint)((int)puVar8 << 0xf) >> 0x10;

      while (uVar7 != 0)
      {
        puVar11[0x19] = *(ushort *)((int)puVar23 + 2);
        puVar23 = (uint16 *)((int)puVar23 + 4);
        uVar7 = uVar7 - 1 & 0xffff;
        puVar11 = puVar11 + 0x32;
        *puVar11 = *(ushort *)puVar23;
      }
    }

    iVar22 = DAT_80013e78;
    uVar7 = 0;

    if (0 < (int)((int)puVar8 - 1U))
    {
      do {
        puVar11 = (ushort *)(DAT_80013e7c + uVar7 * 0x32);
        uVar1 = *puVar11;
        uVar13 = puVar11[0x19];
        sVar17 = 0xc;
        if (uVar1 < uVar13) {
          uVar16 = uVar13 - uVar1;
        }
        else {
          uVar16 = uVar1 - uVar13;
        }
        iVar9 = 0;
        uVar18 = (uint)uVar16;
        if (uVar1 < uVar13) {
          do {
            lVar2 = (longlong)iVar22 * (longlong)(int)(uVar18 * (iVar9 + 2));
            lVar3 = (longlong)iVar22 * (longlong)(int)(uVar18 * (iVar9 + 1));
            sVar17 = sVar17 + -1;
            puVar11[1] = ((short)(int)(lVar3 >> 0x23) - (short)(lVar3 >> 0x3f)) + uVar1;
            iVar9 = iVar9 + 2;
            puVar11 = puVar11 + 2;
            *puVar11 = ((short)(int)(lVar2 >> 0x23) - (short)(lVar2 >> 0x3f)) + uVar1;
          } while (sVar17 != 0);
        }
        else {
          do {
            lVar2 = (longlong)iVar22 * (longlong)(int)(uVar18 * (iVar9 + 2));
            lVar3 = (longlong)iVar22 * (longlong)(int)(uVar18 * (iVar9 + 1));
            sVar17 = sVar17 + -1;
            puVar11[1] = uVar1 - ((short)(int)(lVar3 >> 0x23) - (short)(lVar3 >> 0x3f));
            iVar9 = iVar9 + 2;
            puVar11 = puVar11 + 2;
            *puVar11 = uVar1 - ((short)(int)(lVar2 >> 0x23) - (short)(lVar2 >> 0x3f));
          } while (sVar17 != 0);
        }
        uVar7 = uVar7 + 1 & 0xfffeffff;
      } while ((int)uVar7 < (int)((int)puVar8 - 1U));
    }

    uVar7 = (int)puVar8 - 1;
    if (0 < (int)uVar7)
    {
      puVar12 = DAT_80013e84;
      puVar24 = DAT_80013e80;

      if ((uVar7 & 1) != 0)
      {
        puVar24 = DAT_80013e80 + 0x19;
        puVar12 = DAT_80013e84 + 0x19;
        *puVar12 = *puVar24;
      }

      uVar7 = uVar7 * 0x8000 >> 0x10;

      while (uVar7 != 0)
      {
        puVar12[0x19] = puVar24[0x19];
        puVar24 = puVar24 + 0x32;
        uVar7 = uVar7 - 1 & 0xffff;
        puVar12 = puVar12 + 0x32;
        *puVar12 = *puVar24;
      }
    }

    uVar7 = 0;
    puVar11 = puVar8 + -1;

    if (0 < (int)puVar11)
    {
      do
      {
        iVar9 = DAT_80013e88 + uVar7 * 0x32;
        uVar1 = *(ushort *)(iVar9 + 0x18);
        uVar13 = *(ushort *)(iVar9 + 0x4a);

        if (uVar1 < uVar13)
        {
          psVar14 = (short *)(iVar9 + 0x18);
          iVar9 = 0;
          sVar17 = 0xc;

          do
          {
            lVar2 = (longlong)iVar22 * (longlong)(int)((uint)(ushort)(uVar13 - uVar1) * (iVar9 + 1));
            lVar3 = (longlong)iVar22 * (longlong)(int)((uint)(ushort)(uVar13 - uVar1) * (iVar9 + 2));
            sVar17 = sVar17 + -1;
            psVar14[1] = ((short)(int)(lVar2 >> 0x23) - (short)(lVar2 >> 0x3f)) + uVar1;
            iVar9 = iVar9 + 2;
            psVar14 = psVar14 + 2;
            *psVar14 = ((short)(int)(lVar3 >> 0x23) - (short)(lVar3 >> 0x3f)) + uVar1;
          } while (sVar17 != 0);
        }
        else
        {
          psVar14 = (short *)(iVar9 + 0x18);
          iVar9 = 0;
          sVar17 = 0xc;

          do
          {
            lVar2 = (longlong)iVar22 * (longlong)(int)((uint)(ushort)(uVar1 - uVar13) * (iVar9 + 1));
            lVar3 = (longlong)iVar22 * (longlong)(int)((uint)(ushort)(uVar1 - uVar13) * (iVar9 + 2));
            sVar17 = sVar17 + -1;
            psVar14[1] = uVar1 - ((short)(int)(lVar2 >> 0x23) - (short)(lVar2 >> 0x3f));
            iVar9 = iVar9 + 2;
            psVar14 = psVar14 + 2;
            *psVar14 = uVar1 - ((short)(int)(lVar3 >> 0x23) - (short)(lVar3 >> 0x3f));
          } while (sVar17 != 0);
        }

        puVar8 = (ushort *)(uVar7 + 1);
        uVar7 = (uint)puVar8 & 0xfffeffff;
      } while ((int)uVar7 < (int)puVar11);
    }

    uVar7 = uVar19 >> 1;

    if (uVar19 != 0)
    {
      uVar18 = uVar7;
      puVar11 = DAT_80013e90;
      puVar8 = DAT_80013e8c;
      puVar23 = (uint16 *)((int)puVar21 + -2);

      if ((uVar19 & 1) != 0)
      {
        puVar8 = DAT_80013e8c + 1;
        puVar11 = DAT_80013e90 + 1;
        *(short *)puVar21 = (short)((uint)*puVar8 + (uint)*puVar11 >> 1);
        puVar23 = puVar21;
      }

      while (uVar18 != 0)
      {
        *(short *)((int)puVar23 + 2) = (short)((uint)puVar8[1] + (uint)puVar11[1] >> 1);
        *(short *)(uint16 *)((int)puVar23 + 4) = (short)((uint)puVar11[2] + (uint)puVar8[2] >> 1);
        uVar18 = uVar18 - 1;
        puVar11 = puVar11 + 2;
        puVar8 = puVar8 + 2;
        puVar23 = (uint16 *)((int)puVar23 + 4);
      }
    }

    uVar5 = uVar19 * DAT_80013e94;
    uVar18 = uVar5 >> 0x13;
    uVar6 = uVar18 - 1;

    if (0 < (int)uVar6)
    {
      puVar11 = (ushort *)((int)puVar21 + -0xc);
      puVar8 = DAT_80013e98;

      if ((uVar6 & 1) != 0)
      {
        puVar11 = (ushort *)((int)puVar21 + 0xc);
        puVar8 = DAT_80013e98 + 0xc;
        *puVar8 = *puVar11;
      }

      uVar6 = uVar6 * 0x8000 >> 0x10;

      while (uVar6 != 0)
      {
        puVar8[0xc] = puVar11[0xc];
        puVar11 = puVar11 + 0x18;
        uVar6 = uVar6 - 1 & 0xffff;
        puVar8 = puVar8 + 0x18;
        *puVar8 = *puVar11;
      }
    }
    iVar22 = uVar18 - 2;

    if (0 < iVar22)
    {
      puVar8 = DAT_80013e9c;
    }

    uVar18 = 0;

    if (0 < iVar22)
    {
      do
      {
        iVar9 = DAT_80013e88 + uVar18 * 0x18;
        uVar1 = *(ushort *)(iVar9 + 0xc);
        uVar13 = *(ushort *)(iVar9 + 0x24);

        if (uVar1 < uVar13)
        {
          uVar6 = (uint)(ushort)(uVar13 - uVar1);
          iVar15 = 1;
          sVar17 = 5;
          psVar14 = (short *)(iVar9 + 0xe);
          *psVar14 = ((short)(int)((longlong)(int)puVar8 * (longlong)(int)uVar6 >> 0x21) - (short)((longlong)(int)puVar8 * (longlong)(int)uVar6 >> 0x3f)) + uVar1;

          do
          {
            lVar2 = (longlong)(int)puVar8 * (longlong)(int)(uVar6 * (iVar15 + 1));
            lVar3 = (longlong)(int)puVar8 * (longlong)(int)(uVar6 * (iVar15 + 2));
            sVar17 = sVar17 + -1;
            psVar14[1] = ((short)(int)(lVar2 >> 0x21) - (short)(lVar2 >> 0x3f)) + uVar1;
            iVar15 = iVar15 + 2;
            psVar14 = psVar14 + 2;
            *psVar14 = ((short)(int)(lVar3 >> 0x21) - (short)(lVar3 >> 0x3f)) + uVar1;
          } while (sVar17 != 0);
        }
        else
        {
          uVar6 = (uint)(ushort)(uVar1 - uVar13);
          iVar15 = 1;
          sVar17 = 5;
          psVar14 = (short *)(iVar9 + 0xe);
          *psVar14 = uVar1 - ((short)(int)((longlong)(int)puVar8 * (longlong)(int)uVar6 >> 0x21) - (short)((longlong)(int)puVar8 * (longlong)(int)uVar6 >> 0x3f));

          do
          {
            lVar2 = (longlong)(int)puVar8 * (longlong)(int)(uVar6 * (iVar15 + 1));
            lVar3 = (longlong)(int)puVar8 * (longlong)(int)(uVar6 * (iVar15 + 2));
            sVar17 = sVar17 + -1;
            psVar14[1] = uVar1 - ((short)(int)(lVar2 >> 0x21) - (short)(lVar2 >> 0x3f));
            iVar15 = iVar15 + 2;
            psVar14 = psVar14 + 2;
            *psVar14 = uVar1 - ((short)(int)(lVar3 >> 0x21) - (short)(lVar3 >> 0x3f));
          } while (sVar17 != 0);
        }

        uVar18 = uVar18 + 1 & 0xfffeffff;
      } while ((int)uVar18 < iVar22);
    }

    if (uVar19 != 0)
    {
      uVar18 = uVar7;
      puVar23 = (uint16 *)((int)puVar21 + -2);
      puVar8 = DAT_80013e90;

      if ((uVar19 & 1) != 0)
      {
        puVar8 = DAT_80013e90 + 1;
        *(short *)puVar21 = (short)((uint)*(ushort *)puVar21 + (uint)*puVar8 >> 1);
        puVar23 = puVar21;
      }

      while (uVar18 != 0)
      {
        puVar10 = (uint16 *)((int)puVar23 + 4);
        *(ushort *)((int)puVar23 + 2) = (ushort)((uint)*(ushort *)((int)puVar23 + 2) + (uint)puVar8[1] >> 1);
        *(ushort *)puVar10 = (ushort)((uint)puVar8[2] + (uint)*(ushort *)puVar10 >> 1);
        uVar18 = uVar18 - 1;
        puVar23 = puVar10;
        puVar8 = puVar8 + 2;
      }
    }

    uVar5 = uVar5 >> 0x12;
    uVar18 = uVar5 - 1;

    if (0 < (int)uVar18)
    {
      puVar11 = (ushort *)((int)puVar21 + -6);
      puVar8 = DAT_80013ea0;

      if ((uVar18 & 1) != 0)
      {
        puVar11 = (ushort *)((int)puVar21 + 6);
        puVar8 = DAT_80013ea0 + 6;
        *puVar8 = *puVar11;
      }

      uVar18 = uVar18 * 0x8000 >> 0x10;

      while (uVar18 != 0)
      {
        puVar8[6] = puVar11[6];
        puVar11 = puVar11 + 0xc;
        uVar18 = uVar18 - 1 & 0xffff;
        puVar8 = puVar8 + 0xc;
        *puVar8 = *puVar11;
      }
    }

    uVar18 = DAT_80013ea8;
    uVar5 = uVar5 - 2;

    if (0 < (int)uVar5)
    {
      uVar5 = uVar5 & 0xffff;
      puVar8 = DAT_80013ea4;

      do
      {
        uVar1 = *puVar8;
        uVar13 = puVar8[6];

        if (uVar1 < uVar13)
        {
          uVar13 = uVar13 - uVar1;
          uVar6 = (uint)uVar13;
          puVar8[1] = uVar1 + (ushort)(uVar6 * DAT_80013e94 >> 0x12);
          puVar8[2] = uVar1 + (short)(uint)((ulonglong)uVar13 * 2 * (ulonglong)uVar18 >> 0x22);
          puVar8[3] = uVar1 + (short)(uint)((ulonglong)(uVar6 * 3) * (ulonglong)uVar18 >> 0x22);
          puVar8[4] = uVar1 + (short)(uint)((ulonglong)uVar13 * 4 * (ulonglong)uVar18 >> 0x22);
          puVar8[5] = uVar1 + (short)(uint)((ulonglong)(uVar6 * 5) * (ulonglong)uVar18 >> 0x22);
        }
        else
        {
          uVar13 = uVar1 - uVar13;
          uVar6 = (uint)uVar13;
          puVar8[1] = uVar1 - (ushort)(uVar6 * DAT_80013e94 >> 0x12);
          puVar8[2] = uVar1 - (short)(uint)((ulonglong)uVar13 * 2 * (ulonglong)uVar18 >> 0x22);
          puVar8[3] = uVar1 - (short)(uint)((ulonglong)(uVar6 * 3) * (ulonglong)uVar18 >> 0x22);
          puVar8[4] = uVar1 - (short)(uint)((ulonglong)uVar13 * 4 * (ulonglong)uVar18 >> 0x22);
          puVar8[5] = uVar1 - (short)(uint)((ulonglong)(uVar6 * 5) * (ulonglong)uVar18 >> 0x22);
        }

        uVar5 = uVar5 - 1 & 0xffff;
        puVar8 = puVar8 + 6;
      } while (uVar5 != 0);
    }

    if (uVar19 != 0)
    {
      puVar23 = (uint16 *)((int)puVar21 + -2);
      puVar8 = DAT_80013e90;

      if ((uVar19 & 1) != 0)
      {
        puVar8 = DAT_80013e90 + 1;
        *(short *)puVar21 = (short)((uint)*(ushort *)puVar21 + (uint)*puVar8 >> 1);
        puVar23 = puVar21;
      }

      if (uVar7 != 0)
      {
        do
        {
          puVar11 = (ushort *)((int)puVar23 + 2);
          uVar7 = uVar7 - 1;
          puVar23 = (uint16 *)((int)puVar23 + 4);
          *puVar11 = (ushort)((uint)*puVar11 + (uint)puVar8[1] >> 1);
          puVar8 = puVar8 + 2;
          *(ushort *)puVar23 = (ushort)((uint)*(ushort *)puVar23 + (uint)*puVar8 >> 1);
        } while (uVar7 != 0);

        return;
      }

      return;

    }

    return;
  }

  return;
}


