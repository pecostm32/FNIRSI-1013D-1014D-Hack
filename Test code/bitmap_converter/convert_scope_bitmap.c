#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
  //Read binary image data xsize = 298, ysize = 98
  //16 bits per pixel
  //5 bits R, 6 bits G, 5 bits B
  
  unsigned char  bitmap[100000];
  unsigned short image[32000];
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

  FILE *fi = fopen("bitmap part.bin", "rb");
  
  if(fi)
  {
    //Get the bitmap data
    length = fread(&image, 2, sizeof(image) / 2, fi);
    
    //Original bitmap parameters
    pixels = 298;
    rows = 98;
    
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

    FILE *fo = fopen("scope_image.bmp", "wb");

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

