//----------------------------------------------------------------------------------------------------------------------------------

#ifndef ARMV5TL_THUMB_H
#define ARMV5TL_THUMB_H

//----------------------------------------------------------------------------------------------------------------------------------

#include "armv5tl.h"

//----------------------------------------------------------------------------------------------------------------------------------
//Additional processing opcodes to allow for different flag handling

#define ARM_OPCODE_THUMB_MOV2       32

//----------------------------------------------------------------------------------------------------------------------------------

void ArmV5tlHandleThumb(PARMV5TL_CORE core);


void ArmV5tlThumbShiftImmediate(PARMV5TL_CORE core);
void ArmV5tlThumbShiftRegister(PARMV5TL_CORE core);
void ArmV5tlThumbShift(PARMV5TL_CORE core, u_int32_t type, u_int32_t sa, u_int32_t vm);


void ArmV5tlThumbDP0(PARMV5TL_CORE core);
void ArmV5tlThumbDP1(PARMV5TL_CORE core);


void ArmV5tlThumbDP(PARMV5TL_CORE core, u_int32_t type, u_int32_t  rd, u_int32_t vn, u_int32_t vm);

#endif /* ARMV5TL_THUMB_H */

