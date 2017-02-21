#include <stdint.h>
#include <limits.h>
#include "stm32f4xx.h"
#include "lsm9ds0.h"
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

void LSM9DS0_Read(Raw_IMU_Data *rawdata)
{
    I2C1_ReadReg(I2C_ADDR_G, OUT_X_L_G, 6, (uint8_t*)&rawdata->X_Rot); // Read X,Y, and Z rotation
    I2C1_ReadReg(I2C_ADDR_XM, OUT_X_L_M, 6, (uint8_t*)&rawdata->X_Mag);// Read X,Y, and Z magnetic field
    I2C1_ReadReg(I2C_ADDR_XM, OUT_X_L_A, 6, (uint8_t*)&rawdata->X_Acc);// Read X,Y, and Z acceleration
}

void LSM9DS0_Scale(Raw_IMU_Data *rawdata, IMU_Data *data)
{
    data->X_Acc = scale(rawdata->X_Acc, MAX_ACC);
    data->Y_Acc = scale(rawdata->Y_Acc, MAX_ACC);
    data->Z_Acc = scale(rawdata->Z_Acc, MAX_ACC);
    data->X_Rot = scale(rawdata->X_Rot, MAX_ROT);
    data->Y_Rot = scale(rawdata->Y_Rot, MAX_ROT);
    data->Z_Rot = scale(rawdata->Z_Rot, MAX_ROT);
    data->X_Mag = scale(rawdata->X_Mag, MAX_MAG);
    data->Y_Mag = scale(rawdata->Y_Mag, MAX_MAG);
    data->Z_Mag = scale(rawdata->Z_Mag, MAX_MAG);
}
