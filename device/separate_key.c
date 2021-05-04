#include "separate_key.h"
#include "gpio.h"
#include "delay.h"

static uint16_t data Key_value = 0x000;

static uint8_t data s1Key_dat = 0x00;
static uint16_t data s1Key_cnt = 0x00;
static uint16_t data s1Key_long_cnt = 0x00;
static uint8_t data s2Key_dat = 0x00;
static uint16_t data s2Key_cnt = 0x00;
static uint16_t data s2Key_long_cnt = 0x00;
static uint8_t data s3Key_dat = 0x00;
static uint16_t data s3Key_cnt = 0x00;
static uint16_t data s3Key_long_cnt = 0x00;
static uint8_t data s4Key_dat = 0x00;
static uint16_t data s4Key_cnt = 0x00;
static uint16_t data s4Key_long_cnt = 0x00;
static uint8_t data s1Key_press_cnt = 0;
static uint8_t data s2Key_press_cnt = 0;
static uint8_t data s3Key_press_cnt = 0;
static uint8_t data s4Key_press_cnt = 0;
static void SeparateKey_Hook()
{
    static uint8_t cnt_5ms=0;
    static bit s1Key_press = 0;
    static bit s2Key_press = 0;
    static bit s3Key_press = 0;
    static bit s4Key_press = 0;
    static bit s1Key_long = 0;
    static bit s2Key_long = 0;
    static bit s3Key_long = 0;
    static bit s4Key_long = 0;
    
    cnt_5ms++;
    if(cnt_5ms>=5)
    {
        cnt_5ms = 0;
        s1Key_dat<<=1;
        s2Key_dat<<=1;
        s3Key_dat<<=1;
        s4Key_dat<<=1;
        if(!GPIO_ReadPin(KEY_S1_GPIO,KEY_S1_PIN)){s1Key_dat+=1;}
        if(!GPIO_ReadPin(KEY_S2_GPIO,KEY_S2_PIN)){s2Key_dat+=1;}
        if(!GPIO_ReadPin(KEY_S3_GPIO,KEY_S3_PIN)){s3Key_dat+=1;}
        if(!GPIO_ReadPin(KEY_S4_GPIO,KEY_S4_PIN)){s4Key_dat+=1;}
    }

    
    if(s1Key_dat==0xFF){if(s1Key_press==0){s1Key_press=1;}s1Key_long_cnt++;
        if(s1Key_long_cnt>KEY_LONG_TIMER){s1Key_long=1;s1Key_press=0;}}else if(s1Key_dat==0x00){if(s1Key_press){s1Key_press=0;s1Key_press_cnt++;}s1Key_long_cnt=0;s1Key_long=0;}else{s1Key_long_cnt=0;s1Key_long=0;}
    if(s2Key_dat==0xFF){if(s2Key_press==0){s2Key_press=1;}s2Key_long_cnt++;
        if(s2Key_long_cnt>KEY_LONG_TIMER){s2Key_long=1;s2Key_press=0;}}else if(s2Key_dat==0x00){if(s2Key_press){s2Key_press=0;s2Key_press_cnt++;}s2Key_press=0;s2Key_long_cnt=0;s2Key_long=0;}else{s2Key_long_cnt=0;s2Key_long=0;}
    if(s3Key_dat==0xFF){if(s3Key_press==0){s3Key_press=1;}s3Key_long_cnt++;
        if(s3Key_long_cnt>KEY_LONG_TIMER){s3Key_long=1;s3Key_press=0;}}else if(s3Key_dat==0x00){if(s3Key_press){s3Key_press=0;s3Key_press_cnt++;}s3Key_press=0;s3Key_long_cnt=0;s3Key_long=0;}else{s3Key_long_cnt=0;s3Key_long=0;}
    if(s4Key_dat==0xFF){if(s4Key_press==0){s4Key_press=1;}s4Key_long_cnt++;
        if(s4Key_long_cnt>KEY_LONG_TIMER){s4Key_long=1;s4Key_press=0;}}else if(s4Key_dat==0x00){if(s4Key_press){s4Key_press=0;s4Key_press_cnt++;}s4Key_press=0;s4Key_long_cnt=0;s4Key_long=0;}else{s4Key_long_cnt=0;s4Key_long=0;}
        
    if(s1Key_long&&((s1Key_long_cnt-KEY_LONG_TIMER)%KEY_LONG_INTERVAL)==0){Key_value=Key_value|(KEY_VALUE_S1<<KEY_TYPE_LONG);}
    if(s2Key_long&&((s2Key_long_cnt-KEY_LONG_TIMER)%KEY_LONG_INTERVAL)==0){Key_value=Key_value|(KEY_VALUE_S2<<KEY_TYPE_LONG);}
    if(s3Key_long&&((s3Key_long_cnt-KEY_LONG_TIMER)%KEY_LONG_INTERVAL)==0){Key_value=Key_value|(KEY_VALUE_S3<<KEY_TYPE_LONG);}
    if(s4Key_long&&((s4Key_long_cnt-KEY_LONG_TIMER)%KEY_LONG_INTERVAL)==0){Key_value=Key_value|(KEY_VALUE_S4<<KEY_TYPE_LONG);}
    
    if(s1Key_press_cnt>0){
        s1Key_cnt++;}else{s1Key_cnt=0;}
    if(s2Key_press_cnt>0){s2Key_cnt++;}else{s2Key_cnt=0;}
    if(s3Key_press_cnt>0){s3Key_cnt++;}else{s3Key_cnt=0;}
    if(s4Key_press_cnt>0){s4Key_cnt++;}else{s4Key_cnt=0;}
    if(s1Key_cnt>=KEY_DOUBLE_TIMER){if(s1Key_press_cnt==1){Key_value=Key_value|(KEY_VALUE_S1<<KEY_TYPE_CLICK);}
        else if(s1Key_press_cnt>1){Key_value=Key_value|(KEY_VALUE_S1<<KEY_TYPEDOUBLE);}s1Key_cnt=0;s1Key_press_cnt=0;}    
    if(s2Key_cnt>=KEY_DOUBLE_TIMER){if(s2Key_press_cnt==1){Key_value=Key_value|(KEY_VALUE_S2<<KEY_TYPE_CLICK);}
        else if(s2Key_press_cnt>1){Key_value=Key_value|(KEY_VALUE_S2<<KEY_TYPEDOUBLE);}s2Key_cnt=0;s2Key_press_cnt=0;} 
    if(s3Key_cnt>=KEY_DOUBLE_TIMER){if(s3Key_press_cnt==1){Key_value=Key_value|(KEY_VALUE_S3<<KEY_TYPE_CLICK);}
        else if(s3Key_press_cnt>1){Key_value=Key_value|(KEY_VALUE_S3<<KEY_TYPEDOUBLE);}s3Key_cnt=0;s3Key_press_cnt=0;} 
    if(s4Key_cnt>=KEY_DOUBLE_TIMER){if(s4Key_press_cnt==1){Key_value=Key_value|(KEY_VALUE_S4<<KEY_TYPE_CLICK);}
        else if(s4Key_press_cnt>1){Key_value=Key_value|(KEY_VALUE_S4<<KEY_TYPEDOUBLE);}s4Key_cnt=0;s4Key_press_cnt=0;} 
}


void SeparateKey_Init()
{
    GPIO_Inilize(KEY_S1_GPIO,KEY_S1_PIN,GPIO_OUT_PP);
    GPIO_Inilize(KEY_S2_GPIO,KEY_S2_PIN,GPIO_OUT_PP);
    GPIO_Inilize(KEY_S3_GPIO,KEY_S3_PIN,GPIO_OUT_PP);
    GPIO_Inilize(KEY_S4_GPIO,KEY_S4_PIN,GPIO_OUT_PP);
    delay_add_hook(SeparateKey_Hook);
}

bit SeparateKey_GetValue(uint16_t *value)
{
    if(Key_value)
    {
        *value = Key_value;
        Key_value = 0x000;
        return 1;
    }
    return 0;
}