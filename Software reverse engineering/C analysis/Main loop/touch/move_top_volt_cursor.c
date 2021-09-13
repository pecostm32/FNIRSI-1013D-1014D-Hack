void FUN_8001aa6c(void)

{
  ushort uVar1;
  ushort uVar2;
  undefined *puVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int divisor;
  
  divisor = 1;
  iVar5 = FUN_80017790();
  iVar4 = DAT_8001ab14;
  puVar3 = PTR_DAT_8001ab10;
  if (iVar5 != 0) {
    return;
  }
  uVar1 = *(ushort *)(PTR_DAT_8001ab10 + 0x30);
  uVar2 = *(ushort *)(PTR_DAT_8001ab10 + 0x34);

  if (*(char *)(DAT_8001ab0c + 0x16) != '\0')
  {
    divisor = 5;
  }

  if (uVar1 < uVar2)
  {
    iVar5 = divide((uint)(ushort)(uVar2 - uVar1),divisor);
    uVar6 = (uint)*(ushort *)(puVar3 + 0x1a);

    if (uVar6 <= iVar5 + 0x2fU)
    {
      *(undefined2 *)(iVar4 + 0x9c) = 0x2f;
      return;
    }

    uVar6 = uVar6 - iVar5;
  }
  else
  {
    iVar5 = divide((uint)(ushort)(uVar1 - uVar2),divisor);
    uVar6 = iVar5 + (uint)*(ushort *)(puVar3 + 0x1a);

    if (*(ushort *)(iVar4 + 0x9e) <= uVar6)
    {
      uVar6 = *(ushort *)(iVar4 + 0x9e) - 1;
    }
  }

  *(short *)(iVar4 + 0x9c) = (short)uVar6;
  return;
}

