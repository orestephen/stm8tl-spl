/**
  ******************************************************************************
  * @file    TIM4/TIM4_TimeBase_InterruptConfiguration/main.c
  * @brief   This file contains the main function for TIM4 Time Base Configuration example.
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
  * @addtogroup TIM4_TimeBase_InterruptConfiguration
  * @{
  */

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  ******************************************************************************
  * @brief Example main entry point.
  * @param None
  * @retval None
  ******************************************************************************
  */
void main(void)
{
	
	/* Enable TIM4 CLK */
	CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, ENABLE);
	
  TIM4_DeInit();
  
  /* Time base configuration */ 
  TIM4_TimeBaseInit(TIM4_Prescaler_1, 0xFF);
  TIM4_ITConfig(TIM4_IT_Update, ENABLE);
	
  enableInterrupts();

	/* Initialize I/Os in Output Mode for debug */
  GPIO_Init(GPIOA, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Fast);

  /* Enable TIM4 */
  TIM4_Cmd(ENABLE);
	
  /* Toggles GPIOA.6 in ISR routine*/
  while (1)
	{
	}
	
}

#ifdef  USE_FULL_ASSERT

/**
  ******************************************************************************
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file pointer to the source file name
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
