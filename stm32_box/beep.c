 
#include "beep.h"   

void BEEP_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*�������Ʒ�������GPIO�Ķ˿�ʱ��*/
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); 

		/*ѡ��Ҫ���Ʒ�������GPIO*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	

		/*����GPIOģʽΪͨ���������*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*����GPIO����Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*���ÿ⺯������ʼ�����Ʒ�������GPIO*/
		GPIO_Init(GPIOA, &GPIO_InitStructure);			 
    
    /* �رշ�����*/
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);	 
}
/*********************************************END OF FILE**********************/
