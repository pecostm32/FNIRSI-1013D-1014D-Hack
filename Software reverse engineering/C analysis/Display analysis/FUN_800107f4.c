void FUN_800107f4(int param_1)

{
  int iVar1;
  ushort uVar2;
  undefined2 uVar3;
  undefined *puVar4;
  int *piVar5;
  ushort *puVar6;
  undefined2 *puVar7;
  ushort *puVar8;
  undefined2 *puVar9;
  uint uVar10;
  undefined *puVar11;
  undefined4 uVar12;
  int iVar13;
  
  set_screen_to_global_pointer();
  piVar5 = Global_Frame_Buffer_Pointer;
  puVar4 = PTR_DAT_8001093c;
  if (param_1 == 0) {
    uVar10 = 100;
    do {
      puVar11 = puVar4 + uVar10 * 0x118;
      puVar9 = (undefined2 *)(*piVar5 + uVar10 * 0x640 + 0x5c2);
      *puVar9 = *(undefined2 *)(puVar11 + 0x1c);
      uVar12 = *(undefined4 *)(puVar11 + 0x20);
      iVar13 = 0x1b;
      puVar7 = (undefined2 *)(puVar11 + 0x1c);
      do {
        uVar3 = puVar7[4];
        puVar9[1] = (short)uVar12;
        uVar12 = *(undefined4 *)(puVar7 + 6);
        iVar13 = iVar13 + -1;
        puVar9 = puVar9 + 2;
        *puVar9 = uVar3;
        puVar7 = puVar7 + 4;
      } while (iVar13 != 0);
      iVar13 = uVar10 * 800;
      iVar1 = uVar10 * 0x46;
      uVar10 = uVar10 + 1 & 0xfffeffff;
      *(undefined2 *)(*piVar5 + (iVar13 + 0x37) * 2 + 0x5c2) =
           *(undefined2 *)(puVar4 + (iVar1 + 0x37) * 4 + 0x1c);
    } while (uVar10 < 0x8c);
    return;
  }
  uVar10 = 100;
  do {
    puVar11 = puVar4 + uVar10 * 0x118;
    puVar8 = (ushort *)(*piVar5 + uVar10 * 0x640 + 0x5c2);
    *puVar8 = ~*(ushort *)(puVar11 + 0x1c);
    uVar12 = *(undefined4 *)(puVar11 + 0x20);
    iVar13 = 0x1b;
    puVar6 = (ushort *)(puVar11 + 0x1c);
    do {
      uVar2 = puVar6[4];
      puVar8[1] = ~(ushort)uVar12;
      iVar13 = iVar13 + -1;
      uVar12 = *(undefined4 *)(puVar6 + 6);
      puVar8 = puVar8 + 2;
      *puVar8 = ~uVar2;
      puVar6 = puVar6 + 4;
    } while (iVar13 != 0);
    iVar13 = uVar10 * 0x46;
    iVar1 = uVar10 * 800;
    uVar10 = uVar10 + 1 & 0xfffeffff;
    *(ushort *)(*piVar5 + (iVar1 + 0x37) * 2 + 0x5c2) =
         ~*(ushort *)(puVar4 + (iVar13 + 0x37) * 4 + 0x1c);
  } while (uVar10 < 0x8c);
  return;
}

