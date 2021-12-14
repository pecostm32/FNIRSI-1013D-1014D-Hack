//--------------------------------------------------------------------------------

void calib_copy_ch1_buf3_to_buf4(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 *puVar3;
  undefined2 *puVar4;
  undefined2 *puVar5;
  undefined2 *puVar6;
  int iVar7;
  uint uVar8;
  
  puVar4 = DAT_8000624c;      //0x801AC04A   fourth sample buffer where processed trace data ends up
  puVar3 = DAT_80006248;      //0x801A916A   third sample buffer
  uVar8 = DAT_8000623c;       //0x000009C4   2500

  //Time base dependend number of samples select???
  if ((*(byte *)(DAT_80006238 + 10) < 0x19) && (uVar8 = DAT_80006240, *(byte *)(DAT_80006238 + 10) < 9))    //0x000005DC  ==> 1500
  {
    uVar8 = DAT_80006244;  //0x000002EE  ==> 750
  }

  //2500 samples for timebase 25 and up  250ns up
  //1500 samples for timebase 9 - 24     50ms - 500ns
  //750 samples for timebase below 9     50s - 100ms

  //This is not correct in light of earlier findings


  puVar5 = DAT_80006248 + -1;     //Copy third sample buffer to fourth sample buffer
  puVar6 = DAT_8000624c + -1;

  //Odd number of samples do the first one
  //Copy one buffer to another?????
  if ((uVar8 & 1) == 0)
  {
    *DAT_8000624c = *DAT_80006248;
    puVar5 = puVar3;
    puVar6 = puVar4;
  }

  uVar1 = puVar5[1];

  //Two samples per loop
  iVar7 = (int)(uVar8 - 1) >> 1;

  while (iVar7 != 0)
  {
    uVar2 = puVar5[2];
    puVar6[1] = uVar1;
    uVar1 = puVar5[3];
    iVar7 = iVar7 + -1;
    puVar6 = puVar6 + 2;
    *puVar6 = uVar2;
    puVar5 = puVar5 + 2;
  }

  iVar7 = uVar8 - 1;

  if (-1 < iVar7)
  {
    puVar4[iVar7] = puVar3[iVar7];
    return;
  }

  return;
}

//--------------------------------------------------------------------------------

