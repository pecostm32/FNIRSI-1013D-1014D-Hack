void FUN_80025b7c(uint param_1)

{
  uint *ptr;
  
  fpga_write_cmd(0x0E);
  fpga_write_data((uchar)(param_1 >> 0x18));
  fpga_write_data((uchar)(param_1 >> 0x10));
  fpga_write_data((uchar)(param_1 >> 8));
  fpga_write_data((uchar)(param_1 & 0xFF));
  return;
}

