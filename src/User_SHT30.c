/******************************************************************************
文件名称: User_SHT30.c
文件标识: STC8A8K64S4A12
摘    要: SHT30操作函数
当前版本: V1.0.1	
完成日期: 2021.02.03
*******************************************************************************/
#define	USER_SHT30_GLOBALS
#include "include.h"
#include "wifi.h"


/*****************************************************************************
函数名称 : SHT_Init
功能描述 : SHT30初始化
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void SHT_Init()
{
	Start();
	SendData(SHT30_Address);
  SendACK();
	SendData(PERIODIC_MODE_10S>>8);//设置周期模式
  SendACK();
	SendData(PERIODIC_MODE_10S);
  SendACK();
	Stop();
}
/*****************************************************************************
函数名称 : sht_crc
功能描述 : crc-8校验
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/ 
uint8_t sht_crc(uint8_t *shtdata, uint8_t count)
{
	uint8_t crc_bit;        // bit mask
	uint8_t crc = 0xFF;     // calculated checksum
	uint8_t byteCtr;        // byte counter
	
  // calculates 8-Bit checksum with given polynomial
	for(byteCtr = 0; byteCtr < count; ++byteCtr)
	{
		crc ^= (shtdata[byteCtr]);
		for(crc_bit = 8; crc_bit > 0; --crc_bit) //crc校验，最高位是1就^0x31
		{
			if(crc & 0x80)
				crc = (crc << 1) ^ 0x31;
			else
			  crc = (crc << 1);
		}
	}
	return crc;
}
/*****************************************************************************
函数名称 : sht30_read
功能描述 : SHT30数据读取，通过oled显示
输入参数 : 无
返回参数 : 五
使用说明 : 无
*****************************************************************************/
void sht30_read()
{
	uint8_t result[10];
	uint16_t St;     //传感器的温度原始值
  uint16_t Srh;    //传感器的湿度原始值
	uint16_t e;      //计算出的水汽压
	signed int T;
	int AT;
	
	Start();
	SendData(SHT30_Address);
  SendACK();
	SendData(0xe0);
  SendACK();
	SendData(0x00);
  SendACK();
	
	Start();   //开始读数据
	SendData(SHT30_Address+1);
	SendACK();
  result[0] = RecvData();  //读到的数据暂存在result数组里
	SendACK();
	result[1] = RecvData();
	SendACK();
	result[2] = RecvData();
	SendACK();
	result[3] = RecvData();
	SendACK();
	result[4] = RecvData();
	SendACK();
	result[5] = RecvData();
	Stop();
	
	if((sht_crc(result, 2)==result[2]) && (sht_crc(result+3, 2)==result[5]))//crc校验
	{
		St = (result[0]<<8) | result[1];  //温度拼接
		Srh = (result[3]<<8) | result[4]; //湿度拼接
		FlashBuffer.temper = (-450+1750*(1.0*St/65535));  //10倍实际温度，上报需要
		T = FlashBuffer.temper/10;                      //温度计算
		FlashBuffer.humidity = 100*(1.0*Srh/65535);         //湿度计算
		e = (FlashBuffer.humidity/100)*6.105*exp(17.27*T/(237.7+T));//水气压计算
		AT = 1.07*T+0.2*e-2.7;            //体感温度计算
		
		
		mcu_dp_value_update(DPID_TEMP_CURRENT,FlashBuffer.temper);     //VALUE型数据上报;
    mcu_dp_value_update(DPID_HUMIDITY_VALUE,FlashBuffer.humidity); //VALUE型数据上报;
		OLED_ShowNum(32,4,T,2,16);   //显示温度
		if(T>0)
			OLED_ShowChar(48,4,'`',16);
		else
			OLED_ShowChar(56,4,'`',16);
		
		OLED_ShowNum(104,4,FlashBuffer.humidity,2,16);  //显示湿度
		OLED_ShowChar(120,4,'%',16);
		
		OLED_ShowNum(64,6,AT,2,16);  //显示体感温度
		if(AT>0)
			OLED_ShowChar(80,6,'`',16);
		else
			OLED_ShowChar(88,6,'`',16);
	}
	else  //校验失败
	{
		OLED_ShowStr(32,4,"error",16);  //显示错误
	}
}