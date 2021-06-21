#ifndef __usart_H__
#define __usart_H__

#include <stdio.h> 
void USART_Config(void);
void Usart_SendByte(uint8_t ch);
void Usart_SendString(char str[]);

extern uint8_t Temp;
#endif

