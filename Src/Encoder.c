/******************************************************************************
* The information contained herein is confidential property of Embraco. The
* user, copying, transfer or disclosure of such information is prohibited
* except by express written agreement with Embraco.
******************************************************************************/

/**
 * @file    ADC_Config.c
 * @brief   Utility functions for other modules.
 *
 * @author  Victor E. Menegon
 * @date    2018-01-03
 *
 */

/* Includes Section ---------------------------------------------------------*/
#include "stm32f1xx_hal.h"

TIM_HandleTypeDef htim4;

/* TIM4 init function */
static void MX_TIM4_Init(void)
{
  TIM_Encoder_InitTypeDef sConfigEncoder;

  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = Max_Encoder_Count_Ct;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_IC_Init(&htim4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  sConfigEncoder.Mode = TIM_ENCODERMODE_TI12;
  sConfigEncoder.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfigEncoder.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfigEncoder.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfigEncoder.IC1Filter = 0;
  sConfigEncoder.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfigEncoder.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfigEncoder.IC2Filter = 0;
  sConfigEncoder.IC2Polarity = TIM_ICPOLARITY_RISING;
  
  if (HAL_TIM_Encoder_Init(&htim4, &sConfigEncoder) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    HAL_TIM_Encoder_MspInit(&htim4);
    HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);
}
