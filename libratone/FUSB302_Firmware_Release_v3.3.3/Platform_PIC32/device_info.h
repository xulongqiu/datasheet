/* 
 * File:   device_info.h
 * Author: G. Noblesmith
 *
 * Created on July 8, 2015, 4:16 PM
 */

#ifndef DEVICE_INFO_H
#define	DEVICE_INFO_H

/* MCU Identification */
typedef enum {
    mcuUnknown = 0,
    mcuPIC18F14K50 = 1,
    mcuPIC32MX795F512L = 2,
    mcuPIC32MX250F128B = 3
} mcu_t;

/* Device Type Identification */
typedef enum {
    dtUnknown = -1,
    dtUSBI2CStandard = 0,
    dtUSBI2CPDTypeC = 1
} dt_t;

/* Board Configuration */
typedef enum {
    bcUnknown = -1,
    bcStandardI2CConfig = 0,
    bcFUSB300Eval = 0x100,
    bcFUSB302FPGA = 0x200,
    bcFM14014 = 0x300
} bc_t;

#ifdef FM141014
#define MY_MCU mcuPIC32MX250F128B
#define MY_DEV_TYPE dtUSBI2CPDTypeC
#define MY_BC bcFM14014
#elif defined FM150911A
#define MY_MCU mcuPIC32MX250F128B
#define MY_DEV_TYPE dtUSBI2CPDTypeC
#define MY_BC bcFM14014                 // TODO: Change this and update GUI
#elif defined FM150105
#define MY_MCU mcuPIC32MX250F128B
#define MY_DEV_TYPE dtUSBI2CPDTypeC
#define MY_BC bcFUSB302FPGA
#elif FM150404A
#define MY_MCU mcuPIC32MX250F128B
#define MY_DEV_TYPE dtUSBI2CPDTypeC
#define MY_BC bcFM14014                 // TODO: Change this and update GUI
#endif


/* check that items were defined */
#ifndef MY_MCU
#error ("MCU not defined properly");
#endif

#ifndef MY_DEV_TYPE
#error ("Device type not defined properly");
#endif

#ifndef MY_BC
#error ("Device type not defined properly");
#endif



#endif	/* DEVICE_INFO_H */

