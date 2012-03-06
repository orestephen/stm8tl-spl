/**
  ******************************************************************************
  * @file    I2C/I2C_10bits_Polling_Master/main.c
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
  * @addtogroup I2C_10bits_Polling_Master
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Evalboard I/Os configuration */
#define LEDS_PORT   (GPIOB)
#define LED1_PIN    (GPIO_Pin_2)
#define LED2_PIN    (GPIO_Pin_3)
#define BUTTON_PORT (GPIOB)
#define BUTTON_PIN  (GPIO_Pin_5)

/* I2C settings */
#define OUTPUT_FREQ    ((uint32_t)200000)
#define OWN_ADDRESS_1  ((uint8_t)0x10) // Master
#define SLAVE_ADDRESS  ((uint16_t)0x0102)
#define BUFFERSIZE     ((uint8_t)5) // Change also I2C_Buffer_Tx[]

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
bool ButtonPressed = FALSE;
uint8_t I2C_Buffer_Tx[BUFFERSIZE] = {0x00, 0x55, 0xAA, 0x33, 0xCC};

/* Private function prototypes -----------------------------------------------*/
void SendBuffer(void);
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
  I2C_DeInit();
  I2C_Init(OUTPUT_FREQ, OWN_ADDRESS_1, I2C_DutyCycle_2, I2C_Ack_Enable, I2C_AcknowledgedAddress_10bit);

  enableInterrupts();

  while(1)
  {
    if (ButtonPressed == TRUE)
    {
      ButtonPressed = FALSE;
      SendBuffer();
      GPIO_ToggleBits(LEDS_PORT, LED2_PIN);
    }
    GPIO_ToggleBits(LEDS_PORT, LED1_PIN);
    Delay((uint16_t)60000);
  }

}

/**
  ******************************************************************************
  * @brief Send buffer with I2C
  * @param None
  * @retval None
  ******************************************************************************
  */
void SendBuffer(void)
{

  uint8_t Tx_Idx = 0;

  /* Wait while the bus is busy */
  while(I2C_GetFlagStatus(I2C_FLAG_BUSY));

  /* Send START condition */
  I2C_GenerateSTART(ENABLE);
  
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT));

  /* Send Header to Slave for write:
     0x1111 0xx0 with xx = most significant bits of the address */
  I2C_SendData(((SLAVE_ADDRESS & 0xFF00) >> 7) | 0xF0);
	
  /* Test on EV9 and clear it */
  while(!I2C_CheckEvent(I2C_EVENT_MASTER_MODE_ADDRESS10));
	
  /* Send Slave address low byte for write */
  I2C_Send7bitAddress((uint8_t)SLAVE_ADDRESS, I2C_Direction_Transmitter);
  
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  I2C_GetFlagStatus(I2C_FLAG_ADDR);
  (void)(I2C->SR3);

  /* Send data */
  Tx_Idx = 0;
  while (Tx_Idx < BUFFERSIZE)
  {
    /* Send data */
    I2C_SendData(I2C_Buffer_Tx[Tx_Idx++]);
    /* Test on EV8 and clear it */
    while(!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  }

  /* Send STOP Condition */
  I2C_GenerateSTOP(ENABLE);

  /* Change the first transmitted byte to differentiate the transactions */
  I2C_Buffer_Tx[0] += 1;

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
