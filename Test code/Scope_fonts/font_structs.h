//----------------------------------------------------------------------------------------------------------------------------------

#ifndef FONT_STRUCTS_H
#define FONT_STRUCTS_H

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct tagFontData               FONTDATA,             *PFONTDATA;
typedef struct tagFontInformation        FONTINFORMATION,      *PFONTINFORMATION;
typedef struct tagFontMetrics            FONTMETRICS,          *PFONTMETRICS;


struct tagFontInformation
{
  unsigned short   first_char;
  unsigned short   last_char;
  PFONTMETRICS     fontmetrics;        //Points to metrics data
  PFONTINFORMATION next_info;          //Points to a possible next info field
};

struct tagFontMetrics
{
  unsigned char   pixels;     //Number of pixels per font line
  unsigned char   b;          //
  unsigned char   bytes;      //Number of bytes per font line
  unsigned char   d;          //
  unsigned char  *data;       //Pointer to the actual pixel data. It uses single bit per pixel bitmaps with 8 bit multiples per line. A character width of 11 uses two bytes per line
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
  PFONTINFORMATION  fontinformation;  //Pointer to characters in the font information.
  unsigned short    a;
  unsigned short    b;
};


//----------------------------------------------------------------------------------------------------------------------------------

#endif /* FONT_STRUCTS_H */

