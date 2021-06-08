This is a simple project to convert export data from saleae logic 2 to data that is written and read by the fpga of the FNIRSI 1013D scope.

With saleae a capture of the "I2C" bus between the fpga and the special chip can be made. The file names are hard coded.

Included is a trace made by e_Johny. It holds the startup data into the main loop without any touch. The original trace can be found on the eevblog forum:
https://www.eevblog.com/forum/testgear/fnirsi-1013d-100mhz-tablet-oscilloscope/msg3583666/#msg3583666

The program uses some filtering to get the data out, because it does not comply with the I2C specs.

It also decodes the data and checks the checksums.
