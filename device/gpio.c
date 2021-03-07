#include "gpio.h"




/**
* ��ʼ��IO��.
* @parameter GPIO GPIO��
* @parameter Pin �˿�:GPIO_Pin_All\GPIO_Pin_0~7
* @parameter Mode IOģʽ:GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
* @return ������� 0 �ɹ� 1�ղ�����GPIO���� 1 MODE����
*/
uint8_t	GPIO_Inilize(uint8_t GPIO, uint8_t Pin,uint8_t	Mode)
{
	if(GPIO > GPIO_P7)				return 1;	//�ղ���
	if(Mode > GPIO_OUT_PP)	return 2;	//����
	if(GPIO == GPIO_P0)
	{
		if(Mode == GPIO_PullUp)		P0M1 &= ~Pin,	P0M0 &= ~Pin;	 //����׼˫���
		if(Mode == GPIO_HighZ)		P0M1 |=  Pin,	P0M0 &= ~Pin;	 //��������
		if(Mode == GPIO_OUT_OD)		P0M1 |=  Pin,	P0M0 |=  Pin;	 //��©���
		if(Mode == GPIO_OUT_PP)		P0M1 &= ~Pin,	P0M0 |=  Pin;	 //�������
	}
	else if(GPIO == GPIO_P1)
	{
		if(Mode == GPIO_PullUp)		P1M1 &= ~Pin,	P1M0 &= ~Pin;	 //����׼˫���
		if(Mode == GPIO_HighZ)		P1M1 |=  Pin,	P1M0 &= ~Pin;	 //��������
		if(Mode == GPIO_OUT_OD)		P1M1 |=  Pin,	P1M0 |=  Pin;	 //��©���
		if(Mode == GPIO_OUT_PP)		P1M1 &= ~Pin,	P1M0 |=  Pin;	 //�������
	}
	else if(GPIO == GPIO_P2)
	{
		if(Mode == GPIO_PullUp)		P2M1 &= ~Pin,	P2M0 &= ~Pin;	 //����׼˫���
		if(Mode == GPIO_HighZ)		P2M1 |=  Pin,	P2M0 &= ~Pin;	 //��������
		if(Mode == GPIO_OUT_OD)		P2M1 |=  Pin,	P2M0 |=  Pin;	 //��©���
		if(Mode == GPIO_OUT_PP)		P2M1 &= ~Pin,	P2M0 |=  Pin;	 //�������
	}
	else if(GPIO == GPIO_P3)
	{
		if(Mode == GPIO_PullUp)		P3M1 &= ~Pin,	P3M0 &= ~Pin;	 //����׼˫���
		if(Mode == GPIO_HighZ)		P3M1 |=  Pin,	P3M0 &= ~Pin;	 //��������
		if(Mode == GPIO_OUT_OD)		P3M1 |=  Pin,	P3M0 |=  Pin;	 //��©���
		if(Mode == GPIO_OUT_PP)		P3M1 &= ~Pin,	P3M0 |=  Pin;	 //�������
	}
	else if(GPIO == GPIO_P4)
	{
		if(Mode == GPIO_PullUp)		P4M1 &= ~Pin,	P4M0 &= ~Pin;	 //����׼˫���
		if(Mode == GPIO_HighZ)		P4M1 |=  Pin,	P4M0 &= ~Pin;	 //��������
		if(Mode == GPIO_OUT_OD)		P4M1 |=  Pin,	P4M0 |=  Pin;	 //��©���
		if(Mode == GPIO_OUT_PP)		P4M1 &= ~Pin,	P4M0 |=  Pin;	 //�������
	}
	else if(GPIO == GPIO_P5)
	{
		if(Mode == GPIO_PullUp)		P5M1 &= ~Pin,	P5M0 &= ~Pin;	 //����׼˫���
		if(Mode == GPIO_HighZ)		P5M1 |=  Pin,	P5M0 &= ~Pin;	 //��������
		if(Mode == GPIO_OUT_OD)		P5M1 |=  Pin,	P5M0 |=  Pin;	 //��©���
		if(Mode == GPIO_OUT_PP)		P5M1 &= ~Pin,	P5M0 |=  Pin;	 //�������
	}
	else if(GPIO == GPIO_P6)
	{
		if(Mode == GPIO_PullUp)		P6M1 &= ~Pin,	P6M0 &= ~Pin;	 //����׼˫���
		if(Mode == GPIO_HighZ)		P6M1 |=  Pin,	P6M0 &= ~Pin;	 //��������
		if(Mode == GPIO_OUT_OD)		P6M1 |=  Pin,	P6M0 |=  Pin;	 //��©���
		if(Mode == GPIO_OUT_PP)		P6M1 &= ~Pin,	P6M0 |=  Pin;	 //�������
	}
	else if(GPIO == GPIO_P7)
	{
		if(Mode == GPIO_PullUp)		P7M1 &= ~Pin,	P7M0 &= ~Pin;	 //����׼˫���
		if(Mode == GPIO_HighZ)		P7M1 |=  Pin,	P7M0 &= ~Pin;	 //��������
		if(Mode == GPIO_OUT_OD)		P7M1 |=  Pin,	P7M0 |=  Pin;	 //��©���
		if(Mode == GPIO_OUT_PP)		P7M1 &= ~Pin,	P7M0 |=  Pin;	 //�������
	}
	return 0;	//�ɹ�
}
