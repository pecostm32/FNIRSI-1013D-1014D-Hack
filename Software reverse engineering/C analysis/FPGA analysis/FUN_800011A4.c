//Read 100 bytes into memory and return some processed data

//param_1 ==> type of data to read
uint FUN_800011a4(int param_1)
{
  ushort uVar1;
  ushort *puVar2;
  int iVar3;
  int iVar4;
  ushort *unaff_r4;
  uint uVar5;
  
  if (param_1 == 1)
  {
    param_1 = 0x20;
    unaff_r4 = DAT_800012a0;                //0x8019D5EA
  }
  else 
  {
    if (param_1 == 2) 
    {
      param_1 = 0x21;
      unaff_r4 = DAT_800012a4;             //0x8019ED5A
    }
    else 
    {
      if (param_1 == 3)
      {
        param_1 = 0x22;
        unaff_r4 = DAT_800012a8;           //0x801A04CA
      }
      else 
      {
        if (param_1 == 4) 
        {
          param_1 = 0x23;
          unaff_r4 = DAT_800012ac;        //0x801A1C3A
        }
      }
    }
  }

  FUN_800169f8(param_1);                  //Send command
  FUN_800167a0();
  iVar3 = DAT_800012b0;
  FUN_80017738(DAT_800012b0,9);           //Read data
  FUN_80017738(iVar3,10);
  uVar5 = 0;

  do
  {
    FUN_80017738(iVar3,8);                //clock pulse
    FUN_8001774c(iVar3,8);
    puVar2 = unaff_r4 + (uVar5 * 2);      //short pointer
    uVar5 = uVar5 + 1 & 0xfffeffff;
    *puVar2 = (ushort)*(undefined4 *)(iVar3 + 0x10) & 0xff;
  } while (uVar5 < 100);

  uVar5 = (uint)*unaff_r4;
  uVar1 = unaff_r4[1];
  iVar3 = 0;
  iVar4 = 0x31;
  puVar2 = unaff_r4;

  do
  {
    uVar5 = uVar5 + uVar1;
    uVar1 = puVar2[3];
    iVar4 = iVar4 + -1;
    iVar3 = iVar3 + (uint)puVar2[2];
    puVar2 = puVar2 + 2;
  } while (iVar4 != 0);

  return (uint)((int)((ulonglong)(uVar5 + iVar3 + (uint)unaff_r4[99]) * (ulonglong)DAT_800012b4 >> 0x20) << 0x13) >> 0x18;
}

