//Called from main
void load_config_data(void)

{
  read_from_flash(FLASH_CONFIG_DATA,DAT_80023304,500);  //0x001FD000, 0x8035344E, 500 bytes

  restore_config_data(DAT_80023304);  //0x8035344E
}





void restore_config_data(uint *address)  //0x8035344E

{
  undefined2 uVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  undefined2 *puVar5;
  uint *puVar6;
  int iVar7;
  undefined *puVar8;
  
  puVar5 = DAT_80027a1c;    //0x802F18B0
  iVar4 = DAT_80027a18;     //0x801FA24C    base of measurement settings
  iVar3 = DAT_80027a14;     //0x80361378    base of settings like screen brightness
  puVar2 = DAT_80027a10;    //0x8019D5A0    base of scope settings

  puVar6 = address + 0x53;
  puVar8 = (undefined *)(iVar4 + -1);
  iVar7 = 0xc;

  //                                                                               bytes
  puVar2[0] = *(undefined *)address;                    //channel 1 enable         0x8035344E   0
  puVar2[3] = *(undefined *)((int)address + 2);         //          volts/div      0x80353450   1
  puVar2[4] = *(undefined *)(address + 1);              //          fft enable     0x80353452   2
  puVar2[1] = *(undefined *)((int)address + 6);         //          coupling       0x80353454   3
  puVar2[2] = *(undefined *)(address + 2);              //          magnification  0x80353456   4

  //                                                                               bytes
  puVar2[0xc] = *(undefined *)((int)address + 10);      //channel 2 enable         0x80353458   5
  puVar2[0xf] = *(undefined *)(address + 3);            //          volts/div      0x8035345A   6
  puVar2[0x10] = *(undefined *)((int)address + 0xe);    //          fft enable     0x8035345C   7
  puVar2[0xd] = *(undefined *)(address + 4);            //          coupling       0x8035345E   8
  puVar2[0xe] = *(undefined *)((int)address + 0x12);    //          magnification  0x80353460   9

  //                                                                               byte
  puVar2[10] = *(undefined *)(address + 5);             //time base                0x80353462   10

  //                                                                               byte
  puVar2[0x16] = *(undefined *)((int)address + 0x16);   //move speed               0x80353464   11

  //                                                                               bytes
  puVar2[0x21] = *(undefined *)(address + 6);           //trigger mode             0x80353466   12
  puVar2[0x22] = *(undefined *)((int)address + 0x1a);   //trigger edge             0x80353468   13
  puVar2[0x23] = *(undefined *)(address + 7);           //trigger channel          0x8035346A   14

  //                                                                               byte
  puVar2[0x42] = *(undefined *)((int)address + 0x1e);   //right menu state         0x8035346C   15


  //                                                                                    shorts
  *(undefined2 *)(puVar2 + 0x24) = *(undefined2 *)(address + 0x14);                   //0x8035349E   trigger position on screen    40
  *(undefined2 *)(puVar2 + 0x26) = *(undefined2 *)((int)address + 0x52);              //0x803534A0   trigger level screen offset   41

  //                                                                                    shorts
  *(undefined2 *)(puVar2 + 6) = *(undefined2 *)(address + 0x15);                      //0x803534A2   channel 1 screen offset       42
  *(undefined2 *)(puVar2 + 0x12) = *(undefined2 *)((int)address + 0x56);              //0x803534A4   channel 2 screen offset       43

  //                                                                                    bytes
  *(undefined *)(iVar3 + 2) = *(undefined *)(address + 0x1e);                         //0x803534C6   screen brightness             60
  *(undefined *)(iVar3 + 3) = *(undefined *)((int)address + 0x7a);                    //0x803534C8   grid brightness               61
  *(undefined *)(iVar3 + 4) = *(undefined *)(address + 0x1f);                         //0x803534CA   always 50% trigger            62
  *(undefined *)(iVar3 + 7) = *(undefined *)((int)address + 0x7e);                    //0x803534CC   xy display mode               63

  //Measurement settings
  //Channel 1 enable 12 items                                                           bytes
  *(undefined *)(iVar4 + 0x100) = *(undefined *)(address + 0x28);                     //0x803534EE   Vmax          80
  *(undefined *)(iVar4 + 0x112) = *(undefined *)((int)address + 0xa2);                //0x803534F0   Vmin          81
  *(undefined *)(iVar4 + 0x122) = *(undefined *)(address + 0x29);                     //0x803534F2   Vavg          82
  *(undefined *)(iVar4 + 0x132) = *(undefined *)((int)address + 0xa6);                //0x803534F4   Vrms          83
  *(undefined *)(iVar4 + 0x142) = *(undefined *)(address + 0x2a);                     //0x803534F6   Vpp           84
  *(undefined *)(iVar4 + 0x152) = *(undefined *)((int)address + 0xaa);                //0x803534F8   Vp            85
  *(undefined *)(iVar4 + 0x162) = *(undefined *)(address + 0x2b);                     //0x803534FA   Freq          86
  *(undefined *)(iVar4 + 0x172) = *(undefined *)((int)address + 0xae);                //0x803534FC   Cycle         87
  *(undefined *)(iVar4 + 0x182) = *(undefined *)(address + 0x2c);                     //0x803534FE   Tim+          88
  *(undefined *)(iVar4 + 0x192) = *(undefined *)((int)address + 0xb2);                //0x80353500   Tim-          89
  *(undefined *)(iVar4 + 0x1a2) = *(undefined *)(address + 0x2d);                     //0x80353502   Duty+         90
  *(undefined *)(iVar4 + 0x1b2) = *(undefined *)((int)address + 0xb6);                //0x80353504   Duty-         91

  //Channel 2 enable 12 items                                                           bytes
  *(undefined *)(iVar4 + 0x1c2) = *(undefined *)(address + 0x2e);                     //0x80353506   Vmax          92
  *(undefined *)(iVar4 + 0x1d2) = *(undefined *)((int)address + 0xba);                //0x80353508   Vmin          93
  *(undefined *)(iVar4 + 0x1e2) = *(undefined *)(address + 0x2f);                     //0x8035350A   Vavg          94
  *(undefined *)(iVar4 + 0x1f2) = *(undefined *)((int)address + 0xbe);                //0x8035350C   Vrms          95
  *(undefined *)(iVar4 + 0x202) = *(undefined *)(address + 0x30);                     //0x8035350E   Vpp           96
  *(undefined *)(iVar4 + 0x212) = *(undefined *)((int)address + 0xc2);                //0x80353510   Vp            97
  *(undefined *)(iVar4 + 0x232) = *(undefined *)(address + 0x31);                     //0x80353512   Freq          98
  *(undefined *)(iVar4 + 0x242) = *(undefined *)((int)address + 0xc6);                //0x80353514   Cycle         99
  *(undefined *)(iVar4 + 0x252) = *(undefined *)(address + 0x32);                     //0x80353516   Tim+         100
  *(undefined *)(iVar4 + 0x262) = *(undefined *)((int)address + 0xca);                //0x80353518   Tim-         101
  *(undefined *)(iVar4 + 0x272) = *(undefined *)(address + 0x33);                     //0x8035351A   Duty+        102
  *(undefined *)(iVar4 + 0x282) = *(undefined *)((int)address + 0xce);                //0x8035351C   Duty-        103

  //Channel 1 calibration data                                                          shorts
  puVar5[0] = *(undefined2 *)(address + 0x3c);                                        //0x802F18B0 = 0x8035353E  channel1_calibration_factor    120
  puVar5[1] = *(undefined2 *)((int)address + 0xf2);                                   //0x802F18B2 = 0x80353540  channel1_calibration_data[0]
  puVar5[2] = *(undefined2 *)(address + 0x3d);                                        //0x802F18B4 = 0x80353542
  puVar5[3] = *(undefined2 *)((int)address + 0xf6);                                   //0x802F18B6 = 0x80353544
  puVar5[4] = *(undefined2 *)(address + 0x3e);                                        //0x802F18B8 = 0x80353546
  puVar5[5] = *(undefined2 *)((int)address + 0xfa);                                   //0x802F18BA = 0x80353548
  puVar5[6] = *(undefined2 *)(address + 0x3f);                                        //0x802F18BC = 0x8035354A  channel1_calibration_data[5] (needs to be copied into [6]!!)

  //Channel 2 calibration data                                                          shorts
  puVar5[7] = *(undefined2 *)((int)address + 0xfe);                                   //0x802F18BE = 0x8035354C  channel2_calibration_factor    127
  puVar5[8] = *(undefined2 *)(address + 0x40);                                        //0x802F18C0 = 0x8035354E  channel2_calibration_data[0]
  puVar5[9] = *(undefined2 *)((int)address + 0x102);                                  //0x802F18C2 = 0x80353550
  puVar5[10] = *(undefined2 *)(address + 0x41);                                       //0x802F18C4 = 0x80353552
  puVar5[0xb] = *(undefined2 *)((int)address + 0x106);                                //0x802F18C6 = 0x80353554
  puVar5[0xc] = *(undefined2 *)(address + 0x42);                                      //0x802F18C8 = 0x80353556
  puVar5[0xd] = *(undefined2 *)((int)address + 0x10a);                                //0x802F18CA = 0x80353558  channel2_calibration_data[5]   133


  //Some other calibration data that still needs to be investigated
  //                                                                                    shorts
  puVar5[0xe] = *(undefined2 *)(address + 0x43);                                      //0x802F18CC = 0x8035355A   134
  puVar5[0xf] = *(undefined2 *)((int)address + 0x10e);                                //0x802F18CE = 0x8035355C
  puVar5[0x10] = *(undefined2 *)(address + 0x44);                                     //0x802F18D0 = 0x8035355E
  puVar5[0x11] = *(undefined2 *)((int)address + 0x112);                               //0x802F18D2 = 0x80353560


  //                                                                                    bytes
  *(undefined *)(puVar5 + 0x12) = *(undefined *)(address + 0x45);                     //0x802F18D4 = 0x80353562
  *(undefined *)((int)puVar5 + 0x25) = *(undefined *)((int)address + 0x116);          //0x802F18D5 = 0x80353564
  *(undefined *)(puVar5 + 0x13) = *(undefined *)(address + 0x46);                     //0x802F18D6 = 0x80353566
  *(undefined *)((int)puVar5 + 0x27) = *(undefined *)((int)address + 0x11a);          //0x802F18D7 = 0x80353568
  *(undefined *)(puVar5 + 0x14) = *(undefined *)(address + 0x47);                     //0x802F18D8 = 0x8035356A
  *(undefined *)((int)puVar5 + 0x29) = *(undefined *)((int)address + 0x11e);          //0x802F18D9 = 0x8035356C

  //                                                                                    shorts
  puVar5[0x15] = *(undefined2 *)(address + 0x48);                                     //0x802F18DA = 0x8035356E
  puVar5[0x16] = *(undefined2 *)((int)address + 0x122);                               //0x802F18DC = 0x80353570
  puVar5[0x17] = *(undefined2 *)(address + 0x49);                                     //0x802F18DE = 0x80353572
  puVar5[0x18] = *(undefined2 *)((int)address + 0x126);                               //0x802F18E0 = 0x80353574
  puVar5[0x19] = *(undefined2 *)(address + 0x4a);                                     //0x802F18E2 = 0x80353576
  puVar5[0x1a] = *(undefined2 *)((int)address + 0x12a);                               //0x802F18E4 = 0x80353578

  //                                                                                    bytes
  *(undefined *)(puVar5 + 0x1b) = *(undefined *)(address + 0x4b);                     //0x802F18E6 = 0x8035357A
  *(undefined *)((int)puVar5 + 0x37) = *(undefined *)((int)address + 0x12e);          //0x802F18E7 = 0x8035357C
  *(undefined *)(puVar5 + 0x1c) = *(undefined *)(address + 0x4c);                     //0x802F18E8 = 0x8035357E
  *(undefined *)((int)puVar5 + 0x39) = *(undefined *)((int)address + 0x132);          //0x802F18E9 = 0x80353580
  *(undefined *)(puVar5 + 0x1d) = *(undefined *)(address + 0x4d);                     //0x802F18EA = 0x80353582
  *(undefined *)((int)puVar5 + 0x3b) = *(undefined *)((int)address + 0x136);          //0x802F18EB = 0x80353584

  //                                                                                    shorts
  puVar5[0x1e] = *(undefined2 *)(address + 0x4e);                                     //0x802F18EC = 0x80353586
  puVar5[0x1f] = *(undefined2 *)((int)address + 0x13a);                               //0x802F18EE = 0x80353588
  puVar5[0x20] = *(undefined2 *)(address + 0x4f);                                     //0x802F18F0 = 0x8035358A
  puVar5[0x21] = *(undefined2 *)((int)address + 0x13e);                               //0x802F18F2 = 0x8035358C
  puVar5[0x22] = *(undefined2 *)(address + 0x50);                                     //0x802F18F4 = 0x8035358E

  uVar1 = *(undefined2 *)((int)address + 0x142);                                      //             0x80353590

  //                                                                                    short
  puVar5[0x23] = uVar1;                                                               //0x802F18F6 = 0x80353590  time cursor enable??? for what



  //                                                                                    byte
  *(char *)(iVar4 + 0x292) = (char)uVar1;                                             //0x801FA4DE = 0x80353590  time cursor enable       161

  //                                                                                    shorts
  *(undefined2 *)(iVar4 + 0x294) = *(undefined2 *)(address + 0x51);                   //0x801FA4E0 = 0x80353592  time cursor 1 position   162
  *(undefined2 *)(iVar4 + 0x296) = *(undefined2 *)((int)address + 0x146);             //0x801FA4E2 = 0x80353594  time cursor 2 position   163

  //                                                                                    byte
  *(undefined *)(iVar4 + 0x29a) = *(undefined *)(address + 0x52);                     //0x801FA4E6 = 0x80353596  volt cursor enable       164

  //                                                                                    shorts
  *(undefined2 *)(iVar4 + 0x29c) = *(undefined2 *)((int)address + 0x14a);             //0x801FA4E8 = 0x80353598  volt cursor 1 position   165
  *(undefined2 *)(iVar4 + 0x29e) = *(undefined2 *)(address + 0x53);                   //0x801FA4EA = 0x8035359A  volt cursor 2 position   166


  //12 items times 2
  //Load and store bytes
  //Source start      0x8035359C
  //Destination start 0x801FA24C
  //This is the list of enabled measurement items in the order of displaying
  do {
    iVar7 = iVar7 + -1;
    puVar8[1] = *(undefined *)((int)puVar6 + 2);
    puVar6 = puVar6 + 1;
    puVar8 = puVar8 + 2;
    *puVar8 = *(undefined *)puVar6;
  } while (iVar7 != 0);


  //System OK flag (0x1432)                                                             short
  *(undefined2 *)(puVar2 + 0x44) = *(undefined2 *)(address + 100);                    //0x8019D5E4 = 803535DE
  return;
}








