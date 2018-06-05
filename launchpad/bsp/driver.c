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

volatile int _address = 0x21;

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

    //ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    //ROM_SysCtlPWMClockSet( SYSCTL_PWMDIV_64 );  // 1.25Mhz
    // PWM yuli
    //ROM_GPIOPinConfigure(GPIO_PA6_M1PWM2);
    //ROM_GPIOPinTypePWM(GPIO_PORTA_BASE, GPIO_PIN_6 );
    //ROM_PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_NO_SYNC);  // Configure the PWM0 to count up/down without synchronization.
    //ROM_PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, 5123 );    // 50000 = 25Hz, 0xffff = 19.1hz
    //ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, 1000);
    //ROM_PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT, true);  // Enable the PWM Bits output signals.
    //ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_1);     // Enables the counter for a PWM generator block.
}

void driver_init_hardware(void)
{
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL
                       | SYSCTL_XTAL_16MHZ | SYSCTL_RCC2_USERCC2 | SYSCTL_RCC2_DIV400); // 80 Mhz

    // Enable the GPIO port that is used for the on-board LED.
    //ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    //ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    //ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    //ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    //ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    //ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    //ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
    //ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER1);

    // Check if the peripheral access is enabled.
    //while(!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)) { }

    MA3_encoder_init();
    bumper_init();
    //sonar_init();
    io_manager_init();
    CO_driver_init();
    ConfigureUART();

    // ************************************************************************************************************
    ROM_SysTickPeriodSet(80000);  // every 1mSec, @ 80Mhz
}

inline int driver_get_address(void)
{
    return _address;
}

void driver_init_system(void)
{
    CO_start_listening();

    //encoder_reset();



    //lights_turn_led_red(1);
    //lights_turn_rgb(LIGHTS_RGB_RED);

    //drv8308_enable(1);
    //can_write(_address, 0x12345699, 0 ); // magic number means reset just happened
}

extern void SysTickIntHandler(void);

inline void driver_start_tick()
{
    SysTickIntRegister(SysTickIntHandler);
    ROM_SysTickEnable();
    ROM_SysTickIntEnable();
}
