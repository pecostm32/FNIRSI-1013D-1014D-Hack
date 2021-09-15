
//void FUN_8000bb04(uint filenumber)

void remove_item_from_lists(uint filenumber)
{
  uint uVar1;
  int iVar2;
  undefined2 *puVar3;
  uint uVar4;
  undefined2 *puVar5;
  
  uVar4 = 0;
  uVar1 = 0;

  do
  {
    if (*(ushort *)(DAT_8000bbec + uVar1 * 2 + 0x1e) == filenumber)
    {
      uVar4 = uVar1;

      if (DAT_8000bbf0 <= uVar1)
        goto LAB_8000bb94;

      break;
    }

    uVar1 = uVar1 + 1 & 0xfffeffff;
  } while (uVar1 < 1000);

  iVar2 = DAT_8000bbec + uVar4 * 2;
  uVar4 = DAT_8000bbf0 - uVar4;
  puVar5 = (undefined2 *)(iVar2 + 0x1e);
  puVar3 = (undefined2 *)(iVar2 + 0x1c);

  if ((uVar4 & 1) != 0)
  {
    puVar5 = (undefined2 *)(iVar2 + 0x20);
    puVar3 = (undefined2 *)(iVar2 + 0x1e);
    *puVar3 = *puVar5;
  }

  uVar4 = uVar4 * 0x8000 >> 0x10;

  while (uVar4 != 0)
  {
    puVar3[1] = puVar5[1];
    puVar5 = puVar5 + 2;
    uVar4 = uVar4 - 1 & 0xffff;
    puVar3 = puVar3 + 2;
    *puVar3 = *puVar5;
  }

LAB_8000bb94:
  uVar4 = DAT_8000bbfc;
  iVar2 = DAT_8000bbf8;
  *(undefined2 *)(DAT_8000bbf4 + 0xec) = 0;
  uVar1 = 0;

  do
  {
    if (CONCAT11(*(undefined *)(iVar2 + uVar1),*(undefined *)(iVar2 + uVar1 + 1)) == filenumber)
    {
      *(undefined *)(iVar2 + uVar1) = 0;
      *(undefined *)(iVar2 + uVar1 + 1) = 0;
      return;
    }

    uVar1 = uVar1 + 400;
  } while (uVar1 < uVar4);

  return;
}


