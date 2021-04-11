What I did to build the image:

1) I setup a virtualbox with linux mint 20.

2) Followed the instruction here: "https://hackaday.io/project/171402/instructions"  down to building the sunxi tools. (Used  sunxi-fel version to see what the scope returned)

3) After that I used the instructions here: "https://www.thirtythreeforty.net/posts/2020/01/mastering-embedded-linux-part-3-buildroot/"  to setup buildroot (used the latest date 2021.2) and tested it with the raspberry pi config

4) Then I followed te instructions here: "https://unframework.com/2020/05/27/setting-up-embedded-linux-on-lichee-pi-nano/" to build the linux with uart0 for the lichee nano
   Had to resolve some errors due to missing packages. "sudo apt-get install swig python-dev libssl-dev" Also needed to change the defconfig to overcome legacy options.
   Then to get uart1 in the picture I had to make modifications to some .dts and .dtsi files. The latter is found in several places and concerns these suniv-f1c100s.dtsi or suniv.dtsi. Not sure editing which did the trick.

5) I moved the files from unframework into the buildroot directory and modified them to work from there.

The files I changed are in this directory:
  Place the board/licheepi_nano directory in the buildroot board directory (only the licheepi_nano directory ofcoarse)
  Place the configs/licheepi_nano_defconfig in the buildroot configs directory (only the file)
  Search for the other two files and replace them everywhere you find them. ( suniv-f1c100s.dtsi of suniv.dtsi)

Type in a terminal opened in the buildroot directory
  make licheepi_nano_defconfig
  make

This will make the needed image for the sd card.

With "sudo dd if=~/buildroot/output/images/sdcard.img of=/dev/sdb" I wrote it to my card and placed it in the scope.

Used a breakout board to connect the usb serial and putty on the linux mint machine et voila.

See "readme.tx" and "location of uart1 connections.jpg" in the "images/lichee_nano_uboot_uart0_linux_uart1" directory for connection of an USB to serial adapter


I had to change four files in the u-boot archive to get the image to only use uart1:

1) /uboot-nano-v2018.01/arch/arm/mach-sunxi/board.c
Added:
#elif CONFIG_CONS_INDEX == 2 && defined(CONFIG_MACH_SUNIV)
   sunxi_gpio_set_cfgpin(SUNXI_GPA(2), SUNIV_GPA_UART1);
   sunxi_gpio_set_cfgpin(SUNXI_GPA(3), SUNIV_GPA_UART1);
   sunxi_gpio_set_pull(SUNXI_GPA(3), SUNXI_GPIO_PULL_UP);

2) /uboot-nano-v2018.01/include/asm/arch-sunxi/gpio.h
Added:
#define SUNIV_GPA_UART1      5

3) /uboot-nano-v2018.01/include/configs/sunxi-common.h
Added:
#elif CONFIG_CONS_INDEX == 2 && defined(CONFIG_MACH_SUNIV)
#define OF_STDOUT_PATH      "/soc@01c00000/serial@01c25400:115200"

4) /uboot-nano-v2018.01/configs/lichee_nano_defconfig
Added:
CONFIG_CONS_INDEX=2
