//Check hardware function

void FUN_8001c138(void)
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  undefined8 uVar5;
  
  iVar1 = FUN_8002330c();
  if (iVar1 == 2)
  {
    return;
  }

  FUN_80027d88();
  FUN_8000690c();
  FUN_80009658();
  FUN_80001314();
  FUN_8000689c();
  FUN_800095e8();
  FUN_800068d4();
  FUN_80009620();
  FUN_80012a4c();
  FUN_800267e8();
  FUN_80002790();
  FUN_80026808();
  FUN_800267c4();
  FUN_80026828();
  FUN_8000696c();
  FUN_800096b8();

  FUN_800169f8(0x38);               //Set default brightness
  FUN_800168fc(0xea);
  FUN_800168fc(0x60);

  FUN_80017778();
  FUN_80019704(0);                  //Set display color???
  FUN_80018f6c(0,0,800,0x1e0);
  FUN_80019730(PTR_PTR_FUN_8001c4ac);  //Print string on dispaly??
  FUN_800197c8(0);

  FUN_800169f8(6);             //FPGA command 6
  uVar2 = FUN_80016850();
  uVar3 = FUN_80016850();

  if ((uVar3 | (uVar2 & 0xff) << 8) != 0x1432)
  {
    FUN_80019704(0xff0000);
    FUN_80018bf8(&DAT_8001c4b0,0x1e,0x5a);
    FUN_80018bf8(s_Failed_8001c4b8,100,0x5a);
    do {
                    // WARNING: Do nothing block with infinite loop
    } while( true );
  }

  FUN_80019704(0xffffff);
  FUN_80018bf8(&DAT_8001c4b0,0x1e,0x5a);
  FUN_80018bf8(&DAT_8001c4c0,100,0x5a);
  FUN_80017ce0();


  iVar1 = FUN_80017928(); //Get data from FPGA command 0x41

  if (iVar1 != 0x8150)
  {
    FUN_80019704(0xff0000);
    FUN_80018bf8(s_Encrypt_8001c4c4,0x1e,0x6e);  //Print string on dispaly??
    FUN_80018bf8(s_Failed_8001c4b8,100,0x6e);
    do {
                    // WARNING: Do nothing block with infinite loop
    } while( true );
  }

  FUN_80019704(0xffffff);
  FUN_80018bf8(s_Encrypt_8001c4c4,0x1e,0x6e);
  FUN_80018bf8(&DAT_8001c4c0,100,0x6e);

  iVar1 = FUN_80000e94();   //Check on ADC functionality
  if (iVar1 != 3) {
    if (iVar1 == 1) {
      FUN_80019704(0xff0000);
      FUN_80018bf8(s_AD9288_2_8001c4f8,0x1e,0x82);
      FUN_80018bf8(s_Failed_8001c4b8,0x78,0x82);
      do {
                    // WARNING: Do nothing block with infinite loop
      } while( true );
    }
    if (iVar1 != 2) {
      FUN_80019704(0xff0000);
      FUN_80018bf8(s_AD9288_1_2_8001c4cc,0x1e,0x82);
      FUN_80018bf8(s_Failed_8001c4b8,0x78,0x82);
      do {
                    // WARNING: Do nothing block with infinite loop
      } while( true );
    }
    FUN_80019704(0xff0000);
    FUN_80018bf8(s_AD9288_1_8001c504,0x1e,0x82);
    FUN_80018bf8(s_Failed_8001c4b8,0x78,0x82);
    do {
                    // WARNING: Do nothing block with infinite loop
    } while( true );
  }
  FUN_80019704(0xffffff);
  FUN_80018bf8(s_AD9288_8001c4d8,0x1e,0x82);
  FUN_80018bf8(&DAT_8001c4c0,100,0x82);
  iVar1 = FUN_80027ef8();
  if (iVar1 == 0) {
    FUN_80019704(0xff0000);
    FUN_80018bf8(s_Analog_8001c4e0,0x1e,0x96);
    FUN_80018bf8(s_Failed_8001c4b8,100,0x96);
    do {
                    // WARNING: Do nothing block with infinite loop
    } while( true );
  }
  FUN_80019704(0xffffff);
  FUN_80018bf8(s_Analog_8001c4e0,0x1e,0x96);
  FUN_80018bf8(&DAT_8001c4c0,100,0x96);
  FUN_80019704(0xffffff);
  FUN_80018bf8(s_Touch_8001c4e8,0x1e,0xaa);
  FUN_80018bf8(&DAT_8001c4f0,0x67,0xa7);
  iVar1 = FUN_80028568();
  if (iVar1 == 0) {
    FUN_80019704(0xff0000);
    pcVar4 = s_Failed_8001c4b8;
  }
  else {
    FUN_80019704(0xffffff);
    pcVar4 = &DAT_8001c4f4;
  }
  FUN_80018bf8(pcVar4,100,0xaa);
  if (iVar1 == 0) {
    return;
  }
  FUN_80019704(0xffffff);
  FUN_80018bf8(s_Hard_Checked_Successful___8001c510,0x1e,0xbe);
  iVar1 = DAT_8001c52c;
  *(undefined *)(DAT_8001c52c + 3) = 0;
  *(undefined2 *)(iVar1 + 6) = 300;
  *(undefined *)(iVar1 + 0xf) = 0;
  *(undefined2 *)(iVar1 + 0x12) = 100;
  *(undefined *)(iVar1 + 10) = 0x13;
  FUN_8000696c();
  FUN_800096b8();
  FUN_8000689c();
  FUN_800095e8();
  FUN_800266c4();
  FUN_80025bb0();
  uVar3 = FUN_80023564(0,500);
  uVar2 = uVar3;
  do {
    uVar5 = FUN_80023564(uVar3);
    uVar3 = (int)uVar5 - uVar2;
  } while (uVar3 < (uint)((ulonglong)uVar5 >> 0x20));
  return;
}


