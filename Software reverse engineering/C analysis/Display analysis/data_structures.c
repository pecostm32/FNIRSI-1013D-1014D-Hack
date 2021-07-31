


typedef struct tagDisplaySystem          DISPLAYSYSTEM,        *PDISPLAYSYSTEM;
typedef struct tagDisplayData            DISPLAYDATA,          *PDISPLAYDATA;
typedef struct tagFontData               FONTDATA,             *PFONTDATA;
typedef struct tagFontMetrics            FONTMETRICS,          *PFONTMETRICS;
typedef struct tagFontCharFunctions      FONTCHARFUNCTIONS,    *PFONTCHARFUNCTIONS;


typedef void *(*GETCHARDATA)(char *string);
typedef int   (*GETCHARWIDTH)(void);
typedef void  (*RENDERCHAR)(char data);

typedef int   (*GETSTRINGWIDTH)(char *string, int length);


//Struct at 0x8019D464 (displaysystem)
struct tagDisplaySystem
{

  //0x8019D46C
  PFONTDATA          pfont;

  //0x8019D470
  PDISPLAYDATA       pdisplaydata;

  //0x8019D474 Set in FUN_8002faa8 called from setup_display_lib
  PFONTCHARFUNCTIONS pfontcharfunctions;   // ==> 0x80191814

  //0x8019D488
    //Some pointer to a set of functions


  //0x8019D490
     //Some function pointer for processing after character rendering. Set to 0x00000000 so not used.


  //0x8019D494
  int text_mode;     //When 0 extra data handling is done for placing text

  //0x8019D4CC
    //Some function pointer that is called for text rendering. Points to an empty function at 0x8002FD68. Set with initial data and never written again


  //8019D4F0
    //Some pointer to a structure holding function pointers. At 0x08 is a function pointer for screen buffer select. Set with initial data and never written again  (0x00, 0x04, 0x08 indexes used)

};


//Color system needs to be investigated since it uses a foreground and a background color



//At address 0x80857D4C
struct tagDisplayData
{
  unsigned int foregroundcolor;  //At byte 0x00????  Only short is used
  unsigned int backgroundcolor;  //At byte 0x04???   Only short is used

  unsigned short xstart;       //At byte 0x08
  unsigned short ystart;       //At byte 0x0A
  unsigned short xend;         //At byte 0x0C
  unsigned short yend;         //At byte 0x0E

  unsigned char  fonthandlemode;     //Some data at byte 0x10
  unsigned char  whatisitfor;  //Some data at byte 0x11  Selects a set of functions

 

  void          *ptr1;         //Pointer to something at 0x14 (tagBoundingBox)

                               //Something at 0x18 (Byte data)

                               //Byte data on 0x1A

  PFONTDATA      font;        //Starts at byte 0x1C   (0x80857D68) Pointer to a font structure

  unsigned short xoffset;     //Starts at byte 0x20. Is used in text print when new line or carriage return is processed and textplaceflags & 0x03 = 0
  unsigned short xpos;        //Starts at byte 0x22  (0x80857D6E)
  unsigned short ypos;        //Starts at byte 0x24  (0x80857D70)

  unsigned short fontpaintmode;      //Starts at byte 0x2A  So might be select of screen buffer. 0x00 direct and 0x02 indirect

  unsigned char  textplaceflags;    //Starts at byte 0x2C  (0x80857D78)  Holds some flags 0x08 and 0x04 (for Y pos, left, right, center??), but also in 0x02 and 0x01 (for X pos, top, bottom, center??) 


  unsigned int   fgcolor;        //Starts at byte 0x30
  unsigned int   bgcolor;        //Starts at byte 0x34


  unsigned int *pfgcolor;     //Starts at byte 0x38  Points to foregroundcolor in this struct
  unsigned int *pbgcolor;     //Starts at byte 0x3C  Points to backgroundcolor in this struct


  unsigned int   somedata;    //Starts at byte 0x48  Input to FUN_8001857c

  unsigned short xoff;        //Starts at byte 0x4C
  unsigned short yoff;        //Starts at byte 0x50

  char           flag;        //Starts at byte 0x54    Checked on being 0 in FUN_8002ac10 (called from draw_text)


                              //Starts at byte 0x60 Some pointer to a function table
                              //Starts at byte 0x64?????
};







//At address 0x8018AC58
struct tagFontData
{
  RENDERCHAR        renderchar;       //Some function pointer for rendering the character
  GETCHARPIXWIDTH   getcharwidth;     //(func(char c, void *ptr);)  Function pointer for getting character width in pixels at byte 0x04
  void             *f3;               //Some function pointer
  void             *f4;               //Some function pointer
  void             *f5;               //Some pointer??
  PFONTFUNCTIONS    functions;        //Starts at byte 0x14 (0x8018AC6C) Is 0x00000000 in all fonts in the flash
  unsigned char     baseline;         //Starts at byte 0x18 (0x8018AC70) Seem to do the same when changed. Smaller value reduces the number of lines printed
  unsigned char     height;           //Starts at byte 0x19 (0x8018AC71) Both specify the number of lines in the font. The smallest one is used
  unsigned char     size;             //Starts at byte 0x1A. Used for font calculations. So maybe font size
  unsigned char     ymul;             //Starts at byte 0x1B. (This is a multiplier for the height, but only used for calculating the position not the size of the font)
  PFONTINFORMATION  fontinformation;  //Pointer to characters in the font information (at 0x1C)
  unsigned short    a;
  unsigned short    b;
};


//There are two different font information structs
//The below version is used by fonts 2 - 7
//Font infromation
struct tagFontInformation
{
  unsigned short   first_char;
  unsigned short   last_char;
  PFONTMETRICS     fontmetrics;        //Points to metrics data
  PFONTINFORMATION next_info;
};

//The others use something for fixed width characters like courier
//At byte 0x11 in that information field is the width of the characters
struct tagFontInformation2
{
  unsigned char   *pixeldata1;
  unsigned char   *pixeldata2;   //Used for the second set of characters that are translated
  unsigned int     pointer3;     //Points to more character info data (tagFontInformation3)
  unsigned short   first_char;
  unsigned short   last_char;
  unsigned char    pixels;       //Number of pixels per line
  unsigned char    width;        //Number of pixels per line
  unsigned char    bytes;        //Number of bytes per font line
  unsigned char    notused;
};



struct tagFontInformation3
{
  unsigned short   first_char;
  unsigned short   last_char;
  unsigned short  *data;          //This points to two shorts per character (some sort of translation???)
};

struct tagCharTranslate
{
  unsigned short  idx1;        //These characters can be a made up with two sets of pixels
  unsigned short  idx2;
}


struct tagFontMetrics
{                             //For C
  unsigned char   a;          //0x07  Number of pixels per font line
  unsigned char   b;          //0x07
  unsigned char   c;          //0x01  Number of bytes per font line
  unsigned char   d;          //0x00
  void           *data;       //Actual pixel or vector data. It uses single bit per pixel bitmaps with 8 bit multiples per line
};



//0x80191814
//(function pointer) pfontgetchardata = 0x8002F5EC;  //At byte 0
//(function pointer) pfontgetcharwidth = 0x8002F5F4; //At byte 4

struct tagFontCharFunctions
{
  GETCHARDATA  pgetchardata;
  GETCHARWIDTH pgetcharwidth;
};



struct tagBoundingBox
{
  short left;       //0x00  ??
  short top;        //0x02  ??
  short right;      //0x04  ??
  short bottom;     //0x06  ??
}


