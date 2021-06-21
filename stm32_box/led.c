
#include "led.h"
#include "stm32f10x.h"



void Led_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);  //ʹ��IO��ʱ��
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);   //��ʼ��IO��ģʽ
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);   //��ʼ��IO��ģʽ
	
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);   //��ʼ��IO��ģʽ	
	
		
	GPIO_SetBits(GPIOB,GPIO_Pin_5);  //����IO��(�ر�)
	GPIO_SetBits(GPIOB,GPIO_Pin_0);  //����IO��(�ر�)
	GPIO_SetBits(GPIOB,GPIO_Pin_1);  //����IO��(�ر�)
}

