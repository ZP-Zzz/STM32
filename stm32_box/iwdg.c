
#include "stm32f10x.h"
#include "iwdg.h"

void IWDG_Init(u8 Prer,u16 RLR)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //ȡ��д����
	IWDG_SetPrescaler(Prer);  //��������Ƶϵ��
	IWDG_SetReload(RLR);      //������װ��ֵ
	IWDG_ReloadCounter();     //ι��
	IWDG_Enable();             //ʹ�ܿ��Ź�
	
	
}

void IWDG_Feed(void)
{
	IWDG_ReloadCounter();     //ι��
}


//����Ƶϵ��
//IWDG_Prescaler_4
//IWDG_Prescaler_8
//IWDG_Prescaler_16
//IWDG_Prescaler_32
//IWDG_Prescaler_64
//IWDG_Prescaler_128
//IWDG_Prescaler_256

