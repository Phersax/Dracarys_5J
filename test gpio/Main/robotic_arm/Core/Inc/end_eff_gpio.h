/*
 * end_eff_gpio.h
 *
 *  Created on: Mar 16, 2025
 *      Author: david
 */

#ifndef INC_END_EFF_GPIO_H_
#define INC_END_EFF_GPIO_H_


#include "main.h"

typedef struct {

	TIM_HandleTypeDef *htim;

} gripper_obj;



void gripper_init(gripper_obj *endeff, TIM_HandleTypeDef *htim);
void gripper_config(gripper_obj *endeff,int func, int time);


#endif /* INC_END_EFF_GPIO_H_ */
