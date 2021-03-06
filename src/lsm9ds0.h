#ifndef LSM9DS0_H
#define LSM9DS0_H

#include <stdint.h>

// Scaling macro
#define scale(value, max)   ((float)value*(max/(float)SHRT_MAX))

// Data scaling constants
#define MAX_ACC             ((float)2)      // +- 2 g
#define MAX_MAG             ((float)2)      // +- 2 gauss
#define MAX_ROT             ((float)245)    // +- 245 dps

// Register config
#define CTRL_REG1_G_CFG     ((uint8_t)0x0F)     // DR = 00, BW = 00, PD = 1, Zen = 1, Yen = 1, Xen = 1
#define CTRL_REG1_XM_CFG    ((uint8_t)0x97)     // AODR = 1001 (800Hz), BDU = 0, AZEN = 1, AYEN = 1, AXEN = 1
#define CTRL_REG5_XM_CFG    ((uint8_t)0x10)     // TEMP_EN = 0, M_RES = 00, M_ODR = 100 (50Hz), LIR2 = 0, LIR1 = 0
#define CTRL_REG7_XM_CFG    ((uint8_t)0x04)     // AHPM = 00, AFDS = 0, MLP = 1, MD = 00

// I2C Addresses
#define I2C_ADDR_G          ((uint8_t)0xD7)
#define I2C_ADDR_XM         ((uint8_t)0x3B)

// Gyroscope registers
#define WHO_AM_I_G          ((uint8_t)0x0F)
#define CTRL_REG1_G         ((uint8_t)0x20)
#define CTRL_REG2_G         ((uint8_t)0x21)
#define CTRL_REG3_G         ((uint8_t)0x22)
#define CTRL_REG4_G         ((uint8_t)0x23)
#define CTRL_REG5_G         ((uint8_t)0x24)
#define REFERENCE_G         ((uint8_t)0x25)
#define STATUS_REG_G        ((uint8_t)0x27)
#define OUT_X_L_G           ((uint8_t)0x28)
#define OUT_X_H_G           ((uint8_t)0x29)
#define OUT_Y_L_G           ((uint8_t)0x2a)
#define OUT_Y_H_G           ((uint8_t)0x2b)
#define OUT_Z_L_G           ((uint8_t)0x2c)
#define OUT_Z_H_G           ((uint8_t)0x2d)
#define FIFO_CTRL_REG_G     ((uint8_t)0x2e)
#define FIFO_SRC_REG_G      ((uint8_t)0x2f)
#define INT1_CFG_G          ((uint8_t)0x30)
#define INT1_SRC_G          ((uint8_t)0x31)
#define INT1_TSH_XH_G       ((uint8_t)0x32)
#define INT1_TSH_XL_G       ((uint8_t)0x33)
#define INT1_TSH_YH_G       ((uint8_t)0x34)
#define INT1_TSH_YL_G       ((uint8_t)0x35)
#define INT1_TSH_ZH_G       ((uint8_t)0x36)
#define INT1_TSH_ZL_G       ((uint8_t)0x37)
#define INT1_DURATION_G     ((uint8_t)0x38)

// Accelerometer/magnetometer registers
#define OUT_TEMP_L_XM       ((uint8_t)0x05)
#define OUT_TEMP_H_XM       ((uint8_t)0x06)
#define STATUS_REG_M        ((uint8_t)0x07)
#define OUT_X_L_M           ((uint8_t)0x08)
#define OUT_X_H_M           ((uint8_t)0x09)
#define OUT_Y_L_M           ((uint8_t)0x0a)
#define OUT_Y_H_M           ((uint8_t)0x0b)
#define OUT_Z_L_M           ((uint8_t)0x0c)
#define OUT_Z_H_M           ((uint8_t)0x0d)
#define WHO_AM_I_XM         ((uint8_t)0x0f)
#define INT_CTRL_REG_M      ((uint8_t)0x12)
#define INT_SRC_REG_M       ((uint8_t)0x13)
#define INT_THS_L_M         ((uint8_t)0x14)
#define INT_THS_H_M         ((uint8_t)0x15)
#define OFFSET_X_L_M        ((uint8_t)0x16)
#define OFFSET_X_H_M        ((uint8_t)0x17)
#define OFFSET_Y_L_M        ((uint8_t)0x18)
#define OFFSET_Y_H_M        ((uint8_t)0x19)
#define OFFSET_Z_L_M        ((uint8_t)0x1a)
#define OFFSET_Z_H_M        ((uint8_t)0x1b)
#define REFERENCE_X         ((uint8_t)0x1c)
#define REFERENCE_Y         ((uint8_t)0x1d)
#define REFERENCE_Z         ((uint8_t)0x1e)
#define CTRL_REG0_XM        ((uint8_t)0x1f)
#define CTRL_REG1_XM        ((uint8_t)0x20)
#define CTRL_REG2_XM        ((uint8_t)0x21)
#define CTRL_REG3_XM        ((uint8_t)0x22)
#define CTRL_REG4_XM        ((uint8_t)0x23)
#define CTRL_REG5_XM        ((uint8_t)0x24)
#define CTRL_REG6_XM        ((uint8_t)0x25)
#define CTRL_REG7_XM        ((uint8_t)0x26)
#define STATUS_REG_A        ((uint8_t)0x27)
#define OUT_X_L_A           ((uint8_t)0x28)
#define OUT_X_H_A           ((uint8_t)0x29)
#define OUT_Y_L_A           ((uint8_t)0x2a)
#define OUT_Y_H_A           ((uint8_t)0x2b)
#define OUT_Z_L_A           ((uint8_t)0x2c)
#define OUT_Z_H_A           ((uint8_t)0x2d)
#define FIFO_CTRL_REG       ((uint8_t)0x2e)
#define FIFO_SRC_REG        ((uint8_t)0x2f)
#define INT_GEN_1_REG       ((uint8_t)0x30)
#define INT_GEN_1_SRC       ((uint8_t)0x31)
#define INT_GEN_1_THS       ((uint8_t)0x32)
#define INT_GEN_1_DURATION  ((uint8_t)0x33)
#define INT_GEN_2_REG       ((uint8_t)0x34)
#define INT_GEN_2_SRC       ((uint8_t)0x35)
#define INT_GEN_2_THS       ((uint8_t)0x36)
#define INT_GEN_2_DURATION  ((uint8_t)0x37)
#define CLICK_CFG           ((uint8_t)0x38)
#define CLICK_SRC           ((uint8_t)0x39)
#define CLICK_THS           ((uint8_t)0x3a)
#define TIME_LIMIT          ((uint8_t)0x3b)
#define TIME_LATENCY        ((uint8_t)0x3c)
#define TIME_WINDOW         ((uint8_t)0x3d)
#define Act_THS             ((uint8_t)0x3e)
#define Act_DUR             ((uint8_t)0x3f)

typedef struct
{
    int16_t X_Acc;
    int16_t Y_Acc;
    int16_t Z_Acc;
    int16_t X_Rot;
    int16_t Y_Rot;
    int16_t Z_Rot;
    int16_t X_Mag;
    int16_t Y_Mag;
    int16_t Z_Mag;
}Raw_IMU_Data;

typedef struct
{
    float X_Acc;
    float Y_Acc;
    float Z_Acc;
    float X_Rot;
    float Y_Rot;
    float Z_Rot;
    float X_Mag;
    float Y_Mag;
    float Z_Mag;
}IMU_Data;

void LSM9DS0_Init();
void LSM9DS0_Read(Raw_IMU_Data *rawdata);
void LSM9DS0_Scale(Raw_IMU_Data *rawdata, IMU_Data *data);

#endif
