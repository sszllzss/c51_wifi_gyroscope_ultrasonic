#include "SysInit.h"
#include "config.h"
#include "gpio.h"
#include "delay.h"
#include "usart.h"
#include "stdio.h"
#include "ultrasonic.h"
#include "mpu6050.h"
#include "led.h"
#include "separate_key.h"

int main()
{
    uint16_t Key_value;
    uint16_t len_cnt = 0;
    double distance = 0;
    uint8_t  pwm=128;
    uint16_t i;
    SysInit();
    U_Init();
    
    InitMPU6050();
    Led_init();
    SeparateKey_Init();
    Led_Start(10,0,len_cnt);
    at_esp8266_init();
    P55=0;
    while(1)
    {
//        distance = U_GetDistance();
//        
//        printf("distance:%f\r\n",distance);
//        
//        mpu6050_test();
        if(SeparateKey_GetValue(&Key_value))
        {
            if(((Key_value>>KEY_TYPE_CLICK)&0x0F))
            {
                if(((Key_value>>KEY_TYPE_CLICK)&0x0F)==KEY_VALUE_S1)
                {
                    printf("����S1\r\n");
                }
                else if(((Key_value>>KEY_TYPE_CLICK)&0x0F)==KEY_VALUE_S2)
                {
                    printf("����S2\r\n");
                }
                else if(((Key_value>>KEY_TYPE_CLICK)&0x0F)==KEY_VALUE_S3)
                {
                    printf("����S3\r\n");
                }
                else if(((Key_value>>KEY_TYPE_CLICK)&0x0F)==KEY_VALUE_S4)
                {
                    printf("����S4\r\n");
                }
            }
            else if(((Key_value>>KEY_TYPEDOUBLE)&0x0F))
            {
                if(((Key_value>>KEY_TYPEDOUBLE)&0x0F)==KEY_VALUE_S1)
                {
                   printf("˫��S1\r\n"); 
                }
                else if(((Key_value>>KEY_TYPEDOUBLE)&0x0F)==KEY_VALUE_S2)
                {
                    printf("˫��S2\r\n"); 
                }
                else if(((Key_value>>KEY_TYPEDOUBLE)&0x0F)==KEY_VALUE_S3)
                {
                    printf("˫��S3\r\n"); 
                }
                else if(((Key_value>>KEY_TYPEDOUBLE)&0x0F)==KEY_VALUE_S4)
                {
                    printf("˫��S4\r\n"); 
                }
            }
            else if(((Key_value>>KEY_TYPE_LONG)&0x0F))
            {
                if(((Key_value>>KEY_TYPE_LONG)&0x0F)==KEY_VALUE_S1)
                {
                    printf("����S1\r\n"); 
                }
                else if(((Key_value>>KEY_TYPE_LONG)&0x0F)==KEY_VALUE_S2)
                {
                    printf("����S2\r\n");
                }
                else if(((Key_value>>KEY_TYPE_LONG)&0x0F)==KEY_VALUE_S3)
                {
                    printf("����S3\r\n");
                }
                else if(((Key_value>>KEY_TYPE_LONG)&0x0F)==KEY_VALUE_S4)
                {
                    printf("����S4\r\n",4);
                }
            }
        }
        
//        for(i=0;i<3000;i++)
//        {
//            delay_us(800);
//            if(i%200 == 0)
//            {
//                len_cnt+=1;
//                if(len_cnt>10)
//                    len_cnt = 0;
//                Led_Update(0,len_cnt);

//            }
//        }
        delay_us(500);
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