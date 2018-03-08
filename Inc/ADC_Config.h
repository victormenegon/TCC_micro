/******************************************************************************
* The information contained herein is confidential property of Embraco. The
* user, copying, transfer or disclosure of such information is prohibited
* except by express written agreement with Embraco.
******************************************************************************/

/**
 * @file    ADC_Config.h
 * @brief   ADC configurations.
 *
 * @author  Victor E. Menegon
 * @date    2018-02-21
 *
 * @addtogroup Serial Comm
 * @{
 */

#ifndef  _ADC_CONFIG_H
#define  _ADC_CONFIG_H

/* Functions Protypes ---------------------------------------------------------*/
void HAL_ADC_MspInit(void);
static void MX_ADC1_Init(void);
static void MX_ADC2_Init(void);
void ADC_Main(void);

#endif /** _ADC_CONFIG_H */