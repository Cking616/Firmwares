/*
 * lights.c
 *
 *  Created on: 2018/5/14
 *      Author: cking
 */
#include <stdint.h>
#include <stdbool.h>
#include "lights.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "inc/hw_sysctl.h"
#include "driverlib/sysctl.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"

void lights_init(void)
{
    //MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    // Enable the GPIO pin for the LED
    MAP_GPIOPinTypeGPIOOutput( LED_GREEN_PORT, LED_GREEN_PIN );
    MAP_GPIOPinTypeGPIOOutput( LED_RED_PORT,   LED_RED_PIN );
    MAP_GPIOPinTypeGPIOOutput( RGB_RED_PORT,   RGB_RED_PIN );
    MAP_GPIOPinTypeGPIOOutput( RGB_GREEN_PORT, RGB_GREEN_PIN );
    MAP_GPIOPinTypeGPIOOutput( RGB_BLUE_PORT,  RGB_BLUE_PIN );
}

void lights_turn_led_green(int on)
{
    MAP_GPIOPinWrite(LED_GREEN_PORT, LED_GREEN_PIN, on ? LED_GREEN_PIN : 0);
}

void lights_turn_led_red(int on)
{
    MAP_GPIOPinWrite(LED_RED_PORT, LED_RED_PIN, on ? LED_RED_PIN : 0);
}

void lights_turn_rgb(unsigned int flag)
{
    if(flag & 1)
    {
        MAP_GPIOPinWrite(RGB_BLUE_PORT, RGB_BLUE_PIN, RGB_BLUE_PIN);
    }
    else
    {
        MAP_GPIOPinWrite(RGB_BLUE_PORT, RGB_BLUE_PIN, 0);
    }

    if((flag >> 1) & 1)
    {
        MAP_GPIOPinWrite(RGB_GREEN_PORT, RGB_GREEN_PIN, RGB_GREEN_PIN);
    }
    else
    {
        MAP_GPIOPinWrite(RGB_GREEN_PORT, RGB_GREEN_PIN, 0);
    }

    if((flag >> 2) & 1)
    {
        MAP_GPIOPinWrite(RGB_RED_PORT, RGB_RED_PIN, RGB_RED_PIN);
    }
    else
    {
        MAP_GPIOPinWrite(RGB_RED_PORT, RGB_RED_PIN, 0);
    }
}
