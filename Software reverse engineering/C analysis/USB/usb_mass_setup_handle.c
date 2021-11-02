
// WARNING: Removing unreachable block (ram,0x80029924)
// WARNING: Removing unreachable block (ram,0x8002992c)
// WARNING: Removing unreachable block (ram,0x80029944)
// WARNING: Removing unreachable block (ram,0x80029948)
// WARNING: Removing unreachable block (ram,0x8002994c)
// WARNING: Removing unreachable block (ram,0x80029950)
// WARNING: Removing unreachable block (ram,0x80029958)
// WARNING: Removing unreachable block (ram,0x80029960)
// WARNING: Removing unreachable block (ram,0x80029934)
// WARNING: Removing unreachable block (ram,0x8003813c)
// WARNING: Removing unreachable block (ram,0x80038164)
// WARNING: Could not reconcile some variable overlaps
// WARNING: Restarted to delay deadcode elimination for space: stack

char * usb_mass_setup_handle(byte *buffer,uint len)

{
  byte bVar1;
  char cVar2;
  ushort uVar3;
  undefined2 uVar4;
  int iVar5;
  undefined4 *puVar6;
  byte *pbVar7;
  char *pcVar8;
  uint uVar9;
  void *pvVar10;
  undefined4 uVar11;
  byte *pbVar12;
  ushort *puVar13;
  ushort *puVar14;
  ushort uVar15;
  undefined4 uStack32;
  undefined uStack28;
  undefined uStack27;
  undefined uStack26;
  undefined4 local_18 [2];
  undefined4 local_10;
  
  local_10 = DAT_80039018;
  if (len != 8)
  {
    return s_not_setup_data._8003901c;
  }

  memcpy(DAT_80039030,buffer,8);

  pbVar12 = DAT_80039030;

  usb_dev_printf(s_bRequestType:0x%02x_80039034);
  usb_dev_printf(s_bRequest:0x%02x_8003904c);
  usb_dev_printf(s_wValue:0x%04x_80039060);
  usb_dev_printf(s_wIndex:0x%04x_80039070);
  usb_dev_printf(s_wLength:0x%04x_80039080);


//typedef struct
//{
//  uint8  bRequestType;
//  uint8  bRequest;
//  uint16 wValue;
//  uint16 wIndex;
//  uint16 wLength;
//} __attribute__ ((packed)) USB_DeviceRequest;


  pbVar7 = DAT_80039030;    //0x8019D0A7   usb_setup_request
  pcVar8 = DAT_800369b8;    //0x8019D1DC

  if ((*pbVar12 & 0x60) != 0)    //USB_TYPE_MASK
  {
    pbVar12 = (byte *)(*pbVar12 & 0x60);

    if (pbVar12 != (byte *)0x20)  //USB_TYPE_CLASS
    {
      return (char *)pbVar12;   //Return if USB_TYPE_VENDOR
    }

    //Handle class setup request
    local_18[0] = 0;

    bVar1 = DAT_80039030[1];   //usb_setup_request.bRequest

    //9, 32, 33, 34 are for HID so not needed
    if (bVar1 == 9)   //Class 9????  HID_REQ_SET_REPORT
    {
      pcVar8 = s_HID_REQ_SET_REPORT,_host_set_dev_80032084;
    }
    else
    {
      if (bVar1 != 10)
      {
        if (bVar1 == 0x20)  //Class 32
        {
          usb_dev_printf(s_set_line_coding_80032130);
          iVar5 = DAT_80032144;
          *(undefined4 *)(DAT_80032144 + 4) = 1;
          uVar9 = USBC_ReadLenFromFifo(1);
          pcVar8 = s_set_line_coding:readlen:%d_80032148;
          usb_dev_printf(s_set_line_coding:readlen:%d_80032148);

          if (uVar9 == 7)
          {
            FUN_80037eec(0,&uStack32,7);
            *(undefined4 *)(iVar5 + 4) = 0;
            puVar6 = DAT_80032164;
            *DAT_80032164 = uStack32;
            *(undefined *)(puVar6 + 1) = uStack28;
            *(undefined *)((int)puVar6 + 5) = uStack27;
            *(undefined *)((int)puVar6 + 6) = uStack26;
            FUN_80037f10(1);
            pbVar12 = (byte *)FUN_80037f44(0);
            *(undefined4 *)(iVar5 + 4) = 0;
            return (char *)pbVar12;
          }

          return pcVar8;
        }

        if (bVar1 == 0x21)
        {
          usb_device_write_data_ep_pack(0,DAT_80032164,7,local_10);
          pcVar8 = s_get_line_coding_80032168;
          usb_dev_printf(s_get_line_coding_80032168);
          return pcVar8;
        }

        if (bVar1 == 0x22)
        {
          usb_dev_printf(s_set_control_line_state_8003217c);
          USBC_Dev_Ctrl_ClearSetupEnd();
          pbVar12 = (byte *)FUN_80037f44(0);
          return (char *)pbVar12;
        }
        //The above ones are for HID


        if (bVar1 == 0xfe)    //This one is needed for mass storage device functionality. Returns 0?? Meaning sigle drive???
        {
          FUN_8001bf10();     //Just return 0x8019D238, which holds the number of lun's????

          usb_dev_printf(s_MASS_GET_MAX_LUN:_%d_800321c8);
          pbVar12 = (byte *)usb_device_write_data_ep_pack(0,local_18,*(undefined2 *)(pbVar7 + 6));   //0x8019D0A7+6 ==> wLength
          return (char *)pbVar12;
        }

        pcVar8 = s_Warnning!!!_received_unsupport_c_800320f4;
        usb_dev_printf(s_Warnning!!!_received_unsupport_c_800320f4);
        return pcVar8;
      }

      //Class 10
      pcVar8 = s_HID_REQ_SET_IDLE,_host_set_devic_800320bc;
    }

    usb_dev_printf(pcVar8);
    return pcVar8;
  }

  //standard_setup_request()
  puVar14 = (ushort *)(uint)DAT_80039030[1];

  if (puVar14 != (ushort *)0x6)  //brequest != 6 (USB_REQ_GET_DESCRIPTOR)
  {
    if (puVar14 == (ushort *)0x9)   //USB_REQ_SET_CONFIGURATION
    {
      usb_dev_printf(s_set_configuration_80036a9c);

      if (*pcVar8 == '\x04')
      {
        usb_config_ep_out(1,0x200,4);    //USBC_TS_TYPE_BULK
        usb_config_ep_in(1,0x200,4);
      }
      else
      {
        usb_config_ep_out(1,0x200,3);
        usb_config_ep_in(1,0x200,3);
      }

      usb_device_read_data_status_ep0(1);  //USBC_Dev_ReadDataStatus(USBC_EP_TYPE_EP0, 1);

      USBC_Dev_Ctrl_ClearSetupEnd();

      usb_device_send_nullpack_ep0();
code_r0x80037f44:
      *(undefined4 *)(DAT_80037f50 + 8) = 0;
      return (char *)NULL;
    }


    if (puVar14 == (ushort *)&SupervisorCall)  //USB_REQ_GET_CONFIGURATION
    {
      usb_dev_printf(s_get_configuration_80036b84);
      usb_dev_printf(s_Error!!_unsupprot_USB_REQ_GET_CO_80036b98);
    }
    else
    {
      if (puVar14 == (ushort *)0xb)    //USB_REQ_SET_INTERFACE
      {
        usb_dev_printf(s_set_interface_80036bcc);
        usb_dev_printf(s_Error!!_unsupprot_USB_REQ_SET_IN_80036bdc);
      }
      else
      {
        if (puVar14 == (ushort *)0xa)  //USB_REQ_GET_INTERFACE
        {
          usb_dev_printf(s_Error!!_unsupprot_USB_REQ_GET_IN_80036c0c);
        }
        else
        {
          if (puVar14 == (ushort *)0x5)   //USB_REQ_SET_ADDRESS
          {
            usb_dev_printf(s_set_addr_80036c3c);
            bVar1 = pbVar7[2];
            sd_card_delay(1);
            usb_device_set_address(bVar1 & 0x7f);
            usb_device_read_data_status_ep0(1);
            usb_dev_printf(s_set_dev_address:_%x_80036c48);
            goto code_r0x80037f44;
          }

          if (puVar14 == (ushort *)0x7)   //USB_REQ_SET_DESCRIPTOR
          {
            usb_dev_printf(s_set_Descriptor_80036c60);
            usb_dev_printf(s_Error!!_unsupprot_USB_REQ_SET_DE_80036c70);
          }
          else
          {
            if (puVar14 == (ushort *)&PrefetchAbort)  //USB_REQ_SYNCH_FRAME
            {
              usb_dev_printf(s_sync_frame_80036cf0);
              usb_dev_printf(s_Error!!_unsupprot_USB_REQ_SYNCH__80036cfc);
            }
            else
            {
              if (puVar14 == (ushort *)0x1)  //USB_REQ_CLEAR_FEATURE
              {
                uVar4 = *(undefined2 *)(DAT_80039030 + 4);  //epaddr   setup packet data wIndex
                usb_dev_printf(s_clear_feature_80036d2c);
                usb_device_clear_ep_halt(uVar4);
              }
              else
              {
                usb_dev_printf(s_other_req_800369bc);
                usb_dev_printf(s_Error!!_received_controller_comm_800369cc);
              }
            }
          }
        }
      }
    }
USBC_Dev_ReadDataStatus:
    *(undefined2 *)(DAT_80029974 + 0x82) = 0x48;
    return (char *)NULL;
  }

  //USB_REQ_GET_DESCRIPTOR
  usb_dev_printf(s_getDescriptor_800369f8);

  uVar3 = *(ushort *)(pbVar7 + 2);  //Get high byte of wValue

  uVar15 = uVar3 >> 8;

  if (uVar15 == 1)  //DEVICE_DESCRIPTOR
  {
    cVar2 = *pcVar8;      //device_type

    if (cVar2 == '\x03')
    {
      puVar14 = DAT_80036a34;
    }

    uVar9 = (uint)*(ushort *)(pbVar7 + 6);   //wLength

    puVar13 = puVar14;

    if ((((cVar2 != '\x03') && (puVar13 = DAT_80036a38, cVar2 != '\x01')) && (puVar13 = DAT_80036a3c, cVar2 != '\x02')) && (puVar13 = puVar14, cVar2 == '\x04'))
    {
      puVar13 = DAT_80036a40;
    }

    usb_dev_printf(s_usb_get_device_descriptor_80036a44);

    //Make sure length is correct
    if (0x11 < uVar9)
    {
      uVar9 = 0x12;
    }

    goto code_r0x800380dc;
  }


  if (uVar15 == 2)  //CONFIGURATION_DESCRIPTOR
  {
    cVar2 = *pcVar8;    //device_type

    if (cVar2 == '\x01')
    {
      usb_dev_printf(s_usb_hid_get_cfg_descriptor_8003894c);
      puVar13 = DAT_80038968;
      if (*(short *)(pbVar7 + 6) == 8) {
        uVar9 = 8;
      }
      else {
        if (*(short *)(pbVar7 + 6) == 9) {
          uVar9 = 9;
        }
        else {
          uVar9 = 0x29;
        }
      }
    }
    else
    {
      if (cVar2 == '\x02')
      {
        usb_dev_printf(s_usb_hid_get_cfg_descriptor_80037c24);
        puVar13 = DAT_80037c40;
        if (*(short *)(pbVar7 + 6) == 8) {
          uVar9 = 8;
        }
        else {
          if (*(short *)(pbVar7 + 6) == 9) {
            uVar9 = 9;
          }
          else {
            uVar9 = 0x4b;
          }
        }
      }
      else
      {
        if (cVar2 == '\x03')
        {
          usb_dev_printf(s_usb_uvc_get_cfg_descriptor_800390c4);
          uVar9 = (uint)*(ushort *)(pbVar7 + 6);
          puVar13 = DAT_800390e0;
        }
        else
        {
          if (cVar2 != '\x04')
          {
            return (char *)pbVar7;
          }

          usb_dev_printf(s_usb_mass_get_cfg_descriptor_80038ecc);
          puVar13 = DAT_80038eec;

          if (*(short *)(pbVar7 + 6) == 8)
          {
            uVar9 = 8;
          }
          else {
            if (*(short *)(pbVar7 + 6) == 9) {
              uVar9 = 9;
            }
            else {
              uVar9 = 0x20;
            }
          }
        }
      }
    }
    goto code_r0x800380dc;
  }

  if (uVar15 != 3)
  {
    if (uVar15 != 0x22)
    {
      usb_dev_printf(s_usb_get_descriptor_:_0x%04x_not_s_80036a08);
      goto USBC_Dev_ReadDataStatus;
    }

    uVar9 = 0x23;
    puVar13 = (ushort *)PTR_DAT_800381b4;  //Data found below????
    goto code_r0x800380dc;
  }



  //Get descriptor strings
  uVar15 = uVar3 & 0xff;   //low byte of wValue

  uVar9 = (uint)*(ushort *)(pbVar7 + 6);  //Length

  usb_dev_printf(s_udp_get_dev_descriptor_string:%d_80036a60);

  puVar13 = DAT_80036a88;

  if (uVar15 == 4)
  {
    puVar13 = DAT_80036a90;  //String 4   0x8019D162   interface

    if (0x1d < uVar9)
    {
      uVar9 = 0x1e;
    }

    goto code_r0x800380dc;
  }

  if (uVar15 < 5)
  {
    if ((uVar3 & 0xff) == 0)   //String 0  0x8019D098    Language
    {
      puVar13 = DAT_80036a84;

      if (4 < uVar9)
      {
        uVar9 = 4;
      }

      goto code_r0x800380dc;
    }

    if (uVar15 != 1)
    {
      if (uVar15 == 2)        //String 2 0x8019D0FE    Product
      {
        if (0x26 < uVar9)
        {
          uVar9 = 0x26;
        }

        *DAT_80036a88 = (ushort)uVar9 | 0x300;

        goto code_r0x800380dc;
      }

      if (uVar15 != 3)
        goto LAB_80036860;
    }

    puVar13 = DAT_80036a8c;   //String 1 and 3 0x8019D124   Vendor

    if (0x3d < uVar9)
    {
      uVar9 = 0x3e;
    }
  }
  else
  {
    if (uVar15 == 5)          //String 5 0x8019D180
    {
      puVar13 = DAT_80036a94;

      if (0x41 < uVar9)
      {
        uVar9 = 0x42;
      }
      goto code_r0x800380dc;
    }

    if (uVar15 == 6)           //String 6 0x8019D1C2
    {
      puVar13 = DAT_80036a98;

      if (0x19 < uVar9)
      {
        uVar9 = 0x1a;
      }

      goto code_r0x800380dc;
    }

    if (uVar15 == 0xee)       //String 0xEE   0x8019D124 (Same as 1 and 3)
    {
      if (0x3d < uVar9)
      {
        uVar9 = 0x3e;
      }

      *DAT_80036a8c = (ushort)uVar9 | 0x300;
      puVar13 = DAT_80036a8c;
      goto code_r0x800380dc;
    }

LAB_80036860:           //Default no string
    uVar9 = 0;
    puVar13 = NULL;
  }


//Write the data to the send buffer and back to the host

code_r0x800380dc:
  memcpy(DAT_80038188,puVar13,uVar9);
  iVar5 = DAT_8003818c;
  *(uint *)(DAT_8003818c + 0xc) = uVar9;
  *(ushort **)(iVar5 + 0x1c) = puVar13;
  usb_dev_printf(s_CTRL_IN_LEN_:_%d_80038190);

  if ((int)*(uint *)(iVar5 + 0x20) < (int)uVar9) {
    pvVar10 = USBC_SelectFIFO(0);
    USBC_WritePacket(pvVar10,*(uint *)(iVar5 + 0x20),puVar13);
    USBC_Dev_WriteDataStatus(1,0);
    uVar11 = 0x40;
  }
  else {
    pvVar10 = USBC_SelectFIFO(0);
    USBC_WritePacket(pvVar10,uVar9,puVar13);
    USBC_Dev_WriteDataStatus(1,1);
    uVar11 = 0;
  }

  *(undefined4 *)(iVar5 + 0x10) = uVar11;

  return (char *)NULL;
}

/*


                             DAT_80188fcc                                    XREF[5]:     usb_device_write_data_ep_pack:80
                                                                                          usb_device_write_data_ep_pack:80
                                                                                          usb_device_write_data_ep_pack:80
                                                                                          usb_mass_setup_handle:800381a4(*
                                                                                          800381b4(*)  
        80188fcc 06              ??         06h
        80188fcd 06              ??         06h
        80188fce ff              ??         FFh
        80188fcf 09              ??         09h
        80188fd0 01              ??         01h
        80188fd1 a1              ??         A1h
        80188fd2 01              ??         01h
        80188fd3 15              ??         15h
        80188fd4 00              ??         00h
        80188fd5 26              ??         26h    &
        80188fd6 ff              ??         FFh
        80188fd7 00              ??         00h
        80188fd8 75              ??         75h    u
        80188fd9 08              ??         08h
        80188fda 96              ??         96h
        80188fdb 00              ??         00h
        80188fdc 02              ??         02h
        80188fdd 09              ??         09h
        80188fde 01              ??         01h
        80188fdf 81              ??         81h
        80188fe0 02              ??         02h
        80188fe1 96              ??         96h
        80188fe2 00              ??         00h
        80188fe3 02              ??         02h
        80188fe4 09              ??         09h
        80188fe5 01              ??         01h
        80188fe6 91              ??         91h
        80188fe7 02              ??         02h
        80188fe8 95              ??         95h
        80188fe9 08              ??         08h
        80188fea 09              ??         09h
        80188feb 01              ??         01h
        80188fec b1              ??         B1h
        80188fed 02              ??         02h
        80188fee c0              ??         C0h
        80188fef 00              ??         00h
*/
