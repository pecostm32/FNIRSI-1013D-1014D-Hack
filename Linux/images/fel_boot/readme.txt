This image is an easy way to put an Allwinner chip in FEL mode

write the image to a SD card and stick it in your device. This will boot it into FEL mode and allows flash programming via USB

Change /dev/sdb to where your SD card is mounted
sudo dd if=fel-sdboot.sunxi of=/dev/sdb bs=1024 seek=8

The sunxi tools are needed for writing the flash

To be able to write to the spi flash get this version of the tools

git clone https://github.com/Icenowy/sunxi-tools.git -b f1c100s-spiflash

do:
sudo make install

and the tools are build and available from every location

Boot your device with the sd card with the FEL image and make sure the device shows up in your system

1f3a:efe8 Onda (unverified) V972 tablet in flashing mode

sudo sunxi-fel version

tells which device it is.

sudo sunxi-fel spiflash-info

will show the flash device information.

sudo sunxi-fel spiflash-read 0 4194304 test.bin

will read the flash (if it is 4194304 bytes long) from address 0 to the end and save it 

sudo sunxi-fel -p spiflash-write 0 test.bin

will write the flash starting from address 0 to the end of test.bin file.
