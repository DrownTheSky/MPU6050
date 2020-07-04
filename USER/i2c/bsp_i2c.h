#ifndef			__BSP_I2C_H
#define			__BSP_I2C_H

#include "stm32f4xx.h"


#define     I2CX_GPIO_CLK            RCC_AHB1Periph_GPIOB
#define     I2CX_GPIO_AF             GPIO_AF_I2C1
#define     I2CX_GPIO_SCL_PORT       GPIOB
#define     I2CX_GPIO_SCL_PIN        GPIO_Pin_6
#define     I2CX_GPIO_SCL_SOURCE     GPIO_PinSource6
#define     I2CX_GPIO_SDA_PORT       GPIOB
#define     I2CX_GPIO_SDA_PIN        GPIO_Pin_7
#define     I2CX_GPIO_SDA_SOURCE     GPIO_PinSource7
#define     I2CX                     I2C1
#define     I2CX_CLK                 RCC_APB1Periph_I2C1
#define     I2CX_SPEED               400000
#define     I2CX_OWNADDR             0x0A


#define     EEPROM_ADDR              0xA0            //0x50<<1

void I2Cx_init(void);
void I2Cx_WriteByte(uint8_t Equipaddr, uint8_t Writeaddr, uint8_t Data);
uint8_t I2Cx_ReadByte(uint8_t Equipaddr,uint8_t Readaddr);


#endif			/* __BSP_I2C_H */

