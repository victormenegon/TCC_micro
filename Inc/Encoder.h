/******************************************************************************
* The information contained herein is confidential property of Embraco. The
* user, copying, transfer or disclosure of such information is prohibited
* except by express written agreement with Embraco.
******************************************************************************/

/**
 * @file    Encoder.h
 * @brief   Encoder Configuration and use header.
 *
 * @author  Victor E. Menegon
 * @date    2018-02-21
 *
 * @addtogroup Encoder
 * @{
 */

#ifndef  _ENCODER_H
#define  _ENCODER_H

/* Defines ---------------------------------------------------------*/
#define	External_Encoder_Resolution_Ct	(1024)	
#define	Encoder_Prescaler_Ct	    	(4)	
#define Max_Encoder_Count_Ct            ((Encoder_Prescaler_Ct*External_Encoder_Resolution_Ct) - 1)
#define	Encoder_Counter_Mc	            TIM4->CNT   //Output of Timer Encoder Counter
#define Enc_360deg_Ct                   Qb_16
#define Encoder_Correction_Angle_Ct     ((90*Enc_360deg_Ct)/360)
#define Encoder_2_16bits                (Qb_8*Qb_16/(Max_Encoder_Count_Ct+1))
#define Bits16_2_Encoder                Qb_12*((Max_Encoder_Count_Ct+1)/Qb_16)
#define Mec_Angle_Encoder_16bits_Mc     (Encoder_Counter_Mc*Encoder_2_16bits) + Encoder_Adjust_Pos_Gb - Encoder_Adjust_Neg_Gb
#define Ele_Angle_Encoder_16bits_Mc     (Encoder_Counter_Mc*Encoder_2_16bits*Poles_Pair) + Encoder_Adjust_Pos_Gb - Encoder_Adjust_Neg_Gb1
#define PI_def                          (31416*Qb_16/10000)
#define Encoder_2_Rad                   (2*PI_def/(Max_Encoder_Count_Ct+1))
#define Rad_S_2_RPM                     ((95493*Qb_12)/10000)

/* Functions Protypes ---------------------------------------------------------*/
void Encoder_Direction_Supervisory_Sb(void);
void Motor_Speed(void);
void Motor_Speed_Enc_Param(void);

#endif /** _ENCODER_H */