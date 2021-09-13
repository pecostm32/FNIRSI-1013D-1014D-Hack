
//Create thumbnail data
//Only trace data is used. When FFT is enabled this does not show in the thumbnail.
//It does use trace enabled information

//param_1 is file number
//param_2 is index into thumbnail data

//Thumbnail info
//byte
//0   MSB file number
//1   LSB file number
//2   Channel 1 trace offset
//3   Channel 2 trace offset
//4   trigger level screen offset      (useless in this context)
//5   trigger position screen offset   (useless in this context)
//6   Channel 1 enable
//7   Channel 2 enable
//8   trace position                   (useless in this context)
//9   trace sample start offset        (useless in this context)
//10  xy display mode

void FUN_800251bc(undefined4 param_1,int param_2)

{
  longlong lVar1;
  int iVar2;
  undefined *puVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  ushort *puVar7;
  short sVar8;
  int iVar9;
  
  puVar3 = DAT_800253b4;   //0x8019D5A0  base of settings

  iVar2 = DAT_800253b0;    //0x802F19CE

  iVar9 = DAT_800253b0 + param_2;  //0ffset into thumbnail buffer

  //Fill in the file number MSB first
  *(char *)(DAT_800253b0 + param_2) = (char)((uint)param_1 >> 8);
  *(char *)(iVar9 + 1) = (char)param_1;

  uVar5 = DAT_800253bc;  //0xCCCCCCCD

  uVar4 = DAT_800253b8;  //0x38E38E39


  lVar1 = (longlong)(int)DAT_800253b8 * (longlong)(int)((*(ushort *)(puVar3 + 6) - 0x2e) * 10);  //channel 1 trace offset minus the top bar offset

  *(char *)(iVar9 + 2) = ((char)(int)(lVar1 >> 0x23) - (char)(lVar1 >> 0x3f)) + '\x05';          //reduced to smaller value. Need to figure out the division

  lVar1 = (longlong)(int)uVar4 * (longlong)(int)((*(ushort *)(puVar3 + 0x12) - 0x2e) * 10);      //channel 2 trace offset

  *(char *)(iVar9 + 3) = ((char)(int)(lVar1 >> 0x23) - (char)(lVar1 >> 0x3f)) + '\x05';


  *(char *)(iVar9 + 4) = (char)(uint)((ulonglong)((uint)*(ushort *)(puVar3 + 0x26) * 10) * (ulonglong)uVar4 >> 0x23) + '\x05';   //trigger level screen offset

  *(char *)(iVar9 + 5) = (char)(uint)((ulonglong)((uint)*(ushort *)(puVar3 + 0x24) * 10) * (ulonglong)uVar5 >> 0x25);            //trigger position on screen

  *(undefined *)(iVar9 + 6) = *puVar3;
  *(undefined *)(iVar9 + 7) = puVar3[0xc];

  //Time base setting
  if ((byte)puVar3[10] < 9)
  {    //long time bases 50S - 100mS
    *(undefined *)(iVar9 + 8) = 0;
    *(char *)(iVar9 + 9) = (char)(*(ushort *)PTR_DAT_800253c0 >> 2);  //disp_xpos  0x80192eaa
  }
  else
  {    //Short time bases 50mS - 10nS
    *(char *)(iVar9 + 8) = (char)(*(ushort *)(puVar3 + 0x1a) >> 2);   //disp_x_start
    *(char *)(iVar9 + 9) = (char)(*(ushort *)(puVar3 + 0x1c) >> 2);   //disp_sample_count
  }


  *(undefined *)(iVar9 + 10) = *(undefined *)(DAT_800253c4 + 7);  //0x80361378+7 = xy display mode


  puVar7 = DAT_800253c8;   //0x801C3748  channel 1 trace on screen buffer???
  iVar6 = 0;
  sVar8 = 0x160;  //352 * 2 samples??

  do
  {
    sVar8 = sVar8 + -1;

    lVar1 = (longlong)(int)uVar4 * (longlong)(int)((puVar7[1] - 0x2e) * 10);  //Take top bar offset off

    *(char *)(iVar2 + param_2 + 0x14 + (iVar6 >> 2)) = ((char)(int)(lVar1 >> 0x23) - (char)(lVar1 >> 0x3f)) + '\x05';  //And reduce to byte value

    puVar7 = puVar7 + 2;  //next sample

    lVar1 = (longlong)(int)uVar4 * (longlong)(int)((*puVar7 - 0x2e) * 10);

    iVar9 = iVar6 + 1;

    iVar6 = iVar6 + 2;

    *(char *)(iVar2 + param_2 + 0x14 + (iVar9 >> 2)) = ((char)(int)(lVar1 >> 0x23) - (char)(lVar1 >> 0x3f)) + '\x05';

  } while (sVar8 != 0);

  iVar9 = 0;
  sVar8 = 0x160;
  puVar7 = DAT_800253cc;   //0x801C3F18  channel 2 trace buffer??

  //Second trace data starts at offset 200
  do
  {
    iVar6 = iVar9 + 1;
    lVar1 = (longlong)(int)uVar4 * (longlong)(int)((puVar7[1] - 0x2e) * 10);
    sVar8 = sVar8 + -1;
    *(char *)(iVar2 + param_2 + 200 + (iVar9 >> 2)) = ((char)(int)(lVar1 >> 0x23) - (char)(lVar1 >> 0x3f)) + '\x05';
    puVar7 = puVar7 + 2;
    lVar1 = (longlong)(int)uVar4 * (longlong)(int)((*puVar7 - 0x2e) * 10);
    iVar9 = iVar9 + 2;
    *(char *)(iVar2 + param_2 + 200 + (iVar6 >> 2)) = ((char)(int)(lVar1 >> 0x23) - (char)(lVar1 >> 0x3f)) + '\x05';
  } while (sVar8 != 0);

  return;
}


