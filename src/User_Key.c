/******************************************************************************
�ļ�����: key.c
�ļ���ʶ: STC8A8K64S4A12
ժ    Ҫ: ����������
��ǰ�汾: V1.0	
�������: 2021.02.05
*******************************************************************************/
#define USER_KEY_GLOBAL
#include "include.h"
#include "wifi.h"



uint32_t last_time;
uint8_t Status;
KEY_HANDLE Short_Press_Handle;
KEY_HANDLE Long_Press_Handle;
bit lastButtonState;

/*****************************************************************************
�������� : Key1_ShortPress_Handle
�������� : Key1�̰�������
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
static void Key1_ShortPress_Handle(void)
{
  OLED_ShowStr(24,1," Refresh  ",16);
	Get_Voltage();         //��ȡ��ص�ѹ
	sht30_read();          //��ȡ��ʪ��
	OLED_ShowStr(24,1,"          ",16);
}
/*****************************************************************************
�������� : Key1_LongPress_Handle
�������� : Key1����������
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
static void Key1_LongPress_Handle(void)
{
	//OLED_ShowStr(24,1,"reset wifi",16);
	mcu_reset_wifi();
	if((mcu_get_wifi_work_state() == SMART_CONFIG_STATE) || (mcu_get_wifi_work_state() == AP_STATE))
	{
		OLED_ShowStr(24,1,"reset wifi",16);
	}
	//OLED_ShowStr(24,1,"          ",16);
}
/*****************************************************************************
�������� : key_init
�������� : key��ʼ��
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void key_init(void)
{
	last_time=0;
	Status=0;
	lastButtonState=0;
  //
  Long_Press_Handle = Key1_LongPress_Handle;
  //
  Short_Press_Handle = Key1_ShortPress_Handle;
}
/*****************************************************************************
�������� : Get_Key_Press_Time
�������� : ��ȡ��������ʱ��
������� : last_time:�ϴΰ���ʱ��
���ز��� : 2�ΰ���֮���ֵ
ʹ��˵�� : ��
*****************************************************************************/
static uint32_t Get_Key_Press_Time(uint32_t last_time)
{
  uint32_t time;
  
  time = get_count_value();
  if(time >= last_time)
  {
    time -= last_time;
  }
  else
  {
    //Time2���
    time += ~last_time;
  } 

  return time;
}
/*****************************************************************************
�������� : key_scan
�������� : ɨ�谴��
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void key_scan(void)
{
  uint32_t time;
	
	switch(Status)
	{
		case KEY_NO:
			//�а�������
			if(K1==0)
			{
				Status = KEY_DOWN;
				last_time = get_count_value();
			}
			break;
			
		case KEY_DOWN:
			if(K1==1)
			{
				Status = KEY_UP;
				lastButtonState = 0;
			}
			break;
							
		case KEY_LONG:
			if(K1==1)
			{
				last_time = 0;
				Status = KEY_NO;
				lastButtonState = 0;
			}
			break;  
	}

	if((Status == KEY_DOWN) || (Status == KEY_LONG))
	{
		time = Get_Key_Press_Time(last_time);
		if(time >= TIME_PRESS_LONG)
		{
			//һֱ����
			//last_time = 0;
			Status = KEY_LONG;
			if(Long_Press_Handle && (lastButtonState == 0))
			{
				Key1_LongPress_Handle();
				lastButtonState = 1;
			}
		}          
	}
	else if(Status == KEY_UP)
	{
		//�ɿ�
		time = Get_Key_Press_Time(last_time);
	
		last_time = 0;
		Status = KEY_NO;
		if((time >= TIME_PRESS_SHORT) && (time < TIME_PRESS_LONG))
		{
			//�̰�
			if(Short_Press_Handle && (lastButtonState == 0))
			{
				Key1_ShortPress_Handle();
			}
		}
		else if(time >= TIME_PRESS_LONG)
		{
			//����
			if(Long_Press_Handle && (lastButtonState == 0))
			{
				Key1_LongPress_Handle();
			}
		}
		
	}
}