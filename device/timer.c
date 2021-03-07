#include	"timer.h"

static timer_interrupt_cb_t timer0_int_cb = NULL;
static timer_interrupt_cb_t timer1_int_cb = NULL;
static timer_interrupt_cb_t timer2_int_cb = NULL;
static timer_interrupt_cb_t timer3_int_cb = NULL;
static timer_interrupt_cb_t timer4_int_cb = NULL;
/********************* Timer0�жϺ���************************/
void timer0_int (void) interrupt TIMER0_VECTOR
{

    if(timer0_int_cb)
        timer0_int_cb();
   
}

/********************* Timer1�жϺ���************************/
void timer1_int (void) interrupt TIMER1_VECTOR
{
    if(timer1_int_cb)
        timer1_int_cb();
}

/********************* Timer2�жϺ���************************/
void timer2_int (void) interrupt TIMER2_VECTOR
{
    if(timer2_int_cb)
        timer2_int_cb();
}

/********************* Timer3�жϺ���************************/
void timer3_int (void) interrupt TIMER3_VECTOR
{
    if(timer3_int_cb)
        timer3_int_cb();
}

/********************* Timer4�жϺ���************************/
void timer4_int (void) interrupt TIMER4_VECTOR
{
    if(timer4_int_cb)
        timer4_int_cb();
}


//========================================================================
// ����: u8	Timer_Inilize(uint8_t TIM, TIM_InitTypeDef *TIMx)
// ����: ��ʱ����ʼ������.
// ����: TIMx: �ṹ����,��ο�timer.h��Ķ���.
// ����: �ɹ�����0, �ղ�������1,���󷵻�2.
//========================================================================
uint8_t	Timer_Inilize(uint8_t TIM, TIM_InitTypeDef *TIMx)
{
	if(TIM > TIM4)	return 1;	//�ղ���

	if(TIM == TIM0)
	{
		TR0 = 0;		//ֹͣ����
		if(TIMx->TIM_Interrupt == ENABLE){timer0_int_cb=TIMx->TIM_Timerout_Callback;ET0 = 1;}//�����ж�
		else									ET0 = 0;	//��ֹ�ж�
		if(TIMx->TIM_Polity == PolityHigh)		PT0 = 1;	//�����ȼ��ж�
		else									PT0 = 0;	//�����ȼ��ж�
		if(TIMx->TIM_Mode >  TIM_16BitAutoReloadNoMask)	return 2;	//����
		TMOD = (TMOD & ~0x03) | TIMx->TIM_Mode;	//����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ, 3: 16λ�Զ���װ, ���������ж�
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~0x80;	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x80;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x04;	//����������Ƶ
		else										TMOD &= ~0x04;	//��ʱ
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x01;	//���ʱ��
		else							INT_CLKO &= ~0x01;	//�����ʱ��
		
		TH0 = (u8)(TIMx->TIM_Value >> 8);
		TL0 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR0 = 1;	//��ʼ����
		return	0;		//�ɹ�
	}
	else if(TIM == TIM1)
	{
		TR1 = 0;		//ֹͣ����
		if(TIMx->TIM_Interrupt == ENABLE){timer1_int_cb=TIMx->TIM_Timerout_Callback;ET1 = 1;}//�����ж�
		else									ET1 = 0;	//��ֹ�ж�
		if(TIMx->TIM_Polity == PolityHigh)		PT1 = 1;	//�����ȼ��ж�
		else									PT1 = 0;	//�����ȼ��ж�
		if(TIMx->TIM_Mode >= TIM_16BitAutoReloadNoMask)	return 2;	//����
		TMOD = (TMOD & ~0x30) | TIMx->TIM_Mode;	//����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~0x40;	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x40;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x40;	//����������Ƶ
		else										TMOD &= ~0x40;	//��ʱ
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x02;	//���ʱ��
		else							INT_CLKO &= ~0x02;	//�����ʱ��
		
		TH1 = (u8)(TIMx->TIM_Value >> 8);
		TL1 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR1 = 1;	//��ʼ����
		return	0;		//�ɹ�
	}
	else if(TIM == TIM2)		//TIM2,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		AUXR &= ~(1<<4);	//ֹͣ����
		if(TIMx->TIM_Interrupt == ENABLE){timer2_int_cb=TIMx->TIM_Timerout_Callback;IE2  |=  (1<<2);}//�����ж�
		else										IE2  &= ~(1<<2);	//��ֹ�ж�
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~(1<<2);	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  (1<<2);	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	AUXR |=  (1<<3);	//����������Ƶ
		else										AUXR &= ~(1<<3);	//��ʱ
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x04;	//���ʱ��
		else							INT_CLKO &= ~0x04;	//�����ʱ��

		T2H = (u8)(TIMx->TIM_Value >> 8);
		T2L = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	AUXR |=  (1<<4);	//��ʼ����
		return	0;		//�ɹ�
	}
    else if(TIM == TIM3)		//TIM3,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		T3T4M &= ~(1<<3);	//ֹͣ����
		if(TIMx->TIM_Interrupt == ENABLE){timer3_int_cb=TIMx->TIM_Timerout_Callback;IE2  |=  (1<<5);}//�����ж�
		else										IE2  &= ~(1<<5);	//��ֹ�ж�
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	T3T4M &= ~(1<<1);	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		T3T4M |=  (1<<1);	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	T3T4M |=  (1<<2);	//����������Ƶ
		else										T3T4M &= ~(1<<2);	//��ʱ
		if(TIMx->TIM_ClkOut == ENABLE)	T3T4M |=  0x01;	//���ʱ��
		else							T3T4M &= ~0x01;	//�����ʱ��

		T3H = (u8)(TIMx->TIM_Value >> 8);
		T3L = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	T3T4M |=  (1<<3);	//��ʼ����
		return	0;		//�ɹ�
	}
    else if(TIM == TIM4)		//TIM4,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		T3T4M &= ~(1<<7);	//ֹͣ����
		if(TIMx->TIM_Interrupt == ENABLE){timer4_int_cb=TIMx->TIM_Timerout_Callback;IE2  |=  (1<<6);}//�����ж�
		else										IE2  &= ~(1<<6);	//��ֹ�ж�
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	T3T4M &= ~(1<<5);	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		T3T4M |=  (1<<5);	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	T3T4M |=  (1<<6);	//����������Ƶ
		else										T3T4M &= ~(1<<6);	//��ʱ
		if(TIMx->TIM_ClkOut == ENABLE)	T3T4M |=  (1<<4);	//���ʱ��
		else							T3T4M &= ~(1<<4);	//�����ʱ��

		T4H = (u8)(TIMx->TIM_Value >> 8);
		T4L = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	T3T4M |=  (1<<7);	//��ʼ����
		return	0;		//�ɹ�
	}
	return 2;	//����
}
uint8_t	Timer_Start(uint8_t TIM, uint8_t TIM_Run)
{
    if(TIM > TIM4)	return 1;	//�ղ���

	if(TIM == TIM0)
	{
		if(TIM_Run == ENABLE)	TR0 = 1;	//��ʼ����
        else TR0 = 0;
		return	0;		//�ɹ�
	}
	else if(TIM == TIM1)
	{
		if(TIM_Run == ENABLE)	TR1 = 1;	//��ʼ����
        else TR1 = 0;	
		return	0;		//�ɹ�
	}
	else if(TIM == TIM2)		//TIM2,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		if(TIM_Run == ENABLE)	AUXR |=  (1<<4);	//��ʼ����
        else AUXR &=  ~(1<<4);	
		return	0;		//�ɹ�
	}
    else if(TIM == TIM3)		//TIM3,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		if(TIM_Run == ENABLE)	T3T4M |=  (1<<3);	//��ʼ����
        else T3T4M &=  ~(1<<3);	
		return	0;		//�ɹ�
	}
    else if(TIM == TIM4)		//TIM4,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		if(TIM_Run == ENABLE)	T3T4M |=  (1<<7);	//��ʼ����
        else T3T4M &=  ~(1<<7);	
		return	0;		//�ɹ�
	}
	return 2;	//����
}
uint16_t Timer_Get_Value(uint8_t TIM)
{
    uint16_t rec = 0;
    if(TIM > TIM4)	return 0;	//�ղ���
    
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
	else if(TIM == TIM2)		//TIM2,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
        rec = T2H;
        rec  = rec<<8;
        rec |= T2L;
		return	rec;
	}
    else if(TIM == TIM3)		//TIM3,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
        rec = T3H;
        rec  = rec<<8;
        rec |= T3L;
		return	rec;
	}
    else if(TIM == TIM4)		//TIM4,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
        rec = T4H;
        rec  = rec<<8;
        rec |= T4L;
		return	rec;
	}
	return 0;	//����
}
