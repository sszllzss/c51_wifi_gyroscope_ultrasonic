#include "SysInit.h"
#include "config.h"
#include "gpio.h"
#include "delay.h"
#include "usart.h"
#include "stdio.h"
int main()
{
    uint16_t i;
    SysInit();
    
    GPIO_Inilize(GPIO_P5,GPIO_Pin_5,GPIO_OUT_PP);
    P55=0;
    while(1)
    {
        P55=!P55;
        for(i=0;i<1000;i++)
        {
            delay_us(800);
        }
        printf( "12322222\r\n");
        PrintString(USART2, "123\r\n");
    }
}