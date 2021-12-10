/*
 * rot.c
 *
 *  Created on: 24 de nov de 2021
 *      Author: SOPA_
 */

#include "rot.h"

/*
 * 	Função de inicialização
 */
void rot_Init(void)
{
	rot.constante = 0.6;			/* < Salva a constante para calculo da rotação do motor */
	rot.htim = &htim1;				/* < Salva o ponteiro do Timer que será utilizado */
	rot.channel = TIM_CHANNEL_1;	/* < Salva o channel a ser utilizado */

    	indutivo_Init(&rot);			/* < Chama função de inicialização */
}

/*
 * 	Função de reset
 */
void rot_Reset(void)
{
	indutivo_reset(&rot);
}

/*
 * 	Função de calculo
 */
void rot_Calc(void)
{
	indutivo_calc(&rot);
	//LDEBUG;
}
