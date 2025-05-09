/*
 * trapezoidal_profile.h
 *
 *  Created on: Mar 15, 2025
 *      Author: david
 */

#ifndef INC_TRAPEZOIDAL_PROFILE_H_
#define INC_TRAPEZOIDAL_PROFILE_H_

//#include "stepper.h"
//#include "tim.h"

#define ACCEL_RATE 5

//master timer 1 parameters:
#define ARR_START_0 65535 //min_freq
#define ARR_MAX_0 19999 //max_freq

//master timer 2 parameters:
#define ARR_START_1 65535 //min_freq
#define ARR_MAX_1 32999 //max_freq

//master timer 3 parameters:
#define ARR_START_2 65535 //min_freq
#define ARR_MAX_2 1999 //max_freq

int arr_start[3]={ARR_START_0, ARR_START_1 , ARR_START_2};
int arr_max[3]={ARR_MAX_0, ARR_MAX_1 , ARR_MAX_2};


void trapezoidal_func(int k, TIM_HandleTypeDef *htim, TIM_HandleTypeDef *hslave);

void TIM_Cmd(TIM_TypeDef *TIMx, FunctionalState NewState);

#endif /* INC_TRAPEZOIDAL_PROFILE_H_ */
