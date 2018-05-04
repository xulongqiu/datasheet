#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Platform_None.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Platform_None.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../core/vdm/DisplayPort/dp.c ../../core/vdm/DisplayPort/dp_system_stubs.c ../../core/vdm/vdm_callbacks.c ../../core/vdm/bitfield_translators.c ../../core/vdm/vdm.c ../../core/vdm/vdm_config.c ../../core/Log.c ../../core/TypeC.c ../../core/fusb30X.c ../../core/PDPolicy.c ../../core/PDProtocol.c ../../core/core.c ../../core/AlternateModes.c ../platform.c ../NONE_Main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/403107043/dp.o ${OBJECTDIR}/_ext/403107043/dp_system_stubs.o ${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o ${OBJECTDIR}/_ext/1644920145/bitfield_translators.o ${OBJECTDIR}/_ext/1644920145/vdm.o ${OBJECTDIR}/_ext/1644920145/vdm_config.o ${OBJECTDIR}/_ext/1853363519/Log.o ${OBJECTDIR}/_ext/1853363519/TypeC.o ${OBJECTDIR}/_ext/1853363519/fusb30X.o ${OBJECTDIR}/_ext/1853363519/PDPolicy.o ${OBJECTDIR}/_ext/1853363519/PDProtocol.o ${OBJECTDIR}/_ext/1853363519/core.o ${OBJECTDIR}/_ext/1853363519/AlternateModes.o ${OBJECTDIR}/_ext/1472/platform.o ${OBJECTDIR}/_ext/1472/NONE_Main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/403107043/dp.o.d ${OBJECTDIR}/_ext/403107043/dp_system_stubs.o.d ${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o.d ${OBJECTDIR}/_ext/1644920145/bitfield_translators.o.d ${OBJECTDIR}/_ext/1644920145/vdm.o.d ${OBJECTDIR}/_ext/1644920145/vdm_config.o.d ${OBJECTDIR}/_ext/1853363519/Log.o.d ${OBJECTDIR}/_ext/1853363519/TypeC.o.d ${OBJECTDIR}/_ext/1853363519/fusb30X.o.d ${OBJECTDIR}/_ext/1853363519/PDPolicy.o.d ${OBJECTDIR}/_ext/1853363519/PDProtocol.o.d ${OBJECTDIR}/_ext/1853363519/core.o.d ${OBJECTDIR}/_ext/1853363519/AlternateModes.o.d ${OBJECTDIR}/_ext/1472/platform.o.d ${OBJECTDIR}/_ext/1472/NONE_Main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/403107043/dp.o ${OBJECTDIR}/_ext/403107043/dp_system_stubs.o ${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o ${OBJECTDIR}/_ext/1644920145/bitfield_translators.o ${OBJECTDIR}/_ext/1644920145/vdm.o ${OBJECTDIR}/_ext/1644920145/vdm_config.o ${OBJECTDIR}/_ext/1853363519/Log.o ${OBJECTDIR}/_ext/1853363519/TypeC.o ${OBJECTDIR}/_ext/1853363519/fusb30X.o ${OBJECTDIR}/_ext/1853363519/PDPolicy.o ${OBJECTDIR}/_ext/1853363519/PDProtocol.o ${OBJECTDIR}/_ext/1853363519/core.o ${OBJECTDIR}/_ext/1853363519/AlternateModes.o ${OBJECTDIR}/_ext/1472/platform.o ${OBJECTDIR}/_ext/1472/NONE_Main.o

# Source Files
SOURCEFILES=../../core/vdm/DisplayPort/dp.c ../../core/vdm/DisplayPort/dp_system_stubs.c ../../core/vdm/vdm_callbacks.c ../../core/vdm/bitfield_translators.c ../../core/vdm/vdm.c ../../core/vdm/vdm_config.c ../../core/Log.c ../../core/TypeC.c ../../core/fusb30X.c ../../core/PDPolicy.c ../../core/PDProtocol.c ../../core/core.c ../../core/AlternateModes.c ../platform.c ../NONE_Main.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Platform_None.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX250F128B
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/403107043/dp.o: ../../core/vdm/DisplayPort/dp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/403107043" 
	@${RM} ${OBJECTDIR}/_ext/403107043/dp.o.d 
	@${RM} ${OBJECTDIR}/_ext/403107043/dp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/403107043/dp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/403107043/dp.o.d" -o ${OBJECTDIR}/_ext/403107043/dp.o ../../core/vdm/DisplayPort/dp.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/403107043/dp_system_stubs.o: ../../core/vdm/DisplayPort/dp_system_stubs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/403107043" 
	@${RM} ${OBJECTDIR}/_ext/403107043/dp_system_stubs.o.d 
	@${RM} ${OBJECTDIR}/_ext/403107043/dp_system_stubs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/403107043/dp_system_stubs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/403107043/dp_system_stubs.o.d" -o ${OBJECTDIR}/_ext/403107043/dp_system_stubs.o ../../core/vdm/DisplayPort/dp_system_stubs.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o: ../../core/vdm/vdm_callbacks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1644920145" 
	@${RM} ${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o.d" -o ${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o ../../core/vdm/vdm_callbacks.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1644920145/bitfield_translators.o: ../../core/vdm/bitfield_translators.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1644920145" 
	@${RM} ${OBJECTDIR}/_ext/1644920145/bitfield_translators.o.d 
	@${RM} ${OBJECTDIR}/_ext/1644920145/bitfield_translators.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1644920145/bitfield_translators.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/1644920145/bitfield_translators.o.d" -o ${OBJECTDIR}/_ext/1644920145/bitfield_translators.o ../../core/vdm/bitfield_translators.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1644920145/vdm.o: ../../core/vdm/vdm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1644920145" 
	@${RM} ${OBJECTDIR}/_ext/1644920145/vdm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1644920145/vdm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1644920145/vdm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/1644920145/vdm.o.d" -o ${OBJECTDIR}/_ext/1644920145/vdm.o ../../core/vdm/vdm.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1644920145/vdm_config.o: ../../core/vdm/vdm_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1644920145" 
	@${RM} ${OBJECTDIR}/_ext/1644920145/vdm_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1644920145/vdm_config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1644920145/vdm_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/1644920145/vdm_config.o.d" -o ${OBJECTDIR}/_ext/1644920145/vdm_config.o ../../core/vdm/vdm_config.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1853363519/Log.o: ../../core/Log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1853363519" 
	@${RM} ${OBJECTDIR}/_ext/1853363519/Log.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853363519/Log.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853363519/Log.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/1853363519/Log.o.d" -o ${OBJECTDIR}/_ext/1853363519/Log.o ../../core/Log.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1853363519/TypeC.o: ../../core/TypeC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1853363519" 
	@${RM} ${OBJECTDIR}/_ext/1853363519/TypeC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853363519/TypeC.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853363519/TypeC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/1853363519/TypeC.o.d" -o ${OBJECTDIR}/_ext/1853363519/TypeC.o ../../core/TypeC.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1853363519/fusb30X.o: ../../core/fusb30X.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1853363519" 
	@${RM} ${OBJECTDIR}/_ext/1853363519/fusb30X.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853363519/fusb30X.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853363519/fusb30X.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/1853363519/fusb30X.o.d" -o ${OBJECTDIR}/_ext/1853363519/fusb30X.o ../../core/fusb30X.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1853363519/PDPolicy.o: ../../core/PDPolicy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1853363519" 
	@${RM} ${OBJECTDIR}/_ext/1853363519/PDPolicy.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853363519/PDPolicy.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853363519/PDPolicy.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/1853363519/PDPolicy.o.d" -o ${OBJECTDIR}/_ext/1853363519/PDPolicy.o ../../core/PDPolicy.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1853363519/PDProtocol.o: ../../core/PDProtocol.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1853363519" 
	@${RM} ${OBJECTDIR}/_ext/1853363519/PDProtocol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853363519/PDProtocol.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853363519/PDProtocol.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/1853363519/PDProtocol.o.d" -o ${OBJECTDIR}/_ext/1853363519/PDProtocol.o ../../core/PDProtocol.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1853363519/core.o: ../../core/core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1853363519" 
	@${RM} ${OBJECTDIR}/_ext/1853363519/core.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853363519/core.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853363519/core.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/1853363519/core.o.d" -o ${OBJECTDIR}/_ext/1853363519/core.o ../../core/core.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1853363519/AlternateModes.o: ../../core/AlternateModes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1853363519" 
	@${RM} ${OBJECTDIR}/_ext/1853363519/AlternateModes.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853363519/AlternateModes.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853363519/AlternateModes.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/1853363519/AlternateModes.o.d" -o ${OBJECTDIR}/_ext/1853363519/AlternateModes.o ../../core/AlternateModes.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1472/platform.o: ../platform.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/platform.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/platform.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/platform.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/1472/platform.o.d" -o ${OBJECTDIR}/_ext/1472/platform.o ../platform.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1472/NONE_Main.o: ../NONE_Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/NONE_Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/NONE_Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/NONE_Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/1472/NONE_Main.o.d" -o ${OBJECTDIR}/_ext/1472/NONE_Main.o ../NONE_Main.c    -Wdeclaration-after-statement
	
else
${OBJECTDIR}/_ext/403107043/dp.o: ../../core/vdm/DisplayPort/dp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/403107043" 
	@${RM} ${OBJECTDIR}/_ext/403107043/dp.o.d 
	@${RM} ${OBJECTDIR}/_ext/403107043/dp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/403107043/dp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/403107043/dp.o.d" -o ${OBJECTDIR}/_ext/403107043/dp.o ../../core/vdm/DisplayPort/dp.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/403107043/dp_system_stubs.o: ../../core/vdm/DisplayPort/dp_system_stubs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/403107043" 
	@${RM} ${OBJECTDIR}/_ext/403107043/dp_system_stubs.o.d 
	@${RM} ${OBJECTDIR}/_ext/403107043/dp_system_stubs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/403107043/dp_system_stubs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/403107043/dp_system_stubs.o.d" -o ${OBJECTDIR}/_ext/403107043/dp_system_stubs.o ../../core/vdm/DisplayPort/dp_system_stubs.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o: ../../core/vdm/vdm_callbacks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1644920145" 
	@${RM} ${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o.d" -o ${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o ../../core/vdm/vdm_callbacks.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1644920145/bitfield_translators.o: ../../core/vdm/bitfield_translators.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1644920145" 
	@${RM} ${OBJECTDIR}/_ext/1644920145/bitfield_translators.o.d 
	@${RM} ${OBJECTDIR}/_ext/1644920145/bitfield_translators.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1644920145/bitfield_translators.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/1644920145/bitfield_translators.o.d" -o ${OBJECTDIR}/_ext/1644920145/bitfield_translators.o ../../core/vdm/bitfield_translators.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1644920145/vdm.o: ../../core/vdm/vdm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1644920145" 
	@${RM} ${OBJECTDIR}/_ext/1644920145/vdm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1644920145/vdm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1644920145/vdm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/1644920145/vdm.o.d" -o ${OBJECTDIR}/_ext/1644920145/vdm.o ../../core/vdm/vdm.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1644920145/vdm_config.o: ../../core/vdm/vdm_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1644920145" 
	@${RM} ${OBJECTDIR}/_ext/1644920145/vdm_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1644920145/vdm_config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1644920145/vdm_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/1644920145/vdm_config.o.d" -o ${OBJECTDIR}/_ext/1644920145/vdm_config.o ../../core/vdm/vdm_config.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1853363519/Log.o: ../../core/Log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1853363519" 
	@${RM} ${OBJECTDIR}/_ext/1853363519/Log.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853363519/Log.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853363519/Log.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/1853363519/Log.o.d" -o ${OBJECTDIR}/_ext/1853363519/Log.o ../../core/Log.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1853363519/TypeC.o: ../../core/TypeC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1853363519" 
	@${RM} ${OBJECTDIR}/_ext/1853363519/TypeC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853363519/TypeC.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853363519/TypeC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/1853363519/TypeC.o.d" -o ${OBJECTDIR}/_ext/1853363519/TypeC.o ../../core/TypeC.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1853363519/fusb30X.o: ../../core/fusb30X.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1853363519" 
	@${RM} ${OBJECTDIR}/_ext/1853363519/fusb30X.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853363519/fusb30X.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853363519/fusb30X.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/1853363519/fusb30X.o.d" -o ${OBJECTDIR}/_ext/1853363519/fusb30X.o ../../core/fusb30X.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1853363519/PDPolicy.o: ../../core/PDPolicy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1853363519" 
	@${RM} ${OBJECTDIR}/_ext/1853363519/PDPolicy.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853363519/PDPolicy.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853363519/PDPolicy.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/1853363519/PDPolicy.o.d" -o ${OBJECTDIR}/_ext/1853363519/PDPolicy.o ../../core/PDPolicy.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1853363519/PDProtocol.o: ../../core/PDProtocol.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1853363519" 
	@${RM} ${OBJECTDIR}/_ext/1853363519/PDProtocol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853363519/PDProtocol.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853363519/PDProtocol.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/1853363519/PDProtocol.o.d" -o ${OBJECTDIR}/_ext/1853363519/PDProtocol.o ../../core/PDProtocol.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1853363519/core.o: ../../core/core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1853363519" 
	@${RM} ${OBJECTDIR}/_ext/1853363519/core.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853363519/core.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853363519/core.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/1853363519/core.o.d" -o ${OBJECTDIR}/_ext/1853363519/core.o ../../core/core.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1853363519/AlternateModes.o: ../../core/AlternateModes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1853363519" 
	@${RM} ${OBJECTDIR}/_ext/1853363519/AlternateModes.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853363519/AlternateModes.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853363519/AlternateModes.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/1853363519/AlternateModes.o.d" -o ${OBJECTDIR}/_ext/1853363519/AlternateModes.o ../../core/AlternateModes.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1472/platform.o: ../platform.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/platform.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/platform.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/platform.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/1472/platform.o.d" -o ${OBJECTDIR}/_ext/1472/platform.o ../platform.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1472/NONE_Main.o: ../NONE_Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/NONE_Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/NONE_Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/NONE_Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DFSUSB300_EVAL_BOARD -DPLATFORM_NONE -MMD -MF "${OBJECTDIR}/_ext/1472/NONE_Main.o.d" -o ${OBJECTDIR}/_ext/1472/NONE_Main.o ../NONE_Main.c    -Wdeclaration-after-statement
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Platform_None.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_ICD3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Platform_None.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}           -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,--defsym=_min_heap_size=4096,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Platform_None.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Platform_None.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=4096,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Platform_None.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
