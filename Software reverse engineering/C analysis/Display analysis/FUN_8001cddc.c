void FUN_8001cddc(int param_1,int param_2,int param_3,int param_4,uint param_5)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  
  piVar1 = Global_Frame_Buffer_Pointer;
  uVar2 = param_4 - 1;
  param_2 = param_2 * 800;
  if (param_4 == 0) {
    return;
  }
  do {
    uVar3 = uVar2 & 0xffff;
    memset((void *)(*piVar1 + param_2 * 2 + param_1 * 2),param_5,param_3);
    uVar2 = uVar3 - 1;
    param_2 = param_2 + 800;
  } while (uVar3 != 0);
  return;
}


