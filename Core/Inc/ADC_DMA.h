/*
 *
 *
 *  Created on: Aug 17, 2021
 *      Author: SOPA_
 */

/*

 */

#ifndef INC_ADC_DMA_H_
#define INC_ADC_DMA_H_

#include "main.h"

#define ADC_BUF_SIZE 2 //Variavel pro tamanho do buffer que salva a leitura analogica

ADC_HandleTypeDef hadc1;

struct ADC_DMA_typedef
{
	uint16_t buffer[ADC_BUF_SIZE];
} analog;

void ADC_DMA_Init(void);

#endif /* INC_ADC_DMA_H_ */
