#ifndef __SEPARATE_KEY_H__
#define __SEPARATE_KEY_H__
#include	"config.h"
#define KEY_S1_GPIO GPIO_P2
#define KEY_S2_GPIO GPIO_P2
#define KEY_S3_GPIO GPIO_P2
#define KEY_S4_GPIO GPIO_P2
#define KEY_S1_PIN GPIO_Pin_3
#define KEY_S2_PIN GPIO_Pin_4
#define KEY_S3_PIN GPIO_Pin_5
#define KEY_S4_PIN GPIO_Pin_6

#define KEY_LONG_TIMER 2000// 2S 长按触发时间
#define KEY_LONG_INTERVAL 400// 400ms 长按连续触发间隔
#define KEY_DOUBLE_TIMER 400//400ms 双击检测时间


#define KEY_TYPE_CLICK 0
#define KEY_TYPEDOUBLE 4
#define KEY_TYPE_LONG  8

#define KEY_VALUE_S1 0x01
#define KEY_VALUE_S2 0x02
#define KEY_VALUE_S3 0x04
#define KEY_VALUE_S4 0x08





void SeparateKey_Init();
bit SeparateKey_GetValue(uint16_t xdata *value);

#endif