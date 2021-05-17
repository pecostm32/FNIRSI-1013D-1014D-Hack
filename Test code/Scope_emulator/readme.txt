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


The moment it hits the writing to the display of the scope I have to make the connection to that part of the emulator.
