void scope_adjust_timebase(void)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  char cVar5;
  char *text;
  uint uVar6;
  int iVar7;
  undefined2 uVar8;
  uint uVar9;
  uint uVar10;
  bool bVar11;
  bool bVar12;
  
  iVar3 = DAT_8001af84;  //0x8019D5A0

  //Backed up time base and scope run state
  //time base 50S/div - 100mS and stopped is a state that hase been filtered out with check before entering this function
  //if ((10 < *(byte *)(iVar8 + 0xb)) || (*(char *)(iVar8 + 0x3a) == '\0'))
  if ((*(byte *)(DAT_8001af84 + 0xb) < 9) && (*(char *)(DAT_8001af84 + 0x3a) != '\0'))
    goto limit_on_not_auto;



  uVar2 = *(ushort *)(PTR_DAT_8001af88 + 6);        //0x80192f08 + 6 is prev prev x
  uVar6 = (uint)*(ushort *)(PTR_DAT_8001af88 + 8);  //0x80192f08 + 8 is prev prev y
  uVar9 = DAT_8001af8c + 0x6f;                      //0x00000167 + 0x6F = 0x01D6 = 470
  uVar10 = uVar2 - 1;                               //x minus 1
  bVar12 = uVar10 <= DAT_8001af8c;                  //less or equal to 359
  bVar11 = DAT_8001af8c == uVar10;                  //equal to

  if (bVar12 && !bVar11)                            //less but not equal
  {
    bVar12 = 0x31 < uVar6;                          //y needs to be more then 39
    bVar11 = uVar6 == 0x32;
  }

  if (bVar12 && !bVar11)                            //and less then 470
  {
    bVar12 = uVar6 <= uVar9;
    bVar11 = uVar9 == uVar6;
  }

  //In my code I think it is safe to just check on x, because al the other sections of the screen have been checked before
  //Decrement the time base setting (longer times) when touched on the left side
  if ((bVar12 && !bVar11) && (*(char *)(DAT_8001af84 + 10) != '\0'))
  {
    *(char *)(DAT_8001af84 + 10) = *(char *)(DAT_8001af84 + 10) + -1;
  }

  uVar10 = uVar2 - 0x169;
  bVar12 = uVar10 <= DAT_8001af90;             //0x0000016B   363
  bVar11 = DAT_8001af90 == uVar10;

  if (bVar12 && !bVar11)                        //Check on y
  {
    bVar12 = 0x31 < uVar6;
    bVar11 = uVar6 == 0x32;
  }

  if (bVar12 && !bVar11)
  {
    bVar11 = uVar6 < uVar9;

    if (bVar11)                              //Above bottom range
    {
      uVar6 = (uint)*(byte *)(iVar3 + 10);   //get the current time base
    }

    if (bVar11 && uVar6 < 0x1d)        //check if below last range setting
    {
      *(char *)(iVar3 + 10) = *(char *)(iVar3 + 10) + '\x01';
    }
  }




  //here starts a check on the different ranges with limits when the capture is not running

  if (*(char *)(iVar3 + 0x3a) == '\0')  //Check if in run state
  {
    *(byte *)(iVar3 + 0xb) = *(byte *)(iVar3 + 10);  //Save the new setting if so and set it in the fpga
    goto set_in_fpga;
  }





  //When the new setting is 0-10 and backed up is 11 or up limit on 11
  if ((*(byte *)(iVar3 + 10) < 0xb) && (10 < *(byte *)(iVar3 + 0xb)))
  {
    *(undefined *)(iVar3 + 10) = 0xb;
  }




  uVar8 = 0;

  //backed up time base * some number * -3 + backed up time base is zero?????
  //0xAAAAAAAB
  if ((uint)((ulonglong)(uint)*(byte *)(iVar3 + 0xb) * (ulonglong)DAT_8001af94 >> 0x21) * -3 + (uint)*(byte *)(iVar3 + 0xb) == 0) //  ((backup / 3) * -3) - backup;
  {
    //New setting less then previous setting
    if (*(byte *)(iVar3 + 10) < *(byte *)(iVar3 + 0xb))
    {
      //Get the difference between them
      cVar5 = *(char *)(iVar3 + 0xb) - *(char *)(iVar3 + 10);

      if (cVar5 != '\x01')
      {
        if (cVar5 != '\x02')
          goto joined_r0x8001af30;

        uVar8 = 10;
        goto LAB_8001ae10;
      }

LAB_8001af40:
      *(undefined2 *)PTR_DAT_8001af98 = 5;    //0x80192ec4 ???? variable
      goto set_in_fpga;
    }



    switch(*(char *)(iVar3 + 10) - *(char *)(iVar3 + 0xb))
    {
    case '\x01':
      uVar8 = 2;

    case '\0':
LAB_8001ae10:
      *(undefined2 *)PTR_DAT_8001af98 = uVar8;
      break;

    case '\x02':
LAB_8001aefc:
      *(undefined2 *)PTR_DAT_8001af98 = 3;
      break;

    case '\x03':
LAB_8001af04:
      *(undefined2 *)PTR_DAT_8001af98 = 4;
      break;

    case '\x04':
LAB_8001ae68:
      cVar5 = *(char *)(iVar3 + 10) + -1;
LAB_8001ae18:
      *(char *)(iVar3 + 10) = cVar5;
    }
  }






  else
  {
    if ((uint)*(byte *)(iVar3 + 0xb) + (uint)((ulonglong)(uint)*(byte *)(iVar3 + 0xb) * (ulonglong)DAT_8001af94 >> 0x21) * -3 != 1)
    {
      if ((uint)((ulonglong)(uint)*(byte *)(iVar3 + 0xb) * (ulonglong)DAT_8001af94 >> 0x21) * -3 + (uint)*(byte *)(iVar3 + 0xb) == 2)
      {
        if (*(byte *)(iVar3 + 10) < *(byte *)(iVar3 + 0xb))
        {
          cVar5 = *(char *)(iVar3 + 0xb) - *(char *)(iVar3 + 10);

          if (cVar5 == '\x01')
            goto LAB_8001af40;

          if (cVar5 == '\x02')
            goto LAB_8001af48;

joined_r0x8001af30:
          if (cVar5 == '\x03')
          {
            *(undefined2 *)PTR_DAT_8001af98 = 8;
          }
          else
          {
            if (cVar5 == '\x04')
            {
              cVar5 = *(char *)(iVar3 + 10) + '\x01';
              goto LAB_8001ae18;
            }
          }
        }
        else
        {
          switch(*(char *)(iVar3 + 10) - *(char *)(iVar3 + 0xb))
          {
          case '\0':
            goto LAB_8001ae10;

          case '\x01':
            goto LAB_8001aef4;

          case '\x02':
            goto LAB_8001aefc;

          case '\x03':
            goto LAB_8001af04;

          case '\x04':
            goto LAB_8001ae68;
          }
        }
      }

      goto set_in_fpga;
    }

    if (*(byte *)(iVar3 + 10) < *(byte *)(iVar3 + 0xb))
    {
      cVar5 = *(char *)(iVar3 + 0xb) - *(char *)(iVar3 + 10);

      if (cVar5 == '\x01')
      {
        uVar8 = 6;
        goto LAB_8001ae10;
      }

      if (cVar5 != '\x02')
        goto joined_r0x8001af30;

LAB_8001af48:
      *(undefined2 *)PTR_DAT_8001af98 = 7;
      goto set_in_fpga;
    }

    switch(*(char *)(iVar3 + 10) - *(char *)(iVar3 + 0xb))
    {
    case '\0':
      goto LAB_8001ae10;

    case '\x01':
LAB_8001aef4:
      *(undefined2 *)PTR_DAT_8001af98 = 1;
      break;

    case '\x02':
      uVar8 = 9;
      goto LAB_8001ae10;

    case '\x03':
      goto LAB_8001af04;

    case '\x04':
      goto LAB_8001ae68;
    }
  }

set_in_fpga:
  set_fpga_trigger_timebase();

limit_on_not_auto:
  bVar1 = *(byte *)(iVar3 + 0x21);  //Get trigger mode
  bVar11 = bVar1 != 0;              //Not on auto

  if (bVar11)                       //So on single or normal
  {
    bVar1 = *(byte *)(iVar3 + 10);  //Get the current time base setting
  }

  //Long time base settings are only allowed on auto trigger mode
  if (bVar11 && bVar1 < 9)          //On single or normal and long time base setting 
  {
    *(undefined *)(iVar3 + 10) = 9;  //Fall back to 50mS/div
    set_fpga_trigger_timebase();
  }




//display_time_div_setting
  set_frame_to_global_pointer();

  set_display_fg_color(0);

  display_fill_rect(0x18b,5,0x1e8,0x2c);

  set_display_fg_color(0xffffff);

  select_font(PTR_FONT_0_800124d0);

  switch(*(undefined *)(DAT_800124d4 + 10))
  {
  case 0:
    text = s_50S_div_800124dc;
    break;
  case 1:
    text = s_20S_div_800124e4;
    break;
  case 2:
    text = s_10S_div_800124ec;
    break;
  case 3:
    text = s_5S_div_800124f4;
    break;
  case 4:
    text = s_2S_div_800124fc;
    break;
  case 5:
    text = s_1S_div_80012504;
    break;
  case 6:
    text = s_500mS_div_8001250c;
    break;
  case 7:
    text = s_200mS_div_80012518;
    break;
  case 8:
    text = s_100mS_div_80012524;
    break;
  case 9:
    text = s_50mS_div_80012530;
    break;
  case 10:
    text = s_20mS_div_8001253c;
    break;
  case 0xb:
    text = s_10mS_div_80012548;
    break;
  case 0xc:
    text = s_5mS_div_80012554;
    break;
  case 0xd:
    text = s_2mS_div_8001255c;
    break;
  case 0xe:
    text = s_1mS_div_80012564;
    break;
  case 0xf:
    text = s_500uS_div_8001256c;
    break;
  case 0x10:
    text = s_200uS_div_80012578;
    break;
  case 0x11:
    text = s_100uS_div_80012584;
    break;
  case 0x12:
    text = s_50uS_div_80012590;
    break;
  case 0x13:
    text = s_20uS_div_8001259c;
    break;
  case 0x14:
    text = s_10uS_div_800125a8;
    break;
  case 0x15:
    text = s_5uS_div_800125b4;
    break;
  case 0x16:
    text = s_2uS_div_800125bc;
    break;
  case 0x17:
    text = s_1uS_div_800125c4;
    break;
  case 0x18:
    text = s_500nS_div_800125cc;
    break;
  case 0x19:
    text = s_250nS_div_80012640;
    break;
  case 0x1a:
    text = s_100nS_div_8001264c;
    break;
  case 0x1b:
    text = s_50nS_div_80012658;
    break;
  case 0x1c:
    text = s_25nS_div_80012664;
    break;
  case 0x1d:
    text = s_10nS_div_80012670;
    break;
  default:
    goto switchD_800122c0_caseD_1e;
  }

  display_text(text,(ushort)DAT_800124d8,0x10);

switchD_800122c0_caseD_1e:
  iVar4 = Start_Of_Screen_Mem;
  iVar3 = Screen_Frame_Buffer;
  uVar6 = 5;

  do
  {
    iVar7 = uVar6 * 800 + 0x17c;
    copy_short((void *)(iVar4 + iVar7 * 2),(void *)(iVar3 + iVar7 * 2),0x5f);
    uVar6 = uVar6 + 1;
  } while (uVar6 < 0x2a);

  return;
}

