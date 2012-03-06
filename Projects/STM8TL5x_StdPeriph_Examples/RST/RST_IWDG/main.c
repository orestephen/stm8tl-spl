/**
  ******************************************************************************
  * @file    RST/RST_IWDG/main.c
  * @brief   This file contains the main function for RST IWDG example.
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
  * @addtogroup RST_IWDG
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
/* Global variables ----------------------------------------------------------*/
FunctionalState Refresh;
	
/* Private function prototypes -----------------------------------------------*/
void TIM3_Configuration(void);
void IWDG_Configuration(void);
void Delay (uint16_t nCount);

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
	
	FlagStatus IwdgFlag;
	uint8_t i = 0;

  /* Initialization of I/Os for the LEDs */
  GPIO_Init(LEDS_PORT, (LED1_PIN | LED2_PIN), GPIO_Mode_Out_PP_Low_Fast);

  /* LEDs OFF */
  GPIO_SetBits(LEDS_PORT, (LED1_PIN | LED2_PIN));

  /* Initialization of I/O for the button without interrupt */
  GPIO_Init(BUTTON_PORT, BUTTON_PIN, GPIO_Mode_In_FL_No_IT);

  /* Test if a IWDG Reset has occured */
	IwdgFlag = RST_GetFlagStatus(RST_FLAG_IWDGF);

	if (IwdgFlag)
	{
    for (i=0; i<20; i++)
    {
      GPIO_ToggleBits(LEDS_PORT, (LED1_PIN | LED2_PIN));
      Delay(0x2000);
		}
    /* Clear IWDGF Flag */
    RST_ClearFlag(RST_FLAG_IWDGF);
	}

  /* TIM3 Configuration */
	TIM3_Configuration();

	/* IWDG Configuration */
  IWDG_Configuration();
	
	enableInterrupts();

	/* The IWDG is refreshed periodically by the TIM3 in the
 		 interrupt routine */
	Refresh = ENABLE;

  while (1)
  {
		/* Check if button is pressed */
    if ((GPIO_ReadInputData(BUTTON_PORT) & BUTTON_PIN) == (uint8_t)0x00)
    {
			/* Disable IWDG Refresh by TIM3
			   After a few moment the MCU will reset */
			Refresh = DISABLE;
			GPIO_ResetBits(LEDS_PORT, LED1_PIN); /* LED1 ON */
    }
		/* Normal condition the LED1 blinks while the IWDG is refreshed */
		if (Refresh == ENABLE)
		{
		  GPIO_ToggleBits(LEDS_PORT, LED1_PIN);
      Delay(0xFFFF);
      Delay(0xFFFF);
		}
	}
	
}

/**
  ******************************************************************************
  * @brief Configures the IWDG to generate a Reset if it is not refreched at the correct time.
  * @param None
  * @retval None
  ******************************************************************************
  */
void IWDG_Configuration(void)
{
	
	/* Note: No need to enable the clock for the IWDG */
	
	/* Enable the IWDG */
  IWDG_Enable();

  /* Enable the access to the IWDG registers */
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
  
  /* Fix IWDG Reset period to 1.7s */
  IWDG_SetPrescaler(IWDG_Prescaler_256);
  IWDG_SetReload(0xFF);

  /* Refresh IWDG */
  IWDG_ReloadCounter();
}


/**
  ******************************************************************************
  * @brief Configures the TIM3 to refresh the IWDG periodically.
  * @param None
  * @retval None
  ******************************************************************************
  */
void TIM3_Configuration(void)
{
	
	TIM3_DeInit();
	
	/* Enable TIM3 clock */
	CLK_PeripheralClockConfig(CLK_Peripheral_TIM3, ENABLE);

  /* Time base configuration */
  TIM3_TimeBaseInit(TIM3_Prescaler_128, TIM3_CounterMode_Down, 0xFF);

  /* Enable TIM3 Update Interrupt */
  TIM3_ITConfig(TIM3_IT_Update, ENABLE);
  
  /* Enable TIM3 */
	TIM3_Cmd(ENABLE);
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
