/**
  ******************************************************************************
  * @file    I2C/I2C_EEPROM/main.c
  * @brief   This file contains the main function for I2C EEPROM Read Write example.
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
#include "i2c_ee.h"

/**
  * @addtogroup I2C_EEPROM
  * @{
  */

/* Private define ------------------------------------------------------------*/
/* Evalboard I/Os configuration */
#define LEDS_PORT (GPIOD)
#define LED2_PIN  (GPIO_Pin_4)
#define LED3_PIN  (GPIO_Pin_5)
#define LED4_PIN  (GPIO_Pin_6)

#define BUFFER_SIZE ((uint8_t)8)
#define BASE_ADDRESS ((uint16_t)0x0000)

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Delay (uint16_t nCount);
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/**
  ******************************************************************************
  * @brief How to make a write followed by a read in the E²PROM.
  * @param None
  * @retval None
  * @note
  * - Write 8 bytes on the device (E²PROM) 0xA0.
  * - Read back the 8 bytes written on the device (E²PROM) 0xA0.
  * - Check the coherency between the written and read data.
  ******************************************************************************
  */
void main()
{
    uint8_t i = 0;
    uint8_t data[8] = {0,0,0,0,0,0,0,0};
    uint8_t Buffer_size = BUFFER_SIZE;
    uint8_t Buffer[BUFFER_SIZE] = {0x04, 0x42, 0x53, 0x38, 0x97, 0x03, 0x09, 0x77}; /* Using a 2ko E² you cannot program a buff > 8 bytes in write page mode */
    uint16_t Base_Add = BASE_ADDRESS;
		

		/* Enable I2C clock */
		CLK_PeripheralClockConfig(CLK_Peripheral_I2C, ENABLE);
		
    /* Initialize I/Os in Output Mode */
    GPIO_Init(LEDS_PORT, (LED2_PIN | LED3_PIN | LED4_PIN), GPIO_Mode_Out_PP_Low_Fast);
		
    /* Optional: put here as example only */
    I2C_DeInit();
		
    /* Initialize the I2C */
    I2C_EEInit();
		
    /* All LEDs are ON per default */
    GPIO_ResetBits(LEDS_PORT, (LED2_PIN | LED3_PIN | LED4_PIN));
	
    /*** WRITE SEQUENCE ***/
    I2C_EE_PageWrite(Buffer, Base_Add, Buffer_size);
    Delay(1000); /* To let eeprom the time to finish the write operation */

    /***  READ SEQUENCE ***/
    I2C_EE_BufferRead(data, Base_Add, Buffer_size);
		
     /*** Check transmitted and received buffers ***/
    for (i =Buffer_size; i > 0; i--)
    {
        if (Buffer[i-1] != data[i-1])
        {
            /* Toggle only LED2 if error is detected */
            while (1)
            {
                GPIO_ToggleBits(LEDS_PORT, LED2_PIN);
                Delay((uint16_t)60000);
            }
        }
    }

    /* Toggle all LEDs when I2C communication is terminated and buffers are ok */
    while (1)
    {
        GPIO_ToggleBits(LEDS_PORT, (LED2_PIN | LED3_PIN | LED4_PIN));
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
