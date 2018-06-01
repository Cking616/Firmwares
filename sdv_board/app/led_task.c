/*
 * led_task.c
 *
 *  Created on:  2018/5/28
 *      Author: cking
 */

#include <stdbool.h>
#include <stdint.h>
#include "bps/lights.h"
#include "utils/uartstdio.h"
#include "led_task.h"
#include "priorities.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "PD4Master.h"
#include "motor/speed_controller.h"
#include "motor/BLDC_Motion_task.h"
#include "motor/pos_controller.h"
#include "PD4/PD4_task.h"
//*****************************************************************************
//
// The stack size for the LED toggle task.
//
//*****************************************************************************
#define LEDTASKSTACKSIZE        128         // Stack size in words


//*****************************************************************************
//
// Default LED toggle delay value. LED toggling frequency is twice this number.
//
//*****************************************************************************
#define LED_TOGGLE_DELAY        500


//
// [G, R, B] range is 0 to 0xFFFF per color.
//
static uint8_t g_pRgbColors = LIGHTS_RGB_RED;
static uint8_t g_ui8red = 0;
static uint8_t g_ui8green = 1;
extern xSemaphoreHandle g_pUARTSemaphore;
extern SemaphoreHandle_t g_PD4_Semaphore;
//*****************************************************************************
//
// This task toggles the user selected LED at a user selected frequency. User
// can make the selections by pressing the left and right buttons.
//
//*****************************************************************************
int _pos = -200000;
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
    int _step = 0;

    xSemaphoreTake(g_PD4_Semaphore, 0xffff);

    //
    // Loop forever.
    //
    while(1)
    {
        //
        // Turn on the LED.
        //
        g_ui8red = !g_ui8red;
        g_ui8green = !g_ui8green;

        lights_turn_rgb(g_pRgbColors);
        lights_turn_led_green(g_ui8green);
        lights_turn_led_red(g_ui8red);
        //
        // Wait for the required amount of time.
        //
        vTaskDelayUntil(&ui32WakeTime, ui32LEDToggleDelay / portTICK_RATE_MS);
        g_pRgbColors = g_pRgbColors >> 1;
        if(g_pRgbColors == 0)
        {
            g_pRgbColors = LIGHTS_RGB_RED;
        }

        switch(_step)
        {
        case 0:
            _pos = -_pos;
            BLDC_Motion_start(200, _pos, 3);
            vTaskDelay(100 / portTICK_RATE_MS);
            _step++;
            break;
        case 1:
            if(BLDC_Motion_is_end())
            {
                _step++;
                break;
            }
            else
            {
                break;
            }
        case 2:
            PD4Master_set_pos(2, _pos);
            vTaskDelay(100 / portTICK_RATE_MS);
            _step++;
            break;
        case 3:
            if(PD4_Status[1] & 0x400)
            {
                _step++;
                break;
            }
            else
            {
                break;
            }
        case 4:
            PD4Master_set_pos(3, _pos);
            vTaskDelay(100 / portTICK_RATE_MS);
            _step++;
            break;
        case 5:
            if(PD4_Status[2] & 0x400)
            {
                _step++;
                break;
            }
            else
            {
                break;
            }
        default:
            _step = 0;
            break;
        }
        //pos_controller_print(0);
        //speed_controller_print(0);
        //speed_controller_print(1);
        //UARTprintf("2s:0x%X,c:0x%X,p:%d\n", PD4_Status[1], PD4_Controlword[1], PD4_Position[1]);
        //UARTprintf("3s:0x%X,c:0x%X,p:%d\n", PD4_Status[2], PD4_Controlword[2], PD4_Position[2]);
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
    lights_turn_rgb(0);

    lights_turn_led_red(0);

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


