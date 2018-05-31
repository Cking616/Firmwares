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

#define TESTTASKSTACKSIZE        128         // Stack size in words

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
SemaphoreHandle_t g_BLDC_Semaphore;
SemaphoreHandle_t g_BLDC_Mutex;

void _motion_function(int _tick)
{
	if (_tick < g_inc_acc_tick)
	{
		g_cur_ol_encoder = g_cur_ol_encoder + g_dir * g_a_mol * _tick / g_a_den;
		pos_controller_set_pos(0, g_cur_ol_encoder);
		pos_controller_set_pos(1, g_cur_ol_encoder);
	}
	else if (_tick >= g_inc_acc_tick && _tick < g_dec_acc_tick)
	{
		g_cur_ol_encoder = g_cur_ol_encoder + g_dir * g_speed;
		pos_controller_set_pos(0, g_cur_ol_encoder);
		pos_controller_set_pos(1, g_cur_ol_encoder);
	}
	else if (_tick >= g_dec_acc_tick && _tick <= g_end_tick)
	{
		g_cur_ol_encoder = g_cur_ol_encoder + g_dir * g_a_mol * (g_end_tick - _tick) / g_a_den;
		pos_controller_set_pos(0, g_cur_ol_encoder);
		pos_controller_set_pos(1, g_cur_ol_encoder);
	}
	else
	{
	    g_cur_ol_encoder = g_target_pos;
		pos_controller_set_pos(0, g_cur_ol_encoder);
		pos_controller_set_pos(1, g_cur_ol_encoder);
	}
}

int BLDC_Motion_is_end()
{
	int _encoder = pos_controller_get_encoder(0);
	if (g_target_pos - _encoder < 20)
	{
		return pos_controller_get_flag(0) && g_BLDC_flag;
	}
	return 0;
}

int BLDC_Motion_start(unsigned int speed, int _pos, unsigned int a_mol)
{
	if (xSemaphoreTake(g_BLDC_Mutex, 0xffff) == pdTRUE)
	{
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
		//UARTprintf("S:%d,dir:%d,p:%d,inc:%d,dec:%d,end:%d,op:%d\n", g_speed, g_dir, g_target_pos,g_inc_acc_tick,g_dec_acc_tick,g_end_tick,g_cur_ol_encoder);
		xSemaphoreGive(g_BLDC_Semaphore);
		return 1;
	}
	return 0;
}

static void BLDC_Motion_task(void *pvParameters)
{
    portTickType ui32WakeTime;
    //
    ui32WakeTime = xTaskGetTickCount();
	g_cur_ol_encoder = pos_controller_get_encoder(0);
	int _i = 1;
    while(1)
    {
		if (xSemaphoreTake(g_BLDC_Semaphore, 0xffff) == pdTRUE)
		{
			while (1)
			{
				if (_i == g_end_tick + 3)
				{
					xSemaphoreGive(g_BLDC_Mutex);
					g_BLDC_flag = 1;
					_i = 1;
					break;
				}
				_motion_function(_i);
				vTaskDelayUntil(&ui32WakeTime, 10 / portTICK_RATE_MS);
				_i++;
			}
		}
    }
}

uint32_t
BLDC_Motion_taskInit(void)
{
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
