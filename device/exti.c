

#include "gpio.h"
#include "exti.h"
static Ext_interrupt_cb_t data EXT0_interrupt_cb = NULL;
static Ext_interrupt_cb_t data EXT1_interrupt_cb = NULL;
static Ext_interrupt_cb_t data EXT2_interrupt_cb = NULL;
static Ext_interrupt_cb_t data EXT3_interrupt_cb = NULL;
static Ext_interrupt_cb_t data EXT4_interrupt_cb = NULL;

/********************* INT0中断函数 *************************/
void Ext_INT0 (void) interrupt INT0_VECTOR		//进中断时已经清除标志
{
	if(EXT0_interrupt_cb)
        EXT0_interrupt_cb(EXT_INT0,P32);
}

/********************* INT1中断函数 *************************/
void Ext_INT1 (void) interrupt INT1_VECTOR		//进中断时已经清除标志
{
	if(EXT1_interrupt_cb)
        EXT1_interrupt_cb(EXT_INT1,P33);
}

/********************* INT2中断函数 *************************/
void Ext_INT2 (void) interrupt INT2_VECTOR	//
{
	if(EXT2_interrupt_cb)
        EXT2_interrupt_cb(EXT_INT2,P36);
}

/********************* INT3中断函数 *************************/
void Ext_INT3 (void) interrupt INT3_VECTOR
{
	if(EXT3_interrupt_cb)
        EXT3_interrupt_cb(EXT_INT3,P37);
}

/********************* INT4中断函数 *************************/
void Ext_INT4 (void) interrupt INT4_VECTOR
{
	if(EXT4_interrupt_cb)
        EXT4_interrupt_cb(EXT_INT4,P30);
}

//========================================================================
// 函数: uint8_t	Ext_Inilize(uint8_t EXT, EXTI_InitTypeDef *INTx)
// 描述: 外部中断初始化程序.
// 参数: INTx: 结构参数,请参考Exti.h里的定义.
// 返回: 成功返回0, 空操作返回1,错误返回2.
//========================================================================
uint8_t	Ext_Inilize(uint8_t EXT, EXTI_InitTypeDef *INTx)
{
	if(EXT >  EXT_INT4)	return 1;	//空操作
	
	if(EXT == EXT_INT0)	//外中断0
	{
		if(INTx->EXTI_Interrupt == ENABLE)		EX0 = 1;	//允许中断
		else									EX0 = 0;	//禁止中断
		if(INTx->EXTI_Polity == PolityHigh)		PX0 = 1;	//高优先级中断
		else									PX0 = 0;	//低优先级中断
		if(INTx->EXTI_Mode == EXT_MODE_Fall)	IT0 = 1;	//下降沿中断
		else									IT0 = 0;	//上升,下降沿中断
        if(INTx->EXTI_Interrupt == ENABLE)		EXT0_interrupt_cb = INTx->interrupt_cb;	//回调
        
        GPIO_Inilize(GPIO_P3,GPIO_Pin_2, GPIO_HighZ);
		return	0;		//成功
	}

	if(EXT == EXT_INT1)	//外中断1
	{
		if(INTx->EXTI_Interrupt == ENABLE)		EX1 = 1;	//允许中断
		else									EX1 = 0;	//禁止中断
		if(INTx->EXTI_Polity == PolityHigh)		PX1 = 1;	//高优先级中断
		else									PX1 = 0;	//低优先级中断
		if(INTx->EXTI_Mode == EXT_MODE_Fall)	IT1 = 1;	//下降沿中断
		else									IT1 = 0;	//上升,下降沿中断
        if(INTx->EXTI_Interrupt == ENABLE)		EXT1_interrupt_cb = INTx->interrupt_cb;	//回调
        GPIO_Inilize(GPIO_P3,GPIO_Pin_3, GPIO_HighZ);
		return	0;		//成功
	}

	if(EXT == EXT_INT2)		//外中断2, 固定为下降沿低优先级中断
	{
		if(INTx->EXTI_Interrupt == ENABLE)	INT_CLKO |=  (1 << 4);	//允许中断	
		else								INT_CLKO &= ~(1 << 4);	//禁止中断
        if(INTx->EXTI_Interrupt == ENABLE)		EXT2_interrupt_cb = INTx->interrupt_cb;	//回调
        GPIO_Inilize(GPIO_P3,GPIO_Pin_6, GPIO_HighZ);
		return	0;		//成功
	}

	if(EXT == EXT_INT3)		//外中断3, 固定为下降沿低优先级中断
	{
		if(INTx->EXTI_Interrupt == ENABLE)	INT_CLKO |=  (1 << 5);	//允许中断	
		else								INT_CLKO &= ~(1 << 5);	//禁止中断
        if(INTx->EXTI_Interrupt == ENABLE)		EXT3_interrupt_cb = INTx->interrupt_cb;	//回调
        GPIO_Inilize(GPIO_P3,GPIO_Pin_7, GPIO_HighZ);
		return	0;		//成功
	}

	if(EXT == EXT_INT4)		//外中断4, 固定为下降沿低优先级中断
	{
		if(INTx->EXTI_Interrupt == ENABLE)	INT_CLKO |=  (1 << 6);	//允许中断	
		else								INT_CLKO &= ~(1 << 6);	//禁止中断
        if(INTx->EXTI_Interrupt == ENABLE)		EXT4_interrupt_cb = INTx->interrupt_cb;	//回调
        GPIO_Inilize(GPIO_P3,GPIO_Pin_0, GPIO_HighZ);
		return	0;		//成功
	}
	return 2;	//失败
}
