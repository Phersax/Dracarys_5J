/*
 * end_eff_gpio.c
 *
 *  Created on: Mar 16, 2025
 *      Author: david
 */
#include "end_eff_gpio.h"



void end_eff_config(int time,TIM_HandleTypeDef *htim){
	if(time<1){ //0
		HAL_GPIO_TogglePin(ENDEFF_en_GPIO_Port, ENDEFF_en_Pin);
	}
	/*else{

		//__HAL_TIM_SET_PRESCALER(&htim7,1400*time);
		//__HAL_TIM_SET_AUTORELOAD(&htim7,59999);
		//htim7.Instance->EGR |= TIM_EGR_UG;


		//__HAL_TIM_CLEAR_IT(&htim7,TIM_IT_UPDATE);
		HAL_GPIO_WritePin(ENDEFF_en_GPIO_Port, ENDEFF_en_Pin, GPIO_PIN_SET);

		HAL_TIM_Base_Start_IT(htim);

	}*/
}

