/*
 * trapezoidal_profile.h
 *
 *  Created on: Mar 15, 2025
 *      Author: david
 */

#ifndef INC_TRAPEZOIDAL_PROFILE_H_
#define INC_TRAPEZOIDAL_PROFILE_H_

#include "stepper.h"
#include "tim.h"

#define ACCEL_RATE 50
#define ARR_START 65535 //min_freq
#define ARR_MAX 19999 //max_freq


void TIM_Cmd(TIM_TypeDef *TIMx, FunctionalState NewState);

#endif /* INC_TRAPEZOIDAL_PROFILE_H_ */
