/******************************************************************************
�ļ�����: OLED.c
�ļ���ʶ: STC8A8K64S4A12
ժ    Ҫ: OLED��������
��ǰ�汾: V1.0	
�������: 2021.01.25
*******************************************************************************/
#define	USER_OLED_GLOBALS
#include "include.h"



/*****************************************************************************
�������� : OLED_WR_Byte
�������� : OLEDдһ�ֽ�
������� : dat��Ҫд������� cmd=1дָ�cmd=0д����
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd==1)
	{
		WriteCmd(dat,OLED_Address);
	}
	else
	{
		WriteDat(dat,OLED_Address);
	}
}
/*****************************************************************************
�������� : OLED_OLED_WR_Byte_con
�������� : ����д��count������
������� : dat[]��Ҫд�������  countд��ĸ���
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/ 
void OLED_OLED_WR_Byte_con(uint8_t dat[], uint16_t count)//д����������count��
{
	int i = 0;
	Start();
	SendData(OLED_Address);                        //D/C#=0; R/W#=0
	SendACK();       
	SendData(0x40);                        //write data
	SendACK();       
	for(i = 0 ;i < count ;i++)
	{
		SendData(dat[i]);
		SendACK();
	}
	Stop();
}
/*****************************************************************************
�������� : OLED_OLED_WR_Byte_same
�������� : ����д��count����ͬ������
������� : dat��Ҫд�������  count���ظ�����
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/ 
/*void OLED_OLED_WR_Byte_same(uint8_t dat, uint16_t count)//д����������count��
{
	int i = 0;
	Start();
	SendData(OLED_Address);                        //D/C#=0; R/W#=0
	SendACK();       
	SendData(0x40);                        //write data
	SendACK();       
	for(i = 0 ;i < count ;i++)
	{
		SendData(dat);
		SendACK();
	}
	Stop();
}*/
/*****************************************************************************
�������� : OLED_Init
�������� : OLED��ʼ��
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void OLED_Init()
{
	OLED_WR_Byte(0xAE,1);//--display off
 	OLED_WR_Byte(0x00,1);//--set low column address
 	OLED_WR_Byte(0x10,1);//--set high column address
 	OLED_WR_Byte(0x40,1);//--set display start line
	OLED_WR_Byte(0xB0,1);//--set page address
 	OLED_WR_Byte(0x81,1);//--contract control
 	OLED_WR_Byte(0xFF,1);//--Set SEG Output Current Brightness
 	OLED_WR_Byte(0xA1,1);//--set segment remap     0xa0���ҷ��� 0xa1����
	OLED_WR_Byte(0xA6,1);//--normal / reverse
	OLED_WR_Byte(0xA8,1);//--multiplex ratio
	OLED_WR_Byte(0x3F,1);//--duty = 1/64
 	OLED_WR_Byte(0xC8,1);//--Com scan direction   0xc0���·��� 0xc8����
 	OLED_WR_Byte(0xD3,1);//--set display offset
 	OLED_WR_Byte(0x00,1);//
	OLED_WR_Byte(0xD5,1);//--set osc division
 	OLED_WR_Byte(0x80,1);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,1);//--set pre-charge period
 	OLED_WR_Byte(0xF1,1);//--Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
 	OLED_WR_Byte(0xDA,1);//--set COM pins
 	OLED_WR_Byte(0x12,1);//
 	OLED_WR_Byte(0xDB,1);//--set vcomh
//OLED_WR_Byte(0x40,1);//--Set VCOM Deselect Level
  OLED_WR_Byte(0x30,1);//
 	OLED_WR_Byte(0x8D,1);//--set charge pump disable
	OLED_WR_Byte(0x14,1);//--set(0x10) disable
 	OLED_WR_Byte(0xaf,1);//--turn on oled panel
}
/*****************************************************************************
�������� : OLED_Clear
�������� : OLED����
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void OLED_Clear(void)
{
  uint8_t i,n;              //�������
  for(i=0; i<8; i++)
  {
    OLED_WR_Byte(0xb0+i,1); //����ҳ��ַ��0~7��
    OLED_WR_Byte(0x00,1);   //������ʾλ�á��е͵�ַ
    OLED_WR_Byte(0x10,1);   //������ʾλ�á��иߵ�ַ
    for(n=0; n<128; n++)OLED_WR_Byte(0x00,0); //д0x00����Ļ�Ĵ�����
  }
}
/*****************************************************************************
�������� : OLED_SetPos
�������� : ���ÿ�ʼ�Ĺ��λ��
������� : x��y��λ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void OLED_SetPos(uint8_t x, uint8_t y)
{
	OLED_WR_Byte(0xb0+y,1);             //д��ҳ��ַ
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,1); //д���е͵�ַ
	OLED_WR_Byte(x&0x0f,1);             //д���иߵ�ַ
}
/*****************************************************************************
�������� : OLED_ON
�������� : ��OLED�������л���
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/ 
/*void OLED_ON(void)
{
  OLED_WR_Byte(0X8D,1);  //���õ�ɱ�
  OLED_WR_Byte(0X14,1);  //������ɱ�
  OLED_WR_Byte(0XAF,1);  //OLED����
}*/
/*****************************************************************************
�������� : OLED_OFF
�������� : ��OLED���� -- ����ģʽ��,OLED���Ĳ���10uA
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/ 
/*void OLED_OFF(void)
{
  OLED_WR_Byte(0X8D,1);  //���õ�ɱ�
  OLED_WR_Byte(0X10,1);  //�رյ�ɱ�
  OLED_WR_Byte(0XAE,1);  //OLED����
}*/
/*****************************************************************************
�������� : OLED_ShowChar
�������� : ��ʾ6*8��8*16һ����׼ASCII�ַ���
������� : x����ʼ��
					 y����ʼҳ��TextSize = 16ռ��ҳ��TextSize = 8ռ1ҳ
					 ch���ַ�
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/ 
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t ch, uint8_t TextSize)
{
  uint8_t c=0,i=0;
  c = ch-' ';//��ȡ�ַ���ƫ����	
	if(x>Max_Column-1)//������鳬���˷�Χ���ʹ���2ҳ�ĵ�0�п�ʼ
	{
		x=0;
		y=y+2;
	}
  if(TextSize==16)//�ַ���С���Ϊ 2 = 8*16
  {
		OLED_SetPos(x,y);//��x y ��ʼ����
    for(i=0; i<8; i++)//ѭ��8�� ռ8��
      OLED_WR_Byte(F8X16[c*16+i],0);//�ҳ��ַ� c ������λ�ã����ڵ�һҳ���л���
		OLED_SetPos(x,y+1);//ҳ����1
		for(i=0; i<8; i++)//ѭ��8��
      OLED_WR_Byte(F8X16[c*16+i+8],0);//�ѵڶ�ҳ����������
  }
	else
  {//�ַ���СΪ 6 = 6*8
		OLED_SetPos(x,y);//һҳ�Ϳ��Ի���
    for(i=0; i<6; i++)//ѭ��6�� ��ռ6��
      OLED_WR_Byte(F6x8[c][i],0);//���ַ�����
  }
}
/*****************************************************************************
�������� : OLED_ShowStr
�������� : ��ʾ�ַ���
������� : x����ʼ��
					 y����ʼҳ
					 *ch����һ���ַ��׵�ַ
           TextSize���ַ���С(1:6*8 ; 2:8*16)
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/ 
void OLED_ShowStr(uint8_t x, uint8_t y, uint8_t *ch, uint8_t TextSize)
{
  uint8_t j = 0;//�������
	while(ch[j] != '\0')//����������һ���ַ�
	{		
		OLED_ShowChar(x,y,ch[j],TextSize);//��ʾ�ַ�
		if(TextSize==8)
		{
			x += 6;//������6 ��һ���ַ�������ռ6
			if(x > 122)  //���x����128���л�ҳ���Ӹ�ҳ�ĵ�һ����ʾ
			{
				x = 0;  
				y += 2;  
			}  		
			j++;  //��һ���ַ�
		}
		else
		{
			x += 8;//������8 ��һ���ַ�������ռ8
			if(x > 120)  //���x����128���л�ҳ���Ӹ�ҳ�ĵ�һ����ʾ
			{
				x = 0;  
				y += 2;  
			}  		
			j++;  //��һ���ַ�
		}
	}
}
/*****************************************************************************
�������� : oled_pow
�������� : ����m^n
������� : m�������һ����   n���������Ĵη�
���ز��� : result��һ������n�η�
ʹ��˵�� : ��
*****************************************************************************/ 
uint32_t oled_pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}				  
/*****************************************************************************
�������� : OLED_ShowNum
�������� : ��ָ����λ�ã���ʾһ��ָ�����ȴ�С����
������� : x����ʼ��
					 y����ʼҳ
					 num������
					 len�����ֵĳ���
					 TextSize���ַ���С(1:6*8 ; 2:8*16)
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/ 
void OLED_ShowNum(uint8_t x,uint8_t y,int num,uint8_t len,uint8_t TextSize)
{         	
	uint8_t i,t,temp;  //�������
	uint8_t enshow=0;		//�������
	if(TextSize==8)
		i = 6;
	else
		i = 8;
	if(num<0)  //Ҫ��ʾ����С��0
	{
		num = -num;
		OLED_ShowChar(x,y,'-',TextSize);
		for(t=0;t<len;t++)
		{
			temp=(num/oled_pow(10,len-t-1))%10;//ȡ����������ÿ��λ���ɸߵ���
			if(enshow==0&&t<(len-1)) //enshow���Ƿ�Ϊ��һ������t<(len-1)���ж��Ƿ�Ϊ���һ����
			{
				if(temp==0) //�������Ϊ0 
				{
					OLED_ShowChar(x+i*(t+1),y,' ',TextSize);//��ʾ 0 ��x+(size2/2)*t���������Сƫ�Ƶ�������8��
					continue; //����ʣ����䣬�����ظ�ѭ���������ظ���ʾ��
				}else enshow=1; 
			}
			OLED_ShowChar(x+i*(t+1),y,temp+'0',TextSize); //��ʾһ��λ��x+(size2/2)*t���������Сƫ�Ƶ�������8��
		}
	}
	else  //Ҫ��ʾ��������0
	{
		for(t=0;t<len;t++)
		{
			temp=(num/oled_pow(10,len-t-1))%10;//ȡ����������ÿ��λ���ɸߵ���
			if(enshow==0&&t<(len-1)) //enshow���Ƿ�Ϊ��һ������t<(len-1)���ж��Ƿ�Ϊ���һ����
			{
				if(temp==0) //�������Ϊ0 
				{
					OLED_ShowChar(x+i*t,y,' ',TextSize);//��ʾ 0 ��x+(size2/2)*t���������Сƫ�Ƶ�������8��
					continue; //����ʣ����䣬�����ظ�ѭ���������ظ���ʾ��
				}else enshow=1; 
		 	}
			OLED_ShowChar(x+i*t,y,temp+'0',TextSize); //��ʾһ��λ��x+(size2/2)*t���������Сƫ�Ƶ�������8��
		}
	}
} 
/*****************************************************************************
�������� : OLED_ShowCHinese
�������� : ��ʾ����
������� : x����ʼ�У�һ����ռ16�� y����ʼҳ��һ����ռ��ҳ no����������к�
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/ 
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no)
{      			    
	uint8_t t,adder=0; //�������
	OLED_SetPos(x,y);	//�� x y ��ʼ���㣬�Ȼ���һҳ
    for(t=0;t<16;t++) //ѭ��16�Σ�����һҳ��16��
		{
				OLED_WR_Byte(Hzk[2*no][t],0);//��no������λ�õĵ�һҳ16�еĵ�
				adder+=1; //�����ַ��1
     }	
		OLED_SetPos(x,y+1); //���ڶ���
    for(t=0;t<16;t++)//ѭ��16�Σ����ڶ�ҳ��16��
			{	
				OLED_WR_Byte(Hzk[2*no+1][t],0);//��no������λ�õĵڶ�ҳ16�еĵ�
				adder+=1;//�����ַ��1
      }					
}

/*****************************************************************************
�������� : OLED_DrawBMP
�������� : ��ʾͼƬ
������� : x0����ʼ�е�ַ��0~127��
					 y0����ʼҳ��ַ��0~7��
					 x1����ֹ�е�ַ��1~128��
					 y1����ֹҳ��ַ��1~8��
				   BMP[]�����ͼƬ���������
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/ 
void OLED_DrawBMP(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t BMP[])
{
  uint16_t j=0;  //�������
  uint8_t x,y;   //�������
 
  if(y1%8==0)    //�ж���ֹҳ�Ƿ�Ϊ8��������
    y = y1/8;
  else
    y = y1/8 + 1;
  for(y=y0; y<y1; y++)   //����ʼҳ��ʼ��������ֹҳ
  {
    OLED_SetPos(x0,y);   //��ҳ����ʼ�п�ʼ��
    for(x=x0; x<x1; x++) //��x1 - x0 ��
    {
      OLED_WR_Byte(BMP[j++],0);//��ͼƬ�ĵ�
    }
  }
}
/*****************************************************************************
�������� : OLED_ShowInt
�������� : 
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/ 
//****************���������� ��ʾ6*8��8*16��5λ����   ��ʾ�����꣨x,y����yΪҳ��Χ0��7****************************
 
/*��
OLED_ShowInt(0,0,0,1);   //��(0,0)������ʾ6*8��"0"
OLED_ShowInt(5,4,12345,2);//��(5,4)������ʾ8*16��"12345"
*/
/*void OLED_ShowInt(uint8_t x, uint8_t y, int Data, uint8_t TextSize)
{
  uint8_t temp;
  OLED_SetPos(x,y);
  switch(TextSize)
  {
  case 1:
  {
    if(Data<0)
    {
      OLED_ShowChar(x,y,'-',1);
      x+=6;
      Data=-Data;
    }
    //������Ҫ��ʾ�����������һ����ʾ�����ĸ�λ
    //������������һ�����ţ�����ռ��һ����ʾλ
    OLED_ShowChar(x+30,y,' ',1);
 
    temp=Data/10000;
    OLED_ShowChar(x,y,(temp+'0'),1);
 
    Data%=10000;
    temp=Data/1000;
    OLED_ShowChar(x+6,y,(temp+'0'),1);
 
    Data%=1000;
    temp=Data/100;
    OLED_ShowChar(x+12,y,(temp+'0'),1);
 
    Data%=100;
    temp=Data/10;
    OLED_ShowChar(x+18,y,(temp+'0'),1);
 
    Data%=10;
    temp=Data;
    OLED_ShowChar(x+24,y,(temp+'0'),1);
  }
  break;
  case 2:
  {
    if(Data<0)
    {
      OLED_ShowChar(x,y,'-',2);
      x+=8;
      Data=-Data;
    }
    //������Ҫ��ʾ�����������һ����ʾ�����ĸ�λ
    //������������һ�����ţ�����ռ��һ����ʾλ
    OLED_ShowChar(x+40,y,' ',2);
 
    temp=Data/10000;
    OLED_ShowChar(x,y,(temp+'0'),2);
 
    Data%=10000;
    temp=Data/1000;
    OLED_ShowChar(x+8,y,(temp+'0'),2);
 
    Data%=1000;
    temp=Data/100;
    OLED_ShowChar(x+16,y,(temp+'0'),2);
 
    Data%=100;
    temp=Data/10;
    OLED_ShowChar(x+24,y,(temp+'0'),2);
 
    Data%=10;
    temp=Data;
    OLED_ShowChar(x+32,y,(temp+'0'),2);
  }
  break;
  }
}*/


/*void OLED_ShowData_uchar(uint8_t x, uint8_t y, uint8_t dat,uint8_t TextSize)		//��ʾ�޷���char����
{
	uint8_t display_tab[4];
	display_tab[0]=dat/100+'0';
	display_tab[1]=dat/10%10+'0';
	display_tab[2]=dat%10+'0';
	//display_tab[3]='\n';
	OLED_ShowStr(x,y,display_tab,TextSize);
}*/