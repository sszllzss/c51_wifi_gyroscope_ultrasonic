#ifndef __CONFIG_H__
#define __CONFIG_H__

//导入头文件
#include "stc15wxxxx.h"
#include "typedef.h"

//#define MAIN_Fosc		22118400L	//定义主时钟
//#define MAIN_Fosc		12000000L	//定义主时钟
//#define MAIN_Fosc		11059200L	//定义主时钟
//#define MAIN_Fosc		 5529600L	//定义主时钟
#define MAIN_Fosc		24000000L	//定义主时钟
//#define MAIN_Fosc		27000000L	//定义主时钟

#define Main_Fosc_KHZ	(MAIN_Fosc / 1000)

#define DEBUG_PRINTF
//#define DEBUG_PRINTF_UART1_SW_P30_P31 //使用改IO开启后不能仿真
#define DEBUG_PRINTF_UART1_SW_P36_P37
//#define DEBUG_PRINTF_UART1_SW_P16_P17

#define USING_UART1//开启串口1
#define	COM_TX1_Lenth	128
#define	COM_RX1_Lenth	128
#define USING_UART2//开启串口2
#define	COM_TX2_Lenth	128
#define	COM_RX2_Lenth	128
//#define USING_UART3//开启串口3
//#define	COM_TX3_Lenth	128
//#define	COM_RX3_Lenth	128
//#define USING_UART4//开启串口4
//#define	COM_TX4_Lenth	128
//#define	COM_RX4_Lenth	128
#endif