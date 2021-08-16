//------------------------------------------------------------------------------------------------------------------------------------------------
//When this function is called time base setting can be 9 - 29

undefined4 FUN_800291e0(void)

{
  ushort uVar1;
  bool bVar2;
  bool bVar3;
  undefined4 uVar4;
  uint uVar5;
  byte bVar6;
  int iVar7;
  int iVar8;
  bool bVar9;
  bool bVar10;
  
//TB  9 bvar10 false, bvar9 false    return
//TB 10 bvar10 false, bvar9 false    return
//TB 11 bvar10 true,  bvar9 true,   ==> bvar9 == trigger mode ==> auto true ==> run code, single/normal false ==> return
//TB 12 bvar10 true,  bvar9 false,  ==> bvar9 == trigger mode ==> auto true ==> run code, single/normal false ==> return


  bVar6 = *(byte *)(DAT_80029300 + 10);     //0x8019D5AA  time base
  bVar2 = false;                            //
  bVar10 = 10 < bVar6;                      //true if time base 11 - 29
  bVar9 = bVar6 == 0xb;                     //true if time base is 11. This one does not matter

  if (bVar10)                               //If time base 11 - 29
  {
    bVar6 = *(byte *)(DAT_80029300 + 0x21); //Get the trigger mode
  }

  uVar4 = 1;
  bVar3 = false;

  if (bVar10)                               //If time base 11 - 29
  {
    bVar9 = bVar6 == 0;                     //True if trigger mode auto
  }

  if (!bVar9)                               //Return if not on auto or time base is 9 or 10
  {
    return 0;
  }

  if (0x18 < *(byte *)(DAT_80029300 + 10))  //If time base is 25 - 29 return
  {
    return 0;
  }

  iVar7 = DAT_80029308;         //0x8019D5EA  Channel 1 trace buffer

  if (*(char *)(DAT_80029300 + 0x23) != '\0')  //If trigger channel is not 0 (channel 1) 
  {
    iVar7 = DAT_8002930c;      //0x801A04CA   channel 2 trace buffer
  }



  uVar5 = DAT_80029304;       //0x000002E9    745

  if (*(char *)(DAT_80029300 + 0x22) == '\0')   //Trigger edge rising
  {
    do
    {
      iVar8 = iVar7 + uVar5 * 2;  //Point to sample near half the buffer

      //Do a check on previous sample and trigger level
      if ((*(ushort *)(iVar8 + -2) < (ushort)*(byte *)(DAT_80029300 + 0x28)) && ((ushort)*(byte *)(DAT_80029300 + 0x28) <= *(ushort *)(iVar8 + 2)))
        goto LAB_80029294; //break out of loop, does that mean triggered???

      uVar5 = uVar5 + 1 & 0xfffeffff;
    } while (uVar5 < DAT_80029304 + 10);  //Check max 755 samples
  }
  else                                          //Trigger edge falling
  {
    do
    {
      iVar8 = iVar7 + uVar5 * 2;

      if (((ushort)*(byte *)(DAT_80029300 + 0x28) < *(ushort *)(iVar8 + -2)) && (*(ushort *)(iVar8 + 2) <= (ushort)*(byte *)(DAT_80029300 + 0x28)))
        goto LAB_80029294;

      uVar5 = uVar5 + 1 & 0xfffeffff;
    } while (uVar5 < DAT_80029304 + 10);  //Check max 755 samples
  }

LAB_800292ac:
  uVar5 = 100;

  do
  {
    uVar1 = *(ushort *)(iVar7 + uVar5 * 2);

    if (*(byte *)(DAT_80029300 + 0x28) < uVar1)
    {
      bVar2 = true;
    }

    if (uVar1 < *(byte *)(DAT_80029300 + 0x28))
    {
      bVar3 = true;
    }

    uVar5 = uVar5 + 1 & 0xfffeffff;
  } while (uVar5 < DAT_80029310);   //0x00000578   1400

  //All samples equal to level
  if (!bVar2 || !bVar3)
  {
    return 0;
  }

  return uVar4;

LAB_80029294:
  uVar4 = 0;  //Does this mean triggered????
  goto LAB_800292ac;
}

//------------------------------------------------------------------------------------------------------------------------------------------------

