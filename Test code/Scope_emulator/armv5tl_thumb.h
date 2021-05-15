//----------------------------------------------------------------------------------------------------------------------------------

#ifndef ARMV5TL_THUMB_H
#define ARMV5TL_THUMB_H

//----------------------------------------------------------------------------------------------------------------------------------

#include "armv5tl.h"

//----------------------------------------------------------------------------------------------------------------------------------
//Additional processing opcodes to allow for different flag handling

#define ARM_THUMB_TYPE_MASK           0x0000000F
#define ARM_OPCODE_THUMB_CLR_CV       0x00000010
#define ARM_OPCODE_THUMB_NO_FLAGS     0x00000020
#define ARM_OPCODE_THUMB_NEG          0x00000100
#define ARM_OPCODE_THUMB_MUL          0x00000200

//----------------------------------------------------------------------------------------------------------------------------------

#define ARM_THUMB_SIZE_MASK           0x00000003

#define ARM_THUMB_SIZE_BYTE           0x00000002
#define ARM_THUMB_SIZE_SHORT          0x00000001
#define ARM_THUMB_SIZE_WORD           0x00000000

#define ARM_THUMB_LOAD_FLAG           0x00010000

#define ARM_THUMB_SIGN_EXTEND         0x00100000

//----------------------------------------------------------------------------------------------------------------------------------

void ArmV5tlHandleThumb(PARMV5TL_CORE core);


void ArmV5tlThumbShiftImmediate(PARMV5TL_CORE core);
void ArmV5tlThumbShiftRegister(PARMV5TL_CORE core);
void ArmV5tlThumbShift(PARMV5TL_CORE core, u_int32_t type, u_int32_t sa, u_int32_t vm);


void ArmV5tlThumbDP0(PARMV5TL_CORE core);
void ArmV5tlThumbDP1(PARMV5TL_CORE core);
void ArmV5tlThumbDP2(PARMV5TL_CORE core);
void ArmV5tlThumbDP2S(PARMV5TL_CORE core);
void ArmV5tlThumbDP(PARMV5TL_CORE core, u_int32_t type, u_int32_t rd, u_int32_t vn, u_int32_t vm);

void ArmV5tlThumbLS2I(PARMV5TL_CORE core);
void ArmV5tlThumbLS2R(PARMV5TL_CORE core);
void ArmV5tlThumbLS3(PARMV5TL_CORE core);
void ArmV5tlThumbLS4(PARMV5TL_CORE core);

void ArmV5tlThumbLS(PARMV5TL_CORE core, u_int32_t type, u_int32_t rd, u_int32_t address);

void ArmV5tlThumbLSMIA(PARMV5TL_CORE core);

void ArmV5tlThumbPOP(PARMV5TL_CORE core);
void ArmV5tlThumbPUSH(PARMV5TL_CORE core);

void ArmV5tlThumbBranch2(PARMV5TL_CORE core);
void ArmV5tlThumbBranch6(PARMV5TL_CORE core);
void ArmV5tlThumbBranch7(PARMV5TL_CORE core);


#endif /* ARMV5TL_THUMB_H */

