//--------------------------------------------------------------------------------

void fpga_start_calib_conversion(void)

{
  uint *port;
  byte bVar1;
  
  fpga_write_cmd('(');            //0x28
  fpga_write_data('\0');

                                  //Missing the 0x0F command. Could this be a signal to use trigger

  fpga_write_cmd('\x01');
  fpga_write_data('\x01');

  fpga_write_cmd('\x05');

  do
  {
    bVar1 = fpga_read_data();
  } while ((bVar1 & 1) == 0);

  do
  {
    bVar1 = fpga_read_data();
  } while ((bVar1 & 1) == 0);

  fpga_write_cmd('\x01');
  fpga_write_data(0x00);
}

//--------------------------------------------------------------------------------

