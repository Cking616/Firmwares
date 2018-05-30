/*
 * pos_controller.h
 *
 *  Created on: 2018Äê5ÔÂ18ÈÕ
 *      Author: cking
 */

#ifndef TASK_POS_CONTROLLER_H_
#define TASK_POS_CONTROLLER_H_

// pos close loop use kd and kp,ki;
typedef struct
{
    float       kp;
    float       kp2;
    float       ki;
    float       kd;

    int         target_pos;
    int         last_err;
    int         max_speed;   //unit: rpm / 4 ;300 rpm => (300 / 60 * 4000) pulse per millosecond = 20 pulse / ms
    float       max_acc;
    float       last_speed;
}pos_controller_state;

void pos_controller_init(int num);
inline void pos_controller_set_pos(int num, int pos);
inline int  pos_controller_get_encoder(int num);
inline void pos_controller_set_max_speed(int num, int max_speed);
void pos_controller_period(int num);
void pos_controller_print(int num);



#endif /* TASK_POS_CONTROLLER_H_ */
