/*
 * period.c
 *
 *  Created on: 2018/5/15
 *      Author: cking
 */
#include <stdbool.h>
#include <stdint.h>
#include "bsp/driver.h"
#include "PD4Master.h"
#include "app/canfestival_thread.h"
#include "app/PD4/PD4_task.h"
#include "utils/uartstdio.h"


extern int PD4_bConnected[4];


int _testspeed[5] = {5, 20, 25, 15, 5};
int _testi = 0;
int _tick = 0;
volatile unsigned int _tick_second = 0;

// period: 1ms
inline void on_sys_period(void)
{
    canfestival_period();
    if(_tick % 10 == 1)
    {
        PD4Master_period();
    }

    if(_tick == 999)
    {
        _tick = 0;

        _tick_second++;

        //UARTprintf("Tick Time!\n");

        //int data = readNetworkDict (&TestMaster_Data, 2, 0x6041, 0x00, uint16, 0);
        //UARTprintf("S:0x%X, C:0x%X,P:%d!\n", Statusword2, Contolword2, Position2);
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

