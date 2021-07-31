void main(void)

{
  int iVar1;
  undefined auStack568 [568];
  
  sys_clock_init();
  some_memory_stuff();
  sys_init_uart0(BAUD_115200);
  setup_timer_int();
  sys_spi0_init();
  fpga_init();
  turn_off_brightness();
  sys_init_display();
  FUN_8001931c();
  tp_i2c_setup();
  iVar1 = FUN_80033714(auStack568,&DAT_8003545c,1);
  if (iVar1 != 0) {
    *(undefined *)(DAT_80035460 + 2) = 100;
    fpga_write_cmd('8');
    fpga_write_data(-0x16);
    fpga_write_data((uchar)DEF_BRIGHTNESS);
    set_display_color(0);
    display_clear_rect(0,0,800,0x1e0);
    set_display_color(0xff0000);
    FUN_80019730(PTR_PTR_FUN_80035468);
    FUN_800197c8(0);
    display_text(s_SD_ERROR_8003546c,0x1e,0x32);
    do {
                    // WARNING: Do nothing block with infinite loop
    } while( true );
  }
  FUN_8001c138();
  FUN_8002a17c();
  FUN_80002b7c();
  FUN_800232e4();
  FUN_80016af4();
  FUN_8000690c();
  FUN_80009658();
  FUN_80001314();
  FUN_8000689c();
  FUN_800095e8();
  FUN_800068d4();
  FUN_80009620();
  FUN_80012a4c();
  FUN_80024e18();
  FUN_800266c4();
  FUN_800267e8();
  FUN_80002790();
  FUN_80026808();
  FUN_800267c4();
  FUN_80026828();
  FUN_8000696c();
  FUN_800096b8();
  FUN_80017ce0();
  FUN_80026918();
  FUN_8000a024();
  FUN_8000e8f0();
  FUN_8001d380();
  do {
    FUN_8000a54c();
    FUN_800253e8();
    thunk_FUN_8002b124();
    FUN_8001a3b4();
  } while( true );
}


