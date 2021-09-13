int sd_card_change_clock(uint interface,uint frequency)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  code *UNRECOVERED_JUMPTABLE;
  
  iVar3 = SD_MMC_0_BASE;
  iVar5 = SD_MMC_0_BASE + 0x1000;
  iVar4 = SD_MMC_0_BASE;

  if ((interface != 0) && (iVar4 = iVar5, interface != 1))
  {
    iVar4 = 0;
  }

  iVar1 = SD_MMC_0_BASE;

  if ((interface != 0) && (iVar1 = iVar5, interface != 1))
  {
    iVar1 = 0;
  }

  *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) & 0xfffeffff;

  iVar1 = sd_card_update_clock(interface);

  if ((iVar1 == 0) && (uVar2 = interface, sd_card_clk_init(interface,frequency), uVar2 == 0))
  {
    *(uint *)(iVar4 + 4) = *(uint *)(iVar4 + 4) & 0xffffff00;

    if ((interface != 0) && (iVar3 = iVar5, interface != 1))
    {
      iVar3 = 0;
    }

    *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) | 0x10000;

    iVar3 = sd_card_update_clock(interface);

    if (iVar3 == 0)
    {F
      return iVar3;
    }
  }

  return -1;
}

