#ifndef __usart_H__
#define __usart_H__

#include <stdio.h> 
void USART_Config(void);
void Usart_SendByte(uint8_t ch); //����һ���ֽڣ�����һ���ַ���
void Usart_SendString(char str[]);//�����ַ���
void Usart_SendHalfWord(uint16_t ch);//����һ��16λ��
	
extern uint8_t Temp;
#endif

