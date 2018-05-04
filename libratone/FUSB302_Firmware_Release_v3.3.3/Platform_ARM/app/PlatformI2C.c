
#include "PlatformI2C.h"

#include "stm32f0xx_hal.h"
#include "stm32f0xx_hal_i2c.h"

#ifndef I2C1_TIMEOUT_MAX
#define I2C1_TIMEOUT_MAX 0xFFFF
#endif

I2C_HandleTypeDef I2cHandle;

void InitializeI2C(void)
{
    // Initialize the I2C GPIO Pins
    GPIO_InitTypeDef  GPIO_InitStruct;

    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_I2C2_CLK_ENABLE();

    GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_I2C2;

    GPIO_InitStruct.Pin       = GPIO_PIN_10;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // Initialize the I2C Peripheral!
    // On the STM32F072B_DISCO Board we are going to use:
    // I2C Unit 2
    // SCL: Port B Pin 10
    // SDA: Port B Pin 11
    // Timing:
    //   From STM32Cube: 0x10805D88 for 100kHz @ 48MHz (Rise time = 100 ns, Fall time = 100 ns)
    //   From STM32Cube: 0x0090194B for 400kHz @ 48MHz (Rise time = 100 ns, Fall time = 100 ns)
    //   From STM32Cube: 0x00700814 for 1Mhz @ 48MHz (Rise time = 100 ns, Fall time = 100 ns)
    I2cHandle.Instance             = I2C2;

    I2cHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
    I2cHandle.Init.Timing          = 0x0090194B;
    I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
    I2cHandle.Init.OwnAddress1     = 0;
    I2cHandle.Init.OwnAddress2     = 0;
    I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
    I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLED;

    HAL_I2C_Init(&I2cHandle);
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
