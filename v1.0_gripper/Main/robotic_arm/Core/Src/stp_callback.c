/*
 * stp_callback.c
 *
 *  Created on: Mar 15, 2025
 *      Author: david
 */

//disable the pwm when it reaches the n_steps
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

	if (htim->Instance == TIM6) {

		HAL_GPIO_WritePin(ENDEFF1_en_GPIO_Port, ENDEFF1_en_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(ENDEFF2_en_GPIO_Port, ENDEFF2_en_Pin, GPIO_PIN_SET);

		HAL_TIM_Base_Stop_IT(htim);
		htim->Instance->EGR |= TIM_EGR_UG;

	}
}
