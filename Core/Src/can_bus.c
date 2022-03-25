/*
 * can_bus.c
 *
 *  Created on: Dec 3, 2021
 *      Author: SOPA_
 */

#include "can_bus.h"
#include "ace_gir.h"

void can_bus_Init(void)
{
	HAL_StatusTypeDef result;

	canBus.tx_header.StdId = 				0x000;						//Id Padrão (11Bit)
	canBus.tx_header.ExtId = 				0x000;						//Id Extendido (29Bit, STDID+18)
	canBus.tx_header.IDE = 					CAN_ID_STD;					//Define se está usando id padrão (CAN_ID_STD) ou estendido (CAN_ID_EXT)
	canBus.tx_header.RTR = 					CAN_RTR_DATA;
	canBus.tx_header.DLC = 					1;							//Quantidade de bytes por mensagem (1 a 8)
	canBus.tx_header.TransmitGlobalTime =	DISABLE;

	canBus.filter.FilterIdHigh = 			0x010 << 5;
	canBus.filter.FilterIdLow = 			0x000 << 5;
	canBus.filter.FilterMaskIdHigh = 		0x7F0 << 5;
	canBus.filter.FilterMaskIdLow = 		0x000 << 5;
	canBus.filter.FilterFIFOAssignment = 	CAN_FILTER_FIFO0;
	canBus.filter.FilterBank = 				0;
	canBus.filter.FilterMode = 				CAN_FILTERMODE_IDMASK;
	canBus.filter.FilterScale = 			CAN_FILTERSCALE_32BIT;
	canBus.filter.FilterActivation = 		ENABLE;

	result = HAL_CAN_Start(&hcan);
	result = HAL_CAN_ConfigFilter(&hcan, &canBus.filter);
	result = HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
}

void can_bus_Send(void)
{
	//Envia dados do Giroscopio
	canBus.tx_header.StdId = 0x245;
	canBus.envia[0] = (char) (aceGir.gyro.X_RAW+32768);
	canBus.envia[1] = (char) ((aceGir.gyro.X_RAW+32768) >> 8);
	canBus.envia[2] = (char) (aceGir.gyro.Y_RAW+32768);;
	canBus.envia[3] = (char) ((aceGir.gyro.Y_RAW+32768) >> 8);;
	canBus.envia[4] = (char) (aceGir.gyro.Z_RAW+32768);;
	canBus.envia[5] = (char) ((aceGir.gyro.Z_RAW+32768) >> 8);;
	canBus.envia[6] = 0;
	canBus.envia[7] = 0;
	HAL_CAN_AddTxMessage(&hcan, &canBus.tx_header, canBus.envia, &canBus.tx_mail_box);

	//Envia dados do Acelerometro
	canBus.tx_header.StdId = 0x244;
	canBus.envia[0] = (char) (aceGir.accel.X_RAW+32768);
	canBus.envia[1] = (char) ((aceGir.accel.X_RAW+32768) >> 8);
	canBus.envia[2] = (char) (aceGir.accel.Y_RAW+32768);;
	canBus.envia[3] = (char) ((aceGir.accel.Y_RAW+32768) >> 8);;
	canBus.envia[4] = (char) (aceGir.accel.Z_RAW+32768);;
	canBus.envia[5] = (char) ((aceGir.accel.Z_RAW+32768) >> 8);;
	canBus.envia[6] = 0;
	canBus.envia[7] = 0;
	HAL_CAN_AddTxMessage(&hcan, &canBus.tx_header, canBus.envia, &canBus.tx_mail_box);

	// debug
	canBus.erro = hcan.ErrorCode;
	canBus.count++;
	if (canBus.count % 5 == 0)
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	if (canBus.count>50000)
		canBus.count = 0;
}

void can_bus_Recieve(void)
{
	HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &canBus.rx_header, canBus.recieve);

	if (canBus.rx_header.StdId == 0x010)
	{
		canBus.rx.fuel = (canBus.recieve[4] << 8) + canBus.recieve[5];
		canBus.rx.vel = (canBus.recieve[2] << 8) + canBus.recieve[3];
		canBus.rx.rpm = (canBus.recieve[0] << 8) + canBus.recieve[1];

		if (canBus.rx.vel > 9999)
			canBus.rx.vel = 9999;

		if (canBus.rx.rpm > 9999)
			canBus.rx.rpm = 9999;
	}

	/*if (canBus.rx_header.StdId == 0x244)
	{
		can_rData.accel.x = (canBus.recieve[1] << 8) + canBus.recieve[0];
		can_rData.accel.y = (canBus.recieve[3] << 8) + canBus.recieve[2];
		can_rData.accel.z = (canBus.recieve[5] << 8) + canBus.recieve[4];
	}
	if (canBus.rx_header.StdId == 0x245)
	{
		can_rData.gyro.x = (canBus.recieve[1] << 8) + canBus.recieve[0];
		can_rData.gyro.y = (canBus.recieve[3] << 8) + canBus.recieve[2];
		can_rData.gyro.z = (canBus.recieve[5] << 8) + canBus.recieve[4];
	}*/

	canBus.count=0;
}
