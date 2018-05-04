/****************************************************************************
 * FileName:            HostComm.c
 * Processor:           PIC32
 * Compiler:            MPLAB XC32
 * Company:             Fairchild Semiconductor
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * M. Smith             01/30/2014  Initial Version
 *****************************************************************************/
#ifdef FSC_DEBUG

#include "HostComm.h"
#include "HardwareProfile.h"
#include "AnalogInput.h"
#include "PlatformI2C.h"
#include "device_info.h"
#include "../core/core.h"

void ProcessMsg( FSC_U8* inMsgBuffer, FSC_U8* outMsgBuffer )
{
    FSC_U8 i;

    memset(outMsgBuffer, 0, 64);                // Clear out buffer to start
    outMsgBuffer[0] = inMsgBuffer[0];           // Echo the request

    switch(inMsgBuffer[0])
    {
        case CMD_GETDEVICEINFO:
            if (inMsgBuffer[1] != 0)
                outMsgBuffer[1] = 0x01;         // Return that the version is not recognized
            else
            {
                outMsgBuffer[1] = 0x00;         // Return that the command was recognized

                outMsgBuffer[4] = MY_MCU;       // MCU
                outMsgBuffer[5] = MY_DEV_TYPE;  // USB to I2C device with USB PD and Type C

                outMsgBuffer[6] = core_get_rev_lower();
                outMsgBuffer[7] = core_get_rev_middle();
                outMsgBuffer[8] = core_get_rev_upper();

                outMsgBuffer[9] = 0xFF & MY_BC; // [9:8] make up the board configuration used
                outMsgBuffer[10] = 0xFF & (MY_BC >> 8);

                for(i=0; i<16; i++)              // Loop through all the serial number bytes
                {
                    outMsgBuffer[i + 11] = 0x00; //Read_b_eep(i);   // return each of the bytes from EEPROM data
                }

                outMsgBuffer[26] = TEST_FIRMWARE; // Reports if this firmware runs the test suite
            }
            break;
        case CMD_SETIOCONFIG:
            ProcessSetIOConfig(inMsgBuffer, outMsgBuffer);        // Set the I/O pin configuration
            break;
        case CMD_GETIOCONFIG:
            ProcessGetIOConfig(inMsgBuffer, outMsgBuffer);        // Read the I/O pin configuration
            break;
        case CMD_WRITEIOPORT:
            ProcessWriteIOPort(inMsgBuffer, outMsgBuffer);        // Write to the output latch of the pins
            break;
        case CMD_READIOPORT:
            ProcessReadIOPort(inMsgBuffer, outMsgBuffer);         // Read from the PORT register of the pins
            break;
        case CMD_READADC:
            ProcessReadADCChannel(inMsgBuffer, outMsgBuffer);     // Read from the ADC channel
            break;
        case CMD_GETI2CCONFIG:
            ProcessGetI2CConfig(inMsgBuffer, outMsgBuffer);       // Get the I2C module configuration
            break;
        case CMD_SETI2CCONFIG:
            ProcessSetI2CConfig(inMsgBuffer, outMsgBuffer);       // Set the I2C module configuration
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
        case CMD_SET_ALTERNATE_MODES:
            ProcessSetAlternateModes(inMsgBuffer, outMsgBuffer);
            break;
        case CMD_GET_ALTERNATE_MODES:
            ProcessGetAlternateModes(inMsgBuffer, outMsgBuffer);
            break;
        default:
            outMsgBuffer[1] = 0x01;                 // Return that the request is not implemented
            break;
    }
}

#ifdef FC_TESTER_BOARD
void ProcessSetIOConfig(FSC_U8* MsgBuffer, FSC_U8* retBuffer)
{
    UINT16_VAL tris_new;
    UINT16_VAL adc_new;
    if (MsgBuffer[1] != 0){
        retBuffer[1] = 0x01;                 // Return that the version is not recognized
        return;
    }
    tris_new.v[0] = MsgBuffer[5];
    tris_new.v[1] = MsgBuffer[6];
    switch (MsgBuffer[4])
    {
        case PORT_A:
            TRISA = tris_new.Val;                   // Set the pin direction
            // No PORTA analog pins
            break;
        case PORT_B:
            adc_new.v[0] = MsgBuffer[9] ^ 0xFF;     // Invert the bits to get into right format
            adc_new.v[1] = MsgBuffer[10] ^ 0xFF;    // Invert the bits to get into right format
            TRISB = tris_new.Val;                   // Set the pin direction (in/out)
            AD1PCFG = adc_new.Val;                  // Set if the pins are digital or analog
            break;
        case PORT_C:
            TRISC = tris_new.Val;                   // Set the pin direction
            // No PORTC analog pins
            break;

        case PORT_D:
            TRISD = tris_new.Val;                   // Set the pin direction
            // No PORTD analog pins
            break;
        case PORT_E:
            TRISE = tris_new.Val;                   // Set the pin direction
            // No PORTE analog pins
            break;
        case PORT_F:
            TRISF = tris_new.Val;                   // Set the pin direction
            // No PORTF analog pins
            break;
        case PORT_G:
            TRISG = tris_new.Val;                   // Set the pin direction
            // No PORTG analog pins
            break;
        default:
            retBuffer[3] = 0x01;         // Report that the MCU doesn't have the specified PORT
            break;
    }
}

void ProcessGetIOConfig(FSC_U8* MsgBuffer, FSC_U8* retBuffer)
{
    UINT16_VAL tris;
    UINT16_VAL analog;
    tris.Val = 0x0000;
    analog.Val = 0x0000;
    if (MsgBuffer[1] != 0){
        retBuffer[1] = 0x01;                 // Return that the version is not recognized
        return;
    }
    retBuffer[4] = MsgBuffer[4];             // If we recognize the version, echo the PORT that was requested
    switch (MsgBuffer[4])
    {
        case PORT_A:
            tris.Val = TRISA;                       // Get the pin direction (in/out)
            // No PORTA analog pins available
            break;
        case PORT_B:
            tris.Val = TRISB;                       // Get the pin direction (in/out)
            analog.Val = AD1PCFG ^ 0x0000FFFF;      // Get if pins are digital or analog (invert the bits)
            break;
        case PORT_C:
            tris.Val = TRISC;                       // Get the pin direction (in/out)
            // No PORTC analog pins available
            break;
        case PORT_D:
            tris.Val = TRISD;                       // Get the pin direction (in/out)
            // No PORTD analog pins available
            break;
        case PORT_E:
            tris.Val = TRISE;                       // Get the pin direction (in/out)
            // No PORTE analog pins available
            break;
        case PORT_F:
            tris.Val = TRISF;                       // Get the pin direction (in/out)
            // No PORTF analog pins available
            break;
        case PORT_G:
            tris.Val = TRISG;                       // Get the pin direction (in/out)
            // No PORTG analog pins available
            break;
        default:
            retBuffer[3] = 0x01;             // Report that the MCU doesn't have the specified PORT
            break;
    }
    if (retBuffer[3] != 0x01)                // If we have the specified port...
    {
        retBuffer[5] = tris.v[0];            // Set the lower TRIS byte
        retBuffer[6] = tris.v[1];            // Set the upper TRIS byte
        retBuffer[9] = analog.v[0];          // Set the lower analog byte
        retBuffer[10] = analog.v[1];         // Set the upper analog byte
    }
}
#elif defined USBPD_EXPLORER_BOARD
void ProcessSetIOConfig(FSC_U8* MsgBuffer, FSC_U8* retBuffer)
{
    UINT16_VAL tris_new;
    UINT16_VAL adc_new;
    if (MsgBuffer[1] != 0){
        retBuffer[1] = 0x01;                 // Return that the version is not recognized
        return;
    }
    tris_new.v[0] = MsgBuffer[5];                   // Grab the new tris setting
    tris_new.v[1] = MsgBuffer[6];                   // Grab the new tris setting
    adc_new.v[0] = MsgBuffer[9];                    // Grab the new ANSELx setting
    adc_new.v[1] = MsgBuffer[10];                   // Grab the new ANSELx setting
    switch (MsgBuffer[4])
    {
        case PORT_A:
            TRISA = tris_new.Val;                   // Set the pin direction
            ANSELA = adc_new.Val;                   // Set whether the pins are analog or digital
            break;
        case PORT_B:
            TRISB = tris_new.Val;                   // Set the pin direction (in/out)
            ANSELB = adc_new.Val;                   // Set whether the pins are analog or digital
            break;
        case PORT_C:
            TRISC = tris_new.Val;                   // Set the pin direction
            ANSELC = adc_new.Val;                   // Set whether the pins are analog or digital
            break;
        default:
            retBuffer[3] = 0x01;         // Report that the MCU doesn't have the specified PORT
            break;
    }
}

void ProcessGetIOConfig(FSC_U8* MsgBuffer, FSC_U8* retBuffer)
{
    UINT16_VAL tris;
    UINT16_VAL analog;
    tris.Val = 0x0000;
    analog.Val = 0x0000;
    if (MsgBuffer[1] != 0){
        retBuffer[1] = 0x01;                 // Return that the version is not recognized
        return;
    }
    retBuffer[4] = MsgBuffer[4];             // If we recognize the version, echo the PORT that was requested
    switch (MsgBuffer[4])
    {
        case PORT_A:
            tris.Val = TRISA;                       // Get the pin direction (in/out)
            analog.Val = ANSELA;                    // Get if pins are digital or analog
            break;
        case PORT_B:
            tris.Val = TRISB;                       // Get the pin direction (in/out)
            analog.Val = ANSELB;                    // Get if pins are digital or analog
            break;
        case PORT_C:
            tris.Val = TRISC;                       // Get the pin direction (in/out)
            analog.Val = ANSELC;                    // Get if pins are digital or analog
            break;
        default:
            retBuffer[3] = 0x01;             // Report that the MCU doesn't have the specified PORT
            break;
    }
    if (retBuffer[3] != 0x01)                // If we have the specified port...
    {
        retBuffer[5] = tris.v[0];            // Set the lower TRIS byte
        retBuffer[6] = tris.v[1];            // Set the upper TRIS byte
        retBuffer[9] = analog.v[0];          // Set the lower analog byte
        retBuffer[10] = analog.v[1];         // Set the upper analog byte
    }
}

#elif defined FSUSB300_EVAL_BOARD
void ProcessSetIOConfig(FSC_U8* MsgBuffer, FSC_U8* retBuffer)
{
    UINT16_VAL tris_new;
    UINT16_VAL adc_new;
    if (MsgBuffer[1] != 0){
        retBuffer[1] = 0x01;                 // Return that the version is not recognized
        return;
    }
    tris_new.v[0] = MsgBuffer[5];                   // Grab the new tris setting
    tris_new.v[1] = MsgBuffer[6];                   // Grab the new tris setting
    adc_new.v[0] = MsgBuffer[9];                    // Grab the new ANSELx setting
    adc_new.v[1] = MsgBuffer[10];                   // Grab the new ANSELx setting
    switch (MsgBuffer[4])
    {
        case PORT_A:
            TRISA = tris_new.Val;                   // Set the pin direction
            ANSELA = adc_new.Val;                   // Set whether the pins are analog or digital
            break;
        case PORT_B:
            TRISB = tris_new.Val;                   // Set the pin direction (in/out)
            ANSELB = adc_new.Val;                   // Set whether the pins are analog or digital
            break;
        default:
            retBuffer[3] = 0x01;         // Report that the MCU doesn't have the specified PORT
            break;
    }
}

void ProcessGetIOConfig(FSC_U8* MsgBuffer, FSC_U8* retBuffer)
{
    UINT16_VAL tris;
    UINT16_VAL analog;
    tris.Val = 0x0000;
    analog.Val = 0x0000;
    if (MsgBuffer[1] != 0){
        retBuffer[1] = 0x01;                 // Return that the version is not recognized
        return;
    }
    retBuffer[4] = MsgBuffer[4];             // If we recognize the version, echo the PORT that was requested
    switch (MsgBuffer[4])
    {
        case PORT_A:
            tris.Val = TRISA;                       // Get the pin direction (in/out)
            analog.Val = ANSELA;                    // Get if pins are digital or analog
            break;
        case PORT_B:
            tris.Val = TRISB;                       // Get the pin direction (in/out)
            analog.Val = ANSELB;                    // Get if pins are digital or analog
            break;
        default:
            retBuffer[3] = 0x01;             // Report that the MCU doesn't have the specified PORT
            break;
    }
    if (retBuffer[3] != 0x01)                // If we have the specified port...
    {
        retBuffer[5] = tris.v[0];            // Set the lower TRIS byte
        retBuffer[6] = tris.v[1];            // Set the upper TRIS byte
        retBuffer[9] = analog.v[0];          // Set the lower analog byte
        retBuffer[10] = analog.v[1];         // Set the upper analog byte
    }
}
#elif defined(FM141014) || defined(FM150911A) || defined(FM150404A)
void ProcessSetIOConfig(FSC_U8* MsgBuffer, FSC_U8* retBuffer)
{
    UINT16_VAL tris_new;
    UINT16_VAL adc_new;
    if (MsgBuffer[1] != 0){
        retBuffer[1] = 0x01;                 // Return that the version is not recognized
        return;
    }
    tris_new.v[0] = MsgBuffer[5];                   // Grab the new tris setting
    tris_new.v[1] = MsgBuffer[6];                   // Grab the new tris setting
    adc_new.v[0] = MsgBuffer[9];                    // Grab the new ANSELx setting
    adc_new.v[1] = MsgBuffer[10];                   // Grab the new ANSELx setting
    switch (MsgBuffer[4])
    {
        case PORT_A:
            TRISA = tris_new.Val;                   // Set the pin direction
            ANSELA = adc_new.Val;                   // Set whether the pins are analog or digital
            break;
        case PORT_B:
            TRISB = tris_new.Val;                   // Set the pin direction (in/out)
            ANSELB = adc_new.Val;                   // Set whether the pins are analog or digital
            break;
        default:
            retBuffer[3] = 0x01;         // Report that the MCU doesn't have the specified PORT
            break;
    }
}

void ProcessGetIOConfig(FSC_U8* MsgBuffer, FSC_U8* retBuffer)
{
    UINT16_VAL tris;
    UINT16_VAL analog;
    tris.Val = 0x0000;
    analog.Val = 0x0000;
    if (MsgBuffer[1] != 0){
        retBuffer[1] = 0x01;                 // Return that the version is not recognized
        return;
    }
    retBuffer[4] = MsgBuffer[4];             // If we recognize the version, echo the PORT that was requested
    switch (MsgBuffer[4])
    {
        case PORT_A:
            tris.Val = TRISA;                       // Get the pin direction (in/out)
            analog.Val = ANSELA;                    // Get if pins are digital or analog
            break;
        case PORT_B:
            tris.Val = TRISB;                       // Get the pin direction (in/out)
            analog.Val = ANSELB;                    // Get if pins are digital or analog
            break;
        default:
            retBuffer[3] = 0x01;             // Report that the MCU doesn't have the specified PORT
            break;
    }
    if (retBuffer[3] != 0x01)                // If we have the specified port...
    {
        retBuffer[5] = tris.v[0];            // Set the lower TRIS byte
        retBuffer[6] = tris.v[1];            // Set the upper TRIS byte
        retBuffer[9] = analog.v[0];          // Set the lower analog byte
        retBuffer[10] = analog.v[1];         // Set the upper analog byte
    }
}
#elif defined FM150105
void ProcessSetIOConfig(FSC_U8* MsgBuffer, FSC_U8* retBuffer)
{
    UINT16_VAL tris_new;
    UINT16_VAL adc_new;
    if (MsgBuffer[1] != 0){
        retBuffer[1] = 0x01;                 // Return that the version is not recognized
        return;
    }
    tris_new.v[0] = MsgBuffer[5];                   // Grab the new tris setting
    tris_new.v[1] = MsgBuffer[6];                   // Grab the new tris setting
    adc_new.v[0] = MsgBuffer[9];                    // Grab the new ANSELx setting
    adc_new.v[1] = MsgBuffer[10];                   // Grab the new ANSELx setting
    switch (MsgBuffer[4])
    {
        case PORT_A:
            TRISA = tris_new.Val;                   // Set the pin direction
            ANSELA = adc_new.Val;                   // Set whether the pins are analog or digital
            break;
        case PORT_B:
            TRISB = tris_new.Val;                   // Set the pin direction (in/out)
            ANSELB = adc_new.Val;                   // Set whether the pins are analog or digital
            break;
        default:
            retBuffer[3] = 0x01;         // Report that the MCU doesn't have the specified PORT
            break;
    }
}

void ProcessGetIOConfig(FSC_U8* MsgBuffer, FSC_U8* retBuffer)
{
    UINT16_VAL tris;
    UINT16_VAL analog;
    tris.Val = 0x0000;
    analog.Val = 0x0000;
    if (MsgBuffer[1] != 0){
        retBuffer[1] = 0x01;                 // Return that the version is not recognized
        return;
    }
    retBuffer[4] = MsgBuffer[4];             // If we recognize the version, echo the PORT that was requested
    switch (MsgBuffer[4])
    {
        case PORT_A:
            tris.Val = TRISA;                       // Get the pin direction (in/out)
            analog.Val = ANSELA;                    // Get if pins are digital or analog
            break;
        case PORT_B:
            tris.Val = TRISB;                       // Get the pin direction (in/out)
            analog.Val = ANSELB;                    // Get if pins are digital or analog
            break;
        default:
            retBuffer[3] = 0x01;             // Report that the MCU doesn't have the specified PORT
            break;
    }
    if (retBuffer[3] != 0x01)                // If we have the specified port...
    {
        retBuffer[5] = tris.v[0];            // Set the lower TRIS byte
        retBuffer[6] = tris.v[1];            // Set the upper TRIS byte
        retBuffer[9] = analog.v[0];          // Set the lower analog byte
        retBuffer[10] = analog.v[1];         // Set the upper analog byte
    }
}
#endif

void ProcessWriteIOPort(FSC_U8* MsgBuffer, FSC_U8* retBuffer)
{
    UINT16_VAL data;
    UINT16_VAL mask;
    if (MsgBuffer[1] != 0){
        retBuffer[1] = 0x01;                 // Return that the version is not recognized
        return;
    }
    data.v[0] = MsgBuffer[5];
    data.v[1] = MsgBuffer[6];
    mask.v[0] = MsgBuffer[9];
    mask.v[1] = MsgBuffer[10];
    switch (MsgBuffer[4])
    {
        case PORT_A:
            LATA = (LATA & ~mask.Val) | (data.Val & mask.Val);  // Set the pin direction (in/out)
            break;
        case PORT_B:
            LATB = (LATB & ~mask.Val) | (data.Val & mask.Val);  // Set the pin direction (in/out)
            break;
        #if defined(USBPD_EXPLORER_BOARD) || defined(FC_TESTER_BOARD)
        case PORT_C:
            LATC = (LATC & ~mask.Val) | (data.Val & mask.Val);  // Set the pin direction (in/out)
            break;
        #endif
        #if defined(FC_TESTER_BOARD)
        case PORT_D:
            LATD = (LATD & ~mask.Val) | (data.Val & mask.Val);  // Set the pin direction (in/out)
            break;
        case PORT_E:
            LATE = (LATE & ~mask.Val) | (data.Val & mask.Val);  // Set the pin direction (in/out)
            break;
        case PORT_F:
            LATF = (LATF & ~mask.Val) | (data.Val & mask.Val);  // Set the pin direction (in/out)
            break;
        case PORT_G:
            LATG = (LATG & ~mask.Val) | (data.Val & mask.Val);  // Set the pin direction (in/out)
            break;
        #endif
        default:
            retBuffer[3] = 0x01;             // Report that the MCU doesn't have the specified PORT
            break;
    }
}

void ProcessReadIOPort(FSC_U8* MsgBuffer, FSC_U8* retBuffer)
{
    UINT16_VAL port;
    UINT16_VAL tris;
    if (MsgBuffer[1] != 0) {
        retBuffer[1] = 0x01;                 // Return that the version is not recognized
        return;
    }
    retBuffer[4] = MsgBuffer[4];             // Return the port number requested
    switch (MsgBuffer[4])
    {
        case PORT_A:
            tris.Val = TRISA;                       // Get the pin direction (in/out)
            port.Val = PORTA;                       // Get the pin state (high/low)
            break;
        case PORT_B:
            tris.Val = TRISB;                       // Get the pin direction (in/out)
            port.Val = PORTB;                       // Get the pin state (high/low)
            break;
        #if defined(USBPD_EXPLORER_BOARD) || defined(FC_TESTER_BOARD)
        case PORT_C:
            tris.Val = TRISC;                       // Get the pin direction (in/out)
            port.Val = PORTC;                       // Get the pin state (high/low)
            break;
        #endif
        #if defined(FC_TESTER_BOARD)
        case PORT_D:
            tris.Val = TRISD;                       // Get the pin direction (in/out)
            port.Val = PORTD;                       // Get the pin state (high/low)
            break;
        case PORT_E:
            tris.Val = TRISE;                       // Get the pin direction (in/out)
            port.Val = PORTE;                       // Get the pin state (high/low)
            break;
        case PORT_F:
            tris.Val = TRISF;                       // Get the pin direction (in/out)
            port.Val = PORTF;                       // Get the pin state (high/low)
            break;
        case PORT_G:
            tris.Val = TRISG;                       // Get the pin direction (in/out)
            port.Val = PORTG;                       // Get the pin state (high/low)
            break;
        #endif
        default:
            retBuffer[3] = 0x01;             // Report that the MCU doesn't have the specified PORT
            break;
    }
    if (retBuffer[3] != 0x01)                // If we have the specified port...
    {
        retBuffer[5] = port.v[0];            // Set the lower TRIS byte
        retBuffer[6] = port.v[1];            // Set the upper TRIS byte
        retBuffer[9] = tris.v[0];          // Set the lower analog byte
        retBuffer[10] = tris.v[1];         // Set the upper analog byte
    }
}

void ProcessReadADCChannel(FSC_U8* MsgBuffer, FSC_U8* retBuffer)
{
    FSC_U16 u16Value = 0x0000;
    if (MsgBuffer[1] != 0)
    {
        retBuffer[1] = 0x01;                                 // Return that the version is not recognized
        return;
    }
    if ((MsgBuffer[4] < 0) || (MsgBuffer[4] > 15))
    {
        retBuffer[3] = 0x01;                                 // Return invalid channel received
        return;
    }
    u16Value = ReadADCChannel(MsgBuffer[4]);
    retBuffer[4] = MsgBuffer[4];                             // Get a measurement of the selected channel
    retBuffer[5] = (FSC_U8)(u16Value & 0xFF);         // Return the LSB of the measurement
    retBuffer[6] = (FSC_U8)((u16Value & 0xFF00)>>8);  // Return the MSB of the measurement
    retBuffer[9] = 0xFF;                                     // Return that we are using 10 bits
    retBuffer[10] = 0x03;                                    // ...
    retBuffer[13] = 0x01;                                    // Specify that our reference is based on 3.3V (VCC)
}

void ProcessSetI2CConfig(FSC_U8* MsgBuffer, FSC_U8* retBuffer)
{
    FSC_U8 Module;
    FSC_U32 Frequency;
    FSC_BOOL Enable;
    if (MsgBuffer[1] != 0)
        retBuffer[1] = 0x01;                 // Return that the version is not recognized
    else if (MsgBuffer[4] >= I2C_NUMBER_OF_MODULES)
        retBuffer[3] = I2C_INVALIDMODULE;    // Invalid i2C module requested
    else
    {
        Module = MsgBuffer[4];                      // I2C module to configure
        Enable = ((MsgBuffer[5] & 0x01) == 0x01);     // Enable the module?
        Frequency = MsgBuffer[9] << 24;             // MSB of frequency setting
        Frequency |= MsgBuffer[8] << 16;            // 3rd byte of frequency
        Frequency |= MsgBuffer[7] << 8;             // 2nd byte of frequency
        Frequency |= MsgBuffer[6];                  // LSB of frequency
        I2C_Init(Module, Frequency, Enable);        // Initialize the module
    }
}

void ProcessGetI2CConfig(FSC_U8* MsgBuffer, FSC_U8* retBuffer)
{
    FSC_U8 Module;
    UINT32_VAL Frequency;
    if (MsgBuffer[1] != 0)
        retBuffer[1] = 0x01;                 // Return that the version is not recognized
    else if (MsgBuffer[4] >= I2C_NUMBER_OF_MODULES)
        retBuffer[3] = I2C_INVALIDMODULE;    // Invalid i2C module requested
    else
    {
        Module = MsgBuffer[4];                      // Get the module
        retBuffer[4] = Module;               // Echo the module
        retBuffer[5] = I2C_GetEnable(Module);// Return whether the module is enabled...
        Frequency.Val = I2C_GetFrequency(Module);   // Get the I2C frequency for the specified module
        retBuffer[6] = Frequency.v[0];       // Set the LSB of the frequency
        retBuffer[7] = Frequency.v[1];       // Set the 2nd byte of the frequency
        retBuffer[8] = Frequency.v[2];       // Set the 3rd byte of the frequency
        retBuffer[9] = Frequency.v[3];       // Set the MSB of the frequency
    }
}

void ProcessWriteI2CFCSDevice(FSC_U8* MsgBuffer, FSC_U8* retBuffer)
{
    FSC_U8 Module, SlaveAddress, RegAddrLength, DataLength, PacketSize, IncSize;
    FSC_U8 index;
    FSC_U32 RegAddr = 0;
    if (MsgBuffer[1] != 0)
        retBuffer[1] = 0x01;                     // Return that the version is not recognized
    else if (MsgBuffer[4] >= I2C_NUMBER_OF_MODULES)
        retBuffer[3] = I2C_INVALIDMODULE;        // Invalid i2C module requested
    else if (!I2C_GetEnable(MsgBuffer[4]))
        retBuffer[3] = I2C_MODULEDISABLED;       // I2C module not enabled
    else 
    {
        Module = MsgBuffer[4];                          // I2C module
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
        retBuffer[3] = I2C_WriteData(Module, SlaveAddress, RegAddrLength, DataLength, PacketSize, IncSize, RegAddr, (FSC_U8*)&MsgBuffer[14]);
    }
}

void ProcessReadI2CFCSDevice(FSC_U8* MsgBuffer, FSC_U8* retBuffer)
{
    FSC_U8 Module, SlaveAddress, RegAddrLength, DataLength, PacketSize, IncSize;
    FSC_U8 index;
    FSC_U32 RegAddr = 0;
    if (MsgBuffer[1] != 0)
        retBuffer[1] = 0x01;                     // Return that the version is not recognized
    else if (MsgBuffer[4] >= I2C_NUMBER_OF_MODULES)
        retBuffer[3] = I2C_INVALIDMODULE;        // Invalid i2C module requested
    else if (!I2C_GetEnable(MsgBuffer[4]))
        retBuffer[3] = I2C_MODULEDISABLED;       // I2C module not enabled
    else
    {
        Module = MsgBuffer[4];                              // I2C module
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
        retBuffer[3] = I2C_ReadData(Module, SlaveAddress, RegAddrLength, DataLength, PacketSize, IncSize, RegAddr, (FSC_U8*)&retBuffer[4]);
    }
}

void ProcessSetAlternateModes(FSC_U8* MsgBuffer, FSC_U8* retBuffer)
{
    if (MsgBuffer[1] != 0)
    {
        retBuffer[1] = 0x01;             // Return that the version is not recognized
        return;
    }
    
    core_set_alternate_modes(MsgBuffer, retBuffer);
    core_set_manual_retries(MsgBuffer, retBuffer);
    
    core_set_state_unattached();               // Set state machine to unattached so modes update
}

void ProcessGetAlternateModes(FSC_U8* MsgBuffer, FSC_U8* retBuffer)
{
    if (MsgBuffer[1] != 0)
    {
        retBuffer[1] = 0x01;             // Return that the version is not recognized
        return;
    }

    retBuffer[3] = core_get_alternate_modes();
    retBuffer[4] = core_get_manual_retries();
}

#endif // FSC_DEBUG
