
#ifndef	__PCA_H
#define	__PCA_H

#include	"config.h"

/***************************用户宏定义*******************************************************/
#define		PWM0_DUTY		4000		//定义PWM的周期，数值为PCA所选择的时钟脉冲个数。
#define		PWM0_HIGH_MIN	80			//限制PWM输出的最小占空比。
#define		PWM0_HIGH_MAX	(PWM0_DUTY - PWM0_HIGH_MIN)		//限制PWM输出的最大占空比。

#define		PWM1_DUTY		3000		//定义PWM的周期，数值为PCA所选择的时钟脉冲个数。
#define		PWM1_HIGH_MIN	80			//限制PWM输出的最小占空比。
#define		PWM1_HIGH_MAX	(PWM1_DUTY - PWM1_HIGH_MIN)		//限制PWM输出的最大占空比。

#define		PWM2_DUTY		2000		//定义PWM的周期，数值为PCA所选择的时钟脉冲个数。
#define		PWM2_HIGH_MIN	80			//限制PWM输出的最小占空比。
#define		PWM2_HIGH_MAX	(PWM2_DUTY - PWM2_HIGH_MIN)		//限制PWM输出的最大占空比。

/********************************************************************************************/




#define	PCA0 0
#define	PCA1 1
#define	PCA2 2
#define	PCA_Counter 3

#define	PCA_P12_P11_P10_P37	(0<<4)
#define	PCA_P34_P35_P36_P37	(1<<4)
#define	PCA_P24_P25_P26_P27	(2<<4)
#define	PCA_Mode_PWM				0x42	//B0100_0010
#define	PCA_Mode_Capture			0
#define	PCA_Mode_SoftTimer			0x48	//B0100_1000
#define	PCA_Mode_HighPulseOutput	0x4c	//B0100_1100
#define	PCA_Clock_1T	(4<<1)
#define	PCA_Clock_2T	(1<<1)
#define	PCA_Clock_4T	(5<<1)
#define	PCA_Clock_6T	(6<<1)
#define	PCA_Clock_8T	(7<<1)
#define	PCA_Clock_12T	(0<<1)
#define	PCA_Clock_Timer0_OF	(2<<1)
#define	PCA_Clock_ECI	(3<<1)
#define	PCA_Rise_Active	(1<<5)
#define	PCA_Fall_Active	(1<<4)
#define	PCA_PWM_8bit	(0<<6)
#define	PCA_PWM_7bit	(1<<6)
#define	PCA_PWM_6bit	(2<<6)


typedef struct
{
	uint8_t	PCA_IoUse;	//PCA_P12_P11_P10_P37, PCA_P34_P35_P36_P37, PCA_P24_P25_P26_P27
	uint8_t	PCA_Clock;	//PCA_Clock_1T, PCA_Clock_2T, PCA_Clock_4T, PCA_Clock_6T, PCA_Clock_8T, PCA_Clock_12T, PCA_Clock_Timer0_OF, PCA_Clock_ECI
	uint8_t	PCA_Mode;	//PCA_Mode_PWM, PCA_Mode_Capture, PCA_Mode_SoftTimer, PCA_Mode_HighPulseOutput
	uint8_t	PCA_PWM_Wide;	//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit
	uint8_t	PCA_Interrupt_Mode;	//PCA_Rise_Active, PCA_Fall_Active, ENABLE, DISABLE
	uint8_t	PCA_Polity;	//优先级设置	PolityHigh,PolityLow
	uint16_t PCA_Value; 
} PCA_InitTypeDef;

#ifdef USING_PCA0

#ifdef USING_PCA0
extern bit		B_Capture0;
extern uint8_t		PCA0_mode;
extern uint16_t		CCAP0_tmp,PCA_Timer0;
extern uint16_t	PWM0_low;	//PWM输出低电平的PCA时钟脉冲个数, 用户层不可见。
#endif
#ifdef USING_PCA1
extern bit		B_Capture1;
extern uint8_t		PCA1_mode;
extern uint16_t		CCAP1_tmp,PCA_Timer1;
extern uint16_t	PWM1_low;	//PWM输出低电平的PCA时钟脉冲个数, 用户层不可见。
#endif
#ifdef USING_PCA2
extern bit		B_Capture2;
extern uint8_t		PCA2_mode;
extern uint16_t		CCAP2_tmp,PCA_Timer2;
extern uint16_t	PWM2_low;	//PWM输出低电平的PCA时钟脉冲个数, 用户层不可见。
#endif


void PCA_Init(uint8_t PCA_id, PCA_InitTypeDef *PCAx);
void UpdatePwm(uint8_t PCA_id, uint8_t pwm_value);
void PWMn_Update(uint8_t PCA_id, uint16_t high);

#endif

