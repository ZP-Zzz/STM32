#include "stm32f10x.h"
#include "GeneralTim.h"


void TIM5_Cap_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	TIM_ICInitTypeDef  TIM_ICInitStruct;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef  NVIC_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  //初始化定时器5的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //初始化按键的时钟
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPD;  //下拉输入
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
//	GPIO_InitStruct.GPIO_Speed=    //输入不需要速度
	GPIO_Init(GPIOA,&GPIO_InitStruct); //GPIOA的按键输入模式
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);    //置低电平
	
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;   //预分频值
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;   //向上计数
	TIM_TimeBaseInitStruct.TIM_Period=arr;   //下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStruct); //初始化定时器，配置arr，psc等
	
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICFilter=0x00;   //不滤波
	TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;   //上升沿捕获
	TIM_ICInitStruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;    //DIV1指每次上升沿都捕获，DIVx指x次上升沿才捕获一次
	TIM_ICInitStruct.TIM_ICSelection=TIM_ICSelection_DirectTI;   //映射到TI1上
	TIM_ICInit(TIM5,&TIM_ICInitStruct);  //初始化TIM5输入捕获参数
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStruct.NVIC_IRQChannel=TIM5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStruct);//配置中断分组（NVIC），并使能中断
	
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);  //使能中断,允许更新中断（溢出更新），允许CC1IE捕获中断
	
	TIM_Cmd(TIM5,ENABLE);  //使能定时器
	
}



u8  TIM5CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u16	TIM5CH1_CAPTURE_VAL;	//输入捕获值

void TIM5_IRQHandler(void)   //中断
{ 

 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	(还没到下降沿)
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)   //发生了中断
		 
		{	    
			if(TIM5CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM5CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM5CH1_CAPTURE_VAL=0XFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次上升沿
				TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);
		   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}
			else  								//还未开始,第一次捕获上升沿
			{
				TIM5CH1_CAPTURE_STA=0;			//清空
				TIM5CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM5,0);
				TIM5CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
			}		    
		}			     	    					   
 	}
 
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
 
}



