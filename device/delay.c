#include	"delay.h"
#include	"timer.h"


static delay_timer_hook_t data timer_hook[DELAY_TIMER_HOOK_SIZE];
static uint8_t data timer_hook_pointer = 0;
static uint32_t data delay_ms_tick_cnt = 0;
static uint16_t data delay_TIM_Value = 0;
//========================================================================
// ����: void  delay_ms(uint8_t ms)
// ����: ��ʱ������
// ����: ms,Ҫ��ʱ��ms��, ����ֻ֧��1~255ms. �Զ���Ӧ��ʱ��.
// ����: none.
// ��ע: 
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
//us ֻ����1~999
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
static void delay_Timerout_Callback()//1ms����һ���ж�
{
    uint8_t i;
    delay_ms_tick_cnt++;
    if(timer_hook_pointer>0)
    {
        for(i=0;i<timer_hook_pointer;i++)
        {
            timer_hook[i]();
        }
    }
    
}
void delay_init(void)
{
    TIM_InitTypeDef def;
    def.TIM_Mode = TIM_16BitAutoReloadNoMask;//16λ�Զ���װ, ���������ж�
    def.TIM_Polity = PolityHigh;//�����ȼ�
    def.TIM_Interrupt = ENABLE;//���ж�
    def.TIM_ClkSource=TIM_CLOCK_1T;//1T��ʱ��
    def.TIM_ClkOut =  DISABLE;//�ر����
    def.TIM_Timerout_Callback = delay_Timerout_Callback;
    delay_TIM_Value = def.TIM_Value = 0XFFFF - (MAIN_Fosc/1000);
    def.TIM_Run = ENABLE;//��ʼ����
    Timer_Inilize(TIM0,&def);
    
}

int8_t delay_add_hook(delay_timer_hook_t hook)
{
    if(timer_hook_pointer<DELAY_TIMER_HOOK_SIZE)
    {
        timer_hook[timer_hook_pointer] = hook;
        timer_hook_pointer++;
        return 0;
    }
    return -1;
}
void delay_del_hook(delay_timer_hook_t hook)
{
    uint8_t i=0;
    if(timer_hook_pointer>0)
    {
        for(i=0;i<timer_hook_pointer;i++)
        {
            if(timer_hook[i] == hook)
            {
                break;
            }
        }
        if(i==timer_hook_pointer)
        {
            return;
        }
        for(;i<timer_hook_pointer-1;i++)
        {
            timer_hook[i] = timer_hook[i+1];

        }
        timer_hook_pointer--;
    }
}

