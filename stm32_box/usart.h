#ifndef __usart_H__
#define __usart_H__

#include <stdio.h> 
void USART_Config(void);
void Usart_SendByte(uint8_t ch); //发送一个字节（发送一个字符）
void Usart_SendString(char str[]);//发送字符串
void Usart_SendHalfWord(uint16_t ch);//发送一个16位数
	
extern uint8_t Temp;
#endif

