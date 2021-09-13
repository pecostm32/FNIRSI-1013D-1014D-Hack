uint sys_init_sd_card(int r0)

{
  uint uVar1;
  
  if (r0 != 0)
  {
    return 1;
  }

  uVar1 = sys_sd_card_init(0);

  if (uVar1 != 0)
  {
    uVar1 = 2;
  }

  return uVar1;
}








//------------------------------------------------------------------------------------------------------



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

uint sys_sd_card_init(int interface)

{
  uint uVar1;
  undefined4 *port;
  int *piVar2;
  uint *puVar3;
  char *ptr;
  int iVar4;
  uint *puVar5;
  uint *puVar6;
  uint *puVar7;
  undefined4 *unaff_r9;
  sd_cmd local_40;
  
  port = PORT_C_CFG0;
  puVar5 = SD_MMC_0_BASE;
  puVar6 = SD_MMC_0_BASE + 0x400;
  puVar7 = SD_MMC_0_BASE;
  if ((interface != 0) && (puVar7 = puVar6, interface != 1))
  {
    puVar7 = NULL;
  }

  if (interface == 0)
  {
    unaff_r9 = PORT_F_CFG0;
  }

  iVar4 = 0;

  if (interface == 0)
  {
    do {
      gpio_config_pin(unaff_r9,iVar4,2);
      iVar4 = iVar4 + 1;
    } while (iVar4 < 6);
  }
  else
  {
    if (interface == 1) {
      do {
        gpio_config_pin(port,iVar4,3);
        iVar4 = iVar4 + 1;
      } while (iVar4 < 3);
    }
  }

  puVar3 = BUS_CLK_GATING_REG0;

  uVar1 = 1 << (interface + 8U & 0xff);

  *BUS_CLK_GATING_REG0 = *BUS_CLK_GATING_REG0 | uVar1;

  puVar3[0x98] = uVar1 | puVar3[0x98];

  sd_card_delay(1);

  sd_card_clk_init(interface,DAT_8002446c);

  puVar3 = puVar5;

  if ((interface != 0) && (puVar3 = puVar6, interface != 1))
  {
    puVar3 = NULL;
  }

  puVar3[0x1e] = puVar3[0x1e] | 2;
  puVar3[0x1e] = puVar3[0x1e] & 0xfffffffd;
  uVar1 = DAT_80024470;
  delay(DAT_80024470);
  puVar3[0x1e] = puVar3[0x1e] | 2;
  delay(uVar1);
  puVar3 = puVar5;
  if ((interface != 0) && (puVar3 = puVar6, interface != 1)) {
    puVar3 = NULL;
  }
  *puVar3 = *puVar3 | 7;
  delay(uVar1);
  puVar3 = puVar5;
  if ((interface != 0) && (puVar3 = puVar6, interface != 1)) {
    puVar3 = NULL;
  }
  *puVar3 = *puVar3 & 0xfffffeff;
  puVar3 = puVar5;
  if ((interface != 0) && (puVar3 = puVar6, interface != 1)) {
    puVar3 = NULL;
  }
  puVar3[1] = puVar3[1] | 0x20000;
  puVar3 = puVar5;
  if ((interface != 0) && (puVar3 = puVar6, interface != 1)) {
    puVar3 = NULL;
  }
  puVar3[3] = 0;
  puVar7[2] = 0xffffffff;
  if ((interface != 0) && (puVar5 = puVar6, interface != 1)) {
    puVar5 = NULL;
  }
  puVar5[1] = puVar5[1] | 0x10000;



  sd_card_update_clock(interface);
  sd_card_delay(0x32);


  local_40.cmdidx = 0;
  local_40.cmdarg = 0;
  local_40.resp_type = 0;
  sd_card_send_command(interface,&local_40,NULL);


  sd_card_delay(500);
  local_40.resp_type = 5;
  local_40.cmdidx = 8;
  local_40.cmdarg = DAT_80024474;
  iVar4 = sd_card_send_command(interface,&local_40,NULL);

  piVar2 = DAT_80024478;   //0x8019CF6C  = cardtype


  if (iVar4 == 0)
  {
    uart_printf(s_SD2.0..._80024498);

    local_40.cmdidx = 0x37;
    local_40.cmdarg = 0;
    local_40.resp_type = 5;
    sd_card_send_command(interface,&local_40,NULL);

    uVar1 = _DAT_800244a4;   //0x40FF8000

    local_40.cmdidx = 0x29;
    local_40.resp_type = 7;
    local_40.cmdarg = _DAT_800244a4;
    sd_card_send_command(interface,&local_40,NULL);

    while ((local_40.response[3] & 0x80000000) == 0)
    {
      local_40.cmdidx = 0x37;
      local_40.cmdarg = 0;
      local_40.resp_type = 5;
      sd_card_send_command(interface,&local_40,NULL);

      local_40.cmdidx = 0x29;
      local_40.resp_type = 7;
      local_40.cmdarg = uVar1;
      sd_card_send_command(interface,&local_40,NULL);
    }

//tot hier

    if ((local_40.response[3] & 0x40000000) != 0) 
    {
      ptr = s_@TYPE_SD_HIGH..._800244a7 + 1;
      *piVar2 = 1;
      goto LAB_80024268;
    }
  }
  else
  {
    uart_printf(s_SD1.1..._8002447c);
    local_40.cmdidx = 0;
    local_40.cmdarg = 0;
    local_40.resp_type = 0;
    sd_card_send_command(interface,&local_40,NULL);

    sd_card_delay(500);
    local_40.cmdidx = 0x37;
    local_40.cmdarg = 0;
    local_40.resp_type = 5;
    iVar4 = sd_card_send_command(interface,&local_40,NULL);
    uVar1 = DAT_800244e4;

    if (iVar4 == 0x98)
    {
      local_40.cmdidx = 0;
      local_40.cmdarg = 0;
      local_40.resp_type = 0;
      sd_card_send_command(interface,&local_40,NULL);

      sd_card_delay(1);

      uVar1 = DAT_800244c0;

      local_40.cmdidx = 1;
      local_40.resp_type = 5;
      local_40.cmdarg = DAT_800244c0;
      iVar4 = sd_card_send_command(interface,&local_40,NULL);

      if (iVar4 == 0x98)
      {
        *piVar2 = 0;
        uart_printf(s_ERR_DEVICE..._800244d4);
        return 0xffffffff;
      }

      while ((local_40.response[3] & 0x80000000) == 0) {
        local_40.resp_type = 5;
        local_40.cmdidx = 1;
        local_40.cmdarg = uVar1;
        sd_card_send_command(interface,&local_40,NULL);
      }
      *piVar2 = 3;
      ptr = s_TYPE_MMC..._800244c4;
      goto LAB_80024268;
    }

    if (iVar4 != 0)
    {
      *piVar2 = 0;
      uart_printf(s_Init_Error_!!_80024488);
      return 0xffffffff;
    }

    local_40.resp_type = 7;
    local_40.cmdidx = 0x29;
    local_40.cmdarg = DAT_800244e4;
    sd_card_send_command(interface,&local_40,NULL);

    while ((local_40.response[3] & 0x80000000) == 0)
    {
      local_40.cmdidx = 0x37;
      local_40.cmdarg = 0;
      local_40.resp_type = 5;
      sd_card_send_command(interface,&local_40,NULL);
      local_40.cmdidx = 0x29;
      local_40.resp_type = 7;
      local_40.cmdarg = uVar1;
      sd_card_send_command(interface,&local_40,NULL);
    }
  }

  ptr = s_TYPE_SD_LOW..._800244e8;
  *piVar2 = 2;

LAB_80024268:

//remainder of config part
  uart_printf(ptr);

  if (*piVar2 != 0)
  {
    local_40.cmdidx = 2;
    local_40.resp_type = 7;
    local_40.cmdarg = 0;
    sd_card_send_command(interface,&local_40,NULL);


    puVar5 = DAT_800244bc;                     // 0x80735070
    *DAT_800244bc = local_40.response[3];
    puVar5[1] = local_40.response[2];
    puVar5[2] = local_40.response[1];
    puVar5[3] = local_40.response[0];

    if (*piVar2 == 3)
    {
      local_40.cmdidx = 3;
      local_40.resp_type = 7;
      local_40.cmdarg = 0x10000;
      iVar4 = sd_card_send_command(interface,&local_40,NULL);

      if (iVar4 != 0)
      {
        return 0xffffffff;
      }

      local_40.response[3] = 0x10000;
    }
    else
    {
      local_40.cmdidx = 3;
      local_40.resp_type = 7;
      local_40.cmdarg = 0;
      iVar4 = sd_card_send_command(interface,&local_40,NULL);

      if (iVar4 != 0)
      {
        return 0xffffffff;
      }
    }

    piVar2[1] = local_40.response[3];
  }

  sd_card_get_specifications(interface,&local_40,DAT_80024554);   //0x80735000 ???? 

  sd_card_set_clock_and_bus(interface,&local_40,1);

  return 0;
}



//------------------------------------------------------------------------------------------------------
//Called with 0
//sd_card_init in my code

uint sys_sd_card_init(int in_r0)

{
  uint uVar1;
  undefined4 *port;
  int *piVar2;
  int in_r0;
  uint *puVar3;
  char *pcVar4;
  int iVar5;
  uint *puVar6;
  uint *puVar7;
  uint *puVar8;
  undefined4 *unaff_r9;
  uint local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  
  port = PORT_C_CFG0;
  puVar6 = SD_MMC_0_BASE;
  puVar7 = SD_MMC_0_BASE + 0x400;   //Is pointer calculation ==> SD_MMC_1_BASE
  puVar8 = SD_MMC_0_BASE;

  //Check which interface is selected. F1C100s has two SD_MMC interfaces
  if ((in_r0 != 0) && (puVar8 = puVar7, in_r0 != 1))
  {
    puVar8 = (uint *)0x0;  //No valid interface selected Should have been a return!!!
  }

  if (in_r0 == 0)  //For interface 0 port f is used
  {
    unaff_r9 = PORT_F_CFG0;
  }

  iVar5 = 0;

  if (in_r0 == 0)
  {
    do
    {
      gpio_config_pin(unaff_r9,iVar5,2);  //Setup the pins for SD_MMC
      iVar5 = iVar5 + 1;
    } while (iVar5 < 6);
  }
  else
  {
    if (in_r0 == 1)
    {
      do
      {
        gpio_config_pin(port,iVar5,3);
        iVar5 = iVar5 + 1;
      } while (iVar5 < 3);
    }
  }

  //Enable the interface and lift the reset
  puVar3 = BUS_CLK_GATING_REG0;

  uVar1 = 1 << (in_r0 + 8U & 0xff);    //Bit 8 in BUS_CLK_GATING_REG0 is for SD_MMC0

  *BUS_CLK_GATING_REG0 = *BUS_CLK_GATING_REG0 | uVar1;

  puVar3[0x98] = uVar1 | puVar3[0x98];   //01c202c0  = BUS_SOFT_RST_REG0


  sd_card_delay(1);


  sd_card_clk_init(in_r0,DAT_8002446c);    //0x00061A80

  puVar3 = puVar6;     //SD_MMC_0_BASE

  if ((in_r0 != 0) && (puVar3 = puVar7, in_r0 != 1))
  {
    puVar3 = (uint *)0x0;
  }

  puVar3[0x1e] = puVar3[0x1e] | 2;                    //SD_HWRST_REG  (0x1E is word index, so byte 0x78)
  puVar3[0x1e] = puVar3[0x1e] & 0xfffffffd;           //reset and then lift reset ???

  uVar1 = DAT_80024470;   //0x00001388  = 5000

  delay(DAT_80024470);

  puVar3[0x1e] = puVar3[0x1e] | 2;                    //Or is this lift reset. Yes it is

  delay(uVar1);


  puVar3 = puVar6;     //SD_MMC_0_BASE

  if ((in_r0 != 0) && (puVar3 = puVar7, in_r0 != 1))
  {
    puVar3 = (uint *)0x0;
  }

  *puVar3 = *puVar3 | 7;                            //SD_GCTL_REG   reset  sd/mmc controller, reset fifo, reset dma

  delay(uVar1);

  puVar3 = puVar6;     //SD_MMC_0_BASE

  if ((in_r0 != 0) && (puVar3 = puVar7, in_r0 != 1))
  {
    puVar3 = (uint *)0x0;
  }

  *puVar3 = *puVar3 & 0xfffffeff;                 //SD_GCTL_REG  1111 1111 1111 1111 1111 1110 1111 1111   disable card detect debounce

  puVar3 = puVar6;     //SD_MMC_0_BASE

  if ((in_r0 != 0) && (puVar3 = puVar7, in_r0 != 1))
  {
    puVar3 = (uint *)0x0;
  }

  puVar3[1] = puVar3[1] | 0x20000;                //SD_CLKDIV_REG  Turn card clock of when FSM in idle state

  puVar3 = puVar6;

  if ((in_r0 != 0) && (puVar3 = puVar7, in_r0 != 1))
  {
    puVar3 = (uint *)0x0;
  }

  puVar3[3] = 0;                                  //Single bit interface selected ????

  puVar8[2] = 0xffffffff;                         //Data and response time limit on max???

  if ((in_r0 != 0) && (puVar6 = puVar7, in_r0 != 1))
  {
    puVar6 = (uint *)0x0;
  }

//Tot hier


  puVar6[1] = puVar6[1] | 0x10000;                //SD_CLKDIV_REG  Card clock on

  sd_card_update_clock(in_r0);                    //Send command to update the clock. Not clear what it is for???

  sd_card_delay(0x32);

  //This function is called quite a lot so needs to be figured out
  some_sd_card_stuff_6();   //Send command

  sd_card_delay(500);

  iVar5 = some_sd_card_stuff_6();

  piVar2 = DAT_80024478;

  if (iVar5 == 0)
  {
    uart_printf(s_SD2_0____80024498);

    some_sd_card_stuff_6();

    some_sd_card_stuff_6();

    while ((local_28 & 0x80000000) == 0)
    {
      some_sd_card_stuff_6();

      some_sd_card_stuff_6();
    }

    if ((local_28 & 0x40000000) != 0)
    {
      pcVar4 = s__TYPE_SD_HIGH____800244a7 + 1;
      *piVar2 = 1;
      goto LAB_80024268;
    }
  }
  else
  {
    uart_printf(s_SD1_1____8002447c);

    some_sd_card_stuff_6();

    sd_card_delay(500);

    iVar5 = some_sd_card_stuff_6();

    if (iVar5 == 0x98)
    {
      some_sd_card_stuff_6();

      sd_card_delay(1);

      iVar5 = some_sd_card_stuff_6();

      if (iVar5 == 0x98)
      {
        *piVar2 = 0;
        uart_printf(s_ERR_DEVICE____800244d4);
        return 0xffffffff;
      }

      while ((local_28 & 0x80000000) == 0)
      {
        some_sd_card_stuff_6();
      }

      *piVar2 = 3;
      pcVar4 = s_TYPE_MMC____800244c4;
      goto LAB_80024268;
    }

    if (iVar5 != 0)
    {
      *piVar2 = 0;
      uart_printf(s_Init_Error____80024488);
      return 0xffffffff;
    }

    some_sd_card_stuff_6();

    while ((local_28 & 0x80000000) == 0)
    {
      some_sd_card_stuff_6();

      some_sd_card_stuff_6();
    }
  }

  pcVar4 = s_TYPE_SD_LOW____800244e8;
  *piVar2 = 2;

LAB_80024268:
  uart_printf(pcVar4);

  if (*piVar2 != 0)
  {
    some_sd_card_stuff_6();

    puVar6 = DAT_800244bc;
    *DAT_800244bc = local_28;
    puVar6[1] = local_2c;
    puVar6[2] = local_30;
    puVar6[3] = local_34;

    if (*piVar2 == 3)
    {
      iVar5 = some_sd_card_stuff_6();

      if (iVar5 != 0)
      {
        return 0xffffffff;
      }

      local_28 = 0x10000;
    }
    else
    {
      iVar5 = some_sd_card_stuff_6();

      if (iVar5 != 0)
      {
        return 0xffffffff;
      }
    }

    piVar2[1] = local_28;
  }

  FUN_8001bf1c();

  FUN_800262e0();

  return 0;
}

//-----------------------------------------------------------------------------------

void sd_card_delay(int param_1)

{
  uint local_c;
  uint local_8;
  
  local_8 = 0;

  while (local_8 < (uint)(param_1 * DAT_80032530))   //0x0000073B
  {
    local_c = 0;

    while (local_c < 0x14)
    {
      local_c = local_c + 1;
    }

    local_8 = local_8 + 1;
  }

  return;
}

//-----------------------------------------------------------------------------------

