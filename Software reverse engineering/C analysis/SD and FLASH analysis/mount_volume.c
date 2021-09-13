int mount_volume(uchar **p1,char **p2,uint p3)

{
  byte bVar1;
  char cVar2;
  ushort uVar3;
  short *psVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  char *pcVar8;
  short sVar9;
  char *pcVar10;
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
  
  *p2 = (char *)0x0;
  pbVar11 = *p1;

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

    if (((bVar20) && ((int)uVar15 < 1)) && (*p1 = pbVar12, -1 < (int)uVar15))
    {
LAB_800345e0:
      pcVar14 = *(char **)(DAT_80034a24 + uVar15 * 4);    //0x8019CE10 ==> Set with stack pointer address    FatFs[] ???

      if (pcVar14 == (char *)0x0)
      {
        return 0xc;
      }

      *p2 = pcVar14;

      if ((*pcVar14 == '\0') || (uVar6 = FUN_80033318(pcVar14[1]), (uVar6 & 1) != 0))         //FUN_80033318 just returns a zero.
      {
        *pcVar14 = '\0';
        pcVar14[1] = (char)uVar15;


        uVar15 = sys_init_sd_card(uVar15);



        if ((uVar15 & 1) != 0)
        {
          return 3;
        }

        bVar20 = (p3 & 0xfe) == 0;

        if (!bVar20)
        {
          bVar20 = (uVar15 & 4) == 0;
        }

        if (bVar20) {
          iVar16 = 0;
          *(undefined4 *)(pcVar14 + 0x30) = 0xffffffff;
          pcVar14[3] = '\0';
          iVar7 = FUN_80035ca8(pcVar14,0);
          if (iVar7 != 0) {
            return 1;
          }
          if (*(short *)(pcVar14 + 0x232) == -0x55ab) {
            cVar19 = pcVar14[0x34];
            if ((cVar19 == -0x17 || cVar19 == -0x15) || cVar19 == -0x18) {
              iVar7 = 3;
              pcVar8 = &DAT_80034a28;
              pcVar10 = pcVar14 + 0x6a;
              do {
                cVar19 = *pcVar10;
                cVar2 = *pcVar8;
                iVar7 = iVar7 + -1;
                if (iVar7 == 0) {
                  if (cVar19 == cVar2) goto LAB_80034800;
                  break;
                }
                pcVar8 = pcVar8 + 1;
                pcVar10 = pcVar10 + 1;
              } while (cVar19 == cVar2);
              iVar7 = 5;
              pcVar8 = &DAT_80034a2c;
              pcVar10 = pcVar14 + 0x86;
              do {
                cVar19 = *pcVar10;
                cVar2 = *pcVar8;
                iVar7 = iVar7 + -1;
                if (iVar7 == 0) {
                  if (cVar19 == cVar2) goto LAB_80034800;
                  break;
                }
                pcVar8 = pcVar8 + 1;
                pcVar10 = pcVar10 + 1;
              } while (cVar19 == cVar2);
            }
            uVar15 = 0;
            do {
              if ((pcVar14 + uVar15 * 0x10)[0x1f6] == '\0') {
                iVar7 = 0;
              }
              else {
                iVar7 = *(int *)(pcVar14 + uVar15 * 0x10 + 0x1fa);
              }
              aiStack56[uVar15] = iVar7;
              uVar15 = uVar15 + 1;
            } while (uVar15 < 4);
            uVar15 = 0;
            do {
              iVar16 = aiStack56[uVar15];
              if (iVar16 == 0) {
LAB_800347e0:
                uVar6 = 3;
              }
              else {
                pcVar14[3] = '\0';
                *(undefined4 *)(pcVar14 + 0x30) = 0xffffffff;
                iVar7 = FUN_80035ca8(pcVar14,iVar16);
                if (iVar7 == 0) {
                  if (*(short *)(pcVar14 + 0x232) != -0x55ab) goto LAB_800347e0;
                  cVar19 = pcVar14[0x34];
                  if ((cVar19 == -0x17 || cVar19 == -0x15) || cVar19 == -0x18) {
                    iVar7 = 3;
                    pcVar8 = &DAT_80034a28;
                    pcVar10 = pcVar14 + 0x6a;
                    do {
                      cVar19 = *pcVar10;
                      cVar2 = *pcVar8;
                      iVar7 = iVar7 + -1;
                      if (iVar7 == 0) {
                        if (cVar19 == cVar2) goto LAB_80034800;
                        break;
                      }
                      pcVar8 = pcVar8 + 1;
                      pcVar10 = pcVar10 + 1;
                    } while (cVar19 == cVar2);
                    iVar7 = 5;
                    pcVar8 = &DAT_80034a2c;
                    pcVar10 = pcVar14 + 0x86;
                    do {
                      cVar19 = *pcVar10;
                      cVar2 = *pcVar8;
                      iVar7 = iVar7 + -1;
                      if (iVar7 == 0) {
                        if (cVar19 == cVar2) goto LAB_80034800;
                        break;
                      }
                      pcVar8 = pcVar8 + 1;
                      pcVar10 = pcVar10 + 1;
                    } while (cVar19 == cVar2);
                  }
                  uVar6 = 2;
                }
                else {
                  uVar6 = 4;
                }
              }
              uVar15 = uVar15 + 1;
            } while (uVar15 < 4);
            if (uVar6 == 4) {
              return 1;
            }
            if (uVar6 < 2) {
LAB_80034800:
              if (*(short *)(pcVar14 + 0x3f) == 0x200) {
                uStack40 = (uint)*(ushort *)(pcVar14 + 0x4a);
                if (uStack40 == 0) {
                  uStack40 = *(uint *)(pcVar14 + 0x58);
                }
                uVar15 = (uint)(byte)pcVar14[0x44];
                *(uint *)(pcVar14 + 0x1c) = uStack40;
                pcVar14[2] = pcVar14[0x44];
                if (uVar15 == 1 || uVar15 == 2) {
                  uVar6 = (uint)(byte)pcVar14[0x41];
                  iVar7 = uVar15 * uStack40;
                  *(ushort *)(pcVar14 + 10) = (ushort)(byte)pcVar14[0x41];
                  if ((uVar6 != 0) && ((uVar6 & uVar6 - 1) == 0)) {
                    uVar3 = *(ushort *)(pcVar14 + 0x45);
                    *(ushort *)(pcVar14 + 8) = uVar3;
                    if ((uVar3 & 0xf) == 0) {
                      uVar15 = (uint)*(ushort *)(pcVar14 + 0x47);
                      if (uVar15 == 0) {
                        uVar15 = *(uint *)(pcVar14 + 0x54);
                      }
                      uVar17 = (uint)*(ushort *)(pcVar14 + 0x42);
                      if (((uVar17 != 0) &&
                          (uVar18 = uVar17 + iVar7 + (uint)(uVar3 >> 4), uVar18 <= uVar15)) &&
                         (uVar15 = divide(uVar15 - uVar18,uVar6), uVar15 != 0)) {
                        cVar19 = '\0';
                        if (uVar15 < 0xffffff6) {
                          cVar19 = '\x03';
                        }
                        if (uVar15 <= DAT_80034a34) {
                          cVar19 = '\x02';
                        }
                        if (DAT_80034a38 < uVar15) {
                          if (cVar19 == '\0') {
                            return 0xd;
                          }
                        }
                        else {
                          cVar19 = '\x01';
                        }
                        uVar15 = uVar15 + 2;
                        *(uint *)(pcVar14 + 0x18) = uVar15;
                        *(uint *)(pcVar14 + 0x24) = iVar16 + uVar17;
                        *(uint *)(pcVar14 + 0x2c) = iVar16 + uVar18;
                        *(int *)(pcVar14 + 0x20) = iVar16;
                        if (cVar19 == '\x03') {
                          if (*(short *)(pcVar14 + 0x5e) != 0 || uVar3 != 0) {
                            return 0xd;
                          }
                          iVar7 = uVar15 * 4;
                          *(undefined4 *)(pcVar14 + 0x28) = *(undefined4 *)(pcVar14 + 0x60);
                        }
                        else {
                          if (uVar3 == 0) {
                            return 0xd;
                          }
                          *(uint *)(pcVar14 + 0x28) = iVar16 + uVar17 + iVar7;
                          if (cVar19 == '\x02') {
                            iVar7 = uVar15 * 2;
                          }
                          else {
                            iVar7 = (uVar15 & 1) + (uVar15 * 3 >> 1);
                          }
                        }
                        if (iVar7 + 0x1ffU >> 9 <= uStack40) {
                          *(undefined4 *)(pcVar14 + 0x14) = 0xffffffff;
                          *(undefined4 *)(pcVar14 + 0x10) = 0xffffffff;
                          pcVar14[4] = -0x80;
                          if ((((cVar19 == '\x03') && (*(short *)(pcVar14 + 100) == 1)) &&
                              ((iVar7 = FUN_80035ca8(pcVar14,iVar16 + 1), iVar7 == 0 &&
                               ((pcVar14[4] = '\0', *(short *)(pcVar14 + 0x232) == -0x55ab &&
                                (*(int *)(pcVar14 + 0x34) == DAT_80034b9c)))))) &&
                             (*(int *)(pcVar14 + 0x218) == DAT_80034ba0)) {
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
      else {
        bVar20 = (p3 & 0xfe) == 0;
        if (!bVar20) {
          bVar20 = (uVar6 & 4) == 0;
        }
        if (bVar20) {
          return 0;
        }
      }
      return 10;
    }
  }
  return 0xb;
}


