

//void usb_irq_handle(int arg) in usb_dev.c


void usb_interrupt_handler(void)
{
  char cVar1;
  char *pcVar2;
  undefined4 uVar3;
  undefined uVar4;
  undefined uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  
  uVar4 = FUN_80029aec();
  uVar6 = FUN_80029c38();
  uVar7 = FUN_80029c10(2);
  uVar8 = FUN_80029c10(3);
  FUN_80029b5c(0x80);
  FUN_80029b5c(0x40);
  FUN_80029b5c(0x10);
  FUN_80029b5c(8);
  usb_dev_printf(s_________________________________80038c0c);
  usb_dev_printf(s__irq:_usb_irq=%02x,_tx_irq=%02x,_80038c30);
  pcVar2 = DAT_80038c6c;
  if ((uVar6 & 4) != 0) {
    usb_dev_printf(s_IRQ:_reset_80038c70);
    FUN_80029b5c(4);
    USBC_INT_ClearEpPendingAll(2);
    USBC_INT_ClearEpPendingAll(3);
    USBC_INT_ClearMiscPendingAll();
    *(undefined4 *)(pcVar2 + 4) = 1;
    *(undefined4 *)(pcVar2 + 8) = 0;
    FUN_80029e00(0);
    *(undefined *)(DAT_800299a8 + 0x98) = 0;
    return;
  }
  if ((uVar6 & 2) != 0) {
    usb_dev_printf(s_IRQ:_resume_80038c7c);
    FUN_80029b5c(2);
    *(undefined4 *)(pcVar2 + 4) = 1;
  }
  if ((uVar6 & 1) != 0) {
    usb_dev_printf(s_IRQ:_suspend_80038c8c);
    FUN_80029b5c(1);
    *(undefined4 *)(pcVar2 + 4) = 0;
    *(undefined4 *)(pcVar2 + 8) = 0;
  }
  if ((uVar6 & 0x20) != 0) {
    usb_dev_printf(s_IRQ:_disconnect_80038c9c);
    FUN_80029b5c(0x20);
    *(undefined4 *)(pcVar2 + 8) = 0;
    *(undefined4 *)(pcVar2 + 4) = 0;
  }
  if ((uVar7 & 1) != 0) {
    usb_dev_printf(s_USB_ep0_irq_80038cb0);
    FUN_80029afc(2,0);
    if (pcVar2[1] == '\0') {
      iVar9 = FUN_800298f0();
      iVar10 = DAT_80038cc0;
      if (iVar9 == 3) {
        pcVar2[1] = '\x03';
        *(undefined4 *)(iVar10 + 4) = 0x200;
        *(undefined4 *)(iVar10 + 8) = 0x200;
        usb_dev_printf(s__+++++++++++++++++++++++++++++++_80038cc4);
        usb_dev_printf(s__usb_enter_high_speed._80038e40);
        usb_dev_printf(s__+++++++++++++++++++++++++++++++_80038cc4);
      }
      else {
        pcVar2[1] = '\x02';
        *(undefined4 *)(iVar10 + 4) = 0x40;
        *(undefined4 *)(iVar10 + 8) = 0x40;
        usb_dev_printf(s__+++++++++++++++++++++++++++++++_80038cc4);
        usb_dev_printf(s__usb_enter_full_speed._80038cec);
        usb_dev_printf(s__+++++++++++++++++++++++++++++++_80038cc4);
      }
    }
    FUN_800381b8();
  }
  uVar6 = 1;
  do {
    if ((uVar8 & 1 << (uVar6 & 0xff)) != 0) {
      FUN_80029afc(3,uVar6 & 0xff);
      usb_dev_printf(PTR_s_USB_out_ep%d_irq_80038d04);
      uVar5 = FUN_80029aec();
      FUN_80029e00(uVar6 & 0xff);
      iVar10 = FUN_8002985c(3);
      if (iVar10 != 0) {
        usb_dev_printf(PTR_s_ERR:_rx_ep(%d)_is_stall_80038d08);
        FUN_800297a4(3);
      }
      iVar10 = FUN_8002988c(3);
      if (iVar10 != 0) {
        uVar11 = FUN_80029d7c(3);
        usb_dev_printf(PTR_s_rx_ep(%d)_data_ready_Len:%d!_80038d0c);
        uVar3 = DAT_80038d10;
        uVar12 = FUN_80029e4c(uVar6);
        FUN_80029dac(uVar12,uVar11,uVar3);
        *(undefined4 *)(pcVar2 + 0x14) = uVar11;
        cVar1 = *pcVar2;
        if (cVar1 == '\x01') {
          FUN_80038974(DAT_80038d10,uVar11);
        }
        else {
          if (cVar1 == '\x02') {
            FUN_80037c44(DAT_80038d10);
          }
          else {
            if (cVar1 == '\x03') {
              FUN_800390e4(DAT_80038d10);
            }
            else {
              if (cVar1 == '\x04') {
                thunk_FUN_800203c4(uVar3);
              }
            }
          }
        }
        FUN_8002990c(3,1);
      }
      FUN_80029e00(uVar5);
    }
    uVar6 = uVar6 + 1;
  } while ((int)uVar6 < 4);
  uVar6 = 1;
  do {
    if ((uVar7 & 1 << (uVar6 & 0xff)) != 0) {
      FUN_80029afc(2,uVar6 & 0xff);
      usb_dev_printf(PTR_s_USB_in_ep%d_irq_80038e58);
      uVar5 = FUN_80029aec();
      FUN_80029e00(uVar6 & 0xff);
      iVar10 = FUN_8002985c(2);
      if (iVar10 != 0) {
        usb_dev_printf(PTR_s_ERR:_tx_ep(%d)_is_stall_80038e5c);
        FUN_800297a4(2);
      }
      iVar10 = FUN_800298c4(2);
      if (iVar10 == 0) {
        usb_dev_printf(PTR_s_tx_ep(%d)_data_ready!_80038e60);
        if (*pcVar2 == '\x01') {
          FUN_8003896c();
        }
        else {
          if (*pcVar2 == '\x04') {
            FUN_80038ef0();
          }
        }
      }
      FUN_80029e00(uVar5);
    }
    uVar6 = uVar6 + 1;
  } while ((int)uVar6 < 4);
  *(undefined *)(DAT_80029e0c + 0x42) = uVar4;
  return;
}


