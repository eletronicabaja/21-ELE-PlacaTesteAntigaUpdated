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
	canBus.tx_header.DLC = 8;
	canBus.tx_header.IDE = CAN_ID_STD;
	canBus.tx_header.RTR = CAN_RTR_DATA;
	canBus.tx_header.StdId = 0x243;
	canBus.filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	canBus.filter.FilterMode = CAN_FILTERMODE_IDMASK;
	canBus.filter.FilterBank = 0;
	canBus.filter.FilterIdHigh = 0x120 << 5;
	canBus.filter.FilterIdLow = 0;
	canBus.filter.FilterMaskIdHigh = 0x7fc<<5;
	canBus.filter.FilterMaskIdLow = 0;
	canBus.filter.FilterScale = CAN_FILTERSCALE_32BIT;
	canBus.filter.FilterActivation = ENABLE;

	canBus.count = 0;

	HAL_CAN_ConfigFilter(&canBus.hcan, &canBus.filter);
	HAL_CAN_Start(&canBus.hcan);
	HAL_CAN_ActivateNotification(&canBus.hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
}

void can_bus_Send(void)
{

	//Envia dados do Acelerometro
	canBus.tx_header.StdId = 0x240;
	canBus.envia[0] = (char) (aceGir.accel.X_RAW+32768);
	canBus.envia[1] = (char) ((aceGir.accel.X_RAW+32768) >> 8);
	canBus.envia[2] = (char) (aceGir.accel.Y_RAW+32768);;
	canBus.envia[3] = (char) ((aceGir.accel.Y_RAW+32768) >> 8);;
	canBus.envia[4] = (char) (aceGir.accel.Z_RAW+32768);;
	canBus.envia[5] = (char) ((aceGir.accel.Z_RAW+32768) >> 8);;
	canBus.envia[6] = '0';
	canBus.envia[7] = '0';
	HAL_CAN_AddTxMessage(&canBus.hcan, &canBus.tx_header, canBus.envia, &canBus.tx_mail_box);

	//Envia dados do Giroscopio
	canBus.tx_header.StdId = 0x239;
	canBus.envia[0] = (char) (aceGir.gyro.X_RAW+32768);
	canBus.envia[1] = (char) ((aceGir.gyro.X_RAW+32768) >> 8);
	canBus.envia[2] = (char) (aceGir.gyro.Y_RAW+32768);;
	canBus.envia[3] = (char) ((aceGir.gyro.Y_RAW+32768) >> 8);;
	canBus.envia[4] = (char) (aceGir.gyro.Z_RAW+32768);;
	canBus.envia[5] = (char) ((aceGir.gyro.Z_RAW+32768) >> 8);;
	canBus.envia[6] = '0';
	canBus.envia[7] = '0';
	HAL_CAN_AddTxMessage(&canBus.hcan, &canBus.tx_header, canBus.envia, &canBus.tx_mail_box);

	// debug
	canBus.erro = canBus.hcan.ErrorCode;
	canBus.count++;
	if (canBus.count % 5 == 0)
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	if (canBus.count>50000)
		canBus.count = 0;
}
