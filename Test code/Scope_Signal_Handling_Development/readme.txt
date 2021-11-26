This simulator can run the code written for the scope on the PC. It uses the actual C code and not the arm compiled code like the emulator.

It is using stub functions for the FPGA implementation and the SD card interface.

To let FatFs work the stub functions for it need a file on disk named "scope_sd_card.img". This has to be an image file of the original SD card.

Added USB connect functionality. Used shell command called with system(). User is asked for root password. Not the most elegant solution
but it works. Allows for accessing the SD card image file via the file manager.

More functionality needs to be added to fully support the actual scope code. Think of virtual analog inputs.
