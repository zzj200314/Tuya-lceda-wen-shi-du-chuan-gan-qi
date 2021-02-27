/******************************************************************************
�ļ�����: User_SHT30.c
�ļ���ʶ: STC8A8K64S4A12
ժ    Ҫ: SHT30��������
��ǰ�汾: V1.0.1	
�������: 2021.02.03
*******************************************************************************/
#define	USER_SHT30_GLOBALS
#include "include.h"
#include "wifi.h"


/*****************************************************************************
�������� : SHT_Init
�������� : SHT30��ʼ��
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void SHT_Init()
{
	Start();
	SendData(SHT30_Address);
  SendACK();
	SendData(PERIODIC_MODE_10S>>8);//��������ģʽ
  SendACK();
	SendData(PERIODIC_MODE_10S);
  SendACK();
	Stop();
}
/*****************************************************************************
�������� : sht_crc
�������� : crc-8У��
������� : ��
���ز��� : ��
ʹ��˵�� : ��
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
		for(crc_bit = 8; crc_bit > 0; --crc_bit) //crcУ�飬���λ��1��^0x31
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
�������� : sht30_read
�������� : SHT30���ݶ�ȡ��ͨ��oled��ʾ
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void sht30_read()
{
	uint8_t result[10];
	uint16_t St;     //���������¶�ԭʼֵ
  uint16_t Srh;    //��������ʪ��ԭʼֵ
	uint16_t e;      //�������ˮ��ѹ
	signed int T;
	int AT;
	
	Start();
	SendData(SHT30_Address);
  SendACK();
	SendData(0xe0);
  SendACK();
	SendData(0x00);
  SendACK();
	
	Start();   //��ʼ������
	SendData(SHT30_Address+1);
	SendACK();
  result[0] = RecvData();  //�����������ݴ���result������
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
	
	if((sht_crc(result, 2)==result[2]) && (sht_crc(result+3, 2)==result[5]))//crcУ��
	{
		St = (result[0]<<8) | result[1];  //�¶�ƴ��
		Srh = (result[3]<<8) | result[4]; //ʪ��ƴ��
		FlashBuffer.temper = (-450+1750*(1.0*St/65535));  //10��ʵ���¶ȣ��ϱ���Ҫ
		T = FlashBuffer.temper/10;                      //�¶ȼ���
		FlashBuffer.humidity = 100*(1.0*Srh/65535);         //ʪ�ȼ���
		e = (FlashBuffer.humidity/100)*6.105*exp(17.27*T/(237.7+T));//ˮ��ѹ����
		AT = 1.07*T+0.2*e-2.7;            //����¶ȼ���
		
		
		mcu_dp_value_update(DPID_TEMP_CURRENT,FlashBuffer.temper);     //VALUE�������ϱ�;
    mcu_dp_value_update(DPID_HUMIDITY_VALUE,FlashBuffer.humidity); //VALUE�������ϱ�;
		OLED_ShowNum(32,4,T,2,16);   //��ʾ�¶�
		if(T>0)
			OLED_ShowChar(48,4,'`',16);
		else
			OLED_ShowChar(56,4,'`',16);
		
		OLED_ShowNum(104,4,FlashBuffer.humidity,2,16);  //��ʾʪ��
		OLED_ShowChar(120,4,'%',16);
		
		OLED_ShowNum(64,6,AT,2,16);  //��ʾ����¶�
		if(AT>0)
			OLED_ShowChar(80,6,'`',16);
		else
			OLED_ShowChar(88,6,'`',16);
	}
	else  //У��ʧ��
	{
		OLED_ShowStr(32,4,"error",16);  //��ʾ����
	}
}