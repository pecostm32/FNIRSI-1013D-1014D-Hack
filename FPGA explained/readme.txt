The emulator provided a good insight in what the scope does.

Most of the commands have been identified of what they do, and are noted down in the FPGA explained.txt file.

The sequence of commands are being traced with the emulator.
The first file (Startup and signal data read sequence.txt) shows the startup and signal reading with both channels enabled and a time base set to 20uS/div.

Study of the sequences revealed more secrets of the FPGA. For the time base settings from 100mS up the scope stops communication with the special IC
and probably uses the timer interrupt to start a read of the signal data. The sequence is the same for all the higher time base settings.

For the lower ranges there are some differences in the sequences. There are three types of sequence. This is described in the files.

Would be interesting to see if the special IC is really needed.

Real life tests need to verify the actual working.
