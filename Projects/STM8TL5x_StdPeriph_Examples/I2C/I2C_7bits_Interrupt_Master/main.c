/**
  ******************************************************************************
  * @file    I2C/I2C_7bits_Interrupt_Master/main.c
  * @brief   This file contains the main function for I2C example.
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
  * @addtogroup I2C_7bits_Interrupt_Master
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
/* Private variables ---------------------------------------------------------*/

/* Global variables ----------------------------------------------------------*/
bool EndCommunication = FALSE;
bool ButtonPressed = FALSE;

/* Private function prototypes -----------------------------------------------*/
void Delay (uint16_t nCount);

/* Private functions ---------------------------------------------------------*/
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
  /* Enable I2C clock */
  CLK_PeripheralClockConfig(CLK_Peripheral_I2C, ENABLE);

  /* Initialization of I/O used to drive the LEDs */
  GPIO_Init(LEDS_PORT, (LED1_PIN | LED2_PIN), GPIO_Mode_Out_PP_High_Fast);

  /* Initialization of I/O in Input Mode with Interrupt */
  GPIO_Init(BUTTON_PORT, BUTTON_PIN, GPIO_Mode_In_FL_IT);

  /* Initialization of the Interrupt sensitivity */
  EXTI_SetPinSensitivity(EXTI_Pin_5, EXTI_Trigger_Falling);

  /* Initialize the I2C */

  I2C_DeInit(); /* Optional: put here as example only */

  I2C_Cmd(DISABLE);

  /* freq = 100 kHz, own address = 0x10, 7-bits data */
  I2C_Init(100000, 0x10, I2C_DutyCycle_2, I2C_Ack_Enable, I2C_AcknowledgedAddress_7bit);

  /* Configuration of interrupts */
  I2C_ITConfig((I2C_IT_EVT |I2C_IT_BUF), ENABLE);

  enableInterrupts();

  while(1)
  {
    if (ButtonPressed == TRUE)
    {
      ButtonPressed = FALSE;
      I2C_GenerateSTART(ENABLE);
    }

    if (EndCommunication == TRUE)
    {
      EndCommunication = FALSE;
      GPIO_ToggleBits(LEDS_PORT, LED2_PIN);
    }
   
    GPIO_ToggleBits(LEDS_PORT, LED1_PIN);
    Delay((uint16_t)60000);
  }

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
