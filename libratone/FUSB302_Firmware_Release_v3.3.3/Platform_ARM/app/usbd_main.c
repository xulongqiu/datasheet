#include "usbd_main.h"

#include "usbd_core.h"
#include "usbd_hid.h"

USBD_HandleTypeDef USBD_Device;

#define USB_MSG_LENGTH      64
unsigned char USBInputMsg[ USB_MSG_LENGTH ];
unsigned char USBOutputMsg[ USB_MSG_LENGTH ];

/*******************************************************************************
 * Function:        InitializeUSB
 * Input:           None
 * Return:          None
 * Description:     Initializes all the timers that are used.
 ******************************************************************************/
void InitializeUSB( void )
{
    unsigned int i;

    for( i = 0; i < 64; i++ ) USBInputMsg[ i ] = 0;

    /* Init Device Library */
    USBD_Init(&USBD_Device, &HID_Desc, 0);

    /* Register the HID class */
    USBD_RegisterClass(&USBD_Device, &USBD_HID);

    /* Start Device Process */
    USBD_Start(&USBD_Device);
}
