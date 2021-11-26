/*
 * vel.h
 *
 *  Created on: 26 de nov de 2021
 *      Author: SOPA_
 */

/*
	==HEADER PARA APLICAÇÃO DO SENSOR DE VELOCIDADE==

	Arquivos que acompanham:
	-vel.c

	Arquivos necessarios:
	-indutivo.h
	-indutivo.c

	INSTRUÇÕES:

	-Inicializar na main.c:

		vel_Init(void);

	-Chamar na interrupção de update do timer:

		if (__HAL_TIM_GET_FLAG(&htimx,TIM_FLAG_UPDATE) != RESET)
			vel_Reset();

	-Chamar na interrupção de leitura do canal do timer:

		if (__HAL_TIM_GET_FLAG(&htimx,TIM_FLAG_CCx) != RESET)
			vel_Calc();

 */

#ifndef INC_VEL_H_
#define INC_VEL_H_

#include "indutivo.h"

TIM_HandleTypeDef htim2;	/* < Declara timer que será utilizado */

indutivo_typedef vel;		/* < Variavel que será utilizada */

void vel_Init(void);
void vel_Reset(void);
void vel_Calc(void);

#endif /* INC_VEL_H_ */
