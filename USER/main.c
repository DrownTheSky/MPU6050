#include "stm32f4xx.h"
#include "./usart/bsp_usart.h"
#include "./i2c/bsp_i2c.h"
#include "./mpu6050/mpu6050.h"

int main(void)
{
	
	USART_init();
	I2Cx_init();
	mpu6050_init();
	
	while(1)
	{
		
	}
}

