
//Function to save the scope settings, to be able to return to the way the scope was at the moment of opening the view window

//called from FUN_80002810      with 0x8035344E
//called from FUN_80025c38      with 0x8035344E
//called from setup_view_screen with 0x80356EE6


void save_system_setup(void *buffer)

{
  undefined4 *puVar1;
  byte *pbVar2;
  uint uVar3;
  short sVar4;
  int *piVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  uint uVar8;
  undefined4 *puVar9;
  undefined *puVar10;
  int *piVar11;
  ushort **ppuVar12;
  ushort **ppuVar13;
  undefined4 *puVar14;
  byte *pbVar15;
  undefined4 *puVar16;
  uint uVar17;
  undefined uVar18;
  undefined2 uVar19;
  undefined4 *puVar20;
  int iVar21;
  undefined2 *puVar22;
  void *pvVar23;
  undefined4 uVar24;
  int iVar25;
  undefined uVar26;
  ushort *puVar27;
  undefined4 uVar28;
  int iVar29;
  ushort *puVar30;
  undefined4 uVar31;
  bool bVar32;
  bool bVar33;
  int *piVar34;
  
  pbVar2 = DAT_80002010;            //0x8019D5A0 settings base


  if (DAT_80002010[0x1e] != 0)      //trigger flag (triggerflag4)
  {
    DAT_80002010[0x18] = 1;         //triggerflag2
    pbVar2[0x17] = 1;               //triggerflag1
  }

  //Data is saved as shorts. "arrrrrch"

  *(ushort *)buffer = (ushort)pbVar2[0x3a];                        //run mode

  *(ushort *)((int)buffer + 2) = (ushort)*pbVar2;                  //channel 1 enable
  *(ushort *)((int)buffer + 4) = (ushort)pbVar2[3];                //volts/div
  *(ushort *)((int)buffer + 6) = (ushort)pbVar2[4];                //fft enable
  *(ushort *)((int)buffer + 8) = (ushort)pbVar2[1];                //coupling
  *(ushort *)((int)buffer + 10) = (ushort)pbVar2[2];               //magnification

  *(ushort *)((int)buffer + 0xc) = (ushort)pbVar2[0xc];            //channel 2 enable
  *(ushort *)((int)buffer + 0xe) = (ushort)pbVar2[0xf];            //volt/div
  *(ushort *)((int)buffer + 0x10) = (ushort)pbVar2[0x10];          //fft enable
  *(ushort *)((int)buffer + 0x12) = (ushort)pbVar2[0xd];           //coupling
  *(ushort *)((int)buffer + 0x14) = (ushort)pbVar2[0xe];           //magnification

  *(ushort *)((int)buffer + 0x16) = (ushort)pbVar2[10];            //time base setting

  *(ushort *)((int)buffer + 0x18) = (ushort)pbVar2[0x16];          //move speed

  *(ushort *)((int)buffer + 0x1a) = (ushort)pbVar2[0x21];          //trigger mode
  *(ushort *)((int)buffer + 0x1c) = (ushort)pbVar2[0x22];          //trigger edge
  *(ushort *)((int)buffer + 0x1e) = (ushort)pbVar2[0x23];          //trigger channel

  *(ushort *)((int)buffer + 0x20) = (ushort)pbVar2[0x38];          //battery charge level "uuuhmpfff"

  *(ushort *)((int)buffer + 0x22) = (ushort)pbVar2[0x42];          //right menu mode

  *(ushort *)((int)buffer + 0x24) = (ushort)pbVar2[0x18];          //triggerflag2
  *(ushort *)((int)buffer + 0x26) = (ushort)pbVar2[0x17];          //triggerflag1

  *(undefined2 *)((int)buffer + 0x28) = *(undefined2 *)(pbVar2 + 0x1a);  //disp_x_start. Also a bit nonsense to save this since on return the scope is restarted

  puVar10 = PTR_DAT_80002024;    //0x80192ece
  iVar21 = DAT_8000201c;         //0x80361378

  if (pbVar2[10] < 9)        //time base setting. Long time base values 50S - 100mS
  {
    sVar4 = *(short *)PTR_DAT_80002014 + -1;    //0x80192eaa  (disp_xpos)
  }
  else                       //short time base settings. 50mS - 10nS
  {
    sVar4 = *(short *)(pbVar2 + 0x1c);           //disp_sample_count
  }

  *(short *)((int)buffer + 0x2a) = sVar4;   //time base dependend save of info that is not needed


  iVar25 = DAT_80002020;                     //0x801FA24C  base address of measurement settings

  puVar30 = (ushort *)((int)buffer + 0x12e); //index into the buffer

  *(undefined2 *)((int)buffer + 0x2c) = *(undefined2 *)PTR_DAT_80002018;  //0x80192ec4  State flag for getting start+end in sample buffers???

  pbVar15 = (byte *)(iVar25 + -1);          //0x801FA24B

  sVar4 = 0xc;

  *(undefined2 *)((int)buffer + 0x2e) = *(undefined2 *)puVar10;              //0x80192ece
  *(undefined2 *)((int)buffer + 0x30) = *(undefined2 *)PTR_DAT_80002028;     //0x80192ebc
  *(undefined2 *)((int)buffer + 0x32) = *(undefined2 *)PTR_DAT_8000202c;     //0x80192ebe

  *(ushort *)((int)buffer + 0x34) = (ushort)pbVar2[0xb];                     //copy of time base settings
  *(ushort *)((int)buffer + 0x36) = (ushort)pbVar2[0x43];                    //view mode

  *(undefined2 *)((int)buffer + 0x50) = *(undefined2 *)(pbVar2 + 0x24);      //trigger pos on screen
  *(undefined2 *)((int)buffer + 0x52) = *(undefined2 *)(pbVar2 + 0x26);      //trigger level screen offset

  *(undefined2 *)((int)buffer + 0x54) = *(undefined2 *)(pbVar2 + 6);         //channel 1 trace offset

  *(undefined2 *)((int)buffer + 0x56) = *(undefined2 *)(pbVar2 + 0x12);      //channel 2 trace offset

  *(ushort *)((int)buffer + 0x78) = (ushort)*(byte *)(iVar21 + 2);           //screen brightness
  *(ushort *)((int)buffer + 0x7a) = (ushort)*(byte *)(iVar21 + 3);           //grid brightness
  *(ushort *)((int)buffer + 0x7c) = (ushort)*(byte *)(iVar21 + 4);           //always trigger 50%
  *(ushort *)((int)buffer + 0x7e) = (ushort)*(byte *)(iVar21 + 7);           //x-y display mode

                                                                             //measurements enable channel 1
  *(ushort *)((int)buffer + 0xa0) = (ushort)*(byte *)(iVar25 + 0x100);       //vmax
  *(ushort *)((int)buffer + 0xa2) = (ushort)*(byte *)(iVar25 + 0x112);       //vmin
  *(ushort *)((int)buffer + 0xa4) = (ushort)*(byte *)(iVar25 + 0x122);
  *(ushort *)((int)buffer + 0xa6) = (ushort)*(byte *)(iVar25 + 0x132);
  *(ushort *)((int)buffer + 0xa8) = (ushort)*(byte *)(iVar25 + 0x142);
  *(ushort *)((int)buffer + 0xaa) = (ushort)*(byte *)(iVar25 + 0x152);
  *(ushort *)((int)buffer + 0xac) = (ushort)*(byte *)(iVar25 + 0x162);
  *(ushort *)((int)buffer + 0xae) = (ushort)*(byte *)(iVar25 + 0x172);
  *(ushort *)((int)buffer + 0xb0) = (ushort)*(byte *)(iVar25 + 0x182);
  *(ushort *)((int)buffer + 0xb2) = (ushort)*(byte *)(iVar25 + 0x192);
  *(ushort *)((int)buffer + 0xb4) = (ushort)*(byte *)(iVar25 + 0x1a2);
  *(ushort *)((int)buffer + 0xb6) = (ushort)*(byte *)(iVar25 + 0x1b2);       //duty-

                                                                             //measurements enable channel 2
  *(ushort *)((int)buffer + 0xb8) = (ushort)*(byte *)(iVar25 + 0x1c2);       //vmax
  *(ushort *)((int)buffer + 0xba) = (ushort)*(byte *)(iVar25 + 0x1d2);
  *(ushort *)((int)buffer + 0xbc) = (ushort)*(byte *)(iVar25 + 0x1e2);
  *(ushort *)((int)buffer + 0xbe) = (ushort)*(byte *)(iVar25 + 0x1f2);
  *(ushort *)((int)buffer + 0xc0) = (ushort)*(byte *)(iVar25 + 0x202);
  *(ushort *)((int)buffer + 0xc2) = (ushort)*(byte *)(iVar25 + 0x212);
  *(ushort *)((int)buffer + 0xc4) = (ushort)*(byte *)(iVar25 + 0x232);
  *(ushort *)((int)buffer + 0xc6) = (ushort)*(byte *)(iVar25 + 0x242);
  *(ushort *)((int)buffer + 200) = (ushort)*(byte *)(iVar25 + 0x252);
  *(ushort *)((int)buffer + 0xca) = (ushort)*(byte *)(iVar25 + 0x262);
  *(ushort *)((int)buffer + 0xcc) = (ushort)*(byte *)(iVar25 + 0x272);
  *(ushort *)((int)buffer + 0xce) = (ushort)*(byte *)(iVar25 + 0x282);        //duty-

//Channel 1 measured values????
  *(short *)((int)buffer + 0xd0) = (short)((uint)*(undefined4 *)(iVar25 + 0x104) >> 0x10);
  *(short *)((int)buffer + 0xd2) = (short)*(undefined4 *)(iVar25 + 0x104);
  *(short *)((int)buffer + 0xd4) = (short)((uint)*(undefined4 *)(iVar25 + 0x114) >> 0x10);
  *(short *)((int)buffer + 0xd6) = (short)*(undefined4 *)(iVar25 + 0x114);
  *(short *)((int)buffer + 0xd8) = (short)((uint)*(undefined4 *)(iVar25 + 0x124) >> 0x10);
  *(short *)((int)buffer + 0xda) = (short)*(undefined4 *)(iVar25 + 0x124);
  *(short *)((int)buffer + 0xdc) = (short)((uint)*(undefined4 *)(iVar25 + 0x134) >> 0x10);
  *(short *)((int)buffer + 0xde) = (short)*(undefined4 *)(iVar25 + 0x134);
  *(short *)((int)buffer + 0xe0) = (short)((uint)*(undefined4 *)(iVar25 + 0x144) >> 0x10);
  *(short *)((int)buffer + 0xe2) = (short)*(undefined4 *)(iVar25 + 0x144);
  *(short *)((int)buffer + 0xe4) = (short)((uint)*(undefined4 *)(iVar25 + 0x154) >> 0x10);
  *(short *)((int)buffer + 0xe6) = (short)*(undefined4 *)(iVar25 + 0x154);
  *(short *)((int)buffer + 0xe8) = (short)((uint)*(undefined4 *)(iVar25 + 0x164) >> 0x10);
  *(short *)((int)buffer + 0xea) = (short)*(undefined4 *)(iVar25 + 0x164);
  *(short *)((int)buffer + 0xec) = (short)((uint)*(undefined4 *)(iVar25 + 0x174) >> 0x10);
  *(short *)((int)buffer + 0xee) = (short)*(undefined4 *)(iVar25 + 0x174);
  *(short *)((int)buffer + 0xf0) = (short)((uint)*(undefined4 *)(iVar25 + 0x184) >> 0x10);
  *(short *)((int)buffer + 0xf2) = (short)*(undefined4 *)(iVar25 + 0x184);
  *(short *)((int)buffer + 0xf4) = (short)((uint)*(undefined4 *)(iVar25 + 0x194) >> 0x10);
  *(short *)((int)buffer + 0xf6) = (short)*(undefined4 *)(iVar25 + 0x194);
  *(short *)((int)buffer + 0xf8) = (short)((uint)*(undefined4 *)(iVar25 + 0x1a4) >> 0x10);
  *(short *)((int)buffer + 0xfa) = (short)*(undefined4 *)(iVar25 + 0x1a4);
  *(short *)((int)buffer + 0xfc) = (short)((uint)*(undefined4 *)(iVar25 + 0x1b4) >> 0x10);
  *(short *)((int)buffer + 0xfe) = (short)*(undefined4 *)(iVar25 + 0x1b4);


//Channel 2 measured values????
  *(short *)((int)buffer + 0x100) = (short)((uint)*(undefined4 *)(iVar25 + 0x1c4) >> 0x10);
  *(short *)((int)buffer + 0x102) = (short)*(undefined4 *)(iVar25 + 0x1c4);
  *(short *)((int)buffer + 0x104) = (short)((uint)*(undefined4 *)(iVar25 + 0x1d4) >> 0x10);
  *(short *)((int)buffer + 0x106) = (short)*(undefined4 *)(iVar25 + 0x1d4);
  *(short *)((int)buffer + 0x108) = (short)((uint)*(undefined4 *)(iVar25 + 0x1e4) >> 0x10);
  *(short *)((int)buffer + 0x10a) = (short)*(undefined4 *)(iVar25 + 0x1e4);
  *(short *)((int)buffer + 0x10c) = (short)((uint)*(undefined4 *)(iVar25 + 500) >> 0x10);
  *(short *)((int)buffer + 0x10e) = (short)*(undefined4 *)(iVar25 + 500);
  *(short *)((int)buffer + 0x110) = (short)((uint)*(undefined4 *)(iVar25 + 0x204) >> 0x10);
  *(short *)((int)buffer + 0x112) = (short)*(undefined4 *)(iVar25 + 0x204);
  *(short *)((int)buffer + 0x114) = (short)((uint)*(undefined4 *)(iVar25 + 0x214) >> 0x10);
  *(short *)((int)buffer + 0x116) = (short)*(undefined4 *)(iVar25 + 0x214);
  *(short *)((int)buffer + 0x118) = (short)((uint)*(undefined4 *)(iVar25 + 0x234) >> 0x10);
  *(short *)((int)buffer + 0x11a) = (short)*(undefined4 *)(iVar25 + 0x234);
  *(short *)((int)buffer + 0x11c) = (short)((uint)*(undefined4 *)(iVar25 + 0x244) >> 0x10);
  *(short *)((int)buffer + 0x11e) = (short)*(undefined4 *)(iVar25 + 0x244);
  *(short *)((int)buffer + 0x120) = (short)((uint)*(undefined4 *)(iVar25 + 0x254) >> 0x10);
  *(short *)((int)buffer + 0x122) = (short)*(undefined4 *)(iVar25 + 0x254);
  *(short *)((int)buffer + 0x124) = (short)((uint)*(undefined4 *)(iVar25 + 0x264) >> 0x10);
  *(short *)((int)buffer + 0x126) = (short)*(undefined4 *)(iVar25 + 0x264);
  *(short *)((int)buffer + 0x128) = (short)((uint)*(undefined4 *)(iVar25 + 0x274) >> 0x10);
  *(short *)((int)buffer + 0x12a) = (short)*(undefined4 *)(iVar25 + 0x274);
  *(short *)((int)buffer + 300) = (short)((uint)*(undefined4 *)(iVar25 + 0x284) >> 0x10);
  *(short *)((int)buffer + 0x12e) = (short)*(undefined4 *)(iVar25 + 0x284);

      //Copy 12 * 2 values. This is the list of enabled measurements to show them on the display
  do  //puVar30 = (ushort *)((int)buffer + 0x12e);
  {
    sVar4 = sVar4 + -1;
    puVar30[1] = (ushort)pbVar15[1];    //Initial pVar15 = //0x801FA24B
    pbVar15 = pbVar15 + 2;
    puVar30 = puVar30 + 2;
    *puVar30 = (ushort)*pbVar15;
  } while (sVar4 != 0);


  *(ushort *)((int)buffer + 400) = (ushort)pbVar2[0x39];                      //charging indicator
  *(ushort *)((int)buffer + 0x192) = (ushort)pbVar2[0x38];                    //battery charge level

  *(undefined2 *)((int)buffer + 0x194) = *(undefined2 *)PTR_DAT_80002030;     //0x80192ec6
  *(undefined2 *)((int)buffer + 0x196) = *(undefined2 *)PTR_DAT_80002034;     //0x80192ec8

  //No idea what this does but since it is FPGA related it will be needed
  translate_parameter(0x15,0x18);


  //Copy sample buffers
  iVar25 = DAT_8000203c;  //0x00000BB8      //3000
  iVar21 = DAT_80002038;  //0x801AC04A      //Sample buffer

  puVar7 = (undefined4 *)((int)buffer + (500 - DAT_80002038));

  bVar32 = puVar7 == NULL;

  puVar16 = (undefined4 *)(DAT_8000203c >> 1);  //1500
  puVar20 = puVar7;

  if (0 < (int)puVar7)
  {
    puVar20 = (undefined4 *)((int)puVar16 - (int)puVar7);
    bVar32 = puVar16 == puVar7;
  }

  bVar33 = 0 < (int)puVar7 && SBORROW4((int)puVar16,(int)puVar7);

  if (!bVar32 && (int)puVar20 < 0 == bVar33)
  {
    puVar7 = NULL;
  }

  if (bVar32 || (int)puVar20 < 0 != bVar33)
  {
    //Copy shorts ?????
    FUN_80000730((int)buffer + 1000,DAT_80002038,DAT_8000203c);
  }
  else
  {
    do
    {
      puVar22 = (undefined2 *)(iVar21 + (int)puVar7 * 2);
      pvVar23 = (void *)((int)buffer + (int)puVar7 * 2);
      *(undefined2 *)((int)pvVar23 + 1000) = *puVar22;
      puVar30 = (ushort *)((int)puVar7 + 2);
      puVar7 = (undefined4 *)((uint)puVar30 & 0xfffeffff);
      *(undefined2 *)((int)pvVar23 + 0x3ea) = puVar22[1];
    } while (puVar7 < puVar16);
  }

  iVar21 = DAT_80002040;
  puVar7 = (undefined4 *)((int)buffer + (2000 - DAT_80002040));
  bVar32 = puVar7 == NULL;
  puVar20 = puVar7;

  if (0 < (int)puVar7)
  {
    puVar20 = (undefined4 *)((int)puVar16 - (int)puVar7);
    bVar32 = puVar16 == puVar7;
  }

  bVar33 = 0 < (int)puVar7 && SBORROW4((int)puVar16,(int)puVar7);

  if (!bVar32 && (int)puVar20 < 0 == bVar33)
  {
    puVar7 = NULL;
  }

  if (bVar32 || (int)puVar20 < 0 != bVar33)
  {
    FUN_80000730((int)buffer + 4000,DAT_80002040,iVar25);
  }
  else
  {
    do
    {
      puVar22 = (undefined2 *)(iVar21 + (int)puVar7 * 2);
      pvVar23 = (void *)((int)buffer + (int)puVar7 * 2);
      *(undefined2 *)((int)pvVar23 + 4000) = *puVar22;
      puVar30 = (ushort *)((int)puVar7 + 2);
      puVar7 = (undefined4 *)((uint)puVar30 & 0xfffeffff);
      *(undefined2 *)((int)pvVar23 + 0xfa2) = puVar22[1];
    } while (puVar7 < puVar16);
  }

  uVar3 = DAT_80002048;
  iVar21 = DAT_80002044;
  uVar8 = (int)buffer + (0xdac - DAT_80002044);
  bVar32 = uVar8 == 0;
  uVar17 = uVar8;

  if (0 < (int)uVar8)
  {
    uVar17 = DAT_80002048 - uVar8;
    bVar32 = DAT_80002048 == uVar8;
  }

  bVar33 = 0 < (int)uVar8 && SBORROW4(DAT_80002048,uVar8);

  if (!bVar32 && (int)uVar17 < 0 == bVar33)
  {
    uVar8 = 0;
  }

  if (bVar32 || (int)uVar17 < 0 != bVar33)
  {
    FUN_80000730((int)buffer + 7000,DAT_80002044,puVar16);
  }
  else
  {
    do
    {
      puVar22 = (undefined2 *)(iVar21 + uVar8 * 2);
      pvVar23 = (void *)((int)buffer + uVar8 * 2);
      *(undefined2 *)((int)pvVar23 + 7000) = *puVar22;
      puVar30 = (ushort *)(uVar8 + 2);
      uVar8 = (uint)puVar30 & 0xfffeffff;
      *(undefined2 *)((int)pvVar23 + 0x1b5a) = puVar22[1];
    } while (uVar8 < uVar3);
  }

  puVar20 = DAT_8000204c;
  uVar8 = (int)buffer + (0x109a - (int)DAT_8000204c);
  bVar32 = uVar8 == 0;
  uVar17 = uVar8;

  if (0 < (int)uVar8)
  {
    uVar17 = uVar3 - uVar8;
    bVar32 = uVar3 == uVar8;
  }

  bVar33 = 0 < (int)uVar8 && SBORROW4(uVar3,uVar8);

  if (!bVar32 && (int)uVar17 < 0 == bVar33)
  {
    uVar8 = 0;
  }

  if (!bVar32 && (int)uVar17 < 0 == bVar33)
  {
    do
    {
      puVar16 = (undefined4 *)((int)puVar20 + uVar8 * 2);
      pvVar23 = (void *)((int)buffer + uVar8 * 2);
      *(undefined2 *)((int)pvVar23 + 0x2134) = *(undefined2 *)puVar16;
      uVar8 = uVar8 + 2 & 0xfffeffff;
      *(undefined2 *)((int)pvVar23 + 0x2136) = *(undefined2 *)((int)puVar16 + 2);
    } while (uVar8 < uVar3);

    return;
  }


//From here on down it is FUN_80000730
  puVar7 = (undefined4 *)((int)buffer + 0x2134);
  puVar20 = (undefined4 *)((int)puVar7 - (int)DAT_8000204c);
  bVar32 = puVar20 == NULL;

  if (DAT_8000204c <= puVar7)
  {
    bVar32 = puVar16 == puVar20;
  }

  if ((DAT_8000204c > puVar7 || puVar16 < puVar20) || bVar32)
  {
    puVar9 = DAT_8000204c;

    if ((undefined4 *)0x3 < puVar16)
    {
      puVar27 = (ushort *)((uint)puVar7 & 3);
      puVar30 = puVar27;

      if (puVar27 != NULL)
      {
        uVar18 = *(undefined *)DAT_8000204c;
        puVar20 = (undefined4 *)((int)DAT_8000204c + 1);

        if (puVar27 < (ushort *)0x3)
        {
          puVar20 = (undefined4 *)((int)DAT_8000204c + 2);
          puVar30 = (ushort *)(uint)*(byte *)(undefined4 *)((int)DAT_8000204c + 1);
        }

        *(undefined *)puVar7 = uVar18;
        puVar9 = puVar20;

        if (puVar27 < (ushort *)0x2)
        {
          puVar9 = (undefined4 *)((int)puVar20 + 1);
          uVar18 = *(undefined *)puVar20;
        }

        puVar20 = (undefined4 *)((int)buffer + 0x2135);

        if (puVar27 < (ushort *)0x3)
        {
          puVar20 = (undefined4 *)((int)buffer + 0x2136);
          *(char *)(undefined4 *)((int)buffer + 0x2135) = (char)puVar30;
        }

        puVar16 = (undefined4 *)((int)puVar16 + (int)puVar27 + -4);
        puVar7 = puVar20;

        if (puVar27 < (ushort *)0x2)
        {
          puVar7 = (undefined4 *)((int)puVar20 + 1);
          *(undefined *)puVar20 = uVar18;
        }
      }

      puVar20 = (undefined4 *)((uint)puVar9 & 3);

      //This is function FUN_80000804. Some memory copy functionality
      if (puVar20 == NULL)
      {
        while (puVar1 = puVar16 + -8, (undefined4 *)0x1f < puVar16)
        {
          uVar24 = puVar9[1];
          uVar28 = puVar9[2];
          uVar31 = puVar9[3];
          *puVar7 = *puVar9;
          puVar7[1] = uVar24;
          puVar7[2] = uVar28;
          puVar7[3] = uVar31;
          puVar20 = (undefined4 *)puVar9[4];
          uVar24 = puVar9[5];
          uVar28 = puVar9[6];
          uVar31 = puVar9[7];
          puVar9 = puVar9 + 8;
          puVar7[4] = puVar20;
          puVar7[5] = uVar24;
          puVar7[6] = uVar28;
          puVar7[7] = uVar31;
          puVar7 = puVar7 + 8;
          puVar16 = puVar1;
        }

        if ((bool)((byte)((uint)puVar1 >> 4) & 1))
        {
          puVar20 = (undefined4 *)*puVar9;
          uVar24 = puVar9[1];
          uVar28 = puVar9[2];
          uVar31 = puVar9[3];
          puVar9 = puVar9 + 4;
          *puVar7 = puVar20;
          puVar7[1] = uVar24;
          puVar7[2] = uVar28;
          puVar7[3] = uVar31;
          puVar7 = puVar7 + 4;
        }

        if ((int)puVar16 << 0x1c < 0)
        {
          puVar20 = (undefined4 *)*puVar9;
          uVar24 = puVar9[1];
          puVar9 = puVar9 + 2;
          *puVar7 = puVar20;
          puVar7[1] = uVar24;
          puVar7 = puVar7 + 2;
        }

        puVar6 = puVar7;
        puVar14 = puVar9;

        if ((bool)((byte)((uint)puVar1 >> 2) & 1))
        {
          puVar14 = puVar9 + 1;
          puVar20 = (undefined4 *)*puVar9;
          puVar6 = puVar7 + 1;
          *puVar7 = puVar20;
        }

        uVar19 = SUB42(puVar20,0);

        if (((uint)puVar1 & 3) == 0)
        {
          return;
        }

        bVar33 = (bool)((byte)((uint)puVar1 >> 1) & 1);
        uVar17 = (int)puVar16 << 0x1f;
        bVar32 = (int)uVar17 < 0;
        puVar16 = puVar14;

        if (bVar33)
        {
          puVar16 = (undefined4 *)((int)puVar14 + 2);
          uVar19 = *(undefined2 *)puVar14;
        }

        if (bVar32)
        {
          uVar17 = (uint)*(byte *)puVar16;
        }

        puVar16 = puVar6;

        if (bVar33)
        {
          puVar16 = (undefined4 *)((int)puVar6 + 2);
          *(undefined2 *)puVar6 = uVar19;
        }

        if (bVar32)
        {
          *(char *)puVar16 = (char)uVar17;
        }

        return;
      }

      bVar32 = (undefined4 *)0x3 < puVar16;
      puVar16 = puVar16 + -1;

      if (bVar32)
      {
        ppuVar12 = (ushort **)((int)puVar9 - (int)puVar20);
        puVar30 = *ppuVar12;
        puVar9 = puVar7;

        if (puVar20 == (undefined4 *)0x2)
        {
          do
          {
            ppuVar13 = ppuVar12;
            uVar17 = (uint)puVar30 >> 0x10;
            ppuVar12 = ppuVar13 + 1;
            puVar30 = *ppuVar12;
            bVar32 = (undefined4 *)0x3 < puVar16;
            puVar16 = puVar16 + -1;
            puVar20 = (undefined4 *)(uVar17 | (int)puVar30 << 0x10);
            puVar7 = puVar9 + 1;
            *puVar9 = puVar20;
            puVar9 = puVar7;
          } while (bVar32);

          puVar9 = (undefined4 *)((int)ppuVar13 + 6);
        }
        else
        {
          if (puVar20 < (undefined4 *)0x3)
          {
            do
            {
              ppuVar13 = ppuVar12;
              uVar17 = (uint)puVar30 >> 8;
              ppuVar12 = ppuVar13 + 1;
              puVar30 = *ppuVar12;
              bVar32 = (undefined4 *)0x3 < puVar16;
              puVar16 = puVar16 + -1;
              puVar20 = (undefined4 *)(uVar17 | (int)puVar30 << 0x18);
              puVar7 = puVar9 + 1;
              *puVar9 = puVar20;
              puVar9 = puVar7;
            } while (bVar32);

            puVar9 = (undefined4 *)((int)ppuVar13 + 5);
          }
          else
          {
            do
            {
              ppuVar13 = ppuVar12;
              uVar17 = (uint)puVar30 >> 0x18;
              ppuVar12 = ppuVar13 + 1;
              puVar30 = *ppuVar12;
              bVar32 = (undefined4 *)0x3 < puVar16;
              puVar16 = puVar16 + -1;
              puVar20 = (undefined4 *)(uVar17 | (int)puVar30 << 8);
              puVar7 = puVar9 + 1;
              *puVar9 = puVar20;
              puVar9 = puVar7;
            } while (bVar32);

            puVar9 = (undefined4 *)((int)ppuVar13 + 7);
          }
        }
      }
    }

    uVar26 = SUB41(puVar30,0);
    uVar18 = SUB41(puVar20,0);
    bVar33 = (bool)((byte)((uint)puVar16 >> 1) & 1);
    uVar17 = (int)puVar16 << 0x1f;
    bVar32 = (int)uVar17 < 0;

    if (bVar33)
    {
      puVar10 = (undefined *)((int)puVar9 + 1);
      uVar18 = *(undefined *)puVar9;
      puVar9 = (undefined4 *)((int)puVar9 + 2);
      uVar26 = *puVar10;
    }

    if (bVar32)
    {
      uVar17 = (uint)*(byte *)puVar9;
    }

    if (bVar33)
    {
      puVar10 = (undefined *)((int)puVar7 + 1);
      *(undefined *)puVar7 = uVar18;
      puVar7 = (undefined4 *)((int)puVar7 + 2);
      *puVar10 = uVar26;
    }

    if (bVar32)
    {
      *(char *)puVar7 = (char)uVar17;
    }

    return;  // this is part of memcpy
  }

  piVar5 = (int *)((int)puVar7 + (int)puVar16);
  piVar11 = (int *)((int)DAT_8000204c + (int)puVar16);

  if ((undefined4 *)0x3 < puVar16)
  {
    bVar32 = ((uint)piVar5 & 3) == 0;

    do
    {
      if (!bVar32)
      {
        piVar11 = (int *)((int)piVar11 + -1);
        puVar16 = (undefined4 *)((int)puVar16 - 1);
        piVar5 = (int *)((int)piVar5 + -1);
        *(undefined *)piVar5 = *(undefined *)piVar11;
      }

      bVar32 = ((uint)piVar5 & 3) == 0;
    } while (!bVar32);

    puVar20 = (undefined4 *)((uint)piVar11 & 3);

    if (puVar20 == NULL)
    {
      while (puVar20 = puVar16 + -4, (undefined4 *)0xf < puVar16)
      {
        piVar34 = piVar11 + -1;
        iVar29 = piVar11[-2];
        iVar25 = piVar11[-3];
        piVar11 = piVar11 + -4;
        iVar21 = *piVar11;
        piVar5[-1] = *piVar34;
        piVar5[-2] = iVar29;
        piVar5[-3] = iVar25;
        piVar5 = piVar5 + -4;
        *piVar5 = iVar21;
        puVar16 = puVar20;
      }

      iVar21 = (int)puVar16 << 0x1d;
      bVar32 = iVar21 < 0;

      if ((bool)((byte)((uint)puVar20 >> 3) & 1))
      {
        piVar34 = piVar11 + -1;
        piVar11 = piVar11 + -2;
        iVar21 = *piVar11;
        piVar5[-1] = *piVar34;
        piVar5 = piVar5 + -2;
        *piVar5 = iVar21;
      }

      if (bVar32)
      {
        piVar11 = piVar11 + -1;
        iVar21 = *piVar11;
        piVar5 = piVar5 + -1;
        *piVar5 = iVar21;
      }

      uVar19 = (undefined2)iVar21;

      if (((uint)puVar20 & 3) == 0)
      {
        return;
      }

      bVar33 = (bool)((byte)((uint)puVar20 >> 1) & 1);
      uVar17 = (int)puVar16 << 0x1f;
      bVar32 = (int)uVar17 < 0;

      if (bVar33)
      {
        piVar11 = (int *)((int)piVar11 + -2);
        uVar19 = *(undefined2 *)piVar11;
      }

      if (bVar32)
      {
        uVar17 = (uint)*(byte *)((int)piVar11 + -1);
      }

      if (bVar33)
      {
        piVar5 = (int *)((int)piVar5 + -2);
        *(undefined2 *)piVar5 = uVar19;
      }

      if (bVar32)
      {
        *(char *)((int)piVar5 + -1) = (char)uVar17;
      }

      return;
    }

    bVar32 = (undefined4 *)0x3 < puVar16;
    puVar16 = puVar16 + -1;

    if (bVar32)
    {
      ppuVar12 = (ushort **)((int)piVar11 - (int)puVar20);
      puVar30 = *ppuVar12;

      if (puVar20 < (undefined4 *)0x2)
      {
        do
        {
          ppuVar13 = ppuVar12;
          uVar17 = (int)puVar30 << 0x18;
          ppuVar12 = ppuVar13 + -1;
          puVar30 = *ppuVar12;
          bVar32 = (undefined4 *)0x3 < puVar16;
          puVar16 = puVar16 + -1;
          puVar20 = (undefined4 *)(uVar17 | (uint)puVar30 >> 8);
          piVar5 = piVar5 + -1;
          *piVar5 = (int)puVar20;
        } while (bVar32);

        piVar11 = (int *)((int)ppuVar13 + -3);
      }
      else
      {
        if (puVar20 < (undefined4 *)0x3)
        {
          do
          {
            ppuVar13 = ppuVar12;
            uVar17 = (int)puVar30 << 0x10;
            ppuVar12 = ppuVar13 + -1;
            puVar30 = *ppuVar12;
            bVar32 = (undefined4 *)0x3 < puVar16;
            puVar16 = puVar16 + -1;
            puVar20 = (undefined4 *)(uVar17 | (uint)puVar30 >> 0x10);
            piVar5 = piVar5 + -1;
            *piVar5 = (int)puVar20;
          } while (bVar32);

          piVar11 = (int *)((int)ppuVar13 + -2);
        }
        else
        {
          do
          {
            ppuVar13 = ppuVar12;
            uVar17 = (int)puVar30 << 8;
            ppuVar12 = ppuVar13 + -1;
            puVar30 = *ppuVar12;
            bVar32 = (undefined4 *)0x3 < puVar16;
            puVar16 = puVar16 + -1;
            puVar20 = (undefined4 *)(uVar17 | (uint)puVar30 >> 0x18);
            piVar5 = piVar5 + -1;
            *piVar5 = (int)puVar20;
          } while (bVar32);

          piVar11 = (int *)((int)ppuVar13 + -1);
        }
      }
    }
  }

  uVar26 = SUB41(puVar30,0);
  uVar18 = SUB41(puVar20,0);
  bVar33 = (bool)((byte)((uint)puVar16 >> 1) & 1);
  uVar17 = (int)puVar16 << 0x1f;
  bVar32 = (int)uVar17 < 0;

  if (bVar33)
  {
    uVar18 = *(undefined *)((int)piVar11 + -1);
    piVar11 = (int *)((int)piVar11 + -2);
    uVar26 = *(undefined *)piVar11;
  }

  if (bVar32)
  {
    uVar17 = (uint)*(byte *)((int)piVar11 + -1);
  }

  if (bVar33)
  {
    *(undefined *)((int)piVar5 + -1) = uVar18;
    piVar5 = (int *)((int)piVar5 + -2);
    *(undefined *)piVar5 = uVar26;
  }

  if (bVar32)
  {
    *(char *)((int)piVar5 + -1) = (char)uVar17;
  }

  return;
}


