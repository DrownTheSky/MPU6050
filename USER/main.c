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
		/*������ȥ��ƫ*/
		Prepare_Data();  
		/*��Ԫ����̬����*/
		IMUupdate(&Gyr_rad,&Acc_filt,&MV); 
		printf("MV.yaw = %f  MV.rol = %f  MV.pit = %f\n",MV.yaw,MV.rol,MV.pit);
		
		for(uint32_t i = 0; i < 0xFFFF; i++ );
	}
}

