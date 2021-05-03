void FUN_8001cccc(int param_1,uint param_2,int param_3,uint param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = DAT_8001cd30;
  iVar1 = DAT_8001cd2c;
  if (param_4 <= param_2)
  {
    return;
  }

  do
  {
    iVar3 = param_1 + param_2 * 800;

    FUN_80000608(iVar2 + iVar3 * 2,iVar1 + iVar3 * 2,(param_3 - param_1) + 1);  //memcpy ??

    param_2 = param_2 + 1;
  } while (param_2 < param_4);
  return;
}

