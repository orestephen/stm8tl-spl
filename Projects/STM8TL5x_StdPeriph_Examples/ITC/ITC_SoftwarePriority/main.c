/**
  ******************************************************************************
  * @file    ITC/ITC_SoftwarePriority/main.c
  * @brief   This file contains the main function for the ITC software priority example.
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
#include "main.h"

/**
  * @addtogroup ITC_SoftwarePriority
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Global variables ----------------------------------------------------------*/

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
 
  /* Initialization of I/Os for the LEDs */
  GPIO_Init(LEDS_PORT, (LED1_PIN | LED2_PIN), GPIO_Mode_Out_PP_Low_Fast);

  /* Initialization of I/O for the buttons */
  GPIO_Init(BUTTONS_PORT, (BUTTON1_PIN | BUTTON2_PIN), GPIO_Mode_In_FL_IT);

  /* Initialization of the Interrupt sensitivity for the buttons */
  EXTI_SetPinSensitivity(EXTI_Pin_5, EXTI_Trigger_Falling_Low);
  EXTI_SetPinSensitivity(EXTI_Pin_6, EXTI_Trigger_Falling_Low);

  /*
    Change the software priority between the two buttons:
    - By hardware the Pin_5 (button1) has a higher priority than Pin_6 (button2)
    - We configure the Pin_6 (button2) to have a higher sw priority than Pin_5 (button1)
  */
  ITC_SetSoftwarePriority(EXTI5_IRQn, ITC_PriorityLevel_1);
  ITC_SetSoftwarePriority(EXTI6_IRQn, ITC_PriorityLevel_2); /* button2 has higher sw priority */

  /* LEDs are ON */
  GPIO_ResetBits(LEDS_PORT, (LED1_PIN | LED2_PIN));
 
  enableInterrupts();

  while (1)
  {
    /* The LEDs toggles in the interrupt routines */
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
