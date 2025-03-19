/*
 * trapezoidal_profile.c
 *
 *  Created on: Mar 15, 2025
 *      Author: david
 */

//#include <trapezoidal_profile.h>
extern int arr_des_a[3];
extern int n_steps_a[3];
extern unsigned int arr_start[3];
extern unsigned int arr_max[3];
extern unsigned int acc_rate_a[3];

static int arr_current[3] = { ARR_START_0 - ACCEL_RATE_0, ARR_START_1
		- ACCEL_RATE_1, ARR_START_2 - ACCEL_RATE_2 };

static unsigned int count_rising_edge[3]; //need this to have an artificial CNT reg of the timer slave for each master
unsigned int acc_count[3]; //debug
//int dec_count[3]; //debug

int arr[3]; //debug




/*void TIM_Cmd(TIM_TypeDef *TIMx, FunctionalState NewState) { //to disable the timers

	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE) {

		TIMx->CR1 |= TIM_CR1_CEN;
	} else {

		TIMx->CR1 &= (uint16_t) (~((uint16_t) TIM_CR1_CEN));
	}
}*/





void trapezoidal_func(int k, TIM_HandleTypeDef *htim, TIM_HandleTypeDef *hslave) {

	int cnt = __HAL_TIM_GET_COUNTER(hslave);
	if (cnt >= hslave->Instance->ARR) {
		if (hslave->Instance == TIM3) {
			HAL_TIM_PWM_Stop_IT(htim, TIM_CHANNEL_2);
		}

		HAL_TIM_PWM_Stop_IT(htim, TIM_CHANNEL_1);

		count_rising_edge[k] = 0;
		acc_count[k] = 0;  //debug
		//dec_count[k] = 0; //debug

		htim->Instance->EGR |= TIM_EGR_UG;
		hslave->Instance->EGR |= TIM_EGR_UG;

	} else {

		if (arr_des_a[k] > arr_start[k]) { //arr has to be greater than the arr that starts the motor
			__HAL_TIM_SET_AUTORELOAD(htim, arr_start[k]);
			hslave->Instance->PSC = arr_start[k];
			__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1,
					__HAL_TIM_GET_AUTORELOAD(htim) / 2);

			hslave->Instance->EGR |= TIM_EGR_UG;
			hslave->Instance->CNT = count_rising_edge[k];

		}

		if (arr_des_a[k] < (arr_current[k] - acc_rate_a[k])
				&& cnt <= (int) (n_steps_a[k] * 1 / 2)) { //acceleration phase

			arr_current[k] -= acc_rate_a[k];
			if (arr_current[k] <= arr_max[k])
				arr_current[k] = arr_max[k];

			__HAL_TIM_SET_AUTORELOAD(htim, arr_current[k]);
			hslave->Instance->PSC = arr_current[k];
			__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1,
					__HAL_TIM_GET_AUTORELOAD(htim) / 2);

			hslave->Instance->EGR |= TIM_EGR_UG;
			hslave->Instance->CNT = count_rising_edge[k];

			acc_count[k] += (htim->Instance->PSC + 1); //debug

		}

		else {
			if (arr_des_a[k] >= (arr_current[k] - acc_rate_a[k])
					&& arr_current[k] > arr_des_a[k]
					&& cnt <= (int) (n_steps_a[k] * 1 / 2)) { //constant phase

				__HAL_TIM_SET_AUTORELOAD(htim, arr_des_a[k]);
				hslave->Instance->PSC = arr_des_a[k];
				__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1,
						__HAL_TIM_GET_AUTORELOAD(htim) / 2);

				hslave->Instance->EGR |= TIM_EGR_UG;
				hslave->Instance->CNT = count_rising_edge[k];

			}

			else {

				if (cnt >= (n_steps_a[k] - acc_count[k])) { //deceleration phase
					arr_current[k] += acc_rate_a[k];

					if (arr_current[k] >= (arr_start[k] - acc_rate_a[k]))
						arr_current[k] = arr_start[k];

					__HAL_TIM_SET_AUTORELOAD(htim, arr_current[k]);
					hslave->Instance->PSC = arr_current[k];
					__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1,
							__HAL_TIM_GET_AUTORELOAD(htim) / 2);

					hslave->Instance->EGR |= TIM_EGR_UG;
					hslave->Instance->CNT = count_rising_edge[k];

					//dec_count[k] += 5; //debug

				}

			}

		}
	}

}

//slave callback for trapezoidal profile
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

	/*if (htim->Instance == TIM6) {

	 HAL_GPIO_WritePin(ENDEFF_en_GPIO_Port, ENDEFF_en_Pin, GPIO_PIN_RESET); //disable the end_eff
	 HAL_TIM_Base_Stop_IT(htim);

	 }*/

}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {

	if (htim->Instance == TIM1) {

		count_rising_edge[0] += (htim->Instance->PSC + 1);
		//arr[0] = -(__HAL_TIM_GET_AUTORELOAD(&htim1));  //debug graph
		trapezoidal_func(0, htim, &htim4); //0,1,2 for the tipology of the timer

	}

	if (htim->Instance == TIM2) {

		count_rising_edge[1] += (htim->Instance->PSC + 1);
		//arr[1] = -(__HAL_TIM_GET_AUTORELOAD(htim));  //debug graph
		trapezoidal_func(1, htim, &htim3); //0,1,2 for the tipology of the timer

	}

	if (htim->Instance == TIM8) {

		count_rising_edge[2] += (htim->Instance->PSC + 1);
		//arr[2] = -(__HAL_TIM_GET_AUTORELOAD(htim));  //debug graph
		trapezoidal_func(2, htim, &htim5); //0,1,2 for the tipology of the timer

	}
}

