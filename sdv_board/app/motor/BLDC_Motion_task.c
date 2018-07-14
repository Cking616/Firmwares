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
#include "BLDC_Motion_task.h"
#include "speed_controller.h"
#include "pos_controller.h"

#define TESTTASKSTACKSIZE        256         // Stack size in words

int g_speed = 150;
int g_inc_acc_tick = 0;
int g_dec_acc_tick = 0;
int g_end_tick = 0;
int g_a_mol = 3;
int g_a_den = 5;
int g_target_pos = 0;
int g_cur_ol_encoder = 0;
int g_BLDC_flag = 1;
int g_dir = 1;
int g_stop = 0;
SemaphoreHandle_t g_BLDC_Semaphore;
SemaphoreHandle_t g_BLDC_Mutex;

void _motion_function(int _tick)
{
    int add = 0;
	if (_tick < g_inc_acc_tick)
	{
	    add = g_dir * g_a_mol * _tick / g_a_den;
		g_cur_ol_encoder = g_cur_ol_encoder + add;
		pos_controller_set_pos(0, g_cur_ol_encoder, add);
		pos_controller_set_pos(1, g_cur_ol_encoder, add);
	}
	else if (_tick >= g_inc_acc_tick && _tick < g_dec_acc_tick)
	{
	    add = g_dir * g_speed;
		g_cur_ol_encoder = g_cur_ol_encoder + add;
		pos_controller_set_pos(0, g_cur_ol_encoder, add);
		pos_controller_set_pos(1, g_cur_ol_encoder, add);
	}
	else if (_tick >= g_dec_acc_tick && _tick <= g_end_tick)
	{
	    add = g_dir * g_a_mol * (g_end_tick - _tick) / g_a_den;
		g_cur_ol_encoder = g_cur_ol_encoder + add;
		pos_controller_set_pos(0, g_cur_ol_encoder, add);
		pos_controller_set_pos(1, g_cur_ol_encoder, add);
	}
	else
	{
	    g_cur_ol_encoder = g_target_pos;
		pos_controller_set_pos(0, g_cur_ol_encoder, 0);
		pos_controller_set_pos(1, g_cur_ol_encoder, 0);
	}
}

int BLDC_Motion_get_flag()
{
	int _encoder = pos_controller_get_encoder(0);
	int flag = 0;
	if (g_target_pos - _encoder <= 40 && g_target_pos - _encoder >= -40)
	{
	    flag =  1;
	}
	flag |= g_BLDC_flag ? 0x10 : 0;
	return flag;
}

int BLDC_Motion_start(unsigned int speed, int _pos, unsigned int a_mol)
{
	if (xSemaphoreTake(g_BLDC_Mutex, 5) == pdTRUE)
	{
	    taskDISABLE_INTERRUPTS();
		g_a_mol = a_mol;
		int _acc_pos = speed * speed * g_a_den / a_mol;
		int _dis = _pos - g_cur_ol_encoder;
		if(_dis < 0)
		{
		    g_dir = -1;
		    _dis = -_dis;
		}
		else
		{
		    g_dir = 1;
		}
		g_target_pos = _pos;
		/*Acceleration distance is not enough, the speed will be automatically reduced*/
		while (_dis < 2 * _acc_pos)
		{	
			speed = speed - 5;
			_acc_pos = speed * speed * g_a_den / a_mol;
		}
		g_speed = speed;
		g_inc_acc_tick = speed * g_a_den / a_mol;
		g_dec_acc_tick = g_inc_acc_tick + (_dis - _acc_pos) / speed;
		g_end_tick = g_dec_acc_tick + g_inc_acc_tick;
		g_BLDC_flag = 0;
		taskENABLE_INTERRUPTS();
		xSemaphoreGive(g_BLDC_Semaphore);
		return 1;
	}
	return 0;
}

void BLDC_Motion_stop()
{
    taskDISABLE_INTERRUPTS();
    g_stop = 1;
    taskENABLE_INTERRUPTS();
}

int BLDC_Motion_get_encoder(void)
{
	return pos_controller_get_encoder(0);
}

static void BLDC_Motion_task(void *pvParameters)
{
    portTickType ui32WakeTime;
    ui32WakeTime = xTaskGetTickCount();

	int _i = 1;
	int _ctrl_tick = 1;
	int _start_motion = 0;
    while(1)
    {
        if (xSemaphoreTake(g_BLDC_Semaphore, 0) == pdTRUE)
        {
            taskDISABLE_INTERRUPTS();
            _start_motion = 1;
            g_stop = 0;
            taskENABLE_INTERRUPTS();
        }

        taskDISABLE_INTERRUPTS();
        speed_controller_period(0);
        speed_controller_period(1);
        if(_ctrl_tick % 5 == 0)
        {
            pos_controller_period(0);
            pos_controller_period(1);
        }
        taskENABLE_INTERRUPTS();

        if(_ctrl_tick % 10 == 0)
        {
            if(_start_motion)
            {
                if (_i == g_end_tick + 5 || g_stop)
                {
                    taskDISABLE_INTERRUPTS();
                    _start_motion = 0;
                    g_BLDC_flag = 1;
                    _i = 1;
                    taskENABLE_INTERRUPTS();

                    xSemaphoreGive(g_BLDC_Mutex);
                }

				_motion_function(_i);
                _i++;
            }
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

uint32_t
BLDC_Motion_taskInit(void)
{
    speed_controller_init(0);
    speed_controller_init(1);
    pos_controller_init(0);
    pos_controller_init(1);

    g_cur_ol_encoder = pos_controller_get_encoder(0);

	g_BLDC_Mutex = xSemaphoreCreateMutex();
	g_BLDC_Semaphore = xSemaphoreCreateBinary();
    //
    // Create the LED task.
    //
    if(xTaskCreate(BLDC_Motion_task, (const portCHAR *)"MOT", TESTTASKSTACKSIZE, NULL,
                   tskIDLE_PRIORITY + PRIORITY_MOT_TASK, NULL) != pdTRUE)
    {
        return(1);
    }

    //
    // Success.
    //
    return(0);
}
