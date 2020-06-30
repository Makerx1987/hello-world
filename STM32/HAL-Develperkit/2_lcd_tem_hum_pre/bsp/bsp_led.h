#ifndef __BSP_LED_H
#define	__BSP_LED_H

#include "stm32l4xx.h"

/*
LED,丝印与stm32引脚对应关系：
LED1------PB6
LED2------PE3
LED3------PD15
*/

#define LED1_PIN                  GPIO_PIN_6
#define LED1_GPIO_PORT            GPIOB

#define LED2_PIN                  GPIO_PIN_3
#define LED2_GPIO_PORT            GPIOE

#define LED3_PIN                  GPIO_PIN_15
#define LED3_GPIO_PORT            GPIOD

void LED_GPIO_Config(void);

#endif

