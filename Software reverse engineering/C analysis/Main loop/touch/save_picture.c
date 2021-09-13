
//Save a picture


void save_picture(void)

{
  uint uVar1;
  undefined uVar2;
  undefined2 uVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  undefined2 *puVar7;
  uint uVar8;
  undefined2 *puVar9;
  uint uVar10;
  undefined2 uVar11;
  uint uVar12;
  undefined auStack608 [552];
  char local_38;
  char local_37;
  char local_36;
  char local_35;
  undefined local_34;
  undefined local_33;
  undefined local_32;
  undefined local_31;
  undefined local_30;

  //Need to save this one to be able to return to the previous view mode. It is possible to save a picture when in waveform view mode!!!  
  uVar2 = *PTR_DAT_80026194;   //0x80192ee2 type of view selected  (viewtype in my code) 0 is for picture view and 1 for waveform view

  local_38 = '/';
  local_34 = 0x6d;  //m
  local_36 = '.';
  local_33 = 0x70;  //p
  local_35 = 'b';
  local_32 = 0;

  *PTR_DAT_80026194 = 0;     //switch to picture view mode for working with the correct list and system file

  load_selected_system_file();  //load the picture system file

  uVar12 = 1;

  do
  {
    local_37 = (char)uVar12 + '0';

    iVar6 = f_open(auStack608,&local_38,1);   // check 1 - 9 .bmp file  "/0.bmp"

    if (iVar6 == 4)
    {
      f_close(auStack608);
      break;
    }

    f_close(auStack608);

    uVar12 = uVar12 + 1;
  } while (uVar12 < 10);

  uVar10 = DAT_80026198;

  if (uVar12 == 10)  //if 9.bmp exists
  {
    local_34 = 0x62;    //b
    local_33 = 0x6d;    //m
    local_38 = '/';
    local_32 = 0x70;    //p
    local_35 = '.';
    local_31 = 0;

    do
    {
      cVar4 = (char)(uint)((ulonglong)uVar12 * (ulonglong)uVar10 >> 0x23);

      local_37 = cVar4 + '0';

      local_36 = (char)uVar12 + cVar4 * -10 + '0';

      iVar6 = f_open(auStack608,&local_38,1);

      if (iVar6 == 4)
      {
        f_close(auStack608);
        break;
      }

      f_close(auStack608);

      uVar12 = uVar12 + 1;
    } while (uVar12 < 100);
  }

  uVar8 = DAT_8002619c;  //0x51EB851F

  if (uVar12 == 100)  //if 99.bmp exists
  {
    local_34 = 0x2e;  //.
    local_33 = 0x62;
    local_30 = 0;
    local_32 = 0x6d;
    local_38 = '/';
    local_31 = 0x70;

    do
    {
      uVar1 = (uint)((ulonglong)uVar12 * (ulonglong)uVar8 >> 0x25);

      local_37 = (char)uVar1 + '0';

      local_36 = (char)(uint)((ulonglong)(uVar12 + uVar1 * -100) * (ulonglong)uVar10 >> 0x23) + '0';

      local_35 = (char)uVar12 + (char)(uint)((ulonglong)uVar12 * (ulonglong)uVar10 >> 0x23) * -10 + '0';

      iVar6 = f_open(auStack608,&local_38,1);

      if (iVar6 == 4)
      {
        f_close(auStack608);
        break;
      }

      f_close(auStack608);
      uVar12 = uVar12 + 1;
    } while (uVar12 < 1000);
  }

  load_selected_system_file();  //Again, why?? Already loaded at start of this function

  //Not screen memory!!  = 0x803849A0

  //Not system file memory =0x8035A99C, but might be the end of system file memory

  uVar11 = DAT_800261a0[-1];  //Get data from 0x8035b168
  puVar9 = DAT_800261a0 + 1;  //0x8035B16C  (pointer math)
  puVar7 = DAT_800261a0;      //0x8035B16A
  iVar6 = DAT_800261a4;       //0x000001F3  = 499 * 2 = 998 shorts

  do  //shift all entries in the system file up
  {   //two entries at a time
    uVar3 = puVar7[-2];
    puVar9[-1] = uVar11;
    uVar11 = puVar7[-3];
    iVar6 = iVar6 + -1;
    puVar9 = puVar9 + -2;
    *puVar9 = uVar3;
    iVar5 = DAT_800261a8;   //0x8035A97E = system file buffer
    puVar7 = puVar7 + -2;
  } while (iVar6 != 0);

  *(undefined2 *)(DAT_800261a8 + 0x20) = *(undefined2 *)(DAT_800261a8 + 0x1e);  //0x8035A97E + 0x20  shift last entry up
  *(short *)(iVar5 + 0x1e) = (short)uVar12;                                     //save the new entry

  save_selected_system_file();


  //Thumbnails?? kind of. It is reduced trace data
  load_selected_list_file();   //0x802F19CE start address of thumbnails

  uVar10 = 0;

  do
  {
    //First short of thumbnail list is the file number. MSB is in first byte LSB in second
    //For each thumbnail 400 bytes are used
    uVar8 = (uint)CONCAT11(*(undefined *)(DAT_800261ac + uVar10),*(undefined *)(DAT_800261ac + uVar10 + 1));  //0x802F19CE

    //Get a byte from 0x802F19CE shift it up 8 bits and or in the byte from 0x802F19CF

    //See if it is 0 or equal to the free file number
    if (uVar8 == 0 || uVar8 == (uVar12 & 0xffff))
    {
      //Do some data manipulation
      FUN_800251bc(uVar12 & 0xffff, uVar10);  //Creation of the thumbnail data???
      break;
    }

    uVar10 = uVar10 + 400;
  } while (uVar10 < DAT_800261b0);   //0x00061A80   = 400000

  save_selected_list_file();

  save_picture_file(&local_38);  //Filename of file not found or last file

  show_saved_successfully();   //Show saved successfully


  //Restore the view mode with value before entry of this function
  *PTR_DAT_80026194 = uVar2;
  return;
}


