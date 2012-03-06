/**
  ******************************************************************************
  * @file    TIM2/TIM2_OC_InactiveMode/main.c
  * @brief   This file contains the main function for TIM2 OC_InactiveMode example
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
  * @addtogroup TIM2_OC_InactiveMode
  * @{
  */

/* Private defines -----------------------------------------------------------*/
#define CCR1_Val  ((uint16_t)15625)
#define CCR2_Val  ((uint16_t)7812)

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

  /* Enable TIM2 clock */
	CLK_PeripheralClockConfig(CLK_Peripheral_TIM2, ENABLE);
	
  /* Configure GPIOA.6 pin to be used as a Trigger for the oscilloscope */
  GPIO_Init(GPIOA, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Fast);

	/* Configure GPIOB.4 and GPIOB.5 pins for debug */
	GPIO_Init(GPIOB, (GPIO_Pin_4 | GPIO_Pin_5), GPIO_Mode_Out_PP_Low_Fast);

  /* Time base configuration */
	TIM2_TimeBaseInit(TIM2_Prescaler_128, TIM2_CounterMode_Up, 65535);

  /* Prescaler configuration */
	TIM2_PrescalerConfig(TIM2_Prescaler_128, TIM2_PSCReloadMode_Immediate);
	
  /* Output Compare Active Mode configuration: Channel1 */
  TIM2_OC1Init(TIM2_OCMode_Inactive, TIM2_OutputState_Enable, CCR1_Val, TIM2_OCPolarity_High, TIM2_OCIdleState_Reset); 
  
  TIM2_OC1PreloadConfig(DISABLE);

  /* Output Compare Active Mode configuration: Channel2 */
  TIM2_OC2Init(TIM2_OCMode_Inactive, TIM2_OutputState_Enable, CCR2_Val, TIM2_OCPolarity_High, TIM2_OCIdleState_Reset); 
  
  TIM2_OC2PreloadConfig(DISABLE);

  TIM2_ARRPreloadConfig(ENABLE);
  
  /* Enable TIM2 Capture Compare interrupts */
  TIM2_ITConfig(TIM2_IT_CC1, ENABLE);
  TIM2_ITConfig(TIM2_IT_CC2, ENABLE);

  /* Set Trigger */
	GPIO_SetBits(GPIOA, GPIO_Pin_6);

  /* Enable TIM2 outputs */
	TIM2_CtrlPWMOutputs(ENABLE);
	
  /* TIM2 enable counter */
  TIM2_Cmd(ENABLE);

  enableInterrupts();

  while (1)
	{
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
