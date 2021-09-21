
void save_picture_file(char *filename)

{
  undefined *puVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  undefined auStack584 [552];
  
  puVar1 = DAT_80002adc;  //0x801FAA90   some buffer for holding bitmap file data
  puVar1[0] = 0x42;   //B
  puVar1[1] = 0x4d;   //M
  puVar1[2] = 0xf8;   //Size of the file in bytes  811000 bytes  (On linux it shows 800000 bytes for its size)
  puVar1[3] = 0x5f;
  puVar1[4] = 0xc;
  puVar1[5] = 0;

  puVar1[6] = 0;      //reserved
  puVar1[7] = 0;
  puVar1[8] = 0;      //reserved
  puVar1[9] = 0;


  uVar3 = DAT_80002ae0;   //0xB1DFFFFF
  uVar3 = translate_parameter(0xf,uVar3);

  if (uVar3 == 0)
  {
    uVar3 = DAT_80002ae4;   //0x45126345
  }

  puVar1[0xd] = (char)(uVar3 >> 0x18);   //Set the start of the bitmap data
  puVar1[0xc] = (char)(uVar3 >> 0x10);
  puVar1[0xb] = (char)(uVar3 >> 8);
  puVar1[10] = (char)uVar3;

  //DIB header    (BITMAPINFOHEADER)
  puVar1[0xe] = 0x28;     //Size of dib header needs to include the rgba mask???  so 40 + 16 = 56   BITMAPV3INFOHEADER!!!
  puVar1[0xf] = 0;
  puVar1[0x10] = 0;
  puVar1[0x11] = 0;

  puVar1[0x12] = 0x20;    //Bitmap width in pixels  0x320   = 800
  puVar1[0x13] = 3;
  puVar1[0x14] = 0;
  puVar1[0x15] = 0;

  puVar1[0x16] = 0xe0;    //Bitmap height           0x1E0   = 480    Option is to set this value as a negative number allowing top to bottom copying instead of the other way round
  puVar1[0x17] = 1;
  puVar1[0x18] = 0;
  puVar1[0x19] = 0;

  puVar1[0x1a] = 1;       //Number of color planes     1
  puVar1[0x1b] = 0;

  puVar1[0x1c] = 0x10;    //Number of bits per pixel  16
  puVar1[0x1d] = 0;

  puVar1[0x1e] = 3;       //Compression method         3 = BI_BITFIELDS
  puVar1[0x1f] = 0;
  puVar1[0x20] = 0;
  puVar1[0x21] = 0;

  puVar1[0x22] = 0;       //Image size            0x000BB800  = 768000
  puVar1[0x23] = 0xb8;
  puVar1[0x24] = 0xb;
  puVar1[0x25] = 0;

  puVar1[0x26] = 0;       //Horizontal resolution    0
  puVar1[0x27] = 0;
  puVar1[0x28] = 0;
  puVar1[0x29] = 0;

  puVar1[0x2a] = 0;       //Vertical resolution      0
  puVar1[0x2b] = 0;
  puVar1[0x2c] = 0;
  puVar1[0x2d] = 0;

  puVar1[0x2e] = 0;       //number of colors in the color palette  0
  puVar1[0x2f] = 0;
  puVar1[0x30] = 0;
  puVar1[0x31] = 0;

  puVar1[0x32] = 0;       //number of important colors    0
  puVar1[0x33] = 0;
  puVar1[0x34] = 0;
  puVar1[0x35] = 0;

  //This is a mask field for BI_BITFIELDS compression
  puVar1[0x36] = 0;      //Red mask  0x0000F800
  puVar1[0x37] = 0xf8;
  puVar1[0x38] = 0;
  puVar1[0x39] = 0;

  puVar1[0x3a] = 0xe0;  //Green mask 0x000007E0
  puVar1[0x3b] = 7;
  puVar1[0x3c] = 0;
  puVar1[0x3d] = 0;

  puVar1[0x3e] = 0x1f;  //Blue mask  0x0000001F
  puVar1[0x3f] = 0;
  puVar1[0x40] = 0;
  puVar1[0x41] = 0;

  puVar1[0x42] = 0;     //Alpha mask
  puVar1[0x43] = 0;
  puVar1[0x44] = 0;
  puVar1[0x45] = 0;

  save_system_setup(DAT_80002ae8);   //0x8035344E

  memcpy(puVar1 + 0x46,DAT_80002ae8,DAT_80002aec);  //0x8035344E  0x00003A98 = 150000 bytes

  set_screen_to_global_pointer();

  piVar2 = Global_Frame_Buffer_Pointer;

  iVar4 = DAT_80002af0;  //0x000001DF  copy bitmap from bottum up. bitmap works that way  =479

  uVar3 = 0;



  do
  {
    memcpy(puVar1 + uVar3 * 0x640 + 20000,(void *)(*piVar2 + (iVar4 - uVar3) * 0x640),0x640); // copy 1600 bytes per line
    uVar3 = uVar3 + 1 & 0xfffeffff;
  } while (uVar3 < 0x1e0);

  iVar4 = f_open(auStack584,filename,7);

  if (iVar4 != 0)
  {
    f_close(auStack584);

    iVar4 = f_open(auStack584,filename,7);

    if (iVar4 != 0)
    {
      f_close(auStack584);
      f_open(auStack584,filename,7);
    }
  }

  f_lseek(auStack584,0);

  uVar3 = DAT_80002af8;      //0x000C3500

  iVar4 = f_write(auStack584,DAT_80002adc,DAT_80002af8,NULL);  //0x801FAA90    0x000C3500

  if (iVar4 != 0)
  {
    f_lseek(auStack584,0);

    iVar4 = f_write(auStack584,DAT_80002adc,uVar3,NULL);

    if (iVar4 != 0)
    {
      f_lseek(auStack584,0);
      f_write(auStack584,DAT_80002adc,uVar3,NULL);
    }
  }

  f_close(auStack584);

  return;
}


