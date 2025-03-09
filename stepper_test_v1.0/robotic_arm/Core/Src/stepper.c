#include <stepper.h>

extern TIM_HandleTypeDef htim3;

//definisco l'oggetto stepper con i seguenti parametri

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

void stepper_move(stepper_obj *stp, direction_str direction, float position,
		float freq) {

	n_steps = stp->step_scale * position / 360.0f; //[n_steps]

	//float freq_steps = stp->step_scale * freq / 360.0f; //[n_steps/s]

	//trapezoidal_profile(freq_steps, position);

	HAL_GPIO_WritePin(stp->direction_port, stp->direction_pin, direction); //DIRECTION

	//set arr of timer-slave for the position step count
	__HAL_TIM_SET_AUTORELOAD(stp->position_timer, (n_steps * stp->pwm_timer->Init.Prescaler) - 1);
	reset_timers(stp);

}

void reset_timers(stepper_obj *stp) {
	__HAL_TIM_SET_COUNTER(stp->position_timer, 0);
	__HAL_TIM_SET_COUNTER(stp->pwm_timer, 0);
	stp->pwm_timer->Instance->EGR = TIM_EGR_UG; //reset the trigger
	stp->position_timer->Instance->EGR = TIM_EGR_UG; //reset the trigger

}

/*
 void trapezodial_profile(stepper_obj *stp, float freq_steps, float n_steps){


 float computed_q=0.5*freq_steps*freq_steps;

 if (computed_q <n_steps){

 __HAL_TIM_SET_AUTORELOAD(stp->position_timer, computed_q);
 stp->pwm_timer->Instance->EGR = TIM_EGR_UG; //reset the trigger

 __HAL_TIM_SET_PRESCALER(stp->pwm_timer,999);
 stp->pwm_timer->Instance->EGR = TIM_EGR_UG; //reset the trigger
 float arr=84*1000000/1000* 1/freq_steps;
 __HAL_TIM_SET_AUTORELOAD(stp->pwm_timer, arr);
 stp->pwm_timer->Instance->EGR = TIM_EGR_UG; //reset the trigger

 HAL_TIM_PWM_Stop_IT(stp->pwm_timer, TIM_CHANNEL_1);


 }

 }*/

