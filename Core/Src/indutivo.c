/*
 * indutivo.c
 *
 *  Created on: 24 de nov de 2021
 *      Author: SOPA_
 */

#include "indutivo.h"

HAL_StatusTypeDef indutivo_Init(indutivo_typedef *hindutivo)
{
	HAL_StatusTypeDef result;

	hindutivo->value_raw = 0;
	hindutivo->freq = 0;
	hindutivo->count = 0;

	result = HAL_TIM_Base_Start_IT(hindutivo->htim);
	result = HAL_TIM_IC_Start_IT(hindutivo->htim, hindutivo->channel);

	return result;
}

void indutivo_filtro(indutivo_typedef *hindutivo)
{
	hindutivo->value = 0;

	if (hindutivo->value_raw > 9999)
		hindutivo->value_raw = hindutivo->buf[4];

	for (int i = 0; i < 4; i++)
		hindutivo->buf[i] = hindutivo->buf[i+1];

	hindutivo->buf[4] = hindutivo->value_raw;

	for (int i = 0; i < 5; i++)
		hindutivo->value += hindutivo->buf[i];

	hindutivo->value = (int)hindutivo->value/5.0;
}

void indutivo_calc(indutivo_typedef *hindutivo)
{
	hindutivo->count += __HAL_TIM_GET_COMPARE(hindutivo->htim, hindutivo->channel);
	__HAL_TIM_SET_COUNTER(hindutivo->htim, 0);
	hindutivo->freq = (int)(100000000.0 / hindutivo->count);
	hindutivo->value_raw = (int)(hindutivo->constante*hindutivo->freq);
	indutivo_filtro(hindutivo);
	hindutivo->count = 0;
}

void indutivo_reset(indutivo_typedef *hindutivo)
{
	if(hindutivo->count<1000000)
	{
		hindutivo->count+=50000;
	}
	else
	{
		hindutivo->freq=0;
		hindutivo->value_raw=0;
		indutivo_filtro(hindutivo);
	}
}


