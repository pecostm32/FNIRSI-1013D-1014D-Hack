uint FUN_80033b18(int param_1,int param_2,uint param_3,int *param_4)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  bool bVar7;
  int aiStack44 [2];
  
  *param_4 = 0;
  uVar1 = FUN_800390e8(param_1,aiStack44);  //validate

  bVar7 = uVar1 == 0;

  if (bVar7)
  {
    uVar1 = (uint)*(byte *)(param_1 + 0x11);
  }

  if (!bVar7 || uVar1 != 0)
  {
    return uVar1;
  }

  if ((*(byte *)(param_1 + 0x10) & 1) == 0)
  {
    return 7;
  }

  uVar1 = *(uint *)(param_1 + 0x14);
  uVar2 = *(int *)(param_1 + 0xc) - uVar1;

  if (uVar2 < param_3)
  {
    param_3 = uVar2;
  }

  do
  {
    if (param_3 == 0)
    {
      return 0;
    }

    if ((uVar1 & 0x1ff) == 0)
    {
      uVar2 = *(ushort *)(aiStack44[0] + 10) - 1 & uVar1 >> 9;

      if (uVar2 == 0)
      {
        if (uVar1 == 0)
        {
          uVar1 = *(uint *)(param_1 + 8);
        }
        else
        {
          uVar1 = FUN_800351e0(param_1,*(undefined4 *)(param_1 + 0x18));  //get_fat
        }

        if (uVar1 < 2)
          goto LAB_80033c58;

        if (uVar1 == 0xffffffff)
          goto LAB_80033d00;

        *(uint *)(param_1 + 0x18) = uVar1;
      }

      uVar1 = *(int *)(param_1 + 0x18) - 2;

      if (*(int *)(aiStack44[0] + 0x18) - 2U <= uVar1)
      {
LAB_80033c58:
        *(undefined *)(param_1 + 0x11) = 2;
        return 2;
      }

      uVar5 = (uint)*(ushort *)(aiStack44[0] + 10);

      iVar4 = uVar5 * uVar1 + *(int *)(aiStack44[0] + 0x2c);

      if (iVar4 == 0)
        goto LAB_80033c58;

      iVar4 = iVar4 + uVar2;
      uVar6 = param_3 >> 9;

      if (uVar6 == 0)
      {
        if (*(int *)(param_1 + 0x1c) != iVar4)
        {
          if ((*(byte *)(param_1 + 0x10) & 0x80) != 0)
          {
            iVar3 = FUN_80033320(*(undefined *)(aiStack44[0] + 1),param_1 + 0x28,*(int *)(param_1 + 0x1c),1);

            if (iVar3 != 0)
              goto LAB_80033d00;

            *(byte *)(param_1 + 0x10) = *(byte *)(param_1 + 0x10) & 0x7f;
          }

          iVar3 = FUN_80033274(*(undefined *)(aiStack44[0] + 1),param_1 + 0x28,iVar4,1);

          if (iVar3 != 0)
            goto LAB_80033d00;
        }

        *(int *)(param_1 + 0x1c) = iVar4;
        goto LAB_80033d1c;
      }

      if (uVar5 < uVar2 + uVar6)
      {
        uVar6 = uVar5 - uVar2;
      }

      iVar3 = FUN_80033274(*(undefined *)(aiStack44[0] + 1),param_2,iVar4,uVar6);

      if (iVar3 != 0)
      {
LAB_80033d00:
        *(undefined *)(param_1 + 0x11) = 1;
        return 1;
      }

      if (((*(byte *)(param_1 + 0x10) & 0x80) != 0) && (uVar1 = *(int *)(param_1 + 0x1c) - iVar4, uVar1 < uVar6))
      {
        FUN_80035518(param_2 + uVar1 * 0x200,param_1 + 0x28,0x200);
      }

      uVar6 = uVar6 << 9;
    }
    else
    {
LAB_80033d1c:
      uVar1 = *(ushort *)(param_1 + 0x14) & 0x1ff;
      uVar6 = 0x200 - uVar1;

      if (param_3 < uVar6)
      {
        uVar6 = param_3;
      }

      FUN_80035518(param_2,uVar1 + param_1 + 0x28,uVar6);
    }

    *param_4 = *param_4 + uVar6;
    param_2 = param_2 + uVar6;
    uVar1 = *(int *)(param_1 + 0x14) + uVar6;
    *(uint *)(param_1 + 0x14) = uVar1;
    param_3 = param_3 - uVar6;
  } while( true );
}

