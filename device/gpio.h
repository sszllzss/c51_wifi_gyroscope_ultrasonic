#ifndef __GPIO_H__
#define __GPIO_H__


#include	"config.h"

#define	GPIO_PullUp		0	//����׼˫���
#define	GPIO_HighZ		1	//��������
#define	GPIO_OUT_OD		2	//��©���
#define	GPIO_OUT_PP		3	//�������

#define	GPIO_Pin_0		0x01	//IO���� Px.0
#define	GPIO_Pin_1		0x02	//IO���� Px.1
#define	GPIO_Pin_2		0x04	//IO���� Px.2
#define	GPIO_Pin_3		0x08	//IO���� Px.3
#define	GPIO_Pin_4		0x10	//IO���� Px.4
#define	GPIO_Pin_5		0x20	//IO���� Px.5
#define	GPIO_Pin_6		0x40	//IO���� Px.6
#define	GPIO_Pin_7		0x80	//IO���� Px.7
#define	GPIO_Pin_All	0xFF	//IO��������
	
#define	GPIO_P0			0		//
#define	GPIO_P1			1
#define	GPIO_P2			2
#define	GPIO_P3			3
#define	GPIO_P4			4
#define	GPIO_P5			5
#define	GPIO_P6			6
#define	GPIO_P7			7


uint8_t	GPIO_Inilize(uint8_t GPIO, uint8_t Pin,uint8_t	Mode);
bit	GPIO_ReadPin(uint8_t GPIO, uint8_t pin);
uint8_t	GPIO_Read(uint8_t GPIO);
void GPIO_WritePin(uint8_t GPIO, uint8_t pin,bit dat);
void GPIO_Write(uint8_t GPIO,uint8_t dat);

#endif