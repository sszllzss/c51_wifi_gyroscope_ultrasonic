#include "config.h"
#include "gpio.h"
#include "SysInit.h"
#include "delay.h"
#include "usart.h"

static void GPIO_Init(void)
{
    GPIO_Inilize(GPIO_P0,GPIO_Pin_All,GPIO_HighZ);
    GPIO_Inilize(GPIO_P1,GPIO_Pin_All,GPIO_HighZ);
    GPIO_Inilize(GPIO_P2,GPIO_Pin_All,GPIO_HighZ);
    GPIO_Inilize(GPIO_P3,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_6|GPIO_Pin_7,GPIO_HighZ);
    GPIO_Inilize(GPIO_P4,GPIO_Pin_All,GPIO_HighZ);
    GPIO_Inilize(GPIO_P5,GPIO_Pin_All,GPIO_HighZ);
}
static void Uart_Init(void)
{
    COMx_InitDefine init_define;
#ifdef USING_UART1
    init_define.UART_Mode = UART_8bit_BRTx;                                                                   
    init_define.UART_BRT_Use = BRT_Timer2;
    init_define.UART_BaudRate = 9600L;
    init_define.Morecommunicate = DISABLE;//关闭多机通讯
    init_define.BaudRateDouble = DISABLE;//关闭双倍波特率
    init_define.UART_RXD_TXD_Short = DISABLE;
    init_define.UART_RxEnable = ENABLE;//打开接收
    init_define.UART_Interrupt = ENABLE;//打开中断
    init_define.UART_Polity = PolityHigh;//高优先级
#if  defined(DEBUG_PRINTF_UART1_SW_P30_P31)
    init_define.UART_P_SW = UART1_SW_P30_P31;//选择输出串口硬件为 P30 P31
    GPIO_Inilize(GPIO_P3,GPIO_Pin_0|GPIO_Pin_1,GPIO_PullUp);
#elif defined(DEBUG_PRINTF_UART1_SW_P36_P37)
    init_define.UART_P_SW = UART1_SW_P36_P37;//选择输出串口硬件为 P36 P37
    GPIO_Inilize(GPIO_P3,GPIO_Pin_6|GPIO_Pin_7,GPIO_PullUp);
#elif defined(DEBUG_PRINTF_UART1_SW_P16_P17)
    init_define.UART_P_SW = UART1_SW_P16_P17;//选择输出串口硬件为 P16 P17 必须使用内部时钟
    GPIO_Inilize(GPIO_P1,GPIO_Pin_6|GPIO_Pin_7,GPIO_PullUp);
#endif
    USART_Configuration(USART1,&init_define);
#endif
#ifdef USING_UART2
    init_define.UART_Mode = UART_8bit_BRTx;                                                                   
    init_define.UART_BRT_Use = BRT_Timer2;
    init_define.UART_BaudRate = 9600L;
    init_define.Morecommunicate = DISABLE;//关闭多机通讯
    init_define.BaudRateDouble = DISABLE;//关闭双倍波特率
    init_define.UART_RXD_TXD_Short = DISABLE;
    init_define.UART_RxEnable = ENABLE;//打开接收
    init_define.UART_Interrupt = ENABLE;//打开中断
    init_define.UART_Polity = PolityHigh;//高优先级
    init_define.UART_P_SW = UART2_SW_P10_P11;//选择输出串口硬件为 P10 P11
    GPIO_Inilize(GPIO_P1,GPIO_Pin_0|GPIO_Pin_1,GPIO_PullUp);
//    init_define.UART_P_SW = UART2_SW_P46_P47;//选择输出串口硬件为 P46 P47
//    GPIO_Inilize(GPIO_P4,GPIO_Pin_6|GPIO_Pin_7,GPIO_PullUp);

    USART_Configuration(USART2,&init_define);
#endif
#ifdef USING_UART3
    init_define.UART_Mode = UART_8bit_BRTx;                                                                   
    init_define.UART_BRT_Use = BRT_Timer2;
    init_define.UART_BaudRate = 9600L;
    init_define.Morecommunicate = DISABLE;//关闭多机通讯
    init_define.BaudRateDouble = DISABLE;//关闭双倍波特率
    init_define.UART_RXD_TXD_Short = DISABLE;
    init_define.UART_RxEnable = ENABLE;//打开接收
    init_define.UART_Interrupt = ENABLE;//打开中断
    init_define.UART_Polity = PolityHigh;//高优先级
    init_define.UART_P_SW = UART3_SW_P00_P01;//选择输出串口硬件为 P01 P01
    GPIO_Inilize(GPIO_P0,GPIO_Pin_0|GPIO_Pin_1,GPIO_PullUp);
//    init_define.UART_P_SW = UART3_SW_P56_P51;//选择输出串口硬件为 P56 P51
//    GPIO_Inilize(GPIO_P5,GPIO_Pin_6|GPIO_Pin_1,GPIO_PullUp);
    USART_Configuration(USART3,&init_define);
#endif
#ifdef USING_UART4
    init_define.UART_Mode = UART_8bit_BRTx;                                                                   
    init_define.UART_BRT_Use = BRT_Timer2;
    init_define.UART_BaudRate = 9600L;
    init_define.Morecommunicate = DISABLE;//关闭多机通讯
    init_define.BaudRateDouble = DISABLE;//关闭双倍波特率
    init_define.UART_RXD_TXD_Short = DISABLE;
    init_define.UART_RxEnable = ENABLE;//打开接收
    init_define.UART_Interrupt = ENABLE;//打开中断
    init_define.UART_Polity = PolityHigh;//高优先级
    init_define.UART_P_SW = UART4_SW_P02_P03;//选择输出串口硬件为 P02 P03
    GPIO_Inilize(GPIO_P0,GPIO_Pin_2|GPIO_Pin_3,GPIO_PullUp);
//    init_define.UART_P_SW = UART4_SW_P52_P53;//选择输出串口硬件为 P52 P53
//    GPIO_Inilize(GPIO_P5,GPIO_Pin_2|GPIO_Pin_3,GPIO_PullUp);
    USART_Configuration(USART4,&init_define);
#endif
}

void SysInit(void)
{
    EA = 1;
    GPIO_Init();
    delay_init();
    Uart_Init();

}
#ifdef DEBUG_PRINTF
//重写putchar函数
char putchar(char c)
{

	UARTx_writebuff(USART1,c);
    return c;
}
#endif

