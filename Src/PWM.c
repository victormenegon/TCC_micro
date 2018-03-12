/******************************************************************************
* The information contained herein is confidential property of Embraco. The
* user, copying, transfer or disclosure of such information is prohibited
* except by express written agreement with Embraco.
******************************************************************************/

/**
 * @file    PWM.c
 * @brief   PWM use file.
 *
 * @author  Victor E. Menegon
 * @date    2018-07-03
 *
 */

/* Includes Section ---------------------------------------------------------*/

#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "stm32f1xx_hal_tim.h"
#include "utils.h"

/* Private variables ---------------------------------------------------------*/
static TIM_HandleTypeDef htim1;
static TIM_MasterConfigTypeDef mastertim1;

/* Functions ---------------------------------------------------------*/

/**
 * @brief   Configure and starts TIM1 to use with PWM
 * @details 
 * @author  Victor E. Menegon
 * @date    2018-03-07
 */
/* TIM1 init function */
static void MX_TIM1_Init(void)
{

  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_CENTERALIGNED1;
  htim1.Init.Period = 14400;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 1;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_OC_Init(&htim1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  mastertim1.sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  mastertim1.sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM2;
  sConfigOC.Pulse = 7200;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_ENABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 72;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_ENABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

HAL_TIM_MspPostInit(&htim1);
HAL_TIM_OC_MspInit(&htim1);
HAL_TIMEx_MasterConfigSynchronization(&htim1, &mastertim1);
HAL_TIM_PWM_ConfigChannel(&htim1,&sConfigOC,TIM_CHANNEL_1);
HAL_TIM_PWM_ConfigChannel(&htim1,&sConfigOC,TIM_CHANNEL_2);
HAL_TIM_PWM_ConfigChannel(&htim1,&sConfigOC,TIM_CHANNEL_3);
HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
}


/**
 * @brief   PWM according to sector and required Duty Cycle
 * @details 
 * @author  Victor E. Menegon
 * @date    2018-03-08
 */
void PWM_Manager(uint16_t *duty_cycle, position_t mec_pos)
{
    uint16_t new_duty_cycle = *duty_cycle;
    position_t new_pos = mec_pos;
    
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,new_duty_cycle);
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,new_duty_cycle);
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,new_duty_cycle);

    switch(new_pos)
    {
        case POS_1:
            PWM_1_Pos;
            TIM_EVENTSOURCE_COM;
        break;
        case POS_2:
            PWM_2_Pos;
            TIM_EVENTSOURCE_COM;
        break;
        case POS_3:
            PWM_3_Pos;
            TIM_EVENTSOURCE_COM;
        break;
        case POS_4:
            PWM_4_Pos;
            TIM_EVENTSOURCE_COM;
        break;
        case POS_5:
            PWM_5_Pos;
            TIM_EVENTSOURCE_COM;
        break;
        case POS_6:
            PWM_6_Pos;
            TIM_EVENTSOURCE_COM;
        break;
        default:
            PWM_Dis;
            TIM_EVENTSOURCE_COM;
        break;
    }
}

position_t Motor_Position(uint16_t motor_angle)
{
    //Return position utilizando Get_Motor_Angle.
}

uint16_t Get_Motor_Angle()
{
    //Fazer as contas do Encoder
}
