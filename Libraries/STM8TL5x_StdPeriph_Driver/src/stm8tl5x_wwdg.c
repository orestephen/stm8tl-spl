/**
  ********************************************************************************
  * @file    stm8tl5x_wwdg.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    01-March-2012
  * @brief   This file contains all the functions for the WWDG peripheral.
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
#include "stm8tl5x_wwdg.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BIT_MASK          ((uint8_t)0x7F)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/** @addtogroup WWDG_Public_Functions
  * @{
  */

/**
  * @brief Initializes the WWDG peripheral.
  * @param[in] Counter     WWDG counter value
  * @param[in] WindowValue Specifies the WWDG Window Register (value between 0x00 to 0x7F)
  * @retval None
  * @note This function set Window Register = WindowValue, Counter Register
  * according to Counter and \b ENABLE the WWDG.
  */
void WWDG_Init(uint8_t Counter, uint8_t WindowValue)
{
  /* Check the parameters */
  assert_param(IS_WWDG_WINDOW_LIMIT_VALUE(WindowValue));
  WWDG->WR = WWDG_WR_RESET_VALUE;
  WWDG->CR = (uint8_t)(WWDG_CR_WDGA | Counter);
  WWDG->WR = (uint8_t)((uint8_t)BIT_MASK & (uint8_t) WindowValue);
}

/**
  * @brief Enables WWDG and load the counter value.
  * @param[in] Counter Specifies the watchdog counter value (value between 0x40 and 0x7F).
  * @retval None
  */
void WWDG_Enable(uint8_t Counter)
{
  /* Check the parameters */
  assert_param(IS_WWDG_COUNTER_VALUE(Counter));
  WWDG->CR = (uint8_t)(WWDG_CR_WDGA | Counter);
}

/**
  * @brief Refreshs the WWDG peripheral.
  * @param[in] Counter Specifies the watchdog counter value (value between 0x40 and 0x7F).
  * @retval None
  */
void WWDG_SetCounter(uint8_t Counter)
{
  /* Check the parameters */
  assert_param(IS_WWDG_COUNTER_VALUE(Counter));

  /* Write to T[6:0] bits to configure the counter value, no need to do
     a read-modify-write; writing a 0 to WDGA bit does nothing */
  WWDG->CR = (uint8_t)(Counter & (uint8_t)BIT_MASK);
}

/**
  * @brief Gets the WWDG Counter Value.
  * @param None
  * @retval uint8_t Counter Value
  * @note This value could be used to check if the WWDG counter is in the window, where
  * refresh is allowed.
  */
uint8_t WWDG_GetCounter(void)
{
  return(WWDG->CR);
}

/**
  * @brief Generates immediate WWDG RESET.
  * @param None
  * @retval None
  */
void WWDG_SWReset(void)
{
  WWDG->CR = WWDG_CR_WDGA; /* Activate WWDG, with clearing T6 */
}

/**
  * @brief Sets the WWDG window value.
  * @param[in] WindowValue Specifies the window value to be compared to the downcounter (must be lower than 0x80).
  * @retval None
  */
void WWDG_SetWindowValue(uint8_t WindowValue)
{
  __IO uint8_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_WWDG_WINDOW_LIMIT_VALUE(WindowValue));

  /* Set W[6:0] bits according to WindowValue value */
  tmpreg |= (uint8_t)(WindowValue & (uint8_t) BIT_MASK);

  /* Store the new value */
  WWDG->WR = tmpreg;
}

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
