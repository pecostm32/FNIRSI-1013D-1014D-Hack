void FUN_80014e7c(void)

{
  undefined2 uVar1;
  uint uVar2;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  ushort *puVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  undefined2 *puVar12;
  ushort ypos;
  short sVar13;
  uint uVar14;
  int iVar15;
  
  iVar3 = DAT_800152dc;
  uVar2 = DAT_800152d8;
  uVar9 = DAT_800152d4;
  uVar14 = DAT_800152d0;
  set_frame_to_global_pointer();
  iVar5 = DAT_800152e4;
  puVar4 = PTR_DAT_800152e0;
  uVar11 = 0;
  do {
    puVar12 = (undefined2 *)((*Global_Frame_Buffer_Pointer + uVar11 * 0x640) - iVar5);
    puVar8 = (ushort *)(puVar4 + uVar11 * DAT_800152dc * 2);
    iVar15 = iVar3;
    do {
      uVar6 = (uint)*puVar8;
      uVar7 = uVar14;
      if (uVar6 != 0) {
        if (uVar6 == 0xf800) {
          uVar7 = 0;
        }
        else {
          uVar7 = uVar6;
          if (uVar6 == uVar2) {
            uVar7 = uVar9;
          }
        }
      }
      iVar15 = iVar15 + -1;
      *puVar12 = (short)uVar7;
      puVar12 = puVar12 + 1;
      puVar8 = puVar8 + 1;
    } while (iVar15 != 0);
    do {
      uVar11 = uVar11 + 1 & 0xfffeffff;
      if (0xd5 < uVar11) {
        FUN_800197c8(2);
        FUN_80019730(PTR_PTR_FUN_800152ec);
        set_display_color(0);
        ypos = (ushort)DAT_800152f0;
        display_text(&DAT_800152f4,0xef,ypos);
        display_text(&DAT_800152f8,0x1e8,ypos);
        uVar1 = (undefined2)uVar2;
        if (*(char *)(DAT_800152fc + 0x1c2) != '\0') {
          uVar14 = 0x1b;
          do {
            sVar13 = 0x3d;
            puVar12 = (undefined2 *)
                      ((*Global_Frame_Buffer_Pointer + (uVar14 * 800 + 2) * 2) - iVar5);
            puVar8 = (ushort *)(puVar4 + (uVar14 * iVar3 + 2) * 2);
            do {
              sVar13 = sVar13 + -1;
              if (*puVar8 == uVar2) {
                *puVar12 = uVar1;
              }
              puVar12 = puVar12 + 1;
              puVar8 = puVar8 + 1;
            } while (sVar13 != 0);
            uVar14 = uVar14 + 1 & 0xfffeffff;
          } while (uVar14 < 0x58);
        }
        if (*(char *)(DAT_800152fc + 0x1d2) != '\0') {
          uVar14 = 0x1b;
          do {
            sVar13 = 0x3d;
            puVar12 = (undefined2 *)
                      ((*Global_Frame_Buffer_Pointer + (uVar14 * 800 + 0x40) * 2) - iVar5);
            puVar8 = (ushort *)(puVar4 + (uVar14 * iVar3 + 0x40) * 2);
            do {
              sVar13 = sVar13 + -1;
              if (*puVar8 == uVar2) {
                *puVar12 = uVar1;
              }
              puVar12 = puVar12 + 1;
              puVar8 = puVar8 + 1;
            } while (sVar13 != 0);
            uVar14 = uVar14 + 1 & 0xfffeffff;
          } while (uVar14 < 0x58);
        }
        if (*(char *)(DAT_800152fc + 0x1e2) != '\0') {
          uVar14 = 0x1b;
          do {
            sVar13 = 0x3d;
            puVar12 = (undefined2 *)
                      ((*Global_Frame_Buffer_Pointer + (uVar14 * 800 + 0x7e) * 2) - iVar5);
            puVar8 = (ushort *)(puVar4 + (uVar14 * iVar3 + 0x7e) * 2);
            do {
              sVar13 = sVar13 + -1;
              if (*puVar8 == uVar2) {
                *puVar12 = uVar1;
              }
              puVar12 = puVar12 + 1;
              puVar8 = puVar8 + 1;
            } while (sVar13 != 0);
            uVar14 = uVar14 + 1 & 0xfffeffff;
          } while (uVar14 < 0x58);
        }
        if (*(char *)(DAT_800152fc + 0x1f2) != '\0') {
          uVar14 = 0x1b;
          do {
            sVar13 = 0x3d;
            puVar12 = (undefined2 *)
                      ((*Global_Frame_Buffer_Pointer + (uVar14 * 800 + 0xbc) * 2) - iVar5);
            puVar8 = (ushort *)(puVar4 + (uVar14 * iVar3 + 0xbc) * 2);
            do {
              sVar13 = sVar13 + -1;
              if (*puVar8 == uVar2) {
                *puVar12 = uVar1;
              }
              puVar12 = puVar12 + 1;
              puVar8 = puVar8 + 1;
            } while (sVar13 != 0);
            uVar14 = uVar14 + 1 & 0xfffeffff;
          } while (uVar14 < 0x58);
        }
        if (*(char *)(DAT_800152fc + 0x202) != '\0') {
          uVar14 = 0x59;
          do {
            sVar13 = 0x3d;
            puVar12 = (undefined2 *)
                      ((*Global_Frame_Buffer_Pointer + (uVar14 * 800 + 2) * 2) - iVar5);
            puVar8 = (ushort *)(puVar4 + (uVar14 * iVar3 + 2) * 2);
            do {
              sVar13 = sVar13 + -1;
              if (*puVar8 == uVar2) {
                *puVar12 = uVar1;
              }
              puVar12 = puVar12 + 1;
              puVar8 = puVar8 + 1;
            } while (sVar13 != 0);
            uVar14 = uVar14 + 1 & 0xfffeffff;
          } while (uVar14 < 0x96);
        }
        if (*(char *)(DAT_800152fc + 0x212) != '\0') {
          uVar14 = 0x59;
          do {
            sVar13 = 0x3d;
            puVar12 = (undefined2 *)
                      ((*Global_Frame_Buffer_Pointer + (uVar14 * 800 + 0x40) * 2) - iVar5);
            puVar8 = (ushort *)(puVar4 + (uVar14 * iVar3 + 0x40) * 2);
            do {
              sVar13 = sVar13 + -1;
              if (*puVar8 == uVar2) {
                *puVar12 = uVar1;
              }
              puVar12 = puVar12 + 1;
              puVar8 = puVar8 + 1;
            } while (sVar13 != 0);
            uVar14 = uVar14 + 1 & 0xfffeffff;
          } while (uVar14 < 0x96);
        }
        if (*(char *)(DAT_800152fc + 0x232) != '\0') {
          uVar14 = 0x59;
          do {
            sVar13 = 0x3d;
            puVar12 = (undefined2 *)
                      ((*Global_Frame_Buffer_Pointer + (uVar14 * 800 + 0x7e) * 2) - iVar5);
            puVar8 = (ushort *)(puVar4 + (uVar14 * iVar3 + 0x7e) * 2);
            do {
              sVar13 = sVar13 + -1;
              if (*puVar8 == uVar2) {
                *puVar12 = uVar1;
              }
              puVar12 = puVar12 + 1;
              puVar8 = puVar8 + 1;
            } while (sVar13 != 0);
            uVar14 = uVar14 + 1 & 0xfffeffff;
          } while (uVar14 < 0x96);
        }
        if (*(char *)(DAT_800152fc + 0x242) != '\0') {
          uVar14 = 0x59;
          do {
            sVar13 = 0x3d;
            puVar12 = (undefined2 *)
                      ((*Global_Frame_Buffer_Pointer + (uVar14 * 800 + 0xbc) * 2) - iVar5);
            puVar8 = (ushort *)(puVar4 + (uVar14 * iVar3 + 0xbc) * 2);
            do {
              sVar13 = sVar13 + -1;
              if (*puVar8 == uVar2) {
                *puVar12 = uVar1;
              }
              puVar12 = puVar12 + 1;
              puVar8 = puVar8 + 1;
            } while (sVar13 != 0);
            uVar14 = uVar14 + 1 & 0xfffeffff;
          } while (uVar14 < 0x96);
        }
        if (*(char *)(DAT_800152fc + 0x252) != '\0') {
          uVar14 = 0x97;
          do {
            sVar13 = 0x3d;
            puVar12 = (undefined2 *)
                      ((*Global_Frame_Buffer_Pointer + (uVar14 * 800 + 2) * 2) - iVar5);
            puVar8 = (ushort *)(puVar4 + (uVar14 * iVar3 + 2) * 2);
            do {
              sVar13 = sVar13 + -1;
              if (*puVar8 == uVar2) {
                *puVar12 = uVar1;
              }
              puVar12 = puVar12 + 1;
              puVar8 = puVar8 + 1;
            } while (sVar13 != 0);
            uVar14 = uVar14 + 1 & 0xfffeffff;
          } while (uVar14 < 0xd4);
        }
        if (*(char *)(DAT_800152fc + 0x262) != '\0') {
          uVar14 = 0x97;
          do {
            sVar13 = 0x3d;
            puVar12 = (undefined2 *)
                      ((*Global_Frame_Buffer_Pointer + (uVar14 * 800 + 0x40) * 2) - iVar5);
            puVar8 = (ushort *)(puVar4 + (uVar14 * iVar3 + 0x40) * 2);
            do {
              sVar13 = sVar13 + -1;
              if (*puVar8 == uVar2) {
                *puVar12 = uVar1;
              }
              puVar12 = puVar12 + 1;
              puVar8 = puVar8 + 1;
            } while (sVar13 != 0);
            uVar14 = uVar14 + 1 & 0xfffeffff;
          } while (uVar14 < 0xd4);
        }
        if (*(char *)(DAT_800152fc + 0x272) != '\0') {
          uVar14 = 0x97;
          do {
            sVar13 = 0x3d;
            puVar12 = (undefined2 *)
                      ((*Global_Frame_Buffer_Pointer + (uVar14 * 800 + 0x7e) * 2) - iVar5);
            puVar8 = (ushort *)(puVar4 + (uVar14 * iVar3 + 0x7e) * 2);
            do {
              sVar13 = sVar13 + -1;
              if (*puVar8 == uVar2) {
                *puVar12 = uVar1;
              }
              puVar12 = puVar12 + 1;
              puVar8 = puVar8 + 1;
            } while (sVar13 != 0);
            uVar14 = uVar14 + 1 & 0xfffeffff;
          } while (uVar14 < 0xd4);
        }
        if (*(char *)(DAT_800152fc + 0x282) != '\0') {
          uVar14 = 0x97;
          do {
            sVar13 = 0x3d;
            puVar12 = (undefined2 *)
                      ((*Global_Frame_Buffer_Pointer + (uVar14 * 800 + 0xbc) * 2) - iVar5);
            puVar8 = (ushort *)(puVar4 + (uVar14 * iVar3 + 0xbc) * 2);
            do {
              sVar13 = sVar13 + -1;
              if (*puVar8 == uVar2) {
                *puVar12 = uVar1;
              }
              puVar12 = puVar12 + 1;
              puVar8 = puVar8 + 1;
            } while (sVar13 != 0);
            uVar14 = uVar14 + 1 & 0xfffeffff;
          } while (uVar14 < 0xd4);
        }
        if (*(char *)(DAT_800152fc + 0x100) != '\0') {
          uVar11 = 0x1b;
          uVar14 = DAT_80015ef8 | (int)DAT_80015ef8 >> 4;
          uVar9 = DAT_80015ef8 - 0xf9;
          do {
            if (0xfa < (int)uVar14) {
              puVar12 = (undefined2 *)
                        ((*Global_Frame_Buffer_Pointer + (uVar11 * 800 + 0xfa) * 2) - iVar5);
              uVar7 = uVar9 & 0xffff;
              puVar8 = (ushort *)(puVar4 + (uVar11 * iVar3 + 0xfa) * 2);
              do {
                if (*puVar8 == uVar2) {
                  *puVar12 = uVar1;
                }
                uVar7 = uVar7 - 1 & 0xffff;
                puVar12 = puVar12 + 1;
                puVar8 = puVar8 + 1;
              } while (uVar7 != 0);
            }
            uVar11 = uVar11 + 1 & 0xfffeffff;
          } while (uVar11 < 0x58);
        }
        iVar15 = DAT_80015efc;
        if (*(char *)(DAT_800152fc + 0x112) != '\0') {
          uVar14 = 0x1b;
          do {
            if (0x138 < iVar15) {
              sVar13 = 0x3d;
              puVar12 = (undefined2 *)
                        ((*Global_Frame_Buffer_Pointer + (uVar14 * 800 + 0x138) * 2) - iVar5);
              puVar8 = (ushort *)(puVar4 + (uVar14 * iVar3 + 0x138) * 2);
              do {
                sVar13 = sVar13 + -1;
                if (*puVar8 == uVar2) {
                  *puVar12 = uVar1;
                }
                puVar12 = puVar12 + 1;
                puVar8 = puVar8 + 1;
              } while (sVar13 != 0);
            }
            uVar14 = uVar14 + 1 & 0xfffeffff;
          } while (uVar14 < 0x58);
        }
        if (*(char *)(DAT_800152fc + 0x122) != '\0') {
          uVar11 = 0x1b;
          uVar14 = DAT_80015f00 | (int)DAT_80015f00 >> 7;
          uVar9 = DAT_80015f00 - 0x175;
          do {
            if (0x176 < (int)uVar14) {
              puVar12 = (undefined2 *)
                        ((*Global_Frame_Buffer_Pointer + (uVar11 * 800 + 0x176) * 2) - iVar5);
              uVar7 = uVar9 & 0xffff;
              puVar8 = (ushort *)(puVar4 + (uVar11 * iVar3 + 0x176) * 2);
              do {
                if (*puVar8 == uVar2) {
                  *puVar12 = uVar1;
                }
                uVar7 = uVar7 - 1 & 0xffff;
                puVar12 = puVar12 + 1;
                puVar8 = puVar8 + 1;
              } while (uVar7 != 0);
            }
            uVar11 = uVar11 + 1 & 0xfffeffff;
          } while (uVar11 < 0x58);
        }
        iVar15 = DAT_80015f04;
        if (*(char *)(DAT_800152fc + 0x132) != '\0') {
          uVar14 = 0x1b;
          do {
            if (0x1b4 < iVar15) {
              sVar13 = 0x3d;
              puVar12 = (undefined2 *)
                        ((*Global_Frame_Buffer_Pointer + (uVar14 * 800 + 0x1b4) * 2) - iVar5);
              puVar8 = (ushort *)(puVar4 + (uVar14 * iVar3 + 0x1b4) * 2);
              do {
                sVar13 = sVar13 + -1;
                if (*puVar8 == uVar2) {
                  *puVar12 = uVar1;
                }
                puVar12 = puVar12 + 1;
                puVar8 = puVar8 + 1;
              } while (sVar13 != 0);
            }
            uVar14 = uVar14 + 1 & 0xfffeffff;
          } while (uVar14 < 0x58);
        }
        if (*(char *)(DAT_800152fc + 0x142) != '\0') {
          uVar11 = 0x59;
          uVar14 = DAT_80015ef8 | (int)DAT_80015ef8 >> 4;
          uVar9 = DAT_80015ef8 - 0xf9;
          do {
            if (0xfa < (int)uVar14) {
              puVar12 = (undefined2 *)
                        ((*Global_Frame_Buffer_Pointer + (uVar11 * 800 + 0xfa) * 2) - iVar5);
              uVar7 = uVar9 & 0xffff;
              puVar8 = (ushort *)(puVar4 + (uVar11 * iVar3 + 0xfa) * 2);
              do {
                if (*puVar8 == uVar2) {
                  *puVar12 = uVar1;
                }
                uVar7 = uVar7 - 1 & 0xffff;
                puVar12 = puVar12 + 1;
                puVar8 = puVar8 + 1;
              } while (uVar7 != 0);
            }
            uVar11 = uVar11 + 1 & 0xfffeffff;
          } while (uVar11 < 0x96);
        }
        iVar15 = DAT_80015efc;
        if (*(char *)(DAT_800152fc + 0x152) != '\0') {
          uVar14 = 0x59;
          do {
            if (0x138 < iVar15) {
              sVar13 = 0x3d;
              puVar12 = (undefined2 *)
                        ((*Global_Frame_Buffer_Pointer + (uVar14 * 800 + 0x138) * 2) - iVar5);
              puVar8 = (ushort *)(puVar4 + (uVar14 * iVar3 + 0x138) * 2);
              do {
                sVar13 = sVar13 + -1;
                if (*puVar8 == uVar2) {
                  *puVar12 = uVar1;
                }
                puVar12 = puVar12 + 1;
                puVar8 = puVar8 + 1;
              } while (sVar13 != 0);
            }
            uVar14 = uVar14 + 1 & 0xfffeffff;
          } while (uVar14 < 0x96);
        }
        if (*(char *)(DAT_800152fc + 0x162) != '\0') {
          uVar11 = 0x59;
          uVar14 = DAT_80015f00 | (int)DAT_80015f00 >> 7;
          uVar9 = DAT_80015f00 - 0x175;
          do {
            if (0x176 < (int)uVar14) {
              puVar12 = (undefined2 *)
                        ((*Global_Frame_Buffer_Pointer + (uVar11 * 800 + 0x176) * 2) - iVar5);
              uVar7 = uVar9 & 0xffff;
              puVar8 = (ushort *)(puVar4 + (uVar11 * iVar3 + 0x176) * 2);
              do {
                if (*puVar8 == uVar2) {
                  *puVar12 = uVar1;
                }
                uVar7 = uVar7 - 1 & 0xffff;
                puVar12 = puVar12 + 1;
                puVar8 = puVar8 + 1;
              } while (uVar7 != 0);
            }
            uVar11 = uVar11 + 1 & 0xfffeffff;
          } while (uVar11 < 0x96);
        }
        iVar15 = DAT_80015f04;
        if (*(char *)(DAT_800152fc + 0x172) != '\0') {
          uVar14 = 0x59;
          do {
            if (0x1b4 < iVar15) {
              sVar13 = 0x3d;
              puVar12 = (undefined2 *)
                        ((*Global_Frame_Buffer_Pointer + (uVar14 * 800 + 0x1b4) * 2) - iVar5);
              puVar8 = (ushort *)(puVar4 + (uVar14 * iVar3 + 0x1b4) * 2);
              do {
                sVar13 = sVar13 + -1;
                if (*puVar8 == uVar2) {
                  *puVar12 = uVar1;
                }
                puVar12 = puVar12 + 1;
                puVar8 = puVar8 + 1;
              } while (sVar13 != 0);
            }
            uVar14 = uVar14 + 1 & 0xfffeffff;
          } while (uVar14 < 0x96);
        }
        if (*(char *)(DAT_800152fc + 0x182) != '\0') {
          uVar11 = 0x97;
          uVar14 = DAT_80015ef8 | (int)DAT_80015ef8 >> 4;
          uVar9 = DAT_80015ef8 - 0xf9;
          do {
            if (0xfa < (int)uVar14) {
              puVar12 = (undefined2 *)
                        ((*Global_Frame_Buffer_Pointer + (uVar11 * 800 + 0xfa) * 2) - iVar5);
              uVar7 = uVar9 & 0xffff;
              puVar8 = (ushort *)(puVar4 + (uVar11 * iVar3 + 0xfa) * 2);
              do {
                if (*puVar8 == uVar2) {
                  *puVar12 = uVar1;
                }
                uVar7 = uVar7 - 1 & 0xffff;
                puVar12 = puVar12 + 1;
                puVar8 = puVar8 + 1;
              } while (uVar7 != 0);
            }
            uVar11 = uVar11 + 1 & 0xfffeffff;
          } while (uVar11 < 0xd4);
        }
        iVar15 = DAT_80015efc;
        if (*(char *)(DAT_800152fc + 0x192) != '\0') {
          uVar14 = 0x97;
          do {
            if (0x138 < iVar15) {
              sVar13 = 0x3d;
              puVar12 = (undefined2 *)
                        ((*Global_Frame_Buffer_Pointer + (uVar14 * 800 + 0x138) * 2) - iVar5);
              puVar8 = (ushort *)(puVar4 + (uVar14 * iVar3 + 0x138) * 2);
              do {
                sVar13 = sVar13 + -1;
                if (*puVar8 == uVar2) {
                  *puVar12 = uVar1;
                }
                puVar12 = puVar12 + 1;
                puVar8 = puVar8 + 1;
              } while (sVar13 != 0);
            }
            uVar14 = uVar14 + 1 & 0xfffeffff;
          } while (uVar14 < 0xd4);
        }
        if (*(char *)(DAT_800152fc + 0x1a2) != '\0') {
          uVar9 = 0x97;
          uVar11 = DAT_80015f00 | (int)DAT_80015f00 >> 7;
          uVar14 = DAT_80015f00 - 0x175;
          do {
            if (0x176 < (int)uVar11) {
              puVar12 = (undefined2 *)
                        ((*Global_Frame_Buffer_Pointer + (uVar9 * 800 + 0x176) * 2) - iVar5);
              uVar7 = uVar14 & 0xffff;
              puVar8 = (ushort *)(puVar4 + (uVar9 * iVar3 + 0x176) * 2);
              do {
                if (*puVar8 == uVar2) {
                  *puVar12 = uVar1;
                }
                uVar7 = uVar7 - 1 & 0xffff;
                puVar12 = puVar12 + 1;
                puVar8 = puVar8 + 1;
              } while (uVar7 != 0);
            }
            uVar9 = uVar9 + 1 & 0xfffeffff;
          } while (uVar9 < 0xd4);
        }
        iVar15 = DAT_80015f04;
        if (*(char *)(DAT_800152fc + 0x1b2) != '\0') {
          uVar14 = 0x97;
          do {
            if (0x1b4 < iVar15) {
              puVar12 = (undefined2 *)
                        ((*Global_Frame_Buffer_Pointer + (uVar14 * 800 + 0x1b4) * 2) - iVar5);
              puVar8 = (ushort *)(puVar4 + (uVar14 * iVar3 + 0x1b4) * 2);
              sVar13 = 0x3d;
              do {
                sVar13 = sVar13 + -1;
                if (*puVar8 == uVar2) {
                  *puVar12 = uVar1;
                }
                puVar12 = puVar12 + 1;
                puVar8 = puVar8 + 1;
              } while (sVar13 != 0);
            }
            uVar14 = uVar14 + 1 & 0xfffeffff;
          } while (uVar14 < 0xd4);
        }
        iVar5 = Start_Of_Screen_Mem;
        iVar3 = Screen_Frame_Buffer;
        uVar14 = DAT_80015f08;
        uVar9 = DAT_80015f08 - 0xd8;
        iVar15 = DAT_80015f08 + 0x16;
        if (DAT_80015f08 <= uVar9) {
          return;
        }
        do {
          iVar10 = uVar9 * 800 + 0xe6;
          copy_short((void *)(iVar5 + iVar10 * 2),(void *)(iVar3 + iVar10 * 2),iVar15);
          uVar9 = uVar9 + 1;
        } while (uVar9 < uVar14);
        return;
      }
    } while (iVar3 == 0);
  } while( true );
}


