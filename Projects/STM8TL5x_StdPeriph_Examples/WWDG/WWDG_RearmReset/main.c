/**
  ******************************************************************************
  * @file    WWDG/WWDG_RearmReset/main.c
  * @brief   This file contains the main function for WWDG Rearm Reset example.
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
  * @addtogroup WWDG_RearmReset
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Evalboard I/Os configuration */

#define LEDS_PORT (GPIOB)
#define LED1_PIN  (GPIO_Pin_2)
#define LED2_PIN  (GPIO_Pin_3)

#define BUTTONS_PORT (GPIOB)
#define BUTTON1_PIN  (GPIO_Pin_5)
#define BUTTON2_PIN  (GPIO_Pin_6)

#define WINDOW_VALUE        97
#define COUNTER_INIT       104

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO FunctionalState NonAllowedRefresh = DISABLE;
__IO FunctionalState AllowedRefresh = ENABLE;

/* Private function prototypes -----------------------------------------------*/
void Delay (uint16_t nCount);
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

  uint8_t i;
	
  /* Initialization of I/Os for the LEDs */
  GPIO_Init(LEDS_PORT, (LED1_PIN | LED2_PIN), GPIO_Mode_Out_PP_Low_Fast);

  /* LEDs OFF */
  GPIO_SetBits(LEDS_PORT, (LED1_PIN | LED2_PIN));

  /* Initialization of I/O for the button */
  GPIO_Init(BUTTONS_PORT, (BUTTON1_PIN | BUTTON2_PIN), GPIO_Mode_In_PU_IT);

  /* Initialization of the buttons Interrupt sensitivity */
  EXTI_SetPinSensitivity(EXTI_Pin_5, EXTI_Trigger_Falling);
	EXTI_SetPinSensitivity(EXTI_Pin_6, EXTI_Trigger_Falling);
	
  /* Check if the MCU has resumed from WWDG reset */
  if (RST_GetFlagStatus(RST_FLAG_WWDGF) != RESET)
  {
    /* WWDGF flag set */
    /* Toggle LED1 */
    for (i = 8; i != 0; i--)
    {
      GPIO_ToggleBits(LEDS_PORT, LED1_PIN);
      Delay(0x4000);
    }
    /* Clear WWDGF Flag */
    RST_ClearFlag(RST_FLAG_WWDGF);
  }

  /* WWDG configuration: WWDG is clocked by SYSCLK = 2MHz */
  /* WWDG timeout is equal to 251.9 ms */
  /* Watchdog Window = (COUNTER_INIT - 63) * 1 step
                     = 41 * (12288 / 2Mhz)
                     = 251.9 ms
  */
  /* Non Allowed Window = (COUNTER_INIT - WINDOW_VALUE) * 1 step
                        = (104 - 97) * 1 step
                        =  7 * 1 step 
                        =  7 * (12288 / 2Mhz) 
                        =  43.008 ms
   */
  /* So the non allowed window starts from 0.0 ms to 43.008 ms
  and the allowed window starts from 43.008 ms to 251.9 ms
  If refresh is done during non allowed window, a reset will occur.
  If refresh is done during allowed window, no reset will occur.
  If the WWDG down counter reaches 63, a reset will occur. */
  WWDG_Init(COUNTER_INIT, WINDOW_VALUE);

  enableInterrupts();

  while (1)
  {
    
		/* Check if WWDG counter can be refreshed in the Allowed window */
    if (AllowedRefresh == ENABLE)
    {
      /* Wait until WWDG down-counter becomes lower than window value */
      while ((WWDG_GetCounter() & 0x7F) > WINDOW_VALUE);
      /* Refresh WWDG down-counter during the allowed window
			   --> MCU reset will NOT occur */
      WWDG_SetCounter(COUNTER_INIT);
			GPIO_ToggleBits(LEDS_PORT, LED2_PIN);
    }
   
    /* Check if WWDG counter can be refreshed in the non-Allowed window */
    if (NonAllowedRefresh == ENABLE)
    {
      /* Wait until WWDG down-counter becomes higher than window value */
      while ((WWDG_GetCounter() & 0x7F) < WINDOW_VALUE);
      /* Refresh WWDG down-counter during the non-allowed window
         --> MCU reset will occur */
      WWDG_SetCounter(COUNTER_INIT);
			GPIO_ToggleBits(LEDS_PORT, LED2_PIN);
    }
		
    Delay(0x8000);
		
  }
}

/**
  ******************************************************************************
  * @brief  Inserts a delay time.
  * @param  nCount Specifies the delay time length.
  * @retval None
  ******************************************************************************
  */
void Delay(__IO uint16_t nCount)
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
