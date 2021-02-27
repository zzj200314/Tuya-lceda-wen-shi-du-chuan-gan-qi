/******************************************************************************
文件名称: key.c
文件标识: STC8A8K64S4A12
摘    要: 按键处理函数
当前版本: V1.0	
完成日期: 2021.02.05
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
函数名称 : Key1_ShortPress_Handle
功能描述 : Key1短按处理函数
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
static void Key1_ShortPress_Handle(void)
{
  OLED_ShowStr(24,1," Refresh  ",16);
	Get_Voltage();         //读取电池电压
	sht30_read();          //读取温湿度
	OLED_ShowStr(24,1,"          ",16);
}
/*****************************************************************************
函数名称 : Key1_LongPress_Handle
功能描述 : Key1长按处理函数
输入参数 : 无
返回参数 : 无
使用说明 : 无
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
函数名称 : key_init
功能描述 : key初始化
输入参数 : 无
返回参数 : 无
使用说明 : 无
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
函数名称 : Get_Key_Press_Time
功能描述 : 获取按键按下时间
输入参数 : last_time:上次按下时间
返回参数 : 2次按键之间差值
使用说明 : 无
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
    //Time2溢出
    time += ~last_time;
  } 

  return time;
}
/*****************************************************************************
函数名称 : key_scan
功能描述 : 扫描按键
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void key_scan(void)
{
  uint32_t time;
	
	switch(Status)
	{
		case KEY_NO:
			//有按键按下
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
			//一直长按
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
		//松开
		time = Get_Key_Press_Time(last_time);
	
		last_time = 0;
		Status = KEY_NO;
		if((time >= TIME_PRESS_SHORT) && (time < TIME_PRESS_LONG))
		{
			//短按
			if(Short_Press_Handle && (lastButtonState == 0))
			{
				Key1_ShortPress_Handle();
			}
		}
		else if(time >= TIME_PRESS_LONG)
		{
			//长按
			if(Long_Press_Handle && (lastButtonState == 0))
			{
				Key1_LongPress_Handle();
			}
		}
		
	}
}