# FNIRSI-1013D-Hack
Resources gathered for reverse engineering the FNIRSI-1013D scope

As part of what is on EEVBLOG, resources for the reverse engineering of the FNIRSI-1013D scope are put together in a single repository.

As it is an ongoing process more and more data will be added over time.

The touch panel problem that lead to this hack has been resolved. On the forum there is an arduino sketch that can be used to re configure the touch panel
and in this repository there is a new firmware file for the scope. This is for the scope version with the W25Q32 flash chip (32Mbit). This is also the scope
that has the problems with the reversed coordinates when the touch panel is replaced with one that uses a GOODIX GT915(7) touch panel controller.

There are two other repositories with code for the STM32F103 based bluepill boards for reading and writing the touch panel configuration, but when used in
combination with Windows they seem not to do what is wanted.

On the 1st of May 2021 a new hack has been made where the configuration for the touch panel has been modified. 
This eliminates the use of the above mentioned tools for changing the touch panel config back to how it should be. The scope does this directly. 
The new file can be found here: https://github.com/pecostm32/FNIRSI-1013D-Hack/blob/main/Binaries/Hacked%20files/W25Q32_scope_tp_conf_changed.bin

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!! BE AWARE.
!! The scope has some special data stored in the flash at address 0x001FD000. 
!! There are 0x1F4 bytes there that are loaded after the scope has started. It could be
!! some calibration data.
!!
!! SO ALWAYS make a copy of your own flash first and compare the data with what is in the new firmware
!! file. When different copy your own data in
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


The hack continues with the quest on revealing the secrets of the FPGA that is used in the scope. For now it is solely based on figuring out what the software
does with it. If this does not yield what is needed a reverse engineering of the FPGA might be needed, but is far more difficult.

There is progress in getting to an open source version. The bootloader is reversed to a C project and it is working.

The main program is slowly revealing its secrets.

For this to happen an emulator is being written. It is quite the job but it is already running the boot loader code and some of the initialization of the
main program. The startup imagewith the FNIRSI logo is displayed and the emulator window shows the processor status and the registers when the core is running.
Still a lot of work needs to be done before it is finished. Hopefully it will aid in a full reversal of the actual code.

The emulator is functional and the working of the system is slowly being revealed. Quite a few commands to control the FPGA are now known.

----------------------------------------------------------------------------------------------------------
14-JUNE-2021
Most of the FPGA functions have been discovered and described. With the emulator the sequence of commands have been traced. 
With this information it should be possible to write new software for the scope.

----------------------------------------------------------------------------------------------------------
22-JUNE-2021
The process of reversing the complete software is still ongoing. Focus at the moment is on the display library. 
Data structures are being discovered, with which the reversal of the code becomes more and more possible.
The font data being used has been found in the flash. There are 8 fonts. The Ghidra archive uploaded today has them labeled and commented.

----------------------------------------------------------------------------------------------------------
26-JUNE-2021
Wrote a font extractor and got font_2 from the binary.
Also found more about the working of the color handling. Uploaded the Ghidra archive with the latest findings. Still a long way to go.

----------------------------------------------------------------------------------------------------------
05-JULY-2021
Extracted the fonts and tested them with HTML and javascript. Looks like they used two font types. 
A variable width type like Arial and a fixed with type like courier. Since they use bitmap versions a separate font is needed for each size in use.
Started with a new netbeans project for the scope code. Made a simple display library to display text and draw rectangles. Tested the code in the emulator.
Need to make a code packer to write the separate parts to a binary file. (second program loader, bitmap and main program)
Did it by hand for the tests, but is not a great solution:-(

----------------------------------------------------------------------------------------------------------
08-JULY-2021
Found how the scope display's the menus. It uses a lot of bitmaps that are copied to the display instead of printing text. 
Updated the Ghidra archive with the new findings.
The recreation of the scope project is setup to create a binary in the emulator project directory and start the emulator for testing.
Checked a couple of the fill rects from the original scope code to see where they are used for. 
Found that the original code uses start and end coordinates to define a rectangle were as my code uses positions and dimensions. 
Not a big deal and might change my setup.

----------------------------------------------------------------------------------------------------------
11-JULY-2021
Finished the largest part of the display library. The recreation of the scope code can begin. Started with the structures to hold the scope settings.
Next up is making the functions to display things on the screen. Also need to write the touchscreen code to be able to control the scope.

----------------------------------------------------------------------------------------------------------
20-JULY-2021
Wrote a lot of the display functions and the touchpanel interface functions. Now I found a lot of the variables used in the scope,
like time base setting and trigger mode it is becoming more and more clear what the scope is doing. 
The earlier findings about the working of the FPGA can be seen in the code. The second function in the main while loop seems to be the trace processing.
In the first section a check is made on the time base setting and when below 9 (100mS/div to 50S/div) 
it writes the FPGA command 0x0D with the value 0x000007D0, just as what I found in my explorations:-)

----------------------------------------------------------------------------------------------------------
23-JULY-2021
Implemented channel 1 menu handling and are now able to change the settings for it. Found functions that control the FPGA based on the settings
again confirming the earlier findings. Writing the emulator was worth it. Without it I would not have gotten this far. It also allows for testing the code
I'm writing, without the need for loading it to the actual scope.

----------------------------------------------------------------------------------------------------------
27-JULY-2021
All the top menus are implemented and except for the main manu functional. The main menu allows for opening the system settings menu.
The other options are not yet implemented. The system settings menu is displayed and the screen brightnes setting can be opened.
The base of the slider is shown, but the rest still needs to be implemented.
The latest Ghidra archive has more and more of the functions identified. The C implementation being made is not a one to one
copy, but the functionality is the same.

----------------------------------------------------------------------------------------------------------
31-JULY-2021
Finished the user interface framework.
Also made a new bootloader that allows loading of the new scope code through FEL for easy testing.

With this bootloader it is possible to start the scope in FEL mode with the DRAM enabled. The FNIRSI startup image is displayed.
"sudo ./sunxi-fel -p spl fnirsi_1013d_startup_with_fel.bin" starts the system and returns to FEL. After this DRAM is enabled and FEL is active.
"sudo ./sunxi-fel -p write 0x7FFFFFE0 fnirsi_1013d_scope.bin exe 0x80000000" then loads and executes the output of the scope project

----------------------------------------------------------------------------------------------------------
02-AUGUST-2021
Tested and tweaked the FPGA parameter ic code I wrote a while back. Is needed for the screen brightness setting. In the original code there are some delay's
in between the different actions, of which only one is realy needed. Between the writing and the reading it needs a fair amount of time. Not for the FPGA,
but for the special IC that is communicated with. To short a time and the reading part needs to be repeated. Used another scope to tweak the delay loop such
that it only needs one read action.

Also tweaked the touch panel speed after changing the delay function to assembly code. It is now around 200KHz

The remainder of the user interface, the moving of the traces, cursors, trigger position and timebase change are left for when the scope part is implemented.
Took a look at that part of the user interface code and it is messy, but it starts to make some sense.

Started with the implementation of the functions that send commands to the FPGA. Hooked a lot of them into the user interface and it is now possible to
adjust the channel sensitivity and hear the relay's click.

----------------------------------------------------------------------------------------------------------
06-AUGUST-2021
Fixed a bug in the fpga read parameter function. A local variable was not initialized:-(
Implemented timer0 interrupt handling, somewhat based on the original code, but can do with improvement.
Started implementation of trace data capture. This will take a bit of time. A lot of code to work through.

----------------------------------------------------------------------------------------------------------
11-AUGUST-2021
Got the long time base trace capture and display working. Still has a problem in the timing area, but signals are apearing on the screen.
The short time base trace capture is partially implemented and is still a lot of work to get it all implemented. Have to take a side step and implement
the remainder of the user interface first. This concerns the moving of the traces and the cursors and the adjusting of the time base setting.

----------------------------------------------------------------------------------------------------------
13-AUGUST-2021
Got the adjusting of the time base setting working. Started with the implementation of the trace, cursor and pointers moving. The signal traces can be moved,
but the display flickers when this is done. Need to improve on this trace display refresh. It is done directly to the main display buffer, but needs a separate
buffer to build it in and then copy to the main buffer to make it more steady.

Switching down to 50nS/div kills the program, but this most likely has to do with the fact that the 50nS processing is only partialy implemented.

----------------------------------------------------------------------------------------------------------
11-SEPTEMBER-2021
Been busy with the SD card part of the code and managed to get FatFs into the mix and filled in the functions for talking to the card.
Need to fill in the file operations on top of FatFs and the connections with the user interface. A fair amount of work, but with most 
of the FatFs functions identified it won't be to hard to do.

----------------------------------------------------------------------------------------------------------
15-SEPTEMBER-2021
Started with the implementation of the picture and wavefrom view part of the code.
Most of the original code on this subject has been analyzed now and judged as crap, so my version will differ in code, but will try to
match the functionality and looks as close as possible.

----------------------------------------------------------------------------------------------------------
13-OCTOBER-2021
Made quite a bit of progress, but the reversing of the short time base handling code is a big task. Made a list of what is done and still needs
to be done.

=====================
Implemented so far
=====================
System setup
Timer interrupt
Touch panel interface
Flash reading and writing
SD card functionality based on FatFs
FPGA interface functions
Display library
Battery charge measurement
Power off interrupt for settings save
Saving and loading of the settings to and from flash
Cursor measurements display
User interface
  The main screen with all the menus
  The picture view screen with picture view almost done. (Still needs displaying of the trace data)
  The waveform view screen with waveform view almost done. (Still needs displaying of the trace data)
  Saving of pictures and waveforms
Trace data handling and displaying
  Long time base settings 50S-100mS. (This is in roll mode and fully done)
  Short time base settings 50mS-10nS. (This is partially implemented. Channel 1 data is fetched and displayed raw. Only part of the processing is implemented.)

=====================
Still to do
=====================
USB interface
Finish the picture and waveform single item view. Needs the trace data processing functionality
Trace processing and displaying for the short time bases (50mS-10nS)
Calibration
Auto set
Measurements calculations and displaying
FFT calculation and displaying
Firmware update (This means both code within my version as creating an actual firmware update that can be loaded on a scope)

