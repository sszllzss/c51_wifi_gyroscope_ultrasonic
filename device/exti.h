
#ifndef	__EXTI_H
#define	__EXTI_H

#include	"config.h"

#define	EXT_INT0			0	//初始化外中断0
#define	EXT_INT1			1	//初始化外中断1
#define	EXT_INT2			2	//初始化外中断2
#define	EXT_INT3			3	//初始化外中断3
#define	EXT_INT4			4	//初始化外中断4

#define	EXT_MODE_RiseFall	0	//上升沿/下降沿中断
#define	EXT_MODE_Fall		1	//下降沿中断
typedef void((*Ext_interrupt_cb_t)(uint8_t PCA_id,uint8_t value));
typedef struct
{
	uint8_t	EXTI_Mode;			//中断模式,  	EXT_MODE_RiseFall, EXT_MODE_Fall
	uint8_t	EXTI_Polity;		//优先级设置	PolityHigh,PolityLow
	uint8_t	EXTI_Interrupt;		//中断允许		ENABLE,DISABLE
    Ext_interrupt_cb_t interrupt_cb;
} EXTI_InitTypeDef;

uint8_t	Ext_Inilize(uint8_t EXT, EXTI_InitTypeDef *INTx);

#endif
