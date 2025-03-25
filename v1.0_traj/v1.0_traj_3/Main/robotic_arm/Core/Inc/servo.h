/*
 * servo.h
 *
 *  Created on: Mar 2, 2025
 *      Author: david
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

//ccr for 50hz
#define CCR_MAX 7499.0
#define CCR_MIN 1499.0
#define ANGLE_MAX 90.0 //+-deg

#include "main.h"

typedef struct {
	//timers
	TIM_HandleTypeDef *pwm_timer; //master timer
	float unit;

} servo_obj;

void servo_init(servo_obj *srv, TIM_HandleTypeDef *pwm_timer);

void servo_move(servo_obj *srv, float position);

#endif /* INC_SERVO_H_ */
