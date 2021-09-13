undefined4 disk_ioctl(uint drive,uint cmd,void *buff)

{
  switch(drive)
  {
  case 0:
    if (cmd == 0) {
      return 0;
    }
    if (cmd == 1) {
      *(undefined4 *)buff = *(undefined4 *)(DAT_80033270 + 4);
      return 0;
    }
    break;

  case 1:
    if (cmd == 0) {
      return 0;
    }
    if (cmd == 1) {
      *(undefined4 *)buff = 0x40000;
      return 0;
    }
    break;

  case 2:
    if (cmd == 0) {
      return 0;
    }
    if (cmd == 1) {
      return 1;
    }
    break;

  default:
    goto switchD_800331a4_caseD_3;
  }

  if (cmd == 2)
  {
    *(undefined2 *)buff = 0x200;
    return 0;
  }

  if (cmd == 3)
  {
    *(undefined4 *)buff = 0x200;
    return 0;
  }

switchD_800331a4_caseD_3:
  return 4;
}

