/*
 * stepper.h
 *
 *  Created on: Feb 26, 2025
 *      Author: david
 */

#ifndef INC_STEPPER_H_
#define INC_STEPPER_H_
#include "main.h"

typedef struct {
	GPIO_TypeDef *timer_pwm_ch; //timer_pwm_channel
	//TIM_HandleTypeDef
	float freq_steps;
	//
	GPIO_TypeDef *enable_port;
	GPIO_TypeDef *direction_port;
	//
	uint16_t stepper_resolution;
	uint16_t step_per_rev; // = 360/stepper_resolution; // 360°/resolution
	uint16_t microstep;
	uint16_t step_scale; //= step_per_rev*microstep;

} stepper_obj;

//calcoli gli step necessari per il dato angolo da:
//N_STEPS=STEP_SCALE*DISTANCE_INPUT

void stepper_init(stepper_obj *stp, GPIO_TypeDef *timer_pwm_ch,
		float stepper_resolution, uint16_t microstep, GPIO_TypeDef *enable_port,
		GPIO_TypeDef *direction_port) ;

void stepper_move(stepper_obj *stp, float pwm_port, float dir, uint8_t enable,
		float position, float freq_steps);

/* Useful getter functions to access the parameters of the PWM signal
 uint32_t nidec_h24_GetPeriod();
 uint32_t nidec_h24_GetPrescaler();
 uint32_t nidec_h24_GetCounter();
 uint32_t nidec_h24_GetDutyCycle();*/

#endif /* INC_STEPPER_H_ */
