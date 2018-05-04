/*****************************************************************************
 * FileName:        Main.c
 * Processor:       PIC32
 * Compiler:        MPLAB XC32
 * Company:         Fairchild Semiconductor
 *
 * Author           Date            Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * M. Smith         07/10/2014      Initial Version
 *****************************************************************************/
#include "Main.h"
#include "GenericTypeDefs.h"
#include "HardwareProfile.h"
#include <Peripheral/ports.h>
#include <Peripheral/system.h>

#ifdef FSC_DEBUG
#include "USB/usb_device.h"
#include "USB/usb_main.h"
#endif // FSC_DEBUG

#include "../core/core.h"
#include "PlatformI2C.h"
#include "Timing.h"
#include "AnalogInput.h"
#include "HWIO.h"

#include <limits.h>

// Configuration bits
#ifndef USE_BOOTLOADER
    #pragma config UPLLEN = ON              // USB PLL Enabled
    #pragma config DEBUG = OFF              // Background debugger disabled
    #pragma config FPLLMUL = MUL_20         // PLL Multiplier = Multiply by 20

    #pragma config FWDTEN = OFF             // Disable watchdog timer
    #pragma config POSCMOD = XT             // High speed xtal oscillator mode
    #pragma config FNOSC = PRIPLL           // Primary oscillator with PLL as source
    #pragma config FPBDIV = DIV_1           // Peripheral Bus Clock = Divide by 1
    #pragma config BWP = OFF                // Boot write protect disabled (can enable if desired)

    #pragma config FCKSM = CSECME           //
    #pragma config OSCIOFNC = ON            //
    #pragma config FSOSCEN = OFF            //
    #pragma config CP = OFF                 //
    #pragma config PWP = OFF                //

    #pragma config JTAGEN = OFF             // Disable the JTAG interface

    #if defined(FM141014) || defined(FM150911A) || defined(FM150404A)       // Based on 12MHz crystal
        #pragma config UPLLIDIV = DIV_3     // USB PLL Input Divider = Divide by 3  (UFIN = 4MHz, USB Clock = 48MHz)
        #pragma config FPLLIDIV = DIV_3     // PLL Input Divider = Divide by 3      (FIN = 4MHz, must be within 4-5MHz)
        #pragma config FPLLODIV = DIV_2     // PLL Output Divider: Divide by 2      (Max 40MHz clock)
        #pragma config ICESEL = ICS_PGx3    // ICE pins configured on PGx3
        #pragma config FUSBIDIO = OFF       // Disable the USB ID pin to use it as a GPIO
        #pragma config FVBUSONIO = OFF      // Disable the USB VBUSON pin to use it as a GPIO
    #elif defined(USBPD_EXPLORER_BOARD)     // Based on 8MHz crystal
        #pragma config UPLLIDIV = DIV_2     // USB PLL Input Divider = Divide by 2
        #pragma config FPLLIDIV = DIV_2     // PLL Input Divider = Divide by 2
        #pragma config FPLLODIV = DIV_2     // PLL Output Divider: Divide by 2 (max 40MHz clock)
        #pragma config ICESEL = ICS_PGx1    // ICE pins configured on PGx1 (PGx2 is multiplexed with USB D+ and D- pins).
    #else                                   // Based on 8MHz crystal
        #pragma config UPLLIDIV = DIV_2     // USB PLL Input Divider = Divide by 2
        #pragma config FPLLIDIV = DIV_2     // PLL Input Divider = Divide by 2
        #pragma config FPLLODIV = DIV_1     // PLL Output Divider: Divide by 1
        #pragma config ICESEL = ICS_PGx2    // ICE pins configured on PGx2, Boot write protect OFF.
    #endif
#endif

/////////////////////////////////////////////////////////////////////////////
//                                  MAIN
/////////////////////////////////////////////////////////////////////////////

extern FSC_BOOL volatile haveINTReady;

/////////////////////////////////////////////////////////////////////////////
// Function:    int main()
// Output:      n/a
// Overview:    Program entry point and container of main loop
/////////////////////////////////////////////////////////////////////////////
int main( void )
{
    InitializeSystem();

    while (1)
    {
#ifdef FSC_DEBUG
#ifdef HOST_COM_USB

        // Process incoming USB messages
        USBDeviceTasks();
        ProcessHIDPacket();

#elif defined HOST_COM_UART

        // Process incoming UART messages and return reply
        UARTProcessIncomingMsg();
        UARTProcessOutgoingMsg();

#endif // HOST_COM_XXX
#endif // FSC_DEBUG
        // Run the Type-C state machine
#ifdef FSC_INTERRUPT_TRIGGERED
        if (haveINTReady
#ifdef FSC_DEBUG
            || haveUSBCommand
#endif // FSC_DEBUG
            )
        {
            haveINTReady = FALSE;
#ifdef FSC_DEBUG
            haveUSBCommand = FALSE;
#endif // FSC_DEBUG

            core_state_machine();
            
            // It is possible for the state machine to go into idle mode with
            // the interrupt pin still low and as a result the edge-sensitive
            // IRQ won't get triggered.  Check here before returning to wait
            // on the IRQ.
            if (platform_get_device_irq_state())
            {
                haveINTReady = TRUE;
            }
        }
#else
        core_state_machine();
#endif  /* Interrupt */
    }
}

/********************************************************************
 * Function:        static void InitializeSystem(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        InitializeSystem is a centralize initialization
 *                  routine. All required USB initialization routines
 *                  are called from here.
 *
 *                  User application initialization routine should
 *                  also be called from here.                  
 *
 * Note:            None
 *******************************************************************/
static void InitializeSystem(void)
{
    INTEnableSystemMultiVectoredInt();              // Enable multi-vectored interrupts
    SYSTEMConfigPerformance(GetSystemClock());      // Setup the dividers appropriately
    INTEnableInterrupts();                          // Enable global interrupts
    InitializeBoard();                              // Initialize the board configuration
    
    InitializeCoreTimer();                          // Initialize the Core timer
    EnableCoreTimer(TRUE);

#ifdef FSC_INTERRUPT_TRIGGERED
    InitializeExtIRQ();
    EnableExtIRQ( TRUE );
#endif // FSC_INTERRUPT_TRIGGERED

    #ifdef FPGA_BOARD
        FSC_U8 data;
        InitializeTOTimer(TRUE, USHRT_MAX);         // Starting a timer to try and seed the RNG with something different each time at startup...
        do                                          // If we using the FPGA board, we have to wait for it to come up before trying to communicate with it...
        {
            if (DeviceRead(0x01, 2, &data) == TRUE) // When we get a successful I2C read from the FPGA ...
                break;                              // break out of the loop
        } while (1);
        srand(TMR4);                                // Seed the RNG with the TMR4 count
        InitializeTOTimer(FALSE, 0);                // Disable the timer
    #endif

        
    core_initialize();
    //core_set_vbus_transition_time(tFPF2498Transition);
#ifdef DISABLE_STATE_MACHINE
    core_enable_typec(FALSE);
#else
    core_enable_typec(TRUE);                      
#endif

#ifdef FSC_DEBUG
#ifdef HOST_COM_USB
 	USBDeviceInit();                                // Initialize the USB module for communication (HID)
#elif defined HOST_COM_UART
    UARTDeviceInit();
#endif // HOST_COM_XXX
#endif // FSC_DEBUG
}

/////////////////////////////////////////////////////////////////////////////
// Function:    InitializeBoard()
// Input:       none
// Output:      none
// Overview:    Initializes the hardware components including the PIC device
//              used.
/////////////////////////////////////////////////////////////////////////////
#ifdef FC_TESTER_BOARD
    void InitializeBoard(void) {
        InitializeADC();
        I2C_Init(0, 100000, FALSE);             // Disable I2C module 1
        I2C_Init(1, 100000, TRUE);              // Enable I2C module 2
        I2C_Init(2, 100000, FALSE);             // Disable I2C module 3
        I2C_Init(3, 100000, FALSE);             // Disable I2C module 4
        I2C_Init(4, 100000, FALSE);             // Disable I2C module 5

         //Port A Pin Configuration
        mPORTAClearBits(0x06FF);
        mPORTASetPinsDigitalOut(0x06FF);        // Set unused pins to output low
        mPORTASetPinsDigitalIn(0xC000);         // Set CHG_AL_N and CHG_DET_N from 832 as digital inputs

        //Port B Pin Configuration
        mPORTBClearBits(0xFFFF);
        mPORTBSetPinsDigitalOut(0xFFE0);        // Set unused pins to output low
        mPORTBSetPinsDigitalIn(0x0008);         // Set FC_IN as a digital input
        mPORTBSetPinsAnalogIn(0x0017);          // Set the VBUS and FC pins as analog inputs until otherwise requested

        //Port C Pin Configuration
        mPORTCClearBits(0xFFFF);
        mPORTCSetPinsDigitalOut(0xFFFF);        // Port C is all unused, set to output low

        //Port D Pin Configuration
        mPORTDClearBits(0xFFFF);
        mPORTDSetBits(0x0200);
        mPORTDSetPinsDigitalOut(0x02FF);    // Set GOOD_BAT as an output high
        mPORTDSetPinsDigitalIn(0x0300);     // Set the SW_OPEN as digital input

        //Port E Pin Configuration
        mPORTEClearBits(0x03FF);
        mPORTESetPinsDigitalOut(0x03FF);    // Set the LED's as off and the unused pins as output low

        //Port F Pin Configuration
        mPORTFClearBits(0xFFFF);
        mPORTFSetPinsDigitalOut(0xFF);      // Port F is all unused, set to output low

        //Port G Pin Configuration
        mPORTGClearBits(0xF1C3);
        mPORTGSetPinsDigitalOut(0xF1C3);    // Set unused pins as output low
        mPORTGSetPinsDigitalIn(0x0200);     // Set the bootloader detect pin as a digital input
    }
#elif defined USBPD_EXPLORER_BOARD
    void InitializeBoard(void) {
        InitializeADC();
        I2C_Init(0, 100000, FALSE);             // Disable I2C module 1
        I2C_Init(1, 100000, FALSE);             // Disable I2C module 2

         //Port A Pin Configuration
        mPORTAClearBits(0x001F);
        mPORTASetPinsDigitalOut(0x001F);        // Port A is all unused, set to output low

        //Port B Pin Configuration
        mPORTBClearBits(0xFFFF);
        mPORTBSetPinsDigitalOut(0xFFFF);        // Set all Port B pins to output low (USB module should override for D+/D-)

        //Port C Pin Configuration
        mPORTCClearBits(0x03DF);
        mPORTCSetPinsDigitalOut(0x03FF);        // Port C is all unused, set to output low
        mPORTCSetPinsDigitalIn(0x0020);         // Set the line connected to VBUS as an input
    }

#elif defined FSUSB300_EVAL_BOARD
    void InitializeBoard(void) {
        InitializeADC();
        I2C_Init(0, 1000000, TRUE);              // Enable I2C module 1
        I2C_Init(1, 400000, FALSE);             // Disable I2C module 2

        //Port A Pin Configuration
        mPORTAClearBits(0x000F);                // Set the unused bits to low
        mPORTASetBits(0x0000);                  // Set FPF2498 to off by default
        mPORTASetPinsDigitalOut(0x0013);        // Configure the unused to output low and the 2498 to output high

        //Port B Pin Configuration
        mPORTBClearBits(0xFFFF);                // Set all bits to low by default
        mPORTBSetBits(0x0020);                  // Set the I2C_SEL line to high by default, the 12V output disabled
        mPORTBSetPinsDigitalIn(0x6FC0);         // Configure the digital inputs
        mPORTBSetPinsDigitalOut(0x0030);        // Configure the digital outputs
        mPORTBSetPinsAnalogIn(0x800F);          // Configure the analog pins
    }
#elif defined(FM141014) || defined(FM150911A) || defined(FM150404A)
    void InitializeBoard(void) {
        InitializeADC();
        I2C_Init(0, 1000000, TRUE);              // Enable I2C module 1
        I2C_Init(1, 400000, FALSE);             // Disable I2C module 2

        //Port A Pin Configuration
        mPORTAClearBits(0x001F);                // Set the unused bits to low
        mPORTASetBits(0x0000);                  // Set FPF2498 to off by default
        mPORTASetPinsDigitalOut(0x0013);        // Configure the unused to output low and the 2498 to output high

        //Port B Pin Configuration
        mPORTBClearBits(0xFFFF);                // Set all bits to low by default
        mPORTBSetBits(0x0020);                  // Set the I2C_SEL line to high by default, the 12V output disabled
        mPORTBSetPinsDigitalIn(0x6FC0);         // Configure the digital inputs
        mPORTBSetPinsDigitalOut(0x0038);        // Configure the digital outputs
        mPORTBSetPinsAnalogIn(0x8007);          // Configure the analog pins
    }
#elif defined FM150105
    void InitializeBoard(void) {
        InitializeADC();
        I2C_Init(0, 1000000, TRUE);              // Enable I2C module 1
        I2C_Init(1, 400000, FALSE);             // Disable I2C module 2

        //Port A Pin Configuration
        mPORTAClearBits(0x000F);                // Set the unused bits to low
        mPORTASetBits(0x0000);                  // Set FPF2498 to off by default
        mPORTASetPinsDigitalOut(0x0013);        // Configure the unused to output low and the 2498 to output high

        //Port B Pin Configuration
        mPORTBClearBits(0xFFFF);                // Set all bits to low by default
        mPORTBSetBits(0x0020);                  // Set the I2C_SEL line to high by default, the 12V output disabled
        mPORTBSetPinsDigitalIn(0x6FC0);         // Configure the digital inputs
        mPORTBSetPinsDigitalOut(0x0030);        // Configure the digital outputs
        mPORTBSetPinsAnalogIn(0x800F);          // Configure the analog pins
    }
#endif
