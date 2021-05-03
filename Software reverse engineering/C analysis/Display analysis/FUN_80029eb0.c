void FUN_80029eb0(void)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  
  set_screen_to_global_pointer();
  iVar2 = Screen_Frame_Buffer_2;
  piVar1 = Global_Frame_Buffer_Pointer;
  uVar3 = 0;
  do {
    memcpy((void *)(iVar2 + uVar3 * 0x640),(void *)(*piVar1 + uVar3 * 0x640),0x640);
    uVar3 = uVar3 + 1 & 0xfffeffff;
  } while (uVar3 < 0x1e0);
  *Global_Frame_Buffer_Pointer = Screen_Frame_Buffer;
  return;
}

