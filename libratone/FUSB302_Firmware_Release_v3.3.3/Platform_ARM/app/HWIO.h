
#ifndef _HWIO_H_
#define _HWIO_H_

#include "FSCTypes.h"

/*******************************************************************************
 * Function:        InitializeGPIO
 * Input:           None
 * Return:          None
 * Description:     Initialize the GPIO pins including, if enabled, debug LEDs
 *                  and INT_N IRQ settings.
 ******************************************************************************/
void InitializeGPIO( void );

#ifdef FSC_INTERRUPT_TRIGGERED
/*******************************************************************************
 * Function:        EnableExtIRQ
 * Input:           blnEnable: TRUE=enable, FALSE=disable
 * Return:          None
 * Description:     Enable or disable the INT_N IRQ handler.
 ******************************************************************************/
void EnableExtIRQ(FSC_BOOL enable);
#endif // FSC_INTERRUPT_TRIGGERED

#endif // _HWIO_H_
