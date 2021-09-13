void FUN_8001a9c0(void)

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

  iVar4 = DAT_8001aa68;
  puVar3 = PTR_DAT_8001aa64;

  if (iVar5 != 0)
  {
    return;
  }

  uVar1 = *(ushort *)(PTR_DAT_8001aa64 + 0x2e);
  uVar2 = *(ushort *)(PTR_DAT_8001aa64 + 0x32);

  if (*(char *)(DAT_8001aa60 + 0x16) != '\0')
  {
    divisor = 5;
  }

  if (uVar1 < uVar2)
  {
    iVar5 = divide((uint)(ushort)(uVar2 - uVar1),divisor);
    uVar6 = (uint)*(ushort *)(puVar3 + 0x16);

    if (uVar6 <= iVar5 + 3U)
    {
      *(undefined2 *)(iVar4 + 0x94) = 3;
      return;
    }

    uVar6 = uVar6 - iVar5;
  }
  else
  {
    iVar5 = divide((uint)(ushort)(uVar1 - uVar2),divisor);
    uVar6 = iVar5 + (uint)*(ushort *)(puVar3 + 0x16);

    if (*(ushort *)(iVar4 + 0x96) <= uVar6)
    {
      uVar6 = *(ushort *)(iVar4 + 0x96) - 1;
    }
  }

  *(short *)(iVar4 + 0x94) = (short)uVar6;
  return;
}

