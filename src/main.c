/******************************************************************************
�ļ�����: Main.c
�ļ���ʶ: STC8A8K64S4A12
ժ    Ҫ: ������
��ǰ�汾: V1.0	
�������: 2021.02.07
*******************************************************************************/
#define MAINWORK_GLOBALS
#include "include.h"
#include "wifi.h"


volatile uint8_t is_read_time = 0;

void Delay100ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 6;
	j = 157;
	k = 59;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
/*****************************************************************************
�������� : Bsp_Init
�������� : ��ʼ��Ӳ��
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
static void Bsp_Init(void)
{
	uart3_init();        //����3��ʼ��
	wifi_protocol_init();//WiFiģ���ʼ��
	I2C_init();          //I2C��ʼ��
	OLED_Init();         //OLED��ʼ��
	OLED_Clear();        //OLED����
	SHT_Init();          //SHT3X��ʼ��
	timer0_init();       //��ʱ����ʼ��	
	key_init();
}
/*****************************************************************************
�������� : Boot_animation
�������� : ��������
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void Boot_animation()
{
	uint16_t i,j;
	for(i=0;i<48;i++)  //i��֡��
	{	
		for(j=0;j<8;j++)
		{
			OLED_SetPos(0,j);
			OLED_OLED_WR_Byte_con(table+128*(j+i*8),128);
		}
		Delay100ms();
	}		
}

void welcome()
{
	//OLED_DrawBMP(0,0,16,1,UI);
	//OLED_ShowStr(0,1,"Hello World! ",16);
	OLED_ShowCHinese(0,4,0);
  OLED_ShowCHinese(16,4,1);
	OLED_ShowCHinese(72,4,2);
	OLED_ShowCHinese(88,4,1);
	OLED_ShowCHinese(0,6,3);
	OLED_ShowCHinese(16,6,4);
	OLED_ShowCHinese(32,6,0);
	OLED_ShowCHinese(48,6,1);
}
/*****************************************************************************
�������� : wifi_work_state_led
�������� : wifi״̬��ѯ
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void wifi_work_state_led(void)
{
  uint8_t wifi_state = mcu_get_wifi_work_state();
	switch(wifi_state)
	{
	case SMART_CONFIG_STATE:            //smartconfig����״̬
	  OLED_ShowStr(0,0,"  S! ",8);
		break;
		
	case AP_STATE:                      //AP����״̬
	  OLED_ShowStr(0,0,"  A! ",8);
		break;
		
	case WIFI_NOT_CONNECTED:            //WIFI���óɹ���δ����·����
		OLED_DrawBMP(0,0,24,1,UI1);
		OLED_ShowStr(24,0,"  ",8);
		break;
		
	case WIFI_CONNECTED:                //WIFI���óɹ�������·����
		OLED_DrawBMP(0,0,24,1,UI2);
		OLED_ShowStr(24,0,"  ",8);
		break;
		
	case WIFI_CONN_CLOUD:               //WIFI�Ѿ��������Ʒ�����
		OLED_DrawBMP(0,0,24,1,UI3);
		OLED_ShowStr(24,0,"  ",8);
		break;
		
	case WIFI_LOW_POWER:                //WIFI���ڵ͹���ģʽ
		OLED_DrawBMP(0,0,24,1,UI4);
		OLED_ShowStr(24,0,"  ",8);
		break;
		
	case SMART_AND_AP_STATE:            //WIFI smartconfig&AP ģʽ
		OLED_ShowStr(0,0,"  SA ",8);
		break;
		
	default:                            //δ֪״̬
		OLED_ShowStr(0,0,"error",8);
	 break;
	}
}
/*****************************************************************************
�������� : read_sensor
�������� : ��ȡ������
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
static void read_sensor(void)
{
	Get_Voltage();         //��ȡ��ص�ѹ
	sht30_read();          //��ȡ��ʪ��
}
/*****************************************************************************
�������� : main
�������� : ������
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void main(void)
{
	//��ʼ��
	Bsp_Init();
	
	//��������
	Boot_animation();
	OLED_Clear();
	
	Delay100ms();
	welcome();
	read_sensor();
	
	//��ѭ��
	while(1)
	{
		//wifi���ݴ���
		wifi_uart_service();
		//����ɨ��
		key_scan();
		//wifi״ָ̬ʾ��
		wifi_work_state_led();
		if(is_read_time == 1)                                                       //15���ȡһ��
		{
		  //��ȡ���������ϱ�
		  read_sensor();                                 
		  is_read_time = 0;
		}
	}
	
}