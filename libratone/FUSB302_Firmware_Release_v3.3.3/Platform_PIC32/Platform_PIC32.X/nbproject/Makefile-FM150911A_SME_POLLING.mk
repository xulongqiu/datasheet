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
ifeq "$(wildcard nbproject/Makefile-local-FM150911A_SME_POLLING.mk)" "nbproject/Makefile-local-FM150911A_SME_POLLING.mk"
include nbproject/Makefile-local-FM150911A_SME_POLLING.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=FM150911A_SME_POLLING
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Platform_PIC32.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Platform_PIC32.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../core/vdm/DisplayPort/dp.c ../../core/vdm/DisplayPort/dp_system_stubs.c ../../core/vdm/vdm_callbacks.c ../../core/vdm/bitfield_translators.c ../../core/vdm/vdm.c ../../core/vdm/vdm_config.c ../../core/Log.c ../../core/TypeC.c ../../core/fusb30X.c ../../core/PDPolicy.c ../../core/PDProtocol.c ../../core/core.c ../USB/usb_descriptors.c ../USB/usb_device.c ../USB/usb_function_hid.c ../USB/usb_main.c ../platform.c ../Main.c ../AnalogInput.c ../HostComm.c ../I2CPrivate.c ../TimeDelay.c ../PlatformI2C.c ../Timing.c ../HWIO.c ../uart.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/403107043/dp.o ${OBJECTDIR}/_ext/403107043/dp_system_stubs.o ${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o ${OBJECTDIR}/_ext/1644920145/bitfield_translators.o ${OBJECTDIR}/_ext/1644920145/vdm.o ${OBJECTDIR}/_ext/1644920145/vdm_config.o ${OBJECTDIR}/_ext/1853363519/Log.o ${OBJECTDIR}/_ext/1853363519/TypeC.o ${OBJECTDIR}/_ext/1853363519/fusb30X.o ${OBJECTDIR}/_ext/1853363519/PDPolicy.o ${OBJECTDIR}/_ext/1853363519/PDProtocol.o ${OBJECTDIR}/_ext/1853363519/core.o ${OBJECTDIR}/_ext/1360907413/usb_descriptors.o ${OBJECTDIR}/_ext/1360907413/usb_device.o ${OBJECTDIR}/_ext/1360907413/usb_function_hid.o ${OBJECTDIR}/_ext/1360907413/usb_main.o ${OBJECTDIR}/_ext/1472/platform.o ${OBJECTDIR}/_ext/1472/Main.o ${OBJECTDIR}/_ext/1472/AnalogInput.o ${OBJECTDIR}/_ext/1472/HostComm.o ${OBJECTDIR}/_ext/1472/I2CPrivate.o ${OBJECTDIR}/_ext/1472/TimeDelay.o ${OBJECTDIR}/_ext/1472/PlatformI2C.o ${OBJECTDIR}/_ext/1472/Timing.o ${OBJECTDIR}/_ext/1472/HWIO.o ${OBJECTDIR}/_ext/1472/uart.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/403107043/dp.o.d ${OBJECTDIR}/_ext/403107043/dp_system_stubs.o.d ${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o.d ${OBJECTDIR}/_ext/1644920145/bitfield_translators.o.d ${OBJECTDIR}/_ext/1644920145/vdm.o.d ${OBJECTDIR}/_ext/1644920145/vdm_config.o.d ${OBJECTDIR}/_ext/1853363519/Log.o.d ${OBJECTDIR}/_ext/1853363519/TypeC.o.d ${OBJECTDIR}/_ext/1853363519/fusb30X.o.d ${OBJECTDIR}/_ext/1853363519/PDPolicy.o.d ${OBJECTDIR}/_ext/1853363519/PDProtocol.o.d ${OBJECTDIR}/_ext/1853363519/core.o.d ${OBJECTDIR}/_ext/1360907413/usb_descriptors.o.d ${OBJECTDIR}/_ext/1360907413/usb_device.o.d ${OBJECTDIR}/_ext/1360907413/usb_function_hid.o.d ${OBJECTDIR}/_ext/1360907413/usb_main.o.d ${OBJECTDIR}/_ext/1472/platform.o.d ${OBJECTDIR}/_ext/1472/Main.o.d ${OBJECTDIR}/_ext/1472/AnalogInput.o.d ${OBJECTDIR}/_ext/1472/HostComm.o.d ${OBJECTDIR}/_ext/1472/I2CPrivate.o.d ${OBJECTDIR}/_ext/1472/TimeDelay.o.d ${OBJECTDIR}/_ext/1472/PlatformI2C.o.d ${OBJECTDIR}/_ext/1472/Timing.o.d ${OBJECTDIR}/_ext/1472/HWIO.o.d ${OBJECTDIR}/_ext/1472/uart.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/403107043/dp.o ${OBJECTDIR}/_ext/403107043/dp_system_stubs.o ${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o ${OBJECTDIR}/_ext/1644920145/bitfield_translators.o ${OBJECTDIR}/_ext/1644920145/vdm.o ${OBJECTDIR}/_ext/1644920145/vdm_config.o ${OBJECTDIR}/_ext/1853363519/Log.o ${OBJECTDIR}/_ext/1853363519/TypeC.o ${OBJECTDIR}/_ext/1853363519/fusb30X.o ${OBJECTDIR}/_ext/1853363519/PDPolicy.o ${OBJECTDIR}/_ext/1853363519/PDProtocol.o ${OBJECTDIR}/_ext/1853363519/core.o ${OBJECTDIR}/_ext/1360907413/usb_descriptors.o ${OBJECTDIR}/_ext/1360907413/usb_device.o ${OBJECTDIR}/_ext/1360907413/usb_function_hid.o ${OBJECTDIR}/_ext/1360907413/usb_main.o ${OBJECTDIR}/_ext/1472/platform.o ${OBJECTDIR}/_ext/1472/Main.o ${OBJECTDIR}/_ext/1472/AnalogInput.o ${OBJECTDIR}/_ext/1472/HostComm.o ${OBJECTDIR}/_ext/1472/I2CPrivate.o ${OBJECTDIR}/_ext/1472/TimeDelay.o ${OBJECTDIR}/_ext/1472/PlatformI2C.o ${OBJECTDIR}/_ext/1472/Timing.o ${OBJECTDIR}/_ext/1472/HWIO.o ${OBJECTDIR}/_ext/1472/uart.o

# Source Files
SOURCEFILES=../../core/vdm/DisplayPort/dp.c ../../core/vdm/DisplayPort/dp_system_stubs.c ../../core/vdm/vdm_callbacks.c ../../core/vdm/bitfield_translators.c ../../core/vdm/vdm.c ../../core/vdm/vdm_config.c ../../core/Log.c ../../core/TypeC.c ../../core/fusb30X.c ../../core/PDPolicy.c ../../core/PDProtocol.c ../../core/core.c ../USB/usb_descriptors.c ../USB/usb_device.c ../USB/usb_function_hid.c ../USB/usb_main.c ../platform.c ../Main.c ../AnalogInput.c ../HostComm.c ../I2CPrivate.c ../TimeDelay.c ../PlatformI2C.c ../Timing.c ../HWIO.c ../uart.c


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
	${MAKE}  -f nbproject/Makefile-FM150911A_SME_POLLING.mk dist/${CND_CONF}/${IMAGE_TYPE}/Platform_PIC32.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX250F128B
MP_LINKER_FILE_OPTION=,--script="..\app_32MX250F128B.ld"
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
	@${FIXDEPS} "${OBJECTDIR}/_ext/403107043/dp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/403107043/dp.o.d" -o ${OBJECTDIR}/_ext/403107043/dp.o ../../core/vdm/DisplayPort/dp.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/403107043/dp_system_stubs.o: ../../core/vdm/DisplayPort/dp_system_stubs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/403107043" 
	@${RM} ${OBJECTDIR}/_ext/403107043/dp_system_stubs.o.d 
	@${RM} ${OBJECTDIR}/_ext/403107043/dp_system_stubs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/403107043/dp_system_stubs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/403107043/dp_system_stubs.o.d" -o ${OBJECTDIR}/_ext/403107043/dp_system_stubs.o ../../core/vdm/DisplayPort/dp_system_stubs.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o: ../../core/vdm/vdm_callbacks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1644920145" 
	@${RM} ${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o.d" -o ${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o ../../core/vdm/vdm_callbacks.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1644920145/bitfield_translators.o: ../../core/vdm/bitfield_translators.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1644920145" 
	@${RM} ${OBJECTDIR}/_ext/1644920145/bitfield_translators.o.d 
	@${RM} ${OBJECTDIR}/_ext/1644920145/bitfield_translators.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1644920145/bitfield_translators.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1644920145/bitfield_translators.o.d" -o ${OBJECTDIR}/_ext/1644920145/bitfield_translators.o ../../core/vdm/bitfield_translators.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1644920145/vdm.o: ../../core/vdm/vdm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1644920145" 
	@${RM} ${OBJECTDIR}/_ext/1644920145/vdm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1644920145/vdm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1644920145/vdm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1644920145/vdm.o.d" -o ${OBJECTDIR}/_ext/1644920145/vdm.o ../../core/vdm/vdm.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1644920145/vdm_config.o: ../../core/vdm/vdm_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1644920145" 
	@${RM} ${OBJECTDIR}/_ext/1644920145/vdm_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1644920145/vdm_config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1644920145/vdm_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1644920145/vdm_config.o.d" -o ${OBJECTDIR}/_ext/1644920145/vdm_config.o ../../core/vdm/vdm_config.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1853363519/Log.o: ../../core/Log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1853363519" 
	@${RM} ${OBJECTDIR}/_ext/1853363519/Log.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853363519/Log.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853363519/Log.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1853363519/Log.o.d" -o ${OBJECTDIR}/_ext/1853363519/Log.o ../../core/Log.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1853363519/TypeC.o: ../../core/TypeC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1853363519" 
	@${RM} ${OBJECTDIR}/_ext/1853363519/TypeC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853363519/TypeC.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853363519/TypeC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1853363519/TypeC.o.d" -o ${OBJECTDIR}/_ext/1853363519/TypeC.o ../../core/TypeC.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1853363519/fusb30X.o: ../../core/fusb30X.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1853363519" 
	@${RM} ${OBJECTDIR}/_ext/1853363519/fusb30X.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853363519/fusb30X.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853363519/fusb30X.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1853363519/fusb30X.o.d" -o ${OBJECTDIR}/_ext/1853363519/fusb30X.o ../../core/fusb30X.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1853363519/PDPolicy.o: ../../core/PDPolicy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1853363519" 
	@${RM} ${OBJECTDIR}/_ext/1853363519/PDPolicy.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853363519/PDPolicy.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853363519/PDPolicy.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1853363519/PDPolicy.o.d" -o ${OBJECTDIR}/_ext/1853363519/PDPolicy.o ../../core/PDPolicy.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1853363519/PDProtocol.o: ../../core/PDProtocol.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1853363519" 
	@${RM} ${OBJECTDIR}/_ext/1853363519/PDProtocol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853363519/PDProtocol.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853363519/PDProtocol.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1853363519/PDProtocol.o.d" -o ${OBJECTDIR}/_ext/1853363519/PDProtocol.o ../../core/PDProtocol.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1853363519/core.o: ../../core/core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1853363519" 
	@${RM} ${OBJECTDIR}/_ext/1853363519/core.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853363519/core.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853363519/core.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1853363519/core.o.d" -o ${OBJECTDIR}/_ext/1853363519/core.o ../../core/core.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1360907413/usb_descriptors.o: ../USB/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360907413" 
	@${RM} ${OBJECTDIR}/_ext/1360907413/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360907413/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360907413/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1360907413/usb_descriptors.o.d" -o ${OBJECTDIR}/_ext/1360907413/usb_descriptors.o ../USB/usb_descriptors.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1360907413/usb_device.o: ../USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360907413" 
	@${RM} ${OBJECTDIR}/_ext/1360907413/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360907413/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360907413/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1360907413/usb_device.o.d" -o ${OBJECTDIR}/_ext/1360907413/usb_device.o ../USB/usb_device.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1360907413/usb_function_hid.o: ../USB/usb_function_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360907413" 
	@${RM} ${OBJECTDIR}/_ext/1360907413/usb_function_hid.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360907413/usb_function_hid.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360907413/usb_function_hid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1360907413/usb_function_hid.o.d" -o ${OBJECTDIR}/_ext/1360907413/usb_function_hid.o ../USB/usb_function_hid.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1360907413/usb_main.o: ../USB/usb_main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360907413" 
	@${RM} ${OBJECTDIR}/_ext/1360907413/usb_main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360907413/usb_main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360907413/usb_main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1360907413/usb_main.o.d" -o ${OBJECTDIR}/_ext/1360907413/usb_main.o ../USB/usb_main.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1472/platform.o: ../platform.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/platform.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/platform.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/platform.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1472/platform.o.d" -o ${OBJECTDIR}/_ext/1472/platform.o ../platform.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1472/Main.o: ../Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1472/Main.o.d" -o ${OBJECTDIR}/_ext/1472/Main.o ../Main.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1472/AnalogInput.o: ../AnalogInput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/AnalogInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/AnalogInput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/AnalogInput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1472/AnalogInput.o.d" -o ${OBJECTDIR}/_ext/1472/AnalogInput.o ../AnalogInput.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1472/HostComm.o: ../HostComm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/HostComm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/HostComm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/HostComm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1472/HostComm.o.d" -o ${OBJECTDIR}/_ext/1472/HostComm.o ../HostComm.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1472/I2CPrivate.o: ../I2CPrivate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/I2CPrivate.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/I2CPrivate.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/I2CPrivate.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1472/I2CPrivate.o.d" -o ${OBJECTDIR}/_ext/1472/I2CPrivate.o ../I2CPrivate.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1472/TimeDelay.o: ../TimeDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/TimeDelay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/TimeDelay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/TimeDelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1472/TimeDelay.o.d" -o ${OBJECTDIR}/_ext/1472/TimeDelay.o ../TimeDelay.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1472/PlatformI2C.o: ../PlatformI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/PlatformI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/PlatformI2C.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/PlatformI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1472/PlatformI2C.o.d" -o ${OBJECTDIR}/_ext/1472/PlatformI2C.o ../PlatformI2C.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1472/Timing.o: ../Timing.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Timing.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Timing.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Timing.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1472/Timing.o.d" -o ${OBJECTDIR}/_ext/1472/Timing.o ../Timing.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1472/HWIO.o: ../HWIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/HWIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/HWIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/HWIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1472/HWIO.o.d" -o ${OBJECTDIR}/_ext/1472/HWIO.o ../HWIO.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1472/uart.o: ../uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/uart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1472/uart.o.d" -o ${OBJECTDIR}/_ext/1472/uart.o ../uart.c    -Wdeclaration-after-statement
	
else
${OBJECTDIR}/_ext/403107043/dp.o: ../../core/vdm/DisplayPort/dp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/403107043" 
	@${RM} ${OBJECTDIR}/_ext/403107043/dp.o.d 
	@${RM} ${OBJECTDIR}/_ext/403107043/dp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/403107043/dp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/403107043/dp.o.d" -o ${OBJECTDIR}/_ext/403107043/dp.o ../../core/vdm/DisplayPort/dp.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/403107043/dp_system_stubs.o: ../../core/vdm/DisplayPort/dp_system_stubs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/403107043" 
	@${RM} ${OBJECTDIR}/_ext/403107043/dp_system_stubs.o.d 
	@${RM} ${OBJECTDIR}/_ext/403107043/dp_system_stubs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/403107043/dp_system_stubs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/403107043/dp_system_stubs.o.d" -o ${OBJECTDIR}/_ext/403107043/dp_system_stubs.o ../../core/vdm/DisplayPort/dp_system_stubs.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o: ../../core/vdm/vdm_callbacks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1644920145" 
	@${RM} ${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o.d" -o ${OBJECTDIR}/_ext/1644920145/vdm_callbacks.o ../../core/vdm/vdm_callbacks.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1644920145/bitfield_translators.o: ../../core/vdm/bitfield_translators.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1644920145" 
	@${RM} ${OBJECTDIR}/_ext/1644920145/bitfield_translators.o.d 
	@${RM} ${OBJECTDIR}/_ext/1644920145/bitfield_translators.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1644920145/bitfield_translators.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1644920145/bitfield_translators.o.d" -o ${OBJECTDIR}/_ext/1644920145/bitfield_translators.o ../../core/vdm/bitfield_translators.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1644920145/vdm.o: ../../core/vdm/vdm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1644920145" 
	@${RM} ${OBJECTDIR}/_ext/1644920145/vdm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1644920145/vdm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1644920145/vdm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1644920145/vdm.o.d" -o ${OBJECTDIR}/_ext/1644920145/vdm.o ../../core/vdm/vdm.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1644920145/vdm_config.o: ../../core/vdm/vdm_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1644920145" 
	@${RM} ${OBJECTDIR}/_ext/1644920145/vdm_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1644920145/vdm_config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1644920145/vdm_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1644920145/vdm_config.o.d" -o ${OBJECTDIR}/_ext/1644920145/vdm_config.o ../../core/vdm/vdm_config.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1853363519/Log.o: ../../core/Log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1853363519" 
	@${RM} ${OBJECTDIR}/_ext/1853363519/Log.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853363519/Log.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853363519/Log.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1853363519/Log.o.d" -o ${OBJECTDIR}/_ext/1853363519/Log.o ../../core/Log.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1853363519/TypeC.o: ../../core/TypeC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1853363519" 
	@${RM} ${OBJECTDIR}/_ext/1853363519/TypeC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853363519/TypeC.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853363519/TypeC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1853363519/TypeC.o.d" -o ${OBJECTDIR}/_ext/1853363519/TypeC.o ../../core/TypeC.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1853363519/fusb30X.o: ../../core/fusb30X.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1853363519" 
	@${RM} ${OBJECTDIR}/_ext/1853363519/fusb30X.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853363519/fusb30X.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853363519/fusb30X.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1853363519/fusb30X.o.d" -o ${OBJECTDIR}/_ext/1853363519/fusb30X.o ../../core/fusb30X.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1853363519/PDPolicy.o: ../../core/PDPolicy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1853363519" 
	@${RM} ${OBJECTDIR}/_ext/1853363519/PDPolicy.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853363519/PDPolicy.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853363519/PDPolicy.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1853363519/PDPolicy.o.d" -o ${OBJECTDIR}/_ext/1853363519/PDPolicy.o ../../core/PDPolicy.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1853363519/PDProtocol.o: ../../core/PDProtocol.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1853363519" 
	@${RM} ${OBJECTDIR}/_ext/1853363519/PDProtocol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853363519/PDProtocol.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853363519/PDProtocol.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1853363519/PDProtocol.o.d" -o ${OBJECTDIR}/_ext/1853363519/PDProtocol.o ../../core/PDProtocol.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1853363519/core.o: ../../core/core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1853363519" 
	@${RM} ${OBJECTDIR}/_ext/1853363519/core.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853363519/core.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853363519/core.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1853363519/core.o.d" -o ${OBJECTDIR}/_ext/1853363519/core.o ../../core/core.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1360907413/usb_descriptors.o: ../USB/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360907413" 
	@${RM} ${OBJECTDIR}/_ext/1360907413/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360907413/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360907413/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1360907413/usb_descriptors.o.d" -o ${OBJECTDIR}/_ext/1360907413/usb_descriptors.o ../USB/usb_descriptors.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1360907413/usb_device.o: ../USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360907413" 
	@${RM} ${OBJECTDIR}/_ext/1360907413/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360907413/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360907413/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1360907413/usb_device.o.d" -o ${OBJECTDIR}/_ext/1360907413/usb_device.o ../USB/usb_device.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1360907413/usb_function_hid.o: ../USB/usb_function_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360907413" 
	@${RM} ${OBJECTDIR}/_ext/1360907413/usb_function_hid.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360907413/usb_function_hid.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360907413/usb_function_hid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1360907413/usb_function_hid.o.d" -o ${OBJECTDIR}/_ext/1360907413/usb_function_hid.o ../USB/usb_function_hid.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1360907413/usb_main.o: ../USB/usb_main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360907413" 
	@${RM} ${OBJECTDIR}/_ext/1360907413/usb_main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360907413/usb_main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360907413/usb_main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1360907413/usb_main.o.d" -o ${OBJECTDIR}/_ext/1360907413/usb_main.o ../USB/usb_main.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1472/platform.o: ../platform.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/platform.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/platform.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/platform.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1472/platform.o.d" -o ${OBJECTDIR}/_ext/1472/platform.o ../platform.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1472/Main.o: ../Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1472/Main.o.d" -o ${OBJECTDIR}/_ext/1472/Main.o ../Main.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1472/AnalogInput.o: ../AnalogInput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/AnalogInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/AnalogInput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/AnalogInput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1472/AnalogInput.o.d" -o ${OBJECTDIR}/_ext/1472/AnalogInput.o ../AnalogInput.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1472/HostComm.o: ../HostComm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/HostComm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/HostComm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/HostComm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1472/HostComm.o.d" -o ${OBJECTDIR}/_ext/1472/HostComm.o ../HostComm.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1472/I2CPrivate.o: ../I2CPrivate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/I2CPrivate.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/I2CPrivate.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/I2CPrivate.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1472/I2CPrivate.o.d" -o ${OBJECTDIR}/_ext/1472/I2CPrivate.o ../I2CPrivate.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1472/TimeDelay.o: ../TimeDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/TimeDelay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/TimeDelay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/TimeDelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1472/TimeDelay.o.d" -o ${OBJECTDIR}/_ext/1472/TimeDelay.o ../TimeDelay.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1472/PlatformI2C.o: ../PlatformI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/PlatformI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/PlatformI2C.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/PlatformI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1472/PlatformI2C.o.d" -o ${OBJECTDIR}/_ext/1472/PlatformI2C.o ../PlatformI2C.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1472/Timing.o: ../Timing.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Timing.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Timing.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Timing.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1472/Timing.o.d" -o ${OBJECTDIR}/_ext/1472/Timing.o ../Timing.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1472/HWIO.o: ../HWIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/HWIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/HWIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/HWIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1472/HWIO.o.d" -o ${OBJECTDIR}/_ext/1472/HWIO.o ../HWIO.c    -Wdeclaration-after-statement
	
${OBJECTDIR}/_ext/1472/uart.o: ../uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/uart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DPLATFORM_PIC32 -DHOST_COM_USB -DFM150911A -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_HAVE_ACCMODE -DFSC_HAVE_SNK -DFSC_HAVE_SRC -DFSC_HAVE_DRP -DFSC_HAVE_VDM -DFSC_HAVE_DP -DFSC_DEBUG -DFSC_INTERRUPT_TRIGGERED -DFSC_ILLEGAL_CABLE -I"../" -I"../Microchip" -I"../Microchip/Include" -I"../Microchip/Include/USB" -I"../Board Support Package" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1472/uart.o.d" -o ${OBJECTDIR}/_ext/1472/uart.o ../uart.c    -Wdeclaration-after-statement
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Platform_PIC32.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../app_32MX250F128B.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_SIMULATOR=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Platform_PIC32.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}              -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1,--defsym=_min_heap_size=4096,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Platform_PIC32.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../app_32MX250F128B.ld ../bootloader/USB_HID_Bootloader_FUSB300_v2.hex
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Platform_PIC32.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=4096,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Platform_PIC32.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
	@echo "Creating unified hex file"
	@"C:/Program Files (x86)/Microchip/MPLABX/v3.00/mplab_ide/mplab_ide/modules/../../bin/hexmate" --edf="C:/Program Files (x86)/Microchip/MPLABX/v3.00/mplab_ide/mplab_ide/modules/../../dat/en_msgs.txt" dist/${CND_CONF}/${IMAGE_TYPE}/Platform_PIC32.X.${IMAGE_TYPE}.hex ../bootloader/USB_HID_Bootloader_FUSB300_v2.hex -odist/${CND_CONF}/production/Platform_PIC32.X.production.unified.hex

endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/FM150911A_SME_POLLING
	${RM} -r dist/FM150911A_SME_POLLING

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
