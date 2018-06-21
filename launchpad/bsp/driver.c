/*
 * driver.c
 *
 *  Created on: 2018/5/15
 *      Author: cking
 */

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "driverlib/pwm.h"
#include "utils/uartstdio.h"
#include "can.h"
#include "MA3encoder.h"
#include "Bumper.h"
#include "io.h"
#include "CO_driver.h"
#include "cmdUart.h"

//*****************************************************************************
//
// Configure the UART and its pins.  This must be called before UARTprintf().
//
//*****************************************************************************
void
ConfigureUART(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_SYSTEM);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, SysCtlClockGet());
}

void driver_init_hardware(void)
{
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL
                       | SYSCTL_XTAL_16MHZ | SYSCTL_RCC2_USERCC2 | SYSCTL_RCC2_DIV400); // 80 Mhz
    //ROM_FPULazyStackingEnable();
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    //ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
    //ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER1);

    // Check if the peripheral access is enabled.
    while(!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)) { }

    //IntPrioritySet(INT_UART0, 0xA0);
    //IntPrioritySet(INT_CAN0, 0xD0);

    MA3_encoder_init();
    CO_driver_init();
    //cmd_uart_init();
    //bumper_init();
    //io_manager_init();
    //can_init();
    ConfigureUART();

    // ************************************************************************************************************
    //ROM_SysTickPeriodSet(80000);  // every 1mSec, @ 80Mhz
}

void driver_init_system(void)
{
    CO_start_listening();
}

