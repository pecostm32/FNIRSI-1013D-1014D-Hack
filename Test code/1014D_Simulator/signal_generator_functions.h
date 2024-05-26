//----------------------------------------------------------------------------------------------------------------------------------

#ifndef SIGNAL_GENERATOR_FUNCTIONS_H
#define SIGNAL_GENERATOR_FUNCTIONS_H

//----------------------------------------------------------------------------------------------------------------------------------

#define CHANNEL1_ENABLE_LED                      0
#define CHANNEL1_PULSE_WIDTH_ENABLE_LED          1

#define CHANNEL2_ENABLE_LED                      2
#define CHANNEL2_PULSE_WIDTH_ENABLE_LED          3

#define MODE_WAVEFORM_LED                        4
#define MODE_FREQUENCY_LED                       5
#define MODE_PHASE_LED                           6
#define MODE_LOAD_LED                            7
#define MODE_AMPLITUDE_LED                       8
#define MODE_DC_OFFSET_LED                       9
#define MODE_PULSE_WIDTH_LED                    10
#define MODE_SAVE_LED                           11

#define MAGNITUDE_HZ_LED                        12
#define MAGNITUDE_KHZ_LED                       13
#define MAGNITUDE_MHZ_LED                       14

#define SELECT_CHANNEL1_LED                     15
#define SELECT_CHANNEL2_LED                     16

//----------------------------------------------------------------------------------------------------------------------------------

#define MODE_ITEM_WAVEFORM                       0
#define MODE_ITEM_FREQUENCY                      1
#define MODE_ITEM_PHASE                          2
#define MODE_ITEM_LOAD                           3
#define MODE_ITEM_AMPLITUDE                      4
#define MODE_ITEM_DC_OFFSET                      5
#define MODE_ITEM_PULSE_WIDTH                    6
#define MODE_ITEM_SAVE                           7

//----------------------------------------------------------------------------------------------------------------------------------

#define NUMBER_OF_WAVEFORMS                      5

//----------------------------------------------------------------------------------------------------------------------------------

//Function pointer to handle the events
typedef void (*HANDLEINPUT)(int data);
typedef void (*HANDLEFUNCTION)(void);

typedef void (*DISPLAYFUNCTION)(void);

//----------------------------------------------------------------------------------------------------------------------------------

void DrawSignalGeneratorFrontPanel(tagXlibContext *xc);

void SignalGeneratorShowSignal(tagXlibContext *xc, int channel);

void SignalGeneratorDrawSignal(tagXlibContext *xc, int xpos, int channel);

double calcsample(int waveform, double pulsewidth, double phase);

void formatwavetime(double time);

//----------------------------------------------------------------------------------------------------------------------------------

void initializewaveformedit(void);
void waveformeditenter(void);

void initializefrequencyedit(void);
void frequencyeditenter(void);

void initializephaseedit(void);
void phaseeditenter(void);

void initializeamplitudeedit(void);
void amplitudeeditenter(void);

void initializedcoffsetedit(void);
void dcoffseteditenter(void);

void initializepulsewidthedit(void);
void pulsewidtheditenter(void);

//----------------------------------------------------------------------------------------------------------------------------------

void togglechannel1enable(void);
void togglechannel1pulsewidthenable(void);

void togglechannel2enable(void);
void togglechannel2pulsewidthenable(void);

void togglechannelselect(void);

void selectfrequencyhz(void);
void selectfrequencykhz(void);
void selectfrequencymhz(void);

void handlerotarydial(int direction);

void handleleftarrowkey(void);
void handlerightarrowkey(void);

void handlenumber0key(void);
void handlenumber1key(void);
void handlenumber2key(void);
void handlenumber3key(void);
void handlenumber4key(void);
void handlenumber5key(void);
void handlenumber6key(void);
void handlenumber7key(void);
void handlenumber8key(void);
void handlenumber9key(void);

void handlenumberdotkey(void);
void handlenumberminuskey(void);
void handlenumberpluskey(void);
void handlenumbercancelkey(void);
void handlenumberenterkey(void);

void handlenumberkey(int key);

//----------------------------------------------------------------------------------------------------------------------------------

void togglepulsewidthenable(int channel, int led);

void selectfrequencymagnitude(int magnitude);

//----------------------------------------------------------------------------------------------------------------------------------

void updatethescreen(void);

void finishedit(void);

void displayedititem(int channel);

//----------------------------------------------------------------------------------------------------------------------------------
//Select functionality

void selectinitialize(int id, int value, const char *header, const char *text, const char **list, int count);

void selectonrotarydial(int data);
void selectonnumpad(int data);

void selectshowitems(void);

//----------------------------------------------------------------------------------------------------------------------------------

void editinitialize(int id, double value, const char *header, const char *type, int numdecimals, double minvalue, double maxvalue);

void editonrotarydial(int data);

void editmovecursorleft(int data);
void editmovecursorright(int data);

void editonnumpadstart(int data);
void editonnumpadnext(int data);
void editonnumpaddot(int data);

void editonnumpadminusstart(int data);
void editonnumpadminusnext(int data);
void editonnumpadminusdot(int data);

void numpadleftnodot(int data);
void numpadleftdot(int data);
void numpadleftminusnodot(int data);
void numpadleftminusdot(int data);

void numpadenterdot(void);
void numpadenternodot(void);
void numpadenter(void);


void numpadrotarydialnodot(int data);
void numpadrotarydialdot(int data);
void numpadrotarydial(int data);

void editonplusstart(int data);
void editonplus(int data);
void editonplusdot(int data);

void editonminusstart(int data);
void editonminus(int data);
void editonminusdot(int data);

void editondotstart(int data);
void editondot(int data);
void editondotminusstart(int data);
void editondotminus(int data);

void editshowitem(void);

//----------------------------------------------------------------------------------------------------------------------------------

void setupcursor(int xpos, int ypos, char *text, int position, int fontid, int colorid, int align);

void blinkcursor(void);

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* SIGNAL_GENERATOR_FUNCTIONS_H */

//----------------------------------------------------------------------------------------------------------------------------------


