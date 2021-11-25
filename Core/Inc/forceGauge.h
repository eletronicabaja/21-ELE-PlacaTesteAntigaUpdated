/*
 * forceGauge.h
 *
 *  Created on: 25 de nov de 2021
 *      Author: SOPA_
 */

#ifndef INC_FORCEGAUGE_H_
#define INC_FORCEGAUGE_H_

#include "main.h"

struct forceGauge
{
	UART_HandleTypeDef *huart;
	uint8_t rxbuffer[16];
	int force;
	HAL_StatusTypeDef result;
}forceGauge;

void forceGauge_uart_Init_DMA(UART_HandleTypeDef *huart);
void forceGauge_getForce(void);

#endif /* INC_FORCEGAUGE_H_ */
