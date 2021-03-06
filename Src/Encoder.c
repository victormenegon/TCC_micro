/******************************************************************************
* The information contained herein is confidential property of Embraco. The
* user, copying, transfer or disclosure of such information is prohibited
* except by express written agreement with Embraco.
******************************************************************************/

/**
 * @file    Encoder.c
 * @brief   Encoder functions.
 *
 * @author  Victor E. Menegon
 * @date    2018-01-03
 *
 */

/* Includes Section ---------------------------------------------------------*/
#include "main"
#include "stm32f1xx_hal.h"
#include "Encoder.h"
#include "utils.h"
#include "System_Management.h"
/* Private Variables Section ------------------------------------------------*/
TIM_HandleTypeDef htim4;
volatile uint16_t first_z_signal = TRUE;
volatile uint16_t Encoder_Rec_Value = 0;
volatile uint16_t Encoder_Value_Before_Recal;
volatile uint16_t Encoder_Adjust_Pos_Gb;
volatile uint16_t Encoder_Adjust_Neg_Gb;
volatile uint32_t T_Encoder_Speed_Lc = 0;
volatile uint16_t Freq_Encoder_Lc = 0;
/* Functions Section---------------------------------------------------------*/
/**
 * @brief   Initializes TIM4 for Encoder use
 * @details 
 * @author  Victor E. Menegon
 * @date    2018-03-12
 */
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
#if 0
/**
 * @brief   Z signal interruption handler
 * @details Check if encoder is counting up or down and update properly
                      the correction angle used in GET_ELECTRICAL_ANGLE_FROM_ENCODER_MC
                      to get the Rotor position angle.
                      -If Encoder is counting Up:   add 90deg to encoder
                      -If Encoder is counting Down: sub 90deg to encoder
 * @author  Roberto Andrich
 * @date    2012-01-06
 */
void Encoder_Direction_Supervisory_Sb(void)
{
    static uint16_t Encoder_Lc=0;
    static uint16_t Encoder_Old_Lc=0;
    static uint16_t Count_Up_Lc=0;
    static uint16_t Count_Down_Lc=0;

    Encoder_Lc = Encoder_Counter_Mc;

    if (Encoder_Lc > Encoder_Old_Lc)
    {
        Encoder_Old_Lc = Encoder_Lc;
        Count_Up_Lc++;
        Count_Down_Lc=0;
        if (Count_Up_Lc > N_Confirm_Encoder_Counting_Ct)
        {
            Count_Up_Lc = 0;
            Encoder_Adjust_Pos_Gb =  Encoder_Correction_Angle_Ct;
            Encoder_Adjust_Neg_Gb =  0;
        }
    }
    else if (Encoder_Lc < Encoder_Old_Lc)
    {
        Encoder_Old_Lc = Encoder_Lc;
        Count_Up_Lc=0;
        Count_Down_Lc++;
        if (Count_Down_Lc > N_Confirm_Encoder_Counting_Ct)
        {
            Count_Down_Lc = 0;
            Encoder_Adjust_Pos_Gb =  0;
            Encoder_Adjust_Neg_Gb =  Encoder_Correction_Angle_Ct;
        }
    }
}
#endif

/**
 * @brief   Motor speed calculation using Encoder Signal
 * @details T_Encoder_Speed_Lc is variable for each motor, 
 * depending on its maximum speed. It's calculated through
 * function Motor_Speed_Enc_Param().
 * @author  Victor E. Menegon
 * @date    2018-04-03
 */
void Motor_Speed(void)
{
    static uint32_t Speed_Timer;
    static uint16_t new_angle = 0;
    static uint16_t old_angle = 0;
    static uint16_t delta_angle = 0;
    static uint16_t speed_16b = 0;
    static uint16_t speed_rad_s = 0;
    static uint16_t speed_rpm = 0;

    if(Delay_Mc(Speed_Timer) >= T_Encoder_Speed_Lc)
    {
        Resync_Timer_Mc(Speed_Timer);
        new_angle = Ele_Angle_Encoder_16bits_Mc;
        delta_angle = new_ange - old_angle;
        speed_16b = delta_angle * Freq_Encoder_Lc;
        speed_rad_s = (uint16_t)((((uint32_t)speed_16b * Bits16_2_Encoder) / Qb_12) * Encoder_2_Rad)/Qb_16 ;
        speed_rpm = (uint16_t)(((uint32_t)speed_rad_s * Rad_S_2_RPM) / Qb_12);
        old_angle = new_angle;
    }
}

/**
 * @brief   Motor speed parameters
 * @author  Victor E. Menegon
 * @date    2018-04-03
 */
void Motor_Speed_Enc_Param(void)
{
    Freq_Encoder_Lc = (Max_Speed / 15);    // 4 * Max_Speed / 60
    /*Updating Period for Encoder Speed Calculation*/
    if (Freq_Encoder_Lc <= 0)
    {
        Freq_Encoder_Lc = 1;          /*Avoiding division by zero*/
    }
    T_Encoder_Speed_Lc = Timer_Frequency_Ct / Freq_Encoder_Lc;
}

/**
 * @brief   Z signal interruption handler
 * @details Used to recalibrate encoder counter
 *          at each mechanical turn. At first
 *          interruption, value of counter is saved.
 *          It's later used to force value of counter 
 *          at each mechanical turn.
 * @author  Victor E. Menegon
 * @date    2018-03-13
 */
void EXTI9_5_IRQn(void)
{
    if(first_z_signal)
    {
        Encoder_Rec_Value = Encoder_Counter_Mc;
        first_z_signal = FALSE;
    }
    else
    {
        Encoder_Value_Before_Recal = Encoder_Counter_Mc;
        Encoder_Counter_Mc = Encoder_Rec_Value;
    }
__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_8);
}
