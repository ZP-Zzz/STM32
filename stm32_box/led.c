
#include "led.h"
#include "stm32f10x.h"



void Led_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);  //使能IO口时钟
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);   //初始化IO口模式
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);   //初始化IO口模式
	
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);   //初始化IO口模式	
	
		
	GPIO_SetBits(GPIOB,GPIO_Pin_5);  //操作IO口(关闭)
	GPIO_SetBits(GPIOB,GPIO_Pin_0);  //操作IO口(关闭)
	GPIO_SetBits(GPIOB,GPIO_Pin_1);  //操作IO口(关闭)
}

