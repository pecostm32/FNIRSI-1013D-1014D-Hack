void FUN_80031238(int param_1,int param_2,int param_3)

{
  ushort uVar1;
  int *piVar2;
  ushort uVar3;
  
  piVar2 = Global_Frame_Buffer_Pointer;
  uVar1 = *(ushort *)(*Global_Frame_Buffer_Pointer + (param_2 + param_3 * 800) * 2);
  uVar3 = (**(code **)(*(int *)(param_1 + 0x10) + 8))();
  *(ushort *)(*piVar2 + param_3 * 0x640 + param_2 * 2) = uVar3 ^ uVar1;
  return;
}

