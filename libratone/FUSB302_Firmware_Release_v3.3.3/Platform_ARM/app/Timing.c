#include "Timing.h"

#include "core/core.h"
#include "stm32f0xx_hal.h"

FSC_U16 volatile g_timer;

TIM_HandleTypeDef TimeHandle;

void InitializeCoreTimer( void )
{
    // Initialize a 0.1ms tick timer!
    __TIM2_CLK_ENABLE();

    TimeHandle.Instance = TIM2;

    // SystemCoreClock is 48MHz.
    // A prescaler of 480 gives 1us resolution for a period of 1ms
    TimeHandle.Init.Period            = 100;
    TimeHandle.Init.Prescaler         = (uint32_t)(480);
    TimeHandle.Init.ClockDivision     = 0;
    TimeHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;
    TimeHandle.Init.RepetitionCounter = 0;

    HAL_TIM_Base_Init(&TimeHandle);

    HAL_TIM_Base_Start_IT(&TimeHandle);

    HAL_NVIC_SetPriority(TIM2_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);

    g_timer = 0;
}

void EnableCoreTimer( FSC_BOOL blnEnable )
{
    if( blnEnable )
    {
        HAL_NVIC_EnableIRQ(TIM2_IRQn);
    }
    else
    {
        HAL_NVIC_DisableIRQ(TIM2_IRQn);
    }
}

void platform_enable_timer(FSC_BOOL enable)
{
    EnableCoreTimer( enable );
}

// CoreTimerHandler
void TIM2_IRQHandler(void)
{
    __HAL_TIM_CLEAR_IT(&TimeHandle, TIM_IT_UPDATE);

    g_timer++;
}

FSC_U16 get_system_time(void)
{
    return g_timer;
}
