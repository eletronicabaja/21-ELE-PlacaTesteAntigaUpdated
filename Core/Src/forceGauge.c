/*
 * forceGauge.c
 *
 *  Created on: 25 de nov de 2021
 *      Author: SOPA_
 */


#include <forceGauge.h>

void forceGauge_uart_Init_DMA(UART_HandleTypeDef *huart)
{
	forceGauge.huart = huart;
}

void forceGauge_getForce(void)
{
	int force = 0;

	if (forceGauge.rxbuffer[14] >=48 && forceGauge.rxbuffer[14] <= 57)
	{
		force += (forceGauge.rxbuffer[14] - 48) * 1;
		force += (forceGauge.rxbuffer[13] - 48) * 10;
		force += (forceGauge.rxbuffer[12] - 48) * 100;
		force += (forceGauge.rxbuffer[11] - 48) * 1000;
		force += (forceGauge.rxbuffer[10] - 48) * 10000;
		force += (forceGauge.rxbuffer[9] - 48) * 100000;
		force += (forceGauge.rxbuffer[8] - 48) * 1000000;
		force += (forceGauge.rxbuffer[7] - 48) * 10000000;
	}
	if (forceGauge.huart->hdmatx->State != HAL_DMA_STATE_BUSY)
		forceGauge.result = HAL_UART_Receive_DMA(forceGauge.huart, forceGauge.rxbuffer, 16);

	forceGauge.force = force;
}

