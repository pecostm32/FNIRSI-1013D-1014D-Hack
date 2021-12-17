//----------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

#include <math.h>

#include "xlibfunctions.h"

#include "mousehandling.h"


#include "signal_generator.h"
#include "signal_generator_functions.h"

//----------------------------------------------------------------------------------------------------------------------------------

#define DESIGN_WIDTH        1355
#define DESIGN_HEIGHT       730

//----------------------------------------------------------------------------------------------------------------------------------

#define CHANNEL_WIDTH       444
#define CHANNEL_HEIGHT       85

#define CHANNEL1_XPOS       20
#define CHANNEL2_XPOS       CHANNEL1_XPOS + CHANNEL_WIDTH + 20
#define CHANNEL_YPOS        630

#define CHANNEL1_X1         CHANNEL1_XPOS + 46
#define CHANNEL1_X2         CHANNEL1_X1 + 65
#define CHANNEL1_X3         CHANNEL1_X1 + 115
#define CHANNEL1_X4         CHANNEL1_XPOS + 268
#define CHANNEL1_X5         CHANNEL1_X4 + 65
#define CHANNEL1_X6         CHANNEL1_X4 + 115

#define CHANNEL2_X1         CHANNEL2_XPOS + 46
#define CHANNEL2_X2         CHANNEL2_X1 + 65
#define CHANNEL2_X3         CHANNEL2_X1 + 115
#define CHANNEL2_X4         CHANNEL2_XPOS + 268
#define CHANNEL2_X5         CHANNEL2_X4 + 65
#define CHANNEL2_X6         CHANNEL2_X4 + 115

#define CHANNEL_Y1          CHANNEL_YPOS + 27
#define CHANNEL_Y2          CHANNEL_Y1 + 10
#define CHANNEL_Y3          CHANNEL_Y2 + 10

//----------------------------------------------------------------------------------------------------------------------------------

#define MODE_XPOS            955
#define MODE_YPOS             30
#define MODE_WIDTH           380
#define MODE_HEIGHT          230

#define MODE_SPACING          50

#define MODE_X1             MODE_XPOS + 25
#define MODE_X2             MODE_X1   + 180

#define MODE_LX1            MODE_XPOS + 160
#define MODE_LX2            MODE_LX1  + 180

#define MODE_Y1             MODE_YPOS + 20
#define MODE_Y2             MODE_Y1   + MODE_SPACING
#define MODE_Y3             MODE_Y2   + MODE_SPACING
#define MODE_Y4             MODE_Y3   + MODE_SPACING

#define MODE_LY1            MODE_YPOS + 32
#define MODE_LY2            MODE_LY1  + MODE_SPACING
#define MODE_LY3            MODE_LY2  + MODE_SPACING
#define MODE_LY4            MODE_LY3  + MODE_SPACING

//----------------------------------------------------------------------------------------------------------------------------------

#define CONTROL_XPOS         955
#define CONTROL_YPOS         290
#define CONTROL_WIDTH        380
#define CONTROL_HEIGHT       425

#define MAGNITUDE_X1        CONTROL_XPOS +  25
#define MAGNITUDE_X2        MAGNITUDE_X1 + 115

#define MAGNITUDE_Y1        CONTROL_YPOS +  28
#define MAGNITUDE_Y2        MAGNITUDE_Y1 +  45
#define MAGNITUDE_Y3        MAGNITUDE_Y2 +  45

#define MAGNITUDE_LY1       CONTROL_YPOS  + 38
#define MAGNITUDE_LY2       MAGNITUDE_LY1 + 45
#define MAGNITUDE_LY3       MAGNITUDE_LY2 + 45

#define ROTARY_X1           CONTROL_XPOS + 200
#define ROTARY_Y1           CONTROL_YPOS +  19

#define SELECT_X1           CONTROL_XPOS +  25
#define SELECT_X2           SELECT_X1    +  30
#define SELECT_X3           SELECT_X2    + 115
#define SELECT_X4           CONTROL_XPOS + 225
#define SELECT_X5           SELECT_X4    +  65

#define SELECT_Y1           CONTROL_YPOS + 185
#define SELECT_Y2           SELECT_Y1    +   8

#define KEYPAD_XPOS         CONTROL_XPOS +  83
#define KEYPAD_YPOS         CONTROL_YPOS + 242

#define KEYPAD_SPACING      45

#define KEYPAD_X1           KEYPAD_XPOS
#define KEYPAD_X2           KEYPAD_X1 + KEYPAD_SPACING
#define KEYPAD_X3           KEYPAD_X2 + KEYPAD_SPACING
#define KEYPAD_X4           KEYPAD_X3 + KEYPAD_SPACING

#define KEYPAD_Y1           KEYPAD_YPOS
#define KEYPAD_Y2           KEYPAD_Y1 + KEYPAD_SPACING
#define KEYPAD_Y3           KEYPAD_Y2 + KEYPAD_SPACING
#define KEYPAD_Y4           KEYPAD_Y3 + KEYPAD_SPACING

//----------------------------------------------------------------------------------------------------------------------------------

#define Q1PI                                     1.5707963267948966192
#define Q2PI                                     3.1415926535897932384
#define Q3PI                                     4.7123889803846898576
#define Q4PI                                     6.2831853071795864769

#define PI                                       3.1415926535897932384
#define PI2                                      6.2831853071795864769
#define PI4                                     12.5663706143591729538

#define PIx100                                 314.15926535897932384


#define SIGNAL_GENERATOR_SAMPLE_RATE    1000000000

//----------------------------------------------------------------------------------------------------------------------------------

double triangle(double phase);
double rampup(double phase);
double rampdown(double phase);

//----------------------------------------------------------------------------------------------------------------------------------

void checksettingsupdate(int channel);

void signalstep(int channel);

//----------------------------------------------------------------------------------------------------------------------------------

const tagPlaceText texts[] =
{
  //Text,                 xpos,       ypos, fontid,          colorid,             align
  { "CHANNEL 1",   CHANNEL1_X2, CHANNEL_Y1,      0, PanelTextColorId, ALIGN_TEXT_CENTER },
  { "PULSE WIDTH", CHANNEL1_X5, CHANNEL_Y1,      0, PanelTextColorId, ALIGN_TEXT_CENTER },
  { "CHANNEL 2",   CHANNEL2_X2, CHANNEL_Y1,      0, PanelTextColorId, ALIGN_TEXT_CENTER },
  { "PULSE WIDTH", CHANNEL2_X5, CHANNEL_Y1,      0, PanelTextColorId, ALIGN_TEXT_CENTER }
};

//All the leds on the front panel
tagLed leds[] =
{
  //  xc, state,         xpos,          ypos, diameter,    offcolor,    oncolor,      edgecolor, x, y, d
  { NULL,     0,  CHANNEL1_X3,    CHANNEL_Y3,       15, LedOffColor, LedOnColor, LedBorderColor, 0, 0, 0 },
  { NULL,     0,  CHANNEL1_X6,    CHANNEL_Y3,       15, LedOffColor, LedOnColor, LedBorderColor, 0, 0, 0 },
  { NULL,     0,  CHANNEL2_X3,    CHANNEL_Y3,       15, LedOffColor, LedOnColor, LedBorderColor, 0, 0, 0 },
  { NULL,     0,  CHANNEL2_X6,    CHANNEL_Y3,       15, LedOffColor, LedOnColor, LedBorderColor, 0, 0, 0 },

  { NULL,     0,     MODE_LX1,      MODE_LY1,       15, LedOffColor, LedOnColor, LedBorderColor, 0, 0, 0 },
  { NULL,     0,     MODE_LX1,      MODE_LY2,       15, LedOffColor, LedOnColor, LedBorderColor, 0, 0, 0 },
  { NULL,     0,     MODE_LX1,      MODE_LY3,       15, LedOffColor, LedOnColor, LedBorderColor, 0, 0, 0 },
  { NULL,     0,     MODE_LX1,      MODE_LY4,       15, LedOffColor, LedOnColor, LedBorderColor, 0, 0, 0 },
  { NULL,     0,     MODE_LX2,      MODE_LY1,       15, LedOffColor, LedOnColor, LedBorderColor, 0, 0, 0 },
  { NULL,     0,     MODE_LX2,      MODE_LY2,       15, LedOffColor, LedOnColor, LedBorderColor, 0, 0, 0 },
  { NULL,     0,     MODE_LX2,      MODE_LY3,       15, LedOffColor, LedOnColor, LedBorderColor, 0, 0, 0 },
  { NULL,     0,     MODE_LX2,      MODE_LY4,       15, LedOffColor, LedOnColor, LedBorderColor, 0, 0, 0 },

  { NULL,     0, MAGNITUDE_X2, MAGNITUDE_LY1,       15, LedOffColor, LedOnColor, LedBorderColor, 0, 0, 0 },
  { NULL,     0, MAGNITUDE_X2, MAGNITUDE_LY2,       15, LedOffColor, LedOnColor, LedBorderColor, 0, 0, 0 },
  { NULL,     0, MAGNITUDE_X2, MAGNITUDE_LY3,       15, LedOffColor, LedOnColor, LedBorderColor, 0, 0, 0 },

  { NULL,     0,    SELECT_X1,     SELECT_Y2,       15, LedOffColor, LedOnColor, LedBorderColor, 0, 0, 0 },
  { NULL,     0,    SELECT_X3,     SELECT_Y2,       15, LedOffColor, LedOnColor, LedBorderColor, 0, 0, 0 },
};


tagRotaryDial rotarydials[] =
{
  //        Mouserange set here to make a linked list. Search for object under mouse pointer needs to be done from last to first based on previous pointer
  //  xc,           action,   previous, left, right, top, bottom, move, down,   up,  out,        xpos,      ypos, position
  { NULL, handlerotarydial, {     NULL,    0,     0,   0,      0, NULL, NULL, NULL, NULL }, ROTARY_X1, ROTARY_Y1,        0 }
};

//All the buttons on the front panel
tagButton buttons[] = 
{
  //        Mouserange set here to make a linked list. Search for object under mouse pointer needs to be done from last to first based on previous pointer
  //  xc,                 action,                previous, left, right, top, bottom, move, down,   up,  out,                     type,    xpos,    ypos, 
  { NULL,         initializewaveformedit, { &rotarydials[0].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, MODE_X1, MODE_Y1, 120, 40, 0, "WAVEFORM",   2, ButtonTextColorId },
  { NULL,        initializefrequencyedit, {     &buttons[0].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, MODE_X1, MODE_Y2, 120, 40, 0, "FREQUENCY",  2, ButtonTextColorId },
  { NULL,            initializephaseedit, {     &buttons[1].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, MODE_X1, MODE_Y3, 120, 40, 0, "PHASE",      2, ButtonTextColorId },
  { NULL,                           NULL, {     &buttons[2].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, MODE_X1, MODE_Y4, 120, 40, 0, "LOAD",       2, ButtonTextColorId },
  
  { NULL,        initializeamplitudeedit, {     &buttons[3].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, MODE_X2, MODE_Y1, 120, 40, 0, "AMPLITUDE",   2, ButtonTextColorId },
  { NULL,         initializedcoffsetedit, {     &buttons[4].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, MODE_X2, MODE_Y2, 120, 40, 0, "DC OFFSET",   2, ButtonTextColorId },
  { NULL,       initializepulsewidthedit, {     &buttons[5].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, MODE_X2, MODE_Y3, 120, 40, 0, "PULSE WIDTH", 2, ButtonTextColorId },
  { NULL,                           NULL, {     &buttons[6].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, MODE_X2, MODE_Y4, 120, 40, 0, "SAVE",        2, ButtonTextColorId },
  
  { NULL,              selectfrequencyhz, {  &buttons[7].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, MAGNITUDE_X1,  MAGNITUDE_Y1, 100, 35, 0, "HZ",        2, ButtonTextColorId },
  { NULL,             selectfrequencykhz, {  &buttons[8].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, MAGNITUDE_X1,  MAGNITUDE_Y2, 100, 35, 0, "KHz",       2, ButtonTextColorId },
  { NULL,             selectfrequencymhz, {  &buttons[9].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, MAGNITUDE_X1,  MAGNITUDE_Y3, 100, 35, 0, "MHz",       2, ButtonTextColorId },

  { NULL,            togglechannelselect, { &buttons[10].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, SELECT_X2, SELECT_Y1, 100, 35, 0, "CH1 / CH2",  2, ButtonTextColorId },
  
  { NULL,             handleleftarrowkey, { &buttons[11].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },      BUTTON_ARROW_LEFT, SELECT_X4, SELECT_Y1, 35, 35, 0, NULL,        0, 0 },
  { NULL,            handlerightarrowkey, { &buttons[12].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },     BUTTON_ARROW_RIGHT, SELECT_X5, SELECT_Y1, 35, 35, 0, NULL,        0, 0 },

  { NULL,               handlenumber7key, { &buttons[13].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, KEYPAD_X1,  KEYPAD_Y1, 35, 35, 0, "7",        2, ButtonTextColorId },
  { NULL,               handlenumber8key, { &buttons[14].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, KEYPAD_X2,  KEYPAD_Y1, 35, 35, 0, "8",        2, ButtonTextColorId },
  { NULL,               handlenumber9key, { &buttons[15].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, KEYPAD_X3,  KEYPAD_Y1, 35, 35, 0, "9",        2, ButtonTextColorId },

  { NULL,               handlenumber4key, { &buttons[16].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, KEYPAD_X1,  KEYPAD_Y2, 35, 35, 0, "4",        2, ButtonTextColorId },
  { NULL,               handlenumber5key, { &buttons[17].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, KEYPAD_X2,  KEYPAD_Y2, 35, 35, 0, "5",        2, ButtonTextColorId },
  { NULL,               handlenumber6key, { &buttons[18].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, KEYPAD_X3,  KEYPAD_Y2, 35, 35, 0, "6",        2, ButtonTextColorId },

  { NULL,               handlenumber1key, { &buttons[19].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, KEYPAD_X1,  KEYPAD_Y3, 35, 35, 0, "1",        2, ButtonTextColorId },
  { NULL,               handlenumber2key, { &buttons[20].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, KEYPAD_X2,  KEYPAD_Y3, 35, 35, 0, "2",        2, ButtonTextColorId },
  { NULL,               handlenumber3key, { &buttons[21].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, KEYPAD_X3,  KEYPAD_Y3, 35, 35, 0, "3",        2, ButtonTextColorId },

  { NULL,               handlenumber0key, { &buttons[22].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, KEYPAD_X1,  KEYPAD_Y4, 80, 35, 0, "0",        2, ButtonTextColorId },
  { NULL,             handlenumberdotkey, { &buttons[23].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, KEYPAD_X3,  KEYPAD_Y4, 35, 35, 0, ".",        2, ButtonTextColorId },

  { NULL,           handlenumberminuskey, { &buttons[24].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, KEYPAD_X4,  KEYPAD_Y1, 80, 35, 0, "-",        2, ButtonTextColorId },
  { NULL,            handlenumberpluskey, { &buttons[25].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, KEYPAD_X4,  KEYPAD_Y2, 80, 35, 0, "+",        2, ButtonTextColorId },

  { NULL,          handlenumbercancelkey, { &buttons[26].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, KEYPAD_X4,  KEYPAD_Y3, 80, 35, 0, "CANCEL",   2, ButtonTextColorId },
  { NULL,           handlenumberenterkey, { &buttons[27].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, KEYPAD_X4,  KEYPAD_Y4, 80, 35, 0, "ENTER",    2, ButtonTextColorId },

  { NULL,           togglechannel1enable, { &buttons[28].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, CHANNEL1_X1, CHANNEL_Y2, 100, 35, 0, "ON / OFF",    2, ButtonTextColorId },
  { NULL, togglechannel1pulsewidthenable, { &buttons[29].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, CHANNEL1_X4, CHANNEL_Y2, 100, 35, 0, "ON / OFF",    2, ButtonTextColorId },

  { NULL,           togglechannel2enable, { &buttons[30].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, CHANNEL2_X1, CHANNEL_Y2, 100, 35, 0, "ON / OFF",    2, ButtonTextColorId },
  { NULL, togglechannel2pulsewidthenable, { &buttons[31].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT, CHANNEL2_X4, CHANNEL_Y2, 100, 35, 0, "ON / OFF",    2, ButtonTextColorId },
};

//Set pointer to last mouse range for scanning
MouseRange *mouseranges = &buttons[32].mouse;

//----------------------------------------------------------------------------------------------------------------------------------

pthread_t signal_generator_thread;

int quit_signal_generator_thread_on_zero = 0;

int signal_generator_still_running = 1;

//----------------------------------------------------------------------------------------------------------------------------------

tagXlibContext signalgeneratorxc;

//----------------------------------------------------------------------------------------------------------------------------------

SIGNALGENERATORCHANNELSETTINGS channelsettings[2];

char textbuffer[128];

int currentchannel = 0;
int currentmagnitude = 0;

int signalgeneratorfrozen = 0;
int signalgeneratorready = 0;

//----------------------------------------------------------------------------------------------------------------------------------

int startsignalgenerator(void)
{
  //Setup for keeping the arm ui window thread running
  quit_signal_generator_thread_on_zero = 1;
  
  //Start up the arm emulator ui window thread
  return(pthread_create(&signal_generator_thread, NULL, signalgeneratorthread, NULL));
}

//----------------------------------------------------------------------------------------------------------------------------------

void stopsignalgenerator(void)
{
  //Stop the arm ui window thread
  quit_signal_generator_thread_on_zero = 0;
  
  //Wait until process is stopped
  while(signal_generator_still_running == 1);
}

//----------------------------------------------------------------------------------------------------------------------------------

void *signalgeneratorthread(void *arg)
{
  struct timeval starttime;
  struct timeval endtime;
  long int       duration;
  
  //Since multi threads are used to control display objects initialize the xlib for it
  XInitThreads();
  
	Display *display = XOpenDisplay(NULL);
	int screen_num = DefaultScreen(display);
	Window root = RootWindow(display, screen_num);
	Window win = XCreateSimpleWindow(display, root, 0, 0, DESIGN_WIDTH + BORDER_SIZE_2, DESIGN_HEIGHT + BORDER_SIZE_2, 2, BlackPixel(display, screen_num), WhitePixel(display, screen_num));
  
	XMapWindow(display, win);
  
  //For mouse handling only button press and release are needed in combination with motion which is used for controlling the knobs
	XSelectInput(display, win, ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask );
  
	GC gc = XCreateGC(display, win, 0, NULL);
  
  unsigned int width;	           //width and height for the new window.
  unsigned int height;
  
  unsigned int x,y;
  
  Atom WM_DELETE_WINDOW = XInternAtom(display, "WM_DELETE_WINDOW", False); 
  Atom WM_PROTOCOLS = XInternAtom(display, "WM_PROTOCOLS", False);
  XSetWMProtocols(display, win, &WM_DELETE_WINDOW, 1);
  
	XEvent event;

  double fsize;
  
  int rflag = 1;

  int numsizes;  
  XRRScreenSize *scrsize;
  
  //Get the size of the primary monitor
  scrsize = XRRSizes(display, screen_num, &numsizes);
  
  //For calculations take of a border of 5 pixels for each side
  width  = (scrsize->width - BORDER_SIZE_2) * 0.95;
  height = scrsize->height - BORDER_SIZE_2;
   
  //Determine the scaler based on the width
  signalgeneratorxc.scaler = (float)width / (float)DESIGN_WIDTH;

  //See if it, when scaled, fits for the height. If not determine the scaler based on the height
  if((DESIGN_HEIGHT * signalgeneratorxc.scaler) > height)
    signalgeneratorxc.scaler = (float)height / (float)DESIGN_HEIGHT;
  
  //Check if screen is larger than the desired size
  if(signalgeneratorxc.scaler > 1.0)
  {
    //If so keep the scale on 1
    signalgeneratorxc.scaler = 1.0;
  }

  //Calculate the new width and height
  width = (DESIGN_WIDTH * signalgeneratorxc.scaler) + BORDER_SIZE_2;
  height = (DESIGN_HEIGHT * signalgeneratorxc.scaler) + BORDER_SIZE_2;
  
  //Calculate a nice position on the screen
  x = 50;
  y = 50;
  
  //Set the window to the new position and dimensions
  XMoveResizeWindow(display, win, x, y, width, height);
  
  //Setup the data for the drawing functions
  signalgeneratorxc.screen_num = screen_num;
  signalgeneratorxc.root = root;
  signalgeneratorxc.win = win;
  signalgeneratorxc.display = display;
  signalgeneratorxc.gc = gc;
  
  signalgeneratorxc.visual = DefaultVisual(display, screen_num);
  signalgeneratorxc.cmap  = DefaultColormap(display, screen_num);
    
  //Create all the used fonts
  fsize = 14 * signalgeneratorxc.scaler;
  signalgeneratorxc.font[0] = XftFontOpen(display, screen_num, XFT_FAMILY, XftTypeString, "Arial", XFT_WEIGHT, XftTypeInteger, XFT_WEIGHT_BOLD, XFT_SIZE, XftTypeDouble, fsize, XFT_ANTIALIAS, XftTypeBool, True, NULL);

  fsize = 12 * signalgeneratorxc.scaler;
  signalgeneratorxc.font[1] = XftFontOpen(display, screen_num, XFT_FAMILY, XftTypeString, "Arial", XFT_WEIGHT, XftTypeInteger, XFT_WEIGHT_BOLD, XFT_SIZE, XftTypeDouble, fsize, XFT_ANTIALIAS, XftTypeBool, True, NULL);

  fsize = 11 * signalgeneratorxc.scaler;
  signalgeneratorxc.font[2] = XftFontOpen(display, screen_num, XFT_FAMILY, XftTypeString, "Arial", XFT_WEIGHT, XftTypeInteger, XFT_WEIGHT_BOLD, XFT_SIZE, XftTypeDouble, fsize, XFT_ANTIALIAS, XftTypeBool, True, NULL);

  fsize = 10 * signalgeneratorxc.scaler;
  signalgeneratorxc.font[3] = XftFontOpen(display, screen_num, XFT_FAMILY, XftTypeString, "Arial", XFT_WEIGHT, XftTypeInteger, XFT_WEIGHT_BOLD, XFT_SIZE, XftTypeDouble, fsize, XFT_ANTIALIAS, XftTypeBool, True, NULL);
  
  //Create the used font colors
  rflag = XftColorAllocName(display, signalgeneratorxc.visual, signalgeneratorxc.cmap, PanelTextColor,  &signalgeneratorxc.color[0]);
  rflag = XftColorAllocName(display, signalgeneratorxc.visual, signalgeneratorxc.cmap, ButtonTextColor, &signalgeneratorxc.color[1]);
  rflag = XftColorAllocName(display, signalgeneratorxc.visual, signalgeneratorxc.cmap, BrightTextColor, &signalgeneratorxc.color[2]);
  rflag = XftColorAllocName(display, signalgeneratorxc.visual, signalgeneratorxc.cmap, DimmedTextColor, &signalgeneratorxc.color[3]);
  
  signalgeneratorxc.draw = XftDrawCreate(display, win, signalgeneratorxc.visual, signalgeneratorxc.cmap);
  
  channelsettings[0].waveform = 0;
  channelsettings[0].channelenable = 1;
  channelsettings[0].pulsewidthenable = 0;
  channelsettings[0].frequencymagnitude = 0;
  channelsettings[0].amplitude = 0.1;
  channelsettings[0].dcoffset = 0;  
  channelsettings[0].frequency = 5000000.0;
  channelsettings[0].maxamplitude = 25;
  channelsettings[0].phase = 0;
  channelsettings[0].previousphase = 0;
  channelsettings[0].pulsewidth = 20;

  channelsettings[0].amplitudechanged        = 1;
  channelsettings[0].dcoffsetchanged         = 1;
  channelsettings[0].frequencychanged        = 1;
  channelsettings[0].pulsewidthchanged       = 1;
  channelsettings[0].pulsewidthenablechanged = 1;
  channelsettings[0].phasechanged            = 1;
  
  channelsettings[0].signaltime = 0.0;
  
  
  channelsettings[1].waveform = 0;
  channelsettings[1].channelenable = 1;
  channelsettings[1].pulsewidthenable = 0;
  channelsettings[1].frequencymagnitude = 2;
  channelsettings[1].amplitude = 0.1;  
  channelsettings[1].dcoffset = 0;  
  channelsettings[1].frequency = 10000000;
  channelsettings[1].maxamplitude = 25;
  channelsettings[1].phase = 0;
  channelsettings[1].previousphase = 0;
  channelsettings[1].pulsewidth = 78.27;

  channelsettings[1].amplitudechanged        = 1;
  channelsettings[1].dcoffsetchanged         = 1;
  channelsettings[1].frequencychanged        = 1;
  channelsettings[1].pulsewidthchanged       = 1;
  channelsettings[1].pulsewidthenablechanged = 1;
  channelsettings[1].phasechanged            = 1;
  
  channelsettings[1].signaltime = 0.0;
  
  
  //Get the current time for duration calculation
  gettimeofday(&starttime, 0);
  
  //Quit on window close or thread being stopped
  while(quit_signal_generator_thread_on_zero && rflag)
  {
    //Let other threads know this one is still running
    signal_generator_still_running = 1;
    
    if(XPending(display))
    {
      XNextEvent(display, &event);
      switch(event.type)
      {
        case Expose:
          //Setup the screen
          DrawSignalGeneratorFrontPanel(&signalgeneratorxc);
          break;

        case KeyPress:
          if(event.xkey.keycode == XKeysymToKeycode(display,XK_Escape))
          {
            rflag = 0;
          }
          
          //Need to handle short cut keys here!!!!
          break;

        case ButtonPress:
          //Call mouse handling function down()
          MouseDown(&event);
          break;

        case ButtonRelease:
          //Call mouse handling function up()
          MouseUp(mouseranges, &event);
          break;

        case MotionNotify:
          //Call mouse handling function move()
          MouseMove(mouseranges, &event);
          break;

        case ClientMessage:
          if((event.xclient.message_type == WM_PROTOCOLS) && (event.xclient.data.l[0] == WM_DELETE_WINDOW))
          {
            rflag = 0;
          }
          break;
      }
    }
    
    //Get the current time for duration calculation
    gettimeofday(&endtime, 0);

    //Calculate the duration in micro seconds
    duration = ((endtime.tv_sec - starttime.tv_sec) * 1000000) + (endtime.tv_usec - starttime.tv_usec);

    //Check if 400mS have passed
    if(duration > 400000)
    {
      //Get a new current time for duration calculation
      gettimeofday(&starttime, 0);
      
      //Go and handle cursor blinking
      blinkcursor();
    }
    
    //Update the parameters based on the settings when changed
    checksettingsupdate(0);
    checksettingsupdate(1);
    
    //Signal generator is ready for business
    signalgeneratorready = 1;
    
    //Check if the signal generation is not frozen
    if(signalgeneratorfrozen == 0)
    {
      //Keep the signal phase running
      signalstep(0);
      signalstep(1);
    }
    else if(signalgeneratorfrozen == 1)
    {
      //Signal freeze has been acknowledged
      signalgeneratorfrozen = 2;
    }
  }

  //Cleanup on close  
  XftColorFree(display, signalgeneratorxc.visual, signalgeneratorxc.cmap, &signalgeneratorxc.color[0]);
  XftColorFree(display, signalgeneratorxc.visual, signalgeneratorxc.cmap, &signalgeneratorxc.color[1]);
  XftColorFree(display, signalgeneratorxc.visual, signalgeneratorxc.cmap, &signalgeneratorxc.color[2]);
  XftColorFree(display, signalgeneratorxc.visual, signalgeneratorxc.cmap, &signalgeneratorxc.color[3]);
  
  XftDrawDestroy(signalgeneratorxc.draw);
  
  //Signal window no longer available for messages
  WM_PROTOCOLS = 0;
  WM_DELETE_WINDOW = 0;
  
  //Throw away the window and close up the display
  XDestroyWindow(display, win);
	XCloseDisplay(display);
  
  //Signal signal generator window stopped
  signal_generator_still_running = 0;
  
  //Exit the thread the way it is supposed to
  pthread_exit(NULL);
}

//----------------------------------------------------------------------------------------------------------------------------------

//Function for drawing the front panel and all the objects on it
void DrawSignalGeneratorFrontPanel(tagXlibContext *xc)
{
  int i,n;
  int edgecolor;
  int coloradd;
  int x,y,w,h,r;
  
  //Draw the signal generator window outline
  DrawFillRoundedRect(xc, 0, 0, 12, DESIGN_WIDTH, DESIGN_HEIGHT, PanelColor, BorderColor, 1);

  //Setup color adding variable
  coloradd  = 0x020202;

  //1400 x 800
  //Setup for drawing the inside edge of the analyzer screen
  x = 72;
  y = 72;
  w = 804;
  h = 484;
  
  edgecolor = 0xBBB1A2;

  //Draw the inside edge of the analyzer screen
  for(i=0;i<20;i++)
  {
    DrawRect(xc, x, y, w, h, edgecolor, 4);

    h += 4;
    w += 4;
    x -= 2;
    y -= 2;

    edgecolor += coloradd;
  }
  
  //Setup for drawing the outside edge of the analyzer screen
  x = 14;
  y = 14;
  r = 44;
  w = 920;
  h = 600;

  edgecolor = 0xCFC5B6;

  //Draw the oudside edge of the analyzer screen
  for(i=0;i<10;i++)
  {
    DrawRoundedRect(xc, x, y, r, w, h, edgecolor, 4);

    h -= 4;
    w -= 4;
    r -= 1;
    x += 2;
    y += 2;

    edgecolor += coloradd;
  }
  
  //Clear the display
  FillRect(xc, 74, 74, 800, 480, ScreenBackgroundColor);

  //Draw the lines around the different control sections
  DrawRoundedRect(xc, MODE_XPOS, MODE_YPOS, 18, MODE_WIDTH, MODE_HEIGHT, PanelLineColor, 2);
  
  DrawRoundedRect(xc, CONTROL_XPOS, CONTROL_YPOS, 18, CONTROL_WIDTH, CONTROL_HEIGHT, PanelLineColor, 2);
  
  DrawRoundedRect(xc, CHANNEL1_XPOS, CHANNEL_YPOS, 18, CHANNEL_WIDTH, CHANNEL_HEIGHT, PanelLineColor, 2);
  DrawRoundedRect(xc, CHANNEL2_XPOS, CHANNEL_YPOS, 18, CHANNEL_WIDTH, CHANNEL_HEIGHT, PanelLineColor, 2);
  
  //Setup all the rotary dials
  n = sizeof(rotarydials) / sizeof(tagRotaryDial);
  for(i=0;i<n;i++)
    RotaryDialSetup(xc, &rotarydials[i]);
   
  //Setup all the buttons
  n = sizeof(buttons) / sizeof(tagButton);
  for(i=0;i<n;i++)
    ButtonSetup(xc, &buttons[i]);

  //Place all the texts
  n = sizeof(texts) / sizeof(tagPlaceText);
  for(i=0;i<n;i++)
    PlaceText(xc, texts[i].x, texts[i].y, texts[i].text, texts[i].fontid, texts[i].colorid, texts[i].align);

  //Setup all the leds
  n = sizeof(leds) / sizeof(tagLed);
  for(i=0;i<n;i++)
    LedSetup(xc, &leds[i]);

  //Show the initial led states
  LedSetState(&leds[CHANNEL1_ENABLE_LED], channelsettings[0].channelenable);
  LedSetState(&leds[CHANNEL1_PULSE_WIDTH_ENABLE_LED], channelsettings[0].pulsewidthenable);

  LedSetState(&leds[CHANNEL2_ENABLE_LED], channelsettings[1].channelenable);
  LedSetState(&leds[CHANNEL2_PULSE_WIDTH_ENABLE_LED], channelsettings[1].pulsewidthenable);

  currentmagnitude = channelsettings[0].frequencymagnitude;
  
  switch(channelsettings[0].frequencymagnitude)
  {
    default:
    case 0:
      LedSetState(&leds[MAGNITUDE_HZ_LED], 1);
      break;

    case 1:
      LedSetState(&leds[MAGNITUDE_KHZ_LED], 1);
      break;

    case 2:
      LedSetState(&leds[MAGNITUDE_MHZ_LED], 1);
      break;
  }
  
  LedSetState(&leds[SELECT_CHANNEL1_LED], 1);
  
  //Show the current signal setups on the screen
  SignalGeneratorShowSignal(xc, 0);
  SignalGeneratorShowSignal(xc, 1);
}

//----------------------------------------------------------------------------------------------------------------------------------

const char *waveforms[NUMBER_OF_WAVEFORMS] =
{
  "Sine",
  "Square",
  "Triangle",
  "Ramp up",
  "Ramp down"  
};

//----------------------------------------------------------------------------------------------------------------------------------

void SignalGeneratorShowSignal(tagXlibContext *xc, int channel)
{
  int i;
  int x1 = CHANNEL_DISPLAY_XPOS;
  int x2;
  int y1 = CHANNEL_DISPLAY_YPOS;
  int y2;
  
  char *ptr = "CHANNEL 1";

  //Check if second channel requested
  if(channel)
  {
    //Offset the display location
    x1 += CHANNEL_DISPLAY_X_OFFSET;
    
    ptr = "CHANNEL 2";
  }
  
  x2 = x1 + VERTICAL_TEXT_X2_OFFSET;
  PlaceText(xc, x2, CHANNEL_DISPLAY_HEADER_Y, ptr, 1, BrightTextColorId, ALIGN_TEXT_CENTER);
  
  //Determine the amplitude texts based on amplitude and dc offset
  double min = -1 * channelsettings[channel].maxamplitude;
  double amax = channelsettings[channel].dcoffset + channelsettings[channel].amplitude;
  double amin = channelsettings[channel].dcoffset - channelsettings[channel].amplitude;
  
  //Limit on the outer limits based on max amplitude
  if(amax > channelsettings[channel].maxamplitude)
  {
    amax = channelsettings[channel].maxamplitude;
  }
  else if(amax < min)
  {
    amax = min;
  }
  
  //Limit on the outer limits based on max amplitude
  if(amin > channelsettings[channel].maxamplitude)
  {
    amin = channelsettings[channel].maxamplitude;
  }
  else if(amin < min)
  {
    amin = min;
  }

  //Calculate the center voltage  
  double amid = amax - ((amax - amin) / 2);
  
  //Determine the x location for printing the texts
  x2 = x1 + VERTICAL_TEXT_X1_OFFSET;
  
  //Print the max voltage at the top
  snprintf(textbuffer, sizeof(textbuffer), "%+2.2fV", amax);
  PlaceText(xc, x2, VERTICAL_TEXT_Y1, textbuffer, 3, BrightTextColorId, ALIGN_TEXT_RIGHT);
  
  //Print the center voltage at the middle
  snprintf(textbuffer, sizeof(textbuffer), "%+2.2fV", amid);
  PlaceText(xc, x2, VERTICAL_TEXT_Y2, textbuffer, 3, BrightTextColorId, ALIGN_TEXT_RIGHT);
  
  //Print the min voltage at the bottom
  snprintf(textbuffer, sizeof(textbuffer), "%+2.2fV", amin);
  PlaceText(xc, x2, VERTICAL_TEXT_Y3, textbuffer, 3, BrightTextColorId, ALIGN_TEXT_RIGHT);

  //Draw the left ruler 
  x2 = x1 + VERTICAL_LINE_X1_OFFSET;
  DrawLine(xc, x2, VERTICAL_LINE_Y1, x2, VERTICAL_LINE_Y2, ScreenLineColor, 1);
  
  //With its tick lines
  for(i=0;i<19;i++)
  {
    if((i == 0) || (i == 18))
    {
      x2 = x1 + VERTICAL_LINE_X2_OFFSET;
    }
    else if(i == 9)
    {
      x2 = x1 + VERTICAL_LINE_X3_OFFSET;
    }
    else
    {
      x2 = x1 + VERTICAL_LINE_X1_OFFSET;
    }
    
    DrawLine(xc, x1, y1, x2, y1, ScreenLineColor, 1);
    
    y1 += VERTICAL_SPACER;
  }

  //Draw the time texts based on the frequency and pulse width settings
  if(channelsettings[channel].frequency)
  {
    //Only show time when the signal has a frequency
    double pw = channelsettings[channel].pulsewidth / 100.0;

    //Check if pulse width is turned off
    if(channelsettings[channel].pulsewidthenable == 0)
    {
      //Use 50% if so
      pw = 0.5;
    }
    
    double periodtime = 1 / channelsettings[channel].frequency;
    double pwtime = periodtime * pw;
    
    int x3 = x1 + HORIZONTAL_SIGNAL_CENTER;
    int x4 = x1 + (HORIZONTAL_SIGNAL_WIDTH * 0.25);
    
    //First tick is always 0s
    x2 = x1 + HORIZONTAL_TEXT_X1_OFFSET;
    PlaceText(xc, x2, HORIZONTAL_TEXT_Y2, "0s", 3, BrightTextColorId, ALIGN_TEXT_CENTER);

    //Prepare the zero crossing text for displaying
    formatwavetime(pwtime);
    
    //For the zero crossing point the duty cycle determines where the text needs to be placed
    //Also need to flip the text when it no longer fits in relation to the zero and the period ticks
    x2 = x1 + (HORIZONTAL_SIGNAL_WIDTH * pw) + HORIZONTAL_LINE_X2_OFFSET;
    
    if(x2 < x4)
    {
      //Draw indicator and text with left alignment
      DrawLine(xc, x2, HORIZONTAL_LINE_Y2, x2, HORIZONTAL_LINE_Y5, ScreenSignalColor, 1);
      DrawLine(xc, x2, HORIZONTAL_LINE_Y5, x2 + 4, HORIZONTAL_LINE_Y5, ScreenSignalColor, 1);
      PlaceText(xc, x2 + 6, HORIZONTAL_TEXT_Y1, textbuffer, 3, BrightTextColorId, ALIGN_TEXT_LEFT);
    }
    else if(x2 == x3)
    {
      //Center text can do without indicator and needs to be centered
      PlaceText(xc, x2, HORIZONTAL_TEXT_Y1, textbuffer, 3, BrightTextColorId, ALIGN_TEXT_CENTER);
    }
    else
    {
      //Draw indicator and text with right alignment 
      DrawLine(xc, x2, HORIZONTAL_LINE_Y2, x2, HORIZONTAL_LINE_Y5, ScreenSignalColor, 1);
      DrawLine(xc, x2, HORIZONTAL_LINE_Y5, x2 - 4, HORIZONTAL_LINE_Y5, ScreenSignalColor, 1);
      PlaceText(xc, x2 - 6, HORIZONTAL_TEXT_Y1, textbuffer, 3, BrightTextColorId, ALIGN_TEXT_RIGHT);
    }
    
    //Last tick is the full cycle time
    x2 = x1 + HORIZONTAL_TEXT_X3_OFFSET;
    formatwavetime(periodtime);
    PlaceText(xc, x2, HORIZONTAL_TEXT_Y2, textbuffer, 3, BrightTextColorId, ALIGN_TEXT_CENTER);
  }
  
  //Draw the bottom ruler
  DrawLine(xc, x1 + HORIZONTAL_LINE_X1_OFFSET, HORIZONTAL_LINE_Y2, x1 + HORIZONTAL_LINE_X3_OFFSET, HORIZONTAL_LINE_Y2, ScreenLineColor, 1);

  //With its tick lines
  x2 = x1 + HORIZONTAL_LINE_X2_OFFSET;
  
  for(i=0;i<25;i++)
  {
    if((i == 0) || (i == 24))
    {
      y1 = HORIZONTAL_LINE_Y1;
      y2 = HORIZONTAL_LINE_Y6;
    }
    else if(i == 12)
    {
      y1 = HORIZONTAL_LINE_Y1;
      y2 = HORIZONTAL_LINE_Y4;
    }
    else
    {
      y1 = HORIZONTAL_LINE_Y2;
      y2 = HORIZONTAL_LINE_Y3;
    }
    
    DrawLine(xc, x2, y1, x2, y2, ScreenLineColor, 1);
    
    x2 += HORIZONTAL_SPACER;
  }

  //Check if signal has frequency and amplitude
  if((channelsettings[channel].frequency > 0) && (channelsettings[channel].amplitude > 0))
  {
    //Draw the signal here based on the current channel
    SignalGeneratorDrawSignal(xc, x1 + HORIZONTAL_LINE_X2_OFFSET, channel);
  }
  else
  {
    //Otherwise draw a straight dc line
    y1 = CHANNEL_DISPLAY_YPOS + (SIGNAL_HEIGHT / 2);
    
    //Check if line not on center line
    if(channelsettings[channel].dcoffset != amid)
    {
      y1 = y1 - (((channelsettings[channel].dcoffset - amid) * SIGNAL_HEIGHT) / channelsettings[channel].maxamplitude);
    }
    
    DrawLine(xc, x1 + HORIZONTAL_LINE_X2_OFFSET, y1, x1 + HORIZONTAL_LINE_X3_OFFSET - 8, y1, ScreenSignalColor, 1);
  }
  
  //Display the channel settings
  x2 = x1 - 50;
  PlaceText(xc, x2, SETTINGS_TEXT_Y1, "Waveform:",      3, BrightTextColorId, ALIGN_TEXT_LEFT);
  PlaceText(xc, x2, SETTINGS_TEXT_Y2, "Frequency:",     3, BrightTextColorId, ALIGN_TEXT_LEFT);
  PlaceText(xc, x2, SETTINGS_TEXT_Y3, "Phase:",         3, BrightTextColorId, ALIGN_TEXT_LEFT);
  PlaceText(xc, x2, SETTINGS_TEXT_Y4, "Pulse width:",   3, BrightTextColorId, ALIGN_TEXT_LEFT);
  PlaceText(xc, x2, SETTINGS_TEXT_Y5, "Max amplitude:", 3, BrightTextColorId, ALIGN_TEXT_LEFT);
  PlaceText(xc, x2, SETTINGS_TEXT_Y6, "Amplitude:",     3, BrightTextColorId, ALIGN_TEXT_LEFT);
  PlaceText(xc, x2, SETTINGS_TEXT_Y7, "DC offset:",     3, BrightTextColorId, ALIGN_TEXT_LEFT);

  x2 = x1 + 55;
  PlaceText(xc, x2, SETTINGS_TEXT_Y1, (char *)waveforms[channelsettings[channel].waveform], 3, BrightTextColorId, ALIGN_TEXT_LEFT);
  
  snprintf(textbuffer, sizeof(textbuffer), "%.2fHz", channelsettings[channel].frequency);
  PlaceText(xc, x2, SETTINGS_TEXT_Y2, textbuffer, 3, BrightTextColorId, ALIGN_TEXT_LEFT);

  snprintf(textbuffer, sizeof(textbuffer), "%3.2f degree", channelsettings[channel].phase);
  PlaceText(xc, x2, SETTINGS_TEXT_Y3, textbuffer, 3, BrightTextColorId, ALIGN_TEXT_LEFT);
  
  snprintf(textbuffer, sizeof(textbuffer), "%2.2f%%", channelsettings[channel].pulsewidth);
  
  //Use either the dimmed or the bright color based on the setting being enabled or not
  if(channelsettings[channel].pulsewidthenable)
  {
    //Enabled so bright text
    PlaceText(xc, x2, SETTINGS_TEXT_Y4, textbuffer, 3, BrightTextColorId, ALIGN_TEXT_LEFT);
  }
  else
  {
    //Disabled so dimmed text
    PlaceText(xc, x2, SETTINGS_TEXT_Y4, textbuffer, 3, DimmedTextColorId, ALIGN_TEXT_LEFT);
  }

  snprintf(textbuffer, sizeof(textbuffer), "%2.3fV", channelsettings[channel].maxamplitude);
  PlaceText(xc, x2, SETTINGS_TEXT_Y5, textbuffer, 3, BrightTextColorId, ALIGN_TEXT_LEFT);
  
  snprintf(textbuffer, sizeof(textbuffer), "%2.3fV", channelsettings[channel].amplitude);
  PlaceText(xc, x2, SETTINGS_TEXT_Y6, textbuffer, 3, BrightTextColorId, ALIGN_TEXT_LEFT);

  snprintf(textbuffer, sizeof(textbuffer), "%2.3fV", channelsettings[channel].dcoffset);
  PlaceText(xc, x2, SETTINGS_TEXT_Y7, textbuffer, 3, BrightTextColorId, ALIGN_TEXT_LEFT);
  
  //If an item of this channel is being edited show it on the screen
  displayedititem(channel);
  
  //Make sure the change is processed on screen
  XFlush(xc->display);
}

//----------------------------------------------------------------------------------------------------------------------------------

void SignalGeneratorDrawSignal(tagXlibContext *xc, int xpos, int channel)
{
  int    x,i,j;
  double yc,y1,y2,y3;
  
  double wp,p,d,s,co;
  
  double amx = channelsettings[channel].maxamplitude;
  double amn = -1 * amx;
  
  double smx = channelsettings[channel].dcoffset + channelsettings[channel].amplitude;
  double smn = channelsettings[channel].dcoffset - channelsettings[channel].amplitude;
  
  double pw = channelsettings[channel].pulsewidth;
  
  //Check if pulse width is turned off
  if(channelsettings[channel].pulsewidthenable == 0)
  {
    //Use 50% if so
    pw = 50;
  }
  
  //Determine max signal value
  if(smx > amx)
    smx = amx;
  
  //Determine min signal value
  if(smn < amn)
    smn = amn;
  
  //Calculate the needed scaler for drawing on the screen
  s = SIGNAL_HEIGHT / (smx - smn);
  
  //Calculate where the center offset is
  co = -1 * (smx - ((smx - smn) / 2));
  
  yc = CHANNEL_DISPLAY_YPOS + (SIGNAL_HEIGHT / 2);

  wp = (SIGNAL_WIDTH * pw) / 100;
  p = PI;
  d = -1 * channelsettings[channel].dcoffset;
  x = xpos;

  //Calculate the first pixel
  y1 = d + (calcsample(channelsettings[channel].waveform, pw, PI2) * channelsettings[channel].amplitude);

  //Limit to extremes
  if(y1 > amx)
  {
    y1 = amx;
  }
  else if(y1 < amn)
  {
    y1 = amn;
  }

  //Take center offset out and scale to display size and set offset to position
  y1 = yc + ((y1 - co) * s);
  
  //Save for last pixel
  y3 = y1;
  
  //Process both parts of the signal (top and bottom)
  for(j=0;j<2;j++)
  {
    //Check if current part has energy
    if(wp > 0)
    {
      for(i=1;i<=wp;i++,x++)
      {
        //Calculate sample based on amplitude and offset
        y2 = d + (calcsample(channelsettings[channel].waveform, pw, (((wp - i) / wp) * PI) + p) * channelsettings[channel].amplitude);

        //Limit to extremes
        if(y2 > amx)
        {
          y2 = amx;
        }
        else if(y2 < amn)
        {
          y2 = amn;
        }

        //Take center offset out and scale to display size and set offset to position
        y2 = yc + ((y2 - co) * s);

        //Draw the line segment
        DrawLine(xc, x, y1, x + 1, y2, ScreenSignalColor, 1);
        
        //Save the previous point
        y1 = y2;
      }
    }

    //Calculate width of bottom part
    wp = SIGNAL_WIDTH - wp;
    p = 0;
  }
  
  //Draw a line to center level to finish it of
  DrawLine(xc, x, y1, x + 1, y3, ScreenSignalColor, 1);
}

//----------------------------------------------------------------------------------------------------------------------------------

double calcsample(int waveform, double pulsewidth, double phase)
{
  double sample = 0.0;
  
  switch(waveform)
  {
    default:
    case 0:  //Sine
      sample = sin(phase);
      break;
      
    case 1:  //Square
      if(pulsewidth == 0)
      {
        sample = 1;
      }
      else if(pulsewidth == 100)
      {
        sample = -1;
      }
      else if(phase == 0)
      {
        sample= 0;
      }
      else if(phase < Q2PI)
      {
        sample = 1;
      }
      else if(phase == Q2PI)
      {
        sample = 0;
      }
      else if(phase < Q4PI)
      {
        sample = -1;
      }
      else if(phase == Q4PI)
      {
        sample = 0;
      }
      break;

    case 2:  //Triangle
      if(phase < Q1PI)
      {
        sample = phase / Q1PI;
      }
      else if(phase < Q2PI)
      {
        sample = 1 - ((phase - Q1PI) / Q1PI);
      }
      else if(phase < Q3PI)
      {
        sample = -1 * ((phase - Q2PI) / Q1PI);
      }
      else
      {
        sample = -1 * (1 - ((phase - Q3PI) / Q1PI));
      }
      break;
      
    case 3: //Ramp up
      if(phase < Q2PI)
      {
        sample = phase / Q2PI;
      }
      else if(phase == Q2PI)
      {
        sample = 0;
      }
      else if(phase < Q4PI)
      {
        sample = -1 * (1 - ((phase - Q2PI) / Q2PI));
      }
      else if(phase == Q4PI)
      {
        sample = 0;
      }
      break;
      
    case 4: //Ramp down
      if(phase < Q2PI)
      {
        sample = 1 - (phase / Q2PI);
      }
      else if(phase == Q2PI)
      {
        sample = 0;
      }
      else if(phase < Q4PI)
      {
        sample = -1 * ((phase - Q2PI) / Q2PI);
      }
      else if(phase == Q4PI)
      {
        sample = 0;
      }
      break;
  }
  
  return(sample);
}

//----------------------------------------------------------------------------------------------------------------------------------

void formatwavetime(double time)
{
  char *magnitude = "s";
  
  //Check if in nanosecond range
  if(time < 0.000001)
  {
    magnitude = "ns";
    time *= 1000000000;
  }
  //Check if in micro second range
  else if(time < 0.001)
  {
    magnitude = "us";
    time *= 1000000;
  }
  //Check if in milli second range
  else if(time < 1)
  {
    magnitude = "ms";
    time *= 1000;
  }

  snprintf(textbuffer, sizeof(textbuffer), "%.2f%s", time, magnitude);
}

//--------------------------------------------------------------------------------------------------

double triangle(double phase)
{
  double sample = 0;
  
  if(phase < Q1PI)
    sample = phase / Q1PI;
  else if(phase < Q2PI)
    sample = 1 - ((phase - Q1PI) / Q1PI);
  else if(phase < Q3PI)
    sample = -1 * ((phase - Q2PI) / Q1PI);
  else
    sample = -1 * (1 - ((phase - Q3PI) / Q1PI));
  
  return(sample);
}

//--------------------------------------------------------------------------------------------------

double rampup(double phase)
{
  double sample = 0;
  
  if(phase < Q2PI)
    sample = phase / Q2PI;
  else if(phase == Q2PI)
    sample = 0;
  else if(phase < Q4PI)
    sample = -1 * (1 - ((phase - Q2PI) / Q2PI));
  else if(phase == Q4PI)
    sample = 0;
  
  return(sample);
}

//--------------------------------------------------------------------------------------------------

double rampdown(double phase)
{
  double sample = 0;
  
  if(phase < Q2PI)
    sample = 1 - (phase / Q2PI);
  else if(phase == Q2PI)
    sample = 0;
  else if(phase < Q4PI)
    sample = -1 * ((phase - Q2PI) / Q2PI);
  else if(phase == Q4PI)
    sample = 0;
  
  return(sample);
}

//----------------------------------------------------------------------------------------------------------------------------------

void signalgeneratorfreeze(void)
{
  signalgeneratorfrozen = 1;
}

//----------------------------------------------------------------------------------------------------------------------------------

void signalgeneratorunfreeze(void)
{
  signalgeneratorfrozen = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------

void signalgeneratorgetsamples(int channel, double *buffer, int count, double samplerate)
{
  int i;
  double sample;
  
  double sampletimestep = 1.0 / samplerate;
  double signalphase;
  
  int periods;
  
  if((signalgeneratorready == 0) || (channelsettings[channel].channelenable == 0) || channelsettings[channel].frequency == 0)
  {
    for(i=0;i<count;i++)
    {
      //Return a zero buffer if not ready or channel switched off or frequency is 0
      *buffer++ = 0.0;
    }
  }
  else
  {
    //Make the samples    
    for(i=0;i<count;i++)
    {
      //Determine the signal phase based on the scope sample rate and the signal period
      channelsettings[channel].signaltime += sampletimestep;
      
      //Take of the full signal periods
      periods = channelsettings[channel].signaltime / channelsettings[channel].signalperiod;
      channelsettings[channel].signaltime -= (periods * channelsettings[channel].signalperiod);

      //Check if in positive part of the signal
      if(channelsettings[channel].signaltime < channelsettings[channel].signaltimepart1)
      {
        //Determine the signal phase in radians for the positive part of the signal
        signalphase = (channelsettings[channel].signaltime / channelsettings[channel].signaltimepart1) * PI;
        
      }
      else
      {
        //Determine the signal phase in radians for the negative part of the signal
        signalphase = PI + (((channelsettings[channel].signaltime - channelsettings[channel].signaltimepart1) / channelsettings[channel].signaltimepart2) * PI);
      }
      
      //Take action based on the selected waveform
      switch(channelsettings[channel].waveform)
      {
        //Sine wave
        default:
        case 0:
          sample = channelsettings[channel].amplitude * sin(signalphase);
          break;

        //Square wave
        case 1:
          if(signalphase < PI)    
            sample = channelsettings[channel].amplitude;
          else
            sample = -1 * channelsettings[channel].amplitude;
          break;

        //Triangle wave
        case 2:
          sample = channelsettings[channel].amplitude * triangle(signalphase);
          break;

        //Ramp up wave
        case 3:
          sample = channelsettings[channel].amplitude * rampup(signalphase);
          break;

        //Ramp down wave
        case 4:
          sample = channelsettings[channel].amplitude * rampdown(signalphase);
          break;
      }

      //Add the DC offset
      sample += channelsettings[channel].dcoffset;

      //Check if sample within the signal limits
      if(sample < channelsettings[channel].minsignal)
      {
        //Below then limit on minimum value
        sample = channelsettings[channel].minsignal;
      }
      else if(sample > channelsettings[channel].maxsignal)
      {
        //Above then limit on maximum value
        sample = channelsettings[channel].maxsignal;
      }

      //Store the sample in the buffer
      *buffer++ = sample;
    }  
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void checksettingsupdate(int channel)
{
  double phasediff;
  
  //Check if any signal frequency related setting has changed
  if(channelsettings[channel].frequencychanged || channelsettings[channel].pulsewidthchanged || channelsettings[channel].pulsewidthenablechanged)
  {
    //Signal all changes handled
    channelsettings[channel].frequencychanged        = 0;
    channelsettings[channel].pulsewidthchanged       = 0;
    channelsettings[channel].pulsewidthenablechanged = 0;

    channelsettings[channel].signalperiod   = 1.0 / channelsettings[channel].frequency;
    channelsettings[channel].signaltimestep = 1.0 / SIGNAL_GENERATOR_SAMPLE_RATE;

    //Check if pulse width is enabled
    if(channelsettings[channel].pulsewidthenable)
    {
      //Calculate the time per signal part based on the pulse width setting
      channelsettings[channel].signaltimepart1 = (channelsettings[channel].pulsewidth / 100.0) * channelsettings[channel].signalperiod;
      channelsettings[channel].signaltimepart2 = ((100.0 - channelsettings[channel].pulsewidth) / 100.0) * channelsettings[channel].signalperiod;
    }
    else
    {
      //Calculate the time per signal part based on 50% pulse width
      channelsettings[channel].signaltimepart1 = 0.5 * channelsettings[channel].signalperiod;
      channelsettings[channel].signaltimepart2 = channelsettings[channel].signaltimepart1;
    }
  }

  //Check if the phase has been changed
  if(channelsettings[channel].phasechanged)
  {
    //Signal change has been handled
    channelsettings[channel].phasechanged = 0;

    //Calculate the difference between the two phase for adjusting the signal
    phasediff = channelsettings[channel].phase - channelsettings[channel].previousphase;
    
    //Save the new phase for next change
    channelsettings[channel].previousphase = channelsettings[channel].phase;
    
    //Shift the signal with the phase difference
//    channelsettings[channel].signalphase += phasediff;
  }

  //Not really needed for now, but when max amplitude can be changed it is
  if(channelsettings[channel].amplitudechanged || channelsettings[channel].dcoffsetchanged)
  {
    channelsettings[channel].amplitudechanged = 0;
    channelsettings[channel].dcoffsetchanged  = 0;
    
    channelsettings[channel].maxsignal = channelsettings[channel].maxamplitude;
    channelsettings[channel].minsignal = -1 * channelsettings[channel].maxamplitude;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void signalstep(int channel)
{
  //Keep the signal time running
  channelsettings[channel].signaltime += channelsettings[channel].signaltimestep;
  
  //Check if beyond period time
  if(channelsettings[channel].signaltime > channelsettings[channel].signalperiod)
  {
    //Keep it in range of the period time
    channelsettings[channel].signaltime -= channelsettings[channel].signalperiod;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
