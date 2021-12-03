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

TIM_HandleTypeDef htim4;

typedef struct axis_Handle
{
	int16_t X_RAW;
	int16_t Y_RAW;
	int16_t Z_RAW;
	float x,y,z;
}axis_HandleTypedef;

struct aceGir_Handle
{
	I2C_HandleTypeDef *hi2c;
	axis_HandleTypedef accel;
	axis_HandleTypedef gyro;
}aceGir;

HAL_StatusTypeDef aceGir_Init(I2C_HandleTypeDef *htim);
HAL_StatusTypeDef aceGir_Read(void);

#endif /* INC_ACE_GIR_H_ */
