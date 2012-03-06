/**
  ******************************************************************************
  * @file    stm8tl5x_wfe.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    01-March-2012
  * @brief   This file contains all the functions for the WFE peripheral.
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
#include "stm8tl5x_wfe.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/** @addtogroup WFE_Public_Functions
  * @{
  */

/**
  * @brief Deinitializes the WFE registers to their default reset value.
  * @param None
  * @retval None
  */
void WFE_DeInit(void)
{
  WFE->CR1 = WFE_CR1_RESET_VALUE;
  WFE->CR2 = WFE_CR2_RESET_VALUE;
}

/**
  * @brief Set the source that can generate the wake-up event.
  * @param[in] WFE_Source The wake-up event source
  * @param[in] NewState The source wake up new state.
  */
void WFE_WakeUpSourceEventCmd(WFE_Source_TypeDef WFE_Source, FunctionalState NewState)
{
  uint8_t register_index = 0;
  /* Check function parameters */
  assert_param(IS_WFE_SOURCE_OK(WFE_Source));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* The mask is reversed in order to  */
  register_index = (uint8_t)((uint16_t)WFE_Source >> (uint8_t)0x08);

  if (NewState != DISABLE)
  {
    switch (register_index)
    {
      case 1:
        WFE->CR1 |= (uint8_t)WFE_Source;
        break;

      case 2:
        WFE->CR2 |= (uint8_t)WFE_Source;
        break;

      default:
        break;
    }
  }
  else
  {
    switch (register_index)
    {
      case 1:
        WFE->CR1 &= (uint8_t)(~(uint8_t)WFE_Source);
        break;

      case 2:
        WFE->CR2 &= (uint8_t)(~(uint8_t)WFE_Source);
        break;

      default:
        break;
    }
  }
}

/**
  * @brief Get the status of the specified source event.
  * @param[in] WFE_Source The wake-up event source.
  * @retval FunctionalState Source Event state.
  */
FunctionalState WFE_GetWakeUpSourceEventStatus(WFE_Source_TypeDef WFE_Source)
{
  FunctionalState status = DISABLE;
  /* Check function parameters */
  assert_param(IS_WFE_SOURCE_OK(WFE_Source));

  switch (WFE_Source)
  {
    case WFE_Source_TIM2_EV0:
    case WFE_Source_TIM2_EV1:
    case WFE_Source_PXS_EV0:
    case WFE_Source_EXTI_EV0:
    case WFE_Source_EXTI_EV1:
    case WFE_Source_EXTI_EV2:
    case WFE_Source_EXTI_EV3:

      if ((WFE->CR1 & (uint8_t)WFE_Source) != (uint8_t)0x00)
      {
        /* The wake-up event source is enabled*/
        status = ENABLE;
      }
      else
      {
        /* The wake-up event source is disabled*/
        status = DISABLE;
      }
      break;

    case WFE_Source_EXTI_EV4:
    case WFE_Source_EXTI_EV5:
    case WFE_Source_EXTI_EV6:
    case WFE_Source_EXTI_EV7:
    case WFE_Source_EXTI_EVB:
    case WFE_Source_EXTI_EVD:

      if ((WFE->CR2 & (uint8_t)WFE_Source) != (uint8_t)0x00)
      {
        /* The wake-up event source is enabled*/
        status = ENABLE;
      }
      else
      {
        /* The wake-up event source is disabled*/
        status = DISABLE;
      }
      break;
    default:
      break;
  }
  return status;
}

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
