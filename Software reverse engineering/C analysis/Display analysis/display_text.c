
//display_text is called from 65 locations
//What is strange is that so far no coupling with a screen buffer is found. None of the functions found in the display (screen buffers) analysis is called, at least not directly.

//Initial data
//0x8019D464: 0x00000000
//0x8019D468: 0x8001CF3C
//0x8019D46C: 0x80189750
//0x8019D470: 0x80857D4C
//0x8019D474: 0x00000000

//0x8019d47C: 0x00000000


//0x8019D468: 0x3C, 0xCF, 0x01, 0x80,
//0x8019D46C: 0x50, 0x97, 0x18, 0x80,
//0x8019D470: 0x4C, 0x7D, 0x85, 0x80,
//0x8019D474: 0x00, 0x00, 0x00, 0x00,
//0x8019D478: 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x8019D4AC: 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
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

  iVar1 = *DAT_80018c2c;                        //0x8019D470. This is some pointer holder which points to a struct. Might be a same system as for the screen buffers ==> 0x80857D4C

  *(ushort *)(iVar1 + 0x22) = xpos;
  *(ushort *)(iVar1 + 0x24) = ypos;


  FUN_80018a74(text);                           //Do the actual displaying



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

//Some data manupilation only done once per display sequence
//Needs some investigation to see if it is actualy needed since there is no real restore function
//FUN_80019a6c is called to reduce the count, but no apperant undoing of what this function does


//It is not very clear what this function is for. It looks at memory with a 120 byte interval and checks against it being 0.
//Only when FUN_80019ab8 was programmed to return something other then 0 it could do something else making it so that the next time it does not loop.
//When a byte does not return 0 from one of those intervals it is controlled by what is in memory at address 0x8019D4DC. (4) (4 * 120 = 480 which is the y res)

//This function is called from two other functions
//FUN_8001936c the save context?????
//FUN_800182fc ????

int FUN_8002f92c(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar1 = DAT_8002f980;                                  //r5 = 0x8019D4D4
  iVar5 = 0;                                             //r4 = 0

  while( true )
  {
    if (*(int *)(iVar1 + 8) <= iVar5)                    //*0x8019D4DC <= iVar5  (r0 = 4, r4 = 0)
    {
      return 0;
    }

    iVar2 = FUN_80019ab8();                              //Function returns a zero

    iVar4 = *(int *)(iVar1 + 0x10);                      //*0x8019D4E4 ==> pointer to some where (r2 = 0x803845C0)
    iVar3 = *(int *)(iVar4 + iVar5 * 0x78);              //iVar5 (r4) * 120 = 0 first round test (iVar3 == >r1)

    if (iVar3 == iVar2)                                  //These are the same so return iVar5 = 0
      break; 

    if (iVar3 == 0)
    {
      *(int *)(iVar4 + iVar5 * 0x78) = iVar2;            //Save the check byte
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
//param_1 is pointer to the text. Is the only one used here

//param_2 holds the content of address 0x8019D470
//param_3 is still the ypos (r2)
//param_4 is not set (r3)

//Actual text printing function
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

    sVar5 = FUN_80019210();                                            //Get some data via pointer structure?? Func returns a byte!! 0x0D
                                                                       //Font height most likely

    piVar3 = DAT_80018bf0;                                             //0x8019D470
    uVar1 = *(undefined2 *)(*DAT_80018bf0 + 0x22);                     //In the struct on 0x22 is the xpos

    sVar6 = FUN_8001925c();                                            //Get font base line??? For channel 1 menu it returns 0

    *(short *)(*piVar3 + 0x24) = *(short *)(*piVar3 + 0x24) - sVar6;   //In the struct on 0x24 is the ypos. Some font base line subtract


    while (*param_1 != '\0')                                           //Handle the characters until the terminating 0x00
    {
      //Get string length untill carriage return or end of string
      uVar7 = FUN_80019eb0(param_1,DAT_80018bf4);                      //DAT_80018bf4 = 0x00007FFF. param_1 is used as character pointer and is incremented at the end of this while loop

      //Get length in pixels?????  (print mode like center, top or bottom???)
      iVar8 = FUN_80019e0c(param_1,uVar7);                             //Pointer to the string, length of the string. Returns 0x16 for CH1 text

      iVar10 = *piVar3;
      bVar4 = *(byte *)(iVar10 + 0x2c) & 3;                            //Get font type flags for xpos handling (print mode like center, top or bottom???)
      iVar9 = iVar8;

      if (bVar4 != 1)                //Bottom offset if 1
      {
        if (bVar4 == 2)
        {
          iVar9 = iVar8 / 2;         //Center offset
        }
        else
        {
          iVar9 = 0;                 //No offset
        }
      }

      sVar2 = *(short *)(iVar10 + 0x22) - (short)iVar9;                //Decrement xpos with some value???
      *(short *)(iVar10 + 0x22) = sVar2;                               //Write it back

      local_28 = CONCAT22(*(short *)(iVar10 + 0x24),sVar2);            //ypos and new xpos into one 32 bit variable.   xpos is low part

      local_24 = CONCAT22(*(short *)(iVar10 + 0x24) + sVar5 + -1,sVar2 + (short)iVar8 + -1); //ypos + font_heigt - 1, xpos + text_width - 1


      //text ptr, text length, display position y,x (bounding box)
      FUN_80019cd8(param_1,uVar7,&local_28);           //Put the pixels in the screen buffer



      *(undefined2 *)(*piVar3 + 0x24) = local_28._2_2_;   //Write ypos back to struct


      //text ptr, text length
      iVar9 = FUN_80019988(param_1,uVar7);         //Get number of characters in bytes that have been processed in this run


      param_1 = param_1 + iVar9;                   //Point to next character in the string

      if (*param_1 == '\n' || *param_1 == '\r')                           //Check on carriage return and linefeed
      {
        iVar9 = *piVar3;
        bVar4 = *(byte *)(iVar9 + 0x2c) & 3;       //Get text position flags

        if (bVar4 == 1 || bVar4 == 2)
        {
          *(undefined2 *)(iVar9 + 0x22) = uVar1;    //Restore original xpos
        }
        else
        {
          *(undefined2 *)(iVar9 + 0x22) = *(undefined2 *)(iVar9 + 0x20);  //Use some value from the struct
        }

        if (*param_1 == '\n')                                             //Adjust the ypos when a new line (linefeed) is given
        {
          *(short *)(iVar9 + 0x24) = *(short *)(iVar9 + 0x24) + sVar5;
        }
      }
      else
      {
        *(short *)(*piVar3 + 0x22) = (short)local_28 + (short)iVar8;  //Not a cr or lf position x to after the text
      }

      if (*param_1 == '\0')              //On end of text quit
        break;

      param_1 = param_1 + 1;             //Otherwise skip the non printable character
    }

    iVar9 = *piVar3;
    *(short *)(iVar9 + 0x24) = *(short *)(iVar9 + 0x24) + sVar6;          //Restore ypos??
    *(ushort *)(iVar9 + 0x2c) = *(ushort *)(iVar9 + 0x2c) & 0xfffc;       //clear the bottom textplaceflags???????


    FUN_80019a6c();                                                       //Restore context
  }

  return;
}

//---------------------------------------------------------------------------------------
//Get font height????
undefined FUN_80019210(void)

{
  undefined uVar1;
  
  FUN_8001936c();   //??

  uVar1 = *(undefined *)(*(int *)(*DAT_80019238 + 0x1c) + 0x19);       //0x8019D470.  Get pointer from 0x8019D470. Load from the address found + 0x1C yet another pointer. Index this pointer with 0x19 and load a byte from it.
                                                                       //0x8019D470 ==> 0x80857D4C + 28 = 0x80857D68 ==> 0x8018AC58 + 25 = 0x8018AC71 ==> 0x0D

  FUN_80019a6c();   //??

  return uVar1;
}

//---------------------------------------------------------------------------------------
//Get some font metrics?????
//Only called from FUN_80018a74
//Get font base line???

uint FUN_8001925c(void)

{
  int iVar1;
  byte bVar2;
  uint uVar3;
  
  uVar3 = 0;

  FUN_8001936c();                                  //Save context

  iVar1 = *DAT_800192b0;                           //*0x8019D470 ==> 0x80857D4C
  bVar2 = *(byte *)(iVar1 + 0x2c) & 0xc;           //on byte 0x2C with in a struct is some data

  if (bVar2 == 4)                                  //If it is 4
  {
    uVar3 = *(byte *)(*(int *)(iVar1 + 0x1c) + 0x18) - 1;  //Get a pointer from 0x1C in the struct and from index 0x18 get the data and subtract 1
                                                           //0x8019D470 ==> 0x80857D4C + 28 = 0x80857D68 ==> 0x8018AC58 + 24 = 0x8018AC70 ==> ??
  }
  else
  {
    if (bVar2 == 8 || bVar2 == 0xc)                //if the byte is 8 or 12
    {
      uVar3 = (uint)(*(byte *)(*(int *)(iVar1 + 0x1c) + 0x18) >> 1);  //Get a pointer from 0x1C in the struct and from index 0x18 get the data and divide by 2
                                                                      //0x8019D470 ==> 0x80857D4C + 28 = 0x80857D68 ==> 0x8018AC58 + 24 = 0x8018AC70 ==> ??
    }
  }

  FUN_80019a6c();                                  //Restore context

  return uVar3;
}

//---------------------------------------------------------------------------------------
//Called with pointer to the characters
//param_1 = pointer to string
//param_2 = 0x7FFF (max string length)

//strlen (Get length of the string untill carriage return or end of string)
int FUN_80019eb0(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int local_18;  //Is param_1
  int iStack20;
  
  iVar2 = 0;
  if (param_1 != 0)
  {
    //DISPLAYDATA->FONTDATA->functions
    iVar1 = *(int *)(*(int *)(*DAT_80019f24 + 0x1c) + 0x14);    //0x8019D470 Get a pointer from 0x1C in the struct and from index 0x14 get the data which is a pointer???
                                                                //0x8019D470 ==> 0x80857D4C + 0x1C = 0x80857D68 ==> 0x8018AC58 + 0x14 = 0x8018AC6C ==> 0x00000000

    if (iVar1 != 0)                                             //Skipped
    {
      param_3 = *(code **)(iVar1 + 4);                          //get a function pointer from the given struct address + 4;
    }

    local_18 = param_1;
    iStack20 = param_2;

    if (iVar1 != 0 && param_3 != (code *)0x0)                   //Skipped
    {
      iVar2 = (*param_3)(param_1,param_2);                      //If the function pointer is set call it and get a value. strlen function needed here.
    }
    else 
    {
      //Get the characters untill either a 0x0D (carriage return) or 0x00 (end of string) or iVar2 == 0x7FFF
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

//0x8019D474 is a global pointer which points to a function table
//First entry is for getting a character from a string.
//Second entry is for getting the number of bytes per character

//This function gets a character from the string

//param_1 is a pointer to a pointer
undefined4 FUN_80019934(int *param_1)

{
  code **ppcVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  ppcVar1 = DAT_80019984;                        //0x8019D474 ==> 0x80191814 ==> get_character
                                                 //0x8019D474 ==> 0x80191814 + 4 = 0x80191818 ==> FUN_8002F5F4

  iVar4 = *param_1;                              //iVar4 is pointer to the string.

  uVar2 = (**(code **)*DAT_80019984)(iVar4);     //0x8002F5EC           Get character from the string (byte)

  iVar3 = (**(code **)(*ppcVar1 + 4))(iVar4);    //FUN_8002F5F4         Get 1 (One byte per character)

  *param_1 = iVar3 + iVar4;                      //Increment the string pointer with the character width         

  return uVar2;
}

//---------------------------------------------------------------------------------------

//param_1 pointer to the string
//param_2 length of the string

//Calculate the length in pixels????

int FUN_80019e0c(int param_1,int param_2)
{
  int iVar1;
  code **ppcVar2;
  code *pcVar3;
  int iVar4;
  undefined4 uVar5;
  int local_18;
  int local_14;
  
  pcVar3 = *DAT_80019ea8;                                //0x8019D4CC ==> 0x8002FD68
  local_18 = param_1;
  local_14 = param_2;


  local_18 = (*pcVar3)(param_1,&local_14);               //Empty function so does nothing. It is variable though. Part of a struct. Set on init


  iVar4 = 0;

  if (local_18 != 0)
  {
    uVar5 = 0;

    //DISPLAYDATA -> FONTDATA -> functions
    ppcVar2 = *(code ***)(*(int *)(*DAT_80019eac + 0x1c) + 0x14);    //0x8019D470 ==> 0x80857D4C + 0x1C = 0x80857D68 ==> 0x8018AC58 + 0x14 = 0x8018AC6C ==> 0x00000000 

    if (ppcVar2 != (code **)0x0)                              //Skipped
    {
      pcVar3 = *ppcVar2;
    }

    if (ppcVar2 != (code **)0x0 && pcVar3 != (code *)0x0)   //Skipped
    {
      iVar4 = (*pcVar3)(local_18,local_14);
    }
    else
    {
      //Process the characters
      while (local_14 = local_14 + -1, -1 < local_14)
      {
        //Get character from string
        uVar5 = FUN_80019934(&local_18);

        
        iVar1 = FUN_80019160();    //Get the width of the character. Input is uVar5

        iVar4 = iVar4 + iVar1;
      }

      //Does something with the last character
      iVar1 = FUN_80019f28(uVar5);  //More or less the same as FUN_80019160. Uses the same function pointer set in the font

      iVar4 = iVar4 + iVar1;
    }
  }
  return iVar4;
}

//---------------------------------------------------------------------------------------

//Character input
//Process character
undefined4 FUN_80019160(undefined4 param_1)

{
  undefined4 uVar1;
  
  FUN_8001936c();   //Save context

  //DISPLAYDATA -> FONTDATA -> pgetstringwidth               //0x8019D470 ==> 0x80857D4C + 0x1C = 0x80857D68 ==> 0x8018AC58 + 4 = 0x8018AC5C ==> 0x800181C4
  uVar1 = (**(code **)(*(int *)(*DAT_800191a0 + 0x1c) + 4))(param_1,0);   //Function at 0x800181C4

  FUN_80019a6c();  //Restore context
  return uVar1;
}

//---------------------------------------------------------------------------------------

//Character as input
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
//text ptr, text length, display position y,x  , also modified x,y are passed in

//This function takes a structure for param_3. (ystart, xstart, yend, xend)

//Convert the character to pixels in the screen buffer
void FUN_80019cd8(undefined4 param_1,undefined4 param_2,void *param_3,undefined4 param_4)

{
  int *piVar1;
  int iVar2;
  undefined4 local_18;
  undefined4 local_14;
  
  local_18 = param_3;
  local_14 = param_4;

  if (*DAT_80019de4 == 0)                 //0x8019D494
  {
    memcpy(&local_18,param_3,8);

    piVar1 = DAT_80019de8;  //0x8019D470 DISPLAYDATA pointer
    iVar2 = *DAT_80019de8;  //0x80857D4C DISPLAYDATA


    //Get ypos and add some offset, do the same for xoffset and merge them into one 32 bit value again
    local_18 = (void *)CONCAT22((short)((uint)local_18 >> 0x10) + *(short *)(iVar2 + 0x50),(short)local_18 + *(short *)(iVar2 + 0x4c));  //Offsets are zero

    //Get ypos and add some offset, do the same for xoffset and merge them into one 32 bit value again
    local_14 = CONCAT22((short)((uint)local_14 >> 0x10) + *(short *)(iVar2 + 0x50),(short)local_14 + *(short *)(iVar2 + 0x4c));

    //Input bounding box coordinates
    iVar2 = FUN_8002ac10(&local_18);

    while (iVar2 != 0)
    {
      iVar2 = *piVar1;  //0x80857D4C DISPLAYDATA

      *(short *)(iVar2 + 0x22) = (short)local_18;
      *(undefined2 *)(iVar2 + 0x24) = local_18._2_2_;


      //Do the actual rendering???
      FUN_8002d2f0(param_1,param_2,&local_18);

      iVar2 = FUN_8002ab40();
    }

    iVar2 = *piVar1;  //0x80857D4C DISPLAYDATA

    *(short *)(iVar2 + 0x22) = *(short *)(iVar2 + 0x22) - *(short *)(iVar2 + 0x4c);  //xpos Take of the offsets??? 
    *(short *)(iVar2 + 0x24) = *(short *)(iVar2 + 0x24) - *(short *)(iVar2 + 0x50);  //ypos
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
  
  puVar2 = DAT_8002ada0;  //0x80857DE4   Some array of data
  piVar1 = DAT_8002ad9c;  //0x8019D470
  iVar4 = *DAT_8002ad9c;  //0x80857D4C
  ppuVar5 = &local_30;

  if (*(char *)(iVar4 + 0x54) == '\0')        //Is 1 so skipped
  {
    FUN_8002a9a4();

    return 1;
  }

  iVar7 = DAT_8002ada0[5];                    //First round is 0
  DAT_8002ada0[5] = iVar7 + 1;                //Makes 1

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
//param_1 ==> pointer to text string
//param_2 ==> text length
//param_3 ==> pointer to bounding box data sitting on stack

//render string
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
  local_20 = (**DAT_8002d3c4)(param_1,&local_1c);   //Do some function pointer based processing, input is the text pointer and the bounding box. For setting the background color around the text??? Empty function!!!
  piVar1 = DAT_8002d3c8;  //0x8019D470 pointer to the display data struct


  //FUN_8001962c does some checking on the bounding box
  //DAT_8002d3c8 + 0x14  ==> 0x80857D60
  //*0x80857D60  = 0x80857D54


  //Check if there is a bounding box set in the displaydata. If so check the two bounding boxes in function FUN_8001962c
  //If there is no bounding box set in the display data just render as is
  //Else do it based on the outcome of FUN_8001962c. If this returns 0 do not process.
  if ((*(int *)(*DAT_8002d3c8 + 0x14) == 0) || (iVar3 = FUN_8001962c(*(int *)(*DAT_8002d3c8 + 0x14),param_3), iVar3 != 0))
  {
    //Signal start of render??
    FUN_8001a004(1);

    ppcVar2 = DAT_8002d3cc;    //0x8019D490

    iVar3 = *(int *)(*(int *)(*piVar1 + 0x1c) + 0x14);  //Get funtion pointer displaydata->font->functions 

    if (iVar3 == 0)
    {
      //Loop through the characters local_1c = param_2 = length
      while (local_1c = local_1c + -1, -1 < local_1c)
      {
        //Get character from the string and point to the next
        uVar4 = FUN_80019934(&local_20);    //Input is pointer to a charachter of the string

        //displaydata->font->renderchar
        (***(code ***)(*piVar1 + 0x1c))(uVar4);        //Calls FUN_80018090   Font based render function. (Either font_render_char_1 or font_render_char_2)

        if (*ppcVar2 != (code *)0x0)            //For display text this one is zero??? Is not modified by the software so never used. 
        {
          (**ppcVar2)(uVar4);       //Calls function pointed to by 0x8019D490 
          return;
        }
      }
    }
    else
    {
      (**(code **)(iVar3 + 8))(local_20,local_1c);
    }

    //Signal end of render??
    FUN_8001a004(0);
  }
  return;
}

//---------------------------------------------------------------------------------------
//This funtion is used for fonts 0 and 1. Fixed width style like courier

void font_render_char_1(uint char)

{
  int *piVar1;
  undefined uVar2;
  short *psVar3;
  uint uVar4;
  ushort *puVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int *piVar9;
  uint unaff_r6;
  uint uVar10;
  int iVar11;
  int unaff_r8;
  int unaff_r9;
  int iVar12;
  int iVar13;
  bool bVar14;
  bool bVar15;
  
  piVar1 = DAT_80017ff8;                                   //0x8019D470

  iVar8 = *DAT_80017ff8;                                   //0x80857D4C

  uVar6 = SEXT24(*(short *)(iVar8 + 0x22));                //xpos

  piVar9 = *(int **)(*(int *)(iVar8 + 0x1c) + 0x1c);       //font->information

  iVar12 = (int)*(short *)(iVar8 + 0x24);                  //ypos

  uVar4 = (uint)*(ushort *)(piVar9 + 3);                   //font->information2->first_char =   0x0020

  bVar15 = char <= uVar4;                                  //If input char less then first char

  bVar14 = uVar4 == char;                                  //If input char is first char

  uVar7 = uVar6;

  if (!bVar15 || bVar14)                                   //If char is printable
  {
    uVar7 = (uint)*(ushort *)((int)piVar9 + 0xe);          //Get the last char
  }

  if (!bVar15 || bVar14)
  {
    bVar15 = uVar7 <= char;                                //If input char is greater then last char
    bVar14 = char == uVar7;                                //If input is last char
  }

  if (!bVar15 || bVar14)                                   //If char is printable from first range
  {
    unaff_r9 = *piVar9;                                    //Point to the pixel data to use
  }

  if (!bVar15 || bVar14)
  {
    unaff_r8 = char - uVar4;                               //Index into pixel data??  Is input char - first char
  }

  if (!bVar15 || bVar14)
  {
    iVar11 = -1;                                           //Signal something
  }
  else
  {
    puVar5 = (ushort *)piVar9[2];                         //Not in range so point to next data set (word pointer)

    unaff_r9 = piVar9[1];                                 //Point to pixel data for the rest????

    if (puVar5 == (ushort *)0x0)                          //No more chars then done
      goto LAB_80017fd8;

    uVar7 = (uint)*puVar5;                                //Get first_char (short)

    bVar15 = char <= uVar7;                               //Check if less then

    bVar14 = uVar7 == char;

    if (!bVar15 || bVar14)                                //In range
    {
      unaff_r6 = (uint)puVar5[1];                         //get last char (short)
    }

    if (!bVar15 || bVar14)                        
    {
      bVar15 = unaff_r6 <= char;                          //Check if greather then
      bVar14 = char == unaff_r6;
    }

    if (bVar15 && !bVar14)                                //Not in range then done
      goto LAB_80017fd8;

    psVar3 = (short *)(*(int *)(puVar5 + 2) + (char - uVar7 & 0xffff) * 4); //get pixel pointer +   ((input char - first char) * 4)

    unaff_r8 = (int)*psVar3;  //Get 16 bit from location pointed to by character. First character index

    iVar11 = (int)psVar3[1];  //Second character index.
  }


  //iVar11 == -1 for characters 0x20 - 0x7E
  //For characters 0x90 - 0xFF it depends on the translation table

  //Check if valid character
  if (unaff_r8 != -1)
  {
    uVar7 = (uint)*(byte *)(*(int *)(iVar8 + 0x1c) + 0x18);      //font->baseline (height)

    iVar13 = uVar7 * *(byte *)((int)piVar9 + 0x12);              //height * numbytes

    uVar4 = (uint)*(byte *)(piVar9 + 4);                         //num pixels

    uVar10 = SEXT24(*(short *)(iVar8 + 0x2a));                   //fontpaintmode

    uVar2 = FUN_8001d474(uVar10);                                //swap font paint mode

    iVar8 = *(int *)(*piVar1 + 0x1c);                            //font


    //disp->xpos, disp->ypos, pfontmetrics->a, font->baseline, font->size, font->ymul, 1, pfontmetrics->c, pfontmetrics->data, disp->colorptr
    FUN_8001c7e4(uVar6, iVar12, uVar4,  uVar7,     *(undefined *)(iVar8 + 0x1a), *(undefined *)(iVar8 + 0x1b), 1, *(undefined *)((int)piVar9 + 0x12), unaff_r8 * iVar13 + unaff_r9, *(undefined4 *)(*piVar1 + 0x38));
//               xpos,  ypos    pixels  lines      fontsize                      fontymul                         numbytes                            pointer to the data            pointer to the color


    //This is only for characters 0x90 - 0xFF
    if (iVar11 != -1)
    {
      FUN_8001d474(uVar10 | 2);    //Do second part in mode 2

      iVar8 = *(int *)(*piVar1 + 0x1c);       //font

      //Second part is printed on top of first part.
      FUN_8001c7e4(uVar6, iVar12, uVar4, uVar7, *(undefined *)(iVar8 + 0x1a), *(undefined *)(iVar8 + 0x1b), 1, *(undefined *)((int)piVar9 + 0x12), iVar11 * iVar13 + unaff_r9, *(undefined4 *)(*piVar1 + 0x38));
    }


    //font->baseline (height) < font->height (baseline) and paint mode not 2
    if ((*(byte *)(*(int *)(*piVar1 + 0x1c) + 0x18) < *(byte *)(*(int *)(*piVar1 + 0x1c) + 0x19)) && (uVar10 != 2))
    {
      FUN_8001d474(uVar10 ^ 4); //Swap the fore ground and background color

      iVar8 = *(int *)(*piVar1 + 0x1c);  //point to font again

      //???
      FUN_8001cd50(uVar6,(uint)*(byte *)(iVar8 + 0x1b) * (uint)*(byte *)(iVar8 + 0x18) + iVar12, uVar4 * *(byte *)(iVar8 + 0x1a) + uVar6,(uint)*(byte *)(iVar8 + 0x19) + iVar12);
    }

    FUN_8001d474(uVar2);    //Restore the original font paint mode
  }
LAB_80017fd8:

  *(ushort *)(*piVar1 + 0x22) = *(short *)(*piVar1 + 0x22) + (ushort)*(byte *)((int)piVar9 + 0x11); //Shift the xpos to next position
  return;
}

//---------------------------------------------------------------------------------------
//Most of the fonts use this function for rendering

void font_render_char_2(uint char)

{
  byte bVar1;
  byte bVar2;
  int *piVar3;
  ushort *puVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  uint color;
  uint color_00;
  int iVar8;
  byte *pbVar9;
  int iVar10;
  
  piVar3 = DAT_800181c0;  //0x8019D470


  iVar10 = (int)*(short *)(*DAT_800181c0 + 0x2a);    //Get the data set with function FUN_800197c8??  displaysystem->pdisplaydata->screenbufsel

  //displaysystem->pdisplaydata->font->fontinformation, character to check
  //return pointer to the font information data if found
  puVar4 = (ushort *)check_char_in_font(*(void **)(*(int *)(*DAT_800181c0 + 0x1c) + 0x1c),char);

  //Process if character has data
  if (puVar4 != (ushort *)0x0)  //puVar4 => PFONTINFORMATION
  {
    //puVar4->fontmetrics + ((char - puVar4->first_char) * 8) ==> PFONTMETRICS
    pbVar9 = (byte *)(*(int *)(puVar4 + 2) + (char - *puVar4) * 8);

    //pbVar9->c
    bVar1 = pbVar9[2];   //Need to determine what this one means


    //Do something with the screen buffer select??? As long as bit 2 is not set in either it just swaps two variables (curscreen, screenbufsel). Still not clear what it actualy is for
    uVar5 = FUN_8001d474(iVar10);   


    //displaysystem->pdisplaydata
    iVar6 = *piVar3;


    //displaysystem->pdisplaydata->font
    iVar8 = *(int *)(iVar6 + 0x1c);

    //0x00A6,     0x0010,     0x07,            0x0D,           0x01,       0x01,        1, 1,               0x8018A5F7,         0x80857D4C
    //disp->xpos, disp->ypos, pfontmetrics->a, font->baseline, font->size, font->width, 1, pfontmetrics->c, pfontmetrics->data, disp->buffer1
    FUN_8001c7e4((int)*(short *)(iVar6 + 0x22), (int)*(short *)(iVar6 + 0x24), *pbVar9, *(undefined *)(iVar8 + 0x18), *(undefined *)(iVar8 + 0x1a), *(undefined *)(iVar8 + 0x1b), 1, bVar1, *(undefined4 *)(pbVar9 + 4), *(undefined4 *)(iVar6 + 0x38));


    //displaysystem->pdisplaydata->font
    iVar6 = *(int *)(*piVar3 + 0x1c);

    bVar1 = *(byte *)(iVar6 + 0x19);  //font->height
    bVar2 = *(byte *)(iVar6 + 0x18);  //font->baseline

    //If baseline less then height
    if ((uint)bVar2 < (uint)bVar1)
    {
      uVar7 = (uint)*(byte *)(iVar6 + 0x1b);  //font->width

      //If screen buf not is 2
      if (iVar10 != 2)
      {
        color = FUN_800191ec(uVar7);

        color_00 = FUN_8001913c();

        set_display_color(color_00);

        iVar10 = *piVar3;

        //disp->xpos, disp->ypos + (font->baseline * font->width), (font->width * pfontmetrics->a) + disp->xpos, disp->ypos + (font->height * font->width)
        FUN_8001cd50((int)*(short *)(iVar10 + 0x22), (int)*(short *)(iVar10 + 0x24) + bVar2 * uVar7, (uint)*(byte *)(*(int *)(iVar10 + 0x1c) + 0x1b) * (uint)*pbVar9 + (int)*(short *)(iVar10 + 0x22), (int)*(short *)(iVar10 + 0x24) + bVar1 * uVar7);

        set_display_color(color);
      }
    }

    //Back to previous font mode
    FUN_8001d474(uVar5);

    iVar10 = *piVar3;

    //Adjust the x position.  xpos += (pfontmetrics->b * font->size);
    *(ushort *)(iVar10 + 0x22) = (ushort)pbVar9[1] * (ushort)*(byte *)(*(int *)(iVar10 + 0x1c) + 0x1a) + *(short *)(iVar10 + 0x22);
  }

  return;
}


//---------------------------------------------------------------------------------------
//Called to do something with the font mode

void FUN_8001d474(void)

{
  //Some function pointer system that always returns the same function.
  (**(code **)(*DAT_8001d484 + 8))();  //0x8019D4F0 ==> 0x80191824 + 8 = 0x8019182C ==> 0x8003016C
  return;
}

//---------------------------------------------------------------------------------------
//Secondary function called to do something with the font mode
//This is a font paint mode
//When bit 2 is set two color pointers are swapped
//param_1 is font paint mode
void FUN_8003016c(byte param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  
  piVar1 = DAT_800301bc;   //0x8019D470

  iVar2 = *DAT_800301bc;   //0x8019D470 ==> 0x80857D4C

  //tagDisplayData->curscreen ^ selscreen ==> 0x00 ^ 0x02 = 0x02
  if (((*(byte *)(iVar2 + 0x10) ^ param_1) & 4) != 0)
  {
    //When switch to or from a 0x04 (bit 2 set) do this

    uVar3 = **(undefined4 **)(iVar2 + 0x38);

    **(undefined4 **)(iVar2 + 0x38) = **(undefined4 **)(iVar2 + 0x3c);

    **(undefined4 **)(*piVar1 + 0x3c) = uVar3;
  }

  //Otherwise just set the new value and return the old
  *(byte *)(*piVar1 + 0x10) = param_1;

  return;
}




//---------------------------------------------------------------------------------------
//Actual rendering of the text????????

//param_1     param_2     param_3          param_4         param_5     param_6      param_7   param_8          param_9             param_10
//0x00A6,     0x0010,     0x07,            0x0D,           0x01,       0x01,        1,        1,               0x8018A5F7,         0x80857D4C
//disp->xpos, disp->ypos, pfontmetrics->a, font->baseline, font->size, font->width, 1,        pfontmetrics->c, pfontmetrics->data, disp->buffer1

void FUN_8001c7e4(byte *param_1,byte *param_2,byte *param_3,byte *param_4,byte *param_5,byte *param_6,byte *param_7,byte *param_8,byte *param_9,int param_10)

{
  uint uVar1;
  byte *pbVar2;
  uint uVar3;
  byte *pbVar4;
  byte *pbVar5;
  uint uVar6;
  byte *pbVar7;
  code *pcVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  bool bVar12;
  bool bVar13;
  int iVar14;
  
  uVar9 = 0;

  if ((code **)*DAT_8001cb18 != (code **)0x0)   //*0x8019D494 == 0x00000000 so skip this
  {
    pcVar8 = *(code **)*DAT_8001cb18;
    pbVar4 = param_3;
    pbVar2 = param_9;
    goto LAB_8001c9d4;
  }

  //Adds param_2 + param_4, takes 1 of (r10)    yend
  //Adds param_1 + param_3, takes 1 of (r3)     xend



  //Only if (font->size or font->width) not 1?? In the code it looks like it checks param_7 and param_8
  if (((uint)param_5 | (uint)param_6) != 1)
  {
    uVar1 = 8 - (int)param_7;   //uVar1 = 7
    iVar14 = 0;

    //For font 2 letter C this is 0x0D
    while (iVar14 < (int)param_4)
    {
      pbVar2 = param_6 + (int)param_2;
      pbVar5 = pbVar2 + -1;
      pbVar7 = (byte *)(int)*(short *)(*DAT_8001cb1c + 10);
      bVar13 = SBORROW4((int)pbVar7,(int)pbVar5);
      pbVar4 = pbVar7 + -(int)pbVar5;
      bVar12 = pbVar7 == pbVar5;

      if ((int)pbVar7 <= (int)pbVar5)
      {
        pbVar7 = (byte *)(int)*(short *)(*DAT_8001cb1c + 0xe);
        bVar13 = SBORROW4((int)param_2,(int)pbVar7);
        pbVar4 = param_2 + -(int)pbVar7;
        bVar12 = param_2 == pbVar7;
      }

      if (bVar12 || (int)pbVar4 < 0 != bVar13)
      {
        iVar10 = 0;
        iVar11 = 0;
        pbVar4 = param_1;
        pbVar7 = param_9;


        //For font 2 letter C this is 0x07
        while (iVar11 < (int)param_3)
        {
          if (iVar10 == 0)
          {
            iVar10 = 8;
            uVar9 = (uint)*pbVar7;
            pbVar7 = pbVar7 + 1;
          }

          iVar10 = iVar10 - (int)param_7;
          uVar3 = uVar9 >> (uVar1 & 0xff);
          uVar9 = uVar9 << ((uint)param_7 & 0xff) & 0xff;

          if ((uVar3 != 0) || ((*(byte *)(*DAT_8001cb1c + 0x10) & 2) == 0))
          {
            uVar6 = **(uint **)(*DAT_8001cb1c + 0x3c);

            if (param_10 != 0)
            {
              uVar3 = *(uint *)(param_10 + uVar3 * 4);
            }

            **(uint **)(*DAT_8001cb1c + 0x3c) = uVar3;

            //Is this for putting data in a screen buffer???
            FUN_8001cd50(pbVar4, param_2, (int)param_5 + (int)pbVar4 + -1, pbVar5);

            **(uint **)(*DAT_8001cb1c + 0x3c) = uVar6;
          }

          iVar11 = iVar11 + 1;
          pbVar4 = pbVar4 + (int)param_5;
        }
      }

      iVar14 = iVar14 + 1;
      param_9 = param_9 + (int)param_8;
      param_2 = pbVar2;
    }

    return;
  }

  iVar14 = *DAT_8001cb1c;   //0x8019D470 ==> 0x80857D4C (displaydata)

  pbVar2 = (byte *)(int)*(short *)(iVar14 + 10) + -(int)param_2;   //disp->ystart - ypos
  param_5 = param_4;
  pbVar4 = param_2;

  if (0 < (int)pbVar2)  //Not true so skipped
  {
    param_5 = param_4 + -(int)pbVar2;

    if ((int)param_5 < 1)
    {
      return;
    }

    param_9 = param_9 + (int)pbVar2 * (int)param_8;
    pbVar4 = (byte *)(int)*(short *)(iVar14 + 10);
  }


  iVar10 = ((int)param_2 + (int)param_4 + -1) - (int)*(short *)(iVar14 + 0xe);  //ypos + (font->baseline - 1) - disp->yend;

  if ((0 < iVar10) && (param_5 = param_5 + -iVar10, (int)param_5 < 1))
  {
    return;
  }

  iVar10 = ((int)param_1 + (int)param_3 + -1) - (int)*(short *)(iVar14 + 0xc);  //xpos + (pfontmetrics->a - 1) - disp->xend;
  param_4 = param_3;

  if (0 < iVar10)
  {
    param_4 = param_3 + -iVar10;
  }

  pbVar2 = (byte *)0x0;
  param_2 = param_1;

  if ((int)param_1 < (int)*(short *)(iVar14 + 8))
  {
    pbVar2 = (byte *)((int)*(short *)(iVar14 + 8) - (int)param_1);
    param_4 = param_4 + -(int)pbVar2;

    if (param_7 == &SupervisorCall)
    {
      param_9 = param_9 + (int)pbVar2;
    }
    else
    {
      if ((int)param_7 < 9)
      {
        if (param_7 == (byte *)0x1)
        {
          uVar9 = (uint)pbVar2 & 0xfffffff8;
          param_9 = param_9 + ((int)pbVar2 >> 3);
          pbVar2 = (byte *)((uint)pbVar2 & 7);
          param_2 = param_1 + uVar9;
        }
        else
        {
          if (param_7 == (byte *)0x2)
          {
            uVar9 = (uint)pbVar2 & 0xfffffffc;
            param_9 = param_9 + ((int)pbVar2 >> 2);
            pbVar2 = (byte *)((uint)pbVar2 & 3);
            param_2 = param_1 + uVar9;
          }
          else
          {
            if (param_7 == &UndefinedInstruction)
            {
              uVar9 = (uint)pbVar2 & 0xfffffffe;
              param_9 = param_9 + ((int)pbVar2 >> 1);
              pbVar2 = (byte *)((uint)pbVar2 & 1);
              param_2 = param_1 + uVar9;
            }
          }
        }

        goto LAB_8001c990;
      }

      if (param_7 == &DataAbort)
      {
        param_9 = param_9 + (int)pbVar2 * 2;
      }
      else
      {
        if (param_7 != &IRQ && param_7 != (byte *)0x20)
          goto LAB_8001c990;

        param_9 = param_9 + (int)pbVar2 * 4;
      }
    }

    param_2 = pbVar2 + (int)param_1;
    pbVar2 = (byte *)0x0;
  }

LAB_8001c990:
  if ((int)param_4 < 1)
  {
    return;
  }

  param_1 = *(byte **)(DAT_8001cb20 + (uint)*(byte *)(iVar14 + 0x11) * 4);  //0x8019D488

  //0x8019D488 ==> 0x803845A0 + 0x0C ==> 0x8015E3B8 + 0x04 ==> 0x8002DCBC
  pcVar8 = *(code **)(*(int *)(param_1 + 0xc) + 4);

  param_6 = param_7;
  param_7 = param_8;
  param_8 = param_9;


LAB_8001c9d4:
//Need to check what is set in the params here. Is not a direct copy of the input of this function

  (*pcVar8)(param_1,param_2,pbVar4,param_4,param_5,param_6,param_7,param_8,pbVar2,param_10);  //0x8002DCBC

  return;
}

//param_1     param_2     param_3          param_4         param_5     param_6      param_7   param_8          param_9             param_10
//0x00A6,     0x0010,     0x07,            0x0D,           0x01,       0x01,        1,        1,               0x8018A5F7,         0x80857D4C
//disp->xpos, disp->ypos, pfontmetrics->a, font->baseline, font->size, font->width, 1,        pfontmetrics->c, pfontmetrics->data, disp->color



//---------------------------------------------------------------------------------------
//This one does the actual rendering to a screen buffer


//The indirect screen buffer is used. Need to find where 0x8019CF60 is set with this data (0x804FB9B4)
//80010bac		FUN_80010a30	                str r11,[r4,#0x0]=>DAT_8019cf60
//80017768		set_frame_to_global_pointer	str r0,[r1,#0x0]=>DAT_8019cf60
//80017780		set_screen_to_global_pointer	str r0,[r1,#0x0]=>DAT_8019cf60
//8001d5e8		sys_init_display	        str r0,[r1,#0x0]=>DAT_8019cf60

//param_1      param_2      param_3      param_4           param_5          param_6      param_7           param_8              param_9             param_10
//0x803845A0,  0xA6,        0x10,        0x07,             0x0D,            0x01,        1,                0x8018A5F7,          0x00,               0x80857D4C
//ptr,         disp->xpos,  disp->ypos,  pfontmetrics->a,  font->baseline,  font->size,  pfontmetrics->c,  pfontmetrics->data,  ???,                disp->color
void FUN_8002dcbc(int param_1,int param_2,int param_3,uint param_4,int param_5,int param_6,int param_7,undefined2 *param_8,uint param_9,undefined4 *param_10)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  int *piVar4;
  byte bVar5;
  ushort uVar6;
  undefined2 *puVar7;
  int iVar8;
  undefined2 uVar9;
  uint uVar10;
  undefined2 *puVar11;
  undefined4 uVar12;
  uint uVar13;
  uint unaff_r4;
  int unaff_r5;
  int iVar14;
  int iVar15;
  undefined2 *unaff_r6;
  int unaff_r7;
  int unaff_r8;
  int iVar16;
  int iVar17;
  int iVar18;
  undefined2 *puVar19;
  uint uVar20;
  int *piVar21;
  int *piVar22;
  int *piVar23;
  undefined4 uVar24;
  bool bVar25;
  int local_40;
  int local_3c;
  int local_38;
  int iStack52;
  int iStack48;
  int iStack44;
  uint uStack40;
  
  piVar4 = DAT_8002e548;
  piVar3 = Global_Frame_Buffer_Pointer;      //0x8019CF60
  uStack40 = param_4;
  iStack44 = param_3;
  iStack48 = param_2;
  iStack52 = param_1;
  piVar22 = &local_40;
  piVar23 = &local_40;
  piVar21 = &local_40;
  local_40 = *Global_Frame_Buffer_Pointer;   //0x804FB9B4

  //font size 8??, not the case so skipped
  if (param_6 == 8)
  {
    iVar16 = param_5;

    if (param_5 < 1)
    {
      piVar22 = (int *)&stack0xfffffff0;
      param_4 = unaff_r4;
      param_8 = unaff_r6;
      iVar16 = unaff_r7;
      param_7 = unaff_r8;
    }

    iVar8 = 0;

    if (0 < param_5)
    {
      do
      {
        iVar14 = piVar22[0x15];
        iVar17 = piVar22[5] + iVar8;

        if ((*(byte *)(*piVar4 + 0x10) & 3) == 0)
        {
          if (iVar14 == 0)
          {
            if (0 < (int)param_4)
            {
              iVar15 = *piVar22;
              uVar20 = param_4;
              iVar14 = param_2;
              puVar11 = param_8;

              do
              {
                iVar18 = iVar14 * 2;
                uVar20 = uVar20 - 1;
                iVar14 = iVar14 + 1;
                *(ushort *)(iVar15 + iVar17 * 0x640 + iVar18) = (ushort)*(byte *)puVar11;
                puVar11 = (undefined2 *)((int)puVar11 + 1);
              } while (0 < (int)uVar20);
            }
          }
          else
          {
            if (0 < (int)param_4)
            {
              iVar18 = *piVar22;
              uVar20 = param_4;
              iVar15 = param_2;
              puVar11 = param_8;

              do
              {
                iVar1 = iVar15 * 2;
                uVar20 = uVar20 - 1;
                iVar15 = iVar15 + 1;
                *(short *)(iVar18 + iVar17 * 0x640 + iVar1) = (short)*(undefined4 *)(iVar14 + (uint)*(byte *)puVar11 * 4);
                puVar11 = (undefined2 *)((int)puVar11 + 1);
              } while (0 < (int)uVar20);
            }
          }
        }
        else
        {
          if ((*(byte *)(*piVar4 + 0x10) & 3) == 2)
          {
            if (iVar14 == 0)
            {
              if (0 < (int)param_4)
              {
                iVar15 = *piVar22;
                uVar20 = param_4;
                iVar14 = param_2;
                puVar11 = param_8;

                do
                {
                  bVar5 = *(byte *)puVar11;
                  uVar20 = uVar20 - 1;
                  puVar11 = (undefined2 *)((int)puVar11 + 1);

                  if (bVar5 != 0)
                  {
                    *(ushort *)(iVar15 + iVar17 * 0x640 + iVar14 * 2) = (ushort)bVar5;
                  }

                  iVar14 = iVar14 + 1;
                } while (0 < (int)uVar20);
              }
            }
            else
            {
              if (0 < (int)param_4)
              {
                iVar18 = *piVar22;
                uVar20 = param_4;
                iVar15 = param_2;
                puVar11 = param_8;
                do
                {
                  if (*(byte *)puVar11 != 0)
                  {
                    *(short *)(iVar18 + iVar17 * 0x640 + iVar15 * 2) = (short)*(undefined4 *)(iVar14 + (uint)*(byte *)puVar11 * 4);
                  }

                  uVar20 = uVar20 - 1;
                  iVar15 = iVar15 + 1;
                  puVar11 = (undefined2 *)((int)puVar11 + 1);
                } while (0 < (int)uVar20);
              }
            }
          }
        }

        iVar8 = iVar8 + 1;
        param_8 = (undefined2 *)((int)param_8 + param_7);
      } while (iVar8 < iVar16);

      return;
    }

    return;
  }

  //font size > 8, not the case
  if (8 < param_6)
  {
    if (param_6 == 0x10)
    {
      iVar14 = 0;
      iVar16 = 0;
      iVar8 = param_5;

      if (param_5 < 1)
      {
        piVar23 = (int *)&stack0xfffffff0;
        param_4 = unaff_r4;
        iVar16 = unaff_r5;
        param_8 = unaff_r6;
        iVar8 = unaff_r7;
        param_7 = unaff_r8;
      }

      iVar17 = 0;

      if (0 < param_5)
      {
        iVar15 = *(int *)((int)piVar23 + 0x14);

        do
        {
          if (0 < (int)param_4)
          {
            puVar19 = (undefined2 *)(*piVar3 + (param_2 + iVar15 * 800 + iVar16) * 2);
            bVar25 = (param_4 & 1) != 0;
            puVar11 = puVar19 + -1;

            if (bVar25)
            {
              *puVar19 = *(undefined2 *)((int)param_8 + iVar14);
              puVar11 = puVar19;
            }

            uVar20 = (uint)bVar25;
            param_4 = (int)param_4 >> 1;

            while (param_4 != 0)
            {
              puVar19 = (undefined2 *)((int)param_8 + uVar20 * 2 + iVar14);
              param_4 = param_4 - 1;
              uVar20 = uVar20 + 2;
              puVar11[1] = *puVar19;
              puVar11 = puVar11 + 2;
              *puVar11 = puVar19[1];
            }
          }

          iVar17 = iVar17 + 1;
          iVar14 = iVar14 + param_7;
          iVar16 = iVar16 + 800;
        } while (iVar17 < iVar8);

        return;
      }

      return;
    }

    if (param_6 != 0x20)
    {
      return;
    }

    iVar16 = param_5;

    if (param_5 < 1)
    {
      piVar21 = (int *)&stack0xfffffff0;
      param_4 = unaff_r4;
      param_8 = unaff_r6;
      iVar16 = unaff_r7;
      param_7 = unaff_r8;
    }

    iVar8 = 0;

    if (0 < param_5)
    {
      do {
        iVar14 = piVar21[5];
        if (0 < (int)param_4) {
          iVar15 = *piVar21;
          iVar17 = param_2;
          uVar20 = param_4;
          puVar11 = param_8;
          do {
            iVar18 = iVar17 * 2;
            uVar20 = uVar20 - 1;
            iVar17 = iVar17 + 1;
            *(undefined2 *)(iVar15 + (iVar14 + iVar8) * 0x640 + iVar18) = *puVar11;
            puVar11 = puVar11 + 2;
          } while (0 < (int)uVar20);
        }
        iVar8 = iVar8 + 1;
        param_8 = (undefined2 *)((int)param_8 + param_7);
      } while (iVar8 < iVar16);

      return;
    }

    return;
  }

  local_3c = param_2 + param_9;   //xpos plus some offset???


  if (param_6 != 1)  //Font size is 1 so skipped
  {
    
    if (param_6 == 2)
    {
      local_38 = 0;

      if (0 < param_5)
      {
        do
        {
          iVar16 = local_38 + param_3;
          uVar20 = (uint)*(byte *)param_8;

          //Paint mode 0
          if ((*(byte *)(*DAT_8002e548 + 0x10) & 3) == 0)
          {
            if (param_10 == (undefined4 *)0x0)
            {
              iVar8 = local_3c;
              uVar10 = param_9;
              puVar11 = param_8;
              uVar13 = param_4;

              do
              {
                iVar17 = 3 - uVar10;
                iVar14 = iVar8 * 2;
                uVar10 = uVar10 + 1;
                iVar8 = iVar8 + 1;
                *(short *)(local_40 + iVar16 * 0x640 + iVar14) = (short)((0xc0U >> (iVar17 * -2 + 6U & 0xff) & uVar20) >> (iVar17 * 2 & 0xffU));

                if (uVar10 == 4)
                {
                  puVar11 = (undefined2 *)((int)puVar11 + 1);
                  uVar20 = (uint)*(byte *)puVar11;
                  uVar10 = 0;
                }

                uVar13 = uVar13 - 1;
              } while (uVar13 != 0);
            }
            else
            {
              iVar8 = local_3c;
              uVar10 = param_9;
              puVar11 = param_8;
              uVar13 = param_4;

              do
              {
                iVar17 = 3 - uVar10;
                iVar14 = iVar8 * 2;
                uVar10 = uVar10 + 1;
                iVar8 = iVar8 + 1;
                *(short *)(local_40 + iVar16 * 0x640 + iVar14) = (short)param_10[(0xc0U >> (iVar17 * -2 + 6U & 0xff) & uVar20) >> (iVar17 * 2 & 0xffU)];

                if (uVar10 == 4)
                {
                  puVar11 = (undefined2 *)((int)puVar11 + 1);
                  uVar20 = (uint)*(byte *)puVar11;
                  uVar10 = 0;
                }

                uVar13 = uVar13 - 1;
              } while (uVar13 != 0);
            }
          }
          else
          {
            //Paint mode 2
            if ((*(byte *)(*DAT_8002e548 + 0x10) & 3) == 2)
            {
              if (param_10 == (undefined4 *)0x0)
              {
                iVar8 = local_3c;
                uVar10 = param_9;
                puVar11 = param_8;
                uVar13 = param_4;

                do
                {
                  puVar19 = (undefined2 *)(0xc0U >> ((3 - uVar10) * -2 + 6 & 0xff) & uVar20);
                  uVar2 = (uint)puVar19 >> ((3 - uVar10) * 2 & 0xff);

                  if (uVar2 != 0)
                  {
                    puVar19 = (undefined2 *)(local_40 + iVar16 * 0x640 + iVar8 * 2);
                  }

                  uVar10 = uVar10 + 1;

                  if (uVar2 != 0)
                  {
                    *puVar19 = (short)uVar2;
                  }

                  iVar8 = iVar8 + 1;

                  if (uVar10 == 4)
                  {
                    puVar11 = (undefined2 *)((int)puVar11 + 1);
                    uVar20 = (uint)*(byte *)puVar11;
                    uVar10 = 0;
                  }

                  uVar13 = uVar13 - 1;
                } while (uVar13 != 0);
              }
              else
              {
                iVar8 = local_3c;
                uVar10 = param_9;
                puVar11 = param_8;
                uVar13 = param_4;

                do
                {
                  uVar2 = (0xc0U >> ((3 - uVar10) * -2 + 6 & 0xff) & uVar20) >> ((3 - uVar10) * 2 & 0xff);

                  if (uVar2 != 0)
                  {
                    *(short *)(local_40 + iVar16 * 0x640 + iVar8 * 2) = (short)param_10[uVar2];
                  }

                  uVar10 = uVar10 + 1;
                  iVar8 = iVar8 + 1;

                  if (uVar10 == 4)
                  {
                    puVar11 = (undefined2 *)((int)puVar11 + 1);
                    uVar20 = (uint)*(byte *)puVar11;
                    uVar10 = 0;
                  }

                  uVar13 = uVar13 - 1;
                } while (uVar13 != 0);
              }
            }
          }

          param_8 = (undefined2 *)((int)param_8 + param_7);
          local_38 = local_38 + 1;

        } while (local_38 < param_5);

        return;
      }

      return;
    }

    if (param_6 == 4)
    {
      local_38 = 0;

      //Only if font has height
      if (0 < param_5)
      {
        do
        {
          iVar16 = local_38 + param_3;
          uVar20 = (uint)*(byte *)param_8;

          if ((*(byte *)(*DAT_8002e548 + 0x10) & 3) == 0)
          {
            if (param_10 == (undefined4 *)0x0)
            {
              iVar8 = local_3c;
              uVar10 = param_9;
              puVar11 = param_8;
              uVar13 = param_4;

              do
              {
                iVar17 = 1 - uVar10;
                iVar14 = iVar8 * 2;
                uVar10 = uVar10 + 1;
                iVar8 = iVar8 + 1;

                *(short *)(local_40 + iVar16 * 0x640 + iVar14) = (short)((0xf0U >> (iVar17 * -4 + 4U & 0xff) & uVar20) >> (iVar17 * 4 & 0xffU));

                if (uVar10 == 2)
                {
                  puVar11 = (undefined2 *)((int)puVar11 + 1);
                  uVar20 = (uint)*(byte *)puVar11;
                  uVar10 = 0;
                }

                uVar13 = uVar13 - 1;

              } while (uVar13 != 0);
            }
            else
            {
              iVar8 = local_3c;
              uVar10 = param_9;
              puVar11 = param_8;
              uVar13 = param_4;

              do
              {
                iVar17 = 1 - uVar10;
                iVar14 = iVar8 * 2;
                uVar10 = uVar10 + 1;
                iVar8 = iVar8 + 1;

                *(short *)(local_40 + iVar16 * 0x640 + iVar14) = (short)param_10[(0xf0U >> (iVar17 * -4 + 4U & 0xff) & uVar20) >> (iVar17 * 4 & 0xffU)];

                if (uVar10 == 2)
                {
                  puVar11 = (undefined2 *)((int)puVar11 + 1);
                  uVar20 = (uint)*(byte *)puVar11;
                  uVar10 = 0;
                }

                uVar13 = uVar13 - 1;

              } while (uVar13 != 0);
            }
          }
          else
          {
            if ((*(byte *)(*DAT_8002e548 + 0x10) & 3) == 2)
            {
              if (param_10 == (undefined4 *)0x0)
              {
                iVar8 = local_3c;
                uVar10 = param_9;
                puVar11 = param_8;
                uVar13 = param_4;

                do
                {
                  puVar19 = (undefined2 *)(0xf0U >> ((1 - uVar10) * -4 + 4 & 0xff) & uVar20);
                  uVar2 = (uint)puVar19 >> ((1 - uVar10) * 4 & 0xff);

                  if (uVar2 != 0)
                  {
                    puVar19 = (undefined2 *)(local_40 + iVar16 * 0x640 + iVar8 * 2);
                  }

                  uVar10 = uVar10 + 1;

                  if (uVar2 != 0)
                  {
                    *puVar19 = (short)uVar2;
                  }

                  iVar8 = iVar8 + 1;

                  if (uVar10 == 2)
                  {
                    puVar11 = (undefined2 *)((int)puVar11 + 1);
                    uVar20 = (uint)*(byte *)puVar11;
                    uVar10 = 0;
                  }

                  uVar13 = uVar13 - 1;

                } while (uVar13 != 0);
              }
              else
              {
                iVar8 = local_3c;
                uVar10 = param_9;
                puVar11 = param_8;
                uVar13 = param_4;

                do
                {
                  uVar2 = (0xf0U >> ((1 - uVar10) * -4 + 4 & 0xff) & uVar20) >> ((1 - uVar10) * 4 & 0xff);

                  if (uVar2 != 0)
                  {
                    *(short *)(local_40 + iVar16 * 0x640 + iVar8 * 2) = (short)param_10[uVar2];
                  }

                  uVar10 = uVar10 + 1;
                  iVar8 = iVar8 + 1;

                  if (uVar10 == 2)
                  {
                    puVar11 = (undefined2 *)((int)puVar11 + 1);
                    uVar20 = (uint)*(byte *)puVar11;
                    uVar10 = 0;
                  }

                  uVar13 = uVar13 - 1;

                } while (uVar13 != 0);
              }
            }
          }
          param_8 = (undefined2 *)((int)param_8 + param_7);
          local_38 = local_38 + 1;

        } while (local_38 < param_5);

        return;
      }

      return;
    }

    return;
  }

  local_40 = 0;

  //Check if font baseline (height) has a value
  if (param_5 < 1)
  {
    return;
  }


  //Handle the last or actual font data (font->size == 1)
  do
  {
    iVar16 = local_3c;                       //disp->xpos plus some offset
    local_38 = local_40 + iStack44;          //0 + disp->ypos
    uVar12 = param_10[1];
    uVar24 = *param_10;

    bVar5 = *(byte *)(*DAT_8002e548 + 0x10) & 3;   //displaydata->fonthandlemode ??  0, 1, 2, 3 (If bit 2 is set in other parts of the code stuff is done with that. Pointers are being swapped then)

    //If target is 0 do next
    if ((*(byte *)(*DAT_8002e548 + 0x10) & 3) == 0)
    {
      iVar8 = *Global_Frame_Buffer_Pointer;
      uVar20 = param_9;  //Start pixel
      puVar11 = param_8; //Font data
      uVar10 = param_4;  //Number of pixels per line

      do
      {
        uVar9 = (short)uVar12;   //Set background color

        //If pixel is set 
        if (((uint)*(byte *)puVar11 & (0x80U >> (uVar20 & 0xff))) == 0)
        {
          uVar9 = (short)uVar24;  //Set foreground color
        }

        uVar20 = uVar20 + 1;
        iVar14 = iVar16 * 2;

        if (uVar20 == 8)
        {
          uVar20 = 0;
          puVar11 = (undefined2 *)((int)puVar11 + 1);
        }

        uVar10 = uVar10 - 1;
        iVar16 = iVar16 + 1;
        *(undefined2 *)(iVar8 + local_38 * 0x640 + iVar14) = uVar9;

      } while (uVar10 != 0);
    }
    else
    {
      //bVar5 == 2 so skipped
      if (bVar5 == 1)
      {
LAB_8002df4c:
        uVar6 = (**(code **)(*(int *)(iStack52 + 0x10) + 8))();
        iVar8 = *Global_Frame_Buffer_Pointer;
        uVar20 = param_9;
        puVar11 = param_8;
        uVar10 = param_4;

        do
        {
          if (((uint)*(byte *)puVar11 & 0x80U >> (uVar20 & 0xff)) != 0)
          {
            *(ushort *)(iVar8 + local_38 * 0x640 + iVar16 * 2) = *(ushort *)(iVar8 + (iVar16 + local_38 * 800) * 2) ^ uVar6;
          }

          uVar20 = uVar20 + 1;

          if (uVar20 == 8)
          {
            uVar20 = 0;
            puVar11 = (undefined2 *)((int)puVar11 + 1);
          }

          uVar10 = uVar10 - 1;
          iVar16 = iVar16 + 1;

        } while (uVar10 != 0);
      }
      else
      {
        //This one is used
        if (bVar5 == 2)
        {
          puVar7 = (undefined2 *)*Global_Frame_Buffer_Pointer;   //r0
          puVar11 = puVar7;   //frame buffer pointer
          uVar20 = param_9;   //some offset. Start pixel in font line   r9
          puVar19 = param_8;  //pointer to font data           r6 and r10
          uVar10 = param_4;   //character width 0x07

          //Handle the bits in the font data bytes
          do
          {
            bVar25 = ((uint)*(byte *)puVar19 & (0x80U >> (uVar20 & 0xff))) != 0;  //Shift bit 7 right, so test the MSB first loop and down to LSB if all the bits are used

            if (bVar25)
            {
              //800 bytes per line, but with two bytes per pixel this seems wrong. But since puVar7 is a short pointer it adds up. In the assembly it is
              //ldr         r2, [sp, #8]           //Get the y position
              //add         r12, r2, r2, lsl #3    //Multiply by 9
              //add         r2, r12, r2, lsl #4    //Add multiply by 16 to make it multiply by 25
              //add         r2, r0, r2, lsl #6     //Multiply by 64 to make it multiply by 1600 and add it to the buffer base
              //This is puVar11 = puVar7 + local_38 * 800;
              //The xpos is also multiplied by 2 before adding
              //addne       r0, r2, r5, lsl #1
              puVar11 = puVar7 + local_38 * 800 + iVar16;   //iVar16 == xpos per pixel, local_38 == ypos per line
            }

            uVar20 = uVar20 + 1;  //Next bit

            if (bVar25)
            {
              *puVar11 = (short)uVar12;  //Set the pixel
            }

            if (uVar20 == 8)   //Check on last bit in a byte (r9)
            {
              uVar20 = 0;
              puVar19 = (undefined2 *)((int)puVar19 + 1);  //If so select next byte
            }

            uVar10 = uVar10 - 1;  //One pixel done
            iVar16 = iVar16 + 1;  //Move to next xpos

          } while (uVar10 != 0); //(r11)
        }
        else
        {
          if (bVar5 == 3) //Use the same code as for type 0
            goto LAB_8002df4c;
        }
      }
    }

    param_8 = (undefined2 *)((int)param_8 + param_7); //Skip to next font line data
    local_40 = local_40 + 1;  //One more line done

    //Handle number of lines in the font
    if (param_5 <= local_40)
    {
      return;
    }
  } while( true );
}


//param_1      param_2      param_3      param_4           param_5          param_6      param_7           param_8              param_9             param_10
//0x803845A0,  0xA6,        0x10,        0x07,             0x0D,            0x01,        1,                0x8018A5F7,          0x00,               0x80857D4C
//ptr,         disp->xpos,  disp->ypos,  pfontmetrics->a,  font->baseline,  font->size,  pfontmetrics->c,  pfontmetrics->data,  ???,                disp->buffer1

//---------------------------------------------------------------------------------------


void FUN_8001cd50(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  iVar1 = *DAT_8001cdd4;                        //0x8019D470 (displaysystem->pdisplaydata) ==> 0x80857D4C

  if (param_1 < *(short *)(iVar1 + 8))          //displaysystem->pdisplaydata->xstart
  {
    param_1 = (int)*(short *)(iVar1 + 8);
  }

  if (*(short *)(iVar1 + 0xc) < param_3)        //xend
  {
    param_3 = (int)*(short *)(iVar1 + 0xc);
  }

  if (param_1 <= param_3)                      //start before or equal to end
  {
    if (param_2 < *(short *)(iVar1 + 10))      //ystart
    {
      param_2 = (int)*(short *)(iVar1 + 10);
    }

    if (*(short *)(iVar1 + 0xe) < param_4)    //yend
    {
      param_4 = (int)*(short *)(iVar1 + 0xe);
    }

    if (param_2 <= param_4)                   //ystart before or equal to yend
    {
      iVar1 = *(int *)(DAT_8001cdd8 + (uint)*(byte *)(iVar1 + 0x11) * 4);  //0x8019D488 + (pdisplaydata->whatisitfor * 4) = 0x8019D488; (whatisitfor = 0???) ==> 0x803845A0

      //0x8019D488 ==> 0x803845A0 + 0x0C ==> 0x8015E3B8 + 0x10 ==> 0x8002EF2C
      (**(code **)(*(int *)(iVar1 + 0xc) + 0x10))(iVar1,param_1,param_2,param_3,param_4);  //FUN_8002ef2c
    }
  }

  return;
}


//---------------------------------------------------------------------------------------

void FUN_8002ef2c(int param_1,uint param_2,uint param_3,int param_4,int param_5)

{
  uint uVar1;
  ushort uVar2;
  uint uVar3;
  int *piVar4;
  ushort uVar5;
  
  piVar4 = Global_Frame_Buffer_Pointer;
  uVar1 = param_2 & 0xffff;

  if ((*(byte *)(*DAT_8002f038 + 0x10) & 1) == 0)
  {
    FUN_8001cddc(uVar1,param_3 & 0xffff,(param_4 - param_2) + 1 & 0xffff,(param_5 - param_3) + 1 & 0xffff);

    return;
  }

  uVar3 = uVar1;

  if (param_5 < (int)param_3)
  {
    return;
  }

  do
  {
    while ((int)uVar3 <= param_4)
    {
      uVar2 = *(ushort *)(*piVar4 + (uVar3 + param_3 * 800) * 2);

      uVar5 = (**(code **)(*(int *)(param_1 + 0x10) + 8))();

      *(ushort *)(*piVar4 + param_3 * 0x640 + uVar3 * 2) = uVar5 ^ uVar2;

      uVar3 = uVar3 + 1 & 0xfffeffff;
    }

    param_3 = param_3 + 1;
    uVar3 = uVar1;
  } while ((int)param_3 <= param_5);

  return;
}


//---------------------------------------------------------------------------------------

void FUN_8001cddc(int param_1,int param_2,int param_3,int param_4,uint param_5)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  
  piVar1 = Global_Frame_Buffer_Pointer;
  uVar2 = param_4 - 1;
  param_2 = param_2 * 800;
  if (param_4 == 0) {
    return;
  }
  do {
    uVar3 = uVar2 & 0xffff;
    memset((void *)(*piVar1 + param_2 * 2 + param_1 * 2),param_5,param_3);
    uVar2 = uVar3 - 1;
    param_2 = param_2 + 800;
  } while (uVar3 != 0);
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
//Param_1 ==> pointer to bounding box structure from displaydata
//Param_2 ==> pointer to bounding box structure on stack

//Checks on bounding box being correct.
//Returns 1 if ok, 0 if not

short * FUN_8001962c(short *param_1,short *param_2)

{
  short *psVar1;
  short *psVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  bool bVar6;
  bool bVar7;
  
  iVar3 = (int)param_1[1];         //Sign extended short from displaydata + 0x02  ()
  iVar5 = (int)param_2[3];         //Sign extended short from bounding box + 0x06 (bottom ==> yend???)
  bVar7 = SBORROW4(iVar3,iVar5);
  iVar4 = iVar3 - iVar5;
  bVar6 = iVar3 == iVar5;


  //Check if bounding box parameters are in the right order (top less then or equal to bottom)
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

//Called before display text
//Uses the select context, lock or whatever function at the beginning and the restore, unlock or whatever function at the end

//It loads a function pointer into a global variable and returns what was in that global variable
//param_1 0x8018AC58  ==> FUN_80018090 ??

undefined4 FUN_80019730(int param_1)

{
  undefined4 uVar1;
  
  FUN_8001936c();

  uVar1 = *(undefined4 *)(*DAT_80019760 + 0x1c);  //0x8019D470  ==> 0x80857D4C + 0x1C = 0x80857D68 ==> 0x80189750

  if (param_1 != 0)
  {
    *(int *)(*DAT_80019760 + 0x1c) = param_1;
  }

  FUN_80019a6c();

  return uVar1;
}

//---------------------------------------------------------------------------------------


