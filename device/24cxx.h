#ifndef __24CXXX_H_
#define __24CXXX_H_
#include	"config.h"

enum  eepromtype  {M2401,M2402,M2404,M2408,M2416,M2432,M2464,M24128,M24256};



#define  ERRORCOUNT 10
#define  readI2C  0xa1
#define  writeI2C 0xa0   

bit   RW24XX(unsigned char *DataBuff,unsigned char ByteQuantity,unsigned int Address,
                     unsigned char ControlByte,enum eepromtype EepromType);
void test_24c01();
#endif
