/**
  ******************************************************************************
  * @file    stm8tl5x_rst.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    01-March-2012
  * @brief   This file contains all the functions for the RST peripheral.
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

#include "stm8tl5x_rst.h"

/* Private typedef -----------------------------------------------------------*/

/**
  * @addtogroup RST_Private_Define
  * @{
  */

#define RST_CR_MASK  0xD0 /*!< Enable the GPIO */

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private Constants ---------------------------------------------------------*/

/**
  * @addtogroup RST_Public_Functions
  * @{
  */

/**
  * @brief Checks whether the specified RST flag is set or not.
  * @param[in] RST_Flag Specify the reset flag to check.
  * @retval FlagStatus Status of the given RST flag.
  */
FlagStatus RST_GetFlagStatus(RST_Flag_TypeDef RST_Flag)
{
  /* Check the parameters */
  assert_param(IS_RST_FLAG(RST_Flag));

  /* Get flag status */

  return ((FlagStatus)((uint8_t)RST->SR & (uint8_t)RST_Flag));
}

/**
  * @brief Clears the specified RST flag.
  * @param[in] RST_Flag Specify the reset flag to clear.
  * @retval None
  */
void RST_ClearFlag(RST_Flag_TypeDef RST_Flag)
{
  /* Check the parameters */
  assert_param(IS_RST_FLAG(RST_Flag));

  RST->SR = (uint8_t)RST_Flag;
}

/**
  * @brief Configure the reset pad as GP output.
  * @param None
  * @retval None
  */
void RST_GPOutputEnable(void)
{

  RST->CR = RST_CR_MASK;
}

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
