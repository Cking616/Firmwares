/*
 * period.c
 *
 *  Created on: 2018Äê5ÔÂ15ÈÕ
 *      Author: cking
 */
#include <stdbool.h>
#include <stdint.h>
#include "bsp/driver.h"
#include "task/blinky.h"
#include "task/stepperctrl.h"
#include "task/cmdpool.h"
#include "utils/uartstdio.h"
#include "bsp/stepmotor.h"

int _testspeed[4] = {400, 0, -400, 0};
int _testi = 0;
int _tick = 0;
volatile unsigned int _tick_second = 0;

// period: 1ms
inline void on_sys_period(void)
{
    stepperctrl_thread();

    if(_tick == 2999)
    {
        _tick = 0;

        blinky_thread();

        _tick_second++;
        UARTprintf("Tick Time!\n");

        step_motor_set_speed(0, _testspeed[_testi], 1000);
        _testi = (_testi + 1) % 4;
        //stepperctrl_set_speed(_testspeed[_testi]);
    }
    else
    {
        _tick++;
    }
}

void SysTickIntHandler(void)
{
    on_sys_period();
}

