#include "gpio.h"



/**
* 初始化IO口.
* @parameter GPIO GPIO组
* @parameter Pin 端口:GPIO_Pin_All\GPIO_Pin_0~7
* @parameter Mode IO模式:GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
* @return 操作结果 0 成功 1空操作（GPIO错误） 1 MODE错误
*/
uint8_t	GPIO_Inilize(uint8_t GPIO, uint8_t Pin,uint8_t	Mode)
{
	if(GPIO > GPIO_P7)				return 1;	//空操作
	if(Mode > GPIO_OUT_PP)	return 2;	//错误
	if(GPIO == GPIO_P0)
	{
		if(Mode == GPIO_PullUp)		P0M1 &= ~Pin,	P0M0 &= ~Pin;	 //上拉准双向口
		if(Mode == GPIO_HighZ)		P0M1 |=  Pin,	P0M0 &= ~Pin;	 //浮空输入
		if(Mode == GPIO_OUT_OD)		P0M1 |=  Pin,	P0M0 |=  Pin;	 //开漏输出
		if(Mode == GPIO_OUT_PP)		P0M1 &= ~Pin,	P0M0 |=  Pin;	 //推挽输出
	}
	else if(GPIO == GPIO_P1)
	{
		if(Mode == GPIO_PullUp)		P1M1 &= ~Pin,	P1M0 &= ~Pin;	 //上拉准双向口
		if(Mode == GPIO_HighZ)		P1M1 |=  Pin,	P1M0 &= ~Pin;	 //浮空输入
		if(Mode == GPIO_OUT_OD)		P1M1 |=  Pin,	P1M0 |=  Pin;	 //开漏输出
		if(Mode == GPIO_OUT_PP)		P1M1 &= ~Pin,	P1M0 |=  Pin;	 //推挽输出
	}
	else if(GPIO == GPIO_P2)
	{
		if(Mode == GPIO_PullUp)		P2M1 &= ~Pin,	P2M0 &= ~Pin;	 //上拉准双向口
		if(Mode == GPIO_HighZ)		P2M1 |=  Pin,	P2M0 &= ~Pin;	 //浮空输入
		if(Mode == GPIO_OUT_OD)		P2M1 |=  Pin,	P2M0 |=  Pin;	 //开漏输出
		if(Mode == GPIO_OUT_PP)		P2M1 &= ~Pin,	P2M0 |=  Pin;	 //推挽输出
	}
	else if(GPIO == GPIO_P3)
	{
		if(Mode == GPIO_PullUp)		P3M1 &= ~Pin,	P3M0 &= ~Pin;	 //上拉准双向口
		if(Mode == GPIO_HighZ)		P3M1 |=  Pin,	P3M0 &= ~Pin;	 //浮空输入
		if(Mode == GPIO_OUT_OD)		P3M1 |=  Pin,	P3M0 |=  Pin;	 //开漏输出
		if(Mode == GPIO_OUT_PP)		P3M1 &= ~Pin,	P3M0 |=  Pin;	 //推挽输出
	}
	else if(GPIO == GPIO_P4)
	{
		if(Mode == GPIO_PullUp)		P4M1 &= ~Pin,	P4M0 &= ~Pin;	 //上拉准双向口
		if(Mode == GPIO_HighZ)		P4M1 |=  Pin,	P4M0 &= ~Pin;	 //浮空输入
		if(Mode == GPIO_OUT_OD)		P4M1 |=  Pin,	P4M0 |=  Pin;	 //开漏输出
		if(Mode == GPIO_OUT_PP)		P4M1 &= ~Pin,	P4M0 |=  Pin;	 //推挽输出
	}
	else if(GPIO == GPIO_P5)
	{
		if(Mode == GPIO_PullUp)		P5M1 &= ~Pin,	P5M0 &= ~Pin;	 //上拉准双向口
		if(Mode == GPIO_HighZ)		P5M1 |=  Pin,	P5M0 &= ~Pin;	 //浮空输入
		if(Mode == GPIO_OUT_OD)		P5M1 |=  Pin,	P5M0 |=  Pin;	 //开漏输出
		if(Mode == GPIO_OUT_PP)		P5M1 &= ~Pin,	P5M0 |=  Pin;	 //推挽输出
	}
	else if(GPIO == GPIO_P6)
	{
		if(Mode == GPIO_PullUp)		P6M1 &= ~Pin,	P6M0 &= ~Pin;	 //上拉准双向口
		if(Mode == GPIO_HighZ)		P6M1 |=  Pin,	P6M0 &= ~Pin;	 //浮空输入
		if(Mode == GPIO_OUT_OD)		P6M1 |=  Pin,	P6M0 |=  Pin;	 //开漏输出
		if(Mode == GPIO_OUT_PP)		P6M1 &= ~Pin,	P6M0 |=  Pin;	 //推挽输出
	}
	else if(GPIO == GPIO_P7)
	{
		if(Mode == GPIO_PullUp)		P7M1 &= ~Pin,	P7M0 &= ~Pin;	 //上拉准双向口
		if(Mode == GPIO_HighZ)		P7M1 |=  Pin,	P7M0 &= ~Pin;	 //浮空输入
		if(Mode == GPIO_OUT_OD)		P7M1 |=  Pin,	P7M0 |=  Pin;	 //开漏输出
		if(Mode == GPIO_OUT_PP)		P7M1 &= ~Pin,	P7M0 |=  Pin;	 //推挽输出
	}
	return 0;	//成功
}
bit	GPIO_ReadPin(uint8_t GPIO, uint8_t pin)
{
    if(GPIO == GPIO_P0){return (P0&pin);}
    else if(GPIO == GPIO_P1){return (P1&pin)?1:0;}
    else if(GPIO == GPIO_P2){return (P2&pin)?1:0;}
    else if(GPIO == GPIO_P3){return (P3&pin)?1:0;}
    else if(GPIO == GPIO_P4){return (P4&pin)?1:0;}
    else if(GPIO == GPIO_P5){return (P5&pin)?1:0;}
    else if(GPIO == GPIO_P6){return (P6&pin)?1:0;}
    else if(GPIO == GPIO_P7){return (P7&pin)?1:0;}
    return 0;
}
uint8_t	GPIO_Read(uint8_t GPIO)
{
    if(GPIO == GPIO_P0){return P0;}
    else if(GPIO == GPIO_P1){return P1;}
    else if(GPIO == GPIO_P2){return P2;}
    else if(GPIO == GPIO_P3){return P3;}
    else if(GPIO == GPIO_P4){return P4;}
    else if(GPIO == GPIO_P5){return P5;}
    else if(GPIO == GPIO_P6){return P6;}
    else if(GPIO == GPIO_P7){return P7;}
    return 0;
}
void GPIO_WritePin(uint8_t GPIO, uint8_t pin,bit dat)
{
    uint8_t tmp=0x00;
    if(GPIO == GPIO_P0){tmp=P0;tmp=tmp&(~(pin));if(dat)tmp=tmp|(pin);P0=tmp; return;}
    else if(GPIO == GPIO_P1){tmp=P1;tmp=tmp&(~(pin));if(dat)tmp=tmp|(pin);P1=tmp; return;}
    else if(GPIO == GPIO_P2){tmp=P2;tmp=tmp&(~(pin));if(dat)tmp=tmp|(pin);P2=tmp; return;}
    else if(GPIO == GPIO_P3){tmp=P3;tmp=tmp&(~(pin));if(dat)tmp=tmp|(pin);P3=tmp; return;}
    else if(GPIO == GPIO_P4){tmp=P4;tmp=tmp&(~(pin));if(dat)tmp=tmp|(pin);P4=tmp; return;}
    else if(GPIO == GPIO_P5){tmp=P5;tmp=tmp&(~(pin));if(dat)tmp=tmp|(pin);P5=tmp; return;}
    else if(GPIO == GPIO_P6){tmp=P6;tmp=tmp&(~(pin));if(dat)tmp=tmp|(pin);P6=tmp; return;}
    else if(GPIO == GPIO_P7){tmp=P7;tmp=tmp&(~(pin));if(dat)tmp=tmp|(pin);P7=tmp; return;}
    
}
void GPIO_Write(uint8_t GPIO, uint8_t dat)
{
    if(GPIO == GPIO_P0){P0=dat; return;}
    else if(GPIO == GPIO_P1){P1=dat; return;}
    else if(GPIO == GPIO_P2){P2=dat; return;}
    else if(GPIO == GPIO_P3){P3=dat; return;}
    else if(GPIO == GPIO_P4){P4=dat; return;}
    else if(GPIO == GPIO_P5){P5=dat; return;}
    else if(GPIO == GPIO_P6){P6=dat; return;}
    else if(GPIO == GPIO_P7){P7=dat; return;}
}