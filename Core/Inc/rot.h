/*
 * rot.h
 *
 *  Created on: 24 de nov de 2021
 *      Author: SOPA_
 */

/*
	==HEADER PARA APLICAÇÃO DO SENSOR DE ROTAÇÃO==

	Arquivos que acompanham:
	-rot.c

	Arquivos necessarios:
	-indutivo.h
	-indutivo.c

	INSTRUÇÕES:

	-Inicializar na main.c:

		rot_Init(void);

	-Chamar na interrupção de update do timer:

		if (__HAL_TIM_GET_FLAG(&htimx,TIM_FLAG_UPDATE) != RESET)
			rot_Reset();

	-Chamar na interrupção de leitura do canal do timer:

		if (__HAL_TIM_GET_FLAG(&htimx,TIM_FLAG_CCx) != RESET)
			rot_Calc();

 */

#ifndef INC_ROT_H_
#define INC_ROT_H_

#include "indutivo.h"

TIM_HandleTypeDef htim1;	/* < Declara timer que será utilizado */

indutivo_typedef rot;		/* < Variavel que será utilizada */

void rot_Init(void);
void rot_Reset(void);
void rot_Calc(void);

#endif /* INC_ROT_H_ */
