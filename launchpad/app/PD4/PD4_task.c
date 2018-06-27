/*
 * PD4_task.c
 *
 *  Created on: 2018/5/28
 *      Author: cking
 */

#include <stdbool.h>
#include <stdint.h>
#include "bsp/CO_driver.h"
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
#define PD4TASKSTACKSIZE        256        // Stack size in words


xQueueHandle g_Slave_Queue;
SemaphoreHandle_t g_SDO_Semaphore;
SemaphoreHandle_t g_SDO_Mutex;
SemaphoreHandle_t g_PD4_Semaphore;
bool g_trip_bit4[4] = { 0, 0, 0, 0 };
int g_need_init[4] = { 1, 1, 0, 0 };

int _PD4_speed_tmp = 0;
int _PD4_pos_tmp = 0;

void PD4Master_set_speed(UNS8 nodeID, int speed)
{
    _PD4_speed_tmp = speed;
    PD4Master_writeSlaveParam(&TestMaster_Data, /*CO_Data* d*/
                              nodeID, /*UNS8 nodeId*/
                              0x6081, /*UNS16 index*/
                              0x00, /*UNS16 index*/
                              4, /*UNS8 count*/
                              uint32, /*UNS8 dataType*/
                              &_PD4_speed_tmp); /* use block mode */
}

void PD4Master_set_ctrl(UNS8 nodeID, UNS16 word)
{
    PD4_Controlword[nodeID - 1] = word;
    PD4Master_writeSlaveParam(&TestMaster_Data, /*CO_Data* d*/
                              nodeID, /*UNS8 nodeId*/
                              0x6040, /*UNS16 index*/
                              0x00, /*UNS16 index*/
                              2, /*UNS8 count*/
                              uint16, /*UNS8 dataType*/
                              & PD4_Controlword[nodeID - 1]); /* use block mode */
}

void PD4Master_set_pos(UNS8 nodeID, int pos)
{
    _PD4_pos_tmp = pos;
    //UARTprintf("set id:%d, pos:%d\n", nodeID, pos);
    PD4Master_writeSlaveParam(&TestMaster_Data, /*CO_Data* d*/
                              nodeID, /*UNS8 nodeId*/
                              0x607a, /*UNS16 index*/
                              0x00, /*UNS16 index*/
                              4, /*UNS8 count*/
                              int32, /*UNS8 dataType*/
                              &_PD4_pos_tmp); /* use block mode */
    taskDISABLE_INTERRUPTS();
    PD4Master_set_ctrl(nodeID, 0x3F);
	g_trip_bit4[nodeID - 1] = 1;
	taskENABLE_INTERRUPTS();
}

unsigned char PD4Master_get_flag(unsigned char nodeID)
{
    unsigned char _flag = ((PD4_Status[nodeID - 1] & 0x67) == 0x27) ? 0x10 : 0;
    _flag |= (PD4_Status[nodeID - 1] & 0x400) ? 0x1 : 0;
    return _flag;
}

void PD4Master_stop(unsigned char nodeID)
{
    taskDISABLE_INTERRUPTS();
    PD4Master_set_ctrl(nodeID, 0xB);
    taskENABLE_INTERRUPTS();
}

inline int PD4Master_get_encoder(unsigned char nodeID)
{
	return PD4_Position[nodeID - 1];
}

int __homing_step[4] = { 0, 0, 0, 0 };

inline void PD4_home_loop(int _i)
{
	switch (__homing_step[_i])
	{
	case 0:
	{
		if (PD4_Status[_i] & 0x40)
		{
			PD4_Controlword[_i] = 0x6;
		}
		else if (PD4_Status[_i] & 0x20)
		{
			if (PD4_Status[_i] & 0x2)
			{
				PD4_Controlword[_i] = 0xF;
			}
			else
			{
				PD4_Controlword[_i] = 0x7;
			}
		}

		if ((PD4_Status[_i] & 0x67) == 0x27)
		{
			PD4_Controlword[_i] = 0x3F;
			__homing_step[_i]++;
		}
		break;
	}
	case 1:
	{
		if ((PD4_Status[_i] & 0x3400) == 0x1400)
		{
			PD4_Controlword[_i] = 0x6;
			__homing_step[_i]++;
		}
		else if ((PD4_Status[_i] & 0x3400) == 0x2000)
		{
			PD4_Controlword[_i] = 0x6;
			__homing_step[_i] = 0;
		}

		break;
	}
	case 2:
	{
		if ((PD4_Status[_i] & 0x006F) == 0x21)
		{
			g_need_init[_i] = 0;
            PD4_Mode[_i] = 1;
			__homing_step[_i] = 0;
		}
		break;
	}
	default:
	{
		break;
	}
	}

}

inline void PD4_running_loop(int _i)
{
	if (PD4_Status[_i] & 0x40)
	{
		PD4_Controlword[_i] = 0x6;
	}
	else if (PD4_Status[_i] & 0x20)
	{
		if (PD4_Status[_i] & 0x2)
		{
			PD4_Controlword[_i] = 0xF;
		}
		else
		{
			PD4_Controlword[_i] = 0x7;
		}
	}

	if ((PD4_Status[_i] & 0x67) == 0x27)
	{
		if (g_trip_bit4[_i])
		{
			PD4_Controlword[_i] = 0x3F;
			taskDISABLE_INTERRUPTS();
			g_trip_bit4[_i] = 0;
			taskENABLE_INTERRUPTS();
		}
		else
		{
			PD4_Controlword[_i] = 0x2F;
		}
	}
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
	bool	 PD4_bConnected[4] = { 0, 0, 0, 0 };

	//UARTprintf("PD4 init 1\n");

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
    CO_timer_start();
    vTaskDelay(10);
    setState(&TestMaster_Data, Initialisation);     // Init the state
    setState(&TestMaster_Data, Pre_operational);
    vTaskDelay(10);

    //masterSendNMTstateChange(&TestMaster_Data, 0x03, NMT_Enter_PreOperational);
    //
    // Initialize the LED Toggle Delay to default value.
    //
    ui32PD4ToggleDelay = 20;

    //
    // Get the current tick count.
    //
    ui32WakeTime = xTaskGetTickCount();
    //
    // Loop forever.
    //
    //UARTprintf("PD4 init 2\n");
    masterSendNMTstateChange(&TestMaster_Data, 0x01, NMT_Enter_PreOperational);
    vTaskDelay(10);
    masterSendNMTstateChange(&TestMaster_Data, 0x02, NMT_Enter_PreOperational);
    vTaskDelayUntil(&ui32WakeTime, 200 / portTICK_RATE_MS);

    while(1)
    {
        UNS8 nodeId;

        if( xQueueReceive( g_Slave_Queue, &nodeId, 0xffff ) == pdPASS)
        {
            PD4Master_confSlaveNode(&TestMaster_Data, nodeId);
            PD4_bConnected[nodeId - 1] = 1;
            PD4_Controlword[nodeId - 1] = 0x86;


			if(PD4_bConnected[1] && PD4_bConnected[0])
			{
				//UARTprintf("op mode\n");
			    //masterSendNMTstateChange (&TestMaster_Data, 1, NMT_Start_Node);
			    //vTaskDelay(10);
			    //masterSendNMTstateChange (&TestMaster_Data, 4, NMT_Start_Node);
			    //vTaskDelay(10);
                masterSendNMTstateChange (&TestMaster_Data, 1, NMT_Start_Node);
                vTaskDelay(10);
			    masterSendNMTstateChange (&TestMaster_Data, 2, NMT_Start_Node);
			    vTaskDelay(10);
				setState(&TestMaster_Data, Operational);
				xSemaphoreGive(g_PD4_Semaphore);
				break;
			}
        }
    }

    while(1)
    {
        int _i = 0;

        for (_i = 0; _i < 4; _i++)
        {
            if (!PD4_bConnected[_i])
            {
                continue;
            }

            taskDISABLE_INTERRUPTS();
            sendPDOrequest(&TestMaster_Data, 0x1400 + _i);
            taskENABLE_INTERRUPTS();
        }

        for (_i = 0; _i < 4; _i++)
        {
            if (!PD4_bConnected[_i])
            {
                continue;
            }

			if (!g_need_init[_i])
			{
				PD4_running_loop(_i);
			}
			else
			{
				PD4_home_loop(_i);
			}
        }

        vTaskDelayUntil(&ui32WakeTime, ui32PD4ToggleDelay / portTICK_RATE_MS);

        for (_i = 0; _i < 4; _i++)
        {
            if (!PD4_bConnected[_i])
            {
                continue;
            }
            taskDISABLE_INTERRUPTS();
            sendOnePDOevent(&TestMaster_Data, _i);
            taskENABLE_INTERRUPTS();
        }
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
    g_PD4_Semaphore = xSemaphoreCreateBinary();
    //UARTprintf("Create PD4\n");
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
