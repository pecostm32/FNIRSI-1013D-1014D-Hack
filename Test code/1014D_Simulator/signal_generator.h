//----------------------------------------------------------------------------------------------------------------------------------

#ifndef SIGNAL_GENERATOR_H
#define SIGNAL_GENERATOR_H

//----------------------------------------------------------------------------------------------------------------------------------

#include "xlibfunctions.h"

#include "sg_led.h"
#include "sg_buttons.h"
#include "sg_rotary_dial.h"

//----------------------------------------------------------------------------------------------------------------------------------

#define PanelTextColor                "#E3D9CA"
#define ButtonTextColor               "#000000"
#define BrightTextColor               "#B4FFFE"
#define DimmedTextColor               "#549F9E"

#define PanelTextColorId              0
#define ButtonTextColorId             1
#define BrightTextColorId             2
#define DimmedTextColorId             3

//----------------------------------------------------------------------------------------------------------------------------------

#define BorderColor                   0x000000
#define PanelColor                    0x414244
#define PanelLineColor                0xE3D9CA

#define ScreenBackgroundColor         0x202020
#define ScreenLineColor               0x549F9E
#define ScreenSignalColor             0xB4FFFE

//----------------------------------------------------------------------------------------------------------------------------------
//Due to possible overlap in the two signal displays both need to be redrawn and the screen needs to be cleared on forehand

#define CHANNEL_DISPLAY_XPOS        144
#define CHANNEL_DISPLAY_YPOS        114

#define CHANNEL_DISPLAY_WIDTH       400
#define CHANNEL_DISPLAY_HEIGHT      460

#define CHANNEL_CLEAR_X_OFFSET      -70
#define CHANNEL_CLEAR_Y_OFFSET      -40

#define CHANNEL_DISPLAY_X_OFFSET    385

#define CHANNEL_DISPLAY_HEADER_Y    (CHANNEL_DISPLAY_YPOS - 14)

#define VERTICAL_SPACER             12

#define VERTICAL_TEXT_X1_OFFSET     -2
#define VERTICAL_TEXT_X2_OFFSET     134

#define VERTICAL_TEXT_Y1            (CHANNEL_DISPLAY_YPOS + 4)
#define VERTICAL_TEXT_Y2            ((VERTICAL_SPACER * 9) + VERTICAL_TEXT_Y1)
#define VERTICAL_TEXT_Y3            ((VERTICAL_SPACER * 18) + VERTICAL_TEXT_Y1)

#define VERTICAL_LINE_X1_OFFSET     6
#define VERTICAL_LINE_X2_OFFSET     12
#define VERTICAL_LINE_X3_OFFSET     308

#define VERTICAL_LINE_Y1            CHANNEL_DISPLAY_YPOS
#define VERTICAL_LINE_Y2            (CHANNEL_DISPLAY_YPOS + (VERTICAL_SPACER * 18) + 1)

#define HORIZONTAL_SPACER           12

#define HORIZONTAL_LINE_X1_OFFSET   8
#define HORIZONTAL_LINE_X2_OFFSET   12
#define HORIZONTAL_LINE_X3_OFFSET   308

#define HORIZONTAL_SIGNAL_WIDTH     288
#define HORIZONTAL_SIGNAL_CENTER    ((HORIZONTAL_SIGNAL_WIDTH / 2) + HORIZONTAL_LINE_X2_OFFSET)

#define HORIZONTAL_LINE_Y1          (CHANNEL_DISPLAY_YPOS + (VERTICAL_SPACER * 18) + 2)
#define HORIZONTAL_LINE_Y2          (CHANNEL_DISPLAY_YPOS + (VERTICAL_SPACER * 18) + 8)
#define HORIZONTAL_LINE_Y3          (CHANNEL_DISPLAY_YPOS + (VERTICAL_SPACER * 18) + 13)
#define HORIZONTAL_LINE_Y4          (CHANNEL_DISPLAY_YPOS + (VERTICAL_SPACER * 18) + 17)
#define HORIZONTAL_LINE_Y5          (CHANNEL_DISPLAY_YPOS + (VERTICAL_SPACER * 18) + 22)
#define HORIZONTAL_LINE_Y6          (CHANNEL_DISPLAY_YPOS + (VERTICAL_SPACER * 18) + 28)

#define HORIZONTAL_TEXT_Y1          (HORIZONTAL_LINE_Y5 + 5)
#define HORIZONTAL_TEXT_Y2          (HORIZONTAL_LINE_Y6 + 10)

#define HORIZONTAL_TEXT_X1_OFFSET   14
#define HORIZONTAL_TEXT_X2_OFFSET   12
#define HORIZONTAL_TEXT_X3_OFFSET   300

#define SETTINGS_TEXT_SPACING       18

#define SETTINGS_TEXT_Y1            (CHANNEL_DISPLAY_YPOS + (VERTICAL_SPACER * 18) + 90)
#define SETTINGS_TEXT_Y2            (SETTINGS_TEXT_Y1 + SETTINGS_TEXT_SPACING)
#define SETTINGS_TEXT_Y3            (SETTINGS_TEXT_Y2 + SETTINGS_TEXT_SPACING)
#define SETTINGS_TEXT_Y4            (SETTINGS_TEXT_Y3 + SETTINGS_TEXT_SPACING)
#define SETTINGS_TEXT_Y5            (SETTINGS_TEXT_Y4 + SETTINGS_TEXT_SPACING)
#define SETTINGS_TEXT_Y6            (SETTINGS_TEXT_Y5 + SETTINGS_TEXT_SPACING)
#define SETTINGS_TEXT_Y7            (SETTINGS_TEXT_Y6 + SETTINGS_TEXT_SPACING)

#define SIGNAL_HEIGHT               (VERTICAL_SPACER * 18)
#define SIGNAL_WIDTH                (HORIZONTAL_SPACER * 24)

#define EDIT_ITEM_XPOS              308
#define EDIT_ITEM_YPOS              (SETTINGS_TEXT_Y1 - SETTINGS_TEXT_SPACING - 24)

#define EDIT_ITEM_WIDTH             156
#define EDIT_ITEM_HEIGHT            168

#define EDIT_ITEM_SPACING           16

#define EDIT_ITEM_X1                8
#define EDIT_ITEM_X2                16
#define EDIT_ITEM_X3                (EDIT_ITEM_WIDTH / 2)

#define EDIT_ITEM_Y1                (EDIT_ITEM_YPOS + 16)
#define EDIT_ITEM_Y2                (EDIT_ITEM_Y1 + 24)
#define EDIT_ITEM_Y3                (EDIT_ITEM_Y2 + 24)
#define EDIT_ITEM_Y4                (EDIT_ITEM_Y3 + EDIT_ITEM_SPACING)
#define EDIT_ITEM_Y5                (EDIT_ITEM_Y4 + EDIT_ITEM_SPACING)

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct tagSignalGeneratorChannelSettings         SIGNALGENERATORCHANNELSETTINGS,        *PSIGNALGENERATORCHANNELSETTINGS;

//----------------------------------------------------------------------------------------------------------------------------------

struct tagSignalGeneratorChannelSettings
{
  int waveform;
  int channelenable;
  int pulsewidthenable;
  int frequencymagnitude;
  
  int amplitudechanged;
  int dcoffsetchanged;
  int frequencychanged;
  int pulsewidthchanged;
  int pulsewidthenablechanged;
  int phasechanged;
  
  double amplitude;
  double maxamplitude;
  double dcoffset;
  double frequency;
  double pulsewidth;
  double phase;
  double previousphase;
  
  double signalperiod;
  double signaltime;
  double signaltimestep;
  double signaltimepart1;
  double signaltimepart2;
  
  double maxsignal;
  double minsignal;
};

//----------------------------------------------------------------------------------------------------------------------------------

int startsignalgenerator(void);
void stopsignalgenerator(void);

void *signalgeneratorthread(void *arg);

//----------------------------------------------------------------------------------------------------------------------------------

void signalgeneratorfreeze(void);
void signalgeneratorunfreeze(void);

void signalgeneratorgetsamples(int channel, double *buffer, int count, double samplerate);

double signalgeneratorgetsample(int channel, int delay, double samplerate);

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* SIGNAL_GENERATOR_H */
