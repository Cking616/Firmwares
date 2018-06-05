/*
 * cmdUart.h
 *
 *  Created on: 2018/5/31
 *      Author: cking
 */

#ifndef BPS_CMDUART_H_
#define BPS_CMDUART_H_


void cmd_uart_init(void);
void cmd_uart_send(const uint8_t *pui8Buffer, uint32_t ui32Count);

#endif /* BPS_CMDUART_H_ */
