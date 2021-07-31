//Only called from init in main
//Initialize UART0
void FUN_8002809c(undefined4 param_1)
{
  undefined4 uVar1;
  uint *puVar2;
  uint uVar3;
  uint *puVar4;
  uint *puVar5;
  
  uVar3 = FUN_80000dc4(DAT_80028164,param_1);                //0x02DC6C00, 0x0001C200
  uVar1 = DAT_80028168;                                      //0x01C20890. Port E
  FUN_8001764c(DAT_80028168,0,5);                            //Set up pin PE0 for UART0
  FUN_8001764c(uVar1,1,5);                                   //Set up pin PE1 for UART0
  puVar2 = DAT_8002816c;                                     //0x01C20068. Some CCU register. Setup of UART0?
  *DAT_8002816c = *DAT_8002816c | 0x100000;
  puVar2[0x9a] = puVar2[0x9a] | 0x100000;                    //0x01c202d0.
  puVar2 = DAT_80028170;                                     //0x01C25000. UART0 base register address
  puVar5 = DAT_80028170 + 1;
  *puVar5 = 0;                                               //0x01c25004 = 0;
  puVar2[2] = 0xf7;                                          //0x01c25008 = 0xF7;
  puVar2[4] = 0;                                             //0x01c25010 = 0;
  puVar4 = puVar2 + 3;
  *puVar4 = *puVar4 | 0x80;                                  //0x01c2500c |= 0x80;
  *puVar2 = uVar3 >> 4 & 0xff;                               //0x01c25000 = 0xFF;
  *puVar5 = ((uVar3 >> 4) << 0x10) >> 0x18;                  //0x01c25004
  *puVar4 = *puVar4 & 0xffffff7f;                            //0x01c2500c
  *puVar4 = *puVar4 & 0xffffffe0 | 3;                        //0x01c2500c
  return;
}

