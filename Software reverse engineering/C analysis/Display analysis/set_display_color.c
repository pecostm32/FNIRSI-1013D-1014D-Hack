void set_display_color(uint color)

{
  int iVar1;
  
  FUN_8001936c();                                      //Some depth count increment or context save

  FUN_8001d43c(color);

  //Next bit is FUN_80019a6c                           //Some depth count decrement or context restore
  iVar1 = *(int *)(DAT_80019a84 + 0xc) + -1;
  *(int *)(DAT_80019a84 + 0xc) = iVar1;

  if (iVar1 != 0)
  {
    return;
  }

  return;
}

//---------------------------------------------------------------------------------------

void FUN_8001d43c(void)

{
                    // WARNING: Could not recover jumptable at 0x8001d448. Too many branches
                    // WARNING: Treating indirect jump as call
  (**(code **)*DAT_8001d44c)();   //0x8019D4F0 ==> 0x80191824 ==> 0x80030138
  return;
}

//---------------------------------------------------------------------------------------
//Function called from FUN_8001d43c

void FUN_80030138(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  //If disp->color == param_1 were done
  if (*(int *)(*DAT_80030168 + 0x30) == param_1)
  {
    return;
  }

  //Store the new color
  *(int *)(*DAT_80030168 + 0x30) = param_1;


  uVar1 = FUN_8001c7bc();   //Convert 24 bit color into 16 bit color


  //This is FUN_8001d450
  iVar2 = *DAT_8001d470;

  if ((*(byte *)(iVar2 + 0x10) & 4) == 0)     //Depending on disp->fonthandlemode bit 2 use the selected disp struct to store the color as foreground color
  {
    puVar3 = *(undefined4 **)(iVar2 + 0x3c);
  }
  else
  {
    puVar3 = *(undefined4 **)(iVar2 + 0x38);
  }

  *puVar3 = uVar1;
  return;
}

//---------------------------------------------------------------------------------------

void FUN_8001c7bc(void)

{
                    // WARNING: Could not recover jumptable at 0x8001c7d8. Too many branches
                    // WARNING: Treating indirect jump as call
  (***(code ***)(*(int *)(DAT_8001c7e0 + (uint)*(byte *)(*DAT_8001c7dc + 0x11) * 4) + 0x10))();  //0x8019D488 ==> 0x803845A0 + 0x10 ==> 0x80189044 ==> 0x8002D1BC
  return;
}

//---------------------------------------------------------------------------------------
//Convert a 24bit color into a 16bit color
uint convert_color(uint color)

{
  return (uint)(byte)PTR_DAT_8002d1e8[color & 0xff] +
         (uint)(byte)PTR_DAT_8002d1ec[(color << 0x10) >> 0x18] * 0x20 +
         (uint)(byte)PTR_DAT_8002d1e8[(color << 8) >> 0x18] * 0x800;
}

//---------------------------------------------------------------------------------------


