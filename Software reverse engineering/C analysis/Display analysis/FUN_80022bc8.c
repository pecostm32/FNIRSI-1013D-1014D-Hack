void FUN_80022bc8(void)

{
  short sVar1;
  undefined *puVar2;
  int *piVar3;
  ushort uVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  int iVar8;
  short *psVar9;
  short *psVar10;
  int iVar11;
  uint uVar12;
  code *in_lr;
  undefined auStack576 [556];
  code *UNRECOVERED_JUMPTABLE_00;
  
  iVar11 = DAT_80022dac;
  puVar2 = PTR_DAT_80022da8;
  uVar4 = *(ushort *)(PTR_DAT_80022da8 + 2);
  if (*(byte *)(DAT_80022dac + 0xc) <= uVar4) {
    if (uVar4 == 0) {
      return;
    }
    uVar4 = uVar4 - 1;
    *(ushort *)(PTR_DAT_80022da8 + 2) = uVar4;
  }
  UNRECOVERED_JUMPTABLE_00 = in_lr;
  iVar8 = FUN_800337c4(auStack576,(uint)uVar4 * 0xf + iVar11 + 0x7ee,1);
  if (iVar8 != 4) {
    FUN_800334ac(auStack576,0x46);
    FUN_80033b18(auStack576,DAT_80022db4,DAT_80022db0,0);
    FUN_8003347c(auStack576);
    iVar11 = DAT_80022db8;
    *(undefined *)(DAT_80022db8 + 0x43) = 0;
    FUN_80001358(DAT_80022db4);
    *(undefined *)(iVar11 + 0x18) = 1;
    *(undefined *)(iVar11 + 0x17) = 1;
    FUN_8001d4ec(DAT_80022dbc);
    delay_2(0xf);
    set_frame_to_global_pointer();
    FUN_8000e8f0();
    set_frame_to_global_pointer();
    FUN_8002b68c();
    if (*puVar2 != '\0') {
      sVar5 = FUN_800232b4(0);
      sVar6 = FUN_800232b4(DAT_80022dc0);
      set_screen_to_global_pointer();
      piVar3 = Global_Frame_Buffer_Pointer;
      puVar2 = PTR_DAT_80022dc4;
      uVar12 = 0x1a4;
      do {
        iVar11 = 800;
        psVar9 = (short *)(*piVar3 + uVar12 * 0x640);
        psVar10 = (short *)(puVar2 + uVar12 * 0xc80 + -0x148200);
        do {
          sVar1 = *psVar10;
          sVar7 = sVar6;
          if ((sVar1 != 0) && (sVar7 = sVar1, sVar1 == -0x800)) {
            sVar7 = sVar5;
          }
          iVar11 = iVar11 + -1;
          *psVar9 = sVar7;
          psVar9 = psVar9 + 1;
          psVar10 = psVar10 + 2;
        } while (iVar11 != 0);
        uVar12 = uVar12 + 1 & 0xfffeffff;
      } while (uVar12 < 0x1e0);
      set_frame_to_global_pointer();
    }
    copy_short(DAT_80022dbc,Start_Of_Screen_Mem,number_of_pixels);
    FUN_8001d4ec(Start_Of_Screen_Mem);
                    // WARNING: Could not recover jumptable at 0x80022d4c. Too many branches
                    // WARNING: Treating indirect jump as call
    (*UNRECOVERED_JUMPTABLE_00)(0);
    return;
  }
  FUN_8002c7a4();
  FUN_8000b2ac();
  FUN_8000bb04(*(undefined2 *)(iVar11 + (uint)*(ushort *)(puVar2 + 2) * 2 + 0x1e));
  FUN_80033ea4((uint)*(ushort *)(puVar2 + 2) * 0xf + iVar11 + 0x7ee);
  FUN_8002c8f4();
  FUN_800261b4();
  FUN_8002c7a4();
  FUN_8000b2ac();
  FUN_8003347c(auStack576);
                    // WARNING: Could not recover jumptable at 0x80022da4. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE_00)(1);
  return;
}

