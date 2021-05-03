void display_text(char *text,ushort xpos,ushort ypos)

{
  int iVar1;
  
  FUN_8001936c();
  iVar1 = *DAT_80018c2c;
  *(ushort *)(iVar1 + 0x22) = xpos;
  *(ushort *)(iVar1 + 0x24) = ypos;
  FUN_80018a74(text);
  iVar1 = *(int *)(DAT_80019a84 + 0xc) + -1;
  *(int *)(DAT_80019a84 + 0xc) = iVar1;
  if (iVar1 != 0) {
    return;
  }
  return;
}

