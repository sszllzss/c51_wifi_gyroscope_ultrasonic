#include	"timer.h"

static timer_interrupt_cb_t timer0_int_cb = NULL;
static timer_interrupt_cb_t timer1_int_cb = NULL;
static timer_interrupt_cb_t timer2_int_cb = NULL;
static timer_interrupt_cb_t timer3_int_cb = NULL;
static timer_interrupt_cb_t timer4_int_cb = NULL;
/********************* Timer0中断函数************************/
void timer0_int (void) interrupt TIMER0_VECTOR
{

    if(timer0_int_cb)
        timer0_int_cb();
   
}

/********************* Timer1中断函数************************/
void timer1_int (void) interrupt TIMER1_VECTOR
{
    if(timer1_int_cb)
        timer1_int_cb();
}

/********************* Timer2中断函数************************/
void timer2_int (void) interrupt TIMER2_VECTOR
{
    if(timer2_int_cb)
        timer2_int_cb();
}

/********************* Timer3中断函数************************/
void timer3_int (void) interrupt TIMER3_VECTOR
{
    if(timer3_int_cb)
        timer3_int_cb();
}

/********************* Timer4中断函数************************/
void timer4_int (void) interrupt TIMER4_VECTOR
{
    if(timer4_int_cb)
        timer4_int_cb();
}


//========================================================================
// 函数: u8	Timer_Inilize(uint8_t TIM, TIM_InitTypeDef *TIMx)
// 描述: 定时器初始化程序.
// 参数: TIMx: 结构参数,请参考timer.h里的定义.
// 返回: 成功返回0, 空操作返回1,错误返回2.
//========================================================================
uint8_t	Timer_Inilize(uint8_t TIM, TIM_InitTypeDef *TIMx)
{
	if(TIM > TIM4)	return 1;	//空操作

	if(TIM == TIM0)
	{
		TR0 = 0;		//停止计数
		if(TIMx->TIM_Interrupt == ENABLE){timer0_int_cb=TIMx->TIM_Timerout_Callback;ET0 = 1;}//允许中断
		else									ET0 = 0;	//禁止中断
		if(TIMx->TIM_Polity == PolityHigh)		PT0 = 1;	//高优先级中断
		else									PT0 = 0;	//低优先级中断
		if(TIMx->TIM_Mode >  TIM_16BitAutoReloadNoMask)	return 2;	//错误
		TMOD = (TMOD & ~0x03) | TIMx->TIM_Mode;	//工作模式,0: 16位自动重装, 1: 16位定时/计数, 2: 8位自动重装, 3: 16位自动重装, 不可屏蔽中断
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~0x80;	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x80;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x04;	//对外计数或分频
		else										TMOD &= ~0x04;	//定时
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x01;	//输出时钟
		else							INT_CLKO &= ~0x01;	//不输出时钟
		
		TH0 = (u8)(TIMx->TIM_Value >> 8);
		TL0 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR0 = 1;	//开始运行
		return	0;		//成功
	}
	else if(TIM == TIM1)
	{
		TR1 = 0;		//停止计数
		if(TIMx->TIM_Interrupt == ENABLE){timer1_int_cb=TIMx->TIM_Timerout_Callback;ET1 = 1;}//允许中断
		else									ET1 = 0;	//禁止中断
		if(TIMx->TIM_Polity == PolityHigh)		PT1 = 1;	//高优先级中断
		else									PT1 = 0;	//低优先级中断
		if(TIMx->TIM_Mode >= TIM_16BitAutoReloadNoMask)	return 2;	//错误
		TMOD = (TMOD & ~0x30) | TIMx->TIM_Mode;	//工作模式,0: 16位自动重装, 1: 16位定时/计数, 2: 8位自动重装
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~0x40;	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x40;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x40;	//对外计数或分频
		else										TMOD &= ~0x40;	//定时
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x02;	//输出时钟
		else							INT_CLKO &= ~0x02;	//不输出时钟
		
		TH1 = (u8)(TIMx->TIM_Value >> 8);
		TL1 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR1 = 1;	//开始运行
		return	0;		//成功
	}
	else if(TIM == TIM2)		//TIM2,固定为16位自动重装, 中断无优先级
	{
		AUXR &= ~(1<<4);	//停止计数
		if(TIMx->TIM_Interrupt == ENABLE){timer2_int_cb=TIMx->TIM_Timerout_Callback;IE2  |=  (1<<2);}//允许中断
		else										IE2  &= ~(1<<2);	//禁止中断
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~(1<<2);	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  (1<<2);	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	AUXR |=  (1<<3);	//对外计数或分频
		else										AUXR &= ~(1<<3);	//定时
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x04;	//输出时钟
		else							INT_CLKO &= ~0x04;	//不输出时钟

		T2H = (u8)(TIMx->TIM_Value >> 8);
		T2L = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	AUXR |=  (1<<4);	//开始运行
		return	0;		//成功
	}
    else if(TIM == TIM3)		//TIM3,固定为16位自动重装, 中断无优先级
	{
		T3T4M &= ~(1<<3);	//停止计数
		if(TIMx->TIM_Interrupt == ENABLE){timer3_int_cb=TIMx->TIM_Timerout_Callback;IE2  |=  (1<<5);}//允许中断
		else										IE2  &= ~(1<<5);	//禁止中断
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	T3T4M &= ~(1<<1);	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		T3T4M |=  (1<<1);	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	T3T4M |=  (1<<2);	//对外计数或分频
		else										T3T4M &= ~(1<<2);	//定时
		if(TIMx->TIM_ClkOut == ENABLE)	T3T4M |=  0x01;	//输出时钟
		else							T3T4M &= ~0x01;	//不输出时钟

		T3H = (u8)(TIMx->TIM_Value >> 8);
		T3L = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	T3T4M |=  (1<<3);	//开始运行
		return	0;		//成功
	}
    else if(TIM == TIM4)		//TIM4,固定为16位自动重装, 中断无优先级
	{
		T3T4M &= ~(1<<7);	//停止计数
		if(TIMx->TIM_Interrupt == ENABLE){timer4_int_cb=TIMx->TIM_Timerout_Callback;IE2  |=  (1<<6);}//允许中断
		else										IE2  &= ~(1<<6);	//禁止中断
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	T3T4M &= ~(1<<5);	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		T3T4M |=  (1<<5);	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	T3T4M |=  (1<<6);	//对外计数或分频
		else										T3T4M &= ~(1<<6);	//定时
		if(TIMx->TIM_ClkOut == ENABLE)	T3T4M |=  (1<<4);	//输出时钟
		else							T3T4M &= ~(1<<4);	//不输出时钟

		T4H = (u8)(TIMx->TIM_Value >> 8);
		T4L = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	T3T4M |=  (1<<7);	//开始运行
		return	0;		//成功
	}
	return 2;	//错误
}
uint8_t	Timer_Start(uint8_t TIM, uint8_t TIM_Run)
{
    if(TIM > TIM4)	return 1;	//空操作

	if(TIM == TIM0)
	{
		if(TIM_Run == ENABLE)	TR0 = 1;	//开始运行
        else TR0 = 0;
		return	0;		//成功
	}
	else if(TIM == TIM1)
	{
		if(TIM_Run == ENABLE)	TR1 = 1;	//开始运行
        else TR1 = 0;	
		return	0;		//成功
	}
	else if(TIM == TIM2)		//TIM2,固定为16位自动重装, 中断无优先级
	{
		if(TIM_Run == ENABLE)	AUXR |=  (1<<4);	//开始运行
        else AUXR &=  ~(1<<4);	
		return	0;		//成功
	}
    else if(TIM == TIM3)		//TIM3,固定为16位自动重装, 中断无优先级
	{
		if(TIM_Run == ENABLE)	T3T4M |=  (1<<3);	//开始运行
        else T3T4M &=  ~(1<<3);	
		return	0;		//成功
	}
    else if(TIM == TIM4)		//TIM4,固定为16位自动重装, 中断无优先级
	{
		if(TIM_Run == ENABLE)	T3T4M |=  (1<<7);	//开始运行
        else T3T4M &=  ~(1<<7);	
		return	0;		//成功
	}
	return 2;	//错误
}
uint16_t Timer_Get_Value(uint8_t TIM)
{
    uint16_t rec = 0;
    if(TIM > TIM4)	return 0;	//空操作
    
	if(TIM == TIM0)
	{
        rec = TH0;
        rec  = rec<<8;
        rec |= TL0;
		return	rec;
	}
	else if(TIM == TIM1)
	{
        rec = TH1;
        rec  = rec<<8;
        rec |= TL1;
		return	rec;
	}
	else if(TIM == TIM2)		//TIM2,固定为16位自动重装, 中断无优先级
	{
        rec = T2H;
        rec  = rec<<8;
        rec |= T2L;
		return	rec;
	}
    else if(TIM == TIM3)		//TIM3,固定为16位自动重装, 中断无优先级
	{
        rec = T3H;
        rec  = rec<<8;
        rec |= T3L;
		return	rec;
	}
    else if(TIM == TIM4)		//TIM4,固定为16位自动重装, 中断无优先级
	{
        rec = T4H;
        rec  = rec<<8;
        rec |= T4L;
		return	rec;
	}
	return 0;	//错误
}
