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

void reset_timers(stepper_obj *stp);

#endif /* INC_STEPPER_H_ */
