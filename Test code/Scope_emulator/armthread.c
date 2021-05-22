//----------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "xlibfunctions.h"

#include "mousehandling.h"

#include "lcdisplay.h"
#include "buttons.h"

#include "armthread.h"
#include "armv5tl.h"

//----------------------------------------------------------------------------------------------------------------------------------

int DrawArmPanel(tagXlibContext *xc);

void UpdateArmPanel(tagXlibContext *xc, PARMV5TL_CORE core);

//----------------------------------------------------------------------------------------------------------------------------------

#define DESIGN_WIDTH       1100
#define DESIGN_HEIGHT      1000

//----------------------------------------------------------------------------------------------------------------------------------

#define TextColor               "#D5D5D5"
#define LogoColor               "#858585"

#define ArmLineColor            0x000000
#define ArmPanelColor           0x414244

//----------------------------------------------------------------------------------------------------------------------------------

const tagPlaceText texts[] =
{
  //Text, xpos, ypos, fontid, colorid, align
  //All header texts with 20pt font
  { "PROCESSOR STATUS",  190,  32, 0, 0, ALIGN_TEXT_CENTER },
  { "REGISTERS",         530,  32, 0, 0, ALIGN_TEXT_CENTER },
  { "STACK",             870,  32, 0, 0, ALIGN_TEXT_CENTER },
  { "DISASSEMBLY",       265, 382, 0, 0, ALIGN_TEXT_CENTER },
  { "MEMORY",            802, 382, 0, 0, ALIGN_TEXT_CENTER },
  { "Scroll",           1060, 196, 0, 0, ALIGN_TEXT_CENTER },
  { "Scroll",            524, 616, 0, 0, ALIGN_TEXT_CENTER },
  { "Scroll",           1060, 616, 0, 0, ALIGN_TEXT_CENTER },
  { "Reset",              78, 890, 0, 0,   ALIGN_TEXT_LEFT },
  { "Run / Stop",         78, 930, 0, 0,   ALIGN_TEXT_LEFT },
  { "Single step",        78, 970, 0, 0,   ALIGN_TEXT_LEFT },
};

tagLcDisplay lcdisplays[] =
{
  //  xc, xpos, ypos, chars, lines,          offcolor,          oncolor,                  bgcolor,           ledgecolor,          bredgecolor
  { NULL,   40,   40,    24,    16, LcDisplayOffColor, LcDisplayOnColor, LcDisplayBackGroundColor, LcDisplaytledgecolor, LcDisplaybredgecolor },
  { NULL,  380,   40,    24,    16, LcDisplayOffColor, LcDisplayOnColor, LcDisplayBackGroundColor, LcDisplaytledgecolor, LcDisplaybredgecolor },
  { NULL,  720,   40,    24,    16, LcDisplayOffColor, LcDisplayOnColor, LcDisplayBackGroundColor, LcDisplaytledgecolor, LcDisplaybredgecolor },
  { NULL,   40,  390,    36,    24, LcDisplayOffColor, LcDisplayOnColor, LcDisplayBackGroundColor, LcDisplaytledgecolor, LcDisplaybredgecolor },
  { NULL,  576,  390,    36,    24, LcDisplayOffColor, LcDisplayOnColor, LcDisplayBackGroundColor, LcDisplaytledgecolor, LcDisplaybredgecolor },
};

//All the buttons on the front panel
tagButton buttons[] = 
{
  //        Mouserange set here to make a linked list. Search for object under mouse pointer needs to be done from last to first based on previous pointer
  //  xc,                 action,             previous, left, right, top, bottom, move, down,   up,  out,                 type, xpos, ypos, 
  { NULL,                   NULL, {               NULL,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,   40,  867, 0 },
  { NULL,                   NULL, {  &buttons[0].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,   40,  907, 0 },
  { NULL,                   NULL, {  &buttons[1].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,   40,  947, 0 },
  { NULL,                   NULL, {  &buttons[2].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },        BUTTON_ARROW_UP, 1045,  146, 0 },
  { NULL,                   NULL, {  &buttons[3].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },      BUTTON_ARROW_DOWN, 1045,  204, 0 },
  { NULL,                   NULL, {  &buttons[4].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },        BUTTON_ARROW_UP,  509,  566, 0 },
  { NULL,                   NULL, {  &buttons[5].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },      BUTTON_ARROW_DOWN,  509,  624, 0 },
  { NULL,                   NULL, {  &buttons[6].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },        BUTTON_ARROW_UP, 1045,  566, 0 },
  { NULL,                   NULL, {  &buttons[7].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },      BUTTON_ARROW_DOWN, 1045,  624, 0 },
};

//Set pointer to last mouse range for scanning
MouseRange *mouseranges = &buttons[8].mouse;

//----------------------------------------------------------------------------------------------------------------------------------

pthread_t arm_emulator_thread;

int quit_armemulator_thread_on_zero = 0;

//ID's for communication between the threads and the main window
Window arm_window_id = 0;
Window arm_msg_id = 0;

//----------------------------------------------------------------------------------------------------------------------------------

int startarmemulator(void)
{
  //Setup for keeping the arm ui window thread running
  quit_armemulator_thread_on_zero = 1;
  
  //Start up the led blink thread
  return(pthread_create(&arm_emulator_thread, NULL, armemulatorthread, NULL));
}

//----------------------------------------------------------------------------------------------------------------------------------

void stoparmemulator(void)
{
  //Stop the arm ui window thread
  quit_armemulator_thread_on_zero = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------

void *armemulatorthread(void *arg)
{
  //The arm core needs to be readable from here to be able to get to the display data
  //Setup a key for getting the shared memory
  key_t key = SHARED_MEMORY_KEY;
 
  //Get a handle to the shared memory
  int shmid = shmget(key, sizeof(ARMV5TL_CORE), 0666 | IPC_CREAT); 

  //Check on error shmid == -1.
  if(shmid == -1)
  {
    //On error exit the thread the way it is supposed to
    pthread_exit(NULL);
  }
  
  //Attach to the shared memory
  PARMV5TL_CORE parm_core = (PARMV5TL_CORE)shmat(shmid, (void*)0, 0);
  
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
  
  //Create atoms for the display messages
  arm_msg_id = XInternAtom(display, "ARM_EMULATOR_MESSAGE", False); 

  //Set the window id for message sending
  arm_window_id = win;
  
	XEvent event;

  double fsize;
  
  int rflag = 1;

  tagXlibContext xc;

  int numsizes;  
  XRRScreenSize *scrsize;
  
  //Get the size of the primary monitor
  scrsize = XRRSizes(display, screen_num, &numsizes);
  
  //For calculations take of a border of 5 pixels for each side
  width  = (scrsize->width - BORDER_SIZE_2) * 0.95;
  height = scrsize->height - BORDER_SIZE_2;
   
  //Determine the scaler based on the width
  xc.scaler = (float)width / (float)DESIGN_WIDTH;

  //See if it scaled fits for the height. If not determine the scaler based on the height
  if((DESIGN_HEIGHT * xc.scaler) > height)
    xc.scaler = (float)height / (float)DESIGN_HEIGHT;
  
  //Check if screen is larger than the desired size
  if(xc.scaler > 1.0)
  {
    //If so keep the scale on 1
    xc.scaler = 1.0;
  }

  //Calculate the new width and height
  width = (DESIGN_WIDTH * xc.scaler) + BORDER_SIZE_2;
  height = (DESIGN_HEIGHT * xc.scaler) + BORDER_SIZE_2;
  
  //Calculate a nice position on the screen
  x = 50;
  y = 50;
  
  //Set the window to the new position and dimensions
  XMoveResizeWindow(display, win, x, y, width, height);
  
  //Setup the data for the drawing functions
  xc.screen_num = screen_num;
  xc.root = root;
  xc.win = win;
  xc.display = display;
  xc.gc = gc;
  
  xc.visual = DefaultVisual(display, screen_num);
  xc.cmap  = DefaultColormap(display, screen_num);
    
  //Create all the used fonts
  fsize = 14 * xc.scaler;
  xc.font[0] = XftFontOpen(display, screen_num, XFT_FAMILY, XftTypeString, "Arial", XFT_WEIGHT, XftTypeInteger, XFT_WEIGHT_BOLD, XFT_SIZE, XftTypeDouble, fsize, XFT_ANTIALIAS, XftTypeBool, True, NULL);

  fsize = 12 * xc.scaler;
  xc.font[1] = XftFontOpen(display, screen_num, XFT_FAMILY, XftTypeString, "Arial", XFT_WEIGHT, XftTypeInteger, XFT_WEIGHT_BOLD, XFT_SIZE, XftTypeDouble, fsize, XFT_ANTIALIAS, XftTypeBool, True, NULL);
  
  //Create the used font colors
  rflag = XftColorAllocName(display, xc.visual, xc.cmap, TextColor, &xc.color[0]);

  rflag = XftColorAllocName(display, xc.visual, xc.cmap, LogoColor, &xc.color[1]);
  
  xc.draw = XftDrawCreate(display, win, xc.visual, xc.cmap);
  
  //Quit on window close or thread being stopped
  while(quit_armemulator_thread_on_zero && rflag)
  {
    if(XPending(display))
    {
      XNextEvent(display, &event);
      switch(event.type)
      {
        case Expose:
          //Setup the screen
          DrawArmPanel(&xc);
          break;

        case KeyPress:
          if(event.xkey.keycode == XKeysymToKeycode(display,XK_Escape))
          {
            rflag = 0;
          }
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
          else if(event.xclient.message_type == arm_msg_id)
          {
            //Here the scope display update needs to be done
  //          LedDisplaySetBCD(&leddisplays[event.xclient.data.l[0]], event.xclient.data.l[1]);
          }
          break;
      }
    }
    
    UpdateArmPanel(&xc, parm_core);
  }

  //Cleanup on close  
  XftColorFree(display, xc.visual, xc.cmap, &xc.color[0]);
  XftColorFree(display, xc.visual, xc.cmap, &xc.color[1]);
  XftDrawDestroy(xc.draw);
  
  //Signal window no longer available for messages
  arm_window_id = 0;
  arm_msg_id = 0;
  WM_PROTOCOLS = 0;
  WM_DELETE_WINDOW = 0;
  
  //Throw away the window and close up the display
  XDestroyWindow(display, win);
	XCloseDisplay(display);
  
  //detach from shared memory  
  shmdt(parm_core);   

  //destroy the shared memory 
  shmctl(shmid, IPC_RMID, NULL); 
  
  //Exit the thread the way it is supposed to
  pthread_exit(NULL);
}

//----------------------------------------------------------------------------------------------------------------------------------

//Function for drawing the frontpanel and all the objects on it
int DrawArmPanel(tagXlibContext *xc)
{
  int i,n;
  char text[32];
  
  //Draw the scope outline
  DrawFillRoundedRect(xc, 0, 0, 8, DESIGN_WIDTH, 1000, ArmPanelColor, ArmLineColor, 1);
  

  //Place the front panels text  
//  PlaceText(xc, 70, 600, "TABLET", 0, 0, ALIGN_TEXT_LEFT);
//  PlaceText(xc, 250, 600, "OSCILLOSCOPE", 1, 0, ALIGN_TEXT_LEFT);

//  PlaceText(xc, 780, 575, "100MHZ", 1, 0, ALIGN_TEXT_LEFT);
//  PlaceText(xc, 780, 600, "1 GSa/s", 1, 0, ALIGN_TEXT_LEFT);

  
  //Place all the texts
  n = sizeof(texts) / sizeof(tagPlaceText);
  for(i=0;i<n;i++)
    PlaceText(xc, texts[i].x, texts[i].y, texts[i].text, texts[i].fontid, texts[i].colorid, texts[i].align);
  
  //Setup all the displays
  n = sizeof(lcdisplays) / sizeof(tagLcDisplay);
  for(i=0;i<n;i++)
    LcdDisplaySetup(xc, &lcdisplays[i]);
  
  //Setup all the buttons
  n = sizeof(buttons) / sizeof(tagButton);
  for(i=0;i<n;i++)
    ButtonSetup(xc, &buttons[i]);
  
  //Display status
  LcdDisplayText(&lcdisplays[0], 0,  0, "MODE[4:0]           USER");
  LcdDisplayText(&lcdisplays[0], 0,  1, "10000                   ");
  LcdDisplayText(&lcdisplays[0], 0,  4, "  CONDITION CODE FLAGS  ");
  LcdDisplayText(&lcdisplays[0], 0,  5, "N  Z  C  V   Q   GE[3:0]");
  LcdDisplayText(&lcdisplays[0], 0,  6, "0  0  0  0   0   0000   ");
  LcdDisplayText(&lcdisplays[0], 0,  9, " INTERRUPT DISABLE BITS ");
  LcdDisplayText(&lcdisplays[0], 0, 10, "        A  I  F         ");
  LcdDisplayText(&lcdisplays[0], 0, 11, "        0  0  0         ");
  LcdDisplayText(&lcdisplays[0], 0, 13, "  EXECUTION STATE BITS  ");
  LcdDisplayText(&lcdisplays[0], 0, 14, "         J  T           ");
  LcdDisplayText(&lcdisplays[0], 0, 15, "         0  0           ");

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------

const char regnames[16][7] =
{
  "R0    ",
  "R1    ",
  "R2    ",
  "R3    ",
  "R4    ",
  "R5    ",
  "R6    ",
  "R7    ",
  "R8    ",
  "R9    ",
  "R10   ",
  "R11   ",
  "R12   ",
  "R13 SP",
  "R14 LR",
  "R15 PC"
};

const char banknames[16][6][4] =
{
  { "   ", "   ", "   ", "   ", "   ", "   " },
  { "   ", "   ", "   ", "   ", "   ", "   " },
  { "   ", "   ", "   ", "   ", "   ", "   " },
  { "   ", "   ", "   ", "   ", "   ", "   " },
  { "   ", "   ", "   ", "   ", "   ", "   " },
  { "   ", "   ", "   ", "   ", "   ", "   " },
  { "   ", "   ", "   ", "   ", "   ", "   " },
  { "   ", "   ", "   ", "   ", "   ", "   " },
  { "usr", "fiq", "usr", "usr", "usr", "usr" },
  { "usr", "fiq", "usr", "usr", "usr", "usr" },
  { "usr", "fiq", "usr", "usr", "usr", "usr" },
  { "usr", "fiq", "usr", "usr", "usr", "usr" },
  { "usr", "fiq", "usr", "usr", "usr", "usr" },
  { "usr", "fiq", "irq", "svc", "abt", "und" },
  { "usr", "fiq", "irq", "svc", "abt", "und" },
  { "   ", "   ", "   ", "   ", "   ", "   " },
};

void UpdateArmPanel(tagXlibContext *xc, PARMV5TL_CORE core)
{
  char displaytext[32];
  int  reg;
  
  //Display registers
  for(reg=0;reg<16;reg++)
  {
    snprintf(displaytext, sizeof(displaytext), "%s  %s   0x%08X", regnames[reg], banknames[reg][core->current_bank], *core->registers[core->current_bank][reg]);
    LcdDisplayText(&lcdisplays[1], 0,  reg, displaytext);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//Function to call for sending the emulator window a message indicating the core executed another instruction
void updateemulatormessage(void)
{
  Display *display;
  XEvent   event;
 
  if(arm_window_id && arm_msg_id)
  {
    display = XOpenDisplay(NULL);
    
    event.xclient.type = ClientMessage;
    event.xclient.display = display;
    event.xclient.window = arm_window_id;
    event.xclient.message_type = arm_msg_id;
    event.xclient.format = 32;

    XSendEvent(display, arm_window_id, False, NoEventMask, &event);
  
    XCloseDisplay(display);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
