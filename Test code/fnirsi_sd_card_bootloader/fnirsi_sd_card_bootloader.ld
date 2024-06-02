MEMORY
{
	sram  : org = 0x00000000, len = 32K
  dram  : org = 0x81C00000, len =  4M
}

SECTIONS
{
  . = ORIGIN(sram);
  .text : 
  {
    build/Debug/GNU_ARM-Linux/start.o (.text)
    *(.text);
    *(.data);
    *(.rodata);
  } >sram

  .dmem :
  {
    *(.dmem);
  } >dram

	__bootloader_size = SIZEOF(.text);
}