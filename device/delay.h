
#ifndef	__DELAY_H
#define	__DELAY_H

#include	"config.h"

#ifndef DELAY_TIMER_HOOK_SIZE
#define DELAY_TIMER_HOOK_SIZE 5
#endif

typedef void((*delay_timer_hook_t)(void));

uint32_t delay_get_tick();
void  delay_ms_while(uint8_t ms);
void  delay_ms(uint16_t ms);
void  delay_us(uint16_t us);
void delay_init(void);
int8_t delay_add_hook(delay_timer_hook_t hook);
void delay_del_hook(delay_timer_hook_t hook);
#endif
