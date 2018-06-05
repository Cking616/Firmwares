/*
 * MA3encoder.h
 *
 *  Created on: 2018/5.15
 *      Author: cking
 */

#ifndef BSP_MA3ENCODER_H_
#define BSP_MA3ENCODER_H_

void MA3_encoder_init(void);

inline int MA3_encoder_get_value(void);

void MA3_encoder_print_value(void);

void MA3_encoder_process(void);
#endif /* BSP_MA3ENCODER_H_ */
