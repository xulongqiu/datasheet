#include "uart.h"
#include "HostComm.h"

#ifdef FSC_DEBUG

FSC_U8 UARTReceivedBuffer[64];
FSC_U8 UARTSendBuffer[64];

void UARTDeviceInit( void )
{
    // TODO - Initialize UART device, if available.
}

void UARTProcessIncomingMsg( void )
{
    FSC_BOOL haveNewMsg = FALSE;
    
    // TODO - Receive a full new message from the host
    
    if( haveNewMsg )
    {
        ProcessMsg( UARTReceivedBuffer, UARTSendBuffer );
    }
}

void UARTProcessOutgoingMsg( void )
{
    // TODO - Return a reply to the host.
}

#endif // FSC_DEBUG
