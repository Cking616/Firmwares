/*
 * test_BLDC_task.c
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
#include "pos_controller.h"
#include "../PD4/PD4_task.h"

#define TESTTASKSTACKSIZE        128         // Stack size in words

int _pos = -800000;
int _i = 1;
int g_target_encoder = 0;
// you should change position like this.
// move to 20000, a = 2
void test_pos(int _tick)
{
     if(_tick < 50)
     {
         g_target_encoder = g_target_encoder + 2 * _tick;
         pos_controller_set_pos(0, g_target_encoder);
         pos_controller_set_pos(1, g_target_encoder);
     }
     else if(_tick >= 50 && _tick < 200)
     {
         g_target_encoder = g_target_encoder + 100;
         pos_controller_set_pos(0, g_target_encoder);
         pos_controller_set_pos(1, g_target_encoder);
     }
     else if(_tick >= 200 && _tick <= 250)
     {
         g_target_encoder = g_target_encoder + 2 * (250 - _tick);
         pos_controller_set_pos(0, g_target_encoder);
         pos_controller_set_pos(1, g_target_encoder);
     }
}

void test_pos2(int _tick)
{
    if(_tick < 100)
    {
        g_target_encoder = g_target_encoder - 2 * _tick;
        pos_controller_set_pos(0, g_target_encoder);
        pos_controller_set_pos(1, g_target_encoder);
    }
    else if(_tick >= 100 && _tick < 400)
    {
        g_target_encoder = g_target_encoder - 200;
        pos_controller_set_pos(0, g_target_encoder);
        pos_controller_set_pos(1, g_target_encoder);
    }
    else if(_tick >= 400 && _tick <= 500)
    {
        g_target_encoder = g_target_encoder - 2 * (500 - _tick);
        pos_controller_set_pos(0, g_target_encoder);
        pos_controller_set_pos(1, g_target_encoder);
    }
}

static void test_BLDC_task(void *pvParameters)
{
    portTickType ui32WakeTime;
    //
    ui32WakeTime = xTaskGetTickCount();

    while(1)
    {
        if(_i <= 250)
        {
            test_pos(_i);
        }

        if(_i >= 550 && _i <= 1050)
        {
            test_pos2(_i - 550);
        }


        if(_i >= 1350 && _i <= 1600)
        {
            test_pos(_i - 1350);
        }

        if(_i >= 1900 && _i <= 2150)
        {
            test_pos(_i - 1900);
        }

        if(_i >= 2450 && _i <= 2700)
        {
            test_pos(_i - 2450);
        }

        if(_i == 3000)
        {
            _i = 1;
            _pos = -_pos;
            PD4Master_set_pos(2, &_pos);
        }

        vTaskDelayUntil(&ui32WakeTime, 10 / portTICK_RATE_MS);
        _i ++;
    }
}

uint32_t
test_BLDC_taskInit(void)
{
    //
    // Create the LED task.
    //
    if(xTaskCreate(test_BLDC_task, (const portCHAR *)"TEST", TESTTASKSTACKSIZE, NULL,
                   tskIDLE_PRIORITY + PRIORITY_TEST_TASK, NULL) != pdTRUE)
    {
        return(1);
    }

    //
    // Success.
    //
    return(0);
}
