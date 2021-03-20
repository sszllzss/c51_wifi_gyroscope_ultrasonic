
#include "usart.h"
#include	"delay.h"
#include	"gpio.h"




#ifdef USING_UART1
static uint8_t	xdata TX1_Buffer[COM_TX1_Lenth];	//���ͻ���
static uint8_t 	xdata RX1_Buffer[COM_RX1_Lenth];	//���ջ���
#endif
#ifdef USING_UART2
static uint8_t	xdata TX2_Buffer[COM_TX2_Lenth];	//���ͻ���
static uint8_t 	xdata RX2_Buffer[COM_RX2_Lenth];	//���ջ���
#endif
#ifdef USING_UART3
static uint8_t	xdata TX3_Buffer[COM_TX3_Lenth];	//���ͻ���
static uint8_t 	xdata RX3_Buffer[COM_RX3_Lenth];	//���ջ���
#endif
#ifdef USING_UART4
static uint8_t	xdata TX4_Buffer[COM_TX4_Lenth];	//���ͻ���
static uint8_t 	xdata RX4_Buffer[COM_RX4_Lenth];	//���ջ���
#endif

static uint8_t xdata  uart_init = 0;


static COMx_Define xdata Uartx_config[]=
{
    #ifdef USING_UART1
        {1,RX1_Buffer,TX1_Buffer,COM_RX1_Lenth,COM_TX1_Lenth,0,0,0,0,0,0,0},
    #endif
    #ifdef USING_UART2
        {2,RX2_Buffer,TX2_Buffer,COM_RX2_Lenth,COM_TX2_Lenth,0,0,0,0,0,0,0},
    #endif
    #ifdef USING_UART3
        {3,RX3_Buffer,TX3_Buffer,COM_RX3_Lenth,COM_TX3_Lenth,0,0,0,0,0,0,0},
    #endif
    #ifdef USING_UART4
        {4,RX4_Buffer,TX4_Buffer,COM_RX4_Lenth,COM_TX4_Lenth,0,0,0,0,0,0,0},
    #endif
};

static void USART_Hook()
{
    uint8_t data i;
    for(i=0;i<sizeof(Uartx_config)/sizeof(Uartx_config[0]);i++)
    {
        if(Uartx_config[i].RX_TimeOut > 0)
        {
            Uartx_config[i].RX_TimeOut--;
            if(Uartx_config[i].RX_TimeOut==0)
            {
                if(Uartx_config[i].timer_out_cb)
                {
                    Uartx_config[i].timer_out_cb();
                }
            }
        }
    }
}
void USART_Set_rx_timer_out_cb(uint8_t UARTx, usart_rx_timer_out_cb_t timer_out_cb,uint8_t RX_TimeOut)//���ó�ʱ֪ͨ�ص�
{
    Uartx_config[UARTx].timer_out_cb = timer_out_cb;
    Uartx_config[UARTx].RX_TimeOut = RX_TimeOut;
}
int8_t USART_Configuration(uint8_t UARTx, COMx_InitDefine *COMx)
{
	uint8_t	i;
	uint32_t	j;
    
    Uartx_config[UARTx].TX_read = 0;
    Uartx_config[UARTx].TX_write = 0;
    Uartx_config[UARTx].B_TX_busy = 0;
    Uartx_config[UARTx].RX_Front = 0;
    Uartx_config[UARTx].RX_Rear = 0;
    Uartx_config[UARTx].RX_RxCnt = 0;
    Uartx_config[UARTx].timer_out_cb = NULL;
    if(COMx->RX_TimeOut == 0)
    {
        Uartx_config[UARTx].RX_TimeOut = 0;
    }
    else
    {
        Uartx_config[UARTx].RX_TimeOut = COMx->RX_TimeOut;
    }
    if(uart_init==0)
    {
        delay_add_hook(USART_Hook);
        uart_init = 1;
    }
#ifdef USING_UART1
	if(UARTx == USART1)
	{

		for(i=0; i<COM_TX1_Lenth; i++)	TX1_Buffer[i] = 0;
		for(i=0; i<COM_RX1_Lenth; i++)	RX1_Buffer[i] = 0;

		if(COMx->UART_Mode > UART_9bit_BRTx)	return 2;	//ģʽ����
		if(COMx->UART_Polity == PolityHigh)		PS = 1;	//�����ȼ��ж�
		else									PS = 0;	//�����ȼ��ж�
		SCON = (SCON & 0x3f) | COMx->UART_Mode;
		if((COMx->UART_Mode == UART_9bit_BRTx) ||(COMx->UART_Mode == UART_8bit_BRTx))	//�ɱ䲨����
		{

            j = (MAIN_Fosc / COMx->UART_BaudRate) / 4;	//��1T����

            if(j >= 65536UL)	return 2;	//����
            j = 65536UL - j;
            
            

			if(COMx->UART_BRT_Use == BRT_Timer1)
			{
				TR1 = 0;
				AUXR &= ~0x01;		//S1 BRT Use Timer1;
				TMOD &= ~(1<<6);	//Timer1 set As Timer
				TMOD &= ~0x30;		//Timer1_16bitAutoReload;
                AUXR |=  (1<<6);	//Timer1 set as 1T mode
				TH1 = (uint8_t)(j>>8);
				TL1 = (uint8_t)j;
				ET1 = 0;	//��ֹ�ж�
				TMOD &= ~0x40;	//��ʱ
				INT_CLKO &= ~0x02;	//�����ʱ��
				TR1  = 1;
			}
			else if(COMx->UART_BRT_Use == BRT_Timer2)
			{
				AUXR &= ~(1<<4);	//Timer stop
				AUXR |= 0x01;		//S1 BRT Use Timer2;
				AUXR &= ~(1<<3);	//Timer2 set As Timer
                AUXR |=  (1<<2);	//Timer2 set as 1T mode
				T2H = (uint8_t)(j>>8);
				T2L = (uint8_t)j;
				IE2  &= ~(1<<2);	//��ֹ�ж�
				AUXR &= ~(1<<3);	//��ʱ
				AUXR |=  (1<<4);	//Timer run enable
			}
			else return 2;	//����
		}
		else if(COMx->UART_Mode == UART_ShiftRight)
		{
			if(COMx->BaudRateDouble == ENABLE)	AUXR |=  (1<<5);	//�̶�������SysClk/2
			else								AUXR &= ~(1<<5);	//�̶�������SysClk/12
		}
		else if(COMx->UART_Mode == UART_9bit)	//�̶�������SysClk*2^SMOD/64
		{
			if(COMx->BaudRateDouble == ENABLE)	PCON |=  (1<<7);	//�̶�������SysClk/32
			else								PCON &= ~(1<<7);	//�̶�������SysClk/64
		}
        if(COMx->Morecommunicate == ENABLE) SCON |=  (1<<5);
        else                                SCON &= ~(1<<5);
		if(COMx->UART_Interrupt == ENABLE)	ES = 1;	//�����ж�
		else								ES = 0;	//��ֹ�ж�
		if(COMx->UART_RxEnable == ENABLE)	REN = 1;	//�������
		else								REN = 0;	//��ֹ����
		P_SW1 = (P_SW1 & 0x3f) | (COMx->UART_P_SW & 0xc0);	//�л�IO
		if(COMx->UART_RXD_TXD_Short == ENABLE)	PCON2 |=  (1<<4);	//�ڲ���·RXD��TXD, ���м�, ENABLE,DISABLE
		else									PCON2 &= ~(1<<4);
        if(COMx->UART_P_SW == UART1_SW_P30_P31){GPIO_Inilize(GPIO_P3,GPIO_Pin_0, GPIO_PullUp);GPIO_Inilize(GPIO_P3,GPIO_Pin_1,GPIO_OUT_PP);}
        else if(COMx->UART_P_SW == UART1_SW_P36_P37){GPIO_Inilize(GPIO_P3,GPIO_Pin_6, GPIO_PullUp);GPIO_Inilize(GPIO_P3,GPIO_Pin_7,GPIO_OUT_PP);}
        else if(COMx->UART_P_SW == UART1_SW_P16_P17){GPIO_Inilize(GPIO_P1,GPIO_Pin_6, GPIO_PullUp);GPIO_Inilize(GPIO_P1,GPIO_Pin_7,GPIO_OUT_PP);}
		return	0;
	}
#endif
#ifdef USING_UART2
	if(UARTx == USART2)
	{

		for(i=0; i<COM_TX2_Lenth; i++)	TX2_Buffer[i] = 0;
		for(i=0; i<COM_RX2_Lenth; i++)	RX2_Buffer[i] = 0;

		if((COMx->UART_Mode == UART_9bit_BRTx) ||(COMx->UART_Mode == UART_8bit_BRTx))	//�ɱ䲨����
		{
			if(COMx->UART_Polity == PolityHigh)		IP2 |=  1;	//�����ȼ��ж�
			else									IP2 &= ~1;	//�����ȼ��ж�
			if(COMx->UART_Mode == UART_9bit_BRTx)	S2CON |=  (1<<7);	//9bit
			else									S2CON &= ~(1<<7);	//8bit
			j = (MAIN_Fosc / 4) / COMx->UART_BaudRate;	//��1T����
			if(j >= 65536UL)	return 2;	//����
			j = 65536UL - j;
            if(COMx->UART_BRT_Use != BRT_Timer2) return 2;	//ģʽ����
			AUXR &= ~(1<<4);	//Timer stop
			AUXR &= ~(1<<3);	//Timer2 set As Timer
			AUXR |=  (1<<2);	//Timer2 set as 1T mode
			T2H = (uint8_t)(j>>8);
			T2L = (uint8_t)j;
			IE2  &= ~(1<<2);	//��ֹ�ж�
			AUXR |=  (1<<4);	//Timer run enable
		}
		else	return 2;	//ģʽ����
        if(COMx->Morecommunicate == ENABLE) S2CON |=  (1<<5);
        else                                S2CON &= ~(1<<5);
		if(COMx->UART_Interrupt == ENABLE)	IE2   |=  1;		//�����ж�
		else								IE2   &= ~1;		//��ֹ�ж�
		if(COMx->UART_RxEnable == ENABLE)	S2CON |=  (1<<4);	//�������
		else								S2CON &= ~(1<<4);	//��ֹ����
		P_SW2 = (P_SW2 & ~1) | (COMx->UART_P_SW & 0x01);	//�л�IO
        if(COMx->UART_P_SW == UART2_SW_P10_P11){GPIO_Inilize(GPIO_P1,GPIO_Pin_0, GPIO_PullUp);GPIO_Inilize(GPIO_P1,GPIO_Pin_1,GPIO_OUT_PP);}
        else if(COMx->UART_P_SW == UART2_SW_P46_P47){GPIO_Inilize(GPIO_P4,GPIO_Pin_6, GPIO_PullUp);GPIO_Inilize(GPIO_P4,GPIO_Pin_7,GPIO_OUT_PP);}
        
        return 0;
	}
#endif
#ifdef USING_UART3
	if(UARTx == USART3)
	{

		for(i=0; i<COM_TX3_Lenth; i++)	TX3_Buffer[i] = 0;
		for(i=0; i<COM_RX3_Lenth; i++)	RX3_Buffer[i] = 0;

		if((COMx->UART_Mode == UART_9bit_BRTx) || (COMx->UART_Mode == UART_8bit_BRTx))	//�ɱ䲨����
		{

			if(COMx->UART_Mode == UART_9bit_BRTx)	S3CON |=  (1<<7);	//9bit
			else									S3CON &= ~(1<<7);	//8bit
			j = (MAIN_Fosc / 4) / COMx->UART_BaudRate;	//��1T����
			if(j >= 65536UL)	return 2;	//����
			j = 65536UL - j;
			if(COMx->UART_BRT_Use == BRT_Timer2)
			{
                AUXR &= ~(1<<4);	//Timer stop
                S3CON &= ~0x40;		//S3 BRT Use Timer2;
                AUXR &= ~(1<<3);	//Timer2 set As Timer
                AUXR |=  (1<<2);	//Timer2 set as 1T mode
                T2H = (uint8_t)(j>>8);
                T2L = (uint8_t)j;
                IE2  &= ~(1<<2);	//��ֹ�ж�
                AUXR |=  (1<<4);	//Timer run enable
            }
            else if(COMx->UART_BRT_Use == BRT_Timer3)
            {
                T3T4M &=  ~(1<<3);	//Timer stop
                S3CON |= 0x40;		//S3 BRT Use Timer3;
                T3T4M &= ~(1<<2);	//Timer3 set As Timer
                T3T4M |=  (1<<1);	//Timer3 set as 1T mode
                T3H = (uint8_t)(j>>8);
                T3L = (uint8_t)j;
                IE2  &= ~(1<<5);	//��ֹ�ж�
                T3T4M |=  (1<<3);	//Timer run enable
            }
            else
            {
                return 2;	//ģʽ����
            }

		}
		else	return 2;	//ģʽ����
        if(COMx->Morecommunicate == ENABLE) S3CON |=  (1<<5);
        else                                S3CON &= ~(1<<5);
		if(COMx->UART_Interrupt == ENABLE)	IE2   |=  (1<<3);		//�����ж�
		else								IE2   &= ~(1<<3);		//��ֹ�ж�
		if(COMx->UART_RxEnable == ENABLE)	S3CON |=  (1<<4);	//�������
		else								S3CON &= ~(1<<4);	//��ֹ����
		P_SW2 = (P_SW2 & ~(1<<1)) | ((COMx->UART_P_SW & 0x01)<<1);	//�л�IO
        if(COMx->UART_P_SW == UART3_SW_P00_P01){GPIO_Inilize(GPIO_P0,GPIO_Pin_0, GPIO_PullUp);GPIO_Inilize(GPIO_P0,GPIO_Pin_1,GPIO_OUT_PP);}
        else if(COMx->UART_P_SW == UART3_SW_P56_P51){GPIO_Inilize(GPIO_P5,GPIO_Pin_6, GPIO_PullUp);GPIO_Inilize(GPIO_P5,GPIO_Pin_7,GPIO_OUT_PP);}
        return 0;
	}
#endif
#ifdef USING_UART4
	if(UARTx == USART4)
	{

		for(i=0; i<COM_TX4_Lenth; i++)	TX4_Buffer[i] = 0;
		for(i=0; i<COM_RX4_Lenth; i++)	RX4_Buffer[i] = 0;

		if((COMx->UART_Mode == UART_9bit_BRTx) ||(COMx->UART_Mode == UART_8bit_BRTx))	//�ɱ䲨����
		{
			if(COMx->UART_Mode == UART_9bit_BRTx)	S4CON |=  (1<<7);	//9bit
			else									S4CON &= ~(1<<7);	//8bit
			j = (MAIN_Fosc / 4) / COMx->UART_BaudRate;	//��1T����
			if(j >= 65536UL)	return 2;	//����
			j = 65536UL - j;
			if(COMx->UART_BRT_Use == BRT_Timer2)
			{
                AUXR &= ~(1<<4);	//Timer stop
                S4CON &= ~0x40;		//S3 BRT Use Timer2;
                AUXR &= ~(1<<3);	//Timer2 set As Timer
                AUXR |=  (1<<2);	//Timer2 set as 1T mode
                T2H = (uint8_t)(j>>8);
                T2L = (uint8_t)j;
                IE2  &= ~(1<<2);	//��ֹ�ж�
                AUXR |=  (1<<4);	//Timer run enable
            }
            else if(COMx->UART_BRT_Use == BRT_Timer4)
            {
                T3T4M &=  ~(1<<7);	//Timer stop
                S4CON |= 0x40;		//S3 BRT Use Timer4;
                T3T4M &= ~(1<<6);	//Timer4 set As Timer
                T3T4M |=  (1<<5);	//Timer4 set as 1T mode
                T4H = (uint8_t)(j>>8);
                T4L = (uint8_t)j;
                IE2  &= ~(1<<6);	//��ֹ�ж�
                T3T4M |=  (1<<7);	//Timer run enable
            }
            else
            {
                return 2;	//ģʽ����
            }
            
		}
		else	return 2;	//ģʽ����
        if(COMx->Morecommunicate == ENABLE) S4CON |=  (1<<5);
        else                                S4CON &= ~(1<<5);
		if(COMx->UART_Interrupt == ENABLE)	IE2   |=  (1<<4);		//�����ж�
		else								IE2   &= ~(1<<4);		//��ֹ�ж�
		if(COMx->UART_RxEnable == ENABLE)	S4CON |=  (1<<4);	//�������
		else								S4CON &= ~(1<<4);	//��ֹ����
		P_SW2 = (P_SW2 & ~(1<<2)) | ((COMx->UART_P_SW & 0x01)<<2);	//�л�IO
        if(COMx->UART_P_SW == UART4_SW_P02_P03){GPIO_Inilize(GPIO_P0,GPIO_Pin_2, GPIO_PullUp);GPIO_Inilize(GPIO_P0,GPIO_Pin_3,GPIO_OUT_PP);}
        else if(COMx->UART_P_SW == UART4_SW_P52_P53){GPIO_Inilize(GPIO_P5,GPIO_Pin_2, GPIO_PullUp);GPIO_Inilize(GPIO_P5,GPIO_Pin_3,GPIO_OUT_PP);}
        return 0;
	}
#endif
    return 2;
}


/*************** װ�ش��ڷ��ͻ��� *******************************/
#ifdef USING_UART1
void TX1_write2buff(uint8_t dat)	//д�뷢�ͻ��壬ָ��+1
{
	TX1_Buffer[Uartx_config[USART1].TX_write] = dat;	//װ���ͻ���
	if(++Uartx_config[USART1].TX_write >= COM_TX1_Lenth)	Uartx_config[USART1].TX_write = 0;

	if(Uartx_config[USART1].B_TX_busy == 0)		//����
	{  
		Uartx_config[USART1].B_TX_busy = 1;		//��־æ
		TI = 1;					//���������ж�
	}
}
#endif
#ifdef USING_UART2
void TX2_write2buff(uint8_t dat)	//д�뷢�ͻ��壬ָ��+1
{
    
	TX2_Buffer[Uartx_config[USART2].TX_write] = dat;	//װ���ͻ���
	if(++Uartx_config[USART2].TX_write >= COM_TX2_Lenth)	Uartx_config[USART2].TX_write = 0;

	if(Uartx_config[USART2].B_TX_busy == 0)		//����
	{  
		Uartx_config[USART2].B_TX_busy = 1;		//��־æ
		S2CON |=  2;				//���������ж�
	}
}
#endif
#ifdef USING_UART3
void TX3_write2buff(uint8_t dat)	//д�뷢�ͻ��壬ָ��+1
{
    
	TX3_Buffer[Uartx_config[USART3].TX_write] = dat;	//װ���ͻ���
	if(++Uartx_config[USART3].TX_write >= COM_TX3_Lenth)	Uartx_config[USART3].TX_write = 0;

	if(Uartx_config[USART3].B_TX_busy == 0)		//����
	{  
		Uartx_config[USART3].B_TX_busy = 1;		//��־æ
		S3CON |=  2;				//���������ж�
	}
}
#endif
#ifdef USING_UART4
void TX4_write2buff(uint8_t dat)	//д�뷢�ͻ��壬ָ��+1
{
    
	TX4_Buffer[Uartx_config[USART4].TX_write] = dat;	//װ���ͻ���
	if(++Uartx_config[USART4].TX_write >= COM_TX4_Lenth)	Uartx_config[USART4].TX_write = 0;

	if(Uartx_config[USART4].B_TX_busy == 0)		//����
	{  
		Uartx_config[USART4].B_TX_busy = 1;		//��־æ
		S4CON |=  2;				//���������ж�
	}
}
#endif

void UARTx_writebuff(enum USARTx com, uint8_t dat)	//д�뷢�ͻ��壬ָ��+1
{
    #ifdef USING_UART1
	if(Uartx_config[com].id == 1)	TX1_write2buff(dat);
    #endif
    #ifdef USING_UART2
	if(Uartx_config[com].id == 2)	TX2_write2buff(dat);
    #endif
    #ifdef USING_UART3
	if(Uartx_config[com].id == 3)	TX3_write2buff(dat);
    #endif
    #ifdef USING_UART4
	if(Uartx_config[com].id == 4)	TX4_write2buff(dat);
    #endif
}
uint8_t UARTx_ReadRxLen(enum USARTx com)
{
    return Uartx_config[com].RX_RxCnt;
}
int8_t UARTx_ReadRxChar(enum USARTx com,uint8_t *dat)
{
    if(Uartx_config[com].RX_Front != Uartx_config[com].RX_Rear)
    {
        *dat = Uartx_config[com].Rx_buff[Uartx_config[com].RX_Front];
        Uartx_config[com].RX_Front = (Uartx_config[com].RX_Front+1)%Uartx_config[com].RX_BuffLen;
        Uartx_config[com].RX_RxCnt--;
        return 0;
    }
    return  -1;
    
}
int8_t UARTx_CheckRxChar(enum USARTx com,uint8_t *dat)//�����Ӷ�����ȡ������ֻ�ǲ鿴һ������
{
    if(Uartx_config[com].RX_Front != Uartx_config[com].RX_Rear)
    {
        *dat = Uartx_config[com].Rx_buff[Uartx_config[com].RX_Front];
        return 0;
    }

    return  -1;
    
}


int8_t UARTx_CheckPosRxBuff(enum USARTx com,uint8_t pos,uint8_t *buff,uint8_t len)//�����Ӷ�����ȡ������ֻ�ǲ鿴һ������
{
    uint8_t i=0;

    if(Uartx_config[com].RX_RxCnt <= 0 || len <= 0 || (pos+len) > Uartx_config[com].RX_RxCnt)
    {
        return -1;
    }
    if((Uartx_config[com].RX_Front + pos + len ) / (Uartx_config[com].RX_BuffLen) >= 1)
    {
        if((Uartx_config[com].RX_Front + pos) / (Uartx_config[com].RX_BuffLen) >= 1)
        {
            for(i=0;i<len;i++)
            {
                buff[i] = Uartx_config[com].Rx_buff[(Uartx_config[com].RX_Front + pos)%(Uartx_config[com].RX_BuffLen) + i];
            }
        }
        else
        {

            for(i=0;i<Uartx_config[com].RX_BuffLen - (Uartx_config[com].RX_Front + pos);i++)
            {
                buff[i] = Uartx_config[com].Rx_buff[(Uartx_config[com].RX_Front + pos) + i];
            }
            for(i=0;i<(Uartx_config[com].RX_Front + pos + len)%Uartx_config[com].RX_BuffLen;i++)
            {
                buff[Uartx_config[com].RX_BuffLen - (Uartx_config[com].RX_Front + pos) + i] = Uartx_config[com].Rx_buff[i];
            }
        }

        
    }
    else
    {
        for(i=0;i<len;i++)
        {
            buff[i] = Uartx_config[com].Rx_buff[Uartx_config[com].RX_Front+pos+i];
        }
    }
    return 0;  
}
int8_t UARTx_CheckRxBuff(enum USARTx com,uint8_t *buff,uint8_t len)//�����Ӷ�����ȡ������ֻ�ǲ鿴һ������
{
    uint8_t i=0;
    if(Uartx_config[com].RX_RxCnt <=len)
    {
        for(i=0;i<len;i++)
        {
            buff[i] = Uartx_config[com].Rx_buff[(Uartx_config[com].RX_Front + i)%(Uartx_config[com].RX_BuffLen)];
        }
        return 0;
    }
    return -1;
}
int8_t UARTx_RemoveRxBuff(enum USARTx com,uint8_t len)
{
    if(Uartx_config[com].RX_RxCnt <=len)
    {
        Uartx_config[com].RX_Front = (Uartx_config[com].RX_Front + len) % (Uartx_config[com].RX_BuffLen);
        Uartx_config[com].RX_RxCnt=Uartx_config[com].RX_RxCnt-len;
        return 0;
    }
    return -1;
    
}
void PrintString(enum USARTx com, uint8_t *puts)
{
    for (; *puts != 0;	puts++)  UARTx_writebuff(com,*puts); 	//����ֹͣ��0����
}


#ifdef USING_UART1
/********************* UART1�жϺ���************************/
void UART1_int (void) interrupt UART1_VECTOR
{
	if(RI)
	{
		RI = 0;
        if(((Uartx_config[USART1].RX_Rear+1) % COM_RX1_Lenth) != Uartx_config[USART1].RX_Front)//����û����
		{
			RX1_Buffer[Uartx_config[USART1].RX_Rear] = SBUF;
            Uartx_config[USART1].RX_RxCnt++;
            Uartx_config[USART1].RX_Rear =(Uartx_config[USART1].RX_Rear +1) % COM_RX1_Lenth;
			Uartx_config[USART1].RX_TimeOut = Uartx_config[USART1].RX_TimeOut;;
		}
        else if(Uartx_config[USART1].timer_out_cb)
        {
            Uartx_config[USART1].timer_out_cb();
        }
	}

	if(TI)
	{
		TI = 0;
		if(Uartx_config[USART1].TX_read != Uartx_config[USART1].TX_write)
		{
		 	SBUF = TX1_Buffer[Uartx_config[USART1].TX_read];
			if(++Uartx_config[USART1].TX_read >= COM_TX1_Lenth)		Uartx_config[USART1].TX_read = 0;
		}
		else	Uartx_config[USART1].B_TX_busy = 0;
	}
}
#endif
#ifdef USING_UART2
/********************* UART2�жϺ���************************/
void UART2_int (void) interrupt UART2_VECTOR
{
	if((S2CON & 1) != 0)
	{
		S2CON &= ~1;
        if(((Uartx_config[USART2].RX_Rear+1) % COM_RX2_Lenth) != Uartx_config[USART2].RX_Front)//����û����
		{
			RX2_Buffer[Uartx_config[USART2].RX_Rear] = S2BUF;
            Uartx_config[USART2].RX_RxCnt++;
            Uartx_config[USART2].RX_Rear =(Uartx_config[USART2].RX_Rear +1) % COM_RX2_Lenth;
			Uartx_config[USART2].RX_TimeOut = Uartx_config[USART2].RX_TimeOut;
		}
        else if(Uartx_config[USART2].timer_out_cb)
        {
            Uartx_config[USART2].timer_out_cb();
        }
	}

	if((S2CON & 2) != 0)
	{
		S2CON &= ~2;
		if(Uartx_config[USART2].TX_read != Uartx_config[USART2].TX_write)
		{
		 	S2BUF = TX2_Buffer[Uartx_config[USART2].TX_read];
			if(++Uartx_config[USART2].TX_read >= COM_TX2_Lenth)		Uartx_config[USART2].TX_read = 0;
		}
		else	Uartx_config[USART2].B_TX_busy = 0;
	}

}
#endif
#ifdef USING_UART3
/********************* UART3�жϺ���************************/
void UART3_int (void) interrupt UART3_VECTOR
{
	if((S3CON & 1) != 0)
	{
		S3CON &= ~1;
        if(((Uartx_config[USART3].RX_Rear+1) % COM_RX3_Lenth) != Uartx_config[USART3].RX_Front)//����û����
		{
			RX3_Buffer[Uartx_config[USART3].RX_Rear] = S3BUF;
            Uartx_config[USART3].RX_RxCnt++;
            Uartx_config[USART3].RX_Rear =(Uartx_config[USART3].RX_Rear +1) % COM_RX3_Lenth;
			Uartx_config[USART3].RX_TimeOut = Uartx_config[USART3].RX_TimeOut;
		}
        else if(Uartx_config[USART3].timer_out_cb)
        {
            Uartx_config[USART3].timer_out_cb();
        }
	}

	if((S3CON & 2) != 0)
	{
		S3CON &= ~2;
		if(Uartx_config[USART3].TX_read != Uartx_config[USART3].TX_write)
		{
		 	S3BUF = TX3_Buffer[Uartx_config[USART3].TX_read];
			if(++Uartx_config[USART3].TX_read >= COM_TX3_Lenth)		Uartx_config[USART3].TX_read = 0;
		}
		else	Uartx_config[USART3].B_TX_busy = 0;
	}
}
#endif
#ifdef USING_UART4
/********************* UART4�жϺ���************************/
void UART4_int (void) interrupt UART4_VECTOR
{
	if((S4CON & 1) != 0)
	{
		S4CON &= ~1;
        if(((Uartx_config[USART4].RX_Rear+1) % COM_RX4_Lenth) != Uartx_config[USART4].RX_Front)//����û����
		{
			RX4_Buffer[Uartx_config[USART4].RX_Rear] = S4BUF;
            Uartx_config[USART4].RX_RxCnt++;
            Uartx_config[USART4].RX_Rear =(Uartx_config[USART4].RX_Rear +1) % COM_RX4_Lenth;
			Uartx_config[USART4].RX_TimeOut = Uartx_config[USART4].RX_TimeOut;
		}
        else if(Uartx_config[USART4].timer_out_cb)
        {
            Uartx_config[USART4].timer_out_cb();
        }
	}

	if((S4CON & 2) != 0)
	{
		S4CON &= ~2;
		if(Uartx_config[USART4].TX_read != Uartx_config[USART4].TX_write)
		{
		 	S4BUF = TX4_Buffer[Uartx_config[USART4].TX_read];
			if(++Uartx_config[USART4].TX_read >= COM_TX4_Lenth)		Uartx_config[USART4].TX_read = 0;
		}
		else	Uartx_config[USART4].B_TX_busy = 0;
	}
}
#endif
