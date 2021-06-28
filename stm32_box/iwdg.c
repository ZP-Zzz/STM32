
#include "stm32f10x.h"
#include "iwdg.h"

void IWDG_Init(u8 Prer,u16 RLR)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //取消写保护
	IWDG_SetPrescaler(Prer);  //设置欲分频系数
	IWDG_SetReload(RLR);      //设置重装载值
	IWDG_ReloadCounter();     //喂狗
	IWDG_Enable();             //使能看门狗
	
	
}

void IWDG_Feed(void)
{
	IWDG_ReloadCounter();     //喂狗
}


//欲分频系数
//IWDG_Prescaler_4
//IWDG_Prescaler_8
//IWDG_Prescaler_16
//IWDG_Prescaler_32
//IWDG_Prescaler_64
//IWDG_Prescaler_128
//IWDG_Prescaler_256

