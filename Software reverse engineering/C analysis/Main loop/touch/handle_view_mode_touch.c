
// WARNING: Unknown calling convention yet parameter storage is locked

int handle_view_mode_touch(void)

{
  char cVar1;
  ushort uVar2;
  undefined *puVar3;
  char *pcVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint unaff_r8;
  bool bVar10;
  bool bVar11;
  
  tp_i2c_read_status();
  pcVar4 = DAT_80022bbc;
  puVar3 = PTR_DAT_80022bb8;
  uVar5 = (uint)*(ushort *)(PTR_DAT_80022bb8 + 2);
  if ((uVar5 - 0x2db < 0x45) && (uVar2 = *(ushort *)(PTR_DAT_80022bb8 + 4), uVar2 != 0)) {
    if (uVar2 < 0x50) {
      cVar1 = *PTR_DAT_80022bb8;
      while (cVar1 != '\0') {
        tp_i2c_read_status();
        cVar1 = *puVar3;
      }
      FUN_8002b0f4();             //wait for touch release
      return 1;
    }
    if (0x50 < uVar2) {
      if (uVar2 < 0xa0) {
        cVar1 = *PTR_DAT_80022bb8;
        while (cVar1 != '\0') {
          tp_i2c_read_status();
          cVar1 = *puVar3;
        }
        FUN_8002b0f4();
        return 2;
      }
      if (0xa0 < uVar2) {
        if (uVar2 < 0xf0) {
          cVar1 = *PTR_DAT_80022bb8;
          while (cVar1 != '\0') {
            tp_i2c_read_status();
            cVar1 = *puVar3;
          }
          FUN_8002b0f4();
          return 3;
        }
        if (0xf0 < uVar2) {
          if (uVar2 < 0x140) {
            cVar1 = *PTR_DAT_80022bb8;
            while (cVar1 != '\0') {
              tp_i2c_read_status();
              cVar1 = *puVar3;
            }
            FUN_8002b0f4();
            return 4;
          }
          if (0x140 < uVar2) {
            bVar10 = 399 < uVar2;
            if (!bVar10) {
              cVar1 = *PTR_DAT_80022bb8;
              while (cVar1 != '\0') {
                tp_i2c_read_status();
                cVar1 = *puVar3;
              }
              FUN_8002b0f4();
              return 5;
            }
            if (uVar2 != 400) {
              bVar10 = 0x1df < uVar2;
            }
            if (!bVar10) {
              cVar1 = *PTR_DAT_80022bb8;
              while (cVar1 != '\0') {
                tp_i2c_read_status();
                cVar1 = *puVar3;
              }
              FUN_8002b0f4();
              return 6;
            }
          }
        }
      }
    }
  }
  uVar8 = uVar5 - 1;
  if ((uVar8 < 0xb3) && (*(ushort *)(PTR_DAT_80022bb8 + 4) != 0 && *(ushort *)(PTR_DAT_80022bb8 + 4) < 0x75)) {
    cVar1 = *PTR_DAT_80022bb8;
    while (cVar1 != '\0') {
      tp_i2c_read_status();
      cVar1 = *puVar3;
    }
    FUN_8002b0f4();
    if ((ushort)((ushort)(byte)pcVar4[10] * 0x10 - 0x10) < (ushort)(byte)pcVar4[0xc]) {
      if (*pcVar4 != '\0') {
        if (pcVar4[0xd] == '\0') {
          pcVar4[0xd] = '\x01';
        }
        else {
          pcVar4[0xd] = '\0';
        }
      }
      return 7;
    }
  }
  else {
    uVar7 = uVar5 - 0xb7;
    if ((uVar7 < 0xb3) && (*(ushort *)(PTR_DAT_80022bb8 + 4) != 0 && *(ushort *)(PTR_DAT_80022bb8 + 4) < 0x75)) {
      cVar1 = *PTR_DAT_80022bb8;
      while (cVar1 != '\0') {
        tp_i2c_read_status();
        cVar1 = *puVar3;
      }
      FUN_8002b0f4();
      if ((ushort)((ushort)(byte)pcVar4[10] * 0x10 - 0xf) < (ushort)(byte)pcVar4[0xc]) {
        if (*pcVar4 != '\0') {
          if (pcVar4[0xe] == '\0') {
            pcVar4[0xe] = '\x01';
          }
          else {
            pcVar4[0xe] = '\0';
          }
        }
        return 8;
      }
    }
    else {
      uVar6 = uVar5 - 0x16d;
      if ((uVar6 < 0xb3) && (*(ushort *)(PTR_DAT_80022bb8 + 4) != 0 && *(ushort *)(PTR_DAT_80022bb8 + 4) < 0x75)) {
        cVar1 = *PTR_DAT_80022bb8;
        while (cVar1 != '\0') {
          tp_i2c_read_status();
          cVar1 = *puVar3;
        }
        FUN_8002b0f4();
        if ((ushort)((ushort)(byte)pcVar4[10] * 0x10 - 0xe) < (ushort)(byte)pcVar4[0xc]) {
          if (*pcVar4 != '\0') {
            if (pcVar4[0xf] == '\0') {
              pcVar4[0xf] = '\x01';
            }
            else {
              pcVar4[0xf] = '\0';
            }
          }
          return 9;
        }
      }
      else {
        uVar5 = uVar5 - 0x223;
        if ((uVar5 < 0xb3) && (*(ushort *)(PTR_DAT_80022bb8 + 4) != 0 && *(ushort *)(PTR_DAT_80022bb8 + 4) < 0x75)) {
          cVar1 = *PTR_DAT_80022bb8;
          while (cVar1 != '\0') {
            tp_i2c_read_status();
            cVar1 = *puVar3;
          }
          FUN_8002b0f4();
          if ((ushort)((ushort)(byte)pcVar4[10] * 0x10 - 0xd) < (ushort)(byte)pcVar4[0xc]) {
            if (*pcVar4 != '\0') {
              if (pcVar4[0x10] == '\0') {
                pcVar4[0x10] = '\x01';
              }
              else {
                pcVar4[0x10] = '\0';
              }
            }
            return 10;
          }
        }
        else {
          if (((uVar8 < 0xb3) && (0x77 < *(ushort *)(PTR_DAT_80022bb8 + 4))) && (*(ushort *)(PTR_DAT_80022bb8 + 4) < 0xec)) {
            cVar1 = *PTR_DAT_80022bb8;
            while (cVar1 != '\0') {
              tp_i2c_read_status();
              cVar1 = *puVar3;
            }
            FUN_8002b0f4();
            if ((ushort)((ushort)(byte)pcVar4[10] * 0x10 - 0xc) < (ushort)(byte)pcVar4[0xc]) {
              if (*pcVar4 != '\0') {
                if (pcVar4[0x11] == '\0') {
                  pcVar4[0x11] = '\x01';
                }
                else {
                  pcVar4[0x11] = '\0';
                }
              }
              return 0xb;
            }
          }
          else {
            if (((uVar7 < 0xb3) && (0x77 < *(ushort *)(PTR_DAT_80022bb8 + 4))) && (*(ushort *)(PTR_DAT_80022bb8 + 4) < 0xec)) {
              cVar1 = *PTR_DAT_80022bb8;
              while (cVar1 != '\0') {
                tp_i2c_read_status();
                cVar1 = *puVar3;
              }
              FUN_8002b0f4();
              if ((ushort)((ushort)(byte)pcVar4[10] * 0x10 - 0xb) < (ushort)(byte)pcVar4[0xc]) {
                if (*pcVar4 != '\0') {
                  if (pcVar4[0x12] == '\0') {
                    pcVar4[0x12] = '\x01';
                  }
                  else {
                    pcVar4[0x12] = '\0';
                  }
                }
                return 0xc;
              }
            }
            else {
              if (((uVar6 < 0xb3) && (0x77 < *(ushort *)(PTR_DAT_80022bb8 + 4))) && (*(ushort *)(PTR_DAT_80022bb8 + 4) < 0xec)) {
                cVar1 = *PTR_DAT_80022bb8;
                while (cVar1 != '\0') {
                  tp_i2c_read_status();
                  cVar1 = *puVar3;
                }
                FUN_8002b0f4();
                if ((ushort)((ushort)(byte)pcVar4[10] * 0x10 - 10) < (ushort)(byte)pcVar4[0xc]) {
                  if (*pcVar4 != '\0') {
                    if (pcVar4[0x13] == '\0') {
                      pcVar4[0x13] = '\x01';
                    }
                    else {
                      pcVar4[0x13] = '\0';
                    }
                  }
                  return 0xd;
                }
              }
              else {
                if (((uVar5 < 0xb3) && (0x77 < *(ushort *)(PTR_DAT_80022bb8 + 4))) && (*(ushort *)(PTR_DAT_80022bb8 + 4) < 0xec)) {
                  cVar1 = *PTR_DAT_80022bb8;
                  while (cVar1 != '\0') {
                    tp_i2c_read_status();
                    cVar1 = *puVar3;
                  }
                  FUN_8002b0f4();
                  if ((ushort)((ushort)(byte)pcVar4[10] * 0x10 - 9) < (ushort)(byte)pcVar4[0xc]) {
                    if (*pcVar4 != '\0') {
                      if (pcVar4[0x14] == '\0') {
                        pcVar4[0x14] = '\x01';
                      }
                      else {
                        pcVar4[0x14] = '\0';
                      }
                    }
                    return 0xe;
                  }
                }
                else {
                  if (uVar8 < 0xb3) {
                    unaff_r8 = (uint)*(ushort *)(PTR_DAT_80022bb8 + 4);
                    bVar11 = 0xed < unaff_r8;
                    bVar10 = unaff_r8 == 0xee;
                    if (0xee < unaff_r8) {
                      bVar11 = unaff_r8 <= DAT_80022bc0;
                      bVar10 = DAT_80022bc0 == unaff_r8;
                    }
                    if (bVar11 && !bVar10) {
                      cVar1 = *PTR_DAT_80022bb8;
                      while (cVar1 != '\0') {
                        tp_i2c_read_status();
                        cVar1 = *puVar3;
                      }
                      FUN_8002b0f4();
                      if ((ushort)(byte)pcVar4[0xc] <= (ushort)((ushort)(byte)pcVar4[10] * 0x10 - 8)) {
                        return 0;
                      }
                      if (*pcVar4 != '\0') {
                        if (pcVar4[0x15] == '\0') {
                          pcVar4[0x15] = '\x01';
                        }
                        else {
                          pcVar4[0x15] = '\0';
                        }
                      }
                      return 0xf;
                    }
                  }
                  if (uVar7 < 0xb3) {
                    unaff_r8 = (uint)*(ushort *)(PTR_DAT_80022bb8 + 4);
                    bVar11 = 0xed < unaff_r8;
                    bVar10 = unaff_r8 == 0xee;
                    if (0xee < unaff_r8) {
                      bVar11 = unaff_r8 <= DAT_80022bc0;
                      bVar10 = DAT_80022bc0 == unaff_r8;
                    }
                    if (bVar11 && !bVar10) {
                      cVar1 = *PTR_DAT_80022bb8;
                      while (cVar1 != '\0') {
                        tp_i2c_read_status();
                        cVar1 = *puVar3;
                      }
                      FUN_8002b0f4();
                      if ((ushort)(byte)pcVar4[0xc] <= (ushort)((ushort)(byte)pcVar4[10] * 0x10 - 7)) {
                        return 0;
                      }
                      if (*pcVar4 != '\0') {
                        if (pcVar4[0x16] == '\0') {
                          pcVar4[0x16] = '\x01';
                        }
                        else {
                          pcVar4[0x16] = '\0';
                        }
                      }
                      return 0x10;
                    }
                  }
                  if (uVar6 < 0xb3) {
                    unaff_r8 = (uint)*(ushort *)(PTR_DAT_80022bb8 + 4);
                    bVar11 = 0xed < unaff_r8;
                    bVar10 = unaff_r8 == 0xee;
                    if (0xee < unaff_r8) {
                      bVar11 = unaff_r8 <= DAT_80022bc0;
                      bVar10 = DAT_80022bc0 == unaff_r8;
                    }
                    if (bVar11 && !bVar10) {
                      cVar1 = *PTR_DAT_80022bb8;
                      while (cVar1 != '\0') {
                        tp_i2c_read_status();
                        cVar1 = *puVar3;
                      }
                      FUN_8002b0f4();
                      if ((ushort)(byte)pcVar4[0xc] <= (ushort)((ushort)(byte)pcVar4[10] * 0x10 - 6)) {
                        return 0;
                      }
                      if (*pcVar4 != '\0') {
                        if (pcVar4[0x17] == '\0') {
                          pcVar4[0x17] = '\x01';
                        }
                        else {
                          pcVar4[0x17] = '\0';
                        }
                      }
                      return 0x11;
                    }
                  }
                  if (uVar5 < 0xb3) {
                    unaff_r8 = (uint)*(ushort *)(PTR_DAT_80022bb8 + 4);
                    bVar11 = 0xed < unaff_r8;
                    bVar10 = unaff_r8 == 0xee;
                    if (0xee < unaff_r8) {
                      bVar11 = unaff_r8 <= DAT_80022bc0;
                      bVar10 = DAT_80022bc0 == unaff_r8;
                    }
                    if (bVar11 && !bVar10) {
                      cVar1 = *PTR_DAT_80022bb8;
                      while (cVar1 != '\0') {
                        tp_i2c_read_status();
                        cVar1 = *puVar3;
                      }
                      FUN_8002b0f4();
                      if ((ushort)(byte)pcVar4[0xc] <= (ushort)((ushort)(byte)pcVar4[10] * 0x10 - 5)) {
                        return 0;
                      }
                      if (*pcVar4 != '\0') {
                        if (pcVar4[0x18] == '\0') {
                          pcVar4[0x18] = '\x01';
                        }
                        else {
                          pcVar4[0x18] = '\0';
                        }
                      }
                      return 0x12;
                    }
                  }
                  if (0xb2 >= uVar8) {
                    unaff_r8 = (uint)*(ushort *)(PTR_DAT_80022bb8 + 4);
                  }
                  uVar9 = DAT_80022bc4 + 0x75;
                  if ((0xb2 < uVar8 || unaff_r8 <= DAT_80022bc4) || uVar9 <= unaff_r8) {
                    bVar10 = 0xb2 < uVar7;
                    if (!bVar10) {
                      uVar7 = (uint)*(ushort *)(PTR_DAT_80022bb8 + 4);
                    }
                    if ((bVar10 || uVar7 <= DAT_80022bc4) || uVar9 <= uVar7) {
                      bVar10 = 0xb2 < uVar6;
                      if (!bVar10) {
                        uVar6 = (uint)*(ushort *)(PTR_DAT_80022bb8 + 4);
                      }
                      if ((bVar10 || uVar6 <= DAT_80022bc4) || uVar9 <= uVar6) {
                        bVar10 = uVar5 < 0xb3;
                        if (bVar10) {
                          uVar5 = (uint)*(ushort *)(PTR_DAT_80022bb8 + 4);
                        }
                        if ((bVar10 && DAT_80022bc4 < uVar5) && uVar5 < uVar9) {
                          cVar1 = *PTR_DAT_80022bb8;
                          while (cVar1 != '\0') {
                            tp_i2c_read_status();
                            cVar1 = *puVar3;
                          }
                          FUN_8002b0f4();
                          if ((ushort)((ushort)(byte)pcVar4[10] * 0x10 - 1) < (ushort)(byte)pcVar4[0xc]) {
                            if (*pcVar4 != '\0') {
                              if (pcVar4[0x1c] == '\0') {
                                pcVar4[0x1c] = '\x01';
                              }
                              else {
                                pcVar4[0x1c] = '\0';
                              }
                            }
                            return 0x16;
                          }
                        }
                      }
                      else {
                        cVar1 = *PTR_DAT_80022bb8;
                        while (cVar1 != '\0') {
                          tp_i2c_read_status();
                          cVar1 = *puVar3;
                        }
                        FUN_8002b0f4();
                        if ((ushort)((ushort)(byte)pcVar4[10] * 0x10 - 2) < (ushort)(byte)pcVar4[0xc]) {
                          if (*pcVar4 != '\0') {
                            if (pcVar4[0x1b] == '\0') {
                              pcVar4[0x1b] = '\x01';
                            }
                            else {
                              pcVar4[0x1b] = '\0';
                            }
                          }
                          return 0x15;
                        }
                      }
                    }
                    else {
                      cVar1 = *PTR_DAT_80022bb8;
                      while (cVar1 != '\0') {
                        tp_i2c_read_status();
                        cVar1 = *puVar3;
                      }
                      FUN_8002b0f4();
                      if ((ushort)((ushort)(byte)pcVar4[10] * 0x10 - 3) < (ushort)(byte)pcVar4[0xc]) {
                        if (*pcVar4 != '\0') {
                          if (pcVar4[0x1a] == '\0') {
                            pcVar4[0x1a] = '\x01';
                          }
                          else {
                            pcVar4[0x1a] = '\0';
                          }
                        }
                        return 0x14;
                      }
                    }
                  }
                  else {
                    cVar1 = *PTR_DAT_80022bb8;
                    while (cVar1 != '\0') {
                      tp_i2c_read_status();
                      cVar1 = *puVar3;
                    }
                    FUN_8002b0f4();
                    if ((ushort)((ushort)(byte)pcVar4[10] * 0x10 - 4) < (ushort)(byte)pcVar4[0xc]) {
                      if (*pcVar4 != '\0') {
                        if (pcVar4[0x19] == '\0') {
                          pcVar4[0x19] = '\x01';
                        }
                        else {
                          pcVar4[0x19] = '\0';
                        }
                      }
                      return 0x13;
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
  return 0;
}


