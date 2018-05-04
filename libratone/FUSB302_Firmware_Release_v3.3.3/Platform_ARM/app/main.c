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
#include "usbd_main.h"
#endif // FSC_DEBUG

#include "FSCTypes.h"

#include "../../core/core.h"

#include "stm32f0xx.h"
#include "stm32f0xx_hal.h"
#include "stm32f0xx_hal_rcc.h"
#include "stm32f0xx_hal_flash.h"

static void SystemClock_Config(void);
static void Error_Handler(void);

static void InitializeSystem( void );
static void InitializeBoard( void );

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
    HAL_Init();

    SystemClock_Config();

    // Initialize the GPIO pins
    InitializeGPIO();

    // Initialize the I2C interface
    InitializeI2C();

#ifdef FSC_DEBUG
    // Initialize the USB interface
    InitializeUSB();
#endif // FSC_DEBUG
}

/*******************************************************************************
 * Function:        SystemClock_Config
 * Input:           None
 * Return:          None
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSI48)
 *            SYSCLK(Hz)                     = 48000000
 *            HCLK(Hz)                       = 48000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 1
 *            HSI Frequency(Hz)              = 48000000
 *            PREDIV                         = 2
 *            PLLMUL                         = 2
 *            Flash Latency(WS)              = 1
 *****************************************************************************/
static void SystemClock_Config(void)
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;
    RCC_CRSInitTypeDef RCC_CRSInitStruct;

    /* Select HSI48 Oscillator as PLL source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
    RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI48;
    RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV2;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
    {
        Error_Handler();
    }

    /* Select HSI48 as USB clock source */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USB;
    PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

    /* Select PLL as system clock source and configure the HCLK and PCLK1 clocks dividers */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1)!= HAL_OK)
    {
        Error_Handler();
    }

    /*Configure the clock recovery system (CRS)**********************************/
    /*Enable CRS Clock*/
    __HAL_RCC_CRS_CLK_ENABLE();

    /* Default Synchro Signal division factor (not divided) */
    RCC_CRSInitStruct.Prescaler = RCC_CRS_SYNC_DIV1;

    /* Set the SYNCSRC[1:0] bits according to CRS_Source value */
    RCC_CRSInitStruct.Source = RCC_CRS_SYNC_SOURCE_USB;

    /* HSI48 is synchronized with USB SOF at 1KHz rate */
    RCC_CRSInitStruct.ReloadValue =  __HAL_RCC_CRS_CALCULATE_RELOADVALUE(48000000, 1000);
    RCC_CRSInitStruct.ErrorLimitValue = RCC_CRS_ERRORLIMIT_DEFAULT;

    /* Set the TRIM[5:0] to the default value*/
    RCC_CRSInitStruct.HSI48CalibrationValue = 0x20;

    /* Start automatic synchronization */
    HAL_RCCEx_CRSConfig (&RCC_CRSInitStruct);

    __HAL_RCC_PWR_CLK_ENABLE();
}

static void Error_Handler(void)
{
    /* User may add here some code to deal with this error */
    while(1)
    {
    }
}
