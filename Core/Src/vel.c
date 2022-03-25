/*
 * vel.c
 *
 *  Created on: 26 de nov de 2021
 *      Author: SOPA_
 */

#include "vel.h"

/*
 * 	Função de inicialização
 */
void vel_Init(void)
{
	vel.constante = 1.65179;			/* < Salva a constante para calculo da velocidade */
	vel.htim = &htim2;				/* < Salva o ponteiro do Timer que será utilizado */
	vel.channel = TIM_CHANNEL_1;	/* < Salva o channel a ser utilizado */

	indutivo_Init(&vel);			/* < Chama função de inicialização */
}

/*
 * 	Função de reset
 */
void vel_Reset(void)
{
	indutivo_reset(&vel);
}

/*
 * 	Função de calculo
 */
void vel_Calc(void)
{
	indutivo_calc(&vel);
}
