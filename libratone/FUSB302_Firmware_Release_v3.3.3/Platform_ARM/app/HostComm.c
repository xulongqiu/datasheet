/****************************************************************************
 * FileName:            HostComm.c
 * Processor:           ARM M0
 * Compiler:
 * Company:             Fairchild Semiconductor
 *****************************************************************************/
#ifdef FSC_DEBUG

#include "HostComm.h"
#include "PlatformI2C.h"
#include "../../core/core.h"

void ProcessMsg( FSC_U8* inMsgBuffer, FSC_U8* outMsgBuffer )
{
    FSC_U8 i;

    for( i = 0; i < 64; i++ ) outMsgBuffer[ i ] = 0;

    outMsgBuffer[0] = inMsgBuffer[0];           // Echo the request

    switch(inMsgBuffer[0])
    {
        case CMD_GETDEVICEINFO:
            if (inMsgBuffer[1] != 0)
                outMsgBuffer[1] = 0x01;         // Return that the version is not recognized
            else
            {
                outMsgBuffer[1] = 0x00;         // Return that the command was recognized

                outMsgBuffer[4] = 3;            // MCU
                outMsgBuffer[5] = 1;            // USB to I2C device with USB PD and Type C

                outMsgBuffer[6] = core_get_rev_lower();
                outMsgBuffer[7] = core_get_rev_middle();
                outMsgBuffer[8] = core_get_rev_upper();

                outMsgBuffer[9] = 0x00;         // [9:8] make up the board configuration used
                outMsgBuffer[10] = 0x03;

                for(i=0; i<16; i++)             // Loop through all the serial number bytes
                {
                    outMsgBuffer[i + 11] = 0x00;    //Read_b_eep(i);   // return each of the bytes from EEPROM data
                }

                outMsgBuffer[26] = TEST_FIRMWARE;   // Reports if this firmware runs the test suite
            }
            break;
        case CMD_SETIOCONFIG:
            outMsgBuffer[1] = 0x01;                 // Return that the request is not implemented
            break;
        case CMD_GETIOCONFIG:
            outMsgBuffer[1] = 0x01;                 // Return that the request is not implemented
            break;
        case CMD_WRITEIOPORT:
            outMsgBuffer[1] = 0x01;                 // Return that the request is not implemented
            break;
        case CMD_READIOPORT:
            outMsgBuffer[1] = 0x01;                 // Return that the request is not implemented
            break;
        case CMD_READADC:
            outMsgBuffer[1] = 0x01;                 // Return that the request is not implemented
            break;
        case CMD_GETI2CCONFIG:
            outMsgBuffer[1] = 0x01;                 // Return that the request is not implemented
            break;
        case CMD_SETI2CCONFIG:
            outMsgBuffer[1] = 0x01;                 // Return that the request is not implemented
            break;
        case CMD_READI2C_FCSDEVICE:
            ProcessReadI2CFCSDevice(inMsgBuffer, outMsgBuffer);   // Read from the I2C slave
            break;
        case CMD_WRITEI2C_FCSDEVICE:
            ProcessWriteI2CFCSDevice(inMsgBuffer, outMsgBuffer);  // Write to the I2C slave
            break;
        case CMD_USBPD_BUFFER_READ:
            core_process_pd_buffer_read(inMsgBuffer, outMsgBuffer);    // Grab as many bytes from the USB PD buffer as possible
            break;
        case CMD_USBPD_STATUS:
            core_process_typec_pd_status(inMsgBuffer, outMsgBuffer);        // Get the status of the PD state machines
            break;
        case CMD_USBPD_CONTROL:
            core_process_typec_pd_control(inMsgBuffer, outMsgBuffer);       // Update the PD state machine settings
            break;
        case CMD_DEVICE_LOCAL_REGISTER_READ:       
            core_process_local_register_request(inMsgBuffer, outMsgBuffer); // Send local register values
            break;
        case CMD_SET_STATE:                         // Set state
            core_process_set_typec_state(inMsgBuffer, outMsgBuffer);
            break;
        case CMD_READ_STATE_LOG:                          // Read state log
            core_process_read_typec_state_log(inMsgBuffer, outMsgBuffer);
            break;
        case CMD_READ_PD_STATE_LOG:                          // Read PD state log
            core_process_read_pd_state_log(inMsgBuffer, outMsgBuffer);
            break;
        default:
            outMsgBuffer[1] = 0x01;                 // Return that the request is not implemented
            break;
    }
}

void ProcessWriteI2CFCSDevice(FSC_U8* MsgBuffer, FSC_U8* retBuffer)
{
    FSC_U8 SlaveAddress, RegAddrLength, DataLength, PacketSize, IncSize;
    FSC_U8 index;
    FSC_U32 RegAddr = 0;
    if (MsgBuffer[1] != 0)
        retBuffer[1] = 0x01;                     // Return that the version is not recognized
    else if (MsgBuffer[4] >= I2C_NUMBER_OF_MODULES)
        retBuffer[3] = I2C_INVALIDMODULE;        // Invalid i2C module requested
    else
    {
        SlaveAddress = MsgBuffer[5];                    // Slave address
        RegAddrLength = MsgBuffer[6];                   // Address length
        DataLength = MsgBuffer[7];                      // Data Length
        PacketSize = MsgBuffer[8];                      // Packet Size
        IncSize = MsgBuffer[9];                         // Increment Size
        if (RegAddrLength > 4)                          // If the reg addr length is greater than 4, return an error
        {
            retBuffer[1] = 0x02;                 // Return that the address length is invalid
            return;
        }
        if (DataLength > 50)                            // If the data length is greater than 50, clamp it to 50
        {
            retBuffer[1] = 0x03;
            return;
        }
        if (PacketSize > DataLength)                    // If the packet size is greater than the data length, set the packet size equal
            PacketSize = DataLength;
        if (PacketSize == 0)                            // If the packet size is zero, treat it as 1
            PacketSize = 1;
        if (IncSize > DataLength)                       // If the increment size is greater than the data length, set the increment size equal
            IncSize = DataLength;
        if (IncSize == 0)                               // If the increment size is zero, set it to 1
            IncSize = 1;
        for (index=RegAddrLength; index>0; index--)     // Build the register address (Little Endian)
        {
            RegAddr <<= 8;
            RegAddr |= MsgBuffer[10 + index - 1];
        }
        retBuffer[3] = platform_i2c_write(SlaveAddress, RegAddrLength, DataLength, PacketSize, IncSize, RegAddr, (FSC_U8*)&MsgBuffer[14]);
    }
}

void ProcessReadI2CFCSDevice(FSC_U8* MsgBuffer, FSC_U8* retBuffer)
{
    FSC_U8 SlaveAddress, RegAddrLength, DataLength, PacketSize, IncSize;
    FSC_U8 index;
    FSC_U32 RegAddr = 0;
    if (MsgBuffer[1] != 0)
        retBuffer[1] = 0x01;                     // Return that the version is not recognized
    else if (MsgBuffer[4] >= I2C_NUMBER_OF_MODULES)
        retBuffer[3] = I2C_INVALIDMODULE;        // Invalid i2C module requested
    else
    {
        SlaveAddress = MsgBuffer[5];                        // Slave address
        RegAddrLength = MsgBuffer[6];                       // Address length
        DataLength = MsgBuffer[7];                          // Data Length
        PacketSize = MsgBuffer[8];                          // Packet Size
        IncSize = MsgBuffer[9];                             // Increment Size
        if (RegAddrLength > 4)                              // If the reg addr length is greater than 4, return an error
        {
            retBuffer[1] = 0x02;                     // Return that the address length is invalid
            return;
        }
        if (DataLength > 60)                                // If the data length is greater than 60 return an error
        {
            retBuffer[1] = 0x03;                     // Return that the data length is invalid
            return;
        }
        if (PacketSize > DataLength)                        // If the packet size is greater than the data length, set the packet size equal
            PacketSize = DataLength;
        if (PacketSize == 0)                                // If the packet size is zero, treat it as 1
            PacketSize = 1;
        if (IncSize > DataLength)                           // If the increment size is greater than the data length, set the increment size equal
            IncSize = DataLength;
        if (IncSize == 0)                                   // If the increment size is zero, set it to 1
            IncSize = 1;
        for (index=RegAddrLength; index>0; index--)         // Build the register address (Little Endian)
        {
            RegAddr <<= 8;
            RegAddr |= MsgBuffer[10 + index - 1];
        }
        retBuffer[3] = platform_i2c_read(SlaveAddress, RegAddrLength, DataLength, PacketSize, IncSize, RegAddr, (FSC_U8*)&retBuffer[4]);
    }
}

#endif // FSC_DEBUG
