#ifndef __USER_KEY_H__
#define __USER_KEY_H__

#ifdef USER_KEY_GLOBALS
#define USER_KEY_EXT
#else
#define USER_KEY_EXT extern 
#endif

//==============================================================================
//常量定义
//==============================================================================
#define MAX_KEY         1
#define PRESS_KEY1      0x01
//#define PRESS_KEY2      0x02
//#define PRESS_KEY3      0x04
//#define PRESS_KEY4      0x08

#define KEY_NO          0x00
#define KEY_DOWN        0x10  	
#define KEY_UP          0x20   
#define KEY_LONG        0x40
//#define KEY_CLICK       0x80

#define TIME_PRESS_LONG         (3 * 100)																			//(10ms)
#define TIME_PRESS_SHORT        5																							//5*10ms

typedef void (* KEY_HANDLE)(void);
typedef struct
{
  uint8_t Status;
  uint32_t Press_Time;
  KEY_HANDLE Short_Press_Handle;
  KEY_HANDLE Long_Press_Handle;
} KEY_STATE_T;

/*****************************************************************************
函数名称 : key_init
功能描述 : KEY初始化
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void key_init(void);

/*****************************************************************************
函数名称 : key_scan
功能描述 : 扫描按键
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void key_scan(void);

#endif

