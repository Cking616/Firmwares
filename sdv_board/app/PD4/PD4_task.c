/*
 * PD4_task.c
 *
 *  Created on: 2018/5/28
 *      Author: cking
 */

#include <stdbool.h>
#include <stdint.h>
#include "bps/lights.h"
#include "utils/uartstdio.h"
#include "../priorities.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "Master.h"
#include "PD4Master.h"
#include "PD4_task.h"
#include "utils/uartstdio.h"
 //*****************************************************************************
 //
 // The stack size for the LED toggle task.
 //
 //*****************************************************************************
#define PD4TASKSTACKSIZE        128        // Stack size in words


xQueueHandle g_Slave_Queue;
SemaphoreHandle_t g_SDO_Semaphore;
SemaphoreHandle_t g_SDO_Mutex;

void PD4Master_set_speed(UNS8 nodeID, void* speed)
{
    PD4Master_writeSlaveParam(&TestMaster_Data, /*CO_Data* d*/
                              nodeID, /*UNS8 nodeId*/
                              0x6081, /*UNS16 index*/
                              0x00, /*UNS16 index*/
                              4, /*UNS8 count*/
                              uint32, /*UNS8 dataType*/
                              speed); /* use block mode */
}

void PD4Master_set_pos(UNS8 nodeID, void* pos)
{
    PD4Master_writeSlaveParam(&TestMaster_Data, /*CO_Data* d*/
                              nodeID, /*UNS8 nodeId*/
                              0x607a, /*UNS16 index*/
                              0x00, /*UNS16 index*/
                              4, /*UNS8 count*/
                              int32, /*UNS8 dataType*/
                              pos); /* use block mode */
}
//*****************************************************************************
//
// This task toggles the user selected LED at a user selected frequency. User
// can make the selections by pressing the left and right buttons.
//
//*****************************************************************************
static void
PD4Master_task(void *pvParameters)
{
    portTickType ui32WakeTime;
    uint32_t ui32PD4ToggleDelay;
    //uint8_t i8Message;

    TestMaster_Data.heartbeatError = PD4Master_heartbeatError;
    TestMaster_Data.initialisation = PD4Master_initialisation;
    TestMaster_Data.preOperational = PD4Master_preOperational;
    TestMaster_Data.operational = PD4Master_operational;
    TestMaster_Data.stopped = PD4Master_stopped;
    TestMaster_Data.post_sync = PD4Master_post_sync;
    TestMaster_Data.post_TPDO = PD4Master_post_TPDO;
    TestMaster_Data.post_emcy = PD4Master_post_emcy;
    TestMaster_Data.post_SlaveStateChange = PD4Master_post_SlaveStateChange;

    setNodeId(&TestMaster_Data, 0x7F);
    setState(&TestMaster_Data, Initialisation);     // Init the state
    setState(&TestMaster_Data, Pre_operational);

    //
    // Initialize the LED Toggle Delay to default value.
    //
    ui32PD4ToggleDelay = 10;

    //
    // Get the current tick count.
    //
    ui32WakeTime = xTaskGetTickCount();
    //
    // Loop forever.
    //
    while(1)
    {
        UNS8 nodeId;
        if( xQueueReceive( g_Slave_Queue, &nodeId, 2 / portTICK_RATE_MS ) == pdPASS)
        {
            PD4Master_confSlaveNode(&TestMaster_Data, nodeId);
            setState(&TestMaster_Data, Operational);
            PD4_Contolword_2 = 0x86;
            /* Ask slave node to go in operational mode */
            //masterSendNMTstateChange (&TestMaster_Data, nodeId, NMT_Start_Node);
        }

        if(PD4_Statusword_2 & 0x40)
        {
            PD4_Contolword_2 = 0x6;
        }
        else if(PD4_Statusword_2 & 0x20)
        {
            if(PD4_Statusword_2 & 0x2)
            {
                PD4_Contolword_2 = 0xF;
            }
            else
            {
                PD4_Contolword_2 = 0x7;
            }
        }

        if((PD4_Statusword_2 & 0x67) == 0x27)
        {
            //PD4_Contolword_2 |= 0x30;
            if((PD4_Statusword_2 & 0x400))
            {
                PD4_Contolword_2 = 0x0F;
            }
            else
            {
                PD4_Contolword_2 = 0x3F;
            }
        }

        if(getState(&TestMaster_Data) == Operational)
        {
            sendPDOevent(&TestMaster_Data);
            sendPDOrequest(&TestMaster_Data, 0x1400);
        }
        //
        // Wait for the required amount of time.
        //
        //UARTprintf("s:0x%X,c:0x%X,p:%d\n", PD4_Statusword_2, PD4_Contolword_2, PD4_Position_2);
        vTaskDelayUntil(&ui32WakeTime, ui32PD4ToggleDelay / portTICK_RATE_MS);
    }
}

//*****************************************************************************
//
// Initializes the LED task.
//
//*****************************************************************************
uint32_t
PD4Master_taskInit(void)
{
    g_Slave_Queue = xQueueCreate( 4 , sizeof( UNS8 ) );
    g_SDO_Mutex = xSemaphoreCreateMutex();
    g_SDO_Semaphore = xSemaphoreCreateBinary();

    //
    // Create the LED task.
    //
    if(xTaskCreate(PD4Master_task, (const portCHAR *)"PD4", PD4TASKSTACKSIZE, NULL,
                   tskIDLE_PRIORITY + PRIORITY_PD4_TASK, NULL) != pdTRUE)
    {
        return(1);
    }

    //
    // Success.
    //
    return(0);
}
