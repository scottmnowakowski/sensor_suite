#ifndef I2C1_H
#define I2C1_H

void I2C1_Init();
void I2C1_ReadReg(uint8_t addr, uint8_t reg, uint8_t size, uint8_t *buf);
void I2C1_WriteReg(uint8_t addr, uint8_t reg, uint8_t size, uint8_t *buf);

#endif
