#include "stm32f10x.h"
#include "wwdg.h" 
#include "bsp_SysTick.h"

/* WWDG ���ú���
 * tr ���ݼ���ʱ���ĳ�ֵ�� ȡֵ��ΧΪ��0x7f~0x40
 * wr ������ֵ��ȡֵ��ΧΪ��0x7f~0x40
 * prv��Ԥ��Ƶ��ֵ��ȡֵ������
 *      @arg WWDG_Prescaler_1: WWDG counter clock = (PCLK1(36MHZ)/4096)/1
 *      @arg WWDG_Prescaler_2: WWDG counter clock = (PCLK1(36mhz)/4096)/2
 *      @arg WWDG_Prescaler_4: WWDG counter clock = (PCLK1(36mhz)/4096)/4
 *      @arg WWDG_Prescaler_8: WWDG counter clock = (PCLK1(36mhz)/4096)/8
 */

void WWDG_Init(uint8_t tr, uint8_t wr, uint32_t prv)
{	
	// ���� WWDG ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	
	// ���õݼ���������ֵ
	WWDG_SetCounter( tr );
	
	// ����Ԥ��Ƶ����ֵ
	WWDG_SetPrescaler( prv );
	
	// �����ϴ���ֵ
	WWDG_SetWindowValue( wr );
	
	// ���ü�������ֵ��ʹ��WWDG
	WWDG_Enable(0X7F);	// ���ڼ�������ֵ����ΧΪ��0x40~0x7f��һ�����ó����0X7F
	
	// �����ǰ�����жϱ�־λ
	WWDG_ClearFlag();	
	
	// ����WWDG�ж����ȼ�
	WWDG_NVIC_Init();	
	
	// ��WWDG �ж�
	WWDG_EnableIT();
}




// WWDG �ж����ȼ���ʼ��
void WWDG_NVIC_Init(void)
{
  NVIC_InitTypeDef NVIC_InitStructure; 
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
  NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}



// ι��
void WWDG_Feed(void)
{
	// ι����ˢ�µݼ���������ֵ�����ó����WDG_CNT=0X7F
	WWDG_SetCounter( 0X7F );
}




 // WWDG �жϸ����������������˴��жϣ���ʾ�����Ѿ������˹��ϣ�
 // ����һ����ǰ�жϡ��ڴ��жϷ��������Ӧ�ø�����Ҫ���£�
 // ���籣����Ҫ�����ݵȣ����ʱ������ж೤��Ҫ
 // �� WDGTB ��ֵ������
 // WDGTB:0 113us
 // WDGTB:1 227us
 // WDGTB:2 455us
 // WDGTB:3 910us
void WWDG_IRQHandler(void)
{
	
 // ����жϱ�־λ
	WWDG_ClearFlag();
	
 //LED2 �������� LED ֻ��ʾ���ԵĲ�����
 //����ʹ�õ�ʱ������Ӧ����������Ҫ������
	GPIOB->ODR ^=GPIO_Pin_1;
}




