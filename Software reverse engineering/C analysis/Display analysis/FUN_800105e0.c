void FUN_800105e0(void)

{
  int iVar1;
  undefined2 uVar2;
  undefined *puVar3;
  int *piVar4;
  undefined2 *puVar5;
  undefined2 *puVar6;
  uint uVar7;
  undefined4 uVar8;
  int iVar9;
  
  set_screen_to_global_pointer();
  set_display_color(0);
  display_clear_rect(0,0,0x2da,0x1e0);
  piVar4 = Global_Frame_Buffer_Pointer;
  puVar3 = PTR_DAT_8001069c;
  uVar7 = 0;
  do {
    puVar5 = (undefined2 *)(puVar3 + uVar7 * 0x118);
    puVar6 = (undefined2 *)(*piVar4 + uVar7 * 0x640 + 0x5b4);
    *puVar6 = *puVar5;
    uVar8 = *(undefined4 *)(puVar5 + 2);
    iVar9 = 0x22;
    do {
      uVar2 = puVar5[4];
      puVar6[1] = (short)uVar8;
      uVar8 = *(undefined4 *)(puVar5 + 6);
      iVar9 = iVar9 + -1;
      puVar6 = puVar6 + 2;
      *puVar6 = uVar2;
      puVar5 = puVar5 + 4;
    } while (iVar9 != 0);
    iVar9 = uVar7 * 800;
    iVar1 = uVar7 * 0x46;
    uVar7 = uVar7 + 1 & 0xfffeffff;
    *(short *)(*piVar4 + (iVar9 + 0x45) * 2 + 0x5b4) =
         (short)*(undefined4 *)(puVar3 + (iVar1 + 0x45) * 4);
  } while (uVar7 < 0x1e0);
  *Global_Frame_Buffer_Pointer = Screen_Frame_Buffer;
  return;
}

