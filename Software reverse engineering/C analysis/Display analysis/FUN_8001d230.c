void FUN_8001d230(uint param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  uint uVar2;
  undefined2 *puVar3;
  undefined2 *puVar4;
  int iVar5;
  int iVar6;
  undefined2 *puVar7;
  int iVar8;
  undefined2 *puVar9;
  
  iVar6 = Start_Of_Screen_Mem;
  iVar5 = Screen_Frame_Buffer_2;
  if (param_2 < param_4) {
    uVar1 = (param_3 - param_1) * 0x8000 >> 0x10;
    do {
      if (param_1 < param_3) {
        iVar8 = param_1 + param_2 * 800;
        puVar7 = (undefined2 *)(iVar5 + iVar8 * 2);
        puVar9 = (undefined2 *)(iVar6 + iVar8 * 2);
        uVar2 = uVar1;
        puVar3 = puVar9 + -1;
        puVar4 = puVar7 + -1;
        if ((param_3 - param_1 & 1) != 0) {
          *puVar9 = *puVar7;
          puVar3 = puVar9;
          puVar4 = puVar7;
        }
        while (uVar2 != 0) {
          puVar3[1] = puVar4[1];
          puVar3[2] = puVar4[2];
          uVar2 = uVar2 - 1 & 0xffff;
          puVar3 = puVar3 + 2;
          puVar4 = puVar4 + 2;
        }
      }
      param_2 = param_2 + 1 & 0xfffeffff;
    } while (param_2 < param_4);
    return;
  }
  return;
}

