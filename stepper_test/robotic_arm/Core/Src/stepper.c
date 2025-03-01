#include <stepper.h>

extern TIM_HandleTypeDef htim3;

//definisco l'oggetto stepper con i seguenti parametri

void stepper_init(stepper_obj *stp, GPIO_TypeDef *timer_pwm_ch,
		float stepper_resolution, uint16_t microstep, GPIO_TypeDef *enable_port,
		GPIO_TypeDef *direction_port, TIM_HandleTypeDef *position_timer) {

	stp->position_timer=position_timer;
	stp->timer_pwm_ch = timer_pwm_ch;
	stp->enable_port = enable_port;
	stp->direction_port = direction_port;

	stp->stepper_resolution = stepper_resolution;
	stp->microstep = microstep;
	stp->step_per_rev = 360.0f / stepper_resolution; // 360°/resolution
	stp->step_scale = stp->step_per_rev * microstep;
}

void stepper_move(stepper_obj *stp, float direction, float position, float freq_steps) {

	float displacement;
	displacement = stp->step_scale * position /360.0f;
	HAL_GPIO_WritePin(DIRECTION_GPIO_Port, DIRECTION_Pin, direction); //DIRECTION

	//set arr of timer-slave for the position step count
	__HAL_TIM_SET_AUTORELOAD(stp->position_timer, displacement);
	stp->position_timer->Instance->EGR=TIM_EGR_UG; //reset the trigger
}

