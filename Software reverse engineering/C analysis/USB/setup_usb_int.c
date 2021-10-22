
void setup_usb_int(void)

{
  
  usb_dev_printf(PTR_s_sunxi_udc_disable_8002a15c);

  USBC_INT_DisableUsbMiscAll();

  USBC_INT_DisableEpAll(3);

  USBC_INT_DisableEpAll(2);

  //Clear all irq
  USBC_INT_ClearEpPendingAll(2);   //TX

  USBC_INT_ClearEpPendingAll(3);   //RX

  USBC_INT_ClearMiscPendingAll();

  usb_dev_printf(PTR_s_usbd_stop_work_8002a160);

  USBC_Dev_ConectSwitch(0);

  setup_interrupt(1,0x1a,(uint)PTR_usb_interrupt_handler_8002a164,2);

  change_status_reg_control_bits('\x7f');

  usb_dev_printf(PTR_s_sunxi_udc_enable_called_8002a168);

  *(undefined *)(DAT_8002a16c + 1) = 0;

  usb_dev_printf(PTR_s_CONFIG_USB_GADGET_DUALSPEED:_USB_8002a170);

  USBC_Dev_ConfigTransferMode(4,3);

  USBC_INT_EnableUsbMiscUint(0);

  USBC_INT_EnableUsbMiscUint(1);

  USBC_INT_EnableUsbMiscUint(2);

  USBC_INT_EnableUsbMiscUint(5);

  USBC_INT_EnableEp(2,0);

  usb_dev_printf(PTR_s_usbd_start_work_8002a174);

  USBC_Dev_ConectSwitch(1);

  delay_2(3000);  //Wait 3 seconds. This is done to allow a pc to make a connection before disabling the usb again. If turned of to soon it crashes the system
}


delay_2(uint ticks)
{
  uint uVar1;
  uint uVar2;
  uint extraout_r1;

  uVar1 = get_timer_ticks();

  do
  {
    uVar2 = get_timer_ticks();
  } while (uVar2 - uVar1 < extraout_r1);
  return;
}


