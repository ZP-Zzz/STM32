#ifndef __BEEP_H
#define	__BEEP_H


#include "stm32f10x.h"


/* 高电平时，蜂鸣器响 */
#define ON  1
#define OFF 0

/* 带参宏，可以像内联函数一样使用 */
#define BEEP(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_8);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_8)

void BEEP_GPIO_Config(void);
					
#endif /* __BEEP_H */
