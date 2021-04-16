# FNIRSI-1013D-Hack
Resources gathered for reverse engineering the FNIRSI-1013D scope

As part of what is on EEVBLOG, resources for the reverse engineering of the FNIRSI-1013D scope are put together in a single repository.

As it is an ongoing process more and more data will be added over time.

The touch panel problem that lead to this hack has been resolved. On the forum there is a arduino sketch that can be used to re configure the touch panel and in this repository there is a new firmware file for the scope. This is for the scope version with the W25Q32 flash chip (32Mbit). This is also the scope that has the problems with the reversed coordinates when the touch panel is replaced with one that uses a GOODIX GT915(7) touch panel controller.

There are two other repositories with code for the STM32F103 based bluepill boards for reading and writting the touch panel configuration, but when used in combination with Windows they seem not to do what is wanted.

The hack continues with the quest on revealing the secrets of the FPGA that is used in the scope. For now it is solely based on figuring out what the software does with it. If this does not yield what is needed a reverse engineering of the FPGA might be needed, but is far more difficult.
