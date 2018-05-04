#ifndef _FSCTYPES_H_
#define _FSCTYPES_H_

#if !defined(__PACKED)
    #define __PACKED
#endif

// Length of the hostcomm buffer, needed in both core and platform
#define FSC_HOSTCOMM_BUFFER_SIZE    64

typedef enum _BOOL { FALSE = 0, TRUE } FSC_BOOL;

typedef signed char         FSC_S8;
typedef signed short int    FSC_S16;
typedef signed long int     FSC_S32;

typedef unsigned char       FSC_U8;
typedef unsigned short int  FSC_U16;
typedef unsigned long int   FSC_U32;

#endif // _FSCTYPES_H_

