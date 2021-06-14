#include "stm32f10x.h"

int main(void)
{
	
	//打开 GPIOB 端口时钟
	*(unsigned int *)0x40021018 |=(1<<3);
	
	//配置IO口为输出
	*(unsigned int *)0x40010c00 |=(1<<0);
	
	//控制ODR寄存器
	*(unsigned int *)0x40010c0c &=~(1<<0);
	return 0;
}


void SystemInit()
{
	//函数体为空，目的是为了骗过编译器不报错
}

