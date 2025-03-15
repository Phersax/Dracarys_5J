/*
 * servo.c
 *
 *  Created on: Mar 2, 2025
 *      Author: david
 */
#include <servo.h>

void servo_init(servo_obj *srv, TIM_HandleTypeDef *pwm_timer) {
	srv->pwm_timer = pwm_timer;
	srv->unit = (CCR_MAX - CCR_MIN) / (2*ANGLE_MAX);
	//pwm=50hz
	srv->pwm_timer->Instance->PSC=27;
	srv->pwm_timer->Instance->ARR=60000-1;

}
//int ccr; //debug

void servo_move(servo_obj *srv, float position) {

	int ccr;


	//saturation
	if (position > ANGLE_MAX)
	position = ANGLE_MAX;//max angle position available
	if (position < -ANGLE_MAX)
		position = -ANGLE_MAX; //min angle position available

	//compute ccr value
	if (position != 0)
		ccr = (int) ((CCR_MAX + CCR_MIN) / 2) + (int) (srv->unit * position);

	else {  //position==0
		ccr = (int) ((CCR_MAX + CCR_MIN) / 2);
	}
	__HAL_TIM_SET_COMPARE(srv->pwm_timer, TIM_CHANNEL_1, ccr); //deg=0
	srv->pwm_timer->Instance->EGR = TIM_EGR_UG; //not relevant in this case



}

