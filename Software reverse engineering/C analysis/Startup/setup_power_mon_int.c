void setup_power_mon_int(void)

{
  undefined4 *port;
  
  enable_keyadc();
  port = DAT_80002c00;

  gpio_config_pin(DAT_80002c00,0xc,0);

  gpio_config_pin(port,0xb,0);   //Why o why
  gpio_config_pin(port,0xb,6);   //It needs to be interrupt
  FUN_800176b4(1,0xb,1);
  FUN_800176f0(1,0xb);
  setup_interrupt(1,0x27,(uint)PTR_LAB_80002c04,3);   //type 1 interrupt, port E interrupt source, function, priority 3
  return;
}



void FUN_800176b4(int param_1,uint param_2,int param_3)
void config_external_interrupt (uint port, uint pin, uint setting)
{
  uint uVar1;
  uint *puVar2;
  
  puVar2 = (uint *)(param_1 * 0x20 + (param_2 >> 3) * 4 + DAT_800176ec);    //01C20A00  Non documented external interrupt control configuration
  uVar1 = (param_2 << 0x1d) >> 0x1b;  //= (x & 0x07) << 2
  *puVar2 = *puVar2 & ~(0xf << uVar1);  //Clear fourth nibble
  *puVar2 = *puVar2 | param_3 << uVar1;  //Put in the setting
  return;
}


void FUN_800176f0(int param_1,undefined4 param_2)
void enable_external_interrupt (uint port, uint pin)
{
  uint uVar1;
  uint *puVar2;
  uint uVar3;
  
  puVar2 = (uint *)(DAT_80017720 + param_1 * 0x20);    //0x01C20A10 + (1 * 0x20) ==> 01C20A30
  uVar3 = *puVar2;
  uVar1 = FUN_8000056c(1,0,param_2);
  *puVar2 = uVar1 | uVar3;
  return;
}



longlong FUN_8000056c(uint param_1,int param_2,uint param_3)
longlong convert_pin_number_to_parameter (uint p1, uint p2, uint pin)
{
  if ((int)(param_3 - 0x20) < 0)
  {
    return CONCAT44(param_2 << (param_3 & 0xff) | param_1 >> (0x20 - param_3 & 0xff),param_1 << (param_3 & 0xff));
  }
  return (ulonglong)(param_1 << (param_3 - 0x20 & 0xff)) << 0x20;
}




void power_off_interrupt_handler(void)

{
  signal_sys_ok();
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}






// WARNING: Restarted to delay deadcode elimination for space: stack
//ALso called at the after calibration

void signal_sys_ok(void)

{
  undefined uVar1;
  undefined uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uchar *puVar6;
  uint uVar7;
  uint uVar8;
  uchar *extraout_r1;
  uchar *extraout_r1_00;
  uint *puVar9;
  uint uVar10;
  uchar *puVar11;
  undefined4 unaff_r4;
  uint *puVar12;
  uint uVar13;
  int iVar14;
  undefined4 in_lr;
  uchar uStack72;
  undefined uStack71;
  undefined uStack70;
  undefined uStack69;
  uint uStack68;
  uint *puStack64;
  uchar *puStack60;
  uint uStack52;
  uint *puStack48;
  uint uStack44;
  uint uStack40;
  undefined4 uStack36;
  undefined4 uStack4;power_off_interrupt_handler
  
  iVar14 = DAT_80025bec;
  *(short *)(DAT_80025bec + 0x44) = (short)DAT_80025be8;
  *(undefined *)(iVar14 + 0x21) = 0;
  uStack4 = in_lr;
  set_fpga_trigger_mode();
  save_config_data(DAT_80025bf0);


//This is flash write
  uStack36 = unaff_r4;
  uStack40 = 500;
  uStack44 = FLASH_CONFIG_DATA;
  puStack48 = DAT_80025bf0;
  uStack52 = 0;
  uStack68 = FLASH_CONFIG_DATA >> 0xc;
  uVar10 = FLASH_CONFIG_DATA & 0xfff;
  uVar13 = 0x1000 - uVar10;
  if (499 < 0x1000 - uVar10) {
    uVar13 = 500;
  }
  puStack64 = (uint *)(SPI0_BASE + 8);
  do {
    uVar4 = uStack52;
    puVar9 = puStack64;
    puStack60 = DAT_80036614;
    iVar14 = uStack68 << 0xc;
    uStack72 = '\x03';
    uVar1 = (undefined)((uStack68 << 0x14) >> 0x18);
    uVar2 = (undefined)((uStack68 << 0x1c) >> 0x18);
    uStack69 = 0;
    *puStack64 = *puStack64 & 0xffffff4f;
    uStack71 = uVar1;
    uStack70 = uVar2;
    uVar5 = spi_start_transfer(uStack52,&uStack72,NULL,4);
    puVar6 = extraout_r1;
    if (uVar5 == 4) {
      spi_start_transfer(uVar4,NULL,puStack60,0x1000);
      puVar6 = extraout_r1_00;
    }
    uVar4 = uStack52;
    iVar3 = SPI0_BASE;
    *puVar9 = *puVar9 & 0xffffff4f | 0x80;
    if (uVar13 != 0) {
      puVar6 = DAT_80036614;
    }
    uVar5 = 0;
    if (uVar13 != 0) {
      do {
        if (puVar6[uVar10 + uVar5] != -1) break;
        uVar5 = uVar5 + 1 & 0xfffeffff;
      } while (uVar5 < uVar13);
    }
    if (uVar5 < uVar13) {
      uStack72 = ' ';
      uStack69 = 0;
      uStack71 = uVar1;
      uStack70 = uVar2;
      spi_flash_write_enable(uStack52);
      spi_flash_wait_while_busy(uVar4);
      puVar9 = puStack64;
      *puStack64 = *puStack64 & 0xffffff4f;
      spi_start_transfer(uVar4,&uStack72,NULL,4);
      *puVar9 = *puVar9 & 0xffffff4f | 0x80;
      spi_flash_wait_while_busy(uVar4);
      uVar4 = uStack52;
      if (uVar13 != 0) {
        puVar11 = DAT_80036614 + uVar10;
        puVar6 = puVar11 + -1;
        puVar9 = (uint *)((int)puStack48 + -1);
        if ((uVar13 & 1) != 0) {
          *puVar11 = *(uchar *)puStack48;
          puVar6 = puVar11;
          puVar9 = puStack48;
        }
        uVar10 = uVar13 >> 1;
        while (uVar10 != 0) {
          uVar10 = uVar10 - 1;
          puVar6[1] = *(uchar *)((int)puVar9 + 1);
          puVar9 = (uint *)((int)puVar9 + 2);
          puVar6 = puVar6 + 2;
          *puVar6 = *(uchar *)puVar9;
        }
      }
      puVar9 = (uint *)(iVar3 + uStack52 * 0x1000 + 8);
      uVar10 = 0x1000;
      uVar5 = 0x100;
      puVar6 = DAT_80036614;
      while( true ) {
        uStack72 = '\x02';
        uStack71 = (undefined)((uint)iVar14 >> 0x10);
        uStack70 = (undefined)((uint)iVar14 >> 8);
        uStack69 = 0;
        spi_flash_write_enable(uVar4);
        spi_flash_wait_while_busy(uVar4);
        *puVar9 = *puVar9 & 0xffffff4f;
        uVar7 = spi_start_transfer(uVar4,&uStack72,NULL,4);
        if (uVar7 == 4) {
          spi_start_transfer(uVar4,puVar6,NULL,uVar5);
        }
        *puVar9 = *puVar9 & 0xffffff4f | 0x80;
        spi_flash_wait_while_busy(uVar4);
        if (uVar10 == uVar5) break;
        uVar10 = uVar10 - uVar5 & 0xffff;
        puVar6 = puVar6 + uVar5;
        iVar14 = iVar14 + uVar5;
        uVar5 = uVar10;
        if (0x100 < uVar10) {
          uVar5 = 0x100;
        }
      }
    }
    else {
      uVar10 = 0x100 - (uStack44 & 0xff);
      if (uVar13 <= uVar10) {
        uVar10 = uVar13;
      }
      puVar12 = (uint *)(iVar3 + uStack52 * 0x1000 + 8);
      uVar7 = uStack44;
      uVar5 = uVar13;
      puVar9 = puStack48;
      while( true ) {
        uStack72 = '\x02';
        uStack71 = (undefined)(uVar7 >> 0x10);
        uStack70 = (undefined)(uVar7 >> 8);
        uStack69 = (undefined)uVar7;
        spi_flash_write_enable(uVar4);
        spi_flash_wait_while_busy(uVar4);
        *puVar12 = *puVar12 & 0xffffff4f;
        uVar8 = spi_start_transfer(uVar4,&uStack72,NULL,4);
        if (uVar8 == 4) {
          spi_start_transfer(uVar4,(uchar *)puVar9,NULL,uVar10);
        }
        *puVar12 = *puVar12 & 0xffffff4f | 0x80;
        spi_flash_wait_while_busy(uVar4);
        if (uVar5 == uVar10) break;
        uVar5 = uVar5 - uVar10 & 0xffff;
        puVar9 = (uint *)((int)puVar9 + uVar10);
        uVar7 = uVar7 + uVar10;
        uVar10 = uVar5;
        if (0x100 < uVar5) {
          uVar10 = 0x100;
        }
      }
    }
    if (uStack40 == uVar13) {
      return;
    }
    uVar10 = 0;
    uStack68 = uStack68 + 1;
    uStack40 = uStack40 - uVar13 & 0xffff;
    puStack48 = (uint *)((int)puStack48 + uVar13);
    uStack44 = uStack44 + uVar13;
    uVar13 = uStack40;
    if (0x1000 < uStack40) {
      uVar13 = 0x1000;
    }
  } while( true );
}


