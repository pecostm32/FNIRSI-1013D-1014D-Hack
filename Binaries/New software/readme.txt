The binary of the semi reversed engineered FNIRSI-1013D scope software can be found here.

To play with it one needs a micro SD card of which the size does not matter. It is only 9KB that needs to be written on it.

One also needs a machine with linux to make it work with the given commands.

This concerns the bootloader that makes the scope ready for loading the actual program with the sunxi-fel utility.


To write it to the SD card use the following command:

   sudo dd if=fnirsi_1013d_startup_with_fel.bin of=/dev/sdc bs=1024 seek=8


Insert the newly written SD card into the scope. On power up it will show the FNIRSI-1013D startup bitmap and go into fel mode.


This can be verified on the linux machine with “lsusb”. The list should show the following line, where the bus and device id can be different.

   Bus 001 Device 026: ID 1f3a:efe8 Onda (unverified) V972 tablet in flashing mode


At this point the actual program can be loaded to the device.


Use the following command for this:

   sudo ./sunxi-fel -p write 0x7FFFFFE0 fnirsi_1013d_scope.bin exe 0x80000000


The sunxi-fel utility is also in this directory and is compiled from the sources with flash support. Feel free to get them from the net and build your own utility.
