/*
 * stepper.h
 *
 *  Created on: Feb 26, 2025
 *      Author: david
 */

#ifndef INC_STEPPER_H_
#define INC_STEPPER_H_
#include "main.h"

#define ACCEL_RATE 1 //1 OR 2 CHANGED THE GRANULARITY


typedef struct {
	//timers
	TIM_HandleTypeDef *pwm_timer; //master timer
	TIM_HandleTypeDef *position_timer; //SLAVE timer

	float freq_steps;
	//
	GPIO_TypeDef *direction_port;
	uint16_t direction_pin;
	//stepper data
	float stepper_resolution;
	float step_per_rev; // = 360/stepper_resolution; // 360°/resolution
	uint16_t microstep;
	float step_scale; //= step_per_rev*microstep;

} stepper_obj;

typedef enum {
	CLOCKWISE = 1, COUNTERCLOCKWISE = 0

} direction_str;
void stepper_init(stepper_obj *stp, TIM_HandleTypeDef *pwm_timer,
		TIM_HandleTypeDef *position_timer, float stepper_resolution,
		uint16_t microstep, GPIO_TypeDef *direction_port,
		uint16_t direction_pin) ;

void stepper_move(stepper_obj *stp, direction_str direction, float position,
		float freq_steps);

void trapezodial_profile(stepper_obj *stp,float freq_steps, float n_steps);

#endif /* INC_STEPPER_H_ */
