#ifndef __USER_UART_H__
#define __USER_UART_H__


#ifdef USER_UART_GLOBALS
#define USER_UART_EXT
#else
#define USER_UART_EXT extern 
#endif

/*****************************************************************************
�������� : uart3_init
�������� : uart3��ʼ��
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void uart3_init();
/*****************************************************************************
�������� : Uart_PutChar
�������� : ���ڷ���
������� : dat:����������
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void Uart_PutChar(uint8_t dat);

#endif
