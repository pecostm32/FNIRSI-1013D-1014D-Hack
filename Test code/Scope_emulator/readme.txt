Far from finished and only here for safe keeping.

The arm core is running but functions are missing and some might have errors.

It needs implementation of all the internal peripherals of the F1C100s.

There is no connection with the emulator or scope screen yet.

Most of the thumb instructions are implemented. So far only push and pop are tested.

Test case is the boot loader of the scope. For now it runs to address 0x4E4 where it encounters a not yet implemented strd instruction, so this one is next on the list.

Next step after that is to implement some of the F1C100s peripherals, and see how far the program will run.

The moment it hits the writing to the display of the scope I have to make the connection to that part of the emulator.
