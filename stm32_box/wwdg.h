#ifndef __wwdg_H__
#define __wwdg_H__

void WWDG_Init(uint8_t tr, uint8_t wr, uint32_t prv);
void WWDG_NVIC_Init(void);
void WWDG_Feed(void);
void WWDG_IRQHandler(void);

#endif


//上窗口的值必须大于下窗口的0x40，定时器递减到0x3f
//窗口看门狗时钟来源于PCLK1（APB1总线）分频后。
