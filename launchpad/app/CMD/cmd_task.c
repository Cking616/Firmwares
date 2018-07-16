/*
 * cmd_task.c
 *
 *  Created on: 2018\6\3
 *      Author: cking
 */
#include <stdbool.h>
#include <stdint.h>
#include "../priorities.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "bsp/cmdUart.h"
#include "../PD4/PD4_task.h"

#define TESTTASKSTACKSIZE        256         // Stack size in words

#pragma pack(4)
typedef struct {
    unsigned char len;
    char cmd;
    unsigned char data[10]; // data[len - 3] = crc
}_cmd_message;
#pragma pack()

xQueueHandle g_cmd_Queue;
extern SemaphoreHandle_t g_PD4_Semaphore;

inline void _send_cmd(_cmd_message* cmd_)
{
    cmd_uart_send(( unsigned char *)cmd_, cmd_->len);
}

inline void _send_error(char dat)
{
    _cmd_message _t_cmd;
    _t_cmd.cmd = '?';
    _t_cmd.len = 4;
    _t_cmd.data[0] = dat;
    _send_cmd(&_t_cmd);
}

static void
cmd_task(void *pvParameters)
{
    _cmd_message _t_cmd;
    xSemaphoreTake(g_PD4_Semaphore, 0x1000);
    _t_cmd.cmd = '&';
    _t_cmd.len = 3;
    _send_cmd(&_t_cmd);

    _cmd_message _r_cmd;
    int _i;
    _t_cmd.cmd = 'f';
    _t_cmd.len = 8;
    while(1)
    {
        if( xQueueReceive( g_cmd_Queue, &_r_cmd, 0 ) == pdPASS)
        {
            switch(_r_cmd.cmd)
            {
            case 'D':
            {
                if( _t_cmd.len < 7)
                {
                    _send_error(_r_cmd.cmd);
                    break;
                }
                char _nodeId = _r_cmd.data[0];
                int _pos = *(int*) (_r_cmd.data + 1);
                PD4Master_set_pos(_nodeId, _pos);
                break;
            }

            case 'E':
            {
                if( _t_cmd.len < 3)
                {
                    _send_error(_r_cmd.cmd);
                    break;
                }
                char _nodeId = _r_cmd.data[0];
				int _encoder = PD4Master_get_encoder(_nodeId);
				_t_cmd.cmd = 'e';
				_t_cmd.len = 7;
				_t_cmd.data[0] = _nodeId;
				*(int*)(_t_cmd.data + 1) = _encoder;
				_send_cmd(&_t_cmd);
				break;
            }

			case 'F':
			{
				if (_t_cmd.len < 7)
				{
					_send_error(_r_cmd.cmd);
					break;
				}
				char _nodeId = _r_cmd.data[0];
				int _speed = *(int*) (_r_cmd.data + 1);
				PD4Master_set_speed(_nodeId, _speed);
				break;
			}

			case 'G':
			{
				if (_t_cmd.len < 3)
				{
					_send_error(_r_cmd.cmd);
					break;
				}
				char _nodeId = _r_cmd.data[0];
				PD4Master_stop(_nodeId);
				break;
			}
            default:
            {
                break;
            }

            }
        }

        _t_cmd.cmd = '%';
        _t_cmd.len = 7;
        for(_i = 0; _i < 4; _i++)
        {
            _t_cmd.data[_i] = PD4Master_get_flag(_i + 1);
        }

        _send_cmd(&_t_cmd);
        vTaskDelay(100);
    }
}

//*****************************************************************************
//
// Initializes the LED task.
//
//*****************************************************************************
uint32_t
cmd_taskInit(void)
{
    g_cmd_Queue = xQueueCreate( 12 , sizeof( _cmd_message ) );

    //
    // Create the LED task.
    //
    if(xTaskCreate(cmd_task, (const portCHAR *)"CMD", TESTTASKSTACKSIZE, NULL,
                   tskIDLE_PRIORITY + PRIORITY_CMD_TASK, NULL) != pdTRUE)
    {
        return(1);
    }

    //
    // Success.
    //
    return(0);
}
