/*
 * stepmotor.h
 *
 *  Created on: 2018/5/15
 *      Author: cking
 */

#ifndef BSP_STEPMOTOR_H_
#define BSP_STEPMOTOR_H_

#define SRESET_PORT         GPIO_PORTG_BASE
#define SRESET_PIN          GPIO_PIN_5
#define SENABLE0_PORT       GPIO_PORTF_BASE
#define SENABLE0_PIN        GPIO_PIN_3
#define SFAULT0_PORT        GPIO_PORTF_BASE
#define SFAULT0_PIN         GPIO_PIN_2
#define SDIR0_PORT          GPIO_PORTA_BASE
#define SDIR0_PIN           GPIO_PIN_5
#define SENABLE1_PORT       GPIO_PORTA_BASE
#define SENABLE1_PIN        GPIO_PIN_4
#define SFAULT1_PORT        GPIO_PORTA_BASE
#define SFAULT1_PIN         GPIO_PIN_3
#define SDIR1_PORT          GPIO_PORTA_BASE
#define SDIR1_PIN           GPIO_PIN_2

void step_motor_init(void);

//speed unit: rpm, maybe 300 ~ 600 rpm.
void step_motor_set_speed(int Motor,  int Speed );

#define STEP_MOTOR_CCW  1
#define STEP_MOTOR_CW   0

void step_motor_set_dir(int Motor,  int dir);

#endif /* BSP_STEPMOTOR_H_ */
