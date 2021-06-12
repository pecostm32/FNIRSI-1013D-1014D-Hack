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
