#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
  //Read binary image data xsize = 298, ysize = 98
  //16 bits per pixel
  //5 bits R, 6 bits G, 5 bits B
  
  unsigned char  bitmap[800000];
  unsigned short image[200000];
  unsigned int   length;
  
  unsigned int    pixel;
  unsigned int    pixels;
  unsigned int    row;
  unsigned int    rows;
  unsigned int    bytesperrow;
  int             vertres;
  int             horzres;
  unsigned int    size;
  unsigned int    filesize;
  unsigned char   buffer[54];
  unsigned short *dptr;
  unsigned char  *sptr;
  
  unsigned int address;

  FILE *fi = fopen("W25Q32_scope.bin", "rb");

  
//612 pixels
#define AddressOfBitmap   0x8003a8ec
//#define AddressOfBitmap   0x8003adb4     //STOP
#define NofPixels         34
#define NofLines          18
  
//#define AddressOfBitmap   0x8003b27c   //MOVE FAST
//#define AddressOfBitmap   0x8003bdbc   //MOVE SLOW
//#define NofPixels         40
//#define NofLines          36
  
  
//#define AddressOfBitmap   0x8003C8FC    //RUN/STOP
//#define AddressOfBitmap   0x8003E2C4    //AUTO SET
//#define AddressOfBitmap   0x8003FC8C    //50% TRIG
//#define AddressOfBitmap   0x80041654    //T CURSOR 
//#define AddressOfBitmap   0x8004301c    //V CURSOR 
//#define AddressOfBitmap   0x80047d74    //SAVE PIC
//#define AddressOfBitmap   0x8004973c    //SAVE WAVE
//#define AddressOfBitmap   0x800449e4    //CTRL
//#define AddressOfBitmap   0x800463ac    //MEAS URES
//#define NofPixels         60
//#define NofLines          55

//#define AddressOfBitmap   0x8004B104  //V+ V-
//#define NofPixels         60
//#define NofLines          176
    
//#define AddressOfBitmap   0x80050384    //menu button
//#define NofPixels           80
//#define NofLines            42
  
//#define AddressOfBitmap   0x80051fa4  //Channel menu
//#define NofPixels         183
//#define NofLines          252

//#define AddressOfBitmap   0x800687ec  //trigger menu
//#define NofPixels         172
//#define NofLines          186

//#define AddressOfBitmap   0x800781DC  //meas ures menu
//#define NofPixels         499
//#define NofLines          214
  
//#define AddressOfBitmap   0x800AC420   //Main menu
//#define NofPixels         149
//#define NofLines          235
  
//#define AddressOfBitmap   0x800BD5AE    //Start calibration text
//#define NofPixels         197
//#define NofLines          60
  
//#define AddressOfBitmap   0x800C3206     //Calibrating... text
//#define AddressOfBitmap   0x800C6596       //Calibration successful text
//#define NofPixels         110
//#define NofLines          60
  
//#define AddressOfBitmap   0x800c9926     //System settings
//#define NofPixels         244
//#define NofLines          294
  
//#define AddressOfBitmap   0x800EC998      //arrow return symbol
//#define NofPixels         160
//#define NofLines          40

//#define AddressOfBitmap   0x800efb98      //page up button text
//#define AddressOfBitmap   0x800f2f28      //page down button text
//#define AddressOfBitmap   0x800F62B8      //delete wave button text
//#define AddressOfBitmap   0x800F9648      //show grid button text
//#define NofPixels         120
//#define NofLines          55
  
//#define AddressOfBitmap   0x800FC9D8       //Confirm delete menu
//#define NofPixels         360
//#define NofLines          97
  
//#define AddressOfBitmap   0x8010daa8       //Return delete left right select menu
//#define NofPixels         800
//#define NofLines          120

//#define AddressOfBitmap   0x8013c8a8       //Selected sign
//#define NofPixels         60
//#define NofLines          30

//#define AddressOfBitmap   0x8013d6b8       //File select menu bar
//#define NofPixels         140
//#define NofLines          480
  
//

  
  if(fi)
  {
    //Location of bitmap in file
    address = (AddressOfBitmap & 0x1FFFFFFF) + 0x27020;
    
    //Point to it in the file
    fseek(fi, address, SEEK_SET);
    
    size = NofPixels * NofLines;
    
    //Get the bitmap data
    length = fread(&image, 2, size, fi);
    
    //Original bitmap parameters
//    pixels = 298;
//    rows = 98;

    pixels = NofPixels;
    rows = NofLines;
    
    //Number of bytes on a row for a 24 bits per pixel bitmap
    bytesperrow = pixels * 3;
    
    //Adjust for 32 bit segments
    bytesperrow = (bytesperrow + 3) & 0x0FFFFFFC;
    
    //Calculate the size of the bitmap in bytes
    size = bytesperrow * rows;
    
    memset(bitmap, 0, sizeof(bitmap));
    
    dptr = image;

    //Convert to 24 bits per pixel based on 565 RGB
    for(row=0;row<rows;row++)
    {
       sptr = bitmap + ((rows-row) * bytesperrow);

       for(pixel=0;pixel<pixels;pixel++)
       {
         *sptr++ = (unsigned char)(*dptr << 3) & 0x00F8;
         *sptr++ = (unsigned char)(*dptr >> 3) & 0x00FC;
         *sptr++ = (unsigned char)(*dptr >> 8) & 0x00F8;
         
         dptr++;
       }
    }

    FILE *fo = fopen("scope_text_image.bmp", "wb");

    if(fo)
    {
      //Bitmap magic number
      buffer[0] = 'B';
      buffer[1] = 'M';
      
      filesize = size + 54;
      
      //File size
      buffer[2] = filesize & 0xFF;
      buffer[3] = (filesize >>  8) & 0xFF;
      buffer[4] = (filesize >> 16) & 0xFF;
      buffer[5] = (filesize >> 24) & 0xFF;

      //reserved
      buffer[6] = 0;
      buffer[7] = 0;
      buffer[8] = 0;
      buffer[9] = 0;
      
      //Bitmap offset
      buffer[10] = 54;
      buffer[11] = 0;
      buffer[12] = 0;
      buffer[13] = 0;

      //Header size
      buffer[14] = 40;
      buffer[15] = 0;
      buffer[16] = 0;
      buffer[17] = 0;

      //Bitmap width
      buffer[18] = pixels & 0xFF;
      buffer[19] = (pixels >>  8) & 0xFF;
      buffer[20] = (pixels >> 16) & 0xFF;
      buffer[21] = (pixels >> 24) & 0xFF;
      
      //Bitmap height
      buffer[22] = rows & 0xFF;
      buffer[23] = (rows >>  8) & 0xFF;
      buffer[24] = (rows >> 16) & 0xFF;
      buffer[25] = (rows >> 24) & 0xFF;

      //Number of planes      
      buffer[26] = 1;
      buffer[27] = 0;
      
      //Bits per pixel
      buffer[28] = 24;
      buffer[29] = 0;

      //Bitmap compression
      buffer[30] = 0;
      buffer[31] = 0;
      buffer[32] = 0;
      buffer[33] = 0;
      
      //Image size
      buffer[34] = 0;
      buffer[35] = 0;
      buffer[36] = 0;
      buffer[37] = 0;
      
      //Horiz res
      buffer[38] = 0;
      buffer[39] = 0;
      buffer[40] = 0;
      buffer[41] = 0;

      //Vert res
      buffer[42] = 0;
      buffer[43] = 0;
      buffer[44] = 0;
      buffer[45] = 0;

      //Nof colors
      buffer[46] = 0;
      buffer[47] = 0;
      buffer[48] = 0;
      buffer[49] = 0;
      
      //Colors important
      buffer[50] = 0;
      buffer[51] = 0;
      buffer[52] = 0;
      buffer[53] = 0;
      
      fwrite(buffer, 1, 54, fo);

      fwrite(bitmap, 1, size, fo);

      fclose(fo);
    }

    fclose(fi);
  }  
}

