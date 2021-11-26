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
CC=gcc
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
	${OBJECTDIR}/_ext/4a4fb115/display_lib.o \
	${OBJECTDIR}/_ext/4a4fb115/ff.o \
	${OBJECTDIR}/_ext/4a4fb115/ffunicode.o \
	${OBJECTDIR}/_ext/4a4fb115/font_0.o \
	${OBJECTDIR}/_ext/4a4fb115/font_2.o \
	${OBJECTDIR}/_ext/4a4fb115/font_3.o \
	${OBJECTDIR}/_ext/4a4fb115/font_4.o \
	${OBJECTDIR}/_ext/4a4fb115/font_5.o \
	${OBJECTDIR}/_ext/4a4fb115/icons.o \
	${OBJECTDIR}/_ext/4a4fb115/scope_functions.o \
	${OBJECTDIR}/_ext/4a4fb115/sin_cos_math.o \
	${OBJECTDIR}/_ext/4a4fb115/statemachine.o \
	${OBJECTDIR}/_ext/4a4fb115/variables.o \
	${OBJECTDIR}/Scope_Processing.o \
	${OBJECTDIR}/Scope_Signal_Handling_Development.o \
	${OBJECTDIR}/mousehandling.o \
	${OBJECTDIR}/stub_functions.o \
	${OBJECTDIR}/touchpanel.o \
	${OBJECTDIR}/xlibfunctions.o


# C Compiler Flags
CFLAGS=

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/scope_signal_handling_development

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/scope_signal_handling_development: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/scope_signal_handling_development ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/4a4fb115/display_lib.o: ../../F1C100s/fnirsi_1013d_scope/display_lib.c
	${MKDIR} -p ${OBJECTDIR}/_ext/4a4fb115
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4a4fb115/display_lib.o ../../F1C100s/fnirsi_1013d_scope/display_lib.c

${OBJECTDIR}/_ext/4a4fb115/ff.o: ../../F1C100s/fnirsi_1013d_scope/ff.c
	${MKDIR} -p ${OBJECTDIR}/_ext/4a4fb115
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4a4fb115/ff.o ../../F1C100s/fnirsi_1013d_scope/ff.c

${OBJECTDIR}/_ext/4a4fb115/ffunicode.o: ../../F1C100s/fnirsi_1013d_scope/ffunicode.c
	${MKDIR} -p ${OBJECTDIR}/_ext/4a4fb115
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4a4fb115/ffunicode.o ../../F1C100s/fnirsi_1013d_scope/ffunicode.c

${OBJECTDIR}/_ext/4a4fb115/font_0.o: ../../F1C100s/fnirsi_1013d_scope/font_0.c
	${MKDIR} -p ${OBJECTDIR}/_ext/4a4fb115
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4a4fb115/font_0.o ../../F1C100s/fnirsi_1013d_scope/font_0.c

${OBJECTDIR}/_ext/4a4fb115/font_2.o: ../../F1C100s/fnirsi_1013d_scope/font_2.c
	${MKDIR} -p ${OBJECTDIR}/_ext/4a4fb115
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4a4fb115/font_2.o ../../F1C100s/fnirsi_1013d_scope/font_2.c

${OBJECTDIR}/_ext/4a4fb115/font_3.o: ../../F1C100s/fnirsi_1013d_scope/font_3.c
	${MKDIR} -p ${OBJECTDIR}/_ext/4a4fb115
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4a4fb115/font_3.o ../../F1C100s/fnirsi_1013d_scope/font_3.c

${OBJECTDIR}/_ext/4a4fb115/font_4.o: ../../F1C100s/fnirsi_1013d_scope/font_4.c
	${MKDIR} -p ${OBJECTDIR}/_ext/4a4fb115
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4a4fb115/font_4.o ../../F1C100s/fnirsi_1013d_scope/font_4.c

${OBJECTDIR}/_ext/4a4fb115/font_5.o: ../../F1C100s/fnirsi_1013d_scope/font_5.c
	${MKDIR} -p ${OBJECTDIR}/_ext/4a4fb115
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4a4fb115/font_5.o ../../F1C100s/fnirsi_1013d_scope/font_5.c

${OBJECTDIR}/_ext/4a4fb115/icons.o: ../../F1C100s/fnirsi_1013d_scope/icons.c
	${MKDIR} -p ${OBJECTDIR}/_ext/4a4fb115
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4a4fb115/icons.o ../../F1C100s/fnirsi_1013d_scope/icons.c

${OBJECTDIR}/_ext/4a4fb115/scope_functions.o: ../../F1C100s/fnirsi_1013d_scope/scope_functions.c
	${MKDIR} -p ${OBJECTDIR}/_ext/4a4fb115
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4a4fb115/scope_functions.o ../../F1C100s/fnirsi_1013d_scope/scope_functions.c

${OBJECTDIR}/_ext/4a4fb115/sin_cos_math.o: ../../F1C100s/fnirsi_1013d_scope/sin_cos_math.c
	${MKDIR} -p ${OBJECTDIR}/_ext/4a4fb115
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4a4fb115/sin_cos_math.o ../../F1C100s/fnirsi_1013d_scope/sin_cos_math.c

${OBJECTDIR}/_ext/4a4fb115/statemachine.o: ../../F1C100s/fnirsi_1013d_scope/statemachine.c
	${MKDIR} -p ${OBJECTDIR}/_ext/4a4fb115
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4a4fb115/statemachine.o ../../F1C100s/fnirsi_1013d_scope/statemachine.c

${OBJECTDIR}/_ext/4a4fb115/variables.o: ../../F1C100s/fnirsi_1013d_scope/variables.c
	${MKDIR} -p ${OBJECTDIR}/_ext/4a4fb115
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4a4fb115/variables.o ../../F1C100s/fnirsi_1013d_scope/variables.c

${OBJECTDIR}/Scope_Processing.o: Scope_Processing.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Scope_Processing.o Scope_Processing.c

${OBJECTDIR}/Scope_Signal_Handling_Development.o: Scope_Signal_Handling_Development.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Scope_Signal_Handling_Development.o Scope_Signal_Handling_Development.c

${OBJECTDIR}/mousehandling.o: mousehandling.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mousehandling.o mousehandling.c

${OBJECTDIR}/stub_functions.o: stub_functions.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/stub_functions.o stub_functions.c

${OBJECTDIR}/touchpanel.o: touchpanel.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/touchpanel.o touchpanel.c

${OBJECTDIR}/xlibfunctions.o: xlibfunctions.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/xlibfunctions.o xlibfunctions.c

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
