/*
 * indutivo.h
 *
 *  Created on: 24 de nov de 2021
 *      Author: SOPA_
 */

#ifndef INC_INDUTIVO_H_
#define INC_INDUTIVO_H_

#include "main.h"

typedef struct
{
	float constante;
	int value;
	int value_raw;
	int count;
	int freq;
	int buf[5];
	TIM_HandleTypeDef *htim;
	uint32_t channel;
}indutivo_typedef;

HAL_StatusTypeDef indutivo_Init(indutivo_typedef *hindutivo);
void indutivo_filtro(indutivo_typedef *hindutivo);
void indutivo_calc(indutivo_typedef *hindutivo);
void indutivo_reset(indutivo_typedef *hindutivo);

#endif /* INC_INDUTIVO_H_ */
