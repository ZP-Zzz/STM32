#ifndef __KEY_H
#define	__KEY_H


#include "stm32f10x.h"


void Key_GPIO_Config(void);
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);


#endif /* __KEY_H */

