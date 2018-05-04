/*********************************************************************
 *
 *	Hardware specific definitions
 *
 *********************************************************************
 * FileName:        HardwareProfile.h
 * Dependencies:    None
 * Processor:       PIC24, dsPIC, PIC32
 * Compiler:        Microchip C30 and C32
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright (c) 2011 Microchip Technology Inc.  All rights 
 * reserved.
 *
 * Microchip licenses to you the right to use, modify, copy, and 
 * distribute: 
 * (i)  the Software when embedded on a Microchip microcontroller or 
 *      digital signal controller product ("Device") which is 
 *      integrated into Licensee�s product; or
 * (ii) ONLY the Software driver source files ENC28J60.c and 
 *      ENC28J60.h ported to a non-Microchip device used in 
 *      conjunction with a Microchip ethernet controller for the 
 *      sole purpose of interfacing with the ethernet controller. 
 *
 * You should refer to the license agreement accompanying this 
 * Software for additional information regarding your rights and 
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED �AS IS� WITHOUT 
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT 
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A 
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL 
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR 
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF 
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS 
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE 
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER 
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT 
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 *
 * Date	                Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 10/03/06             Original, copied from Compiler.h
 * 06/25/09             dsPIC & PIC24H support 
 * 09/15/09             Added PIC24FJ256DA210 Development Board Support
 * 06/02/11             Added MPLAB X Support
 * 01/19/12		Removed support for GFXV2
 ********************************************************************/

#ifndef HARDWARE_PROFILE_H
#define HARDWARE_PROFILE_H

//   Part number defining Macro
#if   (((__PIC32_FEATURE_SET__ >= 100) && (__PIC32_FEATURE_SET__ <= 299)))
    #define __PIC32MX1XX_2XX__
#elif (((__PIC32_FEATURE_SET__ >= 300) && (__PIC32_FEATURE_SET__ <= 799)))
    #define __PIC32MX3XX_7XX__
#else
    #error("Controller not supported")
#endif

#if defined(__PIC32MX1XX_2XX__)
    // Maximum System frequency of 40MHz for PIC32MX1xx and PIC32MX2xx devices.
    #define GetSystemClock()        (40000000ul)
#elif defined(__PIC32MX3XX_7XX__)
    // Maximum System frequency of 80MHz for PIC32MX3xx, PIC32MX4xx,
    // PIC32MX5xx, PIC32MX6xx and PIC32MX7xx devices.
    #define GetSystemClock()        (80000000ul)
#endif

#define GetPeripheralClock()    (GetSystemClock() / (1 << OSCCONbits.PBDIV))
#define GetInstructionClock()   (GetSystemClock())
#define self_power              1

#ifdef  FC_TESTER_BOARD

    //#define USE_USB_BUS_SENSE_IO
    //#define USB_BUS_SENSE       	U1OTGSTATbits.SESVD // Special considerations required if using SESVD for this purpose.  See documentation.

    #define FC_ADCCHANNEL       4               // ADC channel to use for the FC_OUT measurement
    #define FC_PORTMASK         0x0010          // FC_OUT port mask (used for port and adc configuration)
    #define FC_DMTHRESHOLD      0x5D            // ~300mV = 0x5D/1024 * 3.3V; used for the Smart Adaptor detection
    #define VB_5VLOWTHRESHOLD   0x7C            // ~4.0V = 0x7C/1024 * 3.3V * 10
    #define VB_5VHIGHTHRESHOLD  0xBA            // ~6.0V = 0xBA/1024 * 3.3V * 10
    #define VB_9VLOWTHRESHOLD   0xDF            // ~7.2V = 0xDF/1024 * 3.3V * 10
    #define VB_9VHIGHTHRESHOLD  0x14F           // ~10.8V = 0x14F/1024 * 3.3V * 10

    #define BCD_CHG_AL_N        PORTAbits.RA14  // CHG_AL_N input from the FSA832 (Charging allowed?, SDP, CDP, DCP all pull low)
    #define BCD_CHG_DET         PORTAbits.RA15  // CHG_DET input from the FSA832 (Charger detected?, CDP and DCP assert high)
    #define BCD_SW_OPEN         PORTDbits.RD8   // SW_OPEN input from the FSA832 (Detect difference between DCP/CDP, high = DCP)
    #define BCD_GOODBAT         PORTDbits.RD9   // GOOD_BAT output to the FSA832 (Assert high to differentiate between DCP/CDP)

    #define Read_Control()      mPORTDReadBits(BIT_1 | BIT_0)

    #define LED_General_Set()   mPORTESetBits(BIT_0)                // Red LED
    #define LED_General_Clear() mPORTEClearBits(BIT_0)
    #define LED_TOErr_Set()     mPORTESetBits(BIT_1)                // Red LED
    #define LED_TOErr_Clear()   mPORTEClearBits(BIT_1)
    #define LED_FCErr_Set()     mPORTESetBits(BIT_2)                // Red LED
    #define LED_FCErr_Clear()   mPORTEClearBits(BIT_2)
    #define LED_VBOK_Set()      mPORTESetBits(BIT_3)                // Green LED
    #define LED_VBOK_Clear()    mPORTEClearBits(BIT_3)
    #define LED_9VReq_Set()     mPORTESetBits(BIT_4)                // Green LED
    #define LED_9VReq_Clear()   mPORTEClearBits(BIT_4)
    #define LED_FCAct_Set()     mPORTESetBits(BIT_5)                // Green LED
    #define LED_FCAct_Clear()   mPORTEClearBits(BIT_5)
    #define LED_Smart_Set()     mPORTESetBits(BIT_6)                // Yellow LED
    #define LED_Smart_Clear()   mPORTEClearBits(BIT_6)
    #define LED_VBUS_Set()      mPORTESetBits(BIT_7)                // Yellow LED
    #define LED_VBUS_Clear()    mPORTEClearBits(BIT_7)
    #define LED_ClearAll()      mPORTEClearBits(0xFF)               

    #define mFCOUT_SetInput     mPORTBSetPinsDigitalIn(BIT_4)
    #define mFCOUT_SetOutput    mPORTBSetPinsDigitalOut(BIT_4)
    #define mFCOUT_SetHigh      mPORTBSetBits(BIT_4)
    #define mFCOUT_SetLow       mPORTBClearBits(BIT_4)
    #define mFCIN_SetInput      mPORTBSetPinsDigitalIn(BIT_3)
    #define mFCIN_Read          mPORTBReadBits(BIT_3)

#elif defined USBPD_EXPLORER_BOARD
    #define USE_USB_BUS_SENSE_IO
    #define USB_BUS_SENSE           PORTCbits.RC5

#elif defined FSUSB300_EVAL_BOARD
    #define VBUS_5V_EN          LATAbits.LATA4
    #define VBUS_12V_EN         LATBbits.LATB4
    #define DEVICE_INT_N        PORTBbits.RB7

#elif defined FM141014
    #define VBUS_5V_EN          LATAbits.LATA4
    #define VBUS_12V_EN         LATBbits.LATB4
    #define VBUS_DISCHARGE      LATBbits.LATB3
    #define DEVICE_INT_N        PORTBbits.RB7
#elif defined FM150911A
    #define VBUS_5V_EN          LATAbits.LATA4
    #define VBUS_12V_EN         LATBbits.LATB4
    #define VBUS_DISCHARGE      LATBbits.LATB3
    #define DEVICE_INT_N        PORTBbits.RB7
#elif defined FM150105
    #define VBUS_5V_EN          LATAbits.LATA4
    #define VBUS_12V_EN         LATBbits.LATB4
    #define DEVICE_INT_N        PORTBbits.RB7
    #ifndef FPGA_BOARD
        #define FPGA_BOARD
    #endif
#elif defined FM150404A
    #define VBUS_5V_EN          LATAbits.LATA4
    #define VBUS_12V_EN         LATBbits.LATB5  /* not used on this EVB */
    #define VBUS_DISCHARGE      LATBbits.LATB3
    #define DEVICE_INT_N        PORTBbits.RB7
#else
    #error ("Hardware profile is either not defined or not defined properly");
#endif

#endif

