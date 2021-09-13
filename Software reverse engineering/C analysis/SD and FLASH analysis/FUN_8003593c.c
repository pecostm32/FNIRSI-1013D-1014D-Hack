
//mmc_trans_data_by_cpu

undefined4 FUN_8003593c(uint interface,sd_data *data)

{
  byte bVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  uint uVar7;
  bool bVar8;
  
  bVar1 = *(byte *)&data->flags;

  pcVar6 = data->data;

  uVar5 = data->blocksize * data->blocks;

  if ((bVar1 & 1) == 0)     //no read
  {
    uVar7 = 8;    //FIFO_FULL flag
  }
  else
  {
    uVar7 = 4;   //FIFO_EMPTY flag
  }

  uVar4 = (uVar5 >> 8) * 1000;

  puVar2 = SD_MMC_0_BASE;

  if ((interface != 0) && (puVar2 = DAT_80035a34, interface != 1))
  {
    puVar2 = NULL;
  }

  //Time out based on number of bytes
  if (uVar4 < DAT_80035a38)    //0x001E8480
  {
    uVar4 = DAT_80035a38;
  }

  *puVar2 = *puVar2 | 0x80000000;   //SD0_GCTL   Set FIFO access mode to AHB bus

  uVar3 = 0;

  if (uVar5 >> 2 != 0)
  {
    do
    {
      while ((puVar2[0xf] & uVar7) != 0)   //SD0_STAR  status register
      {
        bVar8 = uVar4 == 0;
        uVar4 = uVar4 - 1;

        if (bVar8)
        {
          uart_printf(s_Data[%d]_timeout_BIT=0x%08x..._80035a3c,uVar3,puVar2[0xf]);
          return 0xffffffff;
        }

        delay(5);
      }

      if ((bVar1 & 1) == 0)
      {
        puVar2[0x80] = *(uint *)(pcVar6 + uVar3 * 4);
      }
      else
      {
        *(uint *)(pcVar6 + uVar3 * 4) = puVar2[0x80];
      }

      uVar3 = uVar3 + 1;
    } while (uVar3 < uVar5 >> 2);
  }

  return 0;
}


