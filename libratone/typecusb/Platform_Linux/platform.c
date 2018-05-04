#include <linux/printk.h>                                                       // pr_err, printk, etc
#include "fusb30x_global.h"                                                     // Chip structure
#include "platform_helpers.h"                                                   // Implementation details
#include "../core/platform.h"

/*******************************************************************************
* Function:        platform_set/get_vbus_lvl_enable
* Input:           VBUS_LVL - requested voltage
*                  Boolean - enable this voltage level
*                  Boolean - turn off other supported voltages
* Return:          Boolean - on or off
* Description:     Provide access to the VBUS control pins.
******************************************************************************/
void platform_set_vbus_lvl_enable(VBUS_LVL level, FSC_BOOL blnEnable, FSC_BOOL blnDisableOthers)
{
    FSC_U32 i;
    return;

    // Additional VBUS levels can be added here as needed.
    switch (level) {
    case VBUS_LVL_5V:
        // Enable/Disable the 5V Source
        fusb_GPIO_Set_VBus5v(blnEnable == TRUE ? true : false);
        break;

    case VBUS_LVL_12V:
        // Enable/Disable the 12V Source
        fusb_GPIO_Set_VBusOther(blnEnable == TRUE ? true : false);
        break;

    default:
        // Otherwise, do nothing.
        break;
    }

    // Turn off other levels, if requested
    if (blnDisableOthers || ((level == VBUS_LVL_ALL) && (blnEnable == FALSE))) {
        i = 0;

        do {
            // Skip the current level
            if (i == level) {
                continue;
            }

            // Turn off the other level(s)
            platform_set_vbus_lvl_enable(i, FALSE, FALSE);
        } while (++i < VBUS_LVL_COUNT);
    }

    return;
}

FSC_BOOL platform_get_vbus_lvl_enable(VBUS_LVL level)
{
    // Additional VBUS levels can be added here as needed.
    return TRUE;

    switch (level) {
    case VBUS_LVL_5V:
        // Return the state of the 5V VBUS Source.
        return fusb_GPIO_Get_VBus5v() ? TRUE : FALSE;

    case VBUS_LVL_12V:
        // Return the state of the 12V VBUS Source.
        return fusb_GPIO_Get_VBusOther() ? TRUE : FALSE;

    default:
        // Otherwise, return FALSE.
        return FALSE;
    }
}

/*******************************************************************************
* Function:        platform_set_vbus_discharge
* Input:           Boolean
* Return:          None
* Description:     Enable/Disable Vbus Discharge Path
******************************************************************************/
void platform_set_vbus_discharge(FSC_BOOL blnEnable)
{
    // TODO - Implement if required for platform
}

/*******************************************************************************
* Function:        platform_get_device_irq_state
* Input:           None
* Return:          Boolean.  TRUE = Interrupt Active
* Description:     Get the state of the INT_N pin.  INT_N is active low.  This
*                  function handles that by returning TRUE if the pin is
*                  pulled low indicating an active interrupt signal.
******************************************************************************/
FSC_BOOL platform_get_device_irq_state(void)
{
    return fusb_GPIO_Get_IntN() ? TRUE : FALSE;
}

/*******************************************************************************
* Function:        platform_i2c_write
* Input:           SlaveAddress - Slave device bus address
*                  RegAddrLength - Register Address Byte Length
*                  DataLength - Length of data to transmit
*                  PacketSize - Maximum size of each transmitted packet
*                  IncSize - Number of bytes to send before incrementing addr
*                  RegisterAddress - Internal register address
*                  Data - Buffer of char data to transmit
* Return:          Error state
* Description:     Write a char buffer to the I2C peripheral.
******************************************************************************/
FSC_BOOL platform_i2c_write(FSC_U8 SlaveAddress,
                            FSC_U8 RegAddrLength,
                            FSC_U8 DataLength,
                            FSC_U8 PacketSize,
                            FSC_U8 IncSize,
                            FSC_U32 RegisterAddress,
                            FSC_U8* Data)
{
    FSC_BOOL ret = FALSE;

    if (Data == NULL) {
        pr_err("%s - Error: Write data buffer is NULL!\n", __func__);
        ret = TRUE;
    } else if (fusb_I2C_WriteData((FSC_U8)RegisterAddress, DataLength, Data)) {
        ret = FALSE;
    } else { // I2C Write failure
        ret = TRUE;       // Write data block to the device
    }
    //platform_delay_10us(50);

    return ret;
}

/*******************************************************************************
* Function:        platform_i2c_read
* Input:           SlaveAddress - Slave device bus address
*                  RegAddrLength - Register Address Byte Length
*                  DataLength - Length of data to attempt to read
*                  PacketSize - Maximum size of each received packet
*                  IncSize - Number of bytes to recv before incrementing addr
*                  RegisterAddress - Internal register address
*                  Data - Buffer for received char data
* Return:          Error state.
* Description:     Read char data from the I2C peripheral.
******************************************************************************/
FSC_BOOL platform_i2c_read(FSC_U8 SlaveAddress,
                           FSC_U8 RegAddrLength,
                           FSC_U8 DataLength,
                           FSC_U8 PacketSize,
                           FSC_U8 IncSize,
                           FSC_U32 RegisterAddress,
                           FSC_U8* Data)
{
    FSC_BOOL ret = FALSE;
    FSC_S32 i = 0;
    FSC_U8 temp = 0;
    struct fusb30x_chip* chip = fusb30x_GetChip();

    if (!chip) {
        pr_err("FUSB  %s - Error: Chip structure is NULL!\n", __func__);
        return TRUE;
    }

    if (Data == NULL) {
        pr_err("%s - Error: Read data buffer is NULL!\n", __func__);
        ret = TRUE;
    } else if (DataLength > 1 && chip->use_i2c_blocks) { // Do block reads if able and necessary
        if (!fusb_I2C_ReadBlockData(RegisterAddress, DataLength, Data)) {
            ret = TRUE;
        } else {
            ret = FALSE;
        }
    } else {
        for (i = 0; i < DataLength; i++) {
            if (fusb_I2C_ReadData((FSC_U8)RegisterAddress + i, &temp)) {
                Data[i] = temp;
                ret = FALSE;
            } else {
                ret = TRUE;
                break;
            }
        }
    }
    //platform_delay_10us(50);
    return ret;
}

/*****************************************************************************
* Function:        platform_enable_timer
* Input:           enable - TRUE to enable platform timer, FALSE to disable
* Return:          None
* Description:     Enables or disables platform timer
******************************************************************************/
void platform_enable_timer(FSC_BOOL enable)
{

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
    // Optional: Control Data Direction
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

void platform_set_timer(TIMER* timer, FSC_U16 timeout)
{
    timer->start_time = get_system_time();
    timer->timeout = timeout;
}

FSC_BOOL platform_check_timer(TIMER* timer)
{
    return (((FSC_U16)(get_system_time() - timer->start_time) > timer->timeout) ? TRUE : FALSE);
}

FSC_U16 platform_get_system_time()
{
    return get_system_time();
}

/*******************************************************************************
* Function:        platform_notify_attached
* Input:           isAttached: true, attached; false, deattached
* Return:          None
* Description:     notify platform that device attached or deattached
*******************************************************************************/
extern void power_fusb252_switch2host(void);
extern void power_fusb252_switch2bc12(void);
extern int isl923x_set_charger(bool isPlugIn);
void platform_notify_attached(FSC_BOOL isAttached)
{
#ifdef FSC_DEBUG
    //pr_err("FUSB  %s - typeC %s!\n", __func__, (isAttached ? "Attached, fusb252 switch to bc1.2" : "DeAttached, fusb252 switch to usb_host"));
#endif
    isl923x_set_charger(isAttached);
    if (isAttached) {
        power_fusb252_switch2bc12();
    } else {
        power_fusb252_switch2host();
    }
}

/*******************************************************************************
* Function:        platform_notify_sink_current
* Input:           current: USBTypeCCurrent.
* Return:          None
* Description:     notify platform that sink current capability
*******************************************************************************/
extern int isl923x_set_voltage_current(uint16_t vin_mV, uint16_t cmax_mA);
extern int power_bq24392_get_charger_type(void);
void platform_notify_sink_def_current(USBTypeCCurrent sinkCurrent)
{
    int bc12_cc = 0;

    switch (sinkCurrent) {
    case utccNone:
        power_fusb252_switch2host();
#ifdef FSC_DEBUG
        pr_err("FUSB  %s - sink current none, fusb252 switch to usb_host!\n", __func__);
#endif
        break;

    case utcc1p5A:
        power_fusb252_switch2host();
#ifdef FSC_DEBUG
        //pr_err("FUSB  %s - sink current 1.5A, fusb252 switch to usb_host!\n", __func__);
#endif
        break;

    case utcc3p0A:
        power_fusb252_switch2host();
#ifdef FSC_DEBUG
        //pr_err("FUSB  %s - sink current 3.0A, fusb252 switch to usb_host!\n", __func__);
#endif
        break;

    case utccDefault:
        bc12_cc = power_bq24392_get_charger_type();
        isl923x_set_voltage_current(5000, bc12_cc);
#ifdef FSC_DEBUG
        pr_err("FUSB  %s - sink current usb default, bq24392_check_current=%d(mA)!\n", __func__, bc12_cc);
#endif
        break;

    default:
        pr_err("FUSB  %s - sink current error!\n", __func__);
        break;
    }
}

/*******************************************************************************
* Function:        platform_notify_sink_current
* Input:           current: USBTypeCCurrent.
* Return:          None
* Description:     notify platform that sink current capability
*******************************************************************************/
void platform_notify_pd_sel_cap(FSC_U16 pdVoltage, FSC_U16 pdCurrent)
{
    int bc12_cc = 0;

    if (pdVoltage == 0 || pdCurrent == 0) {
        bc12_cc = power_bq24392_get_charger_type();
        isl923x_set_voltage_current(5000, bc12_cc);
#ifdef FSC_DEBUG
        pr_err("FUSB  %s - selected pd cap(no), bq24392_check_current=%d(mA)!\n", __func__, bc12_cc);
#endif
    } else {
        isl923x_set_voltage_current(pdVoltage, pdCurrent);
#ifdef  FSC_DEBUG
        pr_err("FUSB  %s - selected pd cap, voltage=%d(mV), current=%d(mA)\n", __func__,  pdVoltage, pdCurrent);
#endif
    }
    //got the capacity, switch to host
    power_fusb252_switch2host();
}
