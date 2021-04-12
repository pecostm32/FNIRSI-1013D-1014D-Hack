This image is an easy way to put an Allwinner chip in FEL mode

write the image to a SD card and stick it in your device. This will boot it into FEL mode and allows flash programming via USB

Change /dev/sdb to where your SD card is mounted
sudo dd if=fel-sdboot.sunxi of=/dev/sdb

The sunxi tools are needed for writing the flash
