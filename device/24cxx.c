#include "24cxx.h"
#include "i2c.h"
#include <intrins.h>
#include	"delay.h"

#ifdef USING_24CXX

//DataBuffΪ��д�������룯�������������ַ
//ByteQuantity ΪҪ��д���ݵ��ֽ�����
//Address ΪEEPROM��Ƭ�ڵ�ַ
//ControlByte ΪEEPROM�Ŀ����ֽڣ�������ʽΪ(1)(0)(1)(0)(A2)(A1)(A0)(R/W),����R/W=1,
//��ʾ������,R/W=0Ϊд����,A2,A1,A0ΪEEPROM��ҳѡ��Ƭѡ��ַ;
//EepromTypeΪö�ٱ���,��ΪM2401��M24256�е�һ��,�ֱ��Ӧ24C01��24C256;
//��������ֵΪһ��λ������������1��ʾ�˴β���ʧЧ��0��ʾ�����ɹ�;
//ERRORCOUNTΪ������������������ERRORCOUNT�β���ʧЧ��������ֹ������������1
//SDA��SCL���û��Զ��壬�����ݶ���ΪP0^0��P0^1;
//������û����ùܣ�ֻҪ��ֻ�ӳ��������ĳ����в��������Ϳ�����;


/*******************************I2C��������**********************************************/
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