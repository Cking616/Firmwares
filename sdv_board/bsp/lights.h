/*
 * lights.h
 *
 *  Created on: 2018Äê5ÔÂ14ÈÕ
 *      Author: cking
 */

#ifndef BSP_LIGHTS_H_
#define BSP_LIGHTS_H_


#define LED_RED_PORT GPIO_PORTH_BASE
#define LED_RED_PIN GPIO_PIN_3
#define LED_GREEN_PORT GPIO_PORTB_BASE
#define LED_GREEN_PIN GPIO_PIN_2
#define RGB_RED_PORT GPIO_PORTH_BASE   // M1PWM0
#define RGB_RED_PIN GPIO_PIN_2
#define RGB_GREEN_PORT GPIO_PORTH_BASE   // M0PWM0
#define RGB_GREEN_PIN GPIO_PIN_0
#define RGB_BLUE_PORT GPIO_PORTH_BASE   // M0PWM1
#define RGB_BLUE_PIN GPIO_PIN_1

void lights_init(void);

inline void lights_turn_led_red(int on);
inline void lights_turn_led_green(int on);

#define LIGHTS_RGB_RED      0x4
#define LIGHTS_RGB_GREEN    0x2
#define LIGHTS_RGB_BLUE     0x1

inline void lights_turn_rgb(unsigned int flag);

#endif /* BSP_LIGHTS_H_ */
