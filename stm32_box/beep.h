#ifndef __BEEP_H
#define	__BEEP_H


#include "stm32f10x.h"


/* �ߵ�ƽʱ���������� */
#define ON  1
#define OFF 0

/* ���κ꣬��������������һ��ʹ�� */
#define BEEP(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_8);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_8)

void BEEP_GPIO_Config(void);
					
#endif /* __BEEP_H */
