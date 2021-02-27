#ifndef __USER_ADC_H__
#define __USER_ADC_H__

#ifdef USER_ADC_GLOBALS
#define USER_ADC_EXT
#else
#define USER_ADC_EXT extern 
#endif




//void ADC_init();

void Get_Voltage();

#endif

