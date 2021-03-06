/******************************************************************************
* The information contained herein is confidential property of Embraco. The
* user, copying, transfer or disclosure of such information is prohibited
* except by express written agreement with Embraco.
******************************************************************************/

/**
 * @file    utils.h
 * @brief   Utility functions for other modules.
 *
 * @author  Victor H. B. Preuss
 * @date    2017-02-23
 *
 * @addtogroup
 * @{
 */

#ifndef _UTILS_H
#define _UTILS_H

/* Defines sections ---------------------------------------------------------*/
typedef int                 bool_t;
typedef char                char_t;
typedef signed char         int8_t;
typedef unsigned char       uint8_t;
typedef signed int          int16_t;
typedef unsigned int        uint16_t;
typedef signed long         int32_t;
typedef unsigned long       uint32_t;

typedef enum {UNDEFINED_POS, POS_1, POS_2, POS_3, POS_4, POS_5, POS_6} position_t;

#define Qb_8    256
#define Qb_10   1024
#define Qb_12   4096
#define Qb_16   65536

#define PWM_1_Pos  TIM1->CCER |= ((uint16_t)0b0000000001000001)
#define PWM_2_Pos  TIM1->CCER |= ((uint16_t)0b0000010000000001)
#define PWM_3_Pos  TIM1->CCER |= ((uint16_t)0b0000010000010000)
#define PWM_4_Pos  TIM1->CCER |= ((uint16_t)0b0000000000010100)
#define PWM_5_Pos  TIM1->CCER |= ((uint16_t)0b0000000100000100)
#define PWM_6_Pos  TIM1->CCER |= ((uint16_t)0b0000000101000000)
#define PWM_Dis    TIM1->CCER |= ((uint16_t)0b0000000000000000)

/* Prototypes sections ---------------------------------------------------------*/
/**
 * @brief   Convert two uint8_t into a 16 bits word.
 */
void uint8_to_uint16 (uint8_t in_low, uint8_t in_high, uint16_t* const out);

/**
 * @brief   Convert a 16 bits word into two uint8_t.
 */
void uint16_to_uint8 (uint16_t in, uint8_t* const out_low, uint8_t* const out_high);


#endif /** _UTILS_H */
