/*
 * io.c
 *
 *  Created on: 2018/5/15
 *      Author: cking
 */
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_can.h"
#include "driverlib/can.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"
#include "driverlib/rom.h"
#include "utils/uartstdio.h"
#include "io.h"
//#include "PG2Slave.h"

void io_manager_init()
{
    HWREG(GPIO_PORTK_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;   // unlock port F
    HWREG(GPIO_PORTK_BASE + GPIO_O_CR) = 0xFF;
    // SOL out
    GPIOPinTypeGPIOOutput( GPIO_PORTK_BASE,   GPIO_PIN_0 );
    GPIOPinTypeGPIOOutput( GPIO_PORTK_BASE,   GPIO_PIN_1 );

    HWREG(GPIO_PORTK_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;  // relock port F
    HWREG(GPIO_PORTK_BASE + GPIO_O_CR) = 0x00;
    HWREG(GPIO_PORTK_BASE + GPIO_O_LOCK) = 0;
}

void io_manager_turn_sol(int port, int value)
{
    if(port == 0)
    {
        if(value == 0)
        {
            GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_0, 0);
        }
        else
        {
            GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_0, GPIO_PIN_0);
        }
    }
    else
    {
        if(value == 0)
        {
            GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_1, 0);
        }
        else
        {
            GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_1, GPIO_PIN_1);
        }
    }
}
