/*****************************************************************************
 * FileName:        Main.c
 * Processor:       PIC32
 * Compiler:        MPLAB XC32
 * Company:         Fairchild Semiconductor
 *****************************************************************************/

#include "NONE_Main.h"
#include "../core/core.h"

#define MSG_LENGTH      64

/*******************************************************************************
 * Function:        main
 * Input:           None
 * Return:          None
 * Description:     Program entry point and container of main loop
 ******************************************************************************/
int main( void )
{
    InitializeSystem();

    while (1)
    {
        // Run the Type-C state machine
        core_state_machine();
    }
}


/*******************************************************************************
 * Function:        static void InitializeSystem(void)
 * Input:           None
 * Return:          None
 * Description:     InitializeSystem is a centralize initialization routine.
 ******************************************************************************/
static void InitializeSystem(void)
{
    /* Initialize the system */
    /* Timers, GPIO, Type-C/PD configuration, etc... */

    core_initialize();
    core_enable_typec(TRUE);
}

