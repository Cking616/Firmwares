/*
 * period.c
 *
 *  Created on: 2018/5/15
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
#include "bsp/Bumper.h"

int _testspeed[4] = {-500, 0, 500, 0};
int _testi = 0;
int _tick = 0;
volatile unsigned int _tick_second = 0;

// period: 1ms
inline void on_sys_period(void)
{
    stepperctrl_thread();

    if(_tick == 999)
    {
        _tick = 0;

        blinky_thread();

        _tick_second++;
        //UARTprintf("Tick Time!\n");
        bumper_print();
        //step_motor_set_speed(0, _testspeed[_testi], 1750);
        //step_motor_set_speed(1, _testspeed[_testi], 1750);
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

