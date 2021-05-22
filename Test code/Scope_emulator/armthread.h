#ifndef ARMTHREAD_H
#define ARMTHREAD_H

//----------------------------------------------------------------------------------------------------------------------------------
// Arm emulator window thread functions
//----------------------------------------------------------------------------------------------------------------------------------

int startarmemulator(void);
void stoparmemulator(void);

void *armemulatorthread(void *arg);

//Function to call for sending the emulator window a message indicating the core executed another instruction
void updateemulatormessage(void);



#endif /* ARMTHREAD_H */

