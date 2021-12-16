/*
 * traction.c
 *
 *  Created on: Dec 15, 2021
 *      Author: SOPA_
 */

#include "traction.h"

void traction_Init(void)
{
	traction.cell1.huart = &huart1;
	traction.cell2.huart = &huart2;
	forceGauge_uart_Init_DMA(&traction.cell1);
	forceGauge_uart_Init_DMA(&traction.cell2);
}

void traction_Update(void)
{
	forceGauge_getForce(&traction.cell1);
	forceGauge_getForce(&traction.cell2);
}
