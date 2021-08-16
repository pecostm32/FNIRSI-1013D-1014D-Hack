
//Function to determine starting point in sample buffer????

void FUN_8001b424(short *param_1,short *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  short sVar9;
  
  iVar1 = DAT_8001b644;                            //0x8019D5A0
  *(undefined2 *)(DAT_8001b644 + 0x1a) = 3;        //3     start x
  *(undefined2 *)(iVar1 + 0x1c) = 0x2d3;           //723   end x

  uVar8 = DAT_8001b668;         //0x00000177       375
  uVar7 = DAT_8001b664;         //0x0000038F       911
  uVar6 = DAT_8001b660;         //0x0000031F       799
  uVar5 = DAT_8001b65c;         //0x0000036A       874
  uVar4 = DAT_8001b654;         //0x00000256       598
  uVar3 = DAT_8001b650;         //0x000002EE       750
  uVar2 = DAT_8001b64c;         //0x0000044B      1099


  //Some not yet know variable. Reset when restarted after stop, set when adjusting time base in stopped mode!!!
  switch(*(undefined2 *)(PTR_DAT_8001b648 + 0x1a))   //0x80192EAA + 1A     some struct with the first being the disp_xpos var in my code
  {
  case 5:
    if (0x177 < *(ushort *)(iVar1 + 0x24))  //Trigger position on screen
    {
      if (*(ushort *)(iVar1 + 0x24) < 0x15d)
      {
        *param_1 = *(short *)(iVar1 + 0x24) + -0x174;
        *param_2 = (short)uVar3;
        return;
      }

      *param_1 = *(short *)(iVar1 + 0x24) + -0x174;
      sVar9 = (short)uVar2 - *(short *)(iVar1 + 0x24);
      break;
    }

    *param_1 = 3;
    sVar9 = *(short *)(iVar1 + 0x24) + 0x77;
    goto LAB_8001b4dc;

  case 6:
    if (300 < *(ushort *)(iVar1 + 0x24))
    {
      if (*(ushort *)(iVar1 + 0x24) < 0x1a8)
      {
        *param_1 = *(short *)(iVar1 + 0x24) + -0x129;
        *param_2 = (short)uVar4;
        return;
      }

      *param_1 = *(short *)(iVar1 + 0x24) + -0x129;
      sVar9 = 0x400 - *(short *)(iVar1 + 0x24);
      break;
    }

    *param_1 = 3;
    sVar9 = *(short *)(iVar1 + 0x24) + 0x2a;

LAB_8001b4dc:
    sVar9 = sVar9 + 0x100;
    break;

  case 7:
    if (*(ushort *)(iVar1 + 0x24) < 0x97)
    {
      *param_1 = 3;
      sVar9 = *(short *)(iVar1 + 0x24) + 0x96;
    }
    else
    {
      if (*(ushort *)(iVar1 + 0x24) < DAT_8001b658)
      {
        *param_1 = *(short *)(iVar1 + 0x24) + -0x93;
        *param_2 = 300;
        return;
      }

      *param_1 = *(short *)(iVar1 + 0x24) + -0x93;
      sVar9 = (short)uVar5 - *(short *)(iVar1 + 0x24);
    }
    break;

  case 8:
    if (*(ushort *)(iVar1 + 0x24) < 0x4c)
    {
      *param_1 = 3;
      sVar9 = *(short *)(iVar1 + 0x24) + 0x4b;
    }
    else
    {
      if (*(ushort *)(iVar1 + 0x24) < 0x289)
      {
        *param_1 = *(short *)(iVar1 + 0x24) + -0x48;
        *param_2 = 0x96;
        return;
      }
      *param_1 = *(short *)(iVar1 + 0x24) + -0x48;
      sVar9 = (short)uVar6 - *(short *)(iVar1 + 0x24);
    }
    break;

  default:
    return;

  case 10:
    if (*(ushort *)(iVar1 + 0x24) < 0xbc)
    {
      *param_1 = 3;
      sVar9 = *(short *)(iVar1 + 0x24) + 0xbb;
    }
    else
    {
      if (*(ushort *)(iVar1 + 0x24) < 0x219)
      {
        *param_1 = *(short *)(iVar1 + 0x24) + -0xb8;
        *param_2 = (short)uVar8;
        return;
      }

      *param_1 = *(short *)(iVar1 + 0x24) + -0xb8;
      sVar9 = (short)uVar7 - *(short *)(iVar1 + 0x24);
    }
  }

  *param_2 = sVar9;
  return;
}

