#include "ultrasonic.h"
#include "pca.h"
#include "gpio.h"
#include "delay.h"
static uint32_t data u_cnt = 0;
static uint32_t data u_ago = 0;
static double data u_distance = 0.0;
static double data u_distance_bk = 0.0;
static double data u_distance_temp = 0.0;
static bit u_is_high=0;
static bit u_is_succeed=0;
static bit u_is_measure=0;//ÊÇ·ñÔÚ²âÁ¿
static void pca_interrupt_cb(uint8_t PCA_id,uint16_t value)
{
    if(u_is_measure)
    {
        if(PCA_id == PCA_Counter&&u_is_high == 1)
        {
            

            if(u_cnt == 0)
            {
                u_ago = (0xFFFF - u_ago)/(MAIN_Fosc/1000000);
            }
            else
            {
                u_ago+= 0xFFFF/(MAIN_Fosc/1000000);
            }
            u_cnt++;
        

        }
        else
        {
            if(P35 == 1 && u_is_high == 0){
                
                u_ago = value;u_is_high = 1;
            }
            else if(P35 == 0 && u_is_high == 1)
            {
                if(u_cnt>0)
                {
                    u_ago += value/(MAIN_Fosc/1000000);
                }
                else
                {
                    u_ago = (value-u_ago)/(MAIN_Fosc/1000000);
                }
                

                u_is_succeed = 1;
                
                u_cnt=0; 
                u_is_high = 0;
                
            }
        } 
    }
    
}
static void U_Hook()//1ms
{
    static uint8_t cont_timerout = 0;
    cont_timerout++;
    if(cont_timerout==69)
    {
 
        
        if(u_is_succeed)
        {
            u_distance_temp = u_ago/58.0;
            
            if((u_distance_bk>u_distance_temp)&&(u_distance_bk-u_distance_temp <= 5) || (u_distance_bk<=u_distance_temp)&&(u_distance_temp-u_distance_bk <= 5))
            {
                u_distance = u_distance_temp;
            }
            else
            {
                u_distance = -1;
            }
            u_distance_bk = u_distance_temp;
            
            u_is_succeed = 0;
            u_is_measure = 1; 
            P53 = 1;
        }
        else 
        {

            if(P35 == 1)
            {
                u_is_measure = 0; 
            }
            else
            {
                u_is_measure = 1; 
                P53 = 1;
            }
        }
        u_ago = 0;u_cnt = 0;
        u_is_high = 0;
        
        
        
        
    }
    else if(cont_timerout>=70)
    {
        P53 = 0;
        cont_timerout = 0;
    }
    
}
static void Pca_Init(void)
{
    PCA_InitTypeDef PCA_def;
    PCA_def.PCA_IoUse = PCA_P34_P35_P36_P37;
    PCA_def.PCA_Clock = PCA_Clock_1T;
    PCA_def.PCA_Mode = PCA_Mode_Capture;
    PCA_def.PCA_PWM_Wide = PCA_PWM_8bit;
    PCA_def.PCA_Interrupt_Mode = PCA_Rise_Active|PCA_Fall_Active|ENABLE;
    PCA_def.PCA_Polity = PolityHigh;
    PCA_def.PCA_Value = 0;
    PCA_def.PCA_Callback = pca_interrupt_cb;
    PCA_Init(PCA0, &PCA_def);
    PCA_Init(PCA_Counter, &PCA_def);
}
double U_GetDistance(void)
{
    return u_distance;
}
void U_Init(void)
{	
    GPIO_Inilize(GPIO_P5,GPIO_Pin_3,GPIO_OUT_PP);
    P53 = 0;
    P35 = 0;
	Pca_Init();
    delay_add_hook(U_Hook);
}
