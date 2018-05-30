/*
 * PD4_task.h
 *
 *  Created on: 2018/5/28
 *      Author: cking
 */

#ifndef APP_PD4_TASK_H_
#define APP_PD4_TASK_H_


uint32_t PD4Master_taskInit(void);

void PD4Master_set_speed(unsigned char nodeID, void* speed);
void PD4Master_set_pos(unsigned char nodeID,void* pos);
#endif /* APP_PD4_TASK_H_ */
