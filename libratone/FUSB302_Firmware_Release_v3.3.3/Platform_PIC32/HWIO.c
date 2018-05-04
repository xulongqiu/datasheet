#include "HWIO.h"

#include "HardwareProfile.h"
#include "../core/platform.h"

#include <Peripheral/ports.h>

void platform_set_vbus_lvl_enable(VBUS_LVL level, FSC_BOOL blnEnable, FSC_BOOL blnDisableOthers)
{
    unsigned int i;

    // Additional VBUS levels can be added here as needed.
    switch (level) {
    case VBUS_LVL_5V:
        // Enable/Disable the 5V Source
        VBUS_5V_EN = blnEnable ? 1 : 0;
        break;
    case VBUS_LVL_12V:
        // Enable/Disable the 12V Source
        VBUS_12V_EN = blnEnable ? 1 : 0;
        break;
    default:
        // Otherwise, do nothing.
        break;
    }

    // Turn off other levels, if requested
    if (blnDisableOthers || ((level == VBUS_LVL_ALL) && (blnEnable == FALSE)))
    {
        i = 0;

        do {
            // Skip the current level
            if( i == level ) continue;

            // Turn off the other level(s)
            platform_set_vbus_lvl_enable( i, FALSE, FALSE );
        } while (++i < VBUS_LVL_COUNT);
    }
}

FSC_BOOL platform_get_vbus_lvl_enable( VBUS_LVL level )
{
    // Additional VBUS levels can be added here as needed.
    switch (level) {
    case VBUS_LVL_5V:
        // Return the state of the 5V VBUS Source.
        return ( VBUS_5V_EN == 1 ) ? TRUE : FALSE;
    case VBUS_LVL_12V:
        // Return the state of the 12V VBUS Source.
        return ( VBUS_12V_EN == 1 ) ? TRUE : FALSE;
    default:
        // Otherwise, return FALSE.
        return FALSE;
    }
}

void platform_set_vbus_discharge(FSC_BOOL blnEnable)
{
    // Enable/Disable Vbus Discharge Path
    VBUS_DISCHARGE = blnEnable ? 1 : 0;
}

#ifdef FSC_INTERRUPT_TRIGGERED
void InitializeExtIRQ(void)
{
    CNPUAbits.CNPUA1 = 1;           // Set internal pull up on.
    mINT0IntEnable(FALSE);          // Interrupt is disabled to start
    mINT0ClearIntFlag();            // Clear the interrupt flag
    mINT0SetEdgeMode(0);            // Falling edge
    mINT0SetIntPriority(2);         // Set the priority to level 2
    mINT0SetIntSubPriority(3);      // Set the sub-priority to the highest level
}

void EnableExtIRQ(FSC_BOOL enable)
{
    mINT0IntEnable(enable);         // Enable the interrupt if requested
}

FSC_BOOL volatile haveINTReady = FALSE;

void __ISR(_EXTERNAL_0_VECTOR, IPL3AUTO) _External0Handler(void)
{
    mINT0ClearIntFlag();            // Clear the interrupt flag
    haveINTReady = TRUE;
}
#endif // FSC_INTERRUPT_TRIGGERED

FSC_BOOL platform_get_device_irq_state(void)
{
    // The interrupt pin is ACTIVE LOW, so this may look backwards!
    return DEVICE_INT_N ? FALSE : TRUE;
}
