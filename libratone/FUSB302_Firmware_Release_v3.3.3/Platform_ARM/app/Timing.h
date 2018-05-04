#ifndef _TIMING_H_
#define _TIMING_H_

#include "FSCTypes.h"

/*******************************************************************************
 * Function:        InitializeCoreTimer
 * Input:           None
 * Return:          None
 * Description:     Initializes the timer to trip every 0.1ms
 ******************************************************************************/
void InitializeCoreTimer( void );

/*******************************************************************************
 * Function:        EnableCoreTimer
 * Input:           blnEnable: TRUE=Start, FALSE=Stop
 * Return:          None
 * Description:     Start or stop the timer based on input boolean.
 ******************************************************************************/
void EnableCoreTimer( FSC_BOOL blnEnable );

FSC_U16 get_system_time(void);

#endif // _TIMING_H_
