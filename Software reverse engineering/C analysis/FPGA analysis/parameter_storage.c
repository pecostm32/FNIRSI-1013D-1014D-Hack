//-------------------------------------------------------------------------------------------------------------------------------

void init_parameter_storage(void)
{
  uchar *puVar1;
  byte bVar2;
  uchar uVar3;
  
                               //0x8035EC04  Buffer in ram where the data for the parameter storage communication resides
  puVar1 = DAT_80024ed8;       //0x8035EC04

  fpga_write_cmd('d');

  fpga_write_cmd('d');

  delay(0x14);

  fpga_write_cmd('f');

  do
  {
    fpga_write_cmd('g');

    bVar2 = fpga_read_data();

  } while ((bVar2 & 1) == 0);

  fpga_write_cmd('h');

  uVar3 = fpga_read_data();

  *puVar1 = uVar3;

  fpga_write_cmd('i');

  uVar3 = fpga_read_data();

  puVar1[1] = uVar3;

  fpga_write_cmd('j');

  uVar3 = fpga_read_data();

  puVar1[2] = uVar3;

  fpga_write_cmd('k');

  uVar3 = fpga_read_data();

  puVar1[3] = uVar3;

  fpga_write_cmd('l');

  uVar3 = fpga_read_data();

  puVar1[4] = uVar3;

  fpga_write_cmd('m');

  uVar3 = fpga_read_data();

  puVar1[5] = uVar3;

  fpga_write_cmd('n');

  uVar3 = fpga_read_data();

  puVar1[6] = uVar3;

  *PTR_DAT_80024edc = DAT_80024ed8[3];  //Set byte for next action    //0x80192eea

  return;
}

//-------------------------------------------------------------------------------------------------------------------------------
//Write to parameter storage
void write_parameter_storage(uint id,uint value)

{
  uchar uVar1;
  uchar uVar2;
  uchar uVar3;
  uchar *puVar4;
  byte bVar5;
  
  puVar4 = DAT_80025094;                //0x8035EC04

  *DAT_80025094 = *PTR_DAT_80025098;    //load the first byte with the crypt byte

  puVar4[1] = (uchar)(id << 2);         //Fill in the parameter id

  uVar3 = (uchar)value;
  bVar5 = 0;

  uVar1 = (uchar)((value << 8) >> 0x18);

  uVar2 = (uchar)((value << 0x10) >> 0x18);

  if (value < 0x1000000)
  {
    if (value < 0x10000)
    {
      if (value < 0x100)
      {
        puVar4[3] = 'i';
        puVar4[4] = -0x6a;
        puVar4[5] = -0x67;
        puVar4[6] = uVar3;
      }
      else
      {
        puVar4[3] = 'i';
        bVar5 = 1;
        puVar4[4] = -0x6a;
        puVar4[5] = uVar2;
        puVar4[6] = uVar3;
      }
    }
    else
    {
      bVar5 = 2;
      puVar4[3] = 'i';
      puVar4[4] = uVar1;
      puVar4[5] = uVar2;
      puVar4[6] = uVar3;
    }
  }
  else
  {
    bVar5 = 3;
    puVar4[3] = (uchar)(value >> 0x18);
    puVar4[4] = uVar1;
    puVar4[5] = uVar2;
    puVar4[6] = uVar3;
  }

  puVar4[1] = bVar5 | puVar4[1];

  do_xor();

  puVar4[2] = puVar4[6] + puVar4[3] + puVar4[4] + puVar4[1] + *puVar4 + puVar4[5];

  fpga_write_cmd('e');       //0x65
  fpga_write_cmd('e');       //0x65   Init write

  uVar1 = *puVar4;
  fpga_write_cmd('h');       //0x68   crypt byte      [0]
  fpga_write_data(uVar1);

  uVar1 = puVar4[1];
  fpga_write_cmd('i');       //0x69   Id + count      [1]
  fpga_write_data(uVar1);

  uVar1 = puVar4[2];
  fpga_write_cmd('j');       //0x6A   checksum        [2]
  fpga_write_data(uVar1);

  uVar1 = puVar4[3];
  fpga_write_cmd('k');       //0x6B   msb             [3]
  fpga_write_data(uVar1);

  uVar1 = puVar4[4];
  fpga_write_cmd('l');       //0x6C   mlsb
  fpga_write_data(uVar1);

  uVar1 = puVar4[5];
  fpga_write_cmd('m');       //0x6D   lmsb
  fpga_write_data(uVar1);

  uVar1 = puVar4[6];
  fpga_write_cmd('n');       //0x6E   lsb
  fpga_write_data(uVar1);

  fpga_write_cmd('f');       //0x66    start transmission

  do
  {
    fpga_write_cmd('g');     //0x67    check status

    bVar5 = fpga_read_data();

  } while ((bVar5 & 1) == 0);

  return;
}

//-------------------------------------------------------------------------------------------------------------------------------

uint get_setting(uint setting,uint cur_val)

{
  bool bVar1;
  undefined *puVar2;
  uchar *puVar3;
  uchar *puVar4;
  byte bVar5;
  uchar uVar6;
  byte bVar7;
  byte bVar8;
  uint uVar9;
  
  puVar3 = DAT_80024b10;
  puVar2 = PTR_DAT_80024b0c;
  bVar8 = 0;
  do
  {
    write_parameter_storage(setting, cur_val);

    delay(500);
    bVar7 = 0;

    do
    {
      delay(100);
      puVar4 = DAT_80024b10;

      fpga_write_cmd('d');   //0x64
      fpga_write_cmd('d');

      delay(0x14);

      fpga_write_cmd('f');  //0x66

      do
      {
        fpga_write_cmd('g');  //0x67
        bVar5 = fpga_read_data();
      } while ((bVar5 & 1) == 0);

      fpga_write_cmd('h');
      uVar6 = fpga_read_data();
      *puVar4 = uVar6;

      fpga_write_cmd('i');
      uVar6 = fpga_read_data();
      puVar4[1] = uVar6;

      fpga_write_cmd('j');
      uVar6 = fpga_read_data();
      puVar4[2] = uVar6;

      fpga_write_cmd('k');
      uVar6 = fpga_read_data();
      puVar4[3] = uVar6;

      fpga_write_cmd('l');
      uVar6 = fpga_read_data();
      puVar4[4] = uVar6;

      fpga_write_cmd('m');
      uVar6 = fpga_read_data();
      puVar4[5] = uVar6;

      fpga_write_cmd('n');
      uVar6 = fpga_read_data();
      puVar4[6] = uVar6;

      FUN_80024b14();

      *puVar2 = *puVar3;         //Save the crypt byte

      if (puVar3[1] == 'U')      //0x55
      {
        uVar9 = (uint)puVar3[6];
      }
      else
      {
        if (puVar3[1] == 'Z')    //0x5A
        {
          uVar9 = (uint)CONCAT11(puVar3[5],puVar3[6]);
        }
        else
        {
          if (puVar3[1] == -0x5b)   //0xA5
          {
            uVar9 = (uint)CONCAT21(CONCAT11(puVar3[4],puVar3[5]),puVar3[6]);
          }
          else
          {
            if (puVar3[1] == -0x56)  //0xAA
            {
              uVar9 = CONCAT31(CONCAT21(CONCAT11(puVar3[3],puVar3[4]),puVar3[5]),puVar3[6]);
            }
            else
            {
              uVar9 = 0;
            }
          }
        }
      }

      uVar6 = puVar3[1];

      bVar1 = true;

      if ((uVar6 != 'U' && uVar6 != 'Z') && (uVar6 != -0x5b && uVar6 != -0x56))
      {
        bVar1 = false;
      }

      if (((uchar)(*puVar3 + puVar3[1] + puVar3[3] + puVar3[4] + puVar3[5] + puVar3[6]) == puVar3[2]) && (bVar1))
      {
        return uVar9;
      }

      bVar7 = bVar7 + 1;

    } while (bVar7 < 0x32);

    delay(10);

    bVar8 = bVar8 + 1;

    if (5 < bVar8)
    {
      return uVar9;
    }
  } while( true );
}

//-------------------------------------------------------------------------------------------------------------------------------

void FUN_80024b14(void)

{
  byte *pbVar1;
  uint uVar2;
  byte bVar3;
  
  pbVar1 = DAT_80024c78;              //Pointer to data buffer

  uVar2 = 1;

  bVar3 = ~*DAT_80024c78;             //Get crypt byte and invert it

  *DAT_80024c78 = ~*DAT_80024c78;     //Write it back to the buffer

  do  //Use the inverted byte for the xor and process all the received bytes
  {
    if ((bVar3 & 0x80) != 0)
    {
      pbVar1[uVar2] = ~pbVar1[uVar2] & 0x80 | pbVar1[uVar2] & 0x7f;
    }

    if ((bVar3 & 0x40) != 0)
    {
      pbVar1[uVar2] = ~pbVar1[uVar2] & 0x40 | pbVar1[uVar2] & 0xbf;
    }

    if ((bVar3 & 0x20) != 0)
    {
      pbVar1[uVar2] = ~pbVar1[uVar2] & 0x20 | pbVar1[uVar2] & 0xdf;
    }

    if ((bVar3 & 0x10) != 0)
    {
      pbVar1[uVar2] = ~pbVar1[uVar2] & 0x10 | pbVar1[uVar2] & 0xef;
    }

    if ((bVar3 & 8) != 0)
    {
      pbVar1[uVar2] = ~pbVar1[uVar2] & 8 | pbVar1[uVar2] & 0xf7;
    }

    if ((bVar3 & 4) != 0)
    {
      pbVar1[uVar2] = ~pbVar1[uVar2] & 4 | pbVar1[uVar2] & 0xfb;
    }

    if ((bVar3 & 2) != 0)
    {
      pbVar1[uVar2] = ~pbVar1[uVar2] & 2 | pbVar1[uVar2] & 0xfd;
    }

    if ((bVar3 & 1) != 0)
    {
      pbVar1[uVar2] = ~pbVar1[uVar2] & 1 | pbVar1[uVar2] & 0xfe;
    }

    uVar2 = uVar2 + 1 & 0xff;
  } while (uVar2 < 7);
  return;
}

//-------------------------------------------------------------------------------------------------------------------------------
//Exor functie

void do_xor(void)

{
  byte bVar1;
  byte *pbVar2;
  byte bVar3;
  uint uVar4;
  
  pbVar2 = DAT_80024e14;                       //0x8035EC04  Buffer in ram where the data for the parameter storage communication resides
  bVar1 = *DAT_80024e14;
  uVar4 = 1;

  do
  {
    if ((bVar1 & 0x80) != 0)
    {
      pbVar2[uVar4] = ~pbVar2[uVar4] & 0x80 | pbVar2[uVar4] & 0x7f;
    }

    if ((bVar1 & 0x40) != 0)
    {
      pbVar2[uVar4] = ~pbVar2[uVar4] & 0x40 | pbVar2[uVar4] & 0xbf;
    }

    if ((bVar1 & 0x20) != 0)
    {
      pbVar2[uVar4] = ~pbVar2[uVar4] & 0x20 | pbVar2[uVar4] & 0xdf;
    }

    if ((bVar1 & 0x10) != 0)
    {
      pbVar2[uVar4] = ~pbVar2[uVar4] & 0x10 | pbVar2[uVar4] & 0xef;
    }

    if ((bVar1 & 8) != 0)
    {
      pbVar2[uVar4] = ~pbVar2[uVar4] & 8 | pbVar2[uVar4] & 0xf7;
    }

    if ((bVar1 & 4) != 0)
    {
      pbVar2[uVar4] = ~pbVar2[uVar4] & 4 | pbVar2[uVar4] & 0xfb;
    }

    if ((bVar1 & 2) != 0)
    {
      pbVar2[uVar4] = ~pbVar2[uVar4] & 2 | pbVar2[uVar4] & 0xfd;
    }

    if ((bVar1 & 1) != 0)
    {
      pbVar2[uVar4] = ~pbVar2[uVar4] & 1 | pbVar2[uVar4] & 0xfe;
    }

    uVar4 = uVar4 + 1 & 0xff;
  } while (uVar4 < 7);

  bVar3 = 0;                    //Mangle the crypt byte after a write session
  if ((bVar1 & 4) != 0)         //If bit 2 is set it sets bit 7 instead
  {
    bVar3 = 0x80;
  }

  if ((bVar1 & 0x10) != 0)      //If bit 4 is set it sets bit 6 instead
  {
    bVar3 = bVar3 | 0x40;
  }

  if ((bVar1 & 1) != 0)         //If bit 0 is set it sets bit 5 instead
  {
    bVar3 = bVar3 | 0x20;
  }

  if ((bVar1 & 0x40) != 0)      //If bit 6 is set it sets bit 4 instead
  {
    bVar3 = bVar3 | 0x10;
  }

  if ((bVar1 & 2) != 0)         //If bit 1 is set it sets bit 3 instead
  {
    bVar3 = bVar3 | 8;
  }

  if ((bVar1 & 0x80) != 0)      //If bit 7 is set it sets bit 2 instead
  {
    bVar3 = bVar3 | 4;
  }

  if ((bVar1 & 8) != 0)         //If bit 3 is set it sets bit 1 instead
  {
    bVar3 = bVar3 | 2;
  }

  if ((bVar1 & 0x20) != 0)      //If bit 5 is set it sets bit 0 instead
  {
    bVar3 = bVar3 | 1;
  }

  *pbVar2 = bVar3;

  return;
}

//-------------------------------------------------------------------------------------------------------------------------------

