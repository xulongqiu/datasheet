#include "../core/platform.h"
#include "GenericTypeDefs.h"
#include "HWIO.h"
#include "PlatformI2C.h"
#include "TimeDelay.h"
#include "Timing.h"

FSC_BOOL platform_i2c_write(FSC_U8 SlaveAddress,
                            FSC_U8 RegAddrLength,
                            FSC_U8 DataLength,
                            FSC_U8 PacketSize,
                            FSC_U8 IncSize,
                            FSC_U32 RegisterAddress,
                            FSC_U8* Data)
{ 
    I2C_ERROR_t ret;
    ret = I2C_WriteData(    FUSB300I2CMod,
                            SlaveAddress,
                            RegAddrLength,
                            DataLength,
                            PacketSize,
                            IncSize,
                            RegisterAddress,
                            Data);

    if (ret == I2C_NOERROR) return FALSE;
    else                    return TRUE;
}

FSC_BOOL platform_i2c_read (FSC_U8 SlaveAddress,
                            FSC_U8 RegAddrLength,
                            FSC_U8 DataLength,
                            FSC_U8 PacketSize,
                            FSC_U8 IncSize,
                            FSC_U32 RegisterAddress,
                            FSC_U8* Data)
{
    I2C_ERROR_t ret;
    ret = I2C_ReadData(     FUSB300I2CMod,
                            SlaveAddress,
                            RegAddrLength,
                            DataLength,
                            PacketSize,
                            IncSize,
                            RegisterAddress,
                            Data);

    if (ret == I2C_NOERROR) return FALSE;
    else                    return TRUE;
}

void platform_delay_10us( FSC_U32 tenMicroSecondCounter )
{
    Delay10us(tenMicroSecondCounter);
}

void platform_enable_timer(FSC_BOOL enable)
{
    EnableCoreTimer(enable);
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
#ifdef FM150404A
    /* configure SS_SW_EN pin */
    if (orientation == CC1)
        LATBbits.LATB4 = 0;
    else
        LATBbits.LATB4 = 1;
#endif
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
    // Set data role
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
    return (((FSC_U16)(get_system_time() - timer->start_time) > timer->timeout) ? TRUE: FALSE);
}

FSC_U16 platform_get_system_time()
{
    return get_system_time();
}