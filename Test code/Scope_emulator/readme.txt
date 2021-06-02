Far from finished and only here for safe keeping.

The arm core is running but functions are missing and some might have errors.

It needs implementation of all the internal peripherals of the F1C100s.

There is no connection with the emulator or scope screen yet.

Most of the thumb instructions are implemented. So far only push and pop are tested.

----------------------------------------------------------------------------------------------
15-May-2021 15:00
Test case is the boot loader of the scope. For now it runs to address 0x04E4 where it encounters a not yet implemented strd instruction,
so this one is next on the list.

----------------------------------------------------------------------------------------------
15-May-2021 19:30
Implemented the missing instructions and tested again. It now runs to address 0x0B3C where it hits a 
mul instruction. Did not implement that yet, so that is next on the list.

----------------------------------------------------------------------------------------------
16-May-2021 11:00
Most of the instructions for both arm and thumb are implemented. The code now runs to a loop at address 0x14B0 where it checks on
PLL_DDR_CTRL_REG to see if the PLL is locked and stable. Since no peripheral part of the F1C100s is implemented yet the code is stuck on that check.

----------------------------------------------------------------------------------------------
17-May-2021 11:40
Implemented some basic response for the clock and dram control so the code now runs to 0x051c where it calls the spi0 for flash initialization routine.
Added the outline for the spi and need to implement the functionality for it to be able to load the bitmap and the main program.
Still a lot of work needs to be done. For the arm core interrupt and exception handling needs to be implemented. For the F1C100s a lot of the
other peripherals need to be implemented.

----------------------------------------------------------------------------------------------
21-May-2021 21:10
The code is getting shape. The main scope code loads but runs into an endless wait loop when calling sys_init_display. The startup image is loaded and
the emulator needs to display this on the scope window. For this the project is being modified to use shared memory and the ability to put an XImage on
the screen. The shared memory part seems to work since the project starts and runs the scope code. Hope to get the display working tomorrow.
After that it is still a lot of work to implement the rest of the peripherals, the interrupt system and the emulator stuff like disassembly,
breakpoints and tracing.

----------------------------------------------------------------------------------------------
24-May-2021 19:50
Implemented the core interrupt handling for just the irq and finished the f1c100s timer and intc peripheral to do what is needed for the scope code.
Unfortunately the scope code goes wrong at address 0x800197AC where it jumps to address 0 where there is no valid code.
To be able to see where it goes wrong I implemented a better tracing system. For this I need to write a program that can read the trace information.

----------------------------------------------------------------------------------------------
30-May-2021 20:25
Fixed several errors in both the arm and the thumb instruction handling.
1) ARM condition code checks had errors
2) Thumb branch condition code checks had the same errors
3) The thumb special data processing instructions were not being handled
4) Fixed thumb instruction short not being written in the trace buffer. Instead the last arm_instruction was used.
5) The thumb instruction union had a copy paste not modify error. The struct type for branch type 7 in the union was not modified from type 6 and
   therefore bl, bl / blx combination failed.
6) Added the clz instruction
   
Also looked into the memory management system and decided it is not needed in the emulator for running the scope.

The scope is now running down into the sd card handling code and sits there since the peripheral is not yet implemented.

----------------------------------------------------------------------------------------------
31-MAY-2021 20:50
Modified the original scope code to remove the SD card check to allow testing of the emulator without implementing the SD peripheral. To use it remanme the
original W25Q32_scope.bin file and rename the W25Q32_scope_no_sd.bin to W25Q32_scope.bin. The emulater as is will then display the basic scope screen.

Started with the implementation of the touch panel emulation to be able to control the emulated scope. This should work since the scope code ends up in 
the infinite main loop where it does the actual scope process.

Still needs a lot of work before it is a fully functional emulator, but the main target is to get to the FPGA commands used so one can write it's
own scope program.

----------------------------------------------------------------------------------------------
02-JUNE-2021 21:10
Finished the touch panel implementation and the scope seems to read the coordinates, but does not react to them. It looks like more FPGA functionality 
needs to be implemented to get it to work.

The screen shows more of the actual scope screen after a "touch event", so there is progress.

