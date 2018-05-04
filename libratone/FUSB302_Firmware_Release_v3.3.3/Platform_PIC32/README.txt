Fairchild Semiconductor

FUSB302 PIC32 Platform Firmware

PIC part on evaluation board: PIC32MX250F128B


Project is developed and organized for the MPLAB X (v3.10) development environment.

http://www.microchip.com/pagehandler/en-us/family/mplabx/


Also required:

XC32 Compiler: Version "1.34" tested.  A different version may require selection in the build configurations settings window under "Compiler Toolchain".
http://www.microchip.com/pagehandler/en-us/devtools/mplabxc/home.html


*** Compile Time Options:
For the PIC platform, the PLATFORM_PIC32 flag must be defined.

For Interrupt mode operation, use FSC_INTERRUPT_TRIGGERED.  Polling is enabled by default if this isn't defined.

Note: Interrupt mode still relies on polling a flag in the main while(1) loop. For power/processor cycle savings, clocks can be idled or low power mode(s) entered and woken back up again in the interrupt function.

Source, Sink, and DRP options can be configured using the compile flags FSC_HAVE_SRC, FSC_HAVE_SNK, and FSC_HAVE_DRP in the following combinations:

FSC_HAVE_SRC - Source Only
FSC_HAVE_SNK - Sink Only
FSC_HAVE_SRC, FSC_HAVE_SNK - Source or Sink Configurable
FSC_HAVE_SRC, FSC_HAVE_SNK, FSC_HAVE_DRP - DRP capable Source or Sink

Accessory mode support is enabled using FSC_HAVE_ACCMODE.

VDM and DP support is enabled using FSC_HAVE_VDM and FSC_HAVE_DP.

Debug support (Hostcomm, GUI communication, USB-to-Host) is enabled using FSC_DEBUG.
