//-------------------------------------------------------------
//p3 = 1
//p2 = 0x8003545c ==> 0x00003A30
//p1 = stack pointer

int check_sd_card(uint p1,uint p2,uint p3)

{
  byte bVar1;
  byte *pbVar2;
  int iVar4;
  undefined *puVar5;
  uint uVar6;
  code *UNRECOVERED_JUMPTABLE_00;
  bool bVar7;
  byte *pbVar3;
  
  iVar4 = DAT_800337c0;               //0x8019CE10  ==> 0x00000000 at startup

  pbVar3 = (byte *)p2;                //pbVar3 = 0x8003545c

  if (p2 != 0)                        //Valid pointer given
  {
    do
    {
      pbVar2 = pbVar3 + 1;
      bVar1 = *pbVar3;                //bVar1 = 0x30, second round bVar1 = 0x3A

      if (bVar1 < 0x20)               //Not true at entry, also not true second go
      {
        uVar6 = 0;
        goto LAB_80033774;
      }

      pbVar3 = pbVar2;                //Point to next byte
    } while (bVar1 != 0x3a);          //Quit on second loop

    uVar6 = *(byte *)p2 - 0x30;       //uVar6 = 0
    bVar7 = uVar6 == 9;               //bVar7 = 0

    if (uVar6 < 10)                   //True
    {
      bVar7 = (byte *)(p2 + 2) == pbVar2; //bVar7 = 1
    }

    if (((bVar7) && ((int)uVar6 < 1)) && (-1 < (int)uVar6)) // True
    {
LAB_80033774:
      puVar5 = *(undefined **)(DAT_800337c0 + uVar6 * 4);

      if (puVar5 != (undefined *)0x0)  //Skip
      {
        *puVar5 = 0;
      }

      if (p1 != 0)                      //True
      {
        *(undefined *)p1 = 0;           //0 on stack
      }

      *(uint *)(iVar4 + uVar6 * 4) = p1; // store stack address??????

      if (p3 != 0)                       //true
      {
        iVar4 = some_sd_card_stuff_5();  //Three inputs, sp + 4, sp, 0

        return iVar4;
      }

      return(0);
    }

  }
  return 0xb;
}

//---------------------------------------------------------------------------------------------------------------

undefined4 some_sd_card_stuff_5(void)

{
  byte bVar1;
  char cVar2;
  ushort uVar3;
  short *psVar4;
  undefined4 uVar5;
  byte **in_r0;
  uint uVar6;
  int iVar7;
  char *pcVar8;
  short sVar9;
  char **in_r1;
  char *pcVar10;
  uint in_r2;
  byte *pbVar11;
  byte *pbVar12;
  char *pcVar14;
  uint uVar15;
  int iVar16;
  uint uVar17;
  uint uVar18;
  char cVar19;
  bool bVar20;
  int aiStack56 [4];
  uint uStack40;
  byte *pbVar13;
  
  *in_r1 = (char *)0x0;
  pbVar11 = *in_r0;
  pbVar13 = pbVar11;

  if (pbVar11 != (byte *)0x0)
  {
    do
    {
      pbVar12 = pbVar13 + 1;
      bVar1 = *pbVar13;
      if (bVar1 < 0x20)
      {
        uVar15 = 0;
        goto LAB_800345e0;
      }

      pbVar13 = pbVar12;
    } while (bVar1 != 0x3a);

    uVar15 = *pbVar11 - 0x30;
    bVar20 = uVar15 == 9;

    if (uVar15 < 10)
    {
      bVar20 = pbVar11 + 2 == pbVar12;
    }

    if (((bVar20) && ((int)uVar15 < 1)) && (*in_r0 = pbVar12, -1 < (int)uVar15))
    {
LAB_800345e0:
      pcVar14 = *(char **)(DAT_80034a24 + uVar15 * 4);

      if (pcVar14 == (char *)0x0)
      {
        return 0xc;
      }

      *in_r1 = pcVar14;

      if ((*pcVar14 == '\0') || (uVar6 = FUN_80033318(pcVar14[1]), (uVar6 & 1) != 0))         //FUN_80033318 just returns a zero.
      {
        *pcVar14 = '\0';
        pcVar14[1] = (char)uVar15;

        uVar15 = sys_init_sd_card();

        if ((uVar15 & 1) != 0)
        {
          return 3;
        }

        bVar20 = (in_r2 & 0xfe) == 0;

        if (!bVar20)
        {
          bVar20 = (uVar15 & 4) == 0;
        }

        if (bVar20)
        {
          iVar16 = 0;
          *(undefined4 *)(pcVar14 + 0x30) = 0xffffffff;
          pcVar14[3] = '\0';

          iVar7 = FUN_80035ca8(pcVar14,0);

          if (iVar7 != 0)
          {
            return 1;
          }

          if (*(short *)(pcVar14 + 0x232) == -0x55ab)
          {
            cVar19 = pcVar14[0x34];

            if ((cVar19 == -0x17 || cVar19 == -0x15) || cVar19 == -0x18)
            {
              iVar7 = 3;
              pcVar8 = &DAT_80034a28;
              pcVar10 = pcVar14 + 0x6a;

              do
              {
                cVar19 = *pcVar10;
                cVar2 = *pcVar8;
                iVar7 = iVar7 + -1;

                if (iVar7 == 0)
                {
                  if (cVar19 == cVar2)
                    goto LAB_80034800;

                  break;
                }

                pcVar8 = pcVar8 + 1;
                pcVar10 = pcVar10 + 1;
              } while (cVar19 == cVar2);

              iVar7 = 5;
              pcVar8 = &DAT_80034a2c;
              pcVar10 = pcVar14 + 0x86;

              do
              {
                cVar19 = *pcVar10;
                cVar2 = *pcVar8;
                iVar7 = iVar7 + -1;

                if (iVar7 == 0)
                {
                  if (cVar19 == cVar2)
                    goto LAB_80034800;

                  break;
                }

                pcVar8 = pcVar8 + 1;
                pcVar10 = pcVar10 + 1;
              } while (cVar19 == cVar2);
            }

            uVar15 = 0;

            do
            {
              if ((pcVar14 + uVar15 * 0x10)[0x1f6] == '\0')
              {
                iVar7 = 0;
              }
              else
              {
                iVar7 = *(int *)(pcVar14 + uVar15 * 0x10 + 0x1fa);
              }

              aiStack56[uVar15] = iVar7;
              uVar15 = uVar15 + 1;
            } while (uVar15 < 4);

            uVar15 = 0;

            do
            {
              iVar16 = aiStack56[uVar15];

              if (iVar16 == 0)
              {
LAB_800347e0:
                uVar6 = 3;
              }
              else
              {
                pcVar14[3] = '\0';
                *(undefined4 *)(pcVar14 + 0x30) = 0xffffffff;

                iVar7 = FUN_80035ca8(pcVar14,iVar16);

                if (iVar7 == 0)
                {
                  if (*(short *)(pcVar14 + 0x232) != -0x55ab)
                    goto LAB_800347e0;

                  cVar19 = pcVar14[0x34];

                  if ((cVar19 == -0x17 || cVar19 == -0x15) || cVar19 == -0x18)
                  {
                    iVar7 = 3;
                    pcVar8 = &DAT_80034a28;
                    pcVar10 = pcVar14 + 0x6a;

                    do
                    {
                      cVar19 = *pcVar10;
                      cVar2 = *pcVar8;
                      iVar7 = iVar7 + -1;

                      if (iVar7 == 0)
                      {
                        if (cVar19 == cVar2)
                          goto LAB_80034800;

                        break;
                      }

                      pcVar8 = pcVar8 + 1;
                      pcVar10 = pcVar10 + 1;
                    } while (cVar19 == cVar2);

                    iVar7 = 5;
                    pcVar8 = &DAT_80034a2c;
                    pcVar10 = pcVar14 + 0x86;

                    do
                    {
                      cVar19 = *pcVar10;
                      cVar2 = *pcVar8;
                      iVar7 = iVar7 + -1;

                      if (iVar7 == 0)
                      {
                        if (cVar19 == cVar2)
                          goto LAB_80034800;

                        break;
                      }

                      pcVar8 = pcVar8 + 1;
                      pcVar10 = pcVar10 + 1;
                    } while (cVar19 == cVar2);
                  }

                  uVar6 = 2;
                }
                else
                {
                  uVar6 = 4;
                }
              }

              uVar15 = uVar15 + 1;
            } while (uVar15 < 4);

            if (uVar6 == 4)
            {
              return 1;
            }

            if (uVar6 < 2)
            {
LAB_80034800:
              if (*(short *)(pcVar14 + 0x3f) == 0x200)
              {
                uStack40 = (uint)*(ushort *)(pcVar14 + 0x4a);

                if (uStack40 == 0)
                {
                  uStack40 = *(uint *)(pcVar14 + 0x58);
                }

                uVar15 = (uint)(byte)pcVar14[0x44];
                *(uint *)(pcVar14 + 0x1c) = uStack40;
                pcVar14[2] = pcVar14[0x44];

                if (uVar15 == 1 || uVar15 == 2)
                {
                  uVar6 = (uint)(byte)pcVar14[0x41];
                  iVar7 = uVar15 * uStack40;
                  *(ushort *)(pcVar14 + 10) = (ushort)(byte)pcVar14[0x41];

                  if ((uVar6 != 0) && ((uVar6 & uVar6 - 1) == 0))
                  {
                    uVar3 = *(ushort *)(pcVar14 + 0x45);
                    *(ushort *)(pcVar14 + 8) = uVar3;

                    if ((uVar3 & 0xf) == 0)
                    {
                      uVar15 = (uint)*(ushort *)(pcVar14 + 0x47);

                      if (uVar15 == 0)
                      {
                        uVar15 = *(uint *)(pcVar14 + 0x54);
                      }

                      uVar17 = (uint)*(ushort *)(pcVar14 + 0x42);

                      if (((uVar17 != 0) && (uVar18 = uVar17 + iVar7 + (uint)(uVar3 >> 4), uVar18 <= uVar15)) && (uVar15 = divide(uVar15 - uVar18,uVar6), uVar15 != 0))
                      {
                        cVar19 = '\0';

                        if (uVar15 < 0xffffff6)
                        {
                          cVar19 = '\x03';
                        }
 
                        if (uVar15 <= DAT_80034a34)
                        {
                          cVar19 = '\x02';
                        }

                        if (DAT_80034a38 < uVar15)
                        {
                          if (cVar19 == '\0')
                          {
                            return 0xd;
                          }
                        }
                        else
                        {
                          cVar19 = '\x01';
                        }

                        uVar15 = uVar15 + 2;
                        *(uint *)(pcVar14 + 0x18) = uVar15;
                        *(uint *)(pcVar14 + 0x24) = iVar16 + uVar17;
                        *(uint *)(pcVar14 + 0x2c) = iVar16 + uVar18;
                        *(int *)(pcVar14 + 0x20) = iVar16;

                        if (cVar19 == '\x03')
                        {
                          if (*(short *)(pcVar14 + 0x5e) != 0 || uVar3 != 0)
                          {
                            return 0xd;
                          }

                          iVar7 = uVar15 * 4;
                          *(undefined4 *)(pcVar14 + 0x28) = *(undefined4 *)(pcVar14 + 0x60);
                        }
                        else
                        {
                          if (uVar3 == 0)
                          {
                            return 0xd;
                          }

                          *(uint *)(pcVar14 + 0x28) = iVar16 + uVar17 + iVar7;

                          if (cVar19 == '\x02')
                          {
                            iVar7 = uVar15 * 2;
                          }
                          else
                          {
                            iVar7 = (uVar15 & 1) + (uVar15 * 3 >> 1);
                          }
                        }

                        if (iVar7 + 0x1ffU >> 9 <= uStack40)
                        {
                          *(undefined4 *)(pcVar14 + 0x14) = 0xffffffff;
                          *(undefined4 *)(pcVar14 + 0x10) = 0xffffffff;
                          pcVar14[4] = -0x80;

                          if ((((cVar19 == '\x03') && (*(short *)(pcVar14 + 100) == 1)) && ((iVar7 = FUN_80035ca8(pcVar14,iVar16 + 1), iVar7 == 0 && ((pcVar14[4] = '\0', *(short *)(pcVar14 + 0x232) == -0x55ab && (*(int *)(pcVar14 + 0x34) == DAT_80034b9c)))))) && (*(int *)(pcVar14 + 0x218) == DAT_80034ba0))
                          {
                            *(undefined4 *)(pcVar14 + 0x14) = *(undefined4 *)(pcVar14 + 0x21c);
                            *(undefined4 *)(pcVar14 + 0x10) = *(undefined4 *)(pcVar14 + 0x220);
                          }

                          psVar4 = DAT_80034ba4;
                          *pcVar14 = cVar19;
                          sVar9 = *psVar4 + 1;
                          *psVar4 = sVar9;
                          uVar5 = DAT_80034ba8;
                          *(short *)(pcVar14 + 6) = sVar9;
                          *(undefined4 *)(pcVar14 + 0xc) = uVar5;

                          return 0;
                        }
                      }
                    }
                  }
                }
              }
            }
          }

          return 0xd;
        }
      }
      else
      {
        bVar20 = (in_r2 & 0xfe) == 0;

        if (!bVar20)
        {
          bVar20 = (uVar6 & 4) == 0;
        }

        if (bVar20)
        {
          return 0;
        }
      }

      return 10;
    }
  }
  return 0xb;
}

//---------------------------------------------------------------------------------------------------------------

undefined4 FUN_80033318(void)

{
  return 0;
}

//---------------------------------------------------------------------------------------------------------------

bool FUN_80035ca8(int param_1,int param_2)

{
  int iVar1;
  bool bVar2;
  
  bVar2 = false;

  if (*(int *)(param_1 + 0x30) != param_2)
  {
    if (*(char *)(param_1 + 3) != '\0')
    {
      iVar1 = FUN_80033320(*(undefined *)(param_1 + 1),param_1 + 0x34,*(int *)(param_1 + 0x30),1);

      bVar2 = iVar1 != 0;

      if (bVar2)
      {
        return bVar2;
      }

      *(undefined *)(param_1 + 3) = 0;

      if (((uint)(*(int *)(param_1 + 0x30) - *(int *)(param_1 + 0x24)) < *(uint *)(param_1 + 0x1c)) && (*(char *)(param_1 + 2) == '\x02'))
      {
        FUN_80033320(*(undefined *)(param_1 + 1),param_1 + 0x34, *(int *)(param_1 + 0x30) + *(uint *)(param_1 + 0x1c),1);
      }
    }

    iVar1 = FUN_80033274(*(undefined *)(param_1 + 1),param_1 + 0x34,param_2,1);

    if (iVar1 != 0)
    {
      param_2 = -1;
      bVar2 = true;
    }

    *(int *)(param_1 + 0x30) = param_2;
  }

  return bVar2;
}

//---------------------------------------------------------------------------------------------------------------

uint FUN_80033320(undefined4 param_1,void *param_2,undefined4 param_3,int param_4)

{
  void *dest;
  int iVar1;
  uint unaff_r4;
  
  switch(param_1)
  {
  case 0:
    if (((uint)param_2 & 3) == 0)
    {
      iVar1 = FUN_80024730(0,param_3,param_4,param_2);

      if (iVar1 == 0)
      {
        return 0;
      }
    }
    else
    {
      dest = (void *)FUN_800001cc();

      if (dest != (void *)0x0)
      {
        memcpy(dest,param_2,param_4 << 9);

        iVar1 = FUN_80024730(0,param_3,param_4,dest);

        FUN_8000022e(dest);

        return (uint)(iVar1 != 0);
      }
    }

    unaff_r4 = 1;
    break;

  case 1:
  case 2:
  case 3:
  case 4:
    break;

  default:
    unaff_r4 = 4;
  }

  return unaff_r4;
}

//---------------------------------------------------------------------------------------------------------------

uint FUN_80033274(int param_1,void *param_2,undefined4 param_3,uint param_4)

{
  void *source;
  int iVar1;
  longlong lVar2;
  
  if (param_1 == 0) {
    if (((uint)param_2 & 3) == 0) {
      iVar1 = FUN_80024558(0,param_3,param_4,param_2);
      if (iVar1 == 0) {
        return 0;
      }
    }
    else {
      source = (void *)FUN_800001cc();
      if (source != (void *)0x0) {
        iVar1 = FUN_80024558(0,param_3,param_4,source);
        lVar2 = memcpy(param_2,source,param_4 << 9);
        FUN_8000022e(source,(int)((ulonglong)lVar2 >> 0x20));
        return (uint)(iVar1 != 0);
      }
    }
    param_4 = 1;
  }
  return param_4;
}


//---------------------------------------------------------------------------------------------------------------

int FUN_80024730(undefined4 param_1,int param_2,int param_3,uint param_4)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  undefined2 uVar4;
  undefined2 local_50 [2];
  undefined4 local_4c;
  int local_48;
  uint uStack48;
  undefined4 uStack44;
  int iStack40;
  undefined4 uStack36;
  
  piVar1 = DAT_80024898;
  uVar3 = (param_2 + param_3) - 1;
  if ((uint)DAT_80024898[3] < uVar3) {
    FUN_800376f8(DAT_8002489c,uVar3);
    FUN_800376f8(PTR_s__The_max_valid_sector_number_for_800248a0,piVar1[3]);
    return DAT_800248a4;
  }
  if (param_4 == 0) {
    FUN_800376f8(s_ERROR__fmiSD_Read_in____uBufcnt_c_800248c4);
    return DAT_800248f4;
  }
  if ((param_4 & 3) != 0) {
    FUN_800376f8(s_Addr_Align_Err_____800248a8);
    return DAT_800248c0;
  }
  local_48 = DAT_80024898[1];
  if (*DAT_80024898 != 1) {
    param_2 = param_2 << 9;
  }
  local_50[0] = 7;
  if (param_3 == 1) {
    uVar4 = 0x18;
  }
  else {
    uVar4 = 0x19;
  }
  local_4c = 0xd;
  iVar2 = FUN_80036d3c(param_1,local_50,0);
  if (iVar2 == 0) {
    uStack36 = 0x200;
    uStack44 = 2;
    local_4c = 0xd;
    local_50[0] = uVar4;
    local_48 = param_2;
    uStack48 = param_4;
    iStack40 = param_3;
    iVar2 = FUN_80036d3c(param_1,local_50,&uStack48);
    if (iVar2 == 0) {
      local_50[0] = 7;
      local_48 = 0;
      local_4c = 0;
      FUN_80036d3c(param_1,local_50);
      return 0;
    }
    return iVar2;
  }
  return iVar2;
}

//---------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------


