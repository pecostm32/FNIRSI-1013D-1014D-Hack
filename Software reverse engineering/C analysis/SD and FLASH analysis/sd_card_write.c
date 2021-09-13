

int sd_card_write(uint interface,uint sector,uint count,byte *buffer)
{
  int *piVar1;
  int iVar2;
  uint uVar3;
  undefined2 uVar4;
  undefined2 local_50;
  undefined4 local_4c;
  uint local_48;
  byte *pbStack48;
  undefined4 uStack44;
  uint uStack40;
  undefined4 uStack36;
  
  piVar1 = DAT_80024898;    //0x8019CF6C

  uVar3 = (sector + count) - 1;

  if ((uint)DAT_80024898[3] < uVar3)
  {
    uart_printf(DAT_8002489c,uVar3);    //=ERROR: Fail to access invalid sector number

    uart_printf(PTR_s__The_max_valid_sector_number_for_800248a0,piVar1[3]);

    return DAT_800248a4;   //0xFFFCA9A3
  }

  if (buffer == (byte *)0x0)
  {
    uart_printf(s_ERROR:_fmiSD_Read_in():_uBufcnt_c_800248c4);
    return DAT_800248f4;
  }

  if (((uint)buffer & 3) != 0)
  {
    uart_printf(s_Addr_Align_Err_..._800248a8);
    return DAT_800248c0;   //0xFFF4A025
  }

  local_48 = DAT_80024898[1];

  if (*DAT_80024898 != 1)
  {
    sector = sector << 9;
  }

  local_50 = 7;

  if (count == 1)
  {
    uVar4 = 0x18;
  }
  else
  {
    uVar4 = 0x19;
  }

  local_4c = 0xd;

  iVar2 = sd_card_send_command(interface,(uint16 *)&local_50,(uint *)0x0);

  if (iVar2 == 0)
  {
    uStack36 = 0x200;
    uStack44 = 2;
    local_4c = 0xd;
    local_50 = uVar4;
    local_48 = sector;
    pbStack48 = buffer;
    uStack40 = count;

    iVar2 = sd_card_send_command(interface,(uint16 *)&local_50,(uint *)&pbStack48);

    if (iVar2 == 0)
    {
      local_50 = 7;
      local_48 = 0;
      local_4c = 0;
      sd_card_send_command(interface,(uint16 *)&local_50,(uint *)0x0);
      return 0;
    }

    return iVar2;
  }

  return iVar2;
}





int sd_card_write(uint interface,uint sector,uint blocks,byte *buffer)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  ushort uVar4;
  sd_cmd local_50;
  sd_data sStack48;
  
  piVar1 = DAT_80024898;
  uVar3 = (sector + blocks) - 1;
  if ((uint)DAT_80024898[3] < uVar3) {
    uart_printf(DAT_8002489c,uVar3);
    uart_printf(PTR_s__The_max_valid_sector_number_for_800248a0,piVar1[3]);
    return DAT_800248a4;
  }
  if (buffer == NULL) {
    uart_printf(s_ERROR:_fmiSD_Read_in():_uBufcnt_c_800248c4);
    return DAT_800248f4;
  }
  if (((uint)buffer & 3) != 0) {
    uart_printf(s_Addr_Align_Err_..._800248a8);
    return DAT_800248c0;
  }
  local_50.cmdarg = DAT_80024898[1];
  if (*DAT_80024898 != 1) {
    sector = sector << 9;
  }
  local_50.cmdidx = 7;
  if (blocks == 1) {
    uVar4 = 0x18;
  }
  else {
    uVar4 = 0x19;
  }
  local_50.resp_type = 0xd;
  iVar2 = sd_card_send_command(interface,&local_50,NULL);
  if (iVar2 == 0) {
    sStack48.blocksize = 0x200;
    sStack48.flags = 2;
    local_50.resp_type = 0xd;
    local_50.cmdidx = uVar4;
    local_50.cmdarg = sector;
    sStack48.data = (char *)buffer;
    sStack48.blocks = blocks;
    iVar2 = sd_card_send_command(interface,&local_50,&sStack48);
    if (iVar2 == 0) {
      local_50.cmdidx = 7;
      local_50.cmdarg = 0;
      local_50.resp_type = 0;
      sd_card_send_command(interface,&local_50,NULL);
      return 0;
    }
    return iVar2;
  }
  return iVar2;
}



