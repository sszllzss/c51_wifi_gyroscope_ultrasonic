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
#define	PWR_MGMT_2		0x6C	//电源管理
#define	WHO_AM_I		0x75	//IIC地址寄存器(默认数值0x68，只读)

#define INTBP_CFG       0x37
#define INT_EN          0x38
#define USER_CTRL       0x6A
#define FIFO_EN         0x23



#define	SlaveAddress	0xD0	//IIC写入时的地址字节数据，+1为读取




#ifdef USING_MPU6050

void mpu6050_interrupt_cb(uint8_t EXT,uint8_t value)
{
    
}


uint8_t MPU_Set_LPF(uint16_t lpf)
{
    uint8_t dat=0;
    if(lpf>=188) dat=1;
    else if(lpf>=98) dat=2;
    else if(lpf>=42) dat=2;
    else if(lpf>=42) dat=3;
    else if(lpf>=20) dat=4;
    else if(lpf>=10) dat=5;
    else dat=6; 
    return I2C_WriteI2C(SlaveAddress,CONFIG,dat);//设置数字低通滤波器  
}
u8 MPU_Set_Rate(u16 rate)
{
    u8 dat;
    if(rate>1000)rate=1000;
    if(rate<4)rate=4;
    dat=1000/rate-1;
    dat=I2C_WriteI2C(SlaveAddress,SMPLRT_DIV,dat);  //设置数字低通滤波器
    return MPU_Set_LPF(rate/2); //自动设置LPF为采样率的一半
}
uint8_t MPU_Set_Gyro_Fsr(uint8_t fsr)
{
    return I2C_WriteI2C(SlaveAddress,GYRO_CONFIG,fsr<<3);//设置陀螺仪满量程范围
}

uint8_t MPU_Set_Accel_Fsr(uint8_t fsr)
{
    return I2C_WriteI2C(SlaveAddress,ACCEL_CONFIG,fsr<<3);//设置加速度传感器满量程范围
}
//**************************************
//初始化MPU6050
//**************************************
void InitMPU6050(void)
{
    uint8_t res = 0;
    EXTI_InitTypeDef INTx;
    INTx.EXTI_Mode = EXT_MODE_Fall;
    INTx.EXTI_Polity = PolityLow;
    INTx.EXTI_Interrupt = ENABLE;
    INTx.interrupt_cb = mpu6050_interrupt_cb;
    I2C_Init();
    Ext_Inilize(MPU6050_INT,&INTx);
    I2C_WriteI2C(SlaveAddress,PWR_MGMT_1,0X80);//复位MPU6050
    delay_ms(100);
	I2C_WriteI2C(SlaveAddress,PWR_MGMT_1, 0x00);	//解除休眠状态 唤醒MPU6050
    
    I2C_WriteI2C(SlaveAddress,GYRO_CONFIG,3<<3);//设置陀螺仪满量程范围
    MPU_Set_Gyro_Fsr(3);
    //I2C_WriteI2C(SlaveAddress,GYRO_CONFIG, 0x18);
    
    MPU_Set_Accel_Fsr(0);
    //I2C_WriteI2C(SlaveAddress,ACCEL_CONFIG, 0x01);
    
	
    MPU_Set_Rate(50);
	//I2C_WriteI2C(SlaveAddress,CONFIG, 0x06);
    //I2C_WriteI2C(SlaveAddress,SMPLRT_DIV, 0x07);

	I2C_WriteI2C(SlaveAddress,INT_EN,0X00); //关闭所有中断
    I2C_WriteI2C(SlaveAddress,USER_CTRL,0X00);//I2C主模式关闭
    I2C_WriteI2C(SlaveAddress,FIFO_EN,0X00);//关闭FIFO
    I2C_WriteI2C(SlaveAddress,INTBP_CFG,0X80);//INT引脚低电平有效
    
    
    I2C_ReadI2C(SlaveAddress,WHO_AM_I,&res);
    if(res== (SlaveAddress>>1))//器件ID正确
    {
        I2C_WriteI2C(PWR_MGMT_1,0X01);//设置CLKSEL,PLL X 轴为参考
        I2C_WriteI2C(PWR_MGMT_2,0X00);//加速度陀螺仪都工作
        MPU_Set_Rate(50); //设置采样率为50HZ
    }
    else 
    {
        printf("MPU6050 Init Error!\r\n");
        return;
    }
    I2Cdelay_while(10);
    mpu6050_test();
}
//**************************************
//合成数据
//**************************************
int mpu6050_GetData(uint8_t REG_Address)
{
	uint8_t H,L;
	I2C_ReadI2C(SlaveAddress,REG_Address,&H);
    I2Cdelay_while(10);
	I2C_ReadI2C(SlaveAddress,REG_Address+1,&L);
    I2Cdelay_while(10);
	return (H<<8)+L;   //合成数据
}

//**************************************
//显示温度
//**************************************
double mpu6050_GetTemp(void)
{ 
    int16_t	Temperature;
    uint8_t Temp_h,Temp_l;	//温度及高低位数据
	I2C_ReadI2C(SlaveAddress,TEMP_OUT_H,&Temp_h); //读取温度
    I2Cdelay_while(10);
	I2C_ReadI2C(SlaveAddress,TEMP_OUT_L,&Temp_l); //读取温度
    I2Cdelay_while(10);
	Temperature=Temp_h<<8|Temp_l;     //合成温度
    return 36.53 + ((double) (Temperature )) / 340; // 计算出温度
}



//*********************************************************
//测试
//*********************************************************
void mpu6050_test(void)
{ 
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