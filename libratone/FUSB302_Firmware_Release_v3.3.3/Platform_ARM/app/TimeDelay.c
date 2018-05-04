
#include "TimeDelay.h" 

#include "FSCTypes.h"
#include "stm32f0xx_hal.h"

TIM_HandleTypeDef DelayTimeHandle;

void InitializeDelay( void )
{
    __TIM3_CLK_ENABLE();

    DelayTimeHandle.Instance = TIM3;

    // SystemCoreClock is 48MHz.
    // A prescaler of 48 gives 1us resolution.
    // A period of FFFF just allows the timer to free run.
    DelayTimeHandle.Init.Period            = 0xFFFF;
    DelayTimeHandle.Init.Prescaler         = (uint32_t)(48);
    DelayTimeHandle.Init.ClockDivision     = 0;
    DelayTimeHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;
    DelayTimeHandle.Init.RepetitionCounter = 0;

    HAL_TIM_Base_Init(&DelayTimeHandle);

    HAL_TIM_Base_Start_IT(&DelayTimeHandle);
}

void platform_delay_10us( FSC_U32 tenMicroSecondCounter )
{
    // We are using a 1us timer, so get the number of us to delay.
    FSC_U32 countTime = tenMicroSecondCounter * 10;

    // Limit the delay to a 16-bit value to prevent dealing with roll-over.
    if( countTime > 0xFFF0 ) countTime = 0xFFF0;

    // Clear the free-running counter.
    __HAL_TIM_SetCounter(&DelayTimeHandle, 0);

    // Watch the counter and wait until we've reached our delay time.
    while( countTime > __HAL_TIM_GetCounter(&DelayTimeHandle) ) continue;

    return;
}
