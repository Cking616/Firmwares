/*
 * speed_controller.h
 *
 *  Created on: 2018Äê4ÔÂ25ÈÕ
 *      Author: Administrator
 */

#ifndef SPEED_CONTROLLER_H_
#define SPEED_CONTROLLER_H_

#include <stdint.h>
#include <stdbool.h>

#define PID_PERIOD_TIME 1 // unit: ms

// speed close loop use ki and kp
typedef struct
{
    float       kp;
    float       ki;
    //float       kd;

    int         last_encoder; // 4000 pulse per round

    int         target_speed; // unit: rpm / 4 ;max: 300 rpm => (300 / 60 * 4000) pulse per millosecond = 20 pulse / ms
    int         rel_speed;
    int         rel_speed2;
    int         last_err;

    float       last_pwm;   // pwm , max: 200
}speed_controller_state;

void speed_controller_init(int num);
void speed_controller_set_speed(int num, int speed);
inline int  speed_controller_get_speed(int num);
inline int  speed_controller_get_encoder(int num);
void speed_controller_period(int num);
void speed_controller_print(int num);
void  speed_controller_set_kp(int kp);
void  speed_controller_set_ki(int ki);
#endif /* speed_controller_H_ */
