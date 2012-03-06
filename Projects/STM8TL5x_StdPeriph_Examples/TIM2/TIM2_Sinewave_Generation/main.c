/**
  ******************************************************************************
  * @file    TIM2/TIM2_Sinewave_Generation/main.c
  * @brief   This file contains the main function for TIM2 Sinewave_Generation example.
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

__IO MySin_Typedef sin ;/* Stores the sin structure */
__IO uint8_t counter ;	 /* The counter variable for counting the Update cycles in TIM2 */

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @addtogroup TIM2_Sinewave_Generation
  * @{
  */

/* This shows the value of the samples for the different no of samples in half
sine wave. The last value corresponds to the amplitude of the sine wave.*/

#if	nbr_of_samples_half == 16
__CONST uint8_t sample[9]={0,20,38,56,71,83,92,98,100};

#elif	nbr_of_samples_half == 18
__CONST uint8_t sample[10]={0,17,34,50,64,76,86,93,97,99};

#elif	nbr_of_samples_half == 22
__CONST uint8_t sample[12]={0,14,28,42,54,65,76,84,91,96,99,100};

#elif	nbr_of_samples_half == 24
__CONST uint8_t sample[13]={0,13,25,38,49,60,69,78,85,91,95,97,98};

#elif	nbr_of_samples_half == 26
__CONST uint8_t sample[14]={0,12,24,35,46,56,66,74,81,88,93,96,98,99};

#elif	nbr_of_samples_half == 28
__CONST uint8_t sample[15]={0,11,22,33,43,53,62,71,78,85,90,94,97,99,100};

#elif 	nbr_of_samples_half == 30 
__CONST uint8_t sample[16]={0,10,21,31,41,50,59,67,74,81,87,91,95,98,99,100};

#elif	nbr_of_samples_half == 46
__CONST uint8_t sample[24]={0,7,13,20,26,33,39,45,51,57,62,67,72,76,80,84,87,90,92, \
								     94,96,97,98,98};
#endif

/* Private defines -----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void LoadValueIntoSinStruct(void);
void TIMER_Init(void);

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
  
	/* Select Clock = 4 MHz */
	CLK_MasterPrescalerConfig(CLK_MasterPrescaler_HSIDiv4);
  
	/* Init counter */
  counter = 0;
	
	/* Call LoadValueIntoSinStruct() & TIMER_Init()*/
  LoadValueIntoSinStruct();           

  TIMER_Init();

  enableInterrupts();  			
  
  while(1)
	{
	}
	
}  


/* Private functions ---------------------------------------------------------*/

void LoadValueIntoSinStruct(void)
{
  uint8_t	offset=0, diff=0;
	
  while(offset <= (nbr_of_samples_half/2))
  {
    /*First half of upper half samples of sine wave is loaded into "value" of sin structure.*/
	   sin.Value[offset] = sample[offset]; 
	   offset++;				            	
  }
  
	diff = (uint8_t)(offset - 1);
  
	while(offset < nbr_of_samples_half)
  {                                    
	    diff--;	
	    /* Second half of upper half samples of sine wave is loaded into "value" of sin structure.*/
	    sin.Value[offset] = sample[diff];		
	    offset++;				                 
  }
  
	/*Index is initialized to 0.Sin wave upper half is generated at start*/
  sin.Index = 0;                      
  sin.Up = TRUE;                      
}

void TIMER_Init(void)
{
	/* Enable TIM2 clock */
	CLK_PeripheralClockConfig(CLK_Peripheral_TIM2, ENABLE);
	
	/* Configure TIM2 Channel 1 pin */
	GPIO_Init(GPIOD, GPIO_Pin_4, GPIO_Mode_Out_PP_High_Fast);
	
	TIM2_DeInit();
	
	/* Time base configuration */
  TIM2_TimeBaseInit(0, TIM2_CounterMode_Up, INIT_TIM2_ARR);
	
	/* PWM configuration */
  TIM2_OC1Init(TIM2_OCMode_PWM1, TIM2_OutputState_Enable,INIT_TIM2_CCR1, TIM2_OCPolarity_Low, TIM2_OCIdleState_Reset);
	
	/* Update Interrupt Enable */
	TIM2_ITConfig(TIM2_IT_Update, ENABLE);
	
	/* ARRPreload Enable */
	TIM2_ARRPreloadConfig(ENABLE);
	
	/* Enable TIM2 */
	TIM2_Cmd(ENABLE);
	
	/* Enable CC1 output*/
	TIM2_CtrlPWMOutputs(ENABLE);
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
