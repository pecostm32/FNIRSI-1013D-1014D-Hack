#include "SPL_c.h"



void Reset(void)

{
  undefined *puVar1;
  uint uVar2;
  undefined4 uVar3;
  code *UNRECOVERED_JUMPTABLE;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  
  puVar1 = PTR_DAT_0000008c;
  uVar2 = coproc_movefrom_Control();
  coproc_moveto_Control(uVar2 & 0xffffdfff);
  uVar2 = coproc_movefrom_Control();
  puVar10 = (undefined4 *)PTR_H_Reset_00000090;
  if ((uVar2 & 0x2000) == 0) {
    puVar10 = (undefined4 *)0x0;
  }
  uVar3 = *(undefined4 *)(PTR_DAT_0000008c + 4);
  uVar4 = *(undefined4 *)(PTR_DAT_0000008c + 8);
  uVar5 = *(undefined4 *)(PTR_DAT_0000008c + 0xc);
  uVar6 = *(undefined4 *)(PTR_DAT_0000008c + 0x10);
  uVar7 = *(undefined4 *)(PTR_DAT_0000008c + 0x14);
  uVar8 = *(undefined4 *)(PTR_DAT_0000008c + 0x18);
  uVar9 = *(undefined4 *)(PTR_DAT_0000008c + 0x1c);
  puVar11 = (undefined4 *)(PTR_DAT_0000008c + 0x20);
  *puVar10 = *(undefined4 *)PTR_DAT_0000008c;
  puVar10[1] = uVar3;
  puVar10[2] = uVar4;
  puVar10[3] = uVar5;
  puVar10[4] = uVar6;
  puVar10[5] = uVar7;
  puVar10[6] = uVar8;
  puVar10[7] = uVar9;
  uVar3 = *(undefined4 *)(puVar1 + 0x24);
  uVar4 = *(undefined4 *)(puVar1 + 0x28);
  uVar5 = *(undefined4 *)(puVar1 + 0x2c);
  uVar6 = *(undefined4 *)(puVar1 + 0x30);
  uVar7 = *(undefined4 *)(puVar1 + 0x34);
  uVar8 = *(undefined4 *)(puVar1 + 0x38);
  uVar9 = *(undefined4 *)(puVar1 + 0x3c);
  puVar10[8] = *puVar11;
  puVar10[9] = uVar3;
  puVar10[10] = uVar4;
  puVar10[0xb] = uVar5;
  puVar10[0xc] = uVar6;
  puVar10[0xd] = uVar7;
  puVar10[0xe] = uVar8;
  puVar10[0xf] = uVar9;
  FUN_0000009c(puVar1 + 0x40,puVar10 + 0x10);
  FUN_0000010c();
  puVar1 = PTR_FUN_000000d0;
  puVar10 = (undefined4 *)(PTR_FUN_000000d0 + 0xd0);
  if (puVar10 == (undefined4 *)(DAT_000000d4 + 0xd0)) {
    FUN_0000010c();
  }
  UNRECOVERED_JUMPTABLE = *(code **)(puVar1 + 0xdc);
                    // WARNING: Could not recover jumptable at 0x000000c8. Too many branches
                    // WARNING: Treating indirect jump as call
  if (((uint)UNRECOVERED_JUMPTABLE & 1) != 0) {
    (*(code *)(puVar1 + (0xcf - (int)UNRECOVERED_JUMPTABLE)))();
    return;
  }
                    // WARNING: Could not recover jumptable at 0x000000cc. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE)(*puVar10,*(undefined4 *)(puVar1 + 0xd4),*(undefined4 *)(puVar1 + 0xd8));
  return;
}



void UndefinedInstruction(void)

{
  undefined *puVar1;
  uint uVar2;
  undefined4 uVar3;
  code *UNRECOVERED_JUMPTABLE;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  
  puVar1 = PTR_DAT_0000008c;
  uVar2 = coproc_movefrom_Control();
  coproc_moveto_Control(uVar2 & 0xffffdfff);
  uVar2 = coproc_movefrom_Control();
  puVar10 = (undefined4 *)PTR_H_Reset_00000090;
  if ((uVar2 & 0x2000) == 0) {
    puVar10 = (undefined4 *)0x0;
  }
  uVar3 = *(undefined4 *)(PTR_DAT_0000008c + 4);
  uVar4 = *(undefined4 *)(PTR_DAT_0000008c + 8);
  uVar5 = *(undefined4 *)(PTR_DAT_0000008c + 0xc);
  uVar6 = *(undefined4 *)(PTR_DAT_0000008c + 0x10);
  uVar7 = *(undefined4 *)(PTR_DAT_0000008c + 0x14);
  uVar8 = *(undefined4 *)(PTR_DAT_0000008c + 0x18);
  uVar9 = *(undefined4 *)(PTR_DAT_0000008c + 0x1c);
  puVar11 = (undefined4 *)(PTR_DAT_0000008c + 0x20);
  *puVar10 = *(undefined4 *)PTR_DAT_0000008c;
  puVar10[1] = uVar3;
  puVar10[2] = uVar4;
  puVar10[3] = uVar5;
  puVar10[4] = uVar6;
  puVar10[5] = uVar7;
  puVar10[6] = uVar8;
  puVar10[7] = uVar9;
  uVar3 = *(undefined4 *)(puVar1 + 0x24);
  uVar4 = *(undefined4 *)(puVar1 + 0x28);
  uVar5 = *(undefined4 *)(puVar1 + 0x2c);
  uVar6 = *(undefined4 *)(puVar1 + 0x30);
  uVar7 = *(undefined4 *)(puVar1 + 0x34);
  uVar8 = *(undefined4 *)(puVar1 + 0x38);
  uVar9 = *(undefined4 *)(puVar1 + 0x3c);
  puVar10[8] = *puVar11;
  puVar10[9] = uVar3;
  puVar10[10] = uVar4;
  puVar10[0xb] = uVar5;
  puVar10[0xc] = uVar6;
  puVar10[0xd] = uVar7;
  puVar10[0xe] = uVar8;
  puVar10[0xf] = uVar9;
  FUN_0000009c(puVar1 + 0x40,puVar10 + 0x10);
  FUN_0000010c();
  puVar1 = PTR_FUN_000000d0;
  puVar10 = (undefined4 *)(PTR_FUN_000000d0 + 0xd0);
  if (puVar10 == (undefined4 *)(DAT_000000d4 + 0xd0)) {
    FUN_0000010c();
  }
  UNRECOVERED_JUMPTABLE = *(code **)(puVar1 + 0xdc);
                    // WARNING: Could not recover jumptable at 0x000000c8. Too many branches
                    // WARNING: Treating indirect jump as call
  if (((uint)UNRECOVERED_JUMPTABLE & 1) != 0) {
    (*(code *)(puVar1 + (0xcf - (int)UNRECOVERED_JUMPTABLE)))();
    return;
  }
                    // WARNING: Could not recover jumptable at 0x000000cc. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE)(*puVar10,*(undefined4 *)(puVar1 + 0xd4),*(undefined4 *)(puVar1 + 0xd8));
  return;
}



void SupervisorCall(void)

{
  undefined *puVar1;
  uint uVar2;
  undefined4 uVar3;
  code *UNRECOVERED_JUMPTABLE;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  
  puVar1 = PTR_DAT_0000008c;
  uVar2 = coproc_movefrom_Control();
  coproc_moveto_Control(uVar2 & 0xffffdfff);
  uVar2 = coproc_movefrom_Control();
  puVar10 = (undefined4 *)PTR_H_Reset_00000090;
  if ((uVar2 & 0x2000) == 0) {
    puVar10 = (undefined4 *)0x0;
  }
  uVar3 = *(undefined4 *)(PTR_DAT_0000008c + 4);
  uVar4 = *(undefined4 *)(PTR_DAT_0000008c + 8);
  uVar5 = *(undefined4 *)(PTR_DAT_0000008c + 0xc);
  uVar6 = *(undefined4 *)(PTR_DAT_0000008c + 0x10);
  uVar7 = *(undefined4 *)(PTR_DAT_0000008c + 0x14);
  uVar8 = *(undefined4 *)(PTR_DAT_0000008c + 0x18);
  uVar9 = *(undefined4 *)(PTR_DAT_0000008c + 0x1c);
  puVar11 = (undefined4 *)(PTR_DAT_0000008c + 0x20);
  *puVar10 = *(undefined4 *)PTR_DAT_0000008c;
  puVar10[1] = uVar3;
  puVar10[2] = uVar4;
  puVar10[3] = uVar5;
  puVar10[4] = uVar6;
  puVar10[5] = uVar7;
  puVar10[6] = uVar8;
  puVar10[7] = uVar9;
  uVar3 = *(undefined4 *)(puVar1 + 0x24);
  uVar4 = *(undefined4 *)(puVar1 + 0x28);
  uVar5 = *(undefined4 *)(puVar1 + 0x2c);
  uVar6 = *(undefined4 *)(puVar1 + 0x30);
  uVar7 = *(undefined4 *)(puVar1 + 0x34);
  uVar8 = *(undefined4 *)(puVar1 + 0x38);
  uVar9 = *(undefined4 *)(puVar1 + 0x3c);
  puVar10[8] = *puVar11;
  puVar10[9] = uVar3;
  puVar10[10] = uVar4;
  puVar10[0xb] = uVar5;
  puVar10[0xc] = uVar6;
  puVar10[0xd] = uVar7;
  puVar10[0xe] = uVar8;
  puVar10[0xf] = uVar9;
  FUN_0000009c(puVar1 + 0x40,puVar10 + 0x10);
  FUN_0000010c();
  puVar1 = PTR_FUN_000000d0;
  puVar10 = (undefined4 *)(PTR_FUN_000000d0 + 0xd0);
  if (puVar10 == (undefined4 *)(DAT_000000d4 + 0xd0)) {
    FUN_0000010c();
  }
  UNRECOVERED_JUMPTABLE = *(code **)(puVar1 + 0xdc);
                    // WARNING: Could not recover jumptable at 0x000000c8. Too many branches
                    // WARNING: Treating indirect jump as call
  if (((uint)UNRECOVERED_JUMPTABLE & 1) != 0) {
    (*(code *)(puVar1 + (0xcf - (int)UNRECOVERED_JUMPTABLE)))();
    return;
  }
                    // WARNING: Could not recover jumptable at 0x000000cc. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE)(*puVar10,*(undefined4 *)(puVar1 + 0xd4),*(undefined4 *)(puVar1 + 0xd8));
  return;
}



void PrefetchAbort(void)

{
  undefined *puVar1;
  uint uVar2;
  undefined4 uVar3;
  code *UNRECOVERED_JUMPTABLE;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  
  puVar1 = PTR_DAT_0000008c;
  uVar2 = coproc_movefrom_Control();
  coproc_moveto_Control(uVar2 & 0xffffdfff);
  uVar2 = coproc_movefrom_Control();
  puVar10 = (undefined4 *)PTR_H_Reset_00000090;
  if ((uVar2 & 0x2000) == 0) {
    puVar10 = (undefined4 *)0x0;
  }
  uVar3 = *(undefined4 *)(PTR_DAT_0000008c + 4);
  uVar4 = *(undefined4 *)(PTR_DAT_0000008c + 8);
  uVar5 = *(undefined4 *)(PTR_DAT_0000008c + 0xc);
  uVar6 = *(undefined4 *)(PTR_DAT_0000008c + 0x10);
  uVar7 = *(undefined4 *)(PTR_DAT_0000008c + 0x14);
  uVar8 = *(undefined4 *)(PTR_DAT_0000008c + 0x18);
  uVar9 = *(undefined4 *)(PTR_DAT_0000008c + 0x1c);
  puVar11 = (undefined4 *)(PTR_DAT_0000008c + 0x20);
  *puVar10 = *(undefined4 *)PTR_DAT_0000008c;
  puVar10[1] = uVar3;
  puVar10[2] = uVar4;
  puVar10[3] = uVar5;
  puVar10[4] = uVar6;
  puVar10[5] = uVar7;
  puVar10[6] = uVar8;
  puVar10[7] = uVar9;
  uVar3 = *(undefined4 *)(puVar1 + 0x24);
  uVar4 = *(undefined4 *)(puVar1 + 0x28);
  uVar5 = *(undefined4 *)(puVar1 + 0x2c);
  uVar6 = *(undefined4 *)(puVar1 + 0x30);
  uVar7 = *(undefined4 *)(puVar1 + 0x34);
  uVar8 = *(undefined4 *)(puVar1 + 0x38);
  uVar9 = *(undefined4 *)(puVar1 + 0x3c);
  puVar10[8] = *puVar11;
  puVar10[9] = uVar3;
  puVar10[10] = uVar4;
  puVar10[0xb] = uVar5;
  puVar10[0xc] = uVar6;
  puVar10[0xd] = uVar7;
  puVar10[0xe] = uVar8;
  puVar10[0xf] = uVar9;
  FUN_0000009c(puVar1 + 0x40,puVar10 + 0x10);
  FUN_0000010c();
  puVar1 = PTR_FUN_000000d0;
  puVar10 = (undefined4 *)(PTR_FUN_000000d0 + 0xd0);
  if (puVar10 == (undefined4 *)(DAT_000000d4 + 0xd0)) {
    FUN_0000010c();
  }
  UNRECOVERED_JUMPTABLE = *(code **)(puVar1 + 0xdc);
                    // WARNING: Could not recover jumptable at 0x000000c8. Too many branches
                    // WARNING: Treating indirect jump as call
  if (((uint)UNRECOVERED_JUMPTABLE & 1) != 0) {
    (*(code *)(puVar1 + (0xcf - (int)UNRECOVERED_JUMPTABLE)))();
    return;
  }
                    // WARNING: Could not recover jumptable at 0x000000cc. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE)(*puVar10,*(undefined4 *)(puVar1 + 0xd4),*(undefined4 *)(puVar1 + 0xd8));
  return;
}



void DataAbort(void)

{
  undefined *puVar1;
  uint uVar2;
  undefined4 uVar3;
  code *UNRECOVERED_JUMPTABLE;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  
  puVar1 = PTR_DAT_0000008c;
  uVar2 = coproc_movefrom_Control();
  coproc_moveto_Control(uVar2 & 0xffffdfff);
  uVar2 = coproc_movefrom_Control();
  puVar10 = (undefined4 *)PTR_H_Reset_00000090;
  if ((uVar2 & 0x2000) == 0) {
    puVar10 = (undefined4 *)0x0;
  }
  uVar3 = *(undefined4 *)(PTR_DAT_0000008c + 4);
  uVar4 = *(undefined4 *)(PTR_DAT_0000008c + 8);
  uVar5 = *(undefined4 *)(PTR_DAT_0000008c + 0xc);
  uVar6 = *(undefined4 *)(PTR_DAT_0000008c + 0x10);
  uVar7 = *(undefined4 *)(PTR_DAT_0000008c + 0x14);
  uVar8 = *(undefined4 *)(PTR_DAT_0000008c + 0x18);
  uVar9 = *(undefined4 *)(PTR_DAT_0000008c + 0x1c);
  puVar11 = (undefined4 *)(PTR_DAT_0000008c + 0x20);
  *puVar10 = *(undefined4 *)PTR_DAT_0000008c;
  puVar10[1] = uVar3;
  puVar10[2] = uVar4;
  puVar10[3] = uVar5;
  puVar10[4] = uVar6;
  puVar10[5] = uVar7;
  puVar10[6] = uVar8;
  puVar10[7] = uVar9;
  uVar3 = *(undefined4 *)(puVar1 + 0x24);
  uVar4 = *(undefined4 *)(puVar1 + 0x28);
  uVar5 = *(undefined4 *)(puVar1 + 0x2c);
  uVar6 = *(undefined4 *)(puVar1 + 0x30);
  uVar7 = *(undefined4 *)(puVar1 + 0x34);
  uVar8 = *(undefined4 *)(puVar1 + 0x38);
  uVar9 = *(undefined4 *)(puVar1 + 0x3c);
  puVar10[8] = *puVar11;
  puVar10[9] = uVar3;
  puVar10[10] = uVar4;
  puVar10[0xb] = uVar5;
  puVar10[0xc] = uVar6;
  puVar10[0xd] = uVar7;
  puVar10[0xe] = uVar8;
  puVar10[0xf] = uVar9;
  FUN_0000009c(puVar1 + 0x40,puVar10 + 0x10);
  FUN_0000010c();
  puVar1 = PTR_FUN_000000d0;
  puVar10 = (undefined4 *)(PTR_FUN_000000d0 + 0xd0);
  if (puVar10 == (undefined4 *)(DAT_000000d4 + 0xd0)) {
    FUN_0000010c();
  }
  UNRECOVERED_JUMPTABLE = *(code **)(puVar1 + 0xdc);
                    // WARNING: Could not recover jumptable at 0x000000c8. Too many branches
                    // WARNING: Treating indirect jump as call
  if (((uint)UNRECOVERED_JUMPTABLE & 1) != 0) {
    (*(code *)(puVar1 + (0xcf - (int)UNRECOVERED_JUMPTABLE)))();
    return;
  }
                    // WARNING: Could not recover jumptable at 0x000000cc. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE)(*puVar10,*(undefined4 *)(puVar1 + 0xd4),*(undefined4 *)(puVar1 + 0xd8));
  return;
}



void NotUsed(void)

{
  undefined *puVar1;
  uint uVar2;
  undefined4 uVar3;
  code *UNRECOVERED_JUMPTABLE;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  
  puVar1 = PTR_DAT_0000008c;
  uVar2 = coproc_movefrom_Control();
  coproc_moveto_Control(uVar2 & 0xffffdfff);
  uVar2 = coproc_movefrom_Control();
  puVar10 = (undefined4 *)PTR_H_Reset_00000090;
  if ((uVar2 & 0x2000) == 0) {
    puVar10 = (undefined4 *)0x0;
  }
  uVar3 = *(undefined4 *)(PTR_DAT_0000008c + 4);
  uVar4 = *(undefined4 *)(PTR_DAT_0000008c + 8);
  uVar5 = *(undefined4 *)(PTR_DAT_0000008c + 0xc);
  uVar6 = *(undefined4 *)(PTR_DAT_0000008c + 0x10);
  uVar7 = *(undefined4 *)(PTR_DAT_0000008c + 0x14);
  uVar8 = *(undefined4 *)(PTR_DAT_0000008c + 0x18);
  uVar9 = *(undefined4 *)(PTR_DAT_0000008c + 0x1c);
  puVar11 = (undefined4 *)(PTR_DAT_0000008c + 0x20);
  *puVar10 = *(undefined4 *)PTR_DAT_0000008c;
  puVar10[1] = uVar3;
  puVar10[2] = uVar4;
  puVar10[3] = uVar5;
  puVar10[4] = uVar6;
  puVar10[5] = uVar7;
  puVar10[6] = uVar8;
  puVar10[7] = uVar9;
  uVar3 = *(undefined4 *)(puVar1 + 0x24);
  uVar4 = *(undefined4 *)(puVar1 + 0x28);
  uVar5 = *(undefined4 *)(puVar1 + 0x2c);
  uVar6 = *(undefined4 *)(puVar1 + 0x30);
  uVar7 = *(undefined4 *)(puVar1 + 0x34);
  uVar8 = *(undefined4 *)(puVar1 + 0x38);
  uVar9 = *(undefined4 *)(puVar1 + 0x3c);
  puVar10[8] = *puVar11;
  puVar10[9] = uVar3;
  puVar10[10] = uVar4;
  puVar10[0xb] = uVar5;
  puVar10[0xc] = uVar6;
  puVar10[0xd] = uVar7;
  puVar10[0xe] = uVar8;
  puVar10[0xf] = uVar9;
  FUN_0000009c(puVar1 + 0x40,puVar10 + 0x10);
  FUN_0000010c();
  puVar1 = PTR_FUN_000000d0;
  puVar10 = (undefined4 *)(PTR_FUN_000000d0 + 0xd0);
  if (puVar10 == (undefined4 *)(DAT_000000d4 + 0xd0)) {
    FUN_0000010c();
  }
  UNRECOVERED_JUMPTABLE = *(code **)(puVar1 + 0xdc);
                    // WARNING: Could not recover jumptable at 0x000000c8. Too many branches
                    // WARNING: Treating indirect jump as call
  if (((uint)UNRECOVERED_JUMPTABLE & 1) != 0) {
    (*(code *)(puVar1 + (0xcf - (int)UNRECOVERED_JUMPTABLE)))();
    return;
  }
                    // WARNING: Could not recover jumptable at 0x000000cc. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE)(*puVar10,*(undefined4 *)(puVar1 + 0xd4),*(undefined4 *)(puVar1 + 0xd8));
  return;
}



void IRQ(void)

{
  undefined *puVar1;
  uint uVar2;
  undefined4 uVar3;
  code *UNRECOVERED_JUMPTABLE;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  
  puVar1 = PTR_DAT_0000008c;
  uVar2 = coproc_movefrom_Control();
  coproc_moveto_Control(uVar2 & 0xffffdfff);
  uVar2 = coproc_movefrom_Control();
  puVar10 = (undefined4 *)PTR_H_Reset_00000090;
  if ((uVar2 & 0x2000) == 0) {
    puVar10 = (undefined4 *)0x0;
  }
  uVar3 = *(undefined4 *)(PTR_DAT_0000008c + 4);
  uVar4 = *(undefined4 *)(PTR_DAT_0000008c + 8);
  uVar5 = *(undefined4 *)(PTR_DAT_0000008c + 0xc);
  uVar6 = *(undefined4 *)(PTR_DAT_0000008c + 0x10);
  uVar7 = *(undefined4 *)(PTR_DAT_0000008c + 0x14);
  uVar8 = *(undefined4 *)(PTR_DAT_0000008c + 0x18);
  uVar9 = *(undefined4 *)(PTR_DAT_0000008c + 0x1c);
  puVar11 = (undefined4 *)(PTR_DAT_0000008c + 0x20);
  *puVar10 = *(undefined4 *)PTR_DAT_0000008c;
  puVar10[1] = uVar3;
  puVar10[2] = uVar4;
  puVar10[3] = uVar5;
  puVar10[4] = uVar6;
  puVar10[5] = uVar7;
  puVar10[6] = uVar8;
  puVar10[7] = uVar9;
  uVar3 = *(undefined4 *)(puVar1 + 0x24);
  uVar4 = *(undefined4 *)(puVar1 + 0x28);
  uVar5 = *(undefined4 *)(puVar1 + 0x2c);
  uVar6 = *(undefined4 *)(puVar1 + 0x30);
  uVar7 = *(undefined4 *)(puVar1 + 0x34);
  uVar8 = *(undefined4 *)(puVar1 + 0x38);
  uVar9 = *(undefined4 *)(puVar1 + 0x3c);
  puVar10[8] = *puVar11;
  puVar10[9] = uVar3;
  puVar10[10] = uVar4;
  puVar10[0xb] = uVar5;
  puVar10[0xc] = uVar6;
  puVar10[0xd] = uVar7;
  puVar10[0xe] = uVar8;
  puVar10[0xf] = uVar9;
  FUN_0000009c(puVar1 + 0x40,puVar10 + 0x10);
  FUN_0000010c();
  puVar1 = PTR_FUN_000000d0;
  puVar10 = (undefined4 *)(PTR_FUN_000000d0 + 0xd0);
  if (puVar10 == (undefined4 *)(DAT_000000d4 + 0xd0)) {
    FUN_0000010c();
  }
  UNRECOVERED_JUMPTABLE = *(code **)(puVar1 + 0xdc);
                    // WARNING: Could not recover jumptable at 0x000000c8. Too many branches
                    // WARNING: Treating indirect jump as call
  if (((uint)UNRECOVERED_JUMPTABLE & 1) != 0) {
    (*(code *)(puVar1 + (0xcf - (int)UNRECOVERED_JUMPTABLE)))();
    return;
  }
                    // WARNING: Could not recover jumptable at 0x000000cc. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE)(*puVar10,*(undefined4 *)(puVar1 + 0xd4),*(undefined4 *)(puVar1 + 0xd8));
  return;
}



void FIQ(void)

{
  undefined *puVar1;
  uint uVar2;
  undefined4 uVar3;
  code *UNRECOVERED_JUMPTABLE;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  
  puVar1 = PTR_DAT_0000008c;
  uVar2 = coproc_movefrom_Control();
  coproc_moveto_Control(uVar2 & 0xffffdfff);
  uVar2 = coproc_movefrom_Control();
  puVar10 = (undefined4 *)PTR_H_Reset_00000090;
  if ((uVar2 & 0x2000) == 0) {
    puVar10 = (undefined4 *)0x0;
  }
  uVar3 = *(undefined4 *)(PTR_DAT_0000008c + 4);
  uVar4 = *(undefined4 *)(PTR_DAT_0000008c + 8);
  uVar5 = *(undefined4 *)(PTR_DAT_0000008c + 0xc);
  uVar6 = *(undefined4 *)(PTR_DAT_0000008c + 0x10);
  uVar7 = *(undefined4 *)(PTR_DAT_0000008c + 0x14);
  uVar8 = *(undefined4 *)(PTR_DAT_0000008c + 0x18);
  uVar9 = *(undefined4 *)(PTR_DAT_0000008c + 0x1c);
  puVar11 = (undefined4 *)(PTR_DAT_0000008c + 0x20);
  *puVar10 = *(undefined4 *)PTR_DAT_0000008c;
  puVar10[1] = uVar3;
  puVar10[2] = uVar4;
  puVar10[3] = uVar5;
  puVar10[4] = uVar6;
  puVar10[5] = uVar7;
  puVar10[6] = uVar8;
  puVar10[7] = uVar9;
  uVar3 = *(undefined4 *)(puVar1 + 0x24);
  uVar4 = *(undefined4 *)(puVar1 + 0x28);
  uVar5 = *(undefined4 *)(puVar1 + 0x2c);
  uVar6 = *(undefined4 *)(puVar1 + 0x30);
  uVar7 = *(undefined4 *)(puVar1 + 0x34);
  uVar8 = *(undefined4 *)(puVar1 + 0x38);
  uVar9 = *(undefined4 *)(puVar1 + 0x3c);
  puVar10[8] = *puVar11;
  puVar10[9] = uVar3;
  puVar10[10] = uVar4;
  puVar10[0xb] = uVar5;
  puVar10[0xc] = uVar6;
  puVar10[0xd] = uVar7;
  puVar10[0xe] = uVar8;
  puVar10[0xf] = uVar9;
  FUN_0000009c(puVar1 + 0x40,puVar10 + 0x10);
  FUN_0000010c();
  puVar1 = PTR_FUN_000000d0;
  puVar10 = (undefined4 *)(PTR_FUN_000000d0 + 0xd0);
  if (puVar10 == (undefined4 *)(DAT_000000d4 + 0xd0)) {
    FUN_0000010c();
  }
  UNRECOVERED_JUMPTABLE = *(code **)(puVar1 + 0xdc);
                    // WARNING: Could not recover jumptable at 0x000000c8. Too many branches
                    // WARNING: Treating indirect jump as call
  if (((uint)UNRECOVERED_JUMPTABLE & 1) != 0) {
    (*(code *)(puVar1 + (0xcf - (int)UNRECOVERED_JUMPTABLE)))();
    return;
  }
                    // WARNING: Could not recover jumptable at 0x000000cc. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE)(*puVar10,*(undefined4 *)(puVar1 + 0xd4),*(undefined4 *)(puVar1 + 0xd8));
  return;
}



void FUN_0000009c(void)

{
  undefined *puVar1;
  code *UNRECOVERED_JUMPTABLE;
  undefined4 *puVar2;
  
  puVar1 = PTR_FUN_000000d0;
  puVar2 = (undefined4 *)(PTR_FUN_000000d0 + 0xd0);
  if (puVar2 == (undefined4 *)(DAT_000000d4 + 0xd0)) {
    FUN_0000010c();
  }
  UNRECOVERED_JUMPTABLE = *(code **)(puVar1 + 0xdc);
                    // WARNING: Could not recover jumptable at 0x000000c8. Too many branches
                    // WARNING: Treating indirect jump as call
  if (((uint)UNRECOVERED_JUMPTABLE & 1) != 0) {
    (*(code *)(puVar1 + (0xcf - (int)UNRECOVERED_JUMPTABLE)))();
    return;
  }
                    // WARNING: Could not recover jumptable at 0x000000cc. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE)(*puVar2,*(undefined4 *)(puVar1 + 0xd4),*(undefined4 *)(puVar1 + 0xd8));
  return;
}



undefined8 FUN_00000104(undefined4 param_1,undefined4 param_2)

{
  return CONCAT44(param_2,param_1);
}



void FUN_00000108(void)

{
  return;
}



// WARNING: Control flow encountered bad instruction data

void FUN_0000010c(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  uVar1 = FUN_00000768();
  FUN_00000104(uVar1,param_3);
  (*(code *)(DAT_0000013c + 0x124))();
  FUN_00002f38();
                    // WARNING: Bad instruction - Truncating control flow here
  halt_baddata();
}



void FUN_00000140(undefined4 param_1,undefined4 param_2)

{
  FUN_00000108();
  FUN_00000758(param_1,param_2);
  FUN_000017d8(DAT_00000724,0,0);
  FUN_000017d8(DAT_00000724,1,0);
  FUN_000017d8(DAT_00000724,2,0);
  FUN_000017d8(DAT_00000724,3,0);
  FUN_000017d8(DAT_00000724,4,0);
  FUN_000017d8(DAT_00000724,5,0);
  FUN_000017d8(DAT_00000724,6,0);
  FUN_000017d8(DAT_00000724,7,0);
  return;
}



void FUN_00000150(void)

{
  FUN_000017d8(DAT_00000724,0,0);
  FUN_000017d8(DAT_00000724,1,0);
  FUN_000017d8(DAT_00000724,2,0);
  FUN_000017d8(DAT_00000724,3,0);
  FUN_000017d8(DAT_00000724,4,0);
  FUN_000017d8(DAT_00000724,5,0);
  FUN_000017d8(DAT_00000724,6,0);
  FUN_000017d8(DAT_00000724,7,0);
  return;
}



void FUN_000001f8(void)

{
  FUN_000017d8(DAT_00000724,0,1);
  FUN_000017d8(DAT_00000724,1,1,0);
  FUN_000017d8(DAT_00000724,2,1,0);
  FUN_000017d8(DAT_00000724,3,1,0);
  FUN_000017d8(DAT_00000724,4,1,0);
  FUN_000017d8(DAT_00000724,5,1,0);
  FUN_000017d8(DAT_00000724,6,1,0);
  FUN_000017d8(DAT_00000724,7,1,0);
  return;
}



void FUN_000002a0(void)

{
  FUN_000017d8(DAT_00000724,9,1,0);
  FUN_000017d8(DAT_00000724,10,1,0);
  FUN_000017d8(DAT_00000724,8,1,0);
  FUN_000018c0(DAT_00000724,8);
  FUN_00000150();
  return;
}



uint FUN_000002f4(void)

{
  FUN_00000150();
  FUN_000018d4(DAT_00000724,9);
  FUN_000018d4(DAT_00000724,10);
  FUN_000018d4(DAT_00000724,8);
  FUN_000018c0(DAT_00000724,8);
  return *DAT_00000728 & 0xff;
}



uint FUN_0000033c(void)

{
  FUN_00000150();
  FUN_000018d4(DAT_00000724,9);
  FUN_000018c0(DAT_00000724,10);
  FUN_000018d4(DAT_00000724,8);
  FUN_000018c0(DAT_00000724,8);
  return *DAT_00000728 & 0xff;
}



void FUN_00000384(uint param_1)

{
  FUN_000001f8();
  FUN_000018c0(DAT_00000724,9);
  FUN_000018d4(DAT_00000724,10);
  *DAT_00000728 = *DAT_00000728 & 0xffffff00 | param_1 & 0xff;
  FUN_000018d4(DAT_00000724,8);
  FUN_000018c0(DAT_00000724,8);
  return;
}



void FUN_000003e0(uint param_1)

{
  FUN_000001f8();
  FUN_000018c0(DAT_00000724,9);
  FUN_000018c0(DAT_00000724,10);
  *DAT_00000728 = *DAT_00000728 & 0xffffff00 | param_1 & 0xff;
  FUN_000018d4(DAT_00000724,8);
  FUN_000018c0(DAT_00000724,8);
  return;
}



void FUN_0000043c(void)

{
  FUN_000003e0(0x38);
  FUN_00000384(0xea);
  FUN_00000384(DAT_0000072c);
  return;
}



void FUN_00000460(void)

{
  FUN_000002a0();
  return;
}



void FUN_0000046c(int param_1,int param_2,int param_3,int param_4,undefined2 *param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  while (iVar2 < param_4) {
    iVar3 = *(int *)PTR_DAT_00000730;
    iVar1 = 0;
    while (iVar1 < param_3) {
      *(undefined2 *)(iVar3 + (param_2 + iVar2) * 0x640 + param_1 * 2 + iVar1 * 2) = *param_5;
      iVar1 = iVar1 + 1;
      param_5 = param_5 + 1;
    }
    iVar2 = iVar2 + 1;
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_000004d8(void)

{
  int iVar1;
  undefined auStack48 [4];
  char acStack44 [12];
  byte local_20;
  byte local_1f;
  byte local_1e;
  byte local_1d;
  ushort local_16;
  ushort local_14;
  undefined4 local_10;
  undefined4 uStack12;
  undefined4 local_8;
  undefined4 uStack4;
  
  local_8 = s_eGON_BMPeGON_EXE_00000734._0_4_;
  uStack4 = s_eGON_BMPeGON_EXE_00000734._4_4_;
  local_10 = s_eGON_BMPeGON_EXE_00000734._8_4_;
  uStack12 = s_eGON_BMPeGON_EXE_00000734._12_4_;
  FUN_00001670(s_eGON_BMPeGON_EXE_00000734._8_4_);
  FUN_00000970();
  FUN_0000212c();
  FUN_00001970(ram0x00000744);
  FUN_000025a8(0x13000,auStack48,0x20);
  FUN_000025a8(uRam00000748,0x81000000,
               ((uint)local_1d << 0x18 | (uint)local_1e << 0x10 | (uint)local_1f << 8 |
               (uint)local_20) - 0x28);
  FUN_00001fe0(0x4b0);
  FUN_00000460();
  *(undefined4 *)PTR_DAT_00000730 = 0x81b00000;
  iVar1 = iRam0000074c;
  while (-1 < iVar1) {
    *(undefined4 *)(iVar1 * 4 + -0x7e500000) = 0;
    iVar1 = iVar1 + -1;
  }
  FUN_00002d24(800,0x1e0,0x81b00000,0x81b00000);
  FUN_0000046c(800 - local_16 >> 1,0x1e0 - local_14 >> 1,(uint)local_16,(uint)local_14,0x81000000);
  FUN_0000043c();
  FUN_000025a8(0x27000,auStack48,0x20);
  iVar1 = 0;
  while ((iVar1 < 8 && (acStack44[iVar1] == *(char *)((int)&local_10 + iVar1)))) {
    iVar1 = iVar1 + 1;
  }
  if (iVar1 == 8) {
    FUN_000025a8(uRam00000750,0x80000000,
                 ((uint)local_1d << 0x18 | (uint)local_1e << 0x10 | (uint)local_1f << 8 |
                 (uint)local_20) - 0x20);
    FUN_00001fe0(100);
    (*(code *)0x80000000)();
  }
  else {
    FUN_000025a8(0x6000,auStack48,0x20);
    iVar1 = 0;
    while ((iVar1 < 8 && (acStack44[iVar1] == *(char *)((int)&local_10 + iVar1)))) {
      iVar1 = iVar1 + 1;
    }
    if (iVar1 == 8) {
      FUN_000025a8(uRam00000754,0x80000000,
                   ((uint)local_1d << 0x18 | (uint)local_1e << 0x10 | (uint)local_1f << 8 |
                   (uint)local_20) - 0x20);
      FUN_00001fe0(100);
      (*(code *)0x80000000)();
    }
  }
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



void FUN_00000758(void)

{
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



undefined8 FUN_00000768(undefined4 param_1,undefined4 param_2)

{
  return CONCAT44(param_2,DAT_00000794);
}



undefined4 FUN_000007b8(undefined4 *param_1)

{
  return *param_1;
}



void FUN_000007e8(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  *param_1 = param_3;
  return;
}



void FUN_000007f8(undefined4 param_1)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = DAT_00000a90;
  do {
    uVar1 = FUN_000007b8(param_1,0);
    iVar2 = iVar2 + -1;
    if (iVar2 == 0) {
      return;
    }
  } while ((uVar1 & 0x10000000) == 0);
  return;
}



void FUN_00000838(uint param_1)

{
  int iVar1;
  uint uVar2;
  int extraout_r1;
  int extraout_r1_00;
  int extraout_r1_01;
  int iVar3;
  uint uVar4;
  
  if (DAT_00000a94 < param_1) {
    param_1 = DAT_00000a94;
  }
  FUN_00002f44(param_1,DAT_00000a98);
  if (extraout_r1 == 0) {
    iVar1 = FUN_00002f44(param_1,DAT_00000a98);
    iVar1 = iVar1 + -1;
    iVar3 = 0;
    uVar4 = 0;
  }
  else {
    FUN_00002f44(param_1,DAT_00000a9c);
    if (extraout_r1_00 == 0) {
      uVar4 = 1;
      uVar2 = FUN_00002f44(param_1,DAT_00000a9c);
      FUN_00002f44(uVar2,3);
      if (extraout_r1_01 == 0) {
        iVar3 = 2;
      }
      else {
        if ((uVar2 & 3) == 0) {
          iVar3 = 3;
        }
        else {
          iVar3 = 1;
        }
      }
      iVar1 = FUN_00002f44(uVar2,iVar3 + 1);
      iVar1 = iVar1 + -1;
    }
    else {
      iVar1 = FUN_00002f44(param_1,DAT_00000a98);
      iVar1 = iVar1 + -1;
      iVar3 = 0;
      uVar4 = 0;
    }
  }
  uVar2 = FUN_000007b8(DAT_00000aa0,0);
  FUN_000007e8(DAT_00000aa0,0,uVar2 & DAT_00000aa4 | iVar1 << 8 | 0x80000000U | iVar3 << 4 | uVar4);
  FUN_000007f8(DAT_00000aa0);
  return;
}



void FUN_00000970(void)

{
  uint uVar1;
  
  FUN_000007e8(DAT_00000aac,0,DAT_00000aa8);
  FUN_000007e8(DAT_00000ab0,0,DAT_00000aa8);
  uVar1 = FUN_000007b8(DAT_00000ab4,0);
  FUN_000007e8(DAT_00000ab4,0,uVar1 & 0xfffcffff | 0x10000);
  FUN_00000a74(100);
  FUN_000007e8(DAT_00000abc,0,DAT_00000ab8);
  FUN_00000a74(100);
  FUN_000007e8(DAT_00000ac4,0,DAT_00000ac0);
  FUN_00000a74(100);
  FUN_000007e8(DAT_00000ac8,0,0x3180);
  FUN_00000a74(100);
  uVar1 = FUN_000007b8(DAT_00000acc,0);
  FUN_000007e8(DAT_00000acc,0,uVar1 | 0x5000000);
  FUN_00000a74(100);
  FUN_00000838(DAT_00000ad0);
  uVar1 = FUN_000007b8(DAT_00000ab4,0);
  FUN_000007e8(DAT_00000ab4,0,uVar1 & 0xfffcffff | 0x20000);
  FUN_00000a74(100);
  return;
}



void FUN_00000a74(void)

{
  int iVar1;
  
  iVar1 = 0;
  while (iVar1 < 300) {
    iVar1 = iVar1 + 1;
  }
  return;
}



undefined4 FUN_00000af4(undefined4 *param_1)

{
  return *param_1;
}



void FUN_00000b24(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  *param_1 = param_3;
  return;
}



undefined4 FUN_00000b34(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = 0;
  while (iVar1 < 300) {
    iVar1 = iVar1 + 1;
  }
  return param_1;
}



undefined4 FUN_00000b5c(void)

{
  uint uVar1;
  int iVar2;
  bool bVar3;
  
  iVar2 = 0xffffff;
  uVar1 = FUN_00000af4(DAT_000016e8,0);
  FUN_00000b24(DAT_000016e8,0,uVar1 | 1);
  while ((uVar1 = FUN_00000af4(DAT_000016e8,0), (uVar1 & 1) != 0 &&
         (bVar3 = iVar2 != 0, iVar2 = iVar2 + -1, bVar3))) {
    if (iVar2 == 0) {
      return 0;
    }
  }
  return 1;
}



undefined4 FUN_00000bc4(void)

{
  uint uVar1;
  int iVar2;
  bool bVar3;
  
  iVar2 = 0xffffff;
  uVar1 = FUN_00000af4(DAT_000016ec,0);
  FUN_00000b24(DAT_000016ec,0,uVar1 | 1);
  while ((uVar1 = FUN_00000af4(DAT_000016ec,0), (uVar1 & 1) != 0 &&
         (bVar3 = iVar2 != 0, iVar2 = iVar2 + -1, bVar3))) {
    if (iVar2 == 0) {
      return 0;
    }
  }
  return 1;
}



void FUN_00000c2c(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = 0;
  uVar1 = FUN_00000af4(DAT_000016f0,0);
  uVar1 = (uVar1 & 0x1e0) >> 5;
  if (uVar1 == 0xc) {
    if (param_1 < DAT_000016f4) {
      uVar2 = param_1 * DAT_000016fc >> 6;
    }
    else {
      uVar1 = param_1 + (param_1 >> 3) + (param_1 >> 4) + (param_1 >> 5);
      while (DAT_000016f8 <= uVar1) {
        uVar1 = uVar1 - DAT_000016f8;
        uVar2 = uVar2 + 1;
      }
    }
  }
  else {
    if (uVar1 == 0xb) {
      if (param_1 < DAT_000016f4) {
        uVar2 = param_1 * DAT_000016fc >> 5;
      }
      else {
        uVar1 = param_1 + (param_1 >> 3) + (param_1 >> 4) + (param_1 >> 5);
        while (DAT_00001704 <= uVar1) {
          uVar1 = uVar1 + DAT_00001700;
          uVar2 = uVar2 + 1;
        }
      }
    }
  }
  FUN_00000b24(DAT_00001708,0,uVar2);
  return;
}



void FUN_00000d08(int param_1)

{
  uint uVar1;
  
  if (*(char *)(param_1 + 0x18) == '\0') {
    uVar1 = *(uint *)(param_1 + 0x1c) >> 5;
  }
  else {
    uVar1 = *(uint *)(param_1 + 0x1c) >> 4;
  }
  FUN_00000b24(DAT_000016f0,0,
               *(uint *)(param_1 + 0x14) | 2 | (*(uint *)(param_1 + 0x28) >> 2) << 3 |
               (*(uint *)(param_1 + 0x10) >> 1) << 4 | (*(int *)(param_1 + 0x24) + -1) * 0x20 |
               (*(int *)(param_1 + 0x20) + -1) * 0x200 | uVar1 << 0xd |
               *(int *)(param_1 + 0xc) << 0xf | (uint)*(byte *)(param_1 + 0x18) << 0x10);
  uVar1 = FUN_00000af4(DAT_000016e8,0);
  FUN_00000b24(DAT_000016e8,0,uVar1 | 0x80000);
  FUN_00000b5c();
  return;
}



int FUN_00000db8(int param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  iVar4 = 0;
  uVar5 = 0;
  if (param_1 == 0x10) {
    uVar1 = 4;
  }
  else {
    uVar1 = 2;
  }
  uVar2 = 0;
  while (uVar2 < uVar1) {
    if (uVar2 == 0) {
      uVar5 = FUN_00000af4(DAT_0000170c,0);
    }
    else {
      if (uVar2 == 1) {
        uVar5 = FUN_00000af4(DAT_00001710,0);
      }
      else {
        if (uVar2 == 2) {
          uVar5 = FUN_00000af4(DAT_00001714,0);
        }
        else {
          if (uVar2 == 3) {
            uVar5 = FUN_00000af4(DAT_00001718,0);
          }
        }
      }
    }
    uVar3 = 0;
    while (uVar3 < 0x20) {
      if ((uVar5 & 1) != 0) {
        iVar4 = iVar4 + 1;
      }
      uVar5 = uVar5 >> 1;
      uVar3 = uVar3 + 1;
    }
    uVar2 = uVar2 + 1;
  }
  return iVar4;
}



undefined4 FUN_00000e90(void)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = 0;
  while (uVar2 < 0x20) {
    FUN_00000b24(uVar2 * 4 + -0x80000000,0,uVar2);
    uVar2 = uVar2 + 1;
  }
  uVar2 = 0;
  while( true ) {
    if (0x1f < uVar2) {
      return 1;
    }
    uVar1 = FUN_00000af4(uVar2 * 4 + -0x80000000,0);
    if (uVar1 != uVar2) break;
    uVar2 = uVar2 + 1;
  }
  return 0;
}



uint FUN_00000f04(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = 0;
  while( true ) {
    if (7 < uVar3) {
      return 0;
    }
    uVar1 = FUN_00000af4(DAT_000016e8,0);
    FUN_00000b24(DAT_000016e8,0,uVar1 & 0xfffffe3f | uVar3 << 6);
    iVar2 = FUN_00000e90();
    if (iVar2 != 0) break;
    uVar3 = uVar3 + 1;
  }
  return uVar3;
}



bool FUN_00000f68(int param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = 0;
  uVar2 = 0;
  while (uVar2 < 8) {
    uVar1 = FUN_00000af4(DAT_000016e8,0);
    FUN_00000b24(DAT_000016e8,0,uVar1 & 0xfffffe3f | uVar2 << 6);
    FUN_00000bc4();
    uVar1 = FUN_00000af4(DAT_000016ec,0);
    if ((uVar1 & 0x30) != 0) {
      iVar3 = iVar3 + 1;
    }
    uVar2 = uVar2 + 1;
  }
  if (iVar3 != 8) {
    *(undefined *)(param_1 + 0x18) = 1;
  }
  else {
    *(undefined *)(param_1 + 0x18) = 0;
  }
  return iVar3 != 8;
}



undefined4 FUN_00000ff8(int param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint local_38 [8];
  
  uVar4 = 0;
  uVar5 = 0;
  if (*(char *)(param_1 + 0x18) == '\x01') {
    uVar3 = 0;
    while (uVar3 < 8) {
      uVar1 = FUN_00000af4(DAT_000016e8,0);
      FUN_00000b24(DAT_000016e8,0,uVar1 & 0xfffffe3f | uVar3 << 6);
      FUN_00000bc4();
      local_38[uVar3] = 0;
      uVar1 = FUN_00000af4(DAT_000016ec,0);
      if (((uVar1 >> 4 & 3) == 0) && (uVar1 = FUN_00000af4(DAT_000016ec,0), (uVar1 >> 4 & 1) == 0))
      {
        uVar1 = FUN_00000db8(*(undefined4 *)(param_1 + 0x1c));
        local_38[uVar3] = uVar1;
      }
      if (uVar5 < local_38[uVar3]) {
        uVar5 = local_38[uVar3];
        uVar4 = uVar3;
      }
      uVar3 = uVar3 + 1;
    }
    uVar5 = FUN_00000af4(DAT_000016e8,0);
    FUN_00000b24(DAT_000016e8,0,uVar5 & 0xfffffe3f | uVar4 << 6);
    FUN_00000bc4();
  }
  else {
    uVar4 = FUN_00000af4(DAT_000016f0,0);
    FUN_00000b24(DAT_000016f0,0,uVar4 & 0xfffe9fff);
    iVar2 = FUN_00000f04();
    uVar4 = FUN_00000af4(DAT_000016e8,0);
    FUN_00000b24(DAT_000016e8,0,uVar4 & 0xfffffe3f | iVar2 << 6);
  }
  return 0;
}



undefined4 FUN_00001150(int param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  
  uVar1 = 0;
  iVar3 = 0;
  *(undefined4 *)(param_1 + 0x20) = 10;
  *(undefined4 *)(param_1 + 0x24) = 0xd;
  FUN_00000d08(param_1);
  FUN_00000ff8(param_1);
  while (iVar4 = DAT_0000171c, uVar1 < 0x20) {
    *(int *)(&DAT_80000200 + uVar1) = DAT_0000171c;
    *(int *)(&DAT_80000600 + uVar1) = iVar4 << 1;
    uVar1 = uVar1 + 1;
  }
  uVar1 = 0;
  while (uVar1 < 0x20) {
    if (*(int *)(&DAT_80000200 + uVar1) == DAT_00001720) {
      iVar3 = iVar3 + 1;
    }
    uVar1 = uVar1 + 1;
  }
  if (iVar3 == 0x20) {
    iVar3 = 9;
  }
  else {
    iVar3 = 10;
  }
  iVar4 = 0;
  *(int *)(param_1 + 0x20) = iVar3;
  *(undefined4 *)(param_1 + 0x24) = 0xd;
  FUN_00000d08(param_1);
  if (iVar3 == 10) {
    uVar6 = DAT_00001724 | DAT_00001724 << 1;
    uVar1 = DAT_00001724;
  }
  else {
    uVar6 = DAT_00001728 | DAT_00001728 << 1;
    uVar1 = DAT_00001728;
  }
  uVar2 = 0;
  while (uVar2 < 0x20) {
    *(undefined4 *)(uVar1 + uVar2) = DAT_0000172c;
    *(int *)(uVar6 + uVar2) = DAT_00001730;
    uVar2 = uVar2 + 1;
  }
  uVar6 = 0;
  while (uVar6 < 0x20) {
    if (*(int *)(uVar1 + uVar6) == DAT_00001730) {
      iVar4 = iVar4 + 1;
    }
    uVar6 = uVar6 + 1;
  }
  if (iVar4 == 0x20) {
    uVar5 = 0xc;
  }
  else {
    uVar5 = 0xd;
  }
  *(int *)(param_1 + 0x20) = iVar3;
  *(undefined4 *)(param_1 + 0x24) = uVar5;
  if (*(int *)(param_1 + 0x24) == 0xd) {
    if (*(int *)(param_1 + 0x20) == 10) {
      *(undefined4 *)(param_1 + 4) = 0x40;
    }
    else {
      *(undefined4 *)(param_1 + 4) = 0x20;
    }
  }
  else {
    *(undefined4 *)(param_1 + 4) = 0x10;
  }
  FUN_00000c2c(*(undefined4 *)(param_1 + 8));
  *(undefined4 *)(param_1 + 0xc) = 0;
  FUN_00000d08(param_1);
  return 0;
}



undefined4 FUN_000012e0(int *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  uVar1 = FUN_00000af4(DAT_00001734,0);
  FUN_00000b24(DAT_00001734,0,uVar1 | 0x7000);
  FUN_00000b34(5);
  if (((uint)param_1[0xb] >> 3 & 1) != 0) {
    uVar1 = FUN_00000af4(DAT_00001738,0);
    FUN_00000b24(DAT_00001738,0,uVar1 | 0xc00000);
  }
  if ((0x8f < (uint)param_1[2]) && ((uint)param_1[2] < 0xb5)) {
    FUN_00000b24(DAT_00001740,0,DAT_0000173c);
  }
  if (0xb3 < (uint)param_1[2]) {
    FUN_00000b24(DAT_00001740,0,DAT_00001744);
  }
  if ((uint)param_1[2] < 0x61) {
    iVar2 = FUN_00002f44(param_1[2] << 1,0xc);
    uVar1 = (iVar2 + -1) * 0x100 | 1;
  }
  else {
    iVar2 = FUN_00002f44(param_1[2] << 1,0x18);
    uVar1 = (iVar2 + -1) * 0x100;
  }
  uVar3 = uVar1 | 0x80000000;
  if ((*(byte *)(param_1 + 0xb) & 0x10) == 0) {
    if ((*(byte *)(param_1 + 0xb) & 0x20) == 0) {
      if ((*(byte *)(param_1 + 0xb) & 0x40) == 0) {
        if ((*(byte *)(param_1 + 0xb) & 0x80) != 0) {
          FUN_00000b24(DAT_0000174c,0,DAT_00001758);
        }
      }
      else {
        FUN_00000b24(DAT_0000174c,0,DAT_00001754);
      }
    }
    else {
      FUN_00000b24(DAT_0000174c,0,DAT_00001750);
    }
  }
  else {
    FUN_00000b24(DAT_0000174c,0,DAT_00001748);
  }
  if ((*(byte *)(param_1 + 0xb) & 0xf0) != 0) {
    uVar3 = uVar1 | 0x81000000;
  }
  FUN_00000b24(DAT_0000175c,0,uVar3);
  uVar1 = FUN_00000af4(DAT_0000175c,0);
  FUN_00000b24(DAT_0000175c,0,uVar1 | 0x100000);
  do {
    uVar1 = FUN_00000af4(DAT_0000175c,0);
  } while ((uVar1 & 0x10000000) == 0);
  FUN_00000b34(5);
  uVar1 = FUN_00000af4(DAT_00001760,0);
  FUN_00000b24(DAT_00001760,0,uVar1 | 0x4000);
  uVar1 = FUN_00000af4(DAT_00001764,0);
  FUN_00000b24(DAT_00001764,0,uVar1 & 0xffffbfff);
  uVar1 = 0;
  while (uVar1 < 10) {
    uVar1 = uVar1 + 1;
  }
  uVar1 = FUN_00000af4(DAT_00001764,0);
  FUN_00000b24(DAT_00001764,0,uVar1 | 0x4000);
  uVar1 = FUN_00000af4(DAT_00001738,0);
  if (*(char *)(param_1 + 6) == '\x01') {
    uVar1 = uVar1 | 0x10000;
  }
  else {
    uVar1 = uVar1 & 0xfffeffff;
  }
  FUN_00000b24(DAT_00001738,0,uVar1);
  FUN_00000b24(DAT_0000176c,0,DAT_00001768);
  FUN_00000b24(DAT_00001774,0,DAT_00001770);
  FUN_00000d08(param_1);
  FUN_00000f68(param_1);
  uVar1 = FUN_00000af4(DAT_00001738,0);
  if (*(char *)(param_1 + 6) == '\x01') {
    uVar1 = uVar1 | 0x10000;
  }
  else {
    uVar1 = uVar1 & 0xfffeffff;
  }
  FUN_00000b24(DAT_00001738,0,uVar1);
  FUN_00000c2c(param_1[2]);
  FUN_00000ff8(param_1);
  FUN_00001150(param_1);
  uVar1 = 0;
  while (uVar1 < 0x80) {
    *(uint *)(*param_1 + uVar1 * 4) = uVar1 * 4 + *param_1;
    uVar1 = uVar1 + 1;
  }
  uVar1 = 0;
  while( true ) {
    if (0x7f < uVar1) {
      return 1;
    }
    if (*(int *)(*param_1 + uVar1 * 4) != uVar1 * 4 + *param_1) break;
    uVar1 = uVar1 + 1;
  }
  return 0;
}



void FUN_00001670(void)

{
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_38 = 0x80000000;
  local_34 = 0x20;
  local_30 = 0x9c;
  local_2c = 1;
  local_28 = 1;
  local_24 = 0;
  local_20 = 1;
  local_1c = 0x10;
  local_18 = 10;
  local_14 = 0xd;
  local_10 = 4;
  local_c = 3;
  FUN_000012e0(&local_38);
  return;
}



void FUN_000017d8(int param_1,uint param_2,int param_3,int param_4)

{
  *(uint *)(param_1 + (param_2 >> 3) * 4) =
       *(uint *)(param_1 + (param_2 >> 3) * 4) & ~(0xf << ((param_2 << 0x1d) >> 0x1b));
  if (param_3 == 0) {
    *(uint *)(param_1 + (param_2 >> 3) * 4) =
         *(uint *)(param_1 + (param_2 >> 3) * 4) & ~(1 << ((param_2 << 0x1d) >> 0x1b));
  }
  else {
    if (param_3 == 1) {
      *(uint *)(param_1 + (param_2 >> 3) * 4) =
           *(uint *)(param_1 + (param_2 >> 3) * 4) | 1 << ((param_2 << 0x1d) >> 0x1b);
    }
    else {
      *(uint *)(param_1 + (param_2 >> 3) * 4) =
           *(uint *)(param_1 + (param_2 >> 3) * 4) | param_3 << ((param_2 << 0x1d) >> 0x1b);
    }
  }
  *(uint *)(param_1 + 0x1c + (param_2 >> 4) * 4) =
       *(uint *)(param_1 + 0x1c + (param_2 >> 4) * 4) & ~(3 << ((param_2 << 0x1c) >> 0x1b));
  *(uint *)(param_1 + 0x1c + (param_2 >> 4) * 4) =
       *(uint *)(param_1 + 0x1c + (param_2 >> 4) * 4) | param_4 << ((param_2 << 0x1c) >> 0x1b);
  return;
}



void FUN_000018c0(int param_1,uint param_2)

{
  *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | 1 << (param_2 & 0xff);
  return;
}



void FUN_000018d4(int param_1,uint param_2)

{
  *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) & ~(1 << (param_2 & 0xff));
  return;
}



undefined4 FUN_00001930(undefined4 *param_1)

{
  return *param_1;
}



void FUN_00001960(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  *param_1 = param_3;
  return;
}



void FUN_00001970(undefined4 param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  uVar1 = FUN_00002f44(DAT_00001fd0,param_1);
  FUN_000017d8(DAT_00001fd4,0,5);
  FUN_000017d8(DAT_00001fd4,1,5,0);
  iVar3 = DAT_00001fd8;
  uVar2 = FUN_00001930(DAT_00001fd8,0);
  FUN_00001960(iVar3,0,uVar2 | 0x100000);
  iVar3 = iVar3 + 0x268;
  uVar2 = FUN_00001930(iVar3,0);
  FUN_00001960(iVar3,0,uVar2 | 0x100000);
  iVar3 = DAT_00001fdc;
  FUN_00001960(DAT_00001fdc + 4,0);
  FUN_00001960(iVar3 + 8,0,0xf7);
  FUN_00001960(iVar3 + 0x10,0);
  uVar2 = FUN_00001930(iVar3 + 0xc,0);
  FUN_00001960(iVar3 + 0xc,0,uVar2 | 0x80);
  FUN_00001960(iVar3,0,uVar1 >> 4 & 0xff);
  FUN_00001960(iVar3 + 4,0,((uVar1 >> 4) << 0x10) >> 0x18);
  uVar1 = FUN_00001930(iVar3 + 0xc,0);
  FUN_00001960(iVar3 + 0xc,0,uVar1 & 0xffffff7f);
  uVar1 = FUN_00001930(iVar3 + 0xc,0);
  FUN_00001960(iVar3 + 0xc,0,uVar1 & 0xffffffe0 | 3);
  return;
}



void FUN_00001ad0(undefined4 param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = DAT_00001fdc;
  do {
    uVar2 = FUN_00001930(iVar1 + 0x7c,0);
  } while ((uVar2 & 2) == 0);
  FUN_00001960(iVar1,0,param_1);
  return;
}



void FUN_00001b0c(char *param_1)

{
  while (*param_1 != '\0') {
    FUN_00001ad0(*param_1);
    param_1 = param_1 + 1;
  }
  return;
}



void FUN_00001b34(undefined4 param_1,int param_2)

{
  bool bVar1;
  
  while (bVar1 = param_2 != 0, param_2 = param_2 + -1, bVar1) {
    FUN_00001ad0(param_1);
  }
  return;
}



void FUN_00001b5c(int param_1,int param_2)

{
  while (0 < param_2) {
    FUN_00001ad0(*(undefined *)(param_1 + param_2 + -1));
    param_2 = param_2 + -1;
  }
  return;
}



void FUN_00001b84(uint param_1,int param_2,int param_3,int param_4)

{
  bool bVar1;
  char cVar2;
  uint extraout_r1;
  int iVar3;
  int iVar4;
  uint uVar5;
  bool bVar6;
  char local_4c [40];
  
  iVar3 = 0;
  bVar1 = false;
  if (param_4 == 0) {
    param_4 = 0x20;
  }
  bVar6 = -1 < param_3;
  if (!bVar6) {
    param_3 = -param_3;
  }
  if ((param_3 < 0) || (0x50 < param_3)) {
    param_3 = 0;
  }
  if ((param_2 < 0) && (param_2 = -param_2, (int)param_1 < 0)) {
    bVar1 = true;
    param_1 = -param_1;
  }
  do {
    if (param_2 == 0x10) {
      uVar5 = param_1 & 0xf;
      param_1 = param_1 >> 4;
    }
    else {
      FUN_00002f44(param_1,param_2);
      uVar5 = extraout_r1 & 0xffff;
      param_1 = FUN_00002f44(param_1,param_2);
    }
    if (uVar5 < 10) {
      cVar2 = '0';
    }
    else {
      cVar2 = '7';
    }
    local_4c[iVar3] = cVar2 + (char)uVar5;
    iVar4 = iVar3 + 1;
    if (((param_1 != 0) && (param_2 == 10)) &&
       ((iVar4 == 3 || ((iVar4 == 7 || (iVar4 == 0xb || iVar4 == 0xf)))))) {
      iVar4 = iVar3 + 2;
      local_4c[iVar3 + 1] = ',';
    }
    iVar3 = iVar4;
  } while (param_1 != 0);
  if (bVar1) {
    local_4c[iVar4] = '-';
    iVar4 = iVar4 + 1;
  }
  if (iVar4 < param_3) {
    if (bVar6) {
      FUN_00001b34(param_4,param_3 - iVar4);
    }
    FUN_00001b5c(local_4c,iVar4);
    if (!bVar6) {
      FUN_00001b34(param_4,param_3 - iVar4);
    }
  }
  else {
    FUN_00001b5c(local_4c,iVar4);
  }
  return;
}



byte * FUN_00001d44(byte *param_1,uint param_2)

{
  bool bVar1;
  uint uVar2;
  byte *pbVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  
  uVar2 = 0;
  bVar1 = false;
  iVar5 = 0;
  uVar6 = 0x20;
  if (*param_1 == 0x30) {
    uVar6 = 0x30;
  }
  do {
    pbVar3 = param_1 + 1;
    uVar4 = (uint)*param_1;
    if (uVar4 == 0) break;
    if ((uVar4 < 0x30) || (0x39 < uVar4)) {
      if (uVar4 == 100) {
LAB_00001ed4:
        iVar5 = -10;
      }
      else {
        if (uVar4 < 0x65) {
          if (uVar4 == 0x2d) {
            bVar1 = true;
          }
          else {
            if (uVar4 < 0x2e) {
              if (uVar4 == 0) {
                return param_1;
              }
              if (uVar4 == 0x25) {
                FUN_00001ad0(0x25);
                return pbVar3;
              }
            }
            else {
              if (uVar4 == 0x58) {
                iVar5 = 0x10;
                goto LAB_00001f1c;
              }
              if (uVar4 == 99) {
                if (bVar1) {
                  FUN_00001ad0(param_2 & 0x7f);
                }
                if (0 < (int)uVar2) {
                  FUN_00001b34(uVar6,uVar2 - 1);
                }
                if (bVar1) {
                  return pbVar3;
                }
                FUN_00001ad0(param_2 & 0x7f);
                return pbVar3;
              }
            }
LAB_00001f0c:
            iVar5 = 3;
          }
        }
        else {
          if (uVar4 == 0x73) {
            if (bVar1) {
              FUN_00001b0c(param_2);
            }
            uVar4 = FUN_00002d78(param_2);
            if (uVar4 < uVar2) {
              iVar5 = FUN_00002d78(param_2);
              FUN_00001b34(uVar6,uVar2 - iVar5);
            }
            if (bVar1) {
              return pbVar3;
            }
            FUN_00001b0c(param_2);
            return pbVar3;
          }
          if (uVar4 < 0x74) {
            if (uVar4 == 0x69) goto LAB_00001ed4;
            if (uVar4 != 0x6f) goto LAB_00001f0c;
            iVar5 = 8;
          }
          else {
            if (uVar4 == 0x75) {
              iVar5 = 10;
            }
            else {
              if (uVar4 != 0x78) goto LAB_00001f0c;
              iVar5 = 0x10;
            }
          }
        }
      }
    }
    else {
      uVar2 = (uVar4 - 0x30) + uVar2 * 10;
    }
LAB_00001f1c:
    param_1 = pbVar3;
  } while (iVar5 == 0);
  if (bVar1) {
    uVar2 = -uVar2;
  }
  FUN_00001b84(param_2,iVar5,uVar2,uVar6);
  return pbVar3;
}



void FUN_00001fe0(int param_1)

{
  uint local_c;
  uint local_8;
  
  local_8 = 0;
  while (local_8 < (uint)(param_1 * 0x42)) {
    local_c = 0;
    while (local_c < 0x14) {
      local_c = local_c + 1;
    }
    local_8 = local_8 + 1;
  }
  return;
}



void FUN_00002040(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  bool bVar1;
  uint uVar2;
  undefined8 uVar3;
  uint uVar4;
  
  FUN_000032d8(param_1);
  uVar3 = FUN_00003274();
  FUN_00003034((int)uVar3,(int)((ulonglong)uVar3 >> 0x20),DAT_000020c4,DAT_000020c8,param_2,param_3,
               param_4);
  uVar2 = FUN_00002fc4();
  uVar4 = 0;
  while (uVar4 < uVar2) {
    bVar1 = false;
    while (!bVar1) {
      bVar1 = true;
    }
    uVar4 = uVar4 + 1;
  }
  return;
}



undefined FUN_000020cc(undefined *param_1)

{
  return *param_1;
}



undefined4 FUN_000020ec(undefined4 *param_1)

{
  return *param_1;
}



void FUN_0000210c(undefined *param_1,undefined4 param_2,undefined param_3)

{
  *param_1 = param_3;
  return;
}



void FUN_0000211c(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  *param_1 = param_3;
  return;
}



void FUN_0000212c(void)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  uVar1 = DAT_000025fc;
  uVar2 = FUN_000020ec(DAT_000025fc,0);
  FUN_0000211c(uVar1,0,uVar2 & 0xfffffff0 | 2);
  uVar2 = FUN_000020ec(uVar1,0);
  FUN_0000211c(uVar1,0,uVar2 & 0xffffff0f | 0x20);
  uVar2 = FUN_000020ec(uVar1,0);
  FUN_0000211c(uVar1,0,uVar2 & 0xfffff0ff | 0x200);
  uVar2 = FUN_000020ec(uVar1,0);
  FUN_0000211c(uVar1,0,uVar2 & 0xffff0fff | 0x2000);
  iVar4 = DAT_00002600;
  uVar2 = FUN_000020ec(DAT_00002600,0);
  FUN_0000211c(iVar4,0,uVar2 | 0x100000);
  iVar4 = iVar4 + -0x260;
  uVar2 = FUN_000020ec(iVar4,0);
  FUN_0000211c(iVar4,0,uVar2 | 0x100000);
  uVar2 = DAT_00002604;
  FUN_0000211c(DAT_00002604 + 0x24,0xffffffdb < DAT_00002604,DAT_00002608);
  uVar3 = FUN_000020ec(uVar2 + 4,0xfffffffb < uVar2);
  FUN_0000211c(uVar2 + 4,0xfffffffb < uVar2,uVar3 | 0x80000083);
  do {
    uVar3 = FUN_000020ec(uVar2 + 4,0xfffffffb < uVar2);
  } while ((uVar3 & 0x80000000) != 0);
  uVar3 = FUN_000020ec(uVar2 + 8,0xfffffff7 < uVar2);
  FUN_0000211c(uVar2 + 8,0xfffffff7 < uVar2,uVar3 & 0xfffffffc | 0x44);
  uVar3 = FUN_000020ec(uVar2 + 0x18,0xffffffe7 < uVar2);
  FUN_0000211c(uVar2 + 0x18,0xffffffe7 < uVar2,uVar3 | 0x80008000);
  return;
}



void FUN_000022f8(void)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = DAT_00002604;
  uVar2 = FUN_000020ec(DAT_00002604 + 4,0xfffffffb < DAT_00002604);
  FUN_0000211c(uVar1 + 4,0xfffffffb < uVar1,uVar2 & 0xfffffffc);
  return;
}



void FUN_00002334(void)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = DAT_00002604;
  uVar2 = FUN_000020ec(DAT_00002604 + 8,0xfffffff7 < DAT_00002604);
  FUN_0000211c(uVar1 + 8,0xfffffff7 < uVar1,uVar2 & 0xffffff4f);
  return;
}



void FUN_00002374(void)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = DAT_00002604;
  uVar2 = FUN_000020ec(DAT_00002604 + 8,0xfffffff7 < DAT_00002604);
  FUN_0000211c(uVar1 + 8,0xfffffff7 < uVar1,uVar2 & 0xffffff4f | 0x80);
  return;
}



void FUN_000023b4(undefined *param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = DAT_00002604;
  if (param_1 == (undefined *)0x0) {
    param_2 = 0;
  }
  FUN_0000211c(DAT_00002604 + 0x34,0xffffffcb < DAT_00002604,param_2 & 0xffffff);
  FUN_0000211c(uVar1 + 0x38,0xffffffc7 < uVar1,param_2 & 0xffffff);
  iVar2 = 0;
  while (iVar2 < (int)param_2) {
    FUN_0000210c(uVar1 + 0x200,0xfffffdff < uVar1,*param_1);
    iVar2 = iVar2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}



uint FUN_00002428(int param_1,undefined *param_2,uint param_3,undefined4 param_4)

{
  uint uVar1;
  undefined uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined *puVar6;
  int local_34;
  
  uVar1 = DAT_00002604;
  uVar5 = param_3;
  while (0 < (int)uVar5) {
    uVar3 = uVar5;
    if (0x40 < (int)uVar5) {
      uVar3 = 0x40;
    }
    FUN_0000211c(uVar1 + 0x30,0xffffffcf < uVar1,uVar3,param_4,uVar1 + 0x30);
    FUN_000023b4(param_1,uVar3);
    uVar4 = FUN_000020ec(uVar1 + 8,0xfffffff7 < uVar1);
    FUN_0000211c(uVar1 + 8,0xfffffff7 < uVar1,uVar4 | 0x80000000,param_4,uVar1 + 8);
    do {
      uVar4 = FUN_000020ec(uVar1 + 0x1c,0xffffffe3 < uVar1);
    } while ((uVar4 & 0xff) < uVar3);
    local_34 = 0;
    while (local_34 < (int)uVar3) {
      uVar2 = FUN_000020cc(uVar1 + 0x300,0xfffffcff < uVar1);
      puVar6 = param_2;
      if (param_2 != (undefined *)0x0) {
        puVar6 = param_2 + 1;
        *param_2 = uVar2;
      }
      local_34 = local_34 + 1;
      param_2 = puVar6;
    }
    if (param_1 != 0) {
      param_1 = param_1 + uVar3;
    }
    uVar5 = uVar5 - uVar3;
  }
  return param_3;
}



undefined4 FUN_0000254c(undefined4 param_1,int param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00002428(param_1,0,param_2);
  if (iVar1 == param_2) {
    iVar1 = FUN_00002428(0,param_3,param_4);
    if (iVar1 == param_4) {
      uVar2 = 0;
    }
    else {
      uVar2 = 0xffffffff;
    }
  }
  else {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



// WARNING: Could not reconcile some variable overlaps

void FUN_000025a8(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 local_18;
  
  local_18 = CONCAT13((char)param_1,
                      CONCAT12((char)((uint)(param_1 << 0x10) >> 0x18),
                               CONCAT11((char)((uint)(param_1 << 8) >> 0x18),3)));
  FUN_00002334();
  FUN_0000254c(&local_18,4,param_2,param_3);
  FUN_00002374();
  return;
}



undefined4 FUN_0000262c(undefined4 *param_1)

{
  return *param_1;
}



void FUN_0000265c(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  *param_1 = param_3;
  return;
}



void FUN_0000266c(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = DAT_00002d54;
  iVar4 = DAT_00002d54 + -5;
  iVar3 = *(int *)(param_1 + 0x10);
  uVar2 = FUN_0000262c(DAT_00002d58,0);
  FUN_0000265c(DAT_00002d58,0,uVar2 & 0x7fffffff);
  FUN_0000265c(DAT_00002d58,0,0x3004003);
  uVar2 = FUN_0000262c(DAT_00002d58,0);
  FUN_0000265c(DAT_00002d58,0,uVar2 | 0x80000000);
  FUN_00001fe0(1);
  uVar2 = FUN_0000262c(DAT_00002d5c,0);
  FUN_0000265c(DAT_00002d5c,0,uVar2 | 0x10);
  uVar2 = FUN_0000262c(DAT_00002d60,0);
  FUN_0000265c(DAT_00002d60,0,uVar2 | 0x80000000);
  uVar2 = FUN_0000262c(DAT_00002d64,0);
  FUN_0000265c(DAT_00002d64,0,uVar2 | 0x10);
  FUN_00001fe0(1);
  uVar2 = FUN_0000262c(iVar3,0);
  FUN_0000265c(iVar3,0,uVar2 & 0xfffffffe);
  FUN_0000265c(iVar3 + 0x40,0,
               (uint)((*(int *)(param_1 + 0x50) + *(int *)(param_1 + 0x54) +
                      *(int *)(param_1 + 0x58)) * 0x8000000) >> 0x17 | 0x80000000);
  FUN_0000265c(iVar3 + 0x44,0,0xf0000006);
  FUN_0000265c(iVar3 + 0x48,0,
               *(int *)(param_1 + 0x20) - 1U | (*(ushort *)(param_1 + 0x1c) - 1) * 0x10000);
  FUN_0000265c(iVar3 + 0x4c,0,(iVar1 + -1) * 0x10000 | 0x44);
  FUN_0000265c(iVar3 + 0x50,0,iVar4 * 0x10000 | 0x17);
  FUN_0000265c(iVar3 + 0x54,0,0x160000);
  FUN_0000265c(iVar3 + 0x58,0);
  FUN_0000265c(iVar3 + 0x60,0);
  uVar2 = 0x10000000;
  if (*(int *)(param_1 + 0x5c) == 0) {
    uVar2 = 0x12000000;
  }
  if (*(int *)(param_1 + 0x60) == 0) {
    uVar2 = uVar2 | 0x1000000;
  }
  if (*(int *)(param_1 + 100) == 0) {
    uVar2 = uVar2 | 0x8000000;
  }
  if (*(int *)(param_1 + 0x68) == 0) {
    uVar2 = uVar2 | 0x4000000;
  }
  FUN_0000265c(iVar3 + 0x88,0,uVar2);
  FUN_0000265c(iVar3 + 0x8c,0);
  return;
}



void FUN_000028e4(int param_1)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 8);
  uVar1 = FUN_0000262c(DAT_00002d5c,0);
  FUN_0000265c(DAT_00002d5c,0,uVar1 | 0x1000);
  uVar1 = FUN_0000262c(DAT_00002d64,0);
  FUN_0000265c(DAT_00002d64,0,uVar1 | 0x1000);
  FUN_00001fe0(1);
  uVar1 = FUN_0000262c(iVar2 + 0x800,0);
  FUN_0000265c(iVar2 + 0x800,0,uVar1 | 1);
  FUN_0000265c(iVar2 + 0x808,0,
               *(int *)(param_1 + 0x1c) - 1U | (*(ushort *)(param_1 + 0x20) - 1) * 0x10000);
  FUN_0000265c(iVar2 + 0x810,0,
               *(int *)(param_1 + 0x1c) - 1U | (*(ushort *)(param_1 + 0x20) - 1) * 0x10000);
  FUN_0000265c(iVar2 + 0x840,0,*(int *)(param_1 + 0x1c) << 4);
  FUN_0000265c(iVar2 + 0x850,0,*(int *)(param_1 + 0x38) << 3);
  FUN_0000265c(iVar2 + 0x860,0,*(uint *)(param_1 + 0x38) >> 0x1d);
  FUN_0000265c(iVar2 + 0x8a0,0,0x500);
  uVar1 = FUN_0000262c(iVar2 + 0x800,0);
  FUN_0000265c(iVar2 + 0x800,0,uVar1 | 0x100);
  uVar1 = FUN_0000262c(iVar2 + 0x870,0);
  FUN_0000265c(iVar2 + 0x870,0,uVar1 | 1);
  uVar1 = FUN_0000262c(iVar2 + 0x800,0);
  FUN_0000265c(iVar2 + 0x800,0,uVar1 | 2);
  return;
}



void FUN_00002a5c(int param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 8);
  FUN_0000265c(iVar1 + 0x850,0,param_2 << 3);
  FUN_0000265c(iVar1 + 0x860,0,param_2 >> 0x1d);
  return;
}



void FUN_00002a90(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_1 + 0x10);
  uVar1 = FUN_0000262c(uVar2,0);
  FUN_0000265c(uVar2,0,uVar1 | 0x80000000);
  return;
}



void FUN_00002ac4(int param_1)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x10);
  FUN_0000265c(iVar2,0);
  FUN_0000265c(iVar2 + 4,0);
  uVar1 = FUN_0000262c(iVar2 + 0x44,0);
  FUN_0000265c(iVar2 + 0x44,0,uVar1 & 0xfffffff);
  FUN_0000265c(iVar2 + 0x8c,0,0xffffffff);
  FUN_0000265c(iVar2 + 0xf4,0,0xffffffff);
  return;
}



void FUN_00002b38(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  
  *(undefined **)PTR_DAT_00002d6c = PTR_DAT_00002d68;
  iVar2 = DAT_00002d70;
  iVar1 = *(int *)PTR_DAT_00002d6c;
  *(undefined4 *)(iVar1 + 0xc) = 0;
  *(int *)(iVar1 + 8) = iVar2;
  iVar1 = *(int *)PTR_DAT_00002d6c;
  *(undefined4 *)(iVar1 + 0x14) = 0;
  *(int *)(iVar1 + 0x10) = iVar2 + -0x254000;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x18) = 1;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x1c) = param_1;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x20) = param_2;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x2c) = 0x10;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x44) = 0xd2;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x48) = 0x2e;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x4c) = 0x14;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x50) = 0x16;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x54) = 0x17;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x58) = 10;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x5c) = 0;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x60) = 0;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 100) = 1;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x68) = 0;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x34) = 0;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x30) = 2;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x38) = param_3;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x3c) = 0;
  iVar2 = 0x800;
  while (iVar2 < 0x1000) {
    FUN_0000265c(iVar2 + 0x1e60000,iVar2 + 0x1e60000 >> 0x1f,0);
    iVar2 = iVar2 + 4;
  }
  FUN_00002ac4(*(undefined4 *)PTR_DAT_00002d6c);
  FUN_000028e4(*(undefined4 *)PTR_DAT_00002d6c);
  FUN_0000266c(*(undefined4 *)PTR_DAT_00002d6c);
  FUN_00002a90(*(undefined4 *)PTR_DAT_00002d6c);
  return;
}



undefined4 FUN_00002cf0(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = 0;
  while (iVar1 < 0x16) {
    param_1 = FUN_000017d8(DAT_00002d74,iVar1,2,0);
    iVar1 = iVar1 + 1;
  }
  return param_1;
}



void FUN_00002d24(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  FUN_00002cf0();
  FUN_00002b38(param_1,param_2,param_3,param_4);
  return;
}



uint * FUN_00002d78(uint *param_1)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  
  pcVar3 = (char *)((int)param_1 + 1);
  while (((uint)param_1 & 3) != 0) {
    cVar1 = *(char *)param_1;
    param_1 = (uint *)((int)param_1 + 1);
    if (cVar1 == '\0') {
      return (uint *)((int)param_1 - (int)pcVar3);
    }
  }
  do {
    uVar2 = *param_1;
    param_1 = param_1 + 1;
    uVar2 = uVar2 - DAT_00002db8 & ~uVar2 & DAT_00002db8 << 7;
  } while (uVar2 == 0);
  param_1 = (uint *)((int)param_1 - (int)pcVar3);
  if ((uVar2 & 0xff) != 0) {
    return (uint *)((int)param_1 + -3);
  }
  if ((uVar2 & 0xffff) == 0) {
    if ((uVar2 & 0xffffff) != 0) {
      return (uint *)((int)param_1 + -1);
    }
  }
  else {
    param_1 = (uint *)((int)param_1 + -2);
  }
  return param_1;
}



// WARNING: Removing unreachable block (ram,0x00002f18)
// WARNING: Removing unreachable block (ram,0x00002f24)
// WARNING: Removing unreachable block (ram,0x00002f14)

longlong FUN_00002f38(undefined4 param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  bool bVar8;
  bool bVar9;
  longlong lVar10;
  
  lVar10 = FUN_00000140(param_1);
  uVar3 = (uint)((ulonglong)lVar10 >> 0x20);
  uVar1 = (uint)lVar10;
  iVar4 = 0;
  if (uVar3 <= uVar1 >> 2) {
    if (uVar3 <= uVar1 >> 5) {
      if (uVar3 <= uVar1 >> 8) {
        uVar2 = uVar3 << 6;
        iVar4 = -0x4000000;
        if (uVar1 >> 8 < uVar2) goto LAB_00002eac;
        uVar2 = uVar3 << 0xc;
        iVar4 = -0x100000;
        if (uVar1 >> 8 < uVar2) goto LAB_00002eac;
        uVar2 = uVar3 << 0x12;
        iVar4 = -0x4000;
        if (uVar2 <= uVar1 >> 8) {
          uVar2 = uVar3 << 0x18;
          iVar4 = -0x100;
        }
        bVar5 = uVar2 == 0;
        if (!bVar5) {
          do {
            if (bVar5) {
              uVar2 = uVar2 >> 6;
            }
LAB_00002eac:
            bVar5 = uVar2 <= uVar1 >> 7;
            if (bVar5) {
              uVar1 = uVar1 + uVar2 * -0x80;
            }
            bVar6 = uVar2 <= uVar1 >> 6;
            if (bVar6) {
              uVar1 = uVar1 + uVar2 * -0x40;
            }
            bVar7 = uVar2 <= uVar1 >> 5;
            if (bVar7) {
              uVar1 = uVar1 + uVar2 * -0x20;
            }
            bVar8 = uVar2 <= uVar1 >> 4;
            if (bVar8) {
              uVar1 = uVar1 + uVar2 * -0x10;
            }
            bVar9 = uVar2 <= uVar1 >> 3;
            if (bVar9) {
              uVar1 = uVar1 + uVar2 * -8;
            }
            uVar3 = ((((iVar4 * 2 + (uint)bVar5) * 2 + (uint)bVar6) * 2 + (uint)bVar7) * 2 +
                    (uint)bVar8) * 2 + (uint)bVar9;
            bVar6 = uVar2 <= uVar1 >> 2;
            if (bVar6) {
              uVar1 = uVar1 + uVar2 * -4;
            }
            bVar5 = !bVar6 && CARRY4(uVar3,uVar3) || bVar6 && uVar3 * 2 + 1 <= uVar3;
            iVar4 = uVar3 * 2 + (uint)bVar6;
          } while (bVar5);
          bVar5 = uVar2 <= uVar1 >> 1;
          if (bVar5) {
            uVar1 = uVar1 + uVar2 * -2;
          }
          uVar3 = uVar1 - uVar2;
          if (uVar2 > uVar1) {
            uVar3 = uVar1;
          }
          return CONCAT44(uVar3,(iVar4 * 2 + (uint)bVar5) * 2 + (uint)(uVar2 <= uVar1));
        }
        return lVar10 << 0x20;
      }
      bVar5 = uVar3 <= uVar1 >> 7;
      if (bVar5) {
        uVar1 = uVar1 + uVar3 * -0x80;
      }
      bVar6 = uVar3 <= uVar1 >> 6;
      if (bVar6) {
        uVar1 = uVar1 + uVar3 * -0x40;
      }
      bVar7 = uVar3 <= uVar1 >> 5;
      if (bVar7) {
        uVar1 = uVar1 + uVar3 * -0x20;
      }
      iVar4 = ((uint)bVar5 * 2 + (uint)bVar6) * 2 + (uint)bVar7;
    }
    bVar5 = uVar3 <= uVar1 >> 4;
    if (bVar5) {
      uVar1 = uVar1 + uVar3 * -0x10;
    }
    bVar6 = uVar3 <= uVar1 >> 3;
    if (bVar6) {
      uVar1 = uVar1 + uVar3 * -8;
    }
    bVar7 = uVar3 <= uVar1 >> 2;
    if (bVar7) {
      uVar1 = uVar1 + uVar3 * -4;
    }
    iVar4 = ((iVar4 * 2 + (uint)bVar5) * 2 + (uint)bVar6) * 2 + (uint)bVar7;
  }
  bVar5 = uVar3 <= uVar1 >> 1;
  if (bVar5) {
    uVar1 = uVar1 + uVar3 * -2;
  }
  uVar2 = uVar1 - uVar3;
  if (uVar3 > uVar1) {
    uVar2 = uVar1;
  }
  return CONCAT44(uVar2,(iVar4 * 2 + (uint)bVar5) * 2 + (uint)(uVar3 <= uVar1));
}



// WARNING: Removing unreachable block (ram,0x00002f18)
// WARNING: Removing unreachable block (ram,0x00002f24)
// WARNING: Removing unreachable block (ram,0x00002f14)

longlong FUN_00002f44(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  bool bVar8;
  
  iVar3 = 0;
  if (param_2 <= param_1 >> 2) {
    if (param_2 <= param_1 >> 5) {
      if (param_2 <= param_1 >> 8) {
        uVar1 = param_2 << 6;
        iVar3 = -0x4000000;
        if (param_1 >> 8 < uVar1) goto LAB_00002eac;
        uVar1 = param_2 << 0xc;
        iVar3 = -0x100000;
        if (param_1 >> 8 < uVar1) goto LAB_00002eac;
        uVar1 = param_2 << 0x12;
        iVar3 = -0x4000;
        if (uVar1 <= param_1 >> 8) {
          uVar1 = param_2 << 0x18;
          iVar3 = -0x100;
        }
        bVar4 = uVar1 == 0;
        if (!bVar4) {
          do {
            if (bVar4) {
              uVar1 = uVar1 >> 6;
            }
LAB_00002eac:
            bVar4 = uVar1 <= param_1 >> 7;
            if (bVar4) {
              param_1 = param_1 + uVar1 * -0x80;
            }
            bVar5 = uVar1 <= param_1 >> 6;
            if (bVar5) {
              param_1 = param_1 + uVar1 * -0x40;
            }
            bVar6 = uVar1 <= param_1 >> 5;
            if (bVar6) {
              param_1 = param_1 + uVar1 * -0x20;
            }
            bVar7 = uVar1 <= param_1 >> 4;
            if (bVar7) {
              param_1 = param_1 + uVar1 * -0x10;
            }
            bVar8 = uVar1 <= param_1 >> 3;
            if (bVar8) {
              param_1 = param_1 + uVar1 * -8;
            }
            uVar2 = ((((iVar3 * 2 + (uint)bVar4) * 2 + (uint)bVar5) * 2 + (uint)bVar6) * 2 +
                    (uint)bVar7) * 2 + (uint)bVar8;
            bVar5 = uVar1 <= param_1 >> 2;
            if (bVar5) {
              param_1 = param_1 + uVar1 * -4;
            }
            bVar4 = !bVar5 && CARRY4(uVar2,uVar2) || bVar5 && uVar2 * 2 + 1 <= uVar2;
            iVar3 = uVar2 * 2 + (uint)bVar5;
          } while (bVar4);
          bVar4 = uVar1 <= param_1 >> 1;
          if (bVar4) {
            param_1 = param_1 + uVar1 * -2;
          }
          uVar2 = param_1 - uVar1;
          if (uVar1 > param_1) {
            uVar2 = param_1;
          }
          return CONCAT44(uVar2,(iVar3 * 2 + (uint)bVar4) * 2 + (uint)(uVar1 <= param_1));
        }
        return (ulonglong)param_1 << 0x20;
      }
      bVar4 = param_2 <= param_1 >> 7;
      if (bVar4) {
        param_1 = param_1 + param_2 * -0x80;
      }
      bVar5 = param_2 <= param_1 >> 6;
      if (bVar5) {
        param_1 = param_1 + param_2 * -0x40;
      }
      bVar6 = param_2 <= param_1 >> 5;
      if (bVar6) {
        param_1 = param_1 + param_2 * -0x20;
      }
      iVar3 = ((uint)bVar4 * 2 + (uint)bVar5) * 2 + (uint)bVar6;
    }
    bVar4 = param_2 <= param_1 >> 4;
    if (bVar4) {
      param_1 = param_1 + param_2 * -0x10;
    }
    bVar5 = param_2 <= param_1 >> 3;
    if (bVar5) {
      param_1 = param_1 + param_2 * -8;
    }
    bVar6 = param_2 <= param_1 >> 2;
    if (bVar6) {
      param_1 = param_1 + param_2 * -4;
    }
    iVar3 = ((iVar3 * 2 + (uint)bVar4) * 2 + (uint)bVar5) * 2 + (uint)bVar6;
  }
  bVar4 = param_2 <= param_1 >> 1;
  if (bVar4) {
    param_1 = param_1 + param_2 * -2;
  }
  uVar1 = param_1 - param_2;
  if (param_2 > param_1) {
    uVar1 = param_1;
  }
  return CONCAT44(uVar1,(iVar3 * 2 + (uint)bVar4) * 2 + (uint)(param_2 <= param_1));
}



// WARNING: Control flow encountered bad instruction data

uint FUN_00002fc4(uint param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  
  iVar2 = (param_2 >> 0x14) - 0x400;
  bVar5 = SBORROW4(0x1e,iVar2);
  iVar1 = -iVar2;
  uVar3 = iVar1 + 0x1e;
  uVar4 = uVar3;
  if (iVar2 < 0x1f) {
    bVar5 = SBORROW4(0x20,uVar3);
    uVar4 = 0x20 - uVar3;
  }
  if ((int)uVar4 < 0 == bVar5) {
    return (param_2 << 0xb | 0x80000000 | param_1 >> 0x15) >> (uVar3 & 0xff);
  }
  if ((int)param_2 < 0) {
    return 0;
  }
  if (0x10 < (int)uVar3) {
    param_1 = 0;
  }
  if (uVar3 != 0x10 && iVar1 + 0xe < 0 == SBORROW4(uVar3,0x10)) {
    return param_1;
  }
  if (iVar1 != -0x3ff) {
    return 0xffffffff;
  }
  FUN_000031ac();
                    // WARNING: Bad instruction - Truncating control flow here
  halt_baddata();
}



longlong FUN_00003034(uint param_1,uint param_2,uint param_3,uint param_4)

{
  longlong lVar1;
  byte bVar2;
  uint uVar3;
  uint extraout_r1;
  int iVar4;
  uint uVar5;
  uint unaff_r5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  bool bVar13;
  bool bVar14;
  undefined4 in_cr0;
  undefined4 in_cr1;
  undefined4 in_cr9;
  
  bVar2 = (byte)(param_2 >> 3);
  uVar10 = DAT_000031a0 & param_2 >> 4;
  bVar14 = uVar10 == 0;
  if (!bVar14) {
    bVar2 = (byte)(param_4 >> 3);
    unaff_r5 = DAT_000031a0 & param_4 >> 4;
    bVar14 = unaff_r5 == 0;
  }
  bVar13 = (bool)(bVar2 & 1);
  if (!bVar14) {
    bVar14 = uVar10 == DAT_000031a0;
  }
  if (!bVar14) {
    bVar14 = unaff_r5 == DAT_000031a0;
  }
  if (bVar14) {
    if (uVar10 != DAT_000031a0 && (DAT_000031a0 & param_4 >> 4) != DAT_000031a0) {
      return (ulonglong)((param_2 ^ param_4) & 0x80000000) << 0x20;
    }
    FUN_000031ac();
    if (!bVar13) {
      coprocessor_function(0,0,4,in_cr0,in_cr1,in_cr9);
    }
    param_4 = extraout_r1 ^ param_4;
  }
  else {
    uVar3 = param_2 & ~(DAT_000031a0 << 5) | 0x100000;
    uVar5 = param_4 & ~(DAT_000031a0 << 5) | 0x100000;
    iVar11 = (uVar10 | (param_2 ^ param_4) >> 0x1f) + unaff_r5;
    lVar1 = (ulonglong)param_3 * (ulonglong)uVar3;
    uVar10 = (uint)lVar1;
    uVar9 = (uint)((ulonglong)lVar1 >> 0x20);
    lVar1 = (ulonglong)uVar5 * (ulonglong)param_1;
    uVar8 = (uint)lVar1;
    uVar6 = (uint)((ulonglong)lVar1 >> 0x20);
    iVar12 = iVar11 + -0x3fc0000;
    bVar14 = CARRY4(uVar8,uVar10);
    uVar8 = uVar8 + uVar10;
    uVar7 = uVar6 + uVar9 + (uint)bVar14;
    lVar1 = (ulonglong)uVar5 * (ulonglong)uVar3;
    uVar10 = (uint)lVar1;
    uVar3 = (uint)((ulonglong)param_3 * (ulonglong)param_1 >> 0x20);
    bVar13 = CARRY4(uVar8,uVar3);
    uVar8 = uVar8 + uVar3;
    uVar3 = uVar7 + uVar10 + (uint)bVar13;
    uVar10 = (int)((ulonglong)lVar1 >> 0x20) +
             (uint)(bVar14 == false && CARRY4(uVar6,uVar9) ||
                   bVar14 == true && uVar6 + uVar9 + 1 <= uVar6) +
             (uint)(bVar13 == false && CARRY4(uVar7,uVar10) ||
                   bVar13 == true && uVar7 + uVar10 + 1 <= uVar7);
    if ((int)((ulonglong)param_3 * (ulonglong)param_1) != 0) {
      uVar8 = uVar8 | 1;
    }
    if ((uVar10 & 0x200) == 0) {
      uVar5 = uVar8 << 0xc;
      uVar6 = uVar10 * 0x1000 | uVar3 >> 0x14;
      uVar10 = uVar3 * 0x1000 | uVar8 >> 0x14;
      iVar4 = -4;
    }
    else {
      uVar5 = uVar8 << 0xb;
      uVar6 = uVar10 * 0x800 | uVar3 >> 0x15;
      uVar10 = uVar3 * 0x800 | uVar8 >> 0x15;
      iVar4 = -3;
    }
    uVar3 = iVar4 + (iVar12 >> 0x10);
    param_4 = uVar6 + uVar3 * 0x100000 ^ iVar11 * -0x80000000;
    if (uVar5 != 0) {
      bVar2 = -(char)((int)uVar5 >> 0x1f);
      if ((uVar5 & 0x7fffffff) != 0) {
        uVar5 = 0;
      }
      param_4 = param_4 + (bVar2 == 1 && uVar10 + 1 <= uVar10);
      uVar10 = uVar10 + bVar2 & ~(uVar5 >> 0x1f);
    }
    if (uVar3 < DAT_000031a4) {
      return CONCAT44(param_4,uVar10);
    }
    if (0x3ffffff < iVar12) {
      param_4 = param_4 + 0xa0000000;
    }
    if (iVar11 + -0x7fc0000 < 0 != SBORROW4(iVar12,0x4000000)) {
      return (ulonglong)(param_4 + 0x60000000 & 0x80000000) << 0x20;
    }
  }
  return (ulonglong)(param_4 & 0x80000000 | 0x7ff00000) << 0x20;
}



undefined8 FUN_000031ac(int param_1,uint param_2,int param_3,uint param_4)

{
  uint unaff_r5;
  uint uVar1;
  uint *in_lr;
  bool bVar2;
  bool bVar3;
  undefined8 uVar4;
  
  if ((((int)*in_lr < 0) || (unaff_r5 = param_4 * 2 + (uint)(param_3 != 0), unaff_r5 < 0xffe00001))
     && (uVar1 = param_2 * 2 + (uint)(param_1 != 0), uVar1 < 0xffe00001)) {
    if (uVar1 == 0xffe00000) {
      uVar1 = ((int)param_2 >> 0x1f) * -3 + 2;
      if (unaff_r5 == 0xffe00000) {
        uVar1 = (uVar1 - ((int)param_4 >> 0x1f)) + (uint)(0xffdfffff < unaff_r5);
      }
    }
    else {
      uVar1 = param_4 >> 0x1f;
    }
  }
  else {
    uVar1 = 8;
  }
  uVar1 = *in_lr >> uVar1 * 3 & 7;
  switch(uVar1) {
  case 4:
    break;
  case 5:
    param_3 = param_1;
    param_4 = param_2;
    break;
  case 6:
  case 7:
    return 0x7ff8000000000000;
  default:
                    // WARNING: Could not recover jumptable at 0x0000321c. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar4 = (*(code *)(in_lr + uVar1 + 1))();
    return uVar4;
  }
  bVar2 = param_3 != 0;
  bVar3 = !bVar2 && CARRY4(param_4,param_4) || bVar2 && param_4 * 2 + 1 <= param_4;
  uVar1 = param_4 * 2 + (uint)bVar2;
  bVar2 = uVar1 != 0;
  if (bVar2) {
    bVar3 = uVar1 < 0x200001;
  }
  if (bVar3 && (bVar2 && uVar1 != 0x200000)) {
    param_3 = 0;
  }
  if (bVar3 && (bVar2 && uVar1 != 0x200000)) {
    param_4 = param_4 & 0x80000000;
  }
  return CONCAT44(param_4,param_3);
}



longlong FUN_00003274(uint param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  byte extraout_var;
  byte bVar3;
  uint uVar4;
  bool bVar5;
  bool bVar6;
  
  uVar1 = param_1 & 0x80000000;
  uVar2 = (param_1 << 1) >> 4;
  uVar4 = param_1 << 1 ^ param_1;
  bVar5 = uVar4 == 0;
  if (!bVar5) {
    param_1 = param_1 << 0x1d;
    param_2 = (uVar1 | uVar2) + 0x38000000;
    bVar5 = (uVar4 & 0x7f000000) == 0;
  }
  if (bVar5) {
    bVar6 = false;
    bVar5 = (uVar2 & 0x8000000) == 0;
    if (!bVar5) {
      FUN_00003308(uVar1 | param_1 >> 0x1d | uVar2 << 3);
      bVar3 = extraout_var;
      if (!bVar6 || bVar5) {
        bVar3 = 0;
      }
      return (ulonglong)((uint)(bVar3 >> 7) << 0x1f | 0x7ff00000) << 0x20;
    }
    return (ulonglong)uVar1 << 0x20;
  }
  return CONCAT44(param_2,param_1);
}



uint FUN_000032d8(uint param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  
  uVar2 = param_1 & 0x80000000;
  if ((int)uVar2 < 0) {
    param_1 = -param_1;
  }
  uVar3 = count_leading_zeroes(param_1);
  uVar1 = param_1 << (uVar3 & 0xff);
  if (uVar1 == 0) {
    return param_1;
  }
  bVar4 = (bool)((byte)(uVar1 >> 7) & 1);
  uVar2 = (uVar2 | (0x9d - uVar3) * 0x800000) + (uVar1 >> 8) + (uint)bVar4;
  if (!bVar4) {
    return uVar2;
  }
  if ((uVar1 & 0x7f) == 0) {
    uVar2 = uVar2 & 0xfffffffe;
  }
  return uVar2;
}



uint FUN_00003308(uint param_1,uint param_2,uint param_3)

{
  uint uVar1;
  uint *in_lr;
  bool bVar2;
  
  if ((((int)*in_lr < 0) || (param_3 = param_2 * 2, param_3 < 0xff000001)) &&
     (param_1 * 2 < 0xff000001)) {
    if (param_1 * 2 == 0xff000000) {
      uVar1 = ((int)param_1 >> 0x1f) * -3 + 2;
      if (param_3 == 0xff000000) {
        uVar1 = (uVar1 - ((int)param_2 >> 0x1f)) + (uint)(0xfeffffff < param_3);
      }
    }
    else {
      uVar1 = param_2 >> 0x1f;
    }
  }
  else {
    uVar1 = 8;
  }
  uVar1 = *in_lr >> uVar1 * 3 & 7;
  switch(uVar1) {
  case 4:
    break;
  case 5:
    param_2 = param_1;
    break;
  case 6:
  case 7:
    return 0x7fc00000;
  default:
                    // WARNING: Could not recover jumptable at 0x00003370. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar1 = (*(code *)(in_lr + uVar1 + 1))();
    return uVar1;
  }
  bVar2 = SUB41(param_2 >> 0x1f,0);
  uVar1 = param_2 * 2;
  if (uVar1 != 0) {
    bVar2 = uVar1 < 0x1000001;
  }
  if (bVar2 && (uVar1 != 0 && uVar1 != 0x1000000)) {
    param_2 = param_2 & 0x80000000;
  }
  return param_2;
}


