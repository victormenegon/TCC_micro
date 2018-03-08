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
 * @addtogroup Thermostat
 * @{
 */

#ifndef _UTILS_H
#define _UTILS_H

/* Defines sections ---------------------------------------------------------*/
typedef enum {UNDEFINED_POS, POS_1, POS_2, POS_3, POS_4, POS_5, POS_6} position_t;

#define Qb_8    256
#define Qb_10   1024
#define Qb_12   4096
#define Qb_16   65536

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
