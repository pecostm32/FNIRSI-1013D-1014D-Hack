//Delay function

//param_1 ==> number of delay cycles

void FUN_8000bc34(undefined4 param_1)
{
  bool bVar1;
  undefined4 uVar2;
  uint uVar3;
  uint local_18;
  
  uVar2 = FUN_8003a370(param_1);
  FUN_8003a44c(uVar2,DAT_8000bcb4);
  uVar3 = FUN_8003a31c();
  local_18 = 0;
  while (local_18 < uVar3) {
    bVar1 = false;
    while (!bVar1) {
      bVar1 = true;
    }
    local_18 = local_18 + 1;
  }
  return;
}

