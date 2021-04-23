The easiest way to upload these files to the scope is with the sunxi-fel tool. One can build it ore use the one added here.
Make sure to get the sources that have the SPI flash in them.

See: https://github.com/pecostm32/FNIRSI-1013D-Hack/tree/main/Linux/images/fel_boot

First thing to do is create a SD card with the FEL boot image. It can be found on the internet, but also added here.

Change /dev/sdb to where your SD card is mounted
sudo dd if=fel-sdboot.sunxi of=/dev/sdb bs=1024 seek=8

The use the following to write the new firmware to the flash
sudo ./sunxi-fel -p spiflash-write 0 W25Q32_scope_tp_conf_not_written.bin
