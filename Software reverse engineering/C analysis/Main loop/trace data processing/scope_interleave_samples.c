

//void scope_pre_process_ch1_25ns_data(void)
void scope_interleave_samples(void)
{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  uint *puVar5;
  uint *puVar6;
  uint *puVar7;
  uint **ppuVar8;
  uint **ppuVar9;
  byte *pbVar10;
  undefined2 *puVar11;
  uint uVar12;
  uint uVar13;
  byte bVar14;
  uint uVar15;
  int iVar16;
  short *psVar17;
  byte bVar18;
  undefined2 uVar19;
  uint *puVar20;
  uint *puVar21;
  uint uVar22;
  uint uVar23;
  uint uVar24;
  bool bVar25;
  bool bVar26;
  
  puVar7 = DAT_8000470c;    //0x801AEF2A    = temptracebuffer1 + 4
  puVar21 = DAT_80004708;   //0x8019D5EA    = channel1tracebuffer1  (1500 samples from most likely adc1)
  iVar16 = 0x2e8;           //744

  //Copy a short from buffer1 to buffer2
  *(undefined2 *)((int)DAT_8000470c + 2) = *(undefined2 *)DAT_80004708;       //0x801aef2c = 0x8019d5ea

  uVar19 = *(undefined2 *)((int)puVar21 + 2);  //Get data from 0x8019d5ec
  puVar11 = (undefined2 *)((int)puVar7 + 2);   //point to next item in the temp buffer

  //Copy data from sample buffer to temp buffer while skipping a sample in the temp buffer. (Make room for another sample???)
  do
  {
    uVar1 = *(undefined2 *)(puVar21 + 1);          //0x8019d5ee
    puVar11[2] = uVar19;                           //0x801aef30  = 0x8019d5ec skip one item
    uVar19 = *(undefined2 *)((int)puVar21 + 6);    //0x8019d5f0
    iVar16 = iVar16 + -1;
    puVar11 = puVar11 + 4;
    *puVar11 = uVar1;                              //0x801aef34  = 0x8019d5ee
    puVar21 = puVar21 + 1;
  } while (iVar16 != 0);

  //Last copies done
  //0x0x801B0668 = 0x8019E18A
  //0x0x801B066C = 0x8019E18C

  iVar3 = DAT_8000471c;    //0x8019ED5A   channel1tracebuffer2  (1500 samples from most likely adc2)
  iVar2 = DAT_80004718;    //0x802F18B0   Calibration data


  *(undefined2 *)(DAT_80004714 + 2) = *DAT_80004710;         //0x801B0670 = 0x8019E18C
  uVar15 = DAT_80004720;                                     //0x000005D2 = 1490
  uVar12 = 0;

  if (*(short *)(iVar2 + 0x1c) == 0)   //0x802f18cc  Either 1 or 0 based on some calibration action
  {
    //Trace data showed this to be zero on my scope, so this loop is done
    do
    {
      uVar13 = (uint)*(ushort *)(iVar3 + uVar12 * 2);    //First sample from 0x8019ed5a

      if (*(ushort *)(iVar2 + 0x1e) < uVar13)      //0x802f18ce also some calibration data  (3 on my scope)
      {
        puVar21 = (uint *)(uVar13 - *(ushort *)(iVar2 + 0x1e));
        *(short *)(puVar7 + uVar12) = (short)puVar21;                  //puVar7 = temp trace buffer
      }
      else
      {
        puVar21 = puVar7 + uVar12;
        *(undefined2 *)puVar21 = 0;
      }

      uVar12 = uVar12 + 1 & 0xfffeffff;
    } while (uVar12 < uVar15);

    //Trace shows this
    //First samples
    //0x801AEF2A = 0x8019ED5A
    //0x801AEF2E = 0x8019ED5C
    //0x801AEF32 = 0x8019ED5E

    //Last samples
    //0x801B066A = 0x8019F8FA
    //0x801B066E = 0x8019F8FC
  }
  else
  {
    do
    {  //two samples at a time, but I miss the interleaving???? Maybe buffers or pointers defined as 32 bit items
      psVar17 = (short *)(iVar3 + uVar12 * 2);
      puVar21 = puVar7 + uVar12;
      uVar12 = uVar12 + 2 & 0xfffeffff;
      *(short *)puVar21 = *psVar17 + *(short *)(iVar2 + 0x1e);
      *(short *)(puVar21 + 1) = psVar17[1] + *(short *)(iVar2 + 0x1e);
    } while (uVar12 < uVar15);

    //Trace shows this
    //First samples
    //0x801AEF2A = 0x8019ED5A
    //0x801AEF2E = 0x8019ED5C
    //0x801AEF32 = 0x8019ED5E
    //0x801AEF36 = 0x8019ED60

    //Last samples
    //0x801B0662 = 0x8019F8F6
    //0x801B0666 = 0x8019F8F8
    //0x801B066A = 0x8019F8FA
    //0x801B066E = 0x8019F8FC

  }

  //DAT_80004724;   //0x000016A8   5800 bytes
  //DAT_80004708;   //0x8019D5EA   first buffer  destination
  //DAT_8000470c;   //0x801AEF2A   temp buffer   source
  //Copy the temp buffer back to the first trace buffer
  memcpy(DAT_80004708, DAT_8000470c, DAT_80004724); 
}

//This part from here is memcpy to copy the prepared buffer back to the original sample buffer
  uVar12 = DAT_80004724;   //0x000016A8   5800 bytes
  puVar5 = DAT_80004708;   //0x8019D5EA   first buffer  destination
  puVar7 = DAT_8000470c;   //0x801AEF2A   temp buffer   source

  if (3 < DAT_80004724)
  {
    puVar20 = (uint *)((uint)DAT_80004708 & 3);
    uVar13 = DAT_80004724;
    puVar21 = puVar20;
    if (puVar20 != NULL) {
      bVar14 = *(byte *)DAT_8000470c;
      puVar6 = (uint *)((int)DAT_8000470c + 1);
      if (puVar20 < (uint *)0x3) {
        puVar6 = (uint *)((int)DAT_8000470c + 2);
        puVar21 = (uint *)(uint)*(byte *)(uint *)((int)DAT_8000470c + 1);
      }
      puVar4 = (uint *)((int)DAT_80004708 + 1);
      *(byte *)DAT_80004708 = bVar14;
      puVar7 = puVar6;
      if (puVar20 < (uint *)0x2) {
        puVar7 = (uint *)((int)puVar6 + 1);
        bVar14 = *(byte *)puVar6;
      }
      puVar6 = puVar4;
      if (puVar20 < (uint *)0x3) {
        puVar6 = (uint *)((int)puVar5 + 2);
        *(byte *)puVar4 = (byte)puVar21;
      }
      uVar13 = (int)puVar20 + (uVar12 - 4);
      puVar5 = puVar6;
      if (puVar20 < (uint *)0x2) {
        puVar5 = (uint *)((int)puVar6 + 1);
        *(byte *)puVar6 = bVar14;
      }
    }
    uVar15 = (uint)puVar7 & 3;
    if (uVar15 == 0) {
      while (uVar12 = uVar13 - 0x20, 0x1f < uVar13) {
        uVar15 = puVar7[1];
        uVar13 = puVar7[2];
        uVar22 = puVar7[3];
        *puVar5 = *puVar7;
        puVar5[1] = uVar15;
        puVar5[2] = uVar13;
        puVar5[3] = uVar22;
        uVar15 = puVar7[4];
        uVar13 = puVar7[5];
        uVar22 = puVar7[6];
        uVar23 = puVar7[7];
        puVar7 = puVar7 + 8;
        puVar5[4] = uVar15;
        puVar5[5] = uVar13;
        puVar5[6] = uVar22;
        puVar5[7] = uVar23;
        puVar5 = puVar5 + 8;
        uVar13 = uVar12;
      }
      if ((bool)((byte)(uVar12 >> 4) & 1)) {
        uVar15 = *puVar7;
        uVar22 = puVar7[1];
        uVar23 = puVar7[2];
        uVar24 = puVar7[3];
        puVar7 = puVar7 + 4;
        *puVar5 = uVar15;
        puVar5[1] = uVar22;
        puVar5[2] = uVar23;
        puVar5[3] = uVar24;
        puVar5 = puVar5 + 4;
      }
      if ((int)(uVar13 << 0x1c) < 0) {
        uVar15 = *puVar7;
        uVar22 = puVar7[1];
        puVar7 = puVar7 + 2;
        *puVar5 = uVar15;
        puVar5[1] = uVar22;
        puVar5 = puVar5 + 2;
      }
      puVar20 = puVar5;
      puVar21 = puVar7;
      if ((bool)((byte)(uVar12 >> 2) & 1)) {
        puVar21 = puVar7 + 1;
        uVar15 = *puVar7;
        puVar20 = puVar5 + 1;
        *puVar5 = uVar15;
      }
      uVar19 = (undefined2)uVar15;
      if ((uVar12 & 3) != 0) {
        bVar26 = (bool)((byte)(uVar12 >> 1) & 1);
        uVar13 = uVar13 << 0x1f;
        bVar25 = (int)uVar13 < 0;
        puVar7 = puVar21;
        if (bVar26) {
          puVar7 = (uint *)((int)puVar21 + 2);
          uVar19 = *(undefined2 *)puVar21;
        }
        if (bVar25) {
          uVar13 = (uint)*(byte *)puVar7;
        }
        puVar21 = puVar20;
        if (bVar26) {
          puVar21 = (uint *)((int)puVar20 + 2);
          *(undefined2 *)puVar20 = uVar19;
        }
        if (bVar25) {
          *(byte *)puVar21 = (byte)uVar13;
        }
        return;
      }
      return;
    }
    uVar12 = uVar13 - 4;
    if (3 < uVar13) {
      ppuVar8 = (uint **)((int)puVar7 - uVar15);
      puVar21 = *ppuVar8;
      puVar7 = puVar5;
      if (uVar15 == 2) {
        do {
          ppuVar9 = ppuVar8;
          uVar15 = (uint)puVar21 >> 0x10;
          ppuVar8 = ppuVar9 + 1;
          puVar21 = *ppuVar8;
          bVar25 = 3 < uVar12;
          uVar12 = uVar12 - 4;
          uVar15 = uVar15 | (int)puVar21 << 0x10;
          puVar5 = puVar7 + 1;
          *puVar7 = uVar15;
          puVar7 = puVar5;
        } while (bVar25);
        puVar7 = (uint *)((int)ppuVar9 + 6);
      }
      else {
        if (uVar15 < 3) {
          do {
            ppuVar9 = ppuVar8;
            uVar15 = (uint)puVar21 >> 8;
            ppuVar8 = ppuVar9 + 1;
            puVar21 = *ppuVar8;
            bVar25 = 3 < uVar12;
            uVar12 = uVar12 - 4;
            uVar15 = uVar15 | (int)puVar21 << 0x18;
            puVar5 = puVar7 + 1;
            *puVar7 = uVar15;
            puVar7 = puVar5;
          } while (bVar25);
          puVar7 = (uint *)((int)ppuVar9 + 5);
        }
        else {
          do {
            ppuVar9 = ppuVar8;
            uVar15 = (uint)puVar21 >> 0x18;
            ppuVar8 = ppuVar9 + 1;
            puVar21 = *ppuVar8;
            bVar25 = 3 < uVar12;
            uVar12 = uVar12 - 4;
            uVar15 = uVar15 | (int)puVar21 << 8;
            puVar5 = puVar7 + 1;
            *puVar7 = uVar15;
            puVar7 = puVar5;
          } while (bVar25);
          puVar7 = (uint *)((int)ppuVar9 + 7);
        }
      }
    }
  }
  bVar18 = (byte)puVar21;
  bVar14 = (byte)uVar15;
  bVar26 = (bool)((byte)(uVar12 >> 1) & 1);
  uVar12 = uVar12 << 0x1f;
  bVar25 = (int)uVar12 < 0;
  if (bVar26) {
    pbVar10 = (byte *)((int)puVar7 + 1);
    bVar14 = *(byte *)puVar7;
    puVar7 = (uint *)((int)puVar7 + 2);
    bVar18 = *pbVar10;
  }
  if (bVar25) {
    uVar12 = (uint)*(byte *)puVar7;
  }
  if (bVar26) {
    pbVar10 = (byte *)((int)puVar5 + 1);
    *(byte *)puVar5 = bVar14;
    puVar5 = (uint *)((int)puVar5 + 2);
    *pbVar10 = bVar18;
  }
  if (bVar25) {
    *(byte *)puVar5 = (byte)uVar12;
  }
  return;
}


