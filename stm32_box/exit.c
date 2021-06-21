#include "stm32f10x.h"
#include "key.h"
#include "bsp_SysTick.h"

void EXIT_Init(void)
{
	EXTI_InitTypeDef  EXTI_InitStruct;
	NVIC_InitTypeDef  NVIC_InitStruct;
	
	//按键初始化
	Key_GPIO_Config();
	
	//开启IO口复用时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	//设置IO口与中断线的映射关系
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	
	//初始化线上中断，设置触发条件等
	EXTI_InitStruct.EXTI_Line=EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);
	
	//配置中断分组（NVIC），并使能中断
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStruct);
}


void EXTI0_IRQHandler(void)    //中断服务函数
{
//	SysTick_Delay_Us(10);
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)  //判断是否按下
	{
		GPIOB->ODR ^=GPIO_Pin_0;
	}
	EXTI_ClearITPendingBit(EXTI_Line0);  //清除标志位
}



