
typedef struct tagFontData               FONTDATA,             *PFONTDATA;
typedef struct tagFontInformation        FONTINFORMATION,      *PFONTINFORMATION;
typedef struct tagFontExtendedInfo       FONTEXTENDEDINFO,     *PFONTEXTENDEDINFO;

struct tagFontInformation
{
  unsigned int     pixeldata1;        //Points to pixel data for base characters
  unsigned int     pixeldata2;        //Points to pixel data for extended characters
  unsigned int     extended_info;     //Points to a possible extended characters info field
  unsigned short   first_char;
  unsigned short   last_char;
  unsigned char    pixels;            //Number of pixels per font line
  unsigned char    width;             //Character width
  unsigned char    bytes;             //Number of bytes per font line
  unsigned char    nu;                //Not used
};

struct tagFontExtendedInfo
{
  unsigned short   first_char;
  unsigned short   last_char;
  unsigned int     data;              //Pointer to a translation table. Two shorts per entry
};

struct tagFontData
{
  unsigned int      renderchar;       //Some function pointer for rendering the character
  unsigned int      getcharwidth;     //Function pointer for getting character width in pixels
  unsigned int      f3;               //Some function pointer
  unsigned int      f4;               //Some function pointer
  unsigned int      f5;               //Some pointer
  unsigned int      functions;        //Pointer to a set of functions
  unsigned char     height;           //Both specify the number of lines in the font. The smallest one is used
  unsigned char     baseline;         //Baseline and height seem to do the same when changed. Smaller value reduces the number of lines printed
  unsigned char     size;             //Used for font calculations, seems to be font size. When changed from 1 to 2 the displayed text doubles in size
  unsigned char     ymul;             //This is a multiplier for the height, but only used for calculating the position not the size of the font. The text shifts down when set to 2
  unsigned int      fontinformation;  //Pointer to characters in the font information.
  unsigned short    a;
  unsigned short    b;
};


#include <stdio.h>      // standard input / output functions
#include <stdlib.h>
#include <string.h>


//#define FONT_ADDRESS     0x8018A380
//#define FONT_FILE        "font_0.c"
//#define FONT_ID          0

#define FONT_ADDRESS     0x80189750
#define FONT_FILE        "font_8.c"
#define FONT_ID          8



#define ADDRESS_MASK     0x01FFFFFF


void processfontinformation(unsigned int datapos);

unsigned short findlastcharacter(unsigned int datapos);

void processpixeldata(unsigned int datapos, unsigned short character);


unsigned short convertshort(unsigned char *ptr)
{
  return(ptr[0] | (ptr[1] << 8));
}

unsigned int convertword(unsigned char *ptr)
{
  return(ptr[0] | (ptr[1] << 8) | (ptr[2] << 16) | (ptr[3] << 24));
}

unsigned char buffer[3000000];
unsigned int  proglength;

FONTDATA          font;
FONTINFORMATION   information;
FONTEXTENDEDINFO  extended;
 
FILE *fo;
 
int main(int argc, char** argv)
{
  FILE *fp;
  
  unsigned char header[32];
  unsigned int length;
  unsigned int datapos;
    
  unsigned char *ptr;
  
  //Open the font output file
  fo = fopen(FONT_FILE, "w");
  
  //Check if it opened
  if(fo)
  {
    fprintf(fo, "//---------------------------------------------------------------------------------------------------------------------\n");
    fprintf(fo, "//Scope font data\n");
    fprintf(fo, "//---------------------------------------------------------------------------------------------------------------------\n\n");
    fprintf(fo, "#include \"font_structs.h\"\n\n");
    fprintf(fo, "//---------------------------------------------------------------------------------------------------------------------\n\n");
    
    //Open the program file
    fp = fopen("W25Q32_scope.bin", "rb");

    //Check if it opened
    if(fp)
    {
      //Point to the scope program in the bin file
      fseek(fp, 0x27000, SEEK_SET);

      //Read in the header to get the program length
      length = fread(header, 1, sizeof(header), fp);

      //Check if the full header is read
      if(length == 32)
      {
        //Get the length from the header and take of the header
        proglength = ((header[19] << 24) | (header[18] << 16) | (header[17] << 8) | header[16]) - 32;

        //Check if it fits in the buffer
        if(proglength < sizeof(buffer))
        {
          //Read in the program data
          length = fread(buffer, 1, proglength, fp);

          //Check if it is fully loaded
          if(length == proglength)
          {
            //At this point the program data is in buffer. For addresses this means that 0x80000000 should be subtracted to get to the right byte
            datapos = FONT_ADDRESS & ADDRESS_MASK;

            //Check if the font data is in the program
            if((datapos + 36) < proglength)
            {
              //Point to the font data
              ptr = &buffer[datapos];

              //Fill the font struct with this data
              font.renderchar = convertword(ptr);
              ptr += 4;

              font.getcharwidth = convertword(ptr);
              ptr += 4;

              font.f3 = convertword(ptr);
              ptr += 4;

              font.f4 = convertword(ptr);
              ptr += 4;

              font.f5 = convertword(ptr);
              ptr += 4;

              font.functions = convertword(ptr);
              ptr += 4;

              font.height = *ptr++;
              font.baseline = *ptr++;
              font.size = *ptr++;
              font.ymul = *ptr++;

              font.fontinformation = convertword(ptr);
              ptr += 4;

              font.a = convertshort(ptr);
              ptr += 2;

              font.b = convertshort(ptr);
              
              //Next is to get the font information data
              datapos = font.fontinformation & ADDRESS_MASK;

              //process a single information packet
              processfontinformation(datapos);
              
              //Print font data
              fprintf(fo, "FONTDATA font_%d = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x%02X, 0x%02X, 0x%02X, 0x%02X, &font_%d_information, 0x%04X, 0x%04X };\n", FONT_ID, font.height, font.baseline, font.size, font.ymul, FONT_ID, font.a, font.b);
              fprintf(fo, "\n//---------------------------------------------------------------------------------------------------------------------\n\n");
            }
          }
        }  
      }

      fclose(fp);
    }
    
    fclose(fo);
  }
}

void processfontinformation(unsigned int datapos)
{
  unsigned int    length;  
  unsigned short  character;
  unsigned short  last_char;
  unsigned int    pixelbytes;
  unsigned int    idx;
  unsigned char  *ptr;
  unsigned short *sptr;
  unsigned short  char1;
  unsigned short  char2;

  if((datapos + 20) < proglength)
  {
    //Point to the font information data
    ptr = &buffer[datapos];

    //Get the font information data
    information.pixeldata1 = convertword(ptr);
    ptr += 4;

    information.pixeldata2 = convertword(ptr);
    ptr += 4;
    
    information.extended_info = convertword(ptr);
    ptr += 4;
    
    information.first_char = convertshort(ptr);
    ptr += 2;

    information.last_char = convertshort(ptr);
    ptr += 2;

    information.pixels = *ptr++;
    information.width = *ptr++;
    information.bytes = *ptr++;
    information.nu = *ptr++;
    
    //Get the position of the extended info data
    datapos = information.extended_info & ADDRESS_MASK;

    if((datapos + 8) < proglength)
    {
      //Point to the extended information data
      ptr = &buffer[datapos];
      
      //Get the extended info
      extended.first_char = convertshort(ptr);
      ptr += 2;

      extended.last_char = convertshort(ptr);
      ptr += 2;

      extended.data = convertword(ptr);
      
      //Get the position of the translation data
      datapos = extended.data & ADDRESS_MASK;
      
      //Get the real last character for calculating the length of the pixel data
      last_char = findlastcharacter(datapos) + 1;
      
      //The length is based on the found last character plus 1 times the number of bytes used per character
      pixelbytes = information.bytes * font.height;
      length = last_char * pixelbytes;
      
      //Get the position of the pixel data
      //Not looking at pixeldata2 since they are the same for the fonts in the binary
      datapos = information.pixeldata1 & ADDRESS_MASK;
      
      //Check if within the data
      if((datapos + length) < proglength)
      {
        //Point to the pixel data
        ptr = &buffer[datapos];
        
        fprintf(fo, "unsigned char font_%d_pixel_data[%d][%d] =\n{\n", FONT_ID, last_char, pixelbytes);
        
        //Process the character pixel data one character at a time
        //The pixel data table is from zero to last char for the extended characters
        //For the normal characters it is information first char to information last char
        for(character=0;character<last_char;)
        {
          fprintf(fo, "  { ");
          
          for(idx=0;idx<pixelbytes;)
          {
            fprintf(fo, "0x%02X", *ptr++);

            idx++;

            if(idx < pixelbytes)
              fprintf(fo, ", ");
          }
      
          character++;

          if(character < last_char)
            fprintf(fo, " },\n");
          else
            fprintf(fo, " }\n");
        }
        
        fprintf(fo, "};\n");
        fprintf(fo, "\n//---------------------------------------------------------------------------------------------------------------------\n\n");
       
        //Get the position of the translation data
        datapos = extended.data & ADDRESS_MASK;

        //Four bytes per entry. Two unsigned shorts
        length = (extended.last_char - extended.first_char) * 4;
        
        //Check if within the data
        if((datapos + length) < proglength)
        {
          //Point to the translation data
          sptr = (unsigned short *)&buffer[datapos];
          
          fprintf(fo, "FONTTANSLATIONTABLE font_%d_translation_table[] =\n{\n", FONT_ID);
          
          //Go through the data to find the highest character number
          while(length)
          {
            //Get the numbers
            char1 = *sptr++;
            char2 = *sptr++;
            
            //Print the numbers
            fprintf(fo, "  { 0x%04X, 0x%04X }", char1, char2);

            //Take two of
            length -= 4;
            
            if(length)
              fprintf(fo, ",\n");
            else
              fprintf(fo, "\n");
          }
          
          fprintf(fo, "};\n");
          fprintf(fo, "\n//---------------------------------------------------------------------------------------------------------------------\n\n");
          
          //Print the extended information
          fprintf(fo, "FONTEXTENDEDINFO font_%d_extended_info = { 0x%04X, 0x%04X, font_%d_translation_table };\n", FONT_ID, extended.first_char, extended.last_char, FONT_ID);
          fprintf(fo, "\n//---------------------------------------------------------------------------------------------------------------------\n\n");
        
          //Print the font information
          fprintf(fo, "FONTFIXEDWIDTHINFO font_%d_information = { (unsigned char *)&font_%d_pixel_data, (unsigned char *)&font_%d_pixel_data, &font_%d_extended_info, 0x%04X, 0x%04X, 0x%02X, 0x%02X, 0x%02X, 0x%02X };\n", FONT_ID, FONT_ID, FONT_ID, FONT_ID, information.first_char, information.last_char, information.pixels, information.width, information.bytes, information.nu);
          fprintf(fo, "\n//---------------------------------------------------------------------------------------------------------------------\n\n");
        }
      }        
    }
  }
}

unsigned short findlastcharacter(unsigned int datapos)
{
  //Four bytes per entry. Two unsigned shorts
  unsigned int length = (extended.last_char - extended.first_char) * 4;
  unsigned short last_char = 0;

  unsigned short *ptr;
  
  //Check if within the data
  if((datapos + length) < proglength)
  {
    //Point to the translation data
    ptr = (unsigned short *)&buffer[datapos];
    
    //Go through the data to find the highest character number
    while(length)
    {
      //Check on valid entry
      if(*ptr != 0xFFFF)
      {
        if(*ptr > last_char)
          last_char = *ptr;
        
      }
      
      //Point to next one and take one of
      ptr++;
      length -= 2;
    }
  }
  
  return(last_char);
}



