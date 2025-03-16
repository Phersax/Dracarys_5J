/*
 * stp_callback.c
 *
 *  Created on: Mar 15, 2025
 *      Author: david
 */

//#include "tim.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM5) {
		HAL_TIM_PWM_Stop_IT(&htim8, TIM_CHANNEL_1);

	}
	if (htim->Instance == TIM3) {
		HAL_TIM_PWM_Stop_IT(&htim2, TIM_CHANNEL_1);
		HAL_TIM_PWM_Stop_IT(&htim2, TIM_CHANNEL_2);
	}

	if (htim->Instance == TIM4) {

		if (htim4.Instance->CNT >= htim4.Instance->ARR) {
			HAL_TIM_PWM_Stop_IT(&htim1, TIM_CHANNEL_1);
		}

	}

}
