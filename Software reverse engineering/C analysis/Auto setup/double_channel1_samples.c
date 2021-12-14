//--------------------------------------------------------------------------------

void double_channel1_samples(void)

{
  int iVar1;
  ushort *puVar2;
  ushort *puVar3;
  uint uVar4;
  uint uVar5;
  ushort *unaff_r4;
  ushort *puVar6;
  
  puVar6 = CH1_SAMPLE_BUFFER_4;
  iVar1 = SETTINGS_BASE;

  if (*(byte *)(SETTINGS_BASE + 10) < 0x19)    //Time base less then 25. (time > 250ns)
  {
    if (*(byte *)(SETTINGS_BASE + 10) < 9)     //Time base lesst then 9 (time >50ms) which is not correct. should be 11
    {
      uVar4 = LENGTH_750;

      if (*(char *)(SETTINGS_BASE + 3) != '\x06')   //Channel 1 volts per div, so only when it is 6 the rest is done
      {
        return;
      }
    }
    else
    {
      uVar4 = LENGTH_1500;

      if (*(char *)(SETTINGS_BASE + 3) != '\x06')
      {
        return;
      }
    }
  }
  else
  {
    uVar4 = LENGTH_2500;

    if (*(char *)(SETTINGS_BASE + 3) != '\x06')
    {
      return;
    }
  }

  puVar2 = CH1_SAMPLE_BUFFER_4 + -1;

  //Odd number of samples detect
  if ((uVar4 & 1) != 0)
  {
    *CH1_SAMPLE_BUFFER_4 = *CH1_SAMPLE_BUFFER_4 << 1;
    puVar2 = puVar6;
  }

  //Do two samples in one loop
  uVar5 = uVar4 >> 1;

  //Double the magnitude of the samples for the lowest sensitivity setting
  while (uVar5 != 0)
  {
    puVar3 = puVar2 + 2;
    uVar5 = uVar5 - 1;
    puVar2[1] = puVar2[1] << 1;
    *puVar3 = (ushort)((*puVar3 & 0x7fff7fff) << 1);
    puVar2 = puVar3;
  }

  if (uVar4 == 0)
  {
    puVar6 = unaff_r4;
  }

  uVar5 = 0;

  if (uVar4 == 0)
  {
    return;
  }

  //Do trace offset adjust
  do
  {
    puVar2 = puVar6 + uVar5;

    if (*puVar2 < *(ushort *)(iVar1 + 6))  //Channel 1 trace offset
    {
      *puVar2 = 0;
    }
    else
    {
      *puVar2 = *puVar2 - *(short *)(iVar1 + 6);
    }

    uVar5 = uVar5 + 1 & 0xfffeffff;
  } while (uVar5 < uVar4);

  return;
}

//--------------------------------------------------------------------------------

