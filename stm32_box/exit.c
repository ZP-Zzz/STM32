#include "stm32f10x.h"
#include "key.h"
#include "bsp_SysTick.h"

void EXIT_Init(void)
{
	EXTI_InitTypeDef  EXTI_InitStruct;
	NVIC_InitTypeDef  NVIC_InitStruct;
	
	//������ʼ��
	Key_GPIO_Config();
	
	//����IO�ڸ���ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	//����IO�����ж��ߵ�ӳ���ϵ
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	
	//��ʼ�������жϣ����ô���������
	EXTI_InitStruct.EXTI_Line=EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);
	
	//�����жϷ��飨NVIC������ʹ���ж�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStruct);
}


void EXTI0_IRQHandler(void)    //�жϷ�����
{
//	SysTick_Delay_Us(10);
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)  //�ж��Ƿ���
	{
		GPIOB->ODR ^=GPIO_Pin_0;
	}
	EXTI_ClearITPendingBit(EXTI_Line0);  //�����־λ
}



