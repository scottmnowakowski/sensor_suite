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

}

void I2C1_WriteReg(uint8_t addr, uint8_t reg, uint8_t size, uint8_t *buf)
{

}
