#include "./mpu6050/mpu6050.h"
#include "./i2c/bsp_i2c.h"
#include "./usart/bsp_usart.h"
#include <math.h>

static void mpu6050_Writebyte(uint8_t Writeaddr, uint8_t Data)
{
    I2Cx_WriteByte(MPU6050_ADDRESS,Writeaddr,Data);
}

static uint8_t mpu6050_Readbyte(uint8_t Writeaddr)
{
    return I2Cx_ReadByte(MPU6050_ADDRESS,Writeaddr);
}

static void mpu6050_exti_init(void)
{
    NVIC_InitTypeDef NVIC_InitStruct;
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;

    RCC_AHB1PeriphClockCmd(MPU6050_INT_GPIO_CLK,ENABLE);
    RCC_APB2PeriphClockCmd(MPU6050_INT_EXTI_CLK,ENABLE);

    NVIC_InitStruct.NVIC_IRQChannel = MPU6050_INT_IRQN;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStruct);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Pin = MPU6050_INT_GPIO_PIN;
    GPIO_Init(MPU6050_INT_GPIO_PORT,&GPIO_InitStruct);

    EXTI_InitStruct.EXTI_Line = MPU6050_INT_GPIO_LINE;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    SYSCFG_EXTILineConfig(MPU6050_INT_GPIO_PORTSOURCE,MPU6050_INT_GPIO_PINSOURCE);
    EXTI_Init(&EXTI_InitStruct);

}

void mpu6050_init(void)
{
    mpu6050_exti_init();
    for(uint32_t value = 0xFFFFF; value > 0; value--);
    if(mpu6050_Readbyte(MPU6050_WHO_AM_I) == 0x68)
    {
        mpu6050_Writebyte(MPU6050_RA_PWR_MGMT_1, 0x00);//解除休眠状态
        mpu6050_Writebyte(MPU6050_RA_SMPLRT_DIV , 0x07);//陀螺仪采样率
        mpu6050_Writebyte(MPU6050_RA_CONFIG , 0x06);	
				mpu6050_Writebyte(MPU6050_INTCONFIG , 0x01);		//中断使能
        mpu6050_Writebyte(MPU6050_RA_ACCEL_CONFIG , 0x01);//配置加速度传感器工作在2G模式
        mpu6050_Writebyte(MPU6050_RA_GYRO_CONFIG, 0x18);//陀螺仪自检及测量范围(不自检，2000deg/s)
        printf("MPU6050 init OK\n");
    }
    else
    {
        printf("MPU6050 init Error\n");
    }
    
}

void mpu6050_ReadAcc(short *AccData)
{
    uint8_t buf[6];
    for(uint8_t i = 0; i < 6; i++)
    {
        buf[i] = mpu6050_Readbyte(MPU6050_ACC_OUT + i);
    }
    AccData[0] = (buf[0] << 8) | buf[1];
    AccData[1] = (buf[2] << 8) | buf[3];
    AccData[2] = (buf[4] << 8) | buf[5];

}

void mpu6050_Acc(float *AccData)
{
    short accdata[3];
    mpu6050_ReadAcc(accdata);
    AccData[0] = accdata[0] * 9.8 / 16384;
    AccData[1] = accdata[1] * 9.8 / 16384;
    AccData[2] = accdata[2] * 9.8 / 16384;
}

void mpu6050_ReadGyro(short *GyroData)
{
    uint8_t buf[6];
    for(uint8_t i = 0; i < 6; i++)
    {
        buf[i] = mpu6050_Readbyte(MPU6050_GYRO_OUT + i);
    }
    GyroData[0] = (buf[0] << 8) | buf[1];
    GyroData[1] = (buf[2] << 8) | buf[3];
    GyroData[2] = (buf[4] << 8) | buf[5];
}

void mpu6050_Gyro(float *GyroData)
{
    short gyrodata[3];
    mpu6050_ReadGyro(gyrodata);
    GyroData[0] = gyrodata[0] / 16.384;
    GyroData[1] = gyrodata[1] / 16.384;
    GyroData[2] = gyrodata[2] / 16.384;
}

//float Acel[3];
//float Gyro[3];
//void MPU6050_INT_IRQHANDLER(void)
//{
//  if(EXTI_GetITStatus(MPU6050_INT_GPIO_LINE) != RESET)
//  {
//		mpu6050_Acc(Acel);
//		printf("AccX = %.3f  AccY = %.3f  AccZ = %.3f\n",Acel[0],Acel[1],Acel[2]);
//		mpu6050_Gyro(Gyro);
//		printf("GyrX = %.3f  GyrY = %.3f  GyrZ = %.3f\n",Gyro[0],Gyro[1],Gyro[2]);

//    EXTI_ClearITPendingBit(MPU6050_INT_GPIO_LINE);
//  }
//}
