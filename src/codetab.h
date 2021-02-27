#ifndef _CODETAB_H  
#define _CODETAB_H  
  
#define uint8_t unsigned char
  
/***************************16*16 Chinese, common gnd - column style - reverse output*********/  
extern const uint8_t code Hzk[][32];
  
/************************************6*8************************************/  
extern const uint8_t code F6x8[][6];  
/****************************************8*16************************************/  
extern const uint8_t code F8X16[];  

extern const uint8_t code UI1[];//WIFI_NOT_CONNECTED UI   WIFI配置成功但未连上路由器

extern const uint8_t code UI2[];//WIFI_CONNECTED UI   WIFI配置成功且连上路由器

extern const uint8_t code UI3[];//WIFI_CONN_CLOUD UI   WIFI已经连接上云服务器

extern const uint8_t code UI4[];//WIFI_LOW_POWER UI   WIFI处于低功耗模式

extern const uint8_t code table[];
  
#endif  