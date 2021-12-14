//--------------------------------------------------------------------------------

void calib_adjust_channel_1_samples(void)

{
  uint uVar1;
  ushort uVar2;
  uint uVar3;
  ushort uVar4;
  uint uVar5;
  ushort *puVar6;
  ushort *puVar7;
  int unaff_r4;
  int iVar8;
  int iVar9;
  undefined auStack4 [4];
  
  iVar8 = DAT_80006154;  //2500

  //Time base setting check
  if ((*(byte *)(DAT_80006150 + 10) < 0x19) && (iVar8 = DAT_80006158, *(byte *)(DAT_80006150 + 10) < 9))  //1500
  {
    iVar8 = DAT_8000615c;  //750
  }

  //Number of samples set based on time base, but not correct.


  //Get the readings adjustment values from the special ic
  uVar5 = translate_parameter(0xb,(uint)*(byte *)(DAT_80006150 + 3));

  uVar3 = DAT_80006168;       //0x51EB851F  correction value

  iVar9 = iVar8;

  if (iVar8 == 0)
  {
    iVar9 = unaff_r4;
  }
 
  puVar6 = DAT_80006164;   //0x801A916A   third sample buffer
  puVar7 = DAT_80006160;   //0x8019D5EA   first sample buffer

  if (iVar8 == 0)
  {
    return;
  }

  //Calibrate the samples from buffer 1 into buffer 3
  do
  {
    uVar1 = (uVar5 & 0xffff) * (uint)*puVar7 & 0xffff;
    uVar2 = (ushort)(DAT_8000616c * uVar1 + DAT_8000616c >> 0x10);
    uVar4 = uVar2 >> 6;

    if (0x32 < (int)(uVar1 + (uint)((ulonglong)uVar1 * (ulonglong)uVar3 >> 0x25) * -100))
    {
      uVar4 = (uVar2 >> 6) + 1;
    }

    iVar9 = iVar9 + -1;
    *puVar6 = uVar4;
    puVar6 = puVar6 + 1;
    puVar7 = puVar7 + 1;
  } while (iVar9 != 0);

  return;
}

//--------------------------------------------------------------------------------

