
#ifndef __USART_H
#define __USART_H	 

#include	"config.h"


enum USARTx
{
#ifdef USING_UART1
	USART1,
#endif
#ifdef USING_UART2
	USART2,
#endif
#ifdef USING_UART3
	USART3
#endif
#ifdef USING_UART4
	USART4
#endif
};

#define	UART_ShiftRight	0		//同步移位输出
#define	UART_8bit_BRTx	(1<<6)	//8位数据,可变波特率
#define	UART_9bit		(2<<6)	//9位数据,固定波特率
#define	UART_9bit_BRTx	(3<<6)	//9位数据,可变波特率

#define	UART1_SW_P30_P31	0
#define	UART1_SW_P36_P37	(1<<6)
#define	UART1_SW_P16_P17	(2<<6)	//必须使用内部时钟
#define	UART2_SW_P10_P11	0
#define	UART2_SW_P46_P47	1
#define	UART3_SW_P00_P01	0
#define	UART3_SW_P56_P51	1
#define	UART4_SW_P02_P03	0
#define	UART4_SW_P52_P53	1




#define	TimeOutSet1		5
#define	TimeOutSet2		5
#define	TimeOutSet3		5
#define	TimeOutSet4		5

#define	BRT_Timer1	1//USART1 
#define	BRT_Timer2	2//USART2 USART3 USART4
#define	BRT_Timer3	3//USART3
#define	BRT_Timer4	4//USART4

typedef struct
{ 
	uint8_t	id;				//串口号

	uint8_t	TX_read;		//发送读指针
	uint8_t	TX_write;		//发送写指针
	uint8_t	B_TX_busy;		//忙标志

	uint8_t 	RX_Cnt;			//接收字节计数
	uint8_t	RX_TimeOut;		//接收超时
	uint8_t	B_RX_OK;		//接收块完成
} COMx_Define; 

typedef struct
{ 
	uint8_t	UART_Mode;			//模式,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	uint8_t	UART_BRT_Use;		//使用波特率,   BRT_Timer1,BRT_Timer2,TimeOutSet3,TimeOutSet4//当多个串口选择同一定时器时只能波特率保存统一(非固定波特率模式下)
	uint32_t UART_BaudRate;		//波特率,       
	uint8_t	Morecommunicate;	//多机通讯允许, ENABLE,DISABLE
	uint8_t	UART_RxEnable;		//允许接收,   ENABLE,DISABLE
	uint8_t	BaudRateDouble;		//波特率加倍, ENABLE,DISABLE
	uint8_t	UART_Interrupt;		//中断控制,   ENABLE,DISABLE
	uint8_t	UART_Polity;		//优先级,     PolityLow,PolityHigh
	uint8_t	UART_P_SW;			//切换端口,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17(必须使用内部时钟)
	uint8_t	UART_RXD_TXD_Short;	//内部短路RXD与TXD, 做中继, ENABLE,DISABLE

} COMx_InitDefine; 

uint8_t	USART_Configuration(uint8_t UARTx, COMx_InitDefine *COMx);
void UARTx_writebuff(enum USARTx com, uint8_t dat);	//写入发送缓冲，指针+1
void PrintString(enum USARTx com, uint8_t *puts);

#endif

