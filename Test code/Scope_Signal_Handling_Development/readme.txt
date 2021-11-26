This simulator can run the code written for the scope on the PC. It uses the actual C code and not the arm compiled code like the emulator.

It is using stub functions for the FPGA implementation and the SD card interface.

To let FatFs work the stub functions for it need a file on disk named "scope_sd_card.img". This has to be an image file of the original SD card.

More functionality needs to be added to fully support the actual scope code. Think of USB emulation, or virtual analog inputs.
