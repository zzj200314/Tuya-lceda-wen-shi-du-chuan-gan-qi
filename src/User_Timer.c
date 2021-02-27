/******************************************************************************
�ļ�����: User_Timer.c
�ļ���ʶ: STC8A8K64S4A12
ժ    Ҫ: Timer�û�����
��ǰ�汾: V1.0	
�������: 2021.02.06
*******************************************************************************/
#define USER_TIMER_GLOBAL
#include "include.h"

static unsigned long Timer_Value = 0;
static unsigned long Timer_Sec_Value = 0;


/*****************************************************************************
�������� : timer0_init
�������� : timer0��ʼ��
������� : ��
���ز��� : ��
ʹ��˵�� : 10����@11.0592MHz
*****************************************************************************/
void timer0_init(void)
{
	AUXR &= 0x7F;																																//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;																																//���ö�ʱ��ģʽ
	TL0 = 0x00;																																	//���ö�ʱ��ֵ
	TH0 = 0xDC;																																	//���ö�ʱ��ֵ
	TF0 = 0;																																		//���TF0��־
	TR0 = 1;																																		//��ʱ��0��ʼ��ʱ
	ET0 = 1;
	//
	Timer_Value = 0;
	FlashBuffer.SAMPLING = 15;
}
/*****************************************************************************
�������� : timer0_isr_handle
�������� : timer0�жϴ�����
������� : ��
���ز��� : ��
ʹ��˵�� : 10����@11.0592MHz
*****************************************************************************/
void timer0_isr_handle(void) interrupt 1
{
	extern uint8_t is_read_time;

	Timer_Value ++;
	if((Timer_Value % 100) == 0)
	{
		Timer_Sec_Value ++;
		if(Timer_Sec_Value % FlashBuffer.SAMPLING == 0)
		{
			//X���ʱ
			is_read_time = 1;
		}
		
		if(Timer_Sec_Value >= 60)
		{
			Timer_Sec_Value = 0;
			
			FlashBuffer.run_time ++;
		}
	}
}
/*****************************************************************************
�������� : get_count_value
�������� : ��ȡTimer0����ֵ
������� : ��
���ز��� : Timer_Value
ʹ��˵�� : ��
*****************************************************************************/
unsigned long get_count_value(void)
{
	return Timer_Value;
}