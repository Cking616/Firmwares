/*
 * pos_controller.c
 *
 *  Created on: 2018/5/18
 *      Author: cking
 */
#include "pos_controller.h"
#include "speed_controller.h"
#include "bsp/encoder.h"
#include "utils/uartstdio.h"

volatile pos_controller_state pos_state[2];

void pos_controller_init(int num)
{
    pos_state[num].kp = 0.0036;
    pos_state[num].ki = 0.000007;
    pos_state[num].kd = 0.000022;
    pos_state[num].last_err = 0;
    pos_state[num].last_speed = 0;
    pos_state[num].target_pos = speed_controller_get_encoder(num);
    pos_state[num].max_speed = 24;
    pos_state[num].max_acc = 0.74;
	pos_state[num].flag = 1;
}

inline void pos_controller_set_pos(int num, int pos)
{
    if(num == 0)
    {
        pos_state[num].target_pos = pos;
    }
    else
    {
        pos_state[num].target_pos = -pos;
    }
}

inline int  pos_controller_get_encoder(int num)
{
    return encoder_get_value(num);
}

inline void pos_controller_set_max_speed(int num, int max_speed)
{
    pos_state[num].max_speed = max_speed;
}

void pos_controller_period(int num)
{
    static float a = 0.63;
    float speed =  pos_state[num].last_speed;
    int err = pos_state[num].target_pos - encoder_get_value(num);
    int abs_err = err > 0? err: -err;
	
    if(abs_err > 300)
    {
        speed = pos_state[num].kp * err + pos_state[num].kd * (err - pos_state[num].last_err);
		pos_state[num].flag = 0;
    }
    else if(abs_err > 10 && abs_err <= 300)
    {
        float increase = pos_state[num].ki * err +  pos_state[num].kp * (err - pos_state[num].last_err) / 4;
        speed = speed + increase;
		pos_state[num].flag = 0;
    }
    else
    {
        speed = 0;
		pos_state[num].flag = 1;
		err = 0;
    }

    speed = a * speed + (1 - a) * pos_state[num].last_speed;
    float acc = speed - pos_state[num].last_speed;

    if(acc > pos_state[num].max_acc)
    {
        acc = pos_state[num].max_acc;
    }

    if(acc < -pos_state[num].max_acc)
    {
        acc = -pos_state[num].max_acc;
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
    UARTprintf("ts:%d,err:%d\n", pos_state[num].target_pos, pos_state[num].last_err);
}

inline int pos_controller_get_flag(int num)
{
	return pos_state[num].flag;
}

inline void pos_controller_set_kp(int kp)
{
    pos_state[0].kp = (float)kp / 10000;
    pos_state[1].kp = (float)kp / 10000;

}

inline void pos_controller_set_ki(int ki)
{
    pos_state[0].ki = (float)ki / 1000000;
    pos_state[1].ki = (float)ki / 1000000;
}


inline void pos_controller_set_kd(int kd)
{
    pos_state[0].kd = (float)kd / 1000000;
    pos_state[1].kd = (float)kd / 1000000;
}
