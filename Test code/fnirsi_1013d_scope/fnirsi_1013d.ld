MEMORY
{
	ram  : org = 0x7FFFFFE0, len = 32M
}

SECTIONS
{
  . = ORIGIN(ram);
  .text : 
  {
    build/Debug/GNU_ARM-Linux/start.o (.text)
    *(.text);
  } >ram

  .data :
  {
    *(.data);
    *(.rodata);
  } >ram

  BSS_START = .;
  .bss : 
  {
    *(.bss);
  } >ram
  BSS_END = .;

	__program_size = SIZEOF(.text) + SIZEOF(.data);
}