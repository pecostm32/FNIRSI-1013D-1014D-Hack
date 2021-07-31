//---------------------------------------------------------------------------------------

//There is some global struct in use for the display system

void FUN_8001936c(void)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  piVar1 = DAT_80019410;                              //0x8019D4D4  Base address
  if (DAT_80019410[3] != 0)                           //0x8019d4e0
  {
    iVar2 = FUN_80019ab8();                           //Function returns a zero

    if (iVar2 == piVar1[1]) goto LAB_8001939c;        //0x8019d4d8
  }

  empty_func_3();

  iVar2 = FUN_80019ab8();                             //Function returns a zero

  piVar1[1] = iVar2;                                  //0x8019d4d8 is made 0

LAB_8001939c:
  iVar2 = piVar1[3];                                  //Get data from 0x8019d4e0
  piVar1[3] = iVar2 + 1;                              //Add one to it

  if (iVar2 + 1 == 1)                                 //If it was zero do the next bit
  {
    iVar2 = FUN_8002f92c();

    if (iVar2 != *piVar1)                             //If content of 0x8019D4D4 not equal to iVar2
    {
      if (-1 < *piVar1)                               //and *piVar1 >= 0
      {
        uVar3 = FUN_80018964();

        iVar4 = piVar1[4];
        *(undefined4 *)(iVar4 + *piVar1 * 0x78 + 0x74) = uVar3;
        iVar4 = iVar4 + iVar2 * 0x78;
        *DAT_80019414 = iVar4 + 4;                    //Store to address 0x8019D470

        FUN_8001893c(*(undefined4 *)(iVar4 + 0x74));
      }

      *piVar1 = iVar2;
    }
  }

  return;
}

//---------------------------------------------------------------------------------------

int FUN_8002f92c(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar1 = DAT_8002f980;                                  //0x8019D4D4
  iVar5 = 0;

  while( true )
  {
    if (*(int *)(iVar1 + 8) <= iVar5)
    {
      return 0;
    }

    iVar2 = FUN_80019ab8();                              //Function returns a zero

    iVar4 = *(int *)(iVar1 + 0x10);
    iVar3 = *(int *)(iVar4 + iVar5 * 0x78);

    if (iVar3 == iVar2)
      break;

    if (iVar3 == 0)
    {
      *(int *)(iVar4 + iVar5 * 0x78) = iVar2;
      return iVar5;
    }

    iVar5 = iVar5 + 1;
  }

  return iVar5;
}

//---------------------------------------------------------------------------------------

uint * FUN_80018964(uint *param_1)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  uint **ppuVar4;
  int iVar5;
  int iVar6;
  uint **ppuVar7;
  
  puVar3 = PTR_DAT_800189cc;
  iVar2 = DAT_800189c8;
  ppuVar7 = (uint **)0x0;
  iVar5 = 0;

  do
  {
    ppuVar4 = *(uint ***)(iVar2 + iVar5 * 4);

    while (ppuVar4 != (uint **)0x0)
    {
      param_1 = (uint *)(uint)(byte)puVar3[*ppuVar4[3]];

      if (param_1 != (uint *)0x0)
      {
        param_1 = (uint *)FUN_800306e0(ppuVar4);

        *ppuVar4 = (uint *)ppuVar7;
        ppuVar7 = ppuVar4;
      }

      ppuVar4 = (uint **)*ppuVar4;
    }

    iVar6 = iVar5 + 1;
    iVar1 = iVar5 + -1;

    if (1 < iVar6)
    {
      param_1 = (uint *)ppuVar7;
    }

    iVar5 = iVar6;
  } while (iVar1 < 0 != SBORROW4(iVar6,2));

  return param_1;
}

//---------------------------------------------------------------------------------------

void FUN_8001893c(int *param_1)

{
  while (param_1 != (int *)0x0) {
    param_1 = (int *)*param_1;
    FUN_8001884c();
  }
  return;
}

//---------------------------------------------------------------------------------------

void FUN_800306e0(int *param_1)

{
  if (*(int **)(DAT_80030728 + param_1[6] * 4) == param_1)
  {
    *(int *)(DAT_80030728 + param_1[6] * 4) = *param_1;
  }

  if ((int *)param_1[1] != (int *)0x0)
  {
    *(int *)param_1[1] = *param_1;
  }

  if (*param_1 != 0)
  {
    *(int *)(*param_1 + 4) = param_1[1];
  }

  *param_1 = 0;
  param_1[1] = 0;
  return;
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


