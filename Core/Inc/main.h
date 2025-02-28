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
#include "stm32f1xx_hal.h"

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
#define PWMA_Pin GPIO_PIN_0
#define PWMA_GPIO_Port GPIOA
#define PWMB_Pin GPIO_PIN_1
#define PWMB_GPIO_Port GPIOA
#define AIN1_Pin GPIO_PIN_2
#define AIN1_GPIO_Port GPIOA
#define AIN2_Pin GPIO_PIN_3
#define AIN2_GPIO_Port GPIOA
#define BIN1_Pin GPIO_PIN_4
#define BIN1_GPIO_Port GPIOA
#define BIN2_Pin GPIO_PIN_5
#define BIN2_GPIO_Port GPIOA
#define encoder1A_Pin GPIO_PIN_6
#define encoder1A_GPIO_Port GPIOA
#define encoder1B_Pin GPIO_PIN_7
#define encoder1B_GPIO_Port GPIOA
#define Trig_Pin GPIO_PIN_0
#define Trig_GPIO_Port GPIOB
#define Echo_Pin GPIO_PIN_1
#define Echo_GPIO_Port GPIOB
#define Echo_EXTI_IRQn EXTI1_IRQn
#define IR1_Pin GPIO_PIN_12
#define IR1_GPIO_Port GPIOB
#define IR2_Pin GPIO_PIN_13
#define IR2_GPIO_Port GPIOB
#define IR3_Pin GPIO_PIN_14
#define IR3_GPIO_Port GPIOB
#define IR4_Pin GPIO_PIN_15
#define IR4_GPIO_Port GPIOB
#define IR5_Pin GPIO_PIN_8
#define IR5_GPIO_Port GPIOA
#define IR6_Pin GPIO_PIN_9
#define IR6_GPIO_Port GPIOA
#define IR7_Pin GPIO_PIN_10
#define IR7_GPIO_Port GPIOA
#define IR8_Pin GPIO_PIN_11
#define IR8_GPIO_Port GPIOA
#define IR9_Pin GPIO_PIN_12
#define IR9_GPIO_Port GPIOA
#define IR10_Pin GPIO_PIN_15
#define IR10_GPIO_Port GPIOA
#define encoder2A_Pin GPIO_PIN_6
#define encoder2A_GPIO_Port GPIOB
#define encoder2B_Pin GPIO_PIN_7
#define encoder2B_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
