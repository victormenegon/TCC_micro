/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "GPIO_Config.h"
#include "ADC_Config.h"
#include "Serial_Comm.h"
#include "PWM.h"

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart3;

/* Global variables ---------------------------------------------------------*/
volatile uint16_t Motor_Ref_Speed_Gb;
volatile uint16_t Motor_Real_Speed_Gb;
volatile uint8_t fl_over_voltage = 0;
volatile uint16_t V_Bus_Max;

/* Private function prototypes -----------------------------------------------*/

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  SystemClock_Config();

  /* Initialize all configured peripherals */
  GPIO_Init();
  HAL_ADC_MspInit();
  Serial_Comm_Init();
  MX_ADC1_Init();
  MX_ADC2_Init(); 
  MX_TIM1_Init();
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    if(V_Bus_Avg_Gb >= V_Bus_Max)
        {
          fl_over_voltage = 1;
          PWM_Outputs_Disable_Mc;				/*Open PWM OUTPUTS*/
        }

    Serial_Comm_Main();
    ADC_main();
    
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */