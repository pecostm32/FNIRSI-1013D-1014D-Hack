int FUN_80022dd4(void)

{
  short sVar1;
  undefined *puVar2;
  int *piVar3;
  undefined *puVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  short sVar8;
  int iVar9;
  short *psVar10;
  short *psVar11;
  uint uVar12;
  longlong lVar13;
  
  puVar4 = PTR_DAT_80022fb4;
  piVar3 = Global_Frame_Buffer_Pointer;
  puVar2 = PTR_DAT_80022fac;
LAB_80022df0:
  while( true ) {
    do {
      iVar9 = FUN_800230a0();
    } while (iVar9 == 0);
    if (iVar9 == 1) {
      lVar13 = memset(DAT_80022fbc,0,number_of_pixels);
      *puVar4 = 1;
      puVar4[4] = 1;
      puVar4[5] = 0;
      return (int)lVar13;
    }
    if (iVar9 != 2) break;
    sVar8 = FUN_800232b4(DAT_80022fc0);
    sVar5 = FUN_800232b4(DAT_80022fc4);
    sVar6 = FUN_800232b4(DAT_80022fc8);
    set_screen_to_global_pointer();
    uVar12 = 0xc0;
    do {
      iVar9 = 0xb4;
      psVar10 = (short *)(*piVar3 + uVar12 * 0x640 + 0x226);
      psVar11 = (short *)(puVar2 + uVar12 * 0x2d0 + -0x21c00);
      do {
        sVar1 = *psVar11;
        sVar7 = sVar6;
        if (((sVar1 != 0) && (sVar7 = sVar8, sVar1 != -0x800)) && (sVar7 = sVar1, sVar1 == 0x7e0)) {
          sVar7 = sVar5;
        }
        iVar9 = iVar9 + -1;
        *psVar10 = sVar7;
        psVar10 = psVar10 + 1;
        psVar11 = psVar11 + 2;
      } while (iVar9 != 0);
      uVar12 = uVar12 + 1 & 0xfffeffff;
    } while (uVar12 < 0x121);
    do {
      iVar9 = FUN_80022fd0();
    } while (iVar9 == 2);
    if (iVar9 == 0) goto LAB_80022f64;
    FUN_8002c7a4();
    FUN_8000b2ac();
    iVar9 = DAT_80022fcc;
    FUN_8000bb04(*(undefined2 *)(DAT_80022fcc + (uint)*(ushort *)(puVar4 + 2) * 2 + 0x1e));
    FUN_80033ea4((uint)*(ushort *)(puVar4 + 2) * 0xf + iVar9 + 0x7ee);
    FUN_8002c8f4();
    FUN_800261b4();
    FUN_8002c7a4();
    FUN_8000b2ac();
    puVar4[4] = 1;
    puVar4[5] = 0;
    iVar9 = FUN_80022bc8();
    if (iVar9 != 0) {
      return iVar9;
    }
  }
  if (iVar9 == 3) {
    if (*(short *)(puVar4 + 2) == 0) goto LAB_80022df0;
    sVar8 = *(short *)(puVar4 + 2) + -1;
  }
  else {
    if (iVar9 != 4) {
      if (iVar9 == 5) {
        FUN_80022bc8();
      }
      goto LAB_80022df0;
    }
    if ((int)(*(byte *)(DAT_80022fcc + 0xc) - 1) <= (int)(uint)*(ushort *)(puVar4 + 2))
    goto LAB_80022df0;
    sVar8 = *(ushort *)(puVar4 + 2) + 1;
  }
  *(short *)(puVar4 + 2) = sVar8;
LAB_80022f64:
  puVar4[4] = 1;
  puVar4[5] = 0;
  FUN_80022bc8();
  goto LAB_80022df0;
}

