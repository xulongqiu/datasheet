#include "Timing.h"
#include <Peripheral/ports.h>
#include <Peripheral/system.h>
#include "../core/core.h"
#include "HardwareProfile.h"

FSC_U16 volatile g_timer;

void InitializeCoreTimer(void)
{
    T2CON = 0x00;                   // Stop any Timer2 operation
    T2CONSET = 0x0050;              // 1:32 interval (0.4탎 80MHz PBCLK / 0.8탎 40MHz PBCLK), use 16 bit
    TMR2 = 0x0000;                  // Clear the contents of TMR2
    #if defined (__PIC32MX1XX_2XX__)
        PR2 = 1250;                  // If we are using the 40MHz PBCLK, set to 125 for a 0.1ms timer
    #else
        PR2 = 2500;                  // If we are using the 80MHz PBCLK, set to 250 for a 0.1ms timer
    #endif
    mT2ClearIntFlag();              // Clear the interrupt flag
    mT2IntEnable(TRUE);             // Enable the interrupt if requested
    mT2SetIntPriority(5);           // Set the timer interrupt priority to level 5 (below the INTB interrupt)
    mT2SetIntSubPriority(3);        // Set the sub-priority to the highest level
    
    g_timer = 0;
}

void EnableCoreTimer(FSC_BOOL blnEnable)
{
    if( blnEnable )
        T2CONSET = 0x8000;  // Start the timer
    else
        T2CONCLR = 0x8000;  // Stop the timer
}

void __ISR(_TIMER_2_VECTOR) _Timer2Handler(void)
{
//    core_tick();
    g_timer++;
    mT2ClearIntFlag();
}

void InitializeTOTimer(FSC_BOOL blnEnable, FSC_U16 uintTO)
{
    T4CON = 0x00;                   // Stop any Timer4 operation
    T4CONSET = 0x0070;              // 1:256 interval (3.2탎 80MHz PBCLK / 6.4탎 40MHz PBCLK), use 16 bit
    TMR4 = 0x0000;                  // Clear the contents of TMR4
    #if defined (__PIC32MX1XX_2XX__)
        uintTO >>= 1;               // If we are using the 40MHz PBCLK, divide by 2 to keep consistency
    #endif
    PR4 = uintTO;                   // Set the timer to go off every timeout interval
    mT4ClearIntFlag();              // Clear the interrupt flag
    mT4IntEnable(FALSE);            // Disable the interrupt (only going to monitor the flag for timeouts
    if (blnEnable)                  // Only start the timer if requested
        T4CONSET = 0x8000;          // Start the timer
}

void DisableTOTimer( void )
{
    T4CONbits.ON = 0;
}

FSC_U16 get_system_time(void)
{
    return g_timer;
}
