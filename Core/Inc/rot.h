/*
 * rot.h
 *
 *  Created on: 24 de nov de 2021
 *      Author: SOPA_
 */

#ifndef INC_ROT_H_
#define INC_ROT_H_

#include "indutivo.h"

TIM_HandleTypeDef htim1;

indutivo_typedef rot;

void rot_Init(void);
void rot_Reset(void);
void rot_Calc(void);

#endif /* INC_ROT_H_ */
