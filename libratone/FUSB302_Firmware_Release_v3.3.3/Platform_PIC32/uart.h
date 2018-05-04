
#ifndef _UART_H_
#define _UART_H_

#ifdef FSC_DEBUG

#include "GenericTypeDefs.h"

/*******************************************************************************
 * Function:        UARTDeviceInit
 * Input:           None
 * Return:          None
 * Description:     Initialize the UART peripheral.
 ******************************************************************************/
void UARTDeviceInit( void );

/*******************************************************************************
 * Function:        UARTProcessIncomingMsg
 * Input:           None
 * Return:          None
 * Description:     Receive a full message from the Host.
 ******************************************************************************/
void UARTProcessIncomingMsg( void );

/*******************************************************************************
 * Function:        UARTProcessOutgoingMsg
 * Input:           None
 * Return:          None
 * Description:     Return a response to the host.
 ******************************************************************************/
void UARTProcessOutgoingMsg( void );

#endif // FSC_DEBUG

#endif // _UART_H_