/******************************************************************************
* The information contained herein is confidential property of Embraco. The
* user, copying, transfer or disclosure of such information is prohibited
* except by express written agreement with Embraco.
******************************************************************************/

/**
 * @file    PWM.h
 * @brief   PWM Configuration and use header.
 *
 * @author  Victor E. Menegon
 * @date    2018-02-21
 *
 * @addtogroup Serial Comm
 * @{
 */

#ifndef  _PWM_H
#define  _PWM_H


/* Functions Protypes ---------------------------------------------------------*/
static void MX_TIM1_Init(void);
void PWM_Manager(uint16_t *duty_cycle, position_t mec_pos);
position_t Motor_Position(uint16_t motor_angle);

#endif /** _PWM_H */