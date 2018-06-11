/*
 * delay.c
 *
 *  Created on: 2018Äê5ÔÂ15ÈÕ
 *      Author: cking
 */
#include <stdint.h>
#include <stdbool.h>
#include "delay.h"
#include "driverlib/rom.h"

inline void delay_ms(int ms)
{
    int num = ms  * 40000;
    ROM_SysCtlDelay(num);
}

inline void delay_s(int s)
{
    int i = 0;
    for(i = 0; i < s; i++)
    {
        delay_ms(1000);
    }
}
