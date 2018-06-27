/*
 * CANopen_task.c
 *
 *  Created on: 2018Äê6ÔÂ25ÈÕ
 *      Author: cking
 */
#include <stdint.h>
#include <stdbool.h>
#include "canfestival.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "utils/uartstdio.h"
#include "PD4Master.h"
#include "../priorities.h"
#include "PD4_task.h"

#define CANTASKSTACKSIZE 256
xQueueHandle g_MSG_Queue;

static void
CANopen_task(void *pvParameters)
{
    Message recv;
    while(1)
    {
        if( xQueueReceive( g_MSG_Queue, &recv, 0xffff ) == pdPASS)
        {
            canDispatch(&TestMaster_Data, &recv);
        }
    }
}

uint32_t CANopen_taskInit(void)
{
    g_MSG_Queue = xQueueCreate( 5 , sizeof( Message ) );
    //UARTprintf("Create PD4\n");
    //
    // Create the LED task.
    //
    if(xTaskCreate(CANopen_task, (const portCHAR *)"CAN", CANTASKSTACKSIZE, NULL,
                   tskIDLE_PRIORITY + PRIORITY_CAN_TASK, NULL) != pdTRUE)
    {
        return(1);
    }

    //
    // Success.
    //
    return(0);
}
