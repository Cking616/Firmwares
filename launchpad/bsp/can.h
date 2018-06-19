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

void can_init();

void can_start_listening();

void can_write(uint32_t id, uint32_t len, uint8_t mode, uint8_t* data );

#endif /* CAN_H_ */
