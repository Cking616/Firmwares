/*
 * encoder.c
 *
 *  Created on: 2018/4/25
 *      Author: Administrator
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_qei.h"
#include "inc/hw_types.h"
#include "driverlib/qei.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "encoder.h"
#include "utils/uartstdio.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"

volatile int _encoder_dir1 = 1;
volatile int _encoder_dir2 = 1;

void encoder_init()
{
    //
    // Enable the QEI0 peripheral
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI0);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI1);
    //
    // Wait for the QEI0 module to be ready.
    //
    while(!MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_QEI0))
    {
    }



    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;   // unlock port F
    HWREG(GPIO_PORTD_BASE + GPIO_O_CR) = 0xFF;

    // QEI-0,1
    MAP_GPIOPinConfigure(GPIO_PD6_PHA0);
    MAP_GPIOPinConfigure(GPIO_PD7_PHB0);
    MAP_GPIOPinConfigure(GPIO_PG0_PHA1);
    MAP_GPIOPinConfigure(GPIO_PG1_PHB1);
    MAP_GPIOPinTypeQEI(GPIO_PORTG_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    MAP_GPIOPinTypeQEI(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);
    MAP_QEIConfigure( QEI0_BASE, QEI_CTL_CAPMODE, 0xffffffff );
    MAP_QEIConfigure( QEI1_BASE, QEI_CTL_CAPMODE, 0xffffffff );
    MAP_QEIPositionSet( QEI0_BASE, 0 );
    MAP_QEIPositionSet( QEI1_BASE, 0 );
    MAP_QEIEnable( QEI0_BASE );
    MAP_QEIEnable( QEI1_BASE );

    QEIVelocityConfigure(QEI0_BASE, QEI_VELDIV_1, SysCtlClockGet() / 10);
    QEIVelocityConfigure(QEI1_BASE, QEI_VELDIV_1, SysCtlClockGet() / 10);

    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;  // relock port F
    HWREG(GPIO_PORTD_BASE + GPIO_O_CR) = 0x00;
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0;
}

inline int encoder_get_speed(int num)
{
    if(num == 1)
    {
        int dir = MAP_QEIDirectionGet(QEI0_BASE);
        return _encoder_dir1 * dir * MAP_QEIVelocityGet(QEI0_BASE);
    }
    else
    {
        int dir = MAP_QEIDirectionGet(QEI1_BASE);
        return _encoder_dir2 * dir * MAP_QEIVelocityGet(QEI1_BASE);
    }
}

//*****************************************************************************
inline int encoder_get_value(int num)
{
    if(num == 1)
    {
        int reslv =  (int)QEIPositionGet( QEI0_BASE );
        return _encoder_dir1 * reslv;
    }
    else
    {
        int reslv =  (int)QEIPositionGet( QEI1_BASE );
        return _encoder_dir2 * reslv;
    }
}

inline void encoder_reset(int num)
{
    if(num == 1)
    {
        MAP_QEIPositionSet( QEI0_BASE, 0 );
    }
    else
    {
        MAP_QEIPositionSet( QEI1_BASE, 0 );
    }
}

void encoder_set_dir(int num, int dir)
{
    if(num == 1)
    {
        _encoder_dir1 = dir;
    }
    else
    {
        _encoder_dir2 = dir;
    }
}
