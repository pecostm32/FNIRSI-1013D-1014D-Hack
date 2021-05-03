void FUN_80002810(undefined4 param_1)

{
  undefined *puVar1;
  int *piVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  undefined auStack584 [552];
  
  puVar1 = DAT_80002adc;
  *DAT_80002adc = 0x42;
  puVar1[1] = 0x4d;
  puVar1[2] = 0xf8;
  puVar1[3] = 0x5f;
  puVar1[4] = 0xc;
  puVar1[5] = 0;
  puVar1[6] = 0;
  puVar1[7] = 0;
  puVar1[8] = 0;
  uVar4 = DAT_80002ae0;
  puVar1[9] = 0;
  uVar4 = get_setting(0xf,uVar4);
  if (uVar4 == 0) {
    uVar4 = DAT_80002ae4;
  }
  puVar1[0xd] = (char)(uVar4 >> 0x18);
  puVar1[0xc] = (char)(uVar4 >> 0x10);
  puVar1[0xb] = (char)(uVar4 >> 8);
  puVar1[10] = (char)uVar4;
  puVar1[0xe] = 0x28;
  puVar1[0xf] = 0;
  puVar1[0x10] = 0;
  puVar1[0x11] = 0;
  puVar1[0x12] = 0x20;
  puVar1[0x13] = 3;
  puVar1[0x14] = 0;
  puVar1[0x15] = 0;
  puVar1[0x16] = 0xe0;
  puVar1[0x17] = 1;
  puVar1[0x18] = 0;
  puVar1[0x19] = 0;
  puVar1[0x1a] = 1;
  puVar1[0x1b] = 0;
  puVar1[0x1c] = 0x10;
  puVar1[0x1d] = 0;
  puVar1[0x1e] = 3;
  puVar1[0x1f] = 0;
  puVar1[0x20] = 0;
  puVar1[0x21] = 0;
  puVar1[0x22] = 0;
  puVar1[0x23] = 0xb8;
  puVar1[0x24] = 0xb;
  puVar1[0x25] = 0;
  puVar1[0x26] = 0;
  puVar1[0x27] = 0;
  puVar1[0x28] = 0;
  puVar1[0x29] = 0;
  puVar1[0x2a] = 0;
  puVar1[0x2b] = 0;
  puVar1[0x2c] = 0;
  puVar1[0x2d] = 0;
  puVar1[0x2e] = 0;
  puVar1[0x2f] = 0;
  puVar1[0x30] = 0;
  puVar1[0x31] = 0;
  puVar1[0x32] = 0;
  puVar1[0x33] = 0;
  puVar1[0x34] = 0;
  puVar1[0x35] = 0;
  puVar1[0x36] = 0;
  puVar1[0x37] = 0xf8;
  puVar1[0x38] = 0;
  puVar1[0x39] = 0;
  puVar1[0x3a] = 0xe0;
  puVar1[0x3b] = 7;
  puVar1[0x3c] = 0;
  puVar1[0x3d] = 0;
  puVar1[0x3e] = 0x1f;
  puVar1[0x3f] = 0;
  puVar1[0x40] = 0;
  puVar1[0x41] = 0;
  puVar1[0x42] = 0;
  puVar1[0x43] = 0;
  puVar1[0x44] = 0;
  puVar1[0x45] = 0;
  FUN_800019fc(DAT_80002ae8);
  memcpy(puVar1 + 0x46,DAT_80002ae8,DAT_80002aec);
  set_screen_to_global_pointer();
  piVar2 = Global_Frame_Buffer_Pointer;
  iVar5 = DAT_80002af0;
  uVar4 = 0;
  do {
    memcpy(puVar1 + uVar4 * 0x640 + 20000,(void *)(*piVar2 + (iVar5 - uVar4) * 0x640),0x640);
    uVar4 = uVar4 + 1 & 0xfffeffff;
  } while (uVar4 < 0x1e0);
  iVar5 = FUN_800337c4(auStack584,param_1,7);
  if (iVar5 != 0) {
    FUN_8003347c(auStack584);
    iVar5 = FUN_800337c4(auStack584,param_1,7);
    if (iVar5 != 0) {
      FUN_8003347c(auStack584);
      FUN_800337c4(auStack584,param_1,7);
    }
  }
  FUN_800334ac(auStack584,0);
  uVar3 = DAT_80002af8;
  iVar5 = FUN_80034074(auStack584,DAT_80002adc,DAT_80002af8,0);
  if (iVar5 != 0) {
    FUN_800334ac(auStack584,0);
    iVar5 = FUN_80034074(auStack584,DAT_80002adc,uVar3,0);
    if (iVar5 != 0) {
      FUN_800334ac(auStack584,0);
      FUN_80034074(auStack584,DAT_80002adc,uVar3,0);
    }
  }
  FUN_8003347c(auStack584);
  return;
}

