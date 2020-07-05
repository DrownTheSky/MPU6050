#include "./i2c/bsp_i2c.h"

#if HARD_IIC

void I2C_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    I2C_InitTypeDef I2C_InitStruct;

    RCC_AHB1PeriphClockCmd(I2C_GPIO_CLK, ENABLE);
    RCC_APB1PeriphClockCmd(I2C_CLK, ENABLE);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;

    GPIO_PinAFConfig(I2C_SCL_GPIO_PORT, I2C_SCL_GPIO_SOURCE, I2C_GPIO_AF);
    GPIO_InitStruct.GPIO_Pin = I2C_SCL_GPIO_PIN;
    GPIO_Init(I2C_SCL_GPIO_PORT, &GPIO_InitStruct);

    GPIO_PinAFConfig(I2C_SDA_GPIO_PORT, I2C_SDA_GPIO_SOURCE, I2C_GPIO_AF);
    GPIO_InitStruct.GPIO_Pin = I2C_SDA_GPIO_PIN;
    GPIO_Init(I2C_SDA_GPIO_PORT, &GPIO_InitStruct);

    I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStruct.I2C_ClockSpeed = I2C_SPEED;
    I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStruct.I2C_OwnAddress1 = I2C_OWNADDR;
    I2C_Init(I2CX, &I2C_InitStruct);

    I2C_Cmd(I2CX, ENABLE);
}

void I2C_WriteByte(uint8_t Equipaddr, uint8_t Writeaddr, uint8_t Data)
{
    I2C_GenerateSTART(I2CX, ENABLE);
    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_MODE_SELECT))
        ;
    I2C_Send7bitAddress(I2CX, Equipaddr, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
        ;
    I2C_SendData(I2CX, Writeaddr);
    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;
    I2C_SendData(I2CX, Data);
    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;
    I2C_GenerateSTOP(I2CX, ENABLE);
}

uint8_t I2C_ReadByte(uint8_t Equipaddr, uint8_t Readaddr)
{
    uint8_t value = 0;
    I2C_GenerateSTART(I2CX, ENABLE);
    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_MODE_SELECT))
        ;
    I2C_Send7bitAddress(I2CX, Equipaddr, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
        ;
    I2C_SendData(I2CX, Readaddr);
    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;
    I2C_GenerateSTART(I2CX, ENABLE);
    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_MODE_SELECT))
        ;
    I2C_Send7bitAddress(I2CX, Equipaddr, I2C_Direction_Receiver);
    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
        ;
    I2C_AcknowledgeConfig(I2CX, DISABLE);
    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_BYTE_RECEIVED))
        ;
    value = I2C_ReceiveData(I2CX);
    I2C_GenerateSTOP(I2CX, ENABLE);
    return value;
}

void I2C_WriteBuffer(uint8_t Equipaddr, uint8_t Writeaddr, uint8_t *pDate, uint16_t Num)
{
    I2C_GenerateSTART(I2CX, ENABLE);
    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_MODE_SELECT))
        ;
    I2C_Send7bitAddress(I2CX, Equipaddr, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
        ;
    I2C_SendData(I2CX, Writeaddr);
    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;
    while (Num--)
    {
        I2C_SendData(I2CX, *(pDate++));
        while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
            ;
    }
    I2C_GenerateSTOP(I2CX, ENABLE);
}

void I2C_ReadBuffer(uint8_t Equipaddr, uint8_t Readaddr, uint8_t *pDate, uint16_t Num)
{
    I2C_GenerateSTART(I2CX, ENABLE);
    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_MODE_SELECT))
        ;
    I2C_Send7bitAddress(I2CX, Equipaddr, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
        ;
    I2C_SendData(I2CX, Readaddr);
    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;
    I2C_GenerateSTART(I2CX, ENABLE);
    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_MODE_SELECT))
        ;
    I2C_Send7bitAddress(I2CX, Equipaddr, I2C_Direction_Receiver);
    while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
        ;
    I2C_AcknowledgeConfig(I2CX, ENABLE);
    while (Num--)
    {
        while (!I2C_CheckEvent(I2CX, I2C_EVENT_MASTER_BYTE_RECEIVED))
            ;
        *(pDate++) = I2C_ReceiveData(I2CX);
        if (Num == 1)
        {
            I2C_AcknowledgeConfig(I2CX, DISABLE);
        }
        else
        {
            I2C_AcknowledgeConfig(I2CX, ENABLE);
        }
    }
    I2C_GenerateSTOP(I2CX, ENABLE);
}

#else

void I2C_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_AHB1PeriphClockCmd(I2C_GPIO_CLK, ENABLE);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;

    GPIO_InitStruct.GPIO_Pin = I2C_SCL_GPIO_PIN;
    GPIO_Init(I2C_SCL_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = I2C_SDA_GPIO_PIN;
    GPIO_Init(I2C_SDA_GPIO_PORT, &GPIO_InitStruct);
}

/*　
CPU主频180MHz ，MDK编译环境，1级优化
循环次数为50时，SCL频率 = 333KHz 
循环次数为30时，SCL频率 = 533KHz，  
循环次数为20时，SCL频率 = 727KHz， 
*/
static void I2C_Delay(void)
{
    for (uint8_t i = 0; i < 50; i++)
        ;
}

static void I2C_Start(void)
{
    IIC_SDA_HIGH;
    IIC_SCL_HIGH;
    I2C_Delay();
    IIC_SDA_LOW;
    I2C_Delay();
    IIC_SCL_LOW;
    I2C_Delay();
}

static void I2C_Stop(void)
{
    IIC_SDA_LOW;
    IIC_SCL_HIGH;
    I2C_Delay();
    IIC_SDA_HIGH;
}

static void Send_Byte(uint8_t Value)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        if (Value & 0x80)
        {
            IIC_SDA_HIGH;
        }
        else
        {
            IIC_SDA_LOW;
        }
        I2C_Delay();
        IIC_SCL_HIGH;
        I2C_Delay();
        IIC_SCL_LOW;
        I2C_Delay();
        if (i == 7)
        {
            IIC_SDA_HIGH;
        }
        Value <<= 1;
        I2C_Delay();
    }
}

static uint8_t Receive_Byte(void)
{
    uint8_t Value = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        Value <<= 1;
        IIC_SCL_HIGH;
        I2C_Delay();
        if (IIC_SDA_READ)
        {
            Value++;
        }
        IIC_SCL_LOW;
        I2C_Delay();
    }
    return Value;
}

static void I2C_Wait_Ack(void)
{

    IIC_SDA_HIGH;
    I2C_Delay();
    IIC_SCL_HIGH;
    I2C_Delay();
    while (IIC_SDA_READ)
        ;
    IIC_SCL_LOW;
    I2C_Delay();
}

static void I2C_Ack(void)
{
    IIC_SDA_LOW;
    I2C_Delay();
    IIC_SCL_HIGH;
    I2C_Delay();
    IIC_SCL_LOW;
    I2C_Delay();
    IIC_SDA_HIGH;
}

static void I2C_NoAck(void)
{
    IIC_SDA_HIGH;
    I2C_Delay();
    IIC_SCL_HIGH;
    I2C_Delay();
    IIC_SCL_LOW;
    I2C_Delay();
}

void I2C_WriteByte(uint8_t Equipaddr, uint8_t Writeaddr, uint8_t Data)
{
    I2C_Start();
    Send_Byte(Equipaddr | IIC_WRITE_DIRECTION);
    I2C_Wait_Ack();
    Send_Byte(Writeaddr);
    I2C_Wait_Ack();
    Send_Byte(Data);
    I2C_Wait_Ack();
    I2C_Stop();
}

uint8_t I2C_ReadByte(uint8_t Equipaddr, uint8_t Readaddr)
{
    uint8_t Value;

    I2C_Start();
    Send_Byte(Equipaddr | IIC_WRITE_DIRECTION);
    I2C_Wait_Ack();
    Send_Byte(Readaddr);
    I2C_Wait_Ack();
    I2C_Start();
    Send_Byte(Equipaddr | IIC_READ_DIRECTION);
    I2C_Wait_Ack();
    Value = Receive_Byte();
    I2C_NoAck();
    I2C_Stop();

    return Value;
}

void I2C_WriteBuffer(uint8_t Equipaddr, uint8_t Writeaddr, uint8_t *pDate, uint16_t Num)
{
    I2C_Start();
    Send_Byte(Equipaddr | IIC_WRITE_DIRECTION);
    I2C_Wait_Ack();
    Send_Byte(Writeaddr);
    I2C_Wait_Ack();
    while (Num--)
    {
        Send_Byte(*(pDate++));
        if (Num == 1)
        {
            I2C_NoAck();
        }
        else
        {
            I2C_Ack();
        }
    }
    I2C_Stop();
}

void I2C_ReadBuffer(uint8_t Equipaddr, uint8_t Readaddr, uint8_t *pDate, uint16_t Num)
{
    I2C_Start();
    Send_Byte(Equipaddr | IIC_WRITE_DIRECTION);
    I2C_Wait_Ack();
    Send_Byte(Readaddr);
    I2C_Wait_Ack();
    I2C_Start();
    Send_Byte(Equipaddr | IIC_READ_DIRECTION);
    I2C_Wait_Ack();
    while (Num--)
    {
        *(pDate++) = Receive_Byte();
        if (Num == 1)
        {
            I2C_NoAck();
        }
        else
        {
            I2C_Ack();
        }
    }
    I2C_Stop();
}

#endif
