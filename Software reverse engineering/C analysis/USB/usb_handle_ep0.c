
void usb_handle_ep0(void)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  char *pcVar5;
  void *pvVar6;
  bool bVar7;
  byte local_20 [12];
  
  USBC_SelectActiveEp(0);

  uVar2 = USBC_Dev_IsEpStall(1);   //USBC_EP_TYPE_EP0

  pcVar5 = DAT_80038408;                      //0x8019D1DC    base of state machine variables  device_type, current_speed, usb_connect, usb_ep0_state

  if (uVar2 == 0)        //Not in stall
  {
    uVar2 = USBC_Dev_Ctrl_IsSetupEnd();

    if (uVar2 != 0)
    {
      usb_dev_printf(s_handle_ep0:_ep0_setup_end_8003841c);
      USBC_Dev_Ctrl_ClearSetupEnd();
      *(undefined4 *)(pcVar5 + 8) = 0;         //usb_ep0_state = EP0_IDLE;
    }

    usb_dev_printf(s_usb_ep0_state:%d_80038438);

    USBC_Dev_Read_EP0_CSR();

    usb_dev_printf(s_ep0csr:0x%02x_8003844c);

    uVar2 = USBC_Dev_IsReadDataReady(1);   //USBC_EP_TYPE_EP0

    if (uVar2 != 0)
    {
      *(undefined4 *)(pcVar5 + 8) = 0;        //usb_ep0_state = EP0_IDLE;
    }

    iVar3 = *(int *)(pcVar5 + 8);

    if (iVar3 == 0)               //usb_ep0_state == EP0_IDLE
    {
      uVar2 = USBC_Dev_IsReadDataReady(1); //Check the data ready flag again

      if (uVar2 != 0)       //If data recieved handle it
      {
        uVar2 = USBC_ReadLenFromFifo(1);   //Get the length of the received data

        usb_dev_printf(s_ep0_len_:%d._80038484);

        if (uVar2 != 8)
        {
          iVar3 = 0xf;

          do
          {
            uVar2 = USBC_ReadLenFromFifo(1);
            bVar7 = iVar3 == 0;
            iVar3 = iVar3 + -1;

            if (bVar7)
            {
              usb_dev_printf(s_ep0_len_wait_:%d._80038494);

              if (uVar2 != 8)
              {
                usb_dev_printf(s_ERR:_data_len_=_%d,_not_setup_da_800384cc);
                USBC_Dev_ReadDataStatus(1,0);
                USBC_Dev_EpSendStall(1);
                return;
              }

              goto LAB_800382c4;
            }
          } while (uVar2 != 8);

          usb_dev_printf(s_ep0_len_wait_:%d._80038494);
        }

LAB_800382c4:
        pvVar6 = USBC_SelectFIFO(0);
        USBC_ReadPacket(pvVar6,uVar2,local_20);
        USBC_Dev_ReadDataStatus(1,0);

        if ((local_20[0] & 0x80) == 0)
        {
          uVar4 = 2;
        }
        else {
          uVar4 = 1;
        }

        *(undefined4 *)(pcVar5 + 8) = uVar4;


        //This is a global variable set on init of the usb device, so no relation to the actual interface
        cVar1 = *pcVar5;

        if ((cVar1 != '\x01' && cVar1 != '\x02') && (cVar1 != '\x03' && cVar1 != '\x04'))
        {
          usb_dev_printf(s_ERR:_usb_class_%d_not_suppost!!!_800384a8);
          return;
        }

        usb_mass_setup_handle(local_20,uVar2);
        return;
      }

      pcVar5 = s_ERR:_data_is_ready,_can_not_read_8003845c;
LAB_80038628:
      usb_dev_printf(pcVar5);
      return;
    }

    if (iVar3 == 1)    //EP0_IN_DATA_PHASE
    {
      if (*(int *)(pcVar5 + 0x10) == 0)  //usb_tx_pos
      {
        usb_dev_printf(s_in_data_has_sended!_80038638);
      }
      else
      {
        usb_dev_printf(s_in_data_is_not_write_ok!_800384f4);
        usb_dev_printf(s_usb_tx_pos_:_%d_80038510);
        usb_dev_printf(s_usb_tx_buf_len_:_%d_80038524);

        if (0x40 < *(int *)(pcVar5 + 0xc) - *(int *)(pcVar5 + 0x10))
        {
          pvVar6 = USBC_SelectFIFO(0);
          USBC_WritePacket(pvVar6,*DAT_8003853c,(void *)(*(int *)(pcVar5 + 0x1c) + *(int *)(pcVar5 + 0x10)));
          USBC_Dev_WriteDataStatus(1,0);
          *(int *)(pcVar5 + 0x10) = *(int *)(pcVar5 + 0x10) + 0x40;
          return;
        }

        usb_dev_printf(s_write_end_80038650);
        pvVar6 = USBC_SelectFIFO(0);
        USBC_WritePacket(pvVar6,*(int *)(pcVar5 + 0xc) - *(int *)(pcVar5 + 0x10),(void *)(*(int *)(pcVar5 + 0x1c) + *(int *)(pcVar5 + 0x10)));
        USBC_Dev_WriteDataStatus(1,1);
        *(undefined4 *)(pcVar5 + 0x10) = 0;
      }
    }
    else
    {
      if (iVar3 == 2)       //EP0_OUT_DATA_PHASE
      {
        uVar2 = USBC_Dev_IsReadDataReady(1);

        if (uVar2 != 0)
        {
          uVar2 = USBC_ReadLenFromFifo(1);
          usb_dev_printf(s_ep0_out_intr_len_:%d._80038690);
          pvVar6 = USBC_SelectFIFO(0);
          USBC_ReadPacket(pvVar6,uVar2,local_20);
          USBC_Dev_ReadDataStatus(1,0);
          *(undefined4 *)(pcVar5 + 8) = 0;
          usb_dev_printf(PTR_s_d[0]_:0x%02x_data[1]_:0x%02x_dat_800386a8);
          return;
        }

        pcVar5 = s_ep0_out_intr:_data_is_ready,_can_8003865c;
        goto LAB_80038628;
      }

      if (iVar3 == 3)    //EP0_END_XFER
      {
        pcVar5[3] = '\0';   //usb_xfer_type = NONE_REQ;
      }
    }
  }
  else  //Stall handling
  {
    usb_dev_printf(s_ERR:_ep0_stall_8003840c);
    USBC_Dev_EpClearStall(1);         //USBC_EP_TYPE_EP0
  }

  *(undefined4 *)(pcVar5 + 8) = 0;  //usb_ep0_state = EP0_IDLE;
  return;
}


