/*
 * BLDC_task.c
 *
 *  Created on: 2018/5/29
 *      Author: cking
 */

#include <stdbool.h>
#include <stdint.h>
#include "utils/uartstdio.h"
#include "../priorities.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "speed_controller.h"
#include "pos_controller.h"


#define BLDCTASKSTACKSIZE        128         // Stack size in words

//*****************************************************************************
//
// This task toggles the user selected LED at a user selected frequency. User
// can make the selections by pressing the left and right buttons.
//
//*****************************************************************************
static void BLDC_task(void *pvParameters)
{
    portTickType ui32WakeTime;
    //
    ui32WakeTime = xTaskGetTickCount();
	int _ctrl_tick = 0;
    //
    // Loop forever.
    //
    while(1)
    {
        speed_controller_period(0);
        speed_controller_period(1);
        if(_ctrl_tick % 5 == 0)
        {
            pos_controller_period(0);
            pos_controller_period(1);
        }
        vTaskDelayUntil(&ui32WakeTime, 1 / portTICK_RATE_MS);
        if(_ctrl_tick == 999)
        {
            _ctrl_tick = 0;
        }
        else
        {
            _ctrl_tick ++;
        }
    }
}

//*****************************************************************************
//
// Initializes the LED task.
//
//*****************************************************************************
uint32_t
BLDC_taskInit(void)
{
    speed_controller_init(0);
    speed_controller_init(1);
    pos_controller_init(0);
    pos_controller_init(1);
    //
    // Create the LED task.
    //
    if(xTaskCreate(BLDC_task, (const portCHAR *)"MCTRL", BLDCTASKSTACKSIZE, NULL,
                   tskIDLE_PRIORITY + PRIORITY_MCTRL_TASK, NULL) != pdTRUE)
    {
        return(1);
    }

    //
    // Success.
    //
    return(0);
}


