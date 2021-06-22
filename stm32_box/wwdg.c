#include "stm32f10x.h"
#include "wwdg.h" 
#include "bsp_SysTick.h"

/* WWDG 配置函数
 * tr ：递减计时器的初值， 取值范围为：0x7f~0x40
 * wr ：窗口值，取值范围为：0x7f~0x40
 * prv：预分频器值，取值可以是
 *      @arg WWDG_Prescaler_1: WWDG counter clock = (PCLK1(36MHZ)/4096)/1
 *      @arg WWDG_Prescaler_2: WWDG counter clock = (PCLK1(36mhz)/4096)/2
 *      @arg WWDG_Prescaler_4: WWDG counter clock = (PCLK1(36mhz)/4096)/4
 *      @arg WWDG_Prescaler_8: WWDG counter clock = (PCLK1(36mhz)/4096)/8
 */

void WWDG_Init(uint8_t tr, uint8_t wr, uint32_t prv)
{	
	// 开启 WWDG 时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	
	// 设置递减计数器的值
	WWDG_SetCounter( tr );
	
	// 设置预分频器的值
	WWDG_SetPrescaler( prv );
	
	// 设置上窗口值
	WWDG_SetWindowValue( wr );
	
	// 设置计数器的值，使能WWDG
	WWDG_Enable(0X7F);	// 窗口计数器初值，范围为：0x40~0x7f，一般设置成最大0X7F
	
	// 清除提前唤醒中断标志位
	WWDG_ClearFlag();	
	
	// 配置WWDG中断优先级
	WWDG_NVIC_Init();	
	
	// 开WWDG 中断
	WWDG_EnableIT();
}




// WWDG 中断优先级初始化
void WWDG_NVIC_Init(void)
{
  NVIC_InitTypeDef NVIC_InitStructure; 
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
  NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}



// 喂狗
void WWDG_Feed(void)
{
	// 喂狗，刷新递减计数器的值，设置成最大WDG_CNT=0X7F
	WWDG_SetCounter( 0X7F );
}




 // WWDG 中断复服务程序，如果发生了此中断，表示程序已经出现了故障，
 // 这是一个死前中断。在此中断服务程序中应该干最重要的事，
 // 比如保存重要的数据等，这个时间具体有多长，要
 // 由 WDGTB 的值决定：
 // WDGTB:0 113us
 // WDGTB:1 227us
 // WDGTB:2 455us
 // WDGTB:3 910us
void WWDG_IRQHandler(void)
{
	
 // 清除中断标志位
	WWDG_ClearFlag();
	
 //LED2 亮，点亮 LED 只是示意性的操作，
 //真正使用的时候，这里应该是做最重要的事情
	GPIOB->ODR ^=GPIO_Pin_1;
}




