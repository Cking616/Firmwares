/*
 * period.c
 *
 *  Created on: 2018Äê5ÔÂ15ÈÕ
 *      Author: cking
 */
#include <stdbool.h>
#include <stdint.h>
#include "bsp/driver.h"
#include "bsp/MA3encoder.h"
#include "utils/uartstdio.h"


int _testspeed[5] = {100, 1000, 10, 300, 10};
int _testi = 0;
int _tick = 0;
volatile unsigned int _tick_second = 0;

// period: 1ms
inline void on_sys_period(void)
{

    if(_tick == 999)
    {
        _tick = 0;

        _tick_second++;
        if(_tick_second % 4 == 1)
        {
            //driver_test_pwm(_testspeed[_testi]);
            _testi = (_testi + 1) % 5;
        }
        //UARTprintf("Tick Time\n");
        MA3_encoder_print_value();
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

