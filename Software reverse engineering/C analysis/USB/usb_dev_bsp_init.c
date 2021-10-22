void usb_dev_bsp_init(int param)
{
  uart_printf(s_usb_init..._80037ec4);

  if ((uint)*DAT_80037ed4 != param)  //Not in the code I found, but some sort of flag to avoid doing things again
  {
    *DAT_80037ed4 = (byte)param;     //0x8019D1DC

     usb_phy_open_clock();

    USBC_PhyConfig();          //Not an exact match with the code I found, but it is targeting the same register

    USBC_ConfigFIFO_Base();    //Targets SUNXI_SRAMC_BASE + 0x04. No documentation available for this register

    USBC_EnableDpDmPullUp();   //Again not an exact match but the target register is the same (USBC_BP_ISCR_VBUS_VALID_SRC = bit 10, but also bit 11 is set???)

    USBC_EnableIdPullUp();     //Couple of bit are cleared and one bit is set, which is also done in the sunxi code

    USBC_ForceId(2);           //Make it an usb device (USBC_ID_TYPE_DEVICE)

    USBC_ForceVbusValid(2);    //Set bust type high (USBC_VBUS_TYPE_HIGH)

    USBC_SelectBus(0,0,0);     //First zero is defined as USBC_IO_TYPE_PIO. Is io_type. End point 0 is set idle (control endpoint)
    return;
  }

  uart_printf(s_usb_type_err..._80037ed8);
  return;
}

