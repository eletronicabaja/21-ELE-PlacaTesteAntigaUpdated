/*
 * ace_gir.h
 *
 *  Created on: Dec 3, 2021
 *      Author: SOPA_
 */

#ifndef INC_ACE_GIR_H_
#define INC_ACE_GIR_H_

#include "main.h"

#define MPU6050_ADDR 0xD0
#define SMPLRT_DIV_REG 0x19
#define GYRO_CONFIG_REG 0x1B
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_XOUT_H_REG 0x3B
#define TEMP_OUT_H_REG 0x41
#define GYRO_XOUT_H_REG 0x43
#define PWR_MGMT_1_REG 0x6B
#define WHO_AM_I_REG 0x75

struct aceGir_Handle
{
	I2C_HandleTypeDef *hi2c;
	int16_t Accel_X_RAW;
	int16_t Accel_Y_RAW;
	int16_t Accel_Z_RAW;
	int16_t Gyro_X_RAW;
	int16_t Gyro_Y_RAW;
	int16_t Gyro_Z_RAW;
	float Ax, Ay, Az, Gx, Gy, Gz;
}aceGir;

void aceGir_Init(void);
void aceGir_Read(void);

#endif /* INC_ACE_GIR_H_ */
