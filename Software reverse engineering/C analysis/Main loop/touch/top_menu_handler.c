
/* WARNING (jumptable): Heritage AFTER dead removal. Example location: s0xffffffd8 : 0x8001fce8 */
/* WARNING: Heritage AFTER dead removal. Example location: s0xffffffd8 : 0x8001f7ec */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

void top_menu_handler(void)

{
  char cVar1;
  byte bVar2;
  ushort uVar3;
  undefined *puVar4;
  int iVar5;
  char *pcVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  code *UNRECOVERED_JUMPTABLE_00;
  bool bVar17;
  bool bVar18;
  
  set_frame_to_global_pointer();
  tp_i2c_read_status();
  uVar12 = DAT_8001e9c0;
  pcVar6 = DAT_8001e9bc;
  iVar13 = DAT_8001e9b8;
  puVar4 = PTR_DAT_8001e9b4;
  uVar10 = (uint)*(ushort *)(PTR_DAT_8001e9b4 + 2);
  if ((uVar10 - 1 < 0x4f) &&
     (*(ushort *)(PTR_DAT_8001e9b4 + 4) != 0 && *(ushort *)(PTR_DAT_8001e9b4 + 4) < 0x2a)) {
    cVar1 = *PTR_DAT_8001e9b4;
    if (DAT_8001e9bc[0x43] == '\0') {
      while (cVar1 != '\0') {
        display_menu_button(1);
        tp_i2c_read_status();
        cVar1 = *puVar4;
      }
      display_menu_button(0);
      setup_main_menu();
      tp_i2c_read_status();
      cVar1 = *puVar4;
      while (cVar1 != '\0') {
        tp_i2c_read_status();
        cVar1 = *puVar4;
      }
    }
    else {
      while (cVar1 != '\0') {
        display_return_arrow_symbol(1);
        tp_i2c_read_status();
        cVar1 = *puVar4;
      }
      display_return_arrow_symbol(0);
      pcVar6[0x43] = '\0';
      tp_i2c_read_status();
      cVar1 = *puVar4;
      while (cVar1 != '\0') {
        tp_i2c_read_status();
        cVar1 = *puVar4;
      }
    }
  }
  else {
    if ((uVar10 - 0xa2 < 0x67) &&
       (*(ushort *)(PTR_DAT_8001e9b4 + 4) != 0 && *(ushort *)(PTR_DAT_8001e9b4 + 4) < 0x3d)) {
      cVar1 = *PTR_DAT_8001e9b4;
      while (cVar1 != '\0') {
        display_ch1_settings(1);
        tp_i2c_read_status();
        cVar1 = *puVar4;
      }
      display_ch1_settings(0);
      setup_channel1_menu();
LAB_8001dc04:
      do {
        tp_i2c_read_status();
        uVar10 = (uint)*(ushort *)(puVar4 + 2);
        if (uVar10 - 0xa2 < 0xb6) {
          uVar11 = (uint)*(ushort *)(puVar4 + 4);
          bVar18 = 0x2d < uVar11;
          bVar17 = uVar11 == 0x2e;
          if (0x2e < uVar11) {
            bVar18 = uVar11 <= uVar12;
            bVar17 = uVar12 == uVar11;
          }
          if (bVar18 && !bVar17) {
            uVar14 = uVar10 - 0xdc;
            if (((uVar14 < 0x3b) && (0x30 < uVar11)) && (uVar11 < 0x6a)) {
              if (*puVar4 != '\0') {
                *pcVar6 = '\x01';
                display_channel1_menu();
                set_fpga_channel_trigger_channel();
                tp_i2c_read_status();
                cVar1 = *puVar4;
                while (cVar1 != '\0') {
                  tp_i2c_read_status();
                  cVar1 = *puVar4;
                }
              }
            }
            else {
              uVar16 = uVar10 - 0x11a;
              if (((uVar16 < 0x3a) && (0x31 < uVar11)) && (uVar11 < 0x6b)) {
                if (*puVar4 != '\0') {
                  *pcVar6 = '\0';
                  display_channel1_menu();
                  set_fpga_channel_trigger_channel();
                  pcVar6[3] = '\0';
                  set_fpga_channel1_voltperdiv();
                  tp_i2c_read_status();
                  cVar1 = *puVar4;
                  while (cVar1 != '\0') {
                    tp_i2c_read_status();
                    cVar1 = *puVar4;
                  }
                }
              }
              else {
                if (((uVar14 < 0x3b) && (0x6f < uVar11)) && (uVar11 < 0xa9)) {
                  if (*puVar4 != '\0') {
                    pcVar6[4] = '\x01';
                    display_channel1_menu();
                    tp_i2c_read_status();
                    cVar1 = *puVar4;
                    while (cVar1 != '\0') {
                      tp_i2c_read_status();
                      cVar1 = *puVar4;
                    }
                  }
                }
                else {
                  if (((uVar16 < 0x3a) && (0x6f < uVar11)) && (uVar11 < 0xa9)) {
                    if (*puVar4 != '\0') {
                      pcVar6[4] = '\0';
                      display_channel1_menu();
                      tp_i2c_read_status();
                      cVar1 = *puVar4;
                      while (cVar1 != '\0') {
                        tp_i2c_read_status();
                        cVar1 = *puVar4;
                      }
                    }
                  }
                  else {
                    if (((uVar14 < 0x3b) && (0xad < uVar11)) && (uVar11 < 0xe7)) {
                      if (*puVar4 != '\0') {
                        pcVar6[1] = '\0';
                        set_fpga_channel1_coupling();
                        display_channel1_menu();
                        tp_i2c_read_status();
                        cVar1 = *puVar4;
                        while (cVar1 != '\0') {
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                        }
                      }
                    }
                    else {
                      if (((uVar16 < 0x3a) && (0xad < uVar11)) && (uVar11 < 0xe7)) {
                        if (*puVar4 != '\0') {
                          pcVar6[1] = '\x01';
                          set_fpga_channel1_coupling();
                          display_channel1_menu();
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                          while (cVar1 != '\0') {
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                          }
                        }
                      }
                      else {
                        if (((uVar10 - 0xe6 < 0x22) && (0xeb < uVar11)) && (uVar11 < 0x125)) {
                          if (*puVar4 != '\0') {
                            pcVar6[2] = '\0';
                            display_channel1_menu();
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                            while (cVar1 != '\0') {
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                            }
                          }
                        }
                        else {
                          if (((uVar10 - 0x108 < 0x20) && (0xeb < uVar11)) && (uVar11 < 0x125)) {
                            if (*puVar4 != '\0') {
                              pcVar6[2] = '\x01';
                              display_channel1_menu();
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                              while (cVar1 != '\0') {
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                              }
                            }
                          }
                          else {
                            if (((uVar10 - 0x129 < 0x20) && (0xeb < uVar11)) &&
                               ((uVar11 < 0x125 && (*puVar4 != '\0')))) {
                              pcVar6[2] = '\x02';
                              display_channel1_menu();
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                              while (cVar1 != '\0') {
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
            goto LAB_8001dc04;
          }
        }
      } while (*puVar4 == '\0');
      restore_screen_channel1();
      tp_i2c_read_status();
      cVar1 = *puVar4;
      while (cVar1 != '\0') {
        tp_i2c_read_status();
        cVar1 = *puVar4;
      }
    }
    else {
      if ((uVar10 - 0x121 < 0x67) &&
         (*(ushort *)(PTR_DAT_8001e9b4 + 4) != 0 && *(ushort *)(PTR_DAT_8001e9b4 + 4) < 0x3d)) {
        cVar1 = *PTR_DAT_8001e9b4;
        while (cVar1 != '\0') {
          display_ch2_settings(1);
          tp_i2c_read_status();
          cVar1 = *puVar4;
        }
        display_ch2_settings(0);
        setup_channel2_menu();
LAB_8001dfb0:
        do {
          tp_i2c_read_status();
          uVar10 = (uint)*(ushort *)(puVar4 + 2);
          if (uVar10 - 0x121 < 0xb6) {
            uVar11 = (uint)*(ushort *)(puVar4 + 4);
            bVar18 = 0x2d < uVar11;
            bVar17 = uVar11 == 0x2e;
            if (0x2e < uVar11) {
              bVar18 = uVar11 <= uVar12;
              bVar17 = uVar12 == uVar11;
            }
            if (bVar18 && !bVar17) {
              uVar14 = uVar10 - 0x15b;
              if (((uVar14 < 0x3b) && (0x31 < uVar11)) && (uVar11 < 0x6b)) {
                if (*puVar4 != '\0') {
                  pcVar6[0xc] = '\x01';
                  display_channel2_menu();
                  set_fpga_channel_trigger_channel();
                  tp_i2c_read_status();
                  cVar1 = *puVar4;
                  while (cVar1 != '\0') {
                    tp_i2c_read_status();
                    cVar1 = *puVar4;
                  }
                }
              }
              else {
                uVar16 = uVar10 - 0x199;
                if (((uVar16 < 0x3a) && (0x31 < uVar11)) && (uVar11 < 0x6b)) {
                  if (*puVar4 != '\0') {
                    pcVar6[0xc] = '\0';
                    display_channel2_menu();
                    set_fpga_channel_trigger_channel();
                    pcVar6[0xf] = '\0';
                    set_fpga_channel2_voltperdiv();
                    tp_i2c_read_status();
                    cVar1 = *puVar4;
                    while (cVar1 != '\0') {
                      tp_i2c_read_status();
                      cVar1 = *puVar4;
                    }
                  }
                }
                else {
                  if (((uVar14 < 0x3b) && (0x6f < uVar11)) && (uVar11 < 0xa9)) {
                    if (*puVar4 != '\0') {
                      pcVar6[0x10] = '\x01';
                      display_channel2_menu();
                      tp_i2c_read_status();
                      cVar1 = *puVar4;
                      while (cVar1 != '\0') {
                        tp_i2c_read_status();
                        cVar1 = *puVar4;
                      }
                    }
                  }
                  else {
                    if (((uVar16 < 0x3a) && (0x6f < uVar11)) && (uVar11 < 0xa9)) {
                      if (*puVar4 != '\0') {
                        pcVar6[0x10] = '\0';
                        display_channel2_menu();
                        tp_i2c_read_status();
                        cVar1 = *puVar4;
                        while (cVar1 != '\0') {
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                        }
                      }
                    }
                    else {
                      if (((uVar14 < 0x3b) && (0xad < uVar11)) && (uVar11 < 0xe7)) {
                        if (*puVar4 != '\0') {
                          pcVar6[0xd] = '\0';
                          set_fpga_channel2_coupling();
                          display_channel2_menu();
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                          while (cVar1 != '\0') {
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                          }
                        }
                      }
                      else {
                        if (((uVar16 < 0x3a) && (0xad < uVar11)) && (uVar11 < 0xe7)) {
                          if (*puVar4 != '\0') {
                            pcVar6[0xd] = '\x01';
                            set_fpga_channel2_coupling();
                            display_channel2_menu();
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                            while (cVar1 != '\0') {
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                            }
                          }
                        }
                        else {
                          if (((uVar10 - 0x165 < 0x22) && (0xeb < uVar11)) && (uVar11 < 0x125)) {
                            if (*puVar4 != '\0') {
                              pcVar6[0xe] = '\0';
                              display_channel2_menu();
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                              while (cVar1 != '\0') {
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                              }
                            }
                          }
                          else {
                            if (((uVar10 - 0x187 < 0x20) && (0xeb < uVar11)) && (uVar11 < 0x125)) {
                              if (*puVar4 != '\0') {
                                pcVar6[0xe] = '\x01';
                                display_channel2_menu();
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                                while (cVar1 != '\0') {
                                  tp_i2c_read_status();
                                  cVar1 = *puVar4;
                                }
                              }
                            }
                            else {
                              if (((uVar10 - 0x1a8 < 0x20) && (0xeb < uVar11)) &&
                                 ((uVar11 < 0x125 && (*puVar4 != '\0')))) {
                                pcVar6[0xe] = '\x02';
                                display_channel2_menu();
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                                while (cVar1 != '\0') {
                                  tp_i2c_read_status();
                                  cVar1 = *puVar4;
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
              goto LAB_8001dfb0;
            }
          }
        } while (*puVar4 == '\0');
        FUN_8000a6e8();
        tp_i2c_read_status();
        cVar1 = *puVar4;
        while (cVar1 != '\0') {
          tp_i2c_read_status();
          cVar1 = *puVar4;
        }
      }
      else {
        if ((uVar10 - 0x1f1 < 0x2c) &&
           (*(ushort *)(PTR_DAT_8001e9b4 + 4) != 0 && *(ushort *)(PTR_DAT_8001e9b4 + 4) < 0x3c)) {
          cVar1 = *PTR_DAT_8001e9b4;
          while (cVar1 != '\0') {
            display_move_speed(1);
            tp_i2c_read_status();
            cVar1 = *puVar4;
          }
          if (pcVar6[0x16] == '\0') {
            pcVar6[0x16] = '\x01';
          }
          else {
            pcVar6[0x16] = '\0';
          }
          display_move_speed(0);
          tp_i2c_read_status();
          cVar1 = *puVar4;
          while (cVar1 != '\0') {
            tp_i2c_read_status();
            cVar1 = *puVar4;
          }
        }
        else {
          if ((uVar10 - 0x23b < 0x77) &&
             (*(ushort *)(PTR_DAT_8001e9b4 + 4) != 0 && *(ushort *)(PTR_DAT_8001e9b4 + 4) < 0x3c)) {
            if (DAT_8001e9bc[0x43] == '\0') {
              cVar1 = *PTR_DAT_8001e9b4;
              while (cVar1 != '\0') {
                display_trigger_settings(1);
                tp_i2c_read_status();
                cVar1 = *puVar4;
              }
              display_trigger_settings(0);
              setup_trigger_menu();
              do {
                while( true ) {
                  tp_i2c_read_status();
                  uVar12 = (uint)*(ushort *)(puVar4 + 2);
                  if (((0xaa < uVar12 - 0x230) || (uVar3 = *(ushort *)(puVar4 + 4), uVar3 < 0x2f))
                     || (0xe7 < uVar3)) break;
                  if (((uVar12 - 0x26e < 0x1e) && (0x30 < uVar3)) && (uVar3 < 0x6a)) {
                    if (*puVar4 != '\0') {
                      pcVar6[0x21] = '\0';
                      set_fpga_trigger_mode();
                      display_trigger_menu();
                      pcVar6[0x3a] = '\0';
                      pcVar6[0x18] = '\x01';
                      pcVar6[0x17] = '\x01';
                      display_run_stop_text((uint)(byte)pcVar6[0x3a]);
                      tp_i2c_read_status();
                      cVar1 = *puVar4;
                      while (cVar1 != '\0') {
                        tp_i2c_read_status();
                        cVar1 = *puVar4;
                      }
                    }
                  }
                  else {
                    if (((uVar12 - 0x28e < 0x2a) && (0x30 < uVar3)) && (uVar3 < 0x6a)) {
                      if (*puVar4 != '\0') {
                        pcVar6[0x21] = '\x01';
                        pcVar6[0x3a] = '\0';
                        pcVar6[0x36] = '\0';
                        pcVar6[0x37] = '\x01';
                        set_fpga_trigger_mode();
                        display_trigger_menu();
                        display_run_stop_text((uint)(byte)pcVar6[0x3a]);
                        if ((byte)pcVar6[10] < 0xb) {
                          pcVar6[10] = '\v';
                          set_fpga_trigger_timebase();
                          display_time_div_setting();
                        }
                        tp_i2c_read_status();
                        cVar1 = *puVar4;
                        while (cVar1 != '\0') {
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                        }
                      }
                    }
                    else {
                      if (((uVar12 - 0x2b9 < 0x1f) && (0x30 < uVar3)) && (uVar3 < 0x6a)) {
                        if (*puVar4 != '\0') {
                          pcVar6[0x21] = '\x02';
                          set_fpga_trigger_mode();
                          display_trigger_menu();
                          pcVar6[0x3a] = '\0';
                          display_run_stop_text((uint)(byte)pcVar6[0x3a]);
                          pcVar6[0x36] = '\0';
                          pcVar6[0x37] = '\x01';
                          if ((byte)pcVar6[10] < 0xb) {
                            pcVar6[10] = '\v';
                            set_fpga_trigger_timebase();
                            display_time_div_setting();
                          }
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                          while (cVar1 != '\0') {
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                          }
                        }
                      }
                      else {
                        if (((uVar12 - 0x268 < 0x35) && (0x6e < uVar3)) && (uVar3 < 0xa8)) {
                          if (*puVar4 != '\0') {
                            pcVar6[0x22] = '\0';
                            set_fpga_trigger_edge();
                            display_trigger_menu();
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                            while (cVar1 != '\0') {
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                            }
                          }
                        }
                        else {
                          if (((uVar12 - 0x29e < 0x34) && (0x6e < uVar3)) && (uVar3 < 0xa8)) {
                            if (*puVar4 != '\0') {
                              pcVar6[0x22] = '\x01';
                              set_fpga_trigger_edge();
                              display_trigger_menu();
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                              while (cVar1 != '\0') {
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                              }
                            }
                          }
                          else {
                            if (((uVar12 - 0x268 < 0x35) && (0xac < uVar3)) && (uVar3 < 0xe6)) {
                              if (*puVar4 != '\0') {
                                if (*pcVar6 != '\0') {
                                  pcVar6[0x23] = '\0';
                                  set_fpga_trigger_channel();
                                  display_trigger_menu();
                                }
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                                while (cVar1 != '\0') {
                                  tp_i2c_read_status();
                                  cVar1 = *puVar4;
                                }
                              }
                            }
                            else {
                              if (((uVar12 - 0x29e < 0x34) && (0xac < uVar3)) &&
                                 ((uVar3 < 0xe6 && (*puVar4 != '\0')))) {
                                if (pcVar6[0xc] != '\0') {
                                  pcVar6[0x23] = '\x01';
                                  set_fpga_trigger_channel();
                                  display_trigger_menu();
                                }
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                                while (cVar1 != '\0') {
                                  tp_i2c_read_status();
                                  cVar1 = *puVar4;
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              } while (*puVar4 == '\0');
              FUN_8000a728();
              tp_i2c_read_status();
              cVar1 = *puVar4;
              while (cVar1 != '\0') {
                tp_i2c_read_status();
                cVar1 = *puVar4;
              }
            }
          }
          else {
            if ((uVar10 - 0x2e5 < 0x3a) &&
               (uVar3 = *(ushort *)(PTR_DAT_8001e9b4 + 4), 0x12f < uVar3)) {
              bVar17 = uVar3 == 0x164;
              if (uVar3 < 0x165) {
                bVar17 = DAT_8001e9bc[0x42] == '\0';
              }
              if (bVar17) {
                cVar1 = *PTR_DAT_8001e9b4;
                while (cVar1 != '\0') {
                  display_measures_button(1);
                  tp_i2c_read_status();
                  cVar1 = *puVar4;
                }
                display_measures_button(0);
                setup_measures_menu();
                uVar12 = DAT_8001e9c4;
                uVar11 = DAT_8001e9c4 - 0x15;
                uVar10 = DAT_8001e9c4 - 0x92;
LAB_8001e7b0:
                do {
                  tp_i2c_read_status();
                  iVar5 = DAT_8001e9b8;
                  uVar14 = (uint)*(ushort *)(puVar4 + 2);
                  if (uVar14 - 0xe7 < uVar12) {
                    uVar16 = (uint)*(ushort *)(puVar4 + 4);
                    bVar17 = uVar16 == 0x108;
                    if (0x107 < uVar16) {
                      bVar17 = uVar11 == uVar16;
                    }
                    if ((0x107 < uVar16 && uVar16 <= uVar11) && !bVar17) {
                      uVar15 = uVar14 - 0x1e2;
                      if (((uVar15 < 0x3c) && (0x123 < uVar16)) && (uVar16 < 0x160)) {
                        if (*puVar4 != '\0') {
                          if (*(char *)(iVar13 + 0x100) == '\0') {
                            uVar14 = 0;
                            *(undefined *)(iVar13 + 0x100) = 1;
                            do {
                              uVar15 = (uint)*(byte *)(iVar5 + uVar14);
                              if (uVar15 == 0) {
                                *(undefined *)(iVar5 + uVar14) = 1;
                                break;
                              }
                              uVar14 = uVar14 + 1 & 0xff;
                            } while (uVar14 < 0x18);
                          }
                          else {
                            *(undefined *)(iVar13 + 0x100) = 0;
                            remove_measures_item_from_list(1);
                          }
                        }
                        highlight_measures_menu_items();
                        tp_i2c_read_status();
                        cVar1 = *puVar4;
                        while (cVar1 != '\0') {
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                        }
                      }
                      else {
                        uVar15 = uVar14 - 0x220;
                        if (((uVar15 < 0x3c) && (0x123 < uVar16)) && (uVar16 < 0x160)) {
                          if (*puVar4 != '\0') {
                            if (*(char *)(iVar13 + 0x112) == '\0') {
                              uVar14 = 0;
                              *(undefined *)(iVar13 + 0x112) = 1;
                              do {
                                uVar15 = (uint)*(byte *)(iVar5 + uVar14);
                                if (uVar15 == 0) {
                                  *(undefined *)(iVar5 + uVar14) = 2;
                                  break;
                                }
                                uVar14 = uVar14 + 1 & 0xff;
                              } while (uVar14 < 0x18);
                            }
                            else {
                              *(undefined *)(iVar13 + 0x112) = 0;
                              remove_measures_item_from_list(2);
                            }
                          }
                          highlight_measures_menu_items();
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                          while (cVar1 != '\0') {
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                          }
                        }
                        else {
                          uVar15 = uVar14 - 0x25e;
                          if (((uVar15 < 0x3c) && (0x123 < uVar16)) && (uVar16 < 0x160)) {
                            if (*puVar4 != '\0') {
                              if (*(char *)(iVar13 + 0x122) == '\0') {
                                uVar14 = 0;
                                *(undefined *)(iVar13 + 0x122) = 1;
                                do {
                                  uVar15 = (uint)*(byte *)(iVar5 + uVar14);
                                  if (uVar15 == 0) {
                                    *(undefined *)(iVar5 + uVar14) = 3;
                                    break;
                                  }
                                  uVar14 = uVar14 + 1 & 0xff;
                                } while (uVar14 < 0x18);
                              }
                              else {
                                *(undefined *)(iVar13 + 0x122) = 0;
                                remove_measures_item_from_list(3);
                              }
                            }
                            highlight_measures_menu_items();
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                            while (cVar1 != '\0') {
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                            }
                          }
                          else {
                            if (((uVar14 - 0x29c < 0x3c) && (0x123 < uVar16)) && (uVar16 < 0x160)) {
                              if (*puVar4 != '\0') {
                                if (*(char *)(iVar13 + 0x132) == '\0') {
                                  uVar14 = 0;
                                  *(undefined *)(iVar13 + 0x132) = 1;
                                  do {
                                    uVar15 = (uint)*(byte *)(iVar5 + uVar14);
                                    if (uVar15 == 0) {
                                      *(undefined *)(iVar5 + uVar14) = 4;
                                      break;
                                    }
                                    uVar14 = uVar14 + 1 & 0xff;
                                  } while (uVar14 < 0x18);
                                }
                                else {
                                  *(undefined *)(iVar13 + 0x132) = 0;
                                  remove_measures_item_from_list(4);
                                }
                              }
                              highlight_measures_menu_items();
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                              while (cVar1 != '\0') {
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                              }
                            }
                          }
                        }
                      }
                      iVar5 = DAT_8001e9b8;
                      uVar16 = (uint)*(ushort *)(puVar4 + 2);
                      uVar14 = uVar16 - 0x1e2;
                      bVar17 = 0x3b < uVar14;
                      if (!bVar17) {
                        uVar14 = (uint)*(ushort *)(puVar4 + 4);
                      }
                      if (!bVar17 && uVar14 > uVar10) {
                        uVar15 = DAT_8001f98c;
                      }
                      if ((bVar17 || uVar14 <= uVar10) || uVar15 <= uVar14) {
                        uVar14 = uVar16 - 0x220;
                        bVar17 = 0x3b < uVar14;
                        if (!bVar17) {
                          uVar14 = (uint)*(ushort *)(puVar4 + 4);
                        }
                        if (!bVar17 && uVar14 > uVar10) {
                          uVar15 = DAT_8001f98c;
                        }
                        if ((bVar17 || uVar14 <= uVar10) || uVar15 <= uVar14) {
                          uVar14 = uVar16 - 0x25e;
                          bVar17 = 0x3b < uVar14;
                          if (!bVar17) {
                            uVar14 = (uint)*(ushort *)(puVar4 + 4);
                          }
                          if (!bVar17 && uVar14 > uVar10) {
                            uVar15 = DAT_8001f98c;
                          }
                          if ((bVar17 || uVar14 <= uVar10) || uVar15 <= uVar14) {
                            uVar16 = uVar16 - 0x29c;
                            bVar17 = uVar16 < 0x3c;
                            if (bVar17) {
                              uVar16 = (uint)*(ushort *)(puVar4 + 4);
                            }
                            if (bVar17 && uVar10 < uVar16) {
                              uVar14 = DAT_8001f98c;
                            }
                            if ((bVar17 && uVar10 < uVar16) && uVar16 < uVar14) {
                              if (*puVar4 != '\0') {
                                if (*(char *)(iVar13 + 0x172) == '\0') {
                                  uVar14 = 0;
                                  *(undefined *)(iVar13 + 0x172) = 1;
                                  do {
                                    uVar15 = (uint)*(byte *)(iVar5 + uVar14);
                                    if (uVar15 == 0) {
                                      *(undefined *)(iVar5 + uVar14) = 8;
                                      break;
                                    }
                                    uVar14 = uVar14 + 1 & 0xff;
                                  } while (uVar14 < 0x18);
                                }
                                else {
                                  *(undefined *)(iVar13 + 0x172) = 0;
                                  remove_measures_item_from_list(8);
                                }
                              }
                              highlight_measures_menu_items();
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                              while (cVar1 != '\0') {
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                              }
                            }
                          }
                          else {
                            if (*puVar4 != '\0') {
                              if (*(char *)(iVar13 + 0x162) == '\0') {
                                uVar14 = 0;
                                *(undefined *)(iVar13 + 0x162) = 1;
                                do {
                                  uVar15 = (uint)*(byte *)(iVar5 + uVar14);
                                  if (uVar15 == 0) {
                                    *(undefined *)(iVar5 + uVar14) = 7;
                                    break;
                                  }
                                  uVar14 = uVar14 + 1 & 0xff;
                                } while (uVar14 < 0x18);
                              }
                              else {
                                *(undefined *)(iVar13 + 0x162) = 0;
                                remove_measures_item_from_list(7);
                              }
                            }
                            highlight_measures_menu_items();
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                            while (cVar1 != '\0') {
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                            }
                          }
                        }
                        else {
                          if (*puVar4 != '\0') {
                            if (*(char *)(iVar13 + 0x152) == '\0') {
                              uVar14 = 0;
                              *(undefined *)(iVar13 + 0x152) = 1;
                              do {
                                uVar15 = (uint)*(byte *)(iVar5 + uVar14);
                                if (uVar15 == 0) {
                                  *(undefined *)(iVar5 + uVar14) = 6;
                                  break;
                                }
                                uVar14 = uVar14 + 1 & 0xff;
                              } while (uVar14 < 0x18);
                            }
                            else {
                              *(undefined *)(iVar13 + 0x152) = 0;
                              remove_measures_item_from_list(6);
                            }
                          }
                          highlight_measures_menu_items();
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                          while (cVar1 != '\0') {
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                          }
                        }
                      }
                      else {
                        if (*puVar4 != '\0') {
                          if (*(char *)(iVar13 + 0x142) == '\0') {
                            uVar14 = 0;
                            *(undefined *)(iVar13 + 0x142) = 1;
                            do {
                              uVar15 = (uint)*(byte *)(iVar5 + uVar14);
                              if (uVar15 == 0) {
                                *(undefined *)(iVar5 + uVar14) = 5;
                                break;
                              }
                              uVar14 = uVar14 + 1 & 0xff;
                            } while (uVar14 < 0x18);
                          }
                          else {
                            *(undefined *)(iVar13 + 0x142) = 0;
                            remove_measures_item_from_list(5);
                          }
                        }
                        highlight_measures_menu_items();
                        tp_i2c_read_status();
                        cVar1 = *puVar4;
                        while (cVar1 != '\0') {
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                        }
                      }
                      iVar5 = DAT_8001e9b8;
                      uVar14 = (uint)*(ushort *)(puVar4 + 2);
                      if (((uVar14 - 0x1e2 < 0x3c) && (0x19f < *(ushort *)(puVar4 + 4))) &&
                         (*(ushort *)(puVar4 + 4) < 0x1dc)) {
                        if (*puVar4 != '\0') {
                          if (*(char *)(iVar13 + 0x182) == '\0') {
                            uVar14 = 0;
                            *(undefined *)(iVar13 + 0x182) = 1;
                            do {
                              uVar15 = (uint)*(byte *)(iVar5 + uVar14);
                              if (uVar15 == 0) {
                                *(undefined *)(iVar5 + uVar14) = 9;
                                break;
                              }
                              uVar14 = uVar14 + 1 & 0xff;
                            } while (uVar14 < 0x18);
                          }
                          else {
                            *(undefined *)(iVar13 + 0x182) = 0;
                            remove_measures_item_from_list(9);
                          }
                        }
                        highlight_measures_menu_items();
                        tp_i2c_read_status();
                        cVar1 = *puVar4;
                        while (cVar1 != '\0') {
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                        }
                      }
                      else {
                        if (((uVar14 - 0x220 < 0x3c) && (0x19f < *(ushort *)(puVar4 + 4))) &&
                           (*(ushort *)(puVar4 + 4) < 0x1dc)) {
                          if (*puVar4 != '\0') {
                            if (*(char *)(iVar13 + 0x192) == '\0') {
                              uVar14 = 0;
                              *(undefined *)(iVar13 + 0x192) = 1;
                              do {
                                uVar15 = (uint)*(byte *)(iVar5 + uVar14);
                                if (uVar15 == 0) {
                                  *(undefined *)(iVar5 + uVar14) = 10;
                                  break;
                                }
                                uVar14 = uVar14 + 1 & 0xff;
                              } while (uVar14 < 0x18);
                            }
                            else {
                              *(undefined *)(iVar13 + 0x192) = 0;
                              remove_measures_item_from_list(10);
                            }
                          }
                          highlight_measures_menu_items();
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                          while (cVar1 != '\0') {
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                          }
                        }
                        else {
                          if (((uVar14 - 0x25e < 0x3c) && (0x19f < *(ushort *)(puVar4 + 4))) &&
                             (*(ushort *)(puVar4 + 4) < 0x1dc)) {
                            if (*puVar4 != '\0') {
                              if (*(char *)(iVar13 + 0x1a2) == '\0') {
                                uVar14 = 0;
                                *(undefined *)(iVar13 + 0x1a2) = 1;
                                do {
                                  uVar15 = (uint)*(byte *)(iVar5 + uVar14);
                                  if (uVar15 == 0) {
                                    *(undefined *)(iVar5 + uVar14) = 0xb;
                                    break;
                                  }
                                  uVar14 = uVar14 + 1 & 0xff;
                                } while (uVar14 < 0x18);
                              }
                              else {
                                *(undefined *)(iVar13 + 0x1a2) = 0;
                                remove_measures_item_from_list(0xb);
                              }
                            }
                            highlight_measures_menu_items();
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                            while (cVar1 != '\0') {
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                            }
                          }
                          else {
                            if (((uVar14 - 0x29c < 0x3c) && (0x19f < *(ushort *)(puVar4 + 4))) &&
                               (*(ushort *)(puVar4 + 4) < 0x1dc)) {
                              if (*puVar4 != '\0') {
                                if (*(char *)(iVar13 + 0x1b2) == '\0') {
                                  uVar14 = 0;
                                  *(undefined *)(iVar13 + 0x1b2) = 1;
                                  do {
                                    uVar15 = (uint)*(byte *)(iVar5 + uVar14);
                                    if (uVar15 == 0) {
                                      *(undefined *)(iVar5 + uVar14) = 0xc;
                                      break;
                                    }
                                    uVar14 = uVar14 + 1 & 0xff;
                                  } while (uVar14 < 0x18);
                                }
                                else {
                                  *(undefined *)(iVar13 + 0x1b2) = 0;
                                  remove_measures_item_from_list(0xc);
                                }
                              }
                              highlight_measures_menu_items();
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                              while (cVar1 != '\0') {
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                              }
                            }
                          }
                        }
                      }
                      iVar5 = DAT_8001e9b8;
                      uVar14 = (uint)*(ushort *)(puVar4 + 2);
                      if (((uVar14 - 0xe9 < 0x3c) && (0x123 < *(ushort *)(puVar4 + 4))) &&
                         (*(ushort *)(puVar4 + 4) < 0x160)) {
                        if (*puVar4 != '\0') {
                          if (*(char *)(iVar13 + 0x1c2) == '\0') {
                            uVar14 = 0;
                            *(undefined *)(iVar13 + 0x1c2) = 1;
                            do {
                              uVar15 = (uint)*(byte *)(iVar5 + uVar14);
                              if (uVar15 == 0) {
                                *(undefined *)(iVar5 + uVar14) = 0xd;
                                break;
                              }
                              uVar14 = uVar14 + 1 & 0xff;
                            } while (uVar14 < 0x18);
                          }
                          else {
                            *(undefined *)(iVar13 + 0x1c2) = 0;
                            remove_measures_item_from_list(0xd);
                          }
                        }
                        highlight_measures_menu_items();
                        tp_i2c_read_status();
                        cVar1 = *puVar4;
                        while (cVar1 != '\0') {
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                        }
                      }
                      else {
                        if (((uVar14 - 0x127 < 0x3c) && (0x123 < *(ushort *)(puVar4 + 4))) &&
                           (*(ushort *)(puVar4 + 4) < 0x160)) {
                          if (*puVar4 != '\0') {
                            if (*(char *)(iVar13 + 0x1d2) == '\0') {
                              uVar14 = 0;
                              *(undefined *)(iVar13 + 0x1d2) = 1;
                              do {
                                uVar15 = (uint)*(byte *)(iVar5 + uVar14);
                                if (uVar15 == 0) {
                                  *(undefined *)(iVar5 + uVar14) = 0xe;
                                  break;
                                }
                                uVar14 = uVar14 + 1 & 0xff;
                              } while (uVar14 < 0x18);
                            }
                            else {
                              *(undefined *)(iVar13 + 0x1d2) = 0;
                              remove_measures_item_from_list(0xe);
                            }
                          }
                          highlight_measures_menu_items();
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                          while (cVar1 != '\0') {
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                          }
                        }
                        else {
                          if (((uVar14 - 0x165 < 0x3c) && (0x123 < *(ushort *)(puVar4 + 4))) &&
                             (*(ushort *)(puVar4 + 4) < 0x160)) {
                            if (*puVar4 != '\0') {
                              if (*(char *)(iVar13 + 0x1e2) == '\0') {
                                uVar14 = 0;
                                *(undefined *)(iVar13 + 0x1e2) = 1;
                                do {
                                  uVar15 = (uint)*(byte *)(iVar5 + uVar14);
                                  if (uVar15 == 0) {
                                    *(undefined *)(iVar5 + uVar14) = 0xf;
                                    break;
                                  }
                                  uVar14 = uVar14 + 1 & 0xff;
                                } while (uVar14 < 0x18);
                              }
                              else {
                                *(undefined *)(iVar13 + 0x1e2) = 0;
                                remove_measures_item_from_list(0xf);
                              }
                            }
                            highlight_measures_menu_items();
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                            while (cVar1 != '\0') {
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                            }
                          }
                          else {
                            if (((uVar14 - 0x1a3 < 0x3c) && (0x123 < *(ushort *)(puVar4 + 4))) &&
                               (*(ushort *)(puVar4 + 4) < 0x160)) {
                              if (*puVar4 != '\0') {
                                if (*(char *)(iVar13 + 0x1f2) == '\0') {
                                  uVar14 = 0;
                                  *(undefined *)(iVar13 + 0x1f2) = 1;
                                  do {
                                    uVar15 = (uint)*(byte *)(iVar5 + uVar14);
                                    if (uVar15 == 0) {
                                      *(undefined *)(iVar5 + uVar14) = 0x10;
                                      break;
                                    }
                                    uVar14 = uVar14 + 1 & 0xff;
                                  } while (uVar14 < 0x18);
                                }
                                else {
                                  *(undefined *)(iVar13 + 0x1f2) = 0;
                                  remove_measures_item_from_list(0x10);
                                }
                              }
                              highlight_measures_menu_items();
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                              while (cVar1 != '\0') {
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                              }
                            }
                          }
                        }
                      }
                      iVar5 = DAT_8001e9b8;
                      uVar16 = (uint)*(ushort *)(puVar4 + 2);
                      uVar14 = uVar16 - 0xe9;
                      bVar17 = 0x3b < uVar14;
                      if (!bVar17) {
                        uVar14 = (uint)*(ushort *)(puVar4 + 4);
                      }
                      if (!bVar17 && uVar14 > uVar10) {
                        uVar15 = DAT_8001f98c;
                      }
                      if ((bVar17 || uVar14 <= uVar10) || uVar15 <= uVar14) {
                        uVar14 = uVar16 - 0x127;
                        bVar17 = 0x3b < uVar14;
                        if (!bVar17) {
                          uVar14 = (uint)*(ushort *)(puVar4 + 4);
                        }
                        if (!bVar17 && uVar14 > uVar10) {
                          uVar15 = DAT_8001f98c;
                        }
                        if ((bVar17 || uVar14 <= uVar10) || uVar15 <= uVar14) {
                          uVar14 = uVar16 - 0x165;
                          bVar17 = 0x3b < uVar14;
                          if (!bVar17) {
                            uVar14 = (uint)*(ushort *)(puVar4 + 4);
                          }
                          if (!bVar17 && uVar14 > uVar10) {
                            uVar15 = DAT_8001f98c;
                          }
                          if ((bVar17 || uVar14 <= uVar10) || uVar15 <= uVar14) {
                            uVar16 = uVar16 - 0x1a3;
                            bVar17 = uVar16 < 0x3c;
                            if (bVar17) {
                              uVar16 = (uint)*(ushort *)(puVar4 + 4);
                            }
                            if (bVar17 && uVar10 < uVar16) {
                              uVar14 = DAT_8001f98c;
                            }
                            if ((bVar17 && uVar10 < uVar16) && uVar16 < uVar14) {
                              if (*puVar4 != '\0') {
                                if (*(char *)(iVar13 + 0x242) == '\0') {
                                  uVar14 = 0;
                                  *(undefined *)(iVar13 + 0x242) = 1;
                                  do {
                                    if (*(char *)(iVar5 + uVar14) == '\0') {
                                      *(undefined *)(iVar5 + uVar14) = 0x14;
                                      break;
                                    }
                                    uVar14 = uVar14 + 1 & 0xff;
                                  } while (uVar14 < 0x18);
                                }
                                else {
                                  *(undefined *)(iVar13 + 0x242) = 0;
                                  remove_measures_item_from_list(0x14);
                                }
                              }
                              highlight_measures_menu_items();
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                              while (cVar1 != '\0') {
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                              }
                            }
                          }
                          else {
                            if (*puVar4 != '\0') {
                              if (*(char *)(iVar13 + 0x232) == '\0') {
                                uVar14 = 0;
                                *(undefined *)(iVar13 + 0x232) = 1;
                                do {
                                  if (*(char *)(iVar5 + uVar14) == '\0') {
                                    *(undefined *)(iVar5 + uVar14) = 0x13;
                                    break;
                                  }
                                  uVar14 = uVar14 + 1 & 0xff;
                                } while (uVar14 < 0x18);
                              }
                              else {
                                *(undefined *)(iVar13 + 0x232) = 0;
                                remove_measures_item_from_list(0x13);
                              }
                            }
                            highlight_measures_menu_items();
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                            while (cVar1 != '\0') {
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                            }
                          }
                        }
                        else {
                          if (*puVar4 != '\0') {
                            if (*(char *)(iVar13 + 0x212) == '\0') {
                              uVar14 = 0;
                              *(undefined *)(iVar13 + 0x212) = 1;
                              do {
                                if (*(char *)(iVar5 + uVar14) == '\0') {
                                  *(undefined *)(iVar5 + uVar14) = 0x12;
                                  break;
                                }
                                uVar14 = uVar14 + 1 & 0xff;
                              } while (uVar14 < 0x18);
                            }
                            else {
                              *(undefined *)(iVar13 + 0x212) = 0;
                              remove_measures_item_from_list(0x12);
                            }
                          }
                          highlight_measures_menu_items();
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                          while (cVar1 != '\0') {
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                          }
                        }
                      }
                      else {
                        if (*puVar4 != '\0') {
                          if (*(char *)(iVar13 + 0x202) == '\0') {
                            uVar14 = 0;
                            *(undefined *)(iVar13 + 0x202) = 1;
                            do {
                              if (*(char *)(iVar5 + uVar14) == '\0') {
                                *(undefined *)(iVar5 + uVar14) = 0x11;
                                break;
                              }
                              uVar14 = uVar14 + 1 & 0xff;
                            } while (uVar14 < 0x18);
                          }
                          else {
                            *(undefined *)(iVar13 + 0x202) = 0;
                            remove_measures_item_from_list(0x11);
                          }
                        }
                        highlight_measures_menu_items();
                        tp_i2c_read_status();
                        cVar1 = *puVar4;
                        while (cVar1 != '\0') {
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                        }
                      }
                      iVar5 = DAT_8001e9b8;
                      uVar14 = (uint)*(ushort *)(puVar4 + 2);
                      if (((uVar14 - 0xe9 < 0x3c) && (0x19f < *(ushort *)(puVar4 + 4))) &&
                         (*(ushort *)(puVar4 + 4) < 0x1dc)) {
                        if (*puVar4 != '\0') {
                          if (*(char *)(iVar13 + 0x252) == '\0') {
                            uVar14 = 0;
                            *(undefined *)(iVar13 + 0x252) = 1;
                            do {
                              if (*(char *)(iVar5 + uVar14) == '\0') {
                                *(undefined *)(iVar5 + uVar14) = 0x15;
                                break;
                              }
                              uVar14 = uVar14 + 1 & 0xff;
                            } while (uVar14 < 0x18);
                          }
                          else {
                            *(undefined *)(iVar13 + 0x252) = 0;
                            remove_measures_item_from_list(0x15);
                          }
                        }
                        highlight_measures_menu_items();
                        tp_i2c_read_status();
                        cVar1 = *puVar4;
                        while (cVar1 != '\0') {
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                        }
                      }
                      else {
                        if (((uVar14 - 0x127 < 0x3c) && (0x19f < *(ushort *)(puVar4 + 4))) &&
                           (*(ushort *)(puVar4 + 4) < 0x1dc)) {
                          if (*puVar4 != '\0') {
                            if (*(char *)(iVar13 + 0x262) == '\0') {
                              uVar14 = 0;
                              *(undefined *)(iVar13 + 0x262) = 1;
                              do {
                                if (*(char *)(iVar5 + uVar14) == '\0') {
                                  *(undefined *)(iVar5 + uVar14) = 0x16;
                                  break;
                                }
                                uVar14 = uVar14 + 1 & 0xff;
                              } while (uVar14 < 0x18);
                            }
                            else {
                              *(undefined *)(iVar13 + 0x262) = 0;
                              remove_measures_item_from_list(0x16);
                            }
                          }
                          highlight_measures_menu_items();
                          tp_i2c_read_status();
                          cVar1 = *puVar4;
                          while (cVar1 != '\0') {
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                          }
                        }
                        else {
                          if (((uVar14 - 0x165 < 0x3c) && (0x19f < *(ushort *)(puVar4 + 4))) &&
                             (*(ushort *)(puVar4 + 4) < 0x1dc)) {
                            if (*puVar4 != '\0') {
                              if (*(char *)(iVar13 + 0x272) == '\0') {
                                uVar14 = 0;
                                *(undefined *)(iVar13 + 0x272) = 1;
                                do {
                                  if (*(char *)(iVar5 + uVar14) == '\0') {
                                    *(undefined *)(iVar5 + uVar14) = 0x17;
                                    break;
                                  }
                                  uVar14 = uVar14 + 1 & 0xff;
                                } while (uVar14 < 0x18);
                              }
                              else {
                                *(undefined *)(iVar13 + 0x272) = 0;
                                remove_measures_item_from_list(0x17);
                              }
                            }
                            highlight_measures_menu_items();
                            tp_i2c_read_status();
                            cVar1 = *puVar4;
                            while (cVar1 != '\0') {
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                            }
                          }
                          else {
                            if (((uVar14 - 0x1a3 < 0x3c) && (0x19f < *(ushort *)(puVar4 + 4))) &&
                               (*(ushort *)(puVar4 + 4) < 0x1dc)) {
                              if (*puVar4 != '\0') {
                                if (*(char *)(iVar13 + 0x282) == '\0') {
                                  uVar14 = 0;
                                  *(undefined *)(iVar13 + 0x282) = 1;
                                  do {
                                    if (*(char *)(iVar5 + uVar14) == '\0') {
                                      *(undefined *)(iVar5 + uVar14) = 0x18;
                                      break;
                                    }
                                    uVar14 = uVar14 + 1 & 0xff;
                                  } while (uVar14 < 0x18);
                                }
                                else {
                                  *(undefined *)(iVar13 + 0x282) = 0;
                                  remove_measures_item_from_list(0x18);
                                }
                              }
                              highlight_measures_menu_items();
                              tp_i2c_read_status();
                              cVar1 = *puVar4;
                              while (cVar1 != '\0') {
                                tp_i2c_read_status();
                                cVar1 = *puVar4;
                              }
                            }
                          }
                        }
                      }
                      goto LAB_8001e7b0;
                    }
                  }
                } while (*puVar4 == '\0');
                FUN_8000a710();
                tp_i2c_read_status();
                cVar1 = *puVar4;
                while (cVar1 != '\0') {
                  tp_i2c_read_status();
                  cVar1 = *puVar4;
                }
              }
            }
          }
        }
      }
    }
  }
  puVar9 = PTR_DAT_8001f998;
  puVar8 = PTR_DAT_8001f994;
  puVar7 = PTR_DAT_8001f990;
  if (pcVar6[0x42] == '\0') {
    if (0x39 < *(ushort *)(puVar4 + 2) - 0x2e5) {
                    /* WARNING: Could not recover jumptable at 0x8001f868. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE_00)();
      return;
    }
    uVar3 = *(ushort *)(puVar4 + 4);
    if ((3 < uVar3) && (uVar3 < 0x39)) {
      cVar1 = *puVar4;
      while (cVar1 != '\0') {
        display_ctrl_button(1);
        tp_i2c_read_status();
        cVar1 = *puVar4;
      }
      display_ctrl_button(0);
      if (pcVar6[0x42] == '\0') {
        pcVar6[0x42] = '\x01';
      }
      else {
        pcVar6[0x42] = '\0';
      }
      display_right_menu();
      tp_i2c_read_status();
      if (*puVar4 != '\0') {
        do {
          tp_i2c_read_status();
        } while (*puVar4 != '\0');
                    /* WARNING: Could not recover jumptable at 0x8001f8f0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (*UNRECOVERED_JUMPTABLE_00)();
        return;
      }
                    /* WARNING: Could not recover jumptable at 0x8001f8d4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE_00)();
      return;
    }
    if ((0x3f < uVar3) && (uVar3 < 0x75)) {
      cVar1 = *puVar4;
      if (pcVar6[0x43] == '\0') {
        while (cVar1 != '\0') {
          display_run_stop_button(1);
          tp_i2c_read_status();
          cVar1 = *puVar4;
        }
        display_run_stop_button(0);
        if (pcVar6[0x3a] == '\0') {
          pcVar6[0x3a] = '\x01';
          *(ushort *)puVar7 = (ushort)(byte)pcVar6[3];
          *(ushort *)puVar8 = (ushort)(byte)pcVar6[0xf];
        }
        else {
          pcVar6[0x3a] = '\0';
          *(undefined2 *)PTR_DAT_800202ec = 0;
          *(undefined2 *)PTR_DAT_800202f0 = 400;
          *(undefined2 *)PTR_DAT_800202f4 = 0;
          *(undefined2 *)PTR_DAT_800202f8 = 400;
        }
        if ((pcVar6[0x21] == '\0') || (pcVar6[0x3a] != '\0')) {
          pcVar6[0x18] = '\x01';
          pcVar6[0x17] = '\x01';
        }
        else {
          pcVar6[0x36] = '\0';
          pcVar6[0x37] = '\x01';
        }
        display_run_stop_text((uint)(byte)pcVar6[0x3a]);
      }
      else {
        while (cVar1 != '\0') {
          display_page_up_button(1);
          tp_i2c_read_status();
          cVar1 = *puVar4;
        }
        display_page_up_button(0);
        if (*(short *)(puVar9 + 2) != 0) {
          *(short *)(puVar9 + 2) = *(short *)(puVar9 + 2) + -1;
          waveform_select_file();
        }
      }
      tp_i2c_read_status();
      if (*puVar4 != '\0') {
        do {
          tp_i2c_read_status();
        } while (*puVar4 != '\0');
                    /* WARNING: Could not recover jumptable at 0x8001f988. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (*UNRECOVERED_JUMPTABLE_00)();
        return;
      }
                    /* WARNING: Could not recover jumptable at 0x8001f96c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE_00)();
      return;
    }
    if ((0x7b < uVar3) && (uVar3 < 0xb1)) {
      cVar1 = *puVar4;
      if (pcVar6[0x43] == '\0') {
        while (cVar1 != '\0') {
          display_auto_set_button(1);
          tp_i2c_read_status();
          cVar1 = *puVar4;
        }
        display_auto_set_button(0);
        pcVar6[0x21] = '\0';
        set_fpga_trigger_mode();
        display_trigger_settings(0);
        perform_auto_set();
        display_ch1_settings(0);
        display_ch2_settings(0);
      }
      else {
        while (cVar1 != '\0') {
          display_page_down_button(1);
          tp_i2c_read_status();
          cVar1 = *puVar4;
        }
        display_page_down_button(0);
        if ((int)(uint)*(ushort *)(puVar9 + 2) < (int)(*(byte *)(DAT_800202fc + 0xc) - 1)) {
          *(ushort *)(puVar9 + 2) = *(ushort *)(puVar9 + 2) + 1;
          waveform_select_file();
        }
      }
      tp_i2c_read_status();
      if (*puVar4 != '\0') {
        do {
          tp_i2c_read_status();
        } while (*puVar4 != '\0');
                    /* WARNING: Could not recover jumptable at 0x8001fae0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (*UNRECOVERED_JUMPTABLE_00)();
        return;
      }
                    /* WARNING: Could not recover jumptable at 0x8001fac4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE_00)();
      return;
    }
    if ((0xb7 < uVar3) && (uVar3 < 0xed)) {
      cVar1 = *puVar4;
      while (cVar1 != '\0') {
        display_t_cursor_button(1);
        tp_i2c_read_status();
        cVar1 = *puVar4;
      }
      display_t_cursor_button(0);
      if (8 < (byte)pcVar6[10]) {
        if (*(char *)(iVar13 + 0x292) == '\0') {
          *(undefined *)(iVar13 + 0x292) = 1;
        }
        else {
          *(undefined *)(iVar13 + 0x292) = 0;
        }
      }
      tp_i2c_read_status();
      if (*puVar4 != '\0') {
        do {
          tp_i2c_read_status();
        } while (*puVar4 != '\0');
                    /* WARNING: Could not recover jumptable at 0x8001fbbc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (*UNRECOVERED_JUMPTABLE_00)();
        return;
      }
                    /* WARNING: Could not recover jumptable at 0x8001fba0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE_00)();
      return;
    }
    if ((0xf3 < uVar3) && (uVar3 < 0x129)) {
      cVar1 = *puVar4;
      while (cVar1 != '\0') {
        display_v_cursor_button(1);
        tp_i2c_read_status();
        cVar1 = *puVar4;
      }
      display_v_cursor_button(0);
      if (8 < (byte)pcVar6[10]) {
        if (*(char *)(iVar13 + 0x29a) == '\0') {
          *(undefined *)(iVar13 + 0x29a) = 1;
        }
        else {
          *(undefined *)(iVar13 + 0x29a) = 0;
        }
      }
      tp_i2c_read_status();
      if (*puVar4 != '\0') {
        do {
          tp_i2c_read_status();
        } while (*puVar4 != '\0');
                    /* WARNING: Could not recover jumptable at 0x8001fc48. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (*UNRECOVERED_JUMPTABLE_00)();
        return;
      }
                    /* WARNING: Could not recover jumptable at 0x8001fc2c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE_00)();
      return;
    }
    if ((0x16b < uVar3) && (uVar3 < 0x1a1)) {
      cVar1 = *puVar4;
      while (cVar1 != '\0') {
        display_save_pic_button(1);
        tp_i2c_read_status();
        cVar1 = *puVar4;
      }
      display_save_pic_button(0);

      FUN_80025f2c();

      if ((pcVar6[0x43] != '\0') && (*PTR_DAT_80020300 == '\x01'))
      {
        FUN_8002c8e4();

        some_sd_card_stuff_3();
      }

      tp_i2c_read_status();
      if (*puVar4 != '\0') {
        do {
          tp_i2c_read_status();
        } while (*puVar4 != '\0');

        return;
      }

      return;
    }
    if (uVar3 < 0x1a8)
    {
      return;
    }

    if (uVar3 < 0x1dd) {
      cVar1 = *puVar4;
      if (pcVar6[0x43] == '\0') {
        while (cVar1 != '\0') {
          display_save_wave_button(1);
          tp_i2c_read_status();
          cVar1 = *puVar4;
        }
        display_save_wave_button(0);
        FUN_80025c38();
      }
      else {
        while (cVar1 != '\0') {
          display_delete_wave_button(1);
          tp_i2c_read_status();
          cVar1 = *puVar4;
        }
        display_delete_wave_button(0);
        iVar13 = FUN_8002b8e8();
        if (iVar13 == 0) {
          waveform_select_file();
        }
        else {
          iVar13 = FUN_8002ca34();
          waveform_select_file();
          if (iVar13 != 0) {
            pcVar6[0x43] = '\0';
          }
        }
      }
      tp_i2c_read_status();
      if (*puVar4 != '\0') {
        do {
          tp_i2c_read_status();
        } while (*puVar4 != '\0');
                    /* WARNING: Could not recover jumptable at 0x8001fdc0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (*UNRECOVERED_JUMPTABLE_00)();
        return;
      }
                    /* WARNING: Could not recover jumptable at 0x8001fda4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE_00)();
      return;
    }
                    /* WARNING: Could not recover jumptable at 0x8001fd00. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE_00)();
    return;
  }
  if (pcVar6[0x42] == '\0') {
                    /* WARNING: Could not recover jumptable at 0x8001f7a8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE_00)();
    return;
  }
  if (0x39 < *(ushort *)(puVar4 + 2) - 0x2e5) {
                    /* WARNING: Could not recover jumptable at 0x8001f7c4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE_00)();
    return;
  }
  uVar12 = (uint)*(ushort *)(puVar4 + 4);
  if ((3 < uVar12) && (uVar12 < 0x39)) {
    cVar1 = *puVar4;
    while (cVar1 != '\0') {
      display_ctrl_button(1);
      tp_i2c_read_status();
      cVar1 = *puVar4;
    }
    display_ctrl_button(0);
    if (pcVar6[0x42] == '\0') {
      pcVar6[0x42] = '\x01';
    }
    else {
      pcVar6[0x42] = '\0';
    }
    display_right_menu();
    tp_i2c_read_status();
    if (*puVar4 != '\0') {
      do {
        tp_i2c_read_status();
      } while (*puVar4 != '\0');
                    /* WARNING: Could not recover jumptable at 0x8001f84c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE_00)();
      return;
    }
                    /* WARNING: Could not recover jumptable at 0x8001f830. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE_00)();
    return;
  }
  if ((0x4e < uVar12) && (uVar12 < 0x8c)) {
    cVar1 = *puVar4;
    while (cVar1 != '\0') {
      display_ch1_sensitivity_control(0,1);
      tp_i2c_read_status();
      cVar1 = *puVar4;
    }
    display_ch1_sensitivity_control(0,0);
    if (*pcVar6 != '\0') {
      bVar2 = pcVar6[0x3a];
      bVar17 = bVar2 != 0;
      if (bVar17) {
        bVar2 = pcVar6[10];
      }
      if (((!bVar17 || 8 < bVar2) && ((byte)pcVar6[3] < 6)) &&
         ((pcVar6[0x3a] == '\0' ||
          (((ushort)(byte)pcVar6[3] <= *(ushort *)puVar7 ||
           (((ushort)(byte)pcVar6[3] - *(ushort *)puVar7 & 0xff) < 2)))))) {
        pcVar6[3] = pcVar6[3] + '\x01';
        display_ch1_settings(0);
        if (pcVar6[0x43] == '\0') {
          set_fpga_channel1_voltperdiv();
          set_fpga_channel1_offset();
          delay_2(0x3c);
        }
      }
    }
    tp_i2c_read_status();
    if (*puVar4 != '\0') {
      do {
        tp_i2c_read_status();
      } while (*puVar4 != '\0');
                    /* WARNING: Could not recover jumptable at 0x8001fec4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE_00)();
      return;
    }
                    /* WARNING: Could not recover jumptable at 0x8001fea8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE_00)();
    return;
  }
  if ((0xa3 < uVar12) && (uVar12 < 0xdf)) {
    cVar1 = *puVar4;
    while (cVar1 != '\0') {
      display_ch1_sensitivity_control(1,1);
      tp_i2c_read_status();
      cVar1 = *puVar4;
    }
    display_ch1_sensitivity_control(1,0);
    if (*pcVar6 != '\0') {
      bVar2 = pcVar6[0x3a];
      bVar17 = bVar2 != 0;
      if (bVar17) {
        bVar2 = pcVar6[10];
      }
      if (((!bVar17 || 8 < bVar2) && (pcVar6[3] != '\0')) &&
         ((pcVar6[0x3a] == '\0' ||
          ((*(ushort *)puVar7 <= (ushort)(byte)pcVar6[3] ||
           ((*(ushort *)puVar7 - (ushort)(byte)pcVar6[3] & 0xff) < 2)))))) {
        pcVar6[3] = pcVar6[3] + -1;
        display_ch1_settings(0);
        if (pcVar6[0x43] == '\0') {
          set_fpga_channel1_voltperdiv();
          set_fpga_channel1_offset();
          delay_2(0x3c);
        }
      }
    }
    tp_i2c_read_status();
    if (*puVar4 != '\0') {
      do {
        tp_i2c_read_status();
      } while (*puVar4 != '\0');
                    /* WARNING: Could not recover jumptable at 0x8001ffc8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE_00)();
      return;
    }
                    /* WARNING: Could not recover jumptable at 0x8001ffac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE_00)();
    return;
  }
  if (DAT_80020304 < uVar12 && uVar12 < 0x140) {
    cVar1 = *puVar4;
    while (cVar1 != '\0') {
      display_ch2_sensitivity_control(0,1);
      tp_i2c_read_status();
      cVar1 = *puVar4;
    }
    display_ch2_sensitivity_control(0,0);
    if (pcVar6[0xc] != '\0') {
      bVar2 = pcVar6[0x3a];
      bVar17 = bVar2 != 0;
      if (bVar17) {
        bVar2 = pcVar6[10];
      }
      if (((!bVar17 || 8 < bVar2) && ((byte)pcVar6[0xf] < 6)) &&
         ((pcVar6[0x3a] == '\0' ||
          (((ushort)(byte)pcVar6[0xf] <= *(ushort *)puVar8 ||
           (((ushort)(byte)pcVar6[0xf] - *(ushort *)puVar8 & 0xff) < 2)))))) {
        pcVar6[0xf] = pcVar6[0xf] + '\x01';
        display_ch2_settings(0);
        if (pcVar6[0x43] == '\0') {
          set_fpga_channel2_voltperdiv();
          set_fpga_channel2_offset();
          delay_2(0x3c);
        }
      }
    }
    tp_i2c_read_status();
    if (*puVar4 != '\0') {
      do {
        tp_i2c_read_status();
      } while (*puVar4 != '\0');
                    /* WARNING: Could not recover jumptable at 0x800200cc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE_00)();
      return;
    }
                    /* WARNING: Could not recover jumptable at 0x800200b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE_00)();
    return;
  }
  if (uVar12 < 0x158) {
                    /* WARNING: Could not recover jumptable at 0x800200dc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE_00)();
    return;
  }
  if (uVar12 < DAT_80020308) {
    cVar1 = *puVar4;
    while (cVar1 != '\0') {
      display_ch2_sensitivity_control(1,1);
      tp_i2c_read_status();
      cVar1 = *puVar4;
    }
    display_ch2_sensitivity_control(1,0);
    if (pcVar6[0xc] != '\0') {
      bVar2 = pcVar6[0x3a];
      bVar17 = bVar2 != 0;
      if (bVar17) {
        bVar2 = pcVar6[10];
      }
      if (((!bVar17 || 8 < bVar2) && (pcVar6[0xf] != '\0')) &&
         ((pcVar6[0x3a] == '\0' ||
          ((*(ushort *)puVar8 <= (ushort)(byte)pcVar6[0xf] ||
           ((*(ushort *)puVar8 - (ushort)(byte)pcVar6[0xf] & 0xff) < 2)))))) {
        pcVar6[0xf] = pcVar6[0xf] + -1;
        display_ch2_settings(0);
        if (pcVar6[0x43] == '\0') {
          set_fpga_channel2_voltperdiv();
          set_fpga_channel2_offset();
          delay_2(0x3c);
        }
      }
    }
    tp_i2c_read_status();
    if (*puVar4 != '\0') {
      do {
        tp_i2c_read_status();
      } while (*puVar4 != '\0');
                    /* WARNING: Could not recover jumptable at 0x800201dc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE_00)();
      return;
    }
                    /* WARNING: Could not recover jumptable at 0x800201c0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE_00)();
    return;
  }
  if (uVar12 < 0x1a8) {
                    /* WARNING: Could not recover jumptable at 0x800201ec. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE_00)();
    return;
  }
  if (0x1dc < uVar12) {
                    /* WARNING: Could not recover jumptable at 0x800201fc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE_00)();
    return;
  }
  cVar1 = *puVar4;
  if (pcVar6[0x43] == '\0') {
    while (cVar1 != '\0') {
      display_50_trigger_button(1);
      tp_i2c_read_status();
      cVar1 = *puVar4;
    }
    display_50_trigger_button(0);
    if (pcVar6[0x3a] == '\0') {
      FUN_80029314();
    }
    tp_i2c_read_status();
    if (*puVar4 != '\0') {
      do {
        tp_i2c_read_status();
      } while (*puVar4 != '\0');
                    /* WARNING: Could not recover jumptable at 0x800202e8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE_00)();
      return;
    }
                    /* WARNING: Could not recover jumptable at 0x800202cc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE_00)();
    return;
  }
  while (cVar1 != '\0') {
    display_show_grid_button(1);
    tp_i2c_read_status();
    cVar1 = *puVar4;
  }
  display_show_grid_button(0);
  if (*(char *)(DAT_8002030c + 3) == '\x14') {
    *(undefined *)(DAT_8002030c + 3) = 0;
  }
  else {
    *(undefined *)(DAT_8002030c + 3) = 0x14;
  }
  tp_i2c_read_status();
  if (*puVar4 != '\0') {
    do {
      tp_i2c_read_status();
    } while (*puVar4 != '\0');
                    /* WARNING: Could not recover jumptable at 0x80020280. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE_00)();
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x80020264. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE_00)();
  return;
}


