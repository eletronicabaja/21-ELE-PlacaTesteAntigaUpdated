/*
 * forceGauge.h
 *
 *  Created on: 25 de nov de 2021
 *      Author: SOPA_
 *
 */

/*
	==HEADER PARA APLICAÇÃO DA CELULA DE CARGA==

	Arquivos que acompanham:
	-forceGauge.c

	INSTRUÇÕES:

	-Inserir na main.c:

		 USER CODE BEGIN 2

		 forceGauge_uart_Init_DMA([PONTEIRO_UART]);

		 USER CODE END 2

		 Exemplo:

		 USER CODE BEGIN 2

		 forceGauge_uart_Init_DMA(&huart2);

		 USER CODE END 2

	 -Chamar no loop da main, numa interrupção ou numa Task:

	 	 forceGauge_getForce();

	-O valor lido é armazenado na variavel 'force' da struct 'forceGauge'
 */




#ifndef INC_FORCEGAUGE_H_
#define INC_FORCEGAUGE_H_

#include "main.h"

/*
 * 	@breif Define struct forceGauge
 */
struct forceGauge
{
	UART_HandleTypeDef *huart;	/*< Handle do UART a ser utilizado */

	uint8_t rxbuffer[16];		/*< Buffer pra recepção UART */

	int force;					/*< Variavel que armazena o valor lido */

	HAL_StatusTypeDef result;	/*< Variavel que armazena retorno de erros das funções */
}forceGauge;

void forceGauge_uart_Init_DMA(UART_HandleTypeDef *huart);
void forceGauge_getForce(void);

#endif /* INC_FORCEGAUGE_H_ */
