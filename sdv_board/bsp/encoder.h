/*
 * encoder.h
 *
 *  Created on: 2018Äê4ÔÂ25ÈÕ
 *      Author: Administrator
 */

#ifndef ENCODER_H_
#define ENCODER_H_


void encoder_init();

int encoder_get_value(int num);

void encoder_reset(int num);

#define ENCODER_DIR_CW                                   1
#define ENCODER_DIR_CCW                                  -1
extern volatile int _encoder_dir;
void encoder_set_dir(int num, int dir);

int encoder_get_speed(int num);
#endif /* ENCODER_H_ */
