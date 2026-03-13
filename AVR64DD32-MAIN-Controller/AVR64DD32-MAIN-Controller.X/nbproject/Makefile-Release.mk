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
ifeq "$(wildcard nbproject/Makefile-local-Release.mk)" "nbproject/Makefile-local-Release.mk"
include nbproject/Makefile-local-Release.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=Release
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/AVR64DD32-MAIN-Controller.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/AVR64DD32-MAIN-Controller.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../Actions.c ../ADC.c ../CLK.c ../CRC.c ../FOUSART.c ../GPIO.c ../i2c.c ../Joystick.c ../LinearMotor.c ../main.c ../RS485LED.c ../RS485USART.c ../RTC.c ../SSD1306.c ../StepperMotor.c ../TCA.c ../TCD.c ../USART.c ../Windows.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/Actions.o ${OBJECTDIR}/_ext/1472/ADC.o ${OBJECTDIR}/_ext/1472/CLK.o ${OBJECTDIR}/_ext/1472/CRC.o ${OBJECTDIR}/_ext/1472/FOUSART.o ${OBJECTDIR}/_ext/1472/GPIO.o ${OBJECTDIR}/_ext/1472/i2c.o ${OBJECTDIR}/_ext/1472/Joystick.o ${OBJECTDIR}/_ext/1472/LinearMotor.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/RS485LED.o ${OBJECTDIR}/_ext/1472/RS485USART.o ${OBJECTDIR}/_ext/1472/RTC.o ${OBJECTDIR}/_ext/1472/SSD1306.o ${OBJECTDIR}/_ext/1472/StepperMotor.o ${OBJECTDIR}/_ext/1472/TCA.o ${OBJECTDIR}/_ext/1472/TCD.o ${OBJECTDIR}/_ext/1472/USART.o ${OBJECTDIR}/_ext/1472/Windows.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/Actions.o.d ${OBJECTDIR}/_ext/1472/ADC.o.d ${OBJECTDIR}/_ext/1472/CLK.o.d ${OBJECTDIR}/_ext/1472/CRC.o.d ${OBJECTDIR}/_ext/1472/FOUSART.o.d ${OBJECTDIR}/_ext/1472/GPIO.o.d ${OBJECTDIR}/_ext/1472/i2c.o.d ${OBJECTDIR}/_ext/1472/Joystick.o.d ${OBJECTDIR}/_ext/1472/LinearMotor.o.d ${OBJECTDIR}/_ext/1472/main.o.d ${OBJECTDIR}/_ext/1472/RS485LED.o.d ${OBJECTDIR}/_ext/1472/RS485USART.o.d ${OBJECTDIR}/_ext/1472/RTC.o.d ${OBJECTDIR}/_ext/1472/SSD1306.o.d ${OBJECTDIR}/_ext/1472/StepperMotor.o.d ${OBJECTDIR}/_ext/1472/TCA.o.d ${OBJECTDIR}/_ext/1472/TCD.o.d ${OBJECTDIR}/_ext/1472/USART.o.d ${OBJECTDIR}/_ext/1472/Windows.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/Actions.o ${OBJECTDIR}/_ext/1472/ADC.o ${OBJECTDIR}/_ext/1472/CLK.o ${OBJECTDIR}/_ext/1472/CRC.o ${OBJECTDIR}/_ext/1472/FOUSART.o ${OBJECTDIR}/_ext/1472/GPIO.o ${OBJECTDIR}/_ext/1472/i2c.o ${OBJECTDIR}/_ext/1472/Joystick.o ${OBJECTDIR}/_ext/1472/LinearMotor.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/RS485LED.o ${OBJECTDIR}/_ext/1472/RS485USART.o ${OBJECTDIR}/_ext/1472/RTC.o ${OBJECTDIR}/_ext/1472/SSD1306.o ${OBJECTDIR}/_ext/1472/StepperMotor.o ${OBJECTDIR}/_ext/1472/TCA.o ${OBJECTDIR}/_ext/1472/TCD.o ${OBJECTDIR}/_ext/1472/USART.o ${OBJECTDIR}/_ext/1472/Windows.o

# Source Files
SOURCEFILES=../Actions.c ../ADC.c ../CLK.c ../CRC.c ../FOUSART.c ../GPIO.c ../i2c.c ../Joystick.c ../LinearMotor.c ../main.c ../RS485LED.c ../RS485USART.c ../RTC.c ../SSD1306.c ../StepperMotor.c ../TCA.c ../TCD.c ../USART.c ../Windows.c

# Pack Options 
PACK_COMPILER_OPTIONS=-I "${DFP_DIR}/include"
PACK_COMMON_OPTIONS=-B "${DFP_DIR}/gcc/dev/avr64dd32"



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
	${MAKE}  -f nbproject/Makefile-Release.mk ${DISTDIR}/AVR64DD32-MAIN-Controller.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=AVR64DD32
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
${OBJECTDIR}/_ext/1472/Actions.o: ../Actions.c  .generated_files/flags/Release/2de40b70f113f60ea3715f20f88598b69518d9ae .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Actions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Actions.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/Actions.o.d" -MT "${OBJECTDIR}/_ext/1472/Actions.o.d" -MT ${OBJECTDIR}/_ext/1472/Actions.o  -o ${OBJECTDIR}/_ext/1472/Actions.o ../Actions.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/ADC.o: ../ADC.c  .generated_files/flags/Release/fa586d16820286bc031c78ca15cfff6aded177cc .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ADC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ADC.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/ADC.o.d" -MT "${OBJECTDIR}/_ext/1472/ADC.o.d" -MT ${OBJECTDIR}/_ext/1472/ADC.o  -o ${OBJECTDIR}/_ext/1472/ADC.o ../ADC.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/CLK.o: ../CLK.c  .generated_files/flags/Release/ca7c0b32da78b49853fce698138573af296740ff .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/CLK.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/CLK.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/CLK.o.d" -MT "${OBJECTDIR}/_ext/1472/CLK.o.d" -MT ${OBJECTDIR}/_ext/1472/CLK.o  -o ${OBJECTDIR}/_ext/1472/CLK.o ../CLK.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/CRC.o: ../CRC.c  .generated_files/flags/Release/5ddfb09f8d1d1d4373d392d02ebd3a383d649ea6 .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/CRC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/CRC.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/CRC.o.d" -MT "${OBJECTDIR}/_ext/1472/CRC.o.d" -MT ${OBJECTDIR}/_ext/1472/CRC.o  -o ${OBJECTDIR}/_ext/1472/CRC.o ../CRC.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/FOUSART.o: ../FOUSART.c  .generated_files/flags/Release/bc8dfc094a960ff01c4abb485e46eb9cbc7505d .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/FOUSART.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/FOUSART.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/FOUSART.o.d" -MT "${OBJECTDIR}/_ext/1472/FOUSART.o.d" -MT ${OBJECTDIR}/_ext/1472/FOUSART.o  -o ${OBJECTDIR}/_ext/1472/FOUSART.o ../FOUSART.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/GPIO.o: ../GPIO.c  .generated_files/flags/Release/38199b541f3f0dd2efb25420a26d43c901829dc4 .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/GPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/GPIO.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/GPIO.o.d" -MT "${OBJECTDIR}/_ext/1472/GPIO.o.d" -MT ${OBJECTDIR}/_ext/1472/GPIO.o  -o ${OBJECTDIR}/_ext/1472/GPIO.o ../GPIO.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/i2c.o: ../i2c.c  .generated_files/flags/Release/624ccff0fb7e0ee96d7ce23c6d47faf2aff26bc2 .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/i2c.o.d" -MT "${OBJECTDIR}/_ext/1472/i2c.o.d" -MT ${OBJECTDIR}/_ext/1472/i2c.o  -o ${OBJECTDIR}/_ext/1472/i2c.o ../i2c.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/Joystick.o: ../Joystick.c  .generated_files/flags/Release/b7e3c512369cc43960c823ae6625603c0674f0c7 .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Joystick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Joystick.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/Joystick.o.d" -MT "${OBJECTDIR}/_ext/1472/Joystick.o.d" -MT ${OBJECTDIR}/_ext/1472/Joystick.o  -o ${OBJECTDIR}/_ext/1472/Joystick.o ../Joystick.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/LinearMotor.o: ../LinearMotor.c  .generated_files/flags/Release/455eab2cc24629fe2964938f40c372ae048f407d .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/LinearMotor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/LinearMotor.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/LinearMotor.o.d" -MT "${OBJECTDIR}/_ext/1472/LinearMotor.o.d" -MT ${OBJECTDIR}/_ext/1472/LinearMotor.o  -o ${OBJECTDIR}/_ext/1472/LinearMotor.o ../LinearMotor.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  .generated_files/flags/Release/826b0b539fc45fe8597fce4287d48ed0e6594ec3 .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/main.o.d" -MT "${OBJECTDIR}/_ext/1472/main.o.d" -MT ${OBJECTDIR}/_ext/1472/main.o  -o ${OBJECTDIR}/_ext/1472/main.o ../main.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/RS485LED.o: ../RS485LED.c  .generated_files/flags/Release/5bfec6b92079e852dd656eb79e6586b8403f9c9e .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/RS485LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/RS485LED.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/RS485LED.o.d" -MT "${OBJECTDIR}/_ext/1472/RS485LED.o.d" -MT ${OBJECTDIR}/_ext/1472/RS485LED.o  -o ${OBJECTDIR}/_ext/1472/RS485LED.o ../RS485LED.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/RS485USART.o: ../RS485USART.c  .generated_files/flags/Release/174334c6feb2cc9fd07b2f43e564703251895fda .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/RS485USART.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/RS485USART.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/RS485USART.o.d" -MT "${OBJECTDIR}/_ext/1472/RS485USART.o.d" -MT ${OBJECTDIR}/_ext/1472/RS485USART.o  -o ${OBJECTDIR}/_ext/1472/RS485USART.o ../RS485USART.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/RTC.o: ../RTC.c  .generated_files/flags/Release/c3daea667d8642481c712eb0633c437905859323 .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/RTC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/RTC.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/RTC.o.d" -MT "${OBJECTDIR}/_ext/1472/RTC.o.d" -MT ${OBJECTDIR}/_ext/1472/RTC.o  -o ${OBJECTDIR}/_ext/1472/RTC.o ../RTC.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/SSD1306.o: ../SSD1306.c  .generated_files/flags/Release/8567df9b052368b9ca177199391c6e53a8079ff5 .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/SSD1306.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/SSD1306.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/SSD1306.o.d" -MT "${OBJECTDIR}/_ext/1472/SSD1306.o.d" -MT ${OBJECTDIR}/_ext/1472/SSD1306.o  -o ${OBJECTDIR}/_ext/1472/SSD1306.o ../SSD1306.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/StepperMotor.o: ../StepperMotor.c  .generated_files/flags/Release/50828467791c651ddfaea502bbd4c65b48bdfec1 .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/StepperMotor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/StepperMotor.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/StepperMotor.o.d" -MT "${OBJECTDIR}/_ext/1472/StepperMotor.o.d" -MT ${OBJECTDIR}/_ext/1472/StepperMotor.o  -o ${OBJECTDIR}/_ext/1472/StepperMotor.o ../StepperMotor.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/TCA.o: ../TCA.c  .generated_files/flags/Release/1a2911b37f59f12330a266ebc9c80bb5605258cd .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/TCA.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/TCA.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/TCA.o.d" -MT "${OBJECTDIR}/_ext/1472/TCA.o.d" -MT ${OBJECTDIR}/_ext/1472/TCA.o  -o ${OBJECTDIR}/_ext/1472/TCA.o ../TCA.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/TCD.o: ../TCD.c  .generated_files/flags/Release/97cf73a90395ae4ae092c6de70c7fdd14c0c1a3 .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/TCD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/TCD.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/TCD.o.d" -MT "${OBJECTDIR}/_ext/1472/TCD.o.d" -MT ${OBJECTDIR}/_ext/1472/TCD.o  -o ${OBJECTDIR}/_ext/1472/TCD.o ../TCD.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/USART.o: ../USART.c  .generated_files/flags/Release/e2b5d7e89ac8fb8cbb773c80af083fc323f17b8b .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/USART.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/USART.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/USART.o.d" -MT "${OBJECTDIR}/_ext/1472/USART.o.d" -MT ${OBJECTDIR}/_ext/1472/USART.o  -o ${OBJECTDIR}/_ext/1472/USART.o ../USART.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/Windows.o: ../Windows.c  .generated_files/flags/Release/452ad5c3813918250dd4e489320ba8061f3a5b5c .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Windows.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Windows.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/Windows.o.d" -MT "${OBJECTDIR}/_ext/1472/Windows.o.d" -MT ${OBJECTDIR}/_ext/1472/Windows.o  -o ${OBJECTDIR}/_ext/1472/Windows.o ../Windows.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/1472/Actions.o: ../Actions.c  .generated_files/flags/Release/c0c1fe8993cf67d0150e2e9a453dac39337397dd .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Actions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Actions.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/Actions.o.d" -MT "${OBJECTDIR}/_ext/1472/Actions.o.d" -MT ${OBJECTDIR}/_ext/1472/Actions.o  -o ${OBJECTDIR}/_ext/1472/Actions.o ../Actions.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/ADC.o: ../ADC.c  .generated_files/flags/Release/5607d9626c64a26be0546d15a59c07a3c570bf7c .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ADC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ADC.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/ADC.o.d" -MT "${OBJECTDIR}/_ext/1472/ADC.o.d" -MT ${OBJECTDIR}/_ext/1472/ADC.o  -o ${OBJECTDIR}/_ext/1472/ADC.o ../ADC.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/CLK.o: ../CLK.c  .generated_files/flags/Release/6e57eb51a32a19e00eee12ee0627180b5fe58d30 .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/CLK.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/CLK.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/CLK.o.d" -MT "${OBJECTDIR}/_ext/1472/CLK.o.d" -MT ${OBJECTDIR}/_ext/1472/CLK.o  -o ${OBJECTDIR}/_ext/1472/CLK.o ../CLK.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/CRC.o: ../CRC.c  .generated_files/flags/Release/e7b4be2606a79ac673a6b86d316c2a4d86e223a4 .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/CRC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/CRC.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/CRC.o.d" -MT "${OBJECTDIR}/_ext/1472/CRC.o.d" -MT ${OBJECTDIR}/_ext/1472/CRC.o  -o ${OBJECTDIR}/_ext/1472/CRC.o ../CRC.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/FOUSART.o: ../FOUSART.c  .generated_files/flags/Release/976827cc822b23bddc283d56c835ef1d540a06c1 .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/FOUSART.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/FOUSART.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/FOUSART.o.d" -MT "${OBJECTDIR}/_ext/1472/FOUSART.o.d" -MT ${OBJECTDIR}/_ext/1472/FOUSART.o  -o ${OBJECTDIR}/_ext/1472/FOUSART.o ../FOUSART.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/GPIO.o: ../GPIO.c  .generated_files/flags/Release/3703417972504148d3e5fde4bd14d2b5f4901c41 .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/GPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/GPIO.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/GPIO.o.d" -MT "${OBJECTDIR}/_ext/1472/GPIO.o.d" -MT ${OBJECTDIR}/_ext/1472/GPIO.o  -o ${OBJECTDIR}/_ext/1472/GPIO.o ../GPIO.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/i2c.o: ../i2c.c  .generated_files/flags/Release/dc6ffbdb46c5e1df9e467baf12f1b21d6a40f054 .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/i2c.o.d" -MT "${OBJECTDIR}/_ext/1472/i2c.o.d" -MT ${OBJECTDIR}/_ext/1472/i2c.o  -o ${OBJECTDIR}/_ext/1472/i2c.o ../i2c.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/Joystick.o: ../Joystick.c  .generated_files/flags/Release/8961962b5446630815a0a302b40341ee7fdd9624 .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Joystick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Joystick.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/Joystick.o.d" -MT "${OBJECTDIR}/_ext/1472/Joystick.o.d" -MT ${OBJECTDIR}/_ext/1472/Joystick.o  -o ${OBJECTDIR}/_ext/1472/Joystick.o ../Joystick.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/LinearMotor.o: ../LinearMotor.c  .generated_files/flags/Release/60e4f629c2c0c70c7d3564daba34cbd3f8ad4129 .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/LinearMotor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/LinearMotor.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/LinearMotor.o.d" -MT "${OBJECTDIR}/_ext/1472/LinearMotor.o.d" -MT ${OBJECTDIR}/_ext/1472/LinearMotor.o  -o ${OBJECTDIR}/_ext/1472/LinearMotor.o ../LinearMotor.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  .generated_files/flags/Release/ef59460a0f3bd556c1438dc26915a95717f97f92 .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/main.o.d" -MT "${OBJECTDIR}/_ext/1472/main.o.d" -MT ${OBJECTDIR}/_ext/1472/main.o  -o ${OBJECTDIR}/_ext/1472/main.o ../main.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/RS485LED.o: ../RS485LED.c  .generated_files/flags/Release/938df32d56d8a1bd875e5bd53134dfa2123ae058 .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/RS485LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/RS485LED.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/RS485LED.o.d" -MT "${OBJECTDIR}/_ext/1472/RS485LED.o.d" -MT ${OBJECTDIR}/_ext/1472/RS485LED.o  -o ${OBJECTDIR}/_ext/1472/RS485LED.o ../RS485LED.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/RS485USART.o: ../RS485USART.c  .generated_files/flags/Release/9e34abfbd574e33d813fb85a0c40b916184b33e7 .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/RS485USART.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/RS485USART.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/RS485USART.o.d" -MT "${OBJECTDIR}/_ext/1472/RS485USART.o.d" -MT ${OBJECTDIR}/_ext/1472/RS485USART.o  -o ${OBJECTDIR}/_ext/1472/RS485USART.o ../RS485USART.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/RTC.o: ../RTC.c  .generated_files/flags/Release/77173e6443a02dfb4530ea827e0154e9bb757910 .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/RTC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/RTC.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/RTC.o.d" -MT "${OBJECTDIR}/_ext/1472/RTC.o.d" -MT ${OBJECTDIR}/_ext/1472/RTC.o  -o ${OBJECTDIR}/_ext/1472/RTC.o ../RTC.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/SSD1306.o: ../SSD1306.c  .generated_files/flags/Release/347c6d508af62d699bf752e447f91aae4d01722a .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/SSD1306.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/SSD1306.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/SSD1306.o.d" -MT "${OBJECTDIR}/_ext/1472/SSD1306.o.d" -MT ${OBJECTDIR}/_ext/1472/SSD1306.o  -o ${OBJECTDIR}/_ext/1472/SSD1306.o ../SSD1306.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/StepperMotor.o: ../StepperMotor.c  .generated_files/flags/Release/1827c83d5651730e7ca312b33c5c73ac6fed0d46 .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/StepperMotor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/StepperMotor.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/StepperMotor.o.d" -MT "${OBJECTDIR}/_ext/1472/StepperMotor.o.d" -MT ${OBJECTDIR}/_ext/1472/StepperMotor.o  -o ${OBJECTDIR}/_ext/1472/StepperMotor.o ../StepperMotor.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/TCA.o: ../TCA.c  .generated_files/flags/Release/38b953018da26b256f4057e3fe13c8ab3f1b145b .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/TCA.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/TCA.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/TCA.o.d" -MT "${OBJECTDIR}/_ext/1472/TCA.o.d" -MT ${OBJECTDIR}/_ext/1472/TCA.o  -o ${OBJECTDIR}/_ext/1472/TCA.o ../TCA.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/TCD.o: ../TCD.c  .generated_files/flags/Release/1129c5b200b32187ae229ce82958dc9558449dcb .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/TCD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/TCD.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/TCD.o.d" -MT "${OBJECTDIR}/_ext/1472/TCD.o.d" -MT ${OBJECTDIR}/_ext/1472/TCD.o  -o ${OBJECTDIR}/_ext/1472/TCD.o ../TCD.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/USART.o: ../USART.c  .generated_files/flags/Release/bac3d56d3eab53d15a96885076a9fa05cf503a7 .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/USART.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/USART.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/USART.o.d" -MT "${OBJECTDIR}/_ext/1472/USART.o.d" -MT ${OBJECTDIR}/_ext/1472/USART.o  -o ${OBJECTDIR}/_ext/1472/USART.o ../USART.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/Windows.o: ../Windows.c  .generated_files/flags/Release/13786dc8b105ebb62b7da002356ba5cc04047289 .generated_files/flags/Release/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Windows.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Windows.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64dd32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/Windows.o.d" -MT "${OBJECTDIR}/_ext/1472/Windows.o.d" -MT ${OBJECTDIR}/_ext/1472/Windows.o  -o ${OBJECTDIR}/_ext/1472/Windows.o ../Windows.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/AVR64DD32-MAIN-Controller.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=avr64dd32 ${PACK_COMMON_OPTIONS}   -gdwarf-2 -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="${DISTDIR}\AVR64DD32-MAIN-Controller.X.${IMAGE_TYPE}.map"    -o ${DISTDIR}/AVR64DD32-MAIN-Controller.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1 -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,-lm -Wl,--end-group 
	
	${MP_CC_DIR}\\avr-objcopy -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex "${DISTDIR}/AVR64DD32-MAIN-Controller.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "${DISTDIR}/AVR64DD32-MAIN-Controller.X.${IMAGE_TYPE}.eep" || exit 0
	${MP_CC_DIR}\\avr-objdump -h -S "${DISTDIR}/AVR64DD32-MAIN-Controller.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" > "${DISTDIR}/AVR64DD32-MAIN-Controller.X.${IMAGE_TYPE}.lss"
	${MP_CC_DIR}\\avr-objcopy -O srec -R .eeprom -R .fuse -R .lock -R .signature "${DISTDIR}/AVR64DD32-MAIN-Controller.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "${DISTDIR}/AVR64DD32-MAIN-Controller.X.${IMAGE_TYPE}.srec"
	
	
else
${DISTDIR}/AVR64DD32-MAIN-Controller.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=avr64dd32 ${PACK_COMMON_OPTIONS}  -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="${DISTDIR}\AVR64DD32-MAIN-Controller.X.${IMAGE_TYPE}.map"    -o ${DISTDIR}/AVR64DD32-MAIN-Controller.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION) -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}\\avr-objcopy -O ihex "${DISTDIR}/AVR64DD32-MAIN-Controller.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "${DISTDIR}/AVR64DD32-MAIN-Controller.X.${IMAGE_TYPE}.hex"
	${MP_CC_DIR}\\avr-objcopy -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex "${DISTDIR}/AVR64DD32-MAIN-Controller.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "${DISTDIR}/AVR64DD32-MAIN-Controller.X.${IMAGE_TYPE}.eep" || exit 0
	${MP_CC_DIR}\\avr-objdump -h -S "${DISTDIR}/AVR64DD32-MAIN-Controller.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" > "${DISTDIR}/AVR64DD32-MAIN-Controller.X.${IMAGE_TYPE}.lss"
	${MP_CC_DIR}\\avr-objcopy -O srec -R .eeprom -R .fuse -R .lock -R .signature "${DISTDIR}/AVR64DD32-MAIN-Controller.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "${DISTDIR}/AVR64DD32-MAIN-Controller.X.${IMAGE_TYPE}.srec"
	
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
