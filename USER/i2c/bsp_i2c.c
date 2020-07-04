#include "./i2c/bsp_i2c.h"

void I2Cx_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    I2C_InitTypeDef I2C_InitStruct;

    RCC_AHB1PeriphClockCmd(I2CX_GPIO_CLK,ENABLE);
    RCC_APB1PeriphClockCmd(I2CX_CLK,ENABLE);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;

    GPIO_PinAFConfig(I2CX_GPIO_SCL_PORT,I2CX_GPIO_SCL_SOURCE,I2CX_GPIO_AF);
    GPIO_InitStruct.GPIO_Pin = I2CX_GPIO_SCL_PIN;
    GPIO_Init(I2CX_GPIO_SCL_PORT,&GPIO_InitStruct);

    GPIO_PinAFConfig(I2CX_GPIO_SDA_PORT,I2CX_GPIO_SDA_SOURCE,I2CX_GPIO_AF);
    GPIO_InitStruct.GPIO_Pin = I2CX_GPIO_SDA_PIN;
    GPIO_Init(I2CX_GPIO_SDA_PORT,&GPIO_InitStruct);

    I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStruct.I2C_ClockSpeed = I2CX_SPEED;
    I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStruct.I2C_OwnAddress1 = I2CX_OWNADDR;
    I2C_Init(I2CX,&I2C_InitStruct);

    I2C_Cmd(I2CX,ENABLE);
}

void I2Cx_WriteByte(uint8_t Equipaddr, uint8_t Writeaddr, uint8_t Data)
{
    I2C_GenerateSTART(I2CX,ENABLE);

    while(!I2C_CheckEvent(I2CX,I2C_EVENT_MASTER_MODE_SELECT));//EV5

    I2C_Send7bitAddress(I2CX,Equipaddr,I2C_Direction_Transmitter);

    while(!I2C_CheckEvent(I2CX,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

    I2C_SendData(I2CX,Writeaddr);

    while(!I2C_CheckEvent(I2CX,I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    I2C_SendData(I2CX,Data);

    while(!I2C_CheckEvent(I2CX,I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    I2C_GenerateSTOP(I2CX,ENABLE);
}

uint8_t I2Cx_ReadByte(uint8_t Equipaddr,uint8_t Readaddr)
{
    uint8_t value = 0;

    I2C_GenerateSTART(I2CX,ENABLE);

    while(!I2C_CheckEvent(I2CX,I2C_EVENT_MASTER_MODE_SELECT));

    I2C_Send7bitAddress(I2CX,Equipaddr,I2C_Direction_Transmitter);

    while(!I2C_CheckEvent(I2CX,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

    I2C_SendData(I2CX,Readaddr);

    while(!I2C_CheckEvent(I2CX,I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    I2C_GenerateSTART(I2CX,ENABLE);

    while(!I2C_CheckEvent(I2CX,I2C_EVENT_MASTER_MODE_SELECT));

    I2C_Send7bitAddress(I2CX,Equipaddr,I2C_Direction_Receiver);

    while(!I2C_CheckEvent(I2CX,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

    I2C_AcknowledgeConfig(I2CX,DISABLE);

    while(!I2C_CheckEvent(I2CX,I2C_EVENT_MASTER_BYTE_RECEIVED));

    value = I2C_ReceiveData(I2CX);

    I2C_GenerateSTOP(I2CX,ENABLE);
		
		return value;
}

