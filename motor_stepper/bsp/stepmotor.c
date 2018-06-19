/*
 * stepmotor.c
 *
 *  Created on: 2018/5/15
 *      Author: cking
 */
#include <stdint.h>
#include <stdbool.h>
#include "stepmotor.h"
#include "driverlib/rom.h"
#include "inc/hw_sysctl.h"
#include "driverlib/sysctl.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "utils/uartstdio.h"
#include "delay.h"

int _count = 0;
int _end_step = 0;
//*****************************************************************************
//
// The interrupt handler for the for PWM0 interrupts.
//
//*****************************************************************************
void
PWM1IntHandler(void)
{
    //
    // Clear the PWM1 LOAD interrupt flag.  This flag gets set when the PWM
    // counter gets reloaded.
    //
    ROM_PWMGenIntClear(PWM1_BASE, PWM_GEN_1, PWM_INT_CNT_LOAD);

    _count++;
    if(_end_step == _count)
    {
        ROM_PWMGenDisable(PWM1_BASE, PWM_GEN_1);
    }
}

void step_motor_init(void)
{
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    //ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    ROM_SysCtlPWMClockSet( SYSCTL_PWMDIV_64 );  // 1.25Mhz --> 50Khz division is 25

    HWREG(GPIO_PORTA_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;   // unlock port F
    HWREG(GPIO_PORTA_BASE + GPIO_O_CR) = 0xFF;
    // PWM
    ROM_GPIOPinConfigure(GPIO_PA6_M1PWM2); // step-1
    ROM_GPIOPinConfigure(GPIO_PA7_M1PWM3); // step-0
    ROM_GPIOPinTypePWM(GPIO_PORTA_BASE, GPIO_PIN_6 | GPIO_PIN_7);
    ROM_PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);  // Configure the PWM0 to count up/down without synchronization.
    ROM_PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, 10000);
    ROM_PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT, true);  // Enable the PWM Bits output signals.
    ROM_PWMOutputState(PWM1_BASE, PWM_OUT_3_BIT, true);  // Enable the PWM Bits output signals.
    ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_1);     // Enables the counter for a PWM generator block.

    //
    // Enable processor interrupts.
    //
    IntMasterEnable();

    //
    // Allow PWM0 generated interrupts.  This configuration is done to
    // differentiate fault interrupts from other PWM0 related interrupts.
    //
    ROM_PWMIntEnable(PWM1_BASE, PWM_INT_GEN_1);

    //
    // Enable the PWM0 LOAD interrupt on PWM0.

    //
    PWMGenIntTrigEnable(PWM1_BASE, PWM_GEN_1, PWM_INT_CNT_LOAD);

    //
    // Enable the PWM0 interrupts on the processor (NVIC).
    //
    IntEnable(INT_PWM1_1);


    // Stepper control
    ROM_GPIOPinTypeGPIOInput( SFAULT0_PORT, SFAULT0_PIN );
    ROM_GPIOPinTypeGPIOInput( SFAULT1_PORT, SFAULT1_PIN );
    ROM_GPIOPinTypeGPIOOutput( SRESET_PORT,   SRESET_PIN );
    ROM_GPIOPinTypeGPIOOutput( SENABLE0_PORT, SENABLE0_PIN );
    ROM_GPIOPinTypeGPIOOutput( SENABLE1_PORT, SENABLE1_PIN );
    ROM_GPIOPinTypeGPIOOutput( SDIR0_PORT,     SDIR0_PIN );
    ROM_GPIOPinTypeGPIOOutput( SDIR1_PORT,     SDIR1_PIN );
    ROM_GPIOPinWrite( SRESET_PORT,   SRESET_PIN,   0 );
    delay_ms(1);
    ROM_GPIOPinWrite( SRESET_PORT,   SRESET_PIN,   SRESET_PIN );
    ROM_GPIOPinWrite( SENABLE0_PORT, SENABLE0_PIN, SENABLE0_PIN );  // #enable0 is disabled
    ROM_GPIOPinWrite( SENABLE1_PORT, SENABLE1_PIN, SENABLE1_PIN );  // #enable1 is disabled
    ROM_GPIOPinWrite( SDIR0_PORT,    SDIR0_PIN,    0 );
    ROM_GPIOPinWrite( SDIR1_PORT,    SDIR1_PIN,    0 );

    HWREG(GPIO_PORTA_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;  // relock port F
    HWREG(GPIO_PORTA_BASE + GPIO_O_CR) = 0x00;
    HWREG(GPIO_PORTA_BASE + GPIO_O_LOCK) = 0;
}

//*****************************************************************************
//*****************************************************************************
void step_motor_set_speed(int Motor,  int Speed, int Step)
{
    if(Step > 0)
    {
        _count = 0;
        _end_step = Step;
    }
    else
    {
        _end_step = -1;
    }

    if(Speed < 0)
    {
        step_motor_set_dir(Motor, 0);
        Speed = -Speed;
    }
    else
    {
        step_motor_set_dir(Motor, 1);
    }

    int count = 1250000 / Speed;

    if ( Speed == 0 ) {
        if (Motor==0) {
            ROM_GPIOPinWrite(SENABLE0_PORT, SENABLE0_PIN, SENABLE0_PIN );  // #enable0 is disabled
        }
        else {
            ROM_GPIOPinWrite(SENABLE1_PORT, SENABLE1_PIN, SENABLE1_PIN );  // #enable1 is disabled
        }
    }
    else {
        ROM_PWMGenPeriodSet( PWM1_BASE, PWM_GEN_1, count );
        if(Motor==0)
            ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3, count / 2);
        else
            ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, count / 2);
        ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_1);
        if (Motor==0) {
            ROM_GPIOPinWrite(SENABLE0_PORT, SENABLE0_PIN, 0 );  // #enable0 is enabled
        }
        else {
            ROM_GPIOPinWrite(SENABLE1_PORT, SENABLE1_PIN, 0 );  // #enable1 is enabled
        }
    }
}

void step_motor_set_dir(int Motor,  int dir)
{
    if (Motor==0) {
        ROM_GPIOPinWrite(SDIR0_PORT,  SDIR0_PIN, (dir==0)? 0 : SDIR0_PIN ); // SDIR0
    }
    else {
        ROM_GPIOPinWrite(SDIR1_PORT,  SDIR1_PIN, (dir==0)? 0 : SDIR1_PIN ); // SDIR1
    }
}
