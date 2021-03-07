
#ifndef	__DELAY_H
#define	__DELAY_H

#include	"config.h"
uint32_t delay_get_tick();
void  delay_ms_while(uint8_t ms);
void  delay_ms(uint16_t ms);
void  delay_us(uint16_t us);
void delay_init(void);
#endif
