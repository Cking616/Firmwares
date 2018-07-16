/*
 * led_task.c
 *
 *  Created on:  2018/5/28
 *      Author: cking
 */

#include <stdbool.h>
#include <stdint.h>
#include "utils/uartstdio.h"
#include "led_task.h"
#include "priorities.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "PD4Master.h"
#include "PD4/PD4_task.h"
#include "bsp/MA3encoder.h"
//*****************************************************************************
//
// The stack size for the LED toggle task.
//
//*****************************************************************************
#define LEDTASKSTACKSIZE        256         // Stack size in words


//*****************************************************************************
//
// Default LED toggle delay value. LED toggling frequency is twice this number.
//
//*****************************************************************************
#define LED_TOGGLE_DELAY        5

extern SemaphoreHandle_t g_PD4_Semaphore;
extern int g_need_init[4];
//*****************************************************************************
//
// This task toggles the user selected LED at a user selected frequency. User
// can make the selections by pressing the left and right buttons.
//
//*****************************************************************************
static void
LEDTask(void *pvParameters)
{
    portTickType ui32WakeTime;
    uint32_t ui32LEDToggleDelay;
    //uint8_t i8Message;

    //
    // Initialize the LED Toggle Delay to default value.
    //
    ui32LEDToggleDelay = LED_TOGGLE_DELAY;

    //
    // Get the current tick count.
    //
    ui32WakeTime = xTaskGetTickCount();

    int Nodeid = 3;
    int Nodeid2 = 2;
    //int _tick = 0;
    //
    // Loop forever.
    //
    while(g_need_init[Nodeid - 1])
    {
        UARTprintf("3s:0x%X,c:0x%X,p:%d\n", PD4_Status[Nodeid - 1], PD4_Controlword[Nodeid - 1], PD4_Position[Nodeid - 1]);
        vTaskDelay(1000);
    }

    while(g_need_init[Nodeid2 - 1])
    {
        UARTprintf("2s:0x%X,c:0x%X,p:%d\n", PD4_Status[Nodeid2 - 1], PD4_Controlword[Nodeid2 - 1], PD4_Position[Nodeid2 - 1]);
        vTaskDelay(1000);
    }

    while((PD4_Status[Nodeid - 1] & 0x67) != 0x27)
    {
        UARTprintf("3s:0x%X,c:0x%X,p:%d\n", PD4_Status[Nodeid - 1], PD4_Controlword[Nodeid - 1], PD4_Position[Nodeid - 1]);
        vTaskDelay(1000);
    }

    while((PD4_Status[Nodeid2 - 1] & 0x67) != 0x27)
    {
        UARTprintf("2s:0x%X,c:0x%X,p:%d\n", PD4_Status[Nodeid2 - 1], PD4_Controlword[Nodeid2 - 1], PD4_Position[Nodeid2 - 1]);
        vTaskDelay(1000);
    }

    PD4Master_set_speed(Nodeid2, 350);
    PD4Master_set_speed(Nodeid, 2500);

    while(1)
    {
        //PD4Master_set_pos(Nodeid, 100);
        PD4Master_set_pos(Nodeid2, 55000);
        //_tick++;
        //if(_tick == 200)
        //{
        //    _tick = 0;
        //    UARTprintf("2s:0x%X,c:0x%X,p:%d\n", PD4_Status[1], PD4_Controlword[1], PD4_Position[1]);
        //}
        vTaskDelay(50);

        while(!(PD4_Status[Nodeid2 - 1] & 0x400))
        {
            UARTprintf("2s:0x%X,c:0x%X,p:%d\n", PD4_Status[Nodeid2 - 1], PD4_Controlword[Nodeid2 - 1], PD4_Position[Nodeid2 - 1]);
            vTaskDelay(1000);
        }
        vTaskDelay(50);
        //int encoder = MA3_encoder_get_value();
        UARTprintf("2s:0x%X,c:0x%X,p:%d\n", PD4_Status[Nodeid2 - 1], PD4_Controlword[Nodeid2 - 1], PD4_Position[Nodeid2 - 1]);

        vTaskDelay(1500);

        PD4Master_set_pos(Nodeid2, 1000);
        //_tick++;
        //if(_tick == 200)
        //{
        //    _tick = 0;
        //    UARTprintf("2s:0x%X,c:0x%X,p:%d\n", PD4_Status[1], PD4_Controlword[1], PD4_Position[1]);
        //}
        vTaskDelay(50);

        while(!(PD4_Status[Nodeid2 - 1] & 0x400))
        {
            UARTprintf("2s:0x%X,c:0x%X,p:%d\n", PD4_Status[Nodeid2 - 1], PD4_Controlword[Nodeid2 - 1], PD4_Position[Nodeid2 - 1]);
            vTaskDelay(1000);
        }
        vTaskDelay(50);
        //int encoder = MA3_encoder_get_value();
        UARTprintf("2s:0x%X,c:0x%X,p:%d\n", PD4_Status[Nodeid2 - 1], PD4_Controlword[Nodeid2 - 1], PD4_Position[Nodeid2 - 1]);

        vTaskDelay(1500);

        PD4Master_set_pos(Nodeid, 10000);
        vTaskDelay(50);

        while(!(PD4_Status[Nodeid - 1] & 0x400))
        {
            UARTprintf("3s:0x%X,c:0x%X,p:%d\n", PD4_Status[Nodeid - 1], PD4_Controlword[Nodeid - 1], PD4_Position[Nodeid - 1]);
            vTaskDelay(1000);
        }
        vTaskDelay(50);
        //encoder = MA3_encoder_get_value();
        UARTprintf("3s:0x%X,c:0x%X,p:%d\n", PD4_Status[Nodeid - 1], PD4_Controlword[Nodeid - 1], PD4_Position[Nodeid - 1]);

        vTaskDelay(1500);

        PD4Master_set_pos(Nodeid, 0);
        vTaskDelay(50);

        while(!(PD4_Status[Nodeid - 1] & 0x400))
        {
            UARTprintf("3s:0x%X,c:0x%X,p:%d\n", PD4_Status[Nodeid - 1], PD4_Controlword[Nodeid - 1], PD4_Position[Nodeid - 1]);
            vTaskDelay(1000);
        }
        vTaskDelay(50);
        //encoder = MA3_encoder_get_value();
        UARTprintf("3s:0x%X,c:0x%X,p:%d\n", PD4_Status[Nodeid - 1], PD4_Controlword[Nodeid - 1], PD4_Position[Nodeid - 1]);

        vTaskDelay(1500);
        //PD4Master_set_pos(Nodeid,0);
        //UARTprintf("3s:0x%X,c:0x%X,p:%d\n", PD4_Status[2], PD4_Controlword[2], PD4_Position[2]);

        //UARTprintf("4s:0x%X,c:0x%X,p:%d\n", PD4_Status[3], PD4_Controlword[3], PD4_Position[3]);
    }
}

//*****************************************************************************
//
// Initializes the LED task.
//
//*****************************************************************************
uint32_t
LEDTaskInit(void)
{
    //
    // Create the LED task.
    //
    if(xTaskCreate(LEDTask, (const portCHAR *)"LED", LEDTASKSTACKSIZE, NULL,
                   tskIDLE_PRIORITY + PRIORITY_LED_TASK, NULL) != pdTRUE)
    {
        return(1);
    }

    //
    // Success.
    //
    return(0);
}


