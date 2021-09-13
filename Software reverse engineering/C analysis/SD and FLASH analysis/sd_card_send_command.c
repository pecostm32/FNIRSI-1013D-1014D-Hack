
//SD card function, used a lot

//some_sd_card_stuff_6

//command (param_2) is a structure of some sort

//unsigned short
//unsigned short
//int
//int


struct mmc_cmd {
	ushort cmdidx;
	uint resp_type;
	uint cmdarg;
	uint response[4];
};

struct mmc_data {
	union {
		char *dest;
		const char *src; /* src buffers don't get written to */
	};
	uint flags;
	uint blocks;
	uint blocksize;
};




int sd_card_send_command(int interface,sd_cmd *cmd,sd_data *data)

{
  int iVar1;
  uint uVar2;
  char *ptr;
  uint *puVar3;
  uint uVar4;
  int iVar5;
  uint *puVar6;
  uint uVar7;
  undefined4 uVar8;
  uint *puVar9;
  uint *puVar10;
  code *UNRECOVERED_JUMPTABLE_00;
  bool bVar11;
  bool bVar12;
  
  puVar9 = SD_MMC_0_BASE;
  bVar11 = false;
  puVar10 = SD_MMC_0_BASE + 0x400;
  puVar6 = SD_MMC_0_BASE;
  if ((interface != 0) && (puVar6 = puVar10, interface != 1))
  {
    puVar6 = (uint *)0x0;
  }

  if (cmd->cmdidx == 0xc)
  {
    return 0;
  }

  uVar2 = cmd->resp_type;
  uVar7 = 0x80000000;

  if (cmd->cmdidx == 0)
  {
    uVar7 = DAT_800370e0;
  }

  if ((uVar2 & 1) != 0)
  {
    uVar7 = uVar7 | 0x40;
  }

  if ((uVar2 & 2) != 0)
  {
    uVar7 = uVar7 | 0x80;
  }

  if ((uVar2 & 4) != 0)
  {
    uVar7 = uVar7 | 0x100;
  }








  if (data == (sd_data *)0x0)
  {
LAB_80036e08:
    puVar6[7] = cmd->cmdarg;

    if (data == (sd_data *)0x0)
    {
      puVar6[6] = cmd->cmdidx | uVar7;
    }
    else
    {

//This differs from sunxi_mmc implementation

      if (data->blocks * data->blocksize < 0x41)
      {
        puVar6[6] = cmd->cmdidx | uVar7;

        iVar1 = FUN_8003593c(interface,data);   //Small amount of data send directly with CPU control

        if (iVar1 != 0)
        {
          uart_printf(s_error_%08x_80037104,DAT_80037100 & puVar6[0xe]);
LAB_80037038:
          uVar8 = 0xffffff68;
          goto LAB_8003703c;
        }
      }
      else
      {
        bVar11 = true;

        //For bigger data blocks use DMA
        FUN_80035a60(interface,data,DAT_800370fc);    //0x80734000

        puVar6[6] = cmd->cmdidx | uVar7;
      }
    }

    iVar1 = DAT_80037114;   //0x00030D40
    uVar7 = DAT_80037100;   //0x0000BFC2




    puVar3 = puVar9;  //SD_MMC_0_BASE

    if ((interface != 0) && (puVar3 = puVar10, interface != 1))  //SD_MMC_1_BASE
    {
      puVar3 = (uint *)0x0;
    }







    iVar5 = DAT_80037114;   //0x00030D40


//Wait on some interrupt or a timeout (mmc_rint_wait)
    do
    {
      uVar2 = puVar3[0xe];    //SD0_RISR  raw interrupt status register

      bVar12 = iVar5 == 0;

      iVar5 = iVar5 + -1;

      if ((bVar12) || ((uVar2 & DAT_80037100) != 0))  //0x0000BFC2   All error bits!!!
      {
        uart_printf(PTR_s_ERR:_mmc%d_tmier=[%d]_timeout_%x_80037118,interface,iVar5,uVar2 & DAT_80037100);
        ptr = s_ERR1_8003711c;
        goto LAB_80037000;
      }
    } while ((uVar2 & 4) == 0); //SD_RINT_COMMAND_DONE








    uVar8 = 0;

    if (bVar11)
    {
      puVar3 = puVar9;

      if ((interface != 0) && (puVar3 = puVar10, interface != 1))
      {
        puVar3 = (uint *)0x0;
      }

      puVar3 = puVar3 + 0x22;
      uVar2 = (uint)((*puVar3 & 1) != 0);

      if ((*puVar3 & 2) != 0)
      {
        uVar2 = uVar2 | 2;
      }

      bVar12 = uVar2 == 0;

      if (bVar12)
      {
        do
        {
          if (!bVar12) goto LAB_80036fa0;

          puVar3 = puVar9;

          if ((interface != 0) && (puVar3 = puVar10, interface != 1))
          {
            puVar3 = (uint *)0x0;
          }

          uVar2 = (uint)((puVar3[0x22] & 1) != 0);

          if ((puVar3[0x22] & 2) != 0)
          {
            uVar2 = uVar2 | 2;
          }

          bVar12 = uVar2 == 0;
        } while (bVar12);

        puVar3[0x22] = uVar2 | puVar3[0x22];
      }
      else
      {
        *puVar3 = uVar2 | *puVar3;
      }
    }

LAB_80036fa0:
    if (data != (sd_data *)0x0)
    {
      if (data->blocks < 2)
      {
        uVar2 = 8;
      }
      else
      {
        uVar2 = 0x4000;
      }

      if ((interface != 0) && (puVar9 = puVar10, interface != 1))
      {
        puVar9 = (uint *)0x0;
      }

LAB_80036fd4:
      uVar4 = puVar9[0xe];
      bVar12 = iVar1 != 0;
      iVar1 = iVar1 + -1;

      if ((bVar12) && ((uVar4 & uVar7) == 0))
        goto LAB_80037008;

      uart_printf(PTR_s_ERR:_mmc%d_tmier=[%d]_timeout_%x_80037118,interface,iVar1,uVar4 & uVar7);
      ptr = s_ERR2_80037124;

LAB_80037000:
      uVar8 = 0xffffff68;
      uart_printf(ptr);
      goto LAB_8003703c;
    }

LAB_80037010:
    if ((cmd->resp_type & 8) != 0)
    {
      iVar1 = DAT_8003712c;

      do
      {
        bVar12 = iVar1 == 0;
        iVar1 = iVar1 + -1;

        if (bVar12)
        {
          uart_printf(s_busy_timeout_80037130);
          goto LAB_80037038;
        }
      } while ((puVar6[0xf] & 0x200) != 0);
    }

    cmd->response[0] = puVar6[8];
    cmd->response[1] = puVar6[9];

    if ((cmd->resp_type & 2) != 0)
    {
      cmd->response[2] = puVar6[10];
      cmd->response[3] = puVar6[0xb];
    }
  }







//This bit is when there is data given

  else
  {
    if ((*(byte *)&data->data & 3) == 0)
    {
      uVar2 = uVar7 | 0x2200;

      if ((*(byte *)&data->flags & 2) != 0)
      {
        uVar2 = uVar7 | 0x2600;
      }

      uVar7 = uVar2;

      if (1 < data->blocks)
      {
        uVar7 = uVar7 | 0x1000;
      }

      puVar6[4] = data->blocksize;
      puVar6[5] = data->blocksize * data->blocks;
      goto LAB_80036e08;
    }

    uVar8 = 0xffffffff;
    uart_printf(s_Addr_Align_Err_..._800370e4);

LAB_8003703c:
    uart_printf(s_err_reset..._80037140);
    *puVar6 = 7;

    sd_card_update_clock(interface);
  }

  if (data != (sd_data *)0x0 && bVar11)
  {
    puVar6[0x22] = puVar6[0x22];   //SD_IDST_REG
    puVar6[0x23] = 0;              //SD_IDIE_REG
    puVar6[0x20] = 0;              //SD_DMAC_REG
  }

  puVar6[0xe] = puVar6[0xe];       //SD_RISR_REG Reset the active bits

  *puVar6 = *puVar6 | 6;           //DMA and FIFO reset

  bVar11 = data == (sd_data *)0x0;

  if (!bVar11)
  {
    bVar11 = (*(byte *)&data->flags & 1) == 0;
  }

  if (!bVar11)
  {
    uVar7 = (uint)data->data & 0xffffffe0;

    while (uVar7 <= ((uint)(data->data + data->blocks * data->blocksize) & 0xffffffe0))
    {
      coproc_moveto_Invalidate_Data_Cache_by_MVA(uVar7);
      coproc_moveto_Invalidate_Instruction_Cache_by_MVA(uVar7);
      uVar7 = uVar7 + 0x20;
    }
  }

  return uVar8;

LAB_80037008:

  if ((uVar4 & uVar2) != 0)
    goto LAB_80037010;

  goto LAB_80036fd4;
}


//-----------
LAB_800370b8
        800370b8 3e 0f 07 ee     mcr        p15,0x0,r0,cr7,cr14,0x1
        800370bc 35 0f 07 ee     mcr        p15,0x0,r0,cr7,cr5,0x1
        800370c0 20 00 80 e2     add        r0,r0,#0x20
        800370c4 01 00 50 e1     cmp        r0,r1
        800370c8 fa ff ff 9a     bls        LAB_800370b8


