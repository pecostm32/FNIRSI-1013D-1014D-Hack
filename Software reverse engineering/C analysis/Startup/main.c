//-----------------------------------------------------------------------------------------------

void main(void)

{
  int iVar1;
  undefined auStack568 [568];
  
  sys_clock_init();                         //Has been implemented
  setup_mmu();                              //Only caches enabled
  sys_init_uart0(BAUD_115200);              //Not needed because there is no free uart available
  setup_timer_int();
  sys_spi0_init();                          //Has been implemented
  fpga_init();                              //Done
  turn_off_brightness();                    //Also done
  sys_init_display();                       //Finished
  setup_display_lib();                      //Made my own and is working
  tp_i2c_setup();                           //Up and running

  //Needs to be done still, but is for a later moment in time
  iVar1 = check_sd_card((uint)auStack568,(uint)&DAT_8003545c,1);

  if (iVar1 != 0)
  {
    *(undefined *)(DAT_80035460 + 2) = 100;
    fpga_write_cmd('8');
    fpga_write_data(-0x16);
    fpga_write_data((uchar)DEFAULT_BRIGHTNESS);
    set_display_fg_color(0);
    display_fill_rect(0,0,800,0x1e0);
    set_display_fg_color(0xff0000);
    select_font(PTR_FONT_3_80035468);
    set_font_paint_mode(0);
    display_text(s_SD_ERROR_8003546c,0x1e,0x32);

    while( true );
  }

  check_hardware();                         //Hardware check only performed when flash address 0x001FE000 not contains 0x9086  
  FUN_8002a17c();                           //Some usb setup stuff
  setup_power_mon_int();
  load_config_data();
  check_sys_ok_load_config_on_fail();
  set_fpga_channel1_enable();               //Implemented
  set_fpga_channel2_enable();               //Implemented
  FUN_80001314();                           //Some variable initialization. set_trigger_level_dividers. Hard coded in my version
  set_fpga_channel1_voltperdiv();           //Implemented
  set_fpga_channel2_voltperdiv();           //Implemented
  set_fpga_channel1_coupling();             //Implemented
  set_fpga_channel2_coupling();             //Implemented
  FUN_80012a4c();                           //Implemented (fpga_enable_system)
  init_parameter_conversion();              //Implemented and working
  FUN_800266c4();                           //set_fpga_trigger_timebase
  set_fpga_trigger_channel();               //Implemented
  set_fpga_channel_trigger_channel();       //Implemented
  set_fpga_trigger_edge();                  //Implemented
  FUN_800267c4();                           //set_fpga_trigger_level  needs more research
  set_fpga_trigger_mode();                  //Implemented
  FUN_8000696c();                           //Channel 1 offset needs mre research
  FUN_800096b8();                           //Channel 2 offset needs mre research
  FUN_80017ce0();                           //Something with battery chagre level and FPGA command 0x3C. Implemented
  FUN_80026918();                           //Another hardware check only performed when flash address 0x001FE000 not contains 0x9086
  FUN_8000a024();                           //No idea about this one yet????
  setup_main_screen();                      //Implemented
  set_translated_brightness();              //Implemented

  do
  {
    monitor_battery();
    process_trace_data();
    display_cursors();
    touch_handler();                        //Mostly implemented
  } while( true );
}

//-----------------------------------------------------------------------------------------------

