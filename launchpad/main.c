#include <stdbool.h>
#include <stdint.h>
#include "bsp/driver.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "app/PD4/PD4_task.h"
#include "app/CMD/cmd_task.h"
#include "app/led_task.h"
//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}

#endif

//*****************************************************************************
//
// This hook is called by FreeRTOS when an stack overflow error is detected.
//
//*****************************************************************************
void
vApplicationStackOverflowHook(xTaskHandle *pxTask, char *pcTaskName)
{
    //
    // This function can not return, so loop forever.  Interrupts are disabled
    // on entry to this function, so no processor interrupts will interrupt
    // this loop.
    //
    while(1)
    {
    }
}

/**
 * main.c
 */
int main(void)
{
    driver_init_hardware();

    driver_init_system();

    if(CANopen_taskInit() != 0)
    {

        while(1)
        {
        }
    }
//#ifdef 0
    if(PD4Master_taskInit() != 0)
    {

        while(1)
        {
        }
    }

    if(cmd_taskInit() != 0)
    {

        while(1)
        {
        }
    }


    //
    // Create the LED task.
    //
    if(LEDTaskInit() != 0)
    {

        while(1)
        {
        }
    }
//#endif
    // Start the scheduler.  This should not return.
    //
    vTaskStartScheduler();

    //
    // In case the scheduler returns for some reason, print an error and loop
    // forever.
    //

    while(1)
    {
    }
}
