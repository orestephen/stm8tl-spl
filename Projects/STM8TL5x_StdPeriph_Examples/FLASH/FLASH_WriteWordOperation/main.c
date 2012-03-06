/**
  ******************************************************************************
  * @file    FLASH/FLASH_WriteWordOperation/main.c
  * @brief   This file contains the main function for FLASH write word example.
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
  * @addtogroup FLASH_WriteWord
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;
TestStatus OperationStatus;
/* Private function prototypes -----------------------------------------------*/
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
	uint16_t start_add = 0x9000;
  uint16_t add;
  uint32_t new_val = 0x01234567;
  uint8_t sub_test_count;
  uint8_t val;

  /* Define FLASH programming time */
  FLASH_SetProgrammingTime(FLASH_ProgramMode_Standard);
  
	/* Unlock flash program memory */
  FLASH_Unlock(FLASH_MemType_Program);

  /* Program word at addres 0x9000 */
	FLASH_ProgramWord(start_add, new_val);

  /* Check program word action */
  val = FLASH_ReadByte(start_add);
  add = start_add;
  if (val != BYTE_3(new_val))
  {
    /* Error */
    OperationStatus = FAILED;
    /* OperationStatus = PASSED, if the data written/read to/from FLASH Program memory is correct */
    /* OperationStatus = FAILED, if the data written/read to/from FLASH Program memory is corrupted */
    while (1);
  }

  add += 1;
  val = FLASH_ReadByte(add);
  if (val != BYTE_2(new_val))
  {
    /* Error */
    OperationStatus = FAILED;
    /* OperationStatus = PASSED, if the data written/read to/from FLASH Program memory is correct */
    /* OperationStatus = FAILED, if the data written/read to/from FLASH Program memory is corrupted */
    while (1);
  }

  add += 1;
  val = FLASH_ReadByte(add);
  if (val != BYTE_1(new_val))
  {
    /* Error */
    OperationStatus = FAILED;
    /* OperationStatus = PASSED, if the data written/read to/from FLASH Program memory is correct */
    /* OperationStatus = FAILED, if the data written/read to/from FLASH Program memory is corrupted */
    while (1);
  }

  add += 1;
  val = FLASH_ReadByte(add);
  if (val != BYTE_0(new_val))
  {
    /* Error */
    OperationStatus = FAILED;
    /* OperationStatus = PASSED, if the data written/read to/from FLASH Program memory is correct */
    /* OperationStatus = FAILED, if the data written/read to/from FLASH Program memory is corrupted */
    while (1);
  }

  /* Erase word using Erase byte */
  add = start_add;
  for (sub_test_count = 0; sub_test_count < 4; sub_test_count++)
  {
    FLASH_EraseByte(add);
    add += 1;
  }

  /* Verify Erase action */
  add = start_add;
  for (sub_test_count = 0; sub_test_count < 4; sub_test_count++)
  {
    val = FLASH_ReadByte(add);
    if (val != 0x00)
    {
      /* Error */
      OperationStatus = FAILED;
      /* OperationStatus = PASSED, if the data written/read to/from FLASH Program memory is correct */
      /* OperationStatus = FAILED, if the data written/read to/from FLASH Program memory is corrupted */
      while (1);
    }
    add += 1;
  }

  /* Pass */
  OperationStatus = PASSED;
  /* OperationStatus = PASSED, if the data written/read to/from FLASH Program memory is correct */
  /* OperationStatus = FAILED, if the data written/read to/from FLASH Program memory is corrupted */
  while (1);

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
