#include "24cxx.h"
#include "i2c.h"
#include <intrins.h>
#include	"delay.h"

#ifdef USING_24CXX

//DataBuff为读写数据输入／输出缓冲区的首址
//ByteQuantity 为要读写数据的字节数量
//Address 为EEPROM的片内地址
//ControlByte 为EEPROM的控制字节，具体形式为(1)(0)(1)(0)(A2)(A1)(A0)(R/W),其中R/W=1,
//表示读操作,R/W=0为写操作,A2,A1,A0为EEPROM的页选或片选地址;
//EepromType为枚举变量,需为M2401至M24256中的一种,分别对应24C01至24C256;
//函数返回值为一个位变量，若返回1表示此次操作失效，0表示操作成功;
//ERRORCOUNT为允许最大次数，若出现ERRORCOUNT次操作失效后，则函数中止操作，并返回1
//SDA和SCL由用户自定义，这里暂定义为P0^0和P0^1;
//其余的用户不用管，只要把只子程序放在你的程序中并调用它就可以了;


/*******************************I2C总线驱动**********************************************/
bit   RW24XX(unsigned char *DataBuff,unsigned char ByteQuantity,unsigned int Address,
                     unsigned char ControlByte,enum eepromtype EepromType)
{
    unsigned char data j,i=ERRORCOUNT;
    bit      errorflag=1;
    while(i--)
    {
       I2CStart();
       I2CSendByte(ControlByte&0xfe);
       if(I2CRecAck())
           continue;
       if(EepromType>M2416)
       {
          I2CSendByte((unsigned char)(Address>>8));
          if(I2CRecAck())
             continue;
       }
       I2CSendByte((unsigned char)Address);
       if(I2CRecAck())
           continue;
       if(!(ControlByte&0x01))
       {
          j=ByteQuantity;
          errorflag=0;                      //********clr errorflag
          while(j--)
          {
            I2CSendByte(*DataBuff++);
            if(!I2CRecAck())
               continue;
            errorflag=1;
            break;
          }
          if(errorflag==1)
            continue;
          break;
       }
       else
       {
         I2CStart();
         I2CSendByte(ControlByte);
         if(I2CRecAck())
           continue;
         while(--ByteQuantity)
         {
           *DataBuff++=I2CReceiveByte();
           I2CAck();
         }
         *DataBuff=I2CReceiveByte();        //read last byte data
         I2CNoAck();
         errorflag=0;
         break;
       }
    }

    I2CStop();
    if(!(ControlByte&0x01))
    {
      delay_us(255);
      delay_us(255);
      delay_us(255);
      delay_us(255);
    }
    return(errorflag);
}



void test_24c01()
{

  unsigned char *pa,*pb,temp=0;
  unsigned char a[8]={5,6,7,8,9,10,11,12};
  unsigned char b[8]={0,0,0,0,0,0,0,0};
  pa=&a[0];
  pb=&b[0]; 
  RW24XX(pa,8,0x0,writeI2C,M2401);   
  RW24XX(pa,8,0x20,writeI2C,M2401);  
  RW24XX(pb,8,0x20,readI2C,M2401); 
  RW24XX(pb,8,0x30,writeI2C,M2401); 
//  RW24XX(unsigned char *DataBuff,unsigned char ByteQuantity,unsigned int Address,
//                     unsigned char ControlByte,enum eepromtype EepromType)
}
#endif