/*
 * forceGauge.c
 *
 *  Created on: 25 de nov de 2021
 *      Author: SOPA_
 */


#include <forceGauge.h>

/*
 *	Função que inicia a leitura
 */
void forceGauge_uart_Init_DMA(fGauge_HandleTypeDef *hfGauge)
{
	//hfGauge->result = HAL_UART_Init(hfGauge->huart);
	hfGauge->result = HAL_UART_Receive_DMA(hfGauge->huart, hfGauge->rxbuffer, 16);
}

/*
 * 	Função que lê os valores no buffer e converte a string em um int.
 * 	Essa função tambem detecta se a celula de carga foi desconectada e reinicia a leitura quando possivel.
 */
void forceGauge_getForce(fGauge_HandleTypeDef *hfGauge)
{
	int force = 0;

	/*	Logica para reiniciar a leitura	*/
	if (hfGauge->huart->hdmatx->State != HAL_DMA_STATE_BUSY)
		hfGauge->result = HAL_UART_Receive_DMA(hfGauge->huart, hfGauge->rxbuffer, 16);
	//hfGauge->result = HAL_UART_Receive(hfGauge->huart, hfGauge->rxbuffer, 16, 10000);

	/*	Conversão string to int	*/
	if (hfGauge->rxbuffer[14] >=48 && hfGauge->rxbuffer[14] <= 57)
	{
		force += (hfGauge->rxbuffer[14] - 48) * 1;
		force += (hfGauge->rxbuffer[13] - 48) * 10;
		force += (hfGauge->rxbuffer[12] - 48) * 100;
		force += (hfGauge->rxbuffer[11] - 48) * 1000;
		force += (hfGauge->rxbuffer[10] - 48) * 10000;
		force += (hfGauge->rxbuffer[9] - 48) * 100000;
		force += (hfGauge->rxbuffer[8] - 48) * 1000000;
		force += (hfGauge->rxbuffer[7] - 48) * 10000000;
	}

	hfGauge->force = force;
}

