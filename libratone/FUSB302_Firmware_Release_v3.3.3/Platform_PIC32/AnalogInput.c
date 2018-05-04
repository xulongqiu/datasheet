/****************************************************************************
 * FileName:        AnalogInput.c
 * Processor:       PIC32
 * Compiler:        MPLAB XC32
 * Company:         Fairchild Semiconductor
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * M. Smith             11/19/2013  Initial Version
 *****************************************************************************/
#include "AnalogInput.h"
#include "HardwareProfile.h"
#include <Peripheral/ports.h>


void InitializeADC(void)
{
    AD1CON1 = 0x00E0;                               // Configure sample clock source and conversion trigger mode
                                                    // ADC off (for now), stop in idle, 16-bit integer, manual triggering
    AD1CON2 = 0x0000;                               // Configure reference and buffer fill mode
                                                    // AVDD is REF, no cal, no scan, set int after every conv., 16-bit buffer, MUX A always
    AD1CON3 = 0x9F13;                               // Configure ADC conversion clock
                                                    // Internal RC clock, {TPB * 2 * (ADCS<7:0>+1) = TAD} ~100kHz conversion
    AD1CHS = 0x0000;                                // Initialize the ADC to have the negative input at ground and the positive input at AN0
}

#ifdef __PIC32MX3XX_7XX__

    FSC_U16 ReadADCChannel(BYTE bytChannel)
    {
        FSC_U32 uintValue = 0;                          // Initialize the return value
        FSC_S32 intIndex;
        if (bytChannel > 0x0F)                          // If an unknown channel is selected
            return 0xFFFF;                              // Return an invalid value
        AD1CHSbits.CH0SA = bytChannel;                  // Otherwise, select the channel from the mux
        AD1CON1bits.ADON = 1;                           // Turn on the ADC
        for (intIndex=0; intIndex<4; intIndex++)        // Sample 4 times to get an average
        {
            IFS1bits.AD1IF = 0;                         // Clear the interrupt bit
            AD1CON1bits.ASAM = 1;                       // Enable auto-sampling... start sampling
            while (!IFS1bits.AD1IF);                    // Wait for conversion to complete
            AD1CON1bits.ASAM = 0;                       // Disable auto-sampling... stop sampling
            uintValue += ADC1BUF0;                      // Add the conversion result to our value
        }
        AD1CON1bits.ADON = 0;                           // Turn off the ADC
        uintValue >>= 2;                                // Divide by 4 to get the average
        return (FSC_U16) uintValue;                     // Return the average value
    }

#elif defined __PIC32MX1XX_2XX__

        FSC_U16 ReadADCChannel(BYTE bytChannel)
    {
        FSC_U32 uintValue = 0;                          // Initialize the return value
        FSC_S32 intIndex;
        if (bytChannel > 0x0F)                          // If an unknown channel is selected
            return 0xFFFF;                              // Return an invalid value
        AD1CHSbits.CH0SA = bytChannel;                  // Otherwise, select the channel from the mux
        AD1CON1bits.ADON = 1;                           // Turn on the ADC
        for (intIndex=0; intIndex<4; intIndex++)        // Sample 4 times to get an average
        {
            IFS0bits.AD1IF = 0;                         // Clear the interrupt bit
            AD1CON1bits.ASAM = 1;                       // Enable auto-sampling... start sampling
            while (!IFS0bits.AD1IF);                    // Wait for conversion to complete
            AD1CON1bits.ASAM = 0;                       // Disable auto-sampling... stop sampling
            uintValue += ADC1BUF0;                      // Add the conversion result to our value
        }
        AD1CON1bits.ADON = 0;                           // Turn off the ADC
        uintValue >>= 2;                                // Divide by 4 to get the average
        return (FSC_U16) uintValue;                     // Return the average value
    }

#else
    #error ("Hardware profile is either not defined or not defined properly");
#endif

