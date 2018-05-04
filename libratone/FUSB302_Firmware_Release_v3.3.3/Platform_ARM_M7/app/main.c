/*****************************************************************************
 * FileName:        Main.c
 * Processor:       ARM M0
 * Compiler:
 * Company:         Fairchild Semiconductor
 *****************************************************************************/

#include "HWIO.h"
#include "TimeDelay.h"
#include "Timing.h"
#include "PlatformI2C.h"

#ifdef FSC_DEBUG
//#include "usbd_main.h"
#endif // FSC_DEBUG

#include "FSCTypes.h"

#include "../../core/core.h"

#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_rcc.h"
#include "stm32f7xx_hal_flash.h"

static void SystemClock_Config(void);
static void Error_Handler(void);

static void InitializeSystem( void );
static void InitializeBoard( void );

static void MPU_Config(void);
static void CPU_CACHE_Enable(void);

#ifdef FSC_INTERRUPT_TRIGGERED
volatile FSC_BOOL haveINTReady = FALSE;
#endif // FSC_INTERRUPT_TRIGGERED

#ifdef FSC_DEBUG
volatile FSC_BOOL haveUSBInMsg = FALSE;
#endif // FSC_DEBUG

/*******************************************************************************
 * Function:        main
 * Input:           None
 * Return:          None
 * Description:     Program entry point and container of main loop
 ******************************************************************************/

int main( void )
{
    InitializeSystem();

    while (1)
    {
        // Run the Type-C state machine
#ifdef FSC_INTERRUPT_TRIGGERED
        if( haveINTReady
#ifdef FSC_DEBUG
            || haveUSBInMsg
#endif // FSC_DEBUG
        )
        {
            haveINTReady = FALSE;
#ifdef FSC_DEBUG
            haveUSBInMsg = FALSE;
#endif // FSC_DEBUG

            core_state_machine();

            // It is possible for the state machine to go into idle mode with
            // the interrupt pin still low and as a result the edge-sensitive
            // IRQ won't get triggered.  Check here before returning to wait
            // on the IRQ.
            if( platform_get_device_irq_state() )
            {
                haveINTReady = TRUE;
            }
        }
#else // FSC_POLLING
        core_state_machine();
#endif // FSC_INTERRUPT_TRIGGERED
    }
}


/*******************************************************************************
 * Function:        static void InitializeSystem(void)
 * Input:           None
 * Return:          None
 * Description:     InitializeSystem is a centralize initialization routine.
 ******************************************************************************/
static void InitializeSystem(void)
{
    InitializeBoard();
    InitializeDelay();

    InitializeCoreTimer();

    core_initialize();

    core_enable_typec( TRUE );  // Enable the state machine by default
}

/*******************************************************************************
 * Function:        InitializeBoard()
 * Input:           None
 * Return:          None
 * Description:     Initializes the hardware components.
 ******************************************************************************/
static void InitializeBoard( void )
{
    MPU_Config();
    CPU_CACHE_Enable();

	HAL_Init();

    SystemClock_Config();

    // Initialize the GPIO pins
    InitializeGPIO();

    // Initialize the I2C interface
    InitializeI2C();

#ifdef FSC_DEBUG
    // Initialize the USB interface
//    InitializeUSB();
#endif // FSC_DEBUG
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 96000000
  *            HCLK(Hz)                       = 48000000
  *            AHB Prescaler                  = 2
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 16000000
  *            PLL_M                          = 16
  *            PLL_N                          = 192
  *            PLL_P                          = RCC_PLLP_DIV2
  *            PLL_Q                          = 2
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 7
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;

  __PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /* Enable HSI Oscillator and activate PLL with HSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;

  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }

  /* Activate the OverDrive to reach the 96 MHz Frequency */
  ret = HAL_PWREx_EnableOverDrive();
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }

  /* Select PCLK1 as I2C1 clock source */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  ret = HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/**
  * @brief  I2C error callbacks.
  * @param  I2cHandle: I2C handle
  * @note   This example shows a simple way to report transfer error, and you can
  *         add your own implementation.
  * @retval None
  */
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *I2cHandle)
{
  Error_Handler();
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* Error if LED1 is slowly blinking (1 sec. period) */
  while(1)
  {
//    BSP_LED_Toggle(LED1);
    HAL_Delay(1000);
  }
}

/**
  * @brief  Configure the MPU attributes as Write Through for SRAM1/2.
  * @note   The Base Address is 0x20010000 since this memory interface is the AXI.
  *         The Region Size is 256KB, it is related to SRAM1 and SRAM2  memory size.
  * @param  None
  * @retval None
  */
static void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct;

  /* Disable the MPU */
  HAL_MPU_Disable();

  /* Configure the MPU attributes as WT for SRAM */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x20010000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_256KB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Enable the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

/**
  * @brief  CPU L1-Cache enable.
  * @param  None
  * @retval None
  */
static void CPU_CACHE_Enable(void)
{
  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}
