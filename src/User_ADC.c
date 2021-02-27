/******************************************************************************
文件名称: ADC.c
文件标识: STC8A8K64S4A12
摘    要: ADC硬件操作函数
当前版本: V1.0	
完成日期: 2021.02.03
*******************************************************************************/
#define	USER_ADC_GLOBALS
#include "include.h"
#include "wifi.h"



//#define Interrupt //中断方法
#define Query     //查询方法




#ifdef Interrupt

/*****************************************************************************
函数名称 : I2C_init
功能描述 : I2C初始化
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void ADC_init()
{
	P1M0 = 0x00;                                //设置P1.0为ADC口
	P1M1 = 0x01;
	ADCCFG = 0x2f;                              //设置ADC时钟为系统时钟/2/16/16
	ADC_CONTR = 0x80;                           //使能ADC模块
	EADC = 1;                                   //使能ADC中断
	EA = 1;
	ADC_CONTR |= 0x40;                          //启动AD转换
}

/*****************************************************************************
函数名称 : I2C_Isr
功能描述 : I2C中断处理函数
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void ADC_Isr() interrupt 5
{
	ADC_CONTR &= ~0x20;                         //清中断标志
	ADC_CONTR |= 0x40;                          //继续AD转换
}



#elif defined(Query)

/*****************************************************************************
函数名称 : I2C_init
功能描述 : I2C初始化
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void ADC_init()
{
	P1M0 = 0x00;                                //设置P1.0为ADC口
	P1M1 = 0x01;
	ADCCFG = 0x2f;                              //设置ADC时钟为系统时钟/2/16/16
	ADC_CONTR = 0x80;                           //使能ADC模块
}
/*****************************************************************************
函数名称 : Wait
功能描述 : 检测状态
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
int ADC_read()
{
	int res;
	
	ADC_CONTR |= 0x40;                      //启动AD转换
	_nop_();
	_nop_();
	while (!(ADC_CONTR & 0x20));            //查询ADC完成标志
	ADC_CONTR &= ~0x20;                     //清完成标志
	res = (ADC_RES<<8)|ADC_RESL;            //读取ADC结果
	
	return res;
}
#endif



/*****************************************************************************
函数名称 : WriteCmd
功能描述 : 写指令函数
输入参数 : command：指令
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void Get_Voltage()
{
	int res;
	int vcc;  //电池电压，单位mv
	int i;
	
	ADC_init();
	ADC_read();
	ADC_read();
	res = 0;
	for(i=0;i<8;i++)
	{
		res += ADC_read();
	}
	res >>= 3;
	vcc = (int)((6600L*res>>12)+50);  //电压计算
	
	if((vcc <= 4200) && (vcc >= 4088))
	{
		FlashBuffer.Power = 100;
		OLED_ShowNum(96,0,FlashBuffer.Power,3,8);
		OLED_ShowChar(120,0,'%',8);
	}
	else if((vcc <= 4088) && (vcc >= 4012))
	{
		FlashBuffer.Power = 90;
		OLED_ShowNum(96,0,FlashBuffer.Power,3,8);
		OLED_ShowChar(120,0,'%',8);
	}
	else if((vcc <= 4012) && (vcc >= 3956))
	{
		FlashBuffer.Power = 80;
		OLED_ShowNum(96,0,FlashBuffer.Power,3,8);
		OLED_ShowChar(120,0,'%',8);
	}
	else if((vcc <= 3956) && (vcc >= 3910))
	{
		FlashBuffer.Power = 70;
		OLED_ShowNum(96,0,FlashBuffer.Power,3,8);
		OLED_ShowChar(120,0,'%',8);
	}
	else if((vcc <= 3910) && (vcc >= 3870))
	{
		FlashBuffer.Power = 60;
		OLED_ShowNum(96,0,FlashBuffer.Power,3,8);
		OLED_ShowChar(120,0,'%',8);
	}
	else if((vcc <= 3870) && (vcc >= 3830))
	{
		FlashBuffer.Power = 50;
		OLED_ShowNum(96,0,FlashBuffer.Power,3,8);
		OLED_ShowChar(120,0,'%',8);
	}
	else if((vcc <= 3830) && (vcc >= 3802))
	{
		FlashBuffer.Power = 40;
		OLED_ShowNum(96,0,FlashBuffer.Power,3,8);
		OLED_ShowChar(120,0,'%',8);
	}
	else if((vcc <= 3802) && (vcc >= 3782))
	{
		FlashBuffer.Power = 30;
		OLED_ShowNum(96,0,FlashBuffer.Power,3,8);
		OLED_ShowChar(120,0,'%',8);
	}
	else if((vcc <= 3782) && (vcc >= 3764))
	{
		FlashBuffer.Power = 20;
		OLED_ShowNum(96,0,FlashBuffer.Power,3,8);
		OLED_ShowChar(120,0,'%',8);
	}
	else if((vcc <= 3764) && (vcc >= 3740))
	{
		FlashBuffer.Power = 10;
		OLED_ShowNum(96,0,FlashBuffer.Power,3,8);
		OLED_ShowChar(120,0,'%',8);
	}
	else if(vcc <= 3740)
	{
		FlashBuffer.Power = 0;
		OLED_ShowNum(96,0,FlashBuffer.Power,3,8);
		OLED_ShowChar(120,0,'%',8);
	}
	mcu_dp_enum_update(DPID_BATTERY_STATE,FlashBuffer.Power);
	mcu_dp_value_update(DPID_BATTERY_PERCENTAGE,FlashBuffer.Power); //VALUE型数据上报;
}
