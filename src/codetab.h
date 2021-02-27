#ifndef _CODETAB_H  
#define _CODETAB_H  
  
#define uint8_t unsigned char
  
/***************************16*16 Chinese, common gnd - column style - reverse output*********/  
extern const uint8_t code Hzk[][32];
  
/************************************6*8************************************/  
extern const uint8_t code F6x8[][6];  
/****************************************8*16************************************/  
extern const uint8_t code F8X16[];  

extern const uint8_t code UI1[];//WIFI_NOT_CONNECTED UI   WIFI���óɹ���δ����·����

extern const uint8_t code UI2[];//WIFI_CONNECTED UI   WIFI���óɹ�������·����

extern const uint8_t code UI3[];//WIFI_CONN_CLOUD UI   WIFI�Ѿ��������Ʒ�����

extern const uint8_t code UI4[];//WIFI_LOW_POWER UI   WIFI���ڵ͹���ģʽ

extern const uint8_t code table[];
  
#endif  