/**
  ******************************************************************************
  * @file    IWDG/IWDG_RearmReset/main.c
  * @brief   This file contains the main function for IWDG Rearm Reset example.
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
  * @addtogroup IWDG_RearmReset
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
#define Key_is_Pressed ((GPIO_ReadInputData(BUTTON_PORT) & BUTTON_PIN) == (uint8_t)0x00)

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void Delay (uint16_t nCount);
void IWDG_Configuration(void);
void Test_IWDGReset(void);


/**
  ******************************************************************************
  * @brief Example main entry point.
  * @param None
  * @retval None
  ******************************************************************************
  */
void main(void)
{
  
  uint8_t i;
	FunctionalState Refresh;

  /* Initialization of I/Os for the LEDs */
  GPIO_Init(LEDS_PORT, (LED1_PIN | LED2_PIN), GPIO_Mode_Out_PP_Low_Fast);

  /* LEDs OFF */
  GPIO_SetBits(LEDS_PORT, (LED1_PIN | LED2_PIN));

  /* Initialization of I/O for the button */
  GPIO_Init(BUTTON_PORT, BUTTON_PIN, GPIO_Mode_In_FL_IT);
  
  /* IWDG Configuration */
  IWDG_Configuration();

  /* Test if a IWDG Reset has occured */
  Test_IWDGReset();

  /* Enable IWDG Refresh */
  Refresh = ENABLE;

  while (1)
  {
		if (Key_is_Pressed)
		{
			/* Disable IWDG Refresh */
			Refresh = DISABLE;
     
			/* LED1 OFF */
			GPIO_SetBits(LEDS_PORT, LED1_PIN);
     
			/* LED2 ON */
			GPIO_ResetBits(LEDS_PORT, LED2_PIN);
	  }
   
   	if (Refresh == ENABLE)
	  {
			/* Refresh IWDG */
			IWDG_ReloadCounter();
    }
  }
	
}

/* Private functions ---------------------------------------------------------*/
void Delay(uint16_t nCount)
{
	/* Decrement nCount value */
  while(nCount != 0)
	{
		nCount--;
	}
}

/**
  ******************************************************************************
  * @brief Configures the IWDG to generate a Reset if it is not refreshed at the correct time.
  * @param None
  * @retval None
  ******************************************************************************
  */
void IWDG_Configuration(void)
{
	/* Enable the IWDG */
	IWDG_Enable();
  
	/* Enable the access to the IWDG registers */
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	
	/* Fix IWDG Reset period
	  fLSI = 38kHz -> TLSI = 26.3µs
		T = 26.3µs x 256 x (255 + 1) = 1.7s
	*/
  IWDG_SetPrescaler(IWDG_Prescaler_256);
	IWDG_SetReload(255);
	
	/* Refresh IWDG */
  IWDG_ReloadCounter();
}


/**
  ******************************************************************************
  * @brief Tests if an IWDG Reset occured. If Yes, toggle LED1 few times.
  * @param None
  * @retval None
  ******************************************************************************
  */
void Test_IWDGReset(void)
{
  FlagStatus IwdgFlag;
	uint8_t i;
  
  /* Get IWDG Reset Status */ 
	IwdgFlag = RST_GetFlagStatus(RST_FLAG_IWDGF);

  /* Toggle LED1 and LED2 if a IWDG Reset has occured
	   otherwise toggle LED1 only */
	if (IwdgFlag)
  {
		for (i=0; i<4; i++)
		{
			GPIO_ToggleBits(LEDS_PORT, (LED1_PIN | LED2_PIN));
			Delay(0x8000);
		}
    /* Clear IWDGF Flag */
		RST_ClearFlag(RST_FLAG_IWDGF);
	}
	else
	{
		GPIO_ResetBits(LEDS_PORT, LED1_PIN);
		Delay(0x8000);
		GPIO_SetBits(LEDS_PORT, LED1_PIN);
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
