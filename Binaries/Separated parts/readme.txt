The old and the new binary image of the flash are different. The structure is the same, but the block sizes differ.

The 1st 32 bytes of each block are its header.
In the header, at offset 0x10, there is the size of the block (including header).

Load Address in the MCU
SPL (second program loader):  0x00000000  (32KB internal SRAM)
The two executables:          0x80000000  (32MB internal dram)

The offsets and sizes for the blocks are:

(Old version 16Mbit flash)
Offset:   Size:
00000000  00003400 - SPL (Second program loader. Loads the bitmap on the screen and starts the 2nd executable)
00006000  00007400 - 1st executable (FEL program or just starts FEL present in the MCU)
00013000  0000E600 - bitmap
00027000  00193200 - 2nd executable (main scope app)


(New version 32Mbit flash)
Offset:   Size:
00000000  00003400 - SPL (Second program loader. Loads the bitmap on the screen and starts the 2nd executable)
00006000  00007A00 - 1st executable (FEL program or just starts FEL present in the MCU)
00013000  0000E600 - bitmap
00027000  00193A00 - 2nd executable (main scope app)

The research here is done on the new version
