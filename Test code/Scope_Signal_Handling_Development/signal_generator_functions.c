//----------------------------------------------------------------------------------------------------------------------------------

#include <math.h>

#include "signal_generator.h"
#include "signal_generator_functions.h"

//----------------------------------------------------------------------------------------------------------------------------------


//Need a system with function pointers to assign the different actions to the enter and cancel key's


extern SIGNALGENERATORCHANNELSETTINGS channelsettings[2];
extern tagLed leds[];

extern const char *waveforms[5];

extern int currentchannel;
extern int currentmagnitude;

extern char textbuffer[128];

extern tagXlibContext signalgeneratorxc;

//----------------------------------------------------------------------------------------------------------------------------------
//The mode items can handle multiple pushes. For this the current selected item is remembered

int currentselecteditem = -1;

char  *edititemheader   = NULL;
char  *edititemtext     = NULL;
char  *edititemtypetext = NULL;
char **edititemlist     = NULL;

int edititemcount = 0;
int edititemvalue = 0;
int edititemstate = 0;

double edititemdouble         = 0.0;
double edititemmindouble      = 0.0;
double edititemmaxdouble      = 0.0;
double edititemaddfactor      = 0.0;
double edititemdecimaldivider = 0.0;

int edititemnumberofdecimals = 0;
int edititemcursorfromend    = 0;
int edititemfreqdisplaymode  = 0;
int edititemdecimalcount     = 0;

//----------------------------------------------------------------------------------------------------------------------------------

char mintextbuffer[128];
char maxtextbuffer[128];

char formatstring[20];

//----------------------------------------------------------------------------------------------------------------------------------

char *cursortext;
int   cursorfontid;
int   cursortextcolorid;
int   cursoralign;
int   cursorbgcolor;
int   cursorfgcolor;
int   cursorposition;
int   cursortextxpos;
int   cursortextypos;
int   cursortextwidth;
int   cursortextheight;
int   cursorxpos;
int   cursorypos;
int   cursorwidth;
int   cursorheight;
int   cursorenable = 0;
int   cursorstate  = 0;

//----------------------------------------------------------------------------------------------------------------------------------

//Function pointer for handling control panel actions
HANDLEINPUT    rotarydialfunction = NULL;
HANDLEFUNCTION enterfunction      = NULL;
HANDLEINPUT    dotfunction        = NULL;
HANDLEINPUT    minusfunction      = NULL;
HANDLEINPUT    plusfunction       = NULL;
HANDLEINPUT    leftfunction       = NULL;
HANDLEINPUT    rightfunction      = NULL;
HANDLEINPUT    numberpadfunction  = NULL;


//Function pointers used when entry via number pad
HANDLEFUNCTION numberpadenterfunction      = NULL;
HANDLEINPUT    numberpadleftunction        = NULL;
HANDLEINPUT    numberpadrightunction       = NULL;
HANDLEINPUT    numberpadrotarydialfunction = NULL;

//Is this needed?? fro frequency adjusting
//var NPFMFunction = NULL;



DISPLAYFUNCTION  displayeditfunction = NULL;

//----------------------------------------------------------------------------------------------------------------------------------

void initializewaveformedit(void)
{
  //A mode select item allows for multiple pushes of the button to step through the available settings
  //Check if this button was pressed before
  if(currentselecteditem == MODE_ITEM_WAVEFORM)
  {
    //Pressed an extra time, so select the next item on the list
    channelsettings[currentchannel].waveform++;
    
    if(channelsettings[currentchannel].waveform >= NUMBER_OF_WAVEFORMS)
    {
      channelsettings[currentchannel].waveform = 0;
    }
    
    //Update the waveform on the display
    updatethescreen();
  }
  else
  {
    //First press, so initialize waveform editing
    selectinitialize(MODE_ITEM_WAVEFORM, channelsettings[currentchannel].waveform, "WAVEFORM", "", waveforms, NUMBER_OF_WAVEFORMS);
    
    //Set the enter function to save the change
    enterfunction = waveformeditenter;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void waveformeditenter(void)
{
  //Update the setting
  channelsettings[currentchannel].waveform = edititemvalue;
  
  //Refresh the display. This function clears all the edit items and calls the display update function
  finishedit();
}

//----------------------------------------------------------------------------------------------------------------------------------

void initializefrequencyedit(void)
{
  
  //On a second push enable direct updating???!!!
  //Show this in the display somehow
  //Or have the rotary dial be direct update and only need the enter for number pad actions
  
  
  //Set the enter function to save the change
  enterfunction = frequencyeditenter;
  
  editinitialize(MODE_ITEM_FREQUENCY, channelsettings[currentchannel].frequency, "FREQUENCY", "Hz", 2, 0, 100000000);
}

//----------------------------------------------------------------------------------------------------------------------------------

void frequencyeditenter(void)
{
  //Update the setting
  channelsettings[currentchannel].frequency = edititemdouble / edititemdecimaldivider;
  
  //Refresh the display. This function clears all the edit items and calls the display update function
  finishedit();
}

//----------------------------------------------------------------------------------------------------------------------------------

void initializephaseedit(void)
{
  //Set the enter function to save the change
  enterfunction = phaseeditenter;
  
  editinitialize(MODE_ITEM_PHASE, channelsettings[currentchannel].phase, "PHASE", " degree", 2, 0, 360);
}

//----------------------------------------------------------------------------------------------------------------------------------

void phaseeditenter(void)
{
  //Update the setting
  channelsettings[currentchannel].phase = edititemdouble / edititemdecimaldivider;
  
  //Refresh the display. This function clears all the edit items and calls the display update function
  finishedit();
}

//----------------------------------------------------------------------------------------------------------------------------------

void initializeamplitudeedit(void)
{
  //Set the enter function to save the change
  enterfunction = amplitudeeditenter;
  
  editinitialize(MODE_ITEM_AMPLITUDE, channelsettings[currentchannel].amplitude, "AMPLITUDE", "V", 3, 0, 25);
}

//----------------------------------------------------------------------------------------------------------------------------------

void amplitudeeditenter(void)
{
  //Update the setting
  channelsettings[currentchannel].amplitude = edititemdouble / edititemdecimaldivider;
  
  //Refresh the display. This function clears all the edit items and calls the display update function
  finishedit();
}

//----------------------------------------------------------------------------------------------------------------------------------

void initializedcoffsetedit(void)
{
  //Set the enter function to save the change
  enterfunction = dcoffseteditenter;
  
  editinitialize(MODE_ITEM_DC_OFFSET, channelsettings[currentchannel].dcoffset, "DC OFFSET", "V", 3, 0, 25);
}

//----------------------------------------------------------------------------------------------------------------------------------

void dcoffseteditenter(void)
{
  //Update the setting
  channelsettings[currentchannel].dcoffset = edititemdouble / edititemdecimaldivider;
  
  //Refresh the display. This function clears all the edit items and calls the display update function
  finishedit();
}

//----------------------------------------------------------------------------------------------------------------------------------

void initializepulsewidthedit(void)
{
  //Set the enter function to save the change
  enterfunction = pulsewidtheditenter;
  
  editinitialize(MODE_ITEM_PULSE_WIDTH, channelsettings[currentchannel].pulsewidth, "pulse width", "%", 2, 0, 100);
}

//----------------------------------------------------------------------------------------------------------------------------------

void pulsewidtheditenter(void)
{
  //Update the setting
  channelsettings[currentchannel].pulsewidth = edititemdouble / edititemdecimaldivider;
  
  //Refresh the display. This function clears all the edit items and calls the display update function
  finishedit();
}

//----------------------------------------------------------------------------------------------------------------------------------

void togglechannel1enable(void)
{
  //Toggle the channel enable setting
  channelsettings[0].channelenable ^= 1;

  //Update the led state
  LedSetState(&leds[CHANNEL1_ENABLE_LED], channelsettings[0].channelenable);
}

//----------------------------------------------------------------------------------------------------------------------------------

void togglechannel1pulsewidthenable(void)
{
  togglepulsewidthenable(0, CHANNEL1_PULSE_WIDTH_ENABLE_LED);
}

//----------------------------------------------------------------------------------------------------------------------------------

void togglechannel2enable(void)
{
  //Toggle the channel enable setting
  channelsettings[1].channelenable ^= 1;

  //Update the led state
  LedSetState(&leds[CHANNEL2_ENABLE_LED], channelsettings[1].channelenable);
}

//----------------------------------------------------------------------------------------------------------------------------------

void togglechannel2pulsewidthenable(void)
{
  togglepulsewidthenable(1, CHANNEL2_PULSE_WIDTH_ENABLE_LED);
}

//----------------------------------------------------------------------------------------------------------------------------------

void togglechannelselect(void)
{
  //Cancel any edit item
  if(currentselecteditem >= 0)
  {
    LedSetState(&leds[currentselecteditem + MODE_WAVEFORM_LED], 0);
  }
  
  //No item selected any more
  currentselecteditem = -1;
  
  //Reset the cursor
  cursorenable = 0;
  
  //Clear the settings edit section on the screen
  displayedititem(currentchannel);  
  
  //Toggle the global channel select
  currentchannel ^= 1;
  
  //Show the selected channel
  if(currentchannel == 0)
  {
    LedSetState(&leds[SELECT_CHANNEL1_LED], 1);
    LedSetState(&leds[SELECT_CHANNEL2_LED], 0);
  }
  else
  {
    LedSetState(&leds[SELECT_CHANNEL1_LED], 0);
    LedSetState(&leds[SELECT_CHANNEL2_LED], 1);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void selectfrequencyhz(void)
{
  selectfrequencymagnitude(0);
}

//----------------------------------------------------------------------------------------------------------------------------------

void selectfrequencykhz(void)
{
  selectfrequencymagnitude(1);
}

//----------------------------------------------------------------------------------------------------------------------------------

void selectfrequencymhz(void)
{
  selectfrequencymagnitude(2);
}

//----------------------------------------------------------------------------------------------------------------------------------

void handlerotarydial(int direction)
{
  //Check if there is a function coupled and execute it if so
  if(rotarydialfunction)
  {
    rotarydialfunction(direction);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void handleleftarrowkey(void)
{
  //Check if there is a function coupled and execute it if so
  if(leftfunction)
  {
    leftfunction(-1);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void handlerightarrowkey(void)
{
  //Check if there is a function coupled and execute it if so
  if(rightfunction)
  {
    rightfunction(1);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void handlenumber0key(void)
{
  handlenumberkey(0);
}

//----------------------------------------------------------------------------------------------------------------------------------

void handlenumber1key(void)
{
  handlenumberkey(1);
}

//----------------------------------------------------------------------------------------------------------------------------------

void handlenumber2key(void)
{
  handlenumberkey(2);
}

//----------------------------------------------------------------------------------------------------------------------------------

void handlenumber3key(void)
{
  handlenumberkey(3);
}

//----------------------------------------------------------------------------------------------------------------------------------

void handlenumber4key(void)
{
  handlenumberkey(4);
}

//----------------------------------------------------------------------------------------------------------------------------------

void handlenumber5key(void)
{
  handlenumberkey(5);
}

//----------------------------------------------------------------------------------------------------------------------------------

void handlenumber6key(void)
{
  handlenumberkey(6);
}

//----------------------------------------------------------------------------------------------------------------------------------

void handlenumber7key(void)
{
  handlenumberkey(7);
}

//----------------------------------------------------------------------------------------------------------------------------------

void handlenumber8key(void)
{
  handlenumberkey(8);
}

//----------------------------------------------------------------------------------------------------------------------------------

void handlenumber9key(void)
{
  handlenumberkey(9);
}

//----------------------------------------------------------------------------------------------------------------------------------

void handlenumberdotkey(void)
{
  //Check if there is a function coupled and execute it if so
  if(dotfunction)
  {
    dotfunction(0);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void handlenumberminuskey(void)
{
  //Check if there is a function coupled and execute it if so
  if(minusfunction)
  {
    minusfunction(0);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void handlenumberpluskey(void)
{
  //Check if there is a function coupled and execute it if so
  if(plusfunction)
  {
    plusfunction(0);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void handlenumberkey(int key)
{
  //Check if there is a function coupled and execute it if so
  if(numberpadfunction)
  {
    numberpadfunction(key);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void handlenumbercancelkey(void)
{
  //Turn of the led of the previous selected item if any
  if(currentselecteditem >= 0)
  {
    LedSetState(&leds[currentselecteditem + MODE_WAVEFORM_LED], 0);
  }
  
  //No selected item any more
  currentselecteditem = -1;

  //No selected edit item variables any more
  edititemheader = NULL;
  edititemtext   = NULL;
  edititemlist   = NULL;
  edititemcount  = 0;
  edititemvalue  = 0;
  edititemstate  = 0;
  
  //Clear all the edit item functions
  rotarydialfunction  = NULL;
  enterfunction       = NULL;
  dotfunction         = NULL;
  minusfunction       = NULL;
  plusfunction        = NULL;
  leftfunction        = NULL;
  rightfunction       = NULL;
  numberpadfunction   = NULL;
  displayeditfunction = NULL;
  
  //Reset the cursor
  cursorenable = 0;
  cursorstate  = 0;
  
  //Clear the display part showing the edit item
  displayedititem(currentchannel);
}

//----------------------------------------------------------------------------------------------------------------------------------

void handlenumberenterkey(void)
{
  //Check if there is a function coupled and execute it if so
  if(enterfunction)
  {
    enterfunction();
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void togglepulsewidthenable(int channel, int led)
{
  //Toggle the channel pulse width enable setting
  channelsettings[channel].pulsewidthenable ^= 1;
  
  //Update the led state
  LedSetState(&leds[led], channelsettings[channel].pulsewidthenable);
  
  //Cancel any ongoing edit
  handlenumbercancelkey();  
  
  //Show the changed setting on the screen
  updatethescreen();
}

//----------------------------------------------------------------------------------------------------------------------------------

void selectfrequencymagnitude(int magnitude)
{
  currentmagnitude = magnitude;
  
  switch(magnitude)
  {
    default:
    case 0:
      LedSetState(&leds[MAGNITUDE_HZ_LED],  1);
      LedSetState(&leds[MAGNITUDE_KHZ_LED], 0);
      LedSetState(&leds[MAGNITUDE_MHZ_LED], 0);
      break;

    case 1:
      LedSetState(&leds[MAGNITUDE_HZ_LED],  0);
      LedSetState(&leds[MAGNITUDE_KHZ_LED], 1);
      LedSetState(&leds[MAGNITUDE_MHZ_LED], 0);
      break;

    case 2:
      LedSetState(&leds[MAGNITUDE_HZ_LED],  0);
      LedSetState(&leds[MAGNITUDE_KHZ_LED], 0);
      LedSetState(&leds[MAGNITUDE_MHZ_LED], 1);
      break;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void updatethescreen(void)
{
  //Clear the generator screen
  FillRect(&signalgeneratorxc, 74, 74, 800, 480, ScreenBackgroundColor);
  
  //Update the generator screen for both channels
  SignalGeneratorShowSignal(&signalgeneratorxc, 0);
  SignalGeneratorShowSignal(&signalgeneratorxc, 1);
}

//----------------------------------------------------------------------------------------------------------------------------------

void finishedit(void)
{
  //Turn of the led of the previous selected item if any
  if(currentselecteditem >= 0)
  {
    LedSetState(&leds[currentselecteditem + MODE_WAVEFORM_LED], 0);
  }
  
  //No selected item any more
  currentselecteditem = -1;

  //No selected edit item variables any more
  edititemheader = NULL;
  edititemtext   = NULL;
  edititemlist   = NULL;
  edititemcount  = 0;
  edititemvalue  = 0;
  edititemstate  = 0;
  
  //Clear all the edit item functions
  rotarydialfunction  = NULL;
  enterfunction       = NULL;
  dotfunction         = NULL;
  minusfunction       = NULL;
  plusfunction        = NULL;
  leftfunction        = NULL;
  rightfunction       = NULL;
  numberpadfunction   = NULL;
  displayeditfunction = NULL;

  //Reset the cursor
  cursorenable = 0;
  cursorstate  = 0;
  
  //Show the new setting on the screen
  updatethescreen();
}

//----------------------------------------------------------------------------------------------------------------------------------

void displayedititem(int channel)
{
  int x = EDIT_ITEM_XPOS;

  //Check if channel 2 is selected
  if(channel)
  {
    //Offset the display location
    x += CHANNEL_DISPLAY_X_OFFSET;
  }  
  
  //Clear the needed section on the screen
  FillRect(&signalgeneratorxc, x, EDIT_ITEM_YPOS, EDIT_ITEM_WIDTH, EDIT_ITEM_HEIGHT, ScreenBackgroundColor);
  
  //If the channel is equal to the current channel and an item is being edited show it on the given positions
  if((channel == currentchannel) && (currentselecteditem >= 0))
  {
    //Display a bounding box
    DrawRect(&signalgeneratorxc, x, EDIT_ITEM_YPOS, EDIT_ITEM_WIDTH - 1, EDIT_ITEM_HEIGHT - 1, ScreenSignalColor, 1);
    
    //Display the header
    if(edititemheader)
    {
      PlaceText(&signalgeneratorxc, x + EDIT_ITEM_X3, EDIT_ITEM_Y1, edititemheader, 2, BrightTextColorId, ALIGN_TEXT_CENTER);
    }

    //Check if a display function is set
    if(displayeditfunction)
    {
      //Go and display the settings
      displayeditfunction();
    }
  }
}

//==================================================================================================================================
//Select functionality
//==================================================================================================================================

void selectinitialize(int id, int value, const char *header, const char *text, const char **list, int count)
{
  //Turn of the led of the previous selected item if any
  if(currentselecteditem >= 0)
  {
    LedSetState(&leds[currentselecteditem + MODE_WAVEFORM_LED], 0);
  }
  
  //Select this item
  currentselecteditem = id;

  //Turn on its led
  LedSetState(&leds[id + MODE_WAVEFORM_LED], 1);
  
  //Reset the cursor
  cursorenable = 0;

  //Need to display the settings list and show the current selected item above it
  edititemheader = (char *)header;
  
  //Set the parameters for editing this select item
  edititemvalue = value;
  edititemtext  = (char *)text;
  edititemlist  = (char **)list;
  edititemcount = count;
  
  //Setup the function pointers to handle this edit item
  rotarydialfunction  = selectonrotarydial;
  leftfunction        = selectonrotarydial;
  rightfunction       = selectonrotarydial;
  numberpadfunction   = selectonnumpad;
  displayeditfunction = selectshowitems;
  
  //Display the item edit parameters on the screen
  displayedititem(currentchannel);
}

//----------------------------------------------------------------------------------------------------------------------------------

void selectonrotarydial(int data)
{
  //Check if there is anything to edit
  if(edititemcount)
  {
    //Add the current change to the setting
    edititemvalue += data;
    
    //Check if out of range on the bottom
    if(edititemvalue < 0)
    {
      //If so fall through to other end
      edititemvalue = edititemcount - 1;
    }
    //Check if out of range on the top
    else if(edititemvalue >= edititemcount)
    {
      //If so fall through to other end
      edititemvalue = 0;
    }

    //Show the result on the edit panel
    displayedititem(currentchannel);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void selectonnumpad(int data)
{
  int value;
  
  //Check if there is anything to edit
  if(edititemcount)
  {
    //Check if first entry
    if(edititemstate == 0)
    {
      //Check if the current selection is valid
      if(data < edititemcount)
      {
        //Set it as the new selection
        edititemvalue = data;
      }

      //Check if multi digit selection can be made
      if((data != 0) && ((edititemvalue * 10) < edititemcount))
      {
        //Switch to additional input state
        edititemstate = 1;
      }
    }
    else
    {
      //On multiple digit entry add in the next digit
      value = (edititemvalue * 10) + data;

      //Check if result allows for a selection
      if(value < edititemcount)
      {
        //Set it as the new selection
        edititemvalue = data;

        //Check if more digits can be added
        if((edititemvalue * 10) >= edititemcount)
        {
          //If not then no more additional input allowed
          edititemstate = 0;
        }
      }
      else
      {
        //No more additional input allowed
        edititemstate = 0;
      }
    }

    //Show the result on the edit panel
    displayedititem(currentchannel);
  }  
}

//----------------------------------------------------------------------------------------------------------------------------------

void selectshowitems(void)
{
  int x = EDIT_ITEM_XPOS;
  int y = EDIT_ITEM_Y3;
  int i;

  //Check if channel 2 is selected
  if(currentchannel)
  {
    //Offset the display location
    x += CHANNEL_DISPLAY_X_OFFSET;
  }  
  
  //Check if item list and count set
  if(edititemlist && edititemcount)
  {
    //Show the selected item on top
    PlaceText(&signalgeneratorxc, x + EDIT_ITEM_X1, EDIT_ITEM_Y2, edititemlist[edititemvalue], 2, BrightTextColorId, ALIGN_TEXT_LEFT);
    
    //Need to add the edititemtext when it is set. Not used for now
    
    //Need to add an asterix at the right side if more digits can be selected via the number pad. Not needed for now
    
    //Need to limit count if list is to long
    //For longer lists a scrolling system is needed. Need a timer function for this. Is not needed for now.
    
    x += EDIT_ITEM_X2;
    
    //Show the item list with the item number and the dimmed color
    for(i=0;i<edititemcount;i++)
    {
      snprintf(textbuffer, sizeof(textbuffer), "%d: %s", i, edititemlist[i]);
      
      PlaceText(&signalgeneratorxc, x, y, textbuffer, 3, DimmedTextColorId, ALIGN_TEXT_LEFT);
      
      y += EDIT_ITEM_SPACING;
    }
  }
}

//==================================================================================================================================
//Item edit functionality
//==================================================================================================================================

void editinitialize(int id, double value, const char *header, const char *type, int numdecimals, double minvalue, double maxvalue)
{
  //Turn of the led of the previous selected item if any
  if(currentselecteditem >= 0)
  {
    LedSetState(&leds[currentselecteditem + MODE_WAVEFORM_LED], 0);
  }
  
  //Select this item
  currentselecteditem = id;

  //Turn on its led
  LedSetState(&leds[id + MODE_WAVEFORM_LED], 1);

  //Need to display the settings list and show the current selected item above it
  edititemheader = (char *)header;

  edititemtypetext = (char *)type;

  edititemnumberofdecimals = numdecimals;
  
  edititemaddfactor = pow(10, edititemnumberofdecimals);
  edititemdecimaldivider = edititemaddfactor;
  
  //Set the parameters for editing this select item
  edititemdouble    = value * edititemdecimaldivider;
  edititemmindouble = minvalue * edititemdecimaldivider;
  edititemmaxdouble = maxvalue * edititemdecimaldivider;

  edititemcursorfromend = 2 + edititemnumberofdecimals + strlen(type);
  
  
  //Setup the function pointers to handle this edit item
  rotarydialfunction  = editonrotarydial;
  
  leftfunction        = editmovecursorleft;
  rightfunction       = editmovecursorright;

  numberpadfunction   = editonnumpadstart;
  
  //Set the original enter function for calling when number pad is being used
  numberpadenterfunction      = enterfunction;
  numberpadrotarydialfunction = editonrotarydial;
  numberpadrightunction       = editmovecursorright;
  numberpadleftunction        = editmovecursorleft;
//  NPFMFunction = changefreqmagnitude;
  
  if(edititemmindouble < 0)
    minusfunction = editonminusstart;
  else
    minusfunction = NULL;
  
  if(edititemnumberofdecimals > 0)
    dotfunction = editondotstart;
  else
    dotfunction = NULL;
  
  displayeditfunction = editshowitem;
  
  //Display the item edit parameters on the screen
  displayedititem(currentchannel);
}

//----------------------------------------------------------------------------------------------------------------------------------

void editshowitem(void)
{
  int x = EDIT_ITEM_XPOS;
  int y = EDIT_ITEM_Y3;

  //Check if channel 2 is selected
  if(currentchannel)
  {
    //Offset the display location
    x += CHANNEL_DISPLAY_X_OFFSET;
  }  
  
  //Setup the format string for the needed number of decimals
  snprintf(formatstring, sizeof(formatstring), "%%s%%.%df%%s", edititemnumberofdecimals);
  
  //Print the values with the type specifier
  snprintf(textbuffer,    sizeof(textbuffer),    formatstring, "",       edititemdouble / edititemdecimaldivider, edititemtypetext);
  snprintf(mintextbuffer, sizeof(mintextbuffer), formatstring, ">= ", edititemmindouble / edititemdecimaldivider, edititemtypetext);
  snprintf(maxtextbuffer, sizeof(maxtextbuffer), formatstring, "<= ", edititemmaxdouble / edititemdecimaldivider, edititemtypetext);

  //Show the to edit value with a blinking cursor
  setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, textbuffer, strlen(textbuffer) - edititemcursorfromend, 2, BrightTextColorId, ALIGN_TEXT_LEFT);

  //Show the limit values
  PlaceText(&signalgeneratorxc, x + EDIT_ITEM_X2, EDIT_ITEM_Y4, mintextbuffer, 3, DimmedTextColorId, ALIGN_TEXT_LEFT);
  PlaceText(&signalgeneratorxc, x + EDIT_ITEM_X2, EDIT_ITEM_Y5, maxtextbuffer, 3, DimmedTextColorId, ALIGN_TEXT_LEFT);
}

//----------------------------------------------------------------------------------------------------------------------------------

void editonrotarydial(int data)
{
  int ci;
  double uaaf = edititemaddfactor * 10;
  
  int x = EDIT_ITEM_XPOS;

  //Check if channel 2 is selected
  if(currentchannel)
  {
    //Offset the display location
    x += CHANNEL_DISPLAY_X_OFFSET;
  }  
  
  edititemdouble += (data * edititemaddfactor);
  
  //Keep in range of max and min values
  //When over or under restore previous value
  //In case the result is 0 and adjusting is not on lowest digit jump down one digit and continue lowering the value
  //In case the result equals the next adjust add factor and not over max value jump up and continue raising the value
  if(edititemdouble > edititemmaxdouble)
  {
    edititemdouble -= edititemaddfactor;
  }
  else if((edititemdouble == 0) && (edititemaddfactor > 1))
  {
    //Back to previous value
    edititemdouble += edititemaddfactor;
    
    //Shift to lower digit and take it of the variable
    edititemaddfactor /= 10;
    edititemdouble -= edititemaddfactor;

    //Make sure not below min value
    if(edititemdouble < edititemmindouble)
    {
      edititemdouble += edititemaddfactor;
    }
  }
  else if(edititemdouble == uaaf)
  {
    //Shift to upper digit
    edititemaddfactor *= 10;
  }
  else if(edititemdouble < edititemmindouble)
  {
    edititemdouble += edititemaddfactor;
  }

  //Check if cursor out of range of current value
  if(edititemaddfactor > abs(edititemdouble))
  {
    //Set in range of highest digit in current value
    edititemaddfactor = pow(10, floor(log10(abs(edititemdouble))));

    //Don't go below lowest digit
    if(edititemaddfactor < 1)
      edititemaddfactor = 1;
  }

  ci = edititemcursorfromend + log10(edititemaddfactor / edititemdecimaldivider);

  if(edititemaddfactor < edititemdecimaldivider)
    ci--;
  
  snprintf(textbuffer, sizeof(textbuffer), formatstring, "", edititemdouble / edititemdecimaldivider, edititemtypetext);
  
  ci = strlen(textbuffer) - ci;

  if(ci < 0)
    ci = 0;

  setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, textbuffer, ci, 2, BrightTextColorId, ALIGN_TEXT_LEFT);
}

//==================================================================================================================================
//Rotary dial functions
//==================================================================================================================================

//Used when numpad entry has started without decimals
void numpadrotarydialnodot(int data)
{
  //Correct the value as needed
  edititemdouble *= edititemdecimaldivider;

  numpadrotarydial(data);
}

//----------------------------------------------------------------------------------------------------------------------------------

//Used when numpad entry has started with decimals
void numpadrotarydialdot(int data)
{
  double adjmul = pow(10, edititemnumberofdecimals - edititemdecimalcount);
  
  //Correct the value as needed
  edititemdouble *= adjmul;
  
  numpadrotarydial(data);
}

//----------------------------------------------------------------------------------------------------------------------------------

void numpadrotarydial(int data)
{
  if(edititemdouble < edititemmindouble)
    edititemdouble = edititemmindouble;
  
  //Reset the number pad entry state
  numberpadfunction = editonnumpadstart;
  rotarydialfunction = numberpadrotarydialfunction;
  enterfunction      = numberpadenterfunction;
  leftfunction       = numberpadleftunction;
  rightfunction      = numberpadrightunction;
  plusfunction       = editonplusstart;
//  FrequencyMagnitudeFunction = NPFMFunction;

  if(edititemmindouble < 0)
    minusfunction = editonminusstart;
  else
    minusfunction = NULL;

  if(edititemnumberofdecimals > 0)
    dotfunction = editondotstart;
  else
    dotfunction = NULL;
  
  //Check if there is a function to call
  if(numberpadrotarydialfunction)
  {
    //Process the normal rotray dial
    numberpadrotarydialfunction(data);
  }
}

//==================================================================================================================================
//Left key functions
//==================================================================================================================================

void editmovecursorleft(int data)
{
  int ci;
  int x = EDIT_ITEM_XPOS;

  //Check if channel 2 is selected
  if(currentchannel)
  {
    //Offset the display location
    x += CHANNEL_DISPLAY_X_OFFSET;
  }  
  
  //Up one digit
  edititemaddfactor *= 10;

  //Check if out of range of current value
  if((edititemaddfactor > abs(edititemdouble)) && (edititemaddfactor > edititemdecimaldivider))
    edititemaddfactor /= 10;

  ci = edititemcursorfromend + log10(edititemaddfactor / edititemdecimaldivider);

  //Needed to jump the dot character
  if(edititemaddfactor < edititemdecimaldivider)
    ci--;

  snprintf(textbuffer, sizeof(textbuffer), formatstring, "", edititemdouble / edititemdecimaldivider, edititemtypetext);
  
  ci = strlen(textbuffer) - ci;

  if(ci < 0)
    ci = 0;

  setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, textbuffer, ci, 2, BrightTextColorId, ALIGN_TEXT_LEFT);
}

//----------------------------------------------------------------------------------------------------------------------------------

//Used when input given with the number key pad without decimals
void numpadleftnodot(int data)
{
  int x = EDIT_ITEM_XPOS;

  //Check if channel 2 is selected
  if(currentchannel)
  {
    //Offset the display location
    x += CHANNEL_DISPLAY_X_OFFSET;
  }  

  //Take last digit of
  edititemdouble = (int)(edititemdouble / 10);
  
  //When still digits available display them
  if(edititemdouble > 0)
  {
    snprintf(textbuffer, sizeof(textbuffer), "%d", (int)edititemdouble);
    
    setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, textbuffer, strlen(textbuffer), 2, BrightTextColorId, ALIGN_TEXT_LEFT);
  }
  else
  {
    setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, "", 0, 2, BrightTextColorId, ALIGN_TEXT_LEFT);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

//Used when input given with the number key pad with decimals
void numpadleftdot(int data)
{
  char formatstr[20];
  double decdiv;
  int x = EDIT_ITEM_XPOS;

  //Check if channel 2 is selected
  if(currentchannel)
  {
    //Offset the display location
    x += CHANNEL_DISPLAY_X_OFFSET;
  }  
  
  //Take last decimal of if any
  if(edititemdecimalcount > 0)
  {
    edititemdouble = (int)(edititemdouble / 10);
    
    edititemdecimalcount--;
    
    if(edititemdecimalcount > 0)
    {
      //Display with decimals
      decdiv = pow(10, edititemdecimalcount);

      //Setup the format string for the needed number of decimals
      snprintf(formatstr, sizeof(formatstr), "%%.%df", edititemdecimalcount);

      //Need functionality here for setting up the format specifier with the correct number of decimals
      snprintf(textbuffer, sizeof(textbuffer), formatstr, edititemdouble / decdiv);

      setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, textbuffer, strlen(textbuffer), 2, BrightTextColorId, ALIGN_TEXT_LEFT);
    }
    else
    {
      snprintf(textbuffer, sizeof(textbuffer), "%d.", (int)edititemdouble);

      setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, textbuffer, strlen(textbuffer), 2, BrightTextColorId, ALIGN_TEXT_LEFT);
    }
  }
  else
  {
    snprintf(textbuffer, sizeof(textbuffer), "%d", (int)edititemdouble);
    
    setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, textbuffer, strlen(textbuffer), 2, BrightTextColorId, ALIGN_TEXT_LEFT);

    dotfunction        = editondot;
    numberpadfunction  = editonnumpadnext;
    enterfunction      = numpadenternodot;
    rotarydialfunction = numpadrotarydialnodot;
    leftfunction       = numpadleftnodot;
    plusfunction       = NULL;
    minusfunction      = editonminus;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

//Used when negative input given with the number key pad without decimals
void numpadleftminusnodot(int data)
{
  int x = EDIT_ITEM_XPOS;

  //Check if channel 2 is selected
  if(currentchannel)
  {
    //Offset the display location
    x += CHANNEL_DISPLAY_X_OFFSET;
  }  

  //Take last digit of
  edititemdouble = (int)(edititemdouble / 10);
  
  //When still digits available display them
  if(edititemdouble < 0)
  {
    snprintf(textbuffer, sizeof(textbuffer), "%d", (int)edititemdouble);
    
    setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, textbuffer, strlen(textbuffer), 2, BrightTextColorId, ALIGN_TEXT_LEFT);
  }
  else
  {
    setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, "-", 1, 2, BrightTextColorId, ALIGN_TEXT_LEFT);
    
    //Next left will make entry positive
    leftfunction = editonplusstart;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

//Used when negative input given with the number key pad with decimals
void numpadleftminusdot(int data)
{
  char formatstr[20];
  double decdiv;
  int x = EDIT_ITEM_XPOS;

  //Check if channel 2 is selected
  if(currentchannel)
  {
    //Offset the display location
    x += CHANNEL_DISPLAY_X_OFFSET;
  }  
  
  //Take last decimal of if any
  if(edititemdecimalcount > 0)
  {
    edititemdouble = (int)(edititemdouble / 10);
    
    edititemdecimalcount--;
    
    if(edititemdecimalcount > 0)
    {
      //Display with decimals
      decdiv = pow(10, edititemdecimalcount);

      //Setup the format string for the needed number of decimals
      snprintf(formatstr, sizeof(formatstr), "%%.%df", edititemdecimalcount);

      //Need functionality here for setting up the format specifier with the correct number of decimals
      snprintf(textbuffer, sizeof(textbuffer), formatstr, edititemdouble / decdiv);

      setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, textbuffer, strlen(textbuffer), 2, BrightTextColorId, ALIGN_TEXT_LEFT);
    }
    else
    {
      if(edititemdouble == 0)
      {
        setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, "-0.", 3, 2, BrightTextColorId, ALIGN_TEXT_LEFT);
      }
      else
      {
        snprintf(textbuffer, sizeof(textbuffer), "%d.", (int)edititemdouble);

        setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, textbuffer, strlen(textbuffer), 2, BrightTextColorId, ALIGN_TEXT_LEFT);
      }
    }
  }
  else
  {
    if(edititemdouble == 0)
    {
      setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, "-0", 2, 2, BrightTextColorId, ALIGN_TEXT_LEFT);
    }
    else
    {
      snprintf(textbuffer, sizeof(textbuffer), "%d", (int)edititemdouble);

      setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, textbuffer, strlen(textbuffer), 2, BrightTextColorId, ALIGN_TEXT_LEFT);
    }

    dotfunction        = editondotminus;
    numberpadfunction  = editonnumpadminusstart;
    enterfunction      = numpadenternodot;
    rotarydialfunction = numpadrotarydialnodot;
    leftfunction       = numpadleftminusnodot;
    plusfunction       = editonplus;
    minusfunction      = NULL;
  }
}

//==================================================================================================================================
//Right key functions
//==================================================================================================================================

void editmovecursorright(int data)
{
  int ci;
  int x = EDIT_ITEM_XPOS;

  //Check if channel 2 is selected
  if(currentchannel)
  {
    //Offset the display location
    x += CHANNEL_DISPLAY_X_OFFSET;
  }  

  //Down one digit
  edititemaddfactor /= 10;

  //Limit to last digit below the comma
  if(edititemaddfactor < 1)
    edititemaddfactor = 1;

  ci = edititemcursorfromend + log10(edititemaddfactor / edititemdecimaldivider);

  //Needed to jump the dot character
  if(edititemaddfactor < edititemdecimaldivider)
    ci--;

  snprintf(textbuffer, sizeof(textbuffer), formatstring, "", edititemdouble / edititemdecimaldivider, edititemtypetext);
  
  ci = strlen(textbuffer) - ci;

  if(ci < 0)
    ci = 0;

  setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, textbuffer, ci, 2, BrightTextColorId, ALIGN_TEXT_LEFT);
}

//==================================================================================================================================
//Number pad digit key functions
//==================================================================================================================================

//Used to handle first input from digit keys
//Displays the first entry and sets up the needed functions for positive input
void editonnumpadstart(int data)
{
  int x = EDIT_ITEM_XPOS;

  //Check if channel 2 is selected
  if(currentchannel)
  {
    //Offset the display location
    x += CHANNEL_DISPLAY_X_OFFSET;
  }
  
  //Check if the given input is in range of the item being edited
  if(data <= (edititemmaxdouble / edititemdecimaldivider))
  {
    //Set the input as the new data
    edititemdouble = data;
    
    //Set the functions for handling the next entry
    numberpadfunction  = editonnumpadnext;
    enterfunction      = numpadenternodot;
    rotarydialfunction = numpadrotarydialnodot;
    rightfunction      = NULL;
    leftfunction       = numpadleftnodot;
    
    //Need some way to determine if this needs to be enabled
    //Maybe look at the edititemmindouble to see if it is negative
    if(edititemmindouble < 0)
    {
      minusfunction = editonminus;
    }
    else
    {
      minusfunction = NULL;
    }
      
    if(edititemnumberofdecimals > 0)
    {
      dotfunction = editondot;
    }
    else
    {
      dotfunction = NULL;
    }
    
    snprintf(textbuffer, sizeof(textbuffer), "%d", (int)edititemdouble);
    
    setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, textbuffer, strlen(textbuffer), 2, BrightTextColorId, ALIGN_TEXT_LEFT);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

//Used to handle next digits
void editonnumpadnext(int data)
{
  double adjvar;
  int x = EDIT_ITEM_XPOS;

  //Check if channel 2 is selected
  if(currentchannel)
  {
    //Offset the display location
    x += CHANNEL_DISPLAY_X_OFFSET;
  }  
  
  adjvar = (edititemdouble * 10) + data;

  if(adjvar <= (edititemmaxdouble / edititemdecimaldivider))
  {
    edititemdouble = adjvar;
    
    snprintf(textbuffer, sizeof(textbuffer), "%d", (int)edititemdouble);
    
    setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, textbuffer, strlen(textbuffer), 2, BrightTextColorId, ALIGN_TEXT_LEFT);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

//Used to handle decimal input after the dot key has been pressed
void editonnumpaddot(int data)
{
  char formatstr[20];
  double adjvar;
  int x = EDIT_ITEM_XPOS;

  //Check if channel 2 is selected
  if(currentchannel)
  {
    //Offset the display location
    x += CHANNEL_DISPLAY_X_OFFSET;
  }  
  
  adjvar = (edititemdouble * 10) + data;

  if((edititemdecimalcount < edititemnumberofdecimals) && (adjvar >= edititemmindouble))
  {
    edititemdouble = adjvar;
    edititemdecimalcount++;
    
    adjvar = pow(10, edititemdecimalcount);

    //Setup the format string for the needed number of decimals
    snprintf(formatstr, sizeof(formatstr), "%%.%df", edititemdecimalcount);
    
    //Need functionality here for setting up the format specifier with the correct number of decimals
    snprintf(textbuffer, sizeof(textbuffer), formatstr, edititemdouble / adjvar);
    
    setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, textbuffer, strlen(textbuffer), 2, BrightTextColorId, ALIGN_TEXT_LEFT);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

//Used to handle first input after the negative sign from digit keys
//Displays the first entry and sets up the needed functions for negative input
void editonnumpadminusstart(int data)
{
  int x = EDIT_ITEM_XPOS;

  //Check if channel 2 is selected
  if(currentchannel)
  {
    //Offset the display location
    x += CHANNEL_DISPLAY_X_OFFSET;
  }  
  
  //Make input negative
  data *= -1;
  
  if(data >= (edititemmindouble / edititemdecimaldivider))
  {
    edititemdouble = data;
    
    //Set the needed new functions
    numberpadfunction = editonnumpadminusnext;
    enterfunction     = numpadenternodot;
    leftfunction      = numpadleftminusnodot;
    plusfunction      = editonplus;
      
    //Check if this item allows decimals
    if(edititemnumberofdecimals > 0)
    {
      dotfunction = editondotminus;
    }
    else
    {
      dotfunction = NULL;
    }
    
    if(edititemdouble == 0)
    {
      setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, "-0", 2, 2, BrightTextColorId, ALIGN_TEXT_LEFT);
    }
    else
    {
      snprintf(textbuffer, sizeof(textbuffer), "%d", (int)edititemdouble);

      setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, textbuffer, strlen(textbuffer), 2, BrightTextColorId, ALIGN_TEXT_LEFT);
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

//Used to handle next negative digits
void editonnumpadminusnext(int data)
{
  double adjvar;
  int x = EDIT_ITEM_XPOS;

  //Check if channel 2 is selected
  if(currentchannel)
  {
    //Offset the display location
    x += CHANNEL_DISPLAY_X_OFFSET;
  }  
  
  adjvar = (edititemdouble * 10) - data;

  if(adjvar >= (edititemmindouble / edititemdecimaldivider))
  {
    edititemdouble = adjvar;

    snprintf(textbuffer, sizeof(textbuffer), "%d", (int)edititemdouble);

    setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, textbuffer, strlen(textbuffer), 2, BrightTextColorId, ALIGN_TEXT_LEFT);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

//Used to handle negative decimal input after the dot key has been pressed
void editonnumpadminusdot(int data)
{
  char formatstr[20];
  double adjvar;
  int x = EDIT_ITEM_XPOS;

  //Check if channel 2 is selected
  if(currentchannel)
  {
    //Offset the display location
    x += CHANNEL_DISPLAY_X_OFFSET;
  }  
  
  adjvar = (edititemdouble * 10) - data;

  if((edititemdecimalcount < edititemnumberofdecimals) && (adjvar >= edititemmindouble))
  {
    edititemdouble = adjvar;
    edititemdecimalcount++;
    
    adjvar = pow(10, edititemdecimalcount);

    //Setup the format string for the needed number of decimals
    snprintf(formatstr, sizeof(formatstr), "%%.%df", edititemdecimalcount);
    
    //Need functionality here for setting up the format specifier with the correct number of decimals
    snprintf(textbuffer, sizeof(textbuffer), formatstr, edititemdouble / adjvar);
    
    setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, textbuffer, strlen(textbuffer), 2, BrightTextColorId, ALIGN_TEXT_LEFT);
  }
}

//==================================================================================================================================
//Dot key functions
//==================================================================================================================================

//Used for first input from the number key pad
//Displays 0. and sets up the needed function pointers for inputting positive decimals
void editondotstart(int data)
{
  int x = EDIT_ITEM_XPOS;

  //Check if channel 2 is selected
  if(currentchannel)
  {
    //Offset the display location
    x += CHANNEL_DISPLAY_X_OFFSET;
  }  
  
  edititemdouble = 0;
  edititemdecimalcount = 0;
  
  dotfunction        = NULL;
  numberpadfunction  = editonnumpaddot;
  enterfunction      = numpadenterdot;
  leftfunction       = numpadleftdot;
  plusfunction       = NULL;
  minusfunction      = editonminusdot;
  rotarydialfunction = numpadrotarydialdot;
  
  setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, "0.", 2, 2, BrightTextColorId, ALIGN_TEXT_LEFT);
}

//----------------------------------------------------------------------------------------------------------------------------------

//Used when positive input already given
void editondot(int data)
{
  int x = EDIT_ITEM_XPOS;

  //Check if channel 2 is selected
  if(currentchannel)
  {
    //Offset the display location
    x += CHANNEL_DISPLAY_X_OFFSET;
  }  
  
  if(edititemdouble < (edititemmaxdouble / edititemdecimaldivider))
  {
    edititemdecimalcount = 0;

    dotfunction        = NULL;
    numberpadfunction  = editonnumpaddot;
    enterfunction      = numpadenterdot;
    leftfunction       = numpadleftdot;
    plusfunction       = NULL;
    minusfunction      = editonminusdot;
    rotarydialfunction = numpadrotarydialdot;

    snprintf(textbuffer, sizeof(textbuffer), "%d.", (int)edititemdouble);
    
    setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, textbuffer, strlen(textbuffer), 2, BrightTextColorId, ALIGN_TEXT_LEFT);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

//Used for input directly after negative sign from the number key pad
//Displays -0. and sets up the needed function pointers for inputting negative decimals
void editondotminusstart(int data)
{
  int x = EDIT_ITEM_XPOS;

  //Check if channel 2 is selected
  if(currentchannel)
  {
    //Offset the display location
    x += CHANNEL_DISPLAY_X_OFFSET;
  }  
  
  edititemdouble = 0;
  edititemdecimalcount = 0;
  
  dotfunction        = NULL;
  numberpadfunction  = editonnumpadminusdot;
  enterfunction      = numpadenterdot;
  plusfunction       = editonplusdot;
  leftfunction       = numpadleftminusdot;
  rotarydialfunction = numpadrotarydialdot;
  
  setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, "-0.", 3, 2, BrightTextColorId, ALIGN_TEXT_LEFT);
}

//----------------------------------------------------------------------------------------------------------------------------------

//Used when negative input already given
void editondotminus(int data)
{
  int x = EDIT_ITEM_XPOS;

  //Check if channel 2 is selected
  if(currentchannel)
  {
    //Offset the display location
    x += CHANNEL_DISPLAY_X_OFFSET;
  }  
  
  if(edititemdouble > (edititemmindouble / edititemdecimaldivider))
  {
    edititemdecimalcount = 0;

    dotfunction        = NULL;
    numberpadfunction  = editonnumpadminusdot;
    enterfunction      = numpadenterdot;
    leftfunction       = numpadleftminusdot;
    rotarydialfunction = numpadrotarydialdot;

    if(edititemdouble == 0)
    {
      setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, "-0.", 3, 2, BrightTextColorId, ALIGN_TEXT_LEFT);
    }
    else
    {
      snprintf(textbuffer, sizeof(textbuffer), "%d.", (int)edititemdouble);

      setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, textbuffer, strlen(textbuffer), 2, BrightTextColorId, ALIGN_TEXT_LEFT);
    }
  }
}

//==================================================================================================================================
//Plus key functions
//==================================================================================================================================

//Used for first input from the number key pad
//Clears the display and sets up the needed function pointers for inputting positive numbers
void editonplusstart(int data)
{
  int x = EDIT_ITEM_XPOS;

  //Check if channel 2 is selected
  if(currentchannel)
  {
    //Offset the display location
    x += CHANNEL_DISPLAY_X_OFFSET;
  }  
  
  edititemdouble = 0;

  if(edititemnumberofdecimals > 0)
  {
    dotfunction = editondotstart;
  }
  else
  {
    dotfunction = NULL;
  }

  numberpadfunction = editonnumpadstart;
  leftfunction      = NULL;
  plusfunction      = NULL;
  
  if(edititemmindouble < 0)
  {
    minusfunction = editonminusstart;
  }
  else
  {
    minusfunction = NULL;
  }
  
  setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, "", 0, 2, BrightTextColorId, ALIGN_TEXT_LEFT);
}

//----------------------------------------------------------------------------------------------------------------------------------

//Used when negative input without decimals already given
void editonplus(int data)
{
  int x = EDIT_ITEM_XPOS;

  //Check if channel 2 is selected
  if(currentchannel)
  {
    //Offset the display location
    x += CHANNEL_DISPLAY_X_OFFSET;
  }  
  
  //Invert the current value
  edititemdouble *= -1;

  plusfunction      = NULL;
  minusfunction     = editonminus;
  numberpadfunction = editonnumpadnext;
  
  snprintf(textbuffer, sizeof(textbuffer), "%d", (int)edititemdouble);

  setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, textbuffer, strlen(textbuffer), 2, BrightTextColorId, ALIGN_TEXT_LEFT);
}

//----------------------------------------------------------------------------------------------------------------------------------

//Used when negative input with decimals already given
void editonplusdot(int data)
{
  char formatstr[20];
  double decdiv;
  int x = EDIT_ITEM_XPOS;

  //Check if channel 2 is selected
  if(currentchannel)
  {
    //Offset the display location
    x += CHANNEL_DISPLAY_X_OFFSET;
  }  

  plusfunction       = NULL;
  minusfunction      = editonminusdot;
  numberpadfunction  = editonnumpaddot;
  rotarydialfunction = numpadrotarydialdot;
  
  if(edititemdouble != 0)
  {
    //Invert the current value
    edititemdouble *= -1;

    decdiv = pow(10, edititemdecimalcount);

    //Setup the format string for the needed number of decimals
    snprintf(formatstr, sizeof(formatstr), "%%.%df", edititemdecimalcount);
    
    //Need functionality here for setting up the format specifier with the correct number of decimals
    snprintf(textbuffer, sizeof(textbuffer), formatstr, edititemdouble / decdiv);
    
    setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, textbuffer, strlen(textbuffer), 2, BrightTextColorId, ALIGN_TEXT_LEFT);
  }
  else
  {
    setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, "0.", 2, 2, BrightTextColorId, ALIGN_TEXT_LEFT);
  }
}

//==================================================================================================================================
//Minus key functions
//==================================================================================================================================

//Used for first input from the number key pad
//Displays a - and sets up the needed function pointers for inputting negative numbers
void editonminusstart(int data)
{
  int x = EDIT_ITEM_XPOS;

  //Check if channel 2 is selected
  if(currentchannel)
  {
    //Offset the display location
    x += CHANNEL_DISPLAY_X_OFFSET;
  }  
  
  edititemdouble = 0;

  numberpadfunction = editonnumpadminusstart;

  if(edititemnumberofdecimals > 0)
  {
    dotfunction = editondotminusstart;
  }
  else
  {
    dotfunction = NULL;
  }
  
  rotarydialfunction = numpadrotarydialnodot;
  enterfunction      = numpadenternodot;
  rightfunction      = NULL;
  leftfunction       = editonplusstart;
  plusfunction       = editonplusstart;
  minusfunction      = NULL;
  
  setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, "-", 1, 2, BrightTextColorId, ALIGN_TEXT_LEFT);
}

//----------------------------------------------------------------------------------------------------------------------------------

//Used when input without decimals already given
void editonminus(int data)
{
  int x = EDIT_ITEM_XPOS;

  //Check if channel 2 is selected
  if(currentchannel)
  {
    //Offset the display location
    x += CHANNEL_DISPLAY_X_OFFSET;
  }  
  
  //Invert the current value
  edititemdouble *= -1;
  
  if(edititemnumberofdecimals > 0)
  {
    dotfunction = editondotminus;
  }

  plusfunction      = editonplus;
  minusfunction     = NULL;
  numberpadfunction = editonnumpadminusnext;
  
  snprintf(textbuffer, sizeof(textbuffer), "%d", (int)edititemdouble);

  setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, textbuffer, strlen(textbuffer), 2, BrightTextColorId, ALIGN_TEXT_LEFT);
}

//----------------------------------------------------------------------------------------------------------------------------------

//Used when input with decimals already given
void editonminusdot(int data)
{
  char formatstr[20];
  double decdiv;
  int x = EDIT_ITEM_XPOS;

  //Check if channel 2 is selected
  if(currentchannel)
  {
    //Offset the display location
    x += CHANNEL_DISPLAY_X_OFFSET;
  }  
  
  if(edititemdouble == 0)
  {
    setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, "-0.", 1, 2, BrightTextColorId, ALIGN_TEXT_LEFT);
  }
  else
  {
    //Invert the current value
    edititemdouble *= -1;

    decdiv = pow(10, edititemdecimalcount);

    //Setup the format string for the needed number of decimals
    snprintf(formatstr, sizeof(formatstr), "%%.%df", edititemdecimalcount);
    
    //Need functionality here for setting up the format specifier with the correct number of decimals
    snprintf(textbuffer, sizeof(textbuffer), formatstr, edititemdouble / decdiv);
    
    setupcursor(x + EDIT_ITEM_X1, EDIT_ITEM_Y2, textbuffer, strlen(textbuffer), 2, BrightTextColorId, ALIGN_TEXT_LEFT);
  }

  plusfunction       = editonplusdot;
  minusfunction      = NULL;
  numberpadfunction  = editonnumpadminusdot;
  rotarydialfunction = numpadrotarydialdot;
}

//==================================================================================================================================
//Enter key functions
//==================================================================================================================================

//Used when decimal dot has been entered
void numpadenterdot(void)
{
  double adjmul = pow(10, (edititemnumberofdecimals - edititemdecimalcount));
  
  //Correct the value as needed
  edititemdouble *= adjmul;
  
  numpadenter();
}

//----------------------------------------------------------------------------------------------------------------------------------

//Used when only normal digits have been entered
void numpadenternodot(void)
{
  //Correct the value as needed
  edititemdouble *= edititemdecimaldivider;
  
  numpadenter();
}

//----------------------------------------------------------------------------------------------------------------------------------

//Function to handle the via the number pad entered value
void numpadenter(void)
{
  if(edititemdouble < edititemmindouble)
    edititemdouble = edititemmindouble;
  
  //Check if there is a function to call
  if(numberpadenterfunction)
  {
    //Process the normal enter
    numberpadenterfunction();
  }
}

//==================================================================================================================================
//Cursor functionality
//==================================================================================================================================

void setupcursor(int xpos, int ypos, char *text, int position, int fontid, int colorid, int align)
{
  XGlyphInfo extents;
  int l = strlen(text);

  XftFont  *font = signalgeneratorxc.font[fontid];
  
  //Stop the cursor
  cursorenable = 0;
  
  //Need to perform multiple text measurements
  //determine the start position of the character the cursor needs to be on
  //Determine the width of the character the cursor is on
  //The text align is also of interest!!!

  XftTextExtentsUtf8(signalgeneratorxc.display, font, text, position, &extents);

  cursorxpos = xpos + extents.width;
  cursorypos = ypos - font->height + font->descent;
  
  XftTextExtentsUtf8(signalgeneratorxc.display, font, &text[position], 1, &extents);
  
  cursorxpos -= extents.x;
  cursorwidth = extents.width;
  cursorheight = font->height;
  
  XftTextExtentsUtf8(signalgeneratorxc.display, font, text, l, &extents);
  
  cursortextxpos = xpos;
  cursortextypos = ypos;
  
  cursortextwidth  = EDIT_ITEM_WIDTH - 20;
  cursortextheight = font->height;
  
  cursorbgcolor   = ScreenBackgroundColor;
  cursorfgcolor   = ScreenLineColor;
  
  cursortextcolorid = colorid;
  
  cursortext = text;
  
  cursorfontid = fontid;
  cursoralign  = align;

  //Clear the text area
  FillRect(&signalgeneratorxc, cursortextxpos - 1, cursorypos - 1, cursortextwidth + 2, cursortextheight + 2, cursorbgcolor);
  
  //Might as well place the text here
  PlaceText(&signalgeneratorxc, xpos, ypos, text, fontid, colorid, align);
  
  cursorstate = 0;
  cursorenable = 1;
}

//----------------------------------------------------------------------------------------------------------------------------------

void blinkcursor(void)
{
  if(cursorenable)
  {
    //Toggle the state
    cursorstate ^= 1;
    
    //Clear the text area
    FillRect(&signalgeneratorxc, cursortextxpos - 1, cursorypos - 1, cursortextwidth + 2, cursortextheight + 2, cursorbgcolor);
    
    if(cursorstate)
    {
      //Draw the cursor
      FillRect(&signalgeneratorxc, cursorxpos, cursorypos, cursorwidth, cursorheight, cursorfgcolor);
    }
    
    //Place the text on top of the cursor
    PlaceText(&signalgeneratorxc, cursortextxpos, cursortextypos, cursortext, cursorfontid, cursortextcolorid, cursoralign);    
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
