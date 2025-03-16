/*
 * trapezoidal_profile.c
 *
 *  Created on: Mar 15, 2025
 *      Author: david
 */

//#include <trapezoidal_profile.h>

extern int arr_des_a[3];
extern int n_steps_a[3];
int arr_start[3];
int arr_max[3];

static int arr_current[3] = { ARR_START_0 - ACCEL_RATE,
ARR_START_1 - ACCEL_RATE, ARR_START_2 - ACCEL_RATE };

int count_rising_edge[3]; //need this to have an artificial CNT reg of the timer slave for each master
int acc_count; //debug
int dec_count; //debug

// int arr; //debug

void TIM_Cmd(TIM_TypeDef *TIMx, FunctionalState NewState) { //to disable the timers
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

void trapezoidal_func(int k, TIM_HandleTypeDef *htim, TIM_HandleTypeDef *hslave) {

	int cnt = __HAL_TIM_GET_COUNTER(hslave);

	if (arr_des_a[k] > arr_start[k]) { //arr has to be greater than the arr that starts the motor
		__HAL_TIM_SET_AUTORELOAD(htim, arr_start[k]);
		hslave->Instance->PSC = arr_start[k];
		__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1,
				__HAL_TIM_GET_AUTORELOAD(htim)/2);

		hslave->Instance->EGR |= TIM_EGR_UG;
		hslave->Instance->CNT = count_rising_edge[k];

	}

	if (arr_des_a[k] < (arr_current[k] - ACCEL_RATE)
			&& cnt <= (int) (n_steps_a[k] * 1 / 2)) { //acceleration phase

		arr_current[k] -= ACCEL_RATE;
		if (arr_current[k] <= arr_max[k])
			arr_current[k] = arr_max[k];

		__HAL_TIM_SET_AUTORELOAD(htim, arr_current[k]);
		hslave->Instance->PSC = arr_current[k];
		__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1,
				__HAL_TIM_GET_AUTORELOAD(htim)/2);

		hslave->Instance->EGR |= TIM_EGR_UG;
		hslave->Instance->CNT = count_rising_edge[k];

		acc_count += 5; //debug

	}

	else {
		if (arr_des_a[k] >= (arr_current[k] - ACCEL_RATE)
				&& arr_current[k] > arr_des_a[k]
				&& cnt <= (int) (n_steps_a[k] * 1 / 2)) { //constant phase

			__HAL_TIM_SET_AUTORELOAD(htim, arr_des_a[k]);
			hslave->Instance->PSC = arr_des_a[k];
			__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1,
					__HAL_TIM_GET_AUTORELOAD(htim)/2);

			hslave->Instance->EGR |= TIM_EGR_UG;
			hslave->Instance->CNT = count_rising_edge[k];

		}

		else {

			if (cnt >= (int) (n_steps_a[k] - acc_count)) { //deceleration phase
				arr_current[k] += ACCEL_RATE;

				if (arr_current[k] >= (arr_start[k] + ACCEL_RATE))
					arr_current[k] = arr_start[k] - ACCEL_RATE;

				__HAL_TIM_SET_AUTORELOAD(htim, arr_current[k]);
				hslave->Instance->PSC = arr_current[k];
				__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1,
						__HAL_TIM_GET_AUTORELOAD(htim)/2);

				hslave->Instance->EGR |= TIM_EGR_UG;
				hslave->Instance->CNT = count_rising_edge[k];

				dec_count += 5; //debug

			}

		}

	}

}

//slave callback for trapezoidal profile
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM5) {

		if (htim->Instance->CNT >= htim->Instance->ARR) {
			HAL_TIM_PWM_Stop_IT(&htim8, TIM_CHANNEL_1);
			count_rising_edge[2] = 0;
			//acc_count = 0;  //debug
			//dec_count = 0; //debug
			htim->Instance->EGR |= TIM_EGR_UG;  //reset
			htim8.Instance->EGR |= TIM_EGR_UG;

			TIM_Cmd(htim->Instance, DISABLE); //disable the slave timer
			TIM_Cmd(htim8.Instance, DISABLE); //disable the slave timer

		}

	}

	if (htim->Instance == TIM3) {
		if (htim->Instance->CNT >= htim->Instance->ARR) {
			HAL_TIM_PWM_Stop_IT(&htim2, TIM_CHANNEL_1);
			HAL_TIM_PWM_Stop_IT(&htim2, TIM_CHANNEL_2);
			count_rising_edge[1] = 0;
			//acc_count = 0;  //debug
			//dec_count = 0; //debug
			htim->Instance->EGR |= TIM_EGR_UG;  //reset
			htim2.Instance->EGR |= TIM_EGR_UG;

			TIM_Cmd(htim->Instance, DISABLE); //disable the slave timer

		}

	}

	if (htim->Instance == TIM4) {

		if (htim->Instance->CNT >= htim->Instance->ARR) {
			HAL_TIM_PWM_Stop_IT(&htim1, TIM_CHANNEL_1);
			count_rising_edge[0] = 0;
			//acc_count = 0;  //debug
			//dec_count = 0; //debug
			htim->Instance->EGR |= TIM_EGR_UG;  //reset
			htim1.Instance->EGR |= TIM_EGR_UG;

			TIM_Cmd(htim->Instance, DISABLE); //disable the slave timer

		}

	}

}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {

	if (htim->Instance == TIM1) {

		count_rising_edge[0] += (htim->Instance->PSC+1);
		//arr = -(__HAL_TIM_GET_AUTORELOAD(&htim1));  //debug graph
		trapezoidal_func(0, htim, &htim4); //0,1,2 for the tipology of the timer

	}

	if (htim->Instance == TIM2) {

		count_rising_edge[1] += (htim->Instance->PSC+1);
		//arr = -(__HAL_TIM_GET_AUTORELOAD(&htim1));  //debug graph
		trapezoidal_func(1, htim, &htim3); //0,1,2 for the tipology of the timer

	}

	if (htim->Instance == TIM8) {

		count_rising_edge[2] += (htim->Instance->PSC+1);
		//arr = -(__HAL_TIM_GET_AUTORELOAD(&htim1));  //debug graph
		trapezoidal_func(2, htim, &htim5); //0,1,2 for the tipology of the timer

	}
}

