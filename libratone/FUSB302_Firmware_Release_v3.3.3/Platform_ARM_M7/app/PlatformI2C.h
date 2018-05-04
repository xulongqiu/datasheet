/* 
* File:   PlatformI2C.h
* Author: micsmith
*
* Created on October 17, 2014, 1:28 PM
*/

#ifndef _PLATFORMI2C_H_
#define	_PLATFORMI2C_H_

#include "FSCTypes.h"

typedef enum _I2C_ERROR
{
  I2C_NOERROR,
  I2C_INVALIDMODULE,
  I2C_INVALIDADDRLENGTH,
  I2C_INVALIDDATALENGTH,
  I2C_NOACK,
  I2C_HWERROR,
  I2C_MODULEDISABLED,
} I2C_ERROR_t;

#define I2C_NUMBER_OF_MODULES 1

/*******************************************************************************
 * Function:        InitializeI2C
 * Input:           None
 * Return:          None
 * Description:     Initialize and (optionally) enable the I2C peripheral.
 ******************************************************************************/
void InitializeI2C(void);

/*******************************************************************************
 * Function:        platform_i2c_write
 * Input:           SlaveAddress - Slave device bus address
 *                  RegAddrLength - Register Address Byte Length
 *                  DataLength - Length of data to transmit
 *                  PacketSize - Maximum size of each transmitted packet
 *                  IncSize - Number of bytes to send before incrementing addr
 *                  RegisterAddress - Internal register address
 *                  Data - Buffer of char data to transmit
 * Return:          Error state
 * Description:     Write a char buffer to the I2C peripheral.
 ******************************************************************************/
FSC_BOOL platform_i2c_write(FSC_U8 SlaveAddress,
                            FSC_U8 RegAddrLength,
                            FSC_U8 DataLength,
                            FSC_U8 PacketSize,
                            FSC_U8 IncSize,
                            FSC_U32 RegisterAddress,
                            FSC_U8* Data);

/*******************************************************************************
 * Function:        platform_i2c_read
 * Input:           SlaveAddress - Slave device bus address
 *                  RegAddrLength - Register Address Byte Length
 *                  DataLength - Length of data to attempt to read
 *                  PacketSize - Maximum size of each received packet
 *                  IncSize - Number of bytes to recv before incrementing addr
 *                  RegisterAddress - Internal register address
 *                  Data - Buffer for received char data
 * Return:          Error state.
 * Description:     Read char data from the I2C peripheral.
 ******************************************************************************/
FSC_BOOL platform_i2c_read( FSC_U8 SlaveAddress,
                            FSC_U8 RegAddrLength,
                            FSC_U8 DataLength,
                            FSC_U8 PacketSize,
                            FSC_U8 IncSize,
                            FSC_U32 RegisterAddress,
                            FSC_U8* Data);

#endif // _PLATFORMI2C_H_

