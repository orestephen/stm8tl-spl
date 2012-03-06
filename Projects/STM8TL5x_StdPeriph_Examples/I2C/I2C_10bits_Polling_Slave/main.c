/**
  ******************************************************************************
  * @file    I2C/I2C_10bits_Polling_Slave/main.c
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
  * @addtogroup I2C_10bits_Polling_Slave
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
#define OWN_ADDRESS_1  ((uint16_t)0x0102) // Slave
#define BUFFERSIZE     ((uint8_t)5) // Change also I2C_Buffer_Tx[]

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
uint8_t I2C_Buffer_Tx[BUFFERSIZE] = {0x00, 0x55, 0xAA, 0x33, 0xCC};
uint8_t I2C_Buffer_Rx[BUFFERSIZE];

/* Private function prototypes -----------------------------------------------*/
void ReceiveBuffer(void);
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

  /* Initialize the I2C */
  I2C_DeInit();
  I2C_Init(OUTPUT_FREQ, OWN_ADDRESS_1, I2C_DutyCycle_2, I2C_Ack_Enable, I2C_AcknowledgedAddress_10bit);

  GPIO_ResetBits(LEDS_PORT, (LED1_PIN | LED2_PIN)); // All LEDs are ON

  while(1)
  {
    ReceiveBuffer();
  }

}

/**
  ******************************************************************************
  * @brief Receive a buffer with I2C
  * @param None
  * @retval None
  ******************************************************************************
  */
void ReceiveBuffer(void)
{

  uint8_t Rx_Idx = 0;
  uint8_t data_ok;

  /* Wait while the bus is busy */
  while(I2C_GetFlagStatus(I2C_FLAG_BUSY));

  /* Test on EV1 and clear it */
  while(!I2C_CheckEvent(I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED));
  I2C_GetFlagStatus(I2C_FLAG_ADDR);
  (void)(I2C->SR3);

  /* Receive data */
  Rx_Idx = 0;
  while (Rx_Idx < BUFFERSIZE)
  {
    /* Test on EV2 and clear it */
    while(!I2C_CheckEvent(I2C_EVENT_SLAVE_BYTE_RECEIVED));
    /* Store received data  */
    I2C_Buffer_Rx[Rx_Idx++] = I2C_ReceiveData();
  }
  
  /* Test on EV4 and clear it */
  while(!I2C_CheckEvent(I2C_EVENT_SLAVE_STOP_DETECTED));
 
  /* Clear STOPF flag */
  I2C_GetFlagStatus(I2C_FLAG_STOPF);
  I2C->CR2 = I2C->CR2;
	
  /* Test received data */
  data_ok = 1;
  for (Rx_Idx = 0; Rx_Idx < BUFFERSIZE; Rx_Idx++)
  {
    if (I2C_Buffer_Rx[Rx_Idx] != I2C_Buffer_Tx[Rx_Idx]) data_ok = 0;
  }

  if (data_ok)
  {
    GPIO_ToggleBits(LEDS_PORT, LED1_PIN);
  }
  else
  {
    GPIO_ToggleBits(LEDS_PORT, LED2_PIN);
  }

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
