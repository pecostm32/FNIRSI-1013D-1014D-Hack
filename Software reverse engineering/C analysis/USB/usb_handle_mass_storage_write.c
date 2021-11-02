
// WARNING (jumptable): Heritage AFTER dead removal. Example location: s0xffffffe8 : 0x80023b28
// WARNING: Removing unreachable block (ram,0x80002c14)
// WARNING: Removing unreachable block (ram,0x80002c1c)
// WARNING: Removing unreachable block (ram,0x80002c20)
// WARNING: Removing unreachable block (ram,0x80002c24)
// WARNING: Removing unreachable block (ram,0x80002c30)
// WARNING: Restarted to delay deadcode elimination for space: stack

void usb_handle_mass_storage_write(void *buffer,uint length)

{
  byte bVar1;
  char cVar2;
  ushort uVar3;
  int *piVar4;
  char *pcVar5;
  undefined *puVar6;
  char *pcVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  byte *pbVar11;
  int iVar12;
  int iVar13;
  undefined4 *puVar14;
  ushort *puVar15;
  char *pcVar16;
  undefined uVar17;
  uint uVar18;
  byte *pbVar19;
  undefined4 uVar20;
  uint uVar21;
  int iVar22;
  uint uVar23;
  int iVar24;
  int iVar25;
  bool bVar26;
  
  iVar22 = DAT_80020470;
  pcVar5 = DAT_8002046c;              //0x8019D03C Base of MSC data. Cleared on startup
  pbVar19 = DAT_80020468;
  bVar1 = *DAT_80020468;
  *DAT_80020468 = bVar1 | 0x10;
  cVar2 = *(char *)(iVar22 + 0xf);

  *(short *)(pcVar5 + 2) = (short)length;
  *(void **)(pcVar5 + 4) = buffer;

  piVar4 = DAT_80002fa8;
  iVar24 = DAT_80002fa4;

  if (*pcVar5 != '\0')                     //Check on a state indicator
  {
    if (*pcVar5 == '\x01') {
      if (cVar2 == '*') {
        *pbVar19 = bVar1 | 0x11;
        bVar1 = *(byte *)(iVar22 + 0xd);
        iVar22 = *(int *)(pcVar5 + 8);
        iVar24 = *(int *)(pcVar5 + 0xc);
LAB_80023e4c:
        pcVar16 = DAT_8002cdc0;
        iVar8 = DAT_8002ccb4;
        pcVar7 = DAT_8002ccb0;
        iVar25 = DAT_80023ed8;
        pcVar5 = DAT_80023ed4;
        if (*DAT_80023ed4 != '\0') {
          if (*DAT_80023ed4 != '\x01') {
            return;
          }
          if (*(int *)(DAT_8002ccec + 0x30) == 1) {
            if (*DAT_8002cdc0 == '\0') {
              *(int *)(DAT_8002cdc0 + 0x18) = iVar22;
              *(int *)(pcVar16 + 0x1c) = iVar24;
              *(undefined4 *)(pcVar16 + 0x20) = 0;
              *pcVar16 = '\x01';
            }
            else {
              if (*DAT_8002cdc0 != '\x01') goto LAB_8002cd64;
            }
            memcpy(DAT_8002cdc4 + *(int *)(pcVar16 + 0x20) * 0x200,*DAT_8002cdc8,0x200);
            puVar15 = DAT_8002cdd0;
            iVar24 = DAT_8002cdcc;
            *(int *)(pcVar16 + 0x20) = *(int *)(pcVar16 + 0x20) + 1;
            *(uint *)(iVar24 + 8) = *(int *)(iVar24 + 8) - (uint)*puVar15;
LAB_8002cd64:
            if ((*(uint *)(pcVar16 + 0x20) < *(uint *)(pcVar16 + 0x1c)) && (*DAT_8002cdd4 != '\x04')) {
              return;
            }
            uVar21 = sd_card_write(0,*(uint *)(pcVar16 + 0x18),*(uint *)(pcVar16 + 0x1c),DAT_8002cdc4);
            if ((uVar21 & 0xff) != 0) {
              pcVar16[1] = pcVar16[1] | 4;
            }
            *(undefined4 *)(pcVar16 + 0x20) = 0;
            FUN_80026858(0,1);
            *pcVar16 = '\0';
            return;
          }
          if (*(int *)(DAT_8002ccec + 0x30) != 0) {
            return;
          }
          if (*DAT_8002ccb0 == '\0') {
            iVar25 = *(int *)(DAT_8002ccb4 + (uint)bVar1 * 4);
            *(int *)(DAT_8002ccb0 + 0x24) = iVar25 * iVar22;
            *(int *)(pcVar7 + 0x28) = iVar25 * iVar24;
            *pcVar7 = '\x01';
          }
          else {
            if (*DAT_8002ccb0 != '\x01') goto LAB_8002cc78;
          }
          puVar15 = DAT_8002ccb8;
          uVar3 = *DAT_8002ccb8;
          iVar24 = *(int *)(pcVar7 + 0x24) + (uint)uVar3;
          *(int *)(pcVar7 + 0x24) = iVar24;
          *(uint *)(pcVar7 + 0x28) = *(int *)(pcVar7 + 0x28) - (uint)uVar3;
          iVar22 = *(int *)(iVar8 + (uint)bVar1 * 4);
          memcpy((void *)((iVar24 - iVar22) + DAT_8002ccbc),*DAT_8002ccc0,iVar22);
          *(uint *)(DAT_8002ccc4 + 8) = *(int *)(DAT_8002ccc4 + 8) - (uint)*puVar15;
LAB_8002cc78:
          if ((*(int *)(pcVar7 + 0x28) != 0) && (*DAT_8002ccc8 != '\x04')) {
            return;
          }
          *(undefined4 *)(pcVar7 + 8) = 0;
          FUN_80026858(0,1);
          *pcVar7 = '\0';
          return;
        }
        iVar24 = FUN_80023908(*(undefined *)(DAT_80023ed8 + 0xd),0x2a,iVar22);
        if (iVar24 == 0) {
          return;
        }
        if ((*(byte *)(iVar25 + 0xc) & 0x80) == 0) {
          *pcVar5 = '\x01';
          return;
        }
        FUN_80002c08(0);
        iVar24 = DAT_80023edc;
        *(undefined *)(DAT_80023edc + 2) = 5;
        *(undefined *)(iVar24 + 0xc) = 0x24;
        bVar26 = false;
        uVar17 = 1;
        goto code_r0x80026858;
      }
    }
    else {
      FUN_800266c0(1,2);
    }
    FUN_800266bc(2);
    FUN_800268b4(*(undefined *)(iVar22 + 0xd),5,0x24);
    bVar26 = false;
    uVar17 = 2;
    goto code_r0x80026858;
  }

  //State is zero at this point, meaning incoming data has to be a cbw
  //This is FUN_80002c08

  uVar21 = (uint)*(ushort *)(DAT_80002fa4 + 2);   //Get received data length

  if (uVar21 != 0)
  {
    if ((*(ushort *)(DAT_80002fa4 + 2) & 1) != 0)  //Check on length being odd??????
    {
      *(undefined *)DAT_80002fa8 = **(undefined **)(DAT_80002fa4 + 4);    //0x80746050  Some pointer to the buffer with the CBW
    }

    if ((uVar21 & 1) < uVar21)
    {
      iVar22 = *(int *)(iVar24 + 4);
      uVar23 = uVar21 & 1;

      do
      {
        *(undefined *)((int)piVar4 + uVar23) = *(undefined *)(iVar22 + uVar23);
        uVar18 = uVar23 + 2;
        *(undefined *)((int)piVar4 + uVar23 + 1) = *(undefined *)(iVar22 + uVar23 + 1);
        uVar23 = uVar18;
      } while (uVar18 < uVar21);
    }
  }

  iVar22 = DAT_80002fac;
  *(int *)(DAT_80002fac + 4) = piVar4[1];
  *(int *)(iVar22 + 8) = piVar4[2];

  if (uVar21 != 0x1f)
  {
    usb_dev_printf(s_Valid_CBW_1_80002fb0);
    FUN_800266c0(1,2);
    FUN_800266bc(2);
    *piVar4 = 0;
    FUN_800268b4(*(undefined *)((int)piVar4 + 0xd),5,0x1a);
    bVar26 = false;
    uVar17 = 1;
    goto code_r0x80026858;
  }

  //Compare with read10 or write10 command
  if (*(char *)((int)piVar4 + 0xf) == '(' || *(char *)((int)piVar4 + 0xf) == '*')
  {
    *(uint *)(iVar24 + 8) = (uint)*(byte *)(piVar4 + 5) | (uint)*(byte *)((int)piVar4 + 0x11) << 0x18 | (uint)*(byte *)((int)piVar4 + 0x12) << 0x10 | (uint)*(byte *)((int)piVar4 + 0x13) << 8;
    *(uint *)(iVar24 + 0xc) = (uint)CONCAT11(*(undefined *)((int)piVar4 + 0x16),*(undefined *)((int)piVar4 + 0x17));
  }

  if (*piVar4 != DAT_80002fc0)
  {
    usb_dev_printf(s_Valid_CBW_4_80003050);
    FUN_800266c0(1,2);
    FUN_800266bc(2);
    FUN_800268b4(*(undefined *)((int)piVar4 + 0xd),5,0x20);
    bVar26 = false;
    uVar17 = 1;
    goto code_r0x80026858;
  }

  if (((*DAT_80002fc4 < (uint)*(byte *)((int)piVar4 + 0xd)) || (*(byte *)((int)piVar4 + 0xe) == 0)) || (0x10 < *(byte *)((int)piVar4 + 0xe)))
  {
    usb_dev_printf(s_Valid_CBW_2_80002fc8);
    FUN_800266c0(1,2);
    FUN_800266bc(2);
    FUN_800268b4(*(undefined *)((int)piVar4 + 0xd),5,0x24);
    bVar26 = false;
    uVar17 = 1;
    goto code_r0x80026858;
  }
  usb_dev_printf(s_CTRL:_%02X_80002fd8);
  iVar13 = DAT_80023de8;
  iVar12 = DAT_80023d6c;
  pbVar11 = DAT_80023d68;
  iVar10 = DAT_80023d60;
  iVar9 = DAT_80023ccc;
  pbVar19 = DAT_80023cc8;
  iVar8 = DAT_80023cc0;
  iVar25 = DAT_80023be0;
  pcVar5 = DAT_80023bd0;
  iVar22 = DAT_800239fc;
  bVar1 = *(byte *)((int)piVar4 + 0xf);
  if (bVar1 == 0x25) {
    uVar21 = (uint)*(byte *)((int)piVar4 + 0xd);
    if (1 < uVar21) {
      *(undefined *)(DAT_80023cc0 + 2) = 2;
      *(undefined *)(iVar8 + 0xc) = 0x3a;
      FUN_80026858(1);
      return;
    }
    iVar24 = *(int *)(DAT_80023cc4 + uVar21 * 4) + -1;
    *DAT_80023cc8 = (byte)((uint)iVar24 >> 0x18);
    pbVar19[1] = (byte)((uint)iVar24 >> 0x10);
    pbVar19[2] = (byte)((uint)iVar24 >> 8);
    pbVar19[3] = (byte)iVar24;
    uVar20 = *(undefined4 *)(iVar9 + uVar21 * 4);
    pbVar19[4] = (byte)((uint)uVar20 >> 0x18);
    pbVar19[5] = (byte)((uint)uVar20 >> 0x10);
    pbVar19[6] = (byte)((uint)uVar20 >> 8);
    pbVar19[7] = (byte)uVar20;
    uVar21 = 8;
    pbVar19 = DAT_80023cc8;
    goto FUN_80029198;
  }

  if (bVar1 < 0x26)     //Commands less then 0x26
  {
    if (bVar1 != 0x15)
    {
      if (0x15 < bVar1)  //Commands starting from 0x16
      {
        //This is handling of the built in scsi commands
        switch(bVar1)
        {

        case 0x1a:                 //SCSI_CMD_MODE_SENSE_6
          uVar21 = 4;
          pbVar19 = DAT_80023ae0;  //Points to 0x8019D428 holding 0x03, 0x00, 0x00, 0x00
          break;

        case 0x1b:                   //SCSI_CMD_START_STOP_UNIT
        case 0x1e:                   //SCSI_CMD_PREVENT_ALLOW_MEDIUM_REMOVAL
          bVar26 = true;
          uVar17 = 0;
          goto code_r0x80026858;

        default:
          goto switchD_80002e34_caseD_1c;

        case 0x1d:                 //Send diagnostics
          goto LAB_80023a48;

        case 0x23:             //SCSI_CMD_READ_FORMAT_CAPACITY
          uVar21 = (uint)*(byte *)((int)piVar4 + 0xd);

          if (1 < uVar21) {
            *(undefined *)(DAT_80023d60 + 2) = 2;
            *(undefined *)(iVar10 + 0xc) = 0x3a;
            FUN_80026858(1);
            return;
          }
          uVar20 = *(undefined4 *)(DAT_80023d64 + uVar21 * 4);
          DAT_80023d68[4] = (byte)((uint)uVar20 >> 0x18);
          pbVar11[5] = (byte)((uint)uVar20 >> 0x10);
          pbVar11[6] = (byte)((uint)uVar20 >> 8);
          pbVar11[7] = (byte)uVar20;
          uVar20 = *(undefined4 *)(iVar12 + uVar21 * 4);
          pbVar11[9] = (byte)((uint)uVar20 >> 0x10);
          pbVar11[10] = (byte)((uint)uVar20 >> 8);
          pbVar11[0xb] = (byte)uVar20;
          uVar21 = 0xc;
          pbVar19 = DAT_80023d68;
        }
FUN_80029198:
        usb_device_write_data(1,pbVar19,uVar21);
        iVar24 = DAT_800291d8;
        *DAT_800291dc = 3;
        *(uint *)(iVar24 + 8) = *(int *)(iVar24 + 8) - uVar21;
        *(undefined *)(iVar24 + 0xc) = 0;
        return;
      }
      if (bVar1 != 8) {
        if (bVar1 < 9) {
          if (bVar1 == 0) {
            if (1 < *(byte *)((int)piVar4 + 0xd)) {
              *(undefined *)(DAT_80023de8 + 2) = 2;
              *(undefined *)(iVar13 + 0xc) = 0x3a;
              FUN_80026858(1);
              return;
            }
            bVar26 = true;
            uVar17 = 0;
            goto code_r0x80026858;
          }
          if (bVar1 == 3) {
            uVar21 = (uint)*(byte *)(DAT_80023d88 + 0x13);
            pbVar19 = DAT_80023d8c;
            if (0x12 < uVar21) {
              uVar21 = 0x12;
            }
            goto FUN_80029198;
          }
          if (bVar1 == 4) {
            if (1 < *(byte *)((int)piVar4 + 0xd)) {
              *(undefined *)(DAT_800239fc + 2) = 2;
              *(undefined *)(iVar22 + 0xc) = 0x3a;
              FUN_80026858(1);
              return;
            }
            return;
          }
        }
        else {
          if (bVar1 == 10) goto LAB_80023a48;
          if (bVar1 == 0x12) {
            if ((*(byte *)(DAT_80023a38 + 0x10) & 1) == 0) {
              uVar21 = (uint)*(byte *)(DAT_80023a38 + 0x13);
              pbVar19 = DAT_80023a40;
              if (*(char *)((int)piVar4 + 0xd) != '\0') {
                pbVar19 = DAT_80023a44;
              }
              if (0x24 < uVar21) {
                uVar21 = 0x24;
              }
            }
            else {
              uVar21 = 5;
              pbVar19 = DAT_80023a3c;
            }
            goto FUN_80029198;
          }
        }
switchD_80002e34_caseD_1c:
        usb_dev_printf(s_Valid_CBW_3_80002fe8);
        FUN_800266c0(1,2);
        FUN_800266bc(2);
        FUN_800268b4(*(undefined *)((int)piVar4 + 0xd),5,0x20);
        bVar26 = false;
        uVar17 = 1;
        goto code_r0x80026858;
      }
    }
  }
  else {
    if (bVar1 != 0x8a) {
      if (bVar1 < 0x8b) {
        if (bVar1 != 0x55) {
          if (bVar1 < 0x56) {
            if (bVar1 == 0x28) {
              bVar1 = *(byte *)((int)piVar4 + 0xd);
              uVar21 = *(uint *)(iVar24 + 8);
              uVar23 = *(uint *)(iVar24 + 0xc);
              if (*DAT_80023bd0 == '\0') {
                iVar24 = FUN_80023908(*(undefined *)(DAT_80023be0 + 0xd),0x28,uVar21,uVar23);
                if (iVar24 == 0) {
                  return;
                }
                if ((*(byte *)(iVar25 + 0xc) & 0x80) == 0) {
                  usb_dev_printf(s_ERR:read10_FAILED!_80023c08);
                  FUN_80002c08(2);
                  iVar24 = DAT_80023c20;
                  *(undefined *)(DAT_80023c20 + 2) = 5;
                  *(undefined *)(iVar24 + 0xc) = 0x24;
                  bVar26 = true;
                  uVar17 = 1;
                  goto code_r0x80026858;
                }
                usb_dev_printf(s_read10!_80023bd4);
                *pcVar5 = '\x02';
              }
              else {
                if (*DAT_80023bd0 != '\x02') {
                  return;
                }
                usb_dev_printf(s_read10!_80023bd4);
              }
              pcVar7 = DAT_80023554;
              iVar24 = DAT_80023418;
              pcVar5 = DAT_80023414;
              if (*(int *)(DAT_8002344c + 0x30) == 1) {
                if (*DAT_80023554 == '\0') {
                  *(uint *)(DAT_80023554 + 0xc) = uVar23;
                  *(undefined4 *)(pcVar7 + 4) = 0;
                  *pcVar7 = '\x01';
                }
                else {
                  if (*DAT_80023554 != '\x01') goto LAB_800234dc;
                }
                if (*(int *)(pcVar7 + 4) == 0) {
                  uVar21 = sd_card_read(0,uVar21,uVar23,DAT_80023558);
                  if ((uVar21 & 0xff) != 0) {
                    pcVar7[1] = pcVar7[1] | 8;
                  }
                  FUN_8002a004(2,DAT_80023558,0x200);
                  iVar24 = 0x200;
                  *(int *)(pcVar7 + 0xc) = *(int *)(pcVar7 + 0xc) + -1;
                  *(int *)(pcVar7 + 4) = *(int *)(pcVar7 + 4) + 1;
                }
                else {
                  FUN_8002a004(2,DAT_80023558 + *(int *)(pcVar7 + 0x2c),0x200);
                  *(int *)(pcVar7 + 0xc) = *(int *)(pcVar7 + 0xc) + -1;
                  *(int *)(pcVar7 + 4) = *(int *)(pcVar7 + 4) + 1;
                  iVar24 = *(int *)(pcVar7 + 0x2c) + 0x200;
                }
                *(int *)(pcVar7 + 0x2c) = iVar24;
                *(int *)(DAT_8002355c + 8) = *(int *)(DAT_8002355c + 8) + -0x200;
LAB_800234dc:
                if (*(int *)(pcVar7 + 0xc) != 0) {
                  return;
                }
                *(undefined4 *)(pcVar7 + 4) = 0;
                *(undefined4 *)(pcVar7 + 0x2c) = 0;
                *DAT_80023560 = 3;
                *pcVar7 = '\0';
                return;
              }
              if (*(int *)(DAT_8002344c + 0x30) != 0) {
                return;
              }
              if (*DAT_80023414 == '\0') {
                iVar22 = *(int *)(DAT_80023418 + (uint)bVar1 * 4);
                *(uint *)(DAT_80023414 + 0x10) = iVar22 * uVar21;
                *(uint *)(pcVar5 + 0x14) = iVar22 * uVar23;
                *pcVar5 = '\x01';
              }
              else {
                if (*DAT_80023414 != '\x01') goto LAB_800233e4;
              }
              memcpy((void *)(DAT_8002341c + -0x800),(void *)(*(int *)(pcVar5 + 0x10) + DAT_8002341c),*(int *)(iVar24 + (uint)bVar1 * 4));
              FUN_8002a004(2,DAT_80023420,0x200);
              iVar24 = DAT_80023424;
              *(int *)(pcVar5 + 0x10) = *(int *)(pcVar5 + 0x10) + 0x200;
              *(int *)(pcVar5 + 0x14) = *(int *)(pcVar5 + 0x14) + -0x200;
              *(int *)(iVar24 + 8) = *(int *)(iVar24 + 8) + -0x200;
LAB_800233e4:
              if (*(int *)(pcVar5 + 0x14) != 0) {
                return;
              }
              *(undefined4 *)(pcVar5 + 4) = 0;
              *(undefined4 *)(pcVar5 + 0x2c) = 0;
              puVar6 = DAT_80023428;
              *(undefined4 *)(pcVar5 + 0x10) = 0;
              *puVar6 = 3;
              *pcVar5 = '\0';
              return;
            }
            if (bVar1 == 0x2a) {
              bVar1 = *(byte *)((int)piVar4 + 0xd);
              iVar22 = *(int *)(iVar24 + 8);
              iVar24 = *(int *)(iVar24 + 0xc);
              goto LAB_80023e4c;
            }
            if (bVar1 == 0x2f) {
              bVar26 = *(int *)(DAT_80023e44 + 8) == 0;
              if (bVar26) {
                bVar26 = (*(byte *)(DAT_80023e44 + 0x10) & 4) == 0;
              }
              if (bVar26) {
                bVar26 = true;
                uVar17 = 0;
              }
              else {
                FUN_80002c08(2);
                iVar24 = DAT_80023e48;
                *(undefined *)(DAT_80023e48 + 2) = 5;
                *(undefined *)(iVar24 + 0xc) = 0x24;
                bVar26 = false;
                uVar17 = 1;
              }
              goto code_r0x80026858;
            }
          }
          else {
            if (bVar1 == 0x5a) {
              uVar21 = 8;
              pbVar19 = DAT_80023ad0;
              goto FUN_80029198;
            }
            if (bVar1 == 0x88) goto LAB_80023a48;
          }
          goto switchD_80002e34_caseD_1c;
        }
      }
      else {
        if (bVar1 != 0xa8) {
          if (bVar1 < 0xa9) {
            if (bVar1 != 0x8f && bVar1 != 0x9e) goto switchD_80002e34_caseD_1c;
          }
          else {
            if (bVar1 != 0xaa && bVar1 != 0xaf) goto switchD_80002e34_caseD_1c;
          }
        }
      }
    }
  }
LAB_80023a48:
  if (*(int *)(DAT_80023aa8 + 8) == 0) {
    FUN_80002c08(0);
  }
  else {
    if ((*(byte *)(DAT_80023aa8 + 0xc) & 0x80) == 0) {
      uVar20 = 2;
    }
    else {
      uVar20 = 0;
    }
    FUN_80002c08(uVar20);
  }
  usb_dev_printf(s_SCSI_Invalid_Cmd_80023aac);
  iVar24 = DAT_80023ac0;
  *(undefined *)(DAT_80023ac0 + 2) = 5;
  *(undefined *)(iVar24 + 0xc) = 0x20;
  bVar26 = false;
  uVar17 = 1;


code_r0x80026858:
  puVar14 = DAT_800268ac;
  *DAT_800268ac = DAT_800268a8;
  *(undefined *)(puVar14 + 3) = uVar17;
  FUN_8002a004(2,puVar14,0xd);
  puVar6 = DAT_800268b0;
  *DAT_800268b0 = 5;

  if (bVar26)
  {
    *puVar6 = 4;
    return;
  }

  return;
}


