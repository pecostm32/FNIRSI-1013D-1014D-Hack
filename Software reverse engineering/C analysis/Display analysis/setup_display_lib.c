//---------------------------------------------------------------------------------------


//Load 0x2E to address 0x8019D47C


int setup_display_lib(void)

{
  int iVar1;
  
  FUN_80019c78();                   //Setup function pointers and other initialization

  *DAT_80019364 = 0x2e;             //0x8019D464 = 0x2E

  empty_func_1();

  FUN_8002faa8(DAT_80019368);       //0x80857D4C

  iVar1 = FUN_8001d018();

  FUN_80019764(0);

  FUN_8002a65c();

  FUN_8001827c();

  return iVar1;
}

//---------------------------------------------------------------------------------------
//Only called from setup_display_lib

void FUN_80019c78(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  if (*(int *)(DAT_80019cc0 + 0x18) == 0)             //0x8019D464 + 0x18 ==> 0x8019d47c = 0 on startup
  {
    *(undefined4 *)(DAT_80019cc0 + 0x18) = 1;         //Make it one to indicate initialization has been done

    FUN_80019a88();                                   //Setup a function poiter (pointer) in 0x8019d46c

    FUN_800182fc();                                   //Setup more function pointers

    FUN_8001d660();

    puVar1 = DAT_80019cc8;                            //0x8019D480

    *DAT_80019cc8 = PTR_LAB_80019cc4;                 //*0x8019D480 = 0x8002fdd4. A function pointer at this address, so is 0x8002fdd4 some function

    FUN_8001a19c(DAT_80019cc8);                       //*0x8019D480 = 0x00000000; *0x8019d478 = 0x8019D480;
  }

  return;
}

//---------------------------------------------------------------------------------------
//Only called from FUN_80019c78

void FUN_80019a88(void)

{
  FUN_800183d0(DAT_80019aac,0x19000);                              //0x8036B7A0

  FUN_800185a4(0x80);

  *(undefined **)(DAT_8001972c + 8) = PTR_PTR_FUN_80019ab0;        //0x8019D464 + 0x08 ==> *0x8019d46c = 0x80189750 ==> FUN_80017e20

  return;
}

//---------------------------------------------------------------------------------------
//Only called from FUN_80019c78

int FUN_800182fc(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  puVar1 = DAT_80018354;                            //0x8019D4E8

  *DAT_80018354 = PTR_LAB_80018350;                 //*0x8019D4E8 = 0x8002fe14. Function pointer FUN_8002fe14

  FUN_8001a19c(puVar1);                             //*0x8019D4E8 = 0x8019D480; *0x8019d478 = 0x8019D4E8;

  puVar1 = DAT_80018358;                            //0x8019D4D4

  iVar2 = DAT_80018358[2];                          //iVar2 = *0x8019D4DC ==> 0x80189750

  uVar3 = FUN_80018464(iVar2 * 0x78);

  puVar1[4] = uVar3;

  FUN_8001a258(uVar3,0,iVar2 * 0x78);

  *puVar1 = 0xffffffff;

  empty_func_2();

  iVar2 = DAT_8002f980;

  iVar7 = 0;

  while( true )
  {
    if (*(int *)(iVar2 + 8) <= iVar7)
    {
      return 0;
    }

    iVar4 = FUN_80019ab8();                           //Function returns a zero

    iVar6 = *(int *)(iVar2 + 0x10);

    iVar5 = *(int *)(iVar6 + iVar7 * 0x78);

    if (iVar5 == iVar4)
      break;

    if (iVar5 == 0)
    {
      *(int *)(iVar6 + iVar7 * 0x78) = iVar4;
      return iVar7;
    }

    iVar7 = iVar7 + 1;
  }

  return iVar7;
}

//---------------------------------------------------------------------------------------
//Only called from FUN_80019c78

void FUN_8001d660(void)

{
  int iVar1;
  undefined4 in_r3;
  
  FUN_80018800(PTR_DAT_8001d710,PTR_PTR_LAB_8001d70c,0,0,in_r3);

  iVar1 = FUN_8001cf14();

  if (iVar1 == 0)
  {
    FUN_8001d50c(0,800,0x1e0);

    FUN_8001d570(0,800,0x1e0);

  }
  else
  {
    FUN_8001d50c(0,0x1e0,800);

    FUN_8001d570(0,0x1e0,800);
  }

  FUN_80019924(2);

  FUN_80019828(1,0,0x1df,0x1e0,0);

  FUN_80019828(0,0,799,0,800);

  return;
}

//---------------------------------------------------------------------------------------
// Called from 5 other functions
//param_1 is a pointer to a pointer

void FUN_8001a19c(int param_1)

{
  int iVar1;
  
  iVar1 = DAT_8001a1b0;                                                    //0x8019D464

  *(undefined4 *)(param_1 + 4) = *(undefined4 *)(DAT_8001a1b0 + 0x14);     //*0x8019D480 = *0x8019d478  (when called from FUN_80019c78)

  *(int *)(iVar1 + 0x14) = param_1;                                        //*0x8019d478 = 0x8019D480   (when called from FUN_80019c78)

  return;
}

//---------------------------------------------------------------------------------------

void FUN_800183d0(undefined4 param_1,uint param_2)

{
  undefined4 *puVar1;
  
  puVar1 = DAT_800183e4;

  *DAT_800183e4 = param_1;

  puVar1[1] = param_2 & 0xfffffffc;
  return;
}

//---------------------------------------------------------------------------------------

void FUN_800185a4(uint param_1)

{
  if (param_1 < 0x11)
  {
    param_1 = 0x10;
  }
  else
  {
    if (*(uint *)(DAT_800185c8 + 4) >> 1 <= param_1)
    {
      param_1 = *(uint *)(DAT_800185c8 + 4) >> 1;
    }
  }

  *(uint *)(DAT_800185c8 + 8) = param_1;
  return;
}


//---------------------------------------------------------------------------------------

uint ** FUN_80018464(int param_1)

{
  int iVar1;
  uint **ppuVar2;
  uint **ppuVar3;
  uint *puVar4;
  int *piVar5;
  int iVar6;
  
  FUN_8002fb5c();

  iVar1 = DAT_80018578;

  puVar4 = (uint *)((param_1 + 3U & 0xfffffffc) + 4);

  ppuVar3 = *(uint ***)(DAT_80018578 + 0x3c);

  if (puVar4 < *(uint **)(DAT_80018578 + 0x40))
  {
    puVar4 = *(uint **)(DAT_80018578 + 0x40);
  }

  do
  {
    if (ppuVar3 == (uint **)0x0)
    {
LAB_800184e4:
      iVar6 = *(int *)(DAT_80018578 + 0x38) + *(int *)(DAT_80018578 + 0xc);
      piVar5 = (int *)(iVar6 - *(int *)(iVar6 + -4));

      if (*piVar5 != 0)
      {
        FUN_8002ffac(0);

        piVar5 = (int *)(iVar6 - *(int *)(iVar6 + -4));

        if (*piVar5 != 0)
        {
          return ppuVar3;
        }
      }

      if ((int)puVar4 <= piVar5[1])
      {
        ppuVar2 = (uint **)((int)piVar5 + (piVar5[1] - (int)puVar4));
        ppuVar3 = ppuVar2 + 1;

        FUN_8002ff50(piVar5);

        *(int *)(iVar1 + 0xc) = *(int *)(iVar1 + 0xc) - (int)puVar4;
        *(int *)(iVar1 + 0x14) = *(int *)(iVar1 + 0x14) + (int)puVar4;

        if ((uint *)piVar5[1] != puVar4)
        {
          FUN_8002ce34();
        }

        *ppuVar2 = puVar4;
      }

      return ppuVar3;
    }

    if (ppuVar3[-1] == puVar4)
    {
      if (ppuVar3 != (uint **)0x0)
      {
        if (*ppuVar3 != (uint *)0x0)
        {
          (*ppuVar3)[1] = (uint)ppuVar3[1];
        }

        if ((uint **)ppuVar3[1] != (uint **)0x0)
        {
          *ppuVar3[1] = (uint)*ppuVar3;
        }

        if (*(uint ***)(iVar1 + 0x3c) != ppuVar3)
        {
          return ppuVar3;
        }

        *(uint **)(iVar1 + 0x3c) = *ppuVar3;
        return ppuVar3;
      }

      goto LAB_800184e4;
    }

    ppuVar3 = (uint **)*ppuVar3;
  } while( true );
}

//---------------------------------------------------------------------------------------

void FUN_8001a258(int *param_1,int param_2,uint param_3)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  bool bVar4;
  
  while( true )
  {
    bVar4 = param_3 == 0;

    if (!bVar4)
    {
      bVar4 = ((uint)param_1 & 3) == 0;
    }

    if (!bVar4)
    {
      param_3 = param_3 - 1;
    }

    if (bVar4)
      break;

    *(char *)param_1 = (char)param_2;
    param_1 = (int *)((int)param_1 + 1);
  }

  uVar3 = param_3 >> 2;

  if (uVar3 != 0)
  {
    param_3 = param_3 & 3;
    iVar1 = param_2 * 0x1010101;

    while (3 < (int)uVar3)
    {
      *param_1 = iVar1;
      param_1[1] = iVar1;
      piVar2 = param_1 + 3;
      param_1[2] = iVar1;
      uVar3 = uVar3 - 4;
      param_1 = param_1 + 4;
      *piVar2 = iVar1;
    }

    while (uVar3 != 0)
    {
      uVar3 = uVar3 - 1;
      *param_1 = iVar1;
      param_1 = param_1 + 1;
    }
  }

  while (param_3 != 0)
  {
    param_3 = param_3 - 1;
    *(char *)param_1 = (char)param_2;
    param_1 = (int *)((int)param_1 + 1);
  }

  return;
}

//---------------------------------------------------------------------------------------

undefined4 FUN_80019ab8(void)

{
  return 0;
}

//---------------------------------------------------------------------------------------

int FUN_80018800(void)

{
  int iVar1;
  int in_r3;
  
  iVar1 = FUN_80018774();

  if ((iVar1 != 0) && (FUN_8001884c(), **(int **)(iVar1 + 0xc) == 0))
  {
    *(int *)(*DAT_80018844 + in_r3 * 4 + 0x58) = iVar1;
  }

  return iVar1;
}

//---------------------------------------------------------------------------------------

undefined4 FUN_8001cf14(void)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;

  if ((*(byte *)(*DAT_8001cf28 + 0x11) < 2) && (iVar1 = FUN_800189d0(), iVar1 != 0))
  {
    uVar2 = (**(code **)(*(int *)(iVar1 + 0xc) + 0x28))(iVar1,0xe);
  }

  return uVar2;
}

//---------------------------------------------------------------------------------------

undefined4 FUN_8001d50c(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  code *pcVar1;
  undefined4 uVar2;
  int local_18;
  
  uVar2 = 1;
  local_18 = param_4;
  local_18 = FUN_800189d0();

  if ((local_18 != 0) && (pcVar1 = (code *)(**(code **)(*(int *)(local_18 + 0xc) + 0x24))(&local_18,0xb), pcVar1 != (code *)0x0))
  {
    (*pcVar1)(local_18,param_2,param_3);
    uVar2 = 0;
  }

  return uVar2;
}

//---------------------------------------------------------------------------------------

undefined4 FUN_8001d570(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  code *pcVar1;
  undefined4 uVar2;
  int local_18;
  
  uVar2 = 1;
  local_18 = param_4;
  local_18 = FUN_800189d0();

  if ((local_18 != 0) && (pcVar1 = (code *)(**(code **)(*(int *)(local_18 + 0xc) + 0x24))(&local_18,10), pcVar1 != (code *)0x0))
  {
    (*pcVar1)(local_18,param_2,param_3);
    uVar2 = 0;
  }

  return uVar2;
}

//---------------------------------------------------------------------------------------

void FUN_80019924(undefined4 param_1)

{
  *(undefined4 *)(DAT_80019930 + 0x18) = param_1;
  return;
}

//---------------------------------------------------------------------------------------

undefined4 FUN_80019828(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  
  piVar2 = DAT_8001991c;
  iVar1 = DAT_80019918;

  if ((*(byte *)(DAT_80019918 + 0x18) & 4) == 0)
  {
    iVar3 = FUN_8001cf2c(*(undefined *)(*DAT_8001991c + 0x11));

    iVar4 = FUN_8001cf34(*(undefined *)(*piVar2 + 0x11));
  }
  else
  {
    iVar3 = FUN_8001cf34();

    iVar4 = FUN_8001cf2c(*(undefined *)(*piVar2 + 0x11));
  }

  if (param_1 != 0)
  {
    iVar3 = iVar4;
  }

  iVar4 = param_4 - param_5;

  if (iVar4 < 0)
  {
    iVar4 = -iVar4;
  }

  if (0x13 < iVar4)
  {
    iVar4 = param_2 - param_3;

    if (iVar4 < 0)
    {
      iVar4 = -iVar4;
    }

    if (0x13 < iVar4)
    {
      uVar5 = FUN_8002fd3c(0,param_2,param_3,param_4,param_5);

      iVar4 = DAT_80019920;
      *(undefined4 *)(DAT_80019920 + param_1 * 8) = uVar5;

      uVar5 = FUN_8002fd3c(iVar3 + -1,param_2,param_3,param_4,param_5);

      *(undefined4 *)(iVar4 + param_1 * 8 + 4) = uVar5;

      FUN_800302b8();

      *(undefined4 *)(iVar1 + 0x1c) = 1;
      return 0;
    }
  }

  return 1;
}

//---------------------------------------------------------------------------------------

void FUN_8002fb5c(void)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  
  iVar2 = DAT_8002fc58;

  if (*(char *)(DAT_8002fc58 + 0x28) == '\0')
  {
    piVar6 = (int *)(DAT_8002fc58 + 0xc0);
    *(undefined *)(DAT_8002fc58 + 0x28) = 1;
    uVar5 = *(uint *)(iVar2 + 0xc4);

    if (0x2800 < uVar5)
    {
      uVar5 = 0x2800;
    }

    FUN_80030564(*piVar6,uVar5);

    puVar3 = DAT_8002fc60;

    if (*(int *)(iVar2 + 200) == 0)
    {
      *(uint *)(iVar2 + 200) = *(uint *)(iVar2 + 0xc4) >> 2;
    }

    *puVar3 = PTR_LAB_8002fc5c;

    FUN_8001a19c(puVar3);

    *(undefined4 *)(iVar2 + 0x20) = 0x5a;
    uVar5 = 0;

    do
    {
      uVar1 = uVar5 & 0xff;
      iVar4 = uVar5 * 8;
      uVar5 = uVar5 + 1;
      *(int *)(iVar2 + iVar4 + 0x40) = 0x10 << uVar1;
    } while (uVar5 < 0x10);

    iVar4 = *piVar6;
    *(int *)(iVar2 + 0x38) = iVar4;
    *(int *)(iVar2 + 0xc) = *(int *)(iVar2 + 0xc4);
    *(undefined4 *)(iVar2 + 0x10) = 2;
    *(int *)(iVar2 + 0x34) = iVar4 + *(int *)(iVar2 + 0xc4) + -0x14;
    uVar5 = 0;

    while (uVar5 < *(int *)(iVar2 + 0x10) - 1U)
    {
      *(uint *)(*(int *)(iVar2 + 0x34) + uVar5 * 8 + 4) = uVar5 + 1;
      uVar5 = uVar5 + 1;
    }

    *(undefined4 *)(iVar2 + 0x24) = 1;
    *(int *)(iVar2 + 4) = *(int *)(iVar2 + 0x10) + -1;

    FUN_8002ce34(*(undefined4 *)(iVar2 + 0xc),*(undefined4 *)(iVar2 + 0x38));

    FUN_8002ee40();

    *(undefined4 *)(iVar2 + 0x30) = 1;
  }

  return;
}

//---------------------------------------------------------------------------------------

undefined4 FUN_8002ffac(uint param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int *piVar7;
  int *piVar8;
  int iVar9;
  
  iVar1 = DAT_80030088;
  piVar5 = *(int **)(DAT_80030088 + 0x38);
  piVar8 = (int *)((int)piVar5 + *(int *)(DAT_80030088 + 0xc) + -1);

  do
  {
    iVar6 = piVar5[1];

    if ((*piVar5 == 0) && (piVar7 = (int *)((int)piVar5 + iVar6), piVar7 < piVar8))
    {
      iVar3 = *piVar7;
      iVar9 = piVar7[1];

      if ((iVar3 != 0) && (*(char *)(*(int *)(iVar1 + 0x34) + iVar3 * 8) == '\x01'))
      {
        iVar4 = *(int *)(iVar1 + 0x2c);

        FUN_8002ff50();

        *(int **)(*(int *)(iVar1 + 0x34) + *piVar7 * 8 + 4) = piVar5;

        FUN_80000730(piVar5,piVar7,iVar9);

        if (iVar3 == iVar4)
        {
          *(int *)(iVar1 + 0x34) = *(int *)(iVar1 + 0x34) - (int)((int)piVar7 - (int)piVar5);
        }

        uVar2 = FUN_8002ce34(iVar6,(int)piVar5 + iVar9);

        iVar6 = iVar9;

        if ((param_1 != 0) && (param_1 <= uVar2))
        {
          return 0;
        }
      }
    }

    piVar5 = (int *)((int)piVar5 + iVar6);

    if (piVar8 <= piVar5)
    {
      return 1;
    }

  } while( true );
}

//---------------------------------------------------------------------------------------

void FUN_8002ff50(int param_1)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  
  uVar2 = FUN_8002f838(*(undefined4 *)(param_1 + 4));

  piVar1 = DAT_8002ffa8;

  if (uVar2 < 0x10)
  {
    *DAT_8002ffa8 = *DAT_8002ffa8 - *(int *)(param_1 + 4);
    iVar3 = *(int *)(param_1 + 8);
    piVar4 = *(int **)(param_1 + 0xc);

    if (iVar3 != 0)
    {
      *(int **)(iVar3 + 4) = piVar4;
    }

    if (piVar4 == (int *)0x0)
    {
      piVar1[uVar2 * 2 + 0x11] = iVar3;
    }
    else
    {
      *piVar4 = iVar3;
    }
  }

  return;
}

//---------------------------------------------------------------------------------------

int FUN_8002ce34(int param_1,int *param_2)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  int **ppiVar4;
  int iVar5;
  int *piVar6;
  bool bVar7;
  
  piVar1 = DAT_8002cf24;
  piVar2 = (int *)((int)param_2 + param_1);
  piVar6 = (int *)((DAT_8002cf24[0xe] + DAT_8002cf24[3]) - 1);
  bVar7 = piVar2 == piVar6;

  if (piVar2 <= piVar6)
  {
    bVar7 = *piVar2 == 0;
  }

  if (bVar7)
  {
    param_1 = param_1 + piVar2[1];

    FUN_8002ff50();
  }

  if (((int *)piVar1[0xe] < param_2) && (piVar2 = (int *)((int)param_2 - param_2[-1]), *piVar2 == 0))
  {
    param_1 = param_1 + piVar2[1];

    FUN_8002ff50(piVar2);

    param_2 = piVar2;
  }

  uVar3 = FUN_8002f838(param_1);

  if (uVar3 < 0x10)
  {
    piVar6 = piVar1 + uVar3 * 2;

    FUN_8003072c(param_2,0,param_1,piVar6[0x11]);

    piVar2 = (int *)piVar6[0x11];
    ppiVar4 = (int **)(param_2 + 2);

    if (piVar2 != (int *)0x0)
    {
      piVar2[1] = (int)ppiVar4;
    }

    *ppiVar4 = piVar2;
    param_2[3] = 0;
    piVar6[0x11] = (int)ppiVar4;
    iVar5 = *piVar1;
    *piVar1 = iVar5 + param_1;

    if ((*(char *)((int)piVar1 + 0x29) == '\0') && (uVar3 = piVar1[3] - (iVar5 + param_1), (uint)piVar1[2] < uVar3))
    {
      piVar1[2] = uVar3;
    }
  }

  return param_1;
}

//---------------------------------------------------------------------------------------

undefined4 * FUN_80018774(undefined4 param_1,int param_2,undefined2 param_3,int param_4)

{
  undefined4 *puVar1;
  int *piVar2;
  int *piVar3;
  
  if (param_4 < 2)
  {
    puVar1 = (undefined4 *)FUN_80018464(0x1c);

    if (puVar1 != (undefined4 *)0x0)
    {
      if (param_2 == 0)
      {
        piVar2 = *(int **)(DAT_800187fc + param_4 * 4);

        if (piVar2 != (int *)0x0)
        {
          do
          {
            piVar3 = piVar2;
            piVar2 = (int *)*piVar3;
          } while (piVar2 != (int *)0x0);

          puVar1[4] = piVar3[4];
        }
      }
      else
      {
        puVar1[4] = param_2;
      }

      puVar1[6] = param_4;
      *(undefined2 *)(puVar1 + 5) = param_3;
      *puVar1 = 0;
      puVar1[3] = param_1;
      puVar1[1] = 0;
      puVar1[2] = 0;
    }
  }
  else
  {
    puVar1 = (undefined4 *)0x0;
  }

  return puVar1;
}

//---------------------------------------------------------------------------------------

undefined4 FUN_8001884c(int *param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int **ppiVar2;
  int **ppiVar3;
  uint uVar4;
  bool bVar5;
  
  bVar5 = (int)param_1 < 0;

  if (param_1 != (int *)0x0)
  {
    param_3 = param_1[6];
    bVar5 = param_3 + -2 < 0;
  }

  if (bVar5 != (param_1 != (int *)0x0 && SBORROW4(param_3,2)))
  {
    iVar1 = *(int *)(DAT_80018938 + param_3 * 4);

    if (iVar1 == 0)
    {
      *(int **)(DAT_80018938 + param_3 * 4) = param_1;
      return 0;
    }

    do
    {
      ppiVar2 = (int **)iVar1;
      iVar1 = *(int *)((int)ppiVar2 + 4);
    } while (*(int *)((int)ppiVar2 + 4) != 0);

    while (ppiVar2 != (int **)0x0)
    {
      if (*(int *)((int *)ppiVar2)[3] <= *(int *)param_1[3])
      {
        if (ppiVar2 == (int **)0x0)
        {
          return 1;
        }

        uVar4 = *(uint *)((int *)ppiVar2)[3];
        bVar5 = uVar4 == *(uint *)param_1[3];

        if (bVar5)
        {
          uVar4 = (uint)*(ushort *)(param_1 + 5);
        }

        ppiVar3 = ppiVar2;

        if (!bVar5 || uVar4 != 1)
          goto LAB_800188fc;

        goto LAB_800188e8;
      }

      ppiVar2 = (int **)*ppiVar2;
    }
  }

  return 1;

  while (ppiVar3 = ppiVar2, *(int *)param_1[3] <= *(int *)((int *)ppiVar2)[3])
  {
LAB_800188e8:
    ppiVar2 = (int **)*ppiVar3;

    if (ppiVar2 == (int **)0x0)
    {
      ppiVar2 = ppiVar3;

      if (ppiVar3 == (int **)0x0)
      {
        return 1;
      }
      break;
    }
  }

LAB_800188fc:
  if ((int **)((int *)ppiVar2)[1] == (int **)0x0)
  {
    *(int **)(DAT_80018938 + param_3 * 4) = param_1;
  }
  else
  {
    *(int **)((int *)ppiVar2)[1] = param_1;
    param_1[1] = ((int *)ppiVar2)[1];
  }

  ((int *)ppiVar2)[1] = (int)param_1;

  if ((int **)param_1 == ppiVar2)
  {
    ppiVar2 = (int **)0x0;
  }

  *param_1 = (int)ppiVar2;

  return 0;
}

//---------------------------------------------------------------------------------------

void FUN_800189d0(int param_1)

{
  int *piVar1;
  
  if (1 < param_1)
  {
    return;
  }

  piVar1 = *(int **)(DAT_80018a04 + param_1 * 4);

  while( true )
  {
    if (piVar1 == (int *)0x0)
    {
      return;
    }

    if (*(int *)piVar1[3] == 0)
      break;

    piVar1 = (int *)*piVar1;
  }

  return;
}

//---------------------------------------------------------------------------------------

undefined4 FUN_8001cf2c(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;

  if ((param_1 < 2) && (iVar1 = FUN_800189d0(), iVar1 != 0))
  {
    uVar2 = (**(code **)(*(int *)(iVar1 + 0xc) + 0x28))(iVar1,1);
  }

  return uVar2;
}

//---------------------------------------------------------------------------------------

undefined4 FUN_8001cf34(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;

  if ((param_1 < 2) && (iVar1 = FUN_800189d0(), iVar1 != 0))
  {
    uVar2 = (**(code **)(*(int *)(iVar1 + 0xc) + 0x28))(iVar1,2);
  }

  return uVar2;
}

//---------------------------------------------------------------------------------------

int FUN_8002fd3c(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  
  iVar1 = divide_2((param_5 - param_4) * (param_1 - param_2),param_3 - param_2);

  return iVar1 + param_4;
}

//---------------------------------------------------------------------------------------

void FUN_800302b8(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = DAT_80030300;
  piVar1 = DAT_800302fc;
  iVar3 = DAT_800302fc[1];
  iVar4 = *DAT_800302fc;

  if (iVar4 < iVar3)
  {
    *(int *)(DAT_80030300 + 0x24) = iVar3;
    *(int *)(iVar2 + 0x20) = iVar4;
  }
  else
  {
    *(int *)(DAT_80030300 + 0x20) = iVar3;
    *(int *)(iVar2 + 0x24) = iVar4;
  }

  iVar4 = piVar1[2];
  iVar3 = piVar1[3];

  if (iVar4 < iVar3)
  {
    *(int *)(iVar2 + 0x28) = iVar4;
    *(int *)(iVar2 + 0x2c) = iVar3;
  }
  else
  {
    *(int *)(iVar2 + 0x28) = iVar3;
    *(int *)(iVar2 + 0x2c) = iVar4;
  }

  return;
}


//---------------------------------------------------------------------------------------

void FUN_80030564(int *param_1,uint param_2)

{
  byte bVar1;
  ushort uVar2;
  byte extraout_r1;
  ushort extraout_r1_00;
  int extraout_r1_01;
  int extraout_r1_02;
  uint extraout_r1_03;
  uint extraout_r1_04;
  uint uVar3;
  uint uVar4;
  int *piVar5;
  int iVar6;
  
  uVar3 = 0;

  do
  {
    uVar4 = 0;
    piVar5 = param_1;

    while (uVar4 < param_2 >> 2)
    {
      divide(uVar4 + uVar3,0xff);
      uVar4 = uVar4 + 1;
      *piVar5 = extraout_r1_01;
      piVar5 = piVar5 + 1;
    }

    uVar4 = 0;
    piVar5 = param_1;

    while (uVar4 < param_2 >> 2)
    {
      iVar6 = *piVar5;
      divide(uVar4 + uVar3,0xff);

      if (extraout_r1_02 != iVar6)
      {
        return;
      }

      uVar4 = uVar4 + 1;
      piVar5 = piVar5 + 1;
    }

    uVar3 = uVar3 + 1;

  } while (uVar3 < 2);

  uVar3 = 0;

  do
  {
    uVar4 = 0;
    piVar5 = param_1;

    while (uVar4 < param_2 >> 1)
    {
      divide(uVar4 + uVar3,0xff);
      uVar4 = uVar4 + 1;
      *(ushort *)piVar5 = extraout_r1_00;
      piVar5 = (int *)((int)piVar5 + 2);
    }

    uVar4 = 0;
    piVar5 = param_1;

    while (uVar4 < param_2 >> 1)
    {
      uVar2 = *(ushort *)piVar5;
      divide(uVar4 + uVar3,0xff);

      if (extraout_r1_03 != uVar2)
      {
        return;
      }

      uVar4 = uVar4 + 1;
      piVar5 = (int *)((int)piVar5 + 2);
    }

    uVar3 = uVar3 + 1;

  } while (uVar3 < 2);

  uVar3 = 0;

  do
  {
    uVar4 = 0;
    piVar5 = param_1;

    while (uVar4 < param_2)
    {
      divide(uVar4 + uVar3,0xff);
      uVar4 = uVar4 + 1;
      *(byte *)piVar5 = extraout_r1;
      piVar5 = (int *)((int)piVar5 + 1);
    }

    uVar4 = 0;
    piVar5 = param_1;

    while (uVar4 < param_2)
    {
      bVar1 = *(byte *)piVar5;
      divide(uVar4 + uVar3,0xff);
      if (extraout_r1_04 != bVar1)
      {
        return;
      }

      uVar4 = uVar4 + 1;
      piVar5 = (int *)((int)piVar5 + 1);
    }

    uVar3 = uVar3 + 1;

  } while (uVar3 < 2);

  uVar3 = 0;

  while (uVar3 < param_2)
  {
    uVar3 = uVar3 + 1;
    *(byte *)param_1 = 0;
    param_1 = (int *)((int)param_1 + 1);
  }

  return;
}

//---------------------------------------------------------------------------------------

undefined4 FUN_8002ee40(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar1 = DAT_8002ef24;

  if (*(int *)(DAT_8002ef24 + 0x2c) == 0)
  {
    iVar5 = divide(*(int *)(DAT_8002ef28 + 4),*(int *)(DAT_8002ef28 + 8) + 8);
    iVar5 = iVar5 + 2;
  }
  else
  {
    iVar5 = *(uint *)(DAT_8002ef24 + 0x10) + (*(uint *)(DAT_8002ef24 + 0x10) >> 3) + 4;
  }

  iVar2 = FUN_8002cf28(iVar5 << 3);

  if (iVar2 == 0)
  {
    uVar3 = 1;
  }
  else
  {
    iVar6 = *(int *)(iVar1 + 0x2c);
    iVar7 = *(int *)(*(int *)(iVar1 + 0x34) + iVar2 * 8 + 4) + 8;

    FUN_80000804(iVar7,*(int *)(iVar1 + 0x34),*(int *)(iVar1 + 0x10) << 3);

    *(int *)(iVar1 + 0x2c) = iVar2;
    *(int *)(iVar1 + 0x34) = iVar7;
    uVar4 = *(uint *)(iVar1 + 0x10);

    while (uVar4 < iVar5 - 1U)
    {
      *(uint *)(*(int *)(iVar1 + 0x34) + uVar4 * 8 + 4) = uVar4 + 1;
      uVar4 = uVar4 + 1;
    }

    *(undefined4 *)(*(int *)(iVar1 + 0x34) + uVar4 * 8 + 4) = 0;
    *(int *)(iVar1 + 0x24) = *(int *)(iVar1 + 0x10);
    iVar2 = (iVar5 - *(int *)(iVar1 + 0x10)) + *(int *)(iVar1 + 4);
    *(int *)(iVar1 + 4) = iVar2;

    if (iVar6 != 0)
    {
      iVar2 = iVar6;
    }

    *(int *)(iVar1 + 0x10) = iVar5;

    if (iVar6 != 0)
    {
      FUN_800183e8(iVar2);
    }

    uVar3 = 0;
  }

  return uVar3;
}

//---------------------------------------------------------------------------------------

void FUN_8002f838(uint param_1)

{
  int iVar1;
  
  iVar1 = 0xf;

  do
  {
    if (*(uint *)(DAT_8002f860 + iVar1 * 8 + 0x40) <= param_1)
    {
      return;
    }

    iVar1 = iVar1 + -1;

  } while (-1 < iVar1);

  return;
}

//---------------------------------------------------------------------------------------

void FUN_8003072c(undefined4 *param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  param_1[4] = param_1;
  *param_1 = param_2;
  param_1[1] = param_3;
  param_1[2] = param_4;
  *(int *)((int)param_1 + param_3 + -4) = param_3;
  return;
}

//---------------------------------------------------------------------------------------

int FUN_8002cf28(uint param_1)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int unaff_r5;
  
  FUN_8002fb5c();

  puVar1 = DAT_8002d040;
  uVar5 = DAT_8002d040[0x10];

  if (uVar5 <= param_1)
  {
    uVar5 = param_1 + 3 & 0xfffffffc;
  }

  uVar5 = uVar5 + 0xc;

  if (uVar5 <= *DAT_8002d040)
  {
    iVar2 = FUN_8002fea8();

    if (iVar2 == 0)
    {
      return 0;
    }

    do
    {
      uVar3 = FUN_8002f838(uVar5);

      while (uVar3 < 0x10)
      {
        uVar6 = puVar1[uVar3 * 2 + 0x11];

        if (uVar6 != 0)
        {
          unaff_r5 = *(int *)(uVar6 + 8);
        }

        if (uVar6 != 0 && unaff_r5 != 0)
        {
          uVar6 = *(uint *)(unaff_r5 + 4);

          while( true )
          {
            if (uVar5 <= uVar6)
            {
              if (uVar6 - uVar5 < puVar1[0x10] + 0xc)
              {
                uVar5 = uVar6;
              }

              FUN_8002ff50(unaff_r5);

              *(int *)(puVar1[0xd] + iVar2 * 8 + 4) = unaff_r5;

              FUN_8003072c(unaff_r5,iVar2,uVar5,0);

              if ((int)uVar6 <= (int)uVar5)
              {
                return iVar2;
              }

              FUN_8002ce34(uVar6 - uVar5);

              return iVar2;
            }

            iVar4 = *(int *)(unaff_r5 + 8);

            if (iVar4 != 0)
            {
              unaff_r5 = *(int *)(iVar4 + 8);
            }

            if (iVar4 == 0 || unaff_r5 == 0)
              break;

            uVar6 = *(uint *)(unaff_r5 + 4);
          }
        }

        uVar3 = uVar3 + 1;
      }

      iVar4 = FUN_8002ffac(uVar5);

    } while (iVar4 == 0);

    FUN_8002ff18(iVar2);
  }

  return 0;
}

//---------------------------------------------------------------------------------------

void FUN_800183e8(int param_1)

{
  int iVar1;
  
  if (param_1 == 0)
  {
    return;
  }

  FUN_8001936c();

  if (*(char *)(*(int *)(DAT_80018438 + 0x34) + param_1 * 8) == '\x01')
  {
    FUN_8002ce34(*(undefined4 *)(*(int *)(*(int *)(DAT_80018438 + 0x34) + param_1 * 8 + 4) + 4));

    FUN_8002ff18(param_1);
  }

  FUN_80019a6c();

  return;
}

//---------------------------------------------------------------------------------------

int FUN_8002fea8(void)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  
  iVar1 = DAT_8002ff14;

  if (*(uint *)(DAT_8002ff14 + 4) <= *(uint *)(DAT_8002ff14 + 0x30))
  {
    *(uint *)(DAT_8002ff14 + 0x30) = *(uint *)(DAT_8002ff14 + 0x30) - 1;

    iVar2 = FUN_8002ee40();

    bVar3 = iVar2 != 0;

    if (bVar3)
    {
      iVar2 = 0;
    }

    *(int *)(iVar1 + 0x30) = *(int *)(iVar1 + 0x30) + 1;

    if (bVar3)
    {
      return iVar2;
    }
  }

  *(int *)(iVar1 + 4) = *(int *)(iVar1 + 4) + -1;
  iVar2 = *(int *)(iVar1 + 0x24);
  *(undefined4 *)(iVar1 + 0x24) = *(undefined4 *)(*(int *)(iVar1 + 0x34) + iVar2 * 8 + 4);
  *(undefined *)(*(int *)(iVar1 + 0x34) + iVar2 * 8) = 1;
  return iVar2;
}

//---------------------------------------------------------------------------------------

void FUN_8002ff18(int param_1)

{
  int iVar1;
  
  iVar1 = DAT_8002ff4c;
  *(int *)(DAT_8002ff4c + 4) = *(int *)(DAT_8002ff4c + 4) + 1;
  *(undefined4 *)(*(int *)(iVar1 + 0x34) + param_1 * 8 + 4) = *(undefined4 *)(iVar1 + 0x24);
  *(undefined *)(*(int *)(iVar1 + 0x34) + param_1 * 8) = 0;
  *(int *)(iVar1 + 0x24) = param_1;
  return;
}

//---------------------------------------------------------------------------------------
//Probably some standard lib function. Part of the code is memcpy

undefined8 FUN_80000730(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  int *piVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined *puVar5;
  int *piVar6;
  uint *puVar7;
  uint *puVar8;
  uint uVar9;
  undefined uVar10;
  undefined2 uVar11;
  undefined4 *puVar12;
  int iVar13;
  undefined4 uVar14;
  int iVar15;
  undefined uVar16;
  uint in_r12;
  undefined4 uVar17;
  int iVar18;
  undefined4 uVar19;
  bool bVar20;
  bool bVar21;
  int *piVar22;
  
  puVar12 = (undefined4 *)((int)param_1 - (int)param_2);
  bVar20 = puVar12 == (undefined4 *)0x0;
  if (param_2 <= param_1) {
    bVar20 = param_3 == puVar12;
  }
  if ((param_2 <= param_1 && puVar12 <= param_3) && !bVar20) {
    piVar2 = (int *)((int)param_1 + (int)param_3);
    piVar6 = (int *)((int)param_2 + (int)param_3);
    if ((undefined4 *)0x3 < param_3) {
      bVar20 = ((uint)piVar2 & 3) == 0;
      do {
        if (!bVar20) {
          piVar6 = (int *)((int)piVar6 + -1);
          param_3 = (undefined4 *)((int)param_3 + -1);
          piVar2 = (int *)((int)piVar2 + -1);
          *(undefined *)piVar2 = *(undefined *)piVar6;
        }
        bVar20 = ((uint)piVar2 & 3) == 0;
      } while (!bVar20);
      puVar12 = (undefined4 *)((uint)piVar6 & 3);
      if (puVar12 == (undefined4 *)0x0) {
        while (puVar12 = param_3 + -4, (undefined4 *)0xf < param_3) {
          piVar22 = piVar6 + -1;
          iVar18 = piVar6[-2];
          iVar15 = piVar6[-3];
          piVar6 = piVar6 + -4;
          iVar13 = *piVar6;
          piVar2[-1] = *piVar22;
          piVar2[-2] = iVar18;
          piVar2[-3] = iVar15;
          piVar2 = piVar2 + -4;
          *piVar2 = iVar13;
          param_3 = puVar12;
        }
        iVar13 = (int)param_3 << 0x1d;
        bVar20 = iVar13 < 0;
        if ((bool)((byte)((uint)puVar12 >> 3) & 1)) {
          piVar22 = piVar6 + -1;
          piVar6 = piVar6 + -2;
          iVar13 = *piVar6;
          piVar2[-1] = *piVar22;
          piVar2 = piVar2 + -2;
          *piVar2 = iVar13;
        }
        if (bVar20) {
          piVar6 = piVar6 + -1;
          iVar13 = *piVar6;
          piVar2 = piVar2 + -1;
          *piVar2 = iVar13;
        }
        uVar11 = (undefined2)iVar13;
        if (((uint)puVar12 & 3) != 0) {
          bVar21 = (bool)((byte)((uint)puVar12 >> 1) & 1);
          uVar9 = (int)param_3 << 0x1f;
          bVar20 = (int)uVar9 < 0;
          if (bVar21) {
            piVar6 = (int *)((int)piVar6 + -2);
            uVar11 = *(undefined2 *)piVar6;
          }
          if (bVar20) {
            uVar9 = (uint)*(byte *)((int)piVar6 + -1);
          }
          if (bVar21) {
            piVar2 = (int *)((int)piVar2 + -2);
            *(undefined2 *)piVar2 = uVar11;
          }
          if (bVar20) {
            *(char *)((int)piVar2 + -1) = (char)uVar9;
          }
          return CONCAT44(piVar6,piVar2);
        }
        return CONCAT44(piVar6,piVar2);
      }
      bVar20 = (undefined4 *)0x3 < param_3;
      param_3 = param_3 + -1;
      if (bVar20) {
        puVar7 = (uint *)((int)piVar6 - (int)puVar12);
        in_r12 = *puVar7;
        if (puVar12 < (undefined4 *)0x2) {
          do {
            puVar8 = puVar7;
            uVar9 = in_r12 << 0x18;
            puVar7 = puVar8 + -1;
            in_r12 = *puVar7;
            bVar20 = (undefined4 *)0x3 < param_3;
            param_3 = param_3 + -1;
            puVar12 = (undefined4 *)(uVar9 | in_r12 >> 8);
            piVar2 = piVar2 + -1;
            *piVar2 = (int)puVar12;
          } while (bVar20);
          piVar6 = (int *)((int)puVar8 + -3);
        }
        else {
          if (puVar12 < (undefined4 *)0x3) {
            do {
              puVar8 = puVar7;
              uVar9 = in_r12 << 0x10;
              puVar7 = puVar8 + -1;
              in_r12 = *puVar7;
              bVar20 = (undefined4 *)0x3 < param_3;
              param_3 = param_3 + -1;
              puVar12 = (undefined4 *)(uVar9 | in_r12 >> 0x10);
              piVar2 = piVar2 + -1;
              *piVar2 = (int)puVar12;
            } while (bVar20);
            piVar6 = (int *)((int)puVar8 + -2);
          }
          else {
            do {
              puVar8 = puVar7;
              uVar9 = in_r12 << 8;
              puVar7 = puVar8 + -1;
              in_r12 = *puVar7;
              bVar20 = (undefined4 *)0x3 < param_3;
              param_3 = param_3 + -1;
              puVar12 = (undefined4 *)(uVar9 | in_r12 >> 0x18);
              piVar2 = piVar2 + -1;
              *piVar2 = (int)puVar12;
            } while (bVar20);
            piVar6 = (int *)((int)puVar8 + -1);
          }
        }
      }
    }
    uVar16 = (undefined)in_r12;
    uVar10 = SUB41(puVar12,0);
    bVar21 = (bool)((byte)((uint)param_3 >> 1) & 1);
    uVar9 = (int)param_3 << 0x1f;
    bVar20 = (int)uVar9 < 0;
    if (bVar21) {
      uVar10 = *(undefined *)((int)piVar6 + -1);
      piVar6 = (int *)((int)piVar6 + -2);
      uVar16 = *(undefined *)piVar6;
    }
    if (bVar20) {
      uVar9 = (uint)*(byte *)((int)piVar6 + -1);
    }
    if (bVar21) {
      *(undefined *)((int)piVar2 + -1) = uVar10;
      piVar2 = (int *)((int)piVar2 + -2);
      *(undefined *)piVar2 = uVar16;
    }
    if (bVar20) {
      *(char *)((int)piVar2 + -1) = (char)uVar9;
    }
    return CONCAT44(piVar6,piVar2);
  }
  if ((undefined4 *)0x3 < param_3) {
    uVar9 = (uint)param_1 & 3;
    in_r12 = uVar9;
    if (uVar9 != 0) {
      uVar10 = *(undefined *)param_2;
      puVar12 = (undefined4 *)((int)param_2 + 1);
      if (uVar9 < 3) {
        puVar12 = (undefined4 *)((int)param_2 + 2);
        in_r12 = (uint)*(byte *)(undefined4 *)((int)param_2 + 1);
      }
      *(undefined *)param_1 = uVar10;
      param_2 = puVar12;
      if (uVar9 < 2) {
        param_2 = (undefined4 *)((int)puVar12 + 1);
        uVar10 = *(undefined *)puVar12;
      }
      puVar12 = (undefined4 *)((int)param_1 + 1);
      if (uVar9 < 3) {
        puVar12 = (undefined4 *)((int)param_1 + 2);
        *(char *)(undefined4 *)((int)param_1 + 1) = (char)in_r12;
      }
      param_3 = (undefined4 *)((int)param_3 + (uVar9 - 4));
      param_1 = puVar12;
      if (uVar9 < 2) {
        param_1 = (undefined4 *)((int)puVar12 + 1);
        *(undefined *)puVar12 = uVar10;
      }
    }
    puVar12 = (undefined4 *)((uint)param_2 & 3);
    if (puVar12 == (undefined4 *)0x0) {
      while (puVar1 = param_3 + -8, (undefined4 *)0x1f < param_3) {
        uVar14 = param_2[1];
        uVar17 = param_2[2];
        uVar19 = param_2[3];
        *param_1 = *param_2;
        param_1[1] = uVar14;
        param_1[2] = uVar17;
        param_1[3] = uVar19;
        puVar12 = (undefined4 *)param_2[4];
        uVar14 = param_2[5];
        uVar17 = param_2[6];
        uVar19 = param_2[7];
        param_2 = param_2 + 8;
        param_1[4] = puVar12;
        param_1[5] = uVar14;
        param_1[6] = uVar17;
        param_1[7] = uVar19;
        param_1 = param_1 + 8;
        param_3 = puVar1;
      }
      if ((bool)((byte)((uint)puVar1 >> 4) & 1)) {
        puVar12 = (undefined4 *)*param_2;
        uVar14 = param_2[1];
        uVar17 = param_2[2];
        uVar19 = param_2[3];
        param_2 = param_2 + 4;
        *param_1 = puVar12;
        param_1[1] = uVar14;
        param_1[2] = uVar17;
        param_1[3] = uVar19;
        param_1 = param_1 + 4;
      }
      if ((int)param_3 << 0x1c < 0) {
        puVar12 = (undefined4 *)*param_2;
        uVar14 = param_2[1];
        param_2 = param_2 + 2;
        *param_1 = puVar12;
        param_1[1] = uVar14;
        param_1 = param_1 + 2;
      }
      puVar3 = param_1;
      puVar4 = param_2;
      if ((bool)((byte)((uint)puVar1 >> 2) & 1)) {
        puVar4 = param_2 + 1;
        puVar12 = (undefined4 *)*param_2;
        puVar3 = param_1 + 1;
        *param_1 = puVar12;
      }
      uVar11 = SUB42(puVar12,0);
      if (((uint)puVar1 & 3) != 0) {
        bVar21 = (bool)((byte)((uint)puVar1 >> 1) & 1);
        uVar9 = (int)param_3 << 0x1f;
        bVar20 = (int)uVar9 < 0;
        puVar12 = puVar4;
        if (bVar21) {
          puVar12 = (undefined4 *)((int)puVar4 + 2);
          uVar11 = *(undefined2 *)puVar4;
        }
        puVar1 = puVar12;
        if (bVar20) {
          puVar1 = (undefined4 *)((int)puVar12 + 1);
          uVar9 = (uint)*(byte *)puVar12;
        }
        puVar12 = puVar3;
        if (bVar21) {
          puVar12 = (undefined4 *)((int)puVar3 + 2);
          *(undefined2 *)puVar3 = uVar11;
        }
        puVar4 = puVar12;
        if (bVar20) {
          puVar4 = (undefined4 *)((int)puVar12 + 1);
          *(char *)puVar12 = (char)uVar9;
        }
        return CONCAT44(puVar1,puVar4);
      }
      return CONCAT44(puVar4,puVar3);
    }
    bVar20 = (undefined4 *)0x3 < param_3;
    param_3 = param_3 + -1;
    if (bVar20) {
      puVar7 = (uint *)((int)param_2 - (int)puVar12);
      in_r12 = *puVar7;
      puVar1 = param_1;
      if (puVar12 == (undefined4 *)0x2) {
        do {
          puVar8 = puVar7;
          uVar9 = in_r12 >> 0x10;
          puVar7 = puVar8 + 1;
          in_r12 = *puVar7;
          bVar20 = (undefined4 *)0x3 < param_3;
          param_3 = param_3 + -1;
          puVar12 = (undefined4 *)(uVar9 | in_r12 << 0x10);
          param_1 = puVar1 + 1;
          *puVar1 = puVar12;
          puVar1 = param_1;
        } while (bVar20);
        param_2 = (undefined4 *)((int)puVar8 + 6);
      }
      else {
        if (puVar12 < (undefined4 *)0x3) {
          do {
            puVar8 = puVar7;
            uVar9 = in_r12 >> 8;
            puVar7 = puVar8 + 1;
            in_r12 = *puVar7;
            bVar20 = (undefined4 *)0x3 < param_3;
            param_3 = param_3 + -1;
            puVar12 = (undefined4 *)(uVar9 | in_r12 << 0x18);
            param_1 = puVar1 + 1;
            *puVar1 = puVar12;
            puVar1 = param_1;
          } while (bVar20);
          param_2 = (undefined4 *)((int)puVar8 + 5);
        }
        else {
          do {
            puVar8 = puVar7;
            uVar9 = in_r12 >> 0x18;
            puVar7 = puVar8 + 1;
            in_r12 = *puVar7;
            bVar20 = (undefined4 *)0x3 < param_3;
            param_3 = param_3 + -1;
            puVar12 = (undefined4 *)(uVar9 | in_r12 << 8);
            param_1 = puVar1 + 1;
            *puVar1 = puVar12;
            puVar1 = param_1;
          } while (bVar20);
          param_2 = (undefined4 *)((int)puVar8 + 7);
        }
      }
    }
  }
  uVar16 = (undefined)in_r12;
  uVar10 = SUB41(puVar12,0);
  bVar21 = (bool)((byte)((uint)param_3 >> 1) & 1);
  uVar9 = (int)param_3 << 0x1f;
  bVar20 = (int)uVar9 < 0;
  if (bVar21) {
    puVar5 = (undefined *)((int)param_2 + 1);
    uVar10 = *(undefined *)param_2;
    param_2 = (undefined4 *)((int)param_2 + 2);
    uVar16 = *puVar5;
  }
  puVar12 = param_2;
  if (bVar20) {
    puVar12 = (undefined4 *)((int)param_2 + 1);
    uVar9 = (uint)*(byte *)param_2;
  }
  if (bVar21) {
    puVar5 = (undefined *)((int)param_1 + 1);
    *(undefined *)param_1 = uVar10;
    param_1 = (undefined4 *)((int)param_1 + 2);
    *puVar5 = uVar16;
  }
  puVar1 = param_1;
  if (bVar20) {
    puVar1 = (undefined4 *)((int)param_1 + 1);
    *(char *)param_1 = (char)uVar9;
  }
  return CONCAT44(puVar12,puVar1);
}

//---------------------------------------------------------------------------------------
//Probably some standard lib function. Also used by memcpy

undefined8 FUN_80000804(undefined4 *param_1,undefined4 *param_2,uint param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  uint uVar4;
  undefined2 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  bool bVar9;
  bool bVar10;
  
  uVar4 = param_3 - 0x20;
  if (0x1f < param_3) {
    do {
      uVar6 = param_2[1];
      uVar7 = param_2[2];
      uVar8 = param_2[3];
      bVar9 = 0x1f < uVar4;
      uVar4 = uVar4 - 0x20;
      *param_1 = *param_2;
      param_1[1] = uVar6;
      param_1[2] = uVar7;
      param_1[3] = uVar8;
      param_4 = param_2[4];
      uVar6 = param_2[5];
      uVar7 = param_2[6];
      uVar8 = param_2[7];
      param_2 = param_2 + 8;
      param_1[4] = param_4;
      param_1[5] = uVar6;
      param_1[6] = uVar7;
      param_1[7] = uVar8;
      param_1 = param_1 + 8;
    } while (bVar9);
  }
  if ((bool)((byte)(uVar4 >> 4) & 1)) {
    param_4 = *param_2;
    uVar6 = param_2[1];
    uVar7 = param_2[2];
    uVar8 = param_2[3];
    param_2 = param_2 + 4;
    *param_1 = param_4;
    param_1[1] = uVar6;
    param_1[2] = uVar7;
    param_1[3] = uVar8;
    param_1 = param_1 + 4;
  }
  if ((int)(uVar4 << 0x1c) < 0) {
    param_4 = *param_2;
    uVar6 = param_2[1];
    param_2 = param_2 + 2;
    *param_1 = param_4;
    param_1[1] = uVar6;
    param_1 = param_1 + 2;
  }
  puVar1 = param_1;
  puVar3 = param_2;
  if ((bool)((byte)(uVar4 >> 2) & 1)) {
    puVar3 = param_2 + 1;
    param_4 = *param_2;
    puVar1 = param_1 + 1;
    *param_1 = param_4;
  }
  uVar5 = (undefined2)param_4;
  if ((uVar4 & 3) != 0) {
    bVar10 = (bool)((byte)(uVar4 >> 1) & 1);
    uVar4 = uVar4 << 0x1f;
    bVar9 = (int)uVar4 < 0;
    puVar2 = puVar3;
    if (bVar10) {
      puVar2 = (undefined4 *)((int)puVar3 + 2);
      uVar5 = *(undefined2 *)puVar3;
    }
    puVar3 = puVar2;
    if (bVar9) {
      puVar3 = (undefined4 *)((int)puVar2 + 1);
      uVar4 = (uint)*(byte *)puVar2;
    }
    puVar2 = puVar1;
    if (bVar10) {
      puVar2 = (undefined4 *)((int)puVar1 + 2);
      *(undefined2 *)puVar1 = uVar5;
    }
    puVar1 = puVar2;
    if (bVar9) {
      puVar1 = (undefined4 *)((int)puVar2 + 1);
      *(char *)puVar2 = (char)uVar4;
    }
    return CONCAT44(puVar3,puVar1);
  }
  return CONCAT44(puVar3,puVar1);
}

//---------------------------------------------------------------------------------------


