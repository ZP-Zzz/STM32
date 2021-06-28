#include "stm32f10x.h"
#include "GeneralTim.h"


void TIM5_Cap_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	TIM_ICInitTypeDef  TIM_ICInitStruct;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef  NVIC_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  //��ʼ����ʱ��5��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //��ʼ��������ʱ��
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPD;  //��������
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
//	GPIO_InitStruct.GPIO_Speed=    //���벻��Ҫ�ٶ�
	GPIO_Init(GPIOA,&GPIO_InitStruct); //GPIOA�İ�������ģʽ
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);    //�õ͵�ƽ
	
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;   //Ԥ��Ƶֵ
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;   //���ϼ���
	TIM_TimeBaseInitStruct.TIM_Period=arr;   //��һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStruct); //��ʼ����ʱ��������arr��psc��
	
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICFilter=0x00;   //���˲�
	TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;   //�����ز���
	TIM_ICInitStruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;    //DIV1ָÿ�������ض�����DIVxָx�������زŲ���һ��
	TIM_ICInitStruct.TIM_ICSelection=TIM_ICSelection_DirectTI;   //ӳ�䵽TI1��
	TIM_ICInit(TIM5,&TIM_ICInitStruct);  //��ʼ��TIM5���벶�����
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStruct.NVIC_IRQChannel=TIM5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStruct);//�����жϷ��飨NVIC������ʹ���ж�
	
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);  //ʹ���ж�,��������жϣ�������£�������CC1IE�����ж�
	
	TIM_Cmd(TIM5,ENABLE);  //ʹ�ܶ�ʱ��
	
}



u8  TIM5CH1_CAPTURE_STA=0;	//���벶��״̬		    				
u16	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ

void TIM5_IRQHandler(void)   //�ж�
{ 

 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	(��û���½���)
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)   //�������ж�
		 
		{	    
			if(TIM5CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM5CH1_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM5CH1_CAPTURE_VAL=0XFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//����1���������¼�
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ��������
				TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);
		   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
			}
			else  								//��δ��ʼ,��һ�β���������
			{
				TIM5CH1_CAPTURE_STA=0;			//���
				TIM5CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM5,0);
				TIM5CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
			}		    
		}			     	    					   
 	}
 
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
 
}



