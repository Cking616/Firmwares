/*
 * stepperctrl.c
 *
 *  Created on: 2018/5/15
 *      Author: cking
 */
#include "stepperctrl.h"
#include "..\bsp\stepmotor.h"

int _speed = 0;

void stepperctrl_thread()
{
    //step_motor_set_speed(1, _speed);
    //step_motor_set_speed(0, _speed);
}

void stepperctrl_set_speed(int speed)
{
    _speed = speed;
}
