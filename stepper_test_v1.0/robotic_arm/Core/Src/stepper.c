#include <stepper.h>

//definisco la struct stepper con i seguenti parametri

void stepper_init(stepper_obj *stp, TIM_HandleTypeDef *pwm_timer,
		TIM_HandleTypeDef *position_timer, float stepper_resolution,
		uint16_t microstep, GPIO_TypeDef *direction_port,
		uint16_t direction_pin) {

	stp->position_timer = position_timer;
	stp->pwm_timer = pwm_timer;
	stp->direction_port = direction_port;
	stp->direction_pin = direction_pin;

	stp->stepper_resolution = stepper_resolution;
	stp->microstep = microstep;
	stp->step_per_rev = 360.0f / stepper_resolution; // 360°/resolution
	stp->step_scale = stp->step_per_rev * microstep;
}



int n_steps; //debug

static int flag_configured_timer2 = 0;

void stepper_move(stepper_obj *stp, direction_str direction, float position,
		float freq) {

	n_steps = stp->step_scale * position / 360.0f; //[n_steps]

	//float freq_steps = stp->step_scale * freq / 360.0f; //[n_steps/s]

	HAL_GPIO_WritePin(stp->direction_port, stp->direction_pin, direction); //DIRECTION

	if (stp->pwm_timer->Instance != TIM2) {

		reset_timers(stp);

		__HAL_TIM_SET_AUTORELOAD(stp->position_timer,
				(n_steps * (stp->pwm_timer->Instance->PSC + 1)) - 1);
		__HAL_TIM_SET_COMPARE(stp->pwm_timer, TIM_CHANNEL_1,
				__HAL_TIM_GET_AUTORELOAD(stp->pwm_timer)/2);

		HAL_TIM_PWM_Start_IT(stp->pwm_timer, TIM_CHANNEL_1); //START PWM

	} else { //set parameters for the timer2 separately cause it has 2 channel
		if (flag_configured_timer2 != 1) { //this cause the second stepper must be equal to the first one
			reset_timers(stp);
			__HAL_TIM_SET_AUTORELOAD(stp->position_timer,
					(n_steps * (stp->pwm_timer->Instance->PSC + 1)) - 1);
			__HAL_TIM_SET_COMPARE(stp->pwm_timer, TIM_CHANNEL_1,
					__HAL_TIM_GET_AUTORELOAD(stp->pwm_timer)/2);
			__HAL_TIM_SET_COMPARE(stp->pwm_timer, TIM_CHANNEL_2,
					__HAL_TIM_GET_AUTORELOAD(stp->pwm_timer)/2);

			HAL_TIM_PWM_Start_IT(stp->pwm_timer, TIM_CHANNEL_1); //START PWM
			HAL_TIM_PWM_Start_IT(stp->pwm_timer, TIM_CHANNEL_2); //START PWM)
		}
		flag_configured_timer2 ^= 1;

	}
}

void reset_timers(stepper_obj *stp) {
	__HAL_TIM_SET_COUNTER(stp->position_timer, 0);
	__HAL_TIM_SET_COUNTER(stp->pwm_timer, 0);
	stp->pwm_timer->Instance->EGR = TIM_EGR_UG; //reset the trigger
	stp->position_timer->Instance->EGR = TIM_EGR_UG; //reset the trigger

}


