//--------------------------------------------------------------------------------

void calib_ch1_limit_samples_on_401(void)

{
  uint uVar1;
  ushort *puVar2;
  int iVar3;
  
  uVar1 = DAT_8000619c;         //0x0000191
  puVar2 = DAT_80006198;        //0801AC04A   Fourth sample buffer
  iVar3 = DAT_800061a0;         //0x000009C4  ==> 2500

  do
  {
    if (uVar1 < *puVar2)        //Limit the readings on 401
    {
      *puVar2 = (ushort)uVar1;
    }

    iVar3 = iVar3 + -1;
    puVar2 = puVar2 + 1;
  } while (iVar3 != 0);

  return;
}

//--------------------------------------------------------------------------------

