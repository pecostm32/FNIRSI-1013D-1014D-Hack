//display_text is called from 65 locations
//What is strange is that so far no coupling with a screen buffer is found. None of the functions found in the display (screen buffers) analysis is called, at least not directly.

//Initial data
//0x8019D464: 0x00000000
//0x8019D468: 0x80189750
//0x8019D46C: 0x8001CF3C
//0x8019D470: 0x80857D4C

//0x8019d47C: 0x00000000


//0x8019D468: 0x3C, 0xCF, 0x01, 0x80,
//0x8019D46C: 0x50, 0x97, 0x18, 0x80,
//0x8019D470: 0x4C, 0x7D, 0x85, 0x80,
//0x8019D474: 0x00, 0x00, 0x00, 0x00,
//0x8019D478: 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x8019D4AC: 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
//0x8019D4B4: 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
//0x8019D4CC: 0x68, 0xFD, 0x02, 0x80, 0x00, 0x00, 0x00, 0x00, 
//0x8019D4D4: 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 
//0x8019D4DC: 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
//0x8019D4F0: 0x24, 0x18, 0x19, 0x80, 0x00, 
//0x8019D4F5: 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
//0x8019D57C: 0xFC, 0x7D, 0x85, 0x80, 0xFC, 0x7D, 0x85, 0x80, 
//0x8019D584: 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
//0x8019D590: 0xB4, 0x9A, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 



//0x8019D470 This address needs to be researched!!!
//0x8019D4D4 Same for this address

//0x8019D5A0 End of preset data segment

//---------------------------------------------------------------------------------------

void display_text(char *text,ushort xpos,ushort ypos)

{
  int iVar1;
  
  FUN_8001936c();                               //Used by several functions. Some kind of context save???

  iVar1 = *DAT_80018c2c;                        //0x8019D470. This is some pointer holder which points to a struct. Might be a same system as for the screen buffers

  *(ushort *)(iVar1 + 0x22) = xpos;
  *(ushort *)(iVar1 + 0x24) = ypos;

  FUN_80018a74(text);

  //Next bit is FUN_80019a6c
  iVar1 = *(int *)(DAT_80019a84 + 0xc) + -1;
  *(int *)(DAT_80019a84 + 0xc) = iVar1;

  if (iVar1 != 0) 
  {
    return;
  }

  return;
}

//---------------------------------------------------------------------------------------

//There is some global struct in use for the display system

//Could this be some save context function???
//Or a lock function, because it is used in many functions at the beginning
//FUN_80019a6c seems to be a counter part since it is used at the end of many functions (restore context?? or unlock))
//This one seems to decrease a value in a global variable

void FUN_8001936c(void)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  piVar1 = DAT_80019410;                              //0x8019D4D4  Base address
  if (DAT_80019410[3] != 0)                           //0x8019d4e0 != 0
  {
    iVar2 = FUN_80019ab8();                           //Function returns a zero

    if (iVar2 == piVar1[1])                           //0x8019d4d8 == 0
      goto LAB_8001939c;
  }

  empty_func_3();

  iVar2 = FUN_80019ab8();                             //Function returns a zero

  piVar1[1] = iVar2;                                  //0x8019d4d8 is made 0

LAB_8001939c:                                         //At this point piVar1[1] (0x8019d4d8) is zero

  iVar2 = piVar1[3];                                  //Get data from 0x8019d4e0
  piVar1[3] = iVar2 + 1;                              //Add one to it

  if (iVar2 + 1 == 1)                                 //If it was zero do the next bit, so only the first time this is called in a sequence the next bit is done
  {
    iVar2 = FUN_8002f92c();                           //Results always in 0?????

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

void FUN_80019a6c(void)

{
  int iVar1;
  
  iVar1 = *(int *)(DAT_80019a84 + 0xc) + -1;                           //r0 = 0x8019D4D4; r1 = data from r0 + 0x0C; (0x8019d4e0); r1 = r1 - 1; r1 stored back into 0x8019d4e0;
  *(int *)(DAT_80019a84 + 0xc) = iVar1;

  if (iVar1 != 0)
  {
    return;
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
    if (*(int *)(iVar1 + 8) <= iVar5)                    //*0x8019d4dc <= iVar5
    {
      return 0;
    }

    iVar2 = FUN_80019ab8();                              //Function returns a zero

    iVar4 = *(int *)(iVar1 + 0x10);                      //*0x8019d4e4 ==> pointer to some where (r2)
    iVar3 = *(int *)(iVar4 + iVar5 * 0x78);              //iVar5 (r4) * 120

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
  while (param_1 != (int *)0x0)
  {
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
//This function is only used by display_text
//param_1 is pointer to the text
//param_2 holds the content of address 0x8019D470
//param_3 is still the ypos (r2)
//param_4 is not set (r3)


void FUN_80018a74(char *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined2 uVar1;
  short sVar2;
  int *piVar3;
  byte bVar4;
  short sVar5;
  short sVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined4 local_28;
  undefined4 local_24;
  
  if (param_1 != (char *)0x0)                                          //Check on a NULL pointer
  {
    local_28 = param_3;                                                //r2 and r3 are pushed onto stack and assumed as locals
    local_24 = param_4;

    FUN_8001936c();                                                    //This function is called many times at the start of functions. Save context??

    sVar5 = FUN_80019210();                                            //Get some data via pointer structure??

    piVar3 = DAT_80018bf0;                                             //0x8019D470
    uVar1 = *(undefined2 *)(*DAT_80018bf0 + 0x22);                     //In the struct on 0x22 is the xpos

    sVar6 = FUN_8001925c();                                            //Get font base line???

    *(short *)(*piVar3 + 0x24) = *(short *)(*piVar3 + 0x24) - sVar6;   //In the struct on 0x24 is the ypos. Some font base line subtract

    while (*param_1 != '\0')                                           //Handle the characters until the terminating 0x00
    {
      uVar7 = FUN_80019eb0(param_1,DAT_80018bf4);                      //DAT_80018bf4 = 0x00007FFF. param_1 is used as character pointer and is incremented at the end of this while loop

      iVar8 = FUN_80019e0c(param_1,uVar7);

      iVar10 = *piVar3;
      bVar4 = *(byte *)(iVar10 + 0x2c) & 3;
      iVar9 = iVar8;

      if (bVar4 != 1)
      {
        if (bVar4 == 2)
        {
          iVar9 = iVar8 / 2;
        }
        else
        {
          iVar9 = 0;
        }
      }

      sVar2 = *(short *)(iVar10 + 0x22) - (short)iVar9;
      *(short *)(iVar10 + 0x22) = sVar2;
      local_28 = CONCAT22(*(short *)(iVar10 + 0x24),sVar2);
      local_24 = CONCAT22(*(short *)(iVar10 + 0x24) + sVar5 + -1,sVar2 + (short)iVar8 + -1);

      FUN_80019cd8(param_1,uVar7,&local_28);

      *(undefined2 *)(*piVar3 + 0x24) = local_28._2_2_;

      iVar9 = FUN_80019988(param_1,uVar7);

      param_1 = param_1 + iVar9;

      if (*param_1 == '\n' || *param_1 == '\r')                           //Check on carriage return and linefeed
      {
        iVar9 = *piVar3;
        bVar4 = *(byte *)(iVar9 + 0x2c) & 3;

        if (bVar4 == 1 || bVar4 == 2)
        {
          *(undefined2 *)(iVar9 + 0x22) = uVar1;
        }
        else
        {
          *(undefined2 *)(iVar9 + 0x22) = *(undefined2 *)(iVar9 + 0x20);
        }

        if (*param_1 == '\n')                                             //Adjust the ypos when a new line (linefeed) is given
        {
          *(short *)(iVar9 + 0x24) = *(short *)(iVar9 + 0x24) + sVar5;
        }
      }
      else
      {
        *(short *)(*piVar3 + 0x22) = (short)local_28 + (short)iVar8;
      }

      if (*param_1 == '\0')
        break;

      param_1 = param_1 + 1;
    }

    iVar9 = *piVar3;
    *(short *)(iVar9 + 0x24) = *(short *)(iVar9 + 0x24) + sVar6;          //Update ypos
    *(ushort *)(iVar9 + 0x2c) = *(ushort *)(iVar9 + 0x2c) & 0xfffc;

    FUN_80019a6c();
  }
  return;
}

//---------------------------------------------------------------------------------------

undefined FUN_80019210(void)

{
  undefined uVar1;
  
  FUN_8001936c();   //??

  uVar1 = *(undefined *)(*(int *)(*DAT_80019238 + 0x1c) + 0x19);       //0x8019D470.  Get pointer from 0x8019D470. Load from the address found + 0x1C yet another pointer. Index this pointer with 0x19 and load a byte from it.

  FUN_80019a6c();   //??

  return uVar1;
}

//---------------------------------------------------------------------------------------
//Get some font metrics?????
//Only called from FUN_80018a74

uint FUN_8001925c(void)

{
  int iVar1;
  byte bVar2;
  uint uVar3;
  
  uVar3 = 0;

  FUN_8001936c();                                  //Save context

  iVar1 = *DAT_800192b0;                           //*0x8019D470
  bVar2 = *(byte *)(iVar1 + 0x2c) & 0xc;           //on byte 0x2C with in a struct is some data

  if (bVar2 == 4)                                  //If it is 4
  {
    uVar3 = *(byte *)(*(int *)(iVar1 + 0x1c) + 0x18) - 1;  //Get a pointer from 0x1C in the struct and from index 0x18 get the data and subtract 1
  }
  else
  {
    if (bVar2 == 8 || bVar2 == 0xc)                //if the byte is 8 or 12
    {
      uVar3 = (uint)(*(byte *)(*(int *)(iVar1 + 0x1c) + 0x18) >> 1);  //Get a pointer from 0x1C in the struct and from index 0x18 get the data and divide by 2
    }
  }

  FUN_80019a6c();                                  //Restore context

  return uVar3;
}

//---------------------------------------------------------------------------------------
//Called with pointer to the characters
//param_2 = 0x7FFF


int FUN_80019eb0(int param_1,int param_2,code *param_3)

{
  int iVar1;
  int iVar2;
  int local_18;  //Is param_1
  int iStack20;
  
  iVar2 = 0;
  if (param_1 != 0)
  {
    iVar1 = *(int *)(*(int *)(*DAT_80019f24 + 0x1c) + 0x14);    //0x8019D470 Get a pointer from 0x1C in the struct and from index 0x14 get the data which is a pointer???

    if (iVar1 != 0)
    {
      param_3 = *(code **)(iVar1 + 4);                          //get a function pointer from the given struct address + 4;
    }

    local_18 = param_1;
    iStack20 = param_2;

    if (iVar1 != 0 && param_3 != (code *)0x0)                   //If the function pointer is set call it and get a value
    {
      iVar2 = (*param_3)(param_1,param_2);
    }
    else 
    {
      while ((iVar2 < param_2 && (iVar1 = FUN_80019934(&local_18), iVar1 != 0 && iVar1 != 10)))  //Loop through calling this function max param_2 times
      {
        iVar2 = iVar2 + 1;
      }
    }
  }
  return iVar2;
}

//---------------------------------------------------------------------------------------
//Need to know what is on addresses 0x8019D474 and 0x8019D478

undefined4 FUN_80019934(int *param_1)

{
  code **ppcVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  ppcVar1 = DAT_80019984;    //0x8019D474
  iVar4 = *param_1;

  uVar2 = (**(code **)*DAT_80019984)(iVar4);

  iVar3 = (**(code **)(*ppcVar1 + 4))(iVar4);

  *param_1 = iVar3 + iVar4;

  return uVar2;
}

//---------------------------------------------------------------------------------------

int FUN_80019e0c(int param_1,int param_2)

{
  int iVar1;
  code **ppcVar2;
  code *pcVar3;
  int iVar4;
  undefined4 uVar5;
  int local_18;
  int local_14;
  
  pcVar3 = *DAT_80019ea8;
  local_18 = param_1;
  local_14 = param_2;
  local_18 = (*pcVar3)(param_1,&local_14);
  iVar4 = 0;

  if (local_18 != 0)
  {
    uVar5 = 0;
    ppcVar2 = *(code ***)(*(int *)(*DAT_80019eac + 0x1c) + 0x14);

    if (ppcVar2 != (code **)0x0)
    {
      pcVar3 = *ppcVar2;
    }

    if (ppcVar2 != (code **)0x0 && pcVar3 != (code *)0x0)
    {
      iVar4 = (*pcVar3)(local_18,local_14);
    }
    else
    {
      while (local_14 = local_14 + -1, -1 < local_14)
      {
        uVar5 = FUN_80019934(&local_18);

        iVar1 = FUN_80019160();

        iVar4 = iVar4 + iVar1;
      }

      iVar1 = FUN_80019f28(uVar5);

      iVar4 = iVar4 + iVar1;
    }
  }
  return iVar4;
}

//---------------------------------------------------------------------------------------

undefined4 FUN_80019160(undefined4 param_1)

{
  undefined4 uVar1;
  
  FUN_8001936c();

  uVar1 = (**(code **)(*(int *)(*DAT_800191a0 + 0x1c) + 4))(param_1,0);

  FUN_80019a6c();
  return uVar1;
}

//---------------------------------------------------------------------------------------

int FUN_80019f28(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int local_10;
  
  iVar2 = 0;
  local_10 = 0;

  iVar1 = FUN_800191a4(param_1,&local_10);

  if (iVar1 < local_10)
  {
    iVar2 = local_10 - iVar1;
  }

  return iVar2;
}

//---------------------------------------------------------------------------------------

undefined4 FUN_800191a4(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  FUN_8001936c();

  uVar1 = (**(code **)(*(int *)(*DAT_800191e8 + 0x1c) + 4))(param_1,param_2);

  FUN_80019a6c();

  return uVar1;
}

//---------------------------------------------------------------------------------------

void FUN_80019cd8(undefined4 param_1,undefined4 param_2,void *param_3,undefined4 param_4)

{
  int *piVar1;
  int iVar2;
  undefined4 local_18;
  undefined4 local_14;
  
  local_18 = param_3;
  local_14 = param_4;

  if (*DAT_80019de4 == 0)
  {
    memcpy(&local_18,param_3,8);

    piVar1 = DAT_80019de8;
    iVar2 = *DAT_80019de8;
    local_18 = (void *)CONCAT22((short)((uint)local_18 >> 0x10) + *(short *)(iVar2 + 0x50),(short)local_18 + *(short *)(iVar2 + 0x4c));
    local_14 = CONCAT22((short)((uint)local_14 >> 0x10) + *(short *)(iVar2 + 0x50),(short)local_14 + *(short *)(iVar2 + 0x4c));

    iVar2 = FUN_8002ac10(&local_18);

    while (iVar2 != 0)
    {
      iVar2 = *piVar1;
      *(short *)(iVar2 + 0x22) = (short)local_18;
      *(undefined2 *)(iVar2 + 0x24) = local_18._2_2_;

      FUN_8002d2f0(param_1,param_2,&local_18);

      iVar2 = FUN_8002ab40();
    }

    iVar2 = *piVar1;
    *(short *)(iVar2 + 0x22) = *(short *)(iVar2 + 0x22) - *(short *)(iVar2 + 0x4c);
    *(short *)(iVar2 + 0x24) = *(short *)(iVar2 + 0x24) - *(short *)(iVar2 + 0x50);
  }
  else
  {
    iVar2 = FUN_8002ac10(0);

    while (iVar2 != 0)
    {
      FUN_8002d2f0(param_1,param_2,&local_18);

      iVar2 = FUN_8002ab40();
    }
  }
  return;
}

//---------------------------------------------------------------------------------------

undefined4 FUN_8002ac10(int param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  char *pcVar3;
  int iVar4;
  undefined4 **ppuVar5;
  undefined4 uVar6;
  int iVar7;
  longlong lVar8;
  undefined4 *local_30;
  undefined4 uStack44;
  undefined4 uStack40;
  undefined4 *local_24;
  undefined auStack32 [12];
  
  puVar2 = DAT_8002ada0;
  piVar1 = DAT_8002ad9c;
  iVar4 = *DAT_8002ad9c;
  ppuVar5 = &local_30;

  if (*(char *)(iVar4 + 0x54) == '\0')
  {
    FUN_8002a9a4();

    return 1;
  }

  iVar7 = DAT_8002ada0[5];
  DAT_8002ada0[5] = iVar7 + 1;

  if (1 < iVar7 + 1)
  {
    return 1;
  }

  local_30 = (undefined4 *)FUN_8001857c(*(undefined4 *)(iVar4 + 0x48));

  pcVar3 = DAT_8002ada4;
  puVar2[4] = 0xffffffff;

  if (*pcVar3 == '\0')
  {
    if ((*(byte *)(local_30 + 10) & 2) == 0)
    {
      puVar2[5] = puVar2[5] + -1;

      FUN_800185cc(&local_30);

      return 0;
    }

    uStack44 = *local_30;
    uStack40 = local_30[1];
  }
  else
  {
    memcpy(&uStack44,local_30 + 2,8);
  }

  if (param_1 != 0)
  {
    FUN_80019f54(&uStack44,param_1);
  }

  if (*(int *)(*piVar1 + 0x44) != 0)
  {
    local_24 = local_30;
    lVar8 = memcpy(auStack32,*(void **)(*piVar1 + 0x44),8);

    if (*(int *)(pcVar3 + 0x28) != 0)
    {
      FUN_800185cc(&local_24,(int)((ulonglong)lVar8 >> 0x20));

      local_24 = (undefined4 *)FUN_8001857c(*(undefined4 *)(pcVar3 + 0x28));
    }

    FUN_8002aa24(local_24,auStack32);

    FUN_80019f54(&uStack44,auStack32);

    ppuVar5 = &local_24;
  }

  FUN_800185cc(ppuVar5);

  if (((*(int *)(pcVar3 + 0x28) == 0) || (iVar4 = FUN_8002aa38(&uStack44), iVar4 != 0)) && (iVar4 = FUN_8002aa38(&uStack44,*(undefined4 *)(*piVar1 + 0x48)), iVar4 != 0))
  {
    *puVar2 = uStack44;
    puVar2[1] = uStack40;

    uVar6 = FUN_8002ab40();

    return uVar6;
  }

  puVar2[5] = puVar2[5] + -1;
  return 0;
}

//---------------------------------------------------------------------------------------

void FUN_8002d2f0(undefined4 param_1,int param_2,undefined4 param_3)

{
  int *piVar1;
  code **ppcVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 local_20;
  int local_1c;
  undefined4 uStack24;
  
  local_20 = param_1;
  local_1c = param_2;
  uStack24 = param_3;
  local_20 = (**DAT_8002d3c4)(param_1,&local_1c);
  piVar1 = DAT_8002d3c8;

  if ((*(int *)(*DAT_8002d3c8 + 0x14) == 0) || (iVar3 = FUN_8001962c(*(int *)(*DAT_8002d3c8 + 0x14),param_3), iVar3 != 0))
  {
    FUN_8001a004(1);

    ppcVar2 = DAT_8002d3cc;
    iVar3 = *(int *)(*(int *)(*piVar1 + 0x1c) + 0x14);

    if (iVar3 == 0)
    {
      while (local_1c = local_1c + -1, -1 < local_1c)
      {
        uVar4 = FUN_80019934(&local_20);

        (***(code ***)(*piVar1 + 0x1c))(uVar4);

        if (*ppcVar2 != (code *)0x0)
        {
                    // WARNING: Could not recover jumptable at 0x8002d3a0. Too many branches
                    // WARNING: Treating indirect jump as call
          (**ppcVar2)(uVar4);
          return;
        }
      }
    }
    else
    {
      (**(code **)(iVar3 + 8))(local_20,local_1c);
    }

    FUN_8001a004(0);
  }
  return;
}

//---------------------------------------------------------------------------------------

char FUN_8002ab40(void)

{
  int iVar1;
  char cVar2;
  int iVar3;
  
  iVar1 = DAT_8002aba8;

  cVar2 = *(char *)(*DAT_8002aba4 + 0x54);

  if (cVar2 != '\0')
  {
    iVar3 = *(int *)(DAT_8002aba8 + 0x14);

    if (iVar3 < 2)
    {
      *(int *)(DAT_8002aba8 + 0x10) = *(int *)(DAT_8002aba8 + 0x10) + 1;

      iVar3 = FUN_8002f168();

      if (iVar3 != 0)
      {
        FUN_8002a9a4();

        return '\x01';
      }

      iVar3 = *(int *)(iVar1 + 0x14);
    }

    *(int *)(iVar1 + 0x14) = iVar3 + -1;
    cVar2 = '\0';
  }

  return cVar2;
}

//---------------------------------------------------------------------------------------

int FUN_80019988(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  
  piVar1 = DAT_800199d0;
  iVar3 = 0;

  while (bVar4 = param_2 != 0, param_2 = param_2 + -1, bVar4)
  {
    iVar2 = (**(code **)(*piVar1 + 4))(param_1);
    param_1 = param_1 + iVar2;
    iVar3 = iVar3 + iVar2;
  }

  return iVar3;
}


//---------------------------------------------------------------------------------------

void FUN_8002a9a4(undefined4 param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  undefined4 *local_10;
  undefined4 uStack12;
  undefined4 uStack8;
  
  puVar1 = DAT_8002aa04;
  local_10 = param_2;
  uStack12 = param_3;
  uStack8 = param_4;

  if (*(char *)(*DAT_8002aa00 + 0x54) == '\0')
  {
    local_10 = (undefined4 *)FUN_8001857c(*(undefined4 *)(*DAT_8002aa00 + 0x48));

    uStack12 = *local_10;
    uStack8 = local_10[1];

    FUN_800185cc(&local_10);

    if (*(int *)(DAT_8002aa08 + 0x28) != 0)
    {
      FUN_8002aa38(&uStack12);
    }

    puVar1 = &uStack12;
  }

  FUN_800300c0(puVar1);
  return;
}

//---------------------------------------------------------------------------------------

int FUN_8001857c(int param_1)

{
  int iVar1;
  char *pcVar2;
  
  iVar1 = DAT_800185a0;
  *(int *)(DAT_800185a0 + 0x1c) = *(int *)(DAT_800185a0 + 0x1c) + 1;
  pcVar2 = (char *)(*(int *)(iVar1 + 0x34) + param_1 * 8);
  *pcVar2 = *pcVar2 + '\x01';

  if (param_1 == 0)
  {
    return 0;
  }

  return *(int *)(*(int *)(DAT_8001863c + 0x34) + param_1 * 8 + 4) + 8;
}

//---------------------------------------------------------------------------------------

undefined4 FUN_800185cc(int *param_1)

{
  byte *pbVar1;
  
  pbVar1 = (byte *)(*(int *)(DAT_80018618 + 0x34) + *(int *)(*param_1 + -8) * 8);

  if ((1 < *pbVar1) && (*(int *)(DAT_80018618 + 0x1c) != 0))
  {
    *(int *)(DAT_80018618 + 0x1c) = *(int *)(DAT_80018618 + 0x1c) + -1;
  }

  *pbVar1 = *pbVar1 - 1;
  *param_1 = 0;
  return 0;
}

//---------------------------------------------------------------------------------------

void FUN_80019f54(short *param_1,short *param_2)

{
  if (*param_1 < *param_2)
  {
    *param_1 = *param_2;
  }

  if (param_1[1] < param_2[1])
  {
    param_1[1] = param_2[1];
  }

  if (param_2[2] < param_1[2])
  {
    param_1[2] = param_2[2];
  }

  if (param_2[3] < param_1[3])
  {
    param_1[3] = param_2[3];
  }
  return;
}

//---------------------------------------------------------------------------------------

void FUN_8002aa24(short *param_1,short *param_2)

{
  short sVar1;
  short sVar2;
  
  sVar1 = param_1[1];
  sVar2 = *param_1;

  if (param_2 == (short *)0x0)
  {
    return;
  }

  *param_2 = *param_2 + sVar2;
  param_2[2] = sVar2 + param_2[2];
  param_2[1] = param_2[1] + sVar1;
  param_2[3] = param_2[3] + sVar1;
  return;
}

//---------------------------------------------------------------------------------------

undefined4 FUN_8002aa38(undefined4 param_1,int param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  int local_10;
  
  local_10 = param_4;

  while( true )
  {
    local_10 = FUN_8001857c(param_2);

    if ((*(byte *)(local_10 + 0x28) & 2) == 0)
    {
      FUN_800185cc(&local_10,local_10);

      return 0;
    }

    FUN_80019f54(param_1);

    iVar1 = *(int *)(local_10 + 0x18);

    if (iVar1 == 0)
      break;

    FUN_800185cc(&local_10);

    param_2 = iVar1;
  }

  FUN_800185cc(&local_10);

  iVar1 = FUN_8002d2c0(param_2);

  if (iVar1 < 0)
  {
    return 0;
  }

  return 1;
}

//---------------------------------------------------------------------------------------

short * FUN_8001962c(short *param_1,short *param_2)

{
  short *psVar1;
  short *psVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  bool bVar6;
  bool bVar7;
  
  iVar3 = (int)param_1[1];
  iVar5 = (int)param_2[3];
  bVar7 = SBORROW4(iVar3,iVar5);
  iVar4 = iVar3 - iVar5;
  bVar6 = iVar3 == iVar5;

  if (iVar3 <= iVar5)
  {
    iVar3 = (int)param_2[1];
    iVar5 = (int)param_1[3];
    bVar7 = SBORROW4(iVar3,iVar5);
    iVar4 = iVar3 - iVar5;
    bVar6 = iVar3 == iVar5;
  }

  if (bVar6 || iVar4 < 0 != bVar7)
  {
    iVar4 = (int)*param_1;
    iVar3 = (int)param_2[2];
    bVar7 = SBORROW4(iVar4,iVar3);
    psVar1 = (short *)(iVar4 - iVar3);
    bVar6 = iVar4 == iVar3;

    if (iVar4 <= iVar3)
    {
      psVar2 = (short *)(int)*param_2;
      param_1 = (short *)(int)param_1[2];
      bVar7 = SBORROW4((int)psVar2,(int)param_1);
      psVar1 = (short *)((int)psVar2 - (int)param_1);
      bVar6 = psVar2 == param_1;
    }

    if (bVar6 || (int)psVar1 < 0 != bVar7)
    {
      param_1 = (short *)0x1;
    }

    if (bVar6 || (int)psVar1 < 0 != bVar7)
    {
      return param_1;
    }
  }
  return (short *)0x0;
}

//---------------------------------------------------------------------------------------

undefined4 FUN_8001a004(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  code **ppcVar1;
  uint uVar2;
  code *pcVar3;
  code *UNRECOVERED_JUMPTABLE_00;
  code **ppcVar4;
  undefined4 uVar5;
  int local_20;
  
  ppcVar1 = DAT_8001a198;
  uVar2 = (uint)*(byte *)(*DAT_8001a018 + 0x11);
  uVar5 = 1;

  if (uVar2 < 2)
  {
    ppcVar4 = DAT_8001a198 + 1;
    local_20 = param_4;

    if (param_1 == 0)
    {
      if (((ppcVar4[uVar2] == (code *)0x1) && (local_20 = FUN_800189d0(uVar2), local_20 != 0)) && (pcVar3 = (code *)(**(code **)(*(int *)(local_20 + 0xc) + 0x24))(&local_20,0xd), pcVar3 != (code *)0x0))
      {
        UNRECOVERED_JUMPTABLE_00 = *ppcVar1;
        if (UNRECOVERED_JUMPTABLE_00 != (code *)0x0)
        {
                    // WARNING: Could not recover jumptable at 0x8001a168. Too many branches
                    // WARNING: Treating indirect jump as call
          uVar5 = (*UNRECOVERED_JUMPTABLE_00)();
          return uVar5;
        }

        (*pcVar3)(local_20,0);
        uVar5 = 0;
      }

      pcVar3 = ppcVar4[uVar2] + -(uint)(ppcVar4[uVar2] != (code *)0x0);
    }
    else
    {
      if (param_1 != 1)
      {
        if (param_1 != 2)
        {
          return 1;
        }

        local_20 = FUN_800189d0();

        if (local_20 == 0)
        {
          return 1;
        }

        pcVar3 = (code *)(**(code **)(*(int *)(local_20 + 0xc) + 0x24))(&local_20,0xd);

        if (pcVar3 == (code *)0x0)
        {
          return 1;
        }

        UNRECOVERED_JUMPTABLE_00 = *ppcVar1;
        if (UNRECOVERED_JUMPTABLE_00 == (code *)0x0)
        {
          (*pcVar3)(local_20,2);
          return 0;
        }
                    // WARNING: Could not recover jumptable at 0x8001a100. Too many branches
                    // WARNING: Treating indirect jump as call
        uVar5 = (*UNRECOVERED_JUMPTABLE_00)();
        return uVar5;
      }

      pcVar3 = ppcVar4[uVar2];

      if (pcVar3 == (code *)0x0)
      {
        local_20 = FUN_800189d0(uVar2);

        if (local_20 == 0)
        {
          return 1;
        }

        pcVar3 = (code *)(**(code **)(*(int *)(local_20 + 0xc) + 0x24))(&local_20,0xd);

        if (pcVar3 == (code *)0x0)
        {
          return 1;
        }

        (*pcVar3)(local_20,1);
        pcVar3 = ppcVar4[uVar2];
        uVar5 = 0;
      }

      pcVar3 = pcVar3 + 1;
    }

    ppcVar4[uVar2] = pcVar3;
  }
  return uVar5;
}

//---------------------------------------------------------------------------------------

undefined8 FUN_8002f168(void)

{
  short *psVar1;
  int *piVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int in_r3;
  undefined4 local_20;
  uint local_1c;
  int local_18;
  
  psVar1 = DAT_8002f358;
  local_1c = *(uint *)(DAT_8002f358 + 6);
  local_18 = in_r3;

  if (*(int *)(DAT_8002f358 + 8) == 0)
  {
    local_20._0_2_ = *DAT_8002f358;
    sVar3 = DAT_8002f358[1];
    goto LAB_8002f1cc;
  }

  iVar4 = ((ushort)DAT_8002f358[6] + 1) * 0x10000;
  local_20 = CONCAT22(DAT_8002f358[5],(short)((uint)iVar4 >> 0x10));

  if (iVar4 >> 0x10 <= (int)DAT_8002f358[2])
    goto LAB_8002f1d0;

  do
  {
    local_20._0_2_ = *psVar1;
    sVar3 = psVar1[7] + 1;
LAB_8002f1cc:
    local_20 = CONCAT22(sVar3,(short)local_20);
LAB_8002f1d0:
    piVar2 = DAT_8002f35c;

    if (psVar1[3] < local_20._2_2_)
      goto LAB_8002f338;

    local_18 = FUN_8001857c(*(undefined4 *)(*DAT_8002f35c + 0x48));

    if ((short)local_20 == *psVar1)
    {
      local_1c = *(uint *)(psVar1 + 2);
      iVar4 = *(int *)(*piVar2 + 0x48);

      while (iVar4 != 0)
      {
        iVar4 = FUN_8001861c();

        FUN_8002f4f8(*(undefined4 *)(iVar4 + 0x20),&local_20,0);

        iVar4 = *(int *)(iVar4 + 0x18);
      }

      FUN_8002f4f8(*(undefined4 *)(local_18 + 0x1c),&local_20,0);
    }

LAB_8002f258:
    do
    {
      local_1c = local_1c & 0xffff0000 | local_20 & 0xffff;
      iVar4 = *(int *)(*piVar2 + 0x48);

      while (iVar4 != 0)
      {
        iVar4 = FUN_8001861c();

        iVar5 = FUN_8002f364(*(undefined4 *)(iVar4 + 0x20),&local_20,0);

        if (iVar5 != 0)
          goto LAB_8002f258;

        iVar4 = *(int *)(iVar4 + 0x18);
      }

      iVar4 = FUN_8002f364(*(undefined4 *)(local_18 + 0x1c),&local_20,0);
    } while (iVar4 != 0);

    local_1c = local_1c & 0xffff0000 | (uint)(ushort)psVar1[2];

    if ((short)local_20 <= psVar1[2])
    {
      iVar4 = *(int *)(*piVar2 + 0x48);

      while (iVar4 != 0)
      {
        iVar4 = FUN_8001861c();

        FUN_8002f438(*(undefined4 *)(iVar4 + 0x20),&local_20,0);

        iVar4 = *(int *)(iVar4 + 0x18);
      }

      FUN_8002f438(*(undefined4 *)(local_18 + 0x1c),&local_20,0);

      FUN_800185cc(&local_18);

      if (DAT_8002f360 < *(int *)(psVar1 + 8))
      {
LAB_8002f338:
        uVar6 = 0;
      }
      else
      {
        *(uint *)(psVar1 + 4) = local_20;
        *(uint *)(psVar1 + 6) = local_1c;
        uVar6 = 1;
      }

      return CONCAT44(local_20,uVar6);
    }

    *(uint *)(psVar1 + 4) = local_20;
    *(uint *)(psVar1 + 6) = local_1c;

    FUN_800185cc(&local_18);

  } while( true );
}

//---------------------------------------------------------------------------------------

void FUN_800300c0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  void *source;
  int iVar2;
  longlong lVar3;
  undefined4 local_18;
  undefined4 uStack20;
  undefined4 uStack16;
  
  iVar2 = *DAT_80030130;
  source = *(void **)(iVar2 + 0x44);
  local_18 = param_2;
  uStack20 = param_3;
  uStack16 = param_4;

  if (source != (void *)0x0)
  {
    lVar3 = memcpy(&uStack20,source,8);
    iVar1 = *(int *)(DAT_80030134 + 0x28);

    if (iVar1 == 0)
    {
      iVar1 = *(int *)(iVar2 + 0x48);
    }

    local_18 = FUN_8001857c(iVar1,(int)((ulonglong)lVar3 >> 0x20));

    FUN_8002aa24(local_18,&uStack20);

    FUN_800185cc(&local_18);

    FUN_80019f54(&uStack20,param_1);

    param_1 = &uStack20;
  }

  FUN_8001d3bc(param_1);
  return;
}

//---------------------------------------------------------------------------------------

void FUN_8002d2c0(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  
  iVar2 = 0;
  do
  {
    if (*(int *)(DAT_8002d2ec + iVar2 * 4) == param_1)
    {
      return;
    }

    iVar3 = iVar2 + 1;
    bVar4 = SBORROW4(iVar3,2);
    iVar1 = iVar2 + -1;

    if (1 < iVar3)
    {
      iVar3 = -1;
    }

    iVar2 = iVar3;

  } while (iVar1 < 0 != bVar4);

  return;
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

int FUN_8001861c(int param_1)

{
  if (param_1 == 0)
  {
    return 0;
  }

  return *(int *)(*(int *)(DAT_8001863c + 0x34) + param_1 * 8 + 4) + 8;
}

//---------------------------------------------------------------------------------------

void FUN_8002f4f8(int param_1,int *param_2,int param_3,int param_4)

{
  short sVar1;
  int iVar2;
  uint uVar3;
  int *local_20;
  undefined4 uStack28;
  undefined4 uStack24;
  
  local_20 = param_2;
  uStack28 = param_3;
  uStack24 = param_4;

  while (param_1 != 0)
  {
    local_20 = (int *)FUN_8001857c(param_1);

    uVar3 = local_20[10];

    if ((uVar3 & 2) != 0)
    {
      if (param_3 == 0)
      {
        uStack28 = *local_20;
        uStack24 = local_20[1];
      }
      else
      {
        FUN_80019f98(&uStack28);
      }

      iVar2 = FUN_8001962c(param_2,&uStack28);

      if (iVar2 != 0)
      {
        if ((uVar3 & 1) == 0)
        {
          if (param_3 == 0)
          {
            sVar1 = *(short *)((int)local_20 + 2);
          }
          else
          {
            sVar1 = *(short *)(param_3 + 2);

            if (*(short *)(param_3 + 2) < *(short *)((int)local_20 + 2))
            {
              sVar1 = *(short *)((int)local_20 + 2);
            }
          }

          if (*(short *)((int)param_2 + 2) < sVar1)
          {
          }
          else
          {
            uStack28._2_2_ = uStack24._2_2_;
          }

          iVar2 = (int)uStack28._2_2_;

          if (*(short *)((int)param_2 + 2) < sVar1)
          {
            iVar2 = iVar2 + -1;
          }

          if (iVar2 < *(short *)((int)param_2 + 6))
          {
            *(short *)((int)param_2 + 6) = (short)iVar2;
          }
        }
        else
        {
          iVar2 = local_20[7];

          while (iVar2 != 0)
          {
            FUN_8002f4f8(iVar2,param_2,&uStack28);

            iVar2 = FUN_8001861c(iVar2);

            iVar2 = *(int *)(iVar2 + 0x20);
          }
        }
      }
    }

    param_1 = local_20[8];

    FUN_800185cc(&local_20);
  }
  return;
}

//---------------------------------------------------------------------------------------

undefined8 FUN_8002f364(int param_1,int *param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int *local_20;
  int iStack28;
  int local_18;
  
  uVar3 = 0;
  local_20 = param_2;
  iStack28 = param_3;
  local_18 = param_4;

  while (param_1 != 0)
  {
    local_20 = (int *)FUN_8001857c(param_1);
    uVar4 = local_20[10];

    if ((uVar4 & 2) != 0)
    {
      if (param_3 == 0)
      {
        iStack28 = *local_20;
        local_18 = local_20[1];
      }
      else
      {
        FUN_80019f98(&iStack28);
      }

      iVar1 = FUN_8001962c(param_2,&iStack28);

      if (iVar1 != 0)
      {
        if ((uVar4 & 1) == 0)
        {
          uVar3 = 1;
          *(short *)param_2 = (short)local_18 + 1;
        }
        else
        {
          iVar1 = local_20[7];

          while (iVar1 != 0)
          {
            iVar2 = FUN_8002f364(iVar1,param_2,&iStack28);

            if (iVar2 != 0)
            {
              uVar3 = 1;
            }

            iVar1 = FUN_8001861c(iVar1);
            iVar1 = *(int *)(iVar1 + 0x20);
          }
        }
      }
    }

    param_1 = local_20[8];

    FUN_800185cc(&local_20);
  }

  return CONCAT44(local_20,uVar3);
}

//---------------------------------------------------------------------------------------

void FUN_8002f438(int param_1,int *param_2,int param_3,int param_4)

{
  int iVar1;
  uint uVar2;
  int *local_20;
  int local_1c;
  int iStack24;
  
  local_20 = param_2;
  local_1c = param_3;
  iStack24 = param_4;

  while (param_1 != 0)
  {
    local_20 = (int *)FUN_8001857c(param_1);

    uVar2 = local_20[10];

    if ((uVar2 & 2) != 0)
    {
      if (param_3 == 0)
      {
        local_1c = *local_20;
        iStack24 = local_20[1];
      }
      else
      {
        FUN_80019f98(&local_1c);
      }

      iVar1 = FUN_8001962c(param_2,&local_1c);

      if (iVar1 != 0)
      {
        if ((uVar2 & 1) == 0)
        {
          *(short *)(param_2 + 1) = (short)local_1c + -1;
        }
        else
        {
          iVar1 = local_20[7];

          while (iVar1 != 0)
          {
            FUN_8002f438(iVar1,param_2,&local_1c);

            iVar1 = FUN_8001861c(iVar1);

            iVar1 = *(int *)(iVar1 + 0x20);
          }
        }
      }
    }

    param_1 = local_20[8];

    FUN_800185cc(&local_20);
  }

  return;
}

//---------------------------------------------------------------------------------------

void FUN_8001d3bc(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int *piVar1;
  int iVar2;
  undefined4 local_18;
  undefined4 uStack20;
  
  piVar1 = DAT_8001d408;
  iVar2 = *(int *)(DAT_8001d40c + (uint)*(byte *)(*DAT_8001d408 + 0x11) * 4);
  local_18 = param_3;
  uStack20 = param_4;
  (**(code **)(*(int *)(iVar2 + 0xc) + 0x30))(iVar2,&local_18);

  FUN_80019f98(*piVar1 + 8,param_1,&local_18);

  return;
}

//---------------------------------------------------------------------------------------

bool FUN_80019f98(undefined2 *param_1,short *param_2,short *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  bool bVar6;
  
  iVar3 = (int)*param_3;

  if ((int)*param_3 < (int)*param_2)
  {
    iVar3 = (int)*param_2;
  }

  *param_1 = (short)iVar3;
  iVar5 = (int)param_3[1];

  if ((int)param_3[1] < (int)param_2[1])
  {
    iVar5 = (int)param_2[1];
  }

  param_1[1] = (short)iVar5;
  iVar4 = (int)param_3[2];

  if ((int)param_2[2] < (int)param_3[2])
  {
    iVar4 = (int)param_2[2];
  }

  param_1[2] = (short)iVar4;
  iVar2 = (int)param_2[3];

  if ((int)param_3[3] <= (int)param_2[3])
  {
    iVar2 = (int)param_3[3];
  }

  bVar6 = SBORROW4(iVar4,iVar3);
  iVar1 = iVar4 - iVar3;
  param_1[3] = (short)iVar2;

  if (iVar3 <= iVar4)
  {
    bVar6 = SBORROW4(iVar2,iVar5);
    iVar1 = iVar2 - iVar5;
  }

  return iVar1 < 0 == bVar6;
}

//---------------------------------------------------------------------------------------

