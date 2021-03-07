
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
	uint8_t	TIM_Mode;		//工作模式,  	TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	uint8_t	TIM_Polity;		//优先级设置	PolityHigh,PolityLow
	uint8_t	TIM_Interrupt;	//中断允许		ENABLE,DISABLE
	uint8_t	TIM_ClkSource;	//时钟源		TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	uint8_t	TIM_ClkOut;		//可编程时钟输出,	ENABLE,DISABLE
	uint16_t	TIM_Value;		//装载初值
	uint8_t	TIM_Run;		//是否运行		ENABLE,DISABLE
    timer_interrupt_cb_t TIM_Timerout_Callback;
} TIM_InitTypeDef;

uint8_t	Timer_Inilize(uint8_t TIM, TIM_InitTypeDef *TIMx);
uint8_t	Timer_Start(uint8_t TIM,uint8_t TIM_Run);
uint16_t Timer_Get_Value(uint8_t TIM);
#endif
