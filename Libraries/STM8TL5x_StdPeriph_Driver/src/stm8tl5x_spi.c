/**
  ******************************************************************************
  * @file    stm8tl5x_spi.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    01-March-2012
  * @brief   This file contains all the functions for the SPI peripheral.
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
#include "stm8tl5x_spi.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/** @addtogroup SPI_Public_Functions
  * @{
  */

/**
  * @brief Deinitializes the SPI peripheral registers to their default reset values.
  * @param None
  * @retval None
  */
void SPI_DeInit(void)
{
  SPI->CR1 = SPI_CR1_RESET_VALUE;
  SPI->CR2 = SPI_CR2_RESET_VALUE;
  SPI->ICR = SPI_ICR_RESET_VALUE;
  SPI->SR = SPI_SR_RESET_VALUE;
}

/**
  * @brief Initializes the SPI according to the specified parameters.
  * @param[in] SPI_FirstBit           Select if the MSB or LSB is transmitted first
  * @param[in] SPI_BaudRatePrescaler  Select the baud rate prescaler
  * @param[in] SPI_Mode               Select the master or slave configuration
  * @param[in] SPI_CPOL               Select the polarity of the signals
  * @param[in] SPI_CPHA               Select the phase of the signals
  * @param[in] SPI_DirectionMode      Select the number of lines used and TX or RX
  * @param[in] SPI_NSS                Select the type of the NSS pin (HW or SW)
  * @retval None
  */
void SPI_Init(SPI_FirstBit_TypeDef SPI_FirstBit, SPI_BaudRatePrescaler_TypeDef SPI_BaudRatePrescaler,
              SPI_Mode_TypeDef SPI_Mode, SPI_CPOL_TypeDef SPI_CPOL, SPI_CPHA_TypeDef SPI_CPHA,
              SPI_DirectionMode_TypeDef SPI_DirectionMode, SPI_NSS_TypeDef SPI_NSS)
{

  /* Check structure elements */
  assert_param(IS_SPI_FIRST_BIT(SPI_FirstBit));
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
  assert_param(IS_SPI_MODE(SPI_Mode));
  assert_param(IS_SPI_CPOL(SPI_CPOL));
  assert_param(IS_SPI_CPHA(SPI_CPHA));
  assert_param(IS_SPI_DIRECTION_MODE(SPI_DirectionMode));
  assert_param(IS_SPI_NSS(SPI_NSS));

  /* Frame Format, BaudRate, Clock Polarity and Phase configuration */
  SPI->CR1 = (uint8_t)((uint8_t)(SPI_FirstBit) |
                       (uint8_t)(SPI_BaudRatePrescaler) |
                       (uint8_t)(SPI_CPOL) |
                       (uint8_t)(SPI_CPHA));

  /* Data direction configuration: BDM, BDOE and RXONLY bits */
  SPI->CR2 = (uint8_t)((uint8_t)(SPI_DirectionMode) | (uint8_t)(SPI_NSS));

  if (SPI_Mode == SPI_Mode_Master)
  {
    SPI->CR2 |= (uint8_t)SPI_CR2_SSI;
  }
  else
  {
    SPI->CR2 &= (uint8_t)~(SPI_CR2_SSI);
  }

  /* Master/Slave mode configuration */
  SPI->CR1 |= (uint8_t)(SPI_Mode);
}

/**
  * @brief Enables or disables the specified SPI peripheral.
  * @param[in] NewState New state of the SPI peripheral.
  * @retval None
  */
void SPI_Cmd(FunctionalState NewState)
{

  /* Check function parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    SPI->CR1 |= SPI_CR1_SPE; /* Enable the SPI peripheral */
  }
  else
  {
    SPI->CR1 &= (uint8_t)(~SPI_CR1_SPE); /* Disable the SPI peripheral */
  }

}

/**
  * @brief Enables or disables the specified interrupts.
  * @param[in] SPI_IT   Specifies the SPI interrupts sources to be enabled or disabled.
  * @param[in] NewState The new state of the specified SPI interrupts.
  * @retval None
  */
void SPI_ITConfig(SPI_IT_TypeDef SPI_IT, FunctionalState NewState)
{
  uint8_t itpos = 0;
  /* Check function parameters */
  assert_param(IS_SPI_CONFIG_IT(SPI_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Get the SPI IT index */
  itpos = (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)SPI_IT & (uint8_t)0x0F));

  if (NewState != DISABLE)
  {
    SPI->ICR |= itpos; /* Enable interrupt*/
  }
  else
  {
    SPI->ICR &= (uint8_t)(~itpos); /* Disable interrupt*/
  }
}

/**
  * @brief Transmits a Data through the SPI peripheral.
  * @param[in] Data Byte to be transmitted.
  * @retval None
  */
void SPI_SendData(uint8_t Data)
{
  SPI->DR = Data; /* Write in the DR register the data to be sent*/
}

/**
  * @brief Returns the most recent received data by the SPI peripheral.
  * @param None
  * @retval uint8_t The value of the received data.
  */
uint8_t SPI_ReceiveData(void)
{
  return ((uint8_t)SPI->DR); /* Return the data in the DR register */
}

/**
  * @brief Configures internally by software the NSS pin.
  * @param[in] NewState Indicates the new state of the SPI Software slave management.
  * @retval None
  * @note This function is used only when SPI NSS software mode is enabled
  */
void SPI_NSSInternalSoftwareCmd(FunctionalState NewState)
{

  /* Check function parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    SPI->CR2 |= SPI_CR2_SSI; /* Set NSS pin internally by software */
  }
  else
  {
    SPI->CR2 &= (uint8_t)(~SPI_CR2_SSI); /* Reset NSS pin internally by software */
  }

}

/**
  * @brief Selects the data transfer direction in bi-directional mode.
  * @param[in] SPI_Direction Specifies the data transfer direction in bi-directional mode.
  * @retval None
  */
void SPI_BiDirectionalLineConfig(SPI_Direction_TypeDef SPI_Direction)
{

  /* Check function parameters */
  assert_param(IS_SPI_DIRECTION(SPI_Direction));
  if (SPI_Direction != SPI_Direction_Rx)
  {
    SPI->CR2 |= SPI_CR2_BDOE; /* Set the Tx only mode*/
  }
  else
  {
    SPI->CR2 &= (uint8_t)(~SPI_CR2_BDOE); /* Set the Rx only mode*/
  }
}

/**
  * @brief Checks whether the specified SPI flag is set or not.
  * @param[in] SPI_FLAG Specifies the flag to check.
  * @retval FlagStatus Indicates the state of SPI_FLAG.
  */

FlagStatus SPI_GetFlagStatus(SPI_FLAG_TypeDef SPI_FLAG)
{
  FlagStatus status = RESET;
  /* Check parameters */
  assert_param(IS_SPI_FLAG(SPI_FLAG));

  /* Check the status of the specified SPI flag */
  if ((SPI->SR & (uint8_t)SPI_FLAG) != (uint8_t)RESET)
  {
    status = SET; /* SPI_FLAG is set */
  }
  else
  {
    status = RESET; /* SPI_FLAG is reset*/
  }

  /* Return the SPI_FLAG status */
  return status;
}

/**
  * @brief Clears the WKUP (Wake-up) flag.
  * @param None
  * @retval None
  * @note
  * - OVR (OverRun Error) interrupt pending bit is cleared by software sequence:
  *   a read operation to SPI_DR register (SPI_ReceiveData()) followed by
  *   a read operation to SPI_SR register (SPI_GetFlagStatus()).
  * - MODF (Mode Fault) interrupt pending bit is cleared by software sequence:
  *   a read/write operation to SPI_SR register (SPI_GetFlagStatus()) followed by
  *   a write operation to SPI_CR1 register (SPI_Cmd() to enable the SPI).
  */
void SPI_ClearFlag(void)
{
  /* Clear the flag bit */
  SPI->SR = (uint8_t)(~SPI_SR_WKUP);
}

/**
  * @brief Checks whether the specified interrupt has occurred or not.
  * @param[in] SPI_IT Specifies the SPI interrupt pending bit to check.
  * @retval ITStatus Indicates the state of the SPI_IT.
  */
ITStatus SPI_GetITStatus(SPI_IT_TypeDef SPI_IT)
{
  ITStatus pendingbitstatus = RESET;
  uint8_t itpos = 0;
  uint8_t itmask1 = 0;
  uint8_t itmask2 = 0;
  uint8_t enablestatus = 0;
  assert_param(IS_SPI_GET_IT(SPI_IT));
  /* Get the SPI IT index */
  itpos = (uint8_t)((uint8_t)1 << ((uint8_t)SPI_IT & (uint8_t)0x0F));

  /* Get the SPI IT mask */
  itmask1 = (uint8_t)((uint8_t)SPI_IT >> (uint8_t)4);
  /* Set the IT mask */
  itmask2 = (uint8_t)((uint8_t)1 << itmask1);
  /* Get the SPI_IT enable bit status */
  enablestatus = (uint8_t)((uint8_t)SPI->SR & itmask2);
  /* Check the status of the specified SPI interrupt */
  if (((SPI->ICR & itpos) != (uint8_t)RESET) && enablestatus)
  {
    /* SPI_IT is set */
    pendingbitstatus = SET;
  }
  else
  {
    /* SPI_IT is reset */
    pendingbitstatus = RESET;
  }
  /* Return the SPI_IT status */
  return  pendingbitstatus;
}

/**
  * @brief Clears the WKUP (Wake-up) interrupt pending bit.
  * @param None
  * @retval None
  * @note
  * - OVR (OverRun Error) interrupt pending bit is cleared by software sequence:
  *   a read operation to SPI_DR register (SPI_ReceiveData()) followed by
  *   a read operation to SPI_SR register (SPI_GetITStatus()).
  * - MODF (Mode Fault) interrupt pending bit is cleared by software sequence:
  *   a read/write operation to SPI_SR register (SPI_GetITStatus()) followed by
  *   a write operation to SPI_CR1 register (SPI_Cmd() to enable the SPI).
  */
void SPI_ClearITPendingBit(void)
{
  /* Clear the WKUP pending bit */
  SPI->SR = (uint8_t)(~SPI_SR_WKUP);
}
/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
