Read from flash
  sudo ./sunxi-fel -p spiflash-read 0 2097152 w25q16_new_scope.bin
  
Write to flash
  sudo ./sunxi-fel -p spiflash-write 0 w25q16_new_scope.bin

Make SD card (make sure your card is at /dev/sdc !!!!)
sudo dd if=fel-sdboot.sunxi of=/dev/sdc bs=1024 seek=8

  
