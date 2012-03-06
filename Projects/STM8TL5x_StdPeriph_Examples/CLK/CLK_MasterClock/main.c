/**
  ******************************************************************************
  * @file    CLK/CLK_MasterClock/main.c
  * @brief   This file contains the main function for CLK example
  * @author  STMicroelectronics - MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8tl5x.h"

/**
  * @addtogroup CLK_MasterClock
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Evalboard I/Os configuration */

#define LEDS_PORT (GPIOB)
#define LED1_PIN  (GPIO_Pin_2)
#define LED2_PIN  (GPIO_Pin_3)

#define BUTTON_PORT (GPIOB)
#define BUTTON_PIN  (GPIO_Pin_5)


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Delay (uint16_t nCount);

/* Private functions ---------------------------------------------------------*/
/* Global variables ----------------------------------------------------------*/
bool ButtonPressed = FALSE;

/* Public functions ----------------------------------------------------------*/

/**
  ******************************************************************************
  * @brief Example main entry point.
  * @param None
  * @retval None
  ******************************************************************************
  */
void main(void)
{
  
	uint8_t action = 0;
	
  /* Configure the CCO I/O */
  GPIO_ExternalPullUpConfig(GPIOA, GPIO_Pin_6, ENABLE);

  /* Initialization of I/Os for the LEDs */
  GPIO_Init(LEDS_PORT, (LED1_PIN | LED2_PIN), GPIO_Mode_Out_PP_Low_Fast);
   
  /* LED1 ON */
  GPIO_ResetBits(LEDS_PORT, LED1_PIN);
  /* LED2 OFF */
  GPIO_SetBits(LEDS_PORT, LED2_PIN);

  /* Initialization of I/O for the button */
  GPIO_Init(BUTTON_PORT, BUTTON_PIN, GPIO_Mode_In_FL_IT);

  /* Initialization of the Interrupt sensitivity for the button */
  EXTI_SetPinSensitivity(EXTI_Pin_5, EXTI_Trigger_Falling);
  
  /* Select and enable Master clock output on CCO pin */
  CLK_CCOConfig(CLK_Output_ClockMaster);
	
  enableInterrupts();

  while (1)
	{
    /* Check button status */
    if (ButtonPressed == TRUE) /* Button is pressed */
    {
			disableInterrupts();
      ButtonPressed = FALSE;
			/* Change Clock divider */
      switch (action)
			{
        case 0:
				  /* Clock divider to HSI/4 (4 MHz) */
          CLK_MasterPrescalerConfig(CLK_MasterPrescaler_HSIDiv4);
          action = 1;
				  break;
        case 1:
					/* Clock divider to HSI/2 (8 MHz) */
          CLK_MasterPrescalerConfig(CLK_MasterPrescaler_HSIDiv2);
          action = 2;
				  break;					
        case 2:
					/* Clock divider to HSI/1 (16 MHz) */
          CLK_MasterPrescalerConfig(CLK_MasterPrescaler_HSIDiv1);
          action = 3;
				  break;
        case 3:
					/* Clock divider to HSI/8 (2 MHz - default after Reset) */
          CLK_MasterPrescalerConfig(CLK_MasterPrescaler_HSIDiv8);
          action = 0;
				  break;					
        default:
			    break;
      }
			enableInterrupts();
    }
		
	  GPIO_ToggleBits(LEDS_PORT, (LED1_PIN | LED2_PIN));
	  Delay((uint16_t)60000);
  }
}

/**
  ******************************************************************************
  * @brief Delay.
  * @param[in] nCount
  * @retval None
  ******************************************************************************
  */
void Delay(uint16_t nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}

#ifdef  USE_FULL_ASSERT

/**
  ******************************************************************************
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file Pointer to the source file name
  * @param line assert_param error line source number
  * @retval None
  ******************************************************************************
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
