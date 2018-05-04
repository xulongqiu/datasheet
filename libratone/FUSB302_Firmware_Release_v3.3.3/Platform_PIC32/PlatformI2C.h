/* 
 * File:   FCS_I2C.h
 * Author: micsmith
 *
 * Created on October 17, 2014, 1:28 PM
 */

#ifndef _PLATFORM_I2C_H_
#define	_PLATFORM_I2C_H_

#include <Peripheral/i2c.h>
#define FUSB300I2CMod      0        // First I2C Module


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


// Function prototypes
void I2C_Init(I2C_MODULE module, FSC_U32 frequency, FSC_BOOL enable);
FSC_BOOL I2C_GetEnable(I2C_MODULE module);
FSC_U32 I2C_GetFrequency(I2C_MODULE module);
void I2C_Reset_FCS(I2C_MODULE module);
FSC_BOOL I2C_BusIdle(I2C_MODULE module);
FSC_BOOL I2C_Start(I2C_MODULE module);
FSC_BOOL I2C_Restart(I2C_MODULE module);
FSC_BOOL I2C_Stop(I2C_MODULE module);
I2C_ERROR_t I2C_TransmitByte(I2C_MODULE module, FSC_U8 data);
I2C_ERROR_t I2C_ReceiveByte(I2C_MODULE module, FSC_U8* data, FSC_BOOL acknowledge);
I2C_ERROR_t I2C_WriteData(I2C_MODULE module, FSC_U8 SlaveAddress, FSC_U8 RegAddrLength, FSC_U8 DataLength, FSC_U8 PacketSize, FSC_U8 IncSize, FSC_U32 RegisterAddress, FSC_U8* Data);
I2C_ERROR_t I2C_ReadData(I2C_MODULE module, FSC_U8 SlaveAddress, FSC_U8 RegAddrLength, FSC_U8 DataLength, FSC_U8 PacketSize, FSC_U8 IncSize, FSC_U32 RegisterAddress, FSC_U8* Data);


#endif	/* _PLATFORM_I2C_H_ */

