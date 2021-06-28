
#ifndef __tpad_H__
#define __tpad_H__
#include "stm32f10x.h"
#include "bsp_SysTick.h"
#include "usart.h"

uint8_t TPAD_Init(void);
uint8_t TPAD_Scan(void);
uint16_t TPAD_Get_MaxVal( uint8_t num );
void TPAD_TIM_Init(void);
uint16_t TPAD_Get_Val(void);
void TPAD_Reset(void);
#endif

