#ifndef __MPU6050_H_
#define __MPU6050_H_

#include	"config.h"
#define MPU6050_INT EXT_INT0

void  InitMPU6050(void);													//≥ı ºªØMPU6050
int mpu6050_GetData(uint8_t REG_Address);
double mpu6050_GetTemp(void);
void mpu6050_test(void);
#endif