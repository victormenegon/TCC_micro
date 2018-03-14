/******************************************************************************
* The information contained herein is confidential property of Embraco. The
* user, copying, transfer or disclosure of such information is prohibited
* except by express written agreement with Embraco.
******************************************************************************/

/**
 * @file    utils.c
 * @brief   Utility functions for other modules.
 *
 * @author  Victor E. Menegon
 * @date    2018-01-03
 *
 */

/* Includes Section ---------------------------------------------------------*/

#include "main.h"
#include "utils.h"
/* Private variables ---------------------------------------------------------*/

/**
 * @brief   
 */
static const uint8_t lsb_mask = 0xFFU;

/******************************************************************************
* Public Function Implementation Section
******************************************************************************/

/**
 * @brief   
 * @details 
 * @author  Victor H. B. Preuss
 * @date    2017-09-01
 */
void uint8_to_uint16 (uint8_t in_low, uint8_t in_high, uint16_t* const out)
{
    (*out) = (((uint16_t) in_high) << 8) + in_low;
}

/**
 * @brief   
 * @details 
 * @author  Victor H. B. Preuss
 * @date    2017-09-01
 */
void uint16_to_uint8 (uint16_t in, uint8_t* const out_low, uint8_t* const out_high)
{
    (*out_low)  = (uint8_t)(in & lsb_mask);
    (*out_high) = (uint8_t)(in >> 8);
}
