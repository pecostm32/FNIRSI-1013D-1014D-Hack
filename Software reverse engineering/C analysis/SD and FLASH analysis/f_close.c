void f_close(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uStack16;
  
  uStack16 = param_4;

  iVar1 = FUN_80033d84();    //f_sync

  if (iVar1 == 0)
  {
    iVar1 = FUN_800390e8(param_1,&uStack16);  //validate

    if (iVar1 == 0)
    {
      *param_1 = 0;
    }
    return;
  }
  return;
}

