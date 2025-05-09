/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stepper.h"
#include "servo.h"
#include "end_eff_gpio.h"

#define TRAPEZOIDAL_PROFILE //COMMENT THIS IF YOU DON'T WANT THIS MOTION PROFILE FOR THE STEPPERS

#ifdef TRAPEZOIDAL_PROFILE
#include "trapezoidal_profile.h"
#include "trapezoidal_profile.c"
#endif

#ifndef TRAPEZOIDAL_PROFILE
#include "stp_callback.c"
#endif

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
static stepper_obj stp1;
static stepper_obj stp2;
static stepper_obj stp3;
static stepper_obj stp4;
static servo_obj srv1;
static servo_obj srv2;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_TIM3_Init();
	MX_TIM5_Init();
	MX_TIM1_Init();
	MX_TIM2_Init();
	MX_TIM4_Init();
	MX_TIM8_Init();
	MX_TIM10_Init();
	MX_TIM11_Init();
	MX_TIM6_Init();
	/* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start(&htim4); //start timer 1st joint
	HAL_TIM_Base_Start(&htim3); //start timer 2nd joint
	HAL_TIM_Base_Start(&htim5); //start timer 3rd joint

	HAL_GPIO_WritePin(ENABLE_GPIO_Port, ENABLE_Pin, GPIO_PIN_RESET); //ENABLE stepper motors

	/* stepper_init(obj, timer pwm, timer slave, resol, microstep, enable_port, direction_port */
	stepper_init(&stp1, &htim1, &htim4, 1.8, 4 * 4.27, DIRECTION1_GPIO_Port,
	DIRECTION1_Pin);
	stepper_init(&stp2, &htim2, &htim3, 1.8, 4 * 6, DIRECTION2_GPIO_Port,
	DIRECTION2_Pin);
	stepper_init(&stp3, &htim2, &htim3, 1.8, 4 * 6, DIRECTION3_GPIO_Port,
	DIRECTION3_Pin);
	stepper_init(&stp4, &htim8, &htim5, 1.8, 8 * 4.9, DIRECTION4_GPIO_Port,
	DIRECTION4_Pin);

	//servo: default position 0° in the range {-90,+90}
	/*servo_init(obj, timer pwm)*/
	servo_init(&srv1, &htim10);
	servo_init(&srv2, &htim11);



	stepper_move(&stp2, CLOCKWISE, 90, 10);
	stepper_move(&stp3, COUNTERCLOCKWISE, 90, 10);

	stepper_move(&stp4, CLOCKWISE, 20, 40);
	servo_move(&srv2, -20);

	end_eff_config(0, &htim6);

	HAL_Delay(3000);

	stepper_move(&stp2, COUNTERCLOCKWISE, 50, 10);
	stepper_move(&stp3, CLOCKWISE, 50, 10);

	stepper_move(&stp1, COUNTERCLOCKWISE, 60, 60);

	stepper_move(&stp4, CLOCKWISE, 40, 40);

	servo_move(&srv2, 0);

	HAL_Delay(3000);

	end_eff_config(0, &htim6);

	stepper_move(&stp1, CLOCKWISE, 60, 60);
	stepper_move(&stp4, COUNTERCLOCKWISE, 60, 60);

	stepper_move(&stp2, COUNTERCLOCKWISE, 40, 10);
	stepper_move(&stp3, CLOCKWISE, 40, 10);



	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */

	while (1) {

		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 84;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 2;
	RCC_OscInitStruct.PLL.PLLR = 2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
