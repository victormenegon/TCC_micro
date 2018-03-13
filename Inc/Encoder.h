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

/* defines ---------------------------------------------------------*/
#define	External_Encoder_Resolution_Ct	(1024)	
#define	Encoder_Prescaler_Ct		(4)	
#define Max_Encoder_Count_Ct    ((Encoder_Prescaler_Ct*External_Encoder_Resolution_Ct) - 1)

/* Functions Protypes ---------------------------------------------------------*/
static void MX_TIM4_Init(void);

#endif /** _ENCODER_H */