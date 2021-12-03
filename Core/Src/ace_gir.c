/*
 * ace_gir.c
 *
 *  Created on: Dec 3, 2021
 *      Author: SOPA_
 */

#include "ace_gir.h"

HAL_StatusTypeDef aceGir_Init(I2C_HandleTypeDef *hi2c)
{

	aceGir.hi2c = hi2c;

	HAL_StatusTypeDef result;
	uint8_t check;
	uint8_t dados;

	// checar se o módulo está conectado
	result = HAL_I2C_Mem_Read (aceGir.hi2c, MPU6050_ADDR,WHO_AM_I_REG,1, &check, 1, 1000);
	if (result != HAL_OK)
		return result;

	if (check == 104)  // 0x68 = 104 -> será retornado seu o modulo estiver OK
	{
		// ligar sensor
		dados = 0;
		result = HAL_I2C_Mem_Write(aceGir.hi2c, MPU6050_ADDR, PWR_MGMT_1_REG, 1,&dados, 1, 1000);
		if (result != HAL_OK)
			return result;

		// definir frequencia de 1khz
		dados = 0x07;
		result = HAL_I2C_Mem_Write(aceGir.hi2c, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &dados, 1, 1000);
		if (result != HAL_OK)
			return result;

		// definir configuracao de acelerometro
		dados = 0x00;
		result = HAL_I2C_Mem_Write(aceGir.hi2c, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &dados, 1, 1000);
		if (result != HAL_OK)
			return result;

		// definir configuracao de giroscopio
		dados = 0x00;
		result = HAL_I2C_Mem_Write(aceGir.hi2c, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &dados, 1, 1000);
		if (result != HAL_OK)
			return result;
	}

	result = HAL_TIM_Base_Start_IT(&htim4);

	return result;
}

HAL_StatusTypeDef aceGir_Read(void)
{
	HAL_StatusTypeDef result;
	uint8_t buf[6];

	/*	Leitura do Acelerometro	*/
	result = HAL_I2C_Mem_Read (aceGir.hi2c, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, buf, 6, 1000);
	if (result != HAL_OK)
		return result;

	aceGir.accel.X_RAW = (int16_t)(buf[0] << 8 | buf [1]);
	aceGir.accel.Y_RAW = (int16_t)(buf[2] << 8 | buf [3]);
	aceGir.accel.Z_RAW = (int16_t)(buf[4] << 8 | buf [5]);

	//converter valores em 'g', dividindo por 16384 (FS_SEL)=0
	aceGir.accel.x = aceGir.accel.X_RAW/16384.0;
	aceGir.accel.y = aceGir.accel.Y_RAW/16384.0;
	aceGir.accel.z = aceGir.accel.Z_RAW/16384.0;

	/*	Leitura do Giroscopio	*/
	result = HAL_I2C_Mem_Read (aceGir.hi2c, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, buf, 6, 1000);
	if (result != HAL_OK)
		return result;

	aceGir.gyro.X_RAW = (int16_t)(buf[0] << 8 | buf [1]);
	aceGir.gyro.Y_RAW = (int16_t)(buf[2] << 8 | buf [3]);
	aceGir.gyro.Z_RAW = (int16_t)(buf[4] << 8 | buf [5]);

	//converter valores em 'graus/segundo', dividindo por 131 (FS_SEL)=0
	aceGir.gyro.x = aceGir.gyro.X_RAW/131.0;
	aceGir.gyro.y = aceGir.gyro.Y_RAW/131.0;
	aceGir.gyro.z = aceGir.gyro.Z_RAW/131.0;



	return result;
}
