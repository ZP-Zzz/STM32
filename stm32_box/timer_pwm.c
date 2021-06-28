#include "timer_pwm.h"
#include "led.h"

//void TIMER3_Init(u16 arr,u16 psc)
//{
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
//	NVIC_InitTypeDef  NVIC_InitStruct;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); // ʹ�ܶ�ʱ��ʱ�� (TIM3����ͨ�ö�ʱ��)
// 
//	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;   //Ԥ��Ƶֵ
//	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;   //���ϼ���
//	TIM_TimeBaseInitStruct.TIM_Period=arr;   //��һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
//	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
//	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct); //��ʼ����ʱ��������arr��psc��
//	
//	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);  //ʹ���ж�
//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	NVIC_InitStruct.NVIC_IRQChannel=TIM3_IRQn;
//	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
//	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
//	NVIC_Init(&NVIC_InitStruct);//�����жϷ��飨NVIC������ʹ���ж�
//	
//	TIM_Cmd(TIM3,ENABLE);  //ʹ�ܶ�ʱ��
//}



//void TIM3_IRQHandler(void)   //�ж�
//{
//	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==1)     //�Ƿ���TIM3���жϣ��Ǿͷ���1
//	{
//		GPIOB->ODR ^=GPIO_Pin_5;
//		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);   //�����־λ
//	}
//}




void TIMER3_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
	 TIM_OCInitTypeDef  TIM_OCInitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  //ʹ�ܶ�ʱʱ��3
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO ,ENABLE);  //ʹ��GPIOB�ʹ��ڸ��ù���
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE); //������ӳ��
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);   //��ʼ��IO��Ϊ���ù������ģʽ
		
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;   //Ԥ��Ƶֵ
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;   //���ϼ���
	TIM_TimeBaseInitStruct.TIM_Period=arr;   //��һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseInitStruct.TIM_ClockDivision=0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct); //��ʼ����ʱ��������arr��psc��
	
	TIM_OCInitStruct.TIM_OCNPolarity=TIM_OCPolarity_High; //��Ч��ƽΪ��
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM2;   //ģʽ��(TIM3_CNT>TIM3_CCR1Ϊ��Ч��ƽ)
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC2Init(TIM3,&TIM_OCInitStruct);  //��ʼ������Ƚϲ���
	
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);//ʹ��Ԥװ��
	
	TIM_Cmd(TIM3,ENABLE);//ʹ�ܶ�ʱ��3
	
	
}



















