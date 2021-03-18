#include "SysInit.h"
#include "config.h"
#include "gpio.h"
#include "delay.h"
#include "usart.h"
#include "stdio.h"
#include "ultrasonic.h"


int main()
{
    double distance = 0;
    uint8_t  pwm=128;
    uint16_t i;
    SysInit();
    U_Init();
    GPIO_Inilize(GPIO_P5,GPIO_Pin_5,GPIO_OUT_PP);
    P55=0;
    while(1)
    {
        distance = U_GetDistance();
        P55=!P55;
        printf("distance:%f\r\n",distance);
        for(i=0;i<1000;i++)
        {
            delay_us(800);
        }
        if(UARTx_ReadRxLen(USART1) > 0)
        {
            int8_t len = UARTx_ReadRxLen(USART1);
            for(i=0;i<len;i++)
            {
                char c;
                UARTx_ReadRxChar(USART1,&c);
                UARTx_writebuff(USART2,c);
            }
        }
        if(UARTx_ReadRxLen(USART2) > 0)
        {
            int8_t len = UARTx_ReadRxLen(USART2);
            for(i=0;i<len;i++)
            {
                char c;
                UARTx_ReadRxChar(USART2,&c);
                UARTx_writebuff(USART1,c);
            }
        }
    }
}