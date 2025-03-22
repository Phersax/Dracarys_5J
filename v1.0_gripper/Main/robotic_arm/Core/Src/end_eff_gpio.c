/*
 * end_eff_gpio.c
 *
 *  Created on: Mar 16, 2025
 *      Author: david
 */
#include "end_eff_gpio.h"

void gripper_init(gripper_obj *endeff, TIM_HandleTypeDef *htim) {

	endeff->htim = htim;

}

void gripper_config(gripper_obj *endeff, int func, int time) {

	if (func == 1) { //hold- 00

		HAL_GPIO_WritePin(ENDEFF1_en_GPIO_Port, ENDEFF1_en_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ENDEFF2_en_GPIO_Port, ENDEFF2_en_Pin, GPIO_PIN_SET);
	}
	if (func == 2) { //grip-01

		HAL_GPIO_WritePin(ENDEFF1_en_GPIO_Port, ENDEFF1_en_Pin, GPIO_PIN_RESET);
		GPIO_PinState state = HAL_GPIO_ReadPin(ENDEFF1_en_GPIO_Port,
				ENDEFF1_en_Pin);
		if (state == GPIO_PIN_RESET) {
			HAL_GPIO_WritePin(ENDEFF2_en_GPIO_Port, ENDEFF2_en_Pin,
					GPIO_PIN_SET);
		}

	}
	if (func == 3) { //release-10

		HAL_GPIO_WritePin(ENDEFF2_en_GPIO_Port, ENDEFF2_en_Pin, GPIO_PIN_RESET);
		GPIO_PinState state = HAL_GPIO_ReadPin(ENDEFF2_en_GPIO_Port,
				ENDEFF2_en_Pin);
		if (state == GPIO_PIN_RESET) {
			HAL_GPIO_WritePin(ENDEFF1_en_GPIO_Port, ENDEFF1_en_Pin,
					GPIO_PIN_SET);
		}

	}

	if (func == 4) { //timer

		__HAL_TIM_SET_PRESCALER(endeff->htim, 1400 * time);
		__HAL_TIM_SET_AUTORELOAD(endeff->htim, 59999);
		endeff->htim->Instance->EGR |= TIM_EGR_UG;

		__HAL_TIM_CLEAR_IT(endeff->htim, TIM_IT_UPDATE);
		HAL_TIM_Base_Start_IT(endeff->htim);

	}
	else{
		Error_Handler();
	}
}

