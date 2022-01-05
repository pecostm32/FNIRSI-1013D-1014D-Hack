#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=arm-none-eabi-gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/ccu_control.o \
	${OBJECTDIR}/ch340_class.o \
	${OBJECTDIR}/commands.o \
	${OBJECTDIR}/f1c100s_ch340.o \
	${OBJECTDIR}/fpga_control.o \
	${OBJECTDIR}/interrupt.o \
	${OBJECTDIR}/memcmp.o \
	${OBJECTDIR}/memcpy.o \
	${OBJECTDIR}/memmove.o \
	${OBJECTDIR}/memset.o \
	${OBJECTDIR}/start.o \
	${OBJECTDIR}/timer.o \
	${OBJECTDIR}/usb_interface.o


# C Compiler Flags
CFLAGS=-Wall -Wno-write-strings -Wno-char-subscripts -fno-stack-protector -DNO_STDLIB=1 -O3 -mcpu=cortex-m3 -mthumb

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/f1c100s_ch340

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/f1c100s_ch340: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	arm-none-eabi-gcc -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/f1c100s_ch340 ${OBJECTFILES} ${LDLIBSOPTIONS} -T./stm32f103-64k.ld -nostdlib

${OBJECTDIR}/ccu_control.o: ccu_control.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ccu_control.o ccu_control.c

${OBJECTDIR}/ch340_class.o: ch340_class.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ch340_class.o ch340_class.c

${OBJECTDIR}/commands.o: commands.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands.o commands.c

${OBJECTDIR}/f1c100s_ch340.o: f1c100s_ch340.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/f1c100s_ch340.o f1c100s_ch340.c

${OBJECTDIR}/fpga_control.o: fpga_control.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fpga_control.o fpga_control.c

${OBJECTDIR}/interrupt.o: interrupt.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/interrupt.o interrupt.c

${OBJECTDIR}/memcmp.o: memcmp.s
	${MKDIR} -p ${OBJECTDIR}
	$(AS) $(ASFLAGS) -o ${OBJECTDIR}/memcmp.o memcmp.s

${OBJECTDIR}/memcpy.o: memcpy.s
	${MKDIR} -p ${OBJECTDIR}
	$(AS) $(ASFLAGS) -o ${OBJECTDIR}/memcpy.o memcpy.s

${OBJECTDIR}/memmove.o: memmove.s
	${MKDIR} -p ${OBJECTDIR}
	$(AS) $(ASFLAGS) -o ${OBJECTDIR}/memmove.o memmove.s

${OBJECTDIR}/memset.o: memset.s
	${MKDIR} -p ${OBJECTDIR}
	$(AS) $(ASFLAGS) -o ${OBJECTDIR}/memset.o memset.s

${OBJECTDIR}/start.o: start.s
	${MKDIR} -p ${OBJECTDIR}
	$(AS) $(ASFLAGS) -o ${OBJECTDIR}/start.o start.s

${OBJECTDIR}/timer.o: timer.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/timer.o timer.c

${OBJECTDIR}/usb_interface.o: usb_interface.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/usb_interface.o usb_interface.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
