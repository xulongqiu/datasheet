/*********************************************************************
 * FileName:        AnalogInput.h
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC32
 * Compiler:        XC32
 * Company:         Fairchild Semiconductor
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * M. Smith             11/19/2013   Initial Version
 ********************************************************************/
#ifndef _ANALOGINPUT_H
#define _ANALOGINPUT_H

#include "GenericTypeDefs.h"

/*******************************************************************************
 * Function:        InitializeADC
 * Input:           None
 * Return:          None
 * Description:     Initializes the PIC ADC port.
 ******************************************************************************/
void InitializeADC(void);

/*******************************************************************************
 * Function:        ReadADCChannel
 * Input:           bytChannel - ADC Channel - 0-15?
 * Return:          Averaged measurement.
 * Description:     Make 4 sample measurements in a row and return the average.
 ******************************************************************************/
FSC_U16 ReadADCChannel(BYTE bytChannel);

#endif
