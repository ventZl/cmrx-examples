/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32h7xx_hal.h"

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
#define CAN2_LED2_Pin GPIO_PIN_13
#define CAN2_LED2_GPIO_Port GPIOC
#define CAN2_EN_Pin GPIO_PIN_2
#define CAN2_EN_GPIO_Port GPIOE
#define CAN1_EN_Pin GPIO_PIN_7
#define CAN1_EN_GPIO_Port GPIOB
#define LIN1_EN_Pin GPIO_PIN_4
#define LIN1_EN_GPIO_Port GPIOB
#define CAN1_LED2_Pin GPIO_PIN_15
#define CAN1_LED2_GPIO_Port GPIOA
#define CAN2_LED1_Pin GPIO_PIN_3
#define CAN2_LED1_GPIO_Port GPIOE
#define CAN1_LED1_Pin GPIO_PIN_2
#define CAN1_LED1_GPIO_Port GPIOD
#define LIN1_PHY_EN_Pin GPIO_PIN_4
#define LIN1_PHY_EN_GPIO_Port GPIOE
#define LIN1_LED1_Pin GPIO_PIN_2
#define LIN1_LED1_GPIO_Port GPIOC
#define LIN1_LED2_Pin GPIO_PIN_0
#define LIN1_LED2_GPIO_Port GPIOC
#define NBUS_SHDN_Pin GPIO_PIN_8
#define NBUS_SHDN_GPIO_Port GPIOC
#define LIN2_LED1_Pin GPIO_PIN_0
#define LIN2_LED1_GPIO_Port GPIOA
#define LIN2_LED2_Pin GPIO_PIN_4
#define LIN2_LED2_GPIO_Port GPIOA
#define LIN2_PHY_EN_Pin GPIO_PIN_13
#define LIN2_PHY_EN_GPIO_Port GPIOD
#define ETH_NRST_Pin GPIO_PIN_13
#define ETH_NRST_GPIO_Port GPIOE
#define LIN2_EN_Pin GPIO_PIN_12
#define LIN2_EN_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
