/**
  ********************************************************************************
  * @file    stm8tl5x_iwdg.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    01-March-2012
  * @brief   This file contains all the functions for the IWDG peripheral.
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
#include "stm8tl5x_iwdg.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/** @addtogroup IWDG_Public_Functions
  * @{
  */

/**
  * @brief Enables or disables write access to Prescaler and Reload registers.
  * @param[in] IWDG_WriteAccess New state of write access to Prescaler and Reload registers.
  * @retval None
  */
void IWDG_WriteAccessCmd(IWDG_WriteAccess_TypeDef IWDG_WriteAccess)
{
  /* Check the parameters */
  assert_param(IS_IWDG_WRITEACCESS_MODE(IWDG_WriteAccess));
  IWDG->KR = (uint8_t)IWDG_WriteAccess; /* Write Access */
}

/**
  * @brief Sets IWDG Prescaler value.
  * @param[in] IWDG_Prescaler Specifies the IWDG Prescaler value.
  * @retval None
  * @note The WDG write access must be enabled.
  */
void IWDG_SetPrescaler(IWDG_Prescaler_TypeDef IWDG_Prescaler)
{
  /* Check the parameters */
  assert_param(IS_IWDG_PRESCALER_VALUE(IWDG_Prescaler));
  IWDG->PR = (uint8_t)IWDG_Prescaler;
}

/**
  * @brief Sets IWDG Reload value.
  * @param[in] IWDG_Reload The Reload register value.
  * This parameter must be a number between 0 and 255.
  * @retval None
  * @note The WDG write access must be enabled.
  */
void IWDG_SetReload(uint8_t IWDG_Reload)
{
  IWDG->RLR = IWDG_Reload;
}

/**
  * @brief Reload IWDG counter
  * @param None
  * @retval None
  * @note The WDG write access must be enabled.
  */
void IWDG_ReloadCounter(void)
{
  IWDG->KR = IWDG_KEY_REFRESH;
}

/**
  * @brief Enable IWDG registers access.
  * @param None
  * @retval None
  */
void IWDG_Enable(void)
{
  IWDG->KR = IWDG_KEY_ENABLE;
}

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
