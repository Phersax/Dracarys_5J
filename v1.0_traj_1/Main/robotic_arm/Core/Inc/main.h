/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DISABLE_button_Pin GPIO_PIN_13
#define DISABLE_button_GPIO_Port GPIOC
#define DISABLE_button_EXTI_IRQn EXTI15_10_IRQn
#define PWM2_Pin GPIO_PIN_0
#define PWM2_GPIO_Port GPIOA
#define PWM3_Pin GPIO_PIN_1
#define PWM3_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define DIRECTION4_Pin GPIO_PIN_6
#define DIRECTION4_GPIO_Port GPIOA
#define DIRECTION3_Pin GPIO_PIN_7
#define DIRECTION3_GPIO_Port GPIOA
#define DIRECTION2_Pin GPIO_PIN_4
#define DIRECTION2_GPIO_Port GPIOC
#define ENABLE_Pin GPIO_PIN_5
#define ENABLE_GPIO_Port GPIOC
#define DIRECTION1_Pin GPIO_PIN_0
#define DIRECTION1_GPIO_Port GPIOB
#define SERVO_en_Pin GPIO_PIN_1
#define SERVO_en_GPIO_Port GPIOB
#define ENDEFF_en_Pin GPIO_PIN_2
#define ENDEFF_en_GPIO_Port GPIOB
#define PWM4_Pin GPIO_PIN_6
#define PWM4_GPIO_Port GPIOC
#define PWM1_Pin GPIO_PIN_8
#define PWM1_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define SERVO_1_Pin GPIO_PIN_8
#define SERVO_1_GPIO_Port GPIOB
#define SERVO_2_Pin GPIO_PIN_9
#define SERVO_2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
