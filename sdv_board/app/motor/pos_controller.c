/*
 * pos_controller.c
 *
 *  Created on: 2018/5/18
 *      Author: cking
 */
#include "pos_controller.h"
#include "speed_controller.h"
#include "bps/encoder.h"

volatile pos_controller_state pos_state[2];

void pos_controller_init(int num)
{
    pos_state[num].kp = 0.0036;
    pos_state[num].ki = 0.000007;
    pos_state[num].kd = 0.000022;
    pos_state[num].last_err = 0;
    pos_state[num].last_speed = 0;
    pos_state[num].target_pos = speed_controller_get_encoder(num);
    pos_state[num].max_speed = 22;
    pos_state[num].max_acc = 0.74;

}

inline void pos_controller_set_pos(int num, int pos)
{
    pos_state[num].target_pos = pos;
}

inline int  pos_controller_get_encoder(int num)
{
    return speed_controller_get_encoder(num);
}

inline void pos_controller_set_max_speed(int num, int max_speed)
{
    pos_state[num].max_speed = max_speed;
}

void pos_controller_period(int num)
{
    static float a = 0.626;
    float speed =  pos_state[num].last_speed;
    int err = pos_state[num].target_pos - encoder_get_value(num);
    int abs_err = err > 0? err: -err;
    if(abs_err > 300)
    {
        speed = pos_state[num].kp * err + pos_state[num].kd * (err - pos_state[num].last_err);
    }
    else if(abs_err > 10 && abs_err <= 300)
    {
        float increase = pos_state[num].ki * err +  pos_state[num].kp * (err - pos_state[num].last_err) / 5;
        speed = speed + increase;
    }
    else
    {
        speed = 0;
    }

    speed = a * speed + (1 - a) * pos_state[num].last_speed;
    float acc = speed - pos_state[num].last_speed;

    if(acc > pos_state[num].max_acc)
    {
        acc = pos_state[num].max_acc;
    }

    if(acc < -pos_state[num].max_acc)
    {
        acc =  pos_state[num].last_speed - pos_state[num].max_acc;
    }

    speed = pos_state[num].last_speed + acc;
    if(speed > pos_state[num].max_speed)
        speed =  pos_state[num].max_speed;
    if(speed < -pos_state[num].max_speed)
        speed =  -pos_state[num].max_speed;
    speed_controller_set_speed(num, speed);
    pos_state[num].last_speed = speed;
    pos_state[num].last_err = err;
}

void pos_controller_print(int num)
{

}
