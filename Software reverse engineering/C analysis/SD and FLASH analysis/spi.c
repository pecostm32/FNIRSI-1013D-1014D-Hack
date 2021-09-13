//------------------------------------------------------------------------------------------------

void sys_spi0_init(void)

{
  undefined4 *port;
  int iVar1;
  uint uVar2;
  uint *puVar3;
  uint uVar4;
  
  port = PORT_C_CFG0;

  gpio_config_pin(PORT_C_CFG0,0,2);
  gpio_config_pin(port,1,2);
  gpio_config_pin(port,2,2);
  gpio_config_pin(port,3,2);

  puVar3 = BUS_SOFT_RST_REG0;
  uVar4 = *BUS_SOFT_RST_REG0;

  uVar2 = FUN_8000056c(1,0,0x14);

  *puVar3 = uVar4 | uVar2;     //lift reset

  puVar3 = puVar3 + -0x98;

  *puVar3 = uVar2 | *puVar3;   //enable clock

  iVar1 = SPI0_BASE;

  *(undefined4 *)(SPI0_BASE + 0x24) = DAT_80036248;

  puVar3 = (uint *)(iVar1 + 4);
  *puVar3 = *puVar3 | 0x80000083;

  do
  {
  } while ((*puVar3 & 0x80000000) != 0);

  *(uint *)(iVar1 + 8) = *(uint *)(iVar1 + 8) & 0xfffffffc | 0x44;
  *(uint *)(iVar1 + 0x18) = *(uint *)(iVar1 + 0x18) | 0x80008000;

  return;
}


//------------------------------------------------------------------------------------------------
//1, 0, 0x14  (bit 20)
longlong FUN_8000056c(uint param_1,int param_2,uint param_3)
{
  if ((int)(param_3 - 0x20) < 0)
  {
    return CONCAT44(param_2 << (param_3 & 0xff) | param_1 >> (0x20 - param_3 & 0xff), param_1 << (param_3 & 0xff));
  }

  return (ulonglong)(param_1 << (param_3 - 0x20 & 0xff)) << 0x20;
}

//------------------------------------------------------------------------------------------------

//Called from flash write
uint spi_flash_write_enable(uint interface)

{
  uint uVar1;
  undefined4 in_r3;
  uint *puVar2;
  uint uVar3;
  undefined4 local_10;
  
  local_10 = 6;

  uVar3 = 0;

  puVar2 = (uint *)(DAT_800250f4 + interface * 0x1000 + 8);   //0x01C05000

  *puVar2 = *puVar2 & 0xffffff4f;   //Assert select line

  uVar1 = spi0_start_transfer(interface,(uchar *)&local_10,0,1);     //Start the transfer. Send command 0x06 to the flash

  if (uVar1 != 1)
  {
    uVar3 = 0xffffffff;
  }

  *puVar2 = *puVar2 & 0xffffff4f | 0x80;   //Deselect the flash
  return uVar3;
}


//------------------------------------------------------------------------------------------------


void read_from_flash(uint address,uint *buffer,uint count)

{
  uint uVar1;
  uint *puVar2;
  undefined4 local_20;
  
  local_20 = CONCAT13((char)address, CONCAT12((char)(address >> 8),CONCAT11((char)(address >> 0x10),3)));

  puVar2 = (uint *)(DAT_800375ec + 8);

  *puVar2 = *puVar2 & 0xffffff4f;

  uVar1 = spi_start_transfer(0,(uchar *)&local_20,(uchar *)0x0,4);

  if (uVar1 == 4)
  {
    spi_start_transfer(0,(uchar *)0x0,(uchar *)buffer,count);
  }

  *puVar2 = *puVar2 & 0xffffff4f | 0x80;
  return;
}

//------------------------------------------------------------------------------------------------

//Wait for flash to become ready
void spi_flash_wait_while_busy(void)

{
  int in_r0;
  int iVar1;
  uint *puVar2;
  byte local_1c;
  
  puVar2 = (uint *)(SPI0_BASE + in_r0 * 0x1000 + 8);

  do
  {
    *puVar2 = *puVar2 & 0xffffff4f;
    iVar1 = spi0_start_transfer();
    if (iVar1 == 1) {
      spi0_start_transfer();
    }
    *puVar2 = *puVar2 & 0xffffff4f | 0x80;
  } while ((local_1c & 1) != 0);
  return;
}

//------------------------------------------------------------------------------------------------

//address = 0x001FD000
//count   = 0x01F4

void write_to_flash(uint address,uchar *buffer,uint count)

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
  uchar *puVar9;
  uint uVar10;
  uchar *puVar11;
  uint *puVar12;
  uint uVar13;
  int iVar14;
  uchar local_48;
  undefined local_47;
  undefined local_46;
  undefined local_45;
  uint local_44;
  uint *local_40;
  uchar *local_3c;
  uint local_34;
  uchar *local_30;
  uint local_2c;
  uint local_28;
  
  local_28 = count;
  local_2c = address;
  local_30 = buffer;
  local_34 = 0;
  local_44 = address >> 0xc;

  uVar10 = address & 0xfff;            //Low part of the address (block of 4096 bytes) == sector within a flash. To see if starts is within a sector??
  uVar13 = 0x1000 - uVar10;            //Number of bytes to the end of the sector

  if (count <= 0x1000 - uVar10)        //Number of bytes to do less then the sector remainder, use the actual count
  {
    uVar13 = count;
  }

  local_40 = (uint *)(SPI0_BASE + 8);

  do
  {
    uVar4 = local_34;
    puVar12 = local_40;
    local_3c = DAT_80036614;
    iVar14 = local_44 << 0xc;
    local_48 = '\x03';
    uVar1 = (undefined)((local_44 << 0x14) >> 0x18);  //((address >> 12) << 20) >> 24    0x001FD000 >> 12 = 1FD    0x1F
    uVar2 = (undefined)((local_44 << 0x1c) >> 0x18);  //((address >> 12) << 28) >> 24                              0xD0
    local_45 = 0;

    *local_40 = *local_40 & 0xffffff4f;                  //Assert chip select

    local_47 = uVar1;
    local_46 = uVar2;

    uVar5 = spi_start_transfer(local_34,&local_48,(uchar *)0x0,4);   //Send read command for reading the sector

    puVar6 = extraout_r1;

    if (uVar5 == 4)
    {
      spi_start_transfer(uVar4,(uchar *)0x0,local_3c,0x1000);   //Read the bytes to a buffer
      puVar6 = extraout_r1_00;
    }

    uVar4 = local_34;
    iVar3 = SPI0_BASE;

    *puVar12 = *puVar12 & 0xffffff4f | 0x80;             //Deassert chip select

    if (uVar13 != 0)   //count
    {
      puVar6 = DAT_80036614;    //0x80856C80    some buffer????
    }

    uVar5 = 0;

    if (uVar13 != 0)
    {
      do
      {
        //Start on address in flash destined to write to
        if (puVar6[uVar10 + uVar5] != -1)   //Look for not 0xFF to see if there is actual data in the sector
          break;

        uVar5 = uVar5 + 1 & 0xfffeffff;
      } while (uVar5 < uVar13);
    }

    //Previous data in the sector so need to erase????
    if (uVar5 < uVar13)
    {
      local_48 = ' ';
      local_45 = 0;
      local_47 = uVar1;
      local_46 = uVar2;

      spi_flash_write_enable(local_34);   //Send write enable command to the flash

      spi_flash_wait_while_busy();


      puVar12 = local_40;

      *local_40 = *local_40 & 0xffffff4f;   //Assert

      spi_start_transfer(uVar4,&local_48,(uchar *)0x0,4); //erase sector. needs 24 bit address with lowest 12 bits cleared

      *puVar12 = *puVar12 & 0xffffff4f | 0x80;  //Deassert

      spi_flash_wait_while_busy();

      uVar4 = local_34;

      if (uVar13 != 0)        //Prepare sector for being written back to the flash!!!
      {
        puVar11 = DAT_80036614 + uVar10;  //Index into sector based on write to flash input address
        puVar6 = puVar11 + -1;
        puVar9 = local_30 + -1;

        if ((uVar13 & 1) != 0)    //Use memcpy!!!!!
        {
          *puVar11 = *local_30;
          puVar6 = puVar11;
          puVar9 = local_30;
        }

        uVar10 = uVar13 >> 1;

        while (uVar10 != 0)     
        {
          uVar10 = uVar10 - 1;
          puVar6[1] = puVar9[1];
          puVar9 = puVar9 + 2;
          puVar6 = puVar6 + 2;
          *puVar6 = *puVar9;
        }
      }

      puVar12 = (uint *)(iVar3 + local_34 * 0x1000 + 8);
      uVar10 = 0x1000;
      uVar5 = 0x100;
      puVar6 = DAT_80036614;

      while( true )
      {
        local_48 = '\x02';
        local_47 = (undefined)((uint)iVar14 >> 0x10);
        local_46 = (undefined)((uint)iVar14 >> 8);
        local_45 = 0;

        spi_flash_write_enable(uVar4);

        spi_flash_wait_while_busy();

        *puVar12 = *puVar12 & 0xffffff4f;

        uVar7 = spi_start_transfer(uVar4,&local_48,(uchar *)0x0,4);  //program a page!!!!

        if (uVar7 == 4)
        {
          spi_start_transfer(uVar4,puVar6,(uchar *)0x0,uVar5);  //Write the actual data
        }

        *puVar12 = *puVar12 & 0xffffff4f | 0x80;

        spi_flash_wait_while_busy();

        if (uVar10 == uVar5)
         break;

        uVar10 = uVar10 - uVar5 & 0xffff;
        puVar6 = puVar6 + uVar5;
        iVar14 = iVar14 + uVar5;
        uVar5 = uVar10;

        if (0x100 < uVar10)
        {
          uVar5 = 0x100;
        }
      }
    }
    else   //No previous data in the sector so do write as is???
    {
      uVar10 = 0x100 - (local_2c & 0xff);

      if (uVar13 <= uVar10)
      {SPI_TCR_SS_LEVEL_HIGH
        uVar10 = uVar13;
      }

      puVar12 = (uint *)(iVar3 + local_34 * 0x1000 + 8);
      uVar7 = local_2c;
      uVar5 = uVar13;
      puVar6 = local_30;

      while( true )
      {
        local_48 = '\x02';
        local_47 = (undefined)(uVar7 >> 0x10);
        local_46 = (undefined)(uVar7 >> 8);
        local_45 = (undefined)uVar7;

        spi_flash_write_enable(uVar4);

        spi_flash_wait_while_busy();

        *puVar12 = *puVar12 & 0xffffff4f;

        uVar8 = spi_start_transfer(uVar4,&local_48,(uchar *)0x0,4);    //page program

        if (uVar8 == 4)
        {
          spi_start_transfer(uVar4,puVar6,(uchar *)0x0,uVar10);      //write actual data
        }

        *puVar12 = *puVar12 & 0xffffff4f | 0x80;

        spi_flash_wait_while_busy();

        if (uVar5 == uVar10)
          break;

        uVar5 = uVar5 - uVar10 & 0xffff;
        puVar6 = puVar6 + uVar10;
        uVar7 = uVar7 + uVar10;
        uVar10 = uVar5;

        if (0x100 < uVar5)
        {
          uVar10 = 0x100;
        }
      }
    }

    if (local_28 == uVar13)
    {
      return;
    }

    uVar10 = 0;
    local_44 = local_44 + 1;
    local_28 = local_28 - uVar13 & 0xffff;
    local_30 = local_30 + uVar13;
    local_2c = local_2c + uVar13;
    uVar13 = local_28;

    if (0x1000 < local_28)
    {
      uVar13 = 0x1000;
    }

  } while( true );
}


//------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------


uint spi0_start_transfer(uint interface,uchar *txbuf,uchar *rxbuf,uint count)

{
  uint uVar1;
  undefined *puVar2;
  uchar *puVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  
  iVar6 = SPI0_BASE + interface * 0x1000;

  if (0 < (int)count)
  {
    uVar5 = count;

    do
    {
      uVar1 = uVar5;

      if (0x40 < (int)uVar5)  //Blocks of 64 bytes
      {
        uVar1 = 0x40;
      }

      *(uint *)(iVar6 + 0x30) = uVar1;   //SPI0_MBC

      uVar7 = uVar1;

      if (buffer == (uchar *)0x0)      //No buffer for transmitting
      {
        uVar7 = 0;
      }

      *(uint *)(iVar6 + 0x34) = uVar7 & 0xffffff;    //SPI0_MTC
      *(uint *)(iVar6 + 0x38) = uVar7 & 0xffffff;    //SPI0_BCC

      iVar4 = 0;

      if (0 < (int)uVar7)     //Bytes to do
      {
        puVar3 = buffer;

        do
        {
          *(uchar *)(iVar6 + 0x200) = *puVar3;    //SPI0_TXD_BYTE
          iVar4 = iVar4 + 1;                      //one byte done
          puVar3 = puVar3 + 1;                    //point to next byte
        } while (iVar4 < (int)uVar7);             //Do until last
      }

      *(uint *)(iVar6 + 8) = *(uint *)(iVar6 + 8) | 0x80000000;  //Start transmission

      do
      {
      } while ((*(uint *)(iVar6 + 0x1c) & 0xff) < uVar1);  //SPI0_FSR   wait until data is send

      iVar4 = 0;
      puVar2 = (undefined *)address;

      if (0 < (int)uVar1)
      {
        do
        {
          iVar4 = iVar4 + 1;
          address = (uint)puVar2;

          if (puVar2 != (undefined *)0x0)
          {
            address = (uint)(puVar2 + 1);
            *puVar2 = *(undefined *)(iVar6 + 0x300);   //SPI0_RXD_BYTE  receive byte
          }

          puVar2 = (undefined *)address;

        } while (iVar4 < (int)uVar1);
      }

      if (buffer != (uchar *)0x0)
      {
        buffer = buffer + uVar1;
      }

      uVar5 = uVar5 - uVar1;

    } while (0 < (int)uVar5);
  }

  return count;
}



//------------------------------------------------------------------------------------------------

//r0 == 0
//r1 == buffer
//r2 == address
//r3 == count
//

void flash_write(uint r0,uint r1,uint r2,uint r3)

{
  int iVar1;
  ushort uVar2;
  uint *puVar3;
  uint uVar4;
  undefined *puVar5;
  int iVar6;
  int extraout_r1;
  undefined *puVar7;
  uint uVar8;
  undefined *puVar9;
  uint *puVar10;
  uint uVar11;
  ushort uVar12;
  undefined8 uVar13;
  undefined *local_30;
  uint local_2c;
  uint local_28;
  
  uVar8 = r2 & 0xfff;                 
  uVar11 = 0x1000 - uVar8;
  if (r3 <= 0x1000 - uVar8) {
    uVar11 = r3;
  }
  puVar3 = (uint *)(SPI0_BASE + r0 * 0x1000 + 8);
  local_30 = (undefined *)r1;
  local_2c = r2;
  local_28 = r3;
  do {
    *puVar3 = *puVar3 & 0xffffff4f;
    uVar13 = spi0_start_transfer();
    iVar6 = (int)((ulonglong)uVar13 >> 0x20);
    if ((int)uVar13 == 4) {
      spi0_start_transfer();
      iVar6 = extraout_r1;
    }
    iVar1 = SPI0_BASE;
    *puVar3 = *puVar3 & 0xffffff4f | 0x80;
    if (uVar11 != 0) {
      iVar6 = DAT_80036614;
    }
    uVar4 = 0;
    if (uVar11 != 0) {
      do {
        if (*(char *)(iVar6 + uVar8 + uVar4) != -1) break;
        uVar4 = uVar4 + 1 & 0xfffeffff;
      } while (uVar4 < uVar11);
    }
    if (uVar4 < uVar11) {
      FUN_8002509c(r0);
      spi_flash_wait_while_busy();
      *puVar3 = *puVar3 & 0xffffff4f;
      spi0_start_transfer();
      *puVar3 = *puVar3 & 0xffffff4f | 0x80;
      spi_flash_wait_while_busy();
      if (uVar11 != 0) {
        puVar9 = (undefined *)(DAT_80036614 + uVar8);
        puVar5 = puVar9 + -1;
        puVar7 = local_30 + -1;
        if ((uVar11 & 1) != 0) {
          *puVar9 = *local_30;
          puVar5 = puVar9;
          puVar7 = local_30;
        }
        uVar8 = uVar11 >> 1;
        while (uVar8 != 0) {
          uVar8 = uVar8 - 1;
          puVar5[1] = puVar7[1];
          puVar7 = puVar7 + 2;
          puVar5 = puVar5 + 2;
          *puVar5 = *puVar7;
        }
      }
      puVar10 = (uint *)(iVar1 + r0 * 0x1000 + 8);
      uVar2 = 0x1000;
      uVar12 = 0x100;
      while( true ) {
        FUN_8002509c(r0);
        spi_flash_wait_while_busy();
        *puVar10 = *puVar10 & 0xffffff4f;
        iVar6 = spi0_start_transfer();
        if (iVar6 == 4) {
          spi0_start_transfer();
        }
        *puVar10 = *puVar10 & 0xffffff4f | 0x80;
        spi_flash_wait_while_busy();
        if (uVar2 == uVar12) break;
        uVar2 = uVar2 - uVar12;
        uVar12 = uVar2;
        if (0x100 < uVar2) {
          uVar12 = 0x100;
        }
      }
    }
    else {
      uVar8 = 0x100 - (local_2c & 0xff);
      if (uVar11 <= uVar8) {
        uVar8 = uVar11;
      }
      puVar10 = (uint *)(iVar1 + r0 * 0x1000 + 8);
      uVar4 = uVar11;
      while( true ) {
        FUN_8002509c(r0);
        spi_flash_wait_while_busy();
        *puVar10 = *puVar10 & 0xffffff4f;
        iVar6 = spi0_start_transfer();
        if (iVar6 == 4) {
          spi0_start_transfer();
        }
        *puVar10 = *puVar10 & 0xffffff4f | 0x80;
        spi_flash_wait_while_busy();
        if (uVar4 == uVar8) break;
        uVar4 = uVar4 - uVar8 & 0xffff;
        uVar8 = uVar4;
        if (0x100 < uVar4) {
          uVar8 = 0x100;
        }
      }
    }
    if (local_28 == uVar11) {
      return;
    }
    uVar8 = 0;
    local_28 = local_28 - uVar11 & 0xffff;
    local_30 = local_30 + uVar11;
    local_2c = local_2c + uVar11;
    uVar11 = local_28;
    if (0x1000 < local_28) {
      uVar11 = 0x1000;
    }
  } while( true );
}


//------------------------------------------------------------------------------------------------



void setup_spi(uint spi)
{
  undefined4 *port;
  undefined4 *port_00;
  uint uVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  
  port_00 = PORT_E_CFG0;

  port = PORT_C_CFG0;

  if (spi == 0)
  {
    gpio_config_pin(PORT_C_CFG0,0,2);
    gpio_config_pin(port,1,2);
    gpio_config_pin(port,2,2);
    gpio_config_pin(port,3,2);
  }
  else
  {
    if (spi == 1)
    {
      gpio_config_pin(PORT_E_CFG0,7,4);
      gpio_config_pin(port_00,8,4);
      gpio_config_pin(port_00,9,4);
      gpio_config_pin(port_00,10,4);
    }
  }

  puVar3 = BUS_SOFT_RST_REG0;
  uVar4 = *BUS_SOFT_RST_REG0;

  uVar1 = FUN_8000056c(1,0,spi + 0x14);

  *puVar3 = uVar4 | uVar1;

  puVar3 = puVar3 + -0x98;

  *puVar3 = uVar1 | *puVar3;

  iVar2 = SPI0_BASE + spi * 0x1000;

  *(undefined4 *)(iVar2 + 0x24) = DAT_80036248;

  puVar3 = (uint *)(iVar2 + 4);

  *puVar3 = *puVar3 | 0x80000083;

  do
  {
  } while ((*puVar3 & 0x80000000) != 0);

  *(uint *)(iVar2 + 8) = *(uint *)(iVar2 + 8) & 0xfffffffc | 0x44;
  *(uint *)(iVar2 + 0x18) = *(uint *)(iVar2 + 0x18) | 0x80008000;
  return;
}



