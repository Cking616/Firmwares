/*
 * PD4_task.h
 *
 *  Created on: 2018/5/28
 *      Author: cking
 */

#ifndef APP_PD4_TASK_H_
#define APP_PD4_TASK_H_


uint32_t PD4Master_taskInit(void);
uint32_t CANopen_taskInit(void);
void PD4Master_set_speed(unsigned char nodeID, int speed);
void PD4Master_set_pos(unsigned char nodeID,int pos);
void PD4Master_stop(unsigned char nodeID);
unsigned char PD4Master_get_flag(unsigned char nodeID);
int PD4Master_get_encoder(unsigned char nodeID);
void PD4Master_set_step_pos(unsigned char nodeID, int pos);

#endif /* APP_PD4_TASK_H_ */
