/*
 * period.c
 *
 *  Created on: 2018/5/15
 *      Author: cking
 */
#include <stdbool.h>
#include <stdint.h>
#include "bsp/driver.h"
#include "bsp/MA3encoder.h"
#include "bsp/io.h"
#include "utils/uartstdio.h"

#define DISABLE_INTERRUPTS()                                        \
{                                                                       \
    _set_interrupt_priority( 0x70 );    \
    __asm( "    dsb" );                                                 \
    __asm( "    isb" );                                                 \
}

#define ENABLE_INTERRUPTS()                 _set_interrupt_priority( 0 )

int _testspeed[5] = {100, 1000, 10, 300, 10};
int _testi = 0;
int _tick = 0;
volatile unsigned int _tick_second = 0;

// period: 1ms
inline void on_sys_period(void)
{
	if (_tick % 5 == 1)
	{
		DISABLE_INTERRUPTS();
		io_manager_process();
		MA3_encoder_process();
		ENABLE_INTERRUPTS();
	}

    if(_tick == 999)
    {
        _tick = 0;

        _tick_second++;
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

