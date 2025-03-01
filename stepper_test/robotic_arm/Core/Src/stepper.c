#include <stepper.h>

extern TIM_HandleTypeDef htim3;

//definisco l'oggetto stepper con i seguenti parametri

void stepper_init(stepper_obj *stp, GPIO_TypeDef *timer_pwm_ch,
		float stepper_resolution, uint16_t microstep, GPIO_TypeDef *enable_port,
		GPIO_TypeDef *direction_port) {

	stp->timer_pwm_ch = timer_pwm_ch;
	stp->enable_port = enable_port;
	stp->direction_port = direction_port;

	stp->stepper_resolution = stepper_resolution;
	stp->microstep = microstep;
	stp->step_per_rev = 360.0f / stepper_resolution; // 360°/resolution
	stp->step_scale = stp->step_per_rev * microstep;
}

float stepper_move(stepper_obj *stp, float pwm_port, float direction,
		uint8_t enable, float position, float freq_steps) {

	//float n_steps;
	//calcoli gli step necessari per il dato angolo da:
	return stp->step_scale * position;



	//N_STEPS=STEP_SCALE*DISTANCE_INPUT
}

