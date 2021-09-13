undefined4 sd_card_update_clock(int param_1)

{
  int iVar1;
  uint *puVar2;
  bool bVar3;
  
  iVar1 = SD_MMC_0_BASE;

  if ((param_1 != 0) && (iVar1 = DAT_80035c8c, param_1 != 1))   //0x01C10000
  {
    iVar1 = 0;
  }

  puVar2 = (uint *)(iVar1 + 0x18);                              //SD_CMDR_REG
                                                                //              3322 2222 2222 1111 1111 1100 0000 0000
                                                                //              1098 7654 3210 9876 5432 1098 7654 3210
  *puVar2 = DAT_80035c90;                                       //0x80202000    1000 0000 0010 0000 0010 0000 0000 0000  Start command, Change clock and wait for data transfer complete

  iVar1 = DAT_80035c94;                                         //0x000007CF  = 1999 max time out count

  if ((*puVar2 & 0x80000000) != 0)                              //Check if commnd active
  {
    while (delay(5), (*puVar2 & 0x80000000) != 0)               //Wait for it to complete with a max time out
    {
      bVar3 = iVar1 == 0;
      iVar1 = iVar1 + -1;

      if (bVar3)
      {
        uart_printf(s_timeout____80035c98);
        return 0xffffffff;
      }
    }
  }

  return 0;
}

