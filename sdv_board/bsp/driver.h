/*
 * driver.h
 *
 *  Created on: 2018/5/15
 *      Author: cking
 */

#ifndef BSP_DRIVER_H_
#define BSP_DRIVER_H_

void driver_init_hardware(void);

inline int driver_get_address(void);

void driver_init_system(void);
#endif /* BSP_DRIVER_H_ */
