int sd_card_read(uint interface,uint sector,uint count,byte *buffer)
{
  int *piVar1;
  int iVar2;
  uint uVar3;
  ushort uVar4;
  sd_cmd local_50;
  sd_data sStack48;
  
  piVar1 = DAT_800246c4;                             //0x8019CF6C    cardtype
  uVar3 = (sector + count) - 1;

  if ((uint)DAT_800246c4[3] < uVar3)                 //0x8019CF6C    cardsectors
  {
    uart_printf(DAT_800246c8,uVar3);
    uart_printf(PTR_s__The_max_valid_sector_number_for_800246cc,piVar1[3]);
    return DAT_800246d0;    //0xFFFCA9A3
  }

  if (buffer == NULL)
  {
    uart_printf(s_ERROR:_fmiSD_Read_in():_uBufcnt_c_800246fc);
    return DAT_8002472c;    //0xFFF4A025
  }

  if (((uint)buffer & 3) != 0)
  {
    uart_printf(s_SD_Read_Addr_Align_Err[%08x]_..._800246d4,buffer);
    return DAT_800246f8;
  }

  local_50.cmdarg = DAT_800246c4[1];                 //0x8019CF6C  (0x8019cf70)  cardrca

  if (*DAT_800246c4 != 1)               //cardtype other then 1 use sector * 512????????
  {
    sector = sector << 9;
  }

  local_50.cmdidx = 7;

  if (count == 1)                      //What is this for??? command type select
  {
    uVar4 = 0x11;  //read single block
  }
  else
  {
    uVar4 = 0x12;  //read multiple block
  }

  local_50.resp_type = 0xd;

  iVar2 = sd_card_send_command(interface,&local_50,NULL);  //Select card command

  if (iVar2 == 0)
  {
    sStack48.blocksize = 0x200;
    sStack48.flags = 1;
    local_50.resp_type = 0xd;
    local_50.cmdidx = uVar4;
    local_50.cmdarg = sector;
    sStack48.data = (char *)buffer;
    sStack48.blocks = count;

    iVar2 = sd_card_send_command(interface,&local_50,&sStack48);

    if (iVar2 == 0)
    {
      local_50.cmdidx = 7;
      local_50.cmdarg = 0;
      local_50.resp_type = 0;
      sd_card_send_command(interface,&local_50,NULL);  //Deselect card command

      return 0;
    }

    return iVar2;
  }

  return iVar2;
}

