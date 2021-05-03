void FUN_80010a30(void)

{
  int *piVar1;
  int iVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  int iVar6;
  int iVar7;
  undefined2 *puVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  short sVar12;
  undefined2 *puVar13;
  
  piVar1 = Global_Frame_Buffer_Pointer;
  iVar11 = *Global_Frame_Buffer_Pointer;
  uVar3 = FUN_800232b4(DAT_80010bc0);
  uVar4 = FUN_800232b4(DAT_80010bc4);
  set_screen_to_global_pointer();
  iVar2 = DAT_80010bc8;
  uVar10 = 0;
  do {
    memcpy((void *)(iVar2 + uVar10 * 0x640),(void *)(*piVar1 + uVar10 * 0x640),0x640);
    iVar6 = DAT_80010bcc;
    uVar10 = uVar10 + 1 & 0xfffeffff;
  } while (uVar10 < 0x1e0);
  uVar10 = 0xef;
  do {
    iVar7 = 0;
    sVar12 = 0x6e;
    puVar8 = (undefined2 *)(*piVar1 + uVar10 * 0x640 + 0x26c);
    do {
      uVar9 = *(uint *)(iVar6 + ((iVar7 + uVar10 * 0x6e) - 0x66b2 & 0xffff) * 4) & 0xffff;
      uVar5 = uVar3;
      if ((uVar9 != 0) && (uVar5 = (short)uVar9, uVar9 == 0xf800)) {
        uVar5 = uVar4;
      }
      sVar12 = sVar12 + -1;
      iVar7 = iVar7 + 1;
      *puVar8 = uVar5;
      puVar8 = puVar8 + 1;
    } while (sVar12 != 0);
    uVar10 = uVar10 + 1 & 0xfffeffff;
  } while (uVar10 < 0x11e);
  delay_2(500);
  uVar10 = 0xef;
  do {
    iVar6 = *piVar1;
    if ((iVar6 - iVar2 < 1) || (uVar9 = 0x136, 0x6d < iVar6 - iVar2)) {
      FUN_80000730(iVar6 + uVar10 * 0x640 + 0x26c,iVar2 + uVar10 * 0x640 + 0x26c,0xdc);
    }
    else {
      do {
        iVar7 = uVar9 + uVar10 * 800;
        puVar8 = (undefined2 *)(iVar2 + iVar7 * 2);
        puVar13 = (undefined2 *)(iVar6 + iVar7 * 2);
        uVar9 = uVar9 + 2 & 0xfffeffff;
        *puVar13 = *puVar8;
        puVar13[1] = puVar8[1];
      } while (uVar9 < 0x1a4);
    }
    uVar10 = uVar10 + 1 & 0xfffeffff;
  } while (uVar10 < 0x11e);
  *piVar1 = iVar11;
  return;
}

