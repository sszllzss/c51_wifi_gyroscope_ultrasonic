#include "led.h"
#include "gpio.h"
#include "delay.h"
static uint16_t xdata led_cnt = 0;
static uint16_t xdata led_period = 0;
static uint16_t xdata led_on_tick = 0;
static uint16_t xdata led_off_tick = 0;
static void LED_Hook()//1ms
{
    if(led_period>0)
    {
        led_cnt++;
        if(led_cnt >= led_on_tick && led_cnt < led_off_tick)
        {
            GPIO_WritePin(LED_GPIO,LED_PIN,LED_LEVEL);
        }
        else if(led_cnt >= led_off_tick && led_cnt < led_period)
        {
            GPIO_WritePin(LED_GPIO,LED_PIN,!LED_LEVEL);
        }
        else if(led_cnt >= led_period)
        {
            led_cnt = 0;
        }
    }
}
void Led_init()
{
    GPIO_Inilize(LED_GPIO,LED_PIN,GPIO_OUT_PP);
    GPIO_WritePin(LED_GPIO,LED_PIN,!LED_LEVEL);
    delay_add_hook(LED_Hook);
}
bit Led_Start(uint16_t period,uint16_t on_tick,uint16_t off_tick)
{
    if(period<on_tick||period<off_tick)
        return 0;
    led_cnt = 0;
    led_period = period;led_on_tick = on_tick;led_off_tick = off_tick;
    return 1;
}
bit Led_Update(uint16_t on_tick,uint16_t off_tick)
{
    if(led_period<on_tick||led_period<off_tick)
        return 0;
    led_on_tick = on_tick;led_off_tick = off_tick;
    return 1;
}
void Led_Stop()
{
    led_period = 0;
    GPIO_WritePin(LED_GPIO,LED_PIN,!LED_LEVEL);
}