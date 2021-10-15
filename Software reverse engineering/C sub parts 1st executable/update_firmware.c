
void update_firmware(void)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  uint *puVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  char *pcVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  bool bVar20;
  bool bVar21;
  undefined auStack680 [552];
  uint local_80 [6];
  undefined auStack104 [32];
  uint local_48;
  uint local_44;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  
  //Check if one of the firmware files (different vendors) is present on the SD card
  iVar7 = f_open(auStack680,s_UTX-1013.bin_80000ef4,1);
  if (iVar7 == 0) {
    iVar7 = 1;
    pcVar10 = s_UTX-1013.bin_80000ef4;
  }
  else {
    f_close(auStack680);
    iVar7 = f_open(auStack680,s_FSI-1013.bin_80000f04,1);
    if (iVar7 == 0) {
      iVar7 = 2;
      pcVar10 = s_FSI-1013.bin_80000f04;
    }
    else {
      f_close(auStack680);
      iVar7 = f_open(auStack680,s_DAN-1013.bin_80000f14,1);
      if (iVar7 == 0) {
        iVar7 = 3;
        pcVar10 = s_DAN-1013.bin_80000f14;
      }
      else {
        f_close(auStack680);
        iVar7 = f_open(auStack680,s_YPK-1013.bin_80000f24,1);
        if (iVar7 != 0) {
          f_close(auStack680);
          return;
        }
        iVar7 = 4;
        pcVar10 = s_YPK-1013.bin_80000f24;
      }
    }
  }

  f_stat(pcVar10,local_80);   //File size is returned in the fno object
  
  uVar9 = DAT_80000f34;  //0xFFFF

  //Might be a fill_rect function
  //202, 208, 397, 64, 0xFFFF
  FUN_80001a34(0xca,0xd0,DAT_80000f38,0x40,DAT_80000f34);  //0xCA, 0xD0, 0x018D, 0x40, 0xFFFF

  //204, 210, 393, 62, 0x0000
  FUN_80001a34(0xcc,0xd2,DAT_80000f3c,0x3c,0);             //0xCC, 0xD2, 0x0189, 0x3C, 0x0000

  //Get the data into memory without checking if it even fits
  f_read(auStack680,DAT_80000f40,local_80[0],NULL);
  f_close(auStack680);

  puVar6 = DAT_80000f40;                     //point to the start of the buffer

  iVar8 = (int)DAT_80000f40 + local_80[0];   //Point to the end of the buffer

  //Guess these are check dwords for some CRC type checking
  //Get a bunch of dwords from the end of the file (9 in total)
  local_2c = (uint)*(byte *)(iVar8 + -0x21) | (uint)*(byte *)(iVar8 + -0x23) << 0x10 | (uint)*(byte *)(iVar8 + -0x24) << 0x18 | (uint)*(byte *)(iVar8 + -0x22) << 8;
  local_30 = (uint)*(byte *)(iVar8 + -0x1d) | (uint)*(byte *)(iVar8 + -0x1f) << 0x10 | (uint)*(byte *)(iVar8 + -0x20) << 0x18 | (uint)*(byte *)(iVar8 + -0x1e) << 8;
  local_34 = (uint)*(byte *)(iVar8 + -0x19) | (uint)*(byte *)(iVar8 + -0x1b) << 0x10 | (uint)*(byte *)(iVar8 + -0x1c) << 0x18 | (uint)*(byte *)(iVar8 + -0x1a) << 8;
  local_38 = (uint)*(byte *)(iVar8 + -0x15) | (uint)*(byte *)(iVar8 + -0x17) << 0x10 | (uint)*(byte *)(iVar8 + -0x18) << 0x18 | (uint)*(byte *)(iVar8 + -0x16) << 8;
  local_3c = (uint)*(byte *)(iVar8 + -0x11) | (uint)*(byte *)(iVar8 + -0x13) << 0x10 | (uint)*(byte *)(iVar8 + -0x14) << 0x18 | (uint)*(byte *)(iVar8 + -0x12) << 8;
  local_40 = (uint)*(byte *)(iVar8 + -0xd) | (uint)*(byte *)(iVar8 + -0xf) << 0x10 | (uint)*(byte *)(iVar8 + -0x10) << 0x18 | (uint)*(byte *)(iVar8 + -0xe) << 8;

  bVar1 = *(byte *)(iVar8 + -3);
  bVar2 = *(byte *)(iVar8 + -4);
  local_44 = (uint)*(byte *)(iVar8 + -0xb) << 0x10 | (uint)*(byte *)(iVar8 + -0xc) << 0x18 | (uint)*(byte *)(iVar8 + -10) << 8 | (uint)*(byte *)(iVar8 + -9);
  bVar3 = *(byte *)(iVar8 + -2);
  bVar4 = *(byte *)(iVar8 + -1);
  local_48 = (uint)*(byte *)(iVar8 + -5) | (uint)*(byte *)(iVar8 + -6) << 8 | (uint)*(byte *)(iVar8 + -7) << 0x10 | (uint)*(byte *)(iVar8 + -8) << 0x18;




  memcpy(auStack104,DAT_80000f40 + 0x5000,0xc);   //copy 12 bytes?? from buffer + 0x5000, what is at that location???
  memclear((uint)(puVar6 + 0x5000),0xc);          //clear the source

  uVar14 = 0;

  do
  {
    write_to_flash(uVar14 * 0xffff + 0x13000,(uchar *)((int)puVar6 + uVar14 * 0xffff),uVar9);   //Write the bitmap image in 65535 sized blocks, plus the program code???  (0x1DFFE2 = 1966050 bytes)

    //207 + (i * 13), 213, 10, 54, 0xFFFF
    FUN_80001a34(uVar14 * 0xd + 0xcf & 0xffff,0xd5,10,0x36,uVar9);  //What does this function do????? Progress bar??????

    uVar14 = uVar14 + 1;
  } while (uVar14 < 0x1e);



  memcpy(DAT_80000f40,auStack104,0xc);   //Copy to the first 12 bytes of the data and  write these over the first 12 bytes of the main program

  write_to_flash_no_erase(0,DAT_80000f40,0x27000,0xc);


  //Check dwords need to be calculated over the data that will end up in the flash, so the 12 bytes at 0x5000 need to be set after calculation.

  //File data is extended with the 0x24 bytes for the check dwords, but the calculations need to be done on again 0x24 bytes less???


  //Read the bitmap from flash minus 36 bytes??
  read_from_flash(0x13000,DAT_80000f40,local_80[0] - 0x24);

  uVar14 = 0;
  uVar18 = 0;
  uVar17 = 0;
  uVar16 = 0;
  uVar15 = 0;
  uVar13 = 0;
  uVar12 = 0;
  uVar19 = 0;
  uVar11 = 0;
  uVar9 = 0;

  //File size needs to be at least 72
  if (local_80[0] != 0x48)
  {
    do
    {
      bVar5 = *(byte *)((int)DAT_80000f40 + uVar9); //Get a byte from the buffer

      if ((bVar5 & 0x80) != 0)    //Count the bits that are one but with a location in the data coupling
      {
        uVar18 = uVar18 + uVar9;
      }

      if ((bVar5 & 0x40) != 0)
      {
        uVar17 = uVar17 + uVar9;
      }

      if ((bVar5 & 0x20) != 0)
      {
        uVar16 = uVar16 + uVar9;
      }

      if ((bVar5 & 0x10) != 0)
      {
        uVar15 = uVar15 + uVar9;
      }

      if ((bVar5 & 8) != 0)
      {
        uVar13 = uVar13 + uVar9;
      }

      if ((bVar5 & 4) != 0)
      {
        uVar12 = uVar12 + uVar9;
      }

      if ((bVar5 & 2) != 0)
      {
        uVar19 = uVar19 + uVar9;
      }

      if ((bVar5 & 1) != 0)
      {
        uVar11 = uVar11 + uVar9;
      }

      uVar9 = uVar9 + 1;
      uVar14 = uVar14 + bVar5;   //Calculate a sum of all the bytes
    } while (uVar9 < local_80[0] - 0x48);
  }

  uVar9 = local_2c;

  if (uVar14 == local_2c)  //Check if the checksum is the same (sum of all the bytes)
  {
    uVar9 = local_30;
  }

  if (uVar14 == local_2c && uVar18 == uVar9)  //Check if the bit 7 count checks out
  {
    uVar9 = local_34;

    if (uVar17 == local_34)  //bit 6 count
    {
      uVar9 = local_38;
    }

    if (uVar17 == local_34 && uVar16 == uVar9)   //bit 5
    {
      uVar9 = local_3c;

      if (uVar15 == local_3c)                    //bit 4
      {
        uVar9 = local_40;
      }

      if (uVar15 == local_3c && uVar13 == uVar9)   //bit 3
      {
        bVar20 = uVar12 == local_44;           //bit 2
        uVar9 = local_44;

        if (bVar20)
        {
          uVar9 = local_48;
        }

        bVar21 = bVar20 && uVar19 == uVar9;    //bit 1

        if (bVar20 && uVar19 == uVar9)
        {
          bVar21 = uVar11 == ((uint)bVar4 | (uint)bVar1 << 0x10 | (uint)bVar2 << 0x18 | (uint)bVar3 << 8);   //bit 0
        }

        if (bVar21)    //All bit counts and the sum check out
        {
          if (iVar7 == 1)  //select the file to delete
         {
            pcVar10 = s_UTX-1013.bin_80000ef4;
          }
          else 
          {
            if (iVar7 == 2)
            {
              pcVar10 = s_FSI-1013.bin_80000f04;
            }
            else
            {
              if (iVar7 == 3)
              {
                pcVar10 = s_DAN-1013.bin_80000f14;
              }
              else
              {
                if (iVar7 != 4)
                  goto LAB_80001008;

                pcVar10 = s_YPK-1013.bin_80000f24;
              }
            }
          }

          f_unlink(pcVar10);  //Delete the file if update succeeded

          goto LAB_80001008;
        }
      }
    }
  }

  write_to_flash(0x27000,(uchar *)DAT_80000f40,1000);  //on error make sure the main program is corrupted.

LAB_80001008:
  sys_init_watchdog();   //Force a system reset
  return;
}


