#include "stm32f4xx.h"

void I2C1_Init()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);   // Enable I2C1 clock
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);  // Enable GPIOB clock for SDA and SCL pins

    /* Connect PB6 to I2C1_SCL*/
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);
    /* Connect PB7 to I2C1_SDA*/
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);

    GPIO_InitTypeDef gpio;
    gpio.GPIO_OType = GPIO_OType_OD;
    gpio.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio.GPIO_Mode  = GPIO_Mode_AF;
    gpio.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &gpio);

    I2C_InitTypeDef InitParams;
    I2C_StructInit(&InitParams); // Initialize with default values
    InitParams.I2C_ClockSpeed = 100000;
    InitParams.I2C_Mode = I2C_Mode_I2C;
    InitParams.I2C_Ack = I2C_Ack_Enable;
    InitParams.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;

    I2C_Init(I2C1, &InitParams);
    I2C_Cmd(I2C1, ENABLE);
}

void I2C1_ReadReg(uint8_t addr, uint8_t reg, uint8_t size, uint8_t *buf)
{
    uint8_t bytenum;
    I2C_AcknowledgeConfig(I2C1, ENABLE);
    I2C_GenerateSTART(I2C1, ENABLE);
    ErrorStatus status = ERROR;
    while (status == ERROR)
    {
        status = I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT);
    }
    I2C_GenerateSTART(I2C1, DISABLE);

    I2C_Send7bitAddress(I2C1, addr, I2C_Direction_Transmitter);
    status = ERROR;
    while (status == ERROR)
    {
        status = I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);
    }

    I2C_SendData(I2C1, reg | 0x80); // Set msb to enable auto-increment
    status = ERROR;
    while (status == ERROR)
    {
        status = I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED);
    }

    I2C_GenerateSTART(I2C1, ENABLE);
    status = ERROR;
    while (status == ERROR)
    {
        status = I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT);
    }
    I2C_GenerateSTART(I2C1, DISABLE);

    if (size == 1)
    {
        // There is a buffer of 2 bytes, so if size == 1 we need to disable ack now
        I2C_AcknowledgeConfig(I2C1, DISABLE);
    }
    I2C_Send7bitAddress(I2C1, addr, I2C_Direction_Receiver);
    status = ERROR;
    while (status == ERROR)
    {
        status = I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);
    }

    for (bytenum = 0; bytenum < size; bytenum++)
    {
        if (bytenum == size-1)
        {
            I2C_AcknowledgeConfig(I2C1, DISABLE);
        }
        status = ERROR;
        while (status == ERROR)
        {
            status = I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED);
        }
        buf[bytenum] = I2C_ReceiveData(I2C1);
    }
    I2C_GenerateSTOP(I2C1, ENABLE);
    return;
}

void I2C1_WriteReg(uint8_t addr, uint8_t reg, uint8_t size, uint8_t *buf)
{
    uint8_t bytenum;
    I2C_AcknowledgeConfig(I2C1, ENABLE);
    I2C_GenerateSTART(I2C1, ENABLE);
    ErrorStatus status = ERROR;
    while (status == ERROR)
    {
        status = I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT);
    }
    I2C_GenerateSTART(I2C1, DISABLE);

    I2C_Send7bitAddress(I2C1, addr, I2C_Direction_Transmitter);
    status = ERROR;
    while (status == ERROR)
    {
        status = I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);
    }

    I2C_SendData(I2C1, reg | 0x80); // Set msb to enable auto-increment
    status = ERROR;
    while (status == ERROR)
    {
        status = I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING);
    }

    for (bytenum = 0; bytenum < size; bytenum++)
    {
        I2C_SendData(I2C1, buf[bytenum]);
        status = ERROR;
        while (status == ERROR)
        {
            status = I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING);
        }
    }
    I2C_GenerateSTOP(I2C1, ENABLE);
}
