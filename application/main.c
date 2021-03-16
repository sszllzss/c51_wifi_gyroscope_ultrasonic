#include "SysInit.h"
#include "config.h"
#include "gpio.h"
#include "delay.h"
#include "usart.h"
#include "stdio.h"
#include "pca.h"

static void pca_interrupt_cb(uint8_t PCA_id,uint16_t value)
{
    P55=!P55;
}
static void Pca_Init(void)
{
    PCA_InitTypeDef PCA_def;
    PCA_def.PCA_IoUse = PCA_P34_P35_P36_P37;
    PCA_def.PCA_Clock = PCA_Clock_12T;
    PCA_def.PCA_Mode = PCA_Mode_PWM;
    PCA_def.PCA_PWM_Wide = PCA_PWM_8bit;
    PCA_def.PCA_Interrupt_Mode = PCA_Rise_Active|PCA_Fall_Active|ENABLE;
    PCA_def.PCA_Polity = PolityHigh;
    PCA_def.PCA_Value = 128;
    PCA_def.PCA_Callback = pca_interrupt_cb;
    PCA_Init(PCA0, &PCA_def);
    PCA_Init(PCA_Counter, &PCA_def);
}
int main()
{
    uint8_t  pwm=128;
    uint16_t i;
    SysInit();
    Pca_Init();
    GPIO_Inilize(GPIO_P5,GPIO_Pin_5,GPIO_OUT_PP);
    P55=0;
    while(1)
    {
        PWMn_Update(PCA0, pwm++);
        for(i=0;i<100;i++)
        {
            delay_us(80);
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