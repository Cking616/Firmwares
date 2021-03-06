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
#include "driverlib/rom_map.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "CO_driver.h"
#include "drv8308.h"
#include "encoder.h"
#include "lights.h"
#include "sonar.h"
#include "cmdUart.h"
#include "io.h"

volatile int _address = 0x7F;

//*****************************************************************************
//
// Configure the UART and its pins.  This must be called before UARTprintf().
//
//*****************************************************************************
void
ConfigureUART(void)
{
    //
    // Enable UART0
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART4);

    MAP_GPIOPinConfigure(GPIO_PJ0_U4RX);
    MAP_GPIOPinConfigure(GPIO_PJ1_U4TX);
    MAP_GPIOPinTypeUART(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART4_BASE, UART_CLOCK_SYSTEM);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(4, 115200, SysCtlClockGet());
}

void driver_init_hardware(void)
{
    //
    // Enable lazy stacking for interrupt handlers.  This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.
    //
    MAP_SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_RCC2_USERCC2 | SYSCTL_RCC2_DIV400); // 80 Mhz

    // Enable the GPIO port that is used for the on-board LED.
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);

    // Check if the peripheral access is enabled.
    while(!MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)) {MAP_SysCtlDelay(1); }

    ConfigureUART();

    encoder_init();

    //sonar_init();

    lights_init();

    CO_driver_init();
    drv8308_init();
    cmd_uart_init();

    io_manager_init();
    // ************************************************************************************************************
    //MAP_SysTickPeriodSet(80000);  // every 1mSec, @ 80Mhz
}

inline int driver_get_address(void)
{
    return _address;
}

void driver_init_system(void)
{
    //UARTprintf("Sys init\n");
    CO_start_listening();

    encoder_reset(0);
    encoder_reset(1);

    drv8308_enable(1);

    io_manager_turn_sol(0, 1);
    io_manager_turn_sol(1, 1);
}

