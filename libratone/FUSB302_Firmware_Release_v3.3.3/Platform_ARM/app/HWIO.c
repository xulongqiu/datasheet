#include "HWIO.h"

#include "../../core/platform.h"

#include "stm32f0xx_hal.h"
#include "stm32f0xx_hal_gpio.h"

#define INT_N_PORT      GPIOA
#define INT_N_PIN       GPIO_PIN_1

#define VBUS_PORT       GPIOC
#define VBUS_5V_PIN     GPIO_PIN_3
#define VBUS_12V_PIN    GPIO_PIN_4

void InitializeGPIO( void )
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    // * Outputs (VBUS Controls, etc.) on Port C
    __GPIOC_CLK_ENABLE();

    // Configure IOs in output push-pull mode to drive VBUS outputs
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;

    GPIO_InitStruct.Pin = VBUS_5V_PIN;
    HAL_GPIO_Init(VBUS_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = VBUS_12V_PIN;
    HAL_GPIO_Init(VBUS_PORT, &GPIO_InitStruct);
    
    // * Inputs (INT_N) on Port A
    __GPIOA_CLK_ENABLE();

    // INT_N setup...
#ifdef FSC_INTERRUPT_TRIGGERED
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
#else // FSC_POLLING
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
#endif // FSC_INTERRUPT_TRIGGERED

    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Pin = INT_N_PIN;
    HAL_GPIO_Init(INT_N_PORT, &GPIO_InitStruct);
  
    // Enable and set EXTI line 0 Interrupt
#ifdef FSC_INTERRUPT_TRIGGERED
    HAL_NVIC_SetPriority(EXTI0_1_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);
#endif // FSC_INTERRUPT_TRIGGERED
}

void platform_set_vbus_lvl_enable( VBUS_LVL level, FSC_BOOL blnEnable, FSC_BOOL blnDisableOthers )
{
    unsigned int i;

    // Additional VBUS levels can be added here as needed.
    switch (level) {
    case VBUS_LVL_5V:
        // Enable/Disable the 5V Source
        HAL_GPIO_WritePin( VBUS_PORT, VBUS_5V_PIN,
                           blnEnable ? GPIO_PIN_SET : GPIO_PIN_RESET );
        break;
    case VBUS_LVL_12V:
        // Enable/Disable the 12V Source
        HAL_GPIO_WritePin( VBUS_PORT, VBUS_12V_PIN,
                           blnEnable ? GPIO_PIN_SET : GPIO_PIN_RESET );
        break;
    default:
        // Otherwise, do nothing.
        break;
    }

    // Turn off other levels, if requested
    if (blnDisableOthers || ((level == VBUS_LVL_ALL) && (blnEnable == FALSE)))
    {
        i = 0;

        do {
            // Skip the current level
            if( i == level ) continue;

            // Turn off the other level(s)
            platform_set_vbus_lvl_enable( (VBUS_LVL)i, FALSE, FALSE );
        } while (++i < VBUS_LVL_COUNT);
    }
}

FSC_BOOL platform_get_vbus_lvl_enable( VBUS_LVL level )
{
    GPIO_PinState state = GPIO_PIN_RESET;

    // Additional VBUS levels can be added here as needed.
    switch (level) {
    case VBUS_LVL_5V:
        // Return the state of the 5V VBUS Source.
        state = HAL_GPIO_ReadPin( VBUS_PORT, VBUS_5V_PIN );

        break;
    case VBUS_LVL_12V:
        // Return the state of the 12V VBUS Source.
        state = HAL_GPIO_ReadPin( VBUS_PORT, VBUS_12V_PIN );

        break;
    default:
        // Otherwise, return FALSE.
        break;
    }

    return (state == GPIO_PIN_SET) ? TRUE : FALSE;
}

void platform_set_vbus_discharge(FSC_BOOL blnEnable)
{
    // Enable/Disable the discharge path
    // TODO - Implement as needed on platforms that support this feature.
}

FSC_BOOL platform_get_device_irq_state( void )
{
    // Return the state of the device interrupt signal.
    // Port A, GPIO_PIN_1 -- ACTIVE LOW!
    return HAL_GPIO_ReadPin(INT_N_PORT, INT_N_PIN) ? FALSE : TRUE;
}

#ifdef FSC_INTERRUPT_TRIGGERED

void EnableExtIRQ(FSC_BOOL enable)
{
    if( enable )
    {
        HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);
    }
    else
    {
        HAL_NVIC_DisableIRQ(EXTI0_1_IRQn);
    }
}

extern FSC_BOOL haveINTReady;

void HAL_GPIO_EXTI_Callback( FSC_U16 pin )
{
    if( pin == GPIO_PIN_1 )
    {
        haveINTReady = TRUE;
    }
}
#endif // FSC_INTERRUPT_TRIGGERED
