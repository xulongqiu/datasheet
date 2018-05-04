
#ifndef _USB_MAIN_H_
#define _USB_MAIN_H_

#include "GenericTypeDefs.h"

extern BOOL haveUSBCommand;

void ProcessHIDPacket(void);
void USBCBSuspend(void);
void USBCBWakeFromSuspend(void);
void USBCB_SOF_Handler(void);
void USBCBErrorHandler(void);
void USBCBCheckOtherReq(void);
void USBCBStdSetDscHandler(void);
void USBCBInitEP(void);
void USBCBSendResume(void);
BOOL USER_USB_CALLBACK_EVENT_HANDLER(INT32 event, void *pdata, WORD size);


#endif // _HWIO_H_