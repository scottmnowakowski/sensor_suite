#include "lsm9ds0.h"
#include "stm32f4xx.h"
#include "I2C1.h"

void LSM9DS0_Init()
{
    // Non interrupt related config
    uint8_t cfg = CTRL_REG1_G_CFG;
    I2C1_WriteReg(I2C_ADDR_G, CTRL_REG1_G, 1, &cfg);
    cfg = CTRL_REG1_XM_CFG;
    I2C1_WriteReg(I2C_ADDR_XM, CTRL_REG1_XM, 1, &cfg);
    cfg = CTRL_REG5_XM_CFG;
    I2C1_WriteReg(I2C_ADDR_XM, CTRL_REG5_XM, 1, &cfg);
    cfg = CTRL_REG7_XM_CFG;
    I2C1_WriteReg(I2C_ADDR_XM, CTRL_REG7_XM, 1, &cfg);
}
