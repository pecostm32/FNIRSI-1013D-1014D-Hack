//-----------------------------------------------------------------------------------------------

void reset_config_data(void)

{
  undefined *puVar1;
  undefined *puVar2;
  int iVar3;
  
  puVar1 = DAT_80027eec;     //0x8019D5A0
  puVar2 = DAT_80027ef0;     //0x801FA24C
  iVar3 = DAT_80027ef4;      //0x80361378

  //channel 1
  puVar1[0] = 1;
  puVar1[1] = 0;
  puVar1[2] = 0;
  puVar1[3] = 0;
  puVar1[4] = 0;

  *(undefined2 *)(puVar1 + 6) = 300;

  //channel 2
  puVar1[0xc] = 1;
  puVar1[0xe] = 0;
  puVar1[0xd] = 0;
  puVar1[0xf] = 0;
  puVar1[0x10] = 0;
  *(undefined2 *)(puVar1 + 0x12) = 100;

  //Trigger
  puVar1[0x21] = 0;
  puVar1[0x22] = 0;
  puVar1[0x23] = 0;
  *(undefined2 *)(puVar1 + 0x26) = 200;
  *(undefined2 *)(puVar1 + 0x24) = 0x16a;

  //mpve speed
  puVar1[0x16] = 0;

  //Time base
  puVar1[10] = 0x13;

  //Some flag
  puVar1[0x48] = 0;

  //Measurement settings
  //0x801FA24C
  //5 items in the display list
  puVar2[0] = 5;
  puVar2[1] = 4;
  puVar2[2] = 7;
  puVar2[3] = 0x11;
  puVar2[4] = 0x13;

  //Enable these items
  puVar2[0x132] = 1;  //channel 1 Vrms
  puVar2[0x142] = 1;  //channel 1 Vpp
  puVar2[0x162] = 1;  //Channel 1 Freq
  puVar2[0x202] = 1;  //Channel 2 Vpp
  puVar2[0x232] = 1;  //Channel 2 Freq

  puVar2[0x100] = 0;
  puVar2[0x112] = 0;
  puVar2[0x122] = 0;
  puVar2[0x152] = 0;
  puVar2[0x172] = 0;
  puVar2[0x182] = 0;
  puVar2[0x192] = 0;
  puVar2[0x1a2] = 0;
  puVar2[0x1b2] = 0;
  puVar2[0x1c2] = 0;
  puVar2[0x1d2] = 0;
  puVar2[0x1e2] = 0;
  puVar2[0x1f2] = 0;
  puVar2[0x212] = 0;
  puVar2[0x242] = 0;
  puVar2[0x252] = 0;
  puVar2[0x262] = 0;
  puVar2[0x272] = 0;
  puVar2[0x282] = 0;

  //clear the rest of the list
  memclear((uint)(puVar2 + 5),0x13);

  //Time cursor disabled
  puVar2[0x292] = 0;

  *(undefined2 *)(puVar2 + 0x294) = 0xb7;
  *(undefined2 *)(puVar2 + 0x296) = 0x223;

  puVar2[0x29a] = 0;

  *(undefined2 *)(puVar2 + 0x29c) = 0xa7;
  *(undefined2 *)(puVar2 + 0x29e) = 0x148;


  puVar1[0x42] = 0;
  puVar1[0x18] = 1;
  puVar1[0x17] = 1;

  *(undefined *)(iVar3 + 2) = 100;
  *(undefined *)(iVar3 + 3) = 0xf;
  *(undefined *)(iVar3 + 4) = 1;
  *(undefined *)(iVar3 + 7) = 0;
  return;
}

//-----------------------------------------------------------------------------------------------

