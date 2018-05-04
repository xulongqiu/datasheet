#include "Timing.h"
#include "../core/core.h"

void InitializeTypeCTimer( void )
{
    // TODO - Initialize a 1ms tick timer!
}

void EnableTypeCTimer( BOOL blnEnable )
{
    if( blnEnable )
    {
        // TODO - Start the timer
    }
    else
    {
        // TODO - Stop the timer
    }
}

void TypeCTimerHandler(void)
{
    TypeCTickAt100us();
    ProtocolTickAt100us();
    PolicyTickAt100us();

    // TODO - Reset the interrupt.
}

void InitializeTimestampTimer( void )
{
    // TODO - Initialize a 0.1ms tick timer!
}

void EnableTimestampTimer( BOOL blnEnable )
{
    if( blnEnable )
    {
        // TODO - Start the timer
    }
    else
    {
        // TODO - Stop the timer
    }
}

void TimestampTimerHandler(void)
{
    TickAt100us();

    // TODO - Reset the interrupt.
}
