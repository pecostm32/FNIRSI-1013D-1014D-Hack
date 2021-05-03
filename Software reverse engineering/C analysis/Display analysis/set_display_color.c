void set_display_color(uint color)

{
  int iVar1;
  
  FUN_8001936c();
  FUN_8001d43c(color);
  iVar1 = *(int *)(DAT_80019a84 + 0xc) + -1;
  *(int *)(DAT_80019a84 + 0xc) = iVar1;
  if (iVar1 != 0) {
    return;
  }
  return;
}


