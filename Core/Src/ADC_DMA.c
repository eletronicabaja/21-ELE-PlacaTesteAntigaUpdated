/*
 * anlgDMA.c
 *
 *  Created on: Aug 17, 2021
 *      Author: SOPA_
 */

#include <ADC_DMA.h>

void ADC_DMA_Init(void)
{
	if (HAL_ADCEx_Calibration_Start(&hadc1) != HAL_OK)
		Error_Handler();
	if (HAL_ADC_Start_DMA(&hadc1, &analog.buffer, ADC_BUF_SIZE) != HAL_OK)
		Error_Handler();
}
