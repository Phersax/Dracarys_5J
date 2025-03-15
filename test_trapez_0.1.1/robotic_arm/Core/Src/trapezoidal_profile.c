/*
 * trapezoidal_profile.c
 *
 *  Created on: Mar 15, 2025
 *      Author: david
 */

#include <trapezoidal_profile.h>

extern int arr_des;
int arr_current = ARR_START - ACCEL_RATE;
extern int n_steps;

int count;
int acc_count;
int dec_count;
volatile int cnt;
// int arr; //debug

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
			count = 0;
			acc_count = 0;
			dec_count = 0;
			htim4.Instance->EGR |= TIM_EGR_UG;
			htim1.Instance->EGR |= TIM_EGR_UG;

			TIM_Cmd(htim->Instance, DISABLE);

		}

	}

}

void TIM_Cmd(TIM_TypeDef *TIMx, FunctionalState NewState) {
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE) {
		/* Enable the TIM Counter */
		TIMx->CR1 |= TIM_CR1_CEN;
	} else {
		/* Disable the TIM Counter */
		TIMx->CR1 &= (uint16_t) (~((uint16_t) TIM_CR1_CEN));
	}
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {

	if (htim->Instance == TIM1) {
		count += 5;
		cnt = __HAL_TIM_GET_COUNTER(&htim4);
		//arr = -(__HAL_TIM_GET_AUTORELOAD(&htim1));

		if (arr_des > ARR_START) { //arr has to be greater than the arr that starts the motor
			__HAL_TIM_SET_AUTORELOAD(htim, ARR_START);
			htim4.Instance->PSC = ARR_START;
			__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1,
					__HAL_TIM_GET_AUTORELOAD(htim)/2);

			htim4.Instance->EGR |= TIM_EGR_UG;
			htim4.Instance->CNT = count;

		}

		if (arr_des < (arr_current - ACCEL_RATE)
				&& cnt <= (int) (n_steps * 1 / 2)) { //acceleration phase

			arr_current -= ACCEL_RATE;
			if (arr_current <= ARR_MAX)
				arr_current = ARR_MAX;

			__HAL_TIM_SET_AUTORELOAD(htim, arr_current);
			htim4.Instance->PSC = arr_current;
			__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1,
					__HAL_TIM_GET_AUTORELOAD(htim)/2);

			htim4.Instance->EGR |= TIM_EGR_UG;
			htim4.Instance->CNT = count;
			acc_count += 5;

		}

		else {
			if (arr_des >= (arr_current - ACCEL_RATE) && arr_current > arr_des
					&& cnt <= (int) (n_steps * 1 / 2)) { //constant phase

				__HAL_TIM_SET_AUTORELOAD(htim, arr_des);
				htim4.Instance->PSC = arr_des;
				__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1,
						__HAL_TIM_GET_AUTORELOAD(htim)/2);

				htim4.Instance->EGR |= TIM_EGR_UG;
				htim4.Instance->CNT = count;

			}

			else {

				if (cnt >= (int) (n_steps - acc_count)) { //deceleration phase
					arr_current += ACCEL_RATE;

					if (arr_current >= (ARR_START + ACCEL_RATE))
						arr_current = ARR_START - ACCEL_RATE;

					__HAL_TIM_SET_AUTORELOAD(htim, arr_current);
					htim4.Instance->PSC = arr_current;
					__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1,
							__HAL_TIM_GET_AUTORELOAD(htim)/2);

					htim4.Instance->EGR |= TIM_EGR_UG;
					htim4.Instance->CNT = count;

					dec_count += 5;

				}

			}

		}

	}
}

