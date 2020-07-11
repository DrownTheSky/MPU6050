#include "stm32f4xx.h"
#include "./usart/bsp_usart.h"
#include "./i2c/bsp_i2c.h"
#include "mpu6050.h"
#include "imu.h"

int main(void)
{
	
	USART_init();
	I2C_Config();
	MPU6050_Init();
	
	while(1)
	{
		/*陀螺仪去零偏*/
		Prepare_Data();  
		/*四元数姿态解算*/
		IMUupdate(&Gyr_rad,&Acc_filt,&MV); 
		printf("MV.yaw = %f  MV.rol = %f  MV.pit = %f\n",MV.yaw,MV.rol,MV.pit);
		
		for(uint32_t i = 0; i < 0xFFFF; i++ );
	}
}

