//----------------------------------------------------------------------------------------------------------------------------------

#ifndef FONT_STRUCTS_H
#define FONT_STRUCTS_H

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct tagFontData               FONTDATA,             *PFONTDATA;
typedef struct tagFontInformation        FONTINFORMATION,      *PFONTINFORMATION;
typedef struct tagFontMetrics            FONTMETRICS,          *PFONTMETRICS;
typedef struct tagFontFixedWidthInfo     FONTFIXEDWIDTHINFO,   *PFONTFIXEDWIDTHINFO;
typedef struct tagFontExtendedInfo       FONTEXTENDEDINFO,     *PFONTEXTENDEDINFO;
typedef struct tagFontTanslationTable    FONTTANSLATIONTABLE,  *PFONTTANSLATIONTABLE;

//----------------------------------------------------------------------------------------------------------------------------------
//Font base structure for all types of fonts

struct tagFontData
{
  unsigned int      renderchar;       //Some function pointer for rendering the character
  unsigned int      getcharwidth;     //Function pointer for getting character width in pixels
  unsigned int      f3;               //Some function pointer
  unsigned int      f4;               //Some function pointer
  unsigned int      f5;               //Some pointer
  unsigned int      functions;        //Pointer to a set of functions
  unsigned char     height;           //Baseline and height seem to do the same when changed. Smaller value reduces the number of lines printed
  unsigned char     baseline;         //Both specify the number of lines in the font. The smallest one is used
  unsigned char     size;             //Used for font calculations, seems to be font size. When changed from 1 to 2 the displayed text doubles in size
  unsigned char     ymul;             //This is a multiplier for the height, but only used for calculating the position not the size of the font. The text shifts down when set to 2
  void             *fontinformation;  //Pointer to characters in the font information.
  unsigned short    a;
  unsigned short    b;
};

//----------------------------------------------------------------------------------------------------------------------------------
//Structures for variable width fonts

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
  unsigned char   width;      //Number of pixels to displace for next character
  unsigned char   bytes;      //Number of bytes per font line
  unsigned char   d;          //
  unsigned char  *data;       //Pointer to the actual pixel data. It uses single bit per pixel bitmaps with 8 bit multiples per line. A character width of 11 uses two bytes per line
};

//----------------------------------------------------------------------------------------------------------------------------------
//Structures for fixed width fonts

struct tagFontFixedWidthInfo
{
  unsigned char     *pixeldata1;        //Points to pixel data for base characters
  unsigned char     *pixeldata2;        //Points to pixel data for extended characters
  PFONTEXTENDEDINFO  extended_info;     //Points to a possible extended characters info field
  unsigned short     first_char;
  unsigned short     last_char;
  unsigned char      pixels;            //Number of pixels per font line
  unsigned char      width;             //Character width
  unsigned char      bytes;             //Number of bytes per font line
  unsigned char      nu;                //Not used
};

struct tagFontExtendedInfo
{
  unsigned short       first_char;
  unsigned short       last_char;
  PFONTTANSLATIONTABLE data;            //Pointer to a translation table. Two shorts per entry
};

struct tagFontTanslationTable
{
  unsigned short char1;                 //If 0xFFFF character is not used. If valid printed first
  unsigned short char2;                 //If valid printed second in mode 2. (Only foreground pixels are set)
};

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* FONT_STRUCTS_H */

