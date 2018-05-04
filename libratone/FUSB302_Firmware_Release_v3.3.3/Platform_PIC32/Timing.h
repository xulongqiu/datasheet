#ifndef _TIMING_H_
#define _TIMING_H_

#include "GenericTypeDefs.h"

/*******************************************************************************
 * Function:        InitializeCoreTimer
 * Input:           None
 * Return:          None
 * Description:     Initializes the timer to trip every 0.1ms
 ******************************************************************************/
void InitializeCoreTimer(void);

/*******************************************************************************
 * Function:        EnableCoreTimer
 * Input:           blnEnable: TRUE=Start, FALSE=Stop
 * Return:          None
 * Description:     Start or stop the timer based on input boolean.
 ******************************************************************************/
void EnableCoreTimer(FSC_BOOL blnEnable);

/*******************************************************************************
 * Function:        InitializeTOTimer
 * Input:           blnEnable - determines if the interrupt and timer will be
 *                              started upon exiting routine
 *                  uintTO    - sets the amount of time before the timer expires
 *                              in the base units of the timer
 *                              (need to know the peripheral clock speed)
 * Return:          None
 * Description:     Initializes the timer to trip every uintTO milliseconds.
 *                  This timer is used ONLY by the I2C implementation.
 ******************************************************************************/
void InitializeTOTimer(FSC_BOOL blnEnable, FSC_U16 uintTO);

/*******************************************************************************
 * Function:        DisableTOTimer
 * Input:           None
 * Return:          None
 * Description:     Disable the timer
 ******************************************************************************/
void DisableTOTimer( void );

FSC_U16 get_system_time(void);

#endif // _TIMING_H_