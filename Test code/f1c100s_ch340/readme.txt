This project is simple code to interface with the FPGA via USB.
The code emulates a CH340 device and allows for executing 7 commands.
The commands can be typed in a terminal program and the scope returns the result of the command.

The commands are:
1) WC=xxx    (write command and value ranges from 0 to 255. This sends a command to the FPGA)
2) WB=xxx    (write byte, value 0 - 255. This command sends data to the FPGA)
3) WS=xxxx   (write short, value 0 - 65535)
4) WI=xxxxx  (write int, value 0 - 4294967295)
5) RB        (read byte. Reads a value from the FPGA)
6) RS        (read short)
7) RI        (read int)

It is very crude, but allows for testing while developing FPGA programming.

To have the code run on the scope it can be loaded to the SD card. For this it needs the boot loader project "f1c100s_ch340_sd_package"

Build the bootloader project first and it will copy its binary to the dist folder of this project. Then build this project and load the result to the SD card.

==================
Load package onto SD card

Check if /dev/sdc is the correct device for the scope
==================

sudo umount /dev/sdc1

sudo dd if=f1c100s_ch340_sd_package.bin of=/dev/sdc bs=1024 seek=8


===================
Remove program from SD card
===================

sudo umount /dev/sdc1

sudo dd if=/dev/zero of=/dev/sdc bs=1024 seek=8 count=1


===================
The code can also be loaded with sunxi-fel

Check if scope is active
==================

sudo ./sunxi-fel version

===================
Load to RAM
==================

sudo ./sunxi-fel -p write 0x7FFFFFE0 f1c100s_ch340.bin exe 0x80000000
 


