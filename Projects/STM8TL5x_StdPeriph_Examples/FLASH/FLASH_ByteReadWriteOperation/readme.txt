/**
  @page FLASH_ByteReadWriteOperation FLASH - Read, Write, Erase byte

  @verbatim
  *********************** (C) COPYRIGHT STMicroelectronics *********************
  * @file    FLASH/FLASH_ByteReadWriteOperation/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  * @brief   Read, Write, Erase byte
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
  @endverbatim


@par Example Description

  This example provides a short description on how to use FLASH Read/Write/Erase byte modes:
  - Read a byte at a specified address (0x9000).
  - Write complement value (of previous byte value) at address +1 (0x9001).
  - Check programmed byte (using read function)
  - Erase 2 bytes at address & address+1
  - Check 2 bytes are erased (value must be equal to 0x00).


@par Directory contents

  - FLASH\FLASH_ByteReadWriteOperation\main.c                    Main file containing the "main" function
  - FLASH\FLASH_ByteReadWriteOperation\stm8tl5x_conf.h           Library Configuration file
  - FLASH\FLASH_ByteReadWriteOperation\stm8tl5x_it.c             Interrupt routines source (not used in this example)
  - FLASH\FLASH_ByteReadWriteOperation\stm8tl5x_it.h             Interrupt routines declaration


@par Hardware and Software environment

  - This example runs on STM8TL5x devices.

  - This example has been tested on a generic
    board and ST Visual Develop (STVD) toolchain (Cosmic and Raisonance compilers).
    And can be easily tailored to any other development board.

 
  @par How to use it ?

  In order to make the program work, you must do the following :
  - Create a project and setup all project configuration
  - Add the required Library files :
    - stm8tl5x_flash.c
  

  - Rebuild all files: Build-> Rebuild all. 
  - Load project image: Debug->Start Debugging
  - Run program: Debug->Run (Ctrl+F5)

  - You can check the value of the bytes at the specified addresses by using the memory window in STVD.
  - The data read from the data memory is compared with the expected values.
    The result of this comparison is stored in the "OperationStatus" variable.
   
* <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
*/
