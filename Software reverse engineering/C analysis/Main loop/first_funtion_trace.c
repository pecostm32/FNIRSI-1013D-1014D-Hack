//------------------------------------------------------------------------------------------------------------------------------------------------
//Check on power supply connected
//Read the battery charge level
//??

void monitor_battery(void)
{
  int iVar1;
  undefined *puVar2;
  byte bVar3;
  uint uVar4;
  byte *pbVar5;
  int iVar6;
  int iVar7;
  byte bVar8;
  bool bVar9;
  
  iVar1 = DAT_8000a6a8;                               //Base of settings data
  bVar8 = 0xff;

  if (0xd < *(byte *)(DAT_8000a6a8 + 10))             //Time base setting   If 13 is smaller then, so 14 and up (1mS/div and down)
  {
    iVar7 = 0x1e;                                     //1mS/div --- 10nS/div, factor is 30
    goto LAB_8000a5bc;
  }

  if (*(byte *)(DAT_8000a6a8 + 10) < 0xc)             //Less then 0x0C
  {
    if (*(byte *)(DAT_8000a6a8 + 10) < 9)             //Less then 9
    {
      if (6 < *(byte *)(DAT_8000a6a8 + 10))           //If 6 is smaller then, so 7 and 8.
      {
        iVar7 = 100;                                  //200mS/div, 100mS/div, factor is 100
        goto LAB_8000a5bc;
      }

      if (3 < *(byte *)(DAT_8000a6a8 + 10))           //If 3 is smaller then, so 4, 5 and 6
      {
        iVar7 = 0x32;                                 //2S/div, 1S/div, 500mS/div, factor is 64
        goto LAB_8000a5bc;
      }

      if (1 < *(byte *)(DAT_8000a6a8 + 10))           //If 1 is smaller then, so 2 and 3
        goto LAB_8000a5b0;                            //10S/div, 5S/div, factor is 10
    }

    iVar7 = 3;                                        //0, 1, 9, 10, 11
                                                      //50S/div, 20S/div, 50mS/div, 20mS/div, 10mS/div, factor is 3
  }
  else
  {
LAB_8000a5b0:                                         //12, 13
    iVar7 = 10;                                       //5mS/div, 2mS/div factor is 10
  }

LAB_8000a5bc:

  uVar4 = check_port_pin(DAT_8000a6ac,0xc);           //Battery charge detect  0x01C20890, 12

  puVar2 = PTR_DAT_8000a6b0;                          //0x80192ed4  some global variable, some accumulator??

  if (uVar4 == 0)                                     //If pin is low the battery is being charged
  {
    if (*(char *)(iVar1 + 0x39) == '\0')              //BatteryCharging variable
    {
      *PTR_DAT_8000a6b0 = 0;                          //If previous state was not charging this variable is set 0
    }

    *(undefined *)(iVar1 + 0x39) = 1;                 //Indicate charging
  }
  else
  {
    *(undefined *)(iVar1 + 0x39) = 0;                 //Indicate not charging
  }

  bVar3 = read_keyadc_data();                         //Battery level reading. result 0 - 0x3F

  //Input range 0 - 2V
  //Battery fully charged sends ~1.45V ==> 46 from ADC
  //When on charge it is ~1.62V ==> 51 from ADC
  //Lowest voltage for reading 0,78125, but below 0,90625 it will show red

  //0x80361378 Some base pointer

  //Some fractional addition to the adc value
  //            result from scan                                         byte from 0x8036137A = screen brightness setting                         0x068DB8BB
  uVar4 = (uint)bVar3 + (uint)((ulonglong)(uint)((int)(short)(ushort)*(byte *)(DAT_8000a6b4 + 2) * (int)(short)((ushort)bVar3 * 10)) * (ulonglong)DAT_8000a6b8 >> 0x28);  //High result byte logical shifted right an extra 8

//(100 * 630 * 109951163) / 1099511627776
//63000
// F618

//1/10000


  //At max the value will gain 6. (63 from the adc, 100 for the brightness)
  //Adds 4 when bat is full and screen is on max.

  //Check if on charge
  if (*(char *)(iVar1 + 0x39) != '\0')
  {
    uVar4 = uVar4 - 7;   //Take of 7 as compensation  0,21875V surcharge on battery when charging
  }

  //Check if result is less then 25
  if (uVar4 < 0x19)
  {
    //If so set it to the minimum
    uVar4 = 0x19;
  }

  //Divide ((the result minus the minimum) multiplied by 20) by 21
  pbVar5 = (byte *)divide((uVar4 - 0x19) * 0x14, 0x15);

  //Get data from global variable which is reset when charging starts
  //Is an array index
  bVar3 = *puVar2;


  //0x802F1906 some array where the result is stored
  DAT_8000a6bc[bVar3] = (byte)pbVar5;

  //As long as the index is lower than the factor obtained from timebase setting
  if ((int)(uint)bVar3 < iVar7 + -1)
  {
    //Increment the index and store it back
    *puVar2 = bVar3 + 1;
    return; //and quit
  }

  //When several samples are stored it comes here
  //true since none of the timebase compare paths lead to iVar7 being set zero
  bVar9 = iVar7 != 0;

  if (bVar9)
  {
    pbVar5 = DAT_8000a6bc; //Point to the data
  }

  *puVar2 = 0; //Reset the index

  //As long as there is data to process
  while (bVar9)
  {
    bVar3 = *pbVar5;          //Get the first byte
    pbVar5 = pbVar5 + 1;      //Point to the next one

    if (bVar3 < bVar8)        //Determine the lowest value
    {
      bVar8 = bVar3;          //Keep the lowest value of the samples
    }

    iVar7 = iVar7 + -1;       //One count done
    bVar9 = iVar7 != 0;       //Check on done
  }

  //Store result in BatteryChargeLevel
  *(byte *)(iVar1 + 0x38) = bVar8;

  display_battery_status();
}




uchar read_keyadc_data(void)

{
  return (uchar)((byte)*KEYADC_DATA & 0x3f);
}



void enable_keyadc(void)

{
  uint *puVar1;
  

//Default is 0x01000168
//   0      1       0      0       0      1        6        8
//0000 | 0001 | 00 00 | 0000 | 00 00 | 0001 | 0 1 10 | 10 0 0
//
//FIRST_CONVERT_DLY      1
//CONTINUE_TIME_SELECT   0
//KEY_MODE_SELECT        0 (NORMAL)
//LEVELA_B_CNT           1
//KEY_ADC_HOLD_KEY_EN    0
//KEY_ADC_HOLD_EN        1
//LEVELB_VOL             2
//KEY_ADC_SAMPLE_RATE    2 (62.5HZ)
//KEY_ADC_EN             0

//0x010000159

  puVar1 = KEYADC_CTRL;
  *KEYADC_CTRL = *KEYADC_CTRL & 0xffffcfff;  //Clear 0x3000
  *puVar1 = *puVar1;
  *puVar1 = *puVar1 & 0xffffffcf;            //Clear 0x30
  *puVar1 = *puVar1 | 0x10;                  //Set levelB_VOL ~1,8V
  *puVar1 = *puVar1 | 1;                     //Enable the ADC
  return;
}





//Display_battery_status

  set_frame_to_global_pointer();

  set_display_color(0xffffff);

  display_clear_rect(0x2c0,5,0x2d5,0x11);

  display_clear_rect(0x2be,9,0x2c1,0xd);

  iVar1 = DAT_8000bde4;

  if (*(byte *)(DAT_8000bde4 + 0x38) < 4)
  {
    uVar4 = 0xff0000;
  }
  else
  {
    uVar4 = 0xbb00;
  }

  set_display_color(uVar4);

  if (0x14 < *(byte *)(iVar1 + 0x38))
  {
    *(undefined *)(iVar1 + 0x38) = 0x14;
  }

  if (*(char *)(iVar1 + 0x38) != '\0')
  {
    display_clear_rect(0x2d5 - *(byte *)(iVar1 + 0x38),6,0x2d4,0x10);
  }

  if (*(char *)(iVar1 + 0x39) != '\0')
  {
    set_display_color(DAT_8000bde8);

    uVar4 = DAT_8000bdec;

    FUN_80018ca8(10,0x2c4,DAT_8000bdec);

    FUN_80018ca8(0xb,0x2c4,uVar4);

    FUN_80018ca8(0xc,0x2c4,uVar4);

    FUN_80018ef4(uVar4 | 1,8,0xe);

    FUN_80018ef4(0x2d0,9,0xd);

    FUN_80018ef4(uVar4 + 3,10);

    FUN_80018ef4(uVar4 + 4,0xb);
  }

  iVar7 = Start_Of_Screen_Mem;

  iVar1 = Screen_Frame_Buffer;

  uVar4 = 5;

  do
  {
    iVar6 = uVar4 * 800 + 0x2be;

    copy_short((void *)(iVar7 + iVar6 * 2),(void *)(iVar1 + iVar6 * 2),0x18);

    uVar4 = uVar4 + 1;
  } while (uVar4 < 0x24);

  return;
}

//------------------------------------------------------------------------------------------------------------------------------------------------
//Draw horz line

void FUN_80018ca8(int param_1,int param_2,uint param_3,undefined4 param_4)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  uint local_20;
  uint local_1c;
  
  local_20 = param_3;
  local_1c = param_4;

  FUN_8001936c();

  piVar1 = DAT_80018d2c;
  iVar2 = *(int *)(*DAT_80018d2c + 0x4c);
  uVar3 = param_2 + iVar2;
  param_3 = param_3 + iVar2;
  param_1 = param_1 + *(int *)(*DAT_80018d2c + 0x50);
  local_20 = uVar3 & 0xffff | param_1 * 0x10000;
  local_1c = param_3 & 0xffff | param_1 * 0x10000;

  iVar2 = FUN_8002ac10(&local_20);

  while (iVar2 != 0)
  {
    (***(code ***)(*piVar1 + 100))(uVar3,param_1,param_3);

    iVar2 = FUN_8002ab40();
  }

  FUN_80019a6c();
  return;
}

//------------------------------------------------------------------------------------------------------------------------------------------------
//Draw vert line

void FUN_80018ef4(int param_1,int param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint local_18;
  uint local_14;
  
  local_18 = param_3;
  local_14 = param_4;
  FUN_8001936c();
  iVar1 = *(int *)(*DAT_80018f68 + 0x50);
  uVar3 = param_1 + *(int *)(*DAT_80018f68 + 0x4c);
  param_2 = param_2 + iVar1;
  iVar1 = param_3 + iVar1;
  local_18 = uVar3 & 0xffff | param_2 * 0x10000;
  local_14 = uVar3 & 0xffff | iVar1 * 0x10000;
  iVar2 = FUN_8002ac10(&local_18);
  while (iVar2 != 0) {
    FUN_8001cc4c(uVar3,param_2,iVar1);
    iVar2 = FUN_8002ab40();
  }
  FUN_80019a6c();
  return;
}


//------------------------------------------------------------------------------------------------------------------------------------------------


