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
