/*
 * dina.c
 *
 *  Created on: 29 de nov de 2021
 *      Author: SOPA_
 */

#include "dina.h"

void dina_Init(void)
{
	dina.huart = &huart2;
	forceGauge_uart_Init_DMA(&dina);
}

void dina_Update(void)
{
	forceGauge_getForce(&dina);
}
