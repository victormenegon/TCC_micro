/******************************************************************************
* The information contained herein is confidential property of Embraco. The
* user, copying, transfer or disclosure of such information is prohibited
* except by express written agreement with Embraco.
******************************************************************************/

/**
 * @file    Serial_Comm.h
 * @brief   Serial driver configurations for communication with the
 *          microcontroller which controls the compressor.
 *
 * @author  Victor E. Menegon
 * @date    2018-02-21
 *
 * @addtogroup Serial Comm
 * @{
 */

#ifndef _SERIAL_COMM_H
#define _SERIAL_COMM_H

/* defines ---------------------------------------------------------*/
#define BAUD_RATE   600

/******************************************************************************
* EECON Commercial Protocol
******************************************************************************/

/* Size of serial buffer in bytes*/
#define COMMAND_LENGTH_SERIAL_EMBRACO               5

/* Serial communication baud rate */
#define BAUD_RATE_SERIAL_EMBRACO                    600
                                                    
/* Maximum transmission or reception time (ms) */   
#define TIMEOUT_SERIAL_EMBRACO                      2000U
                                                    
/* Transmitted and received word length */          
#define WORD_LENGTH_SERIAL_EMBRACO                  UART_WORDLENGTH_8B
                                                    
/* Number of stop bits */                           
#define STOP_BITS_SERIAL_EMBRACO                    UART_STOPBITS_1
                                                    
/* Protocol parity */                               
#define PARITY_TYPE_SERIAL_EMBRACO                  UART_PARITY_NONE
                                                    
/* Hardware control flow */                         
#define HW_CONTROL_FLOW_SERIAL_EMBRACO              UART_HWCONTROL_NONE
                                                    
/* Transmission mode */                             
#define TRANSMISSION_MODE_SERIAL_EMBRACO            UART_MODE_TX_RX

/* 1st byte - Identification */
#define TRANSMISSION_IDENTIFICATION_1ST             0xA5U

/* 2nd byte - Command */
#define TRANSMIT_SET_SPEED_2ND                      0xC3U
#define READ_SET_SPEED_2ND                          0x3CU
#define READ_OPERATION_STATUS_2ND                   0x3CU
#define READ_VARIABLE_2ND                           0x3DU
#define TRANSMIT_MZ1_2ND                            0x3EU
#define TRANSMIT_MZ2_2ND                            0x3FU
#define READ_REAL_SPEED_2ND                         0x3CU
#define READ_PARTNUMBER_2ND                         0x8CU
#define EXTENDED_CO_COMM_2ND                        0x3CU
#define SERIAL_OVERWRITE_CO_EXT_2ND                 0x69U

/* 3rd byte - Data low */
#define READ_SET_SPEED_3RD                          0x80U
#define READ_OPERATION_STATUS_3RD                   0x83U
#define READ_REAL_SPEED_3RD                         0x86U
#define READ_PARTNUMBER_3RD                         0x00U
#define READ_POWER_CO_EXT_3RD                       0x82U
#define READ_POWER_LIMIT_CO_EXT_3RD                 0x8AU
#define READ_STARTING_TRIALS_CO_EXT_3RD             0x81U
#define READ_BUS_VOLTAGE_CO_EXT_3RD                 0x84U
#define READ_TEMPERATURE_CO_EXT_3RD                 0x88U
#define READ_TEMPERATURE_BRIDGE_CO_EXT_3RD          0x89U

/* 4th byte - Data high */
#define READ_SET_SPEED_4TH                          0x39U
#define READ_OPERATION_STATUS_4TH                   0x39U
#define READ_REAL_SPEED_4TH                         0x39U
#define READ_BYTE_4TH                               0x39U
#define EXTENDED_CO_COMM_4TH                        0x39U
#define SERIAL_OVERWRITE_CO_EXT_4TH                 0x93U

/* Received Command Structure */

/* 1st byte - Identification */
#define RECEPTION_IDENTIFICATION_1ST                0x5AU

/* 2nd byte - Command */
#define ANSWER_TRANSMIT_SET_SPEED_2ND               0x83U
#define ANSWER_READ_SET_SPEED_2ND                   0x80U
#define ANSWER_READ_OPERATION_STATUS_2ND            0x83U
#define ANSWER_READ_VARIABLE_2ND                    0x86U
#define ANSWER_TRANSMIT_MZ1_2ND                     0x3EU
#define ANSWER_TRANSMIT_MZ2_2ND                     0x3FU
#define ANSWER_READ_REAL_SPEED_2ND                  0x86U
#define ANSWER_READ_PARTNUMBER_2ND                  0xC8U
#define ANSWER_READ_POWER_CO_EXT_2ND                0x82U
#define ANSWER_READ_POWER_LIMIT_CO_EXT_2ND          0x8AU
#define ANSWER_READ_STARTING_TRIALS_CO_EXT_2ND      0x81U
#define ANSWER_BUS_VOLTAGE_READING_2ND              0x84U
#define ANSWER_READ_TEMPERATURE_CO_EXT_2ND          0x88U
#define ANSWER_READ_TEMPERATURE_BRIDGE_CO_EXT_2ND   0x89U
#define ANSWER_SERIAL_OVERWRITE_CO_EXT_2ND          0xC3U

#define COMM_ERROR_4TH_BYTE_BC                      0xF0U
#define COMM_ERROR_CHECKSUM                         0xF2U
#define COMM_ERROR_2ND_BYTE_BC                      0xF4U
#define COMM_ERROR_3TH_BYTE_BC                      0xF8U

/* 3rd byte - Command */
#define ANSWER_READ_PARTNUMBER_3RD_NO_INDEX_ERROR   0x00U
#define ANSWER_READ_PARTNUMBER_3RD_INDEX_ERROR      0xFFU

/* 3rd byte - Data Low */
#define STATUS_OVERLOAD_CONDITION_3RD               0x02U
#define STATUS_SET_SPEED_OUT_OF_SPEC_3RD            0x80U
#define STATUS_UNDER_SPEED_FAIL_3RD                 0x04U
#define STATUS_START_FAIL_3RD                       0x01U
#define STATUS_OVERVOLTAGE_FAIL_3RD                 0x10U
#define STATUS_OVERLOAD_FAIL_3RD                    0x02U
#define STATUS_WRONG_ROTOR_POSITION_3RD             0x08U
#define STATUS_MOTOR_CABLE_FAIL_3RD                 STATUS_START_FAIL_3RD

#define STATUS_OVERTEMPERATURE_FAIL_3RD             0x20U

#define COMM_ERROR_3RD                              0xFFU
#define STATUS_RUNNING_OR_WAITING_COMMAND_4TH       0x00U
#define STATUS_STOPPED_4TH                          0xFFU
#define STATUS_ERROR_4TH                            0xFFU

/* 4th byte - Data High */
#define COMM_ERROR_4TH                              0xFFU


/* Types Section  -------------------------------------------------------------*/
/**
 * @brief   Serial states.
 */
typedef enum
{
	WAITING,
	SENDING,
	RECEIVING
} serial_state_t;


/* Functions Protypes ---------------------------------------------------------*/
void Serial_Comm_Init(void);
void Serial_Comm_Main(void);

#endif /* _USART_CONFIG_H */

/** @} */