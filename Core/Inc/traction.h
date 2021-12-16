/*
 * traction.h
 *
 *  Created on: Dec 15, 2021
 *      Author: SOPA_
 */

#ifndef INC_TRACTION_H_
#define INC_TRACTION_H_

#include "forceGauge.h"

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

struct traction_Handler
{
	fGauge_HandleTypeDef cell1;
	fGauge_HandleTypeDef cell2;
}traction;

void traction_Init(void);
void traction_Update(void);

#endif /* INC_TRACTION_H_ */
