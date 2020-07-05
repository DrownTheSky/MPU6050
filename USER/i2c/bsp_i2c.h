#ifndef __BSP_I2C_H
#define __BSP_I2C_H

#include "stm32f4xx.h"

#define HARD_IIC 1

#define I2C_GPIO_CLK RCC_AHB1Periph_GPIOB
#define I2C_GPIO_AF GPIO_AF_I2C1

#define I2C_SCL_GPIO_PORT GPIOB
#define I2C_SCL_GPIO_PIN GPIO_Pin_6
#define I2C_SCL_GPIO_SOURCE GPIO_PinSource6

#define I2C_SDA_GPIO_PORT GPIOB
#define I2C_SDA_GPIO_PIN GPIO_Pin_7
#define I2C_SDA_GPIO_SOURCE GPIO_PinSource7

#define I2CX I2C1
#define I2C_CLK RCC_APB1Periph_I2C1
#define I2C_SPEED 400000
#define I2C_OWNADDR 0x0A

#define EEPROM_ADDR 0xA0 //0x50<<1

#define IIC_SCL_HIGH GPIO_SetBits(I2C_SCL_GPIO_PORT, I2C_SCL_GPIO_PIN)
#define IIC_SCL_LOW GPIO_ResetBits(I2C_SCL_GPIO_PORT, I2C_SCL_GPIO_PIN)
#define IIC_SDA_HIGH GPIO_SetBits(I2C_SDA_GPIO_PORT, I2C_SDA_GPIO_PIN)
#define IIC_SDA_LOW GPIO_ResetBits(I2C_SDA_GPIO_PORT, I2C_SDA_GPIO_PIN)
#define IIC_SDA_READ GPIO_ReadInputDataBit(I2C_SDA_GPIO_PORT, I2C_SDA_GPIO_PIN)

#define IIC_READ_DIRECTION 0X01
#define IIC_WRITE_DIRECTION 0X00

void I2C_Config(void);
void I2C_WriteByte(uint8_t Equipaddr, uint8_t Writeaddr, uint8_t Data);
uint8_t I2C_ReadByte(uint8_t Equipaddr, uint8_t Readaddr);
void I2C_WriteBuffer(uint8_t Equipaddr, uint8_t Writeaddr,uint8_t *pDate, uint16_t Num);
void I2C_ReadBuffer(uint8_t Equipaddr, uint8_t Readaddr,uint8_t *pDate, uint16_t Num);

#endif /* __BSP_I2C_H */
