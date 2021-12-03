/*
 * ace_gir.c
 *
 *  Created on: Dec 3, 2021
 *      Author: SOPA_
 */

#include "ace_gir.h"

void aceGir_Init(I2C_HandleTypeDef *htim)
{

	aceGir.hi2c = htim;

	uint8_t check;
	uint8_t dados;

	// checar se o módulo está conectado
	HAL_I2C_Mem_Read (aceGir.hi2c, MPU6050_ADDR,WHO_AM_I_REG,1, &check, 1, 1000);

	if (check == 104)  // 0x68 = 104 -> será retornado seu o modulo estiver OK
	{
		// ligar sensor
		dados = 0;
		HAL_I2C_Mem_Write(aceGir.hi2c, MPU6050_ADDR, PWR_MGMT_1_REG, 1,&dados, 1, 1000);

		// definir frequencia de 1khz
		dados = 0x07;
		HAL_I2C_Mem_Write(aceGir.hi2c, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &dados, 1, 1000);

		// definir configuracao de acelerometro
		dados = 0x00;
		HAL_I2C_Mem_Write(aceGir.hi2c, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &dados, 1, 1000);

		// definir configuracao de giroscopio
		dados = 0x00;
		HAL_I2C_Mem_Write(aceGir.hi2c, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &dados, 1, 1000);
	}
}

void aceGir_Read(void)
{
	uint8_t buf[6];

	/*	Leitura do Acelerometro	*/
	HAL_I2C_Mem_Read (aceGir.hi2c, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, buf, 6, 1000);

	aceGir.Accel_X_RAW = (int16_t)(buf[0] << 8 | buf [1]);
	aceGir.Accel_Y_RAW = (int16_t)(buf[2] << 8 | buf [3]);
	aceGir.Accel_Z_RAW = (int16_t)(buf[4] << 8 | buf [5]);

	//converter valores em 'g', dividindo por 16384 (FS_SEL)=0
	aceGir.Ax = aceGir.Accel_X_RAW/16384.0;
	aceGir.Ay = aceGir.Accel_Y_RAW/16384.0;
	aceGir.Az = aceGir.Accel_Z_RAW/16384.0;

	/*	Leitura do Giroscopio	*/
	HAL_I2C_Mem_Read (aceGir.hi2c, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, buf, 6, 1000);

	aceGir.Gyro_X_RAW = (int16_t)(buf[0] << 8 | buf [1]);
	aceGir.Gyro_Y_RAW = (int16_t)(buf[2] << 8 | buf [3]);
	aceGir.Gyro_Z_RAW = (int16_t)(buf[4] << 8 | buf [5]);

	//converter valores em 'graus/segundo', dividindo por 131 (FS_SEL)=0
	aceGir.Gx = aceGir.Gyro_X_RAW/131.0;
	aceGir.Gy = aceGir.Gyro_Y_RAW/131.0;
	aceGir.Gz = aceGir.Gyro_Z_RAW/131.0;
}
