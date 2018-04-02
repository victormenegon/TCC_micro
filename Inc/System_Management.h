/******************************************************************************
* The information contained herein is confidential property of Embraco. The
* user, copying, transfer or disclosure of such information is prohibited
* except by express written agreement with Embraco.
******************************************************************************/

/**
 * @file    System_Management.h
 * @brief   Functions and variables realated to system in general
 *
 * @author  Victor E. Menegon
 * @date    2018-02-21
 *
 * @addtogroup System Management
 * @{
 */

#ifndef  _SYSTEM_MANAGEMENT_H
#define  _SYSTEM_MANAGEMENT_H

/* Defines ---------------------------------------------------------*/
#define Poles_Pair      2

//General mask to access Timer current value
#define Timer_Gb            (SysTick->VAL)
#define SYSCLK_FREQ_72MHz   72000000
#define		SYSCLK_Ct	SYSCLK_FREQ_72MHz
#define Timer_Frequency_Ct		(SYSCLK_Ct/8)
/* Constants for time measurement*/
#define T_1ms_Ct                ((1L*Timer_Frequency_Ct)/1000)
#define T_50ms_Ct                ((50L*Timer_Frequency_Ct)/1000)
#define T_100ms_Ct              ((100L*Timer_Frequency_Ct)/1000)
#define T_200ms_Ct              (2*T_100ms_Ct)
#define T_500ms_Ct              (5*T_100ms_Ct)
#define T_1s_Ct              	(10*T_100ms_Ct)

//Macro for measuring time past since last Ref_Time_Lc Update
#define Delay_Mc(Ref_Time_Lc)     (0xFFFFFF&(Ref_Time_Lc - Timer_Gb))    
//Remember STM32 SysTick decrements with time (inverse logic)

//Macro for resynchronizing Ref_Time
#define	Resync_Timer_Mc(Ref_Time_Lc)\
{\
		Ref_Time_Lc = Timer_Gb;\
}\
/* Functions Protypes ---------------------------------------------------------*/

#endif /** _SYSTEM_MANAGEMENT_H */