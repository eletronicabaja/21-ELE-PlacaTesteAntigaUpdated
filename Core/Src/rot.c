/*
 * rot.c
 *
 *  Created on: 24 de nov de 2021
 *      Author: SOPA_
 */

#include "rot.h"

void rot_Init(void)
{
	rot.constante = 0.6;
	rot.htim = &htim1;
	rot.channel = TIM_CHANNEL_2;

	indutivo_Init(&rot);
}

void rot_Reset(void)
{
	indutivo_reset(&rot);
}

void rot_Calc(void)
{
	indutivo_calc(&rot);
}
