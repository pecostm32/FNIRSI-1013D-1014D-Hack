//----------------------------------------------------------------------------------------------------------------------------------

#ifndef USER_INTERFACE_FUNCTIONS_H
#define USER_INTERFACE_FUNCTIONS_H

//----------------------------------------------------------------------------------------------------------------------------------

void runstopbutton(void);                    //Button functions are only called on button up. On the computer no simultaneous actions.
void autobutton(void);
void menubutton(void);
void savepicturebutton(void);
void savewavebutton(void);
void horizontalcursorbutton(void);
void verticalcursorbutton(void);
void rightbutton(void);
void upbutton(void);
void okbutton(void);
void downbutton(void);
void leftbutton(void);
void slowbutton(void);
void ch1enablebutton(void);
void ch1configbutton(void);
void ch2enablebutton(void);
void ch2configbutton(void);
void originbutton(void);
void triggermodebutton(void);
void triggeredgebutton(void);
void triggerchannelbutton(void);
void trigger50percentbutton(void);
void f1button(void);
void f2button(void);
void f3button(void);
void f4button(void);
void f5button(void);
void f6button(void);
void generatorbutton(void);
void nextbutton(void);
void lastbutton(void);
void deletebutton(void);
void selectallbutton(void);
void selectbutton(void);
void powerbutton(void);

void selectdial(int direction);          //The rotary dial gets either +1 or -1 as data
void ch1position(int direction);
void ch2position(int direction);
void triggerposition(int direction);
void triggerlevel(int direction);
void ch1sensitivity(int direction);
void ch2sensitivity(int direction);
void timeperdiv(int direction);

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* USER_INTERFACE_FUNCTIONS_H */

//----------------------------------------------------------------------------------------------------------------------------------
