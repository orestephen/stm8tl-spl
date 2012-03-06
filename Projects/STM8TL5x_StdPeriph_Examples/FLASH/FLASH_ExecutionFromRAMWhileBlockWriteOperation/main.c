/**
  ******************************************************************************
  * @file    FLASH/FLASH_ExecutionFromRAMWhileBlockWriteOperation/main.c
  * @brief   This file contains the main function for FLASH write erase block example.
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
  * @addtogroup FLASH_BlockOperationOnFlashProgramMemory
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;
TestStatus OperationStatus;
FLASH_Status_TypeDef Status;
uint16_t timeout = 0x1000;

/* Private function prototypes -----------------------------------------------*/
int _fctcpy(char name);
FLASH_Status_TypeDef ProgramOperation(uint16_t BlockNum, FLASH_ProgramMode_TypeDef FLASH_ProgramMode, uint8_t *Buffer);

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
    uint32_t add, start_add, stop_add =0;
    uint8_t new_val2 = 0x55;
    uint8_t i = 0x00;
		uint16_t block = 0;
		uint8_t GBuffer[FLASH_BLOCK_SIZE];

    /* Cosmic routine used to copy segment "boot_Ram" in RAM memory
       (see Cosmic documentation for more details) */
 		_fctcpy('b');
		
    /* Define flash programming Time */
    FLASH_SetProgrammingTime(FLASH_ProgramTime_Standard);

    /* Unlock Program memory */
    FLASH_Unlock(FLASH_MemType_Program);

    /* Fill the buffer in RAM */
    for (i = 0; i < FLASH_BLOCK_SIZE; i++) GBuffer[i] = new_val2;
    
		/* Program the block 100 in Flash Program memory
       from address 0x9900 to 0x993F */
    block = 100;
		
	  /* The FLASH_ProgramOperation and FLASH_WaitForLastOperation are merged in the ProgramOperation function to avoid the fact that
	   the program goes back to Flash program memory, before executing the second function (to avoid that the CPU is stalled until 
	   the block program operation is complete.) */
		
    Status = ProgramOperation(block, FLASH_ProgramMode_Standard, GBuffer);

    /* Check the programmed block */
    start_add = FLASH_START_PHYSICAL_ADDRESS + ((uint16_t)block * (uint16_t)FLASH_BLOCK_SIZE);
		stop_add = start_add + (uint16_t)FLASH_BLOCK_SIZE;	

    for (add = start_add; add < stop_add; add++)
    {
      if (FLASH_ReadByte(add) != new_val2)
      {
        /* Error */
        OperationStatus = FAILED;
        /* OperationStatus = PASSED, if the data written/read to/from Flash Program memory is correct */
        /* OperationStatus = FAILED, if the data written/read to/from Flash Program memory is corrupted */
        for (;;) {}
      }
    }

    /* Pass */
    OperationStatus = PASSED;
    /* OperationStatus = PASSED, if the data written/read to/from Flash Program memory is correct */
    /* OperationStatus = FAILED, if the data written/read to/from Flash Program memory is corrupted */
		for (;;) {}
}

#pragma section (E_W_ROUTs)

FLASH_Status_TypeDef ProgramOperation(uint16_t BlockNum, FLASH_ProgramMode_TypeDef FLASH_ProgramMode, uint8_t *Buffer)
{   

  uint16_t Count = 0;
  uint16_t StartAddress;
  uint8_t My_FlagStatus = 0x00;
  
  /* Check parameters */
  assert_param(IS_FLASH_BLOCK_NUMBER(BlockNum));
  assert_param(IS_FLASH_PROGRAM_MODE(FLASH_ProgramMode));

  /* Selection of Standard or Fast programming mode */
  if (FLASH_ProgramMode == FLASH_ProgramMode_Standard)
  {
    /* Standard programming mode */
    FLASH->CR2 |= FLASH_CR2_PRG;
  }
  else
  {
    /* Fast programming mode */
    FLASH->CR2 |= FLASH_CR2_FPRG;
  }
  
  StartAddress = FLASH_START_PHYSICAL_ADDRESS;
  /* Point to the first Block address */
  StartAddress = StartAddress + ((uint16_t)BlockNum * (uint16_t)FLASH_BLOCK_SIZE);
		
  /* Copy data bytes from RAM to FLASH memory */
  for (Count = 0; Count < FLASH_BLOCK_SIZE; Count++)
  {
    *((PointerAttr uint8_t*)StartAddress + Count) = ((uint8_t)(Buffer[Count]));
  }

  /* Wait until operation completion or write protected page occured */
  while ((My_FlagStatus == 0x00) && (timeout != 0x00))
  {
    My_FlagStatus = (uint8_t)(FLASH->IAPSR & (FLASH_IAPSR_EOP | FLASH_IAPSR_WR_PG_DIS));
    timeout--;
  }

  if (timeout == 0x00 )
  {
    My_FlagStatus = FLASH_Status_TimeOut;
  }

  return((FLASH_Status_TypeDef)My_FlagStatus);
}

#pragma section ()


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
