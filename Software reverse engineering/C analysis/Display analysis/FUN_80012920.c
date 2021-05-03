void FUN_80012920(int param_1)

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
  undefined4 uVar11;
  int iVar12;
  
  piVar5 = Global_Frame_Buffer_Pointer;
  puVar4 = PTR_DAT_80012a44;
  uVar10 = 0;
  if (param_1 == 0) {
    do {
      puVar7 = (undefined2 *)(puVar4 + uVar10 * 0x140);
      puVar9 = (undefined2 *)(*piVar5 + uVar10 * 0x640);
      iVar12 = 0x27;
      *puVar9 = *puVar7;
      uVar11 = *(undefined4 *)(puVar7 + 2);
      do {
        uVar3 = puVar7[4];
        puVar9[1] = (short)uVar11;
        uVar11 = *(undefined4 *)(puVar7 + 6);
        iVar12 = iVar12 + -1;
        puVar9 = puVar9 + 2;
        *puVar9 = uVar3;
        puVar7 = puVar7 + 4;
      } while (iVar12 != 0);
      iVar12 = uVar10 * 0x50;
      iVar1 = uVar10 * 800;
      uVar10 = uVar10 + 1 & 0xfffeffff;
      *(short *)(*piVar5 + (iVar1 + 0x4f) * 2) =
           (short)*(undefined4 *)(puVar4 + (iVar12 + 0x4f) * 4);
    } while (uVar10 < 0x28);
  }
  else {
    do {
      puVar6 = (ushort *)(puVar4 + uVar10 * 0x140);
      puVar8 = (ushort *)(*piVar5 + uVar10 * 0x640);
      *puVar8 = ~*puVar6;
      uVar11 = *(undefined4 *)(puVar6 + 2);
      iVar12 = 0x27;
      do {
        uVar2 = puVar6[4];
        puVar8[1] = ~(ushort)uVar11;
        iVar12 = iVar12 + -1;
        uVar11 = *(undefined4 *)(puVar6 + 6);
        puVar8 = puVar8 + 2;
        *puVar8 = ~uVar2;
        puVar6 = puVar6 + 4;
      } while (iVar12 != 0);
      iVar12 = uVar10 * 0x50;
      iVar1 = uVar10 * 800;
      uVar10 = uVar10 + 1 & 0xfffeffff;
      *(ushort *)(*piVar5 + (iVar1 + 0x4f) * 2) =
           ~(ushort)*(undefined4 *)(puVar4 + (iVar12 + 0x4f) * 4);
    } while (uVar10 < 0x28);
  }
  iVar1 = Start_Of_Screen_Mem;
  iVar12 = Screen_Frame_Buffer;
  uVar10 = 0;
  do {
    copy_short((void *)(iVar1 + uVar10 * 0x640),(void *)(iVar12 + uVar10 * 0x640),0x51);
    uVar10 = uVar10 + 1;
  } while (uVar10 < 0x28);
  return;
}


