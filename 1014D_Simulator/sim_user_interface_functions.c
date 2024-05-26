//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"

//----------------------------------------------------------------------------------------------------------------------------------

uint8 userinterfacecommand = 0;    //Variable to hold the command to be sent to the main process
uint8 userinterfaceflag = 0;       //Flag to signal there is a command to send to the main process

//----------------------------------------------------------------------------------------------------------------------------------

void runstopbutton(void)
{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 1;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void autobutton(void)
{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 2;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void menubutton(void)
{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 3;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void savepicturebutton(void)
{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 4;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void savewavebutton(void)
{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 5;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void horizontalcursorbutton(void)
{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 6;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void verticalcursorbutton(void)
{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 7;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void rightbutton(void)
{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 8;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void upbutton(void)
{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 9;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void okbutton(void)
{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 10;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void downbutton(void)
{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 11;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void leftbutton(void)
{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 12;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void slowbutton(void)

{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 13;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void ch1enablebutton(void)

{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 14;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void ch1configbutton(void)

{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 15;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void ch2enablebutton(void)

{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 16;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void ch2configbutton(void)

{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 17;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void originbutton(void)

{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 18;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void triggermodebutton(void)

{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 19;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void triggeredgebutton(void)

{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 20;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void triggerchannelbutton(void)

{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 21;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void trigger50percentbutton(void)

{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 22;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void f1button(void)

{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 23;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void f2button(void)

{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 24;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void f3button(void)

{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 25;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void f4button(void)

{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 26;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void f5button(void)

{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 27;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void f6button(void)

{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 28;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void generatorbutton(void)

{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 29;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void nextbutton(void)

{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 30;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void lastbutton(void)

{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 31;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void deletebutton(void)

{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 32;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void selectallbutton(void)

{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 33;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void selectbutton(void)

{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 34;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void powerbutton(void)

{
  if(userinterfaceflag == 0)
  {
    userinterfacecommand = 200;
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void selectdial(int direction)
{
  if(userinterfaceflag == 0)
  {
    if(direction == 1)
    {
      userinterfacecommand = 35;
    }
    else
    {
      userinterfacecommand = 36;
    }
    
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void ch1position(int direction)
{
  if(userinterfaceflag == 0)
  {
    if(direction == 1)
    {
      userinterfacecommand = 38;
    }
    else
    {
      userinterfacecommand = 37;
    }
    
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void ch2position(int direction)
{
  if(userinterfaceflag == 0)
  {
    if(direction == 1)
    {
      userinterfacecommand = 40;
    }
    else
    {
      userinterfacecommand = 39;
    }
    
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void triggerposition(int direction)
{
  if(userinterfaceflag == 0)
  {
    if(direction == 1)
    {
      userinterfacecommand = 42;
    }
    else
    {
      userinterfacecommand = 41;
    }
    
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void triggerlevel(int direction)
{
  if(userinterfaceflag == 0)
  {
    if(direction == 1)
    {
      userinterfacecommand = 43;
    }
    else
    {
      userinterfacecommand = 44;
    }
    
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void ch1sensitivity(int direction)
{
  if(userinterfaceflag == 0)
  {
    if(direction == 1)
    {
      userinterfacecommand = 46;
    }
    else
    {
      userinterfacecommand = 45;
    }
    
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void ch2sensitivity(int direction)
{
  if(userinterfaceflag == 0)
  {
    if(direction == 1)
    {
      userinterfacecommand = 48;
    }
    else
    {
      userinterfacecommand = 47;
    }
    
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void timeperdiv(int direction)
{
  if(userinterfaceflag == 0)
  {
    if(direction == 1)
    {
      userinterfacecommand = 50;
    }
    else
    {
      userinterfacecommand = 49;
    }
    
    userinterfaceflag = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

