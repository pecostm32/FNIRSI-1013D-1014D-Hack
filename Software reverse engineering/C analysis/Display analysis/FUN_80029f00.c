void FUN_80029f00(void)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  
  piVar2 = Global_Screen_Pointer;
  iVar1 = Screen_Frame_Buffer_2;
  uVar3 = 0;
  do {
    memcpy((void *)(*piVar2 + uVar3 * 0x640),(void *)(iVar1 + uVar3 * 0x640),0x640);
    uVar3 = uVar3 + 1 & 0xfffeffff;
  } while (uVar3 < 0x1e0);
  return;
}

