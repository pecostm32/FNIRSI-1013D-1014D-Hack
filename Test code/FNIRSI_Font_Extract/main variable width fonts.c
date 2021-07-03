
typedef struct tagFontData               FONTDATA,             *PFONTDATA;
typedef struct tagFontInformation        FONTINFORMATION,      *PFONTINFORMATION;
typedef struct tagFontMetrics            FONTMETRICS,          *PFONTMETRICS;


struct tagFontInformation
{
  unsigned short   first_char;
  unsigned short   last_char;
  unsigned int     fontmetrics;        //Points to metrics data
  unsigned int     next_info;          //Points to a possible next info field
};

struct tagFontMetrics
{
  unsigned char   pixels;     //Number of pixels per font line
  unsigned char   b;          //
  unsigned char   bytes;      //Number of bytes per font line
  unsigned char   d;          //
  unsigned int    data;       //Pointer to the actual pixel data. It uses single bit per pixel bitmaps with 8 bit multiples per line. A character width of 11 uses two bytes per line
//  unsigned char    *data;       //Pointer to the actual pixel data. It uses single bit per pixel bitmaps with 8 bit multiples per line. A character width of 11 uses two bytes per line
};

struct tagFontData
{
  unsigned int      renderchar;       //Some function pointer for rendering the character
  unsigned int      getcharwidth;     //Function pointer for getting character width in pixels
  unsigned int      f3;               //Some function pointer
  unsigned int      f4;               //Some function pointer
  unsigned int      f5;               //Some pointer
  unsigned int      functions;        //Pointer to a set of functions
  unsigned char     baseline;         //Baseline and height seem to do the same when changed. Smaller value reduces the number of lines printed
  unsigned char     height;           //Both specify the number of lines in the font. The smallest one is used
  unsigned char     size;             //Used for font calculations, seems to be font size. When changed from 1 to 2 the displayed text doubles in size
  unsigned char     ymul;             //This is a multiplier for the height, but only used for calculating the position not the size of the font. The text shifts down when set to 2
  unsigned int      fontinformation;  //Pointer to characters in the font information.
  unsigned short    a;
  unsigned short    b;
};


#include <stdio.h>      // standard input / output functions
#include <stdlib.h>
#include <string.h>


//#define FONT_ADDRESS     0x8018AC58
//#define FONT_FILE        "font_2.js"
//#define FONT_ID          2

//#define FONT_ADDRESS     0x8018B738
//#define FONT_FILE        "font_3.js"
//#define FONT_ID          3

//#define FONT_ADDRESS     0x8018C1C0
//#define FONT_FILE        "font_4.js"
//#define FONT_ID          4

//#define FONT_ADDRESS     0x8018D558
//#define FONT_FILE        "font_5.js"
//#define FONT_ID          5

//#define FONT_ADDRESS     0x8018F508
//#define FONT_FILE        "font_6.js"
//#define FONT_ID          6

#define FONT_ADDRESS     0x801913B0
#define FONT_FILE        "font_7.c"
#define FONT_ID          7


#define ADDRESS_MASK     0x01FFFFFF


unsigned int processfontinformation(unsigned int datapos);

void getfontmetrics(unsigned int datapos);
void processmetricsdata(unsigned int datapos, unsigned short character);
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
unsigned int  fontinformations;

FONTDATA        font;
FONTINFORMATION information;
FONTMETRICS     metrics;
 
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

              font.baseline = *ptr++;
              font.height = *ptr++;
              font.size = *ptr++;
              font.ymul = *ptr++;

              font.fontinformation = convertword(ptr);
              ptr += 4;

              font.a = convertshort(ptr);
              ptr += 2;

              font.b = convertshort(ptr);

              fontinformations = 0;
              
              //Next is to get the font information data
              datapos = font.fontinformation & ADDRESS_MASK;

              //Process all the font information packets
              while(datapos)
              {
                //process a single information packet
                datapos = processfontinformation(datapos);
                
                fontinformations++;
              }
              
              //Print font data
              fprintf(fo, "FONTDATA font_%d = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x%02X, 0x%02X, 0x%02X, 0x%02X, &font_%d_information_0, 0x%04X, 0x%04X };\n", FONT_ID, font.baseline, font.height, font.size, font.ymul, FONT_ID, font.a, font.b);
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



unsigned int processfontinformation(unsigned int datapos)
{
  unsigned short character;
  
  unsigned char *ptr;

  if((datapos + 12) < proglength)
  {
    //Point to the font information data
    ptr = &buffer[datapos];

    //Get the font information data
    information.first_char = convertshort(ptr);
    ptr += 2;

    information.last_char = convertshort(ptr);
    ptr += 2;

    information.fontmetrics = convertword(ptr);
    ptr += 4;

    information.next_info = convertword(ptr);
    
    //Get the position of the first metrics data
    datapos = information.fontmetrics & ADDRESS_MASK;
    
    //Process the character pixel data one character at a time
    for(character = information.first_char; character <= information.last_char; character++)
    {
      processpixeldata(datapos, character);
    }

    fprintf(fo, "\n//---------------------------------------------------------------------------------------------------------------------\n\n");
    
    fprintf(fo, "FONTMETRICS font_%d_metrics_%d[] =\n{\n", FONT_ID, fontinformations);
    
    //Process the metrics data one character at a time
    for(character = information.first_char; character <= information.last_char;)
    {
      processmetricsdata(datapos, character);
      
      character++;
      
      if(character <= information.last_char)
        fprintf(fo, ",\n");
    }
    
    fprintf(fo, "\n};\n");
    fprintf(fo, "\n//---------------------------------------------------------------------------------------------------------------------\n\n");
  
    //Print the font information data
    fprintf(fo, "FONTINFORMATION font_%d_information_%d = { 0x%04X, 0x%04X, font_%d_metrics_%d, ", FONT_ID, fontinformations, information.first_char, information.last_char, FONT_ID, fontinformations);
    
    if(information.next_info)
    {
      fprintf(fo, "font_%d_information_%d", FONT_ID, fontinformations + 1);
    }
    else
    {
      fprintf(fo, "0x00000000");
    }

    fprintf(fo, " };\n");
    fprintf(fo, "\n//---------------------------------------------------------------------------------------------------------------------\n\n");
  }
  else
  {
    return(0);
  }
  
  return(information.next_info & ADDRESS_MASK);
}

void getfontmetrics(unsigned int datapos)
{
  unsigned char *ptr;
  
  //Point to the font metrics data
  ptr = &buffer[datapos];

  metrics.pixels = *ptr++;
  metrics.b = *ptr++;
  metrics.bytes = *ptr++;
  metrics.d = *ptr++;
  metrics.data = convertword(ptr);
}


void processpixeldata(unsigned int datapos, unsigned short character)
{
  unsigned char *ptr;
  unsigned int   length;
  unsigned int   idx;
  
  //Calculate the position of the metrics data for this character. Metrics data is 8 bytes long
  datapos = datapos + ((character - information.first_char) * 8);
  
  //Check if within the data
  if((datapos + 8) < proglength)
  {
    //Need the metrics for this character
    getfontmetrics(datapos);

    //Point to the actual pixel data
    datapos = metrics.data & ADDRESS_MASK;
    
    //Get the number of bytes for this character
    length = font.height * metrics.bytes;
    
    //Check if within the data
    if((datapos + length) < proglength)
    {
      //Point to the pixel data
      ptr = &buffer[datapos];
      
      fprintf(fo, "unsigned char font_%d_char_0x%04X_data[] = { ", FONT_ID, character);
      
      for(idx=0;idx<length;)
      {
        fprintf(fo, "0x%02X", *ptr++);
        
        idx++;
        
        if(idx < length)
          fprintf(fo, ", ");
      }
      
      fprintf(fo, " };\n");
    }
  }        
  
}

void processmetricsdata(unsigned int datapos, unsigned short character)
{
  unsigned char *ptr;
  
  //Calculate the position of the metrics data for this character. Metrics data is 8 bytes long
  datapos = datapos + ((character - information.first_char) * 8);
  
  //Check if within the data
  if((datapos + 8) < proglength)
  {
    //Need the metrics for this character
    getfontmetrics(datapos);
    
    fprintf(fo, "  { 0x%02X, 0x%02X, 0x%02X, 0x%02X, font_%d_char_0x%04X_data }", metrics.pixels, metrics.b, metrics.bytes, metrics.d, FONT_ID, character);
  }  
}


/*
//Javascript output
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

              font.baseline = *ptr++;
              font.height = *ptr++;
              font.size = *ptr++;
              font.ymul = *ptr++;

              font.fontinformation = convertword(ptr);
              ptr += 4;

              font.a = convertshort(ptr);
              ptr += 2;

              font.b = convertshort(ptr);

              fontinformations = 0;
              
              //Next is to get the font information data
              datapos = font.fontinformation & ADDRESS_MASK;

              //Process all the font information packets
              while(datapos)
              {
                //process a single information packet
                datapos = processfontinformation(datapos);
                
                fontinformations++;
              }
              
              //Print font data
              fprintf(fo, "var font_%d = [ 0x%02X, 0x%02X, 0x%02X, 0x%02X, font_%d_information_0 ];\n", FONT_ID, font.baseline, font.height, font.size, font.ymul, FONT_ID);
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



unsigned int processfontinformation(unsigned int datapos)
{
  unsigned short character;
  
  unsigned char *ptr;

  if((datapos + 12) < proglength)
  {
    //Point to the font information data
    ptr = &buffer[datapos];

    //Get the font information data
    information.first_char = convertshort(ptr);
    ptr += 2;

    information.last_char = convertshort(ptr);
    ptr += 2;

    information.fontmetrics = convertword(ptr);
    ptr += 4;

    information.next_info = convertword(ptr);
    
    //Get the position of the first metrics data
    datapos = information.fontmetrics & ADDRESS_MASK;

    fprintf(fo, "var font_%d_characters_%d =\n[\n", FONT_ID, fontinformations);
    
    //Process the character pixel data one character at a time
    for(character = information.first_char; character <= information.last_char;)
    {
      processpixeldata(datapos, character);
      
       character++;
       
      if(character <= information.last_char)
        fprintf(fo, ",\n");
    }

    fprintf(fo, "\n];\n");
    fprintf(fo, "\n//---------------------------------------------------------------------------------------------------------------------\n\n");
    
    fprintf(fo, "var font_%d_metrics_%d =\n[\n", FONT_ID, fontinformations);
    
    //Process the metrics data one character at a time
    for(character = information.first_char; character <= information.last_char;)
    {
      processmetricsdata(datapos, character);
      
      character++;
      
      if(character <= information.last_char)
        fprintf(fo, ",\n");
    }
    
    fprintf(fo, "\n];\n");
    fprintf(fo, "\n//---------------------------------------------------------------------------------------------------------------------\n\n");

//This needs to be in an other order to work in javascript
    
    //Print the font information data
    fprintf(fo, "var font_%d_information_%d = [ 0x%04X, 0x%04X, font_%d_metrics_%d, font_%d_characters_%d, ", FONT_ID, fontinformations, information.first_char, information.last_char, FONT_ID, fontinformations, FONT_ID, fontinformations);
    
    if(information.next_info)
    {
      fprintf(fo, "font_%d_information_%d", FONT_ID, fontinformations + 1);
    }
    else
    {
      fprintf(fo, "0");
    }

    fprintf(fo, " ];\n");
    fprintf(fo, "\n//---------------------------------------------------------------------------------------------------------------------\n\n");
  }
  else
  {
    return(0);
  }
  
  return(information.next_info & ADDRESS_MASK);
}

void getfontmetrics(unsigned int datapos)
{
  unsigned char *ptr;
  
  //Point to the font metrics data
  ptr = &buffer[datapos];

  metrics.pixels = *ptr++;
  metrics.b = *ptr++;
  metrics.bytes = *ptr++;
  metrics.d = *ptr++;
  metrics.data = convertword(ptr);
}


void processpixeldata(unsigned int datapos, unsigned short character)
{
  unsigned char *ptr;
  unsigned int   length;
  unsigned int   idx;
  
  //Calculate the position of the metrics data for this character. Metrics data is 8 bytes long
  datapos = datapos + ((character - information.first_char) * 8);
  
  //Check if within the data
  if((datapos + 8) < proglength)
  {
    //Need the metrics for this character
    getfontmetrics(datapos);

    //Point to the actual pixel data
    datapos = metrics.data & ADDRESS_MASK;
    
    //Get the number of bytes for this character
    length = font.height * metrics.bytes;
    
    //Check if within the data
    if((datapos + length) < proglength)
    {
      //Point to the pixel data
      ptr = &buffer[datapos];
      
      fprintf(fo, "  [ ");
      
      for(idx=0;idx<length;)
      {
        fprintf(fo, "0x%02X", *ptr++);
        
        idx++;
        
        if(idx < length)
          fprintf(fo, ", ");
      }
      
      fprintf(fo, " ]");
    }
  }        
  
}

void processmetricsdata(unsigned int datapos, unsigned short character)
{
  unsigned char *ptr;
  
  //Calculate the position of the metrics data for this character. Metrics data is 8 bytes long
  datapos = datapos + ((character - information.first_char) * 8);
  
  //Check if within the data
  if((datapos + 8) < proglength)
  {
    //Need the metrics for this character
    getfontmetrics(datapos);
    
    fprintf(fo, "  [ 0x%02X, 0x%02X, 0x%02X, 0x%02X ]", metrics.pixels, metrics.b, metrics.bytes, metrics.d);
  }  
}
 */