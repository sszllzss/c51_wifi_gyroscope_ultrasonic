#ifndef __CONFIG_H__
#define __CONFIG_H__

//����ͷ�ļ�
#include "stc15wxxxx.h"
#include "typedef.h"

//#define MAIN_Fosc		22118400L	//������ʱ��
//#define MAIN_Fosc		12000000L	//������ʱ��
//#define MAIN_Fosc		11059200L	//������ʱ��
//#define MAIN_Fosc		 5529600L	//������ʱ��
#define MAIN_Fosc		24000000L	//������ʱ��
//#define MAIN_Fosc		27000000L	//������ʱ��

#define Main_Fosc_KHZ	(MAIN_Fosc / 1000)

#define DEBUG_PRINTF
//#define DEBUG_PRINTF_UART1_SW_P30_P31 //ʹ�ø�IO�������ܷ���
#define DEBUG_PRINTF_UART1_SW_P36_P37
//#define DEBUG_PRINTF_UART1_SW_P16_P17

#define USING_UART1//��������1
#define	COM_TX1_Lenth	128
#define	COM_RX1_Lenth	128
#define USING_UART2//��������2
#define	COM_TX2_Lenth	128
#define	COM_RX2_Lenth	128
//#define USING_UART3//��������3
//#define	COM_TX3_Lenth	128
//#define	COM_RX3_Lenth	128
//#define USING_UART4//��������4
//#define	COM_TX4_Lenth	128
//#define	COM_RX4_Lenth	128
#endif