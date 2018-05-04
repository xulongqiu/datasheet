
#include "PlatformI2C.h"

#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_i2c.h"

#ifndef I2C1_TIMEOUT_MAX
#define I2C1_TIMEOUT_MAX 0xFFFF
#endif

I2C_HandleTypeDef I2cHandle;

void InitializeI2C(void)
{
    // Initialize the I2C GPIO Pins
    GPIO_InitTypeDef  GPIO_InitStruct;

    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_I2C1_CLK_ENABLE();

    GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;

    GPIO_InitStruct.Pin       = GPIO_PIN_8 | GPIO_PIN_9;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // Initialize the I2C Peripheral!
    // On the STM32F746B_DISCO Board we are going to use:
    // I2C Unit 1
    // SCL: Port B Pin 8
    // SDA: Port B Pin 9
    // Timing:
    //	From Example Code:		0x40912732 for 100k @ 48MHz		TODO???
    //	From Excel Tool:		0x10805E89 for 100k @ 48MHz		TODO???
    //	From Excel Tool:		0x00901850 for 400k @ 48MHz		TODO???
    //	From STM32CubeMX Tool:	0x00401A58 for 400k @ 48MHz
    I2cHandle.Instance             	= I2C1;

    I2cHandle.Init.AddressingMode  	= I2C_ADDRESSINGMODE_7BIT;
    I2cHandle.Init.Timing          	= 0x00401A58;
    I2cHandle.Init.DualAddressMode 	= I2C_DUALADDRESS_DISABLED;
    I2cHandle.Init.OwnAddress1     	= 0;
    I2cHandle.Init.OwnAddress2     	= 0;
    I2cHandle.Init.OwnAddress2Masks	= I2C_OA2_NOMASK;
    I2cHandle.Init.GeneralCallMode 	= I2C_GENERALCALL_DISABLED;
    I2cHandle.Init.NoStretchMode   	= I2C_NOSTRETCH_DISABLED;

    HAL_I2C_Init(&I2cHandle);

    /**Configure Analogue filter */
    HAL_I2CEx_AnalogFilter_Config(&I2cHandle, I2C_ANALOGFILTER_ENABLE);
}

FSC_BOOL platform_i2c_write(FSC_U8 SlaveAddress,
                            FSC_U8 RegAddrLength,
                            FSC_U8 DataLength,
                            FSC_U8 PacketSize,
                            FSC_U8 IncSize,
                            FSC_U32 RegisterAddress,
                            FSC_U8* Data)
{
    HAL_StatusTypeDef result = HAL_OK;

    result = HAL_I2C_Mem_Write( &I2cHandle, SlaveAddress, RegisterAddress, RegAddrLength,
                                      Data, DataLength, I2C1_TIMEOUT_MAX );

    return ((result == HAL_OK) ? FALSE : TRUE);
}

FSC_BOOL platform_i2c_read( FSC_U8 SlaveAddress,
                            FSC_U8 RegAddrLength,
                            FSC_U8 DataLength,
                            FSC_U8 PacketSize,
                            FSC_U8 IncSize,
                            FSC_U32 RegisterAddress,
                            FSC_U8* Data)
{
    HAL_StatusTypeDef result = HAL_OK;

    result = HAL_I2C_Mem_Read( &I2cHandle, SlaveAddress, RegisterAddress, RegAddrLength,
                                     Data, DataLength, I2C1_TIMEOUT_MAX );

    return ((result == HAL_OK) ? FALSE : TRUE);
}
