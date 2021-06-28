#include "timer.h"
#include "led.h"

void TIMER3_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef  NVIC_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); // 使能定时器时钟 (TIM3属于通用定时器)
 
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;   //预分频值
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;   //向上计数
	TIM_TimeBaseInitStruct.TIM_Period=arr;   //下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct); //初始化定时器，配置arr，psc等
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);  //使能中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStruct.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStruct);//配置中断分组（NVIC），并使能中断
	
	TIM_Cmd(TIM3,ENABLE);  //使能定时器
}



void TIM3_IRQHandler(void)   //中断
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==1)     //是否发生TIM3的中断，是就返回1
	{
		GPIOB->ODR ^=GPIO_Pin_5;
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);   //清除标志位
	}
}

/*根据定时器时钟的频率，比如时钟的频率是72MHZ，可以理解为一秒钟STM32会自己数72M次，
预分频系数就是将频率分割，比如分频系数是72，则该时钟的频率会变成72MHZ/72=1MHZ，
但是在设置的时候要注意，数值应该是72-1。假定分频系数是72-1，那么频率变成1MHZ，
也就意味着STM32在一秒钟会数1M次，即1us数一次。好了，接下来就是确定预装载值，
比如需要定时1ms，由于1ms=1us*1000,那么预装载值就是1000-1；如此类推，
在预分频系数确定的情况下，定时的时长就由预装载值确定了。至于要把值减一的原因，
估计是计数是从0开始，所以要减一。*/

//    TIMER3_Init(4999,7199);   //500ms反转一次led

//  4999指的就是500ms



