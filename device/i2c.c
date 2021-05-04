#include <i2c.h>
#include <intrins.h>
#include	"delay.h"
#include "gpio.h"


void  I2Cdelay_while(uint8_t us)
{
     unsigned int i;
	 do{
	      i = MAIN_Fosc / 13000000;
		  while(--i)	;   //14T per loop
     }while(--us);
}


/*****************以下是对I2C总线的操作子程序***/
/*****************启动总线**********************/
void I2CStart(void)
{
    GPIO_WritePin(SCL_GPIO,SCL_PIN,0);                  
    GPIO_WritePin(SDA_GPIO,SDA_PIN,1);
    GPIO_WritePin(SCL_GPIO,SCL_PIN,1);
    I2Cdelay_while(5);
    GPIO_WritePin(SDA_GPIO,SDA_PIN,0);
    I2Cdelay_while(5);
    GPIO_WritePin(SCL_GPIO,SCL_PIN,0);
    GPIO_WritePin(SDA_GPIO,SDA_PIN,1);                  
}

/*****************停止I2C总线****************/
void I2CStop(void)
{
    GPIO_WritePin(SCL_GPIO,SCL_PIN,0); 
    GPIO_WritePin(SDA_GPIO,SDA_PIN,0);
    GPIO_WritePin(SCL_GPIO,SCL_PIN,1); 
    I2Cdelay_while(5);
    GPIO_WritePin(SDA_GPIO,SDA_PIN,1);
    I2Cdelay_while(5);
    GPIO_WritePin(SCL_GPIO,SCL_PIN,0); 
}

/**************检查应答位*******************/
bit I2CRecAck(void)
{
    bit rec;
    GPIO_WritePin(SCL_GPIO,SCL_PIN,0); 
    GPIO_WritePin(SDA_GPIO,SDA_PIN,1);
    GPIO_WritePin(SCL_GPIO,SCL_PIN,1); 
    GPIO_Inilize(SDA_GPIO, SDA_PIN,GPIO_HighZ);
    I2Cdelay_while(5);
    rec=GPIO_ReadPin(SDA_GPIO,SDA_PIN);
    GPIO_Inilize(SDA_GPIO, SDA_PIN,GPIO_PullUp);    
    GPIO_WritePin(SCL_GPIO,SCL_PIN,0); 
    return(rec);
}

/***************对I2C总线产生应答*******************/
void I2CACK(void)
{
    GPIO_WritePin(SDA_GPIO,SDA_PIN,0);
    GPIO_WritePin(SCL_GPIO,SCL_PIN,1); 
    I2Cdelay_while(5);
    GPIO_WritePin(SCL_GPIO,SCL_PIN,0); 
    I2Cdelay_while(1);
    GPIO_WritePin(SDA_GPIO,SDA_PIN,1);
}

/*****************不对I2C总线产生应答***************/
void I2CNoAck(void)
{
    GPIO_WritePin(SDA_GPIO,SDA_PIN,1);
    GPIO_WritePin(SCL_GPIO,SCL_PIN,1);
    I2Cdelay_while(5);
    GPIO_WritePin(SCL_GPIO,SCL_PIN,0);
}


/*******************向I2C总线写数据*********************/
void I2CSendByte(unsigned char sendbyte)
{
    int8_t j;
    for(j=7;j>=0;j--)
    {
       GPIO_WritePin(SCL_GPIO,SCL_PIN,0); 
        
       if(sendbyte&(0x01<<j))
       {
           GPIO_WritePin(SDA_GPIO,SDA_PIN,1);
       }
       else
       {
           GPIO_WritePin(SDA_GPIO,SDA_PIN,0);
       }
       GPIO_WritePin(SCL_GPIO,SCL_PIN,1);
    }
    GPIO_WritePin(SCL_GPIO,SCL_PIN,0);
}

/**********************从I2C总线上读数据子程序**********/
unsigned char I2CReceiveByte(void)
{
    register receivebyte=0,i=8;
    GPIO_Inilize(SDA_GPIO, SDA_PIN,GPIO_HighZ);
    GPIO_WritePin(SCL_GPIO,SCL_PIN,0);
    while(i--)
    {
        GPIO_WritePin(SCL_GPIO,SCL_PIN,1);
       receivebyte=(receivebyte<<1)|GPIO_ReadPin(SDA_GPIO,SDA_PIN);
        GPIO_WritePin(SCL_GPIO,SCL_PIN,0);
    }
    GPIO_Inilize(SDA_GPIO, SDA_PIN,GPIO_PullUp);
    return(receivebyte);
}
//**************************************
//向I2C设备写入一个字节数据
//**************************************
bit I2C_WriteI2C(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t REG_data)
{
    I2CStart();                  //起始信号
    I2CSendByte(SlaveAddress);   //发送设备地址+写信号
    if(I2CRecAck() == 1){I2CStop();return 0;}
    I2CSendByte(REG_Address);    //内部寄存器地址，
    if(I2CRecAck() == 1){I2CStop();return 0;}
    I2CSendByte(REG_data);       //内部寄存器数据，
    if(I2CRecAck() == 1){I2CStop();return 0;}
    I2CStop();                   //发送停止信号
    return 1;
}
//**************************************
//从I2C设备读取一个字节数据
//**************************************
bit I2C_ReadI2C(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t *dat)
{
	uint8_t REG_data;
	I2CStart();                   //起始信号
	I2CSendByte(SlaveAddress);    //发送设备地址+写信号
    if(I2CRecAck() == 1){I2CStop();return 0;}
	I2CSendByte(REG_Address);     //发送存储单元地址，从0开始	
    if(I2CRecAck() == 1){I2CStop();return 0;}
	I2CStart();                   //起始信号
	I2CSendByte(SlaveAddress+1);    //发送设备地址+读信号
    if(I2CRecAck() == 1){I2CStop();return 0;}
	REG_data=I2CReceiveByte();       //读出寄存器数据
	I2CNoAck();//不应答
    I2Cdelay_while(1);
	I2CStop();                    //停止信号
	*dat = REG_data;
    return 1;
}
void I2C_Init()
{
   GPIO_Inilize(SCL_GPIO, SCL_PIN,GPIO_OUT_PP);
   GPIO_Inilize(SDA_GPIO, SDA_PIN,GPIO_PullUp);
   GPIO_WritePin(SDA_GPIO,SDA_PIN,1);
   GPIO_WritePin(SCL_GPIO,SCL_PIN,0); 
}
