
void usb_interrupt_handler(void)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  byte *buf;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  void *fifo;
  
  uVar4 = USBC_GetActiveEp();

  uVar5 = USBC_INT_MiscPending();
  uVar6 = USBC_INT_EpPending(2);             //USBC_EP_TYPE_TX
  uVar7 = USBC_INT_EpPending(3);             //USBC_EP_TYPE_RX

  //Done in filtrate_irq_misc(). Only thing missing is clearing these in uVar5 (usb_irq)
  USBC_INT_ClearMiscPending(0x80);           //USBC_BP_INTUSB_VBUS_ERROR
  USBC_INT_ClearMiscPending(0x40);           //USBC_BP_INTUSB_SESSION_REQ
  USBC_INT_ClearMiscPending(0x10);           //USBC_BP_INTUSB_CONNECT
  USBC_INT_ClearMiscPending(8);              //USBC_BP_INTUSB_SOF

  usb_dev_printf(s_________________________________80038c0c);
  usb_dev_printf(s__irq:_usb_irq=%02x,_tx_irq=%02x,_80038c30);

  pcVar2 = DAT_80038c6c;                      //0x8019D1DC    base of state machine variables  device_type, current_speed, usb_connect, usb_ep0_state

  if ((uVar5 & 4) != 0)                       //USBC_BP_INTUSB_RESET
  {
    usb_dev_printf(s_IRQ:_reset_80038c70);

    USBC_INT_ClearMiscPending(4);             //USBC_BP_INTUSB_RESET

    //Done in clear_all_irq()
    USBC_INT_ClearEpPendingAll(2);            //USBC_EP_TYPE_TX
    USBC_INT_ClearEpPendingAll(3);            //USBC_EP_TYPE_RX
    USBC_INT_ClearMiscPendingAll();

    *(undefined4 *)(pcVar2 + 4) = 1;           //usb_connect
    *(undefined4 *)(pcVar2 + 8) = 0;           //usb_ep0_state

    USBC_SelectActiveEp(0);

    *(undefined *)(DAT_800299a8 + 0x98) = 0;   //0x01C13000 + 0x98 ==> FADDR
    return;
  }

  if ((uVar5 & 2) != 0)                        //USBC_BP_INTUSB_RESUME
  {
    usb_dev_printf(s_IRQ:_resume_80038c7c);

    USBC_INT_ClearMiscPending(2);              //USBC_BP_INTUSB_RESUME

    *(undefined4 *)(pcVar2 + 4) = 1;           //usb_connect
  }

  if ((uVar5 & 1) != 0)                        //USBC_BP_INTUSB_SUSPEND
  {
    usb_dev_printf(s_IRQ:_suspend_80038c8c);

    USBC_INT_ClearMiscPending(1);              //USBC_BP_INTUSB_SUSPEND
    *(undefined4 *)(pcVar2 + 4) = 0;           //usb_connect
    *(undefined4 *)(pcVar2 + 8) = 0;           //usb_ep0_state
  }

  if ((uVar5 & 0x20) != 0)                     //USBC_INTUSB_DISCONNECT
  {
    usb_dev_printf(s_IRQ:_disconnect_80038c9c);

    USBC_INT_ClearMiscPending(0x20);           //USBC_INTUSB_DISCONNECT

    *(undefined4 *)(pcVar2 + 4) = 0;           //usb_connect
    *(undefined4 *)(pcVar2 + 8) = 0;           //usb_ep0_state
  }

  if ((uVar6 & 1) != 0)                        //USBC_BP_INTTx_FLAG_EP0
  {
    usb_dev_printf(s_USB_ep0_irq_80038cb0);

    USBC_INT_ClearEpPending(2,0);              //USBC_EP_TYPE_TX

    if (pcVar2[1] == '\0')                     //current_speed
    {
      uVar5 = USBC_Dev_QueryTransferMode();
      iVar3 = DAT_80038cc0;

      if (uVar5 == 3)                          //USBC_TS_MODE_HS
      {
        pcVar2[1] = '\x03';                    //current_speed
        *(undefined4 *)(iVar3 + 4) = 0x200;    //0x8019D1FC    end point sizes
        *(undefined4 *)(iVar3 + 8) = 0x200;
        usb_dev_printf(s__+++++++++++++++++++++++++++++++_80038cc4);
        usb_dev_printf(s__usb_enter_high_speed._80038e40);
        usb_dev_printf(s__+++++++++++++++++++++++++++++++_80038cc4);
      }
      else
      {
        pcVar2[1] = '\x02';
        *(undefined4 *)(iVar3 + 4) = 0x40;
        *(undefined4 *)(iVar3 + 8) = 0x40;
        usb_dev_printf(s__+++++++++++++++++++++++++++++++_80038cc4);
        usb_dev_printf(s__usb_enter_full_speed._80038cec);
        usb_dev_printf(s__+++++++++++++++++++++++++++++++_80038cc4);
      }
    }

    usb_handle_ep0();
  }

  uVar5 = 1;      //i from the for loop

  do
  {
    if ((uVar7 & 1 << (uVar5 & 0xff)) != 0)
    {
      USBC_INT_ClearEpPending(3,(byte)uVar5);    //USBC_EP_TYPE_RX

      usb_dev_printf(PTR_s_USB_out_ep%d_irq_80038d04);

      //This is usb_handle_epn_out();
      uVar8 = USBC_GetActiveEp();         //Probably not needed since no other process uses the USB interface

      USBC_SelectActiveEp(uVar5 & 0xff);  //When only one endpoint is used it can be monitored at its own addresses???

      uVar9 = USBC_Dev_IsEpStall(3);       //USBC_EP_TYPE_RX

      if (uVar9 != 0)
      {
        usb_dev_printf(PTR_s_ERR:_rx_ep(%d)_is_stall_80038d08);
        USBC_Dev_EpClearStall(3);           //USBC_EP_TYPE_RX
      }


      uVar9 = USBC_Dev_IsReadDataReady(3);  //USBC_EP_TYPE_RX

      if (uVar9 != 0)
      {
        uVar9 = USBC_ReadLenFromFifo(3);     //USBC_EP_TYPE_RX

        usb_dev_printf(PTR_s_rx_ep(%d)_data_ready_Len:%d!_80038d0c);

        buf = DAT_80038d10;

        fifo = USBC_SelectFIFO(uVar5);

        USBC_ReadPacket(fifo,uVar9,buf);

        *(uint *)(pcVar2 + 0x14) = uVar9;       //usb_rx_buf_len

        cVar1 = *pcVar2;                        //Type of device active. Global variable set on init to 4 and never changes!!!!

        if (cVar1 == '\x01')
        {
          usb_hid_out_ep_callback(DAT_80038d10,uVar9);
        }
        else
        {
          if (cVar1 == '\x02')
          {
            FUN_80037c44(DAT_80038d10);
          }
          else
          {
            if (cVar1 == '\x03')
            {
              FUN_800390e4(DAT_80038d10);         //This one returns directly
            }
            else
            {
              if (cVar1 == '\x04')
              {
                usb_handle_mass_storage_write(buf,uVar9);   //Only one realy used
              }
            }
          }
        }

        USBC_Dev_ReadDataStatus(3,1);        //USBC_EP_TYPE_RX
      }

      USBC_SelectActiveEp(uVar8 & 0xff);
    }
    uVar5 = uVar5 + 1;
  } while ((int)uVar5 < 4);

  uVar5 = 1;

  do
  {
    if ((uVar6 & 1 << (uVar5 & 0xff)) != 0)
    {
      USBC_INT_ClearEpPending(2,(byte)uVar5);       //USBC_EP_TYPE_TX

      usb_dev_printf(PTR_s_USB_in_ep%d_irq_80038e58);

      //This is usb_handle_epn_in();
      uVar7 = USBC_GetActiveEp();

      USBC_SelectActiveEp(uVar5 & 0xff);

      uVar8 = USBC_Dev_IsEpStall(2);     //USBC_EP_TYPE_TX

      if (uVar8 != 0)
      {
        usb_dev_printf(PTR_s_ERR:_tx_ep(%d)_is_stall_80038e5c);
        USBC_Dev_EpClearStall(2);         //USBC_EP_TYPE_TX
      }

      uVar8 = USBC_Dev_Get_Tx_Status(2);   //USBC_EP_TYPE_TX

      if (uVar8 == 0)
      {
        usb_dev_printf(PTR_s_tx_ep(%d)_data_ready!_80038e60);

        if (*pcVar2 == '\x01')
        {
          FUN_8003896c();
        }
        else
        {
          if (*pcVar2 == '\x04')
          {
            usb_handle_mass_storage_read();
          }
        }
      }

      USBC_SelectActiveEp(uVar7 & 0xff);
    }
    uVar5 = uVar5 + 1;
  } while ((int)uVar5 < 4);

  *(char *)(DAT_80029e0c + 0x42) = (char)uVar4;   //USBC_SelectActiveEp
  return;
}


