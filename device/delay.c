#include	"delay.h"
#include	"timer.h"

static uint32_t delay_ms_tick_cnt = 0;
static uint16_t delay_TIM_Value = 0;
//========================================================================
// 函数: void  delay_ms(uint8_t ms)
// 描述: 延时函数。
// 参数: ms,要延时的ms数, 这里只支持1~255ms. 自动适应主时钟.
// 返回: none.
// 备注: 
//========================================================================
void  delay_ms_while(uint8_t ms)
{
     unsigned int i;
	 do{
	      i = MAIN_Fosc / 13000;
		  while(--i)	;   //14T per loop
     }while(--ms);
}
void  delay_ms(uint16_t ms)
{
    uint16_t time_bk = Timer_Get_Value(TIM0);
    uint32_t delay_ms_tick_cnt_bk = delay_ms_tick_cnt;
    if(0xFFFFFFFF-delay_ms_tick_cnt_bk <= ms)
    {
        while(delay_ms_tick_cnt<delay_ms_tick_cnt_bk+ms);
    }
    else
    {
        uint32_t while_cnt = ms - (0xFFFFFFFF-delay_ms_tick_cnt);
        while(delay_ms_tick_cnt>delay_ms_tick_cnt_bk);
        while(delay_ms_tick_cnt<while_cnt);
    }
    while(Timer_Get_Value(TIM0)<time_bk);
}
//us 只能是1~999
void  delay_us(uint16_t us)
{
    uint16_t time_bk;
    uint32_t delay_ms_tick_cnt_bk,while_cnt;
    if(us<=0 || us>999) return;
    time_bk = Timer_Get_Value(TIM0);
    delay_ms_tick_cnt_bk = delay_ms_tick_cnt;
    while_cnt =  ((MAIN_Fosc/1000000UL)*us);
    if((MAIN_Fosc/1000) - (time_bk-delay_TIM_Value) >= while_cnt)
    {
        
        while(Timer_Get_Value(TIM0) - time_bk < while_cnt);
    }
    else
    {
        while_cnt = while_cnt - ((MAIN_Fosc/1000) - (time_bk-delay_TIM_Value));
        while(delay_ms_tick_cnt==delay_ms_tick_cnt_bk);
        while(Timer_Get_Value(TIM0) < while_cnt);
    }
}
uint32_t delay_get_tick()
{
    return delay_ms_tick_cnt;
}
static void delay_Timerout_Callback()//1ms进入一次中断
{

    delay_ms_tick_cnt++;
    
}
void delay_init(void)
{
    TIM_InitTypeDef def;
    def.TIM_Mode = TIM_16BitAutoReloadNoMask;//16位自动重装, 不可屏蔽中断
    def.TIM_Polity = PolityHigh;//高优先级
    def.TIM_Interrupt = ENABLE;//打开中断
    def.TIM_ClkSource=TIM_CLOCK_1T;//1T定时器
    def.TIM_ClkOut =  DISABLE;//关闭输出
    def.TIM_Timerout_Callback = delay_Timerout_Callback;
    delay_TIM_Value = def.TIM_Value = 0XFFFF - (MAIN_Fosc/1000);
    def.TIM_Run = ENABLE;//开始运行
    Timer_Inilize(TIM0,&def);
    
}