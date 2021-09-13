



int sd_card_get_specifications(uint interface,sd_cmd *cmd,void *data)

{
  byte bVar1;
  byte bVar2;
  byte **ppbVar3;
  uint *puVar4;
  uint *puVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  uint extraout_r1;
  char cVar9;
  int iVar10;
  undefined4 unaff_r4;
  byte *dividend;
  int iVar11;
  undefined4 unaff_r5;
  undefined4 unaff_r6;
  byte *pbVar12;
  byte *unaff_r7;
  undefined4 unaff_r8;
  byte **ppbVar13;
  uint uVar14;
  bool bVar15;
  bool bVar16;
  byte abStack105 [41];
  uint uStack64;
  int iStack60;
  undefined4 uStack52;
  undefined4 uStack48;
  undefined4 uStack44;
  byte *pbStack40;
  undefined4 uStack36;
  char *pcVar17;
  undefined4 uStack4;
  
  puVar4 = DAT_8001c0c4;            //0x8019CF6C  = cardtype
  uVar14 = DAT_8001c0c4[1];         // = cardrca


  cmd->cmdidx = 9;                  //Get card specific data (CSD)
  cmd->resp_type = 7;
  cmd->cmdarg = uVar14;
  sd_card_send_command(interface,cmd,NULL);

  puVar5 = DAT_8001c0c8;                    //0x80736040
  uVar14 = cmd->response[3];                //bit 127 - 96
  *DAT_8001c0c8 = uVar14;
  uVar8 = cmd->response[2];                 //bit 95 - 64

  bVar15 = (uVar14 & 0xc0000000) == 0;  //if version is 0 bVar15 is true

  puVar5[1] = uVar8;
  uVar6 = cmd->response[1];                 //bit 63 - 32
  puVar5[2] = uVar6;
  uVar14 = cmd->response[0];                //bit 31 - 0
  puVar5[3] = uVar14;

  if (!bVar15)
  {
    uVar14 = *puVar4;
  }

  if (bVar15 || uVar14 == 3)
  {
    //(cardcsd[1] << 22) >> 20  == ((cardcsd[1] & 0x03FF) << 2) (bit 73 - 64)
    //(cardcsd[2] >> 30) bits 63 and 62

    //C_SIZE + 1

    ///(cardcsd[2] << 14) >> 29  (bits 49 - 47)

    uVar6 = (((uVar8 << 0x16) >> 0x14 | uVar6 >> 0x1e) + 1 << ((uVar6 << 0xe) >> 0x1d) + 2) << ((uVar8 << 0xc) >> 0x1c);
    uVar14 = uVar6 >> 9;  //div by 512
    *(uint *)((int)data + 4) = uVar14;
    *(uint *)((int)data + 8) = uVar6 >> 10;  //div by 1024
  }
  else
  {
    //C_SIZE bits 69:48  22 bits

    //6 bits from cardcsd[1] and 16 bits from cardcsd[2]
    iVar7 = ((uVar8 << 0x1a) >> 10 | uVar6 >> 0x10) * 0x200 + 0x200;
    uVar14 = iVar7 * 2;
    *(int *)((int)data + 8) = iVar7;
    *(uint *)((int)data + 4) = uVar14;
  }

  puVar4[3] = uVar14;   //cardblocks

  *(undefined4 *)((int)data + 0xc) = 0x200;


//Tot hier


  uVar14 = puVar4[1];   //cardrca
  uStack4 = 7;

  cmd->cmdidx = 10;           //Get card identification (CID)  Is a bit double??? CID already read with other command
  cmd->resp_type = 7;
  cmd->cmdarg = uVar14;
  sd_card_send_command(interface,cmd,NULL);

  puVar4 = DAT_8001c0c8;               //0x80736040  byte pointer

  uVar14 = cmd->response[3];
  *puVar5 = uVar14;                    //0x80736040
  puVar5[1] = cmd->response[2];        //0x80736044
  puVar5[2] = cmd->response[1];        //0x80736048
  puVar5[3] = cmd->response[0];        //0x8073604C


  *(char *)((int)data + 0x10) = (char)(uVar14 >> 0x18);   //top 8 bits

  //Product name
  *(undefined *)((int)data + 0x30) = *(undefined *)((int)puVar4 + 4);    //0x80736044  cardcid[1]
  *(undefined *)((int)data + 0x31) = *(undefined *)((int)puVar4 + 5);    //0x80736045
  *(undefined *)((int)data + 0x32) = *(undefined *)((int)puVar4 + 6);    //0x80736046
  *(undefined *)((int)data + 0x33) = *(undefined *)((int)puVar4 + 7);    //0x80736047
  *(undefined *)((int)data + 0x34) = *(undefined *)((int)puVar4 + 8);    //0x80736048

  //Product serial number????
  *(undefined *)((int)data + 0x50) = *(undefined *)((int)puVar4 + 0x13);  //0x80736053  What data is here????
  *(undefined *)((int)data + 0x51) = *(undefined *)((int)puVar4 + 0x14);
  *(undefined *)((int)data + 0x52) = *(undefined *)((int)puVar4 + 0x15);
  *(undefined *)((int)data + 0x53) = *(undefined *)((int)puVar4 + 0x16);


//So this bit is not of interrest 

  uart_printf(s_SD_info_print..._8001c0cc);
  uart_printf(s_SD_info->diskSize=[%d]_8001c0e0,*(undefined4 *)((int)data + 8));
  uart_printf(s_SD_info->totalSectorN=[%d]_8001c0fc,*(undefined4 *)((int)data + 4));


  //This is uart_printf
  pcVar17 = s_SD_info->sectorSize=[%d]_8001c11c;

  uStack36 = unaff_r8;
  pbStack40 = unaff_r7;
  uStack44 = unaff_r6;
  uStack48 = unaff_r5;
  uStack52 = unaff_r4;
  ppbVar3 = (byte **)&stack0xfffffff4;

  puVar4 = DAT_80037bb8;   //0x01C25000

  bVar1 = s_SD_info->sectorSize=[%d]_8001c11c[0];

joined_r0x80037718:

  if (bVar1 == 0)
  {
    DAT_80037bb8 = puVar4;
    return 0;
  }

  bVar1 = *pcVar17;
  DAT_80037bb8 = puVar4;

  if (bVar1 == 0x25)
  {
    uVar6 = (uint)((byte *)pcVar17)[1];
    uVar14 = 0;
    uVar8 = 0x20;
    ppbVar13 = ppbVar3 + 1;
    dividend = *ppbVar3;

    if (uVar6 == 0x30)
    {
      uVar8 = 0x30;
    }

    bVar15 = false;
    iVar7 = 0;
    pcVar17 = (char *)((byte *)pcVar17 + 2);

    if (uVar6 != 0)
    {
      do
      {
        if (9 < uVar6 - 0x30)
        {
          if (uVar6 == 100)
          {
LAB_80037a94:
            iVar7 = -10;
            break;
          }

          if (uVar6 < 0x65)
          {
            if (uVar6 == 0x2d)
            {
              bVar15 = true;
              goto LAB_800377b8;
            }

            if (uVar6 < 0x2e)
            {
              if (uVar6 == 0)
              {
                pcVar17 = (char *)((byte *)pcVar17 + -1);
                goto LAB_80037754;
              }

              if (uVar6 == 0x25)
              {
                uVar14 = 0x25;

                do
                {
                } while ((puVar4[0x1f] & 2) == 0);

LAB_800379c4:
                *DAT_80037bb8 = uVar14;
                goto LAB_80037754;
              }
            }
            else
            {
              if (uVar6 == 0x58)
              {
LAB_80037a9c:
                iVar7 = 0x10;
                break;
              }

              if (uVar6 == 99)
              {
                if (bVar15)
                {
                  do {
                  } while ((puVar4[0x1f] & 2) == 0);

                  *puVar4 = (uint)dividend & 0x7f;
                }

                puVar4 = DAT_80037bb8;

                if ((0 < (int)uVar14) && (iVar7 = uVar14 - 2, iVar7 != -1))
                {
                  do
                  {
                    do
                    {
                    } while ((puVar4[0x1f] & 2) == 0);

                    *puVar4 = uVar8;
                    bVar16 = iVar7 != 0;
                    iVar7 = iVar7 + -1;
                  } while (bVar16);
                }

                if (bVar15)
                  goto LAB_80037754;

                uVar14 = (uint)dividend & 0x7f;

                do
                {
                } while ((DAT_80037bb8[0x1f] & 2) == 0);

                goto LAB_800379c4;
              }
            }
          }
          else
          {
            if (uVar6 == 0x73)
            {
              if (bVar15)
              {
                bVar1 = *dividend;
                pbVar12 = dividend;

                while (bVar1 != 0)
                {
                  do {
                  } while ((puVar4[0x1f] & 2) == 0);

                  *puVar4 = (uint)bVar1;
                  pbVar12 = pbVar12 + 1;
                  bVar1 = *pbVar12;
                }
              }

              uVar6 = FUN_800005bc(dividend);

              if (uVar6 < uVar14)
              {
                iVar7 = FUN_800005bc(dividend);

                puVar4 = DAT_80037bb8;
                iVar7 = uVar14 - iVar7;

                while (iVar7 != 0)
                {
                  iVar7 = iVar7 + -1;

                  do {
                  } while ((puVar4[0x1f] & 2) == 0);

                  *puVar4 = uVar8;
                }
              }

              puVar4 = DAT_80037bb8;

              if (!bVar15)
              {
                bVar1 = *dividend;

                while (bVar1 != 0)
                {
                  do {
                  } while ((puVar4[0x1f] & 2) == 0);

                  *puVar4 = (uint)bVar1;
                  dividend = dividend + 1;
                  bVar1 = *dividend;
                }
              }

              goto LAB_80037754;
            }

            if (uVar6 < 0x74)
            {
              if (uVar6 == 0x69)
                goto LAB_80037a94;

              if (uVar6 != 0x6f)
                goto LAB_80037928;

              iVar7 = 8;
              break;
            }

            if (uVar6 == 0x75)
            {
              iVar7 = 10;
              break;
            }

            if (uVar6 == 0x78)
              goto LAB_80037a9c;
          }

LAB_80037928:
          iVar7 = 3;
          break;
        }

        uVar14 = (uVar6 + uVar14 * 10) - 0x30;
LAB_800377b8:
        pbVar12 = (byte *)pcVar17 + 1;
        uVar6 = (uint)(byte)*pcVar17;
        pcVar17 = (char *)pbVar12;
      } while (uVar6 != 0);

      if (bVar15)
      {
        uVar14 = -uVar14;
      }
    }

    if (uVar8 == 0)
    {
      uVar8 = 0x20;
    }

    bVar15 = (int)uVar14 < 0;
    uStack64 = 0;
    iStack60 = 0;

    if (bVar15)
    {
      uVar14 = -uVar14;
      uStack64 = 1;
    }

    uStack64 = (uint)bVar15;

    if (0x50 < uVar14)
    {
      uVar14 = 0;
    }

    bVar15 = iVar7 < 0;

    if (bVar15)
    {
      iVar7 = -iVar7;
    }

    iVar11 = 0;

    if (bVar15 && (int)dividend < 0)
    {
      dividend = (byte *)-(int)dividend;
      iStack60 = 1;
    }

LAB_80037820:
    do
    {
      iVar10 = iVar11;

      if (iVar7 == 0x10)
      {
        uVar6 = (uint)dividend & 0xf;
        dividend = (byte *)((uint)dividend >> 4);
      }
      else
      {
        dividend = (byte *)divide((int)dividend,iVar7);
        uVar6 = extraout_r1 & 0xffff;
      }

      puVar4 = DAT_80037bb8;

      if (uVar6 < 10)
      {
        cVar9 = '0';
      }
      else
      {
        cVar9 = '7';
      }

      abStack105[iVar10 + 1] = (char)uVar6 + cVar9;

      iVar11 = iVar10 + 1;

      if (dividend == NULL)
        goto LAB_80037aa4;

      if (iVar7 == 10)
      {
        if (iVar11 != 3 && iVar11 != 7)
        {
          if (iVar11 == 0xb)
          {
            bVar1 = 1;

LAB_80037890:
            bVar2 = 0;
          }
          else
          {
            bVar1 = 0;

            if (iVar11 != 0xf)
              goto LAB_80037890;

            bVar2 = 1;
          }

          if (!(bool)(bVar1 | bVar2))
            goto LAB_80037820;
        }

        abStack105[iVar10 + 2] = 0x2c;
        iVar11 = iVar10 + 2;
      }
    } while( true );
  }

  pcVar17 = (char *)((byte *)pcVar17 + 1);

  do {
  } while ((puVar4[0x1f] & 2) == 0);

  *puVar4 = (uint)bVar1;
  ppbVar13 = ppbVar3;
  goto LAB_80037754;

LAB_80037aa4:
  if (iStack60 != 0)
  {
    abStack105[iVar10 + 2] = 0x2d;
    iVar11 = iVar10 + 2;
  }

  if (iVar11 < (int)uVar14)
  {
    iVar10 = uVar14 - iVar11;
    iVar7 = iVar10;
    puVar5 = DAT_80037bb8;

    if (uStack64 == 0)
    {
      while (puVar5 = DAT_80037bb8, iVar7 != 0)
      {
        do {
        } while ((puVar4[0x1f] & 2) == 0);

        *puVar4 = uVar8;
        iVar7 = iVar7 + -1;
      }
    }

    while (puVar4 = DAT_80037bb8, 0 < iVar11)
    {
      do {
      } while ((DAT_80037bb8[0x1f] & 2) == 0);

      *DAT_80037bb8 = (uint)abStack105[iVar11];
      DAT_80037bb8 = puVar5;
      iVar11 = iVar11 + -1;
      puVar5 = DAT_80037bb8;
      DAT_80037bb8 = puVar4;
    }

    DAT_80037bb8 = puVar5;

    if (uStack64 != 0)
    {
      while (iVar10 != 0)
      {
        iVar10 = iVar10 + -1;

        do {
        } while ((puVar5[0x1f] & 2) == 0);

        *puVar5 = uVar8;
      }
    }
  }
  else
  {
    while (0 < iVar11)
    {
      do {
      } while ((puVar4[0x1f] & 2) == 0);

      *puVar4 = (uint)abStack105[iVar11];
      iVar11 = iVar11 + -1;
    }
  }

LAB_80037754:
  bVar1 = *pcVar17;
  ppbVar3 = ppbVar13;
  puVar4 = DAT_80037bb8;
  goto joined_r0x80037718;
}


