#ifndef ARMTHREAD_H
#define ARMTHREAD_H

//----------------------------------------------------------------------------------------------------------------------------------
// Arm emulator window thread functions
//----------------------------------------------------------------------------------------------------------------------------------

int startarmemulator(void);
void stoparmemulator(void);

void *armemulatorthread(void *arg);




#endif /* ARMTHREAD_H */

