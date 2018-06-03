/*
 * test_BLDC_task.h
 *
 *  Created on: 2018/5/29
 *      Author: cking
 */

#ifndef APP_MOTOR_TEST_BLDC_TASK_H_
#define APP_MOTOR_TEST_BLDC_TASK_H_


uint32_t BLDC_Motion_taskInit(void);
int BLDC_Motion_start(unsigned int speed, int pos, unsigned int a_mol);
int BLDC_Motion_get_flag(void);
void BLDC_Motion_stop(void);
int BLDC_Motion_get_encoder(void);
#endif /* APP_MOTOR_TEST_BLDC_TASK_H_ */
