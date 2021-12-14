
//--------------------------------------------------------------------------------

void fpga_setup_for_calib(void)

{
  uint *port;
  int iVar1;
  uchar uVar2;
  
  iVar1 = DAT_800267bc;
  *(undefined *)(DAT_800267bc + 3) = 0;   //Channel 1 volt/div on 5V/div
  *(undefined2 *)(iVar1 + 6) = 200;       //Channel 1 trace offset on 200
  *(undefined *)(iVar1 + 0xf) = 0;        //Channel 2 volt/div on 5V/div
  *(undefined2 *)(iVar1 + 0x12) = 200;    //Channel 2 trace offset on 200
  *(undefined *)(iVar1 + 10) = 0x13;      //Time base 20us/div

  //Write these setting
  fpga_write_cmd('3');                      //Channel 1 volt per div setting
  if (*(char *)(iVar1 + 3) == '\x06')
  {
    uVar2 = '\x05';
  }
  else
  {
    uVar2 = *(uchar *)(iVar1 + 3);
  }

  fpga_write_data(uVar2);

  fpga_write_cmd('6');                      //Channel 2 volt per div setting
  if (*(char *)(iVar1 + 0xf) == '\x06')
  {
    uVar2 = '\x05';
  }
  else
  {
    uVar2 = *(uchar *)(iVar1 + 0xf);
  }

  fpga_write_data(uVar2);


  set_fpga_channel1_offset();
  set_fpga_channel2_offset();

  set_fpga_trigger_timebase();             //Sets the timebase to 20us/div via translate chip


  fpga_write_cmd('\x17');                  //Trigger level on 0
  fpga_write_data('\0');

  delay_2(100);

  write_fpga_cmd_0x0E(DAT_800267c0);           //Set short timebase command 0x00000BB8  ==> 100us/div

  write_fpga_cmd_0x0F();                       //Writes command 0x0F with a 1, which signals end of procedure???

}

//--------------------------------------------------------------------------------

