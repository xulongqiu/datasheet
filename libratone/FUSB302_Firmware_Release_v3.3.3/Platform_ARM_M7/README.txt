Fairchild Semiconductor

FUSB302 ARM-M7 Platform Firmware

ST Micro STM32F746G-DISCO development board


Project is developed and organized for Atollic TrueSTUDIO



*** Also required:

STM32CubeF7 (Low level drivers, example code, etc.)  Version "1.3.0" tested.


*** Suggested build directory structure:

C:/ARM/GNUToolsARMEmbedded/4_9_2015q2/...
C:/ARM/STM32Cube_FW_F7_V1.3.0/...
C:/Projects/fusb302_firmware/...


*** Hardware Connections:

Ground
I2C SCL        - PB8  ( EVB -> CN7.10 )
I2C SDA        - PB9  ( EVB -> CN7.9  )
INT_N          - PA0  ( EVB -> CN5.1  )
VBUS_5V_PIN    - PF7  ( EVB -> CN5.5  )
VBUS_12V_PIN   - PF6  ( EVB -> CN5.6  )


*** Compile Time Options:

The following symbols need to be defined for the ARM platform - at least for the STM32F746G-DISCO board:
PLATFORM_ARM_M7, USE_HAL_DRIVER, USE_USB_CLKSOURCE_CRSHSI48, STM32F746xx

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

