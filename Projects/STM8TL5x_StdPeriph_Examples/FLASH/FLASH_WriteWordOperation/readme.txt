/**
  @page FLASH_WriteWordOperation FLASH - Write word, Erase byte

  @verbatim
  *********************** (C) COPYRIGHT STMicroelectronics *********************
  * @file    FLASH/FLASH_WriteWordOperation/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  * @brief   FLASH Write word, Erase byte
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

  This example provides a short description on how to use FLASH Program word mode and Erase byte modes:
  - Program a word at a specified address (0x9000).
  - Check program word (Read byte).
  - Erase word using Erase byte.
  - Check erase.


@par Directory contents

  - FLASH\FLASH_WriteWordOperation\main.c                    Main file containing the "main" function
  - FLASH\FLASH_WriteWordOperation\stm8tl5x_conf.h           Library Configuration file
  - FLASH\FLASH_WriteWordOperation\stm8tl5x_it.c             Interrupt routines source (not used in this example)
  - FLASH\FLASH_WriteWordOperation\stm8tl5x_it.h             Interrupt routines declaration


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
