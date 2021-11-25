/*
 * indutivo.h
 *
 *  Created on: 24 de nov de 2021
 *      Author: SOPA_
 */

/*
	==HEADER PARA APLICAÇÃO DOS SENSORES INDUTIVOS E DE ROTAÇÃO==

	Arquivos que acompanham:
	-indutivo.c

 */

#ifndef INC_INDUTIVO_H_
#define INC_INDUTIVO_H_

#include "main.h"

/*
 * 	Cria Struct Handler para as variaveis
 */
typedef struct
{
	float constante;			/* < Constante que será usada nos calculos do valor */
	int value;					/* < Velocidade/Rotação */
	int value_raw;				/* < Valor pre-filtro */
	int count;					/* < Contador que salva intervalo de tempo */
	int freq;					/* < Frequencia calculada, usada no calculo da variavel  */
	int buf[5];					/* < Buffer para o filtro */
	TIM_HandleTypeDef *htim;	/* < Ponteiro pro timer a ser utilizado */
	uint32_t channel;			/* < Identifador do channel da interrupção */
}indutivo_typedef;

HAL_StatusTypeDef indutivo_Init(indutivo_typedef *hindutivo);
void indutivo_filtro(indutivo_typedef *hindutivo);
void indutivo_calc(indutivo_typedef *hindutivo);
void indutivo_reset(indutivo_typedef *hindutivo);

#endif /* INC_INDUTIVO_H_ */
