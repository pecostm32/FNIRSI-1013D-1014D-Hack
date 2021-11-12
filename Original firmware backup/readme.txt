Here is the tool plus the steps to make it work.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!                                                 !!
!! I take no responsibility if anything goes wrong !!
!!                                                 !!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

Steps for making the FNIRSI-1013D firmware backup on a Linux machine:

1)  Connect the scope to the computer via USB.
2)  Turn on the scope and start the USB connection via the main menu option.
3)  Wait until the file manager window opens. (Only if auto mount is working properly)
4)  Close the file manager window.
5)  Open a terminal window (ctrl + alt + t) and type the "lsblk" command (!do not use the quotes!) and check which device the scope is on. (~8GB disk)
6)  Copy the files from the card to have a backup on your computer.
7)  Un-mount the partition. ("sudo umount /dev/sdc1" in my case)
8)  Just to be more safe make a backup with dd. ("sudo dd bs=4M if=/dev/sdc of=sd_card_backup.bin" again in my case)
9)  Open gparted and check if the device is properly formated. (Use right mouse and information to see the sector info)
10) If not delete the partition and make a new one leaving 1M free at the start. Format is fat32.
11) When the partition remounts after the previous step un-mount it again.
12) Use dd to place the backup package on the SD card. ("sudo dd if=fnirsi_1013d_fwb.bin of=/dev/sdc bs=1024 seek=8")
13) This will re-mount the partition. Un-mount the partition again. ("sudo umount /dev/sdc1" in my case)
14) Turn of the scope and turn it back on. This will start the backup process.
15) Wait until it is done and the scope is mounted again. File manager window should open after a while.
16) Copy the three files to the computer. (FNIRSI_1013D_full_flash_backup.bin, FNIRSI_1013D_tp_config.bin, FWB_FSI_1013.bin)
17) Turn off the scope and turn it back on. It should start normally.


When the scope showed the "!! special touch panel detected !!" message please upload the "FNIRSI_1013D_tp_config.bin" file to the FNIRSI-1013D thread on EEVBLOG.
(https://www.eevblog.com/forum/testgear/fnirsi-1013d-100mhz-tablet-oscilloscope/msg3807689/#lastPost)

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!                                                                                                              !!
!! If your scope uses a smaller SD card be warned that this is not tested yet. Only 8GB cards have been tested. !!
!!                                                                                                              !!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

The firmware backup made (FWB_FSI_1013.bin) contains both the startup image and the actual scope program plus the settings.
It also has the check values the scope needs for restoring the firmware.

This is not yet tested as such. It needs renaming to FNI_1013.bin and be written on the scopes SD card.
