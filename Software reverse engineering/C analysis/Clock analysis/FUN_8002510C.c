//Does something with IO pins
//Sets Port C for SPI flash
void FUN_8002510c(void)
{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  uint *puVar4;
  uint uVar5;
  
  uVar1 = DAT_80036238;                            //0x01C20848. SPI on port C
  FUN_8001764c(DAT_80036238,0,2);
  FUN_8001764c(uVar1,1,2);
  FUN_8001764c(uVar1,2,2);
  FUN_8001764c(uVar1,3,2);
  puVar4 = DAT_80036240;
  uVar5 = *DAT_80036240;
  uVar3 = FUN_8000056c(1,0,0x14);
  *puVar4 = uVar5 | uVar3;
  puVar4 = puVar4 + -0x98;
  *puVar4 = uVar3 | *puVar4;
  iVar2 = DAT_80036244;
  *(undefined4 *)(DAT_80036244 + 0x24) = DAT_80036248;
  puVar4 = (uint *)(iVar2 + 4);
  *puVar4 = *puVar4 | 0x80000083;
  do {
  } while ((*puVar4 & 0x80000000) != 0);
  *(uint *)(iVar2 + 8) = *(uint *)(iVar2 + 8) & 0xfffffffc | 0x44;
  *(uint *)(iVar2 + 0x18) = *(uint *)(iVar2 + 0x18) | 0x80008000;
  return;
}

