/******************************************************************************
* The information contained herein is confidential property of Embraco. The
* user, copying, transfer or disclosure of such information is prohibited
* except by express written agreement with Embraco.
******************************************************************************/

/**
 * @file    Serial_Comm.c
 * @brief   Serial functions.
 *
 * @author  Victor E. Menegon
 * @date    2018-01-03
 *
 */

/* Includes Section ---------------------------------------------------------*/

#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "utils.h"
#include "Serial_Comm.h"
#include "stm32f1xx_hal_uart.h"

/* Private variables ---------------------------------------------------------*/
static UART_HandleTypeDef husart3;
static serial_state_t serial_state = WAITING;
static uint8_t Rx_Comm_Serial [COMMAND_LENGTH_SERIAL_EMBRACO];
static uint8_t Tx_Comm_Serial [COMMAND_LENGTH_SERIAL_EMBRACO];
uint8_t b_transmission_completed = FALSE;
uint8_t b_reception_completed = FALSE;

/* Global variables ---------------------------------------------------------*/
extern volatile Motor_Ref_Speed_Gb;
extern volatile Motor_Real_Speed_Gb;

/* Local Prototypes ---------------------------------------------------------*/
void USART3_IRQHandler (void);
void processing_received_data (void);
void set_ref_speed(void);
void transmit_ref_speed(void);
void get_status_serial(void);
void get_value_from_variable(void);
void get_real_speed(void);
static uint8_t calc_checksum (const uint8_t * p_command);

/* Functions Section ---------------------------------------------------------*/

/**
 * @brief   Initializes USART3 to use in Serial Communication
 * @details 
 * @author  Victor E. Menegon
 * @date    2018-02-21
 */
/* USART3 init function */
void Serial_Comm_Init(void)
{

  husart3.Instance = USART3;
  husart3.Init.BaudRate = BAUD_RATE;
  husart3.Init.WordLength = UART_WORDLENGTH_8B;
  husart3.Init.StopBits = UART_STOPBITS_1;
  husart3.Init.Parity = UART_PARITY_NONE;
  husart3.Init.Mode = UART_MODE_TX_RX;
  husart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  husart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&husart3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/**
 * @brief   State Machine to communicate Inverter with LabVIEW Interface using EECON Protocol
 * @details 
 * @author  Victor E. Menegon
 * @date    2018-02-21
 */
void Serial_Comm_Main(void)
{
  switch(serial_state)
  {
    case WAITING:
    {
      serial_state = RECEIVING;
      b_reception_completed = FALSE;
      __HAL_UART_ENABLE_IT(&husart3,UART_IT_RXNE);
      __HAL_UART_DISABLE_IT(&husart3,UART_IT_TC);
    }
    break;

    case RECEIVING:
    {
      if(b_reception_completed)
      {
        if (HAL_UART_Receive_IT(&husart3, (uint8_t *) Rx_Comm_Serial, COMMAND_LENGTH_SERIAL_EMBRACO) != HAL_OK)
        {
          //serial_error_handler();
        }
        else
        {
          processing_received_data();
          serial_state = SENDING;
          b_transmission_completed = FALSE;
          __HAL_UART_ENABLE_IT(&husart3,UART_IT_TC);
          __HAL_UART_DISABLE_IT(&husart3,UART_IT_RXNE);
        }    
      }
    }
    break;

    case SENDING:
    {
      if (HAL_UART_Transmit_IT(&husart3, (uint8_t *) Tx_Comm_Serial, COMMAND_LENGTH_SERIAL_EMBRACO) != HAL_OK)
      {
        //serial_error_handler();
      }
      else
      {
        if (b_transmission_completed)
        {
          serial_state = WAITING;
        }
      }
    }
    break;

    default:
      {
        serial_state = WAITING;
      }
    break;
  }
}

/**
 * @brief   Manage the received data
 * @details 
 * @author  Victor E. Menegon
 * @date    2018-02-25
 */
void processing_received_data(void)
{

  if(Rx_Comm_Serial[1] == TRANSMIT_SET_SPEED_2ND)
  {
    set_ref_speed();
  }
  else if(Rx_Comm_Serial[1] == READ_SET_SPEED_2ND | Rx_Comm_Serial[1] == READ_OPERATION_STATUS_2ND | Rx_Comm_Serial[1] == READ_REAL_SPEED_2ND)
  {
    if(Rx_Comm_Serial[2] == READ_SET_SPEED_3RD)
    {
      transmit_ref_speed();
    }
    else if(Rx_Comm_Serial[2] == READ_OPERATION_STATUS_3RD)
    {
      get_status_serial();
    }
     else if(Rx_Comm_Serial[2] == READ_REAL_SPEED_2ND)
    {
      get_real_speed();
    }
  }
  else if(Rx_Comm_Serial[1] == READ_VARIABLE_2ND)
  {
    get_value_from_variable();
  }
}

/**
 * @brief   Set ref speed through serial comm
 * @details 
 * @author  Victor E. Menegon
 * @date    2018-02-25
 */
void set_ref_speed(void)
{
  uint8_t low_byte;
  uint8_t high_byte;

  low_byte = Rx_Comm_Serial[2];
  high_byte = Rx_Comm_Serial[3];
  uint8_to_uint16(low_byte, high_byte, &Motor_Ref_Speed_Gb);

  Tx_Comm_Serial[0] = RECEPTION_IDENTIFICATION_1ST;
  Tx_Comm_Serial[1] = ANSWER_TRANSMIT_SET_SPEED_2ND;
  Tx_Comm_Serial[2] = low_byte;
  Tx_Comm_Serial[3] = high_byte;
  Tx_Comm_Serial[4] = calc_checksum(Tx_Comm_Serial);
}

/**
 * @brief   Read ref speed through serial comm
 * @details 
 * @author  Victor E. Menegon
 * @date    2018-02-25
 */
void transmit_ref_speed(void)
{
  uint8_t low_byte;
  uint8_t high_byte;

  uint16_to_uint8(Motor_Ref_Speed_Gb, &low_byte, &high_byte);
  
  Tx_Comm_Serial[0] = RECEPTION_IDENTIFICATION_1ST;
  Tx_Comm_Serial[1] = ANSWER_READ_SET_SPEED_2ND;
  Tx_Comm_Serial[2] = low_byte;
  Tx_Comm_Serial[3] = high_byte;
  Tx_Comm_Serial[4] = calc_checksum(Tx_Comm_Serial);
}

/**
 * @brief   Read status
 * @details 
 * @author  Victor E. Menegon
 * @date    2018-02-25
 */
void get_status_serial(void)
{
  Tx_Comm_Serial[0] = RECEPTION_IDENTIFICATION_1ST;
  Tx_Comm_Serial[1] = ANSWER_READ_OPERATION_STATUS_2ND;
  Tx_Comm_Serial[2] = 0x00U;
  Tx_Comm_Serial[3] = 0x00U;
  Tx_Comm_Serial[4] = calc_checksum(Tx_Comm_Serial);
}

/**
 * @brief   Reading value from another variable
 * @details 
 * @author  Victor E. Menegon
 * @date    2018-02-25
 */
void get_value_from_variable(void)
{
  uint8_t low_byte_rx;
  uint8_t high_byte_rx;
  uint8_t low_byte_tx;
  uint8_t high_byte_tx;
  uint16_t variable_address;

  low_byte_rx = Rx_Comm_Serial[2];
  high_byte_rx = Rx_Comm_Serial[3];

  uint8_to_uint16(low_byte_rx, high_byte_rx, &variable_address);
  uint16_t* variable_value = variable_address;
  uint16_to_uint8(*variable_value, low_byte_tx, high_byte_tx);
  
  Tx_Comm_Serial[0] = RECEPTION_IDENTIFICATION_1ST;
  Tx_Comm_Serial[1] = ANSWER_READ_VARIABLE_2ND;
  Tx_Comm_Serial[2] = low_byte_tx;
  Tx_Comm_Serial[3] = high_byte_tx;
  Tx_Comm_Serial[4] = calc_checksum(Tx_Comm_Serial);
}

/**
 * @brief   Send real speed
 * @details 
 * @author  Victor E. Menegon
 * @date    2018-02-25
 */
void get_real_speed(void)
{
  uint8_t low_byte;
  uint8_t high_byte;

  uint16_to_uint8(Motor_Real_Speed_Gb, &low_byte, &high_byte);
  
  Tx_Comm_Serial[0] = RECEPTION_IDENTIFICATION_1ST;
  Tx_Comm_Serial[1] = ANSWER_READ_SET_SPEED_2ND;
  Tx_Comm_Serial[2] = low_byte;
  Tx_Comm_Serial[3] = high_byte;
  Tx_Comm_Serial[4] = calc_checksum(Tx_Comm_Serial);
}

/**
 * @brief   
 * @details 
 * @author  Victor H. B. Preuss
 * @date    2017-09-01
 */
static uint8_t calc_checksum (const uint8_t * p_command)
{
    uint8_t checksum = 0;

    for (int idx = 0; idx < COMMAND_LENGTH_SERIAL_EMBRACO-1; idx++)
    {
        checksum -= (*p_command);
        p_command++;
    }

    return checksum;
}

/**
 * @brief   TX complete callback function.
 * @details 
 * @author  Victor E. Menegon
 * @date    2018-03-14
 */
void HAL_UART_TxCpltCallback (UART_HandleTypeDef *huart)
{
   /* Set transmission complete flag */
    b_transmission_completed = TRUE;
}

/**
 * @brief   RX complete callback function.
 * @details 
 * @author  Victor E. Menegon
 * @date    2018-03-14
 */
void HAL_UART_RxCpltCallback (UART_HandleTypeDef *huart)
{
   /* Set transmission complete flag */
	b_reception_completed = TRUE;
}

/**
  * @brief  This function handles UART interrupt request.  
  * @param  None
  * @retval None
  * @Note       
  */
void USART3_IRQHandler(void)
{
	HAL_UART_IRQHandler(&husart3);
}
