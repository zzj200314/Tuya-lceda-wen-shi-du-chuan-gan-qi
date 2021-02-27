#ifndef __USER_TIMER_H__
#define __USER_TIMER_H_

#ifdef USER_TIMER_GLOBALS
#define USER_TIMER_EXT
#else
#define USER_TIMER_KEY extern 
#endif


/*****************************************************************************
函数名称 : timer0_init
功能描述 : timer0初始化
输入参数 : 无
返回参数 : 无
使用说明 : 10毫秒@11.0592MHz
*****************************************************************************/
void timer0_init(void);

/*****************************************************************************
函数名称 : get_count_value
功能描述 : 获取Timer0计数值
输入参数 : 无
返回参数 : Timer_Value
使用说明 : 无
*****************************************************************************/
unsigned long get_count_value(void);



#endif