#include "stm32f10x.h"

int main(void)
{
	
	//�� GPIOB �˿�ʱ��
	*(unsigned int *)0x40021018 |=(1<<3);
	
	//����IO��Ϊ���
	*(unsigned int *)0x40010c00 |=(1<<0);
	
	//����ODR�Ĵ���
	*(unsigned int *)0x40010c0c &=~(1<<0);
	return 0;
}


void SystemInit()
{
	//������Ϊ�գ�Ŀ����Ϊ��ƭ��������������
}

