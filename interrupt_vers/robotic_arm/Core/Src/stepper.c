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

int n_steps_a[3]; //3 pwm timers
int arr_des_a[3];

static int flag_configured_timer2; //for the timer2 config

float freq_des_steps; //DEBUG
static int arr_des = 20000;  //random value

void stepper_move(stepper_obj *stp, direction_str direction, float position,
		float freq_desired) {

	int i = 0;
	int n_steps = stp->step_scale * position / 360.0f; //[n_steps]

	freq_des_steps = stp->step_scale * freq_desired / 360.0f; //[n_steps/s]

	arr_des = (HAL_RCC_GetPCLK2Freq() * 2 / freq_des_steps)
			/ (stp->pwm_timer->Instance->PSC + 1) - 1;

	HAL_GPIO_WritePin(stp->direction_port, stp->direction_pin, direction); //DIRECTION

	if (stp->pwm_timer->Instance != TIM2) {

		//reset_timers(stp);

		__HAL_TIM_SET_AUTORELOAD(stp->position_timer,
				(n_steps * (stp->pwm_timer->Instance->PSC + 1)) - 1);
		__HAL_TIM_SET_COMPARE(stp->pwm_timer, TIM_CHANNEL_1,
				__HAL_TIM_GET_AUTORELOAD(stp->pwm_timer)/2);

		HAL_TIM_PWM_Start_IT(stp->pwm_timer, TIM_CHANNEL_1); //START PWM

	} else { //set parameters for the timer2 separately cause it has 2 channel
		if (flag_configured_timer2 != 1) { //this cause the second stepper must be equal to the first one

			//reset_timers(stp);
			__HAL_TIM_SET_AUTORELOAD(stp->position_timer,
					(n_steps * (stp->pwm_timer->Instance->PSC + 1)) - 1);
			__HAL_TIM_SET_COMPARE(stp->pwm_timer, TIM_CHANNEL_1,
					__HAL_TIM_GET_AUTORELOAD(stp->pwm_timer)/2);

			__HAL_TIM_SET_COMPARE(stp->pwm_timer, TIM_CHANNEL_2,
					__HAL_TIM_GET_AUTORELOAD(stp->pwm_timer)/2);
			HAL_TIM_PWM_Start_IT(stp->pwm_timer, TIM_CHANNEL_1); //START PWM
						HAL_TIM_PWM_Start_IT(stp->pwm_timer, TIM_CHANNEL_2); //START PWM)

		} else {


		}
		flag_configured_timer2 ^= 1;

	}
	n_steps = n_steps * (stp->pwm_timer->Instance->PSC + 1);

	if (stp->pwm_timer->Instance == TIM1) {
		i = 0;
	} else {
		if (stp->pwm_timer->Instance == TIM2) {
			i = 1;
		} else
			i = 2;
	}
	n_steps_a[i] = n_steps;
	arr_des_a[i] = arr_des;

}

void reset_timers(stepper_obj *stp) {

	stp->pwm_timer->Instance->EGR = TIM_EGR_UG; //reset the trigger
	//stp->position_timer->Instance->EGR = TIM_EGR_UG; //reset the trigger

}

