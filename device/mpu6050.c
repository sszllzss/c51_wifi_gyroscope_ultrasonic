#include "mpu6050.h"
#include "i2c.h"
#include	"delay.h"
#include "stdio.h"
#include "gpio.h"
#include	"exti.h"
//****************************************
// 定义MPU6050内部地址
//****************************************
#define	SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG			0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I		0x75	//IIC地址寄存器(默认数值0x68，只读)

#define	SlaveAddress	0xD0	//IIC写入时的地址字节数据，+1为读取




#ifdef USING_MPU6050

void mpu6050_interrupt_cb(uint8_t EXT,uint8_t value)
{
    
}
//**************************************
//初始化MPU6050
//**************************************
void InitMPU6050(void)
{
    EXTI_InitTypeDef INTx;
    INTx.EXTI_Mode = EXT_MODE_Fall;
    INTx.EXTI_Polity = PolityLow;
    INTx.EXTI_Interrupt = ENABLE;
    INTx.interrupt_cb = mpu6050_interrupt_cb;
    I2C_Init();
    Ext_Inilize(MPU6050_INT,&INTx);
	I2C_WriteI2C(SlaveAddress,PWR_MGMT_1, 0x00);	//解除休眠状态
	I2C_WriteI2C(SlaveAddress,SMPLRT_DIV, 0x07);
	I2C_WriteI2C(SlaveAddress,CONFIG, 0x06);
	I2C_WriteI2C(SlaveAddress,GYRO_CONFIG, 0x18);
	if(I2C_WriteI2C(SlaveAddress,ACCEL_CONFIG, 0x01) == 0)
    {
        printf("MPU6050 Init Error!\r\n");//温度
    }
}
//**************************************
//合成数据
//**************************************
int mpu6050_GetData(uint8_t REG_Address)
{
	uint8_t H,L;
	I2C_ReadI2C(SlaveAddress,REG_Address,&H);
	I2C_ReadI2C(SlaveAddress,REG_Address+1,&L);
	return (H<<8)+L;   //合成数据
}

//**************************************
//显示温度
//**************************************
int mpu6050_GetTemp(void)
{ 
    int	Temperature;
    uint8_t Temp_h,Temp_l;	//温度及高低位数据
	I2C_ReadI2C(SlaveAddress,TEMP_OUT_H,&Temp_h); //读取温度
	I2C_ReadI2C(SlaveAddress,TEMP_OUT_L,&Temp_l); //读取温度
	Temperature=Temp_h<<8|Temp_l;     //合成温度
	Temperature = 35+ ((double) (Temperature + 13200)) / 280; // 计算出温度
    return Temperature;
}



//*********************************************************
//测试
//*********************************************************
void mpu6050_test(void)
{ 
	delay_ms(150);
    printf("mpu:%ld,%ld,%ld,%ld,%ld,%ld\r\n",
    mpu6050_GetData(ACCEL_XOUT_H),//显示X轴加速度
    mpu6050_GetData(ACCEL_YOUT_H),//显示Y轴加速度
    mpu6050_GetData(ACCEL_ZOUT_H),//显示Z轴加速度
    mpu6050_GetData(GYRO_XOUT_H),//显示X轴角速度
    mpu6050_GetData(GYRO_YOUT_H),//显示Y轴角速度
    mpu6050_GetData(GYRO_ZOUT_H));//显示Z轴角速度
    printf("Temp:%0.1f\r\n",mpu6050_GetTemp());//温度
}



#endif