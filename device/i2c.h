#ifndef __I2C_H__
#define __I2C_H__
#include	"config.h"
#define SDA_GPIO GPIO_P3
#define SDA_PIN GPIO_Pin_3
#define SCL_GPIO GPIO_P3
#define SCL_PIN GPIO_Pin_4
void I2CStart(void);
void I2CStop(void);
bit I2CRecAck(void);
void I2CACK(void);
void I2CNoAck(void);
void I2CSendByte(unsigned char sendbyte);
unsigned char I2CReceiveByte(void);
bit I2C_WriteI2C(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t REG_data);
bit I2C_ReadI2C(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t *dat);
void I2Cdelay_while(uint8_t us);
void I2C_Init();
#endif