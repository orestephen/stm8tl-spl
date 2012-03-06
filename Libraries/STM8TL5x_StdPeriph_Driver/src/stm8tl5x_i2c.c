/**
  ******************************************************************************
  * @file    stm8tl5x_i2c.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    01-March-2012
  * @brief   This file contains all the functions for the I2C peripheral.
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
#include "stm8tl5x_i2c.h"
#include "stm8tl5x_clk.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* I2C FLAG mask */
#define FLAG_Mask                   ((uint16_t)0x00FF)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

/**
  * @addtogroup I2C_Public_Functions
  * @{
  */

/**
  * @brief Deinitializes the I2C peripheral registers to their default reset values.
  * @param None
  * @retval None
  */
void I2C_DeInit(void)
{
  I2C->CR1 = I2C_CR1_RESET_VALUE;
  I2C->CR2 = I2C_CR2_RESET_VALUE;
  I2C->FREQR = I2C_FREQR_RESET_VALUE;
  I2C->OAR1L = I2C_OAR1L_RESET_VALUE;
  I2C->OAR1H = I2C_OAR1H_RESET_VALUE;
  I2C->OAR2 = I2C_OAR2_RESET_VALUE;
  I2C->ITR = I2C_ITR_RESET_VALUE;
  I2C->CCRL = I2C_CCRL_RESET_VALUE;
  I2C->CCRH = I2C_CCRH_RESET_VALUE;
  I2C->TRISER = I2C_TRISER_RESET_VALUE;
}

/**
  * @brief Initializes the I2C according to the specified parameters in standard or fast mode.
  * @param[in] OutputClockFrequency    Specifies the output clock frequency in Hz.
  * @param[in] OwnAddress1             Specifies the own address 1.
  * @param[in] I2C_DutyCycle           Specifies the duty cycle to apply.
  * @param[in] I2C_Ack                 Specifies the acknowledge mode to apply.
  * @param[in] I2C_AcknowledgedAddress Specifies the addressing mode to apply.
  * @retval None
  */
void I2C_Init(uint32_t OutputClockFrequency, uint16_t OwnAddress1,
              I2C_DutyCycle_TypeDef I2C_DutyCycle, I2C_Ack_TypeDef I2C_Ack,
              I2C_AcknowledgedAddress_TypeDef I2C_AcknowledgedAddress)
{
  uint16_t result = 0x0004;
  uint16_t tmpval = 0;
  uint8_t tmpccrh = 0;
  uint8_t input_clock = 0;

  /* Check the parameters */
  assert_param(IS_I2C_OUTPUT_CLOCK_FREQ(OutputClockFrequency));
  assert_param(IS_I2C_OWN_ADDRESS(OwnAddress1));
  assert_param(IS_I2C_DUTY_CYCLE(I2C_DutyCycle));
  assert_param(IS_I2C_ACK_STATE(I2C_Ack));
  assert_param(IS_I2C_ACKNOWLEDGE_ADDRESS(I2C_AcknowledgedAddress));

  /* Get system clock frequency */
  input_clock = (uint8_t)(CLK_GetClockFreq() / 1000000);

  /*------------------------- I2C FREQ Configuration ------------------------*/
  /* Clear frequency bits */
  I2C->FREQR &= (uint8_t)(~I2C_FREQR_FREQ);
  /* Write new value */
  I2C->FREQR |= input_clock;

  /*--------------------------- I2C CCR Configuration ------------------------*/
  /* Disable I2C to configure TRISER */
  I2C->CR1 &= (uint8_t)(~I2C_CR1_PE);

  /* Clear CCRH & CCRL */
  I2C->CCRH &= (uint8_t)(~(I2C_CCRH_FS | I2C_CCRH_DUTY | I2C_CCRH_CCR));
  I2C->CCRL &= (uint8_t)(~I2C_CCRL_CCR);

  /* Detect Fast or Standard mode depending on the Output clock frequency selected */
  if (OutputClockFrequency > I2C_MAX_STANDARD_FREQ) /* FAST MODE */
  {
    /* Set F/S bit for fast mode */
    tmpccrh = I2C_CCRH_FS;

    if (I2C_DutyCycle == I2C_DutyCycle_2)
    {
      /* Fast mode speed calculate: Tlow/Thigh = 2 */
      result = (uint16_t)((input_clock * 1000000) / (OutputClockFrequency * 3));
    }
    else /* I2C_DutyCycle_16_9 */
    {
      /* Fast mode speed calculate: Tlow/Thigh = 16/9 */
      result = (uint16_t)((input_clock * 1000000) / (OutputClockFrequency * 25));
      /* Set DUTY bit */
      tmpccrh |= I2C_CCRH_DUTY;
    }

    /* Verify and correct CCR value if below minimum value */
    if (result < (uint16_t)0x0001)
    {
      /* Set the minimum allowed value */
      result = (uint16_t)0x0001;
    }

    /* Set Maximum Rise Time: 300ns max in Fast Mode
    = [300ns/(1/input_clock.10e6)]+1
    = [(input_clock * 3)/10]+1 */
    tmpval = ((input_clock * 3) / 10) + 1;
    I2C->TRISER = (uint8_t)tmpval;

  }
  else /* STANDARD MODE */
  {
    /* Calculate standard mode speed */
    result = (uint16_t)((input_clock * 1000000) / (OutputClockFrequency << (uint8_t)1));

    /* Verify and correct CCR value if below minimum value */
    if (result < (uint16_t)0x0004)
    {
      /* Set the minimum allowed value */
      result = (uint16_t)0x0004;
    }

    /* Set Maximum Rise Time: 1000ns max in Standard Mode
    = [1000ns/(1/input_clock.10e6)]+1
    = input_clock+1 */
    I2C->TRISER = (uint8_t)(input_clock + 1);
  }

  /* Write CCR with new calculated value */
  I2C->CCRL = (uint8_t)result;
  I2C->CCRH = (uint8_t)(((uint8_t)(result >> 8) & I2C_CCRH_CCR) | tmpccrh);

  /* Enable I2C */
  I2C->CR1 |= I2C_CR1_PE;

  /* Clear the I2C Ack bit */
  I2C->CR2 &= (uint8_t)(~I2C_CR2_ACK);
  /* Configure I2C acknowledgement */
  I2C->CR2 |= (uint8_t)I2C_Ack;

  /*--------------------------- I2C OAR1 Configuration ------------------------*/
  I2C->OAR1L = (uint8_t)(OwnAddress1); // address bits 0 to 7 only
  I2C->OAR1H = (uint8_t)((uint8_t)I2C_AcknowledgedAddress | I2C_OAR1H_ADDCONF |
                         (uint8_t)((OwnAddress1 & (uint16_t)0x0300) >> (uint8_t)7)); // address bits 8 to 9 only
}

/**
  * @brief  Configures the specified I2C own address2.
  * @param  OwnAddress2 Specifies the 7bit I2C own address2.
  * @retval None
  */
void I2C_OwnAddress2Config(uint8_t OwnAddress2)
{
  uint8_t tmpreg;

  /* Get the current register value */
  tmpreg = I2C->OAR2;

  /* Reset I2C Own address2 bits [7:1] */
  tmpreg &= (uint8_t)(~I2C_OAR2_ADD);

  /* Set I2C Own address2 */
  tmpreg |= (uint8_t)((uint8_t)OwnAddress2 & (uint8_t)0xFE);

  /* Store the new register value */
  I2C->OAR2 = tmpreg;
}

/**
  * @brief  Enables or disables the specified I2C dual addressing mode.
  * @param  NewState New state of the I2C dual addressing mode.
  * @retval None
  */
void I2C_DualAddressCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable dual addressing mode */
    I2C->OAR2 |= I2C_OAR2_ENDUAL;
  }
  else
  {
    /* Disable dual addressing mode */
    I2C->OAR2 &= (uint8_t)(~I2C_OAR2_ENDUAL);
  }
}

/**
  * @brief Enables or disables the I2C peripheral.
  * @param[in] NewState Indicate the new I2C peripheral state.
  * @retval None
  */
void I2C_Cmd(FunctionalState NewState)
{
  /* Check function parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable I2C peripheral */
    I2C->CR1 |= I2C_CR1_PE;
  }
  else
  {
    /* Disable I2C peripheral */
    I2C->CR1 &= (uint8_t)(~I2C_CR1_PE);
  }
}

/**
  * @brief Enables or disables the I2C General Call feature.
  * @param[in] NewState State of the General Call feature.
  * @retval None
  */
void I2C_GeneralCallCmd(FunctionalState NewState)
{
  /* Check function parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable General Call */
    I2C->CR1 |= I2C_CR1_ENGC;
  }
  else
  {
    /* Disable General Call */
    I2C->CR1 &= (uint8_t)(~I2C_CR1_ENGC);
  }
}

/**
  * @brief Generates I2C communication START condition.
  * @param[in] NewState Enable or disable the start condition.
  * @retval None
  * @note CCR must be programmed (i.e. I2C_Init function must
  * have been called with a valid I2C_ClockSpeed)
  */
void I2C_GenerateSTART(FunctionalState NewState)
{
  /* Check function parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Generate a START condition */
    I2C->CR2 |= I2C_CR2_START;
  }
  else
  {
    /* Disable the START condition generation */
    I2C->CR2 &= (uint8_t)(~I2C_CR2_START);
  }
}

/**
  * @brief Generates I2C communication STOP condition.
  * @param[in] NewState Enable or disable the stop condition.
  * @retval None
  */
void I2C_GenerateSTOP(FunctionalState NewState)
{
  /* Check function parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Generate a STOP condition */
    I2C->CR2 |= I2C_CR2_STOP;
  }
  else
  {
    /* Disable the STOP condition generation */
    I2C->CR2 &= (uint8_t)(~I2C_CR2_STOP);
  }
}

/**
  * @brief Enables or disables I2C software reset.
  * @param[in] NewState Specifies the new state of the I2C software reset.
  * @retval None
  * @note Before calling this function with the ENABLE parameter, make sure the
  * I2C lines are released and the bus is free.
  */
void I2C_SoftwareResetCmd(FunctionalState NewState)
{
  /* Check function parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Peripheral under reset */
    I2C->CR2 |= I2C_CR2_SWRST;
  }
  else
  {
    /* Peripheral not under reset */
    I2C->CR2 &= (uint8_t)(~I2C_CR2_SWRST);
  }
}

/**
  * @brief Enables or disables the I2C clock stretching.
  * @param[in] NewState Specifies the new state of the I2C Clock stretching.
  * @retval None
  */
void I2C_StretchClockCmd(FunctionalState NewState)
{
  /* Check function parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Clock Stretching Enable */
    I2C->CR1 &= (uint8_t)(~I2C_CR1_NOSTRETCH);
  }
  else
  {
    /* Clock Stretching Disable (Slave mode) */
    I2C->CR1 |= I2C_CR1_NOSTRETCH;
  }
}

/**
  * @brief Enable or Disable the I2C acknowledge feature.
  * @param[in] NewState Specifies the new state of the I2C acknowledge.
  * @retval None
  */
void I2C_AcknowledgeConfig(FunctionalState NewState)
{
  /* Check function parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the acknowledgement */
    I2C->CR2 |= I2C_CR2_ACK;
  }
  else
  {
    /* Disable the acknowledgement */
    I2C->CR2 &= (uint8_t)(~I2C_CR2_ACK);
  }
}

/**
  * @brief Selects the specified I2C Ack position.
  * @param[in] I2C_AckPosition Specifies the Ack position.
  * @retval None
  * @note This function must be called before data reception starts.
  */
void I2C_AckPositionConfig(I2C_AckPosition_TypeDef I2C_AckPosition)
{
  /* Check function parameters */
  assert_param(IS_I2C_ACK_POSITION(I2C_AckPosition));

  /* Clear the I2C Ack position */
  I2C->CR2 &= (uint8_t)(~I2C_CR2_POS);

  /* Configure the specified I2C Ack position*/
  I2C->CR2 |= I2C_AckPosition;
}

/**
  * @brief Enables or disables the specified I2C interrupt.
  * @param[in] I2C_IT   Name of the interrupt to enable or disable.
  * @param[in] NewState State of the interrupt to apply.
  * @retval None
  */
void I2C_ITConfig(I2C_ITONLY_TypeDef I2C_IT, FunctionalState NewState)
{
  /* Check functions parameters */
  assert_param(IS_I2C_CONFIG_IT(I2C_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected I2C interrupts */
    I2C->ITR |= (uint8_t)I2C_IT;
  }
  else
  {
    /* Disable the selected I2C interrupts */
    I2C->ITR &= (uint8_t)(~(uint8_t)I2C_IT);
  }
}

/**
  * @brief Selects the specified I2C fast mode duty cycle.
  * @param[in] I2C_DutyCycle Specifies the duty cycle to apply.
  * @retval None
  */
void I2C_FastModeDutyCycleConfig(I2C_DutyCycle_TypeDef I2C_DutyCycle)
{
  /* Check function parameters */
  assert_param(IS_I2C_DUTY_CYCLE(I2C_DutyCycle));

  if (I2C_DutyCycle == I2C_DutyCycle_16_9)
  {
    /* I2C fast mode Tlow/Thigh = 16/9 */
    I2C->CCRH |= I2C_CCRH_DUTY;
  }
  else /* I2C_DUTYCYCLE_2 */
  {
    /* I2C fast mode Tlow/Thigh = 2 */
    I2C->CCRH &= (uint8_t)(~I2C_CCRH_DUTY);
  }
}

/**
  * @brief Checks whether the last I2C Event is equal to the one passed as parameter.
  * @param[in] I2C_Event Specifies the event to be checked.
  * @retval ErrorStatus Status of the event
  * - SUCCESS : last event is equal to the I2C_Event
  * - ERROR : last event is different from the I2C_Event
  * @note This function must be called only once as the flags can be reset by reading the registers.
  */
ErrorStatus I2C_CheckEvent(I2C_Event_TypeDef I2C_Event)
{
  uint16_t lastevent = 0;
  uint8_t flags_SR1 = 0;
  uint8_t flags_SR3 = 0;
  ErrorStatus status = ERROR;

  /* Check the parameters */
  assert_param(IS_I2C_EVENT(I2C_Event));

  if (I2C_Event == I2C_EVENT_SLAVE_ACK_FAILURE)
  {
    /* This flag is reset only by writing 0 in the AF bit or by disabling the I2C peripheral */
    lastevent = (uint16_t)(I2C->SR2 & I2C_SR2_AF);
  }
  else
  {
    /* Read flags */
    flags_SR1 = I2C->SR1;
    flags_SR3 = I2C->SR3;
    lastevent = (((uint16_t)flags_SR3 << (uint8_t)8) | (uint16_t)flags_SR1);
  }

  /* Check whether the last event is equal to I2C_EVENT */
  if (lastevent == I2C_Event)
  {
    /* SUCCESS: last event is equal to I2C_EVENT */
    status = SUCCESS;
  }
  else
  {
    /* ERROR: last event is different from I2C_EVENT */
    status = ERROR;
  }

  return status;
}

/**
  * @brief Returns the last I2C Event.
  * @param None
  * @retval I2C_Event_TypeDef The last event
  */
I2C_Event_TypeDef I2C_GetLastEvent(void)
{
  uint16_t lastevent = 0;
  uint8_t flags_SR1 = 0;
  uint8_t flags_SR3 = 0;

  if ((I2C->SR2 & I2C_SR2_AF) != 0)
  {
    lastevent = I2C_EVENT_SLAVE_ACK_FAILURE;
  }
  else
  {
    /* Read the I2C status register */
    flags_SR1 = I2C->SR1;
    flags_SR3 = I2C->SR3;

    /* Get the last event value from I2C status register */
    lastevent = (((uint16_t)flags_SR3 << (uint8_t)8) | (uint16_t)flags_SR1);
  }

  return (I2C_Event_TypeDef)lastevent;
}

/**
  * @brief Returns the most recent received data.
  * @param None
  * @retval uint8_t The value of the received byte data.
  */
uint8_t I2C_ReceiveData(void)
{
  /* Return the data present in the DR register */
  return ((uint8_t)I2C->DR);
}

/**
  * @brief Transmits the 7-bit address (to select the slave device).
  * @param[in] Address       Specifies the slave address which will be transmitted.
  * @param[in] I2C_Direction Specifies whether the I2C device will be a Transmitter or a Receiver.
  * @retval None
  */
void I2C_Send7bitAddress(uint8_t Address, I2C_Direction_TypeDef I2C_Direction)
{
  /* Check function parameters */
  assert_param(IS_I2C_ADDRESS(Address));
  assert_param(IS_I2C_DIRECTION(I2C_Direction));

  /* Clear bit0 (direction) just in case */
  Address &= (uint8_t)0xFE;

  /* Send the Address + Direction */
  I2C->DR = (uint8_t)(Address | (uint8_t)I2C_Direction);
}

/**
  * @brief Send a byte by writing in the DR register.
  * @param[in] Data Byte to be sent.
  * @retval None
  */
void I2C_SendData(uint8_t Data)
{
  /* Write in the DR register the data to be sent */
  I2C->DR = Data;
}

/**
  * @brief Checks whether the specified I2C flag is set or not.
  * @param[in] I2C_FLAG Specifies the flag to check.
  * @retval FlagStatus The new state of I2C_FLAG.
  */
FlagStatus I2C_GetFlagStatus(I2C_FLAG_TypeDef I2C_FLAG)
{
  uint8_t tempreg = 0;
  uint8_t regindex = 0;
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_I2C_GET_FLAG(I2C_FLAG));

  /* Read flag register index (see I2C_FLAG_TypeDef definition) */
  regindex = (uint8_t)(I2C_FLAG >> 8);

  /* Check SRx index */
  switch (regindex)
  {
      /* Read SR1 */
    case 0x01:
      tempreg = (uint8_t)I2C->SR1;
      break;
      /* Read SR2 */
    case 0x02:
      tempreg = (uint8_t)I2C->SR2;
      break;
      /* Read SR3 */
    case 0x03:
      tempreg = (uint8_t)I2C->SR3;
      break;
    default:
      tempreg = 0;
      break;
  }

  /* Check the status of the specified I2C flag */
  if ((tempreg & (uint8_t)I2C_FLAG) != 0)
  {
    /* Flag is set */
    bitstatus = SET;
  }
  else
  {
    /* Flag is reset */
    bitstatus = RESET;
  }

  return bitstatus;
}

/**
  * @brief Clear flags of SR2 status register only
  * @param[in] I2C_FLAG Specifies the SR2 register flag(s) to clear
  * @note
  * The function parameter can be any combination of the following values:
  * - I2C_FLAG_WUFH : Wakeup from Halt
  * - I2C_FLAG_OVR  : Overrun/Underrun flag (Slave mode)
  * - I2C_FLAG_AF   : Acknowledge failure flag
  * - I2C_FLAG_ARLO : Arbitration lost flag (Master mode)
  * - I2C_FLAG_BERR : Bus error flag.
  * @warning This function does NOT clear the STOPF, ADD10, BTF, ADDR and SB flags.
  * Please read the stm8tl5x datasheet for the correct sequence to apply for
  * the clearing of these flags.
  * @retval None
  */
void I2C_ClearFlag(I2C_FLAG_TypeDef I2C_FLAG)
{
  /* Check the parameters */
  assert_param(IS_I2C_CLEAR_FLAG(I2C_FLAG));

  /* Clear the selected I2C flag */
  I2C->SR2 = (uint8_t)(~I2C_FLAG);
}

/**
  * @brief Checks whether the specified I2C interrupt has occurred or not.
  * @param[in] I2C_IT Specifies the interrupt source to check.
  * @retval ITStatus The new state of I2C_IT
  * @note
  * The function parameter can be one of the following values:
  * Flags of SR1 register:
  * - I2C_IT_TXE: Data register empty flag (Transmitter)
  * - I2C_IT_RXNE: Data register not empty (Receiver) flag
  * - I2C_IT_STOPF: Stop detection flag (Slave mode)
  * - I2C_IT_ADD10: 10-bit header sent flag (Master mode)
  * - I2C_IT_BTF: Byte transfer finished flag
  * - I2C_IT_ADDR: Address sent flag (Master mode) “ADSL”
  *                Address matched flag (Slave mode)“ENDAD”
  * - I2C_IT_SB: Start bit flag (Master mode)
  * Flags of SR2 register:
  * - I2C_IT_WUFH: Wakeup from Halt
  * - I2C_IT_OVR: Overrun/Underrun flag (Slave mode)
  * - I2C_IT_AF: Acknowledge failure flag
  * - I2C_IT_ARLO: Arbitration lost flag (Master mode)
  * - I2C_IT_BERR: Bus error flag
  */
ITStatus I2C_GetITStatus(I2C_IT_TypeDef I2C_IT)
{
  ITStatus bitstatus = RESET;
  uint8_t enablestatus = 0;

  /* Check the parameters */
  assert_param(IS_I2C_GET_IT(I2C_IT));

  /* Check if the interrupt source is enabled or not */
  enablestatus = (uint8_t)(((I2C_IT & ITEN_MASK) >> (uint8_t)8) & (I2C->ITR)) ;

  if ((uint16_t)(I2C_IT & REGISTER_MASK) == REGISTER_SR1_INDEX) /* SR1 register */
  {
    /* Check the status of the specified I2C flag */
    if (((I2C->SR1 & (uint8_t)I2C_IT) != RESET) && enablestatus)
    {
      /* I2C_IT is set */
      bitstatus = SET;
    }
    else
    {
      /* I2C_IT is reset */
      bitstatus = RESET;
    }
  }
  else /* SR2 register */
  {
    /* Check the status of the specified I2C flag */
    if (((I2C->SR2 & (uint8_t)I2C_IT) != RESET) && enablestatus)
    {
      /* I2C_IT is set */
      bitstatus = SET;
    }
    else
    {
      /* I2C_IT is reset */
      bitstatus = RESET;
    }
  }

  return  bitstatus;
}

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
