/**
  ******************************************************************************
  * @file    USART/USART_Printf/main.c
  * @brief   This file contains the main function for the USART printf example
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
#include "stdio.h"

/**
  * @addtogroup USART_Printf
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define LEDS_PORT (GPIOB)
#define LED1_PIN  (GPIO_Pin_2)

#define BUTTON_PORT (GPIOB)
#define BUTTON_PIN  (GPIO_Pin_5)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
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
	  uint16_t index = 0;
		
    /* High speed internal clock prescaler: 1*/
    CLK_MasterPrescalerConfig(CLK_MasterPrescaler_HSIDiv1);
   
    /* Initialization of I/O for the LED */
    GPIO_Init(LEDS_PORT, LED1_PIN, GPIO_Mode_Out_PP_Low_Fast);
	 
 		/* Set the USART TX and USART RX at high level */
    GPIO_ExternalPullUpConfig(GPIOA, (GPIO_Pin_3 | GPIO_Pin_4), ENABLE);
		
		/* Enable USART clock */
		CLK_PeripheralClockConfig(CLK_Peripheral_USART, ENABLE);
    
    USART_DeInit();
    /* USART configuration ------------------------------------------------------*/
    /* USART configured as follow:
          - BaudRate = 115200 baud  
          - Word Length = 8 Bits
          - One Stop Bit
          - No parity
          - Receive and transmit enabled
    */
     USART_Init((uint32_t)115200, USART_WordLength_8D, USART_StopBits_1,
                USART_Parity_No, (USART_Mode_Rx | USART_Mode_Tx));

    while (1)
		{
      if ((GPIO_ReadInputData(BUTTON_PORT) & BUTTON_PIN) == (uint8_t)0x00)
			{
			  /* Output a message on Hyperterminal using printf function */
        printf("\n\r%i USART Example: retarget the C library printf function to the USART\n\r", index++);
        GPIO_ToggleBits(LEDS_PORT, LED1_PIN);
				Delay(0xFFFF);
				Delay(0xFFFF);
		  }
		}
		
}

/**
  ******************************************************************************
  * @brief Retargets the C library printf function to the USART.
  * @param[in] c Character to send
  * @retval char Character sent
  ******************************************************************************
  */
#ifdef _RAISONANCE_ 
int putchar (char c)
#else
char putchar (char c)
#endif
{
  /* Write a character to the USART */
  USART_SendData8(c);
  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART_FLAG_TXE) == RESET);
  return (c);
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
  * @param file pointer to the source file name
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
