#ifndef		__MPU6050_H
#define		__MPU6050_H


#include "stm32f4xx.h"

#define MPU6050_INT_GPIO_CLK             RCC_AHB1Periph_GPIOI
#define MPU6050_INT_GPIO_PORT            GPIOI
#define MPU6050_INT_GPIO_PIN             GPIO_Pin_1
#define MPU6050_INT_GPIO_LINE            EXTI_Line1
#define MPU6050_INT_GPIO_PORTSOURCE      EXTI_PortSourceGPIOI
#define MPU6050_INT_GPIO_PINSOURCE       EXTI_PinSource1
#define MPU6050_INT_EXTI_CLK             RCC_APB2Periph_SYSCFG
#define MPU6050_INT_IRQN                 EXTI1_IRQn
#define MPU6050_INT_IRQHANDLER           EXTI1_IRQHandler

#define MPU6050_ADDRESS             0xD0
#define MPU6050_WHO_AM_I            0x75
#define MPU6050_RA_PWR_MGMT_1       0x6B
#define MPU6050_RA_SMPLRT_DIV       0x19
#define MPU6050_RA_CONFIG           0x1A
#define MPU6050_RA_ACCEL_CONFIG     0x1C
#define MPU6050_RA_GYRO_CONFIG      0x1B
#define MPU6050_INTCONFIG           0x38
#define MPU6050_ACC_OUT             0x3B     //MPU6050加速度数据寄存器地址
#define MPU6050_GYRO_OUT            0x43     //MPU6050陀螺仪数据寄存器地址


void mpu6050_init(void);
void mpu6050_ReadAcc(short *AccData);
void mpu6050_Acc(float *AccData);
void mpu6050_ReadGyro(short *GyroData);
void mpu6050_Gyro(float *GyroData);

#endif		/* __MPU6050_H */


