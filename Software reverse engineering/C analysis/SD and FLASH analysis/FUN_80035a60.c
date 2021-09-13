
undefined4 FUN_80035a60(uint interface,sd_data *data,uint *ptr)

{
  uint uVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  undefined2 uVar7;
  uint *puVar8;
  
  uVar3 = (int)(uint *)data->blocks * data->blocksize;

  puVar8 = (uint *)data->blocks;

  if (interface == 0)
  {
    puVar8 = SD_MMC_0_BASE;
  }

  iVar5 = 0;

  if ((interface != 0) && (puVar8 = SD_MMC_1_BASE, interface != 1))
  {
    puVar8 = NULL;
  }

  uVar7 = (undefined2)(uVar3 & 0xfff);   //Back to size per block (4096 bytes per block)

  uVar4 = uVar3 >> 0xc;                  //Number of blocks

  if ((uVar3 & 0xfff) == 0)
  {
    uVar7 = 0x1000;
  }
  else
  {
    uVar4 = uVar4 + 1;
  }

  pcVar6 = data->data;

  if (uVar4 < 0x101)        //Some maximum number of blocks
  {
    uVar1 = (uint)pcVar6 & 0xffffffe0;

    //Something with 32 byte blocks
    while (uVar1 <= ((uint)(pcVar6 + uVar3) & 0xffffffe0))
    {
      coproc_moveto_Invalidate_Data_Cache_by_MVA(uVar1);
      coproc_moveto_Invalidate_Instruction_Cache_by_MVA(uVar1);

      uVar1 = uVar1 + 0x20;
    }

    uVar3 = 0;
    if (uVar4 != 0)
    {
      do
      {
        puVar2 = ptr + iVar5 * 4;
        puVar2[1] = 0;
        puVar2[2] = 0;
        puVar2[3] = 0;
        *puVar2 = (uint)&LAB_80000010+2;

        if ((uVar4 < 2) || (uVar3 == uVar4 - 1))
        {
          *(undefined2 *)(puVar2 + 1) = uVar7;
        }
        else
        {
          *(undefined2 *)(puVar2 + 1) = 0x1000;
        }

        puVar2[2] = (uint)(pcVar6 + uVar3 * 0x1000);

        if (uVar3 == 0)
        {
          *puVar2 = (uint)&LAB_80000018+2;
        }

        if (uVar3 == uVar4 - 1)
        {
          *puVar2 = *puVar2 & 0xfffffffd | 0x24;
        }
        else
        {
          puVar2[3] = (uint)(puVar2 + 4);
        }

        uVar3 = uVar3 + 1;
        iVar5 = iVar5 + 1;
      } while (uVar3 < uVar4);
    }

    uVar3 = (uint)ptr & 0xffffffe0;

    while (uVar3 <= ((uint)(ptr + iVar5 * 4 + 4) & 0xffffffe0))
    {
      coproc_moveto_Invalidate_Data_Cache_by_MVA(uVar3);
      coproc_moveto_Invalidate_Instruction_Cache_by_MVA(uVar3);
      uVar3 = uVar3 + 0x20;
    }

    *puVar8 = *puVar8 & 0x7fffffff;   //Use DMA to transfer the data
    *puVar8 = *puVar8 | 0x24;
    puVar8[0x20] = 1;

    do {
    } while ((puVar8[0x20] & 1) != 0);

    puVar8[0x20] = 0x82;
    if ((*(byte *)&data->flags & 2) == 0) {
      uVar3 = puVar8[0x23] & 0xfffffffc | 2;
    }
    else {
      uVar3 = puVar8[0x23] & 0xfffffffc | 1;
    }
    puVar8[0x23] = uVar3;
    puVar8[0x21] = (uint)ptr;
    puVar8[0x10] = DAT_80035c18;
    return 0;
  }
  return 0xffffffff;
}


