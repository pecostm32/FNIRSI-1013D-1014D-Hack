
//They have a buffer in memory starting from 0x8035A97E
//first 30 bytes are reserved for house keeping data
//then 2000 bytes for 1000 short file numbers
//then 15000 bytes for file names

//void FUN_8000b2ac(void)
void setup_filename_list(void)
{
  ushort uVar1;
  longlong lVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  char cVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  undefined uVar10;
  uint uVar11;
  int iVar12;
  
  iVar5 = DAT_8000b4c0;          //0x8035A97E   start of system file buffer
  iVar4 = DAT_8000b4bc;          //0x66666667
  cVar6 = *PTR_DAT_8000b4b8;     //0x80192ee2   type of view (0 is picture, 1 is wave)
  uVar9 = 0;

  //Walk through the system file list
  do
  {
    uVar1 = *(ushort *)(iVar5 + uVar9 * 2 + 0x1e);   //First index of system file list

    uVar7 = (uint)uVar1;

    if (uVar7 == 0)       //Not set then done
      break;

    cVar3 = (char)uVar1;

    //Less then 10
    if (uVar7 < 10)
    {
      iVar8 = uVar9 * 0xf + iVar5;    //15 byte space reserved per file starting from 0x8035A97E + 0x7EE (2030)

      *(undefined *)(iVar8 + 0x7ee) = 0x2f;       //'/'
      *(char *)(iVar8 + 0x7ef) = cVar3 + '0';     //'1' - '9'
      *(undefined *)(iVar8 + 0x7f0) = 0x2e;       //'.'

      if (cVar6 == '\0')                           //Based on the type set the extension
      {
        *(undefined *)(iVar8 + 0x7f1) = 0x62;
        uVar10 = 0x70;
        *(undefined *)(iVar8 + 0x7f2) = 0x6d;
      }
      else
      {
        *(undefined *)(iVar8 + 0x7f1) = 0x77;
        uVar10 = 0x76;
        *(undefined *)(iVar8 + 0x7f2) = 0x61;
      }

      *(undefined *)(iVar8 + 0x7f3) = uVar10;
      *(undefined *)(iVar8 + 0x7f4) = 0;
    }
    else
    {
      if (uVar7 < 100) {
        uVar11 = uVar7 * DAT_8000b4c4;
        iVar8 = uVar9 * 0xf + iVar5;
        *(undefined *)(iVar8 + 0x7ee) = 0x2f;
        *(char *)(iVar8 + 0x7ef) = (char)(uVar11 >> 0x13) + '0';
        *(char *)(iVar8 + 0x7f0) = cVar3 + (char)(uint)((ulonglong)uVar7 * (ulonglong)DAT_8000b4c8 >> 0x23) * -10 + '0';
        *(undefined *)(iVar8 + 0x7f1) = 0x2e;
        if (cVar6 == '\0') {
          *(undefined *)(iVar8 + 0x7f2) = 0x62;
          uVar10 = 0x70;
          *(undefined *)(iVar8 + 0x7f3) = 0x6d;
        }
        else {
          *(undefined *)(iVar8 + 0x7f2) = 0x77;
          uVar10 = 0x76;
          *(undefined *)(iVar8 + 0x7f3) = 0x61;
        }
        *(undefined *)(iVar8 + 0x7f4) = uVar10;
        *(undefined *)(iVar8 + 0x7f5) = 0;
      }
      else {
        if (uVar7 < 1000) {
          iVar12 = uVar7 * DAT_8000b4cc;
          iVar8 = uVar9 * 0xf + iVar5;
          *(undefined *)(iVar8 + 0x7ee) = 0x2f;
          *(char *)(iVar8 + 0x7ef) = (char)(iVar12 + 0xa3d7U >> 0x16) + '0';
          lVar2 = (longlong)iVar4 * (longlong)(int)(uVar7 + (uint)((ulonglong)uVar7 * (ulonglong)DAT_8000b4d0 >> 0x25) * -100);
          *(char *)(iVar8 + 0x7f0) = ((char)(int)(lVar2 >> 0x22) - (char)(lVar2 >> 0x3f)) + '0';
          *(char *)(iVar8 + 0x7f1) = cVar3 + (char)(uint)((ulonglong)uVar7 * (ulonglong)DAT_8000b4c8 >> 0x23) * -10 + '0';
          *(undefined *)(iVar8 + 0x7f2) = 0x2e;
          if (cVar6 == '\0') {
            *(undefined *)(iVar8 + 0x7f3) = 0x62;
            uVar10 = 0x70;
            *(undefined *)(iVar8 + 0x7f4) = 0x6d;
          }
          else {
            *(undefined *)(iVar8 + 0x7f3) = 0x77;
            uVar10 = 0x76;
            *(undefined *)(iVar8 + 0x7f4) = 0x61;
          }
          *(undefined *)(iVar8 + 0x7f5) = uVar10;
          *(undefined *)(iVar8 + 0x7f6) = 0;
        }
      }
    }

    uVar9 = uVar9 + 1 & 0xfffeffff;
  } while (uVar9 < 1000);

  //Either 1000 or the first index in the system file set to 0
  uVar7 = uVar9 & 0xff;

  //0x8035A98A
  *(char *)(iVar5 + 0xc) = (char)uVar7;

  if ((uVar9 & 0xf) == 0)
  {
    cVar6 = (char)(uVar7 >> 4);
  }
  else
  {
    cVar6 = (char)(uVar7 >> 4) + '\x01';
  }

  *(char *)(iVar5 + 0xb) = cVar6;
  return;
}


