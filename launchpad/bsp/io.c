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
#include "PG2Slave.h"

void io_manager_init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;   // unlock port F
    HWREG(GPIO_PORTD_BASE + GPIO_O_CR) = 0xFF;
    // SOL out
    GPIOPinTypeGPIOOutput( GPIO_PORTB_BASE,   GPIO_PIN_0 );
    GPIOPinTypeGPIOOutput( GPIO_PORTB_BASE,   GPIO_PIN_1 );
    GPIOPinTypeGPIOOutput( GPIO_PORTD_BASE,   GPIO_PIN_0 );
    GPIOPinTypeGPIOOutput( GPIO_PORTD_BASE,   GPIO_PIN_1 );
    GPIOPinTypeGPIOOutput( GPIO_PORTD_BASE,   GPIO_PIN_2 );

    // TB
    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_7);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_2);

    // zero Y
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_4);
    // lock Y
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_7);
    // zero odom
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_5);

    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;  // relock port F
    HWREG(GPIO_PORTD_BASE + GPIO_O_CR) = 0x00;
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0;
}

void io_manager_test()
{
    int data;
    GPIOPinWrite( GPIO_PORTB_BASE,   GPIO_PIN_0, 0);
    GPIOPinWrite( GPIO_PORTB_BASE,   GPIO_PIN_1, 0);
    GPIOPinWrite( GPIO_PORTD_BASE,   GPIO_PIN_0, 0);
    GPIOPinWrite( GPIO_PORTD_BASE,   GPIO_PIN_1, 0);
    GPIOPinWrite( GPIO_PORTD_BASE,   GPIO_PIN_2, 0);

    data = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_2);
    UARTprintf("TB8:%d\n",  data);
    data = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);
    UARTprintf("TB10:%d\n",  data);
    data = GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_7);
    UARTprintf("TB12:%d\n",  data);
    data = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_4);
    UARTprintf("ZeroY:%d\n",  data);
    data = GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_7);
    UARTprintf("LockY:%d\n",  data);
    data = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_5);
    UARTprintf("zero odom:%d\n",  data);
}

void io_manager_process()
{
	int data;
	data = (Output1 & 0x1) ? GPIO_PIN_0 : 0;
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, data);
	data = (Output1 & 0x2) ? GPIO_PIN_1 : 0;
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, data);
	data = (Output1 & 0x4) ? GPIO_PIN_0 : 0;
	GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, data);
	data = (Output1 & 0x8) ? GPIO_PIN_1 : 0;
	GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, data);
	data = (Output1 & 0x10) ? GPIO_PIN_2 : 0;
	GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, data);

	Input1 = 0;
	data = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_2);
	Input1 |= data ? 0x1: 0;
	data = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);
	Input1 |= data ? 0x2 : 0;
	data = GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_7);
	Input1 |= data ? 0x4 : 0;
	data = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_4);
	Input1 |= data ? 0x8 : 0;
	data = GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_7);
	Input1 |= data ? 0x10 : 0;
	data = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_5);
	Input1 |= data ? 0x20 : 0;
}
