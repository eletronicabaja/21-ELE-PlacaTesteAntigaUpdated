/*
 * dina.h
 *
 *  Created on: 29 de nov de 2021
 *      Author: SOPA_
 */

#ifndef INC_DINA_H_
#define INC_DINA_H_

#include "forceGauge.h"

UART_HandleTypeDef huart1;

fGauge_HandleTypeDef dina;

void dina_Init(void);
void dina_Update(void);

#endif /* INC_DINA_H_ */
