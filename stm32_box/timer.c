#include "timer.h"
#include "led.h"

void TIMER3_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef  NVIC_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); // ʹ�ܶ�ʱ��ʱ�� (TIM3����ͨ�ö�ʱ��)
 
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;   //Ԥ��Ƶֵ
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;   //���ϼ���
	TIM_TimeBaseInitStruct.TIM_Period=arr;   //��һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct); //��ʼ����ʱ��������arr��psc��
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);  //ʹ���ж�
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStruct.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStruct);//�����жϷ��飨NVIC������ʹ���ж�
	
	TIM_Cmd(TIM3,ENABLE);  //ʹ�ܶ�ʱ��
}



void TIM3_IRQHandler(void)   //�ж�
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==1)     //�Ƿ���TIM3���жϣ��Ǿͷ���1
	{
		GPIOB->ODR ^=GPIO_Pin_5;
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);   //�����־λ
	}
}

/*���ݶ�ʱ��ʱ�ӵ�Ƶ�ʣ�����ʱ�ӵ�Ƶ����72MHZ���������Ϊһ����STM32���Լ���72M�Σ�
Ԥ��Ƶϵ�����ǽ�Ƶ�ʷָ�����Ƶϵ����72�����ʱ�ӵ�Ƶ�ʻ���72MHZ/72=1MHZ��
���������õ�ʱ��Ҫע�⣬��ֵӦ����72-1���ٶ���Ƶϵ����72-1����ôƵ�ʱ��1MHZ��
Ҳ����ζ��STM32��һ���ӻ���1M�Σ���1us��һ�Ρ����ˣ�����������ȷ��Ԥװ��ֵ��
������Ҫ��ʱ1ms������1ms=1us*1000,��ôԤװ��ֵ����1000-1��������ƣ�
��Ԥ��Ƶϵ��ȷ��������£���ʱ��ʱ������Ԥװ��ֵȷ���ˡ�����Ҫ��ֵ��һ��ԭ��
�����Ǽ����Ǵ�0��ʼ������Ҫ��һ��*/

//    TIMER3_Init(4999,7199);   //500ms��תһ��led

//  4999ָ�ľ���500ms



