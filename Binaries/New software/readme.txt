The new approach is to run everything from the SD card

No need to open up the scope anymore.

!!! BE AWARE. I TAKE NO RESPONSIBILITY IF ANYTHING GOES WRONG !!!

I have tested this on two scopes.

For this the file fnirsi_1013d.bin is needed.

Connect the scope to the computer and start the USB connection
When the file manager window opens, close it
Open a terminal window (ctrl + alt + t)

Find out to which device the disk is connected

Type the following commands to unmount the partition

  sudo umount /dev/sd?1

  sudo dd if=fnirsi_1013d.bin of=/dev/sd? bs=1024 seek=8
  
Turn of the scope and on power on it should start the new software

To get rid of it do the following

Connect the scope to the computer and start the USB connection
When the file manager window opens, close it
Open a terminal window (ctrl + alt + t)

Find out to which device the disk is connected

Type the following commands to unmount the partition

  sudo umount /dev/sd?1

  sudo dd if=/dev/zero of=/dev/sd? bs=1024 seek=8 count=1
  
Turn of the scope and on power on it starts the original code.

-----------------------------------------------------------------------------------------------------------------------------------------------------
OLD STUFF

The binary of the semi reversed engineered FNIRSI-1013D scope software can be found here.

To play with it one needs a micro SD card of which the size does not matter. It is only 9KB that needs to be written on it.

One also needs a machine with linux to make it work with the given commands.

This concerns the bootloader that makes the scope ready for loading the actual program with the sunxi-fel utility.


!!!!!!Make sure to check the /dev device where your SD card resides!!!!!!!

To write it to the SD card use the following command:

   sudo dd if=fnirsi_1013d_startup_with_fel.bin of=/dev/sdc bs=1024 seek=8
   
!!!!!!Make sure to check the /dev device where your SD card resides!!!!!!!


Insert the newly written SD card into the scope. On power up it will show the FNIRSI-1013D startup bitmap and go into fel mode.


This can be verified on the linux machine with “lsusb”. The list should show the following line, where the bus and device id can be different.

   Bus 001 Device 026: ID 1f3a:efe8 Onda (unverified) V972 tablet in flashing mode


At this point the actual program can be loaded to the device.


Use the following command for this:

   sudo ./sunxi-fel -p write 0x7FFFFFE0 fnirsi_1013d_scope.bin exe 0x80000000


The sunxi-fel utility is also in this directory and is compiled from the sources with flash support. Feel free to get them from the net and build your own utility.
