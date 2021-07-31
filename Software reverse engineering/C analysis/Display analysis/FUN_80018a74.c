void FUN_80018a74(char *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined2 uVar1;
  short sVar2;
  int *piVar3;
  byte bVar4;
  short sVar5;
  short sVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined4 local_28;
  undefined4 local_24;
  
  if (param_1 != (char *)0x0) {
    local_28 = param_3;
    local_24 = param_4;

    FUN_8001936c();

    sVar5 = FUN_80019210();

    piVar3 = DAT_80018bf0;
    uVar1 = *(undefined2 *)(*DAT_80018bf0 + 0x22);

    sVar6 = FUN_8001925c();

    *(short *)(*piVar3 + 0x24) = *(short *)(*piVar3 + 0x24) - sVar6;

    while (*param_1 != '\0')
    {
      uVar7 = FUN_80019eb0(param_1,DAT_80018bf4);

      iVar8 = FUN_80019e0c(param_1,uVar7);

      iVar10 = *piVar3;
      bVar4 = *(byte *)(iVar10 + 0x2c) & 3;
      iVar9 = iVar8;

      if (bVar4 != 1)
      {
        if (bVar4 == 2)
        {
          iVar9 = iVar8 / 2;
        }
        else
        {
          iVar9 = 0;
        }
      }

      sVar2 = *(short *)(iVar10 + 0x22) - (short)iVar9;
      *(short *)(iVar10 + 0x22) = sVar2;
      local_28 = CONCAT22(*(short *)(iVar10 + 0x24),sVar2);
      local_24 = CONCAT22(*(short *)(iVar10 + 0x24) + sVar5 + -1,sVar2 + (short)iVar8 + -1);

      FUN_80019cd8(param_1,uVar7,&local_28);

      *(undefined2 *)(*piVar3 + 0x24) = local_28._2_2_;

      iVar9 = FUN_80019988(param_1,uVar7);

      param_1 = param_1 + iVar9;

      if (*param_1 == '\n' || *param_1 == '\r') {
        iVar9 = *piVar3;
        bVar4 = *(byte *)(iVar9 + 0x2c) & 3;
        if (bVar4 == 1 || bVar4 == 2) {
          *(undefined2 *)(iVar9 + 0x22) = uVar1;
        }
        else {
          *(undefined2 *)(iVar9 + 0x22) = *(undefined2 *)(iVar9 + 0x20);
        }
        if (*param_1 == '\n') {
          *(short *)(iVar9 + 0x24) = *(short *)(iVar9 + 0x24) + sVar5;
        }
      }
      else {
        *(short *)(*piVar3 + 0x22) = (short)local_28 + (short)iVar8;
      }
      if (*param_1 == '\0') break;
      param_1 = param_1 + 1;
    }
    iVar9 = *piVar3;
    *(short *)(iVar9 + 0x24) = *(short *)(iVar9 + 0x24) + sVar6;
    *(ushort *)(iVar9 + 0x2c) = *(ushort *)(iVar9 + 0x2c) & 0xfffc;

    FUN_80019a6c();
  }
  return;
}

