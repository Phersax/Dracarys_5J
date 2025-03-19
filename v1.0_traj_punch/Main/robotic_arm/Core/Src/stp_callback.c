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
		htim8.Instance->EGR |= TIM_EGR_UG;

	}
	if (htim->Instance == TIM3) {
		HAL_TIM_PWM_Stop_IT(&htim2, TIM_CHANNEL_1);
		HAL_TIM_PWM_Stop_IT(&htim2, TIM_CHANNEL_2);
		htim2.Instance->EGR |= TIM_EGR_UG;
	}

	if (htim->Instance == TIM4) {

		HAL_TIM_PWM_Stop_IT(&htim1, TIM_CHANNEL_1);
		htim1.Instance->EGR |= TIM_EGR_UG;

	}

}
