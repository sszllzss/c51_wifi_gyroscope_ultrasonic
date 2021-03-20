#ifndef _LED_H_
#include	"config.h"
#define LED_GPIO GPIO_P5
#define LED_PIN GPIO_Pin_5
#define LED_LEVEL 1
void Led_init();
bit Led_Start(uint16_t period,uint16_t on_tick,uint16_t off_tick);
bit Led_Update(uint16_t on_tick,uint16_t off_tick);
void Led_Stop();
#endif