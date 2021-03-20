#include "mpu6050.h"
#include "i2c.h"
#include	"delay.h"
#include "stdio.h"
#include "gpio.h"
#include	"exti.h"
//****************************************
// ����MPU6050�ڲ���ַ
//****************************************
#define	SMPLRT_DIV		0x19	//�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define	CONFIG			0x1A	//��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define	ACCEL_CONFIG	0x1C	//���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
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
#define	PWR_MGMT_1		0x6B	//��Դ��������ֵ��0x00(��������)
#define	WHO_AM_I		0x75	//IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)

#define	SlaveAddress	0xD0	//IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ




#ifdef USING_MPU6050

void mpu6050_interrupt_cb(uint8_t EXT,uint8_t value)
{
    
}
//**************************************
//��ʼ��MPU6050
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
	I2C_WriteI2C(SlaveAddress,PWR_MGMT_1, 0x00);	//�������״̬
	I2C_WriteI2C(SlaveAddress,SMPLRT_DIV, 0x07);
	I2C_WriteI2C(SlaveAddress,CONFIG, 0x06);
	I2C_WriteI2C(SlaveAddress,GYRO_CONFIG, 0x18);
	if(I2C_WriteI2C(SlaveAddress,ACCEL_CONFIG, 0x01) == 0)
    {
        printf("MPU6050 Init Error!\r\n");//�¶�
    }
}
//**************************************
//�ϳ�����
//**************************************
int mpu6050_GetData(uint8_t REG_Address)
{
	uint8_t H,L;
	I2C_ReadI2C(SlaveAddress,REG_Address,&H);
	I2C_ReadI2C(SlaveAddress,REG_Address+1,&L);
	return (H<<8)+L;   //�ϳ�����
}

//**************************************
//��ʾ�¶�
//**************************************
int mpu6050_GetTemp(void)
{ 
    int	Temperature;
    uint8_t Temp_h,Temp_l;	//�¶ȼ��ߵ�λ����
	I2C_ReadI2C(SlaveAddress,TEMP_OUT_H,&Temp_h); //��ȡ�¶�
	I2C_ReadI2C(SlaveAddress,TEMP_OUT_L,&Temp_l); //��ȡ�¶�
	Temperature=Temp_h<<8|Temp_l;     //�ϳ��¶�
	Temperature = 35+ ((double) (Temperature + 13200)) / 280; // ������¶�
    return Temperature;
}



//*********************************************************
//����
//*********************************************************
void mpu6050_test(void)
{ 
	delay_ms(150);
    printf("mpu:%ld,%ld,%ld,%ld,%ld,%ld\r\n",
    mpu6050_GetData(ACCEL_XOUT_H),//��ʾX����ٶ�
    mpu6050_GetData(ACCEL_YOUT_H),//��ʾY����ٶ�
    mpu6050_GetData(ACCEL_ZOUT_H),//��ʾZ����ٶ�
    mpu6050_GetData(GYRO_XOUT_H),//��ʾX����ٶ�
    mpu6050_GetData(GYRO_YOUT_H),//��ʾY����ٶ�
    mpu6050_GetData(GYRO_ZOUT_H));//��ʾZ����ٶ�
    printf("Temp:%0.1f\r\n",mpu6050_GetTemp());//�¶�
}



#endif