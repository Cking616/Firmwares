/*
 * speed_controller.c
 *
 *  Created on: 2018/4/25
 *      Author: Administrator
 */

#include "speed_controller.h"
#include "bsp/encoder.h"
#include "bsp/drv8308.h"
#include "utils/uartstdio.h"

#define MOTOR_MAX_SPEED 3970

volatile speed_controller_state pid_state[2];

void speed_controller_init(int num)
{
    pid_state[num].kp = 34.56f;
    pid_state[num].ki = 1.448f;

    pid_state[num].last_encoder = encoder_get_value(num);
    pid_state[num].target_speed = 0;
    pid_state[num].last_pwm = 0;
    pid_state[num].rel_speed = 0;
    pid_state[num].last_err = 0;

    drv8308_set_brake(num, 1);
    drv8308_set_pwm(num, 0);
}

void speed_controller_period(int num)
{
    static float a = 0.725f;
    float cur_pwm = 0.0f;
    int out_pwm = 0;
    int cur_encoder = encoder_get_value(num);
    pid_state[num].rel_speed = cur_encoder - pid_state[num].last_encoder;
    pid_state[num].rel_speed2 = encoder_get_speed(num);

    int err = pid_state[num].target_speed - pid_state[num].rel_speed;

    float increse = pid_state[num].kp * (err - pid_state[num].last_err)
                    + pid_state[num].ki * err;

    cur_pwm = pid_state[num].last_pwm + increse;

    if( cur_pwm > MOTOR_MAX_SPEED)
    {
        cur_pwm = MOTOR_MAX_SPEED;
    }

    if( cur_pwm < -MOTOR_MAX_SPEED)
    {
        cur_pwm = -MOTOR_MAX_SPEED;
    }

    cur_pwm = cur_pwm * a + pid_state[num].last_pwm * (1 - a);
    pid_state[num].last_pwm = cur_pwm;

    if ( cur_pwm > 0 )
    {
        out_pwm = cur_pwm;
        drv8308_set_dir(num, MOTOR_DIR_CW);
    }
    else
    {
        out_pwm = - cur_pwm;
        drv8308_set_dir(num, MOTOR_DIR_CCW);
    }

    if(out_pwm != 0 )
    {
        drv8308_set_brake(num, 0);
    }

    drv8308_set_pwm(num, out_pwm);

    if(pid_state[num].target_speed == 0 && pid_state[num].rel_speed2 == 0)
    {
        drv8308_set_brake(num, 1);
        pid_state[num].last_pwm = 0;
    }

    pid_state[num].last_encoder = cur_encoder;
    pid_state[num].last_err = err;
}

inline void speed_controller_set_speed(int num, int speed)
{
    if(pid_state[num].target_speed == speed )
    {
        return;
    }


    if(pid_state[num].target_speed == 0 || pid_state[num].target_speed * speed < 0)
    {
        if(speed > 0)
        {
            pid_state[num].last_pwm = 1;
        }
        else
        {
            pid_state[num].last_pwm = -1;
        }
    }

    pid_state[num].target_speed = speed;
}

inline int  speed_controller_get_encoder(int num)
{
    return pid_state[num].last_encoder;
}

inline int  speed_controller_get_speed(int num)
{
    return pid_state[num].rel_speed2;
}

void speed_controller_print(int num)
{
    int pwm = pid_state[num].last_pwm;
    UARTprintf("Pid:\nS:%d,ts:%d,E:%d,PWM:%d,err:%d\n", pid_state[num].rel_speed,pid_state[num].target_speed,pid_state[num].last_encoder,pwm,pid_state[num].last_err);
}
inline void  speed_controller_set_kp(int kp)
{
    pid_state[0].kp = (float)kp / 100;
    pid_state[1].kp = (float)kp / 100;
}

inline void  speed_controller_set_ki(int ki)
{
    pid_state[0].ki = (float)ki /1000;
    pid_state[1].ki = (float)ki /1000;
}
