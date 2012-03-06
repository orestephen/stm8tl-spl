/**
  ******************************************************************************
  * @file    SPI/SPI_SimplexLCD/main.c
  * @brief   This file contains the main function for SPI simplex communication with LCD example.
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
#include "mono_lcd.h"

/**
  * @addtogroup SPI_SimplexLCD
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* I/Os configuration */

#define LEDS_PORT (GPIOB)
#define LED1_PIN  (GPIO_Pin_2)

#define BUTTONS_PORT (GPIOB)
#define BUTTON1_PIN  (GPIO_Pin_5)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
bool ButtonPressed = FALSE;
uint8_t i = 0;
__IO uint8_t LedState = 0, ButtonIndex = 0;
uint8_t pos = 0;

/* Private function prototypes -----------------------------------------------*/
void Delay(uint16_t nCount);

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

  /* Initialization of I/O for the LED */
  GPIO_Init(LEDS_PORT, LED1_PIN, GPIO_Mode_Out_PP_Low_Fast);
  
  /* LED1 OFF */
  GPIO_SetBits(LEDS_PORT, LED1_PIN);

  /* Initialization of I/O for the button */
  GPIO_Init(BUTTONS_PORT, BUTTON1_PIN, GPIO_Mode_In_FL_IT);

  /* Initialization of the Interrupt sensitivity for the button */
  EXTI_SetPinSensitivity(EXTI_Pin_5, EXTI_Trigger_Falling);

	/* Enable SPI clock */
  CLK_PeripheralClockConfig(CLK_Peripheral_SPI, ENABLE);

  /* Set SPI_MOSI and SPI_SCK at high level*/
	GPIO_ExternalPullUpConfig(GPIOA, (GPIO_Pin_2 | GPIO_Pin_4), ENABLE);

	/* Enable general interrupts for button reading */
	enableInterrupts();

	/* Initialize SPI */
	SPI_DeInit();
	SPI_Init(SPI_FirstBit_MSB, SPI_BaudRatePrescaler_4, SPI_Mode_Master,
           SPI_CPOL_High, SPI_CPHA_2Edge, SPI_Direction_1Line_Tx,
           SPI_NSS_Soft);
  SPI_Cmd(ENABLE);

  /* Initialize LCD */
  LCD_Init();

  /* Clear LCD lines */
  LCD_Clear();

  /* Display "moving" ST logo on first line */
  for (pos = 0x80; pos < 0x88; pos++)
  {
    LCD_Clear();
    LCD_DisplayLogo(pos);
    Delay(50000);
  }

  /* Display "moving" ST logo on second line */
  for (pos = 0x90; pos < 0x98; pos++)
  {
    LCD_Clear();
    LCD_DisplayLogo(pos);
    Delay(50000);
  }

	/* Clear LCD lines */
  LCD_Clear();

  /* Max 15 characters per line */
  LCD_PrintString(LCD_LINE1, ENABLE, DISABLE, "    SPI-LCD    ");
  LCD_PrintString(LCD_LINE2, ENABLE, DISABLE, "    example    ");

  for (i = 0; i < 6; i++)
  {
    Delay(0xFFFF);
  }

	/* Clear LCD lines */
  LCD_Clear();

  LCD_PrintString(LCD_LINE1, ENABLE, DISABLE, "Press Button");

  while (1)
  {
		
	  /* Check button status */
    if (ButtonPressed == TRUE)
    {
			
			ButtonPressed = FALSE;
     
			GPIO_ToggleBits(LEDS_PORT, LED1_PIN);
			
			LedState ^= 0x01;
     
			LCD_ClearLine(LCD_LINE2);
			LCD_PrintString(LCD_LINE2, DISABLE, DISABLE, "LED #");
			LCD_PrintDec2((uint8_t)(ButtonIndex + 1)); /* Display at current cursor position */
			LCD_SetCursorPos(LCD_LINE2, 4); /* 8th position */
			
			if (LedState == 0)
			{
				LCD_PrintChar('O');
				LCD_PrintChar('F');
				LCD_PrintChar('F');
			}
			else
			{
				LCD_PrintChar('O');
				LCD_PrintChar('N');
				LCD_PrintChar(' ');
			}
			
    }
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
