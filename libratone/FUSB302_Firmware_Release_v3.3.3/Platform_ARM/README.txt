Fairchild Semiconductor

FUSB302 ARM Platform Firmware

ST Micro STM32F072-Discovery development board
http://www.st.com/web/catalog/tools/FM116/CL1620/SC959/SS1532/LN1848/PF259724


Project is developed and organized for either the Coocox CoIDE development
environment or Keil's uVision5.


----- Coocox CoIDE -----

http://www.coocox.org/



----- Keil uVision5 -----

http://www.keil.com/arm/mdk.asp
(Free license available for use with STM32 processors.)



*** Also required:

ARM toolchain: Version "4.9 2015q2" tested. (Req'd for CoIDE)
http://launchpad.net/gcc-arm-embedded

STM32CubeF0 (Low level drivers, example code, etc.)  Version "1.6.0" tested.
http://www.st.com/web/catalog/tools/FM147/CL1794/SC961/SS1743/LN1897/PF260612


*** Suggested build directory structure:

C:/ARM/GNUToolsARMEmbedded/4_9_2015q2/...
C:/ARM/STM32Cube_FW_F0_V1.6.0/...
C:/Projects/fusb302_firmware/...

*** Hardware Connections:

Ground.
I2C SCL    - B10
I2C SDA    - B11
INT_N      - A1
VBUS 5V En - C3


*** Compile Time Options:

The following symbols need to be defined for the ARM platform - at least for the STM32F072B-Discovery board.
PLATFORM_ARM, USE_USB_CLKSOURCE_CRSHSI48, USE_HAL_DRIVER,
STM32F072xB, STM32F072RBT6

For Interrupt mode operation, use FSC_INTERRUPT_TRIGGERED.  Polling is enabled by default if this isn't defined.

Note: Interrupt mode still relies on polling a flag in the main while(1) loop.
For power/processor cycle savings, clocks can be idled or low power mode(s) entered and woken back up again in the interrupt function.

Debug support (Hostcomm, GUI communication, USB-to-Host) is enabled using FSC_DEBUG.

Source, Sink, and DRP options can be configured using the compile flags FSC_HAVE_SRC, FSC_HAVE_SNK, and FSC_HAVE_DRP in the following combinations:

FSC_HAVE_SRC - Source Only
FSC_HAVE_SNK - Sink Only
FSC_HAVE_SRC, FSC_HAVE_SNK - Source or Sink Configurable
FSC_HAVE_SRC, FSC_HAVE_SNK, FSC_HAVE_DRP - DRP capable Source or Sink

Accessory mode support is enabled using FSC_HAVE_ACCMODE.

VDM and DP support is enabled using FSC_HAVE_VDM and FSC_HAVE_DP.

