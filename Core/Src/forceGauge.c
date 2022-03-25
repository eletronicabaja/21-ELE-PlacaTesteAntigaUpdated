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
	hfGauge->result = HAL_UART_Receive_DMA(hfGauge->huart, hfGauge->rxbuffer, 16);
}

/*
 * 	Função que lê os valores no buffer e converte a string em um int.
 * 	Essa função tambem detecta se a celula de carga foi desconectada e reinicia a leitura quando possivel.
 */
void forceGauge_getForce(fGauge_HandleTypeDef *hfGauge)
{
	int force = 0;
	int i = 0, j = 7;

	/*	Logica para reiniciar a leitura	*/
	if (hfGauge->huart->hdmarx->State != HAL_DMA_STATE_BUSY)
		hfGauge->result = HAL_UART_Receive_DMA(hfGauge->huart, hfGauge->rxbuffer, 16);

	/*	Conversão string to int	*/
	for (i; i < 15 && hfGauge->rxbuffer[i] != 13 ; i++);
	if (i > 8)
		i -= 8;
	else
		i += 8;
	while(j > 0)
	{
		j--;
		if (i < 15)
			i++;
		else
			i = 0;
		force += (hfGauge->rxbuffer[i] - 48) * pow10(j);
	}

	if (force < 0)
		hfGauge->force = 0;
	else if (force > 99999)
		hfGauge->force = 99999;
	else
		hfGauge->force = force;
}

double pow10(double y)
{
	int value = 1;

	for (int i = 0; i < y; i++)
	{
		value = value * 10;
	}

	return value;
}
