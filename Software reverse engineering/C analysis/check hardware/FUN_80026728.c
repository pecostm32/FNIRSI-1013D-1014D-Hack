//Function to control something in the FPGA

void FUN_80026728(void)

{
  uint *ptr;
  int iVar1;
  uchar uVar2;
  
  iVar1 = DAT_800267bc;
  *(undefined *)(DAT_800267bc + 3) = 0;
  *(undefined2 *)(iVar1 + 6) = 200;
  *(undefined *)(iVar1 + 0xf) = 0;
  *(undefined2 *)(iVar1 + 0x12) = 200;
  *(undefined *)(iVar1 + 10) = 0x13;

  fpga_write_cmd(0x33);

  if (*(char *)(iVar1 + 3) == '\x06')
  {
    uVar2 = '\x05';
  }
  else 
  {
    uVar2 = *(uchar *)(iVar1 + 3);
  }

  fpga_write_data(uVar2);

  fpga_write_cmd(0x36);

  if (*(char *)(iVar1 + 0xf) == '\x06')
  {
    uVar2 = '\x05';
  }
  else 
  {
    uVar2 = *(uchar *)(iVar1 + 0xf);
  }

  fpga_write_data(uVar2);


  FUN_8000696c();               //Write some data to FPGA via cmd 0x32
  FUN_800096b8();               //Write some data to FPGA via cmd 0x35
  FUN_800266c4();               //Write some data to FPGA via command retreived from settings.

  fpga_write_cmd(0x17);
  fpga_write_data(0x00);

  delay_2(100);

  FUN_80025b7c(DAT_800267c0);   //Write the given 4 bytes to FPGA via cmd 0x0E

  fpga_write_cmd(0x0F);
  fpga_write_data(0x01);

  return;
}

