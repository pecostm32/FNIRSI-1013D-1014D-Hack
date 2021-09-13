
// WARNING: Restarted to delay deadcode elimination for space: stack

int sd_card_set_clock_and_bus(uint param_1,sd_cmd *param_2,int param_3)

{
  int *piVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  sd_data sStack56;
  
  uart_printf(s_SelectCard..._8002660c);
  piVar1 = DAT_8002661c;                //0x8019CF6C   =cardtype
  uVar6 = DAT_8002661c[1];              //             =cardrca

  param_2->cmdidx = 7;              //Select card
  param_2->resp_type = 5;
  param_2->cmdarg = uVar6;
  iVar3 = sd_card_send_command(param_1,param_2,NULL);

  iVar5 = SD_MMC_0_BASE;
  uVar6 = DAT_80026620;    //0x02DC6C00  = 48000000

  if (iVar3 != 0) {
    return iVar3;
  }

  iVar3 = SD_MMC_0_BASE + 0x1000;


  if (*piVar1 == 1)
  {
    uart_printf(s_CARD_TYPE_SD_HIGH_80026628);

    uVar7 = piVar1[1];              //             =cardrca

    param_2->cmdidx = 0x37;
    param_2->resp_type = 5;
    param_2->cmdarg = uVar7;
    iVar4 = sd_card_send_command(param_1,param_2,NULL);

    pbVar2 = DAT_80026640;          //0x80736000  some global variable or data buffer

    if (iVar4 != 0)
    {
      return iVar4;
    }

    sStack56.blocks = 1;
    sStack56.blocksize = 8;
    sStack56.flags = 1;
    sStack56.data = (char *)DAT_80026640;

    param_2->cmdidx = 0x33;
    param_2->resp_type = 5;
    param_2->cmdarg = 0;
    iVar4 = sd_card_send_command(param_1,param_2,&sStack56);

    if (iVar4 != 0)
    {
      return iVar4;
    }

    if (((*pbVar2 & 0xf) == 2) && (iVar4 = FUN_80009edc(param_1,param_2), iVar4 == 0))
    {
      uart_printf(s_Set_Clock:_%d_HZ_80026644,uVar6);
      FUN_800355d8(param_1,uVar6);   //switch clock to 48MHz
    }

    if (param_3 != 1) 
      goto LAB_800265a8;




    uart_printf(s_Card_width_4bit_80026658);

    uVar6 = piVar1[1];
    param_2->cmdidx = 0x37;
    param_2->resp_type = 5;
    param_2->cmdarg = uVar6;
    iVar4 = sd_card_send_command(param_1,param_2,NULL);

    if (iVar4 != 0)
    {
      return iVar4;
    }

    param_2->cmdidx = 6;
    param_2->resp_type = 5;
    param_2->cmdarg = 2;
    iVar4 = sd_card_send_command(param_1,param_2,NULL);

    if (iVar4 != 0)
    {
      return iVar4;
    }
  }
  else
  {
    if (*piVar1 != 2)
      goto LAB_800265a8;

    uart_printf(s_CARD_TYPE_SD_LOW_8002666c);

    sd_card_change_clock(param_1,uVar6);

    if (param_3 != 1)
      goto LAB_800265a8;

    uart_printf(s_Card_width_4bit_80026658);

    uVar6 = piVar1[1];

    param_2->cmdidx = 0x37;
    param_2->resp_type = 5;
    param_2->cmdarg = uVar6;

    iVar4 = sd_card_send_command(param_1,param_2,NULL);

    if (iVar4 != 0)
    {
      return iVar4;
    }

    param_2->cmdidx = 6;
    param_2->resp_type = 5;
    param_2->cmdarg = 2;
    iVar4 = sd_card_send_command(param_1,param_2,NULL);

    if (iVar4 != 0)
    {
      return iVar4;
    }
  }

  if ((param_1 != 0) && (iVar5 = iVar3, param_1 != 1))
  {
    iVar5 = 0;
  }

  *(undefined4 *)(iVar5 + 0xc) = 1;

LAB_800265a8:
  uart_printf(s_SD_BLOCK_SIZE_512_80026680);

  param_2->cmdidx = 0x10;
  param_2->resp_type = 0xd;
  param_2->cmdarg = 0x200;
  sd_card_send_command(param_1,param_2,NULL);

  param_2->cmdidx = 7;
  param_2->cmdarg = 0;
  param_2->resp_type = 0;
  sd_card_send_command(param_1,param_2,NULL);

  return 0;
}


