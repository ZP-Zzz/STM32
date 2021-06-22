#include "timer_pwm.h"
#include "led.h"

//void TIMER3_Init(u16 arr,u16 psc)
//{
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
//	NVIC_InitTypeDef  NVIC_InitStruct;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); // 使能定时器时钟 (TIM3属于通用定时器)
// 
//	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;   //预分频值
//	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;   //向上计数
//	TIM_TimeBaseInitStruct.TIM_Period=arr;   //下一个更新事件装入活动的自动重装载寄存器周期的值
//	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
//	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct); //初始化定时器，配置arr，psc等
//	
//	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);  //使能中断
//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	NVIC_InitStruct.NVIC_IRQChannel=TIM3_IRQn;
//	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
//	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
//	NVIC_Init(&NVIC_InitStruct);//配置中断分组（NVIC），并使能中断
//	
//	TIM_Cmd(TIM3,ENABLE);  //使能定时器
//}



//void TIM3_IRQHandler(void)   //中断
//{
//	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==1)     //是否发生TIM3的中断，是就返回1
//	{
//		GPIOB->ODR ^=GPIO_Pin_5;
//		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);   //清除标志位
//	}
//}




void TIMER3_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
	 TIM_OCInitTypeDef  TIM_OCInitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  //使能定时时钟3
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO ,ENABLE);  //使能GPIOB和串口复用功能
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE); //设置重映射
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);   //初始化IO口为复用功能输出模式
		
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;   //预分频值
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;   //向上计数
	TIM_TimeBaseInitStruct.TIM_Period=arr;   //下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseInitStruct.TIM_ClockDivision=0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct); //初始化定时器，配置arr，psc等
	
	TIM_OCInitStruct.TIM_OCNPolarity=TIM_OCPolarity_High; //有效电平为高
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM2;   //模式二(TIM3_CNT>TIM3_CCR1为有效电平)
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC2Init(TIM3,&TIM_OCInitStruct);  //初始化输出比较参数
	
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);//使能预装载
	
	TIM_Cmd(TIM3,ENABLE);//使能定时器3
	
	
}



















