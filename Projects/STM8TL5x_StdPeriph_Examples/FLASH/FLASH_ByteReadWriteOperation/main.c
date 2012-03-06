/**
  ******************************************************************************
  * @file    FLASH/FLASH_ByteReadWriteOperation/main.c
  * @brief   This file contains the main function for FLASH byte read write operation example.
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
  * @addtogroup FLASH_ByteReadWriteOperation
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

    uint8_t val, val_comp = 0;
    uint32_t add = 0;

    /* Define FLASH programming time */
    FLASH_SetProgrammingTime(FLASH_ProgramMode_Standard);

    /* Unlock Data memory */
    FLASH_Unlock(FLASH_MemType_Program);

    /* Read a byte at a specified address */
    add = 0x9000;
    val = FLASH_ReadByte(add);

    /* Program complement value (of previous read byte) at previous address + 1 */
    val_comp = (uint8_t)(~val);
    FLASH_ProgramByte((add + 1), val_comp);

    /* Check program action */
    val = FLASH_ReadByte((add + 1));
    if (val != val_comp)
    {
        /* Error */
        OperationStatus = FAILED;
        /* OperationStatus = PASSED, if the data written/read to/from FLASH program memory is correct */
        /* OperationStatus = FAILED, if the data written/read to/from FLASH program memory is corrupted */
        while (1);
    }

    /* Erase byte at a specified address & address + 1 */
    FLASH_EraseByte(add);
    FLASH_EraseByte((add + 1));
    /* Erase action */
    val = FLASH_ReadByte(add);
    val_comp = FLASH_ReadByte((add + 1));
    if ((val != 0x00) & (val_comp != 0x00))
    {
        /* Error */
        OperationStatus = FAILED;
        /* OperationStatus = PASSED, if the data written/read to/from FLASH program memory is correct */
        /* OperationStatus = FAILED, if the data written/read to/from FLASH program memory is corrupted */
        while (1);
    }

    /* Pass */
    OperationStatus = PASSED;
    /* OperationStatus = PASSED, if the data written/read to/from FLASH program memory is correct */
    /* OperationStatus = FAILED, if the data written/read to/from FLASH program memory is corrupted */
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
