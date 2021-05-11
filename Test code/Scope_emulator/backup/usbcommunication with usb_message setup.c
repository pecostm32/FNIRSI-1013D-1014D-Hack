//-----------------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------------

#include "usbcommunication.h"
#include "xlibfunctions.h"

#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions
#include <sys/types.h>
#include <sys/time.h>
#include <pthread.h>


//----------------------------------------------------------------------------------------------------------------------------------
// Start and stop functions
//----------------------------------------------------------------------------------------------------------------------------------

pthread_t usb_com_thread;

int quit_thread_on_zero = 0;

int startusbcommunication(void)
{
  //Setup for keep the thread running
  quit_thread_on_zero = 1;
  
  //Start up the usb thread
  return(pthread_create(&usb_com_thread, NULL, startusbcommunicationthread, NULL));
}

void stopusbcommunication(void)
{
  //Stop the usb thread
  quit_thread_on_zero = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------
// Actual communication code
//----------------------------------------------------------------------------------------------------------------------------------

void *startusbcommunicationthread(void * arg)
{
  struct termios  tty;
  struct timespec ts;
  int ledstate = 1;
  int blinkled = 0;

  ts.tv_sec  = 0;
  ts.tv_nsec = 400000000;

/*  
  //Open File Descriptor for the USB device to be used
  int USB = open("/dev/ttyUSB0", O_RDWR| O_NOCTTY);

  //Check if device is available
  if(USB < 0)
  {
    //Show a blinking led on when not
    blinkled = 1;
  }
  else
  {
    memset(&tty, 0, sizeof tty);

    //Error Handling
    if(tcgetattr(USB, &tty) != 0)
    {
      //Show a blinking led on error
      blinkled = 1;

      //Close the usb port on error
      close(USB);
    }
    else
    {
      //Set send and receive Baud Rate.
      cfsetospeed(&tty, (speed_t)B2000000);
      cfsetispeed(&tty, (speed_t)B2000000);

      //Setting other Port Stuff
      tty.c_cflag     &=  ~PARENB;            //Make 8n1
      tty.c_cflag     &=  ~CSTOPB;
      tty.c_cflag     &=  ~CSIZE;
      tty.c_cflag     |=  CS8;

      tty.c_cflag     &=  ~CRTSCTS;           //No flow control
      tty.c_cc[VMIN]   =  1;                  //Read doesn't block
      tty.c_cc[VTIME]  = 10;                  //1 seconds read timeout
      tty.c_cflag     |=  CREAD | CLOCAL;     //Turn on READ & ignore ctrl lines

      //Make raw
      cfmakeraw(&tty);

      //Flush Port before making changes
      tcflush(USB, TCIFLUSH);

      //Apply new attributes
      if(tcsetattr(USB, TCSANOW, &tty) != 0)
      {
        //Show a blinking led on error
        blinkled = 1;

        //Close the usb port on error
        close(USB);
      }
    }
  }
*/
  //Check if usb device is connected 
  if(blinkled == 0)
  {  
    //Signal the thread is up and running
    Opera6LedSetState(&leds[27], ledstate);
    
#ifdef USB_DEBUG_WINDOW
    //Setup for debug display
    usbopendebugwindow();
#endif
  }

  //Keep the thread alive until stop requested
  while(quit_thread_on_zero)
  {
    //Check if USB device failed to open
    if(blinkled)
    {
      //If so blink the led to show the user there is a problem
      Opera6LedSetState(&leds[27], ledstate);
      
      //Toggle the state
      ledstate ^= 1;
      
      //To allow for a nice blink rate go to sleep for a while
      nanosleep(&ts, NULL);
    }
    else
    {
    }
  }
  
  //Show the user the process has been stopped
  Opera6LedSetState(&leds[27], 0);

  //Check if the usb device was opened and close it if so
  if(blinkled == 0)
  {
#ifdef USB_DEBUG_WINDOW
    //Close the debug window
    usbclosedebugwindow();
#endif
    
//    close(USB);
  }
  
  //Exit the thread the way it is supposed to
  pthread_exit(NULL);
}

//----------------------------------------------------------------------------------------------------------------------------------
// Debug code
//----------------------------------------------------------------------------------------------------------------------------------

#ifdef USB_DEBUG_WINDOW
pthread_t usb_debug_window;

Window usb_info = 0;
Atom   usb_message = 0;
Atom   WM_DELETE_WINDOW = 0;
Atom   WM_PROTOCOLS = 0;

tagXlibContext usbdbgctx;

void usbopendebugwindow(void)
{
 //Start the thread for the usb debug window
  pthread_create(&usb_debug_window, NULL, createdialogwindow, NULL);
}

void usbclosedebugwindow(void)
{
	Display *display = XOpenDisplay(NULL);
  XEvent   event;
 
  event.xclient.type = ClientMessage;
  event.xclient.display = display;
  event.xclient.window = usb_info;
  event.xclient.message_type = WM_PROTOCOLS;
  event.xclient.format = 32;
  event.xclient.data.l[0] = WM_DELETE_WINDOW;

  XSendEvent(display, usb_info, False, NoEventMask, &event);
  
  XCloseDisplay(display);
}

void usbsenddebugmessage(void)
{
	Display *display = XOpenDisplay(NULL);
  XEvent   event;
 
  event.xclient.type = ClientMessage;
  event.xclient.display = display;
  event.xclient.window = usb_info;
  event.xclient.message_type = usb_message;
  event.xclient.format = 8;

  XSendEvent(display, usb_info, False, NoEventMask, &event);
  
  XCloseDisplay(display);
}

void *createdialogwindow(void *arg)
{
  //Keep the while loop running until a delete window comes in
  int rflag = 1;
  
  XEvent event;
	Display *display = XOpenDisplay(NULL);
	int screen_num = DefaultScreen(display);
	Window root = RootWindow(display, screen_num);
	usb_info = XCreateSimpleWindow(display, root, 0, 0, 300, 500, 2, BlackPixel(display, screen_num), WhitePixel(display, screen_num));
  
 	XMapWindow(display, usb_info);

  //Handle exposure and client messages
	XSelectInput(display, usb_info, ExposureMask | StructureNotifyMask);
  
	GC gc = XCreateGC(display, usb_info, 0, NULL);
  
  //Setup for deleting the window with the x button
  WM_DELETE_WINDOW = XInternAtom(display, "WM_DELETE_WINDOW", False); 
  WM_PROTOCOLS = XInternAtom(display, "WM_PROTOCOLS", 0);
  XSetWMProtocols(display, usb_info, &WM_DELETE_WINDOW, 1);  
  
  //Set info for sending client messages to the window
  usb_message = XInternAtom(display, "USB_MESSAGE", 0);
  
  
  usbdbgctx.display = display;
  usbdbgctx.win = usb_info;
  usbdbgctx.root = root;
  usbdbgctx.gc = gc;
  
  //Keep running until window is destroyed
	while(rflag)
	{
    //Wait for the next event for this window
		XNextEvent(display, &event);
    
    //Handle it based on its type
		switch(event.type)
		{
			case Expose:
				break;
        
      case ClientMessage:
        //Check if delete window has been clicked
        if((event.xclient.message_type == WM_PROTOCOLS) && (event.xclient.data.l[0] == WM_DELETE_WINDOW))
        {
					rflag = 0;
        }
        else if(event.xclient.message_type == usb_message)
        {
          //Display text in the debug window
        }
        break;
		}
	}
  
  //Throw away the window and close up the display
  XDestroyWindow(display, usb_info);
	XCloseDisplay(display);
  
  //Stop the thread the way it is supposed to
  pthread_exit(NULL);
}


#endif




//Hier de code voor het debug window opnemen met een #ifdef er omheen zodat het makkelijk uit te zetten is.
//Doordat alles dan in zelfde source zit zijn er ook geen externals nodig voor koppelen


//Moet verbinding maken met usb poort voor serieele communicatie
//Moet uit een message buffer berichten lezen die verstuurd moeten worden
//Bericht is een tekst regel met een cr afsluiter

//Als een bericht verzonden wordt moet deze ook in debug window getoond worden.


//Berichten zijn max 5 bytes voor instructie, 1 byte voor =, 3 bytes voor waarde en 2 bytes voor afsluiter. Denk aan een array van strings van 16 bytes lang en dan 32 berichten diep
//Wel zorgen voor een locking mechanisme als buffer vol loopt.

//Zijn dus pointers nodig voor inkomende berichten, uitgaande berichten en in debug window getoonde berichten.




