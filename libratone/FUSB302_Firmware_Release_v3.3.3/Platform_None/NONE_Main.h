#ifndef _MAIN_H_
#define _MAIN_H_

#include "FSCTypes.h"

static void InitializeSystem(void);
void InitializeBoard(void);
void InitializeVariables(void);
void InitializeTimers(void);

void ProcessMsg( FSC_U8 *ReceivedDataBuffer, FSC_U8 *ReturnDataBuffer );

#endif
