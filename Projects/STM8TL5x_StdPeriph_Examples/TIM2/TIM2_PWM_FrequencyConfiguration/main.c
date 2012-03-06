/**
  ******************************************************************************
  * @file    TIM2/TIM2_PWM_FrequencyConfiguration/main.c
  * @brief   This file contains the main function for TIM2 PWM  Frequency Configuration example
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
  * @addtogroup TIM2_PWM_FrequencyConfiguration
  * @{
  */

__IO uint16_t CCR1_Val = 32768;
__IO uint16_t CCR2_Val = 16384;

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

  /* Enable TIM2 clock */
	CLK_PeripheralClockConfig(CLK_Peripheral_TIM2, ENABLE);

	/* Config TIM2 Channel 1 and channel 2 pins */
	GPIO_Init(GPIOD, (GPIO_Pin_4 | GPIO_Pin_5), GPIO_Mode_Out_PP_High_Fast);

  /* Time base configuration */
  /*
	    TIM2_Prescaler = TIM2_Prescaler_2
	    TIM2_Period = 65535
	*/
	TIM2_TimeBaseInit(TIM2_Prescaler_2, TIM2_CounterMode_Up, 65535);

  /* Used to set the UG bit in TIM2_UGR register */
  TIM2_PrescalerConfig(TIM2_Prescaler_2, TIM2_PSCReloadMode_Immediate);

  /* Output Compare Toggle Mode configuration: Channel1 */
	/*
      TIM2_OCMode = TIM2_OCMode_Toggle
      TIM2_OutputState = TIM2_OutputState_Enable
      TIM2_Pulse = CCR1_Val
      TIM2_OCPolarity = TIM2_OCPolarity_Low
	*/
  TIM2_OC1Init(TIM2_OCMode_Toggle, TIM2_OutputState_Enable, CCR1_Val, TIM2_OCPolarity_Low, TIM2_OCIdleState_Set);

  TIM2_OC1PreloadConfig(DISABLE);

  /* Output Compare Toggle Mode configuration: Channel2 */
  /*TIM2_Pulse = CCR2_Val*/
  TIM2_OC2Init(TIM2_OCMode_Toggle, TIM2_OutputState_Enable, CCR2_Val, TIM2_OCPolarity_Low, TIM2_OCIdleState_Set); 
	
  TIM2_OC2PreloadConfig(DISABLE);

  /* TIM2 IT enable */
  TIM2_ITConfig(TIM2_IT_CC1, ENABLE);
  TIM2_ITConfig(TIM2_IT_CC2, ENABLE);
	
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
