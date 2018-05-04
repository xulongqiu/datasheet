#include "PlatformI2C.h"
#include "string.h"
#include "GenericTypeDefs.h"
#include "I2CPrivate.h"
#include "HardwareProfile.h"
#include "Timing.h"

/************************************************************
 * Function:        I2C_Init
 * Input:           None
 * Return:          None
 * Description:     Initializes the two I2C peripherals
 ************************************************************/
void I2C_Init(I2C_MODULE module, FSC_U32 frequency, FSC_BOOL enable)
{
    I2C_REGISTERS * const i2cRegisters = i2cBase[module];               // Get a pointer to the baud rate generator address
    i2cRegisters->I2CxCON = 0x0000;                                     // Reinitialize the module to the default configuration
    I2CSetFrequency(module, GetPeripheralClock(), frequency);           // Set the I2C frequency for the module
    i2cRegisters->I2CxCONbits.ON = enable;                              // Enable the module if requested
}

FSC_BOOL I2C_GetEnable(I2C_MODULE module)
{
    I2C_REGISTERS * const i2cRegisters = i2cBase[module];               // Get a pointer to the baud rate generator address
    return i2cRegisters->I2CxCONbits.ON;
}

FSC_U32 I2C_GetFrequency(I2C_MODULE module)
{
    I2C_REGISTERS * const i2cRegisters = i2cBase[module];               // Get a pointer to the baud rate generator address
 	return( ( GetPeripheralClock()/(i2cRegisters->I2CxBRG + 2) ) / 2 ); // Return the actual I2C frequency
}

void I2C_Reset_FCS(I2C_MODULE module)
{
    I2CEnable(module, FALSE);
    Nop();
    I2CEnable(module, TRUE);
    Nop();
}

FSC_BOOL I2C_BusIdle(I2C_MODULE module)
{
    FSC_BOOL Success = TRUE;
    InitializeTOTimer(TRUE, 3125);                  // Initialize the TO timer to expire after 10ms
    while (!I2CBusIsIdle(module))                   // Wait for the bus to be idle
    {
        if (mT4GetIntFlag())                        // If we timeout, return that there was an error
        {
            Success = FALSE;                        // Signal an error occurred during the start...
            I2C_Reset_FCS(module);                  // Reset the module
            break;
        }
        DisableTOTimer();                           // Stop the timer
    }
    return Success;
}

FSC_BOOL I2C_Start(I2C_MODULE module)
{
    FSC_BOOL Success;
    Success = I2C_BusIdle(module);                  // Wait for the bus to be idle
    if (Success)                                    // If the bus is idle...
    {
        if (I2CStart(module) != I2C_SUCCESS)        // Attempt to initate a start condition
        {
            I2C_Reset_FCS(module);                  // Reset the module
            return FALSE;
        }
        InitializeTOTimer(TRUE, 313);               // Initialize the TO timer to expire after 1ms
        while ((I2CGetStatus(module) & I2C_START) == 0) // Wait for the start condition to be detected
        {
            if (mT4GetIntFlag())                    // If we timeout, return that there was an error
            {
                Success = FALSE;                    // Signal an error occurred during the start...
                I2C_Reset_FCS(module);              // Reset the module
                break;
            }     
        }
        DisableTOTimer();                           // Stop the timer
    }
    return Success;
}

FSC_BOOL I2C_Restart(I2C_MODULE module)
{
    FSC_BOOL Success = TRUE;
    if (I2CRepeatStart(module) != I2C_SUCCESS)      // Attempt to initate a start condition
        return FALSE;
    InitializeTOTimer(TRUE, 313);                   // Initialize the TO timer to expire after 1ms
    while ((I2CGetStatus(module) & I2C_START) == 0) // Wait for the start condition to be detected
    {
        if (mT4GetIntFlag())                        // If we timeout, return that there was an error
        {
            Success = FALSE;                        // Signal an error occurred during the start...
            I2C_Reset_FCS(module);                  // Reset the module
            break;
        }     
    }
    DisableTOTimer();                           // Stop the timer
    return Success;
}

FSC_BOOL I2C_Stop(I2C_MODULE module)
{
    FSC_BOOL Success = TRUE;
    I2CStop(module);                                // Attempt to initate a stop condition
    InitializeTOTimer(TRUE, 313);                   // Initialize the TO timer to expire after 1ms
    while ((I2CGetStatus(module) & I2C_STOP) == 0)  // Wait for the start condition to be detected
    {
        if (mT4GetIntFlag())                        // If we timeout, return that there was an error
        {
            Success = FALSE;                        // Signal an error occurred during the start...
            I2C_Reset_FCS(module);                  // Reset the module
            break;
        }
    }
    DisableTOTimer();                           // Stop the timer
    return Success;
}

I2C_ERROR_t I2C_TransmitByte(I2C_MODULE module, FSC_U8 data)
{
    InitializeTOTimer(TRUE, 3125);                              // Initialize the TO timer to expire after 10ms
    while (!I2CTransmitterIsReady(module))                      // Loop until the transmitter is ready or we timeout
    {
        if (mT4GetIntFlag())                                    // If we timeout, return that there was an error
        {
            DisableTOTimer();                                   // Stop the timer
            I2C_Reset_FCS(module);                              // Reset the module
            return I2C_HWERROR;                                 // Abort the operation and return that there was an error
        }
    }
    if (I2CSendByte(module, data) == I2C_MASTER_BUS_COLLISION)  // Attempt to start a transmission
    {
        I2C_Reset_FCS(module);                                  // Reset the module
        return I2C_HWERROR;                                     // If there was a bus collision, return that there was a hardware error
    }
    InitializeTOTimer(TRUE, 31250);                             // Initialize the TO timer to expire after 100ms
    while(!I2CTransmissionHasCompleted(module))                 // Loop until the transmission is complete or we timeout
    {
        if (mT4GetIntFlag())                                    // If we timeout, return that there was an error
        {
            DisableTOTimer();                                   // Stop the timer
            I2C_Reset_FCS(module);                              // Reset the module
            return I2C_HWERROR;                                 // Abort the operation and return that there was an error
        }
    }
    DisableTOTimer();                           // Stop the timer
    if (!I2CByteWasAcknowledged(module))                        // Check to see if the byte as acknowledged
    {
        I2C_Stop(module);                                       // Send a stop condition to make sure the bus is in the correct state
        return I2C_NOACK;                                       // Otherwise return that we received a NACK
    }
    return I2C_NOERROR;                                         // If it was, return that there was no error     
}

I2C_ERROR_t I2C_ReceiveByte(I2C_MODULE module, FSC_U8* data, FSC_BOOL acknowledge)
{
    if (I2CReceiverEnable(module, TRUE) == I2C_RECEIVE_OVERFLOW)    // Enable the receiver to receive a byte
    {
        I2C_Reset_FCS(module);                                      // Reset the module
        return I2C_HWERROR;                                         // If there was an overflow, report the error
    }
    InitializeTOTimer(TRUE, 31250);                                 // Initialize the TO timer to expire after 100ms
    while(!I2CReceivedDataIsAvailable(module))                      // Loop until we have data ready or we timeout
    {
        if (mT4GetIntFlag())                                        // If we timeout, return that there was an error
        {
            DisableTOTimer();                                       // Stop the timer
            I2C_Reset_FCS(module);                                  // Reset the module
            return I2C_HWERROR;                                     // Abort the operation and return that there was an error
        }
    }
    *data = I2CGetByte(module);                                     // Grab the byte from the buffer
    I2CAcknowledgeByte(module, acknowledge);                        // Attempt to ACK/NACK the received byte
    InitializeTOTimer(TRUE, 3125);                                  // Initialize the TO timer to expire after 10ms
    while(!I2CAcknowledgeHasCompleted(module))                      // Loop until the acknowledge sequence has completed or we timeout
    {
        if (mT4GetIntFlag())                                        // If we timeout, return that there was an error
        {
            DisableTOTimer();                                       // Stop the timer
            I2C_Reset_FCS(module);                                  // Reset the module
            return I2C_HWERROR;                                     // Abort the operation and return that there was an error
        }
    }
    DisableTOTimer();                                               // Stop the timer
    return I2C_NOERROR;                                             // If we have made it here, everything was good!
}

I2C_ERROR_t I2C_WriteData(I2C_MODULE module,
                        FSC_U8 SlaveAddress,
                        FSC_U8 RegAddrLength,
                        FSC_U8 DataLength,
                        FSC_U8 PacketSize,
                        FSC_U8 IncSize,
                        FSC_U32 RegisterAddress,
                        FSC_U8* Data)
{
    FSC_U8 count, increment;
    FSC_U32 address;
    I2C_ERROR_t status;

    increment = IncSize;                                                    // Initialize the increment counter
    do {
        if (!I2C_Start(module))                                             // Attempt to start...
            return I2C_HWERROR;                                             // If we were unable, return that there was a hardware error
        status = I2C_TransmitByte(module, SlaveAddress);                    // Attempt to send the slave address byte
        if (status != I2C_NOERROR)                                          // If we were successful...
            return status;                                                  // Get out of here, the Transmit routine handled the cleanup
        address = RegisterAddress;                                          // Load the next address to send
        for (count=0; count<RegAddrLength; count++)
        {
            status = I2C_TransmitByte(module, (FSC_U8) (address & 0xFF));    // Attempt to send each of the register address bytes
            if (status != I2C_NOERROR)                                      // If we weren't successful...
                return status;                                              // Get out of here, the Transmit routine handled the cleanup
            address >>= 8;                                                  // Shift the address to be ready for the next byte
        }
        if (PacketSize > DataLength)
            PacketSize = DataLength;
        for (count=0; count<PacketSize; count++)
        {
            if (DataLength ==0)                                             // If we don't have any more data to send...
                break;                                                      // Get out of this loop
            status = I2C_TransmitByte(module, *Data++);                     // Attempt to send the next byte...
            if (status != I2C_NOERROR)                                      // If we weren't successful...
                return status;                                              // Get out of here, the Transmit routine handled the cleanup
            DataLength--;                                                   // Update the number of bytes remaining
            increment--;                                                    // Update the increment counter
            if (!increment)                                                 // If the increment counter is still greater than 0
            {
                RegisterAddress++;                                          // Update the register address
                increment = IncSize;                                        // Reset the increment counter
            }
        }
        if (!I2C_Stop(module))                                              // Attempt to issue a stop at the end of the packet
            return I2C_HWERROR;                                             // Return that there was a hardware error if unsuccessful
    } while (DataLength > 0);                                               // Loop around as long as we have data
    return I2C_NOERROR;                                                     // If we made it here, we were successful!
}

I2C_ERROR_t I2C_ReadData(I2C_MODULE module,
                        FSC_U8 SlaveAddress,
                        FSC_U8 RegAddrLength,
                        FSC_U8 DataLength,
                        FSC_U8 PacketSize,
                        FSC_U8 IncSize,
                        FSC_U32 RegisterAddress,
                        FSC_U8* Data)
{
    FSC_U8 count, increment;
    FSC_U32 address;
    FSC_BOOL acknowledge;
    I2C_ERROR_t status;
    increment = IncSize;                                                    // Initialize the increment counter
    do {
        if (!I2C_Start(module))                                             // Attempt to start...
            return I2C_HWERROR;                                             // If we were unable, return that there was a hardware error
        status = I2C_TransmitByte(module, SlaveAddress);                    // Attempt to send the slave address byte
        if (status != I2C_NOERROR)                                          // If we weren't successful...
            return status;                                                  // Get out of here, the Transmit routine handled the cleanup
        address = RegisterAddress;                                          // Load the next address to send
        for (count=0; count<RegAddrLength; count++)
        {
            status = I2C_TransmitByte(module, (FSC_U8) (address & 0xFF));    // Attempt to send each of the register address bytes
            if (status != I2C_NOERROR)                                      // If we weren't successful...
                return status;                                              // Get out of here, the Transmit routine handled the cleanup
            address >>= 8;                                                  // Shift the address to be ready for the next byte
        }
        if (!I2C_Restart(module))                                           // Attempt to restart for reading the data
            return I2C_HWERROR;
        status = I2C_TransmitByte(module, SlaveAddress | 0x01);             // Attempt to send the slave address with the read bit set
        if (status != I2C_NOERROR)                                          // If we weren't successful
            return status;                                                  // Get out of here, the Transmit routine handled the cleanup
        acknowledge = TRUE;                                                 // Set the acknowledge flag to true for all bytes in each packet by default
        if (DataLength < PacketSize)                                        // If the data length is less than the packet size...
            PacketSize = DataLength;                                        // Set the packet size equal to the data length, since that is how we exit
        for (count=0; count<PacketSize; count++)
        {
            if (count == PacketSize - 1)                                    // If this is the last byte to send...
                acknowledge = FALSE;                                        // Don't acknowledge the byte read to indicate to the slave the end of data
            status = I2C_ReceiveByte(module, Data, acknowledge);            // Attempt to read the next byte...
            if (status != I2C_NOERROR)                                      // If we weren't successful...
                return status;                                              // Get out of here, the Receive routine handled the cleanup
            Data++;                                                        // Increment the pointer to the next data byte
            DataLength--;                                                   // Update the number of bytes remaining
            increment--;                                                    // Update the increment counter
            if (!increment)                                                 // If the increment counter is still greater than 0
            {
                RegisterAddress++;                                          // Update the register address
                increment = IncSize;                                        // Reset the increment counter
            }
        }
        if (!I2C_Stop(module))                                              // Attempt to issue a stop at the end of the packet
            return I2C_HWERROR;                                             // Return that there was a hardware error if unsuccessful
    } while (DataLength > 0);                                               // Loop around as long as there is data to read
    return I2C_NOERROR;                                                     // If we got here, we were successful!
}