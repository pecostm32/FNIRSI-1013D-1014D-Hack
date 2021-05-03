void FUN_8000e1e4(void)

{
  char cVar1;
  undefined *puVar2;
  int *piVar3;
  ushort uVar4;
  short sVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  ushort *puVar13;
  int iVar14;
  uint uVar15;
  ushort *puVar16;
  undefined2 *puVar17;
  int iVar18;
  
  uVar4 = FUN_800232b4(DAT_8000e6d8);
  uVar6 = FUN_800232b4(DAT_8000e6dc);
  uVar7 = FUN_800232b4(0);
  uVar8 = FUN_800232b4(0xffffff);
  cVar1 = *DAT_8000e6e0;
  set_frame_to_global_pointer();
  piVar3 = Global_Frame_Buffer_Pointer;
  puVar2 = PTR_DAT_8000e6e8;
  uVar11 = DAT_8000e6e4;
  uVar15 = 0;
  do {
    iVar18 = 0x95;
    puVar13 = (ushort *)(PTR_DAT_8000e6f0 + uVar15 * 0x12a);
    puVar17 = (undefined2 *)
              (*piVar3 + ((uint)*(ushort *)puVar2 + (*(ushort *)(puVar2 + 2) + uVar15) * 800) * 2);
    do {
      uVar9 = (uint)*puVar13;
      uVar10 = uVar6;
      if (((uVar9 != 0) && (uVar10 = uVar7, uVar9 != 0xf800)) && (uVar10 = uVar9, uVar9 == uVar11))
      {
        uVar10 = uVar8;
      }
      iVar18 = iVar18 + -1;
      *puVar17 = (short)uVar10;
      puVar13 = puVar13 + 1;
      puVar17 = puVar17 + 1;
    } while (iVar18 != 0);
    uVar15 = uVar15 + 1 & 0xfffeffff;
  } while (uVar15 < 0xeb);
  if (cVar1 == '\x01') {
    uVar11 = 0xe;
    do {
      puVar13 = (ushort *)
                (*piVar3 +
                ((*(ushort *)(puVar2 + 2) + uVar11) * 800 + 9 + (uint)*(ushort *)puVar2) * 2);
      sVar5 = 0x83;
      do {
        sVar5 = sVar5 + -1;
        if (*puVar13 == uVar6) {
          *puVar13 = uVar4;
        }
        else {
          *puVar13 = ~*puVar13;
        }
        puVar13 = puVar13 + 1;
      } while (sVar5 != 0);
      uVar11 = uVar11 + 1 & 0xfffeffff;
    } while (uVar11 < 0x2e);
  }
  else {
    if (cVar1 == '\x02') {
      iVar18 = *piVar3;
      uVar11 = 0x47;
      do {
        puVar13 = (ushort *)
                  (iVar18 + ((uint)*(ushort *)puVar2 + (*(ushort *)(puVar2 + 2) + uVar11) * 800 + 9)
                            * 2);
        if (uVar10 == uVar6) {
          *puVar13 = uVar4;
        }
        else {
          *puVar13 = ~*puVar13;
        }
        iVar14 = 1;
        sVar5 = 0x41;
        do {
          puVar13 = (ushort *)
                    (iVar18 + ((uint)*(ushort *)puVar2 + (*(ushort *)(puVar2 + 2) + uVar11) * 800 +
                              iVar14 + 9) * 2);
          if (uVar10 == uVar6) {
            *puVar13 = uVar4;
          }
          else {
            *puVar13 = ~*puVar13;
          }
          iVar12 = iVar18 + ((uint)*(ushort *)puVar2 + (*(ushort *)(puVar2 + 2) + uVar11) * 800 +
                            iVar14 + 9) * 2;
          if (uVar10 == uVar6) {
            *(ushort *)(iVar12 + 2) = uVar4;
          }
          else {
            *(ushort *)(iVar12 + 2) = ~*(ushort *)(iVar12 + 2);
          }
          sVar5 = sVar5 + -1;
          iVar14 = iVar14 + 2;
        } while (sVar5 != 0);
        uVar11 = uVar11 + 1 & 0xfffeffff;
      } while (uVar11 < 0x69);
    }
    else {
      if (cVar1 == '\x03') {
        iVar18 = *piVar3;
        uVar11 = 0x82;
        do {
          puVar13 = (ushort *)
                    (iVar18 + ((uint)*(ushort *)puVar2 + (*(ushort *)(puVar2 + 2) + uVar11) * 800 +
                              9) * 2);
          if (uVar10 == uVar6) {
            *puVar13 = uVar4;
          }
          else {
            *puVar13 = ~*puVar13;
          }
          iVar14 = 1;
          sVar5 = 0x41;
          do {
            puVar13 = (ushort *)
                      (iVar18 + ((uint)*(ushort *)puVar2 + (*(ushort *)(puVar2 + 2) + uVar11) * 800
                                + iVar14 + 9) * 2);
            if (uVar10 == uVar6) {
              *puVar13 = uVar4;
            }
            else {
              *puVar13 = ~*puVar13;
            }
            iVar12 = iVar18 + ((uint)*(ushort *)puVar2 + (*(ushort *)(puVar2 + 2) + uVar11) * 800 +
                              iVar14 + 9) * 2;
            if (uVar10 == uVar6) {
              *(ushort *)(iVar12 + 2) = uVar4;
            }
            else {
              *(ushort *)(iVar12 + 2) = ~*(ushort *)(iVar12 + 2);
            }
            sVar5 = sVar5 + -1;
            iVar14 = iVar14 + 2;
          } while (sVar5 != 0);
          uVar11 = uVar11 + 1 & 0xfffeffff;
        } while (uVar11 < 0xa4);
      }
      else {
        if (cVar1 == '\x04') {
          uVar11 = 0xbe;
          do {
            if (uVar10 == uVar6) {
              puVar13 = (ushort *)
                        (*piVar3 +
                        ((uint)*(ushort *)puVar2 + (*(ushort *)(puVar2 + 2) + uVar11) * 800 + 9) * 2
                        );
              *puVar13 = uVar4;
              sVar5 = 0x41;
              do {
                sVar5 = sVar5 + -1;
                puVar13[1] = uVar4;
                puVar13 = puVar13 + 2;
                *puVar13 = uVar4;
              } while (sVar5 != 0);
            }
            else {
              puVar13 = (ushort *)
                        (*piVar3 +
                        ((uint)*(ushort *)puVar2 + (*(ushort *)(puVar2 + 2) + uVar11) * 800 + 9) * 2
                        );
              *puVar13 = ~*puVar13;
              sVar5 = 0x41;
              do {
                puVar16 = puVar13 + 2;
                sVar5 = sVar5 + -1;
                puVar13[1] = ~puVar13[1];
                *puVar16 = ~*puVar16;
                puVar13 = puVar16;
              } while (sVar5 != 0);
            }
            uVar11 = uVar11 + 1 & 0xfffeffff;
          } while (uVar11 < 0xde);
        }
      }
    }
  }
  set_display_color(DAT_8000e6f4);
  FUN_80018da0((uint)*(ushort *)puVar2,(uint)*(ushort *)(puVar2 + 2),*(ushort *)puVar2 + 0x94,
               *(ushort *)(puVar2 + 2) + 0xea);
  iVar14 = Start_Of_Screen_Mem;
  iVar18 = Screen_Frame_Buffer;
  uVar6 = (uint)*(ushort *)(puVar2 + 2);
  uVar11 = (uint)*(ushort *)puVar2;
  uVar7 = uVar6 + 0xeb & 0xfffeffff;
  if (uVar6 < uVar7) {
    do {
      iVar12 = uVar11 + uVar6 * 800;
      copy_short((void *)(iVar14 + iVar12 * 2),(void *)(iVar18 + iVar12 * 2),
                 ((uVar11 + 0x94 & 0xfffeffff) - uVar11) + 1);
      uVar6 = uVar6 + 1;
    } while (uVar6 < uVar7);
    return;
  }
  return;
}


