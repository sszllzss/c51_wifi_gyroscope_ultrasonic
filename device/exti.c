

#include "gpio.h"
#include "exti.h"
static Ext_interrupt_cb_t data EXT0_interrupt_cb = NULL;
static Ext_interrupt_cb_t data EXT1_interrupt_cb = NULL;
static Ext_interrupt_cb_t data EXT2_interrupt_cb = NULL;
static Ext_interrupt_cb_t data EXT3_interrupt_cb = NULL;
static Ext_interrupt_cb_t data EXT4_interrupt_cb = NULL;

/********************* INT0�жϺ��� *************************/
void Ext_INT0 (void) interrupt INT0_VECTOR		//���ж�ʱ�Ѿ������־
{
	if(EXT0_interrupt_cb)
        EXT0_interrupt_cb(EXT_INT0,P32);
}

/********************* INT1�жϺ��� *************************/
void Ext_INT1 (void) interrupt INT1_VECTOR		//���ж�ʱ�Ѿ������־
{
	if(EXT1_interrupt_cb)
        EXT1_interrupt_cb(EXT_INT1,P33);
}

/********************* INT2�жϺ��� *************************/
void Ext_INT2 (void) interrupt INT2_VECTOR	//
{
	if(EXT2_interrupt_cb)
        EXT2_interrupt_cb(EXT_INT2,P36);
}

/********************* INT3�жϺ��� *************************/
void Ext_INT3 (void) interrupt INT3_VECTOR
{
	if(EXT3_interrupt_cb)
        EXT3_interrupt_cb(EXT_INT3,P37);
}

/********************* INT4�жϺ��� *************************/
void Ext_INT4 (void) interrupt INT4_VECTOR
{
	if(EXT4_interrupt_cb)
        EXT4_interrupt_cb(EXT_INT4,P30);
}

//========================================================================
// ����: uint8_t	Ext_Inilize(uint8_t EXT, EXTI_InitTypeDef *INTx)
// ����: �ⲿ�жϳ�ʼ������.
// ����: INTx: �ṹ����,��ο�Exti.h��Ķ���.
// ����: �ɹ�����0, �ղ�������1,���󷵻�2.
//========================================================================
uint8_t	Ext_Inilize(uint8_t EXT, EXTI_InitTypeDef *INTx)
{
	if(EXT >  EXT_INT4)	return 1;	//�ղ���
	
	if(EXT == EXT_INT0)	//���ж�0
	{
		if(INTx->EXTI_Interrupt == ENABLE)		EX0 = 1;	//�����ж�
		else									EX0 = 0;	//��ֹ�ж�
		if(INTx->EXTI_Polity == PolityHigh)		PX0 = 1;	//�����ȼ��ж�
		else									PX0 = 0;	//�����ȼ��ж�
		if(INTx->EXTI_Mode == EXT_MODE_Fall)	IT0 = 1;	//�½����ж�
		else									IT0 = 0;	//����,�½����ж�
        if(INTx->EXTI_Interrupt == ENABLE)		EXT0_interrupt_cb = INTx->interrupt_cb;	//�ص�
        
        GPIO_Inilize(GPIO_P3,GPIO_Pin_2, GPIO_HighZ);
		return	0;		//�ɹ�
	}

	if(EXT == EXT_INT1)	//���ж�1
	{
		if(INTx->EXTI_Interrupt == ENABLE)		EX1 = 1;	//�����ж�
		else									EX1 = 0;	//��ֹ�ж�
		if(INTx->EXTI_Polity == PolityHigh)		PX1 = 1;	//�����ȼ��ж�
		else									PX1 = 0;	//�����ȼ��ж�
		if(INTx->EXTI_Mode == EXT_MODE_Fall)	IT1 = 1;	//�½����ж�
		else									IT1 = 0;	//����,�½����ж�
        if(INTx->EXTI_Interrupt == ENABLE)		EXT1_interrupt_cb = INTx->interrupt_cb;	//�ص�
        GPIO_Inilize(GPIO_P3,GPIO_Pin_3, GPIO_HighZ);
		return	0;		//�ɹ�
	}

	if(EXT == EXT_INT2)		//���ж�2, �̶�Ϊ�½��ص����ȼ��ж�
	{
		if(INTx->EXTI_Interrupt == ENABLE)	INT_CLKO |=  (1 << 4);	//�����ж�	
		else								INT_CLKO &= ~(1 << 4);	//��ֹ�ж�
        if(INTx->EXTI_Interrupt == ENABLE)		EXT2_interrupt_cb = INTx->interrupt_cb;	//�ص�
        GPIO_Inilize(GPIO_P3,GPIO_Pin_6, GPIO_HighZ);
		return	0;		//�ɹ�
	}

	if(EXT == EXT_INT3)		//���ж�3, �̶�Ϊ�½��ص����ȼ��ж�
	{
		if(INTx->EXTI_Interrupt == ENABLE)	INT_CLKO |=  (1 << 5);	//�����ж�	
		else								INT_CLKO &= ~(1 << 5);	//��ֹ�ж�
        if(INTx->EXTI_Interrupt == ENABLE)		EXT3_interrupt_cb = INTx->interrupt_cb;	//�ص�
        GPIO_Inilize(GPIO_P3,GPIO_Pin_7, GPIO_HighZ);
		return	0;		//�ɹ�
	}

	if(EXT == EXT_INT4)		//���ж�4, �̶�Ϊ�½��ص����ȼ��ж�
	{
		if(INTx->EXTI_Interrupt == ENABLE)	INT_CLKO |=  (1 << 6);	//�����ж�	
		else								INT_CLKO &= ~(1 << 6);	//��ֹ�ж�
        if(INTx->EXTI_Interrupt == ENABLE)		EXT4_interrupt_cb = INTx->interrupt_cb;	//�ص�
        GPIO_Inilize(GPIO_P3,GPIO_Pin_0, GPIO_HighZ);
		return	0;		//�ɹ�
	}
	return 2;	//ʧ��
}
