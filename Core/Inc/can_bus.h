/*
 * can_bus.h
 *
 *  Created on: Dec 3, 2021
 *      Author: SOPA_
 */

#ifndef INC_CAN_BUS_H_
#define INC_CAN_BUS_H_

#include "main.h"

typedef struct can_bus_Hanle
{
	CAN_HandleTypeDef hcan;
	uint16_t count;
	uint32_t erro;
	uint8_t data_byte;
	CAN_TxHeaderTypeDef tx_header;
	CAN_RxHeaderTypeDef rx_header;
	CAN_FilterTypeDef filter;
	uint32_t tx_mail_box;
	uint8_t envia[8];
	uint8_t recebe[8];
}can_bus_HanleTypedef;

can_bus_HanleTypedef canBus;

void can_bus_Init(void);
void can_bus_Send(void);

#endif /* INC_CAN_BUS_H_ */
