/**
  @page FLASH_WriteEraseBlockOperation FLASH - Write/Erase Block on Flash program memory

  @verbatim
  *********************** (C) COPYRIGHT STMicroelectronics *********************
  * @file    FLASH/FLASH_WriteEraseBlockOperation/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  * @brief   Write/Erase Block on Flash program memory
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

  This example provides a short description on how to use FLASH Write/Erase Block mode 
  on data eeprom memory and benefit for the Read While Write feature:
  - Program a block at a specified address (0x9900).
  - Check program block (Read byte).
  - Erase block using Erase block function.
  - Check erase (using Read byte).


@par Directory contents

  - FLASH\FLASH_WriteEraseBlockOperation\main.c             Main file containing the "main" function
  - FLASH\FLASH_WriteEraseBlockOperation\stm8tl5x_conf.h    Library Configuration file
  - FLASH\FLASH_WriteEraseBlockOperation\stm8tl5x_it.c      Interrupt routines source
  - FLASH\FLASH_WriteEraseBlockOperation\stm8tl5x_it.h      Interrupt routines declaration
  - FLASH\FLASH_WriteEraseBlockOperation\stm8tl5x.lkf       stm8tl5x linker file for STVD and Cosmic compiler


@par Hardware and Software environment

  - This example runs on STM8TL5x devices.
  
  - This example has been tested on a generic
    board and ST Visual Develop (STVD) toolchain (Cosmic compiler).
    And can be easily tailored to any other development board.
    
  @b Note: This example is working with Cosmic compiler only.

 
  @par How to use it ?

  In order to make the program work, you must do the following :
  - Create a project and setup all project configuration
  - Use the linker file given in the directory (stm8tl5x.lkf)
       In STVD Select "Project->Settings->Linker->Category->Input" then unchecks the "Auto" box 
       and in the "Script Lkf file name" field add the linker file.

  - Uncomment the line "#define USE_COSMIC_SECTIONS  (1)" to use the cosmic section in the stm8tl5x.h file.
  - Add the required Library files:
    - stm8tl5x_flash.c
  

  - Rebuild all files: Build-> Rebuild all. 
  - Load project image: Debug->Start Debugging
  - Run program: Debug->Run (Ctrl+F5)

  - You can check the value of the bytes at the specified addresses by using the memory window in STVD.
  - The data read from the data memory is compared with the expected values.
  	The result of this comparison is stored in the "OperationStatus" variable.
   
  */

* <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
*/
