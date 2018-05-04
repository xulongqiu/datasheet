#ifndef _HWIO_H_
#define _HWIO_H_

#include "GenericTypeDefs.h"

#ifdef FSC_INTERRUPT_TRIGGERED
/*******************************************************************************
 * Function:        InitializeExtIRQ
 * Input:           None
 * Return:          None
 * Description:     Set up the INT_N interrupt.  Interrupt is disabled.
 ******************************************************************************/
void InitializeExtIRQ(void);

/*******************************************************************************
 * Function:        EnableExtIRQ
 * Input:           enable - enable or disable the interrupt.
 * Return:          None
 * Description:     Set or clear the enable bit for the interrupt.
 ******************************************************************************/
void EnableExtIRQ(FSC_BOOL enable);

#endif // FSC_INTERRUPT_TRIGGERED

#endif // _HWIO_H_