
int check_delete_confirmation(void)

{
  char cVar1;
  undefined *puVar2;
  uint uVar3;
  bool bVar4;
  bool bVar5;
  
  tp_i2c_read_status();
  puVar2 = PTR_DAT_80023098;
  if (*(ushort *)(PTR_DAT_80023098 + 2) - 0x11e < 0x4a) {
    uVar3 = (uint)*(ushort *)(PTR_DAT_80023098 + 4);
    bVar5 = 0xe4 < uVar3;
    bVar4 = uVar3 == 0xe5;
    if (0xe5 < uVar3) {
      bVar5 = uVar3 <= DAT_8002309c;
      bVar4 = DAT_8002309c == uVar3;
    }
    if (bVar5 && !bVar4) {
      cVar1 = *PTR_DAT_80023098;
      while (cVar1 != '\0') {
        tp_i2c_read_status();
        cVar1 = *puVar2;
      }
      goto LAB_8002308c;
    }
  }
  if (*(ushort *)(PTR_DAT_80023098 + 2) - 0x173 < 0x4a) {
    uVar3 = (uint)*(ushort *)(PTR_DAT_80023098 + 4);
    bVar5 = 0xe4 < uVar3;
    bVar4 = uVar3 == 0xe5;
    if (0xe5 < uVar3) {
      bVar5 = uVar3 <= DAT_8002309c;
      bVar4 = DAT_8002309c == uVar3;
    }
    if (bVar5 && !bVar4) {
      cVar1 = *PTR_DAT_80023098;
      while (cVar1 != '\0') {
        tp_i2c_read_status();
        cVar1 = *puVar2;
      }
      wait_for_touch_release();
      return 1;
    }
  }
  if (*PTR_DAT_80023098 == '\0') {
    return 2;
  }
  do {
    tp_i2c_read_status();
  } while (*puVar2 != '\0');
LAB_8002308c:
  wait_for_touch_release();
  return 0;
}


