#ifndef __wwdg_H__
#define __wwdg_H__

void WWDG_Init(uint8_t tr, uint8_t wr, uint32_t prv);
void WWDG_NVIC_Init(void);
void WWDG_Feed(void);
void WWDG_IRQHandler(void);

#endif


//�ϴ��ڵ�ֵ��������´��ڵ�0x40����ʱ���ݼ���0x3f
//���ڿ��Ź�ʱ����Դ��PCLK1��APB1���ߣ���Ƶ��
