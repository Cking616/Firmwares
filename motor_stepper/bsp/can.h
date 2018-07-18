/*
 * can.h
 *
 *  Created on: 2018Äê5ÔÂ2ÈÕ
 *      Author: Administrator
 */

#ifndef CAN_H_
#define CAN_H_

#include <stdbool.h>
#include <stdint.h>

void CO_driver_init(void);

void CO_start_listening(void);

void CO_timer_start(void);

//extern volatile uint32_t CanMsgIn[2];
//extern volatile bool g_bRXFlag;
//extern volatile uint16_t CanRXAd;

#define CANS_PORT GPIO_PORTD_BASE
#define CANS_PIN GPIO_PIN_6

#endif /* CAN_H_ */
