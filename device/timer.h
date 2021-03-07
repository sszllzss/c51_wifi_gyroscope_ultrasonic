
#ifndef	__TIMER_H
#define	__TIMER_H

#include	"config.h"


#define	TIM0						0
#define	TIM1						1
#define	TIM2						2
#define	TIM3						3
#define	TIM4						4

#define	TIM_16BitAutoReload			0
#define	TIM_16Bit					1
#define	TIM_8BitAutoReload			2
#define	TIM_16BitAutoReloadNoMask	3

#define	TIM_CLOCK_1T				0
#define	TIM_CLOCK_12T				1
#define	TIM_CLOCK_Ext				2

typedef void((*timer_interrupt_cb_t)(void));
typedef struct
{
	uint8_t	TIM_Mode;		//����ģʽ,  	TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	uint8_t	TIM_Polity;		//���ȼ�����	PolityHigh,PolityLow
	uint8_t	TIM_Interrupt;	//�ж�����		ENABLE,DISABLE
	uint8_t	TIM_ClkSource;	//ʱ��Դ		TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	uint8_t	TIM_ClkOut;		//�ɱ��ʱ�����,	ENABLE,DISABLE
	uint16_t	TIM_Value;		//װ�س�ֵ
	uint8_t	TIM_Run;		//�Ƿ�����		ENABLE,DISABLE
    timer_interrupt_cb_t TIM_Timerout_Callback;
} TIM_InitTypeDef;

uint8_t	Timer_Inilize(uint8_t TIM, TIM_InitTypeDef *TIMx);
uint8_t	Timer_Start(uint8_t TIM,uint8_t TIM_Run);
uint16_t Timer_Get_Value(uint8_t TIM);
#endif
