
void check_config_ok_refresh_it_on_fail(void)

{
  undefined2 uVar1;
  int iVar2;
  uint uVar3;
  uint16 *puVar4;
  undefined *puVar5;
  int iVar6;
  undefined2 *puVar7;
  uint16 *puVar8;
  undefined *puVar9;
  int iVar10;
  undefined *puVar11;
  
  uVar3 = DAT_80016b5c;
  iVar2 = DAT_80016b58;

  if (*(ushort *)(DAT_80016b58 + 0x44) == DAT_80016b5c)  //0x8019D5E4  == 0x1432
  {
    return;
  }

  reset_config_data();
  *(short *)(iVar2 + 0x44) = (short)uVar3;
  *(undefined *)(iVar2 + 0x21) = 0;
  set_fpga_trigger_mode();
  save_config_data(DAT_80016b60);
  uVar3 = FLASH_CONFIG_DATA;
  write_to_flash(FLASH_CONFIG_DATA,(uchar *)DAT_80016b60,500);
  read_from_flash(uVar3,(uint *)DAT_80016b60,500);

  restore_config_data(DAT_80016b60);
}


