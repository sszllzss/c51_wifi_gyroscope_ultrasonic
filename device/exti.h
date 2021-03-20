
#ifndef	__EXTI_H
#define	__EXTI_H

#include	"config.h"

#define	EXT_INT0			0	//��ʼ�����ж�0 P32
#define	EXT_INT1			1	//��ʼ�����ж�1 P33
#define	EXT_INT2			2	//��ʼ�����ж�2 P36
#define	EXT_INT3			3	//��ʼ�����ж�3 P37
#define	EXT_INT4			4	//��ʼ�����ж�4 P30

#define	EXT_MODE_RiseFall	0	//������/�½����ж�
#define	EXT_MODE_Fall		1	//�½����ж�
typedef void((*Ext_interrupt_cb_t)(uint8_t EXT,uint8_t value));
typedef struct
{
	uint8_t	EXTI_Mode;			//�ж�ģʽ,  	EXT_MODE_RiseFall, EXT_MODE_Fall
	uint8_t	EXTI_Polity;		//���ȼ�����	PolityHigh,PolityLow
	uint8_t	EXTI_Interrupt;		//�ж�����		ENABLE,DISABLE
    Ext_interrupt_cb_t interrupt_cb;
} EXTI_InitTypeDef;

uint8_t	Ext_Inilize(uint8_t EXT, EXTI_InitTypeDef *INTx);

#endif
