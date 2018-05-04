/*********************************************************************
* FileName:        HostComm.h
* Dependencies:    See INCLUDES section below
* Processor:       ARM M0
* Compiler:
* Company:         Fairchild Semiconductor
********************************************************************/
#ifndef _HOSTCOMM_H
#define _HOSTCOMM_H

#ifdef FSC_DEBUG

#include "FSCTypes.h"

// ##### Packet Structure ##### //
#define PKTOUT_REQUEST              0x00
#define PKTOUT_VERSION              0x01
#define PKTIN_REQUEST               0x00
#define PKTIN_STATUS                0x01
#define PKTIN_ERRORCODE             0x03

// ##### Command definitions ##### //
#define CMD_GETDEVICEINFO           0x00
#define CMD_SETSERIALNUMBER         0x01
#define CMD_SETIOCONFIG             0x10
#define CMD_GETIOCONFIG             0x11
#define CMD_SETI2CCONFIG            0x12
#define CMD_GETI2CCONFIG            0x13
#define CMD_WRITEIOPORT             0x40
#define CMD_READIOPORT              0x41
#define CMD_READADC                 0x42
#define CMD_WRITEI2C_FCSDEVICE      0x60
#define CMD_READI2C_FCSDEVICE       0x61
#define CMD_DATACOLLECT_STARTI2C    0x80
#define CMD_DATACOLLECT_STOPI2C     0x81
#define CMD_DATACOLLECT_READ        0x82
#define CMD_ACCP_STATUS             0x90
#define CMD_ACCP_CONTROL            0x91
#define CMD_ACCP_WRITE              0x92
#define CMD_ACCP_READ               0x93
#define CMD_USBPD_BUFFER_READ       0xA0
#define CMD_USBPD_RESERVED          0xA1
#define CMD_USBPD_STATUS            0xA2
#define CMD_USBPD_CONTROL           0xA3

#define CMD_DEVICE_LOCAL_REGISTER_READ  0xB0    // xBX designation for rick's automated testing
#define CMD_SET_STATE                   0xB1
#define CMD_READ_STATE_LOG              0xB2
#define CMD_READ_PD_STATE_LOG           0xB3

#define TEST_FIRMWARE                   0X01    // For GUI identification of firmware

typedef enum _PORTS
{
    PORT_A = 0,
    PORT_B,
    PORT_C,
    PORT_D,
    PORT_E,
    PORT_F,
    PORT_G,
    PORT_H
} PORTS;


// ##### Function Prototypes ##### //
void ProcessMsg( FSC_U8* inMsgBuffer, FSC_U8* outMsgBuffer );
void ProcessWriteI2CFCSDevice(FSC_U8* MsgBuffer, FSC_U8* retBuffer);
void ProcessReadI2CFCSDevice(FSC_U8* MsgBuffer, FSC_U8* retBuffer);

#endif // FSC_DEBUG

#endif	/* HOSTCOMM_H */
