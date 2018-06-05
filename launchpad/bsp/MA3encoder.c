/*
 * MA3encoder.c
 *
 *  Created on: 2018/5/15
 *      Author: cking
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_timer.h"
#include "inc/hw_gpio.h"
#include "inc/hw_pwm.h"
#include "inc/hw_types.h"
#include "driverlib/pin_map.h"
#include "driverlib/timer.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/pwm.h"
#include "driverlib/systick.h"
#include "driverlib/rom.h"
#include "utils/uartstdio.h"
#include "MA3encoder.h"
#include "PG2Slave.h"

void inputInt();
void Captureinit();

//Stores the pulse length
volatile int pulse=0;
volatile int last_pulse=0;
volatile int circle = 0;
volatile int  dir = 1;
volatile uint32_t ton=0;
volatile uint32_t toff=0;


void MA3_encoder_init()
{
    //Configures the timer
    Captureinit();
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    ROM_SysCtlDelay(3);
    //Configure pwm pin
    ROM_GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_6);
    GPIOIntEnable(GPIO_PORTD_BASE, GPIO_PIN_6);
    ROM_GPIOIntTypeSet(GPIO_PORTD_BASE, GPIO_PIN_6,GPIO_BOTH_EDGES);
    GPIOIntRegister(GPIO_PORTD_BASE, inputInt);
}

void inputInt(){
  //Clear interrupt flag. Since we only enabled on this is enough
    GPIOIntClear(GPIO_PORTD_BASE, GPIO_PIN_6);

  /*
    If it's a rising edge then set he timer to 0
    It's in periodic mode so it was in some random value
  */
  if ( ROM_GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_6) == GPIO_PIN_6){
    HWREG(TIMER2_BASE + TIMER_O_TAV) = 0; //Loads value 0 into the timer.
    toff = ROM_TimerValueGet(TIMER3_BASE,TIMER_A);

    if ( (ton + toff) != 0)
    {
        pulse = ((ton * 4098) / (ton + toff)) - 1;
        last_pulse = pulse;
		int inc = pulse - last_pulse;
		if (inc > 0)
		{
			if (inc < 2048)
			{
				dir = 1;
			}
			else
			{
				dir = -1;
				circle--;
			}
		}
		else
		{
			if (inc > -2048)
			{
				dir = -1;
			}
			else
			{
				dir = 1;
				circle++;
			}
		}
    }

    ROM_TimerEnable(TIMER2_BASE,TIMER_A);
    ROM_TimerDisable(TIMER3_BASE,TIMER_A);
  }
  /*
    If it's a falling edge that was detected, then get the value of the counter
  */
  else{
    HWREG(TIMER3_BASE + TIMER_O_TAV) = 0; //Loads value 0 into the timer.
    ton = ROM_TimerValueGet(TIMER2_BASE,TIMER_A); //record value
    ROM_TimerEnable(TIMER3_BASE,TIMER_A);
    ROM_TimerDisable(TIMER2_BASE,TIMER_A);
  }
}

void Captureinit(){
  /*
    Set the timer to be periodic.
  */
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
    ROM_SysCtlDelay(3);
    ROM_TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC_UP);

    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);
    ROM_SysCtlDelay(3);
    ROM_TimerConfigure(TIMER3_BASE, TIMER_CFG_PERIODIC_UP);
    //ROM_TimerConfigure(TIMER2_BASE, TIMER_CFG_SPLIT_PAIR);
}

int MA3_encoder_get_value(void)
{
	return pulse + circle * 4096;
}

void MA3_encoder_print_value(void)
{
    int angle = pulse * 360 / 4096;
    //int   deg = angle;
    //int   Min = (angle - deg) * 100 * 100 / 60;
    UARTprintf("angle:%d deg\n",  angle);
}

void MA3_encoder_process(void)
{
	YEncoder = pulse + circle * 4096;
}