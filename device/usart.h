
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

#define	UART_ShiftRight	0		//ͬ����λ���
#define	UART_8bit_BRTx	(1<<6)	//8λ����,�ɱ䲨����
#define	UART_9bit		(2<<6)	//9λ����,�̶�������
#define	UART_9bit_BRTx	(3<<6)	//9λ����,�ɱ䲨����

#define	UART1_SW_P30_P31	0
#define	UART1_SW_P36_P37	(1<<6)
#define	UART1_SW_P16_P17	(2<<6)	//����ʹ���ڲ�ʱ��
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
	uint8_t	id;				//���ں�

	uint8_t	TX_read;		//���Ͷ�ָ��
	uint8_t	TX_write;		//����дָ��
	uint8_t	B_TX_busy;		//æ��־

	uint8_t 	RX_Cnt;			//�����ֽڼ���
	uint8_t	RX_TimeOut;		//���ճ�ʱ
	uint8_t	B_RX_OK;		//���տ����
} COMx_Define; 

typedef struct
{ 
	uint8_t	UART_Mode;			//ģʽ,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	uint8_t	UART_BRT_Use;		//ʹ�ò�����,   BRT_Timer1,BRT_Timer2,TimeOutSet3,TimeOutSet4//���������ѡ��ͬһ��ʱ��ʱֻ�ܲ����ʱ���ͳһ(�ǹ̶�������ģʽ��)
	uint32_t UART_BaudRate;		//������,       
	uint8_t	Morecommunicate;	//���ͨѶ����, ENABLE,DISABLE
	uint8_t	UART_RxEnable;		//�������,   ENABLE,DISABLE
	uint8_t	BaudRateDouble;		//�����ʼӱ�, ENABLE,DISABLE
	uint8_t	UART_Interrupt;		//�жϿ���,   ENABLE,DISABLE
	uint8_t	UART_Polity;		//���ȼ�,     PolityLow,PolityHigh
	uint8_t	UART_P_SW;			//�л��˿�,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17(����ʹ���ڲ�ʱ��)
	uint8_t	UART_RXD_TXD_Short;	//�ڲ���·RXD��TXD, ���м�, ENABLE,DISABLE

} COMx_InitDefine; 

uint8_t	USART_Configuration(uint8_t UARTx, COMx_InitDefine *COMx);
void UARTx_writebuff(enum USARTx com, uint8_t dat);	//д�뷢�ͻ��壬ָ��+1
void PrintString(enum USARTx com, uint8_t *puts);

#endif

