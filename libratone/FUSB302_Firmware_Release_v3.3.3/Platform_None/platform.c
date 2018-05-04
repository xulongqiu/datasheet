#include "../core/platform.h"

void platform_set_vbus_lvl_enable(VBUS_LVL level,
                                  FSC_BOOL blnEnable,
                                  FSC_BOOL blnDisableOthers)
{
    unsigned int i;

    // Additional VBUS levels can be added here as needed.
    switch (level) {
    case VBUS_LVL_5V:
        // Enable/Disable the 5V Source

        break;
    case VBUS_LVL_12V:
        // Enable/Disable the 12V Source

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

        break;
    case VBUS_LVL_12V:
        // Return the state of the 12V VBUS Source.

        break;
    default:
        // Otherwise, return FALSE.
        break;
    }

    return FALSE;
}

void platform_set_vbus_discharge(FSC_BOOL blnEnable)
{
    // Enable/Disable the discharge path
    // TODO - Implement as needed on platforms that support this feature.
}

FSC_BOOL platform_get_device_irq_state( void )
{
    // Return the state of the device interrupt signal.
    return FALSE;
}

FSC_BOOL platform_i2c_write(FSC_U8 SlaveAddress,
                            FSC_U8 RegAddrLength,
                            FSC_U8 DataLength,
                            FSC_U8 PacketSize,
                            FSC_U8 IncSize,
                            FSC_U32 RegisterAddress,
                            FSC_U8* Data)
{ 
    // Write some data!
    
    /* 
     * Return FALSE if successful,
     * Return TRUE otherwise.
     */

    return TRUE;
}

FSC_BOOL platform_i2c_read( FSC_U8 SlaveAddress,
                            FSC_U8 RegAddrLength,
                            FSC_U8 DataLength,
                            FSC_U8 PacketSize,
                            FSC_U8 IncSize,
                            FSC_U32 RegisterAddress,
                            FSC_U8* Data)
{
    // Read some data!

    /* 
     * Return FALSE if successful,
     * Return TRUE otherwise.
     */
    
    return TRUE;
}

void platform_initialize_timer( void )
{
    // Initialize a 100us tick timer!
}

void platform_enable_timer( FSC_BOOL blnEnable )
{
    if( blnEnable )
    {
        // TODO - Start the timer
    }
    else
    {
        // TODO - Stop the timer
    }
}

/*****************************************************************************
* Function:        platform_delay_10us
* Input:           delayCount - Number of 10us delays to wait
* Return:          None
* Description:     Perform a software delay in intervals of 10us.
******************************************************************************/
void platform_delay_10us(FSC_U32 delayCount)
{
    fusb_Delay10us(delayCount);
}

/*******************************************************************************
* Function:        platform_notify_cc_orientation
* Input:           orientation - Orientation of CC (NONE, CC1, CC2)
* Return:          None
* Description:     A callback used by the core to report to the platform the
*                  current CC orientation. Called in SetStateAttached... and
*                  SetStateUnattached functions.
******************************************************************************/
void platform_notify_cc_orientation(CC_ORIENTATION orientation)
{
        // Optional: Notify platform of CC orientation
}

/*******************************************************************************
* Function:        platform_notify_pd_contract
* Input:           contract - TRUE: Contract, FALSE: No Contract
* Return:          None
* Description:     A callback used by the core to report to the platform the
*                  current PD contract status. Called in PDPolicy.
*******************************************************************************/
void platform_notify_pd_contract(FSC_BOOL contract)
{
    // Optional: Notify platform of PD contract
}

/*******************************************************************************
* Function:        platform_notify_unsupported_accessory
* Input:           None
* Return:          None
* Description:     A callback used by the core to report entry to the
*                  Unsupported Accessory state. The platform may implement
*                  USB Billboard.
*******************************************************************************/
void platform_notify_unsupported_accessory(void)
{
    // Optional: Implement USB Billboard
}

/*******************************************************************************
* Function:        platform_set_data_role
* Input:           PolicyIsDFP - Current data role
* Return:          None
* Description:     A callback used by the core to report the new data role after
*                  a data role swap.
*******************************************************************************/
void platform_set_data_role(FSC_BOOL PolicyIsDFP)
{
    // Optional: Set data role
}

/*******************************************************************************
* Function:        platform_notify_bist
* Input:           bistEnabled - TRUE when BIST enabled, FALSE when disabled
* Return:          None
* Description:     A callback that may be used to limit current sinking during
*                  BIST 
*******************************************************************************/
void platform_notify_bist(FSC_BOOL bistEnabled)
{
    // Do something
}

void platform_set_timer(TIMER *timer, FSC_U16 timeout)
{
    timer->start_time = get_system_time();
    timer->timeout = timeout;
}

FSC_BOOL platform_check_timer(TIMER *timer)
{
    return (((get_system_time() - timer->start_time) > timer->timeout) ? TRUE: FALSE);
}

FSC_U16 platform_get_system_time()
{
    return get_system_time();
}
