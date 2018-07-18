/*
 * stepperctrl.c
 *
 *  Created on: 2018/5/15
 *      Author: cking
 */
#include "stepperctrl.h"
#include "..\bsp\stepmotor.h"
#include "TestSlave.h"

int _speed = 0;
int _cur_pos = 0;
int _last_cur_pos = 0;
int _tar_pos = 0;
int _is_running = 0;
int dir = 1;

void stepperctrl_thread()
{
    int inc = step_motor_get_cur();
    _cur_pos = _last_cur_pos + dir * inc;
    if(_cur_pos == _tar_pos)
    {
        _is_running = 0;
    }
}

void stepperctrl_set_speed(int speed)
{
    _speed = speed;
}

int stepperctrl_set_pos(int pos)
{
    if(!_is_running)
    {
        _tar_pos = pos;
        _is_running = 1;
        int step = _tar_pos - _cur_pos;
        _last_cur_pos = _cur_pos;
        if(step < 0)
        {
            step = -step;
            dir = -1;
            step_motor_set_speed(1, -_speed, step);
            step_motor_set_speed(0, -_speed, step);
        }
        else
        {
            dir = 1;
            step_motor_set_speed(1, _speed, step);
            step_motor_set_speed(0, _speed, step);
        }
        return 1;
    }

    return 0;
}
