#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#ifdef MAINWORK_GLOBALS
#define MAINWORK_EXT
#else
#define MAINWORK_EXT extern 
#endif

//==============================================================================
typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

//==============================================================================
#include 		<intrins.h>
#include    <math.h>

#include        "STC8.H"
#include        "user_uart.h"
#include 				"user_key.h"
#include 				"user_timer.h"
#include 				"user_I2C.h"
#include 				"user_OLED.h"
#include 				"user_SHT30.h"
#include 				"user_ADC.h"

//==============================================================================
//管脚定义
//==============================================================================
sbit K1 = P0^7;			//按键1

#define MAIN_Fosc		11059200UL	//定义主时钟

//**************I2C*************
#define	Speed		    100000UL	  //定义I2C时钟频率
#define MSSPEED     (MAIN_Fosc/Speed/2-4)/2

#define OLED_Address 0x78
#define SHT30_Address 0x88

//*************串口*************
#define	BaudRate		9600UL	//选择波特率
#define BRT         (65536-MAIN_Fosc/BaudRate/4)


//==============================================================================
//变量定义
//==============================================================================
typedef struct {
	
	signed int temper;                                        //温度
  uint8_t humidity;                                         //湿度
	uint32_t run_time;                                        //累计运行时间
	uint8_t Power;
	uint16_t SAMPLING;
	
} TYPE_BUFFER_S;

MAINWORK_EXT TYPE_BUFFER_S FlashBuffer;


#endif